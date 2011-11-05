#ifndef UTIL_ROTATION_HPP
#define UTIL_ROTATION_HPP

#include "util/point.hpp"

#ifndef PI
#define PI 3.141592
#endif


namespace util {

//
inline float rad_to_deg(float rad)
{
  return float(rad * (180.f / PI));
}
inline float deg_to_rad(float deg)
{
  return float(deg * (PI / 180.f));
}

struct euler;
struct quaternion;

  
struct basic_rotation
{
  virtual euler to_euler() = 0;
  virtual quaternion to_quaternion() = 0;
  
};


struct euler : basic_rotation
{
  point3d rot;
  
  euler(point3d o) : rot(o) 
  {}
  euler(point3d::float_t x, point3d::float_t y, point3d::float_t z) : rot(x, y, z)
  {}
  
  euler() : rot() {}

  point3d& operator * ()
  {
    return rot;
  }
  const point3d& operator * () const
  {
    return rot;
  }
  point3d * operator->()
  {
    return &rot;
  }
  const point3d * operator->() const
  {
    return &rot;
  }
  euler to_euler()
  {
    return *this;
  }
  quaternion to_quaternion();
  
};




struct quaternion : basic_rotation
{
  point4d rot;
  
  quaternion(point4d o) : rot(o)
  {}
  
  quaternion(point4d::float_t x, point4d::float_t y, point4d::float_t z, point4d::float_t w) : rot(x, y, z, w)
  {}
  
  quaternion() : rot() 
  {}
  
  point4d& operator * ()
  {
    return rot;
  }
  const point4d& operator * () const
  {
    return rot;
  }
  point4d * operator->()
  {
    return &rot;
  }
  const point4d * operator->() const
  {
    return &rot;
  }  
  
  friend quaternion operator - (const quaternion&);
  
  quaternion to_quaternion()
  {
    return *this;
  }
  
  euler to_euler();
  
};

quaternion operator - (const quaternion&);

}
#endif