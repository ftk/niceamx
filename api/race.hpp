#ifndef API_RACE_HPP
#define API_RACE_HPP

#include "util/point.hpp"

#include <cassert>
#include <map>
#include <algorithm>
#include <functional>
#include <istream>
#include <ostream>

//#include <iostream>

namespace api {
//

namespace detail
{
  struct checkpoint
  {
    util::point3d pos;
    checkpoint * next;

    checkpoint() : next(NULL) {}
    checkpoint(util::point3d pos_) : pos(pos_), next(NULL) {}
  };

  struct player_race_state // perplayer class
  {
    checkpoint * current_cp;

    player_race_state(checkpoint * cp) : current_cp(cp) {}
    player_race_state() : current_cp(NULL) {}
    
    bool next_cp()
    {
      assert(current_cp != NULL);
      if(current_cp->next != NULL)
      {
        current_cp = current_cp->next;
        return true;
      }
      return false;
    }
  };

  struct race_loader
  {
    checkpoint * root_cp;
    checkpoint * current_cp;

    race_loader() : root_cp(NULL), current_cp(NULL) {}
    ~race_loader()
    {
      destruct();
    }

    void operator()(util::point3d pos)
    {
      if(current_cp == NULL)
      {
        current_cp = new checkpoint(pos);
        root_cp = current_cp;
      }
      else
      {
        assert(current_cp->next == NULL);
        current_cp->next = new checkpoint(pos);
        current_cp = current_cp->next;
      }
    }

    operator checkpoint * ()
    {
      return root_cp;
    }

    static void delete_checkpoints(checkpoint * root)
    {
      if(root != NULL)
      {
        delete_checkpoints(root->next);
        root->next = NULL;
        delete root;
      }
    }
    void destruct()
    {
      delete_checkpoints(root_cp);
      root_cp = NULL;
      current_cp = NULL;
    }

    void import_stream(std::istream & s)
    {
      while(!s.eof())
      {
        util::point3d pos;
        s >> pos.x >> pos.y >> pos.z;
        if(pos.x != 0.f && pos.y != 0.f && pos.z != 0.f)
          (*this)(pos);
        //std::cout << pos.x << ' ' << pos.y << ' ' << pos.z << '\n';
      }
    }
    
    void export_stream(std::ostream & s)
    {
      checkpoint * cp = root_cp;
      while(cp)
      {
        util::point3d& pos = cp->pos;
        s << pos.x << ' ' << pos.y << ' ' << pos.z << '\n';
        cp = cp->next;
      }
    }
  };


}
// -------------------------------------
class race
{
private:
  detail::checkpoint * root;

  typedef std::map<int, detail::player_race_state> players_t;
  players_t players;

  int finished;
  
  //typedef void (*onfinish_t)(int, int);
  typedef std::function<void (int, int)> onfinish_t;
  onfinish_t finish_fn;


public:

  float cp_size;
  
  race(detail::checkpoint * r = NULL) : root(r), finished(0), finish_fn(NULL), cp_size(8.f) {}

  inline void set_finish(onfinish_t fn)
  {
    finish_fn = fn;
  }

  // ----
  void join(int id)
  {
    detail::player_race_state start(root);
    players[id] = start;
    //players.insert(pair<int, detail::player_race_state>(playerid, start));
  }
  void part(int id)
  {
    players.erase(id);
    remove_checkpoint(id);
  }

  void start()
  {
    /*
    assert(root != NULL);
    for_each([this](int id)
    {
      set_checkpoint(id, root);
    });
    */
    
    for(auto it = players.begin(), en = players.end(); it != en; ++it)
    {
      assert(it->second.current_cp != NULL);
      set_checkpoint(it->first, it->second.current_cp);
    }
    
  }
  void start(int playerid)
  {
    auto it = players.find(playerid);
    if(it == players.end())
      return;
    assert(it->second.current_cp != NULL);
    set_checkpoint(it->first, it->second.current_cp);
  }
  
  inline bool is_player_in_race(int id) const
  {
    return(players.find(id) != players.end());
  }

  template <typename T>
  void for_each(T fn) const
  {
    for(auto it = players.cbegin(), en = players.cend(); it != en; ++it)
    {
      fn(it->first);
    }
  }

  inline std::size_t count() const
  {
    return players.size();
  }

  // ---
  void proccess_cp(int playerid) // internal
  {
    if(!is_player_in_race(playerid))
      return;
    detail::player_race_state& player = players[playerid];
    if(player.next_cp())
    {
      set_checkpoint(playerid, player.current_cp);
    }
    else // finish
    {
      finished++;
      if(finish_fn != NULL)
        finish_fn(playerid, finished);
      part(playerid);
    }
  }

private:
  static void remove_checkpoint(int playerid);
  void set_checkpoint(int playerid, const detail::checkpoint * cp);
};


}

#endif

