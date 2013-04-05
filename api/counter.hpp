#ifndef API_COUNTER_HPP
#define API_COUNTER_HPP

#include <boost/format.hpp>
#include <functional>
#include <cassert>

#include "timers.hpp"

namespace api {
//

class counter
{
private:
  int cnt;
  int playerid;
  //typedef void (*finish_fn_t)(counter *);
  typedef std::function<void (counter *)> finish_fn_t;
  finish_fn_t onfinish;
public:
  explicit counter(int c = 5, int id = -1, finish_fn_t fn = NULL) : cnt(c), playerid(id), onfinish(fn) {}
  
  inline void operator()()
  {
    if(!count())
      throw signals::timer_stop();
  }
  bool count()
  {
    if(cnt > 0)
    {
      announce(playerid, boost::str(boost::format("~y~%1%") % cnt)); 
      cnt--;
      return true;
    }
    else
    {
      announce(playerid, "GO GO GO", true);
      if(onfinish != NULL)
        onfinish(this);
      return false;
    }
  }
  
  void set_count(int x)
  {
  	assert(x >= 0);
  	cnt = x;
  }
  
private:
  static void announce(int playerid, const std::string& str, bool done = false);
};

}

#endif
