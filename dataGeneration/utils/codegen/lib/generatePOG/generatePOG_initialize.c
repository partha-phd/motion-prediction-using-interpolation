/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * generatePOG_initialize.c
 *
 * Code generation for function 'generatePOG_initialize'
 *
 */

/* Include files */
#include "generatePOG_initialize.h"
#include "generatePOG_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void generatePOG_initialize(void)
{
  omp_init_nest_lock(&generatePOG_nestLockGlobal);
  isInitialized_generatePOG = true;
}

/* End of code generation (generatePOG_initialize.c) */
