/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * inpolygon.c
 *
 * Code generation for function 'inpolygon'
 *
 */

/* Include files */
#include "inpolygon.h"
#include "generatePOG_emxutil.h"
#include "generatePOG_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static void computeScaleFactors(const double xv[5], const double yv[5],
                                int nloops, const int first[5],
                                const int last[5], double scale[5]);

static void contrib(double x1, double b_y1, double x2, double y2,
                    signed char quad1, signed char quad2, double scale,
                    signed char *diffQuad, boolean_T *onj);

static void countLoops(const double xv[5], const double yv[5], int *nloops,
                       int first[5], int last[5]);

static boolean_T scalarInpolygon(double xj, double yj, const double xv[5],
                                 const double yv[5], int nloops,
                                 const int first[5], const int last[5],
                                 double minxv, double maxxv, double minyv,
                                 double maxyv, const double scale[5]);

/* Function Definitions */
static void computeScaleFactors(const double xv[5], const double yv[5],
                                int nloops, const int first[5],
                                const int last[5], double scale[5])
{
  double a;
  double b;
  int b_i;
  int i;
  int i1;
  int j;
  for (i = 0; i < 5; i++) {
    scale[i] = 0.0;
  }
  for (j = 0; j < nloops; j++) {
    b_i = first[j];
    i1 = last[j] - 1;
    for (i = b_i; i <= i1; i++) {
      a = fabs(0.5 * (xv[i - 1] + xv[i]));
      b = fabs(0.5 * (yv[i - 1] + yv[i]));
      if ((a > 1.0) && (b > 1.0)) {
        a *= b;
      } else if ((b > a) || rtIsNaN(a)) {
        a = b;
      }
      scale[i - 1] = a * 6.6613381477509392E-16;
    }
    b_i = first[j];
    i1 = last[j];
    a = fabs(0.5 * (xv[i1 - 1] + xv[b_i - 1]));
    b = fabs(0.5 * (yv[i1 - 1] + yv[b_i - 1]));
    if ((a > 1.0) && (b > 1.0)) {
      a *= b;
    } else if ((b > a) || rtIsNaN(a)) {
      a = b;
    }
    scale[i1 - 1] = a * 6.6613381477509392E-16;
  }
}

static void contrib(double x1, double b_y1, double x2, double y2,
                    signed char quad1, signed char quad2, double scale,
                    signed char *diffQuad, boolean_T *onj)
{
  double cp;
  *onj = false;
  *diffQuad = (signed char)(quad2 - quad1);
  cp = x1 * y2 - x2 * b_y1;
  if (fabs(cp) < scale) {
    *onj = (x1 * x2 + b_y1 * y2 <= 0.0);
    if ((*diffQuad == 2) || (*diffQuad == -2)) {
      *diffQuad = 0;
    } else if (*diffQuad == -3) {
      *diffQuad = 1;
    } else if (*diffQuad == 3) {
      *diffQuad = -1;
    }
  } else if (cp < 0.0) {
    if (*diffQuad == 2) {
      *diffQuad = -2;
    } else if (*diffQuad == -3) {
      *diffQuad = 1;
    } else if (*diffQuad == 3) {
      *diffQuad = -1;
    }
  } else if (*diffQuad == -2) {
    *diffQuad = 2;
  } else if (*diffQuad == -3) {
    *diffQuad = 1;
  } else if (*diffQuad == 3) {
    *diffQuad = -1;
  }
}

static void countLoops(const double xv[5], const double yv[5], int *nloops,
                       int first[5], int last[5])
{
  int i;
  int kfirst;
  boolean_T exitg1;
  *nloops = 0;
  for (i = 0; i < 5; i++) {
    first[i] = 0;
    last[i] = 0;
  }
  i = 0;
  while ((i + 1 <= 5) && rtIsNaN(xv[i])) {
    i++;
  }
  while (i + 1 <= 5) {
    (*nloops)++;
    kfirst = i;
    first[*nloops - 1] = i + 1;
    exitg1 = false;
    while ((!exitg1) && (i + 1 < 5)) {
      i++;
      if (rtIsNaN(xv[i]) || rtIsNaN(yv[i])) {
        i--;
        exitg1 = true;
      }
    }
    if ((xv[i] == xv[kfirst]) && (yv[i] == yv[kfirst])) {
      last[*nloops - 1] = i;
    } else {
      last[*nloops - 1] = i + 1;
    }
    i += 2;
    while ((i + 1 <= 5) && rtIsNaN(xv[i])) {
      i++;
    }
  }
}

