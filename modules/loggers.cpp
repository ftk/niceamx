
#include "samp.h"
#include "api/cmd2.hpp"
#include "api/pipes.hpp"

#include "util/utils.h"
#include "util/log.h"

#include "pawn/pawnlog.hpp"
#include "pawn/hooks.h"

#include <vector>
#include <string>

#include <boost/utility/string_ref.hpp>
#include <boost/circular_buffer.hpp>

struct redirect_entry
{
    std::string module_substr;
    std::string msg_substr;
    int pipe;
};

static std::vector<redirect_entry> redirects;
static boost::circular_buffer<std::string> logbuffer;

// logs to logbuffer (if enabled with 'logbuff') --> read with 'logread'
// and sends log messages to subscribers
// disabled by default
static void logger_redirect(const char * module, const char * msg)
{
    static bool recursion = false;
    if(recursion)
        return;
    recursion = true;


    boost::string_ref module_s(module), msg_s(msg);

    const auto npos = boost::string_ref::npos;

    std::string fmt_msg;

    if(logbuffer.capacity() != 0)
    {
        fmt_msg = util::sprintf("<%s>: %s", module, msg);
        logbuffer.push_back(fmt_msg);
    }

    for(const auto& e : redirects)
    {
        if((!e.module_substr.empty() && module_s.find(e.module_substr) != npos) ||
                (!e.msg_substr.empty() && msg_s.find(e.msg_substr) != npos))
        {
            // found
            if(fmt_msg.empty()) //format
                fmt_msg = util::sprintf("<%s>: %s", module, msg);
            api::send_pipe_msg(e.pipe, std::move(fmt_msg));
        }
    }

    recursion = false;
}

// registers logger_redirect as logger
static void register_logger()
{
    static bool registered = false;

    if(!registered) // once
    {
        util::register_logger(&logger_redirect);
        registered = true;
    }
}


INIT
{
#ifdef HOOK_PAWNLOG
    REGISTER_COMMAND("log_unhook", api::cmdflag::RCON | api::cmdflag::ADMIN,
                     [](api::cmdinfo_t info)
    {
        if(pawn::is_hooked_logprintf())
            if(!pawn::rehook_logprintf())
                api::send_pipe_msg(info.caller, "cant unhook!");
    });
    REGISTER_COMMAND("log_hook", api::cmdflag::RCON | api::cmdflag::ADMIN,
                     [](api::cmdinfo_t info)
    {
        if(!pawn::is_hooked_logprintf())
            if(!pawn::rehook_logprintf())
                api::send_pipe_msg(info.caller, "cant hook!");
    });
#endif

    REGISTER_COMMAND("logsub", api::cmdflag::ADMIN,
                     [](api::cmdinfo_t info)
    {
        api::parser_cmd p("s?sd", info);

        redirect_entry e;
        e.module_substr = p.get_string(0);
        if(p.get_optional<const char *>(1))
            e.msg_substr = p.get_string(1);

        e.pipe = p.get(2, info.caller); // this pipe by default

        redirects.push_back(std::move(e));

        register_logger();
    });

    // unsubscribe
    REGISTER_COMMAND("logunsub", api::cmdflag::ADMIN,
                     [](api::cmdinfo_t info)
    {
        api::parser_cmd p("?d", info);

        auto redir_id = p.get_optional<int>(0);

        if(redir_id)
        {
            try
            {
                redirects.erase(redirects.begin() + *redir_id);
            }
            catch(std::exception&)
            {
                api::send_pipe_msg(info.caller, "{FF0000}Wrong id!");
            }

            return;
        }
        // show redirects
        for(std::size_t i = 0; i < redirects.size(); i++)
        {
            api::send_pipe_msgf(info.caller, R"(%d: %d -> "%s" "%s")", i,
                                redirects[i].pipe, redirects[i].module_substr.c_str(),
                                redirects[i].msg_substr.c_str());
        }

    });

    // saves N last log messages, read with logread
    // logbuff 0 to disable log buffering
    REGISTER_COMMAND("logbuff", api::cmdflag::ADMIN,
                     [](api::cmdinfo_t info)
    {
        api::parser_cmd p("?d", info);
        int cap = p.get(0, 10);
        logbuffer.set_capacity(cap);
        register_logger();
    });
    REGISTER_COMMAND("logread", api::cmdflag::ADMIN,
                     [](api::cmdinfo_t info)
    {
        for(const auto& line : logbuffer)
        {
            api::send_pipe_msg(info.caller, line);
        }

    });


}

