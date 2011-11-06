#include "samp.h"
#include "api/cmd.hpp"
#include "api/playerpool.hpp"
#include "api/streams.hpp"

#include <set>

std::set<int> voted;

extern void new_race();


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
      msg << "—мена гонки на случайную." << std::endl;
      new_race();
      voted.clear();
    }
    return true;
  })("rtv")("vote")("votemap"));

  REGISTER_CALLBACK(on_player_connect, ([](int playerid)
  {
    api::message msg;
    msg << native::get_player_name(playerid) << " присоединилс€ к серверу." << std::endl;
  }));
  REGISTER_CALLBACK(on_player_disconnect, ([](int playerid, int)
  {
    api::message msg;
    msg << native::get_player_name(playerid) << " отключилс€." << std::endl;
    voted.erase(playerid);
  }));
}
