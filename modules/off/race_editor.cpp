#include "api/cmd.hpp"
#include "api/race.hpp"
#include "api/race_details.hpp"

#include "samp.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <boost/format.hpp>

using namespace api;

detail::race_loader * r;
race_details * r_d;

static int step_ = 0;

std::stringstream details(std::stringstream::in | std::stringstream::out);

bool make_cp(int id, util::strings&)
{
  ++step_;
  float x, y, z, a;
  
  native::get_player_pos(id, x, y, z);
  a = native::get_player_facing_angle(id);
  native::send_client_message(id, 0xffffffff, boost::str(boost::format("x: %1% y: %2% z: %3% a: %4%") % x % y % z % a));
  if(step_ == 1 || step_ == 2)
    details << x << ' ' << y << ' ' << z << ' ' << a << '\n';
  else
  {
    (*r)({x, y, z});
  }
  if(step_ == 3)
  {
    r_d->import_stream(details);
    std::ofstream file("race_d.txt");
    r_d->export_stream(file);
  }
  return true;
}

void setup()
{
  r = new detail::race_loader;
  std::cout << "2" << std::endl;
  r_d = new race_details;
  std::cout << "3" << std::endl;
  details << "400\n";
  std::cout << "4" << std::endl;
}

INIT
{
  REGISTER_COMMAND("edit", [](int, util::strings&) -> bool
  {
    setup();
    return true;
  });
  REGISTER_COMMAND("cp", &make_cp);
  REGISTER_COMMAND("stop", [&r, &r_d, &details](int, util::strings&) -> bool
  {
    std::ofstream file("race.txt");
    r->export_stream(file);
    delete r;
    delete r_d;
    return true;
  });
  REGISTER_COMMAND("a", [](int id, util::strings&) -> bool
  {
    native::send_client_message(id, 0xffffffff, "hello world");
    return true;
  });
  REGISTER_COMMAND("v", [](int id, util::strings& s) -> bool
  {
    float x, y, z;
    native::get_player_pos(id, x, y, z);
    native::create_vehicle(util::convert_from_strings<int, 1>(s), x, y, z, 0, -1, -1, 60);
    return true;
  });
  //native::get_player_facing_angle(11);
}


