/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include files */
#include "main.h"
#include "generatePOG.h"
#include "generatePOG_emxAPI.h"
#include "generatePOG_terminate.h"
#include "generatePOG_types.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static double argInit_real_T(void);

static struct0_T argInit_struct0_T(void);

static emxArray_real_T *c_argInit_UnboundedxUnbounded_r(void);

static emxArray_struct0_T *c_argInit_UnboundedxUnboundedxU(void);

static void main_generatePOG(void);

/* Function Definitions */
static double argInit_real_T(void)
{
  return 0.0;
}

static struct0_T argInit_struct0_T(void)
{
  struct0_T result;
  double result_tmp;
  /* Set the value of each structure field.
Change this value to the value that the application requires. */
  result_tmp = argInit_real_T();
  result.minProb = result_tmp;
  result.xCoordinates = c_argInit_UnboundedxUnbounded_r();
  result.yCoordinates = c_argInit_UnboundedxUnbounded_r();
  result.vehicleID = result_tmp;
  return result;
}

static emxArray_real_T *c_argInit_UnboundedxUnbounded_r(void)
{
  emxArray_real_T *result;
  double *result_data;
  int idx0;
  int idx1;
  /* Set the size of the array.
Change this size to the value that the application requires. */
  result = emxCreate_real_T(2, 2);
  result_data = result->data;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      /* Set the value of the array element.
Change this value to the value that the application requires. */
      result_data[idx0 + result->size[0] * idx1] = argInit_real_T();
    }
  }
  return result;
}

static emxArray_struct0_T *c_argInit_UnboundedxUnboundedxU(void)
{
  emxArray_struct0_T *result;
  struct0_T *result_data;
  const int iv[3] = {2, 2, 2};
  int idx0;
  int idx1;
  int idx2;
  /* Set the size of the array.
Change this size to the value that the application requires. */
  result = emxCreateND_struct0_T(3, &iv[0]);
  result_data = result->data;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      for (idx2 = 0; idx2 < result->size[2U]; idx2++) {
        /* Set the value of the array element.
Change this value to the value that the application requires. */
        result_data[(idx0 + result->size[0] * idx1) +
                    result->size[0] * result->size[1] * idx2] =
            argInit_struct0_T();
      }
    }
  }
  return result;
}

static void main_generatePOG(void)
{
  static double pogID[12000];
  static double pogProb[12000];
  emxArray_real_T *x_Road;
  emxArray_real_T *y_Road;
  emxArray_struct0_T *vehicleDatabase;
  /* Initialize function 'generatePOG' input arguments. */
  /* Initialize function input argument 'x_Road'. */
  x_Road = c_argInit_UnboundedxUnbounded_r();
  /* Initialize function input argument 'y_Road'. */
  y_Road = c_argInit_UnboundedxUnbounded_r();
  /* Initialize function input argument 'vehicleDatabase'. */
  vehicleDatabase = c_argInit_UnboundedxUnboundedxU();
  /* Call the entry-point 'generatePOG'. */
  generatePOG(x_Road, y_Road, vehicleDatabase, argInit_real_T(), pogProb,
              pogID);
  emxDestroyArray_struct0_T(vehicleDatabase);
  emxDestroyArray_real_T(y_Road);
  emxDestroyArray_real_T(x_Road);
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_generatePOG();
  /* Terminate the application.
You do not need to do this more than one time. */
  generatePOG_terminate();
  return 0;
}

/* End of code generation (main.c) */
