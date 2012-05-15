/* Include files */

#include "blascompat32.h"
#include "controller1_sfun.h"
#include "c3_controller1.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "controller1_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char *c3_debug_family_names[5] = { "T", "nargin", "nargout", "u",
  "y" };

/* Function Declarations */
static void initialize_c3_controller1(SFc3_controller1InstanceStruct
  *chartInstance);
static void initialize_params_c3_controller1(SFc3_controller1InstanceStruct
  *chartInstance);
static void enable_c3_controller1(SFc3_controller1InstanceStruct *chartInstance);
static void disable_c3_controller1(SFc3_controller1InstanceStruct *chartInstance);
static void c3_update_debugger_state_c3_controller1
  (SFc3_controller1InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_controller1
  (SFc3_controller1InstanceStruct *chartInstance);
static void set_sim_state_c3_controller1(SFc3_controller1InstanceStruct
  *chartInstance, const mxArray *c3_st);
static void finalize_c3_controller1(SFc3_controller1InstanceStruct
  *chartInstance);
static void sf_c3_controller1(SFc3_controller1InstanceStruct *chartInstance);
static void compInitSubchartSimstructsFcn_c3_controller1
  (SFc3_controller1InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static const mxArray *c3_sf_marshall(void *chartInstanceVoid, void *c3_u);
static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[21]);
static const mxArray *c3_b_sf_marshall(void *chartInstanceVoid, void *c3_u);
static real_T c3_emlrt_marshallIn(SFc3_controller1InstanceStruct *chartInstance,
  const mxArray *c3_y, const char_T *c3_name);
static uint8_T c3_b_emlrt_marshallIn(SFc3_controller1InstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_controller1, const char_T
  *c3_name);
static void init_dsm_address_info(SFc3_controller1InstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c3_controller1(SFc3_controller1InstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c3_is_active_c3_controller1 = 0U;
}

static void initialize_params_c3_controller1(SFc3_controller1InstanceStruct
  *chartInstance)
{
}

static void enable_c3_controller1(SFc3_controller1InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_controller1(SFc3_controller1InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c3_update_debugger_state_c3_controller1
  (SFc3_controller1InstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c3_controller1
  (SFc3_controller1InstanceStruct *chartInstance)
{
  const mxArray *c3_st = NULL;
  const mxArray *c3_y = NULL;
  real_T c3_hoistedGlobal;
  real_T c3_u;
  const mxArray *c3_b_y = NULL;
  uint8_T c3_b_hoistedGlobal;
  uint8_T c3_b_u;
  const mxArray *c3_c_y = NULL;
  real_T *c3_d_y;
  c3_d_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellarray(2));
  c3_hoistedGlobal = *c3_d_y;
  c3_u = c3_hoistedGlobal;
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 0, c3_b_y);
  c3_b_hoistedGlobal = chartInstance->c3_is_active_c3_controller1;
  c3_b_u = c3_b_hoistedGlobal;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_b_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 1, c3_c_y);
  sf_mex_assign(&c3_st, c3_y);
  return c3_st;
}

static void set_sim_state_c3_controller1(SFc3_controller1InstanceStruct
  *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  real_T *c3_y;
  c3_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c3_doneDoubleBufferReInit = TRUE;
  c3_u = sf_mex_dup(c3_st);
  *c3_y = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)),
    "y");
  chartInstance->c3_is_active_c3_controller1 = c3_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)),
     "is_active_c3_controller1");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_controller1(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_controller1(SFc3_controller1InstanceStruct
  *chartInstance)
{
}

static void sf_c3_controller1(SFc3_controller1InstanceStruct *chartInstance)
{
  int32_T c3_previousEvent;
  real_T c3_hoistedGlobal;
  real_T c3_u;
  uint32_T c3_debug_family_var_map[5];
  real_T c3_T;
  real_T c3_nargin = 1.0;
  real_T c3_nargout = 1.0;
  real_T c3_y;
  real_T c3_x;
  real_T c3_b_x;
  real_T c3_b_y;
  real_T c3_c_x;
  real_T c3_d_x;
  real_T c3_c_y;
  real_T c3_b;
  real_T c3_d_y;
  real_T c3_A;
  real_T c3_B;
  real_T c3_e_x;
  real_T c3_e_y;
  real_T c3_f_x;
  real_T c3_f_y;
  real_T c3_g_x;
  real_T c3_g_y;
  real_T *c3_b_u;
  real_T *c3_h_y;
  c3_h_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_b_u = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2);
  _SFD_DATA_RANGE_CHECK(*c3_b_u, 0U);
  _SFD_DATA_RANGE_CHECK(*c3_h_y, 1U);
  c3_previousEvent = _sfEvent_;
  _sfEvent_ = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2);
  c3_hoistedGlobal = *c3_b_u;
  c3_u = c3_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 5U, 5U, c3_debug_family_names,
    c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c3_T, c3_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c3_nargin, c3_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c3_nargout, c3_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c3_u, c3_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c3_y, c3_sf_marshall, 4U);
  CV_EML_FCN(0, 0);

  /*  hard limit cutoff function. */
  _SFD_EML_CALL(0, 4);
  c3_T = 100.0;
  _SFD_EML_CALL(0, 5);
  c3_x = c3_u;
  c3_b_x = c3_x;
  c3_b_y = muDoubleScalarAbs(c3_b_x);
  if (CV_EML_IF(0, 0, c3_b_y > c3_T)) {
    _SFD_EML_CALL(0, 6);
    c3_c_x = c3_u;
    c3_d_x = c3_c_x;
    c3_c_y = muDoubleScalarAbs(c3_d_x);
    c3_b = c3_c_y;
    c3_d_y = 100.0 * c3_b;
    c3_A = c3_d_y;
    c3_B = c3_u;
    c3_e_x = c3_A;
    c3_e_y = c3_B;
    c3_f_x = c3_e_x;
    c3_f_y = c3_e_y;
    c3_g_x = c3_f_x;
    c3_g_y = c3_f_y;
    c3_u = c3_g_x / c3_g_y;
  }

  _SFD_EML_CALL(0, 8);
  c3_y = c3_u;
  _SFD_EML_CALL(0, -8);
  sf_debug_symbol_scope_pop();
  *c3_h_y = c3_y;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2);
  _sfEvent_ = c3_previousEvent;
  sf_debug_check_for_state_inconsistency(_controller1MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void compInitSubchartSimstructsFcn_c3_controller1
  (SFc3_controller1InstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
}

static const mxArray *c3_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  real_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  SFc3_controller1InstanceStruct *chartInstance;
  chartInstance = (SFc3_controller1InstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_b_u = *((real_T *)c3_u);
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

const mxArray *sf_c3_controller1_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_ResolvedFunctionInfo c3_info[21];
  const mxArray *c3_m0 = NULL;
  int32_T c3_i0;
  c3_ResolvedFunctionInfo *c3_r0;
  c3_nameCaptureInfo = NULL;
  c3_info_helper(c3_info);
  sf_mex_assign(&c3_m0, sf_mex_createstruct("nameCaptureInfo", 1, 21));
  for (c3_i0 = 0; c3_i0 < 21; c3_i0 = c3_i0 + 1) {
    c3_r0 = &c3_info[c3_i0];
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->context)), "context",
                    "nameCaptureInfo", c3_i0);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c3_r0->name)), "name",
                    "nameCaptureInfo", c3_i0);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c3_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c3_i0);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->resolved)), "resolved"
                    , "nameCaptureInfo", c3_i0);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileLength,
      7, 0U, 0U, 0U, 0), "fileLength", "nameCaptureInfo",
                    c3_i0);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTime1, 7,
      0U, 0U, 0U, 0), "fileTime1", "nameCaptureInfo", c3_i0);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTime2, 7,
      0U, 0U, 0U, 0), "fileTime2", "nameCaptureInfo", c3_i0);
  }

  sf_mex_assign(&c3_nameCaptureInfo, c3_m0);
  return c3_nameCaptureInfo;
}

