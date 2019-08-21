#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <sstream>
#include "outlier_removal.h"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl_conversions/pcl_conversions.h>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

namespace velodyne 
{
		OutlierRemoval::OutlierRemoval(ros::NodeHandle nh, ros::NodeHandle private_nh) 
				: topic_name_ ("No topic specified") 
		{
			priv_nh_ = private_nh;
			
			priv_nh_.getParam("topic_name", topic_name_);
			ROS_INFO("Topic Name Subscribed To: %s", topic_name_.c_str());

			pub_downsample_ = nh.advertise<sensor_msgs::PointCloud2>("filtered_pcd", 10);
			ROS_INFO("Set up publisher for outlier removal...");

		};

		void OutlierRemoval::outlierCallback(const sensor_msgs::PointCloud2::ConstPtr &input)
		{

			// Setting up pclinput cloud to convert to, the filtered pcl cloud, and the output 
			// PointCloud2
			ROS_INFO("Point Cloud Size Before Outlier Removal: %f", float(input->width)); 
			pcl::PointCloud<pcl::PointXYZ>::Ptr 
					cloud(new pcl::PointCloud<pcl::PointXYZ>()), 
					cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>());
			pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
			sensor_msgs::PointCloud2::Ptr output_cloud(new sensor_msgs::PointCloud2());

			// Converting from PointCloud2 to PCL::PointCloud PointXYZ
			pcl::fromROSMsg(*input, *cloud);

			// Statistical Outlier Removal
			sor.setInputCloud(cloud);
			sor.setMeanK(10);
			sor.setStddevMulThresh(0.5);
			sor.filter(*cloud_filtered);

			// Converting back to sensor_msgs/PointCloud2 format
			pcl::toROSMsg(*cloud_filtered, *output_cloud);
			output_cloud->header.stamp = ros::Time::now();
			// Publishing cloud
			pub_downsample_.publish(output_cloud);

			ROS_INFO("Point Cloud Size AFTER Outlier Removal: %f", float(output_cloud->width)); 
		}
}; // namespace


