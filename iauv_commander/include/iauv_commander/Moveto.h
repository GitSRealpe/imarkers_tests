#ifndef MOVETO_
#define MOVETO_
#include <iauv_commander/InstructionClass.h>
#include <string>

#include <iauv_commander_msgs/Instruction.h>
#include <interactive_markers/interactive_marker_server.h>
#include <interactive_markers/menu_handler.h>

namespace iauv_commander
{
    class Moveto : public iauv_commander::InstructionClass
    {
    private:
    public:
        Moveto();
        // MovetoMarker(std::string robot_name, int marker_id, interactive_markers::InteractiveMarkerServer &server);
        Moveto(iauv_commander_msgs::InstructionConstPtr msg,
               std::shared_ptr<interactive_markers::InteractiveMarkerServer> server,
               ros::NodeHandle &nh);

        void markerFeedback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback);
        // void moveCb(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback);
        // void reqCb(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback);
    };

}

#endif