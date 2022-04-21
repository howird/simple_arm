#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <stdint.h>
#include <math.h>
#include <iostream>

class SimpleMover 
{
  private:
    ros::NodeHandle n;
    ros::Publisher joint1;
    ros::Publisher joint2;
    ros::Rate loopRate;

  public:
    SimpleMover(std::string jn1, std::string jn2, float lr) :
        joint1(n.advertise<std_msgs::Float64>("/simple_arm/" + jn1 + "/command", 1000)),
        joint2(n.advertise<std_msgs::Float64>("/simple_arm/" + jn2 + "/command", 1000)),
        loopRate(lr)
    {

        u_int8_t count = 0;
        while(ros::ok())
        {
            std_msgs::Float64 msg;
            msg.data = sin(M_PI * 2.0 *((double) count)/255.0)*M_PI/2.0;
            std::cout << msg.data << std::endl;
            joint1.publish(msg);
            joint2.publish(msg);
            count ++;
            ros::spinOnce();
            loopRate.sleep();
        }
    }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "simple_mover_node"); 
  SimpleMover sm("joint_1_position_controller", "joint_2_position_controller", 10);
  return 0;
}