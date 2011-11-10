#include "signals.hpp"
#include "util/utils.h"
#include "util/notify.h"
#include "destruct.h"

#include "api/cmd.hpp"

#include <ctime>
#include <cstdlib>
#include <cassert>
#include <boost/lexical_cast.hpp>

int main()
{
  srand(time(NULL));
  INVOKE_INIT();
  MAINBOX->plugin_load();
  /*
  MAINBOX->on_dialog_response(10, 1, 1, 0, "a");
  MAINBOX->on_dialog_response(10, 1, 1, 0, "a");
  MAINBOX->on_dialog_response(10, 1, 1, 0, "a");
  */
  assert(nullptr == 0);
  volatile bool isend = false;
  NOTIFY("ggg");
  REGISTER_TIMER(100, [](){ util::notify(boost::lexical_cast<std::string>(util::get_walltime())); } );
  
  auto lambda = []() { util::notify("muhaha"); };
  
  typedef signals::timers_container_t::timer timer;
  timer timer1 { 1000, lambda }; // c++11 syntax
  timer timer2 = { 1001, []() {} };
  
  REGISTER_TIMER2(timer1);
  REGISTER_TIMER2(timer2);
  while(!isend)
  {
    util::sleep(5);
    MAINBOX->timers.proccess(5);
    
    //isend = true;
  }
  INVOKE_COMMANDS(0, "/kill");
  INVOKE_COMMANDS(0, "/v 555");
  INVOKE_COMMANDS(0, "/a");
  MAINBOX->plugin_unload();
  INVOKE_DESTRUCTOR();
  return 0;
}
