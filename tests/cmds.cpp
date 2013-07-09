#include "samp.h"

#include "api/cmd2.hpp"
#include "api/pipes.hpp"


#include <iostream>

static void init()
{
	REGISTER_COMMAND("test1", api::cmdflag::ALL, ([](api::cmdinfo_t info)
	{
		api::parser p("sd+", info);
		api::send_pipe_msg(info.caller, "start");
		for(int i = 0; i < p.size(); i++)
		{
			api::send_pipe_msg(info.caller, p[i]);
		}
	}));
	
	
	bool ok = INVOKE_COMMANDS(api::pipe::LOG, api::cmdflag::CONFIG, "  : \"echo tttt\" test1 t 1 2 3 4 5 6 7 8 9");
	
	api::send_pipe_msgf(api::pipe::STDOUT, "%d", ok);
	api::send_pipe_msg(api::pipe::STDOUT, "test {00FFFF} {FFFFFF}{000000}test");
	
	//pawn::log << "hello" << 0 << ' ' << "world\n!!!!!" << std::endl;
}

INIT { REGISTER_CALLBACK(plugin_load, init); }
