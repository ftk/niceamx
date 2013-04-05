#include "signals.hpp"
#include "util/utils.h"
#include "util/notify.h"
#include "destruct.h"
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
  INVOKE_INIT();
  MAINBOX->plugin_load();
  
  using namespace api;
  
  //REGISTER_COMMAND2("test")
  INVOKE_COMMANDS(pipe::LOG, cmdflag::ALL, "gconfig test \"abc def ghi 1\"");
  INVOKE_COMMANDS(pipe::LOG, cmdflag::ALL, "gconfig test");
  while(false)
  {
    util::sleep(5);
    MAINBOX->timers.proccess(5);
    
    //isend = true;
  }
  MAINBOX->plugin_unload();
  INVOKE_DESTRUCTOR();
  return 0;
}
