#include <iauv_commander/InstructionClass.h>
#include <iostream>

namespace iauv_commander
{
    InstructionClass::InstructionClass()
    {
        std::cout << "nameless print \n";
    }
    InstructionClass::InstructionClass(iauv_commander_msgs::InstructionConstPtr msg, std::shared_ptr<interactive_markers::InteractiveMarkerServer> server) : server_(server), msg_(msg)
    {
        std::cout << "Defining InstructionClass of type {\" ? \"}\n";
    }

    void InstructionClass::createMarker(bool x_mov, bool y_mov, bool z_mov, bool x_rot, bool y_rot, bool z_rot)
    {
        std::cout << "creando marcador\n";
        // control_ = visualization_msgs::InteractiveMarkerControl();
        int_marker_.header.frame_id = "world_ned";
        int_marker_.pose.position.x = msg_->marker_position.x;
        int_marker_.pose.position.y = msg_->marker_position.y;
        int_marker_.pose.position.z = msg_->marker_position.z;
        int_marker_.pose.orientation.w = 1;
        int_marker_.scale = 1;
        int_marker_.name = msg_->marker_name;
        int_marker_.description = msg_->marker_name;

        control_.always_visible = true;
        control_.orientation.w = 1;
        if (x_mov)
        {
            control_.name = "move_x";
            control_.interaction_mode = visualization_msgs::InteractiveMarkerControl::MOVE_AXIS;
            int_marker_.controls.push_back(control_);
        }

        if (x_rot)
        {
            control_.name = "rotate_x";
            control_.interaction_mode = visualization_msgs::InteractiveMarkerControl::ROTATE_AXIS;
            int_marker_.controls.push_back(control_);
        }

        control_.orientation.w = 0.7071;
        control_.orientation.x = 0;
        control_.orientation.y = 0;
        control_.orientation.z = 0.7071;
        if (y_mov)
        {
            control_.name = "move_y";
            control_.interaction_mode = visualization_msgs::InteractiveMarkerControl::MOVE_AXIS;
            int_marker_.controls.push_back(control_);
        }

        if (y_rot)
        {
            control_.name = "rotate_y";
            control_.interaction_mode = visualization_msgs::InteractiveMarkerControl::ROTATE_AXIS;
            int_marker_.controls.push_back(control_);
        }

        control_.orientation.w = 0.7071;
        control_.orientation.x = 0;
        control_.orientation.y = 0.7071;
        control_.orientation.z = 0;
        if (z_mov)
        {
            control_.name = "move_z";
            control_.interaction_mode = visualization_msgs::InteractiveMarkerControl::MOVE_AXIS;
            int_marker_.controls.push_back(control_);
        }
        if (z_rot)
        {
            control_.name = "rotate_z";
            control_.interaction_mode = visualization_msgs::InteractiveMarkerControl::ROTATE_AXIS;
            int_marker_.controls.push_back(control_);
        }
    }
}
