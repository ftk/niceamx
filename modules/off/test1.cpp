#include "util/notify.h"

#include <boost/format.hpp>
#include <boost/bind.hpp>

//#include "api/parsers.hpp"
#include "api/streamer.hpp"
#include "api/cmd.hpp"
#include "api/streams.hpp"

#include "samp.h"


#include <iostream>
#include <istream>
#include <fstream>

namespace {
  
  /*
bool stream()
{
  using namespace native;
  //util::notify("timer");
  //if(!STREAMER->stream(api::player(0)))
    //true;//util::abort("couldnt stream!");
  return true;
}

template <typename node>
bool print(node & obj)
{
  //std::cout << obj.modelid << ' ' << obj.pos->y << std::endl;
  if(!api::streamer::get_instance()->insert(obj.to_object()))
    util::abort("couldnt insert!");
  return true;
}*/

void on_game_mode_init()
{
  native::add_player_class(1, 2500.f, -2700.f, 15.f, 0.f, 0,0, 0,0, 0,0);

  api::message msg(1234, 0);
  *msg << std::endl;
  *msg << "hoho" << "hehe" << 123 << std::endl;
}


void test(int t)
{
  std::cout << t << std::endl;
}


INIT
{
  
  /*
  std::string str = "1459,2237.226318,-2280.630859,5.0,0,0,345.726257;\n";
  api::raw_obj_parser::node node;
  api::raw_obj_parser::parse(str.begin(), str.end(), node);
  std::cout << node.modelid << ' ' << node.rot->z;
  */
  //std::ifstream file("lsfr.ipl");
  //(!file) assert(false && "couldnt open");
    //load_ipl(file);
  //api::ipl_parser::load(file, &print);
  
  //REGISTER_TIMER(1000, &stream);
  
  REGISTER_CB(on_game_mode_init);

  //pawn::log << 123 << " ohoh" << std::hex << 16 << std::endl;
  //pawn::log << "rofl" << "copter" << "\n";
  //if(file)
  //  api::ipl_parser::load(file, [&] {std::cout << _1.modelid;});
}


}
