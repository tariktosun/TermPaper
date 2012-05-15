/* Include files */

#include "blascompat32.h"
#include "controller1_sfun.h"
#include "c1_controller1.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "controller1_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char *c1_debug_family_names[5] = { "th", "nargin", "nargout", "u",
  "y" };

/* Function Declarations */
static void initialize_c1_controller1(SFc1_controller1InstanceStruct
  *chartInstance);
static void initialize_params_c1_controller1(SFc1_controller1InstanceStruct
  *chartInstance);
static void enable_c1_controller1(SFc1_controller1InstanceStruct *chartInstance);
static void disable_c1_controller1(SFc1_controller1InstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_controller1
  (SFc1_controller1InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_controller1
  (SFc1_controller1InstanceStruct *chartInstance);
static void set_sim_state_c1_controller1(SFc1_controller1InstanceStruct
  *chartInstance, const mxArray *c1_st);
static void finalize_c1_controller1(SFc1_controller1InstanceStruct
  *chartInstance);
static void sf_c1_controller1(SFc1_controller1InstanceStruct *chartInstance);
static void compInitSubchartSimstructsFcn_c1_controller1
  (SFc1_controller1InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshall(void *chartInstanceVoid, void *c1_u);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[24]);
static const mxArray *c1_b_sf_marshall(void *chartInstanceVoid, void *c1_u);
static real_T c1_emlrt_marshallIn(SFc1_controller1InstanceStruct *chartInstance,
  const mxArray *c1_y, const char_T *c1_name);
static uint8_T c1_b_emlrt_marshallIn(SFc1_controller1InstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_controller1, const char_T
  *c1_name);
static void init_dsm_address_info(SFc1_controller1InstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_controller1(SFc1_controller1InstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_is_active_c1_controller1 = 0U;
}

static void initialize_params_c1_controller1(SFc1_controller1InstanceStruct
  *chartInstance)
{
}

static void enable_c1_controller1(SFc1_controller1InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_controller1(SFc1_controller1InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_controller1
  (SFc1_controller1InstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c1_controller1
  (SFc1_controller1InstanceStruct *chartInstance)
{
  const mxArray *c1_st = NULL;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  uint8_T c1_b_hoistedGlobal;
  uint8_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T *c1_d_y;
  c1_d_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(2));
  c1_hoistedGlobal = *c1_d_y;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0));
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = chartInstance->c1_is_active_c1_controller1;
  c1_b_u = c1_b_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c1_y, 1, c1_c_y);
  sf_mex_assign(&c1_st, c1_y);
  return c1_st;
}

static void set_sim_state_c1_controller1(SFc1_controller1InstanceStruct
  *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T *c1_y;
  c1_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  *c1_y = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
    "y");
  chartInstance->c1_is_active_c1_controller1 = c1_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 1)),
     "is_active_c1_controller1");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_controller1(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_controller1(SFc1_controller1InstanceStruct
  *chartInstance)
{
}

static void sf_c1_controller1(SFc1_controller1InstanceStruct *chartInstance)
{
  int32_T c1_previousEvent;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  uint32_T c1_debug_family_var_map[5];
  real_T c1_th;
  real_T c1_nargin = 1.0;
  real_T c1_nargout = 1.0;
  real_T c1_y;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_b_y;
  real_T c1_c_x;
  real_T c1_d_x;
  real_T c1_c_y;
  real_T c1_e_x;
  real_T c1_f_x;
  real_T c1_d_y;
  real_T c1_b;
  real_T c1_e_y;
  real_T c1_A;
  real_T c1_B;
  real_T c1_g_x;
  real_T c1_f_y;
  real_T c1_h_x;
  real_T c1_g_y;
  real_T c1_i_x;
  real_T c1_h_y;
  real_T c1_j_x;
  real_T c1_k_x;
  real_T c1_i_y;
  real_T c1_l_x;
  real_T c1_m_x;
  real_T c1_j_y;
  real_T c1_n_x;
  real_T c1_o_x;
  real_T c1_k_y;
  real_T c1_b_b;
  real_T c1_l_y;
  real_T c1_b_A;
  real_T c1_b_B;
  real_T c1_p_x;
  real_T c1_m_y;
  real_T c1_q_x;
  real_T c1_n_y;
  real_T c1_r_x;
  real_T c1_o_y;
  real_T *c1_b_u;
  real_T *c1_p_y;
  c1_p_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_u = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0);
  _SFD_DATA_RANGE_CHECK(*c1_b_u, 0U);
  _SFD_DATA_RANGE_CHECK(*c1_p_y, 1U);
  c1_previousEvent = _sfEvent_;
  _sfEvent_ = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0);
  c1_hoistedGlobal = *c1_b_u;
  c1_u = c1_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 5U, 5U, c1_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c1_th, c1_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c1_nargin, c1_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c1_nargout, c1_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c1_u, c1_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c1_y, c1_sf_marshall, 4U);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0, 2);
  c1_th = 0.1;
  _SFD_EML_CALL(0, 3);
  c1_x = c1_u;
  c1_b_x = c1_x;
  c1_b_y = muDoubleScalarAbs(c1_b_x);
  if (CV_EML_COND(0, 0, c1_b_y > 90.0 - c1_th)) {
    c1_c_x = c1_u;
    c1_d_x = c1_c_x;
    c1_c_y = muDoubleScalarAbs(c1_d_x);
    if (CV_EML_COND(0, 1, c1_c_y < 90.0)) {
      CV_EML_MCDC(0, 0, TRUE);
      CV_EML_IF(0, 0, TRUE);
      _SFD_EML_CALL(0, 4);
      c1_e_x = c1_u;
      c1_f_x = c1_e_x;
      c1_d_y = muDoubleScalarAbs(c1_f_x);
      c1_b = c1_d_y;
      c1_e_y = 89.9 * c1_b;
      c1_A = c1_e_y;
      c1_B = c1_u;
      c1_g_x = c1_A;
      c1_f_y = c1_B;
      c1_h_x = c1_g_x;
      c1_g_y = c1_f_y;
      c1_i_x = c1_h_x;
      c1_h_y = c1_g_y;
      c1_u = c1_i_x / c1_h_y;
      goto label_1;
    }
  }

  CV_EML_MCDC(0, 0, FALSE);
  CV_EML_IF(0, 0, FALSE);
  _SFD_EML_CALL(0, 5);
  c1_j_x = c1_u;
  c1_k_x = c1_j_x;
  c1_i_y = muDoubleScalarAbs(c1_k_x);
  if (CV_EML_COND(0, 2, c1_i_y > 90.0)) {
    c1_l_x = c1_u;
    c1_m_x = c1_l_x;
    c1_j_y = muDoubleScalarAbs(c1_m_x);
    if (CV_EML_COND(0, 3, c1_j_y < 90.0 + c1_th)) {
      CV_EML_MCDC(0, 1, TRUE);
      CV_EML_IF(0, 1, TRUE);
      _SFD_EML_CALL(0, 6);
      c1_n_x = c1_u;
      c1_o_x = c1_n_x;
      c1_k_y = muDoubleScalarAbs(c1_o_x);
      c1_b_b = c1_k_y;
      c1_l_y = 90.1 * c1_b_b;
      c1_b_A = c1_l_y;
      c1_b_B = c1_u;
      c1_p_x = c1_b_A;
      c1_m_y = c1_b_B;
      c1_q_x = c1_p_x;
      c1_n_y = c1_m_y;
      c1_r_x = c1_q_x;
      c1_o_y = c1_n_y;
      c1_u = c1_r_x / c1_o_y;
      goto label_2;
    }
  }

  CV_EML_MCDC(0, 1, FALSE);
  CV_EML_IF(0, 1, FALSE);
 label_2:
  ;
 label_1:
  ;
  _SFD_EML_CALL(0, 8);
  c1_y = c1_u;
  _SFD_EML_CALL(0, -8);
  sf_debug_symbol_scope_pop();
  *c1_p_y = c1_y;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0);
  _sfEvent_ = c1_previousEvent;
  sf_debug_check_for_state_inconsistency(_controller1MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void compInitSubchartSimstructsFcn_c1_controller1
  (SFc1_controller1InstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshall(void *chartInstanceVoid, void *c1_u)
{
  const mxArray *c1_y = NULL;
  real_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  SFc1_controller1InstanceStruct *chartInstance;
  chartInstance = (SFc1_controller1InstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u = *((real_T *)c1_u);
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

const mxArray *sf_c1_controller1_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_ResolvedFunctionInfo c1_info[24];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i0;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 24));
  for (c1_i0 = 0; c1_i0 < 24; c1_i0 = c1_i0 + 1) {
    c1_r0 = &c1_info[c1_i0];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context",
                    "nameCaptureInfo", c1_i0);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name",
                    "nameCaptureInfo", c1_i0);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c1_i0);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved"
                    , "nameCaptureInfo", c1_i0);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileLength,
      7, 0U, 0U, 0U, 0), "fileLength", "nameCaptureInfo",
                    c1_i0);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTime1, 7,
      0U, 0U, 0U, 0), "fileTime1", "nameCaptureInfo", c1_i0);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTime2, 7,
      0U, 0U, 0U, 0), "fileTime2", "nameCaptureInfo", c1_i0);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[24])
{
  c1_info[0].context = "";
  c1_info[0].name = "abs";
  c1_info[0].dominantType = "double";
  c1_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[0].fileLength = 566U;
  c1_info[0].fileTime1 = 1221299532U;
  c1_info[0].fileTime2 = 0U;
  c1_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[1].name = "nargin";
  c1_info[1].dominantType = "";
  c1_info[1].resolved = "[B]nargin";
  c1_info[1].fileLength = 0U;
  c1_info[1].fileTime1 = 0U;
  c1_info[1].fileTime2 = 0U;
  c1_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[2].name = "gt";
  c1_info[2].dominantType = "double";
  c1_info[2].resolved = "[B]gt";
  c1_info[2].fileLength = 0U;
  c1_info[2].fileTime1 = 0U;
  c1_info[2].fileTime2 = 0U;
  c1_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[3].name = "isa";
  c1_info[3].dominantType = "double";
  c1_info[3].resolved = "[B]isa";
  c1_info[3].fileLength = 0U;
  c1_info[3].fileTime1 = 0U;
  c1_info[3].fileTime2 = 0U;
  c1_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[4].name = "ischar";
  c1_info[4].dominantType = "double";
  c1_info[4].resolved = "[B]ischar";
  c1_info[4].fileLength = 0U;
  c1_info[4].fileTime1 = 0U;
  c1_info[4].fileTime2 = 0U;
  c1_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[5].name = "islogical";
  c1_info[5].dominantType = "double";
  c1_info[5].resolved = "[B]islogical";
  c1_info[5].fileLength = 0U;
  c1_info[5].fileTime1 = 0U;
  c1_info[5].fileTime2 = 0U;
  c1_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[6].name = "size";
  c1_info[6].dominantType = "double";
  c1_info[6].resolved = "[B]size";
  c1_info[6].fileLength = 0U;
  c1_info[6].fileTime1 = 0U;
  c1_info[6].fileTime2 = 0U;
  c1_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[7].name = "class";
  c1_info[7].dominantType = "double";
  c1_info[7].resolved = "[B]class";
  c1_info[7].fileLength = 0U;
  c1_info[7].fileTime1 = 0U;
  c1_info[7].fileTime2 = 0U;
  c1_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[8].name = "zeros";
  c1_info[8].dominantType = "double";
  c1_info[8].resolved = "[B]zeros";
  c1_info[8].fileLength = 0U;
  c1_info[8].fileTime1 = 0U;
  c1_info[8].fileTime2 = 0U;
  c1_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[9].name = "eml_scalar_abs";
  c1_info[9].dominantType = "double";
  c1_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[9].fileLength = 461U;
  c1_info[9].fileTime1 = 1203480360U;
  c1_info[9].fileTime2 = 0U;
  c1_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[10].name = "isinteger";
  c1_info[10].dominantType = "double";
  c1_info[10].resolved = "[B]isinteger";
  c1_info[10].fileLength = 0U;
  c1_info[10].fileTime1 = 0U;
  c1_info[10].fileTime2 = 0U;
  c1_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[11].name = "isreal";
  c1_info[11].dominantType = "double";
  c1_info[11].resolved = "[B]isreal";
  c1_info[11].fileLength = 0U;
  c1_info[11].fileTime1 = 0U;
  c1_info[11].fileTime2 = 0U;
  c1_info[12].context = "";
  c1_info[12].name = "minus";
  c1_info[12].dominantType = "double";
  c1_info[12].resolved = "[B]minus";
  c1_info[12].fileLength = 0U;
  c1_info[12].fileTime1 = 0U;
  c1_info[12].fileTime2 = 0U;
  c1_info[13].context = "";
  c1_info[13].name = "lt";
  c1_info[13].dominantType = "double";
  c1_info[13].resolved = "[B]lt";
  c1_info[13].fileLength = 0U;
  c1_info[13].fileTime1 = 0U;
  c1_info[13].fileTime2 = 0U;
  c1_info[14].context = "";
  c1_info[14].name = "mtimes";
  c1_info[14].dominantType = "double";
  c1_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[14].fileLength = 3425U;
  c1_info[14].fileTime1 = 1251064272U;
  c1_info[14].fileTime2 = 0U;
  c1_info[15].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[15].name = "isscalar";
  c1_info[15].dominantType = "double";
  c1_info[15].resolved = "[B]isscalar";
  c1_info[15].fileLength = 0U;
  c1_info[15].fileTime1 = 0U;
  c1_info[15].fileTime2 = 0U;
  c1_info[16].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[16].name = "strcmp";
  c1_info[16].dominantType = "char";
  c1_info[16].resolved = "[B]strcmp";
  c1_info[16].fileLength = 0U;
  c1_info[16].fileTime1 = 0U;
  c1_info[16].fileTime2 = 0U;
  c1_info[17].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[17].name = "eq";
  c1_info[17].dominantType = "double";
  c1_info[17].resolved = "[B]eq";
  c1_info[17].fileLength = 0U;
  c1_info[17].fileTime1 = 0U;
  c1_info[17].fileTime2 = 0U;
  c1_info[18].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[18].name = "not";
  c1_info[18].dominantType = "logical";
  c1_info[18].resolved = "[B]not";
  c1_info[18].fileLength = 0U;
  c1_info[18].fileTime1 = 0U;
  c1_info[18].fileTime2 = 0U;
  c1_info[19].context = "";
  c1_info[19].name = "mrdivide";
  c1_info[19].dominantType = "double";
  c1_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[19].fileLength = 432U;
  c1_info[19].fileTime1 = 1277780622U;
  c1_info[19].fileTime2 = 0U;
  c1_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[20].name = "ge";
  c1_info[20].dominantType = "double";
  c1_info[20].resolved = "[B]ge";
  c1_info[20].fileLength = 0U;
  c1_info[20].fileTime1 = 0U;
  c1_info[20].fileTime2 = 0U;
  c1_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[21].name = "rdivide";
  c1_info[21].dominantType = "double";
  c1_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[21].fileLength = 403U;
  c1_info[21].fileTime1 = 1245134820U;
  c1_info[21].fileTime2 = 0U;
  c1_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[22].name = "eml_div";
  c1_info[22].dominantType = "double";
  c1_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c1_info[22].fileLength = 4918U;
  c1_info[22].fileTime1 = 1267095810U;
  c1_info[22].fileTime2 = 0U;
  c1_info[23].context = "";
  c1_info[23].name = "plus";
  c1_info[23].dominantType = "double";
  c1_info[23].resolved = "[B]plus";
  c1_info[23].fileLength = 0U;
  c1_info[23].fileTime1 = 0U;
  c1_info[23].fileTime2 = 0U;
}

