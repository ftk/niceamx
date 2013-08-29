#include "timers.hpp"
#include "signals.hpp"

//#include "util/overtimer.hpp"
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

#define START() ((void)0)

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
    	
    	
        auto&& top = slots.top();
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
#define SIGNAL0(name) SIGNAL(name,)
#include "events.inl"
#undef SIGNAL0
#undef SIGNAL
}

bool box_t::empty() const
{
    bool is_empty = true; 
#define SIGNAL(name,...) is_empty = is_empty && this->name.empty();
#define SIGNAL0(name) SIGNAL(name,)
#include "events.inl"
#undef SIGNAL0
#undef SIGNAL
    return is_empty;
}

box_t::box_t()
{
    // no inline
}

box_t::~box_t()
{
    // no inline
}




} // namespace

#ifdef SIGNALS_EXPLICIT_INST
// HACK

// explicit template instantiation
#define SIGNAL(name,...) \
    template class std::function<void(__VA_ARGS__)>; \
    template class \
    signals::basic_priority_signal<std::function<void(__VA_ARGS__)>, __VA_ARGS__ >;
#define SIGNAL0(name) /**/

template class std::function<void()>;
template class signals::basic_priority_signal<std::function<void()> >;
template class signals::basic_signal<void (*)()>;

//#include "events.inl" // duplicate explicit instantiation
SIGNAL(i, int)
SIGNAL(ii, int, int)
SIGNAL(iii, int, int, int)
SIGNAL(is, int, std::string&)
SIGNAL(ics, int, const std::string&)
SIGNAL(cs, const std::string&)
SIGNAL(iiii, int, int, int, int)
SIGNAL(cscsi,  const std::string&, const std::string&, int)
SIGNAL(iiiics, int, int, int, int, const std::string&)
SIGNAL(iifi, int, int, float, int)
SIGNAL(ifff, int, float, float, float)

#undef SIGNAL
#undef SIGNAL0

#endif

