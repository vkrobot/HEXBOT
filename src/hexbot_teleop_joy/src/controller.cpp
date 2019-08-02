#include "ros/ros.h"
#include <hexbot_msgs/Buffer.h>
#include <hexbot_msgs/Battery.h>

#include <serial/serial.h>  //ROS已经内置了的串口包 
#include <std_msgs/String.h> 
#include <std_msgs/Empty.h> 

serial::Serial ser; //声明串口对象 
hexbot_msgs::Buffer protocol;  //
  
//回调函数 

void chatterCallback(const hexbot_msgs::Buffer::ConstPtr& protocol)
{
    hexbot_msgs::Buffer data;
    data=*protocol;

    //ROS_INFO_STREAM("the data sending is "<< data<<"\n"); 
    //ROS_INFO_STREAM("the length of data is  "<< data.len<<"\n");  
      ser.write(data.buff);
}
  
int main (int argc, char** argv) 
{ 
    //初始化节点 
    ros::init(argc, argv, "controller"); 
    //声明节点句柄 
    ros::NodeHandle nh; 
  
    //订阅主题，并配置回调函数 
    ros::Subscriber write_sub = nh.subscribe("chatter", 10, chatterCallback); 
    //发布主题 
    ros::Publisher  battery_sub = nh.advertise<hexbot_msgs::Battery>("battery",10); 
  
    try 
    { 
    //设置串口属性，并打开串口 
        ser.setPort("/dev/vkhexbot_serial");
        ser.setBaudrate(115200); 
        serial::Timeout to = serial::Timeout::simpleTimeout(1000); 
        ser.setTimeout(to); 
        ser.open(); 

    } 
    catch (serial::IOException& e) 
    { 
        ROS_ERROR_STREAM("Unable to open port "); 
        return -1; 
    } 
  
    //检测串口是否已经打开，并给出提示信息 
    if(ser.isOpen()) 
    { 
        ROS_INFO_STREAM("Serial Port initialized"); 
    } 
    else 
    { 
        return -1; 
    } 
  
    //指定循环的频率 
    ros::Rate loop_rate(50); 
    while(ros::ok()) 
    { 
  
        if(ser.available()){ 
            //ROS_INFO_STREAM("Reading from serial port\n"); 
	    hexbot_msgs::Battery data;
            std_msgs::String buf; 
            buf.data = ser.read(ser.available());
	    buf.data += ser.read(ser.available());
	    //ROS_INFO_STREAM("Read: " << buf.data << "Read: ");
	    if(('V'==buf.data[0]) && ('K'==buf.data[1]))
	    {
			if((0x03==buf.data[2]) && (0x01==buf.data[3]))
			{                	 			
				data.voltage = (unsigned int)((buf.data[5] << 8) + buf.data[6]);
				data.current = (unsigned int)((buf.data[7] << 8) + buf.data[8]);
				data.quantity = (unsigned char)buf.data[9];
				battery_sub.publish(data);
				printf("voltage:%d current:%d quantity:%d\n",data.voltage, data.current,data.quantity);			         
			} 
	    }  
    }

        //处理ROS的信息，比如订阅消息,并调用回调函数 
        ros::spinOnce(); 
        loop_rate.sleep(); 
  
    } 
}
