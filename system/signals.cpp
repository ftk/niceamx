#include "timers.hpp"
#include "signals.hpp"

#include "util/overtimer.hpp"
#include <iostream>
#include "util/utils.h"
#include "util/log.h"

#ifndef MAX_TIMER_EXEC_TIME
#ifdef MAX_EXEC_TIME
#define MAX_TIMER_EXEC_TIME MAX_EXEC_TIME
#else
#define MAX_TIMER_EXEC_TIME 3
#endif // MAX_EXEC_TIME
#endif //MAX_TIMER_EXEC_TIME

#define START() MAKE_OVERTIMER(MAX_TIMER_EXEC_TIME)

namespace signals {

// timers

void timers_container_t::process()
{
    if(slots.empty())
        return;
    START();

    timer::walltime_t curtime = util::get_walltime();

    while(!slots.empty() && slots.top().trigger <= curtime)
    {
    	// O(log n) for every invoked timer
    	// NOT todo: replace with fibonacci heap: O(1) for invoking timer, O(log n) for destroying timer
    	// http://www.boost.org/doc/libs/1_53_0/doc/html/heap/data_structures.html
    	
    	
        auto& top = slots.top();
        bool once = top.once;
        timer::timeout_t timeout = top.timeout;
        try
        {
            top.invoke();
        }
        catch(timer_stop)
        {
            once = true;
        }
        catch(timer_change_timeout e)
        {
            timeout = e.new_timeout;
        }
        catch(...)
        {
            // remove timer with problems
            slots.pop();
            // next exception handler
            throw;
        }

        //util::log_msg("timer", "%ld %d %u", long(curtime), once, slots.size());

        if(!once)
        {
            slots.emplace(curtime + timeout, timeout, std::move(top.func));
        }
        slots.pop();
    }
}

void box_t::clear()
{
#define SIGNAL(name,...) this->name.clear();
#include "events.inl"
#undef SIGNAL
}

} // namespace
