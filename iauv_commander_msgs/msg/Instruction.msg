# General structure for robot Instructions

string robot_name                           # The name of the robot that will execute the task
string instruction_type                     # Predefined instruction type, ie: "moveto", "grab"
string marker_name                          # Name of the interactive marker to track it easily
std_msgs/ColorRGBA marker_color             # Color of the interactive marker
geometry_msgs/Point marker_position         # Initial position of the interactive marker
iauv_commander_msgs/Params[] params         # List of additional instruction paramaters 