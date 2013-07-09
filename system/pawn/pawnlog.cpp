#include "config.h"
#include "pawnlog.hpp"
#include <boost/algorithm/string.hpp>
#include "util/streambuf.hpp"
#include "util/log.h"

#include "hooks.h"

namespace pawn {

logprintf_t logprintf = NULL;

void logprint(std::string log_str)
{
#ifdef HOOK_PAWNLOG
    if(is_hooked_logprintf())
    {
        return util::log_msg_nofmt("serverlog/msg/logprint", log_str.c_str());
    }
#endif
    boost::replace_all(log_str, "~", " ");
    if(log_str.length() > 127)
	{
      log_str.erase(127-3);
      log_str.append("...");
	}
	if(logprintf != NULL)
      logprintf("%s", log_str.c_str());
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

