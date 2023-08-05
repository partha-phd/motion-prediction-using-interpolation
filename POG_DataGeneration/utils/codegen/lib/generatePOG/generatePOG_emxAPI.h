/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * generatePOG_emxAPI.h
 *
 * Code generation for function 'generatePOG_emxAPI'
 *
 */

#ifndef GENERATEPOG_EMXAPI_H
#define GENERATEPOG_EMXAPI_H

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
extern emxArray_real_T *emxCreateND_real_T(int numDimensions, const int *size);

extern emxArray_struct0_T *emxCreateND_struct0_T(int numDimensions,
                                                 const int *size);

extern emxArray_real_T *
emxCreateWrapperND_real_T(double *data, int numDimensions, const int *size);

extern emxArray_struct0_T *emxCreateWrapperND_struct0_T(struct0_T *data,
                                                        int numDimensions,
                                                        const int *size);

extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows,
                                                int cols);

extern emxArray_struct0_T *emxCreateWrapper_struct0_T(struct0_T *data, int rows,
                                                      int cols);

extern emxArray_real_T *emxCreate_real_T(int rows, int cols);

extern emxArray_struct0_T *emxCreate_struct0_T(int rows, int cols);

extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);

extern void emxDestroyArray_struct0_T(emxArray_struct0_T *emxArray);

extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions);

extern void emxInitArray_struct0_T(emxArray_struct0_T **pEmxArray,
                                   int numDimensions);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (generatePOG_emxAPI.h) */