static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[21])
{
  c3_info[0].context = "";
  c3_info[0].name = "abs";
  c3_info[0].dominantType = "double";
  c3_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[0].fileLength = 566U;
  c3_info[0].fileTime1 = 1221299532U;
  c3_info[0].fileTime2 = 0U;
  c3_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[1].name = "nargin";
  c3_info[1].dominantType = "";
  c3_info[1].resolved = "[B]nargin";
  c3_info[1].fileLength = 0U;
  c3_info[1].fileTime1 = 0U;
  c3_info[1].fileTime2 = 0U;
  c3_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[2].name = "gt";
  c3_info[2].dominantType = "double";
  c3_info[2].resolved = "[B]gt";
  c3_info[2].fileLength = 0U;
  c3_info[2].fileTime1 = 0U;
  c3_info[2].fileTime2 = 0U;
  c3_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[3].name = "isa";
  c3_info[3].dominantType = "double";
  c3_info[3].resolved = "[B]isa";
  c3_info[3].fileLength = 0U;
  c3_info[3].fileTime1 = 0U;
  c3_info[3].fileTime2 = 0U;
  c3_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[4].name = "ischar";
  c3_info[4].dominantType = "double";
  c3_info[4].resolved = "[B]ischar";
  c3_info[4].fileLength = 0U;
  c3_info[4].fileTime1 = 0U;
  c3_info[4].fileTime2 = 0U;
  c3_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[5].name = "islogical";
  c3_info[5].dominantType = "double";
  c3_info[5].resolved = "[B]islogical";
  c3_info[5].fileLength = 0U;
  c3_info[5].fileTime1 = 0U;
  c3_info[5].fileTime2 = 0U;
  c3_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[6].name = "size";
  c3_info[6].dominantType = "double";
  c3_info[6].resolved = "[B]size";
  c3_info[6].fileLength = 0U;
  c3_info[6].fileTime1 = 0U;
  c3_info[6].fileTime2 = 0U;
  c3_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[7].name = "class";
  c3_info[7].dominantType = "double";
  c3_info[7].resolved = "[B]class";
  c3_info[7].fileLength = 0U;
  c3_info[7].fileTime1 = 0U;
  c3_info[7].fileTime2 = 0U;
  c3_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[8].name = "zeros";
  c3_info[8].dominantType = "double";
  c3_info[8].resolved = "[B]zeros";
  c3_info[8].fileLength = 0U;
  c3_info[8].fileTime1 = 0U;
  c3_info[8].fileTime2 = 0U;
  c3_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[9].name = "eml_scalar_abs";
  c3_info[9].dominantType = "double";
  c3_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c3_info[9].fileLength = 461U;
  c3_info[9].fileTime1 = 1203480360U;
  c3_info[9].fileTime2 = 0U;
  c3_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c3_info[10].name = "isinteger";
  c3_info[10].dominantType = "double";
  c3_info[10].resolved = "[B]isinteger";
  c3_info[10].fileLength = 0U;
  c3_info[10].fileTime1 = 0U;
  c3_info[10].fileTime2 = 0U;
  c3_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c3_info[11].name = "isreal";
  c3_info[11].dominantType = "double";
  c3_info[11].resolved = "[B]isreal";
  c3_info[11].fileLength = 0U;
  c3_info[11].fileTime1 = 0U;
  c3_info[11].fileTime2 = 0U;
  c3_info[12].context = "";
  c3_info[12].name = "mtimes";
  c3_info[12].dominantType = "double";
  c3_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[12].fileLength = 3425U;
  c3_info[12].fileTime1 = 1251064272U;
  c3_info[12].fileTime2 = 0U;
  c3_info[13].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[13].name = "isscalar";
  c3_info[13].dominantType = "double";
  c3_info[13].resolved = "[B]isscalar";
  c3_info[13].fileLength = 0U;
  c3_info[13].fileTime1 = 0U;
  c3_info[13].fileTime2 = 0U;
  c3_info[14].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[14].name = "strcmp";
  c3_info[14].dominantType = "char";
  c3_info[14].resolved = "[B]strcmp";
  c3_info[14].fileLength = 0U;
  c3_info[14].fileTime1 = 0U;
  c3_info[14].fileTime2 = 0U;
  c3_info[15].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[15].name = "eq";
  c3_info[15].dominantType = "double";
  c3_info[15].resolved = "[B]eq";
  c3_info[15].fileLength = 0U;
  c3_info[15].fileTime1 = 0U;
  c3_info[15].fileTime2 = 0U;
  c3_info[16].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[16].name = "not";
  c3_info[16].dominantType = "logical";
  c3_info[16].resolved = "[B]not";
  c3_info[16].fileLength = 0U;
  c3_info[16].fileTime1 = 0U;
  c3_info[16].fileTime2 = 0U;
  c3_info[17].context = "";
  c3_info[17].name = "mrdivide";
  c3_info[17].dominantType = "double";
  c3_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c3_info[17].fileLength = 432U;
  c3_info[17].fileTime1 = 1277780622U;
  c3_info[17].fileTime2 = 0U;
  c3_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c3_info[18].name = "ge";
  c3_info[18].dominantType = "double";
  c3_info[18].resolved = "[B]ge";
  c3_info[18].fileLength = 0U;
  c3_info[18].fileTime1 = 0U;
  c3_info[18].fileTime2 = 0U;
  c3_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c3_info[19].name = "rdivide";
  c3_info[19].dominantType = "double";
  c3_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c3_info[19].fileLength = 403U;
  c3_info[19].fileTime1 = 1245134820U;
  c3_info[19].fileTime2 = 0U;
  c3_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c3_info[20].name = "eml_div";
  c3_info[20].dominantType = "double";
  c3_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c3_info[20].fileLength = 4918U;
  c3_info[20].fileTime1 = 1267095810U;
  c3_info[20].fileTime2 = 0U;
}

