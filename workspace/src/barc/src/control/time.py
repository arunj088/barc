#!/usr/bin/env python
import rospy
from rospy import Publisher
from std_msgs.msg import Float64


def clock():
    rospy.init_node('clock', anonymous=True)
    rate = rospy.Rate(1/0.01)
    sim_time = 0  # in seconds
    pub = Publisher('time', Float64, queue_size=1)
    while not rospy.is_shutdown():
	ti = rospy.get_time()
        pub.publish(sim_time)
        rate.sleep()
	tf = rospy.get_time()
	sim_time += tf -ti


if __name__ == '__main__':
    try:
        clock()
    except rospy.ROSInterruptException:
        pass
