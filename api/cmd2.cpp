#include "api/cmd2.hpp"
#include "api/pipes.hpp"
#include "signals.hpp"
#include "pawn/natives.h"

#include "util/log.h"
#include "util/utils.h"

#include <string>
#include <fstream>
#include <cassert>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/utility/string_ref.hpp>

namespace api {


/*
bool commands::process(int pipe, unsigned flags, const std::string &name, const std::string &params)
{
	bool ok = false;
	auto iter_pair = cmds.equal_range(cmdhash(name));
    for(auto it = iter_pair.first; it != iter_pair.second; ++it)
    {
        if((flags & it->second.flags))
        {
        	// TODO: check collisions
            ok = (it->second.handler && it->second.handler(pipe, params)) || ok;
        }
    }
    
    return ok;
}
*/

bool commands::process(cmdinfo_t cmdinfo)
{
    bool ok = false;
    auto iter_pair = cmds.equal_range(cmdinfo.name_hash);
    for(auto it = iter_pair.first; it != iter_pair.second; ++it)
    {
        if((cmdinfo.flags & it->second.flags)/* == it->second.flags && it->second.name == name*/)
        {
            if(/*it->second.handler2 &&*/ boost::algorithm::iequals(cmdinfo.name, it->second.name))
            {
                ok = true;
                try
                {
                    it->second.handler2(cmdinfo);
                }
                catch(cmderr::not_found)
                {
                    ok = false;
                }
                catch(cmderr::cmderr)
                {
                }
            }
        }
    }

    return ok;

}

bool commands::execute_line(int pipe, unsigned flags, const std::string& line)
{
	if(line.empty())
		return true;
	
	std::size_t name_start = line.find_first_not_of(" \t");
	
	if(line[name_start] == '#')
		return true;
	
    std::size_t name_end = line.find_first_of(" \t", name_start+1);
    std::size_t params_start = line.find_first_not_of(" \t", name_end+1);
    if(params_start == std::string::npos)
    	params_start = line.size();

    //util::log_debug("cmd2/invoke", "%s / %s", line.substr(name_start, name_end - name_start).c_str(), line.c_str());
    std::string name = line.substr(name_start, name_end - name_start);

    cmdinfo_t cmdinfo(pipe, name, line, flags, params_start, cmdhash(name));
    bool found = process(std::move(cmdinfo)); // new
    //found = process(pipe, flags, name, line) || found; // old
    return found;
}

void commands::set_flags(const std::string& name, unsigned flags)
{
    auto iter_pair = cmds.equal_range(cmdhash(name));
    for(auto it = iter_pair.first; it != iter_pair.second; ++it)
    {
        it->second.flags = flags;
    }
}

unsigned commands::get_flags(const std::string& name)
{
    auto iter_pair = cmds.equal_range(cmdhash(name));
    for(auto it = iter_pair.first; it != iter_pair.second; ++it)
    {
        return it->second.flags;
    }
    return cmdflag::NUL;
}

// slots
static void player_cmdhandler(int playerid, const std::string& cmdline)
{
    std::string cmd = cmdline.substr(1U); // /cmd -> cmd
	
	// TODO: flags
	unsigned flags = cmdflag::PLAYER;
	if(native::is_player_admin(playerid))
		flags |= cmdflag::ADMIN;

    try
    {
        bool result = INVOKE_COMMANDS(playerid, flags, cmd);

        if(!result)
            send_pipe_msg(playerid, "Incorrect command!");
    }
    catch(std::exception& e)
    {
        util::log_msg("cmd/handler", "exception {%s} on [%d] %s", e.what(), playerid, cmdline.c_str());
        api::send_pipe_msgf(playerid, "Exception: %s", e.what());
    }
}

static void rcon_cmdhandler(const std::string& cmdline)
{
	// TODO: flags
	unsigned flags = cmdflag::RCON;
	
    const int playerid = pipe::RCON;
	
    try
    {
        bool result = INVOKE_COMMANDS(playerid, flags, cmdline);

        if(!result)
            send_pipe_msg(playerid, "Incorrect command!");
    }
    catch(std::exception& e)
    {
        util::log_msg("cmd/rconhandler", "exception {%s} on %s", e.what(), cmdline.c_str());
        api::send_pipe_msgf(playerid, "Exception: %s", e.what());
    }
}

// cmds

static void echo_cmd(cmdinfo_t info)
{
    parser_cmd p("?r", info);
    send_pipe_msg(info.caller, p.get(0, ""));
}

static void execute_file(cmdinfo_t info)
{
    parser_cmd p("r", info);
    std::ifstream in(p.get<const char *>(0));
	if(!in)
	{
        send_pipe_msgf(info.caller, "Cannot open file: %s",p.get<const char *>(0));
        return;
	}
	
	std::string str;
    int line = 1;
	while(!in.eof())
	{
		std::getline(in, str);
        bool ok = INVOKE_COMMANDS(info.caller, info.flags, str);
		if(!ok)
            send_pipe_msgf(info.caller, "Cannot execute(%d): %s", line, str.c_str());
        line++;
	}

}

static void execute_rcon(cmdinfo_t info)
{
    parser_cmd p("r", info);
    native::send_rcon_command(p.get<const char *>(0));
}

static void modify_cmdflags(cmdinfo_t info)
{
    parser_cmd p("s?d", info);
    auto cmdname = p.get<const char *>(0);
    unsigned flags = p.get(1, 0);

    if(info.name == "cmdflags_add")
    {
        flags |= COMMANDBOX->get_flags(cmdname);
    }
    else if(info.name == "cmdflags_rm")
    {
        flags = COMMANDBOX->get_flags(cmdname) & (~flags);
    }

    if(info.name == "cmdflags_get")
    {
        // get
        flags = COMMANDBOX->get_flags(cmdname);
    }
    else
    {
        // set
        COMMANDBOX->set_flags(cmdname, flags);
    }
    api::send_pipe_msgf(info.caller, "Flags %s %u", cmdname, flags);
}

INIT
{
	REGISTER_CALLBACK(on_player_command_text, &player_cmdhandler);
	REGISTER_CALLBACK(on_rcon_command, &rcon_cmdhandler);
    REGISTER_COMMAND("echo", cmdflag::ALL, &echo_cmd);
    REGISTER_COMMAND("echocmd", cmdflag::ALL, ([](cmdinfo_t info)
    {
        send_pipe_msg(info.caller, info.line);
    }));

    const unsigned int ADM = cmdflag::CONFIG | cmdflag::ADMIN | cmdflag::RCON;

    REGISTER_COMMAND("execrcon", cmdflag::CONFIG | cmdflag::ADMIN, &execute_rcon);
    REGISTER_COMMAND("execfile", ADM, &execute_file);
    REGISTER_COMMAND("cmdflags_add", ADM, &modify_cmdflags);
    REGISTER_COMMAND("cmdflags_rm", ADM, &modify_cmdflags);
    REGISTER_COMMAND("cmdflags_get", ADM, &modify_cmdflags);
    REGISTER_COMMAND("cmdflags_set", ADM, &modify_cmdflags);

    REGISTER_COMMAND("execcmd", ADM, ([](cmdinfo_t info)
    {
        parser_cmd p("ddr", info);
        INVOKE_COMMANDS(p.get<int>(0), p.get<int>(1), p.get<const char *>(2));
    }));

    // exec 2 commands
    REGISTER_COMMAND(":", cmdflag::ALL, ([](cmdinfo_t info)
    {
        parser p("sr", info);
        INVOKE_COMMANDS(info.caller, info.flags, p.get<const char *>(0));
        INVOKE_COMMANDS(info.caller, info.flags, p.get<const char *>(1));
    }));
    // AND
    REGISTER_COMMAND("&&", cmdflag::ALL, ([](cmdinfo_t info)
    {
        parser p("sr", info);
        if(INVOKE_COMMANDS(info.caller, info.flags, p.get<const char *>(0)))
            INVOKE_COMMANDS(info.caller, info.flags, p.get<const char *>(1));
    }));
    // OR
    REGISTER_COMMAND("||", cmdflag::ALL, ([](cmdinfo_t info)
    {
        parser p("sr", info);
        if(!INVOKE_COMMANDS(info.caller, info.flags, p.get<const char *>(0)))
            INVOKE_COMMANDS(info.caller, info.flags, p.get<const char *>(1));
    }));

}

// parser


bool parser::parse(const char * format, char * str)
{
	bool optional = false, 
		skip = false;
	
	error = false;
	
	char * pstr = str;
    num_parts = 0;

	while(true)
	{
		// fetch command
		char Command = *format;
        if(Command != '+')
            format++;
        else
        {
            Command = *(format-1);
            assert(Command != '?'); // endless loop
            assert(Command != '*'); // endless loop
        }

		if(!Command)
			break;

		if(Command == '?')
		{
			optional = true;
			continue;
		}
		else if(Command == '*')
		{
			skip = true;
			continue;
		}

        pstr = util::str_skip_whitespaces(pstr);

		if(!(*pstr)) // error, non optional command needs value
		{
			if(!optional)
				error = true;
			break;
		}

		// add token
		if(*pstr == '"')
		{
			char *pdst;
			pstr++;
			if(!skip)
                add_part(pstr, Command);

			pdst = pstr; // we might have to process escape data
            while(pstr[0] != '"')
			{
                if(pstr[0] == '\\')
				{
					if(pstr[1] == '\\')
						pstr++; // skip due to escape
					else if(pstr[1] == '"')
						pstr++; // skip due to escape
				}
                else if(!pstr[0])
                {
                    error = true;
					return false; // unescaped
                }

				*pdst = *pstr;
				pdst++;
				pstr++;
			}

			// write null termination
			*pdst = '\0';


			pstr++;
		}
		else
		{
			if(!skip)
                add_part(pstr, Command);

			if(Command == 'r') // rest of the string
                break;
            else if(Command == 'c') // char
                ++pstr;
            else if(Command != '&') // skip
                pstr = util::str_skip_to_whitespace(pstr);


			if(pstr[0] != '\0') // check for end of string
			{
				pstr[0] = '\0';
				pstr++;
			}
		}
		skip = false;
	}
	return !error;
}

parser_cmd::parser_cmd(const char *format, const cmdinfo_t &cmdinfo)
{
    if(strcmp(cmdinfo.line.c_str()+cmdinfo.params_offset, "help") == 0)
    {
        // help
        send_pipe_msgf(cmdinfo.caller, "{FFFF00}Usage: %s %s", cmdinfo.name.c_str(), format);
        throw cmderr::cmderr();
    }
    parse(format, cmdinfo.line.c_str(), cmdinfo.params_offset);
    if(error)
    {
        send_pipe_msgf(cmdinfo.caller, "{FF0000}Syntax error{FFFFFF}: %s %s", cmdinfo.name.c_str(), format);
        throw cmderr::syntax_error();
    }
}

} // api
