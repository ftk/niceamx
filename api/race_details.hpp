#ifndef API_RACE_DETAILS_HPP
#define API_RACE_DETAILS_HPP

#include "config.h"

#include "util/point.hpp"
#include "counter.hpp"

#include "vehicle.hpp"

#include <istream>
#include <ostream>
#include <cassert>

namespace api {
//

class race_details
{
private:
  struct veh_pos
  {
    util::point3d pos;
    float angle;

    veh_pos() : pos(), angle(0.f) {}
  };
private:
  int vmodel;
  veh_pos left, right;
public:
  float distance;
public:

  race_details(float dist = 15.f) : distance(dist) {}
  
  void import_stream(std::istream& s)
  {
    s >> vmodel;
    s >> left.pos.x >> left.pos.y >> left.pos.z >> left.angle;
    s >> right.pos.x >> right.pos.y >> right.pos.z >> right.angle;
  }
  void export_stream(std::ostream& s)
  {
    s << vmodel << '\n';
    s << left.pos.x << ' ' << left.pos.y << ' ' << left.pos.z << ' ' << left.angle << '\n';
    s << right.pos.x << ' ' << right.pos.y << ' ' << right.pos.z << ' ' << right.angle << '\n';
  }

public:
  void setup_vehicle(basic_vehicle & v, int pos = 1)
  {
    return setup_vehicle(v, get_position(pos - 1));
  }
  int setup_player(int id, int pos = 1);
private:
  void setup_vehicle(basic_vehicle & v, const veh_pos & pos)
  {
    v.set_pos(pos.pos);
    v.set_ang(pos.angle);
  }
  veh_pos get_position(int pos = 0);
};

} // api

#endif