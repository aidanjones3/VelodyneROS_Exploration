#include "ros/ros.h"
#include <sstream>
#include "outlier_removal.h"
#include <iostream>
#include <pcl_ros/point_cloud.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>

typedef pcl::PointCloud<pcl::PointXYZ> PCLCloud;
namespace velodynetest
{
	OutlierRemoval::OutlierRemoval(ros::NodeHandle nh, ros::NodeHandle private_nh)
		: topic_name_("No subscriber topic specified")
	{
		priv_nh_ = private_nh;

		priv_nh_.getParam("topic_name", topic_name_);
		ROS_INFO("Topic Name Subscribed To: %s", topic_name_.c_str());

		pub_ = nh.advertise<sensor_msgs::PointCloud2>("filtered_point_cloud", 10);
		ROS_INFO("Set up publisher...");
	};

	void OutlierRemoval::filter(const sensor_msgs::PointCloud2::ConstPtr &msg){
		// Convert to pcl cloud...
		pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2;
		pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
		pcl_conversions::toPCL(*msg, *cloud);

		// Perform the actual filtering
  		pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
  		sor.setInputCloud(cloudPtr);
  		sor.setLeafSize(0.1, 0.1, 0.1);
  		sor.filter(filtered_cloud_);

		// Convert to ROS data type
  		sensor_msgs::PointCloud2 output;
  		pcl_conversions::moveFromPCL(filtered_cloud_, output);

		// Publish the filtered cloud
		pub_.publish(output);
	};
}; // namespace
