#ifndef API_STREAMS_HPP
#define API_STREAMS_HPP

#include "config.h"
#include <ostream>
#include <cassert>

//#include <boost/preprocessor/cat.hpp>

#include "util/streambuf.hpp"

namespace api {

class message;



class message_stream : public util::streambuf
{
private:
  unsigned color;
  int playerid;
protected:
  void call();

  friend class message;
};


class message : public util::basic_ostream<message_stream>
{
public:
  message(unsigned c = 0xffffffff, int p = -1)
  {
    assert(p >= -1);
    buf.color = c;
    buf.playerid = p;
  }
};


}

//#define MAKE_STREAM(name,...) BOOST_PP_CAT(name, __object) (__VA_ARGS__); std::ostream name (& BOOST_PP_CAT(name, __object) )
//// usage: api::message MAKE_STREAM(msgstream, 0xff); msgstream << "bugoga" << std::endl;

#endif
