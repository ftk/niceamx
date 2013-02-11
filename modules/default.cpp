//# -*- coding: cp1251 -*-
#include "samp.h"
#include "api/cmd.hpp"
#include "api/streams.hpp"

#include "util/utils.h"
#include <iostream>

#ifndef NDEBUG
#define TYPE "debug"
#else
#define TYPE ""
#endif

INIT
{
  REGISTER_CALLBACK(on_game_mode_init, []()
  {
    native::set_game_mode_text(__DATE__ " " __TIME__ " " TYPE);
    native::add_player_class(1, 0.f, 0.f, 10.f, 0.f, 0,0, 0,0, 0,0);
    native::add_player_class(2, 0.f, 0.f, 10.f, 0.f, 0,0, 0,0, 0,0);
    native::add_player_class(180, 0.f, 0.f, 10.f, 0.f, 0,0, 0,0, 0,0);
    native::use_player_ped_anims();
  });
  
  REGISTER_CALLBACK(on_player_request_class, [](int id, int)
  {
    native::set_player_pos(id, 0.f, 0.f, 10.f);
    native::set_player_camera_pos(id, 0.f, 10.f, 10.f);
    native::set_player_camera_look_at(id, 0.f, 0.f, 10.f);
  });
  REGISTER_CALLBACK(on_player_spawn, [](int id)
  {
    native::set_camera_behind_player(id);
  });
  
  /*
  REGISTER_CALLBACK(on_plugin_load, []()
  {
  });*/

  
  REGISTER_COMMAND("kill", [](int playerid, const std::string&) -> bool
  {
    native::set_player_health(playerid, 0.f);
    return true;
  });
  REGISTER_CALLBACK(on_player_connect, ([](int playerid)
  {
    api::message msg;
    msg << native::get_player_name(playerid) << " присоединился к серверу." << std::endl;
  }));
  REGISTER_CALLBACK(on_player_disconnect, ([](int playerid, int)
  {
    api::message msg;
    msg << native::get_player_name(playerid) << " отключился." << std::endl;
  }));
/*
  REGISTER_TIMER(2000, ([]()
  {
  	std::cout << util::get_walltime() << "\n";
  }));*/
}
