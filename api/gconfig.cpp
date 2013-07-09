#include "api/gconfig.hpp"
#include "api/cmd2.hpp"
#include "api/pipes.hpp"

#include "signals.hpp"
#include "pawn/natives.h"

#include <cstdio>
#include <cassert>

namespace api {

static void gconfig_cmd(api::cmdinfo_t info)
{
	/*
	char paramname[128], val[128];
	val[0] = '\0';
	sscanf(params.c_str(), "%*s %s %s", paramname, val);
	*/
	
	const char * paramname, * val;
    parser_cmd p("s?r", info);
	paramname = p.get_string(0);
	val = p.get_string(1);
	
	if(val[0])
	{
		CONFIGBOX->set(paramname, val);
        send_pipe_msgf(info.caller, "%s = %s", paramname, val);
	}
	else if(CONFIGBOX->exists(paramname))
	{
        send_pipe_msgf(info.caller, "%s = %s", paramname, CONFIGBOX->get(paramname).c_str());
	}
	else
        send_pipe_msgf(info.caller, "no such param %s", paramname);
}
static void gconfig_server(api::cmdinfo_t info)
{
	/*
	char paramname[128], val[128];
	val[0] = '\0';
	sscanf(params.c_str(), "%*s %s %s", paramname, val);
	*/
	
    const char * paramname, * servervar;
    parser p("ss", info);
	paramname = p.get_string(0);
    servervar = p.get_string(1);

    auto val = native::get_server_var_as_string(servervar);

    CONFIGBOX->set(paramname, val);
    send_pipe_msgf(info.caller, "%s = %s", paramname, val.c_str());
}


static void gconfig_unset(api::cmdinfo_t info)
{
    parser_cmd p("r", info);
    auto paramname = p.get_string(0);
	
	if(CONFIGBOX->exists(paramname))
	{
		CONFIGBOX->unset(paramname);
	}
}

static void gconfig_ifeq(api::cmdinfo_t info)
{
    parser_cmd p("ssr", info);
	
    const char * lval, * rval;
	
    lval = p.get_string(0);
    rval = p.get_string(1);
	
    bool inverse = info.name == "ifneq"; // ifeq - if equal, ifneq - if not equal
	
	if(CONFIGBOX->exists(lval))
	{
		if((CONFIGBOX->get(lval) == rval) ^ inverse)
            INVOKE_COMMANDS(info.caller, info.flags, p.get_string(2));
	}
	else if(inverse)
	{
        INVOKE_COMMANDS(info.caller, info.flags, p.get_string(2));
	}
	else
	{
		//send_pipe_msgf(pipe, "No such param: %s", paramname);
	}
}

static void gconfig_ifdef(api::cmdinfo_t info)
{
    parser_cmd p("sr", info);
	
    const char * param;
	
    param = p.get_string(0);
	
    bool inverse = info.name == "ifndef"; // ifdef - if defined, ifndef - if not defined
	
	if(CONFIGBOX->exists(param) ^ inverse)
	{
        INVOKE_COMMANDS(info.caller, info.flags, p.get_string(1));
    }
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

    REGISTER_COMMAND("gconfig_xargs", cmdflag::CONFIG | cmdflag::ADMIN | cmdflag::RCON, [](api::cmdinfo_t info)
    {
        api::parser_cmd p("s?s+", info);
        std::string cmdline;

        for(std::size_t i = 0; i < p.size(); i++)
        {
            if(i) cmdline += ' ';
            auto arg = p.get_string(i);
            if(*arg == '$')
            {
                // substitute
                cmdline += CONFIGBOX->get(arg+1); // omit $
            }
            else
            {
                cmdline += arg;
            }
        }
        INVOKE_COMMANDS(info.caller, info.flags, cmdline);
    });
    /* Usage:
     *  gconfig var1 123
     *  gconfig var2 456
     *  gconfig_xargs echo $var1 $var2
     * 123 456
     */
}


} //

