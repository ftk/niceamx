#ifndef API_CMD_HPP
#define API_CMD_HPP

#include "config.h"
#include "util/utils.h"

#include "util/strings.h"

#include <functional>

namespace api {
//

namespace detail
{
  struct cmd_name
  {
    util::hash_t hash;
    std::string name;
    
    cmd_name(std::string s) : name(s)
    {
      hash = util::hash(s);
    }
    
    cmd_name(const char * s) : name(s)
    {
      hash = util::hash(s);
    }
    
  };
  inline bool operator < (const cmd_name & l, const cmd_name & r)
  {
    return(l.hash < r.hash);
  }
  inline bool operator == (const cmd_name & l, const cmd_name & r)
  {
    return(l.hash == r.hash);
  }
  
  
  typedef std::vector<cmd_name> cmd_names;
  
  struct command
  {
    //typedef bool (* handler_t) (int, util::strings&);
    typedef std::function<bool (int, util::strings&)> handler_t;
    cmd_names names;
    
    handler_t handler;
    
    command(handler_t func = NULL) : handler(func)
    {}
    command(std::string cmd, handler_t func = NULL) : handler(func)
    {
      add(cmd);
    }
    
    void add(const std::string& cmdname)
    {
      names.push_back(cmdname);
    }

    command& operator()(const std::string& cmdname)
    {
      add(cmdname);
      return(*this);
    }
    
    bool invoke(int playerid, util::strings& args) const
    {
      if(handler != NULL)
	return handler(playerid, args);
      return false;
    }
  };
  
}



class commands
{
  // singleton
private:
  commands() {}
  static commands * instance;
public:
  static commands * get_instance();
  static void rm_instance();
  
private:
  typedef std::vector<detail::command> cmds_t;
  cmds_t cmds;
public:
  /*
  inline void add(const detail::command& cmd)
  {
    cmds.push_back(cmd);
  }*/
  inline void add(const detail::command& cmd)
  {
    cmds.push_back(cmd);
  }
  
  bool proccess_raw(int, const std::string&);
  
};



/*

namespace detail
{
  
  struct cmd_param
  {
    std::string desc;
    
    enum param_type
    {
      int_type = 1,
      float_type,
      string_type,
      bool_type
    } type;
    
  };
  typedef std::list<cmd_param> cmd_params;
  
  struct command
  {
    cmd_names names;
    cmd_params params;
    
    //box::basic_container_t handlers;
  };
  
} // detail


*/


} // api


#define COMMANDBOX (api::commands::get_instance())

//#define MAKE_COMMAND(name,fn) (api::detail::command(name, fn))
#define MAKE_COMMAND(...) (api::detail::command(__VA_ARGS__))

#define REGISTER_COMMAND2(cmd) COMMANDBOX->add(cmd)
//#define REGISTER_COMMAND(name,fn) REGISTER_COMMAND2(MAKE_COMMAND(name, fn))
#define REGISTER_COMMAND(name,...) REGISTER_COMMAND2(MAKE_COMMAND(name, __VA_ARGS__))

#define INVOKE_COMMANDS(id,str) COMMANDBOX->proccess_raw(id, str)

#endif
