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
  bool isend = false;
  NOTIFY("ggg");
  REGISTER_TIMER(50, [](){ util::notify(boost::lexical_cast<std::string>(util::get_walltime())); } );
  while(!isend)
  {
    util::sleep(5);
    MAINBOX->timers.proccess(5);
    
    isend = true;
  }
  INVOKE_COMMANDS(0, "/kill");
  INVOKE_COMMANDS(0, "/v 555");
  INVOKE_COMMANDS(0, "/a");
  MAINBOX->plugin_unload();
  INVOKE_DESTRUCTOR();
  return 0;
}
