/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * generatePOG.h
 *
 * Code generation for function 'generatePOG'
 *
 */

#ifndef GENERATEPOG_H
#define GENERATEPOG_H

/* Include files */
#include "generatePOG_types.h"
#include "rtwtypes.h"
#include "omp.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void generatePOG(const emxArray_real_T *x_Road,
                        const emxArray_real_T *y_Road,
                        const emxArray_struct0_T *vehicleDatabase, double n,
                        double pogProb[12000], double pogID[12000]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (generatePOG.h) */
