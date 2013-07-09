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
    REGISTER_COMMAND("max_vehicles", CONFIG, [](api::cmdinfo_t info)
    {
        vehicle_models::get_instance()->resize(api::parser("d", info).get<int>(0));
    });

    REGISTER_COMMAND("vehicle_info", CONFIG, [](api::cmdinfo_t info)
    {
        // vehicle_info 400 "Landstalker" 1 1 0 0 ... (colors)
        api::parser_cmd p("ds?d+", info);
        int modelid = p.get<int>(0);
        vehicle_model_t& model = vehicle_models::get_instance()->get_model(modelid);
        model.model_id = modelid;
        model.name = p.get<const char *>(1);

        model.colors.clear();

        //api::send_pipe_msgf(pipe, "vehicle %03d: %s", modelid, p.get_string(1));
        
        for(std::size_t i = 0; i < (p.size()-2)/2; i++)
        {
        	vehicle_color col;
            col.col1 = p.get<int>(2+i*2);
            col.col2 = p.get<int>(2+i*2+1);
        	model.colors.push_back(std::move(col));
        }

    });


    REGISTER_COMMAND("add_vehicle", CONFIG | RCON | ADMIN, [](api::cmdinfo_t info)
    {
        api::parser_cmd p("dffff?ddd", info);
        int id = vehicle_create(p.get<int>(0), {p.get<float>(1),p.get<float>(2),p.get<float>(3)},
                       p.get<float>(4), p.get(5, -1),p.get(6, -1),
                       p.get(7, 120));
        (void)id;
        /*
#ifdef _DEBUG
        auto& model = vehicle_models::get_instance()->get_model(p.get<int>(0));
        api::send_pipe_msgf(info.caller, "%d : %s [%d]", id, model.name.c_str(), model.model_id);
#endif*/
    });

/*
    REGISTER_COMMAND("vehicle_mod", CONFIG, [](api::cmdinfo_t info)
    {
        // vehicle_mod 400 1008 "nto_b_l"
        api::parser_cmd p("dd?s", info);
        const int modelid = p.get<int>(0);
        vehicle_model_t& model = vehicle_models::get_instance()->get_model(modelid);

    });
*/
}