static const mxArray *c3_b_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  boolean_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  SFc3_controller1InstanceStruct *chartInstance;
  chartInstance = (SFc3_controller1InstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_b_u = *((boolean_T *)c3_u);
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 11, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static real_T c3_emlrt_marshallIn(SFc3_controller1InstanceStruct *chartInstance,
  const mxArray *c3_y, const char_T *c3_name)
{
  real_T c3_b_y;
  real_T c3_d0;
  sf_mex_import(c3_name, sf_mex_dup(c3_y), &c3_d0, 1, 0, 0U, 0, 0U, 0);
  c3_b_y = c3_d0;
  sf_mex_destroy(&c3_y);
  return c3_b_y;
}

static uint8_T c3_b_emlrt_marshallIn(SFc3_controller1InstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_controller1,
  const char_T *c3_name)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  sf_mex_import(c3_name, sf_mex_dup(c3_b_is_active_c3_controller1), &c3_u0, 1, 3,
                0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_b_is_active_c3_controller1);
  return c3_y;
}

static void init_dsm_address_info(SFc3_controller1InstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c3_controller1_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4098680417U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(660137832U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1111757674U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2028646997U);
}

mxArray *sf_c3_controller1_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,4,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(3719275678U);
    pr[1] = (double)(4192044686U);
    pr[2] = (double)(4111541287U);
    pr[3] = (double)(4053187991U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  return(mxAutoinheritanceInfo);
}

