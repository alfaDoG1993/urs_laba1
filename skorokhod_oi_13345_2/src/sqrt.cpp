#include <ros/ros.h>
#include <math.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>

ros::Publisher sqrt_out;
ros::Subscriber int_in;

int current_number;
void int_callback(const std_msgs::Int32::ConstPtr &msg)
{
  current_number = msg->data;
}

int main(int argc, char *argv[])
{
  ros::init(argc,argv, "sqrt_node");
  ros::NodeHandle nh("~");
  ROS_INFO("Starting sqrt node...");
  
  sqrt_out = nh.advertise<std_msgs::Float32>("output_float",1);
  int_in = nh.subscribe("incoming_int",1,int_callback);
  ros::Rate fr(10);
  while(ros::ok())
  {
      std_msgs::Float32 out_msg;
      if(current_number<0)
      {
          ROS_INFO("ACHTUNG ACHTUNG! COMPLEX NUMBERS!");
      }
      else
      {
          //ROS_INFO("OK");
          out_msg.data = sqrt(current_number);
          sqrt_out.publish(out_msg);
      }
      ros::spinOnce();
      fr.sleep();
  }
}
