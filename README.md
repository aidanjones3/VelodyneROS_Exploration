# Overview
This repo was used a way to get some more experience with the ROS velodyne
drivers and ROS in general. The objectives highlighted below were originally
a part of a coding challenge. At the time, I did not have the skill set to
complete in the alotted 12 hours. I am now much more comfortable in the ROS
environment, and wanted to prove to myself that I complete the challenge with
ease.

------
Objectives
-----
Given the `.bag` file of recorded ROS topics, create three runnable ROS nodes
that do the following:

1. Remove 2 channels of signals from the 16 channels of the Velodyne VLP16
2. Remove noise in the remaining point cloud
3. Detect upright line structures in the point cloud and visualize them in
   colors.

----
Implementation Overview
----
*Channel Removal*

The initial method is definitely a little over the top, but I wanted to fully
understand the `sensor_msgs/PointCloud2` topic type. Most of the functionality
lays within the callback function `downsample`. Every time a message is received
, a outgoing point cloud message is created, and all the necessary fields are
set (such as header, timestamp etc). The point cloud modifier sets the necessary
data fields (X, Y, Z, Intensity and Ring #) in the point cloud. Iterators are
instantiated that allowed me to loop through the points present in each message,
and if they don't belong to either beam 1 or beam 2, they are pushed into the
new point cloud. Afterwards, the point cloud is then published.

*Noise/Outlier Removal*



---
Downloading/Building
---
`cd /your/catkin_ws/src/`

Once you're in the right directory, clone this repo using the command below.

`git clone https://github.com/aidanjones3/VelodyneROS_Exploration.git`

The repo can be built by running the following command in your catkin_ws

`catkin_make`

----
Running the ROS Nodes
----

The ROS nodes can be run indiviually, as long as you have a topic with `sensor_msgs/PointCloud2` being published to it. The three seperate nodes can be ran with the commands below:

`rosrun velodyne_test velodyne_test _topic_name:="\velodyne_points"`

`rosrun velodyne_test outlier_removal _topic_name:="\velodyne_points"`

`rosrun velodyne_test objec_segmentation _topic_name:="\velodyne_points"`

Obviously, you can substitute the topic name of velodyne_points with the topic
name you wish to subscribe to.
