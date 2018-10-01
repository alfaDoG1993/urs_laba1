#include <ros/ros.h>
#include "std_msgs/Bool.h"                         
#include <sstream>
#include <iostream>

ros::Publisher messege_publisher;
ros::Subscriber messege_subscriber;

std::string output_topic_name;
std::string input_topic_name;

int messege_num = 0;
bool first_messege = false;
bool get_new_messege = false;  // Флаг для публикации цитаты
const double frecuency = 10.0;  // Частота работы узла в Гц
bool messege = false;       // Номер пришедшего сообщения

void citation_info(const std_msgs::Bool::ConstPtr& msg){
  messege = msg->data;
  get_new_messege = true;
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "publisher");
	ros::NodeHandle n;
	n.param<std::string>("out", output_topic_name, "messege");
	 
	messege_publisher = n.advertise<std_msgs::Bool>(output_topic_name, 1);
	messege_subscriber = n.subscribe<std_msgs::Bool>(input_topic_name,1,&citation_info);
	
	ros::Rate loop_rate(frecuency);

	while (ros::ok()) {
		if (get_new_messege == true)
    		{	
			if (messege_num == 0)
			{
				messege_num += 1;
				first_messege = messege;
				get_new_messege = false;
			}
			std_msgs::Bool ans;
			ans = first_messege^messege
			messege_publisher.publish(ans);
			get_new_messege = false;
		}
		ros::spinOnce();
    		loop_rate.sleep();
	}
	return 0;
}








