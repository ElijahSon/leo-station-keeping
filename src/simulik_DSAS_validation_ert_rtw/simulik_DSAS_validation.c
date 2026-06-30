/*
 * File: simulik_DSAS_validation.c
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

#include "simulik_DSAS_validation.h"
#include <emmintrin.h>
#include <math.h>
#include "simulik_DSAS_validation_private.h"
#include "rtwtypes.h"
#include "rt_nonfinite.h"

/* Block signals (default storage) */
B_simulik_DSAS_validation_T simulik_DSAS_validation_B;

/* Continuous states */
X_simulik_DSAS_validation_T simulik_DSAS_validation_X;

/* Disabled State Vector */
XDis_simulik_DSAS_validation_T simulik_DSAS_validation_XDis;

/* Real-time model */
static RT_MODEL_simulik_DSAS_validat_T simulik_DSAS_validation_M_;
RT_MODEL_simulik_DSAS_validat_T *const simulik_DSAS_validation_M =
  &simulik_DSAS_validation_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 13;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  simulik_DSAS_validation_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  simulik_DSAS_validation_step();
  simulik_DSAS_validation_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  simulik_DSAS_validation_step();
  simulik_DSAS_validation_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void simulik_DSAS_validation_step(void)
{
  __m128d tmp;
  __m128d tmp_0;
  __m128d tmp_1;
  __m128d tmp_2;
  __m128d tmp_3;
  real_T P_gali2loc[9];
  real_T Delta_pos_loc_1[6];
  real_T rtb_Sum[6];
  real_T Delta_pos_loc[3];
  real_T Delta_pos_loc_0[3];
  real_T tmp_4[2];
  real_T P_gali2loc_tmp;
  real_T P_gali2loc_tmp_0;
  real_T P_gali2loc_tmp_1;
  real_T P_gali2loc_tmp_2;
  real_T P_gali2loc_tmp_tmp;
  real_T P_gali2loc_tmp_tmp_0;
  real_T a;
  real_T a_tmp;
  real_T a_tmp_tmp;
  real_T rtb_Sum_0;
  real_T rtb_Sum_1;
  real_T rtb_Sum_2;
  int32_T i;
  int32_T i_0;
  int8_T XdotM_l_tmp[18];
  static const int8_T a_0[18] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 1 };

  if (rtmIsMajorTimeStep(simulik_DSAS_validation_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&simulik_DSAS_validation_M->solverInfo,
                          ((simulik_DSAS_validation_M->Timing.clockTick0+1)*
      simulik_DSAS_validation_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(simulik_DSAS_validation_M)) {
    simulik_DSAS_validation_M->Timing.t[0] = rtsiGetT
      (&simulik_DSAS_validation_M->solverInfo);
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Integrator: '<S3>/Integrator'
   *  Integrator: '<S4>/Integrator'
   */
  for (i = 0; i <= 4; i += 2) {
    tmp_2 = _mm_loadu_pd(&simulik_DSAS_validation_X.Integrator_CSTATE[i]);
    tmp_3 = _mm_loadu_pd(&simulik_DSAS_validation_X.Integrator_CSTATE_i[i]);
    _mm_storeu_pd(&rtb_Sum[i], _mm_sub_pd(tmp_2, tmp_3));
  }

  /* End of Sum: '<Root>/Sum' */

  /* MATLAB Function: '<Root>/Projection repère galiléen vers repère local' incorporates:
   *  Integrator: '<Root>/Integrator'
   *  MATLAB Function: '<Root>/f_J3'
   */
  P_gali2loc_tmp_tmp = sin(simulik_DSAS_validation_X.Integrator_CSTATE_l);
  P_gali2loc_tmp_tmp_0 = cos(simulik_DSAS_validation_X.Integrator_CSTATE_l);
  P_gali2loc_tmp = P_gali2loc_tmp_tmp_0 - 0.0 * P_gali2loc_tmp_tmp;
  P_gali2loc[0] = P_gali2loc_tmp;
  P_gali2loc_tmp_0 = 0.0 * P_gali2loc_tmp_tmp_0 + P_gali2loc_tmp_tmp;
  P_gali2loc[3] = P_gali2loc_tmp_0;
  P_gali2loc[6] = 0.0;
  P_gali2loc_tmp_1 = -0.0 * P_gali2loc_tmp_tmp_0 - P_gali2loc_tmp_tmp;
  P_gali2loc[1] = P_gali2loc_tmp_1;
  P_gali2loc_tmp_2 = -0.0 * P_gali2loc_tmp_tmp + P_gali2loc_tmp_tmp_0;
  P_gali2loc[4] = P_gali2loc_tmp_2;
  P_gali2loc[7] = 0.0;
  P_gali2loc[2] = 0.0 * P_gali2loc_tmp_tmp;
  P_gali2loc[5] = -0.0 * P_gali2loc_tmp_tmp_0;
  P_gali2loc[8] = 1.0;
  rtb_Sum_0 = rtb_Sum[1];
  rtb_Sum_1 = rtb_Sum[0];
  rtb_Sum_2 = rtb_Sum[2];
  for (i = 0; i <= 0; i += 2) {
    tmp_2 = _mm_loadu_pd(&P_gali2loc[i + 3]);
    tmp_3 = _mm_loadu_pd(&P_gali2loc[i]);
    tmp_1 = _mm_loadu_pd(&P_gali2loc[i + 6]);
    _mm_storeu_pd(&Delta_pos_loc[i], _mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp_2,
      _mm_set1_pd(rtb_Sum_0)), _mm_mul_pd(tmp_3, _mm_set1_pd(rtb_Sum_1))),
      _mm_mul_pd(tmp_1, _mm_set1_pd(rtb_Sum_2))));
  }

  for (i = 2; i < 3; i++) {
    Delta_pos_loc[i] = (P_gali2loc[i + 3] * rtb_Sum_0 + P_gali2loc[i] *
                        rtb_Sum_1) + P_gali2loc[i + 6] * rtb_Sum_2;
  }

  /* MATLAB Function: '<S4>/MATLAB Function' incorporates:
   *  Integrator: '<S4>/Integrator'
   */
  Delta_pos_loc_1[0] = simulik_DSAS_validation_X.Integrator_CSTATE_i[3];
  Delta_pos_loc_1[1] = simulik_DSAS_validation_X.Integrator_CSTATE_i[4];
  Delta_pos_loc_1[2] = simulik_DSAS_validation_X.Integrator_CSTATE_i[5];
  rtb_Sum_0 = sqrt(rt_powd_snf((simulik_DSAS_validation_X.Integrator_CSTATE_i[0]
    * simulik_DSAS_validation_X.Integrator_CSTATE_i[0] +
    simulik_DSAS_validation_X.Integrator_CSTATE_i[1] *
    simulik_DSAS_validation_X.Integrator_CSTATE_i[1]) +
    simulik_DSAS_validation_X.Integrator_CSTATE_i[2] *
    simulik_DSAS_validation_X.Integrator_CSTATE_i[2], 3.0));
  tmp_2 = _mm_set1_pd(-3.986E+14);
  tmp_3 = _mm_mul_pd(_mm_div_pd(tmp_2, _mm_set1_pd(rtb_Sum_0)), _mm_loadu_pd
                     (&simulik_DSAS_validation_X.Integrator_CSTATE_i[0]));
  _mm_storeu_pd(&Delta_pos_loc_1[3], tmp_3);
  Delta_pos_loc_1[5] = -3.986E+14 / rtb_Sum_0 *
    simulik_DSAS_validation_X.Integrator_CSTATE_i[2];
  for (i = 0; i < 6; i++) {
    simulik_DSAS_validation_B.XdotM[i] = Delta_pos_loc_1[i];
  }

  /* End of MATLAB Function: '<S4>/MATLAB Function' */

  /* MATLAB Function: '<Root>/f_J2' incorporates:
   *  Integrator: '<S3>/Integrator'
   *  MATLAB Function: '<S3>/MATLAB Function'
   */
  a_tmp_tmp = (simulik_DSAS_validation_X.Integrator_CSTATE[0] *
               simulik_DSAS_validation_X.Integrator_CSTATE[0] +
               simulik_DSAS_validation_X.Integrator_CSTATE[1] *
               simulik_DSAS_validation_X.Integrator_CSTATE[1]) +
    simulik_DSAS_validation_X.Integrator_CSTATE[2] *
    simulik_DSAS_validation_X.Integrator_CSTATE[2];
  a_tmp = sqrt(a_tmp_tmp);
  a = (3.0 / rt_powd_snf(a_tmp, 4.0) - 15.0 *
       simulik_DSAS_validation_X.Integrator_CSTATE[2] / rt_powd_snf(a_tmp, 6.0))
    * 8.77709440863242E+24;

  /* MATLAB Function: '<Root>/Projection repère galiléen vers repère local' */
  _mm_storeu_pd(&Delta_pos_loc_0[0], _mm_sub_pd(_mm_mul_pd(_mm_set_pd(0.0,
    Delta_pos_loc[1]), _mm_set_pd(Delta_pos_loc[2], 0.0010624875161092491)),
    _mm_mul_pd(_mm_set_pd(Delta_pos_loc[0], 0.0), _mm_set_pd
               (0.0010624875161092491, Delta_pos_loc[2]))));
  Delta_pos_loc_0[2] = Delta_pos_loc[0] * 0.0 - 0.0 * Delta_pos_loc[1];
  rtb_Sum_0 = rtb_Sum[4];
  rtb_Sum_1 = rtb_Sum[3];
  rtb_Sum_2 = rtb_Sum[5];
  for (i = 0; i <= 0; i += 2) {
    tmp_3 = _mm_loadu_pd(&Delta_pos_loc[i]);
    _mm_storeu_pd(&Delta_pos_loc_1[i], tmp_3);
    tmp_3 = _mm_loadu_pd(&P_gali2loc[i + 3]);
    tmp_1 = _mm_loadu_pd(&P_gali2loc[i]);
    tmp = _mm_loadu_pd(&P_gali2loc[i + 6]);
    tmp_0 = _mm_loadu_pd(&Delta_pos_loc_0[i]);
    _mm_storeu_pd(&Delta_pos_loc_1[i + 3], _mm_add_pd(_mm_add_pd(_mm_add_pd
      (_mm_mul_pd(tmp_3, _mm_set1_pd(rtb_Sum_0)), _mm_mul_pd(tmp_1, _mm_set1_pd
      (rtb_Sum_1))), _mm_mul_pd(tmp, _mm_set1_pd(rtb_Sum_2))), tmp_0));
  }

  for (i = 2; i < 3; i++) {
    Delta_pos_loc_1[i] = Delta_pos_loc[i];
    Delta_pos_loc_1[i + 3] = ((P_gali2loc[i + 3] * rtb_Sum_0 + P_gali2loc[i] *
      rtb_Sum_1) + P_gali2loc[i + 6] * rtb_Sum_2) + Delta_pos_loc_0[i];
  }

  /* Gain: '<Root>/Gain' */
  for (i = 0; i < 3; i++) {
    /* Gain: '<Root>/Gain' */
    rtb_Sum_0 = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Sum_0 += simulik_DSAS_validation_ConstP.Gain_Gain[3 * i_0 + i] *
        Delta_pos_loc_1[i_0];
    }

    /* Gain: '<Root>/Gain' */
    Delta_pos_loc[i] = rtb_Sum_0;
  }

  /* End of Gain: '<Root>/Gain' */

  /* MATLAB Function: '<S3>/MATLAB Function' */
  for (i = 0; i < 18; i++) {
    XdotM_l_tmp[i] = a_0[i];
  }

  /* MATLAB Function: '<Root>/f_J3' */
  P_gali2loc[0] = P_gali2loc_tmp;
  P_gali2loc[1] = P_gali2loc_tmp_0;
  P_gali2loc[2] = 0.0;
  P_gali2loc[3] = P_gali2loc_tmp_1;
  P_gali2loc[4] = P_gali2loc_tmp_2;
  P_gali2loc[5] = 0.0;
  P_gali2loc[6] = 0.0 * P_gali2loc_tmp_tmp;
  P_gali2loc[7] = -0.0 * P_gali2loc_tmp_tmp_0;
  P_gali2loc[8] = 1.0;
  P_gali2loc_tmp_tmp = Delta_pos_loc[0];
  P_gali2loc_tmp_tmp_0 = Delta_pos_loc[1];
  P_gali2loc_tmp = Delta_pos_loc[2];
  for (i = 0; i <= 0; i += 2) {
    tmp_3 = _mm_loadu_pd(&P_gali2loc[i + 3]);
    tmp_1 = _mm_loadu_pd(&P_gali2loc[i]);
    tmp = _mm_loadu_pd(&P_gali2loc[i + 6]);
    _mm_storeu_pd(&Delta_pos_loc[i], _mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp_3,
      _mm_set1_pd(P_gali2loc_tmp_tmp_0)), _mm_mul_pd(tmp_1, _mm_set1_pd
      (P_gali2loc_tmp_tmp))), _mm_mul_pd(tmp, _mm_set1_pd(P_gali2loc_tmp))));
  }

  for (i = 2; i < 3; i++) {
    Delta_pos_loc[i] = (P_gali2loc[i + 3] * P_gali2loc_tmp_tmp_0 + P_gali2loc[i]
                        * P_gali2loc_tmp_tmp) + P_gali2loc[i + 6] *
      P_gali2loc_tmp;
  }

  /* MATLAB Function: '<S3>/MATLAB Function' incorporates:
   *  Integrator: '<S3>/Integrator'
   */
  Delta_pos_loc_1[0] = simulik_DSAS_validation_X.Integrator_CSTATE[3];
  Delta_pos_loc_1[1] = simulik_DSAS_validation_X.Integrator_CSTATE[4];
  Delta_pos_loc_1[2] = simulik_DSAS_validation_X.Integrator_CSTATE[5];
  rtb_Sum_0 = sqrt(rt_powd_snf(a_tmp_tmp, 3.0));
  tmp_2 = _mm_mul_pd(_mm_div_pd(tmp_2, _mm_set1_pd(rtb_Sum_0)), _mm_loadu_pd
                     (&simulik_DSAS_validation_X.Integrator_CSTATE[0]));
  _mm_storeu_pd(&Delta_pos_loc_1[3], tmp_2);
  Delta_pos_loc_1[5] = -3.986E+14 / rtb_Sum_0 *
    simulik_DSAS_validation_X.Integrator_CSTATE[2];

  /* MATLAB Function: '<Root>/f_atom' incorporates:
   *  Integrator: '<S3>/Integrator'
   *  MATLAB Function: '<Root>/f_J2'
   */
  rtb_Sum_0 = sqrt((simulik_DSAS_validation_X.Integrator_CSTATE[3] *
                    simulik_DSAS_validation_X.Integrator_CSTATE[3] +
                    simulik_DSAS_validation_X.Integrator_CSTATE[4] *
                    simulik_DSAS_validation_X.Integrator_CSTATE[4]) +
                   simulik_DSAS_validation_X.Integrator_CSTATE[5] *
                   simulik_DSAS_validation_X.Integrator_CSTATE[5]);
  tmp_2 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_div_pd(_mm_mul_pd(_mm_set1_pd
    (rtb_Sum_0), _mm_set1_pd(-2.52E-12)), _mm_set1_pd(2.0)), _mm_set1_pd(191.1)),
    _mm_loadu_pd(&simulik_DSAS_validation_X.Integrator_CSTATE[3])), _mm_div_pd
                     (_mm_mul_pd(_mm_set1_pd(a), _mm_loadu_pd
    (&simulik_DSAS_validation_X.Integrator_CSTATE[0])), _mm_set1_pd(a_tmp)));
  _mm_storeu_pd(&tmp_4[0], tmp_2);

  /* Sum: '<Root>/Add' incorporates:
   *  Integrator: '<S3>/Integrator'
   *  MATLAB Function: '<Root>/f_J2'
   *  MATLAB Function: '<Root>/f_atom'
   */
  a_tmp_tmp = tmp_4[0];
  P_gali2loc_tmp_tmp = tmp_4[1];
  a_tmp = rtb_Sum_0 * -2.52E-12 / 2.0 / 191.1 *
    simulik_DSAS_validation_X.Integrator_CSTATE[5] + a *
    simulik_DSAS_validation_X.Integrator_CSTATE[2] / a_tmp;

  /* MATLAB Function: '<S3>/MATLAB Function' */
  a = Delta_pos_loc[1];
  P_gali2loc_tmp_tmp_0 = Delta_pos_loc[0];
  P_gali2loc_tmp = Delta_pos_loc[2];
  for (i = 0; i < 6; i++) {
    P_gali2loc_tmp_0 = XdotM_l_tmp[i + 6];
    P_gali2loc_tmp_1 = XdotM_l_tmp[i];
    P_gali2loc_tmp_2 = XdotM_l_tmp[i + 12];
    simulik_DSAS_validation_B.XdotM_l[i] = (((P_gali2loc_tmp_0 * a +
      P_gali2loc_tmp_1 * P_gali2loc_tmp_tmp_0) + P_gali2loc_tmp_2 *
      P_gali2loc_tmp) + Delta_pos_loc_1[i]) + ((P_gali2loc_tmp_0 *
      P_gali2loc_tmp_tmp + P_gali2loc_tmp_1 * a_tmp_tmp) + P_gali2loc_tmp_2 *
      a_tmp);
  }

  if (rtmIsMajorTimeStep(simulik_DSAS_validation_M)) {
    rt_ertODEUpdateContinuousStates(&simulik_DSAS_validation_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++simulik_DSAS_validation_M->Timing.clockTick0;
    simulik_DSAS_validation_M->Timing.t[0] = rtsiGetSolverStopTime
      (&simulik_DSAS_validation_M->solverInfo);

    {
      /* Update absolute timer for sample time: [1.0s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 1.0, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      simulik_DSAS_validation_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void simulik_DSAS_validation_derivatives(void)
{
  XDot_simulik_DSAS_validation_T *_rtXdot;
  int32_T i;
  _rtXdot = ((XDot_simulik_DSAS_validation_T *)
             simulik_DSAS_validation_M->derivs);
  for (i = 0; i < 6; i++) {
    /* Derivatives for Integrator: '<S3>/Integrator' */
    _rtXdot->Integrator_CSTATE[i] = simulik_DSAS_validation_B.XdotM_l[i];

    /* Derivatives for Integrator: '<S4>/Integrator' */
    _rtXdot->Integrator_CSTATE_i[i] = simulik_DSAS_validation_B.XdotM[i];
  }

  /* Derivatives for Integrator: '<Root>/Integrator' incorporates:
   *  Constant: '<Root>/Constant5'
   */
  _rtXdot->Integrator_CSTATE_l = 0.0010624875161092491;
}

/* Model initialize function */
void simulik_DSAS_validation_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&simulik_DSAS_validation_M->solverInfo,
                          &simulik_DSAS_validation_M->Timing.simTimeStep);
    rtsiSetTPtr(&simulik_DSAS_validation_M->solverInfo, &rtmGetTPtr
                (simulik_DSAS_validation_M));
    rtsiSetStepSizePtr(&simulik_DSAS_validation_M->solverInfo,
                       &simulik_DSAS_validation_M->Timing.stepSize0);
    rtsiSetdXPtr(&simulik_DSAS_validation_M->solverInfo,
                 &simulik_DSAS_validation_M->derivs);
    rtsiSetContStatesPtr(&simulik_DSAS_validation_M->solverInfo, (real_T **)
                         &simulik_DSAS_validation_M->contStates);
    rtsiSetNumContStatesPtr(&simulik_DSAS_validation_M->solverInfo,
      &simulik_DSAS_validation_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&simulik_DSAS_validation_M->solverInfo,
      &simulik_DSAS_validation_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&simulik_DSAS_validation_M->solverInfo,
      &simulik_DSAS_validation_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&simulik_DSAS_validation_M->solverInfo,
      &simulik_DSAS_validation_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&simulik_DSAS_validation_M->solverInfo,
      (boolean_T**) &simulik_DSAS_validation_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&simulik_DSAS_validation_M->solverInfo,
                          (&rtmGetErrorStatus(simulik_DSAS_validation_M)));
    rtsiSetRTModelPtr(&simulik_DSAS_validation_M->solverInfo,
                      simulik_DSAS_validation_M);
  }

  rtsiSetSimTimeStep(&simulik_DSAS_validation_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&simulik_DSAS_validation_M->solverInfo,
    false);
  rtsiSetIsContModeFrozen(&simulik_DSAS_validation_M->solverInfo, false);
  simulik_DSAS_validation_M->intgData.y = simulik_DSAS_validation_M->odeY;
  simulik_DSAS_validation_M->intgData.f[0] = simulik_DSAS_validation_M->odeF[0];
  simulik_DSAS_validation_M->intgData.f[1] = simulik_DSAS_validation_M->odeF[1];
  simulik_DSAS_validation_M->intgData.f[2] = simulik_DSAS_validation_M->odeF[2];
  simulik_DSAS_validation_M->contStates = ((X_simulik_DSAS_validation_T *)
    &simulik_DSAS_validation_X);
  simulik_DSAS_validation_M->contStateDisabled =
    ((XDis_simulik_DSAS_validation_T *) &simulik_DSAS_validation_XDis);
  simulik_DSAS_validation_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&simulik_DSAS_validation_M->solverInfo, (void *)
                    &simulik_DSAS_validation_M->intgData);
  rtsiSetSolverName(&simulik_DSAS_validation_M->solverInfo,"ode3");
  rtmSetTPtr(simulik_DSAS_validation_M,
             &simulik_DSAS_validation_M->Timing.tArray[0]);
  simulik_DSAS_validation_M->Timing.stepSize0 = 1.0;

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      /* InitializeConditions for Integrator: '<S3>/Integrator' */
      simulik_DSAS_validation_X.Integrator_CSTATE[i] =
        simulik_DSAS_validation_ConstP.Integrator_IC[i];

      /* InitializeConditions for Integrator: '<S4>/Integrator' */
      simulik_DSAS_validation_X.Integrator_CSTATE_i[i] =
        simulik_DSAS_validation_ConstP.Integrator_IC_o[i];
    }

    /* InitializeConditions for Integrator: '<Root>/Integrator' */
    simulik_DSAS_validation_X.Integrator_CSTATE_l = 0.0;
  }
}

/* Model terminate function */
void simulik_DSAS_validation_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
