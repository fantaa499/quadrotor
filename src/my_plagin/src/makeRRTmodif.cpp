//
// Created by anton on 11.05.18.
//

#include <iostream>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "../include/my_plagin/my_library.h"
#include <cmath>

#define DEVIATE 0.5
#define X_MAX 20
#define Y_MAX 20
#define Z_MAX 20
#define RADIUS 10
#define NUM_NODES 1000
#define BIG_VALUE 9999
#define EPS 2
// 67 dgr
#define ANGLE_R 1.16937




int main( int argc, char** argv )
{
    ros::init(argc, argv, "RRTmodif");
    ros::NodeHandle n;
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);

    std::ofstream file;
    file.open("/home/anton/fileWithNumb.txt");

    ros::Rate r(30);

    float f = 0.0;
    while (ros::ok())
    {

        visualization_msgs::Marker points, points1, line_strip, line_list, line_final;
        points1.header.frame_id = points.header.frame_id = line_strip.header.frame_id = line_list.header.frame_id  = line_final.header.frame_id = "map";
        points1.header.stamp = points.header.stamp = line_strip.header.stamp = line_list.header.stamp = line_final.header.stamp = ros::Time::now();
        points1.ns = points.ns = line_strip.ns = line_list.ns = line_final.ns = "points_and_lines";
        points1.action = points.action = line_strip.action = line_list.action = line_final.action = visualization_msgs::Marker::ADD;
        //points1.pose.orientation.w = points.pose.orientation.w = line_strip.pose.orientation.w = line_list.pose.orientation.w = line_final.pose.orientation.w = 1.0;


        points.id = 0;
        line_strip.id = 1;
        line_list.id = 2;
        line_final.id = 3;
        points1.id = 4;

        points.type = visualization_msgs::Marker::POINTS;
        points1.type = visualization_msgs::Marker::POINTS;
        line_strip.type = visualization_msgs::Marker::LINE_STRIP;
        line_list.type = visualization_msgs::Marker::LINE_LIST;
        line_final.type = visualization_msgs::Marker::LINE_STRIP;


        // POINTS markers use x and y scale for width/height respectively
        points.scale.x = 0.2;
        points.scale.y = 0.2;
        points1.scale.x = 0.2;
        points1.scale.y = 0.2;

        // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
        line_strip.scale.x = 0.1;
        line_list.scale.x = 0.1;
        line_final.scale.x = 0.2;


        // Points are green
        points.color.g = 1.0f;
        points.color.a = 1.0;

        points1.color.r = 1.0;
        points1.color.b = 1.0;
        points1.color.a = 1.0;

        // Line strip is blue
        line_strip.color.b = 1.0;
        line_strip.color.a = 1.0;

        // Line list is red
        line_list.color.r = 1.0;
        line_list.color.a = 1.0;

        line_final.color.b = 1.0;
        line_final.color.a = 1.0;

        octomap::point3d goal = octomap::point3d(5, 5, 5);

        Qnode q_start = Qnode();
        q_start.setParent(-1);
        Qnode q_goal = Qnode(goal); // fix goal

        std::vector<Qnode> nodes;
        nodes.push_back(q_start);
        //draw start node
        points1.points.push_back(q_start.intoPoint3());
        int i = 0;
//        for (int i = 0; i < NUM_NODES; i++)
        
        while (std::abs(nodes.back().getCoord().x() - q_goal.getCoord().x()) > 1 ||
               std::abs(nodes.back().getCoord().y() - q_goal.getCoord().y()) > 1 ||
               std::abs(nodes.back().getCoord().z() - q_goal.getCoord().z()) > 1)
        {
            i += 1;
            // break if goal node is already reached
            if (nodes.back().getCoord() == q_goal.getCoord())
            {
                break;
            }

            //create random node
            std::srand(i * unsigned(std::time(0)*i));
//            octomap::point3d randomVarible (-10 + double (std::rand())/RAND_MAX*X_MAX,
//                                            -10 + double (std::rand())/RAND_MAX*Y_MAX,
//                                            -10 + double (std::rand())/RAND_MAX*Z_MAX);
            double x0 = 0;
            double y0 = 0;
            double z0 = 0;

            double dx = goal.x() - x0;
            double dy = goal.y() - y0;
            double dz = goal.z() - z0;

//            octomap::point3d direction(dx, dy, dz);
            double angle = findAngle2d(dx, dy);
            double randomAngle = double(std::rand())/RAND_MAX*ANGLE_R*2;
            double randomCoord = double(std::rand())/RAND_MAX*RADIUS;
            octomap::point3d randomVar (x0 + randomCoord*cos(ANGLE_R + angle - randomAngle),
                                        y0 + randomCoord*sin(ANGLE_R + angle - randomAngle),
                                        -RADIUS + double(std::rand())/RAND_MAX*2*RADIUS);
            Qnode q_rand = Qnode(randomVar);

            // pick the closest node from existing list to branch out form
            int minIndex = BIG_VALUE;
            double minDist = BIG_VALUE;
            for (int j = 0; j < nodes.size(); j++)
            {
                double tempDist = nodes[j].distanceTo(q_rand);
                octomap::point3d* rayEnd;
//                    if (tempDist < minDist && !checkColision(nodes[j].getCoordVec3(), q_rand.getCoordVec3(), rayEnd))
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
            // determinate parent new node
//            Qnode q_min = Qnode(q_near.getCoord(), q_new.getCost(), 0);
//            for (int j = 0; j < nodes.size(); j++)
//            {
//                double newCost = q_min.distanceTo(nodes[j]) + nodes[j].getCost();
//                if (newCost <= q_min.getCost())
//                {
//                    q_min.setCoord(nodes[j].getCoord());
//                    q_min.setCost(newCost);
//                    q_min.setParent(j);
//                }
//            }
//            q_new.setCost(q_min.getCost());
//            q_new.setParent(q_min.getParent());
            //insert new node to all nodes
            nodes.push_back(q_new);
            //draw new node
            points.points.push_back(q_new.intoPoint3());
            line_list.points.push_back(nodes[q_new.getParent()].intoPoint3());
            line_list.points.push_back(q_new.intoPoint3());
        }

        //add and draw goal point
        int minIndex = BIG_VALUE;
        double minDist = BIG_VALUE;
        for (int i = 0; i < nodes.size(); i++)
        {
            double tempDist = nodes[i].distanceTo(q_goal);
            if (tempDist < minDist)
            {
                minDist = tempDist;
                minIndex = i;
            }
        }
        q_goal.setCost(minDist + nodes[minIndex].getCost());
        q_goal.setParent(minIndex);
        points1.points.push_back(q_goal.intoPoint3());
        line_list.points.push_back(nodes[q_goal.getParent()].intoPoint3());
        line_list.points.push_back(q_goal.intoPoint3());

        //draw final path
        while (q_goal.getParent() != -1)
        {
            line_final.points.push_back(q_goal.intoPoint3());
            q_goal = nodes[q_goal.getParent()];
        }
        line_final.points.push_back(nodes[0].intoPoint3());

        marker_pub.publish(line_list);
        marker_pub.publish(line_final);
        marker_pub.publish(points);
        marker_pub.publish(points1);
        std::cout << i << std::endl;
        if (file.is_open())
        {
            file << i << std::endl;
        }
        ros::Duration(1).sleep();


    }
    file.close();
}