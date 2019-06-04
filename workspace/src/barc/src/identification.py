#!/usr/bin/env python

# Author: Arun Joshi
# Disclaimer:
# This ROS node is created as part of the Capstone Project where AEB and
# collision avoidance by lane change for a vehicle based on camera #detection is the targeted outcome.
# This code is an extension of the codes provided by the barc project ROS code-base developed
# at UC Berkeley in the Model Predictive Control (MPC) lab by Jon Gonzales
# (jon.gonzales@berkeley.edu).

from rospy import init_node, Subscriber, Publisher, get_param
from rospy import Rate, is_shutdown, ROSInterruptException
from sensor_msgs.msg import Imu, LaserScan
from std_msgs.msg import Float32
from barc.msg import ECU, Encoder
from math import pi
from numpy import zeros, array
from numpy import unwrap
from tf import transformations
import numpy as np
import rospy

# raw measurement variables
(roll, pitch, yaw, a_x, a_y, a_z, w_x, w_y, w_z) = zeros(9)
dx = 0
f = 0
yaw_prev = 0
yaw_local = 0
yaw_local_prev = 0
vel_avg = 0
prev_avg = 0
dist = 1
read_yaw0 = False
(motor, servo) = zeros(2)
(l_accel_x, l_accel_y, l_accel_z, a_vel_x, a_vel_y, a_vel_z) = zeros(6)
stime = 0.02        #simulation time step

# low pass filter
def lpf(x, x_prev, stime, t_const):
    alpha = stime / (t_const + stime)
    x = alpha * x + (1 - alpha) * x_prev
    return x

# imu measurement update
def imu_callback(data):
    # units: [rad] and [rad/s]
    global yaw
    global yaw_prev, yaw0, read_yaw0, yaw_local, stime, yaw_local_prev
    global l_accel_x, l_accel_y, l_accel_z, a_vel_x, a_vel_y, a_vel_z
    # get orientation from quaternion data, and convert to roll, pitch, yaw
    # extract angular velocity and linear acceleration data
    ori = data.orientation
    quaternion = (ori.x, ori.y, ori.z, ori.w)
    (_, _, yaw) = transformations.euler_from_quaternion(quaternion)

    # save initial measurements
    if not read_yaw0:
        read_yaw0 = True
        yaw_prev = yaw
        yaw0 = yaw

    # unwrap measurement
    yaw = unwrap(array([yaw_prev, yaw]), discont=pi)[1]
    yaw_prev = yaw
    yaw_unfiltered = yaw - yaw0
    # filtering
    if yaw_unfiltered == 0:
        yaw_local = 0
    else:
        yaw_local = lpf(yaw_unfiltered, yaw_local_prev, stime, 0.3)
    yaw_local_prev = yaw_local

    # raw linear accleration (m/s^2) from sensor
    l_accel_x = data.linear_acceleration.x
    l_accel_y = data.linear_acceleration.y
    l_accel_z = data.linear_acceleration.z
    # raw angular velocity (rad/s) from sensor
    a_vel_x = data.angular_velocity.x
    a_vel_y = data.angular_velocity.y
    a_vel_z = data.angular_velocity.z


def laser_callback(data):
    global dist
    dist = data.ranges[0]

def vel_callback(data):
    global vel_avg, prev_avg, stime, dx
    avg = (data.FL + data.FR)/2*np.cos(dx)
    #filtering
    if avg == 0:
        new_avg = 0
    else:
        new_avg = lpf(avg, prev_avg, stime, 0.3)
    prev_avg = new_avg
    vel_avg = new_avg

def control():
    global read_yaw0, yaw_local

    # initialize ROS node
    init_node('model_identification_tester', anonymous=True)
    Subscriber('imu/data', Imu, imu_callback)
    Subscriber('scan', LaserScan, laser_callback)
    Subscriber('vel_est', Encoder, vel_callback)
    ecu_pub = Publisher('ecu', ECU, queue_size=1)
    encoder_pub = Publisher('filtered_vel', Float32, queue_size=1)
    yaw_pub = Publisher('filtered_yaw', Float32, queue_size=1)
    # acquire parameter from server
    run_time = get_param("/run_time")
    step_time = get_param("/step_time")
    ip1 = get_param("/motor_input")
    ip2 = get_param("/servo_input")
    ##
    rate = Rate(1/stime)
    t_i = 0.0
    (t0, tf, ttc) = (0, 0, 0)
    while not is_shutdown():
        t0 = rospy.get_time()
        if run_time >= t_i >= step_time:
            dx = ip2
            f = ip1
        else:
            dx = 0
            f = 0
        ecu_pub.publish(ECU(f, dx))
        encoder_pub.publish(Float32(vel_avg))
        yaw_pub.publish(Float32(yaw_local))
        rate.sleep()
        tf = rospy.get_time()
        t_elapsed = tf - t0
        t_i += t_elapsed
        print('time elapsed=' + str(t_i) + '\nloop time=' + str(t_elapsed))
        print('vel avg=' + str(vel_avg))
        print('acceleration=' + str())


if __name__ == '__main__':
    try:
        control()
    except ROSInterruptException:
        pass
