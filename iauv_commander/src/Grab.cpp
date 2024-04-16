#include <iauv_commander/Grab.h>
#include <iostream>

#include <visualization_msgs/InteractiveMarker.h>
#include <interactive_markers/interactive_marker_server.h>

namespace iauv_commander
{
    Grab::Grab()
    {
        std::cout << "default Grab \n";
    }

    void Grab::markerFeedback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback)
    {
        ROS_INFO_STREAM(feedback->marker_name << " is now at: "
                                              << feedback->pose.position.x << ", " << feedback->pose.position.y
                                              << ", " << feedback->pose.position.z);
        ROS_INFO_STREAM(feedback->marker_name << " with orientation: "
                                              << feedback->pose.orientation.x << ", " << feedback->pose.orientation.y
                                              << ", " << feedback->pose.orientation.z << ", " << feedback->pose.orientation.w);
        feedback->client_id;
    }

    Grab::Grab(iauv_commander_msgs::InstructionConstPtr msg, std::shared_ptr<interactive_markers::InteractiveMarkerServer> server, ros::NodeHandle &nh) : iauv_commander::InstructionClass(msg, server, nh)
    {
        std::cout << "done by param constructor\n";

        visualization_msgs::InteractiveMarker int_marker = createMarker(true, true, true, true, true, true);
        // control marker for mesh
        visualization_msgs::InteractiveMarkerControl control;
        control.interaction_mode = visualization_msgs::InteractiveMarkerControl::NONE;
        control.always_visible = true;
        visualization_msgs::Marker marker;
        marker.type = visualization_msgs::Marker::MESH_RESOURCE;
        marker.mesh_resource = "package://iauv_commander/resources/grasp.dae";
        marker.pose.position.x = 0;
        marker.pose.position.z = 0;
        marker.pose.orientation.w = 0;
        marker.scale.x = marker.scale.y = marker.scale.z = 1;
        marker.color = msg->marker_color;
        marker.color.a = 1;
        control.markers.push_back(marker);
        int_marker.controls.push_back(control);
        int_marker.scale = 0.3;

        server_->insert(int_marker, boost::bind(&Grab::markerFeedback, this, _1));

        // 'commit' changes and send to all clients
        server_->applyChanges();

        std::cout << "marker creado\n";
    }

    // create marker at position function
}
