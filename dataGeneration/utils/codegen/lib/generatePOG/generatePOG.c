/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * generatePOG.c
 *
 * Code generation for function 'generatePOG'
 *
 */

/* Include files */
#include "generatePOG.h"
#include "generatePOG_data.h"
#include "generatePOG_emxutil.h"
#include "generatePOG_initialize.h"
#include "generatePOG_types.h"
#include "inpolygon.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include <string.h>

/* Function Definitions */
void generatePOG(const emxArray_real_T *x_Road, const emxArray_real_T *y_Road,
                 const emxArray_struct0_T *vehicleDatabase, double n,
                 double pogProb[12000], double pogID[12000])
{
  static double gridNew[48000];
  emxArray_boolean_T *in;
  emxArray_int32_T *ii;
  emxArray_real_T b_x_Road;
  emxArray_real_T c_y_Road;
  emxArray_real_T *b_occProb;
  emxArray_real_T *b_sumProb;
  emxArray_real_T *occProb;
  emxArray_real_T *sumProb;
  emxArray_uint32_T *id;
  const struct0_T *vehicleDatabase_data;
  double occupancyGridProb[12000];
  double xVehicle[5];
  double xvGrid[5];
  double yVehicle[5];
  double yvGrid[5];
  double d;
  double xVehicle_tmp;
  double *b_occProb_data;
  double *occProb_data;
  double *sumProb_data;
  unsigned int occupancyGridID[12000];
  int b_i;
  int b_y_Road;
  int c_x_Road;
  int d_x_Road;
  int d_y_Road;
  int gridNew_tmp;
  int i;
  int idx;
  int k;
  int m;
  int numLatHypotheses;
  int numLongHypotheses;
  int numTargets;
  unsigned int *id_data;
  int *ii_data;
  boolean_T b_in[5];
  boolean_T in1[5];
  boolean_T exitg1;
  boolean_T y;
  boolean_T *in_data;
  if (!isInitialized_generatePOG) {
    generatePOG_initialize();
  }
  vehicleDatabase_data = vehicleDatabase->data;
  /*  Generation of Predicted Occupancy Grids */
  /*  Construction of grids 0.5m x 0.5m */
  k = 0;
  memset(&gridNew[0], 0, 48000U * sizeof(double));
  for (i = 0; i < 29; i++) {
    for (idx = 0; idx < 400; idx++) {
      gridNew_tmp = (k + idx) << 2;
      gridNew[gridNew_tmp] = 0.5 * (double)idx;
      gridNew[gridNew_tmp + 2] = 0.5 * ((double)idx + 1.0);
      gridNew[gridNew_tmp + 1] = 0.5 * (double)i;
      gridNew[gridNew_tmp + 3] = 0.5 * ((double)i + 1.0);
    }
    k += 400;
  }
  /*  Initialisation */
  numLongHypotheses = vehicleDatabase->size[2];
  numLatHypotheses = vehicleDatabase->size[1];
  numTargets = vehicleDatabase->size[0];
  /*  Vectorize the road points */
  /*  Initialisation */
  memset(&pogProb[0], 0, 12000U * sizeof(double));
  memset(&pogID[0], 0, 12000U * sizeof(double));
  memset(&occupancyGridProb[0], 0, 12000U * sizeof(double));
  memset(&occupancyGridID[0], 0, 12000U * sizeof(unsigned int));
  /*  Probability to target */
  /*  START loop over the grids */
  b_y_Road = y_Road->size[0] * y_Road->size[1];
  emxInit_boolean_T(&in);
  emxInit_real_T(&sumProb, 1);
  emxInit_real_T(&occProb, 3);
  emxInit_uint32_T(&id);
  emxInit_int32_T(&ii);
  emxInit_real_T(&b_occProb, 3);
  emxInit_real_T(&b_sumProb, 1);
  for (m = 0; m < 12000; m++) {
    b_i = m << 2;
    xVehicle_tmp = gridNew[b_i];
    xvGrid[0] = xVehicle_tmp;
    d = gridNew[b_i + 2];
    xvGrid[1] = d;
    xvGrid[2] = d;
    xvGrid[3] = xVehicle_tmp;
    xvGrid[4] = xVehicle_tmp;
    xVehicle_tmp = gridNew[b_i + 1];
    yvGrid[0] = xVehicle_tmp;
    yvGrid[1] = xVehicle_tmp;
    d = gridNew[b_i + 3];
    yvGrid[2] = d;
    yvGrid[3] = d;
    yvGrid[4] = xVehicle_tmp;
    gridNew_tmp = x_Road->size[0] * x_Road->size[1];
    b_x_Road = *x_Road;
    c_x_Road = gridNew_tmp;
    b_x_Road.size = &c_x_Road;
    b_x_Road.numDimensions = 1;
    c_y_Road = *y_Road;
    d_y_Road = b_y_Road;
    c_y_Road.size = &d_y_Road;
    c_y_Road.numDimensions = 1;
    inpolygon(&b_x_Road, &c_y_Road, xvGrid, yvGrid, in);
    in_data = in->data;
    y = false;
    gridNew_tmp = 1;
    exitg1 = false;
    while ((!exitg1) && (gridNew_tmp <= in->size[0])) {
      if (in_data[gridNew_tmp - 1]) {
        y = true;
        exitg1 = true;
      } else {
        gridNew_tmp++;
      }
    }
    if (y) {
      occupancyGridProb[m] = 1.0;
    } else {
      b_i = sumProb->size[0];
      sumProb->size[0] = numTargets;
      emxEnsureCapacity_real_T(sumProb, b_i);
      sumProb_data = sumProb->data;
      b_i = occProb->size[0] * occProb->size[1] * occProb->size[2];
      occProb->size[0] = numTargets;
      occProb->size[1] = numLatHypotheses;
      occProb->size[2] = numLongHypotheses;
      emxEnsureCapacity_real_T(occProb, b_i);
      occProb_data = occProb->data;
      gridNew_tmp = numTargets * numLatHypotheses * numLongHypotheses;
      for (b_i = 0; b_i < gridNew_tmp; b_i++) {
        occProb_data[b_i] = 0.0;
      }
      /*  START loop over the target */
      for (i = 0; i < numTargets; i++) {
        /*  START loop over the multiple hypotheses (lateral) */
        for (idx = 0; idx < numLatHypotheses; idx++) {
          /*  START loop over the multiple hypotheses(longitudinal) */
          for (k = 0; k < numLongHypotheses; k++) {
            if ((vehicleDatabase_data[(i + vehicleDatabase->size[0] * idx) +
                                      vehicleDatabase->size[0] *
                                          vehicleDatabase->size[1] * k]
                     .xCoordinates->size[0] != 0) &&
                (vehicleDatabase_data[(i + vehicleDatabase->size[0] * idx) +
                                      vehicleDatabase->size[0] *
                                          vehicleDatabase->size[1] * k]
                     .xCoordinates->size[1] != 0)) {
              xVehicle_tmp =
                  vehicleDatabase_data[(i + vehicleDatabase->size[0] * idx) +
                                       vehicleDatabase->size[0] *
                                           vehicleDatabase->size[1] * k]
                      .xCoordinates->data[(int)n - 1];
              xVehicle[0] = xVehicle_tmp;
              xVehicle[1] =
                  vehicleDatabase_data[(i + vehicleDatabase->size[0] * idx) +
                                       vehicleDatabase->size[0] *
                                           vehicleDatabase->size[1] * k]
                      .xCoordinates
                      ->data[((int)n +
                              vehicleDatabase_data
                                  [(i + vehicleDatabase->size[0] * idx) +
                                   vehicleDatabase->size[0] *
                                       vehicleDatabase->size[1] * k]
                                      .xCoordinates->size[0]) -
                             1];
              xVehicle[2] =
                  vehicleDatabase_data[(i + vehicleDatabase->size[0] * idx) +
                                       vehicleDatabase->size[0] *
                                           vehicleDatabase->size[1] * k]
                      .xCoordinates
                      ->data[((int)n +
                              vehicleDatabase_data
                                      [(i + vehicleDatabase->size[0] * idx) +
                                       vehicleDatabase->size[0] *
                                           vehicleDatabase->size[1] * k]
                                          .xCoordinates->size[0] *
                                  2) -
                             1];
              xVehicle[3] =
                  vehicleDatabase_data[(i + vehicleDatabase->size[0] * idx) +
                                       vehicleDatabase->size[0] *
                                           vehicleDatabase->size[1] * k]
                      .xCoordinates
                      ->data[((int)n +
                              vehicleDatabase_data
                                      [(i + vehicleDatabase->size[0] * idx) +
                                       vehicleDatabase->size[0] *
                                           vehicleDatabase->size[1] * k]
                                          .xCoordinates->size[0] *
                                  3) -
                             1];
              xVehicle[4] = xVehicle_tmp;
              xVehicle_tmp =
                  vehicleDatabase_data[(i + vehicleDatabase->size[0] * idx) +
                                       vehicleDatabase->size[0] *
                                           vehicleDatabase->size[1] * k]
                      .yCoordinates->data[(int)n - 1];
              yVehicle[0] = xVehicle_tmp;
              yVehicle[1] =
                  vehicleDatabase_data[(i + vehicleDatabase->size[0] * idx) +
                                       vehicleDatabase->size[0] *
                                           vehicleDatabase->size[1] * k]
                      .yCoordinates
                      ->data[((int)n +
                              vehicleDatabase_data
                                  [(i + vehicleDatabase->size[0] * idx) +
                                   vehicleDatabase->size[0] *
                                       vehicleDatabase->size[1] * k]
                                      .yCoordinates->size[0]) -
                             1];
              yVehicle[2] =
                  vehicleDatabase_data[(i + vehicleDatabase->size[0] * idx) +
                                       vehicleDatabase->size[0] *
                                           vehicleDatabase->size[1] * k]
                      .yCoordinates
                      ->data[((int)n +
                              vehicleDatabase_data
                                      [(i + vehicleDatabase->size[0] * idx) +
                                       vehicleDatabase->size[0] *
                                           vehicleDatabase->size[1] * k]
                                          .yCoordinates->size[0] *
                                  2) -
                             1];
              yVehicle[3] =
                  vehicleDatabase_data[(i + vehicleDatabase->size[0] * idx) +
                                       vehicleDatabase->size[0] *
                                           vehicleDatabase->size[1] * k]
                      .yCoordinates
                      ->data[((int)n +
                              vehicleDatabase_data
                                      [(i + vehicleDatabase->size[0] * idx) +
                                       vehicleDatabase->size[0] *
                                           vehicleDatabase->size[1] * k]
                                          .yCoordinates->size[0] *
                                  3) -
                             1];
              yVehicle[4] = xVehicle_tmp;
              b_inpolygon(xVehicle, yVehicle, xvGrid, yvGrid, b_in);
              b_inpolygon(xvGrid, yvGrid, xVehicle, yVehicle, in1);
              y = false;
              gridNew_tmp = 0;
              exitg1 = false;
              while ((!exitg1) && (gridNew_tmp < 5)) {
                if (b_in[gridNew_tmp]) {
                  y = true;
                  exitg1 = true;
                } else {
                  gridNew_tmp++;
                }
              }
              if (y) {
                occProb_data[(i + occProb->size[0] * idx) +
                             occProb->size[0] * occProb->size[1] * k] =
                    vehicleDatabase_data[(i + vehicleDatabase->size[0] * idx) +
                                         vehicleDatabase->size[0] *
                                             vehicleDatabase->size[1] * k]
                        .minProb;
              } else {
                y = false;
                gridNew_tmp = 0;
                exitg1 = false;
                while ((!exitg1) && (gridNew_tmp < 5)) {
                  if (in1[gridNew_tmp]) {
                    y = true;
                    exitg1 = true;
                  } else {
                    gridNew_tmp++;
                  }
                }
                if (y) {
                  occProb_data[(i + occProb->size[0] * idx) +
                               occProb->size[0] * occProb->size[1] * k] =
                      vehicleDatabase_data[(i +
                                            vehicleDatabase->size[0] * idx) +
                                           vehicleDatabase->size[0] *
                                               vehicleDatabase->size[1] * k]
                          .minProb;
                } else {
                  occProb_data[(i + occProb->size[0] * idx) +
                               occProb->size[0] * occProb->size[1] * k] = 0.0;
                }
              }
            }
          }
          /*  END loop over the multiple hypotheses (longitudinal) */
        }
        /*  END loop over the multiple hypotheses (lateral) */
        gridNew_tmp = occProb->size[1];
        k = occProb->size[2];
        b_i = b_occProb->size[0] * b_occProb->size[1] * b_occProb->size[2];
        b_occProb->size[0] = 1;
        b_occProb->size[1] = occProb->size[1];
        b_occProb->size[2] = occProb->size[2];
        emxEnsureCapacity_real_T(b_occProb, b_i);
        b_occProb_data = b_occProb->data;
        for (b_i = 0; b_i < k; b_i++) {
          for (idx = 0; idx < gridNew_tmp; idx++) {
            b_occProb_data[idx + b_occProb->size[1] * b_i] =
                occProb_data[(i + occProb->size[0] * idx) +
                             occProb->size[0] * occProb->size[1] * b_i];
          }
        }
        gridNew_tmp = occProb->size[1] * occProb->size[2];
        b_x_Road = *b_occProb;
        d_x_Road = gridNew_tmp;
        b_x_Road.size = &d_x_Road;
        b_x_Road.numDimensions = 1;
        sumProb_data[i] = sum(&b_x_Road);
      }
      /*  END loop over the targets */
      gridNew_tmp = sumProb->size[0];
      b_i = in->size[0];
      in->size[0] = sumProb->size[0];
      emxEnsureCapacity_boolean_T(in, b_i);
      in_data = in->data;
      for (b_i = 0; b_i < gridNew_tmp; b_i++) {
        in_data[b_i] = (sumProb_data[b_i] > 0.001);
      }
      k = in->size[0];
      idx = 0;
      b_i = ii->size[0];
      ii->size[0] = in->size[0];
      emxEnsureCapacity_int32_T(ii, b_i);
      ii_data = ii->data;
      gridNew_tmp = 0;
      exitg1 = false;
      while ((!exitg1) && (gridNew_tmp <= k - 1)) {
        if (in_data[gridNew_tmp]) {
          idx++;
          ii_data[idx - 1] = gridNew_tmp + 1;
          if (idx >= k) {
            exitg1 = true;
          } else {
            gridNew_tmp++;
          }
        } else {
          gridNew_tmp++;
        }
      }
      if (in->size[0] == 1) {
        if (idx == 0) {
          ii->size[0] = 0;
        }
      } else {
        b_i = ii->size[0];
        if (1 > idx) {
          ii->size[0] = 0;
        } else {
          ii->size[0] = idx;
        }
        emxEnsureCapacity_int32_T(ii, b_i);
        ii_data = ii->data;
      }
      b_i = id->size[0];
      id->size[0] = ii->size[0];
      emxEnsureCapacity_uint32_T(id, b_i);
      id_data = id->data;
      gridNew_tmp = ii->size[0];
      for (b_i = 0; b_i < gridNew_tmp; b_i++) {
        id_data[b_i] = (unsigned int)ii_data[b_i];
      }
      if (id->size[0] != 0) {
        b_i = b_sumProb->size[0];
        b_sumProb->size[0] = id->size[0];
        emxEnsureCapacity_real_T(b_sumProb, b_i);
        occProb_data = b_sumProb->data;
        gridNew_tmp = id->size[0];
        for (b_i = 0; b_i < gridNew_tmp; b_i++) {
          occProb_data[b_i] = sumProb_data[(int)id_data[b_i] - 1];
        }
        occupancyGridProb[m] = sum(b_sumProb);
        occupancyGridID[m] = id_data[0];
      }
      /*  END loop over the cells */
      /*  Calculating the predicted occupancy grid */
      for (i = 0; i < 30; i++) {
        for (idx = 0; idx < 400; idx++) {
          pogProb[i + 30 * idx] = occupancyGridProb[idx + 400 * (29 - i)];
        }
      }
      for (i = 0; i < 12000; i++) {
        if (pogProb[i] > 1.0) {
          pogProb[i] = 1.0;
        }
      }
      for (i = 0; i < 30; i++) {
        for (idx = 0; idx < 400; idx++) {
          pogID[i + 30 * idx] = occupancyGridID[idx + 400 * (29 - i)];
        }
      }
    }
  }
  emxFree_real_T(&b_sumProb);
  emxFree_real_T(&b_occProb);
  emxFree_int32_T(&ii);
  emxFree_uint32_T(&id);
  emxFree_real_T(&occProb);
  emxFree_real_T(&sumProb);
  emxFree_boolean_T(&in);
}

/* End of code generation (generatePOG.c) */