static boolean_T scalarInpolygon(double xj, double yj, const double xv[5],
                                 const double yv[5], int nloops,
                                 const int first[5], const int last[5],
                                 double minxv, double maxxv, double minyv,
                                 double maxyv, const double scale[5])
{
  double xv1;
  double xv2;
  double xvFirst;
  double yv1;
  double yv2;
  double yvFirst;
  int exitg1;
  int exitg2;
  int i;
  int k;
  signed char dquad;
  signed char quad1;
  signed char quad2;
  signed char quadFirst;
  signed char sdq;
  boolean_T inj;
  boolean_T onj;
  inj = false;
  if ((xj >= minxv) && (xj <= maxxv) && (yj >= minyv) && (yj <= maxyv)) {
    sdq = 0;
    k = 0;
    do {
      exitg2 = 0;
      if (k <= nloops - 1) {
        xvFirst = xv[first[k] - 1] - xj;
        yvFirst = yv[first[k] - 1] - yj;
        if (xvFirst > 0.0) {
          if (yvFirst > 0.0) {
            quadFirst = 0;
          } else {
            quadFirst = 3;
          }
        } else if (yvFirst > 0.0) {
          quadFirst = 1;
        } else {
          quadFirst = 2;
        }
        xv2 = xvFirst;
        yv2 = yvFirst;
        quad2 = quadFirst;
        i = first[k];
        do {
          exitg1 = 0;
          if (i <= last[k] - 1) {
            xv1 = xv2;
            yv1 = yv2;
            xv2 = xv[i] - xj;
            yv2 = yv[i] - yj;
            quad1 = quad2;
            if (xv2 > 0.0) {
              if (yv2 > 0.0) {
                quad2 = 0;
              } else {
                quad2 = 3;
              }
            } else if (yv2 > 0.0) {
              quad2 = 1;
            } else {
              quad2 = 2;
            }
            contrib(xv1, yv1, xv2, yv2, quad1, quad2, scale[i - 1], &dquad,
                    &onj);
            if (onj) {
              inj = true;
              exitg1 = 1;
            } else {
              sdq += dquad;
              i++;
            }
          } else {
            contrib(xv2, yv2, xvFirst, yvFirst, quad2, quadFirst,
                    scale[last[k] - 1], &dquad, &onj);
            exitg1 = 2;
          }
        } while (exitg1 == 0);
        if (exitg1 == 1) {
          exitg2 = 1;
        } else if (onj) {
          inj = true;
          exitg2 = 1;
        } else {
          sdq += dquad;
          k++;
        }
      } else {
        inj = (sdq != 0);
        exitg2 = 1;
      }
    } while (exitg2 == 0);
  }
  return inj;
}

void b_inpolygon(const double x[5], const double y[5], const double xv[5],
                 const double yv[5], boolean_T in[5])
{
  double scale[5];
  double d;
  double maxxv;
  double maxyv;
  double minxv_tmp;
  double minyv_tmp;
  int first[5];
  int last[5];
  int i;
  int i1;
  int j;
  int k;
  int nloops;
  for (i = 0; i < 5; i++) {
    in[i] = false;
  }
  countLoops(xv, yv, &nloops, first, last);
  if (nloops != 0) {
    minxv_tmp = xv[first[0] - 1];
    maxxv = minxv_tmp;
    minyv_tmp = yv[first[0] - 1];
    maxyv = minyv_tmp;
    for (k = 0; k < nloops; k++) {
      i = first[k];
      i1 = last[k];
      for (j = i; j <= i1; j++) {
        d = xv[j - 1];
        if (d < minxv_tmp) {
          minxv_tmp = d;
        } else if (d > maxxv) {
          maxxv = d;
        }
      }
      i = first[k];
      i1 = last[k];
      for (j = i; j <= i1; j++) {
        d = yv[j - 1];
        if (d < minyv_tmp) {
          minyv_tmp = d;
        } else if (d > maxyv) {
          maxyv = d;
        }
      }
    }
    computeScaleFactors(xv, yv, nloops, first, last, scale);
    for (j = 0; j < 5; j++) {
      in[j] = scalarInpolygon(x[j], y[j], xv, yv, nloops, first, last,
                              minxv_tmp, maxxv, minyv_tmp, maxyv, scale);
    }
  }
}

void inpolygon(const emxArray_real_T *x, const emxArray_real_T *y,
               const double xv[5], const double yv[5], emxArray_boolean_T *in)
{
  double scale[5];
  const double *x_data;
  const double *y_data;
  double d;
  double maxxv;
  double maxyv;
  double minxv;
  double minyv;
  int first[5];
  int last[5];
  int b_j;
  int i;
  int j;
  int k;
  int loop_ub;
  int nloops;
  boolean_T *in_data;
  y_data = y->data;
  x_data = x->data;
  i = in->size[0];
  in->size[0] = x->size[0];
  emxEnsureCapacity_boolean_T(in, i);
  in_data = in->data;
  loop_ub = x->size[0];
  for (i = 0; i < loop_ub; i++) {
    in_data[i] = false;
  }
  if (x->size[0] != 0) {
    countLoops(xv, yv, &nloops, first, last);
    if (nloops != 0) {
      minxv = xv[first[0] - 1];
      maxxv = minxv;
      minyv = yv[first[0] - 1];
      maxyv = minyv;
      for (k = 0; k < nloops; k++) {
        i = first[k];
        loop_ub = last[k];
        for (b_j = i; b_j <= loop_ub; b_j++) {
          d = xv[b_j - 1];
          if (d < minxv) {
            minxv = d;
          } else if (d > maxxv) {
            maxxv = d;
          }
        }
        i = first[k];
        loop_ub = last[k];
        for (b_j = i; b_j <= loop_ub; b_j++) {
          d = yv[b_j - 1];
          if (d < minyv) {
            minyv = d;
          } else if (d > maxyv) {
            maxyv = d;
          }
        }
      }
      computeScaleFactors(xv, yv, nloops, first, last, scale);
      loop_ub = x->size[0] - 1;
#pragma omp parallel for num_threads(omp_get_max_threads())

      for (j = 0; j <= loop_ub; j++) {
        in_data[j] =
            scalarInpolygon(x_data[j], y_data[j], xv, yv, nloops, first, last,
                            minxv, maxxv, minyv, maxyv, scale);
      }
    }
  }
}

/* End of code generation (inpolygon.c) */
