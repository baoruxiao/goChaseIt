#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

using std::cout;
using std::endl;

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ROS_INFO_STREAM("Moving towards the ball");
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!client.call(srv)) {
      ROS_ERROR("Failed to call service drive_robot");
    }
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    unsigned int width = img.width;
    int white_pixel = 255;
    std::vector<unsigned> pos_xs = {};
    for (unsigned i = 0; i < img.height; i++) {
      for (unsigned j = 0; j < img.step; j++) {
        cout << (int)img.data[i*img.step+j] << endl;
        if ((int)img.data[i*img.step+j] == white_pixel) pos_xs.push_back(j);
      }
    }
    cout << "bp" << endl;
    if (pos_xs.size() == 0) return;
    unsigned pos_x_mean = std::accumulate(pos_xs.begin(), pos_xs.end(), 0.0)/width;
    if (pos_x_mean < width / 3) {
      drive_robot(0.5, 0.5);
    } else if (pos_x_mean < 2 * width / 3) {
      drive_robot(0.5, 0.0);
    } else {
      drive_robot(0.5, -0.5);
    }
    return;
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
