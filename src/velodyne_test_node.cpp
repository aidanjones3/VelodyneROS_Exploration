#include <ros/ros.h>
#include <sstream>
#include "channel_remove.h"

void channelCallback(const sensor_msgs::PointCloud2 &msg)
{
	ROS_INFO("I received a PointCloud2 Message");
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "channel_downsampler");

	ros::NodeHandle nh;
	ros::NodeHandle private_nh("~");

	velodynetest::ChannelRemove channelRemove(nh, private_nh);		
	channelRemove.setupTransform();	
	ros::Subscriber sub = nh.subscribe(channelRemove.topic_name_, 10, 
			&velodynetest::ChannelRemove::downsample, &channelRemove);
	ros::spin();

	return 0;
}




