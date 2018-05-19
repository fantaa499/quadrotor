//
// Created by anton on 13.05.18.
//



#include <ros/ros.h>
#include <vector>
//#include "../include/my_plagin/my_library.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Pose.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/Vector3.h"
#include "nav_msgs/Odometry.h"

class SubscribeAndPublish {
public:
    SubscribeAndPublish()
    {
        //Topic you want to publish
        pub_ = n_.advertise<nav_msgs::Path>("/trajectory_line", 1);

        sub_ = n_.subscribe("/ground_truth/state", 1, &SubscribeAndPublish::callback, this);

    }

    void callback(const nav_msgs::Odometry& input)
    {
        nav_msgs::Path msg;
        msg.header.frame_id = "world";
        msg.header.stamp = ros::Time::now();

        geometry_msgs::PoseStamped currentPos;
        currentPos.pose.position.x = input.pose.pose.position.x;
        currentPos.pose.position.y = input.pose.pose.position.y;
        currentPos.pose.position.z = input.pose.pose.position.z;

        poses_.push_back(currentPos);
        msg.poses = poses_;

        pub_.publish(msg);
        ros::Duration(0.5).sleep();
    }

private:
    ros::NodeHandle n_;
    ros::Publisher pub_;
    ros::Subscriber sub_;
    std::vector<geometry_msgs::PoseStamped> poses_;
};





int main(int argc, char **argv)
{
    //Initiate ROS
    ros::init(argc, argv, "genIntermidiatePoint");


    //Create an object of class SubscribeAndPublish that will take care of everything
    SubscribeAndPublish SAPObject;

    ros::spin();

    return 0;
}