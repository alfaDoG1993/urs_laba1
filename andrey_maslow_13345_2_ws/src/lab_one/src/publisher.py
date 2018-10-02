#!/usr/bin/env python
import rospy
from std_msgs import msg
import math as m

def talker():
    rospy.init_node('lab_one')
    pub = rospy.Publisher('rounded', msg.Int32, queue_size=1)

    def callback(data):
        pub.publish(msg.Int32(m.floor(data.data)))

    sub = rospy.Subscriber('pull_down', msg.Float32, callback=callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
