//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: EKF_types.h
//
// Code generated for Simulink model 'EKF'.
//
// Model version                  : 1.7
// Simulink Coder version         : 9.0 (R2018b) 24-May-2018
// C/C++ source code generated on : Thu Jun 13 15:11:48 2019
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_EKF_types_h_
#define RTW_HEADER_EKF_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_EKF_geometry_msgs_Vector3_
#define DEFINED_TYPEDEF_FOR_SL_Bus_EKF_geometry_msgs_Vector3_

// MsgType=geometry_msgs/Vector3
typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} SL_Bus_EKF_geometry_msgs_Vector3;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_EKF_barc_ECU_
#define DEFINED_TYPEDEF_FOR_SL_Bus_EKF_barc_ECU_

// MsgType=barc/ECU
typedef struct {
  real32_T Motor;
  real32_T Servo;
} SL_Bus_EKF_barc_ECU;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_

typedef struct {
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
} SL_Bus_ROSVariableLengthArrayInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_EKF_ros_time_Time_
#define DEFINED_TYPEDEF_FOR_SL_Bus_EKF_ros_time_Time_

// MsgType=ros_time/Time
typedef struct {
  real_T Sec;
  real_T Nsec;
} SL_Bus_EKF_ros_time_Time;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_EKF_std_msgs_Header_
#define DEFINED_TYPEDEF_FOR_SL_Bus_EKF_std_msgs_Header_

// MsgType=std_msgs/Header
typedef struct {
  uint32_T Seq;

  // PrimitiveROSType=string:IsVarLen=1:VarLenCategory=data:VarLenElem=FrameId_SL_Info:TruncateAction=warn 
  uint8_T FrameId[128];

  // IsVarLen=1:VarLenCategory=length:VarLenElem=FrameId
  SL_Bus_ROSVariableLengthArrayInfo FrameId_SL_Info;

  // MsgType=ros_time/Time
  SL_Bus_EKF_ros_time_Time Stamp;
} SL_Bus_EKF_std_msgs_Header;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_EKF_geometry_msgs_Quaternion_
#define DEFINED_TYPEDEF_FOR_SL_Bus_EKF_geometry_msgs_Quaternion_

// MsgType=geometry_msgs/Quaternion
typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
  real_T W;
} SL_Bus_EKF_geometry_msgs_Quaternion;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_EKF_sensor_msgs_Imu_
#define DEFINED_TYPEDEF_FOR_SL_Bus_EKF_sensor_msgs_Imu_

// MsgType=sensor_msgs/Imu
typedef struct {
  real_T OrientationCovariance[9];
  real_T AngularVelocityCovariance[9];
  real_T LinearAccelerationCovariance[9];

  // MsgType=std_msgs/Header
  SL_Bus_EKF_std_msgs_Header Header;

  // MsgType=geometry_msgs/Quaternion
  SL_Bus_EKF_geometry_msgs_Quaternion Orientation;

  // MsgType=geometry_msgs/Vector3
  SL_Bus_EKF_geometry_msgs_Vector3 AngularVelocity;

  // MsgType=geometry_msgs/Vector3
  SL_Bus_EKF_geometry_msgs_Vector3 LinearAcceleration;
} SL_Bus_EKF_sensor_msgs_Imu;

#endif

#ifndef typedef_robotics_slros_internal_block_T
#define typedef_robotics_slros_internal_block_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
} robotics_slros_internal_block_T;

#endif                                 //typedef_robotics_slros_internal_block_T

#ifndef typedef_robotics_slros_internal_blo_b_T
#define typedef_robotics_slros_internal_blo_b_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
} robotics_slros_internal_blo_b_T;

#endif                                 //typedef_robotics_slros_internal_blo_b_T

// Custom Type definition for MATLAB Function: '<S8>/Correct'
#ifndef struct_tag_sLFxjrpZ0dGSQBbMOvbEcyF
#define struct_tag_sLFxjrpZ0dGSQBbMOvbEcyF

struct tag_sLFxjrpZ0dGSQBbMOvbEcyF
{
  char_T FcnName[16];
  boolean_T IsSimulinkFcn;
  real_T NumberOfExtraArgumentInports;
  boolean_T HasJacobian;
  boolean_T HasAdditiveNoise;
};

#endif                                 //struct_tag_sLFxjrpZ0dGSQBbMOvbEcyF

#ifndef typedef_sLFxjrpZ0dGSQBbMOvbEcyF_EKF_T
#define typedef_sLFxjrpZ0dGSQBbMOvbEcyF_EKF_T

typedef struct tag_sLFxjrpZ0dGSQBbMOvbEcyF sLFxjrpZ0dGSQBbMOvbEcyF_EKF_T;

#endif                                 //typedef_sLFxjrpZ0dGSQBbMOvbEcyF_EKF_T

// Custom Type definition for MATLAB Function: '<S10>/Predict'
#ifndef struct_tag_sOmQkQWUklJ25PXcqCB7UGE
#define struct_tag_sOmQkQWUklJ25PXcqCB7UGE

struct tag_sOmQkQWUklJ25PXcqCB7UGE
{
  char_T FcnName[7];
  boolean_T IsSimulinkFcn;
  real_T NumberOfExtraArgumentInports;
  real_T HasJacobian;
  boolean_T HasAdditiveNoise;
};

#endif                                 //struct_tag_sOmQkQWUklJ25PXcqCB7UGE

#ifndef typedef_sOmQkQWUklJ25PXcqCB7UGE_EKF_T
#define typedef_sOmQkQWUklJ25PXcqCB7UGE_EKF_T

typedef struct tag_sOmQkQWUklJ25PXcqCB7UGE sOmQkQWUklJ25PXcqCB7UGE_EKF_T;

#endif                                 //typedef_sOmQkQWUklJ25PXcqCB7UGE_EKF_T

// Parameters (default storage)
typedef struct P_EKF_T_ P_EKF_T;

// Forward declaration for rtModel
typedef struct tag_RTM_EKF_T RT_MODEL_EKF_T;

#endif                                 // RTW_HEADER_EKF_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