static const mxArray *c1_b_sf_marshall(void *chartInstanceVoid, void *c1_u)
{
  const mxArray *c1_y = NULL;
  boolean_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  SFc1_controller1InstanceStruct *chartInstance;
  chartInstance = (SFc1_controller1InstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u = *((boolean_T *)c1_u);
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 11, 0U, 0U, 0U, 0));
  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static real_T c1_emlrt_marshallIn(SFc1_controller1InstanceStruct *chartInstance,
  const mxArray *c1_y, const char_T *c1_name)
{
  real_T c1_b_y;
  real_T c1_d0;
  sf_mex_import(c1_name, sf_mex_dup(c1_y), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_b_y = c1_d0;
  sf_mex_destroy(&c1_y);
  return c1_b_y;
}

static uint8_T c1_b_emlrt_marshallIn(SFc1_controller1InstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_controller1,
  const char_T *c1_name)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_name, sf_mex_dup(c1_b_is_active_c1_controller1), &c1_u0, 1, 3,
                0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_b_is_active_c1_controller1);
  return c1_y;
}

static void init_dsm_address_info(SFc1_controller1InstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c1_controller1_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3307670036U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2312565829U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2471867388U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3273837069U);
}

mxArray *sf_c1_controller1_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,4,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(197768333U);
    pr[1] = (double)(3909635009U);
    pr[2] = (double)(1660578046U);
    pr[3] = (double)(2969166736U);
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

