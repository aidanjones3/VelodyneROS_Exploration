#include "channel_remove.h"
#include "outlier_removal.h"
void channelCallback(const sensor_msgs::PointCloud2 &msg)
{
	ROS_INFO("I received a PointCloud2 Message");
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "velodyne_exploration");

	ros::NodeHandle nh;
	ros::NodeHandle private_nh("~");

	velodynetest::ChannelRemove channelRemove(nh, private_nh);
	ros::Subscriber sub = nh.subscribe(channelRemove.topic_name_, 10, 
			&velodynetest::ChannelRemove::downsample, &channelRemove);
	
	velodynetest::OutlierRemoval outlierRemoval(nh, private_nh);
	ros::Subscriber outlier_sub = nh.subscribe(outlierRemoval.topic_name_, 10, 
					   	   &velodynetest::OutlierRemoval::filter, 
					   	   &outlierRemoval);
	ros::spin();

	return 0;
}




