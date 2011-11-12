#include "player.hpp"
#include "object.hpp"
#include "vehicle.hpp"
#include "streamer.hpp"
#include "streams.hpp"
#include "playerpool.hpp"
#include "dialogs.hpp"
#include "race.hpp"
#include "race_details.hpp"
#include "counter.hpp"
#include "funcs.h"
#include "cmd.hpp"
//#include "parsers.hpp"

#include "util/point.hpp"
#include "util/notify.h"
#include "util/rotation.hpp"
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

// streamer.hpp
/*
streamer * streamer::instance = NULL;

streamer * streamer::get_instance()
{
  if(!instance)
  {
    instance = new streamer;
  }
  return instance;
}
void streamer::rm_instance()
{
    if(instance != NULL)
    {
      delete instance;
      instance = NULL;
    }
}*/

bool streamer::stream_objects(const basic_player& p, objects_t & objs)
{ // returns true if each object is properly streamed
  typedef objects_t::iterator iterator;
  for(iterator it = objs.begin(), en = objs.end(); it != en; ++it)
  {
    if(!it->show(p)) // show *it for p
      return false; // createplayerobject failed
  }
  return true;
}

bool streamer::stream(const basic_player& p)
{ // returns true if each object is properly streamed
  int x_idx, y_idx;
  util::point3d pos = p.get_pos();
  if(!pos.x && !pos.y) return false;
  //std::size_t count(0);

  /*
  if(get_indexes(pos.x, pos.y, x_idx, y_idx))
  {
    if(!stream_objects(p, objects[x_idx][y_idx])) // stream main cell
      return false; // do not stream other objects
  }
  
#define STREAM() \
  if(is_valid_indexes(x_idx, y_idx)) \
  { \
    if(!stream_objects(p, objects[x_idx][y_idx]))  \
      return false; \
  }

  
  // stream neighbor cells
		// OOO
  ++x_idx;	// OGX
  STREAM()	// OOO
  
  --x_idx;	// OXO
  ++y_idx;	// OGO
  STREAM()	// OOO
  
  --y_idx;	// OOO
  --y_idx;	// OGO
  STREAM()	// OXO
  
  ++y_idx;	// OOO
  --x_idx;	// XGO
  STREAM()	// OOO

#undef STREAM
*/
  if(!get_indexes(pos.x, pos.y, x_idx, y_idx)) return false;
  objects_t * objectszone[9]; // zones to stream
  objectszone[0] = &objects[x_idx][y_idx];
#define ASSIGN(i,x,y) objectszone[i] = is_valid_indexes(x, y) ? (&objects[x][y]) : NULL
  ASSIGN(1, x_idx + 1, y_idx);
  ASSIGN(2, x_idx + 1, y_idx + 1);
  ASSIGN(3, x_idx + 1, y_idx - 1);
  ASSIGN(4, x_idx - 1, y_idx);
  ASSIGN(5, x_idx - 1, y_idx + 1);
  ASSIGN(6, x_idx - 1, y_idx - 1);
  ASSIGN(7, x_idx, y_idx + 1);
  ASSIGN(8, x_idx, y_idx - 1);
#undef ASSIGN

  // cleaning zones
  objects_t ** end = objectszone + 9;
  for(int x = 0; x < STREAMER_CELL_X_AMOUNT; x++)
  {
    for(int y = 0; y < STREAMER_CELL_Y_AMOUNT; y++)
    {
      objects_t * current = &objects[x][y];
      if(std::find(objectszone, end, current) == end)
      {
        std::for_each(current->begin(), current->end(), [&p](object& obj)
        {
          obj.hide(p);
        });
      }
    }
  }
  // streaming zones
  try
  {
    std::for_each(objectszone, end, [&p, this](objects_t * zone)
    {
      if(zone)
        if(!stream_objects(p, *zone))
          throw(exception());
    });
  }
  catch(exception)
  {
    return false;
  }
  return true;
}

void streamer::hide_all(const basic_player& p)
{
  for(int x = 0; x < STREAMER_CELL_X_AMOUNT; x++)
  {
    for(int y = 0; y < STREAMER_CELL_Y_AMOUNT; y++)
    {
      objects_t * current = &objects[x][y];
      std::for_each(current->begin(), current->end(), [&p](object& obj)
      {
        obj.hide(p);
      });
    }
  }

}
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

