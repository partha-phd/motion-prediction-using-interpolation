/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_generatePOG_api.c
 *
 * Code generation for function 'generatePOG'
 *
 */

/* Include files */
#include "_coder_generatePOG_api.h"
#include "_coder_generatePOG_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131611U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "generatePOG",                                        /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_real_T *y);

static void c_emlrt_marshallIn(const emlrtStack *sp,
                               const mxArray *vehicleDatabase,
                               const char_T *identifier, emxArray_struct0_T *y);

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_struct0_T *y);

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_real_T *y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *x_Road,
                             const char_T *identifier, emxArray_real_T *y);

static const mxArray *emlrt_marshallOut(const real_T u[12000]);

static void emxEnsureCapacity_real_T(emxArray_real_T *emxArray,
                                     int32_T oldNumel);

static void emxEnsureCapacity_struct0_T(const emlrtStack *sp,
                                        emxArray_struct0_T *emxArray,
                                        int32_T oldNumel);

static void emxExpand_struct0_T(const emlrtStack *sp,
                                emxArray_struct0_T *emxArray, int32_T fromIndex,
                                int32_T toIndex);

static void emxFreeStruct_struct0_T(const emlrtStack *sp, struct0_T *pStruct);

static void emxFree_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray);

static void emxFree_struct0_T(const emlrtStack *sp,
                              emxArray_struct0_T **pEmxArray);

static void emxInitStruct_struct0_T(const emlrtStack *sp, struct0_T *pStruct);

static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
                           boolean_T doPush);

static void emxInit_struct0_T(const emlrtStack *sp,
                              emxArray_struct0_T **pEmxArray);

static void emxTrim_struct0_T(const emlrtStack *sp,
                              emxArray_struct0_T *emxArray, int32_T fromIndex,
                              int32_T toIndex);

static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static real_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *n,
                                 const char_T *identifier);

static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               emxArray_real_T *ret);

static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               emxArray_real_T *ret);

static real_T j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

/* Function Definitions */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_real_T *y)
{
  h_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void c_emlrt_marshallIn(const emlrtStack *sp,
                               const mxArray *vehicleDatabase,
                               const char_T *identifier, emxArray_struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(sp, emlrtAlias(vehicleDatabase), &thisId, y);
  emlrtDestroyArray(&vehicleDatabase);
}

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_struct0_T *y)
{
  static const int32_T dims[3] = {-1, -1, -1};
  static const char_T *fieldNames[4] = {"xCoordinates", "yCoordinates",
                                        "vehicleID", "minProb"};
  emlrtMsgIdentifier thisId;
  struct0_T *y_data;
  int32_T sizes[3];
  int32_T i;
  int32_T n;
  const boolean_T bv[3] = {true, true, true};
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckVsStructR2012b((emlrtCTX)sp, parentId, u, 4,
                           (const char_T **)&fieldNames[0], 3U,
                           (void *)&dims[0], &bv[0], &sizes[0]);
  i = y->size[0] * y->size[1] * y->size[2];
  y->size[0] = sizes[0];
  y->size[1] = sizes[1];
  y->size[2] = sizes[2];
  emxEnsureCapacity_struct0_T(sp, y, i);
  y_data = y->data;
  n = sizes[0] * (sizes[1] * sizes[2]);
  for (i = 0; i < n; i++) {
    thisId.fIdentifier = "xCoordinates";
    e_emlrt_marshallIn(
        sp,
        emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, i, 0,
                                       (const char_T *)"xCoordinates")),
        &thisId, y_data[i].xCoordinates);
    thisId.fIdentifier = "yCoordinates";
    e_emlrt_marshallIn(
        sp,
        emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, i, 1,
                                       (const char_T *)"yCoordinates")),
        &thisId, y_data[i].yCoordinates);
    thisId.fIdentifier = "vehicleID";
    y_data[i].vehicleID = f_emlrt_marshallIn(
        sp,
        emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, i, 2,
                                       (const char_T *)"vehicleID")),
        &thisId);
    thisId.fIdentifier = "minProb";
    y_data[i].minProb = f_emlrt_marshallIn(
        sp,
        emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, i, 3,
                                       (const char_T *)"minProb")),
        &thisId);
  }
  emlrtDestroyArray(&u);
}

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_real_T *y)
{
  i_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *x_Road,
                             const char_T *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(x_Road), &thisId, y);
  emlrtDestroyArray(&x_Road);
}

