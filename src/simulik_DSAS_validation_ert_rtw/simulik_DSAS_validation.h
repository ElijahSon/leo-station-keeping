/*
 * File: simulik_DSAS_validation.h
 *
 * Code generated for Simulink model 'simulik_DSAS_validation'.
 *
 * Model version                  : 2.0
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Jun 25 04:30:43 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef simulik_DSAS_validation_h_
#define simulik_DSAS_validation_h_
#ifndef simulik_DSAS_validation_COMMON_INCLUDES_
#define simulik_DSAS_validation_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                            /* simulik_DSAS_validation_COMMON_INCLUDES_ */

#include "simulik_DSAS_validation_types.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T XdotM[6];                     /* '<S4>/MATLAB Function' */
  real_T XdotM_l[6];                   /* '<S3>/MATLAB Function' */
} B_simulik_DSAS_validation_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE[6];         /* '<S3>/Integrator' */
  real_T Integrator_CSTATE_i[6];       /* '<S4>/Integrator' */
  real_T Integrator_CSTATE_l;          /* '<Root>/Integrator' */
} X_simulik_DSAS_validation_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE[6];         /* '<S3>/Integrator' */
  real_T Integrator_CSTATE_i[6];       /* '<S4>/Integrator' */
  real_T Integrator_CSTATE_l;          /* '<Root>/Integrator' */
} XDot_simulik_DSAS_validation_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[6];      /* '<S3>/Integrator' */
  boolean_T Integrator_CSTATE_i[6];    /* '<S4>/Integrator' */
  boolean_T Integrator_CSTATE_l;       /* '<Root>/Integrator' */
} XDis_simulik_DSAS_validation_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: X_init_chasseur
   * Referenced by: '<S3>/Integrator'
   */
  real_T Integrator_IC[6];

  /* Expression: X_init_cible
   * Referenced by: '<S4>/Integrator'
   */
  real_T Integrator_IC_o[6];

  /* Expression: -Ki
   * Referenced by: '<Root>/Gain'
   */
  real_T Gain_Gain[18];
} ConstP_simulik_DSAS_validatio_T;

/* Real-time Model Data Structure */
struct tag_RTM_simulik_DSAS_validati_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_simulik_DSAS_validation_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_simulik_DSAS_validation_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[13];
  real_T odeF[3][13];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (default storage) */
extern B_simulik_DSAS_validation_T simulik_DSAS_validation_B;

/* Continuous states (default storage) */
extern X_simulik_DSAS_validation_T simulik_DSAS_validation_X;

/* Disabled states (default storage) */
extern XDis_simulik_DSAS_validation_T simulik_DSAS_validation_XDis;

/* Constant parameters (default storage) */
extern const ConstP_simulik_DSAS_validatio_T simulik_DSAS_validation_ConstP;

/* Model entry point functions */
extern void simulik_DSAS_validation_initialize(void);
extern void simulik_DSAS_validation_step(void);
extern void simulik_DSAS_validation_terminate(void);

/* Real-time Model object */
extern RT_MODEL_simulik_DSAS_validat_T *const simulik_DSAS_validation_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Clock' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<Root>/Scope1' : Unused code path elimination
 * Block '<Root>/Scope2' : Unused code path elimination
 * Block '<Root>/Scope3' : Unused code path elimination
 * Block '<Root>/Scope4' : Unused code path elimination
 * Block '<S4>/Scope' : Unused code path elimination
 * Block '<Root>/To Workspace' : Unused code path elimination
 * Block '<Root>/To Workspace1' : Unused code path elimination
 * Block '<Root>/To Workspace2' : Unused code path elimination
 * Block '<Root>/To Workspace3' : Unused code path elimination
 * Block '<Root>/To Workspace4' : Unused code path elimination
 * Block '<Root>/To Workspace5' : Unused code path elimination
 * Block '<Root>/Manual Switch' : Eliminated due to constant selection input
 * Block '<Root>/Manual Switch1' : Eliminated due to constant selection input
 * Block '<Root>/zero1' : Unused code path elimination
 * Block '<Root>/zero3' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'simulik_DSAS_validation'
 * '<S1>'   : 'simulik_DSAS_validation/Projection des positions et vitesses  entre Ch et Ci  dans le repere local '
 * '<S2>'   : 'simulik_DSAS_validation/Projection repère galiléen vers repère local'
 * '<S3>'   : 'simulik_DSAS_validation/Satellite chacheur'
 * '<S4>'   : 'simulik_DSAS_validation/Subsystem1'
 * '<S5>'   : 'simulik_DSAS_validation/f_J2'
 * '<S6>'   : 'simulik_DSAS_validation/f_J3'
 * '<S7>'   : 'simulik_DSAS_validation/f_atom'
 * '<S8>'   : 'simulik_DSAS_validation/Satellite chacheur/MATLAB Function'
 * '<S9>'   : 'simulik_DSAS_validation/Subsystem1/MATLAB Function'
 */
#endif                                 /* simulik_DSAS_validation_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
