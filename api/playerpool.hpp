#ifndef API_PLAYERPOOL_HPP
#define API_PLAYERPOOL_HPP

#include "config.h"
#include <string>
#include <map>
#include <algorithm>
#include <array>

#include <boost/cstdint.hpp>

#include "util/utils.h"
#include "util/singleton.hpp"
#include "util/arraylist.hpp"

#include "num_players.hpp"


namespace api {
//

// exceptions

class bad_player {};


// player constant info

struct player_info
{
    int id = -1;
    boost::uint32_t ipv4 = 0u;
    std::string name;
    boost::uint32_t color;

    // methods
    void update();
    void clean(); // sync?
    std::string get_ip();
    void set_color(boost::uint32_t c);
};



// ----------------
class active_players
{
private:
  typedef std::map<int, util::walltime_t> playertimes_t;
  playertimes_t ptime;

  const int timeout; // if the player is not updating he is not active
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
  typedef util::arraylist<NUM_PLAYERS> playerids_t;
  playerids_t playerids;
  int total_players = 0;


  active_players active;
public:
  std::array<player_info, NUM_PLAYERS> info; // players info


  typedef playerids_t::iterator iterator;
  typedef playerids_t::const_iterator const_iterator;

public:
  
  inline bool is_connected(int playerid) const
  {
    //player_iter_t it = playerids.find(playerid);
    //return(it != playerids.end());
      if(playerid < 0 || playerid >= NUM_PLAYERS)
          throw std::runtime_error("playerbox: wrong playerid");
      return playerids.get(playerid);
  }
  inline bool valid(int playerid) const
  {
      return playerids.get(playerid);
  }

  
  inline std::size_t count() const
  {
      return(total_players);
  }
  inline std::size_t size() const
  {
      return count();
  }
  inline bool empty() const
  {
      return playerids.empty();
  }

  inline playerids_t& get()
  {
    return playerids;
  }
  inline const playerids_t& get() const
  {
    return playerids;
  }

  inline int next(int playerid)
  {
      return playerids.next(playerid);
  }

  
  // internal
  inline void add(int playerid)
  {
    if(playerids.set(playerid))
    {
        info[playerid].id = playerid;
        info[playerid].update();
        total_players++;
    }
  }
  inline void remove(int playerid)
  {
    if(playerids.unset(playerid))
    {
        info[playerid].clean();
        total_players--;
    }
  }

  inline active_players& get_active()
  {
    return active;
  }

  inline player_info& get_info(int id)
  {
      return info.at(id);
  }

  inline const_iterator begin() const
  {
      return playerids.begin();
  }
  inline const_iterator end() const
  {
      return playerids.end();
  }

  
  int get_player(const char * name);
  int get_player(const std::string& name)
  {
      return get_player(name.c_str());
  }


  int get_player_exact(const char * name)
  {
      for(int player : playerids)
      {
          if(info[player].name == name)
              return player;
      }
      throw bad_player();
  }
  int get_player_exact(const std::string& name)
  {
      for(int player : playerids)
      {
          if(info[player].name == name)
              return player;
      }
      throw bad_player();
  }

  int get_player_by_id_or_name(const char * str);
};


}

#define PLAYERBOX        (api::players::get_instance())
#define ACTIVEPLAYERBOX  (PLAYERBOX->get_active())

#endif
