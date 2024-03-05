#ifndef INSTRUCTION_
#define INSTRUCTION_

#include <iauv_commander_msgs/Instruction.h>
#include <interactive_markers/interactive_marker_server.h>
#include <string>

namespace iauv_commander
{
    class InstructionClass
    {
    private:
    public:
        InstructionClass();
        InstructionClass(iauv_commander_msgs::InstructionConstPtr msg, std::shared_ptr<interactive_markers::InteractiveMarkerServer> server);
        // ~InstructionClass();

        /**
         * @brief Create a Marker object
         *
         * @param x_mov enable marker movement in x_axis
         * @param y_mov enable marker movement in y_axis
         * @param z_mov enable marker movement in z_axis
         * @param x_rot enable marker rotation in x_axis
         * @param y_rot enable marker rotation in x_axis
         * @param z_rot enable marker rotation in x_axis
         */
        void createMarker(bool x_mov, bool y_mov, bool z_mov, bool x_rot, bool y_rot, bool z_rot);

        iauv_commander_msgs::InstructionConstPtr msg_;

        visualization_msgs::InteractiveMarker int_marker_;
        visualization_msgs::InteractiveMarkerControl control_;

        std::shared_ptr<interactive_markers::InteractiveMarkerServer> server_;
    };

}

#endif