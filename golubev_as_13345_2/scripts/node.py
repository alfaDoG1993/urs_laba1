#!/usr/bin/env python

import rospy

from std_msgs.msg import Int8
from std_msgs.msg import String


class funnySymbol:

    def __init__(self):
        # Subscriber
        self.sub = rospy.Subscriber("symbol_code",
                                    Int8,
                                    self.callback_sub_msg)
        # Publisher
        self.pub = rospy.Publisher("symbol",
                                   String,
                                   queue_size=1)
        rospy.spin()

    def callback_sub_msg(self, msg):
        try:
            symbol = String()
            symbol.data = chr(msg.data)
        except ValueError:
            symbol.data = "Symbol not exist!"

        self.pub.publish(symbol)



if __name__ == '__main__':
    rospy.init_node('funnySymbol')
    try:
        filter = funnySymbol()
    except rospy.ROSInterruptException:
        pass
