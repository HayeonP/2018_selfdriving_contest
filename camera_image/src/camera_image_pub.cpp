#include "ros/ros.h"
#include "opencv2/opencv.hpp"
#include "image_transport/image_transport.h"
#include "cv_bridge/cv_bridge.h"

// argv[0] : camera_number, argv[1] : frequency
int main(int argc, char **argv)
{
    if(argc!=3){
        ROS_INFO("camera_image_pub [camera_number] [frequency]");
        return 1;
    }
    ros::init(argc, argv, "camera_image_pub");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("camera/image",1);

    int camera_number = atoi(argv[1]);
    int frequency = atoi(argv[2]);
    ROS_INFO("camera_number : %d / frequency : %d",camera_number, frequency);
    if(!frequency){
        ROS_INFO("Frequency is number more than 0");
        return 1;
    }
    cv::VideoCapture cap(camera_number);
    if(!cap.isOpened()) {
        ROS_INFO("Please check camera number");
        return 1;
    }
    cv::Mat frame;
    sensor_msgs::ImagePtr msg;

    ros::Rate loop_rate(frequency);
    
    ROS_INFO("Start publishing");
    while(nh.ok()){
        cap >> frame;

        if(!frame.empty()){
            msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
            pub.publish(msg);
            int ckey = cv::waitKey(1);
            if(ckey == 27)break;
        }
            
        loop_rate.sleep();
    }
    ROS_INFO("Publishing done");
    return 0;
}