static mxArray *sf_get_sim_state_info_c3_controller1(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c3_controller1\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_controller1_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_controller1InstanceStruct *chartInstance;
    chartInstance = (SFc3_controller1InstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_controller1MachineNumber_,
           3,
           1,
           1,
           2,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_controller1MachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_controller1MachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_controller1MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"u");
          _SFD_SET_DATA_PROPS(1,2,0,1,"y");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of EML Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",31,-1,121);
        _SFD_CV_INIT_EML_IF(0,0,68,82,-1,114);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshall);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshall);

        {
          real_T *c3_u;
          real_T *c3_y;
          c3_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c3_u = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c3_u);
          _SFD_SET_DATA_VALUE_PTR(1U, c3_y);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_controller1MachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c3_controller1(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_controller1InstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c3_controller1((SFc3_controller1InstanceStruct*)
    chartInstanceVar);
  initialize_c3_controller1((SFc3_controller1InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_controller1(void *chartInstanceVar)
{
  enable_c3_controller1((SFc3_controller1InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_controller1(void *chartInstanceVar)
{
  disable_c3_controller1((SFc3_controller1InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_controller1(void *chartInstanceVar)
{
  sf_c3_controller1((SFc3_controller1InstanceStruct*) chartInstanceVar);
}

static mxArray* sf_internal_get_sim_state_c3_controller1(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_controller1
    ((SFc3_controller1InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = sf_get_sim_state_info_c3_controller1();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

static void sf_internal_set_sim_state_c3_controller1(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_controller1();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_controller1((SFc3_controller1InstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static mxArray* sf_opaque_get_sim_state_c3_controller1(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_controller1(S);
}

static void sf_opaque_set_sim_state_c3_controller1(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c3_controller1(S, st);
}

static void sf_opaque_terminate_c3_controller1(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_controller1InstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c3_controller1((SFc3_controller1InstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  compInitSubchartSimstructsFcn_c3_controller1((SFc3_controller1InstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_controller1(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_controller1((SFc3_controller1InstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_controller1(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"controller1","controller1",3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"controller1","controller1",3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"controller1",
      "controller1",3,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"controller1","controller1",3,1);
      sf_mark_chart_reusable_outputs(S,"controller1","controller1",3,1);
    }

    sf_set_rtw_dwork_info(S,"controller1","controller1",3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1927516356U));
  ssSetChecksum1(S,(1005794560U));
  ssSetChecksum2(S,(761886919U));
  ssSetChecksum3(S,(3450252518U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c3_controller1(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "controller1", "controller1",3);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_controller1(SimStruct *S)
{
  SFc3_controller1InstanceStruct *chartInstance;
  chartInstance = (SFc3_controller1InstanceStruct *)malloc(sizeof
    (SFc3_controller1InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_controller1InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_controller1;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c3_controller1;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_controller1;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_controller1;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_controller1;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_controller1;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_controller1;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c3_controller1;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_controller1;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_controller1;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_controller1;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c3_controller1_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_controller1(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_controller1(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_controller1(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_controller1_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
