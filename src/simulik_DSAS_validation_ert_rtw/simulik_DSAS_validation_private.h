/*
 * File: simulik_DSAS_validation_private.h
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

#ifndef simulik_DSAS_validation_private_h_
#define simulik_DSAS_validation_private_h_
#include "rtwtypes.h"
#include "simulik_DSAS_validation_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern real_T rt_powd_snf(real_T u0, real_T u1);

/* private model entry point functions */
extern void simulik_DSAS_validation_derivatives(void);

#endif                                 /* simulik_DSAS_validation_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
