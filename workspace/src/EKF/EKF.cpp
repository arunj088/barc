//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: EKF.cpp
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
#include "EKF.h"
#include "EKF_private.h"

// Block signals (default storage)
B_EKF_T EKF_B;

// Block states (default storage)
DW_EKF_T EKF_DW;

// Real-time model
RT_MODEL_EKF_T EKF_M_;
RT_MODEL_EKF_T *const EKF_M = &EKF_M_;

// Forward declaration for local functions
static void EKF_Bicycle(real_T x[6], const real_T ip[2]);
static void matlabCodegenHandle_matlabCo_bd(robotics_slros_internal_blo_b_T *obj);
static void matlabCodegenHandle_matlabCodeg(robotics_slros_internal_block_T *obj);

// Function for MATLAB Function: '<S10>/Predict'
static void EKF_Bicycle(real_T x[6], const real_T ip[2])
{
  real_T Ff;
  real_T Cd;
  real_T delta;
  real_T Fyf;
  real_T Fyr;
  boolean_T ip_0;
  int32_T i;
  Ff = 0.12902;
  Cd = 0.33267;
  delta = ip[1];
  Fyf = (atan((0.125 * x[2] + x[1]) / x[0]) - ip[1]) * -6.0826;
  Fyr = atan((x[1] - 0.125 * x[2]) / x[0]) * -6.0826;
  if (ip[0] == 0.0) {
    Cd = 0.0;
    Ff = 0.0;
    Fyf = 0.0;
    Fyr = 0.0;
    delta = 0.0;
  }

  Ff = ((((ip[0] * 1.7675 - Fyf * sin(delta)) * 0.26315789473684209 + x[2] * x[1])
         - x[0] * x[0] * Cd) - Ff) * 0.01 + x[0];
  delta = cos(delta);
  Cd = ((Fyf * delta + Fyr) * 0.26315789473684209 + -x[2] * Ff) * 0.01 + x[1];
  delta = (0.125 * Fyf * delta - 0.125 * Fyr) * 0.04821368304324767 + x[2];
  ip_0 = (ip[0] == 0.0);
  EKF_B.Ff[0] = Ff;
  EKF_B.Ff[1] = Cd;
  EKF_B.Ff[2] = delta;
  Fyf = sin(x[5]);
  Fyr = cos(x[5]);
  EKF_B.Ff[3] = (Ff * Fyr - Cd * Fyf) * 0.01 + x[3];
  EKF_B.Ff[4] = (Ff * Fyf + Cd * Fyr) * 0.01 + x[4];
  EKF_B.Ff[5] = 0.01 * delta + x[5];
  for (i = 0; i < 6; i++) {
    if (ip_0) {
      x[i] = 0.0;
    } else {
      x[i] = EKF_B.Ff[i];
    }
  }
}

