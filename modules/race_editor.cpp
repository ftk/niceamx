#include "api/cmd.hpp"
#include "api/race.hpp"
#include "api/race_details.hpp"

#include "samp.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <boost/format.hpp>
//#include "util/strings.h"

#define FORMAT(arg) (boost::str(boost::format arg))

namespace {

using namespace api;

detail::race_loader r;

int step_ = 0;

std::stringstream details(std::stringstream::in | std::stringstream::out);

bool make_cp(int id, const std::string&)
{
  ++step_;
  float x, y, z, a;
  
  native::get_player_pos(id, x, y, z);
  a = native::get_player_facing_angle(id);
  native::send_client_message(id, 0xffffffff, FORMAT(("x: %1% y: %2% z: %3% a: %4%") % x % y % z % a));
  if(step_ == 1 || step_ == 2)
    details << x << ' ' << y << ' ' << z << ' ' << a << '\n';
  else
  {
    //r({x, y, z});
    r(util::point3d(x, y, z)); // c++03
  }
  if(step_ == 3)
  {
    race_details r_d;
    r_d.import_stream(details);
    std::ofstream file("race_d.txt");
    r_d.export_stream(file);
  }
  return true;
}

void setup()
{
  details.str(std::string()); // clear
  details << "400\n";
}

INIT
{
  REGISTER_COMMAND("edit", [](int, const std::string&) -> bool
  {
    setup();
    return true;
  });
  REGISTER_COMMAND("cp", &make_cp);
  REGISTER_COMMAND("stop", [](int, const std::string&) -> bool
  {
    std::ofstream file("race.txt");
    r.export_stream(file);
    r.destruct();
    return true;
  });
  REGISTER_COMMAND("a", [](int id, const std::string&) -> bool
  {
    native::send_client_message(id, 0xffffffff, "hello world");
    return true;
  });
  REGISTER_COMMAND("v", [](int id, const std::string& s) -> bool
  {
    float x = 0.f, y = 0.f, z = 0.f;
    native::get_player_pos(id, x, y, z); // TODO: produces a lot of valgrind errors in test mode
    try
    {
      native::create_vehicle(api::tokenizer(s).at<int>(1), x, y, z, 0, -1, -1, 60);
    }
    catch(boost::bad_lexical_cast& e)
    {
      // wrong argument supplied
    }
    return true;
  });
  //native::get_player_facing_angle(11);
}

}
