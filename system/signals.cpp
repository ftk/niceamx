
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

#define SLOT_ACTION(slot,act) \
	  slots.act(slot); \
	  return true; \
/* */

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
    
    bool timers_container_t::connect(slot_t tm)
    {
      SLOT_ACTION(tm, push_back);
    }
    bool timers_container_t::remove(slot_t tm)
    {
      SLOT_ACTION(tm, remove);
    }
    
    void timers_container_t::proccess(int elapsed)
    {
      if(!slots.empty())
      {
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
    }
  
    

}
