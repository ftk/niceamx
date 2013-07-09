#ifndef UTIL_ROTATION_HPP
#define UTIL_ROTATION_HPP

#include "util/point.hpp"


namespace util {

static constexpr double pi = 3.1415926535897932384626433;
static constexpr float pi_f = 3.1415926535897932384626433f;
//
template <typename T>
inline constexpr T rad_to_deg(T rad)
{
  return (rad * (180. / pi));
}
template <typename T>
inline constexpr T deg_to_rad(T deg)
{
  return ((deg * pi) / 180.);
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
  euler(float x, float y, float z) : rot(x, y, z)
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
  
  quaternion(float x, float y, float z, float w) : rot(x, y, z, w)
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
