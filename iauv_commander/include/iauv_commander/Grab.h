#ifndef GRAB_
#define GRAB_
#include <iauv_commander/InstructionClass.h>
#include <string>

#include <iauv_commander_msgs/Instruction.h>
#include <interactive_markers/interactive_marker_server.h>

namespace iauv_commander
{
    class Grab : public iauv_commander::InstructionClass
    {
    private:
    public:
        Grab();
        Grab(iauv_commander_msgs::InstructionConstPtr msg, std::shared_ptr<interactive_markers::InteractiveMarkerServer> server, ros::NodeHandle &nh);

        void markerFeedback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback);
    };

}

#endif