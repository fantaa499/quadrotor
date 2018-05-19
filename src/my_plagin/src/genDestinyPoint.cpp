#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <nav_msgs/Odometry.h>
#include "std_msgs/Bool.h"
#include <ros/console.h>

#include <visualization_msgs/Marker.h>

#include "../include/my_plagin/my_library.h"

#include <octomap/octomap.h>
//#include <octomap/OcTree.h>
#include <octomap_msgs/conversions.h>
#include <octomap_msgs/Octomap.h>

#include <vector>

#define QUADROTOR_SPAN 1
#define QUADROTOR_HEIGHT 0.5
#define PI 3.14159265359
#define N_OF_SECTION_ELL 36
#define EXTRA_RANGE 1
#define DEVIATE 0.5

using namespace std;
using namespace octomap;




class SubscribeAndPublish
{
public:
    SubscribeAndPublish()
    {
        //Topic you want to publish
        pub_ = n_.advertise<geometry_msgs::Vector3>("/intermediate_state", 1);

        marker_pub_ = n_.advertise<visualization_msgs::Marker>("visualization_marker", 10);

        tracePub_ = n_.advertise<visualization_msgs::Marker>("/trace_line", 10);

        subDestiny_ = n_.subscribe("/goal_state", 1, &SubscribeAndPublish::callbackDestiny, this);

        sub_ = n_.subscribe("/ground_truth/state", 1, &SubscribeAndPublish::callback, this);

        subOctomap_ = n_.subscribe("/octomap_full", 1, &SubscribeAndPublish::callbackOctomap, this);

        subFinish_ = n_.subscribe("/is_finish", 1, &SubscribeAndPublish::callbackFinish, this);

    }

    void callbackFinish (const std_msgs::Bool& isFinish)
    {
        if (isFinish.data)
        {
            writeInVec3(semiGoal_, goal_);
        }
    }

    void callbackOctomap(const octomap_msgs::Octomap& input)
    {

        octomap::AbstractOcTree* absTree;
        absTree = octomap_msgs::fullMsgToMap(input);
        // Create Octomap
        octree_ = dynamic_cast<octomap::OcTree*>(absTree);

//            genPointTest();
        genPoint();


    }

    void callback(const nav_msgs::Odometry& input)
    {
        curPos_.x = input.pose.pose.position.x;
        curPos_.y = input.pose.pose.position.y;
        curPos_.z = input.pose.pose.position.z;
        toEulerAngle(input.pose.pose.orientation, orient_.x, orient_.y, orient_.z);
    }

    void callbackDestiny(const geometry_msgs::Vector3& input)
    {
        if ((goal_.x != input.x) ||
            (goal_.y != input.y) ||
            (goal_.z != input.z))
        {
            writeInVec3(goal_, input);
            writeInVec3(semiGoal_, goal_);
            cout << "accept new goal" << endl;
        }
    }

    void genPointTest()
    {
        geometry_msgs::Vector3 output;
        octomap::point3d* intersection;
        octomap::point3d* extraPoint;
        intersection = new octomap::point3d;
        bool isIntersect = checkColision(goal_, intersection);
        if (isIntersect == true)
        {
            ROS_INFO_STREAM("Obstackles on:" << *intersection);
            extraPoint = new octomap::point3d;
            bool isExtraPointExist = findExtraPoint(*intersection, extraPoint);
            if (isExtraPointExist == true)
            {
                ROS_INFO_STREAM("Extra point on" << *extraPoint);
            }
            else
            {
                ROS_INFO_STREAM("Can't found extra point");
            }
        }
        else
        {
            ROS_INFO_STREAM("Sector clear");
        }
        delete intersection;
//            delete extraPoint;
        writeInVec3(output, goal_);
        pub_.publish(output);
    }

    void genPoint ()
    {
        geometry_msgs::Vector3 output;
        writeInVec3(output, semiGoal_);
        octomap::point3d* intersection;
        intersection = new octomap::point3d;
        octomap::point3d* extraPoint;
        extraPoint = new octomap::point3d;
        bool isIntersect = checkColision(semiGoal_, intersection);
//            if(isIntersect == true && (curPos_.z > 0.5))
        if(isIntersect == true)
        {
//                geometry_msgs::Vector3* extraPoint;
            bool isExtraPointExist = findExtraPoint(*intersection, extraPoint);
            if (isExtraPointExist == false)
            {
                ROS_INFO_STREAM("Waiting operator");
                writeInVec3(output, curPos_);
                // TODO
                // make deffence from early off
            }
            else
            {
                semiGoal_.x = extraPoint->x();
                semiGoal_.y = extraPoint->y();
                semiGoal_.z = extraPoint->z();
                writeInVec3(output, semiGoal_);
            }
            publishMarker();
            clearMarker();
        }
        delete intersection;
        delete extraPoint;
        pub_.publish(output);
    }



