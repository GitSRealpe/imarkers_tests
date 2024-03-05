#include <ros/ros.h>
#include <iauv_commander_msgs/Instruction.h>

int main(int argc, char **argv)
{
    std::cout << "un print 2024\n";
    ros::init(argc, argv, "hri_node");
    ros::NodeHandle nh;

    // create the publisher object
    ros::Publisher msg_pub = nh.advertise<iauv_commander_msgs::Instruction>("iauv_commander/instruction", 10);

    // construct the iauv_commander message
    iauv_commander_msgs::Instruction instruc;

    // input fields that come from the GUI
    instruc.robot_name = "girona1000";
    instruc.marker_name = "goal1";
    instruc.instruction_type = "grab";
    instruc.marker_position.x = 0;
    instruc.marker_position.y = 0;
    instruc.marker_position.z = 0;

    instruc.marker_color.r = 1;
    instruc.marker_color.g = 1;
    instruc.marker_color.b = 1;
    instruc.marker_color.a = 1;

    iauv_commander_msgs::Params param;
    param.key = "manipulator_name";
    param.value = "bravo_left";
    instruc.params.push_back(param);

    // 1 second delay because the code runs too fast and the publisher doesnt have time to be created
    ros::Duration(1).sleep();
    // publish the msg to the iauv_commander server
    msg_pub.publish(instruc);
    while (ros::ok())
    {

        ros::spinOnce();
        ros::Duration(1).sleep();
        // ros::spin();
    }

    return 0;
}