#include "cmd.hpp"
#include "util/utils.h"
#include "util/notify.h"

#include <string>

#include <cassert>

namespace api {
//

static void split(util::strings& buffer, const std::string& raw, char separator = ' ')
{
    std::size_t startpos = 0, endpos;

    endpos = raw.find_first_of(separator, 0);
    if(endpos == std::string::npos)
    {
      buffer.push_back(raw);
      return;
    }
    while(endpos != std::string::npos)
    {
        buffer.push_back(raw.substr(startpos, endpos - startpos)); // add to vector
        startpos = endpos+1; //jump past sep
        endpos = raw.find_first_of(separator, startpos); // find next
        if(endpos == std::string::npos)
        {
            //lastone, so no 2nd param required to go to end of string
            buffer.push_back(raw.substr(startpos));
        }
    }
}

commands * commands::instance = NULL;

commands * commands::get_instance()
{
  if(instance == NULL)
    instance = new commands;
  return instance;
}
void commands::rm_instance()
{
  if(instance != NULL)
  {
    delete instance;
    instance = NULL;
  }
}

bool commands::proccess_raw(int playerid, const std::string& rawstr)
{
  // TODO: check if player is invalid
  if(rawstr.empty())
    return false;
  
  assert(rawstr.at(0) == '/');
  
  util::strings args;
  split(args, rawstr);
  assert(args.size() >= 1);
  
  std::string & name(args.at(0)); // name: "/name param param"
  
  assert(name.at(0) == '/');
  name.erase(0, 1); // remove the '/'
  
  util::hash_t hash = util::hash(name);
  
  //typedef cmds_t::const_iterator iterator1;
  for(auto it1 = cmds.cbegin(), en1 = cmds.cend(); it1 != en1; ++it1)
  {
    // loop thru command names
    //typedef detail::cmd_names::const_iterator iterator2;
    for(auto it2 = it1->names.cbegin(), en2 = it1->names.cend(); it2 != en2; ++it2)
    {
      if(hash == it2->hash)
      {
	// we have found the command
	return it1->invoke(playerid, args);
      }
    }
  }
  
   return false; // no such command
}


}
