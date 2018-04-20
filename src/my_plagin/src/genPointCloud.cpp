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
#include <pcl/filters/voxel_grid.h>
#include <pcl/point_cloud.h>
#include <deque>

using namespace octomap;

const float res = 0.1;
ros::Publisher pub;

void cloud_cb (const sensor_msgs::PointCloud2ConstPtr& input)
{
  sensor_msgs::PointCloud2 output;
  pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2;
  pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
  pcl::PCLPointCloud2 cloud_filtered;
  // Do data processing here…
  pcl_conversions::toPCL(*input, *cloud);
  pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
  sor.setInputCloud (cloudPtr);
  sor.setLeafSize(0.05,0.05,0.05);
  sor.filter (cloud_filtered);
  pcl_conversions::fromPCL(cloud_filtered, output);
  // Publish the data.
  pub.publish (output);
}



int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  // Subscribe on kinect
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe<sensor_msgs::PointCloud2>("camera/depth/points",
                                                               1, cloud_cb);
  // Publish Pointcloud2
  pub = n.advertise<sensor_msgs::PointCloud2> ("KinectFilter", 1);

  ros::spin();
  return 0;
}
