#include "samp.h"

#include "api/playerpool.hpp"

#include <functional>
#include <cassert>

#include "util/utils.h"


struct player_timer
{
    std::function<void (int)> handler;
    int cur_id;

    player_timer(std::function<void (int)> handler) : handler(std::move(handler)), cur_id(-1) {}

    void operator()()
    {
        if(PLAYERBOX->empty())
        {
            cur_id = -1;
            return;
        }
        cur_id = PLAYERBOX->next(cur_id);
        if(cur_id < 0)
            cur_id = *(PLAYERBOX->begin()); // the first id

        //assert(native::is_player_connected(cur_id));
        handler(cur_id);
    }
};

static const int seconds_per_game_minute = 1;

static util::walltime_t clock_start = util::get_walltime_s() -
        7 * 60 * seconds_per_game_minute; // starting from 7:00 am

static void sync_player_time(int id)
{
    // time in minutes
    int worldtime = (util::get_walltime_s() - clock_start) / seconds_per_game_minute;
    native::set_player_time(id, (worldtime / 60) % 24, worldtime % 60);
}

static player_timer clock_sync(sync_player_time);

/*
static int current_weather = 10;

static void sync_weather()
{
    current_weather = rand()%20;
}*/


INIT
{

    REGISTER_TIMER(30 * 1000, clock_sync);
    //REGISTER_TIMER(3 * 60000, weather_sync);

    REGISTER_CALLBACK(on_player_spawn, &sync_player_time);
    REGISTER_CALLBACK(on_player_connect, ([](int id)
    {
        native::toggle_player_clock(id, true);
    }));

}
