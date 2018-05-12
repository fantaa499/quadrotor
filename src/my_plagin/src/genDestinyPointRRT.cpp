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
#include <ctime>

#define QUADROTOR_SPAN 1
#define QUADROTOR_HEIGHT 0.5
#define PI 3.14159265359
#define N_OF_SECTION_ELL 36
#define EXTRA_RANGE 1
#define DEVIATE 0.5
#define X_MAX 60
#define Y_MAX 60
#define Z_MAX 60
#define MAX_NUM_NODES 2500
#define BIG_VALUE 9999
#define EPS 2
#define TARGET_ZONE 1

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

        subDestiny_ = n_.subscribe("/goal_state", 1, &SubscribeAndPublish::callbackDestiny, this);

        sub_ = n_.subscribe("/ground_truth/state", 1, &SubscribeAndPublish::callback, this);

        subOctomap_ = n_.subscribe("/octomap_full", 1, &SubscribeAndPublish::callbackOctomap, this);

        subFinish_ = n_.subscribe("/is_finish", 1, &SubscribeAndPublish::callbackFinish, this);

    }

    void callbackFinish (const std_msgs::Bool& isFinish)
    {
        if (isFinish.data)
        {
            if (currentPath_.empty())
            {
                nextPosition_ = goal_;
            }
            else
            {
                nextPosition_ = intoVec3(currentPath_.back());
                currentPath_.pop_back();
            }
        }
        pub_.publish(nextPosition_);
    }

    void callbackOctomap(const octomap_msgs::Octomap& input)
    {
        octomap::AbstractOcTree* absTree;
        absTree = octomap_msgs::fullMsgToMap(input);
        // Create Octomap
        octree_ = dynamic_cast<octomap::OcTree*>(absTree);
        octomap::point3d* rayEnd;
        if ((curPos_.x != 0       || curPos_.y != 0       || curPos_.z != 0)  &&
            (nextPosition_.x != 0 || nextPosition_.y != 0 || nextPosition_.z != 0))
        {
            if (checkColision(curPos_, nextPosition_, rayEnd))
            {
                genPath();
                nextPosition_ = intoVec3(currentPath_.back());
                currentPath_.pop_back();
            }
            pub_.publish(nextPosition_);
        }
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
            writeInVec3(nextPosition_, goal_);
            cout << "accept new goal" << endl;
            pub_.publish(nextPosition_);
        }
    }


    void genPath() {
//        geometry_msgs::Vector3 output; //TODO
        //gen output point

        initMarker();

        currentPath_.clear();

        Qnode q_start = Qnode(octomap::point3d(curPos_.x, curPos_.y, curPos_.z), 0, -1);

        Qnode q_goal = Qnode(octomap::point3d(nextPosition_.x, nextPosition_.y, nextPosition_.z)); // fix goal

        std::vector<Qnode> nodes;
        nodes.push_back(q_start);
        //draw start node
        points_.points.push_back(q_start.intoPoint3());
        int i = 0;
        while (std::abs(nodes.back().getCoord().x() - q_goal.getCoord().x()) > TARGET_ZONE ||
               std::abs(nodes.back().getCoord().y() - q_goal.getCoord().y()) > TARGET_ZONE ||
               std::abs(nodes.back().getCoord().z() - q_goal.getCoord().z()) > TARGET_ZONE)
        {
            i++;
            // break if quantity of node > max
            if (i > MAX_NUM_NODES)
            {
                break;
            }

            //create random node
            std::srand(i*unsigned(std::time(0)));
            // gen new node in box over MAV
            octomap::point3d randomVarible (-double(X_MAX/2) + double (std::rand())/RAND_MAX*X_MAX + curPos_.x,
                                            -double(Y_MAX/2) + double (std::rand())/RAND_MAX*Y_MAX + curPos_.y,
                                            -double(Z_MAX/2) + double (std::rand())/RAND_MAX*Z_MAX + curPos_.z);
            Qnode q_rand = Qnode(randomVarible);

            // pick the closest node from existing list to branch out form
            int minIndex = BIG_VALUE;
            double minDist = BIG_VALUE;
            for (int j = 0; j < nodes.size(); j++)
            {
                double tempDist = nodes[j].distanceTo(q_rand);
                octomap::point3d* rayEnd;
//                if (tempDist < minDist && !checkColision(nodes[j].getCoordVec3(), q_rand.getCoordVec3(), rayEnd))
                //TODO
                // add detecting obstacles
                if (tempDist < minDist)
                {
                    minDist = tempDist;
                    minIndex = j;
                }
            }
            // if can't connect existing nodes with new -> continue();
            if (minDist == BIG_VALUE)
            {
                continue;
            }
            Qnode q_near = nodes[minIndex];
            // set new coordinate, dist between 2 node should be < EPS
            Qnode q_new = calculateNewCoord(q_rand, q_near, minDist, EPS);
            q_new.setCost(q_new.distanceTo(q_near) + q_near.getCost());
            q_new.setParent(minIndex);
            //insert new node to all nodes
            nodes.push_back(q_new);
            //draw new node
            points_.points.push_back(q_new.intoPoint3());
            line_list_.points.push_back(nodes[q_new.getParent()].intoPoint3());
            line_list_.points.push_back(q_new.intoPoint3());
        }

        //add and draw goal point
        int minIndex = BIG_VALUE;
        double minDist = BIG_VALUE;
        for (int j = 0; j < nodes.size(); j++)
        {
            double tempDist = nodes[j].distanceTo(q_goal);
            if (tempDist < minDist)
            {
                minDist = tempDist;
                minIndex = j;
            }
        }
        q_goal.setCost(minDist + nodes[minIndex].getCost());
        q_goal.setParent(minIndex);
        points1_.points.push_back(q_goal.intoPoint3());
        line_list_.points.push_back(nodes[q_goal.getParent()].intoPoint3());
        line_list_.points.push_back(q_goal.intoPoint3());

        //draw final path and add in route
        while (q_goal.getParent() != -1) // index root is -1
        {
            line_final_.points.push_back(q_goal.intoPoint3());
            currentPath_.push_back(q_goal.getCoord());
            q_goal = nodes[q_goal.getParent()];

        }
        line_final_.points.push_back(nodes[0].intoPoint3());
        currentPath_.push_back(nodes[0].getCoord());

//        pub_.publish(output);

        publishMarker();
        clearMarker();
    
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



    bool checkColision(geometry_msgs::Vector3 startPosition, geometry_msgs::Vector3 semiGoal, octomap::point3d* rayEnd)
    {
        // sensing obstacles in safety value
        vector<octomap::point3d> boundaryAr(5);
        int size = 0;
        double halfW = double(QUADROTOR_SPAN) / 2;
        double halfH = double(QUADROTOR_HEIGHT) / 2;

        boundaryAr.at(size++) = point3d(startPosition.x, startPosition.y, startPosition.z);
        boundaryAr.at(size++) = point3d(startPosition.x + halfW, startPosition.y + halfW, startPosition.z);
        boundaryAr.at(size++) = point3d(startPosition.x - halfW, startPosition.y - halfW, startPosition.z);
        boundaryAr.at(size++) = point3d(startPosition.x + halfW, startPosition.y, startPosition.z + halfH);
        boundaryAr.at(size++) = point3d(startPosition.x - halfW, startPosition.y, startPosition.z - halfH);

        double dx = semiGoal.x - startPosition.x;
        double dy = semiGoal.y - startPosition.y;
        double dz = semiGoal.z - startPosition.z;

        octomap::point3d direction(dx, dy, dz);


        // if bottom boundary intersect with obstackles near MAV
        if (curPos_.z < DEVIATE)
        {
            size-=1;
        }
        // check intersection with safety value
        double maxRange = distance3d(dx, dy, dz) + DEVIATION*2;
        octomap::point3d rayEndTemple;
        for (int i = 0; i < size; i++)
        {
//            bool isIntersect = octree_->castRay(boundaryAr.at(i), direction, *rayEnd, false, maxRange);
            bool isIntersect = octree_->castRay(boundaryAr.at(i), direction, rayEndTemple);
            if (isIntersect)
            {
                point3d intersection;
                isIntersect = octree_->getRayIntersection(boundaryAr.at(i), direction, rayEndTemple, intersection);
//                rayEnd->x() = rayEndTemple.x();
//                rayEnd->y() = rayEndTemple.y();
//                rayEnd->z() = rayEndTemple.z();
//TODO return rayEnd
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
        line_final_.color.r = 1.0;
        line_final_.color.a = 1.0;
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
    ros::Publisher marker_pub_;
    ros::Subscriber sub_;
    ros::Subscriber subDestiny_;
    ros::Subscriber subOctomap_;
    ros::Subscriber subFinish_;

    geometry_msgs::Vector3 curPos_;
    geometry_msgs::Vector3 orient_;
    geometry_msgs::Vector3 goal_;
    geometry_msgs::Vector3 nextPosition_;

    visualization_msgs::Marker points_;
    visualization_msgs::Marker points1_;
    visualization_msgs::Marker line_strip_;
    visualization_msgs::Marker line_final_;
    visualization_msgs::Marker line_list_;

    octomap::OcTree* octree_;

    std::vector<octomap::point3d> currentPath_;



};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
    //Initiate ROS
    ros::init(argc, argv, "genIntermidiatePoint");


    //Create an object of class SubscribeAndPublish that will take care of everything
    SubscribeAndPublish SAPObject;

    ros::spin();

    return 0;
}
