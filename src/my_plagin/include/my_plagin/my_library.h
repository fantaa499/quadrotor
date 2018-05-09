#include <geometry_msgs/Quaternion.h>
#include <cmath>

#define DEVIATION 0.2

static void toEulerAngle(const geometry_msgs::Quaternion& q, double& roll, double& pitch, double& yaw)
{
	// roll (x-axis rotation)
	double sinr = +2.0 * (q.w * q.x + q.y * q.z);
	double cosr = +1.0 - 2.0 * (q.x * q.x + q.y * q.y);
	roll = atan2(sinr, cosr);

	// pitch (y-axis rotation)
	double sinp = +2.0 * (q.w * q.y - q.z * q.x);
	if (fabs(sinp) >= 1)
		pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
	else
		pitch = asin(sinp);

	// yaw (z-axis rotation)
	double siny = +2.0 * (q.w * q.z + q.x * q.y);
	double cosy = +1.0 - 2.0 * (q.y * q.y + q.z * q.z);
	yaw = atan2(siny, cosy);
}


float fastDistance2d( float dx, float dy )
{
  if ( dx < 0 ) dx = -dx;
  if ( dy < 0 ) dy = -dy;
  if ( dx < dy )
		return 0.961f*dy+0.398f*dx;
  else
		return 0.961f*dx+0.398f*dy;
}

float distance3d(int dx, int dy, int dz)
{
	return pow(pow(dx,2) + pow(dy,2) + pow(dz,2),0.5);
}

float findAngle2d(float dx, float dy)
{
	float dist = pow((pow(dx, 2) + pow(dy, 2)),0.5);
	return std::atan2(dy/dist, dx/dist);
}
