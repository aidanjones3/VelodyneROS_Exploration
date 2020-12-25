#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <sstream>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <sensor_msgs/point_cloud2_iterator.h>

namespace velodynetest
{
	class OutlierRemoval
	{
	 public:
		OutlierRemoval(ros::NodeHandle nh, ros::NodeHandle private_nh);
		~OutlierRemoval() {};

		void filter(const sensor_msgs::PointCloud2::ConstPtr &msg);

		ros::NodeHandle priv_nh_;
		std::string topic_name_;
	
	private:
		ros::Publisher pub_;
		pcl::PCLPointCloud2 filtered_cloud_;
		void publishPointCloud();
	};
}; //namespace
