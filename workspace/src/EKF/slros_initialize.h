#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block EKF/Subscribe
extern SimulinkSubscriber<barc::ECU, SL_Bus_EKF_barc_ECU> Sub_EKF_30;

// For Block EKF/Subscribe1
extern SimulinkSubscriber<sensor_msgs::Imu, SL_Bus_EKF_sensor_msgs_Imu> Sub_EKF_8;

// For Block EKF/Publish
extern SimulinkPublisher<geometry_msgs::Vector3, SL_Bus_EKF_geometry_msgs_Vector3> Pub_EKF_16;

// For Block EKF/Publish1
extern SimulinkPublisher<geometry_msgs::Vector3, SL_Bus_EKF_geometry_msgs_Vector3> Pub_EKF_21;

void slros_node_init(int argc, char** argv);

#endif
