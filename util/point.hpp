#ifndef UTIL_POINT_HPP
#define UTIL_POINT_HPP

namespace util {
//

template <typename T>
struct basic_point
{
  typedef T result_type;
  typedef T float_t;
  
  virtual basic_point * operator->()
  {
    return this; // ?
  }
  virtual const basic_point * operator->() const
  {
    return this;
  }
};

template <typename T>
struct point2d_base : basic_point<T>
{
  typedef T result_type;
  result_type x, y;
  
  point2d_base(result_type x_ = 0.f, result_type y_ = 0.f) : x(x_), y(y_)
  {}
  
  point2d_base * operator->()
  {
    return this; // ?
  }
  const point2d_base * operator->() const
  {
    return this;
  }
};

template <typename T>
struct point3d_base : basic_point<T>
{
  typedef T result_type;
  result_type x, y, z;

  point3d_base(result_type x_ = 0.f, result_type y_ = 0.f, result_type z_ = 0.f) : x(x_), y(y_), z(z_)
  {}
  
  point3d_base * operator->()
  {
    return this; // ?
  }
  const point3d_base * operator->() const
  {
    return this;
  }

};

template <typename T>
struct point4d_base : basic_point<T>
{
  typedef T result_type;
  result_type x, y, z, w;

  point4d_base(result_type x_ = 0.f, result_type y_ = 0.f, result_type z_ = 0.f, result_type w_ = 0.f) : x(x_), y(y_), z(z_), w(w_)
  {}
  
  point4d_base * operator->()
  {
    return this; // ?
  }
  const point4d_base * operator->() const
  {
    return this;
  }

  
};

typedef point2d_base<float> point2d;
typedef point3d_base<float> point3d;
typedef point4d_base<float> point4d;

}

#endif
