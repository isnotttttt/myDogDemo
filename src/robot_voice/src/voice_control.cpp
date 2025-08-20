#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>   
#include <iconv.h>

#include "qtts.h"
#include "msp_cmn.h"
#include "msp_errors.h"

#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <geometry_msgs/Twist.h>  
#include <geometry_msgs/PoseStamped.h>  

#include <unitree_legged_msgs/HighCmd.h>
#include <unitree_legged_msgs/HighState.h>


/*发送wsad移动命令*/
geometry_msgs::Twist twist;
ros::Publisher cmd_vel_pub;
//语音合成文字
std_msgs::String string_msg;
ros::Publisher tts_text_pub;
//当前运行状态
int cmd_type = 0;
ros::Publisher startTracing;
ros::Publisher LidarModel_pub;
ros::Publisher slam_pub;


int UTF8ToGB2312(char* szSrc, size_t iSrcLen, char* szDst, size_t iDstLen)
{
    iconv_t cd = iconv_open("gb2312//IGNORE", "utf-8//IGNORE");   // take care of "//IGNORE", it will ignore those invalid code
    if(0 == cd)
        return -2;
    memset(szDst, 0, iDstLen);
    char **src = &szSrc;
    char **dst = &szDst;
    if(-1 == (int)iconv(cd, src, &iSrcLen, dst, &iDstLen))
        return -1;
    iconv_close(cd);
    return 0;
}

int GB2312ToUTF8(char* szSrc, size_t iSrcLen, char* szDst, size_t iDstLen)
{
    iconv_t cd = iconv_open("utf-8//IGNORE", "gb2312//IGNORE");
    if(0 == cd)
        return -2;
    memset(szDst, 0, iDstLen);
    char **src = &szSrc;
    char **dst = &szDst;
    if(-1 == (int)iconv(cd, src, &iSrcLen, dst, &iDstLen))
        return -1;
    iconv_close(cd);
    return 0;
}