static const mxArray *emlrt_marshallOut(const real_T u[12000])
{
  static const int32_T iv[2] = {0, 0};
  static const int32_T iv1[2] = {30, 400};
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

static void emxEnsureCapacity_real_T(emxArray_real_T *emxArray,
                                     int32_T oldNumel)
{
  int32_T i;
  int32_T newNumel;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }
  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }
    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }
    newData = emlrtCallocMex((uint32_T)i, sizeof(real_T));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(real_T) * oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }
    emxArray->data = (real_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

static void emxEnsureCapacity_struct0_T(const emlrtStack *sp,
                                        emxArray_struct0_T *emxArray,
                                        int32_T oldNumel)
{
  int32_T i;
  int32_T newNumel;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }
  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }
    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }
    newData = emlrtCallocMex((uint32_T)i, sizeof(struct0_T));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(struct0_T) * oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }
    emxArray->data = (struct0_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
  if (oldNumel > newNumel) {
    emxTrim_struct0_T(sp, emxArray, newNumel, oldNumel);
  } else if (oldNumel < newNumel) {
    emxExpand_struct0_T(sp, emxArray, oldNumel, newNumel);
  }
}

static void emxExpand_struct0_T(const emlrtStack *sp,
                                emxArray_struct0_T *emxArray, int32_T fromIndex,
                                int32_T toIndex)
{
  int32_T i;
  for (i = fromIndex; i < toIndex; i++) {
    emxInitStruct_struct0_T(sp, &emxArray->data[i]);
  }
}

static void emxFreeStruct_struct0_T(const emlrtStack *sp, struct0_T *pStruct)
{
  emxFree_real_T(sp, &pStruct->xCoordinates);
  emxFree_real_T(sp, &pStruct->yCoordinates);
}

static void emxFree_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }
    emlrtFreeMex((*pEmxArray)->size);
    emlrtRemoveHeapReference((emlrtCTX)sp, (void *)pEmxArray);
    emlrtFreeEmxArray(*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

static void emxFree_struct0_T(const emlrtStack *sp,
                              emxArray_struct0_T **pEmxArray)
{
  int32_T i;
  int32_T numEl;
  if (*pEmxArray != (emxArray_struct0_T *)NULL) {
    if ((*pEmxArray)->data != (struct0_T *)NULL) {
      numEl = 1;
      for (i = 0; i < (*pEmxArray)->numDimensions; i++) {
        numEl *= (*pEmxArray)->size[i];
      }
      for (i = 0; i < numEl; i++) {
        emxFreeStruct_struct0_T(sp, &(*pEmxArray)->data[i]);
      }
      if ((*pEmxArray)->canFreeData) {
        emlrtFreeMex((*pEmxArray)->data);
      }
    }
    emlrtFreeMex((*pEmxArray)->size);
    emlrtRemoveHeapReference((emlrtCTX)sp, (void *)pEmxArray);
    emlrtFreeEmxArray(*pEmxArray);
    *pEmxArray = (emxArray_struct0_T *)NULL;
  }
}

static void emxInitStruct_struct0_T(const emlrtStack *sp, struct0_T *pStruct)
{
  emxInit_real_T(sp, &pStruct->xCoordinates, false);
  emxInit_real_T(sp, &pStruct->yCoordinates, false);
}

static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
                           boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocEmxArray(sizeof(emxArray_real_T));
  if (doPush) {
    emlrtPushHeapReferenceStackEmxArray((emlrtCTX)sp, true, (void *)pEmxArray,
                                        (void *)&emxFree_real_T, NULL, NULL,
                                        NULL);
  }
  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = 2;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * 2U);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < 2; i++) {
    emxArray->size[i] = 0;
  }
}

