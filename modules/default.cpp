//# -*- coding: cp1251 -*-
#include "samp.h"
#include "api/cmd2.hpp"
#include "api/pipes.hpp"
#include "api/playerpool.hpp"
#include "api/num_players.hpp"

#include "util/utils.h"
#include "util/log.h"
#include <iostream>

#ifndef NDEBUG
#define TYPE "debug"
#else
#define TYPE ""
#endif

static api::array_players<int> animation_idx;

INIT
{
  REGISTER_CALLBACK(on_game_mode_init, []()
  {
    native::set_game_mode_text(__DATE__ " " __TIME__ " " TYPE);
    /*
    native::add_player_class(1, 0.f, 0.f, 10.f, 0.f, 0,0, 0,0, 0,0);
    native::add_player_class(2, 0.f, 0.f, 10.f, 0.f, 0,0, 0,0, 0,0);
    native::add_player_class(180, 0.f, 0.f, 10.f, 0.f, 0,0, 0,0, 0,0);
    */
    native::use_player_ped_anims();
  });
  /*
  REGISTER_CALLBACK(on_player_request_class, [](int id, int)
  {
    native::set_player_pos(id, 0.f, 0.f, 10.f);
    native::set_player_camera_pos(id, 0.f, 10.f, 10.f);
    native::set_player_camera_look_at(id, 0.f, 0.f, 10.f);
  });*/
  REGISTER_CALLBACK(on_player_spawn, [](int id)
  {
    native::set_camera_behind_player(id);
  });
  

  
  REGISTER_COMMAND2("kill", api::cmdflag::PLAYER, [](int playerid, const std::string&) -> bool
  {
    native::set_player_health(playerid, 0.f);
    return true;
  });
  REGISTER_CALLBACK(on_player_connect, -100, ([](int playerid)
  {
    api::send_pipe_msgf(api::pipe::ALL, "%s has joined", PLAYERBOX->get_info(playerid).name.c_str());
    
    util::log_msg("player/connect", "%d: <%s> <%s>", playerid,
    	PLAYERBOX->get_info(playerid).name.c_str(),
    	PLAYERBOX->get_info(playerid).get_ip().c_str());
    	
    //
    //native::set_spawn_info(playerid, native::NO_TEAM, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
    
  }));
  REGISTER_CALLBACK(on_player_disconnect, 100, ([](int playerid, int reason)
  {
    api::send_pipe_msgf(api::pipe::ALL, "%s has left (%d)", PLAYERBOX->get_info(playerid).name.c_str(), reason);
    util::log_msg("player/disconnect", "%d: <%d> <%s> <%s>", playerid, reason,
    	PLAYERBOX->get_info(playerid).name.c_str(),
    	PLAYERBOX->get_info(playerid).get_ip().c_str());
    // ...

  }));

  REGISTER_CALLBACK(on_player_death, 100, ([](int playerid, int /*killer*/, int /*reason*/)
  {
      std::string name, lib;
      native::get_animation_name(animation_idx[playerid], lib, name);
      if(lib == "PED")
      {
          native::clear_animations(playerid, 0);
      }
  }));


/*
  REGISTER_TIMER(2000, ([]()
  {
  	std::cout << util::get_walltime() << "\n";
  }));*/

  REGISTER_CALLBACK(on_player_update, [](int playerid)
  {
      animation_idx[playerid] = native::get_player_animation_index(playerid);
  });
}
