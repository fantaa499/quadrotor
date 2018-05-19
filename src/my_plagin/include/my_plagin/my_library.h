#include <geometry_msgs/Quaternion.h>
#include <cmath>
#include <octomap/octomap.h>
#include <vector>
#include <geometry_msgs/Point.h>

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

template  <typename  T>
T distance3d(T dx, T dy, T dz)
{
	return pow(pow(dx,2) + pow(dy,2) + pow(dz,2),0.5);
}


float findAngle2d(float dx, float dy)
{
	float dist = pow((pow(dx, 2) + pow(dy, 2)),0.5);
	return std::atan2(dy/dist, dx/dist);
}

class Qnode
{
public:
	Qnode()
	{
		coord_ = octomap::point3d (0,0,0);
		cost_ = 0;
		parent_ = 0;
	}

	Qnode(octomap::point3d coord)
	{
		coord_ = coord;
		cost_ = 0;
		parent_ = 0;
	}

	Qnode(octomap::point3d coord, double cost, int parent)
	{
		coord_ = coord;
		cost_ = cost;
		parent_ = parent;
	}

	void setCost(double cost)
	{
		cost_ = cost;
	}
	void setCoord(octomap::point3d coord)
	{
		coord_ = coord;
	}
	void setParent(int parent)
	{
		parent_ = parent;
	}
	double getCost()
	{
		return(cost_);
	}
    octomap::point3d getCoord()
	{
		return(coord_);
	}
    geometry_msgs::Vector3 getCoordVec3()
    {
        geometry_msgs::Vector3 a;
        a.x = coord_(0);
        a.y = coord_(1);
        a.z = coord_(2);
        return (a);
    }
	int getParent()
	{
		return(parent_);
	}

	double distanceTo (Qnode node)
	{
		node.coord_ -= coord_;
		return (distance3d(node.coord_.x(), node.coord_.y(), node.coord_.z()));
	}

	double operator [] (int n)
    {
        return coord_(n);
    }

    bool operator == (Qnode b)
    {
        if (abs(this->getCoord().x() - b[0]) < DEVIATION &&
            abs(this->getCoord().y() - b[1]) < DEVIATION &&
            abs(this->getCoord().z() - b[2]) < DEVIATION)
        {
            return (true);
        }
        return (false);
    }

    Qnode operator = (Qnode b)
    {
        this->setCoord(b.getCoord());
        this->setParent(b.getParent());
        this->setCost(b.getCost());
        return (*this);
    }

    geometry_msgs::Point intoPoint3 ()
    {
        geometry_msgs::Point p;
        p.x = coord_.x();
        p.y = coord_.y();
        p.z = coord_.z();
        return (p);
    }

private:
	octomap::point3d coord_;
	double cost_;
	int parent_;
};

Qnode calculateNewCoord (Qnode qr, Qnode qn, double dist, double eps)
{
    Qnode q_new = Qnode();
    if (dist > eps)
    {
        q_new.setCoord(octomap::point3d((qn[0] + ((qr[0]-qn[0])*eps)/qn.distanceTo(qr)),
                                        (qn[1] + ((qr[1]-qn[1])*eps)/qn.distanceTo(qr)),
                                        (qn[2] + ((qr[2]-qn[2])*eps)/qn.distanceTo(qr))));
    }
    else
    {
        q_new = qr;
    }
    return (q_new);
}

geometry_msgs::Vector3 intoVec3(octomap::point3d b)
{
    geometry_msgs::Vector3 a;
    a.x = b(0);
    a.y = b(1);
    a.z = b(2);
    return (a);
}