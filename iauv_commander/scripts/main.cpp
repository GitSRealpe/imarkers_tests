// subscribes to the instructions topic

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <iauv_commander_msgs/Instruction.h>
#include <interactive_markers/interactive_marker_server.h>

#include <iauv_commander/Moveto.h>
#include <iauv_commander/Grab.h>

std::shared_ptr<ros::NodeHandle> nhptr;
std::shared_ptr<interactive_markers::InteractiveMarkerServer> server;

void instructionCB(const iauv_commander_msgs::InstructionConstPtr &msg)
{
    std::cout << "received instruction \"" << msg->marker_name << "\" of type: " << msg->instruction_type << "\n";
    if (msg->instruction_type == "moveto")
    {
        // pass the rviz marker server and do magic
        iauv_commander::Moveto(msg, server, *nhptr);
    }
    if (msg->instruction_type == "grab")
    {
        iauv_commander::Grab(msg, server, *nhptr);
    }
}

int main(int argc, char **argv)
{
    std::cout << "best print 2024\n";

    std::cout << "yeah rvizing\n";
    ros::init(argc, argv, "iauv_commander_main");
    ros::NodeHandle nh;
    // *nhptr = nh;
    nhptr = std::make_shared<ros::NodeHandle>(nh);

    server = std::make_shared<interactive_markers::InteractiveMarkerServer>("iauv_commander/marker_server");

    ros::Subscriber sub = nh.subscribe("iauv_commander/instruction", 1000, instructionCB);

    while (ros::ok())
    {
        // ros::spinOnce();
        // ros::Duration(1).sleep();
        ros::spin();
    }
    server.reset();

    return 0;
}
