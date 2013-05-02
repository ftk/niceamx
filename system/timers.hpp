#ifndef TIMERS_HPP
#define TIMERS_HPP

#include <cassert>
#include <functional>
#include <queue>


#include "util/utils.h"

namespace signals {
//
class timers_container_t
{
public:
    //

    //template <typename func_t>
    class timer
    {

	public:
      typedef long timeout_t;
      typedef util::walltime_t walltime_t;
      //typedef bool (*func_t)();
      typedef std::function<void ()> func_t;
    private:
      walltime_t trigger;
      timeout_t timeout;
      //timeout_t remaining;
      func_t func;
      bool once;
    public:
      timer(timeout_t timeout, const func_t& func, bool once = false) :
        timeout(timeout),
        func(std::move(func)), once(once)
      {
        assert(timeout > 0L);
        trigger = util::get_walltime() + timeout;
      }
    //private:
      timer(walltime_t trigger, timeout_t timeout, const func_t& func) :
        trigger(trigger),
        timeout(timeout),
        func(std::move(func)), once(false)
      {
          assert(timeout > 0L);
      }
    public:
      bool operator > (const timer& rhs) const
      {
          return trigger > rhs.trigger;
      }

    private:
      inline void invoke() const
      {
        return func();
      }

    public:
      //bool operator==(const timers_container_t::timer& rhs) const;
      
      friend class timers_container_t;
    };

    typedef timer slot_t;

private:
    typedef std::priority_queue<slot_t, std::vector<slot_t>, std::greater<slot_t> > slots_t;
    slots_t slots;

public:

    timers_container_t() {}

    inline void connect(const slot_t& tm)
    {
        slots.push(tm);
    }
    template <typename... Args>
    inline void emplace(Args&&... args)
    {
        slots.emplace(std::forward<Args>(args)...);
    }

    void process();

    inline void operator () ()
    {
        process();
    }

};



class timer_stop // used as exception
{};

class timer_change_timeout
{
public:
    typedef timers_container_t::timer::timeout_t timeout_t;
    timer_change_timeout(timeout_t t) : new_timeout(t) 
    {
    	assert(t > 0);
    }
private:
    timeout_t new_timeout;
    friend class timers_container_t;
};


} // namespace

/*
//#define REGISTER_TIMER(ms,fn) \
MAINBOX->BOOST_PP_CAT(timer, ms).connect(fn)
*/


#define REGISTER_TIMER(ms,...) (MAINBOX->timers.emplace(ms, (__VA_ARGS__), false))
#define REGISTER_TIMER_ONCE(ms,...) (MAINBOX->timers.emplace(ms, (__VA_ARGS__), true))
//#define REGISTER_TIMER(ms,fn) (MAINBOX->timers.connect({ms, fn}))
//#define REGISTER_TIMER_ONCE(ms,fn) (MAINBOX->timers.connect({ms, fn, true}))

#endif
