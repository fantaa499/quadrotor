#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <nav_msgs/Odometry.h>
#include <cmath>
#include <geometry_msgs/Quaternion.h>
#include "std_msgs/Bool.h"
// #include<pcl/point_cloud.h>
// #include<pcl_conversions/pcl_conversions.h>
// #include<sensor_msgs/PointCloud2.h>
// #include<pcl/io/pcd_io.h>
// #include <octomap/octomap.h>
// #include <octomap/OcTree.h>
// #include <octomap_msgs/conversions.h>
// #include <octomap_msgs/Octomap.h>

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





class SubscribeAndPublish
{
    public:
        SubscribeAndPublish()
        {
            //Topic for publish
            pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

            pubFinish_ = n_.advertise<std_msgs::Bool>("/is_finish", 1);

            //Topic for subscribe
            subDestiny_ = n_.subscribe("/intermediate_state", 1, &SubscribeAndPublish::callbackDestiny, this);

            sub_ = n_.subscribe("/ground_truth/state", 1, &SubscribeAndPublish::callback1, this);


        }
        void callback(const nav_msgs::Odometry& input)
        {
            geometry_msgs::Twist output;
            std_msgs::Bool isFinish;
            isFinish.data = false;

            geometry_msgs::Vector3 locGoal;
            geometry_msgs::Vector3 locPos;
            geometry_msgs::Vector3 orient;
            toEulerAngle(input.pose.pose.orientation, orient.x, orient.y, orient.z);

            // determinate goal point in local system coordinate
            locPos.x = cos(orient.z)*input.pose.pose.position.x + sin(orient.z)*input.pose.pose.position.y;
            locPos.y = -sin(orient.z)*input.pose.pose.position.x + cos(orient.z)*input.pose.pose.position.y;

            locGoal.x = cos(orient.z)*goal_.x + sin(orient.z)*goal_.y - locPos.x;
            locGoal.y = -sin(orient.z)*goal_.x + cos(orient.z)*goal_.y - locPos.y;
            locGoal.z = goal_.z - input.pose.pose.position.z;

            // angular speed
            double distanceForGoalxy = pow((pow(locGoal.x, 2) + pow(locGoal.y, 2)),0.5);
            double dYaw = std::atan2(locGoal.y/distanceForGoalxy, locGoal.x/distanceForGoalxy);

            if (std::abs(dYaw) < 0.03)
            {
                output.angular.z = 0;
                // linear speed
                if ((std::abs(locGoal.x) < deviation_) &&
                    (std::abs(locGoal.y) < deviation_) &&
                    (std::abs(locGoal.z) < deviation_))
                {
                    output.linear.x = 0;
                    output.linear.y = 0;
                    output.linear.z = 0;
                    isFinish.data  = true;
                }
                else
                {

                    double maxDeviation = std::max(std::abs(locGoal.x), std::abs(locGoal.z));
                    output.linear.x = speed_*locGoal.x/maxDeviation;
                    output.linear.z = speed_*locGoal.z/maxDeviation;
                }
            }
            else
            {
                output.linear.x = 0;
                output.linear.y = 0;
                output.linear.z = 0;
                if (dYaw>0)
                {
                    output.angular.z = speed_*2 ;
                }
                else
                {
                    output.angular.z = -speed_*2 ;
                }
            }
            double varible = sin(orient.z);

            pub_.publish(output);
            pubFinish_.publish(isFinish);
        }

        void callback1(const nav_msgs::Odometry& input)
        {
            geometry_msgs::Twist output;
            std_msgs::Bool isFinish;
            isFinish.data = false;

            geometry_msgs::Vector3 locGoal;
            geometry_msgs::Vector3 locPos;
            geometry_msgs::Vector3 orient;

            toEulerAngle(input.pose.pose.orientation, orient.x, orient.y, orient.z);
            locPos.x = cos(orient.z)*input.pose.pose.position.x + sin(orient.z)*input.pose.pose.position.y;
            locPos.y = -sin(orient.z)*input.pose.pose.position.x + cos(orient.z)*input.pose.pose.position.y;

            locGoal.x = cos(orient.z)*goal_.x + sin(orient.z)*goal_.y - locPos.x;
            locGoal.y = -sin(orient.z)*goal_.x + cos(orient.z)*goal_.y - locPos.y;
            locGoal.z = goal_.z - input.pose.pose.position.z;

            geometry_msgs::Vector3 dCoordinate;


            // linear speed
            if ((std::abs(locGoal.x) < deviation_) &&
            (std::abs(locGoal.y) < deviation_) &&
            (std::abs(locGoal.z) < deviation_))
            {
                output.linear.x = 0;
                output.linear.y = 0;
                output.linear.z = 0;
                isFinish.data = true;
            }
            else
            {
                double maxDeviation = std::max(std::abs(locGoal.x), std::abs(locGoal.y));
                maxDeviation = std::max(std::abs(maxDeviation), std::abs(locGoal.z));
                output.linear.x = (locGoal.x / maxDeviation) * speed_;
                output.linear.y = (locGoal.y / maxDeviation) * speed_;
                output.linear.z = (locGoal.z / maxDeviation) * speed_;
            }

            // angular speed
            double distanceForGoalxy =pow((pow(locGoal.x, 2) + pow(locGoal.y, 2)),0.5);
            double dYaw = std::atan2(locGoal.y/distanceForGoalxy, locGoal.x/distanceForGoalxy);

            if (std::abs(dYaw) < deviation_ / 5 )
            {
                output.angular.z = 0;
            }
            else
            {
                if (dYaw>0)
                {
                    output.angular.z = speed_ ;
                }
                else
                {
                    output.angular.z = -speed_ ;
                }
            }

            pubFinish_.publish(isFinish);
            pub_.publish(output);
        }

        void callbackDestiny(const geometry_msgs::Vector3& input)
        {
            goal_.x = input.x;
            goal_.y = input.y;
            goal_.z = input.z;
        }

        void setSpeed (double speed)
        {
            speed_ = speed;
        }

        void setDeviation (double deviation)
        {
            deviation_ = deviation;
        }
    private:
        ros::NodeHandle n_;
        ros::Publisher pub_;
        ros::Publisher pubFinish_;
        ros::Subscriber sub_;
        ros::Subscriber subDestiny_;
        geometry_msgs::Vector3 goal_;
        double speed_ = 0.4;
        double deviation_ = 0.2;
};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
    //Initiate ROS
    ros::init(argc, argv, "goToDestiny");

    //Create an object of class SubscribeAndPublish that will take care of everything
    SubscribeAndPublish SAPObject;

    ros::spin();

    return 0;
}
