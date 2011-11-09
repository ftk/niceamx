// free memory
#include "destruct.h"

#include "api/streamer.hpp"
#include "api/playerpool.hpp"
#include "api/dialogs.hpp"
#include "api/cmd.hpp"
#include "signals.hpp"
//#include "api/log.hpp"

#include <iostream>

DESTRUCTOR void destruct_all()
{
  using namespace api;
  using namespace signals;

  try
  {
    streamer::rm_instance();
    players::rm_instance();
    dialogs::rm_instance();
    commands::rm_instance();
    //log_t::rm_instance();
    box_t::rm_instance();
  }
  catch(...)
  {
    std::cerr << "Exception during destroying singletons" << std::endl;
    throw;
  }
  
}


