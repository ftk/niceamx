#ifndef API_PLAYERPOOL_HPP
#define API_PLAYERPOOL_HPP

#include "config.h"
#include <set>
#include <map>
#include <algorithm>

#include "util/utils.h"
#include "util/singleton.hpp"

namespace api {
//

class active_players
{
private:
  typedef std::map<int, util::walltime_t> playertimes_t;
  playertimes_t ptime;

  const int timeout; // time player not updating so he is not active
public:

  explicit active_players(int timeout_ = 2) : timeout(timeout_) {}

  // internal
  inline void update(int id)
  {
    ptime[id] = util::get_walltime_s() + timeout;
  }
public:
  //
  inline bool is_active(int id)
  {
    auto it = ptime.find(id);
    if(it == ptime.end())
      return false; // not found
    return check_active(it);
  }

  template <typename T>
  void for_each(T fn)
  {
    util::walltime_t wt = util::get_walltime_s();
    for(auto it = ptime.begin(), en = ptime.end(); it != en; ++it)
    {
      if(check_active(it, wt))
      {
	fn(it->first);
      }
      else
      {
	en = ptime.end();
	if(it == en)
	  return;
      }
    }
  }

private:
  inline bool check_active(playertimes_t::iterator it)
  {
    if(it->second < util::get_walltime_s())
    { // not updating
      ptime.erase(it);
      return false;
    }
    return true; // player is active
  }
  
  inline bool check_active(playertimes_t::iterator& it, util::walltime_t t)
  {
    if(it->second < t)
    { // not updating
      it = ptime.erase(it);
      return false;
    }
    return true; // player is active
  }
};

// ----------------
class players : public util::singleton<players>
{
  // singleton
private:
  typedef std::set<int> playerids_t;
  typedef playerids_t::iterator player_iter_t;
  playerids_t playerids;

  active_players active;
  
public:
  
  inline bool is_connected(int playerid) const
  {
    player_iter_t it = playerids.find(playerid);
    return(it != playerids.end());
  }
  
  inline std::size_t count() const
  {
    return(playerids.size());
  }
  inline std::size_t size() const
  {
    return count();
  }
  
  template <typename T>
  inline void for_each(T func) const
  {
    if(!playerids.empty())
      std::for_each(playerids.begin(), playerids.end(), func);
  }
  
  inline playerids_t& get()
  {
    return playerids;
  }
  inline const playerids_t& get() const
  {
    return playerids;
  }
  
  // internal
  inline void add(int playerid)
  {
    playerids.insert(playerid);
  }
  inline void remove(int playerid)
  {
    playerids.erase(playerid);
  }

  active_players * get_active()
  {
    return &active;
  }
  
};


}

#define PLAYERBOX        (api::players::get_instance())
#define ACTIVEPLAYERBOX  (PLAYERBOX->get_active())

#endif
