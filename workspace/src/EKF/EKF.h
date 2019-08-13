//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: EKF.h
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
#ifndef RTW_HEADER_EKF_h_
#define RTW_HEADER_EKF_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef EKF_COMMON_INCLUDES_
# define EKF_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 // EKF_COMMON_INCLUDES_

#include "EKF_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

// Block signals (default storage)
typedef struct {
  SL_Bus_EKF_sensor_msgs_Imu In1;      // '<S14>/In1'
  SL_Bus_EKF_sensor_msgs_Imu b_varargout_2;
  real_T Jacobian[36];
  real_T Jacobian_m[36];
  real_T dHdx[6];
  real_T imvec[6];
  real_T z[6];
  real_T Ff[6];
  SL_Bus_EKF_geometry_msgs_Vector3 BusAssignment1;// '<Root>/Bus Assignment1'
  SL_Bus_EKF_geometry_msgs_Vector3 BusAssignment;// '<Root>/Bus Assignment'
  real_T TmpSignalConversionAtSFunct[2];// '<S10>/Predict'
  real_T epsilon;
  real_T z_c;
  real_T z_k;
  SL_Bus_EKF_barc_ECU In1_e;           // '<S13>/In1'
  SL_Bus_EKF_barc_ECU b_varargout_2_c;
} B_EKF_T;

// Block states (default storage) for system '<Root>'
typedef struct {
  robotics_slros_internal_block_T obj; // '<S5>/SinkBlock'
  robotics_slros_internal_block_T obj_l;// '<S4>/SinkBlock'
  robotics_slros_internal_blo_b_T obj_e;// '<S7>/SourceBlock'
  robotics_slros_internal_blo_b_T obj_d;// '<S6>/SourceBlock'
  real_T P[36];                        // '<S3>/DataStoreMemory - P'
  real_T x[6];                         // '<S3>/DataStoreMemory - x'
} DW_EKF_T;

// Parameters (default storage)
struct P_EKF_T_ {
  SL_Bus_EKF_sensor_msgs_Imu Out1_Y0;  // Computed Parameter: Out1_Y0
                                       //  Referenced by: '<S14>/Out1'

  SL_Bus_EKF_sensor_msgs_Imu Constant_Value;// Computed Parameter: Constant_Value
                                            //  Referenced by: '<S7>/Constant'

  SL_Bus_EKF_geometry_msgs_Vector3 Constant_Value_l;// Computed Parameter: Constant_Value_l
                                                    //  Referenced by: '<S2>/Constant'

  SL_Bus_EKF_geometry_msgs_Vector3 Constant_Value_h;// Computed Parameter: Constant_Value_h
                                                    //  Referenced by: '<S1>/Constant'

  SL_Bus_EKF_barc_ECU Out1_Y0_l;       // Computed Parameter: Out1_Y0_l
                                       //  Referenced by: '<S13>/Out1'

  SL_Bus_EKF_barc_ECU Constant_Value_o;// Computed Parameter: Constant_Value_o
                                       //  Referenced by: '<S6>/Constant'

  real_T R1_Value;                     // Expression: p.R{1}
                                       //  Referenced by: '<S3>/R1'

  real_T MeasurementFcn1Inputs_Value;  // Expression: 0
                                       //  Referenced by: '<S3>/MeasurementFcn1Inputs'

  real_T Q_Value[36];                  // Expression: p.Q
                                       //  Referenced by: '<S3>/Q'

  real_T DataStoreMemoryP_InitialValue[36];// Expression: p.InitialCovariance
                                           //  Referenced by: '<S3>/DataStoreMemory - P'

  real_T DataStoreMemoryx_InitialValue[6];// Expression: p.InitialState
                                          //  Referenced by: '<S3>/DataStoreMemory - x'

  boolean_T yBlockOrdering_Y0;         // Computed Parameter: yBlockOrdering_Y0
                                       //  Referenced by: '<S8>/yBlockOrdering'

  boolean_T BlockOrdering_Value;       // Expression: true()
                                       //  Referenced by: '<S3>/BlockOrdering'

  boolean_T Enable1_Value;             // Expression: true()
                                       //  Referenced by: '<S3>/Enable1'

};

// Real-time Model Data Structure
struct tag_RTM_EKF_T {
  const char_T *errorStatus;
};

// Block parameters (default storage)
#ifdef __cplusplus

extern "C" {

#endif

  extern P_EKF_T EKF_P;

#ifdef __cplusplus

}
#endif

// Block signals (default storage)
extern B_EKF_T EKF_B;

// Block states (default storage)
extern DW_EKF_T EKF_DW;

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void EKF_initialize(void);
  extern void EKF_step(void);
  extern void EKF_terminate(void);

#ifdef __cplusplus

}
#endif

// Real-time Model object
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_EKF_T *const EKF_M;

#ifdef __cplusplus

}
#endif

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S8>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S10>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S3>/checkMeasurementFcn1Signals' : Unused code path elimination
//  Block '<S3>/checkStateTransitionFcnSignals' : Unused code path elimination
//  Block '<S3>/DataTypeConversion_Enable1' : Eliminate redundant data type conversion
//  Block '<S3>/DataTypeConversion_Q' : Eliminate redundant data type conversion
//  Block '<S3>/DataTypeConversion_R1' : Eliminate redundant data type conversion
//  Block '<S3>/DataTypeConversion_uMeas1' : Eliminate redundant data type conversion
//  Block '<S3>/DataTypeConversion_uState' : Eliminate redundant data type conversion
//  Block '<S3>/DataTypeConversion_y1' : Eliminate redundant data type conversion


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'EKF'
//  '<S1>'   : 'EKF/Blank Message1'
//  '<S2>'   : 'EKF/Blank Message2'
//  '<S3>'   : 'EKF/Extended Kalman Filter'
//  '<S4>'   : 'EKF/Publish'
//  '<S5>'   : 'EKF/Publish1'
//  '<S6>'   : 'EKF/Subscribe'
//  '<S7>'   : 'EKF/Subscribe1'
//  '<S8>'   : 'EKF/Extended Kalman Filter/Correct1'
//  '<S9>'   : 'EKF/Extended Kalman Filter/Output'
//  '<S10>'  : 'EKF/Extended Kalman Filter/Predict'
//  '<S11>'  : 'EKF/Extended Kalman Filter/Correct1/Correct'
//  '<S12>'  : 'EKF/Extended Kalman Filter/Predict/Predict'
//  '<S13>'  : 'EKF/Subscribe/Enabled Subsystem'
//  '<S14>'  : 'EKF/Subscribe1/Enabled Subsystem'

#endif                                 // RTW_HEADER_EKF_h_

//
// File trailer for generated code.
//
// [EOF]
//
