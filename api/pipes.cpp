#include "api/pipes.hpp"

#include "api/playerpool.hpp"
#include "api/cmd2.hpp"

#include "pawn/natives.h"
#include "pawn/pawnlog.hpp"

#include "util/log.h"

#include "signals.hpp"


#include <cstdio>
#include <cstdarg>

namespace api {

signals::signal<int, const std::string&> on_pipe_message;

void send_pipe_msg(int pipe, const std::string& msg)
{
    on_pipe_message(pipe, msg);
}



void send_pipe_msgf(int pipe, const char * format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    buffer[len] = '\0';
    va_end(args);
    send_pipe_msg(pipe, buffer);
}



} //api


static void pipe_handler(int pipe, const std::string& msg)
{
    if(pipe >= 0 && pipe < native::MAX_PLAYERS)
    {
        native::send_client_message(pipe, 0xefefefff, msg);
        return;
    }

    using namespace api::pipe;
    //using namespace std;
    switch(pipe)
    {
        case STDOUT:
        fprintf(stdout, "%s\n", msg.c_str()); break;
        case STDERR:
        fprintf(stderr, "%s\n", msg.c_str()); break;
        case SERVERLOG:
        pawn::logprint(msg); break;
        case ALL:
        for(int id : *PLAYERBOX)
        {
            native::send_client_message(id, 0xffffffff, msg);
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
    REGISTER_COMMAND("send_to", RCON | ADMIN | CONFIG, [](int, const std::string& params)
    {
        api::parser p("*sdr", params);
        api::send_pipe_msg(p.get_int(0), p.get_string(1));
        return true;
    });
}
