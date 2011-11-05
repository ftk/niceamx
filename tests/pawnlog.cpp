#include "config.h"
#include "pawn/pawnlog.hpp"
#include <iostream>
#include "util/streambuf.hpp"

namespace pawn
{
  void logprint(std::string const& log_str)
  {
	  std::cout << "logprint: " << log_str << std::endl;
  }
  static void logprintf_impl(const char * str, ...)
  {
	  std::cout << "logprintf: " << str << std::endl;
  }

  logprintf_t logprintf = logprintf_impl;

  class log_t : public util::streambuf
  {
  protected:
    virtual void call()
    {
      logprint(buffer);
    }
  };

  static log_t logbuff;
  std::ostream log(&logbuff);
} // namespace pawn {

