#include "vehicles.hpp"
#include "samp.h"

#include "api/cmd2.hpp"
#include "api/pipes.hpp"
#include "api/playerpool.hpp"

#include <string>

#include <cstdlib>

#include "util/point.hpp"


vehicle_color vehicle_model_t::get_random_color()
{
    if(colors.empty())
        return {-1, -1};
    return colors[rand() % colors.size()];
}


// synced colors
int vehicle_create(int model, util::point3d pos, float angle, int col1, int col2, int respawn)
{
    if(col1 == -1 || col2 == -1)
    {
        vehicle_color randcol = vehicle_models::get_instance()->get_model(model).get_random_color();
        if(col1 == -1)
            col1 = randcol.col1;
        if(col2 == -1)
            col2 = randcol.col2;
    }
    int id;
    if(PLAYERBOX->empty())
        id = native::add_static_vehicle_ex(model, pos.x, pos.y, pos.z, angle, col1, col2, respawn);
    else
        id = native::create_vehicle(model, pos.x, pos.y, pos.z, angle, col1, col2, respawn);

    if(id >= native::MAX_VEHICLES || id < 0)
        id = 0;
    return id;
}


INIT
{
    using namespace api::cmdflag;
    REGISTER_COMMAND("max_vehicles", CONFIG, [](int, const std::string& params)
    {
        vehicle_models::get_instance()->resize(api::parser("*sd", params).get_int(0));
        return true;
    });

    REGISTER_COMMAND("vehicle_info", CONFIG, [](int /*pipe*/, const std::string& params)
    {
        // vehicle_info 400 "Landstalker" 1 1 0 0 ... (colors)
        api::parser p("*sds?r", params);
        int modelid = p.get_int(0);
        vehicle_model_t& model = vehicle_models::get_instance()->get_model(modelid);
        model.model_id = modelid;
        model.name = p.get_string(1);

        model.colors.clear();

        //api::send_pipe_msgf(pipe, "vehicle %03d: %s", modelid, p.get_string(1));

        const char * pstr = p.get_string(2);
        while(*pstr)
        {
            vehicle_color col;
            char * numstop;
            col.col1 = strtol(pstr, &numstop, 0);
            if(*numstop)
                pstr = numstop + 1;
            col.col2 = strtol(pstr, &numstop, 0);

            //api::send_pipe_msgf(pipe, "colors %d %d", col.col1, col.col2);

            model.colors.push_back(std::move(col));
            if(!*numstop)
                break;
            pstr = numstop + 1;
        }



        return true;
    });

    /*
    REGISTER_COMMAND("vehicle_mod", CONFIG, [](int pipe, const std::string& params)
    {
        // vehicle_mod 400 1008 "nto_b_l"
        api::parser p("*sdd?s", params);
        int modelid = p.get_int(0);
        vehicle_model_t& model = vehicle_models::get_instance()->get_model(modelid);

    });*/

}

