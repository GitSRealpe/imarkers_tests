# OPTIHROV Colab

Set of packages to allow colaboration between CIRS (UdG) and CIRTESU (UJI) research labs for the OPTIHROV project.

The way of communication between the HRI and the instruction server is done initially through [iauv_commander/Instruction](https://gitsrealpe.github.io/optihrov_colab/iauv_commander_msgs/doc/html/msg/Instruction.html) messages.

After an instruction marker has been created in the HRI and uploaded to the instruction server, the HRI will publish changes in the marker to the `iauv_commander/marker_server/feedback` topic using [visualization_msgs/InteractiveMarkerFeedback](http://docs.ros.org/en/noetic/api/visualization_msgs/html/msg/InteractiveMarkerFeedback.html) msgs.

General flow diagram

![flow_diagram](./media/fig.svg)

Steps for instruction creation example execution:
In a linux terminal, execute

1. `cd catkin_ws/src`
2. `git clone https://github.com/GitSRealpe/optihrov_colab.git`
3. `cd ..`
4. Within the catkin tools workspace defined: `catkin build human_robot_interface`
5. `source devel/setup.bash`
6. ***Terminal 1***: `roscore`
7. ***Terminal 2***: `rosrun iauv_commander main`
8. ***Terminal 3***: `roslaunch human_robot_interface hmi.launch`
9. ***Terminal 2*** should print `received instruction "goal1" of type: grab`

Given this, if any interface publishes a [visualization_msgs/InteractiveMarkerFeedback](http://docs.ros.org/en/noetic/api/visualization_msgs/html/msg/InteractiveMarkerFeedback.html) message to the `iauv_commander/marker_server/feedback` topic, ***Terminal 2*** should output said feeback.