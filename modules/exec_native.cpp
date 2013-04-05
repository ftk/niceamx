#ifndef TEST_MODE

#include "samp.h"

#include "api/cmd2.hpp"
#include "api/pipes.hpp"

#include "pawn/pawn_marshaling_amx.hpp"
#include "pawn/pawn_marshaling_param.hpp"
#include "pawn/plugin.h"

#include "SDK/amx/amx.h"

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
        api::send_pipe_msg(pipe, "Wrong arguments supplied!");
    }

    cell * cells = new cell[p2.size() + 1];

    cells[0] = p2.size() * sizeof(cell);

    std::list<cell *> addresses;

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
            memcpy(&cells[i+1], &t, sizeof(float));
        }
        else if(type == 's')
        {
            const char * s = p2.get_string(i);
            cell * phys_addr;
            int len = strlen(s) + 1;
            amx_Allot(amx, len, &cells[i+1], &phys_addr);
            amx_SetString(phys_addr, s, 0, 0, len);
        }
        else if(type == 'I' || type == 'F' || type == 'S') // pointers
        {
            cell * phys_addr;
            amx_Allot(amx, pawn::string_len::val, &cells[i+1], &phys_addr);
            addresses.push_back(phys_addr);
        }
    }

    // call
    long result = native_fn(amx, cells);

    // postcall
    for(int i = 0; i < p2.size(); i++)
    {
        char type = p2.get_type(i);
        if(type == 'I')
        {
            api::send_pipe_msgf(pipe, "I@%d: %d", i, *(addresses.front()));
            addresses.pop_front();
        }
        else if(type == 'F')
        {
            float t;
            memcpy(&t, addresses.front(), sizeof(float));

            api::send_pipe_msgf(pipe, "F@%d: %f", i, t);
            addresses.pop_front();
        }
        else if(type == 'S')
        {
            char buff[pawn::string_len::val];
            amx_GetString(buff, addresses.front(), 0, pawn::string_len::val);

            api::send_pipe_msgf(pipe, "S@%d: %s", i, buff);
            addresses.pop_front();
        }

        // release
        if(type == 'I' || type == 'F' || type == 'S' || type == 's')
            amx_Release(amx, cells[i+1]);
    }
    delete[] cells;
    
    float t;
    memcpy(&t, &result, sizeof(float));
    api::send_pipe_msgf(pipe, "Returned: %ld (%.2f)", result, t);
    return true;
}


INIT
{
    using namespace api::cmdflag;
    REGISTER_COMMAND2("native", ADMIN | RCON | SYSTEM, &exec_native);
}

#endif