static mxArray *sf_get_sim_state_info_c1_controller1(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c1_controller1\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_controller1_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_controller1InstanceStruct *chartInstance;
    chartInstance = (SFc1_controller1InstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_controller1MachineNumber_,
           1,
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
        _SFD_CV_INIT_EML(0,1,2,0,0,0,0,4,2);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,188);
        _SFD_CV_INIT_EML_IF(0,0,38,71,106,143);
        _SFD_CV_INIT_EML_IF(0,1,106,143,-1,143);

        {
          static int condStart[] = { 41, 59 };

          static int condEnd[] = { 55, 70 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,0,41,70,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        {
          static int condStart[] = { 113, 128 };

          static int condEnd[] = { 124, 142 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,113,142,2,2,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshall);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshall);

        {
          real_T *c1_u;
          real_T *c1_y;
          c1_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c1_u = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c1_u);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_y);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_controller1MachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c1_controller1(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_controller1InstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c1_controller1((SFc1_controller1InstanceStruct*)
    chartInstanceVar);
  initialize_c1_controller1((SFc1_controller1InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_controller1(void *chartInstanceVar)
{
  enable_c1_controller1((SFc1_controller1InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_controller1(void *chartInstanceVar)
{
  disable_c1_controller1((SFc1_controller1InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_controller1(void *chartInstanceVar)
{
  sf_c1_controller1((SFc1_controller1InstanceStruct*) chartInstanceVar);
}

static mxArray* sf_internal_get_sim_state_c1_controller1(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_controller1
    ((SFc1_controller1InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = sf_get_sim_state_info_c1_controller1();/* state var info */
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

static void sf_internal_set_sim_state_c1_controller1(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_controller1();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_controller1((SFc1_controller1InstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static mxArray* sf_opaque_get_sim_state_c1_controller1(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_controller1(S);
}

static void sf_opaque_set_sim_state_c1_controller1(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c1_controller1(S, st);
}

static void sf_opaque_terminate_c1_controller1(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_controller1InstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c1_controller1((SFc1_controller1InstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  compInitSubchartSimstructsFcn_c1_controller1((SFc1_controller1InstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_controller1(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_controller1((SFc1_controller1InstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_controller1(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"controller1","controller1",1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"controller1","controller1",1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"controller1",
      "controller1",1,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"controller1","controller1",1,1);
      sf_mark_chart_reusable_outputs(S,"controller1","controller1",1,1);
    }

    sf_set_rtw_dwork_info(S,"controller1","controller1",1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3024855993U));
  ssSetChecksum1(S,(1674590172U));
  ssSetChecksum2(S,(3873783345U));
  ssSetChecksum3(S,(2425995982U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c1_controller1(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "controller1", "controller1",1);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_controller1(SimStruct *S)
{
  SFc1_controller1InstanceStruct *chartInstance;
  chartInstance = (SFc1_controller1InstanceStruct *)malloc(sizeof
    (SFc1_controller1InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_controller1InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_controller1;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_controller1;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_controller1;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_controller1;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_controller1;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_controller1;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_controller1;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_controller1;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_controller1;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_controller1;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_controller1;
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

void c1_controller1_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_controller1(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_controller1(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_controller1(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_controller1_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
