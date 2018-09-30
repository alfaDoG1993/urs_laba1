#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include <sstream>
#include <vector>


ros::Publisher speed_publisher;
ros::Subscriber speed_subscriber;

std::string speed_out;
std::string speed_in;

geometry_msgs::Twist received_speed;

void speed_callback(const geometry_msgs::Twist &msg)
{
        received_speed = msg;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "speed_publisher_node");
    ros::NodeHandle nh("~");

    ROS_INFO("Starting speed_publisher_node...");

    nh.param<std::string>("output_speed_topic", speed_out, "speed_out");
    nh.param<std::string>("input_speed_topic", speed_in, "speed_in");

    speed_publisher =  nh.advertise<geometry_msgs::Twist>(speed_out, 1);
    speed_subscriber = nh.subscribe(speed_in, 1, speed_callback);
    ros::Rate r(10);

    ROS_INFO_STREAM("Send to the topic the int value of speed in meters per sec to сonvert it into miles per hour");

    while(ros::ok())
    {
        geometry_msgs::Twist out_msg;
        out_msg.linear.x = received_speed.linear.x*0.44704;
        out_msg.linear.y = received_speed.linear.y*0.44704;
        out_msg.linear.z = received_speed.linear.z*0.44704;
        out_msg.angular = received_speed.angular;
        speed_publisher.publish(out_msg); //отправили сообщение
        ros::spinOnce(); //спим до следующего цикла (запускаем процесс в цикле while 1 раз)
        r.sleep(); //ждем до наступления следующего callback-a (с нужной частотой)
    }
}
