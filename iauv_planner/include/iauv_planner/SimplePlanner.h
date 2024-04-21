#ifndef SIMPLANNER
#define SIMPLANNER

#include <iauv_planner/Planner.h>

namespace iauv_planner
{

    class SimplePlanner : public Planner
    {
    private:
    public:
        SimplePlanner(ros::NodeHandle &nh);
        nav_msgs::Path doPlan(std::vector<double> start, std::vector<double> goal);
    };

} // namespace iauv_planner

#endif