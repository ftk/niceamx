#ifndef API_LOCATION_HPP
#define API_LOCATION_HPP

#include "util/point.hpp"


namespace api {


struct location
{
    float x, y, z;
    float angle;
    int interior;

    location() : x(0.f), y(0.f), z(0.f), angle(0.f), interior(0) {}
    location(float x, float y, float z, float angle = 0.f, int interior = 0) :
      x(x), y(y), z(z), angle(angle), interior(interior)
    {
        while(angle >= 360.f)
        {
            angle -= 360.f;
        }
        while(angle < 0.f)
        {
            angle += 360.f;
        }
    }

    enum teleport_type
    {
        player_only, // teleport player only
        player_or_vehicle, // if player is driver - teleport vehicle
        vehicle_only, // teleport vehicle (if player is in one)
    };

    bool teleport_player(int playerid, teleport_type type = player_only);
    bool teleport_vehicle(int vehicle);

    util::point3d to_point()
    {
        return {x, y, z};
    }

};





} // api


#endif

