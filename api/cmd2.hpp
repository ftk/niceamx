#ifndef API_CMD2_HPP
#define API_CMD2_HPP

#include "config.h"
#include "util/utils.h"
#include "util/singleton.hpp"

#include <functional>
#include <map>
#include <string>
#include <cstdlib>

#include <boost/lexical_cast.hpp>

namespace api {
//

namespace cmdflag
{
    enum
    {
    	NUL = 0,
        SYSTEM = 1,
        CONFIG = 2,
        RCON = 4,
        // ...
        PLAYER = 256,
        LVL1 = 512,
        LVL2 = 1024,
        LVL3 = 2048,
        LVL4 = 4096,
        LVL5 = 8192,

        ADMIN = 16384,
        ALL = 0xffffffffU
    };
} //

typedef util::hash_t cmdhash_t;
inline cmdhash_t cmdhash(const std::string& name)
{
    return util::hash(name);
}

struct command_t
{
    // args: int pipe, const std::string& params
    typedef std::function<bool (int, const std::string&)> handler_t;
    //
    std::string name;
    unsigned flags;
    handler_t handler;
};

class commands2 : public util::singleton<commands2>
{
  // singleton

private:
  typedef std::multimap<cmdhash_t, command_t> commands_t;
  commands_t cmds;
public:

  inline void add(const command_t& cmd)
  {
      cmds.insert(std::make_pair(cmdhash(cmd.name), cmd));
  }

  bool execute_line(int pipe, unsigned flags, const std::string& line);
  
  bool proccess(int pipe, unsigned flags, const std::string& name, const std::string& params);
  
  // TODO:
  //void set_flags(const std::string& name, unsigned flags);
  //unsigned get_flags(const std::string& name);
  
};


class parser
{
private:
	char str[256];
	char * parts[32];
	char part_type[32];
	int num_parts;
public:
	bool error;
	
	parser() : num_parts(0), error(true) {}
	parser(const char * format, const std::string& params) : num_parts(0), error(true)
	{
		parse(format, params.c_str());
	}
	
	
	bool parse(const char * format, const char * params, std::size_t offset = 0u);
	
	inline int size()
	{
		return num_parts;
	}
	
	const char * get_string(int idx)
	{
		if(idx < 0 || idx >= num_parts)
			return "";
		return parts[idx];
	}
	int get_int(int idx)
	{
		if(idx < 0 || idx >= num_parts)
			return 0;
		return atoi(parts[idx]);
	}
	
	template <typename T>
	T get(int idx)
	{
		if(idx < 0 || idx >= num_parts)
			return T();
		return boost::lexical_cast<T>(parts[idx]);
	}
	
	//template <>
	long long int get_llong(int idx)
	{
		if(idx < 0 || idx >= num_parts)
			return 0;
		return atoll(parts[idx]);
	}
	double get_float(int idx)
	{
		if(idx < 0 || idx >= num_parts)
			return 0;
		return atof(parts[idx]);
	}
	
	char get_type(int idx)
	{
		if(idx < 0 || idx >= num_parts)
			return '\0';
		return part_type[idx];
	}
	

	
private:
	inline void add_part(char * p, char t)
	{
		if(num_parts < 32)
		{
			part_type[num_parts] = t;
			parts[num_parts++] = p;
		}
	}
};



} //

/* */
#define COMMANDBOX (api::commands2::get_instance())
#define REGISTER_COMMAND2(name,flags,...) ((COMMANDBOX)->add({name,flags,(__VA_ARGS__)}))

#define INVOKE_COMMANDS(pipe,flags,str) (COMMANDBOX->execute_line(pipe, flags, str))

#endif