static void matlabCodegenHandle_matlabCo_bd(robotics_slros_internal_blo_b_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

static void matlabCodegenHandle_matlabCodeg(robotics_slros_internal_block_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

// Model step function
void EKF_step(void)
{
  int32_T j;
  static const int8_T a[6] = { 0, 0, 1, 0, 0, 0 };

  boolean_T b_varargout_1;
  int32_T i;
  int32_T i_0;
  int32_T Jacobian_tmp;

  // Outputs for Atomic SubSystem: '<Root>/Subscribe1'
  // MATLABSystem: '<S7>/SourceBlock' incorporates:
  //   Inport: '<S14>/In1'

  b_varargout_1 = Sub_EKF_8.getLatestMessage(&EKF_B.b_varargout_2);

  // Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S14>/Enable'

  if (b_varargout_1) {
    EKF_B.In1 = EKF_B.b_varargout_2;
  }

  // End of MATLABSystem: '<S7>/SourceBlock'
  // End of Outputs for SubSystem: '<S7>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe1'

  // Outputs for Enabled SubSystem: '<S3>/Correct1' incorporates:
  //   EnablePort: '<S8>/Enable'

  // Constant: '<S3>/Enable1'
  if (EKF_P.Enable1_Value) {
    // MATLAB Function: '<S8>/Correct' incorporates:
    //   Constant: '<S3>/R1'
    //   DataStoreRead: '<S8>/Data Store ReadP'
    //   DataStoreRead: '<S8>/Data Store ReadX'

    EKF_B.z_c = 0.0;
    for (i = 0; i < 6; i++) {
      EKF_B.z_c += (real_T)a[i] * EKF_DW.x[i];
      EKF_B.z[i] = a[i];
    }

    for (j = 0; j < 6; j++) {
      for (i = 0; i < 6; i++) {
        EKF_B.imvec[i] = EKF_DW.x[i];
      }

      EKF_B.epsilon = 1.4901161193847656E-8 * fabs(EKF_DW.x[j]);
      if ((1.4901161193847656E-8 > EKF_B.epsilon) || rtIsNaN(EKF_B.epsilon)) {
        EKF_B.epsilon = 1.4901161193847656E-8;
      }

      EKF_B.imvec[j] = EKF_DW.x[j] + EKF_B.epsilon;
      EKF_B.z_k = 0.0;
      for (i = 0; i < 6; i++) {
        EKF_B.z_k += EKF_B.z[i] * EKF_B.imvec[i];
      }

      EKF_B.dHdx[j] = (EKF_B.z_k - EKF_B.z_c) / EKF_B.epsilon;
    }

    EKF_B.z_c = 0.0;
    for (i = 0; i < 6; i++) {
      EKF_B.z[i] = 0.0;
      for (j = 0; j < 6; j++) {
        EKF_B.z[i] += EKF_DW.P[6 * i + j] * EKF_B.dHdx[j];
      }

      EKF_B.z_c += EKF_B.z[i] * EKF_B.dHdx[i];
    }

    EKF_B.z_c += EKF_P.R1_Value;
    EKF_B.epsilon = 0.0;
    for (i = 0; i < 6; i++) {
      EKF_B.z_k = 0.0;
      for (j = 0; j < 6; j++) {
        EKF_B.z_k += EKF_DW.P[6 * j + i] * EKF_B.dHdx[j];
      }

      EKF_B.imvec[i] = EKF_B.z_k / EKF_B.z_c;
      EKF_B.epsilon += (real_T)a[i] * EKF_DW.x[i];
    }

    EKF_B.z_c = EKF_B.In1.AngularVelocity.Z - EKF_B.epsilon;
    for (i = 0; i < 6; i++) {
      for (j = 0; j < 6; j++) {
        EKF_B.Jacobian[i + 6 * j] = EKF_B.imvec[i] * EKF_B.dHdx[j];
      }

      for (j = 0; j < 6; j++) {
        EKF_B.z_k = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          EKF_B.z_k += EKF_B.Jacobian[6 * i_0 + i] * EKF_DW.P[6 * j + i_0];
        }

        EKF_B.Jacobian_m[i + 6 * j] = EKF_DW.P[6 * j + i] - EKF_B.z_k;
      }
    }

    // DataStoreWrite: '<S8>/Data Store WriteP'
    memcpy(&EKF_DW.P[0], &EKF_B.Jacobian_m[0], 36U * sizeof(real_T));

    // DataStoreWrite: '<S8>/Data Store WriteX' incorporates:
    //   DataStoreRead: '<S8>/Data Store ReadX'
    //   MATLAB Function: '<S8>/Correct'

    for (i = 0; i < 6; i++) {
      EKF_DW.x[i] += EKF_B.imvec[i] * EKF_B.z_c;
    }

    // End of DataStoreWrite: '<S8>/Data Store WriteX'
  }

  // End of Constant: '<S3>/Enable1'
  // End of Outputs for SubSystem: '<S3>/Correct1'

  // BusAssignment: '<Root>/Bus Assignment' incorporates:
  //   DataStoreRead: '<S9>/Data Store Read'

  EKF_B.BusAssignment.X = EKF_DW.x[3];
  EKF_B.BusAssignment.Y = EKF_DW.x[4];
  EKF_B.BusAssignment.Z = EKF_DW.x[5];

  // Outputs for Atomic SubSystem: '<Root>/Publish'
  // MATLABSystem: '<S4>/SinkBlock'
  Pub_EKF_16.publish(&EKF_B.BusAssignment);

  // End of Outputs for SubSystem: '<Root>/Publish'

  // BusAssignment: '<Root>/Bus Assignment1' incorporates:
  //   DataStoreRead: '<S9>/Data Store Read'

  EKF_B.BusAssignment1.X = EKF_DW.x[0];
  EKF_B.BusAssignment1.Y = EKF_DW.x[1];
  EKF_B.BusAssignment1.Z = EKF_DW.x[2];

  // Outputs for Atomic SubSystem: '<Root>/Publish1'
  // MATLABSystem: '<S5>/SinkBlock'
  Pub_EKF_21.publish(&EKF_B.BusAssignment1);

  // End of Outputs for SubSystem: '<Root>/Publish1'

  // Outputs for Atomic SubSystem: '<Root>/Subscribe'
  // MATLABSystem: '<S6>/SourceBlock' incorporates:
  //   Inport: '<S13>/In1'

  b_varargout_1 = Sub_EKF_30.getLatestMessage(&EKF_B.b_varargout_2_c);

  // Outputs for Enabled SubSystem: '<S6>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S13>/Enable'

  if (b_varargout_1) {
    EKF_B.In1_e = EKF_B.b_varargout_2_c;
  }

  // End of MATLABSystem: '<S6>/SourceBlock'
  // End of Outputs for SubSystem: '<S6>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe'

  // Outputs for Atomic SubSystem: '<S3>/Predict'
  // SignalConversion: '<S12>/TmpSignal ConversionAt SFunction Inport4' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion'
  //   DataTypeConversion: '<Root>/Data Type Conversion1'
  //   MATLAB Function: '<S10>/Predict'

  EKF_B.TmpSignalConversionAtSFunct[0] = EKF_B.In1_e.Motor;
  EKF_B.TmpSignalConversionAtSFunct[1] = EKF_B.In1_e.Servo;

  // MATLAB Function: '<S10>/Predict' incorporates:
  //   DataStoreRead: '<S10>/Data Store ReadX'

  for (i = 0; i < 6; i++) {
    EKF_B.z[i] = EKF_DW.x[i];
  }

  EKF_Bicycle(EKF_B.z, EKF_B.TmpSignalConversionAtSFunct);
  for (j = 0; j < 6; j++) {
    for (i = 0; i < 6; i++) {
      EKF_B.imvec[i] = EKF_DW.x[i];
    }

    EKF_B.epsilon = 1.4901161193847656E-8 * fabs(EKF_DW.x[j]);
    if ((1.4901161193847656E-8 > EKF_B.epsilon) || rtIsNaN(EKF_B.epsilon)) {
      EKF_B.epsilon = 1.4901161193847656E-8;
    }

    EKF_B.imvec[j] = EKF_DW.x[j] + EKF_B.epsilon;
    EKF_Bicycle(EKF_B.imvec, EKF_B.TmpSignalConversionAtSFunct);
    for (i = 0; i < 6; i++) {
      EKF_B.Jacobian[i + 6 * j] = (EKF_B.imvec[i] - EKF_B.z[i]) / EKF_B.epsilon;
    }
  }

  // DataStoreWrite: '<S10>/Data Store WriteX' incorporates:
  //   MATLAB Function: '<S10>/Predict'

  EKF_Bicycle(EKF_DW.x, EKF_B.TmpSignalConversionAtSFunct);

  // MATLAB Function: '<S10>/Predict' incorporates:
  //   DataStoreRead: '<S10>/Data Store ReadP'

  for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
      Jacobian_tmp = j + 6 * i;
      EKF_B.Jacobian_m[Jacobian_tmp] = 0.0;
      for (i_0 = 0; i_0 < 6; i_0++) {
        EKF_B.Jacobian_m[Jacobian_tmp] = EKF_B.Jacobian[6 * i_0 + j] * EKF_DW.P
          [6 * i + i_0] + EKF_B.Jacobian_m[6 * i + j];
      }
    }
  }

  // DataStoreWrite: '<S10>/Data Store WriteP' incorporates:
  //   Constant: '<S3>/Q'
  //   MATLAB Function: '<S10>/Predict'

  for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
      EKF_B.z_k = 0.0;
      for (i_0 = 0; i_0 < 6; i_0++) {
        EKF_B.z_k += EKF_B.Jacobian_m[6 * i_0 + i] * EKF_B.Jacobian[6 * i_0 + j];
      }

      EKF_DW.P[i + 6 * j] = EKF_P.Q_Value[6 * j + i] + EKF_B.z_k;
    }
  }

  // End of DataStoreWrite: '<S10>/Data Store WriteP'
  // End of Outputs for SubSystem: '<S3>/Predict'
}

