#include <ros/ros.h>
#include "sensor_msgs/PointCloud2.h"
#include "geometry_msgs/PoseStamped.h"
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/octree/octree_search.h>
#include <pcl/ModelCoefficients.h>
#include <pcl_ros/io/pcd_io.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl_ros/segmentation/sac_segmentation.h>
#include <iostream>
#include <vector>
#include <ctime>

pcl::PointCloud<pcl::PointXYZ>::Ptr pc(new pcl::PointCloud<pcl::PointXYZ>);
sensor_msgs::PointCloud2 pc_out;

// void imageCallback(){

// }
void convert_image2cloud();

int main(int argc, char** argv){
  ros::init(argc,argv,"image2cloud");
  ros::NodeHandle nh;
  //ros::Subscriber image_reader = nh.subscrib
  ros::Publisher point_sender = nh.advertise<sensor_msgs::PointCloud2>("/lane_pc_out",10);
  ros::Rate loop_rate(10);

  //ros::Timer timer = nh.createTimeer(ros::Duration(0.1), boost::bind(&transform))?

  while(ros::ok())
  {
    ros::spinOnce();
    convert_image2cloud();
    point_sender.publish(pc_out);
  }

}

void convert_image2cloud(){
  pc->clear();

  // Create header
  std::string frame_id("image2cloud");
  pc->header.frame_id = frame_id;
  pc->header.seq = ros::Time::now.toNsec()/1e3;
  //PC->header.stamp = ;
  pc->is_dense = false;
  // PC->sensor_origin
  // PC->sensor_orientation

  pcl::PointCloud<pcl::PointXYZ>::iterator pc_iter = pc->begin();
  pcl::PointXYZ point;
  

  while(pc_iter != pc->end()){
    //point.x = ? point.y = ? point.z = ?
    pc->insert(pc_iter, point);
    ++pc_iter;
  }

  pcl::toROSMsg(*pc, pc_out);
  pc->clear();
}