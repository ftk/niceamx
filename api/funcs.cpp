#include <string>
#include "funcs.h"
#include "pawn/natives.h"

#include "api/playerpool.hpp"

namespace api {
//
void send_client_message_to_all(unsigned color, const std::string& str)
{
  PLAYERBOX->for_each([color,&str](int id)
  {
    native::send_client_message(id, color, str);
  });
}
void send_client_message(int playerid, unsigned color, const std::string& str)
{
  native::send_client_message(playerid, color, str);
}

}
