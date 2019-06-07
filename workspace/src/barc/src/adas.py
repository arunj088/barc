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
from std_msgs.msg import Float32, Float32MultiArray
from geometry_msg.msg import Vector3
from barc.msg import ECU, Encoder
from math import pi
from numpy import zeros, array
from numpy import unwrap
from tf import transformations
from pid import PID
import numpy as np
import rospy

# raw measurement variables
(roll, pitch, yaw, a_x, a_y, a_z, w_x, w_y, w_z) = zeros(9)
yaw_prev = 0
yaw_local = 0
yaw_local_prev = 0
F=0
dx=0
vel_avg = 0
prev_avg = 0
dist = 1
read_yaw0 = False
(motor, servo) = zeros(2)
location = []


# imu measurement update
def imu_callback(data):
    # units: [rad] and [rad/s]
    global yaw
    global yaw_prev, yaw0, read_yaw0, yaw_local, yaw_local_prev

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
    alpha = 0.02 / (0.01 + 0.02)  # alpha = stime/(time constant + stime)
    if yaw_unfiltered == 0:
        yaw_local = 0
    else:
        yaw_local = alpha * yaw_unfiltered + (1 - alpha) * yaw_local_prev

    yaw_local_prev = yaw_local

def pose_callback(data):
    global est_yaw 
    est_yaw = data.Z

def laser_callback(data):
    global dist
    dist = data.ranges[0]

"""
def vel_callback(data):
    global vel_avg, prev_avg
    avg = (data.FL + data.FR)/2*np.cos(dx)
    #filtering
    alpha = 0.02/(0.3 + 0.02)  # alpha = stime/(time constant + stime)
    if avg == 0:
        new_avg = 0
    else:
        new_avg = alpha * avg + (1-alpha) * prev_avg
    prev_avg = new_avg
    vel_avg = new_avg
"""   
   
"""

def range_callback(msg):
    global location
    x = []
    size = np.size(msg.data)/2
    mat = np.reshape(msg.data, [size,2])
    for i in range(size):
        x = np.append(x, mat[i][0])
    x = np.sort(x)
    if not len(x):
        location = []
    else:
        location = x[0]  # the nearest x value
    print(location)
"""

def control():
    global read_yaw0, yaw_local, est_yaw
    # global location

    # initialize ROS node
    init_node('adas', anonymous=True)
    Subscriber('imu/data', Imu, imu_callback)
    Subscriber('scan', LaserScan, laser_callback)
    # Subscriber('vel_est', Encoder, vel_callback)
    # Subscriber('range', Float32MultiArray, range_callback)
    Subscriber('pose_estimate', Vector3, pose_callback)
    ecu_pub = Publisher('ecu', ECU, queue_size=1)
    encoder_pub = Publisher('filtered_vel', Float32, queue_size=1)
    yaw_pub = Publisher('filtered_yaw', Float32, queue_size=1)
    scenario = (get_param("adas/scenario"))
    (p, i, d) = (get_param("adas/PID")[0], get_param("adas/PID")[1], get_param("adas/PID")[2])
    stime = 0.02        # simulation time step
    rate = Rate(1/stime)
    aeb = False
    setReference = False
    setReference1 = False
    trigger = False
    pid = PID(P=p, I=i, D=d)
    t_i = 0.0
    (t0, tf, ttc) = (0, 0, 0)
    while not is_shutdown():
        t0 = rospy.get_time()
        if scenario == "AEB":
            # if 0.0 < location < 15.0:     # for camera based detection
            if dist < 1:
                if not aeb:
                    aeb = True
            else:
                aeb = False
            if aeb:
                if not setReference:
                    pid.setPoint(0)
                    setReference = True
                (F, dx) = (-1/dist*3, 0)
            else:
                setReference = False
                (F, dx) = (2.0, 0.0)
        elif scenario == "Lane Change":
            if t_i >= 50:
                (F, dx) = (0, 0)
            else:
                # if 0.0 < location < 15.0:  #  for camera based detection
                if dist < 1:
                    if not trigger:
                        trigger = True
                        x1 = dist
                        ttc = vel_avg * x1
                        net_time = ttc + t_i
                if trigger:
                    if net_time >= t_i:
                        if not setReference:
                            pid.setPoint(30/57.3)
                            setReference = True
                            setReference1 = False
                        (F, dx) = (3, pid.update(est_yaw, stime))
                    else:
                        if not setReference1:
                            pid.setPoint(0)
                            setReference1 = True
                            setReference = False
                        (F, dx) = (3, pid.update(est_yaw, stime))
                else:
                    (F, dx) = (3, 0)
                    trigger = False
                    setReference1 = False
                    setReference = False

        ecu_pub.publish(ECU(F, dx))
        encoder_pub.publish(Float32(vel_avg))
        yaw_pub.publish(Float32(yaw_local))
        rate.sleep()
        tf = rospy.get_time()
        t_elapsed = tf - t0
        t_i += t_elapsed
        print('time elapsed=' + str(t_i) + '\nloop time=' + str(t_elapsed))
        print('ttc=' + str(ttc))
        print('vel avg=' +str(vel_avg))
        print('range=' +str(dist))

if __name__ == '__main__':
    try:
        control()
    except ROSInterruptException:
        pass
