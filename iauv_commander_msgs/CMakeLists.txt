cmake_minimum_required(VERSION 3.0.2)
project(iauv_commander_msgs)

find_package(catkin REQUIRED)

list(APPEND CATKIN_SOURCES
    std_msgs
    geometry_msgs
  )

find_package(catkin REQUIRED COMPONENTS ${CATKIN_SOURCES} message_generation actionlib genmsg)

add_message_files(
  FILES
  Instruction.msg
  Param.msg
)

generate_messages(
 DEPENDENCIES
 geometry_msgs
 std_msgs
)

catkin_package(
  LIBRARIES
  CATKIN_DEPENDS ${CATKIN_SOURCES}
  DEPENDS
  )

###########s
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations

# list(APPEND INCLUDES
#   ${CMAKE_CURRENT_LIST_DIR}/include
#   ${catkin_INCLUDE_DIRS}
#   ${Boost_INCLUDE_DIRS}
#   )

# include_directories(SYSTEM ${INCLUDES})

# list(APPEND LIBRARIES
#   ${catkin_LIBRARIES}
#   ${Boost_LIBRARIES}
   
# )

