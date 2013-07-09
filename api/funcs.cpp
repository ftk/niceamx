#include <string>
#include "funcs.h"
#include "pawn/natives.h"

#include "api/playerpool.hpp"
#include "api/location.hpp"


namespace api {
//
void send_client_message_to_all(unsigned color, const std::string& str)
{
  for(int id : *PLAYERBOX)
  {
    native::send_client_message(id, color, str);
  }
}
void send_client_message(int playerid, unsigned color, const std::string& str)
{
  native::send_client_message(playerid, color, str);
}

void send_adaptation_cmd(int playerid, const std::string& cmd)
{
    return send_client_message(playerid, 0x01010101u, "$cmd " + cmd);
}

bool is_vehicle_connected(int vehicle)
{
    return native::get_vehicle_model(vehicle) != 0;
}

bool is_player_spawned(int player)
{
    int state = native::get_player_state(player);
    return state == native::PLAYER_STATE_DRIVER || state == native::PLAYER_STATE_PASSENGER ||
            state == native::PLAYER_STATE_ONFOOT;
}

bool location::teleport_player(int playerid, teleport_type type)
{
    if(!native::is_player_connected(playerid))
        return false;
    int vehicle = native::get_player_vehicle_id(playerid);
    if(type != player_only && vehicle &&
            (type == vehicle_only ||
             native::get_player_vehicle_seat(playerid) == 0))
    {
        teleport_vehicle(vehicle);
    }
    else
    {
        if(vehicle)
            native::remove_player_from_vehicle(playerid);
        native::set_player_pos(playerid, x, y, z);
        native::set_player_facing_angle(playerid, angle);
        native::set_player_interior(playerid, interior);
    }

    return true;
}

bool location::teleport_vehicle(int vehicle)
{
    if(!is_vehicle_connected(vehicle))
        return false;
    // teleport vehicle
    native::set_vehicle_pos(vehicle, x, y, z);
    native::set_vehicle_zangle(vehicle, angle);
    native::link_vehicle_to_interior(vehicle, interior);

    for(auto it : PLAYERBOX->get())
    {
        if(native::is_player_in_vehicle(it, vehicle))
            native::set_player_interior(it, interior);
    }
    return true;
}


}
