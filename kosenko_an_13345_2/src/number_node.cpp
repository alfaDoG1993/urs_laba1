#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <math.h>

ros::Publisher int_publisher;
ros::Subscriber float_subscriber;

float current_number;

void int_callback(const std_msgs::Float32 &msg){
	current_number = msg.data;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "numbers_node");
	ros::NodeHandle nh ("~"); 

	ROS_INFO("Starting node ...");
	
	int_publisher = nh.advertise<std_msgs::Int32>("rounded",1);
	float_subscriber = nh.subscribe("pull_up", 1, int_callback);
	ros::Rate r(10);
	
	while(ros::ok())
	{
		std_msgs::Int32 out_msg;
		out_msg.data = (int)round(current_number);
		int_publisher.publish(out_msg);
		ros::spinOnce();
		r.sleep();
	}

	return 0;
		
}
