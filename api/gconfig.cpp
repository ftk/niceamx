#include "api/gconfig.hpp"
#include "api/cmd2.hpp"
#include "api/pipes.hpp"

#include "signals.hpp"

#include <cstdio>
#include <cassert>

namespace api {

static bool gconfig_cmd(int pipe, const std::string& params)
{
	/*
	char paramname[128], val[128];
	val[0] = '\0';
	sscanf(params.c_str(), "%*s %s %s", paramname, val);
	*/
	
	const char * paramname, * val;
	parser p("*ssr", params);
	paramname = p.get_string(0);
	val = p.get_string(1);
	
	if(val[0])
	{
		CONFIGBOX->set(paramname, val);
		send_pipe_msgf(pipe, "%s = %s", paramname, val);
	}
	else if(CONFIGBOX->exists(paramname))
	{
		send_pipe_msgf(pipe, "%s = %s", paramname, CONFIGBOX->get(paramname).c_str());
	}
	else
		send_pipe_msgf(pipe, "no such param %s", paramname);
	
	
	return true;
}

INIT
{
	REGISTER_COMMAND2("gconfig", cmdflag::CONFIG | cmdflag::ADMIN | cmdflag::RCON, &gconfig_cmd);
}


} //

