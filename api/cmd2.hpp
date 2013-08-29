#ifndef API_CMD2_HPP
#define API_CMD2_HPP

#include "config.h"
#include "util/utils.h"
#include "util/singleton.hpp"
#include "util/hash.hpp"

#include <functional>
#include <map>
#include <string>
#include <cstdlib>

#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/utility/string_ref.hpp>


namespace api {
//

namespace cmdflag
{
    enum : unsigned int
    {
        NUL = 0,
        SYSTEM = 1,
        CONFIG = 2,
        RCON = 4,
        HIDDEN = 8,
        // ...
        PLAYER = 256,
        LVL1 = 512,
        LVL2 = 1024,
        LVL3 = 2048,
        LVL4 = 4096,
        LVL5 = 8192,

        ADMIN = 16384,
        ALL = 0xffffffffu & ~HIDDEN
    };
} //

namespace cmderr
{
class cmderr {};
class not_found : cmderr {};
class request_denied : cmderr {};
class syntax_error : cmderr {};
}

typedef util::hash_t cmdhash_t;
inline cmdhash_t cmdhash(const std::string& name)
{
    return util::hash_rt_nocase(name.c_str());
}


class commands;

struct cmdinfo_t
{
    const int caller;
    const std::string& line;
    const std::string& name;
    //boost::string_ref line;
    //boost::string_ref name;
    const unsigned flags;
    const std::size_t params_offset;
    const cmdhash_t name_hash;
    // ...
    //bool result = true;

private:
    explicit cmdinfo_t(int caller, const std::string& name, const std::string& line, unsigned flags,
              std::size_t params_offset, cmdhash_t name_hash) :
        caller(caller), line(line), name(name), flags(flags), params_offset(params_offset),
        name_hash(name_hash) {}
    friend class commands;
};

struct command_t
{
    // args: int pipe, const std::string& params
    typedef std::function<bool (int, const std::string&)> handler_t;
    // args: cmdinfo_t info
    typedef std::function<void (cmdinfo_t info)> handler2_t;
    //
    std::string name;
    unsigned flags;
    //handler_t handler;
    handler2_t handler2;

    /*
    command_t(std::string name, unsigned flags, handler_t&& hnd) : name(std::move(name)),
        flags(flags), handler(std::move(hnd)), handler2() {}*/
    command_t(std::string name, unsigned flags, handler2_t hnd) : name(std::move(name)),
          flags(flags), handler2(std::move(hnd)) {}
};



class commands : public util::singleton<commands>
{
  // singleton

private:
//public:
  typedef std::multimap<cmdhash_t, command_t> commands_t;
  commands_t cmds;
public:

  inline void add(command_t&& cmd)
  {
      cmds.insert(std::make_pair(cmdhash(cmd.name), std::move(cmd)));
  }
  inline void add(cmdhash_t hash, command_t&& cmd)
  {
      cmds.insert(std::make_pair(hash, std::move(cmd)));
      //cmds.emplace(hash, cmd);
  }

  template <typename... Args>
  inline void emplace(Args&&... args)
  {
      cmds.emplace(std::forward<Args>(args)...);
  }

  bool execute_line(int pipe, unsigned flags, const std::string &line);
  
  //bool process(int pipe, unsigned flags, const std::string& name, const std::string& params);
  bool process(cmdinfo_t cmdinfo);

  void set_flags(const std::string& name, unsigned flags);
  unsigned get_flags(const std::string& name);

  std::size_t count(const std::string& name)
  {
      //auto iter_pair = cmds.equal_range(cmdhash(name));
      //return std::distance(iter_pair.first, iter_pair.second);
      return cmds.count(cmdhash(name));
  }

  //iterator
public:
  typedef commands_t::const_iterator iterator;
  typedef commands_t::const_iterator const_iterator;
  const_iterator begin() const { return cmds.begin(); }
  const_iterator end() const { return cmds.end(); }

