#include "config.h"
#include "pawnlog.hpp"
#include <boost/algorithm/string.hpp>
#include "util/streambuf.hpp"

namespace pawn 
{
  logprintf_t logprintf = 0;
  void logprint(std::string const& log_str)
  {
    std::string line = boost::replace_all_copy(log_str, "~", " ");
    if (line.length() > 127)
    {
      line = line.substr(0, 127-3) + "...";
    }
    if(logprintf != NULL)
      logprintf("%s", line.c_str());
  }

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

