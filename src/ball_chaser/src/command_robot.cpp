#include "ros/ros.h"
#include "ball_chaser/CommandRobot."



std::vector<float> clamp_at_boundaries() {

}


bool handle_safe_move_request(ball_chaser::CommandRobot::Request& req,
                              ball_chaser::CommandRobot::Response& res)
{
  ROS_INFO("CommandRobotRequest received - x:%1.2f, y:%1.2f, z:%1.2f,
    r:%1.2f, p:%1.2f, yaw:%1.2f", (float)req.linear[0], (float)req.linear[1],
    (float)req.linear[1], (float)req.angular[0], (float)req.angular[1],
    (float)req.angular[2]);

}


int main() {
  ros::init(argc, argv, "command_robot");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("command_robot", handle_safe_move_request);
  ROS_INFO("Ready to send robot command");

  ros::spin();

  return 0;
}