static void emxInit_struct0_T(const emlrtStack *sp,
                              emxArray_struct0_T **pEmxArray)
{
  emxArray_struct0_T *emxArray;
  int32_T i;
  *pEmxArray =
      (emxArray_struct0_T *)emlrtMallocEmxArray(sizeof(emxArray_struct0_T));
  emlrtPushHeapReferenceStackEmxArray((emlrtCTX)sp, true, (void *)pEmxArray,
                                      (void *)&emxFree_struct0_T, NULL, NULL,
                                      NULL);
  emxArray = *pEmxArray;
  emxArray->data = (struct0_T *)NULL;
  emxArray->numDimensions = 3;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * 3U);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < 3; i++) {
    emxArray->size[i] = 0;
  }
}

static void emxTrim_struct0_T(const emlrtStack *sp,
                              emxArray_struct0_T *emxArray, int32_T fromIndex,
                              int32_T toIndex)
{
  int32_T i;
  for (i = fromIndex; i < toIndex; i++) {
    emxFreeStruct_struct0_T(sp, &emxArray->data[i]);
  }
}

static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = j_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *n,
                                 const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(n), &thisId);
  emlrtDestroyArray(&n);
  return y;
}

static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               emxArray_real_T *ret)
{
  static const int32_T dims[2] = {-1, -1};
  int32_T iv[2];
  int32_T i;
  const boolean_T bv[2] = {true, true};
  emlrtCheckVsBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                            false, 2U, (void *)&dims[0], &bv[0], &iv[0]);
  ret->allocatedSize = iv[0] * iv[1];
  i = ret->size[0] * ret->size[1];
  ret->size[0] = iv[0];
  ret->size[1] = iv[1];
  emxEnsureCapacity_real_T(ret, i);
  ret->data = (real_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               emxArray_real_T *ret)
{
  static const int32_T dims[2] = {-1, 5};
  real_T *ret_data;
  int32_T iv[2];
  int32_T i;
  const boolean_T bv[2] = {true, true};
  emlrtCheckVsBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                            false, 2U, (void *)&dims[0], &bv[0], &iv[0]);
  i = ret->size[0] * ret->size[1];
  ret->size[0] = iv[0];
  ret->size[1] = iv[1];
  emxEnsureCapacity_real_T(ret, i);
  ret_data = ret->data;
  emlrtImportArrayR2015b((emlrtCTX)sp, src, &ret_data[0], 8, false);
  emlrtDestroyArray(&src);
}

static real_T j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 0U, (void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

void generatePOG_api(const mxArray *const prhs[4], int32_T nlhs,
                     const mxArray *plhs[2])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  emxArray_real_T *x_Road;
  emxArray_real_T *y_Road;
  emxArray_struct0_T *vehicleDatabase;
  real_T(*pogID)[12000];
  real_T(*pogProb)[12000];
  real_T n;
  st.tls = emlrtRootTLSGlobal;
  pogProb = (real_T(*)[12000])mxMalloc(sizeof(real_T[12000]));
  pogID = (real_T(*)[12000])mxMalloc(sizeof(real_T[12000]));
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_real_T(&st, &x_Road, true);
  emxInit_real_T(&st, &y_Road, true);
  emxInit_struct0_T(&st, &vehicleDatabase);
  /* Marshall function inputs */
  x_Road->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "x_Road", x_Road);
  y_Road->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "y_Road", y_Road);
  c_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "vehicleDatabase",
                     vehicleDatabase);
  n = g_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "n");
  /* Invoke the target function */
  generatePOG(x_Road, y_Road, vehicleDatabase, n, *pogProb, *pogID);
  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*pogProb);
  emxFree_struct0_T(&st, &vehicleDatabase);
  emxFree_real_T(&st, &y_Road);
  emxFree_real_T(&st, &x_Road);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(*pogID);
  }
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

void generatePOG_atexit(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  generatePOG_xil_terminate();
  generatePOG_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void generatePOG_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void generatePOG_terminate(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (_coder_generatePOG_api.c) */
