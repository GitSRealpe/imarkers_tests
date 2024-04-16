// grabs the path, the robot model, the collision box and publishes it in the planning __HAVE_SPECULATION_SAFE_VALUE

// if enabled, use rviz visual tools

// maybe also handle the map update and the collision objects

#include <iauv_planner/Scene.h>
#include <shape_msgs/Mesh.h>

namespace iauv_planner
{

    Scene::Scene(ros::NodeHandle &nh)
    {
        visual_tools_ = std::make_shared<rviz_visual_tools::RvizVisualTools>("world_ned", "/iauv_scene");

        counter = 0;

        marker_.type = visualization_msgs::Marker::MESH_RESOURCE;
        marker_.header.frame_id = "world_ned";
        marker_.mesh_resource = "package://iauv_commander/resources/g1000.dae";
        marker_.scale.x = marker_.scale.y = marker_.scale.z = 1;
        marker_.color.r = marker_.color.g = marker_.color.b = 1;
        marker_.color.a = 0.5;

        // move this timer to draw path and compute
        timer = nh.createTimer(ros::Duration(0.1), &Scene::animatePath, this, false, false);
    }

    Scene::~Scene()
    {
        std::cout << "destroying scene obj\n";
        visual_tools_->deleteAllMarkers();

        visual_tools_->trigger();
    }

    void Scene::animatePath(const ros::TimerEvent &event)
    {
        if (counter < path_.poses.size())
        {
            marker_.pose = path_.poses[counter].pose;
            visual_tools_->publishMarker(marker_);
            counter++;
        }
        else
        {
            counter = 0;
        }
        visual_tools_->trigger();
    }

    void Scene::drawPath(nav_msgs::Path path)
    {
        path_ = path;
        visual_tools_->deleteAllMarkers();
        EigenSTL::vector_Vector3d puntos;
        std::vector<rviz_visual_tools::colors> colors;
        int i = 0;
        counter = 0;

        for (auto posestmp : path_.poses)
        {
            puntos.push_back({posestmp.pose.position.x, posestmp.pose.position.y, posestmp.pose.position.z});
            colors.push_back(colorlist_.at(i++ % colorlist_.size()));
            visual_tools_->publishArrow(posestmp.pose, rviz_visual_tools::RED, rviz_visual_tools::LARGE);
        }

        visual_tools_->publishPath(puntos, colors, 0.05);

        // Don't forget to trigger the publisher!
        visual_tools_->trigger();
        timer.start();
    }

}