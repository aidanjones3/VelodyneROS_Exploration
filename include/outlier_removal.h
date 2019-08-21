#ifndef OUTLIER_REMOVAL_H
#define OULTIER_REMOVAL_H

#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud2_iterator.h>
#include <sstream>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl_conversions/pcl_conversions.h>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

namespace velodyne {

		class OutlierRemoval
		{
		public:
			OutlierRemoval(ros::NodeHandle nh, ros::NodeHandle private_nh);
			
			~OutlierRemoval() {};
			
			void outlierCallback(const sensor_msgs::PointCloud2::ConstPtr &input);

			ros::NodeHandle priv_nh_;
			std::string topic_name_;


			private:
			ros::Publisher pub_downsample_;

		};
}; //namespace

#endif /* OUTLIER_REMOVAL_H */
