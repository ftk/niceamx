#include "util/rotation.hpp"
#include "util/point.hpp"
//#include "util/notify.h"

#include <cmath>

namespace util {
 

quaternion operator - (const quaternion& o)
{
  //point4d reversed(-o->x, -o->y, -o->y, o->w);
  return quaternion(-o->x, -o->y, -o->y, o->w);
}



static void quaternion_to_euler(float qx, float qy, float qz, float qw, float& x, float& y, float& z)
{
	using namespace std;
	float sqw = qw*qw;
	float sqx = qx*qx;
	float sqy = qy*qy;
	float sqz = qz*qz;

	float vx = atan2(2.0f * (qx*qy + qz*qw), sqx - sqy - sqz + sqw);
	float vy = asin(-2.0f * (qx*qz - qy*qw));
	float vz = atan2(2.0f * (qy*qz + qx*qw), -sqx - sqy + sqz + sqw);

	x = rad_to_deg(vz);
	y = rad_to_deg(vy);
	z = rad_to_deg(vx);
	return;
}
static point4d euler_to_quaternion(float theta_z, float theta_y, float theta_x)
{
    using namespace std;
	const float cos_z_2 = cos(0.5f*theta_z);
	const float cos_y_2 = cos(0.5f*theta_y);
	const float cos_x_2 = cos(0.5f*theta_x);

	const float sin_z_2 = sin(0.5f*theta_z);
	const float sin_y_2 = sin(0.5f*theta_y);
	const float sin_x_2 = sin(0.5f*theta_x);

	// and now compute quaternion
	point4d v;
	v.w   = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
	v.x = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
	v.y = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
	v.z = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
	return v;
}



euler quaternion::to_euler()
{
  point3d result;
  quaternion_to_euler(-rot.x, -rot.y, -rot.z, rot.w, result.x, result.y, result.z);
  return euler(result);
}

quaternion euler::to_quaternion()
{
  // TODO: check if it works
  point4d result = euler_to_quaternion(rot.x, rot.y, rot.z);
  return quaternion(result);
}


}

