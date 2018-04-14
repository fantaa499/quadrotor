#include "ros/ros.h"
#include "std_msgs/String.h"

#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>

#include <octomap/octomap.h>
#include <octomap/OcTree.h>

// geometry_msgs::Twist cmd_command ()
// {
//
// }

using namespace octomap;

void print_query_info(point3d query, OcTreeNode* node) {
  if (node != NULL) {
    ROS_INFO_STREAM("occupancy probability at " << query << ":\t " << node->getOccupancy() );
      }
  else
    ROS_INFO_STREAM("occupancy probability at " << query << ":\t is unknown" );
}


int main(int argc, char **argv)
{


  ROS_INFO_STREAM ("generating example map" );

  OcTree tree (0.1);  // create empty tree with resolution 0.1


  // insert some measurements of occupied cells

  for (int x=-20; x<20; x++) {
    for (int y=-20; y<20; y++) {
      for (int z=-20; z<20; z++) {
        point3d endpoint ((float) x*0.05f, (float) y*0.05f, (float) z*0.05f);
        tree.updateNode(endpoint, true); // integrate 'occupied' measurement
      }
    }
  }

  // insert some measurements of free cells

  for (int x=-30; x<30; x++) {
    for (int y=-30; y<30; y++) {
      for (int z=-30; z<30; z++) {
        point3d endpoint ((float) x*0.02f-1.0f, (float) y*0.02f-1.0f, (float) z*0.02f-1.0f);
        tree.updateNode(endpoint, false);  // integrate 'free' measurement
      }
    }
  }


  ROS_INFO_STREAM("performing some queries:" );

  point3d query (0., 0., 0.);
  OcTreeNode* result = tree.search (query);
  print_query_info(query, result);

  query = point3d(-1.,-1.,-1.);
  result = tree.search (query);
  print_query_info(query, result);

  query = point3d(1.,1.,1.);
  result = tree.search (query);
  print_query_info(query, result);



  tree.writeBinary("simple_tree.bt");
  ROS_INFO_STREAM("wrote example file simple_tree.bt"  );
  ROS_INFO_STREAM("now you can use octovis to visualize: octovis simple_tree.bt");
  ROS_INFO_STREAM ("Hint: hit 'F'-key in viewer to see the freespace"  );

  ros::init(argc, argv, "talker");


  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);

  ros::Rate loop_rate(10);

  geometry_msgs::Twist velocity;



  while (ros::ok())
  {
    velocity.linear.x = 0;
    velocity.linear.y = 0;
    velocity.linear.z = 1.0;
    velocity.angular.x = 0;
    velocity.angular.y = 0;
    velocity.angular.z = 0;
    //std_msgs::String msg;

    //std::stringstream ss;
    //ss << "hello world " << count;
    //msg.data = ss.str();

    //ROS_INFO("%s", msg.data.c_str());


    chatter_pub.publish(velocity);

    ros::spinOnce();

    loop_rate.sleep();

  }


  return 0;
}