    bool findExtraPoint (point3d center, octomap::point3d* extraPoint)
    {
        //direction
        double dx = semiGoal_.x - curPos_.x;
        double dy = semiGoal_.y - curPos_.y;
        double dz = semiGoal_.z - curPos_.z;
        octomap::point3d direction(dx, dy, dz);

//        double dx = center.x() - curPos_.x;
//        double dy = center.y() - curPos_.y;
//        double dz = center.z() - curPos_.z;
//        octomap::point3d direction(dx, dy, dz);

        initMarker();

        double x, y, z, range, angle;
        point3d ray, rayEnd;
        bool isIntersect;
        static double t = PI/2; // start discovery from angle PI/2
        double a = 1.5;
        double b = 1;
        //point3d(0) - x coordinate
        //point3d(1) - y Coordinate
        //point3d(2) - z coordinate
        angle = findAngle2d(direction(0), direction(1));
        octomap::point3d* intersection;
        intersection = new octomap::point3d;
        while(a < 10 || b< 10)
        {
            while (t < 2*PI)
            {
                x = center(0) - a*cos(t)*sin(angle);
                y = center(1) - a*cos(t)*cos(angle);
                z = center(2) - b*sin(t);

                OcTreeNode* result = octree_->search(x, y, z);

                geometry_msgs::Vector3 semiGoal;
                semiGoal.x = x;
                semiGoal.y = y;
                semiGoal.z = z;
                octomap::point3d  semiGoalExtra = octomap::point3d(x, y, z);
                // add visualization
                line_strip_.points.push_back(intoPoint(semiGoalExtra));
                points_.points.push_back(intoPoint(semiGoalExtra));

                bool isIntersect = checkColision(semiGoal, intersection);
                if (result == NULL && isIntersect == false)
                {
                    *extraPoint = semiGoalExtra;
                    ROS_INFO_STREAM("Extra point on" << *extraPoint);
                    delete intersection;
                    points1_.points.push_back(intoPoint(semiGoalExtra));
                    return (true);
                }
                t += (2*PI/N_OF_SECTION_ELL);
            }
            t =  PI/2;
            a += 0.5*2;
            b += 0.5*1.2;
        }
        delete intersection;
        return (false);
    }

    bool checkColision(geometry_msgs::Vector3 semiGoal, octomap::point3d* rayEnd) {
        // sensing obstacles in safety value
        vector<octomap::point3d> boundaryAr(5);
        int size = 0;
        double halfW = double(QUADROTOR_SPAN) / 2;
        double halfH = double(QUADROTOR_HEIGHT) / 2;

        boundaryAr.at(size++) = point3d(curPos_.x, curPos_.y, curPos_.z);
        boundaryAr.at(size++) = point3d(curPos_.x + halfW, curPos_.y + halfW, curPos_.z);
        boundaryAr.at(size++) = point3d(curPos_.x - halfW, curPos_.y - halfW, curPos_.z);
        boundaryAr.at(size++) = point3d(curPos_.x + halfW, curPos_.y, curPos_.z + halfH);
        boundaryAr.at(size++) = point3d(curPos_.x - halfW, curPos_.y, curPos_.z - halfH);

        double dx = semiGoal.x - curPos_.x;
        double dy = semiGoal.y - curPos_.y;
        double dz = semiGoal.z - curPos_.z;

        octomap::point3d direction(dx, dy, dz);


        // if bottom boundary intersect with obstackles near MAV
        if (curPos_.z < DEVIATE)
        {
            size-=1;
        }
        // check intersection with safety value
        for (int i = 0; i < size; i++) {
            bool isIntersect = octree_->castRay(boundaryAr.at(i), direction, *rayEnd);
            if (isIntersect)
            {
                point3d intersection;
                isIntersect = octree_->getRayIntersection(boundaryAr.at(i), direction, *rayEnd, intersection);

                if (isIntersect)
                {
                    // if bottom boundary intersect with obstackles near MAV
//                        if (i == 4 && abs(curPos_.x - intersection.x()) < DEVIATE
//                                   && abs(curPos_.y - intersection.y()) < DEVIATE
//                                   && abs(curPos_.z - intersection.z()) < DEVIATE)
//                        {
//                            return false;
//                        }
                    return true;
                }
            }
        }
        return false;
    }

