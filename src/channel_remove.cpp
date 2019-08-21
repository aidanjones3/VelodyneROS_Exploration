#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud2_iterator.h>
#include <sstream>
#include <boost/foreach.hpp>

#include "channel_remove.h"


namespace velodynetest
{
	ChannelRemove::ChannelRemove(ros::NodeHandle nh, ros::NodeHandle private_nh) 
		: topic_name_ ("no topic specificied")
	{
		priv_nh_ = private_nh;

		priv_nh_.getParam("topic_name", topic_name_);
		ROS_INFO("Topic Name Subscribe To: %s", topic_name_.c_str());

		pub_ = nh.advertise<sensor_msgs::PointCloud2>("removed_channels", 10);
		ROS_INFO("Set up publisher...");
	
	};


	void ChannelRemove::downsample(const sensor_msgs::PointCloud2::ConstPtr &msg)
	{
	    	// Everytime we get a new message, we will create a corresponding one 
            sensor_msgs::PointCloud2 points_msg;
            points_msg.header.stamp = ros::Time::now();
			points_msg.header.frame_id = "velodyne";
            points_msg.height = 1;
            // Setting it be the same size will make some points invalid, but thats okay 
            // as long as they are checked for later on
            points_msg.width = msg->width;
            points_msg.point_step = msg->point_step;
            points_msg.row_step = msg->row_step;
            points_msg.is_dense = false;

			// Allows us to modify point strcuture, and resizes the data structure according
			// to given width, ehight and fields
            // Iterator to Access Fields within the message we want to publish
			sensor_msgs::PointCloud2Modifier pcd_modifier(points_msg);
			pcd_modifier.setPointCloud2Fields(5, 
							"x", 1, sensor_msgs::PointField::FLOAT32,
							"y", 1, sensor_msgs::PointField::FLOAT32,
							"z", 1, sensor_msgs::PointField::FLOAT32,
							"intensity", 1, sensor_msgs::PointField::FLOAT32,
							"ring", 1, sensor_msgs::PointField::UINT16);
			
			sensor_msgs::PointCloud2Iterator<float> iter_x_new(points_msg, "x");
            sensor_msgs::PointCloud2Iterator<float> iter_y_new(points_msg, "y");
            sensor_msgs::PointCloud2Iterator<float> iter_z_new(points_msg, "z");
            sensor_msgs::PointCloud2Iterator<float> iter_intensity_new(points_msg, "intensity");	
			sensor_msgs::PointCloud2Iterator<uint16_t> iter_ring_new(points_msg, "ring");


            // Iterating through received message, checking to see which laser the point
            // belongs to; if it belongs to ring 1 or 2, we know to not pass it along 
            sensor_msgs::PointCloud2ConstIterator<float> iter_x(*msg, "x"); 
		    sensor_msgs::PointCloud2ConstIterator<float> iter_intensity(*msg, "intensity");	
            for(sensor_msgs::PointCloud2ConstIterator<uint16_t> it(*msg, "ring"); 
                    it != it.end(); ++it, ++iter_x, ++iter_intensity, ++iter_x_new, ++iter_y_new, 
                                ++iter_z_new, ++iter_intensity_new, ++iter_ring_new)
            {       
				float x = iter_x[0];
				float y = iter_x[1];
				float z = iter_x[2];
				float intensity = iter_x[3];	
                int ring_num = int(it[0]);

				//for(; iter_x_new != iter_x_new.end(); ++iter_x_new, ++iter_y_new, 
				//				++iter_z_new, ++iter_intensity_new, ++iter_ring_new)
				//{
				/*
				std::cout << "Ring #: " << ring_num << std::endl;
				std::cout << "X:	" << iter_x[0] << std::endl;
				std::cout << "Y:	" << iter_x[1] << std::endl;
				std::cout << "Z:	" << iter_x[2] << std::endl;
				std::cout << "I:	" << iter_intensity[0] << std::endl;
				*/
				//if(ring_num != 1 && ring_num != 2)		
				{
					// Passing data to new PointCloud2 message
					*iter_x_new = x;
					*iter_y_new = y;
					*iter_z_new = z;
					*iter_intensity_new = intensity;
					*iter_ring_new = ring_num;
				}
				//else
				{
					continue;
				}	
            }

			pub_.publish(points_msg);
			static_transformStamped.header.stamp = ros::Time::now();
			static tf2_ros::StaticTransformBroadcaster static_broadcaster;
			static_broadcaster.sendTransform(static_transformStamped);
	}


	void ChannelRemove::setupTransform()
	{	
  		static_transformStamped.header.frame_id = "map";
  		static_transformStamped.child_frame_id = "velodyne";
  		static_transformStamped.transform.translation.x = 0;
  		static_transformStamped.transform.translation.y = 0;
  		static_transformStamped.transform.translation.z = 0;
		static_transformStamped.transform.rotation.x = 0;
  		static_transformStamped.transform.rotation.y = 0;
 		static_transformStamped.transform.rotation.z = 0;
  		static_transformStamped.transform.rotation.w = 1;
	}





}; //namespace


