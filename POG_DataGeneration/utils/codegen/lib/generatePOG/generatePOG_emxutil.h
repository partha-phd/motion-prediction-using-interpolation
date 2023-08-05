/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * generatePOG_emxutil.h
 *
 * Code generation for function 'generatePOG_emxutil'
 *
 */

#ifndef GENERATEPOG_EMXUTIL_H
#define GENERATEPOG_EMXUTIL_H

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
extern void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray,
                                        int oldNumel);

extern void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_uint32_T(emxArray_uint32_T *emxArray,
                                       int oldNumel);

extern void emxFreeStruct_struct0_T(struct0_T *pStruct);

extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);

extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);

extern void emxFree_real_T(emxArray_real_T **pEmxArray);

extern void emxFree_struct0_T(emxArray_struct0_T **pEmxArray);

extern void emxFree_uint32_T(emxArray_uint32_T **pEmxArray);

extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray);

extern void emxInit_int32_T(emxArray_int32_T **pEmxArray);

extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

extern void emxInit_struct0_T(emxArray_struct0_T **pEmxArray,
                              int numDimensions);

extern void emxInit_uint32_T(emxArray_uint32_T **pEmxArray);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (generatePOG_emxutil.h) */
