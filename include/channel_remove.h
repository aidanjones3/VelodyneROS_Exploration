#ifndef CHANNEL_REMOVE_H
#define CHANNEL_REMOVE_H

#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <sensor_msgs/PointCloud2.h>
#include <sstream>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <sensor_msgs/point_cloud2_iterator.h>


namespace velodynetest
{
	class ChannelRemove 
	{
	public:
		ChannelRemove(ros::NodeHandle nh, ros::NodeHandle private_nh);
		~ChannelRemove() {}
	
		void downsample(const sensor_msgs::PointCloud2::ConstPtr &msg);

		ros::NodeHandle priv_nh_;
		std::string topic_name_;
	private:
		// Publisher for manipulated point cloud data
		ros::Publisher pub_;
		pcl::PointCloud<pcl::PointXYZ> filtered_cloud_;
		void publishPointCloud();
	};
}; // namespace

#endif /* CHANNEL_REMOVE_H */
