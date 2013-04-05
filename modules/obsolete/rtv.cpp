//# -*- coding: cp1251 -*-

#include "samp.h"
#include "api/cmd.hpp"
#include "api/playerpool.hpp"
#include "api/streams.hpp"

#include <set>


extern void new_race();
extern void show_vote(int id);

static std::set<int> voted;

INIT
{
  REGISTER_COMMAND2(MAKE_COMMAND([](int playerid, const std::string&) -> bool
  {
    if(voted.find(playerid) != voted.end())
      return true;
    voted.insert(playerid);
    const int needto = PLAYERBOX->count() / 2 + 1;
    api::message msg(0xefefefff);
    msg << native::get_player_name(playerid) << " голосует за смену карты (/rtv). " << voted.size() << " голосов из " << needto << std::endl;
    if((int)voted.size() >= needto)
    {
      msg << "Смена гонки через 20 секунд." << std::endl;
      
      PLAYERBOX->for_each([](int id)
      {
        show_vote(id);
      });
      
      REGISTER_TIMER(20 * 1000, &new_race);
      
      voted.clear();
    }
    return true;
  })("rtv")("vote")("votemap"));

  REGISTER_CALLBACK(on_player_disconnect, ([](int playerid, int)
  {
    voted.erase(playerid);
  }));
}
