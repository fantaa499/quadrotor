// Generated by gencpp from file moveit_msgs/MoveGroupActionFeedback.msg
// DO NOT EDIT!


#ifndef MOVEIT_MSGS_MESSAGE_MOVEGROUPACTIONFEEDBACK_H
#define MOVEIT_MSGS_MESSAGE_MOVEGROUPACTIONFEEDBACK_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <actionlib_msgs/GoalStatus.h>
#include <moveit_msgs/MoveGroupFeedback.h>

namespace moveit_msgs
{
template <class ContainerAllocator>
struct MoveGroupActionFeedback_
{
  typedef MoveGroupActionFeedback_<ContainerAllocator> Type;

  MoveGroupActionFeedback_()
    : header()
    , status()
    , feedback()  {
    }
  MoveGroupActionFeedback_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , status(_alloc)
    , feedback(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::actionlib_msgs::GoalStatus_<ContainerAllocator>  _status_type;
  _status_type status;

   typedef  ::moveit_msgs::MoveGroupFeedback_<ContainerAllocator>  _feedback_type;
  _feedback_type feedback;




  typedef boost::shared_ptr< ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> const> ConstPtr;

}; // struct MoveGroupActionFeedback_

typedef ::moveit_msgs::MoveGroupActionFeedback_<std::allocator<void> > MoveGroupActionFeedback;

typedef boost::shared_ptr< ::moveit_msgs::MoveGroupActionFeedback > MoveGroupActionFeedbackPtr;
typedef boost::shared_ptr< ::moveit_msgs::MoveGroupActionFeedback const> MoveGroupActionFeedbackConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace moveit_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'shape_msgs': ['/opt/ros/kinetic/share/shape_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'moveit_msgs': ['/home/anton/Documents/catkin_ws/devel/share/moveit_msgs/msg', '/home/anton/Documents/catkin_ws/src/moveit_msgs/msg'], 'trajectory_msgs': ['/opt/ros/kinetic/share/trajectory_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'object_recognition_msgs': ['/opt/ros/kinetic/share/object_recognition_msgs/cmake/../msg'], 'octomap_msgs': ['/opt/ros/kinetic/share/octomap_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "12232ef97486c7962f264c105aae2958";
  }

  static const char* value(const ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x12232ef97486c796ULL;
  static const uint64_t static_value2 = 0x2f264c105aae2958ULL;
};

template<class ContainerAllocator>
struct DataType< ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "moveit_msgs/MoveGroupActionFeedback";
  }

  static const char* value(const ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
Header header\n\
actionlib_msgs/GoalStatus status\n\
MoveGroupFeedback feedback\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: actionlib_msgs/GoalStatus\n\
GoalID goal_id\n\
uint8 status\n\
uint8 PENDING         = 0   # The goal has yet to be processed by the action server\n\
uint8 ACTIVE          = 1   # The goal is currently being processed by the action server\n\
uint8 PREEMPTED       = 2   # The goal received a cancel request after it started executing\n\
                            #   and has since completed its execution (Terminal State)\n\
uint8 SUCCEEDED       = 3   # The goal was achieved successfully by the action server (Terminal State)\n\
uint8 ABORTED         = 4   # The goal was aborted during execution by the action server due\n\
                            #    to some failure (Terminal State)\n\
uint8 REJECTED        = 5   # The goal was rejected by the action server without being processed,\n\
                            #    because the goal was unattainable or invalid (Terminal State)\n\
uint8 PREEMPTING      = 6   # The goal received a cancel request after it started executing\n\
                            #    and has not yet completed execution\n\
uint8 RECALLING       = 7   # The goal received a cancel request before it started executing,\n\
                            #    but the action server has not yet confirmed that the goal is canceled\n\
uint8 RECALLED        = 8   # The goal received a cancel request before it started executing\n\
                            #    and was successfully cancelled (Terminal State)\n\
uint8 LOST            = 9   # An action client can determine that a goal is LOST. This should not be\n\
                            #    sent over the wire by an action server\n\
\n\
#Allow for the user to associate a string with GoalStatus for debugging\n\
string text\n\
\n\
\n\
================================================================================\n\
MSG: actionlib_msgs/GoalID\n\
# The stamp should store the time at which this goal was requested.\n\
# It is used by an action server when it tries to preempt all\n\
# goals that were requested before a certain time\n\
time stamp\n\
\n\
# The id provides a way to associate feedback and\n\
# result message with specific goal requests. The id\n\
# specified must be unique.\n\
string id\n\
\n\
\n\
================================================================================\n\
MSG: moveit_msgs/MoveGroupFeedback\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
# The internal state that the move group action currently is in\n\
string state\n\
\n\
";
  }

  static const char* value(const ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.status);
      stream.next(m.feedback);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct MoveGroupActionFeedback_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::moveit_msgs::MoveGroupActionFeedback_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "status: ";
    s << std::endl;
    Printer< ::actionlib_msgs::GoalStatus_<ContainerAllocator> >::stream(s, indent + "  ", v.status);
    s << indent << "feedback: ";
    s << std::endl;
    Printer< ::moveit_msgs::MoveGroupFeedback_<ContainerAllocator> >::stream(s, indent + "  ", v.feedback);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MOVEIT_MSGS_MESSAGE_MOVEGROUPACTIONFEEDBACK_H
