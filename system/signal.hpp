#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include "config.h"
#include "util/config/slist.h"

#ifdef BOOST_NO_VARIADIC_TEMPLATES 
#error required variadic templates support
#endif

#include <functional>
//#include <boost/function.hpp>

//#include <boost/preprocessor/cat.hpp>

#ifndef SIGNAL_SLOT_RETURN_TYPE
#define SIGNAL_SLOT_RETURN_TYPE void
#endif


namespace signals {

//

class slot_remove {};

template <typename Slot, typename ... Args>
class basic_signal
{
public:
  static const int arg_num = sizeof...(Args);
  
  //typedef SIGNAL_SLOT_RETURN_TYPE (*slot_t)(Args...);
  //typedef std::function<SIGNAL_SLOT_RETURN_TYPE (Args ...)> slot_t;
  typedef Slot slot_t;
protected:
  SLIST <slot_t> slots;
  
public:
  //signal() : slots() {}
  
  inline void connect(slot_t f)
  {
    slots.push_front(f);
  }
  inline void remove(slot_t f)
  {
    slots.remove(f);
  }
  
  inline void invoke(Args... args)
  {
    if(slots.empty())
      return;
    auto it = slots.begin(), en = slots.end();
    while(it != en)
    {
      try
      {
        (*it)(args...);
        ++it;
      }
      catch(slot_remove)
      {
        it = slots.erase(it);
        en = slots.end();
      }
    }
  }
  
public:
  inline void operator () (Args... args)
  {
    invoke(args...);
  }
  
  inline basic_signal& operator += (slot_t slot)
  {
    connect(slot);
    return(*this);
  }
public:
  /*
  inline void connect_back(slot_t f)
  {
    slots.push_back(f);
  }
  inline void connect_front(slot_t f)
  {
    slots.push_front(f);
  }*/
};

// functor
template <typename ... Args>
class signal : public basic_signal<std::function<SIGNAL_SLOT_RETURN_TYPE (Args...)>, Args...>
{};

// function pointer
template <typename ... Args>
class signal_simple : public basic_signal<SIGNAL_SLOT_RETURN_TYPE (*)(Args...), Args...>
{};

}


#endif

