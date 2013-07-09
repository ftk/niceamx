#include "api/pipes.hpp"

#include "api/playerpool.hpp"
#include "api/cmd2.hpp"

#include "pawn/natives.h"
#include "pawn/pawnlog.hpp"

#include "util/log.h"
#include "util/utils.h"

#include "signals.hpp"


#include <cstdio>
#include <cstdarg>

namespace api {

signals::signal<int, const std::string&> on_pipe_message;


/*
void send_pipe_msg(int pipe, const std::string& msg)
{
    on_pipe_message(pipe, msg);
}*/

void send_pipe_msg(int pipe, std::string msg)
{

    // erase colors {123456}
    if(!is_pipe_colored(pipe) && msg.size() >= 8)
    {
        /*
        for(auto it = msg.begin() + 7; it != msg.end(); ++it)
        {
            if(*it == '}' && *(it-7) == '{')
            {
                // erase color code
                it = msg.erase(it-7, it+1);

            }
        }*/
        /*
        for(std::size_t i = 0; i < msg.size() - 7; i++)
        {
            while(msg[i] == '{' && msg[i+7] == '}')
            {
                msg.erase(i, 8);
            }
        }*/
        for(std::size_t i = msg.size() - 1; i >= 7; i--)
        {
            while(msg[i] == '}' && msg[i-7] == '{')
            {
                msg.erase(i-7, 8);
                i -= 8;
            }
        }

    }
    on_pipe_message(pipe, std::move(msg));
}




/* copying
void send_pipe_msgf(int pipe, const char * format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    int len = vsnprintf(buffer, util::array_sizeof(buffer), format, args);
    buffer[len] = '\0';
    va_end(args);
    send_pipe_msg(pipe, buffer);
}
*/
// without copying
void send_pipe_msgf(int pipe, const char * format, ...)
{
    va_list args;
    va_start(args, format);
    send_pipe_msg(pipe, util::vsprintf(format, args));
    va_end(args);
    
}


bool is_pipe_colored(int pipe)
{
    return((pipe >= 0 && pipe < native::MAX_PLAYERS) || (pipe == pipe::ALL));
}




} //api


static void pipe_handler(int pipe, const std::string& msg)
{
    if(pipe >= 0 && pipe < native::MAX_PLAYERS)
    {
        if(PLAYERBOX->valid(pipe))
            native::send_client_message(pipe, 0xffffffffu, msg);
        else
            util::log_msg("pipe/error", "sending msg to invalid pipe %d %s", pipe,
                          msg.c_str());
        return;
    }

    using namespace api::pipe;
    //using namespace std;
    switch(pipe)
    {
    case STDOUT:
        //fprintf(stdout, "%s\n", msg.c_str()); break;
        ::puts(msg.c_str()); break;
    case STDERR:
        ::fprintf(stderr, "%s\n", msg.c_str()); break;
    case SERVERLOG:
        pawn::logprint(msg); break;
    case ALL:
        for(int id : *PLAYERBOX)
        {
            native::send_client_message(id, 0xffffffffu, msg);
        } break;

    case LOG:
        util::log_msg_nofmt("pipe/log", msg.c_str()); break;
    case api::pipe::FILE:
        util::log_msg_nofmt("pipe/file", msg.c_str()); break;
    }
}

INIT
{
    api::on_pipe_message.connect(&pipe_handler);

    using namespace api::cmdflag;
    REGISTER_COMMAND("send_to", RCON | ADMIN | CONFIG, [](api::cmdinfo_t info)
    {
        api::parser_cmd p("dr", info);
        api::send_pipe_msg(p.get<int>(0), p.get<const char*>(1));
    });
}