// Model initialize function
void EKF_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // initialize error status
  rtmSetErrorStatus(EKF_M, (NULL));

  // block I/O
  (void) memset(((void *) &EKF_B), 0,
                sizeof(B_EKF_T));

  // states (dwork)
  (void) memset((void *)&EKF_DW, 0,
                sizeof(DW_EKF_T));

  {
    int32_T i;
    static const char_T tmp[10] = { '/', 's', 't', 'a', 't', 'e', '_', 'e', 's',
      't' };

    static const char_T tmp_0[9] = { '/', 'p', 'o', 's', 'e', '_', 'e', 's', 't'
    };

    static const char_T tmp_1[9] = { '/', 'i', 'm', 'u', '/', 'd', 'a', 't', 'a'
    };

    char_T tmp_2[5];
    char_T tmp_3[11];
    char_T tmp_4[10];

    // Start for Atomic SubSystem: '<Root>/Subscribe1'
    // Start for MATLABSystem: '<S7>/SourceBlock'
    EKF_DW.obj_e.matlabCodegenIsDeleted = true;
    EKF_DW.obj_e.isInitialized = 0;
    EKF_DW.obj_e.matlabCodegenIsDeleted = false;
    EKF_DW.obj_e.isSetupComplete = false;
    EKF_DW.obj_e.isInitialized = 1;
    for (i = 0; i < 9; i++) {
      tmp_4[i] = tmp_1[i];
    }

    tmp_4[9] = '\x00';
    Sub_EKF_8.createSubscriber(tmp_4, 1);
    EKF_DW.obj_e.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S7>/SourceBlock'
    // End of Start for SubSystem: '<Root>/Subscribe1'

    // Start for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S4>/SinkBlock'
    EKF_DW.obj_l.matlabCodegenIsDeleted = true;
    EKF_DW.obj_l.isInitialized = 0;
    EKF_DW.obj_l.matlabCodegenIsDeleted = false;
    EKF_DW.obj_l.isSetupComplete = false;
    EKF_DW.obj_l.isInitialized = 1;
    for (i = 0; i < 9; i++) {
      tmp_4[i] = tmp_0[i];
    }

    tmp_4[9] = '\x00';
    Pub_EKF_16.createPublisher(tmp_4, 1);
    EKF_DW.obj_l.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S4>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish'

    // Start for Atomic SubSystem: '<Root>/Publish1'
    // Start for MATLABSystem: '<S5>/SinkBlock'
    EKF_DW.obj.matlabCodegenIsDeleted = true;
    EKF_DW.obj.isInitialized = 0;
    EKF_DW.obj.matlabCodegenIsDeleted = false;
    EKF_DW.obj.isSetupComplete = false;
    EKF_DW.obj.isInitialized = 1;
    for (i = 0; i < 10; i++) {
      tmp_3[i] = tmp[i];
    }

    tmp_3[10] = '\x00';
    Pub_EKF_21.createPublisher(tmp_3, 1);
    EKF_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S5>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish1'

    // Start for Atomic SubSystem: '<Root>/Subscribe'
    // Start for MATLABSystem: '<S6>/SourceBlock'
    EKF_DW.obj_d.matlabCodegenIsDeleted = true;
    EKF_DW.obj_d.isInitialized = 0;
    EKF_DW.obj_d.matlabCodegenIsDeleted = false;
    EKF_DW.obj_d.isSetupComplete = false;
    EKF_DW.obj_d.isInitialized = 1;
    tmp_2[0] = '/';
    tmp_2[1] = 'e';
    tmp_2[2] = 'c';
    tmp_2[3] = 'u';
    tmp_2[4] = '\x00';
    Sub_EKF_30.createSubscriber(tmp_2, 1);
    EKF_DW.obj_d.isSetupComplete = true;

    // End of Start for SubSystem: '<Root>/Subscribe'

    // Start for DataStoreMemory: '<S3>/DataStoreMemory - P'
    memcpy(&EKF_DW.P[0], &EKF_P.DataStoreMemoryP_InitialValue[0], 36U * sizeof
           (real_T));

    // Start for DataStoreMemory: '<S3>/DataStoreMemory - x'
    for (i = 0; i < 6; i++) {
      EKF_DW.x[i] = EKF_P.DataStoreMemoryx_InitialValue[i];
    }

    // End of Start for DataStoreMemory: '<S3>/DataStoreMemory - x'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1'
    // SystemInitialize for Enabled SubSystem: '<S7>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S14>/Out1'
    EKF_B.In1 = EKF_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S7>/Enabled Subsystem'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe1'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S6>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S13>/Out1'
    EKF_B.In1_e = EKF_P.Out1_Y0_l;

    // End of SystemInitialize for SubSystem: '<S6>/Enabled Subsystem'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe'
  }
}

