#ifndef API_FUNCS_H
#define API_FUNCS_H

#include <string>

namespace api {
//
void send_client_message_to_all(unsigned color, const std::string& str);
void send_client_message(int playerid, unsigned color, const std::string& str);

inline void send_client_message(unsigned color, const std::string& str)
{
  send_client_message_to_all(color, str);
}


}

#endif