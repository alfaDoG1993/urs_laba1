#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>

ros::Publisher speed_pub;
ros::Subscriber speed_sub;

geometry_msgs::Twist out_data;

const float coef = 1./0.514;  

void speed_callback( const geometry_msgs::Twist::ConstPtr &msg )
{
    out_data.linear.x = msg->linear.x * coef;
    out_data.linear.y = msg->linear.y * coef;  
    out_data.linear.z = msg->linear.z * coef;

    out_data.angular = msg->angular;	
}

int main( int argc, char **argv )
{
    ros::init( argc, argv, "speed_publisher_node" );
    ros::NodeHandle nh( "~" );

    ROS_INFO( "Starting node..." );

    speed_pub = nh.advertise< geometry_msgs::Twist >( "speed_out", 1 );
    speed_sub = nh.subscribe( "speed_in", 1, speed_callback );

    ros::Rate r(10);

    while ( ros::ok() )
    {
        speed_pub.publish( out_data );
        ros::spinOnce();
        r.sleep();
    }

    return 0;
}
