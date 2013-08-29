#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include "config.h"
#include <forward_list>
#include <functional>
#include <utility>

#include <boost/noncopyable.hpp>


#ifndef SIGNAL_SLOT_RETURN_TYPE
#define SIGNAL_SLOT_RETURN_TYPE void
#endif


namespace signals {

//
// used as exception
class slot_remove {}; // disconnect from signal
class signal_return // skip invoking other slots
{
    const int ret;
public:
    signal_return(int ret) : ret(ret) {}
    int get() const { return ret; }
};



// ------------------
// holds a list of Callable s
template <typename Slot, typename ... Args>
class basic_signal : boost::noncopyable
{
public:
  static const int arg_num = sizeof...(Args);
  
  //typedef SIGNAL_SLOT_RETURN_TYPE (*slot_t)(Args...);
  //typedef std::function<SIGNAL_SLOT_RETURN_TYPE (Args ...)> slot_t;
  typedef Slot slot_t;
protected:
  std::forward_list<slot_t> slots;
  
public:
  //signal() : slots() {}
  
  inline void connect(const slot_t& f) // O(1)
  {
    slots.push_front(f);
  }
  template <typename... EArgs>
  inline void emplace(EArgs&&... args)
  {
      slots.emplace_front(std::forward<EArgs>(args)...);
  }

  inline void clear()
  {
    slots.clear();
  }
  
  inline void invoke(Args... args)
  {
  	(*this)(args...);
  }
  
  inline void operator () (Args... args)
  {
    if(slots.empty())
      return;
    auto it = slots.begin(), end = slots.end();
    auto prev = slots.before_begin();
    while(it != end)
    {
      try
      {
        (*it)(args...);
      }
      catch(slot_remove)
      {
        slots.erase_after(prev);
        it = prev;
      }
      prev = it;
      ++it;
    }
  }
  
  
  inline basic_signal& operator += (const slot_t& slot)
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
  
  inline bool empty()
  {
  	return slots.empty();
  }
};

// -------------------
// holds sorted list of Callable s
// TODO: perfect forwarding
template <typename Slot, typename ... Args>
class basic_priority_signal : boost::noncopyable
{
public:
  static const int arg_num = sizeof...(Args);

  typedef std::pair<const long,Slot> slot_t;

  typedef typename std::forward_list<slot_t>::iterator connection_type;
protected:
  std::forward_list<slot_t> slots;
  const int default_return_value;

public:

  basic_priority_signal(int ret = 1) : default_return_value(ret) {}
  ~basic_priority_signal() {}

  inline connection_type connect(Slot&& f)
  {
      return connect(0L, std::move(f));
  }

  inline connection_type connect(long priority, Slot&& f) // O(n)
  {
      auto prev = slots.cbefore_begin(),
              next = slots.cbegin(),
              end = slots.cend();
      while(next != end)
      {
          // <=
          if(priority < next->first)
          {
              return slots.insert_after(prev, std::make_pair(priority, std::move(f)));
          }
          prev = next;
          ++next;
      }
      return slots.insert_after(prev, std::make_pair(priority, std::move(f)));
  }


  inline void clear()
  {
    slots.clear();
  }

  template <typename ... EArgs>
  inline int operator () (EArgs&&... args) // O(n)
  {
    if(slots.empty())
      return default_return_value;
    auto it = slots.cbegin(), end = slots.cend();
    auto prev = slots.cbefore_begin();
    while(it != end)
    {
      try
      {
        (it->second)(std::forward<EArgs>(args)...);
        prev = it;
        ++it;
      }
      catch(slot_remove)
      {
        it = slots.erase_after(prev);
      }
      catch(signal_return e)
      {
        return e.get();
      }
    }

    return default_return_value;
  }


  inline basic_priority_signal& operator += (Slot&& slot)
  {
    connect(std::move(slot));
    return(*this);
  }
public:


  inline bool empty() const
  {
    return slots.empty();
  }

  inline bool disconnect(connection_type con) // O(n)
  {
      auto it = slots.cbegin(), end = slots.cend();
      auto prev = slots.cbefore_begin();
      while(it != end)
      {
          if(it == con)
          {
              slots.erase_after(prev);
              return true;
          }
          prev = it;
          ++it;
      }
      return false;
  }

};


// functor


template <typename ... Args>
using signal = basic_priority_signal<std::function<void (Args...)>, Args...>;

/*
template <typename ... Args>
class signal : public basic_signal<std::function<void (Args...)>, Args...>
{};
*/

// function pointer

template <typename ... Args>
using signal_funptr = basic_signal<void (*)(Args...), Args...>;
/*
template <typename ... Args>
class signal_simple : public basic_signal<void (*)(Args...), Args...>
{};
*/

}


#endif

