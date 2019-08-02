cmake_minimum_required(VERSION 2.8.3)
project(hexbot_teleop_joy)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  ps3joy
  joy
  roscpp
  std_msgs
  hexbot_msgs
  serial
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
# CATKIN_DEPENDS message_runtime
#  INCLUDE_DIRS include
#  LIBRARIES hexbot_teleop_joy
#  CATKIN_DEPENDS ps3joy roscpp std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########


#Generator messages in the "msg" folder
#add_message_files(
#   FILES
#   data.msg
#)



## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories( include ${catkin_INCLUDE_DIRS})

add_executable(controller src/controller.cpp)
target_link_libraries(controller  ${catkin_LIBRARIES})
add_dependencies(controller hexbot_msgs_gencpp)


