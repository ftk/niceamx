#include "timers.hpp"
#include "signals.hpp"

#include "util/overtimer.hpp"



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

    // main box //
    /*
    box_t * box_t::instance = NULL;

    box_t * box_t::get_instance()
    {
        if(instance == NULL)
        {
            instance = new box_t;
        }

        return instance;
    }
    void box_t::rm_instance()
    {
        if(instance != NULL)
        {
            delete instance;
            instance = NULL;
        }
    }*/


    // timers
    
    void timers_container_t::connect(slot_t tm)
    {
      slots.push_back(tm);
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
      typedef slots_t::iterator iterator;
      for(iterator it = slots.begin(), en = slots.end(); it != en; ++it)
      {
        it->remaining -= elapsed;
        if(it->remaining <= 0)
        {
          it->remaining = it->timeout;
          try
          {
            it->invoke();
          }
          catch(timer_stop)
          {
            it = slots.erase(it);
            en = slots.end();
            if(it == en)
              return;
          }
        }
      }
    }
  
  /*
    bool timers_container_t::timer::operator==(const timers_container_t::timer& rhs) const
    {
      return(timeout == rhs.timeout && (func.target<void *>() == rhs.func.target<void *>()));
    }
*/
}
