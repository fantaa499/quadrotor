#!/usr/bin/env python

import rospy
from std_msgs.msg import String
import math
from geometry_msgs.msg import Twist    # message for topic /cmd_vel
from geometry_msgs.msg import Vector3
import sys

def cmd_command():
    msg = Vector3(-5.0, 2.0, 1.0)
    #rospy.loginfo(cmd)
    return msg

def open_loop():
    rospy.init_node("getoff", anonymous=True, disable_signals=True)
    quad_vel = rospy.Publisher("/intermediate_state", Vector3, queue_size=1)
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        quad_vel.publish(cmd_command())
        rate.sleep()


if __name__ == "__main__":
    try:
        open_loop()
    except rospy.ROSInterruptException:
        pass
