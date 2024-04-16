#include <ros/ros.h>
#include <stdio.h>

#include <iauv_planner/SimplePlanner.h>
#include <iauv_planner/GetPath.h>

int main(int argc, char **argv)
{
    std::cout << "yeah planning\n";
    ros::init(argc, argv, "planner_node");
    ros::NodeHandle nh("~");

    iauv_planner::SimplePlanner plnr(nh);

    while (ros::ok())
    {
        // ros::spinOnce();
        // ros::Duration(1).sleep();
        ros::spin();
    }

    return 0;
}
