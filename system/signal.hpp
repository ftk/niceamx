#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include "config.h"

#ifdef BOOST_NO_VARIADIC_TEMPLATES 
#error required variadic templates support
#endif

#include <list>
#include <functional>
//#include <boost/function.hpp>

//#include <boost/preprocessor/cat.hpp>

#ifndef SIGNAL_SLOT_RETURN_TYPE
#define SIGNAL_SLOT_RETURN_TYPE void
#endif


namespace signals {

//

template <typename Slot, typename ... Args>
class basic_signal
{
public:
  static const int arg_num = sizeof...(Args);
  
  //typedef SIGNAL_SLOT_RETURN_TYPE (*slot_t)(Args...);
  //typedef std::function<SIGNAL_SLOT_RETURN_TYPE (Args ...)> slot_t;
  typedef Slot slot_t;
protected:
  std::list<slot_t> slots;
  
public:
  //signal() : slots() {}
  
  inline bool connect(slot_t f)
  {
    return connect_back(f);
  }
  inline bool remove(slot_t f)
  {
    slots.remove(f);
    return true;
  }
  
  inline void invoke(Args... args)
  {
    if(slots.empty())
      return;
    for(auto it = slots.cbegin(), en = slots.cend(); it != en; ++it)
    {
      (*it)(args...);
    }
  }
  
public:
  inline bool operator () (Args... args)
  {
    invoke(args...);
    return true;
  }
  
  inline basic_signal& operator += (slot_t slot)
  {
    connect(slot);
    return(*this);
  }
public:
  inline bool connect_back(slot_t f)
  {
    try
    {
      slots.push_back(f);
    }
    catch(...)
    {
      return false;
    }
    return true;
  }
  inline bool connect_front(slot_t f)
  {
    try
    {
      slots.push_front(f);
    }
    catch(...)
    {
      return false;
    }
    return true;
  }
};


template <typename ... Args>
class signal : public basic_signal<std::function<SIGNAL_SLOT_RETURN_TYPE (Args...)>, Args...>
{};

template <typename ... Args>
class signal_simple : public basic_signal<SIGNAL_SLOT_RETURN_TYPE (*)(Args...), Args...>
{};

}


#endif

