#!/usr/bin/env python

import rospy
from std_msgs.msg import String
import math
from geometry_msgs.msg import Twist    # message for topic /cmd_vel
from geometry_msgs.msg import Vector3
import sys

def cmd_command():
    msg = Vector3(float(sys.argv[1]), float(sys.argv[2]), float(sys.argv[3]))
    #rospy.loginfo(cmd)
    return msg

def open_loop():
    rospy.init_node("genGoalState", anonymous=True)
    quad_vel = rospy.Publisher("/goal_state", Vector3, queue_size=1)
    # quad_vel = rospy.Publisher("/intermediate_state", Vector3, queue_size=1)
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        quad_vel.publish(cmd_command())
        rate.sleep()


if __name__ == "__main__":
    if len(sys.argv) != 4:
        raise TypeError, "Not 3 arguments (x, y ,z)"
    try:
        open_loop()
    except rospy.ROSInterruptException:
        pass
