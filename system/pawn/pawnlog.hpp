#ifndef PAWN_LOG_HPP
#define PAWN_LOG_HPP
#include "config.h"
#include <string>
#include <ostream>

#include "util/streambuf.hpp"



namespace pawn {

typedef void (*logprintf_t)(char const* format, ...);
extern logprintf_t logprintf;

void logprint(std::string log_str);

/*
class log_t : public std::ostream
{
//std::string buffer;
public:

log_t() {}

template <typename T>
inline log_t& operator << (T& obj)
{

  std::string word(obj);
  if(word == "\n")
  {
logprint(buffer);
buffer = "";
  }
  else
buffer += word;

  logprint(std::string(obj));
  return (*this);
}
};*/


class pawnlog_sink : public util::line_sink
{
protected:
    void call()
    {
        logprint(buffer);
    }
public:
    pawnlog_sink(int) {}
};

extern util::stream<pawnlog_sink> log;


void logger_serverlog(const char * module, const char * msg);



//extern std::ostream log;



} // namespace pawn {


#endif // PAWN_LOG_HPP
