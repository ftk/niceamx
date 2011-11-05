#ifndef UTIL_STREAMBUF_HPP
#define UTIL_STREAMBUF_HPP

#include <streambuf>
#include <ostream>

namespace util {
//

class streambuf : public std::streambuf
{
protected:
  std::string buffer;
protected:

  streambuf()
  {
    buffer.reserve(128);
  }
  
  virtual int_type overflow(int_type c)
  {
    if(c != -1 && c != '\n')
    {
      buffer += static_cast<char>(c);
    }
    else
    {
      flush();
    }
    return c;
  }
public:
  virtual streambuf & flush()
  {
    call();
    buffer.clear();
    return(*this);
  }
protected:
  virtual void call() = 0;
};

template <typename stream>
class basic_ostream
{
protected:
  stream buf;
  std::ostream s;
  basic_ostream() : s(&buf) {}
public:

  operator std::ostream& ()
  {
    return(s);
  }
  std::ostream& operator * ()
  {
    return(s);
  }
  template <typename T>
  std::ostream& operator << (T arg)
  {
    s << arg;
    return(s);
  }
};


}

#endif

