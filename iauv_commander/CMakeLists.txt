cmake_minimum_required(VERSION 3.0.2)
project(iauv_commander)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_STANDARD 11)
#   set(CMAKE_CXX_STANDARD_REQUIRED ON)
#   set(CMAKE_CXX_EXTENSIONS OFF)
#   # this next line shouldn't be necessary, but doesn't always get added by cmake (e.g., for clang++-5)
#   add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH
  "${CMAKE_MODULE_PATH}"
  "${CMAKE_CURRENT_SOURCE_DIR}")

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED)
find_package(Eigen3 REQUIRED)

list(APPEND CATKIN_SOURCES
    roscpp
    rospy
    interactive_markers
    visualization_msgs
    std_msgs
    geometry_msgs
    iauv_commander_msgs
    iauv_planner
  )

find_package(catkin REQUIRED COMPONENTS ${CATKIN_SOURCES} )

# when having setup.py
# catkin_python_setup()

catkin_package(
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS ${CATKIN_SOURCES}
  DEPENDS
  INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/include
  )

###########s
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations

list(APPEND INCLUDES
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  )

include_directories(SYSTEM ${INCLUDES})

list(APPEND LIBRARIES
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
   
)

add_library(${PROJECT_NAME}
  src/InstructionClass.cpp
  src/Moveto.cpp
  src/Grab.cpp
)

add_executable(main scripts/main.cpp)
add_dependencies(main ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(main ${catkin_LIBRARIES} ${PROJECT_NAME})

# catkin_install_python(PROGRAMS
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )
