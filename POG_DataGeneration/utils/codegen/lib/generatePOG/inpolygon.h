/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * inpolygon.h
 *
 * Code generation for function 'inpolygon'
 *
 */

#ifndef INPOLYGON_H
#define INPOLYGON_H

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
void b_inpolygon(const double x[5], const double y[5], const double xv[5],
                 const double yv[5], boolean_T in[5]);

void inpolygon(const emxArray_real_T *x, const emxArray_real_T *y,
               const double xv[5], const double yv[5], emxArray_boolean_T *in);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (inpolygon.h) */
