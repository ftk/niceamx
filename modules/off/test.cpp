#include <iostream>
#include "samp.h"

#include "util/overtimer.hpp"

#include "api/streamer.hpp"

using namespace std;

static void test(int a)
{
    cout << a << endl;

}

static void onload()
{
    api::streamer::get_instance();
}

static bool on_game_mode_init()
{
    //cout << "WOW! it works" << endl;  
    //native::gamemode_exit();
    return true;
}

static bool on_game_mode_exit()
{
    //cout << "EXit" << endl;  
    return true;
}

static void timer100()
{
  cout << "100"  << endl;
}
static void timer500()
{
  cout << "500" << endl;
}
static void timer1000()
{
  cout << "1000 " << util::overtimer::get_walltime() << endl;
}


INIT
{
    //cout << "hoho" << endl;

    //REGISTER_CB(test);
    //REGISTER_CALLBACK(plugin_load, &onload);
    //REGISTER_CB(on_game_mode_init);
    //REGISTER_CB(on_game_mode_exit);
    
    REGISTER_TIMER(100, &timer100);
    REGISTER_TIMER(500, &timer500);
    REGISTER_TIMER(1000, &timer1000);
    
    //return true;
}
