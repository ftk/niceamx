#include "timers.hpp"
#include "signals.hpp"

#include "util/overtimer.hpp"
#include <iostream>
#include "util/utils.h"

#ifndef MAX_TIMER_EXEC_TIME
#ifdef MAX_EXEC_TIME
#define MAX_TIMER_EXEC_TIME MAX_EXEC_TIME
#else
#define MAX_TIMER_EXEC_TIME 3
#endif // MAX_EXEC_TIME
#endif //MAX_TIMER_EXEC_TIME

#define START() MAKE_OVERTIMER(MAX_TIMER_EXEC_TIME)

namespace signals
{

  // timers
  
  void timers_container_t::connect(slot_t tm)
  {
    slots.push_front(tm);
  }
  /*
  void timers_container_t::remove(slot_t tm)
  {
    slots.remove(tm);
  }*/
  
  void timers_container_t::proccess(int elapsed)
  {
    if(slots.empty())
      return;
    
    START();
    auto it = slots.begin(), en = slots.end();
    
    while(it != en)
    {
      it->remaining -= elapsed;
      //std::cout << it->remaining << '\n';
      if(it->remaining <= 0)
      {
        it->remaining = it->timeout;
        try
        {
          it->invoke();
          ++it;
        }
        catch(timer_stop)
        {
          it = slots.erase(it);
          en = slots.end();
        }
      }
      else
      	++it;
    }
    
  }


}
