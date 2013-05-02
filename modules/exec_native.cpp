#ifndef TEST_MODE

#include "samp.h"

#include "api/cmd2.hpp"
#include "api/pipes.hpp"

#include "pawn/pawn_marshaling_amx.hpp"
#include "pawn/marh_param.hpp"
#include "pawn/plugin.h"

#include "SDK/amxinline.h"

#include <string>
#include <list>

/* calling natives dynamically */

static bool exec_native(int pipe, const std::string& params)
{
    // native name format args...
    api::parser p1("*sss?r", params);
    if(p1.error)
        return false;

    const char * native_name = p1.get_string(0);

    AMX * amx = pawn::gamemode;

    AMX_NATIVE native_fn = pawn::marh_amx_t::marh_find_function(amx, native_name);

    if(!native_fn)
    {
        api::send_pipe_msgf(pipe, "No such native: %s", native_name);
        return true;
    }

    const char * format = p1.get_string(1);

    api::parser p2(format, p1.get_string(2));
    if(p2.error)
    {
        //api::send_pipe_msg(pipe, "Wrong arguments supplied!");
        //return true;
    }

    cell * cells = new cell[p2.size() + 1];

    cells[0] = p2.size() * sizeof(cell);

    //std::list<cell *> addresses;

    // precall
    for(int i = 0; i < p2.size(); i++)
    {
        char type = p2.get_type(i);
        if(type == 'd' || type == 'i')
        {
            cells[i+1] = p2.get_int(i);
        }
        else if(type == 'f')
        {
            float t = p2.get_float(i);
            pawn::float_to_cell(&cells[i+1], &t);
        }
        else if(type == 's')
        {
            const char * s = p2.get_string(i);
            int len = strlen(s) + 1;
            pawn::amx_allot(amx, len, cells[i+1]);
            //cell * phys_addr = pawn::amx_get_addr(amx, cells[i+1]);
            //amx_SetString(phys_addr, s, 0, 0, len);
            pawn::amx_set_string(amx, cells[i+1], s, len);
        }
        else if(type == 'I' || type == 'F' || type == 'S') // pointers
        {
            pawn::amx_allot(amx, type == 'S' ? pawn::string_len::val : 1, cells[i+1]);
            //addresses.push_back(phys_addr);
        }
    }

    // call
    cell result = native_fn(amx, cells);

    // postcall
    for(int i = 0; i < p2.size(); i++)
    {
        char type = p2.get_type(i);
        cell amx_addr = cells[i+1];
        if(type == 'I')
        {
            api::send_pipe_msgf(pipe, "I@%d: %d", i, *(pawn::amx_get_addr(amx, amx_addr)));
            //addresses.pop_front();
        }
        else if(type == 'F')
        {
            float t;
            pawn::cell_to_float(&t, pawn::amx_get_addr(amx, amx_addr));

            api::send_pipe_msgf(pipe, "F@%d: %f", i, t);
            //addresses.pop_front();
        }
        else if(type == 'S')
        {
            char buf[pawn::string_len::val];
            //amx_GetString(buf, pawn::amx_get_addr(amx, ax_addr), 0, pawn::string_len::val);

            pawn::amx_get_string(amx, cells[i+1], buf, pawn::string_len::val);
            api::send_pipe_msgf(pipe, "S@%d: %s", i, buf);
            //addresses.pop_front();
        }

        // release
        if(type == 'I' || type == 'F' || type == 'S' || type == 's')
            pawn::amx_release(amx, amx_addr);
    }
    delete[] cells;
    
    float t;
    pawn::cell_to_float(&t, &result);
    api::send_pipe_msgf(pipe, "Returned: %d (%.2f)", result, t);
    return true;
}


INIT
{
    using namespace api::cmdflag;
    REGISTER_COMMAND2("native", ADMIN | RCON | SYSTEM | CONFIG, &exec_native);
}

#endif
