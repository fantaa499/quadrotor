#include <iostream>

#include "ros/ros.h"
#include <sensor_msgs/PointCloud2.h>

#include <octomap/octomap.h>
#include <octomap/OcTree.h>

#include <octomap_msgs/conversions.h>
#include <octomap_msgs/Octomap.h>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/conversions.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/filters/filter.h>
#include <deque>

using namespace octomap;

const float res = 0.1;




void generateOctree(const sensor_msgs::PointCloud2 msg)
{
  // Create Octomap
  OcTree tree(res);
  // Load point
  pcl::PCLPointCloud2 cloud;
	pcl_conversions::toPCL(msg,cloud);
	pcl::PointCloud<pcl::PointXYZ> pcl_pc;
  pcl::fromPCLPointCloud2(cloud,pcl_pc);
  // filter point cloud for NAN
  std::vector<int> nan_indices;
  pcl::removeNaNFromPointCloud(pcl_pc,pcl_pc,nan_indices);
	octomap::Pointcloud oct_pc;
  octomap::point3d origin(0.0f,0.0f,0.0f);
  //adding point cloud to octomap
  for(int i = 0;i<pcl_pc.points.size();i++)
  {
    oct_pc.push_back((float) pcl_pc.points[i].x,(float) pcl_pc.points[i].y,(float) pcl_pc.points[i].z);
  }
  tree.insertPointCloud(oct_pc,origin,-1,false,false);

  // ROS_INFO_STREAM ("generating example map" );
  //
  // OcTree tree (0.1);  // create empty tree with resolution 0.1
  //
  //
  // // insert some measurements of occupied cells
  //
  // for (int x=-20; x<20; x++) {
  //   for (int y=-20; y<20; y++) {
  //     for (int z=-20; z<20; z++) {
  //       point3d endpoint ((float) x*0.05f, (float) y*0.05f, (float) z*0.05f);
  //       tree.updateNode(endpoint, true); // integrate 'occupied' measurement
  //     }
  //   }
  // }
  //
  // // insert some measurements of free cells
  //
  // for (int x=-30; x<30; x++) {
  //   for (int y=-30; y<30; y++) {
  //     for (int z=-30; z<30; z++) {
  //       point3d endpoint ((float) x*0.02f-1.0f, (float) y*0.02f-1.0f, (float) z*0.02f-1.0f);
  //       tree.updateNode(endpoint, false);  // integrate 'free' measurement
  //     }
  //   }
  // }
  //
  //
  // ROS_INFO_STREAM("performing some queries:" );
  //
  // point3d query (0., 0., 0.);
  // OcTreeNode* result = tree.search (query);
  // print_query_info(query, result);
  //
  // query = point3d(-1.,-1.,-1.);
  // result = tree.search (query);
  // print_query_info(query, result);
  //
  // query = point3d(1.,1.,1.);
  // result = tree.search (query);
  // print_query_info(query, result);
  //
  //
  //
  tree.writeBinary("simple_tree.bt");
  // ROS_INFO_STREAM("wrote example file simple_tree.bt"  );
  // ROS_INFO_STREAM("now you can use octovis to visualize: octovis simple_tree.bt");
  // ROS_INFO_STREAM ("Hint: hit 'F'-key in viewer to see the freespace"  );
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;
  ros::Subscriber sub  = n.subscribe<sensor_msgs::PointCloud2>("camera/depth/points",
                                                               1000, generateOctree);

  ros::spin();


  return 0;
}
