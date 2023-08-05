/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_generatePOG_api.h
 *
 * Code generation for function 'generatePOG'
 *
 */

#ifndef _CODER_GENERATEPOG_API_H
#define _CODER_GENERATEPOG_API_H

/* Include files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

#ifndef typedef_struct0_T
#define typedef_struct0_T
typedef struct {
  emxArray_real_T *xCoordinates;
  emxArray_real_T *yCoordinates;
  real_T vehicleID;
  real_T minProb;
} struct0_T;
#endif /* typedef_struct0_T */

#ifndef typedef_emxArray_struct0_T
#define typedef_emxArray_struct0_T
typedef struct {
  struct0_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
} emxArray_struct0_T;
#endif /* typedef_emxArray_struct0_T */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void generatePOG(emxArray_real_T *x_Road, emxArray_real_T *y_Road,
                 emxArray_struct0_T *vehicleDatabase, real_T n,
                 real_T pogProb[12000], real_T pogID[12000]);

void generatePOG_api(const mxArray *const prhs[4], int32_T nlhs,
                     const mxArray *plhs[2]);

void generatePOG_atexit(void);

void generatePOG_initialize(void);

void generatePOG_terminate(void);

void generatePOG_xil_shutdown(void);

void generatePOG_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_generatePOG_api.h) */
