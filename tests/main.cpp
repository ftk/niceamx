#include "signals.hpp"
#include "util/utils.h"
#include "util/notify.h"
#include "destruct.h"

#include <ctime>
#include <cstdlib>
#include <cassert>
#include "util/strings.h"

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
  REGISTER_TIMER(50, [](){ util::notify(util::convert_to_string(util::get_walltime())); } );
  while(!isend)
  {
    util::sleep(5);
    MAINBOX->timers.proccess(5);
    
    isend = true;
  }
  MAINBOX->plugin_unload();
  destruct_all();
  return 0;
}
