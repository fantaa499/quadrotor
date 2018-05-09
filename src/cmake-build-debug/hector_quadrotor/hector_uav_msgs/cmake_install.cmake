# Install script for directory: /home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hector_uav_msgs/msg" TYPE FILE FILES
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/Altimeter.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/AttitudeCommand.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/Compass.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/ControllerState.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/HeadingCommand.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/HeightCommand.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/MotorCommand.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/MotorPWM.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/MotorStatus.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/PositionXYCommand.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/RawImu.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/RawMagnetic.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/RawRC.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/RC.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/RuddersCommand.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/ServoCommand.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/Supply.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/ThrustCommand.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/VelocityXYCommand.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/VelocityZCommand.msg"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/msg/YawrateCommand.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hector_uav_msgs/srv" TYPE FILE FILES "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/srv/EnableMotors.srv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hector_uav_msgs/action" TYPE FILE FILES
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/action/Pose.action"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/action/Landing.action"
    "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/action/Takeoff.action"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hector_uav_msgs/msg" TYPE FILE FILES
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/PoseAction.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/PoseActionGoal.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/PoseActionResult.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/PoseActionFeedback.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/PoseGoal.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/PoseResult.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/PoseFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hector_uav_msgs/msg" TYPE FILE FILES
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/LandingAction.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/LandingActionGoal.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/LandingActionResult.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/LandingActionFeedback.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/LandingGoal.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/LandingResult.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/LandingFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hector_uav_msgs/msg" TYPE FILE FILES
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/TakeoffAction.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/TakeoffActionGoal.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/TakeoffActionResult.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/TakeoffActionFeedback.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/TakeoffGoal.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/TakeoffResult.msg"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/hector_uav_msgs/msg/TakeoffFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hector_uav_msgs/cmake" TYPE FILE FILES "/home/anton/Documents/catkin_ws/src/cmake-build-debug/hector_quadrotor/hector_uav_msgs/catkin_generated/installspace/hector_uav_msgs-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/include/hector_uav_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/roseus/ros/hector_uav_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/common-lisp/ros/hector_uav_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/share/gennodejs/ros/hector_uav_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/lib/python2.7/dist-packages/hector_uav_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/anton/Documents/catkin_ws/src/cmake-build-debug/devel/lib/python2.7/dist-packages/hector_uav_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/anton/Documents/catkin_ws/src/cmake-build-debug/hector_quadrotor/hector_uav_msgs/catkin_generated/installspace/hector_uav_msgs.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hector_uav_msgs/cmake" TYPE FILE FILES "/home/anton/Documents/catkin_ws/src/cmake-build-debug/hector_quadrotor/hector_uav_msgs/catkin_generated/installspace/hector_uav_msgs-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hector_uav_msgs/cmake" TYPE FILE FILES
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/hector_quadrotor/hector_uav_msgs/catkin_generated/installspace/hector_uav_msgsConfig.cmake"
    "/home/anton/Documents/catkin_ws/src/cmake-build-debug/hector_quadrotor/hector_uav_msgs/catkin_generated/installspace/hector_uav_msgsConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hector_uav_msgs" TYPE FILE FILES "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/hector_uav_msgs" TYPE DIRECTORY FILES "/home/anton/Documents/catkin_ws/src/hector_quadrotor/hector_uav_msgs/include/hector_uav_msgs/")
endif()

