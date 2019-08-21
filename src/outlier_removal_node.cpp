#include <ros/ros.h>
#include <sstream>
#include "outlier_removal.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "outlier_removal");
	ros::NodeHandle nh;
	ros::NodeHandle private_nh("~");

	velodyne::OutlierRemoval outlier(nh, private_nh);
	
	ros::Subscriber sub = nh.subscribe(outlier.topic_name_, 10, 
					&velodyne::OutlierRemoval::outlierCallback, &outlier);


	ros::spin();

	return 0;


}
