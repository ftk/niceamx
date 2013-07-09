#ifndef API_PIPES_HPP
#define API_PIPES_HPP

#include "signal.hpp"

#include <string>
#include <list>

#include "util/config/attribute.h"

#include "util/streambuf.hpp"

namespace api {

namespace pipe
{
	enum
	{
		ALL = -1,
		LOG = -2,
		STDOUT = -3,
		STDERR = -4,
		SERVERLOG = -5,
		NUL = -6,
		FILE = -7, // forward responces to log
		// ...
		RCON = SERVERLOG // using pawn::logprint to answer rcon
	};

    enum
    {
        COLOR_BLACK = 0x000000,
        COLOR_RED = 0xFF0000,
        COLOR_GREEN = 0x00FF00,
        COLOR_BLUE = 0x0000FF,
        COLOR_WHITE = 0xFFFFFF
    };
}

extern signals::signal<int, const std::string&> on_pipe_message;

bool is_pipe_colored(int pipe);

void send_pipe_msg(int pipe, std::string msg);

void send_pipe_msgf(int pipe, const char * format, ...) __attribute__(( format(printf, 2, 3) ));

template <typename InputIterator>
void send_pipe_msg(InputIterator first, InputIterator last, const std::string& msg)
{
    while(first != last)
    {
        send_pipe_msg(*first, msg);
        ++first;
    }
}


class pipemsg_sink : public util::line_sink
{
    int pipe;
protected:
    void call()
    {
        send_pipe_msg(pipe, buffer);
    }
public:
    pipemsg_sink(int pipe) : pipe(pipe) {}
};


using pipestream = util::stream<pipemsg_sink>;

/* Using:
 * api::pipestream all(api::pipe::ALL);
 * all << "Hello all!" << std::endl;
 */


}

#endif

