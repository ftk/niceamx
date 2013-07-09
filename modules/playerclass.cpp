#include "api/cmd2.hpp"
#include "api/funcs.h"
#include "api/num_players.hpp"
#include "samp.h"

#include <vector>
#include <cmath>

#include "util/point.hpp"
#include "util/rotation.hpp"

#include <boost/utility.hpp>
#include <boost/ptr_container/ptr_list.hpp>

static float defspawn[4] = {0.f, 0.f, 0.f, 0.f};


struct circle_camera
{
    int playerid;
    //bool destroyme = false;

    typedef std::vector<util::point3d> polygon_t;

    const polygon_t& hexagon;

    polygon_t::const_iterator iter;

    circle_camera(int playerid, const polygon_t& hexagon) : playerid(playerid), hexagon(hexagon)
    {
        iter = hexagon.begin();
    }


    void operator()()
    {
        auto iter_next = boost::next(iter);
        if(iter_next == hexagon.end())
            iter_next = hexagon.begin();

        if(!native::is_player_connected(playerid) || api::is_player_spawned(playerid))
        {
            //destroyme = true;
            throw signals::timer_stop();
        }

        native::interpolate_camera_pos(playerid, iter->x, iter->y, iter->z,
                                       iter_next->x, iter_next->y, iter_next->z,
                                       3000, native::CAMERA_MOVE);
        native::interpolate_camera_look_at(playerid, defspawn[0], defspawn[1], defspawn[2] + 0.6f,
                defspawn[0], defspawn[1], defspawn[2] + 0.6f, 3000);

        iter = iter_next;
    }
};

static circle_camera::polygon_t hexagon;

static circle_camera::polygon_t make_hexagon(int vertices, float dist)
{
    circle_camera::polygon_t hexagon(vertices);
    const float angle_shift = (2 * util::pi) / vertices;
    float angle = util::deg_to_rad(defspawn[3]);
    for(int i = 0; i < vertices; i++)
    {
        hexagon[i].z = defspawn[2] + 1.45f;
        hexagon[i].x = defspawn[0] - std::sin(angle) * dist;
        hexagon[i].y = defspawn[1] - std::cos(angle) * dist;
        angle += angle_shift;
    }
    return hexagon;
}


static api::bitset_players class_selected;


//static boost::ptr_list<circle_camera> cameras_list;

INIT
{
    using namespace api::cmdflag;
    REGISTER_COMMAND("set_spawn", CONFIG, ([](api::cmdinfo_t info)
    {
        api::parser_cmd p("fff?f", info);


        for(int i = 0; i < 4; i++)
            defspawn[i] = p.get(i, 0.f);

        hexagon = make_hexagon(6, 3.5f);
    }));

    REGISTER_COMMAND("add_class", CONFIG, ([](api::cmdinfo_t info)
    {
        api::parser_cmd p("d", info);


        native::add_player_class(p.get<int>(0),
                                 defspawn[0],
                                 defspawn[1],
                                 defspawn[2],
                                 defspawn[3],
                                 // weapons
                                 0, 0,
                                 0, 0,
                                 0, 0);
    }));



    REGISTER_CALLBACK(on_player_request_class, ([](int playerid, int /*classid*/)
    {
        if(!class_selected[playerid])
        {
            /*
            // clean up cameras
            for(auto it = cameras_list.begin(); it != cameras_list.end(); )
            {
                if(it->destroyme)
                {
                    it = cameras_list.erase(it);
                }
                else
                    ++it;
            }
            circle_camera *
            cameras_list*/
            native::set_player_pos(playerid, defspawn[0],
                    defspawn[1],
                    defspawn[2]);
            native::set_player_facing_angle(playerid, defspawn[3]);

            circle_camera c(playerid, hexagon);
            c();
            REGISTER_TIMER(3000, std::move(c));
            class_selected.set(playerid);
        }
    }));

    REGISTER_CALLBACK(on_player_disconnect, ([](int playerid, int)
    {
        class_selected.reset(playerid);
    }));
    REGISTER_CALLBACK(on_player_spawn, ([](int playerid)
    {
        class_selected.reset(playerid);
    }));
}
