
#include "notify.h"

#include <ostream>

#ifdef USE_PAWN_NOTIFY

#include "pawn/pawnlog.hpp"

#else
#include <iostream>
#endif


#include <string>
#include <cstdlib>
#include <boost/lexical_cast.hpp>
#include <ctime>

#ifdef USE_PAWN_NOTIFY
#define STDOUT_STREAM pawn::log
#define STDERR_STREAM pawn::log
#define NEWLINE "\n"
#else
#define STDOUT_STREAM std::cout
#define STDERR_STREAM std::cerr
#define NEWLINE std::endl
#endif

namespace util
{
    static void print_to_stream(std::ostream& out, const std::string& prefix, const std::string& msg)
    {
      time_t timestamp;
      struct tm * timedate;
      time(&timestamp);
      timedate = localtime(&timestamp);
      char buf[128];
      strftime(buf, sizeof(buf) / sizeof(*buf), " [%d-%m-%Y/%H:%M:%S] ", timedate);
      out << timestamp << buf << prefix << ": " << msg << NEWLINE;
    }
    static inline std::string format_prefix(const char * prefix, const char * file, int line, const char * func)
    {
      std::string result = prefix;
      return (((((((result += '[') += file) += ':') += boost::lexical_cast<std::string>(line)) += ':') += func) += ']');
    }

#define MAKE_FUNC(func,ev) \
void func (const std::string& s) \
{ \
 print_to_stream(STDERR_STREAM, ev, s); \
} \
void func (const char * file, int line, const char * func, const std::string& s) \
{ \
 print_to_stream(STDERR_STREAM, format_prefix(ev, file, line, func), s); \
} \
/* */

    MAKE_FUNC(notify, "Notify")
    MAKE_FUNC(warning, "Warning")
    MAKE_FUNC(error, "ERROR")

    
    void abort(const std::string& s, int level)
    {
        print_to_stream(STDERR_STREAM, "ABORTING", s);
        exit(level);
    }


}


