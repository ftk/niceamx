#include "object.hpp"
#include "playerpool.hpp"
#include "dialogs.hpp"
#include "race.hpp"
#include "race_details.hpp"
#include "counter.hpp"
#include "funcs.h"
//#include "cmd.hpp"
//#include "parsers.hpp"
#include "num_players.hpp"

#include "util/point.hpp"
#include "util/notify.h"
#include "util/rotation.hpp"
#include "util/log.h"
//
#include "pawn/natives.h"

#include <cassert>
#include <vector>
#include <map>

#include <algorithm>

//#include <boost/format.hpp>

#include "signals.hpp"
#include "timers.hpp"

namespace api {

// object.hpp
bool object::show(int playerid)
{
  if(!is_object_streamed(playerid))
  {
    int objectid = native::create_player_object(playerid, modelid, pos.x, pos.y, pos.z, rot->x, rot->y, rot->z);
    if(!objectid || objectid == native::INVALID_OBJECT_ID || objectid >= native::MAX_OBJECTS)
      return false;
    pobjects[playerid] = objectid;
  }
  return true;
}

bool object::hide(int playerid)
{
  pobjects_t::iterator it = pobjects.find(playerid);
  if(it != pobjects.end())
  {
    native::destroy_player_object(playerid, it->second);
    pobjects.erase(it);
  }
  return true;
}


// dialogs.hpp


bool dialogs::handle_response(int playerid, unsigned int dialogid, bool success, int listitem, const std::string& inputtext)
{
  assert(dialogid != 0);
  typedef dialogids_t::iterator iterator;
  for(iterator it = dialogids.begin(), en = dialogids.end(); it != en; ++it)
  {
    if(it->dialogid == dialogid)
    {
      it->invoke(playerid, success, listitem, inputtext);
      //delete (*it);
      dialogids.erase(it);

      return true;
    }
  }
  return false;
}

// race.hpp
void race::set_checkpoint(int playerid, const detail::checkpoint * cp)
{
  const detail::checkpoint * next = cp->next;
  if(next == NULL)
  {
    native::set_player_race_checkpoint(playerid, 1, cp->pos.x, cp->pos.y, cp->pos.z, cp->pos.x, cp->pos.y, cp->pos.z, cp_size);
  }
  else
  {
    native::set_player_race_checkpoint(playerid, 0, cp->pos.x, cp->pos.y, cp->pos.z, next->pos.x, next->pos.y, next->pos.z, cp_size);
  }
}
void race::remove_checkpoint(int playerid)
{
  native::disable_player_race_checkpoint(playerid);
}

// race-details.hpp

race_details::veh_pos race_details::get_position(int pos)
{
  assert(pos >= 0);
  veh_pos & root = (pos % 2) ? right : left;
  // first = left, second = right, third = behind left 
  int away = pos / 2; // row
  float dist = away * distance; // distance away from start
  // getting coords
  float angle = util::deg_to_rad(root.angle); // in radians
  util::point3d position = root.pos;
  position.x += sin(angle) * dist;
  position.y += cos(angle) * dist;
  veh_pos p;
  p.pos = position;
  p.angle = root.angle;
  return p;
}

int race_details::setup_player(int id, int pos)
{
  --pos;
  veh_pos p = get_position(pos);
  if(vmodel != 0)
  {
    native::set_player_pos(id, p.pos.x + 5, p.pos.y, p.pos.z + 3);
    int vehid = native::create_vehicle(vmodel, p.pos.x, p.pos.y, p.pos.z, p.angle, -1, -1, 1200);
    if(vehid < 0 || vehid == native::INVALID_VEHICLE_ID)
      return(0);
    REGISTER_TIMER(2000, ([id, vehid]()
    {
      native::put_player_in_vehicle(id, vehid, 0);
      throw(signals::timer_stop());
    }));
    return vehid;
  }
  else
  {
    native::set_player_pos(id, p.pos.x, p.pos.y, p.pos.z);
    return 0;
  }
}


// counter.hpp

void counter::announce(int playerid, const std::string& str, bool done)
{
  const int time = done ? 3000 : 1500;
  const int sound = done ? 1057 : 1056;
  //util::log_msg_nofmt("announce", "test");
  if(playerid == -1)
  {
    for(int id : *PLAYERBOX)
    {
      native::player_play_sound(id, sound, 0.f, 0.f, 0.f);
      native::game_text_for_player(id, str, time, 4);
    }
  }
  else
  {
    native::game_text_for_player(playerid, str, time, 4);
    native::player_play_sound(playerid, sound, 0.f, 0.f, 0.f);
  }
}


// playerpool.hpp

void player_info::update()
{
    if(id >= 0 && native::is_player_connected(id))
    {
        name = native::get_player_name(id);
        std::string ip = native::get_player_ip(id);
        unsigned int a, b, c, d;
        sscanf(ip.c_str(), "%u.%u.%u.%u", &a, &b, &c, &d);
        a &= 0xff; b &= 0xff; c &= 0xff; d &= 0xff;
        this->ipv4 = (a << 24) | (b << 16) | (c << 8) | d;
    }
    else
    {
        id = -1;
        ipv4 = 0;
        name = "~";
    }
}

std::string player_info::get_ip()
{
	char buf[20];
	snprintf(buf, 19, "%d.%d.%d.%d", ipv4 >> 24, (ipv4 >> 16) & 0xff, (ipv4 >> 8) & 0xff, (ipv4) & 0xff);
	return std::string(buf);
}



} // namespace api


/***********************************/

// register callbacks

static void on_player_connect(int playerid)
{
    if(playerid < 0 || playerid >= api::NUM_PLAYERS)
    {
        native::kick(playerid);
        throw signals::signal_return(0);
    }
    PLAYERBOX->add(playerid);
}

static void on_player_disconnect(int playerid, int /*reason*/)
{
  PLAYERBOX->remove(playerid);
  //STREAMER->hide_all(api::player(playerid));
}

/*
static void on_player_command_text(int playerid, const std::string& cmd)
{
  if(!INVOKE_COMMANDS(playerid, cmd))
  {
    native::send_client_message(playerid, 0xffffffff, "Incorrect command!");
  }
}*/

static void on_dialog_response(int playerid, int dialogid, int success, int listitem, const std::string& input)
{
  DIALOGBOX->handle_response(playerid, dialogid, !!success, listitem, input);
}
/*
static void on_player_update(int playerid)
{
  ACTIVEPLAYERBOX->update(playerid);
}*/

INIT
{
  
  REGISTER_CALLBACK(on_player_connect, -100000, on_player_connect); // first
  REGISTER_CALLBACK(on_player_disconnect, 100000, on_player_disconnect); // last
  //REGISTER_CB(on_player_command_text);
  REGISTER_CB(on_dialog_response);
  //REGISTER_CB(on_player_update);
  
  REGISTER_CALLBACK(on_game_mode_init, ([]()
  {
      int maxplayers = native::get_server_var_as_int("maxplayers");
      if(maxplayers > api::NUM_PLAYERS)
      {
          util::log_msg("api/warning",
                        "Server is configured to use %d > %d players. Redefine NUM_PLAYERS",
                        maxplayers, api::NUM_PLAYERS);
      }
  }));
}

