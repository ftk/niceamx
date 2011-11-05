#include "post_process.h"
#include "natives.h"
#include <string>
#include "api/playerpool.hpp"
//#include <iostream>

namespace pawn { namespace pp {
//

int player_text(int playerid, const std::string& text)
{
  //std::cout << text << std::endl;
  PLAYERBOX->for_each([playerid, &text](int id)
  {
    native::send_player_message_to_player(id, playerid, text);
  });
  return 0;
}



}} // namespace
