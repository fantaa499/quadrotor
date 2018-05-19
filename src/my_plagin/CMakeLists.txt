cmake_minimum_required(VERSION 2.8.3)
project(my_plagin)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  octomap REQUIRED
  sensor_msgs
  pcl_ros
)


find_package(PCL 1.8 REQUIRED)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES my_plagin
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

link_directories(${PCL_LIBRARY_DIRS})
link_directories(${OCTOMAP_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${OCTOMAP_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)





add_executable(genPointCloud src/genPointCloud.cpp)
target_link_libraries(genPointCloud ${catkin_LIBRARIES} ${OCTOMAP_LIBRARIES} ${PCL_LIBRARIES})

add_executable(genOctTree src/genOctTree.cpp)
target_link_libraries(genOctTree ${catkin_LIBRARIES} ${OCTOMAP_LIBRARIES} ${PCL_LIBRARIES})

add_executable(moveToDestiny src/moveToDestiny.cpp)
target_link_libraries(moveToDestiny ${catkin_LIBRARIES} ${OCTOMAP_LIBRARIES} ${PCL_LIBRARIES})

add_executable(genDestinyPoint src/genDestinyPoint.cpp)
target_link_libraries(genDestinyPoint ${catkin_LIBRARIES} ${OCTOMAP_LIBRARIES} ${PCL_LIBRARIES})

add_executable(genDestinyPointRRT src/genDestinyPointRRT.cpp)
target_link_libraries(genDestinyPointRRT ${catkin_LIBRARIES} ${OCTOMAP_LIBRARIES} ${PCL_LIBRARIES})

add_executable(makeGraphicInRviz src/makeGraphicInRviz.cpp)
target_link_libraries(makeGraphicInRviz ${catkin_LIBRARIES} ${OCTOMAP_LIBRARIES} ${PCL_LIBRARIES})

add_executable(makeRRTmodif src/makeRRTmodif.cpp)
target_link_libraries(makeRRTmodif ${catkin_LIBRARIES} ${OCTOMAP_LIBRARIES} ${PCL_LIBRARIES})

add_executable(drawTrajectory src/drawTrajectory.cpp)
target_link_libraries(drawTrajectory ${catkin_LIBRARIES})

#add_dependencies(genPointCloud my_plagin_gencpp)
install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
install(DIRECTORY rviz_cfg DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
#############

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)