    void publishMarker()
    {
        marker_pub_.publish(line_final_);
        marker_pub_.publish(line_list_);
        marker_pub_.publish(points_);
        marker_pub_.publish(points1_);
    }

    void clearMarker()
    {
        points_.points.clear();
        line_final_.points.clear();
        line_list_.points.clear();
        points1_.points.clear();
    }

    void initMarker()
    {

        points1_.header.frame_id = points_.header.frame_id = line_strip_.header.frame_id = line_list_.header.frame_id  = line_final_.header.frame_id = "world";
        points1_.header.stamp = points_.header.stamp = line_strip_.header.stamp = line_list_.header.stamp = line_final_.header.stamp = ros::Time::now();
        points1_.ns = points_.ns = line_strip_.ns = line_list_.ns = line_final_.ns = "points_and_lines";
        points1_.action = points_.action = line_strip_.action = line_list_.action = line_final_.action = visualization_msgs::Marker::ADD;
//        points_.pose.orientation.w = line_strip_.pose.orientation.w = line_final_.pose.orientation.w = line_list_.pose.orientation.w = 1.0;

        points_.id = 0;
        line_strip_.id = 1;
        line_list_.id = 2;
        line_final_.id = 3;
        points1_.id = 4;

        points_.type = visualization_msgs::Marker::POINTS;
        points1_.type = visualization_msgs::Marker::POINTS;
        line_strip_.type = visualization_msgs::Marker::LINE_STRIP;
        line_list_.type = visualization_msgs::Marker::LINE_LIST;
        line_final_.type = visualization_msgs::Marker::LINE_STRIP;

        // points_ markers use x and y scale for width/height respectively
        points_.scale.x = 0.2;
        points_.scale.y = 0.2;
        points1_.scale.x = 0.2;
        points1_.scale.y = 0.2;

        // line_strip_/line_list_ markers use only the x component of scale, for the line width
        line_strip_.scale.x = 0.1;
        line_list_.scale.x = 0.1;
        line_final_.scale.x = 0.2;

        // points_ are green
        points_.color.g = 1.0f;
        points_.color.a = 1.0;

        // Line strip is blue
        line_strip_.color.b = 1.0;
        line_strip_.color.a = 1.0;

        points1_.color.r = 1.0;
        points1_.color.b = 1.0;
        points1_.color.a = 1.0;

        // Line list is red
        line_list_.color.r = 1.0;
        line_list_.color.a = 1.0;

        // Line final is red
        line_final_.color.b = 1.0;
        line_final_.color.a = 1.0;
    }

    void writeInVec3(geometry_msgs::Vector3& a, geometry_msgs::Vector3 b)
    {
        a.x = b.x;
        a.y = b.y;
        a.z = b.z;
    }

    geometry_msgs::Point intoPoint(octomap::point3d p)
    {
        geometry_msgs::Point point;
        point.x = p.x();
        point.y = p.y();
        point.z = p.z();
        return (point);
    }



private:
    bool isTakeoff_ = false;
    ros::NodeHandle n_;
    ros::Publisher pub_;
    ros::Publisher marker_pub_;
    ros::Subscriber sub_;
    ros::Subscriber subDestiny_;
    ros::Subscriber subOctomap_;
    ros::Subscriber subFinish_;
    ros::Publisher tracePub_;

    geometry_msgs::Vector3 curPos_;
    geometry_msgs::Vector3 orient_;
    geometry_msgs::Vector3 goal_;
    geometry_msgs::Vector3 semiGoal_;

    visualization_msgs::Marker points_;
    visualization_msgs::Marker points1_;
    visualization_msgs::Marker line_strip_;
    visualization_msgs::Marker line_final_;
    visualization_msgs::Marker line_list_;

    octomap::OcTree* octree_;



};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
    //Initiate ROS
    ros::init(argc, argv, "getnIntermidiatePoint");


    //Create an object of class SubscribeAndPublish that will take care of everything
    SubscribeAndPublish SAPObject;

    ros::spin();

    return 0;
}
