#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <sstream>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/filters/conditional_removal.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/search/organized.h>
#include <sensor_msgs/point_cloud2_iterator.h>

namespace velodynetest{

	class Segmentation
	{
	 public:
		 Segmentation(ros::NodeHandle nh, ros::NodeHandle private_nh);
		 ~Segmentation() {};

		 void difference_of_normals_segmentation(const sensor_msgs::PointCloud2::ConstPtr &msg);

		 ros::NodeHandle priv_nh_;
		 std::string topic_name_;
	 private:
		 ros::Publisher pub_;
		 pcl::PCLPointCloud2 segmented_cloud_;
		 void publishPointCloud();
	};
}; // namespace
