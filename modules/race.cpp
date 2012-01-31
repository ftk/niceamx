//# -*- coding: cp1251 -*-

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
#include <vector>

//#include <boost/format.hpp>

static api::race * r = NULL;
static api::race_details * r_d = NULL;
static api::detail::race_loader * r_l = NULL;

static api::vote vote;

struct playerstate
{
  int vehicleid;
  long start;
  
  std::vector<long> cp_time;
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

void show_vote(int id)
{
  SHOW_DIALOG(api::dialog_list, ([id](int, bool succ, int item)
  {
    if(succ)
    {
      vote.vote_up(item);
      api::message msg;
      *msg << native::get_player_name(id) << " проголосовал за " << vote.get(item) << std::endl;
    }
  }), id, "Голосование", vote.join('\n'), "Выбрать", "Отмена");
}


void load_race()
{
  static std::string racefile = "Tampa";
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
  // cleanup
  if(r != NULL)
    delete r;
  r = new api::race(*r_l);

  for(auto it = players.begin(), en = players.end(); it != en; ++it)
  {
    if(it->second.vehicleid != 0)
      native::destroy_vehicle(it->second.vehicleid);
    //it->second.cp_time.clear();
  }
  players.clear();

  // load new race 
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
    PLAYERBOX->for_each([](int id)race_details
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
    
    show_vote(id);
  });
  throw signals::timer_stop();
}


static int winner_id, winner_cps;
static void on_player_enter_race_checkpoint(int id)
{
  r->proccess_cp(id);
  
  /* time diff announcement */
  playerstate & pl = players[id];
  pl.cp_time.push_back(util::get_walltime_s());
  
  // are you the first ?
  if(pl.cp_time.size() > winner_cps)
  {
    winner_cps = pl.cp_time.size();
    winner_id = id;
  }
  else if(winner_id != -1)
  {
    // looser
    assert(winner_cps >= pl.cp_time.size());
    long timediff = util::get_walltime_s() - players[winner_id].cp_time.at(pl.cp_time.size() - 1); // winner's time at this checkpoint
    native::game_text_for_player(id, util::sprintf("%02ld:%02ld", timediff / 60, timediff % 60), 1000, 0); // show time difference
  }
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
  
    
  REGISTER_CALLBACK(on_player_spawn, &connect_to_race);

  /*
  REGISTER_CALLBACK(on_player_enter_race_checkpoint, [](int id)
  {
    
  });*/
  REGISTER_CB(on_player_enter_race_checkpoint);
  
  REGISTER_CALLBACK(on_player_disconnect, [](int id, int)
  {
    r->part(id);
    if(players[id].vehicleid != 0)
      native::destroy_vehicle(players[id].vehicleid);
    players.erase(id);
  });


  REGISTER_CALLBACK(plugin_unload, []()
  {
    delete r;
    delete r_l;
    delete r_d;
  });
}

