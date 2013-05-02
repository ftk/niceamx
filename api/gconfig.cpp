#include "api/gconfig.hpp"
#include "api/cmd2.hpp"
#include "api/pipes.hpp"

#include "signals.hpp"
#include "pawn/natives.h"

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
	parser p("*ss?r", params);
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
static bool gconfig_server(int pipe, const std::string& params)
{
	/*
	char paramname[128], val[128];
	val[0] = '\0';
	sscanf(params.c_str(), "%*s %s %s", paramname, val);
	*/
	
    const char * paramname, * servervar;
    parser p("*sss", params);
	paramname = p.get_string(0);
    servervar = p.get_string(1);

    auto val = native::get_server_var_as_string(servervar);

    CONFIGBOX->set(paramname, val);
    send_pipe_msgf(pipe, "%s = %s", paramname, val.c_str());
	return true;
}


static bool gconfig_unset(int /*pipe*/, const std::string& params)
{
	const char * paramname;
	parser p("*sr", params);
	if(p.error)
		return false;
	paramname = p.get_string(0);
	
	if(CONFIGBOX->exists(paramname))
	{
		CONFIGBOX->unset(paramname);
	}
	
	return true;
}

static bool gconfig_ifeq(int pipe, const std::string& params)
{
	parser p("sssr", params);
	if(p.error)
		return false;
	
	const char * lval, * rval, * cmdname;
	
	cmdname = p.get_string(0);
	lval = p.get_string(1);
	rval = p.get_string(2);
	
	bool inverse = !strcmp(cmdname, "ifneq"); // ifeq - if equal, ifneq - if not equal
	
	if(CONFIGBOX->exists(lval))
	{
		if((CONFIGBOX->get(lval) == rval) ^ inverse)
			INVOKE_COMMANDS(pipe, cmdflag::CONFIG, p.get_string(3));
	}
	else if(inverse)
	{
		INVOKE_COMMANDS(pipe, cmdflag::CONFIG, p.get_string(3));
	}
	else
	{
		//send_pipe_msgf(pipe, "No such param: %s", paramname);
	}
	
	return true;
}

static bool gconfig_ifdef(int pipe, const std::string& params)
{
	parser p("ssr", params);
	if(p.error)
		return false;
	
	const char * param, * cmdname;
	
	cmdname = p.get_string(0);
	param = p.get_string(1);
	
	bool inverse = !strcmp(cmdname, "ifndef"); // ifdef - if defined, ifndef - if not defined
	
	if(CONFIGBOX->exists(param) ^ inverse)
	{
		INVOKE_COMMANDS(pipe, cmdflag::CONFIG, p.get_string(2));
	}
	
	return true;
}

INIT
{
    REGISTER_COMMAND("gconfig", cmdflag::CONFIG | cmdflag::ADMIN | cmdflag::RCON, &gconfig_cmd);
    REGISTER_COMMAND("gconfig_server", cmdflag::CONFIG | cmdflag::ADMIN | cmdflag::RCON, &gconfig_server);
    REGISTER_COMMAND("gconfig_unset", cmdflag::CONFIG | cmdflag::ADMIN | cmdflag::RCON, &gconfig_unset);
    REGISTER_COMMAND("ifeq", cmdflag::CONFIG, &gconfig_ifeq);
    REGISTER_COMMAND("ifneq", cmdflag::CONFIG, &gconfig_ifeq);
    REGISTER_COMMAND("ifdef", cmdflag::CONFIG, &gconfig_ifdef);
    REGISTER_COMMAND("ifndef", cmdflag::CONFIG, &gconfig_ifdef);
}


} //

