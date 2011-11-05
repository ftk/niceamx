#ifndef API_VEHICLE_HPP
#define API_VEHICLE_HPP

#include "util/point.hpp"

#include <cassert>

namespace api {

struct basic_vehicle
{
  // id
  int vehicleid;

  basic_vehicle(int id) : vehicleid(id)
  {}

  virtual int get_id() const
  {
    return vehicleid;
  }

  int operator * () const
  {
    return get_id();
  }

  virtual operator int () const
  {
    return get_id();
  }

  // props
  // ...

  // methods

  virtual util::point3d get_pos() const = 0;

  virtual void set_pos(const util::point3d& p) = 0;
  virtual void set_ang(float ang) = 0;

  virtual void set_pos(const util::point3d& p, float ang)
  {
    set_pos(p);
    set_ang(ang);
  }

};

struct vehicle : basic_vehicle
{

  vehicle(int id) : basic_vehicle(id) {}

  util::point3d get_pos() const;

  void set_pos(const util::point3d& p);
  void set_ang(float ang);

};


}

#endif

