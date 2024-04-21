#ifndef PLANNER_
#define PLANNER_

#include <string>
#include <ros/ros.h>
#include <nav_msgs/Path.h>

#include <iauv_planner/GetPath.h>
#include <iauv_planner/classForwards.h>
#include <iauv_planner/Scene.h>

namespace iauv_planner
{
    // IAUVPLANNER_CLASS_FORWARD(Planner);

    class Planner
    {
    private:
        ScenePtr scn;
        ros::NodeHandle nh_;
        ros::Publisher pub_;

    public:
        Planner(ros::NodeHandle &nh);

        virtual nav_msgs::Path doPlan(std::vector<double> start, std::vector<double> goal)
        {
        }

        bool getPath(iauv_planner::GetPath::Request &req, iauv_planner::GetPath::Response &res);

        ros::ServiceServer service_;
        nav_msgs::Path path_;
    };

}

#endif