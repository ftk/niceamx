#ifndef API_OBJECT_HPP
#define API_OBJECT_HPP

#include "config.h"

#include "util/point.hpp"
#include "util/rotation.hpp"

#include <map>
#include <algorithm>

namespace api {
  
//

class basic_object
{
public:
  basic_object() {}
  virtual ~basic_object() {}
  
  virtual bool show(int playerid) = 0;
  virtual bool hide(int playerid) = 0;
  
};

class object : public basic_object
{
public:
  // props
  int modelid;
  
  /*
  float x, y, z;
  float rx, ry, rz;
  */
  util::point3d pos;
  util::euler rot;
  
  int interior, world;
protected:
  
  typedef std::map<int, int> pobjects_t; // playerid - objectid
  
  pobjects_t pobjects;
  
public:
  
  
  object(int modelid_, 
      float x_ = 0.f, float y_ = 0.f, float z_ = 0.f, 
      float rx_ = 0.f, float ry_ = 0.f, float rz_ = 0.f, 
      int interior_ = 0, int world_ = 0) 
  : modelid(modelid_),
    //x(x_), y(y_), z(z_),
    pos(x_, y_, z_),
    //rx(rx_), ry(ry_), rz(rz_),
    rot(util::point3d(rx_, ry_, rz_)),
    interior(interior_), world(world_)
  {
  }

  object(int modelid_, 
      util::point3d pos_,
      util::point3d rot_,
      int interior_ = 0, int world_ = 0) 
  : modelid(modelid_),
    pos(pos_),
    rot(rot_),
    interior(interior_), world(world_)
  {
  }
  object(int modelid_, 
      util::point3d pos_,
      util::euler rot_,
      int interior_ = 0, int world_ = 0) 
  : modelid(modelid_),
    pos(pos_),
    rot(rot_),
    interior(interior_), world(world_)
  {
  }


  ~object()
  {
    std::for_each(pobjects.begin(), pobjects.end(),
      [this] (std::pair<int, int> p)
      {
        hide(p.first);
      }
	 );
  }
    
  //


  bool show(int basic_player);


  bool hide(int playerid);


  bool is_object_streamed(int playerid)
  {
    return(pobjects.find(playerid) != pobjects.end());
  }
  
};
  
  
  
}

#endif
