#include "ros/ros.h"
#include <sstream>
#include "channel_remove.h"
#include <iostream>
#include <pcl_ros/point_cloud.h>

typedef pcl::PointCloud<pcl::PointXYZ> PCLCloud;
namespace velodynetest
{
	ChannelRemove::ChannelRemove(ros::NodeHandle nh, ros::NodeHandle private_nh) 
		: topic_name_("no subscribe topic specificied") 
	{
		priv_nh_ = private_nh;

		priv_nh_.getParam("topic_name", topic_name_);
		ROS_INFO("Topic Name Subscribe To: %s", topic_name_.c_str());

		pub_ = nh.advertise<PCLCloud>("downsampled_point_cloud", 10);
		ROS_INFO("Set up publisher...");
	};

	void ChannelRemove::downsample(const sensor_msgs::PointCloud2::ConstPtr &msg){
		// Create iterators to go through input point cloud
		sensor_msgs::PointCloud2ConstIterator<int> iter_ring(*msg, "ring");
		sensor_msgs::PointCloud2ConstIterator<float> iter_x(*msg, "x");
		sensor_msgs::PointCloud2ConstIterator<float> iter_y(*msg, "y");
		sensor_msgs::PointCloud2ConstIterator<float> iter_z(*msg, "z");

		// Perform the downsample of channel data and add it to the PCL point cloud. 
		for(;iter_x != iter_x.end(); ++iter_x, ++iter_ring, ++iter_y, ++iter_z){
			if(*iter_ring != 1){
				pcl::PointXYZ point = pcl::PointXYZ(*iter_x, *iter_y, *iter_z);
				filtered_cloud_.push_back(point);
			}
		}

		// Publish the filtered point cloud
		pub_.publish(filtered_cloud_.makeShared());
		filtered_cloud_.clear();
	};

}; //namespace


