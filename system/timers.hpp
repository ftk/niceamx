#ifndef TIMERS_HPP
#define TIMERS_HPP

#include <cassert>
#include <functional>

#include "util/config/slist.h"


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
      //typedef bool (*func_t)();
      typedef std::function<void ()> func_t;
    private:
      timeout_t timeout;
      timeout_t remaining;
      func_t func;
    public:
      timer(timeout_t timeout_, func_t func_) :
        timeout(timeout_),
        remaining(timeout_),
        func(func_)
      {
        assert(timeout_ >= 0L);
      }
    private:
      inline void invoke()
      {
        return func();
      }

    public:
      //bool operator==(const timers_container_t::timer& rhs) const;
      
      friend class timers_container_t;
    };

    typedef timer slot_t;
private:
    typedef SLIST <slot_t> slots_t;
    slots_t slots;
public:

    timers_container_t() {}

    void connect(slot_t);
    void proccess(int elapsed);

    inline void operator () (int elapsed)
    {
      proccess(elapsed);
    }

};



class timer_stop // used as exception
{};


}

/*
//#define REGISTER_TIMER(ms,fn) \
MAINBOX->BOOST_PP_CAT(timer, ms).connect(fn)
*/

#define MAKE_TIMER(ms,fn) signals::timers_container_t::timer(ms, fn) // calling constructor to make timer ( for internal use )

#define REGISTER_TIMER2(obj) REGISTER_CALLBACK(timers, obj)
#define REGISTER_TIMER(ms,fn) REGISTER_TIMER2(MAKE_TIMER(ms, fn))


#endif