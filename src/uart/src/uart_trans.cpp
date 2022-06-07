#include<ros/ros.h> 
#include<std_msgs/UInt16.h> 
void myCallback(const std_msgs::UInt16::ConstPtr& msg) { 

  ROS_INFO("received value is: [%i]",msg ->data); 
  
} 
 
int main(int argc, char **argv) 
{ 
  ros::init(argc,argv,"uart_trans"); 
  ros::NodeHandle n;
  
  ros::Subscriber my_subscriber_object= n.subscribe("key_command",10,myCallback); 

 
  ros::spin(); 
  return 0; 
} 