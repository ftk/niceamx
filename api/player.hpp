#ifndef API_PLAYER_HPP
#define API_PLAYER_HPP

#include "util/point.hpp"
//#include "util/notify.hpp"

#include <cassert>

namespace api {
  
struct basic_player
{
  // id
  int playerid;
  
  basic_player(int);

  virtual int get_id() const
  {
    return playerid;
  }
  
  int operator * () const
  {
    return get_id();
  }
  
  virtual operator int () const
  {
    return get_id();
    
  }
  
  // props
  //bool connected;
  // ...
  
  // methods

  virtual util::point3d get_pos() const = 0;
  virtual void set_pos(const util::point3d& p) = 0;

  
};
  
struct player : basic_player
{
  
  player(int id);
    
  util::point3d get_pos() const;

  void set_pos(const util::point3d& p);
  
};

struct fake_player : basic_player
{
  
  fake_player(int id) : basic_player(id)
  {
    //connected = true;
  }
  
  util::point3d get_pos() const
  {
    return util::point3d(0.f, 0.f, 0.f);
  }
  void set_pos(const util::point3d& p)
  {
    
  }
  
};


}

#endif

