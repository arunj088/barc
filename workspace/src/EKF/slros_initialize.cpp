#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "EKF";

// For Block EKF/Subscribe
SimulinkSubscriber<barc::ECU, SL_Bus_EKF_barc_ECU> Sub_EKF_30;

// For Block EKF/Subscribe1
SimulinkSubscriber<sensor_msgs::Imu, SL_Bus_EKF_sensor_msgs_Imu> Sub_EKF_8;

// For Block EKF/Publish
SimulinkPublisher<geometry_msgs::Vector3, SL_Bus_EKF_geometry_msgs_Vector3> Pub_EKF_16;

// For Block EKF/Publish1
SimulinkPublisher<geometry_msgs::Vector3, SL_Bus_EKF_geometry_msgs_Vector3> Pub_EKF_21;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

