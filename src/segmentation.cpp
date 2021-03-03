#include <ros/ros.h>
#include <sstream>
#include <iostream>
#include "segmentation.h"

typedef pcl::PointCloud<pcl::PointXYZRGB> PCLCloud;

namespace velodynetest {

	Segmentation::Segmentation(ros::NodeHandle nh, ros::NodeHandle private_nh)
		: topic_name_("No subscriber topic specified")
	{
		priv_nh_ = private_nh;

		priv_nh_.getParam("topic_name", topic_name_);
		ROS_INFO("Topic Name Subscribed To: %s", topic_name_.c_str());

		pub_ = nh.advertise<sensor_msgs::PointCloud2>("segmented_point_cloud", 10);
		ROS_INFO("Set up publisher...");
	}

	void Segmentation::difference_of_normals_segmentation(const sensor_msgs::PointCloud2::ConstPtr &msg){
		// Convert to pcl cloud...
		pcl::PCLPointCloud2 *cloud = new pcl::PCLPointCloud2;
		pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
		pcl_conversions::toPCL(*msg, *cloud);

		// Convert to XYZRGB cloud...
		PCLCloud::Ptr full_cloud (new PCLCloud);
		pcl::fromPCLPointCloud2(*cloud, *full_cloud);

		// Create a search tree, use KDTree for non-organized data
		pcl::search::Search<pcl::PointXYZRGB>::Ptr tree;
		if(full_cloud->isOrganized()){
			tree.reset(new pcl::search::OrganizedNeighbor<pcl::PointXYZRGB>());
		} else {
			tree.reset(new pcl::search::KdTree<pcl::PointXYZRGB>(false));
		}

		// Set input pointcloud for the search tree
		tree->setInputCloud(full_cloud);

		// Compute the normals
		//
	}





};
