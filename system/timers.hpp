#ifndef TIMERS_HPP
#define TIMERS_HPP

#include <cassert>
#include <functional>
#include <list>

namespace signals {
//
class timers_container_t
{
public:
    //

    //template <typename func_t>
    class timer
    {

    private:
      typedef long timeout_t;
      //typedef bool (*func_t)();
      typedef std::function<void ()> func_t;
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
      void invoke()
      {
        return func();
      }

      friend class timers_container_t;
      friend bool operator==(const timers_container_t::timer& l, const timers_container_t::timer& r);
    };

    typedef timer slot_t;
private:
    typedef std::list<slot_t> slots_t;
    slots_t slots;
public:

    timers_container_t() {}

    bool connect(slot_t);
    bool remove(slot_t);
    void proccess(int elapsed);

    inline void operator () (int elapsed = 0)
    {
      proccess(elapsed);
    }

};

inline bool operator==(const timers_container_t::timer& l, const timers_container_t::timer& r)
{
  return(l.timeout == r.timeout && (l.func.target<void *>() == r.func.target<void *>()));
  //return true;
}


class timer_stop // used as exception
{};


}

#endif