#include "samp.h"

#include "api/race.hpp"
#include "api/race_details.hpp"
#include "api/counter.hpp"
#include "api/funcs.h"
#include "api/playerpool.hpp"
#include "api/vote.hpp"
#include "api/streams.hpp"
#include "api/dialogs.hpp"
#include "api/cmd.hpp"

#include "util/notify.h"
#include "util/utils.h"

#include <fstream>
#include <map>

//#include <boost/format.hpp>

static api::race * r = NULL;
static api::race_details * r_d = NULL;
static api::detail::race_loader * r_l = NULL;

api::vote vote;

struct playerstate
{
  int vehicleid;
  long start;
};

static std::map<int, playerstate> players;


void connect_to_race(int playerid)
{
  //util::notify("connect to race");
  
  if(r != NULL && r_d != NULL)
  {
    r->join(playerid);
    players[playerid].vehicleid = r_d->setup_player(playerid, playerid + 1);
    r->start(playerid);
    players[playerid].start = util::get_walltime_s();
  }
  //return false;
}

std::string racefile = "Tampa";

void load_race()
{
  racefile = vote.get_highest();
  vote.clear();
  api::message msg;
  *msg << "Загружена гонка " << racefile << std::endl;
  
  std::ifstream racefp("races/" + racefile + ".txt");
  assert(racefp);
  std::ifstream racedfp("races/" + racefile + "_d.txt");
  assert(racedfp);
  r_l->destruct();
  r_l->import_stream(racefp);
  r_d->import_stream(racedfp);
}

void new_race()
{
  
  load_race();
  if(r != NULL)
    delete r;
  r = new api::race(*r_l);

  for(auto it = players.begin(), en = players.end(); it != en; ++it)
  {
    native::destroy_vehicle(it->second.vehicleid);
  }
  players.clear();

  int playersplace = 0;
  PLAYERBOX->for_each([&playersplace](int playerid)
  {
    r->join(playerid);
    players[playerid].vehicleid = r_d->setup_player(playerid, ++playersplace);
    players[playerid].start = util::get_walltime_s();
    native::toggle_player_controllable(playerid, false);
  });
  api::counter c(6, -1, [](api::counter *)
  {
    r->start();
    PLAYERBOX->for_each([](int id)
    {
      native::toggle_player_controllable(id, true);
    });
  });
  REGISTER_TIMER(1000, c);
  r->set_finish([](int id, unsigned place)
  {
    api::message msg;
    char time[100];
    const long timediff = util::get_walltime_s() - players[id].start;
    sprintf(time, "%02ld:%02ld", timediff / 60, timediff % 60);
    *msg << native::get_player_name(id) << " финишировал " << place <<"-ым за " << time << std::endl;
    if(place == r->count()) // last
    {
    }
    if(place == 1)
    {
      *msg << "Смена гонки через 30 секунд" << std::endl;
      REGISTER_TIMER(30 * 1000, &new_race);
    }
    SHOW_DIALOG(api::dialog_list, ([id, &msg](int, bool succ, int item)
    {
      if(succ)
      {
        vote.vote_up(item);
        *msg << native::get_player_name(id) << " проголосовал за " << vote.get(item) << std::endl;
      }
    }), id, "Голосование", vote.join('\n'), "Выбрать", "Отмена");
  });
  throw signals::timer_stop();
}

INIT
{
  //util::notify("init");
  std::ifstream racestxt("races/races.txt");
  assert(racestxt);
  vote.import_stream(racestxt);

  r_d = new api::race_details;
  
  r_l = new api::detail::race_loader;
  r = new api::race(*r_l);
  
  //REGISTER_TIMER(20000, &new_race);

  try
  {
    new_race();
  }
  catch(signals::timer_stop)
  {}
  
  
  REGISTER_CALLBACK(on_game_mode_init, []()
  {
    native::set_game_mode_text(__DATE__ " " __TIME__);
    native::add_player_class(1, 0.f, 0.f, 10.f, 0.f, 0,0, 0,0, 0,0);
    native::add_player_class(2, 0.f, 0.f, 10.f, 0.f, 0,0, 0,0, 0,0);
    native::add_player_class(180, 0.f, 0.f, 10.f, 0.f, 0,0, 0,0, 0,0);
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
  
  REGISTER_CALLBACK(on_player_spawn, &connect_to_race);

  REGISTER_CALLBACK(on_player_enter_race_checkpoint, [](int id)
  {
    r->proccess_cp(id);
  });

  REGISTER_COMMAND("kill", [](int playerid, const std::string&) -> bool
  {
    native::set_player_health(playerid, 0.f);
    return true;
  });

  REGISTER_CALLBACK(plugin_unload, []()
  {
    delete r;
    delete r_l;
    delete r_d;
  });
}

