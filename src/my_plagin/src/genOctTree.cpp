#include <iostream>
#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <octomap_msgs/conversions.h>
#include <octomap_msgs/Octomap.h>

const float res = 0.1;

void action(const octomap_msgs::Octomap msg)
{

 	//octomap_msgs::fullMapToMsg(tree, msg);
  octomap::AbstractOcTree* absTree;
  absTree = octomap_msgs::fullMsgToMap(msg);
  // Create Octomap
  octomap::OcTree* octree = dynamic_cast<octomap::OcTree*>(absTree);
  //octree->writeBinary("simple_tree.bt");
  for(octomap::OcTree::tree_iterator it =octree->begin_tree(), end = octree->end_tree();
      it!= end;
      it++)
  {
		 //manipulate node, e.g.:
		std::cout << "_____________________________________"<<std::endl;
		std::cout << "Node center: " << it.getCoordinate() << std::endl;
		std::cout << "Node size: " << it.getSize() << std::endl;
		std::cout << "Node depth: "<< it.getDepth() << std::endl;
		std::cout << "Is Leaf : "<< it.isLeaf()<< std::endl;
		std::cout << "_____________________________________"<<std::endl;
	}
  std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||| "<< std::endl;
}



int main (int argc, char **argv)
{
  ros::init (argc, argv, "OctViewer");
  ros::NodeHandle n;
	uint32_t queue_size = 1;

	ros::Subscriber sub = n.subscribe<octomap_msgs::Octomap>("/octomap_full", queue_size, action);

  ros::spin();

  return 0;
}
