#include "api/pipes.hpp"
#include "signals.hpp"
#include "api/playerpool.hpp"

#include "pawn/natives.h"
#include "pawn/pawnlog.hpp"

#include "util/log.h"

#include <cstdio>
#include <cstdarg>

namespace api {

signals::signal<int, const std::string&> on_pipe_message;

void send_pipe_msg(int pipe, const std::string& msg)
{
    on_pipe_message(pipe, msg);
}

static void pipe_handler(int pipe, const std::string& msg)
{
    if(pipe >= 0 && pipe < native::MAX_PLAYERS)
    {
        native::send_client_message(pipe, 0xffffffff, msg);
        return;
    }

    using namespace pipe;
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
		PLAYERBOX->for_each(([&msg](int id)
		{
			native::send_client_message(id, 0xffffffff, msg);
		})); break;

        case LOG:
        util::log_msg_nofmt("pipe/log", msg.c_str()); break;
        case FILE:
        util::log_msg_nofmt("pipe/file", msg.c_str()); break;
    }
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

INIT
{
    on_pipe_message.connect(&pipe_handler);
}

} //
