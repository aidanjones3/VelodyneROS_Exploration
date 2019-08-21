#ifndef CHANNEL_REMOVE_H
#define CHANNEL_REMOVE_H

#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud2_iterator.h>
#include <sstream>
#include <tf2_ros/static_transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>


namespace velodynetest
{
	class ChannelRemove 
	{
	public:
		ChannelRemove(ros::NodeHandle nh, ros::NodeHandle private_nh);
		~ChannelRemove() {};
	
		void downsample(const sensor_msgs::PointCloud2::ConstPtr &msg);
		void setupTransform();		

		ros::NodeHandle priv_nh_;
		std::string topic_name_;

		//static tf2_ros::StaticTransformBroadcaster static_broadcaster;
		geometry_msgs::TransformStamped static_transformStamped;

		//sensor_msgs::PointCloud2Iterator<float> iter_x_new, iter_y_new, 
		//		iter_z_new, iter_intensity_new;
		//ensor_msgs::PointCloud2Iterator<uint16_t> iter_ring_new;

	private:
		// Publisher for manipulated point cloud data
		ros::Publisher pub_;

	


		
	};
}; // namespace

#endif /* CHANNEL_REMOVE_H */
