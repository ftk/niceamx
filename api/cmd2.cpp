#include "api/cmd2.hpp"
#include "api/pipes.hpp"
#include "signals.hpp"
#include "pawn/natives.h"

#include <string>

namespace api {



bool commands2::proccess(int pipe, unsigned flags, const std::string &name, const std::string &params)
{
	bool ok = false;
	auto iter_pair = cmds.equal_range(cmdhash(name));
    for(auto it = iter_pair.first; it != iter_pair.second; ++it)
    {
        if((flags & it->second.flags)/* == it->second->flags*/ && it->second.name == name)
        {
            ok = it->second.handler(pipe, params) || ok;
        }
    }
    
    return ok;
}

bool commands2::execute_line(int pipe, unsigned flags, const std::string &line)
{
	if(line.empty() || line[0] == '#')
		return true;
	
	std::size_t name_start = line.find_first_not_of(' ');
	
	if(line[name_start] == '#')
		return true;
	
	std::size_t name_end = line.find_first_of(' ');
	return proccess(pipe, flags, line.substr(name_start, name_end), line);
}

static void player_cmdhandler(int playerid, const std::string& cmdline)
{
	std::string cmd = cmdline.substr(1U); // /cmd
	
	// TODO: flags
	unsigned flags = cmdflag::PLAYER;
	if(native::is_player_admin(playerid))
		flags |= cmdflag::ADMIN;
	
	bool result = commands2::get_instance()->execute_line(playerid, flags, cmd);
	
	if(!result)
		send_pipe_msg(playerid, "Incorrect command!");
}

static void rcon_cmdhandler(const std::string& cmdline)
{
	// TODO: flags
	unsigned flags = cmdflag::RCON;
	
	int playerid = pipe::RCON;
	
	bool result = commands2::get_instance()->execute_line(playerid, flags, cmdline);
	
	if(!result)
		send_pipe_msg(playerid, "Incorrect command!");
}

static bool echo_cmd(int pipe, const std::string &params)
{
	parser p("*sr", params);
	send_pipe_msg(pipe, p.get_string(0));
	return true;
}

INIT
{
	REGISTER_CALLBACK(on_player_command_text, &player_cmdhandler);
	REGISTER_CALLBACK(on_rcon_command, &rcon_cmdhandler);
	REGISTER_COMMAND2("echo", cmdflag::ALL, &echo_cmd);
}

// parser

static char * str_skip_to_whitespace(char *str)
{
	while(*str && (*str != ' ' && *str != '\t' && *str != '\n'))
		str++;
	return str;
}
static char *str_skip_whitespaces(char *str)
{
	while(*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'))
		str++;
	return str;
}

bool parser::parse(const char * format, const char * params, size_t offset)
{
	strncpy(str, params + offset, sizeof(str) - 1);
	
	bool optional = false, 
		skip = false;
	
	error = false;
	
	char * pstr = str;
    num_parts = 0;

	while(true)
	{
		// fetch command
		char Command = *format;
		format++;

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

		pstr = str_skip_whitespaces(pstr);

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
			while(true)
			{
				if(pstr[0] == '"')
					break;
				else if(pstr[0] == '\\')
				{
					if(pstr[1] == '\\')
						pstr++; // skip due to escape
					else if(pstr[1] == '"')
						pstr++; // skip due to escape
				}
				else if(pstr[0] == 0)
					return false; // unescaped

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
			else if(Command == 'd' || Command == 'i') // validate int
				pstr = str_skip_to_whitespace(pstr);
			else if(Command == 'f') // validate float
				pstr = str_skip_to_whitespace(pstr);
			else if(Command == 's') // validate string
				pstr = str_skip_to_whitespace(pstr);
            else if(Command == 'p') // custom
                pstr = str_skip_to_whitespace(pstr);


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

}
