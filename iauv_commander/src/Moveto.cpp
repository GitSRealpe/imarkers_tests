#include <iauv_commander/Moveto.h>
#include <iostream>

#include <visualization_msgs/InteractiveMarker.h>
#include <interactive_markers/interactive_marker_server.h>

namespace iauv_commander
{
    Moveto::Moveto()
    {
        std::cout << "default moveto \n";
    }

    void markerFeedback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback)
    {
        ROS_INFO_STREAM(feedback->marker_name << " is now at: "
                                              << feedback->pose.position.x << ", " << feedback->pose.position.y
                                              << ", " << feedback->pose.position.z);
        ROS_INFO_STREAM(feedback->marker_name << " with orientation: "
                                              << feedback->pose.orientation.x << ", " << feedback->pose.orientation.y
                                              << ", " << feedback->pose.orientation.z << ", " << feedback->pose.orientation.w);
        feedback->client_id;
    }

    Moveto::Moveto(iauv_commander_msgs::InstructionConstPtr msg, std::shared_ptr<interactive_markers::InteractiveMarkerServer> server) : iauv_commander::InstructionClass(msg, server)
    {
        std::cout << "done by param constructor\n";

        // control marker for mesh
        visualization_msgs::InteractiveMarkerControl control;
        control.interaction_mode = visualization_msgs::InteractiveMarkerControl::NONE;
        control.always_visible = true;
        visualization_msgs::Marker marker;
        marker.type = visualization_msgs::Marker::MESH_RESOURCE;
        marker.mesh_resource = "package://girona1000_description/resources/meshes/girona1000.dae";
        marker.pose.position.x = 0.7;
        marker.pose.position.z = 0.4;
        marker.pose.orientation.y = -0.707;
        marker.pose.orientation.z = 0.707;
        marker.scale.x = marker.scale.y = marker.scale.z = 1;
        marker.color = msg->marker_color;
        marker.color.a = 1;
        control.markers.push_back(marker);
        int_marker_.controls.push_back(control);

        createMarker(true, true, true, false, false, true);

        server_->insert(int_marker_, &markerFeedback);
        // 'commit' changes and send to all clients
        server_->applyChanges();

        std::cout << "marker creado\n";
    }

    // create marker at position function
}
