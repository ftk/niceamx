#ifndef API_CMD_HPP
#define API_CMD_HPP

#include "config.h"
#include "util/utils.h"

#include "util/singleton.hpp"

#include <functional>
#include <vector>
#include <string>
#include <iterator>

#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

namespace api {
//

namespace detail
{
  struct cmd_name
  {
    util::hash_t hash;
    std::string name;
    
    cmd_name(const std::string& s) : name(s)
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
    //typedef bool (* handler_t) (int, std::string&);
    typedef std::function<bool (int, const std::string&)> handler_t;
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
    
    bool invoke(int playerid, const std::string& cmd) const
    {
      if(handler != NULL)
        return handler(playerid, cmd);
      return false;
    }
  };
  
}

class commands : public util::singleton<commands>
{
  // singleton
  
private:
  typedef std::vector<detail::command> cmds_t;
  cmds_t cmds;
public:
  /*
  inline void add(const detail::command& cmd)
  {
    cmds.push_back(cmd);
  }*/
  inline void add(detail::command cmd)
  {
    cmds.push_back(cmd);
  }
  
  bool proccess_raw(int, const std::string&);
  
};


class tokenizer : public boost::tokenizer<boost::char_separator<char> > 
{
public:
  tokenizer(const std::string& s) : boost::tokenizer<boost::char_separator<char> >(s.begin(), s.end(), boost::char_separator<char>(" "))
  {
  }
  
  template <typename Target = std::string>
  Target at(int pos)
  {
    auto it = begin();
    std::advance(it, pos);
    return boost::lexical_cast<Target>(*it);
  }
  
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
