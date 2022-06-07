#include <ros/ros.h>
#include <std_msgs/UInt16.h>
#include <termio.h>
#include <stdio.h>
 
#define KEYCODE_W 0x77
#define KEYCODE_A 0x61
#define KEYCODE_S 0x73
#define KEYCODE_D 0x64
 
#define KEYCODE_A_CAP 0x41
#define KEYCODE_D_CAP 0x44
#define KEYCODE_S_CAP 0x53
#define KEYCODE_W_CAP 0x57
 
int key_command=0x00;
 
void scanKeyboard()
{
	struct termios new_settings;
	struct termios stored_settings;
	tcgetattr(0,&stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	tcgetattr(0,&stored_settings);
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&new_settings);
	key_command = getchar();
	tcsetattr(0,TCSANOW,&stored_settings);
}
 
int main(int argc, char  *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"ros_read_keyboard");
    ros::NodeHandle nh;
 
    ros::Publisher key_publisher = nh.advertise<std_msgs::UInt16>("key_command",10);
    std_msgs::UInt16 key_c;//w:1  a:2  s:3  d:4  i:5  j:6  k:7  l:8
 
	while(1){
		scanKeyboard();
		switch(key_command)
		{
			case KEYCODE_W:
				key_c.data=1;
				key_publisher.publish(key_c);
				break;
			case KEYCODE_A:
				key_c.data=2;
				key_publisher.publish(key_c);
				break;
			case KEYCODE_S:
				key_c.data=3;
				key_publisher.publish(key_c);
				break;
			case KEYCODE_D:
				key_c.data=4;
				key_publisher.publish(key_c);
				break;
			default:
				key_c.data=0;
				key_publisher.publish(key_c);
				break;
		}
		ros::Duration(1).sleep();
		if(key_c.data != 0){
			key_c.data=0;
			key_publisher.publish(key_c);
		}
 
	}
}