void iattextCallback(const std_msgs::String::ConstPtr& msg)
{
    char cmd[2000];
    const char* text;
    std_msgs::String string_start;

    std::string dataString = msg->data;
    const char * xx = dataString.c_str();
    char *intput = const_cast<char *>(xx);
    char output[sizeof(intput)*3];
    GB2312ToUTF8(intput, sizeof(intput), output, sizeof(output));
    dataString = output;

    if(dataString.find("前进") != dataString.npos)
    {
        char forwordString[40] = "开始前进";
        text = forwordString;
        std::cout<<text<<std::endl;
        cmd_type = 1;
        string_start.data = "stop"; 
        startTracing.publish(string_start);
    }
    else if(dataString.find("后退") != dataString.npos)
    {
        char backwordString[40] = "开始后退";
        text = backwordString;
        std::cout<<text<<std::endl;
        cmd_type = 2;
        string_start.data = "stop"; 
        startTracing.publish(string_start);
    }
    else if(dataString.find("左转") != dataString.npos)
    {
        char leftString[40] = "开始左转";
        text = leftString;
        std::cout<<text<<std::endl;
        cmd_type = 3;
        string_start.data = "stop"; 
        startTracing.publish(string_start);
    }
    else if(dataString.find("右转") != dataString.npos)
    {
        char rightdString[40] = "开始右转";
        text = rightdString;
        std::cout<<text<<std::endl;
        cmd_type = 4;
        string_start.data = "stop"; 
        startTracing.publish(string_start);
    }
    else if(dataString.find("停止") != dataString.npos)
    {
        char stopString[40] = "停止";
        text = stopString;
        std::cout<<text<<std::endl;
        cmd_type = 5;
        string_start.data = "stop"; 
        startTracing.publish(string_start);
    }
    else if(dataString.find("寻迹") != dataString.npos)
    {
        char stopString[40] = "start";
        text = stopString;
        std::cout<<text<<std::endl;
        cmd_type = 6;
        string_start.data = "start"; 
        startTracing.publish(string_start);
    }
    else if(dataString.find("7201") != dataString.npos)
    {
        char stopString[40] = "start";
        text = stopString;
        std::cout<<text<<std::endl;
        cmd_type = 6;
        string_start.data = "stop"; 
        startTracing.publish(string_start);
        geometry_msgs::PoseStamped Pose_pub;
        Pose_pub.header.frame_id = "map";
        Pose_pub.pose.position.x = 32.96517562866211;
        Pose_pub.pose.position.y = -1.7084863185882568;
        Pose_pub.pose.position.z = 0.0;

        Pose_pub.pose.orientation.x = 0.0;
        Pose_pub.pose.orientation.y = 0.0;
        Pose_pub.pose.orientation.z = 0.01596426759734398;
        Pose_pub.pose.orientation.w = 0.9998725629599406;
        slam_pub.publish(Pose_pub);
    }
    else if(dataString.find("7202") != dataString.npos)
    {
        char stopString[40] = "start";
        text = stopString;
        std::cout<<text<<std::endl;
        cmd_type = 6;
        string_start.data = "stop"; 
        startTracing.publish(string_start);
        geometry_msgs::PoseStamped Pose_pub;
        Pose_pub.header.frame_id = "map";
        Pose_pub.pose.position.x = 23.475921630859375;
        Pose_pub.pose.position.y = -1.1178008317947388;
        Pose_pub.pose.position.z = 0.0;

        Pose_pub.pose.orientation.x = 0.0;
        Pose_pub.pose.orientation.y = 0.0;
        Pose_pub.pose.orientation.z = -0.028733554334313172;
        Pose_pub.pose.orientation.w = 0.9995871061870081;
        slam_pub.publish(Pose_pub);
    }
        else if(dataString.find("7204") != dataString.npos)
    {
        char stopString[40] = "start";
        text = stopString;
        std::cout<<text<<std::endl;
        cmd_type = 6;
        string_start.data = "stop"; 
        startTracing.publish(string_start);
        geometry_msgs::PoseStamped Pose_pub;
        Pose_pub.header.frame_id = "map";
        Pose_pub.pose.position.x = 5.644010543823242;
        Pose_pub.pose.position.y = -0.6643377542495728;
        Pose_pub.pose.position.z = 0.0;

        Pose_pub.pose.orientation.x = 0.0;
        Pose_pub.pose.orientation.y = 0.0;
        Pose_pub.pose.orientation.z = 0.002897800081714309;
        Pose_pub.pose.orientation.w = 0.999995801368529;
        slam_pub.publish(Pose_pub);
    }
    else if(dataString.find("7203") != dataString.npos)
    {
        char stopString[40] = "start";
        text = stopString;
        std::cout<<text<<std::endl;
        cmd_type = 6;
        string_start.data = "stop"; 
        startTracing.publish(string_start);
        geometry_msgs::PoseStamped Pose_pub;
        Pose_pub.header.frame_id = "map";
        Pose_pub.pose.position.x = 14.062965393066406;
        Pose_pub.pose.position.y = -0.7669128775596619;
        Pose_pub.pose.position.z = 0.0;

        Pose_pub.pose.orientation.x = 0.0;
        Pose_pub.pose.orientation.y = 0.0;
        Pose_pub.pose.orientation.z = 0.002897762130478735;
        Pose_pub.pose.orientation.w = 0.9999958014785038;
        slam_pub.publish(Pose_pub);
    }
    else
    {
        ROS_WARN("unrecognized command");
        text = msg->data.c_str();
    }
	string_msg.data = text;
	tts_text_pub.publish(string_msg);
}


int main(int argc, char* argv[])
{
    float control_speed = 0;
	float control_turn = 0;	
    ros::init(argc,argv,"voice_control");
    ros::NodeHandle n;
    ros::Subscriber iat_text_sub =n.subscribe("iat_text", 1000,iattextCallback); //subscribe voice to text reault
	tts_text_pub = n.advertise<std_msgs::String>("tts_text", 1000);  //publish text to voice string

	cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_voice", 1);  
    startTracing = n.advertise<std_msgs::String>("/cmd_vel_start", 10000);

    slam_pub = n.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1000);


    ROS_INFO("Wait Command...");
    // ros::spin();
    ros::Rate loop_rate(50);
    while(ros::ok()){
        if(cmd_type == 6 or cmd_type == 0)
        {
            ros::spinOnce();
            loop_rate.sleep();
            continue;
        }
        switch (cmd_type)
        {
        case 1:
            control_speed = 0.2; 
            control_turn = 0.0;
            break;
        case 2:
            control_speed = -0.2; 
            control_turn = 0.0;
            break;
        case 3:
            control_speed = 0.1; 
            control_turn = 0.3;
            break;   
        case 4:
            control_speed = 0.1; 
            control_turn = -0.3;
            break;  
        case 5:
            control_speed = 0.0; 
            control_turn = 0.0;
            break; 
        default:
            break;
        }
        twist.linear.x = control_speed; 
        twist.linear.y = 0; 
        twist.linear.z = 0;
        twist.angular.x = 0; 
        twist.angular.y = 0; 
        twist.angular.z = control_turn;
        cmd_vel_pub.publish(twist);
        ros::spinOnce();
        loop_rate.sleep();
    }
exit:
	return 0;
}