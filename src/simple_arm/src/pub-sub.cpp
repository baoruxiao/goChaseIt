#include <ros/ros.h>

class SubscribeAndPublish {
public:
  SubscribeAndPublish() {
  	pub_ = n_.advertise<PUBLISHED_MESSAGE_TYPE>("/published_topic", 1);
    
    sub_ = n_.subscribe("/subscribed_topic", 1, &SubscribeAndPublish::callback, this);
  }
  
  void callback(const SUBSCRIBED_MESSAGE_TYPE& input) {
  	PUBLISHED_MESSAGE_TYPE output;
	// ..., do something with the input and generate the output ...
    pub_.publish(output);
  }
private:
  ros::NodeHandle n_;
  ros::Publisher pub_;
  ros::Subscriber sub_;
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "subscribe_and_publish");
  
  	SubscribeAndPublish SAPObject;
  
  	ros::spin();
  
  	return 0;
}