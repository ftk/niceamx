#ifndef API_PIPES_HPP
#define API_PIPES_HPP

#include "signal.hpp"

#include <string>

#include "util/config/attribute.h"

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
}

extern signals::signal<int, const std::string&> on_pipe_message;

void send_pipe_msg(int pipe, const std::string& msg);


void send_pipe_msgf(int pipe, const char * format, ...) __attribute__(( format(printf, 2, 3) ));


}

#endif

