#ifndef UTIL_POINT_HPP
#define UTIL_POINT_HPP

namespace util {
//


template <typename T>
struct point2d_base
{
  typedef T result_type;
  T x, y;
  
  point2d_base(T x_ = 0.f, T y_ = 0.f) : x(x_), y(y_)
  {}

  point2d_base operator -() const { return point2d_base(-x, -y); }
  point2d_base operator -(const point2d_base &v) const { return point2d_base(x-v.x, y-v.y); }
  point2d_base operator +(const point2d_base &v) const { return point2d_base(x+v.x, y+v.y); }
  point2d_base operator *(const T v) const { return point2d_base(x*v, y*v); }
  point2d_base operator *(const point2d_base &v) const { return point2d_base(x*v.x, y*v.y); }
  point2d_base operator /(const T v) const { return point3d_base(x/v, y/v); }
  point2d_base operator /(const point2d_base &v) const { return point2d_base(x/v.x, y/v.y); }

  const point2d_base &operator =(const point2d_base &v) { x = v.x; y = v.y; return *this; }

  const point2d_base &operator +=(const point2d_base &v) { x += v.x; y += v.y; return *this; }
  const point2d_base &operator -=(const point2d_base &v) { x -= v.x; y -= v.y; return *this; }
  const point2d_base &operator *=(const T v) { x *= v; y *= v; return *this;	}
  const point2d_base &operator *=(const point2d_base &v) { x *= v.x; y *= v.y; return *this; }
  const point2d_base &operator /=(const T v) { x /= v; y /= v; return *this;	}
  const point2d_base &operator /=(const point2d_base &v) { x /= v.x; y /= v.y; return *this; }

  bool operator ==(const point2d_base &v) const { return x == v.x && y == v.y; }

  operator const T* () { return &x; }
};

template <typename T>
struct point3d_base
{
  typedef T result_type;
  T x, y, z;

  point3d_base(T x_ = 0.f, T y_ = 0.f, T z_ = 0.f) : x(x_), y(y_), z(z_)
  {}
  
  const point3d_base &operator =(const point3d_base &v) { x = v.x; y = v.y; z = v.z; return *this; }

  point3d_base operator -(const point3d_base &v) const { return point3d_base(x-v.x, y-v.y, z-v.z); }
  point3d_base operator -() const { return point3d_base(-x, -y, -z); }
  point3d_base operator +(const point3d_base &v) const { return point3d_base(x+v.x, y+v.y, z+v.z); }
  point3d_base operator *(const T v) const { return point3d_base(x*v, y*v, z*v); }
  point3d_base operator *(const point3d_base &v) const { return point3d_base(x*v.x, y*v.y, z*v.z); }
  point3d_base operator /(const T v) const { return point3d_base(x/v, y/v, z/v); }
  point3d_base operator /(const point3d_base &v) const { return point3d_base(x/v.x, y/v.y, z/v.z); }

  const point3d_base &operator +=(const point3d_base &v) { x += v.x; y += v.y; z += v.z; return *this; }
  const point3d_base &operator -=(const point3d_base &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
  const point3d_base &operator *=(const T v) { x *= v; y *= v; z *= v; return *this;	}
  const point3d_base &operator *=(const point3d_base &v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
  const point3d_base &operator /=(const T v) { x /= v; y /= v; z /= v; return *this;	}
  const point3d_base &operator /=(const point3d_base &v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

  bool operator ==(const point3d_base &v) const { return x == v.x && y == v.y && z == v.z; }
};

template <typename T>
struct point4d_base
{
  typedef T result_type;
  T x, y, z, w;

  point4d_base(T x_ = 0.f, T y_ = 0.f, T z_ = 0.f, T w_ = 0.f) : x(x_), y(y_), z(z_), w(w_)
  {}
  
  point4d_base operator +(const point4d_base &v) const { return point4d_base(x+v.x, y+v.y, z+v.z, w+v.w); }
  point4d_base operator -(const point4d_base &v) const { return point4d_base(x-v.x, y-v.y, z-v.z, w-v.w); }
  point4d_base operator -() const { return point4d_base(-x, -y, -z, -w); }
  point4d_base operator *(const point4d_base &v) const { return point4d_base(x*v.x, y*v.y, z*v.z, w*v.w); }
  point4d_base operator *(const T v) const { return point4d_base(x*v, y*v, z*v, w*v); }
  point4d_base operator /(const point4d_base &v) const { return point4d_base(x/v.x, y/v.y, z/v.z, w/v.w); }
  point4d_base operator /(const T v) const { return point4d_base(x/v, y/v, z/v, w/v); }

  const point4d_base &operator =(const point4d_base &v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }

  const point4d_base &operator +=(const point4d_base &v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
  const point4d_base &operator -=(const point4d_base &v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
  const point4d_base &operator *=(const T v) { x *= v; y *= v; z *= v; w *= v; return *this;	}
  const point4d_base &operator *=(const point4d_base &v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
  const point4d_base &operator /=(const T v) { x /= v; y /= v; z /= v; w /= v; return *this;	}
  const point4d_base &operator /=(const point4d_base &v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }

  bool operator ==(const point4d_base &v) const { return x == v.x && y == v.y && z == v.z && w == v.w; } //TODO: do this with an eps instead


};

typedef point2d_base<float> point2d;
typedef point3d_base<float> point3d;
typedef point4d_base<float> point4d;

}

#endif