  std::pair<const_iterator, const_iterator> find(const std::string& name) const
  {
      return cmds.equal_range(cmdhash(name));
  }
  
};

// move to util?
template <typename Target>
struct convert_from_cstring
{
    static Target apply(const char * str, char /*context*/)
    {
        return boost::lexical_cast<Target>(str); // generic
    }
};
// partial
template <>
struct convert_from_cstring<int>
{
    static int apply(const char * str, char context)
    {
        switch(context)
        {
        case 'd':
            return ::strtol(str, NULL, 10);
        case 'x':
        case 'X':
            return ::strtol(str, NULL, 16);
        }
        return ::strtol(str, NULL, 0);
    }
};
template <>
struct convert_from_cstring<long long>
{
    static long long apply(const char * str, char context)
    {
        switch(context)
        {
        case 'd':
            return ::strtoll(str, NULL, 10);
        case 'x':
        case 'X':
            return ::strtoll(str, NULL, 16);
        }
        return ::strtoll(str, NULL, 0);
    }
};
template <>
struct convert_from_cstring<const char *>
{
    static const char * apply(const char * str, char /*context*/)
    {
        return str;
    }
};
template <>
struct convert_from_cstring<std::string>
{
    static std::string apply(const char * str, char /*context*/)
    {
        return std::string(str);
    }
};
template <>
struct convert_from_cstring<float>
{
    static float apply(const char * str, char /*context*/)
    {
        return ::strtof(str, NULL);
    }
};
template <>
struct convert_from_cstring<double>
{
    static double apply(const char * str, char /*context*/)
    {
        return ::strtod(str, NULL);
    }
};
template <>
struct convert_from_cstring<long double>
{
    static double apply(const char * str, char /*context*/)
    {
        return ::strtold(str, NULL);
    }
};
template <>
struct convert_from_cstring<boost::string_ref>
{
    static boost::string_ref apply(const char * str, char /*context*/)
    {
        return boost::string_ref(str);
    }
};
// commands parser
class parser
{
protected:
    enum
    {
        MAX_PARTS = 32,
        MAX_STRING = 256
    };
    char str[MAX_STRING];
    char * parts[MAX_PARTS];
    char part_type[MAX_PARTS];
    std::size_t num_parts = 0;
public:

    class wrong_index : public std::exception { const char * what() { return "parser: wrong index accessed"; } };


    bool error = true;
	
    parser() {}
    parser(const char * format, const std::string& params)
	{
		parse(format, params.c_str());
	}
    parser(const char * format, const cmdinfo_t& cmdinfo)
    {
        parse(format, cmdinfo.line.c_str(), cmdinfo.params_offset);
    }

    bool parse(const char * format, const char * params, std::size_t offset = 0u)
    {
        util::strncpy(str, params + offset);
        return parse(format, str);
    }

    bool parse(const char * format, char * str);
	
    inline std::size_t size() const
	{
		return num_parts;
	}
    inline bool empty() const
    {
        return size() == 0;
    }

    // get
	
    template <typename T>
    T get(int idx) const
    {
        if(static_cast<unsigned>(idx) >= num_parts)
            throw wrong_index();
        return convert_from_cstring<T>::apply(parts[idx], part_type[idx]);
    }
    template <typename T>
    T get(int idx, T def) const
    {
        if(static_cast<unsigned>(idx) >= num_parts)
            return std::move(def);
        return convert_from_cstring<T>::apply(parts[idx], part_type[idx]);
    }

    template <typename T>
    boost::optional<T> get_optional(int idx) const
    {
        if(static_cast<unsigned>(idx) >= num_parts)
            return boost::optional<T>();
        return boost::optional<T>(convert_from_cstring<T>::apply(parts[idx], part_type[idx]));
    }
    // deprecated

    const char * get_string(int idx) const
	{
        return get<const char *>(idx);
	}
/*
    int get_int(int idx) const
	{
        return get<int>(idx);
	}
    int get_int_or(int idx, int def) const
    {
        return get(idx, def);
    }
    long long int get_llong(int idx) const
	{
        return get<long long int>(idx);
    }
    float get_float(int idx) const
	{
        return get<float>(idx);
	}
    float get_float_or(int idx, float def) const
    {
        return get(idx, def);
    }
*/
    //
    char get_type(int idx) const
	{
        if(static_cast<unsigned>(idx) >= num_parts)
			return '\0';
		return part_type[idx];
	}
	
    char * operator[] (int idx)
    {
        if(static_cast<unsigned>(idx) < num_parts)
            return parts[idx];
        return NULL;
    }

	
protected:
	inline void add_part(char * p, char t)
	{
        if(num_parts < MAX_PARTS)
		{
			part_type[num_parts] = t;
			parts[num_parts++] = p;
		}
	}
public:

    typedef char * const * iterator;
    typedef const char * const * const_iterator;

    iterator begin() { return parts; }
    iterator end() { return parts + num_parts; }
    const_iterator begin() const { return parts; }
    const_iterator end() const { return parts + num_parts; }

};

class parser_cmd : public parser
{
public:
    parser_cmd(const char * format, const cmdinfo_t& cmdinfo);
};



} //api


/* */
#define COMMANDBOX (api::commands::get_instance())
//#define REGISTER_COMMAND2(name,flags,...) ((COMMANDBOX)->add(util::const_test<util::const_hash_nocase(name)>::value, api::command_t(name,flags,api::command_t::handler_t(__VA_ARGS__))))
#define REGISTER_COMMAND(name,flags,...) ((COMMANDBOX)->add(util::const_test<util::const_hash_nocase(name)>::value, api::command_t(name,flags,api::command_t::handler2_t(__VA_ARGS__))))

#define REGISTER_COMMAND_RT(name,flags,...) ((COMMANDBOX)->add(api::command_t(name,flags,(__VA_ARGS__))))

#define INVOKE_COMMANDS(pipe,flags,str) (COMMANDBOX->execute_line(pipe, flags, str))


#endif
