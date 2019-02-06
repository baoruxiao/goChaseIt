#include "ros/ros.h"

void process_image_callback(const sensor_msgs::Image img) {
   
}


int main(int argc, char** argv) {
  ros::init(argc, argv, "process_image");
  ros::NodeHandle n;

  client = n.serviceClient<>()

  ros::Subscriber sub = n.subscribe("rgb_camera/image_raw", 10, process_image_callback);

  ros:spin();

  return 0;
}
