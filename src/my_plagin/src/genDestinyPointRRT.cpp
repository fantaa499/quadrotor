#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <nav_msgs/Odometry.h>
#include "std_msgs/Bool.h"
#include <ros/console.h>

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
                bool isIntersect = checkColision(semiGoal, intersection);
                if (result == NULL && isIntersect == false)
                {
                    *extraPoint = semiGoalExtra;
                    ROS_INFO_STREAM("Extra point on" << *extraPoint);
                    delete intersection;
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

    void writeInVec3(geometry_msgs::Vector3& a, geometry_msgs::Vector3 b)
    {
        a.x = b.x;
        a.y = b.y;
        a.z = b.z;
    }

    // cout << endl;
    // cout << "casting ray from " << origin  << " in the " << direction << " direction"<< endl;
    // bool success = octree->castRay(origin, direction, rayEnd);
    //
    // if(success){
    // 	cout << "ray hit cell with center " << rayEnd << endl;
    //
    // 	octomap::point3d intersection;
    // 	success = octree->getRayIntersection(origin, direction, rayEnd, intersection);
    // 	if(success)
    // 		cout << "entrance point is " << intersection << endl;
    // }



private:
    bool isTakeoff_ = false;
    ros::NodeHandle n_;
    ros::Publisher pub_;
    ros::Subscriber sub_;
    ros::Subscriber subDestiny_;
    ros::Subscriber subOctomap_;
    ros::Subscriber subFinish_;
    geometry_msgs::Vector3 curPos_;
    geometry_msgs::Vector3 orient_;
    geometry_msgs::Vector3 goal_;
    geometry_msgs::Vector3 semiGoal_;

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