// Model terminate function
void EKF_terminate(void)
{
  // Terminate for Atomic SubSystem: '<Root>/Subscribe1'
  // Terminate for MATLABSystem: '<S7>/SourceBlock'
  matlabCodegenHandle_matlabCo_bd(&EKF_DW.obj_e);

  // End of Terminate for SubSystem: '<Root>/Subscribe1'

  // Terminate for Atomic SubSystem: '<Root>/Publish'
  // Terminate for MATLABSystem: '<S4>/SinkBlock'
  matlabCodegenHandle_matlabCodeg(&EKF_DW.obj_l);

  // End of Terminate for SubSystem: '<Root>/Publish'

  // Terminate for Atomic SubSystem: '<Root>/Publish1'
  // Terminate for MATLABSystem: '<S5>/SinkBlock'
  matlabCodegenHandle_matlabCodeg(&EKF_DW.obj);

  // End of Terminate for SubSystem: '<Root>/Publish1'

  // Terminate for Atomic SubSystem: '<Root>/Subscribe'
  // Terminate for MATLABSystem: '<S6>/SourceBlock'
  matlabCodegenHandle_matlabCo_bd(&EKF_DW.obj_d);

  // End of Terminate for SubSystem: '<Root>/Subscribe'
}

//
// File trailer for generated code.
//
// [EOF]
//
