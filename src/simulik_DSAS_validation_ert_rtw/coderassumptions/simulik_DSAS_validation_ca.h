/*
 * File: simulik_DSAS_validation_ca.h
 *
 * Abstract: Tests assumptions in the generated code.
 */

#ifndef SIMULIK_DSAS_VALIDATION_CA_H
#define SIMULIK_DSAS_VALIDATION_CA_H

/* preprocessor validation checks */
#include "simulik_DSAS_validation_ca_preproc.h"
#include "coder_assumptions_hwimpl.h"

/* variables holding test results */
extern CA_HWImpl_TestResults CA_simulik_DSAS_validation_HWRes;
extern CA_PWS_TestResults CA_simulik_DSAS_validation_PWSRes;

/* variables holding "expected" and "actual" hardware implementation */
extern const CA_HWImpl CA_simulik_DSAS_validation_ExpHW;
extern CA_HWImpl CA_simulik_DSAS_validation_ActHW;

/* entry point function to run tests */
void simulik_DSAS_validation_caRunTests(void);

#endif                                 /* SIMULIK_DSAS_VALIDATION_CA_H */
