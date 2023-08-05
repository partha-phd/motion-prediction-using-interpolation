/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * generatePOG_terminate.c
 *
 * Code generation for function 'generatePOG_terminate'
 *
 */

/* Include files */
#include "generatePOG_terminate.h"
#include "generatePOG_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void generatePOG_terminate(void)
{
  omp_destroy_nest_lock(&generatePOG_nestLockGlobal);
  isInitialized_generatePOG = false;
}

/* End of code generation (generatePOG_terminate.c) */
