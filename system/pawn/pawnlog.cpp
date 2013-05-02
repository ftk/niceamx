#include "config.h"
#include "pawnlog.hpp"
#include <boost/algorithm/string.hpp>
#include "util/streambuf.hpp"

namespace pawn {

logprintf_t logprintf = NULL;

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



/*
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
*/

util::stream<pawnlog_sink> log(0);

void logger_serverlog(const char * module, const char * msg)
{
	char buf[128];
	int len = snprintf(buf, sizeof(buf) - 1, "<%s>: %s", module, msg);
	buf[len] = '\0';
    logprint(buf);
    //if(logprintf != NULL)
      //logprintf("%s", buf);
}

} // namespace pawn {

