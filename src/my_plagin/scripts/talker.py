#!/usr/bin/env python

import rospy
from std_msgs.msg import String
import math
from geometry_msgs.msg import Twist    # message for topic /cmd_vel
from geometry_msgs.msg import Vector3

def cmd_command():
    cmd = Twist(Vector3(1,0,1), Vector3(0,0,0))
    #rospy.loginfo(cmd)
    return cmd

def open_loop():
    rospy.init_node("open_loop", anonymous=True)
    quad_vel = rospy.Publisher("cmd_vel", Twist, queue_size=1)
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        quad_vel.publish(cmd_command())
        rate.sleep()


if __name__ == "__main__":
    try:
        open_loop()
    except rospy.ROSInterruptException:
        pass
