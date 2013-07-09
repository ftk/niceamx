#include "config.h"
#include "pawn/pawnlog.hpp"
#include <iostream>
#include "util/streambuf.hpp"

namespace pawn {


void logprint(std::string log_str)
{
  std::cout << "logprint: " << log_str << std::endl;
}
static void logprintf_impl(const char * str, ...)
{
  std::cout << "logprintf: " << str << std::endl;
}

logprintf_t logprintf = &logprintf_impl;

util::stream<pawnlog_sink> log(0);

void logger_serverlog(const char * module, const char * msg)
{
	char buf[128];
	int len = snprintf(buf, sizeof(buf) - 1, "<%s>: %s", module, msg);
	buf[len] = '\0';
    logprint(buf);
}

} // namespace pawn {

