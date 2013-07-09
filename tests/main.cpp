#include "signals.hpp"
#include "util/utils.h"
#include "util/log.h"


#include "api/cmd2.hpp"
#include "api/pipes.hpp"

#include <ctime>
#include <cstdlib>
#include <cassert>
#include <boost/lexical_cast.hpp>

int main()
{
  srand(time(NULL));
  util::register_logger(&util::logger_stdout);
  INVOKE_INIT();
  MAINBOX->plugin_load();
  
  using namespace api;
  
  //REGISTER_COMMAND2("test")
  
  while(false)
  {
    util::sleep(5);
    MAINBOX->timers();
    
    //isend = true;
  }
  MAINBOX->plugin_unload();
  return 0;
}
