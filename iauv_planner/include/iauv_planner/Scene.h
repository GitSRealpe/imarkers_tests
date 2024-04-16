#ifndef SCENE_
#define SCENE_

#include <string>
#include <ros/ros.h>
#include <nav_msgs/Path.h>

#include <iauv_planner/classForwards.h>

#include <rviz_visual_tools/rviz_visual_tools.h>

namespace iauv_planner
{
    IAUVPLANNER_CLASS_FORWARD(Scene);

    class Scene
    {
    private:
        nav_msgs::Path path_;
        rviz_visual_tools::RvizVisualToolsPtr visual_tools_;
        std::vector<rviz_visual_tools::colors> colorlist_ = {rviz_visual_tools::WHITE, rviz_visual_tools::BLUE};

        visualization_msgs::Marker marker_;

        ros::Timer timer;
        int counter;

    public:
        Scene(ros::NodeHandle &nh);
        ~Scene();

        void drawPath(nav_msgs::Path path);
        void animatePath(const ros::TimerEvent &event);

        ros::ServiceServer service_;
        ros::Publisher pubState;
    };

}

#endif