// player.hpp

basic_player::basic_player(int id) : playerid(id)
{
  assert(id >= 0 && id < native::MAX_PLAYERS);
}

player::player(int id) : basic_player(id)
{
  //connected = native::is_player_connected(id);
}


util::point3d player::get_pos() const
{
  float x, y, z;
  native::get_player_pos(get_id(), x, y, z);
  return util::point3d(x, y, z);
}

void player::set_pos(const util::point3d& p)
{
  native::set_player_pos(get_id(), p.x, p.y, p.z);
}

// vehicle.hpp

util::point3d vehicle::get_pos() const
{
  float x, y, z;
  native::get_vehicle_pos(get_id(), x, y, z);
  return util::point3d(x, y, z);
}

void vehicle::set_pos(const util::point3d& p)
{
  native::set_vehicle_pos(get_id(), p.x, p.y, p.z);
}
void vehicle::set_ang(float ang)
{
  native::set_vehicle_zangle(get_id(), ang);
}

// playerpool.hpp
/*
players * players::instance = NULL;

players * players::get_instance()
{
  if(instance == NULL)
    instance = new players;
  return instance;
}
void players::rm_instance()
{
    if(instance != NULL)
    {
      delete instance;
      instance = NULL;
    }
}*/

// dialogs.hpp
/*
dialogs * dialogs::instance = NULL;

dialogs * dialogs::get_instance()
{
  if(instance == NULL)
    instance = new dialogs;
  return instance;
}
void dialogs::rm_instance()
{
    if(instance != NULL)
    {
      delete instance;
      instance = NULL;
    }
}*/

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
    native::set_player_race_checkpoint(playerid, 1, cp->pos->x, cp->pos->y, cp->pos->z, cp->pos->x, cp->pos->y, cp->pos->z, cp_size);
  }
  else
  {
    native::set_player_race_checkpoint(playerid, 0, cp->pos->x, cp->pos->y, cp->pos->z, next->pos->x, next->pos->y, next->pos->z, cp_size);
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
  // first = left, second = right, third = next after left ltd
  int away = pos / 2; // cars away from start
  float dist = away * distance; // distance away from start
  // getting coords
  float angle = util::deg_to_rad(-root.angle); // in radians
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


// counter.hpp

void counter::announce(int playerid, const std::string& str, bool done)
{
  int time = done ? 3000 : 1500;
  int sound = done ? 1057 : 1056;
  if(playerid == -1)
  {
    PLAYERBOX->for_each([&str, sound, time](int id)
    {
      native::player_play_sound(id, sound, 0.f, 0.f, 0.f);
      native::game_text_for_player(id, str, time, 4);
    });
  }
  else
  {
    native::game_text_for_player(playerid, str, time, 4);
    native::player_play_sound(playerid, sound, 0.f, 0.f, 0.f);
  }
}

// streams.hpp
void message_stream::call()
{
  if(playerid == -1)
    send_client_message_to_all(color, buffer);
  else
    send_client_message(playerid, color, buffer);
}


} // namespace

// register callbacks

static void on_player_connect(int playerid)
{
  PLAYERBOX->add(playerid);
}

static void on_player_disconnect(int playerid, int reason)
{
  PLAYERBOX->remove(playerid);
  STREAMER->hide_all(api::player(playerid));
}


static void on_player_command_text(int playerid, const std::string& cmd)
{
  if(!INVOKE_COMMANDS(playerid, cmd))
  {
    native::send_client_message(playerid, 0xffffffff, "Incorrect command!");
  }
}

static void on_dialog_response(int playerid, int dialogid, int success, int listitem, const std::string& input)
{
  DIALOGBOX->handle_response(playerid, dialogid, !!success, listitem, input);
}

static void on_player_update(int playerid)
{
  ACTIVEPLAYERBOX->update(playerid);
}

INIT
{
  
  REGISTER_CB(on_player_connect);
  REGISTER_CB(on_player_disconnect);
  REGISTER_CB(on_player_command_text);
  REGISTER_CB(on_dialog_response);
  REGISTER_CB(on_player_update);
  
}

