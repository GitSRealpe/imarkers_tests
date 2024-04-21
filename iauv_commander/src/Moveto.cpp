#include <iauv_commander/Moveto.h>
#include <iostream>

#include <iauv_planner/GetPath.h>

#include <visualization_msgs/InteractiveMarker.h>
#include <interactive_markers/interactive_marker_server.h>
#include <interactive_markers/menu_handler.h>
#include <ros/ros.h>

#include <std_msgs/String.h>

interactive_markers::MenuHandler menu_handler_;

// menu feedback functions cannot be member functions, so these have to be global variables for them to be used
ros::Publisher cmdPub;
ros::Publisher goalPub;

ros::ServiceClient pathClient_;
namespace iauv_commander
{
    Moveto::Moveto()
    {
        std::cout << "default constructor moveto \n";
    }

    void Moveto::markerFeedback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback)
    {
        ROS_INFO_STREAM(feedback->marker_name << " is now at: "
                                              << feedback->pose.position.x << ", " << feedback->pose.position.y
                                              << ", " << feedback->pose.position.z);
        ROS_INFO_STREAM(feedback->marker_name << " with orientation: "
                                              << feedback->pose.orientation.x << ", " << feedback->pose.orientation.y
                                              << ", " << feedback->pose.orientation.z << ", " << feedback->pose.orientation.w);
        feedback->client_id;
    }

    void reqCb(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback)
    {
        std::cout << "requesting planning to planning topic\n";

        iauv_planner::GetPath req;
        req.request.start.position.x = 0;
        req.request.start.position.y = 0;
        req.request.start.position.z = 2;
        req.request.start.orientation.w = 0;

        req.request.goal = feedback->pose;

        pathClient_.call(req);
    }

    void moveCb(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback)
    {
        std::cout << "the robot is moving wohoo\n";
    }

    Moveto::Moveto(iauv_commander_msgs::InstructionConstPtr msg, std::shared_ptr<interactive_markers::InteractiveMarkerServer> server, ros::NodeHandle &nh) : iauv_commander::InstructionClass(msg, server, nh)
    {
        std::cout << "normal constructor\n";

        pathClient_ = nh.serviceClient<iauv_planner::GetPath>("iauv_planner/getPath");

        visualization_msgs::InteractiveMarker int_marker = createMarker(true, true, true, false, false, true);

        int_marker.scale = 1;
        // control marker for mesh
        visualization_msgs::InteractiveMarkerControl control;
        control.interaction_mode = visualization_msgs::InteractiveMarkerControl::BUTTON;
        control.always_visible = true;
        visualization_msgs::Marker marker;
        marker.type = visualization_msgs::Marker::MESH_RESOURCE;
        marker.mesh_resource = "package://iauv_commander/resources/g1000.dae";
        marker.scale.x = marker.scale.y = marker.scale.z = 1;
        marker.color = msg->marker_color;
        marker.color.a = 1;
        control.markers.push_back(marker);
        int_marker.controls.push_back(control);

        visualization_msgs::InteractiveMarker dummy_marker;
        if (!server_->get(msg->marker_name, dummy_marker))
        {
            menu_handler_.insert("Request Path", &reqCb);
            menu_handler_.insert("Move", &moveCb);
        }

        server_->insert(int_marker, boost::bind(&Moveto::markerFeedback, this, _1));
        // menu_handler_.insert("Move", &iauv_commander::Moveto::reqCb);
        menu_handler_.apply(*server_, int_marker.name);
        // 'commit' changes and send to all clients
        server_->applyChanges();

        std::cout << "marker creado\n";
    }

    // create marker at position function
}
