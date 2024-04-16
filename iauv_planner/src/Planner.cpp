#include <iauv_planner/Planner.h>
#include <iauv_planner/GetPath.h>
#include <iostream>

namespace iauv_planner
{

    Planner::Planner(ros::NodeHandle &nh) : nh_(nh)
    {
        std::cout << "planner default\n";
        std::cout << nh.getNamespace() << "\n\n";
        service_ = nh.advertiseService("getPath", &Planner::getPath, this);

        pub_ = nh.advertise<nav_msgs::Path>("/iauv_planner/path", 2, true);
        scn = std::make_shared<iauv_planner::Scene>(nh);
    }

    bool Planner::getPath(iauv_planner::GetPath::Request &req, iauv_planner::GetPath::Response &res)
    {
        std::cout << "executing planner service\n";

        Eigen::Quaternionf q(req.start.orientation.w,
                             req.start.orientation.x,
                             req.start.orientation.y,
                             req.start.orientation.z);

        auto euler = q.toRotationMatrix().eulerAngles(0, 1, 2);

        std::vector<double> start = {req.start.position.x,
                                     req.start.position.y,
                                     req.start.position.z,
                                     atan2(q.toRotationMatrix()(1, 0), q.toRotationMatrix()(0, 0))};

        q = Eigen::Quaternionf(req.goal.orientation.w,
                               req.goal.orientation.x,
                               req.goal.orientation.y,
                               req.goal.orientation.z);
        euler = q.toRotationMatrix().eulerAngles(0, 1, 2);
        std::vector<double> goal = {req.goal.position.x,
                                    req.goal.position.y,
                                    req.goal.position.z,
                                    atan2(q.toRotationMatrix()(1, 0), q.toRotationMatrix()(0, 0))};

        res.path = this->doPlan(start, goal);
        pub_.publish(res.path);
        scn->drawPath(res.path);

        return true;
    }

}