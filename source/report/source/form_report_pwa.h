//---------------------------------------------------------------------------
#ifndef form_report_pwaH
#define form_report_pwaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
#include "TeeDraw3D.hpp"
#include <jpeg.hpp>
#include "GIFImage.hpp"
#include "TeeOpenGL.hpp"
#include <meas\pubtype.h>
#include <scor\child.h>

class TPWA;
//---------------------------------------------------------------------------
class Tfrm_report_pwa : public Child_Form
{
__published:	// IDE-managed Components
  TPanel *pnl_form;
  TPanel *pnl_grid;
    TPopupMenu *ppmnu_report;
    TMenuItem *mnu_text;
    TMenuItem *mnu_graphic;
  TImageList *ImageListDisable;
  TImageList *ImageListEnabled;
   TMenuItem *mnu_all;
   TPanel *pnl_assessments;
   TLabel *lbl_assessments_title;
   TPanel *pnl_study_information;
   TDBGrid *grd_report;
   TPanel *pnl_patient_information;
   TLabel *Label4;
   TLabel *lbl_pname;
   TLabel *lbl_pid_title;
   TLabel *lbl_pid;
   TLabel *lbl_birth_date_title;
   TLabel *lbl_age_title;
   TLabel *lbl_sex_title;
   TLabel *lbl_age;
   TLabel *lbl_birth_date;
   TLabel *lbl_sex;
   TLabel *Label3;
   TLabel *lbl_operator_title;
   TLabel *lbl_operator;
   TLabel *lbl_hwbmi_title;
   TLabel *lbl_hwbmi;
   TLabel *lbl_med_title;
   TLabel *lbl_notes_title;
   TLabel *lbl_interpretation_title;
   TMemo *edt_interpretation;
   TMemo *edt_notes;
   TMemo *edt_med;
   TPanel *pnl_main;
   TPageControl *pgctrl_reports;
   TTabSheet *tbsht_detailed;
   TPanel *pnl_canvas;
   TPanel *pnl_patient_details;
   TLabel *lbl_patient_title;
   TLabel *lbl_pcode_title;
   TLabel *lbl_pcode;
   TLabel *lbl_add_title;
   TLabel *lbl_address1;
   TLabel *lbl_address2;
   TLabel *lbl_address3;
   TPanel *pnl_params;
   TPanel *pnl_chp_bottom;
   TPanel *pnl_left;
   TLabel *lbl_hr_title;
   TLabel *lbl_hr;
   TLabel *lbl_ed;
   TLabel *lbl_ed_title;
   TLabel *lbl_t1t2_title;
   TLabel *lbl_t1t2;
   TLabel *Label1;
   TLabel *Label2;
   TPanel *pnl_centre;
   TLabel *lbl_title_augidx;
   TLabel *lbl_aug_title;
   TLabel *lbl_p1_title;
   TLabel *lbl_p1;
   TLabel *lbl_aug;
   TLabel *lbl_aug_idx;
   TLabel *lbl_augidx_hr75;
   TLabel *lbl_augidx_hr75_title;
   TPanel *pnl_right;
   TLabel *lbl_title_mp;
   TLabel *lbl_svr_title;
   TLabel *lbl_title_endsyst;
   TLabel *lbl_svr;
   TLabel *lbl_mp;
   TLabel *lbl_endsyst;
   TLabel *lbl_pti_title;
   TLabel *lbl_pti;
   TPanel *pnl_chp_title;
   TLabel *lbl_param_title;
   TPanel *pnl_periph_data;
   TLabel *lbl_periph_data_title;
   TLabel *lbl_periph_data;
   TLabel *lbl_ppamplification_title;
   TLabel *lbl_ppamp;
   TLabel *lbl_al_title;
   TLabel *lbl_al;
   TPanel *pnl_study_details;
   TLabel *lbl_study_title;
   TLabel *lbl_date;
   TLabel *lbl_time;
   TLabel *lbl_tonometer_title;
   TLabel *lbl_tonometer;
   TPanel *pnl_reason;
   TLabel *lbl_reason_title;
   TLabel *lbl_qc_title;
   TMemo *edtReason;
   TPanel *pnl_avg;
   TPanel *pnl_periph_pressure;
   TLabel *lbl_psp_title;
   TLabel *lbl_pdp_title;
   TLabel *lbl_pmp_title;
   TLabel *lbl_ppp_title;
   TLabel *lbl_psp;
   TLabel *lbl_pdp;
   TLabel *lbl_pmp;
   TLabel *lbl_ppp;
   TLabel *lbl_pavg_val;
   TPanel *pnl_central_pressure;
   TLabel *lbl_csp_title;
   TLabel *lbl_cdp_title;
   TLabel *lbl_cmp_title;
   TLabel *lbl_cpp_title;
   TLabel *lbl_cpp;
   TLabel *lbl_csp;
   TLabel *lbl_cdp;
   TLabel *lbl_cmp;
   TLabel *lbl_cavg_val;
   TPanel *pnl_avg_central;
   TToolBar *tbar_change_t1t2;
   TToolButton *btn_move_t1_left;
   TToolButton *btn_move_t1_right;
   TToolButton *ToolButton3;
   TToolButton *btn_move_t1_accept;
   TToolButton *btn_move_t1_cancel;
   TToolButton *ToolButton1;
   TToolButton *btn_move_t2_left;
   TToolButton *btn_move_t2_right;
   TToolButton *ToolButton5;
   TToolButton *btn_move_t2_accept;
   TToolButton *btn_move_t2_cancel;
   TChart *chrt_avg_central;
   TLineSeries *srs_avg_central;
   TLineSeries *srs_avg_ced;
   TPointSeries *srs_avg_t1_timing;
   TPointSeries *srs_avg_t2_timing;
   TLineSeries *srs_avg_t1;
   TLineSeries *srs_avg_t2;
   TPanel *pnl_avg_periph;
   TToolBar *tbar_change_ed;
   TToolButton *btn_move_ed_left;
   TToolButton *btn_move_ed_right;
   TToolButton *tbtn_separator_edadjust;
   TToolButton *btn_move_ed_accept;
   TToolButton *btn_move_ed_cancel;
   TChart *chrt_avg_periph;
   TLineSeries *srs_avg_periph;
   TLineSeries *srs_avg_ped;
   TPointSeries *srs_avg_ptiming;
   TPanel *pnl_waveform;
   TPanel *pnl_pulses;
   TChart *chrt_pulse_periph;
   TLineSeries *srs_pulse_periph;
   TPointSeries *srs_trigs_periph;
   TChart *chrt_pulse_central;
   TLineSeries *srs_pulse_central;
   TPointSeries *srs_trigs_central;
   TPanel *pnl_qc_back;
   TPanel *pnl_qc;
   TLabel *lbl_qc1;
   TLabel *lbl_qc2;
   TLabel *lbl_qc3;
   TLabel *lbl_qc5_dpdt;
   TLabel *lbl_qc4;
   TLabel *lbl_qc6;
   TPanel *pnl_qc_pulse_overlay_back;
   TPanel *pnl_qcidx_back;
   TLabel *lbl_qcidx_title;
   TLabel *lbl_qcidx;
   TTabSheet *tbsht_clinical;
   TPanel *pnl_clinical;
   TPanel *pnl_central_periph;
   TChart *chrt_avg_central_periph;
   TLineSeries *srs_avg_clinical_central;
   TLineSeries *srs_avg_clinical_ed;
   TPointSeries *srs_avg_clinical_t1;
   TPointSeries *srs_avg_clinical_t2;
   TLineSeries *srs_avg_clinical_ap;
   TLineSeries *srs_avg_clinical_p1;
   TLineSeries *srs_avg_clinical_p2;
   TPanel *pnl_operator_index;
   TPanel *pnl_clinical_qc_params;
   TLabel *lbl_clinical_qc_ph;
   TLabel *lbl_clinical_qc_phv;
   TLabel *lbl_clinical_qc_dv;
   TLabel *lbl_clinical_qc_sd;
   TLabel *lbl_clinical_qc_ph_title;
   TLabel *lbl_clinical_qc_phv_title;
   TLabel *lbl_clinical_qc_dv_title;
   TLabel *lbl_clinical_qc_sd_title;
   TLabel *lbl_clinical_operatoridx_title;
   TLabel *lbl_clinical_operatoridx;
   TChart *chrt_pulse_overlay;
   TPanel *pnl_clinical_parameters;
   TPanel *pnl_clinical_pressures;
   TLabel *lbl_clinical_aortic;
   TLabel *lbl_clinical_peripheral;
   TLabel *lbl_clinical_sp_title;
   TLabel *lbl_clinical_dp_title;
   TLabel *lbl_clinical_mp_title;
   TLabel *lbl_clinical_pp_title;
   TLabel *lbl_clinical_psp;
   TLabel *lbl_clinical_pdp;
   TLabel *lbl_clinical_pmp;
   TLabel *lbl_clinical_ppp;
   TLabel *lbl_clinical_csp;
   TLabel *lbl_clinical_cdp;
   TLabel *lbl_clinical_cmp;
   TLabel *lbl_clinical_cpp;
   TPanel *pnl_clinical_sp;
   TLabel *lbl_clinical_csp_title;
   TLabel *lbl_clinical_csp_units;
   TShape *shape_clinical_sp_range;
   TShape *shape_clinical_sp_lower;
   TLabel *lbl_clinical_sp;
   TLabel *lbl_clinical_sp_lower;
   TLabel *lbl_clinical_sp_upper;
   TShape *shape_clinical_sp_high;
   TShape *shape_clinical_sp_upper;
   TShape *shape_clinical_sp;
   TPanel *pnl_clinical_pp;
   TLabel *lbl_clinical_cpp_title;
   TLabel *lbl_clinical_cpp_units;
   TShape *shape_clinical_pp_range;
   TShape *shape_clinical_pp_lower;
   TLabel *lbl_clinical_pp_lower;
   TLabel *lbl_clinical_pp_upper;
   TShape *shape_clinical_pp_high;
   TShape *shape_clinical_pp_upper;
   TLabel *lbl_clinical_pp;
   TShape *shape_clinical_pp;
   TPanel *pnl_clinical_ap;
   TLabel *lbl_clinical_ap_title;
   TLabel *lbl_clinical_ap_units;
   TShape *shape_clinical_ap_range;
   TShape *shape_clinical_ap_lower;
   TLabel *lbl_clinical_ap;
   TLabel *lbl_clinical_ap_lower;
   TLabel *lbl_clinical_ap_upper;
   TShape *shape_clinical_ap_high;
   TShape *shape_clinical_ap_upper;
   TShape *shape_clinical_ap;
   TPanel *pnl_clinical_aixhr75;
   TLabel *lbl_clinical_aixhr75_title;
   TLabel *lbl_clinical_aixhr75_units;
   TShape *shape_clinical_aixhr75_range;
   TLabel *lbl_clinical_aixhr75;
   TLabel *lbl_clinical_aixhr75_lower;
   TLabel *lbl_clinical_aixhr75_upper;
   TShape *shape_clinical_aixhr75_high;
   TShape *shape_clinical_aixhr75_lower;
   TShape *shape_clinical_aixhr75_upper;
   TShape *shape_clinical_aixhr75;
   TPanel *pnl_clinical_aix;
   TLabel *lbl_clinical_aix_title;
   TLabel *lbl_clinical_aix_units;
   TShape *shape_clinical_aix_range;
   TShape *shape_clinical_aix_upper;
   TShape *shape_clinical_aix_lower;
   TLabel *lbl_clinical_aix;
   TLabel *lbl_clinical_aix_lower;
   TLabel *lbl_clinical_aix_upper;
   TShape *shape_clinical_aix_high;
   TShape *shape_clinical_aix;
   TPanel *pnl_clinical_reference_age;
   TLabel *lbl_clinical_cv_age_title;
   TShape *shape_cv_range;
   TShape *shape_cv_age;
   TLabel *lbl_age_20;
   TLabel *lbl_age_40;
   TLabel *lbl_age_30;
   TLabel *lbl_age_50;
   TLabel *lbl_age_60;
   TLabel *lbl_age_70;
   TLabel *lbl_age_80;
   TTabSheet *tbsht_reference;
   TPanel *pnl_reference;
   TPanel *pnl_reference_main;
   TChart *chrt_ap_reference;
   TLineSeries *srs_ap_normal_reference;
   TLineSeries *srs_ap_upper_reference;
   TLineSeries *srs_ap_lower_reference;
   TPointSeries *srs_ap_hr75_point_reference;
   TPointSeries *srs_ap_point_reference;
   TChart *chrt_sevr_flow_reference;
   TLineSeries *srs_sevr_flow;
   TPointSeries *srs_sevr_flow_point;
   TPanel *pnl_reference_bottom;
   TPanel *pnl_reference_three;
   TChart *chrt_augidx_reference;
   TLineSeries *srs_aix_normal_reference;
   TLineSeries *srs_aix_upper_reference;
   TLineSeries *srs_aix_lower_reference;
   TPointSeries *srs_aix_hr75_point_reference;
   TPointSeries *srs_aix_point_reference;
   TPanel *pnl_reference_four;
   TChart *chrt_ed_reference;
   TLineSeries *srs_ed_normal_reference;
   TLineSeries *srs_ed_upper_reference;
   TLineSeries *srs_ed_lower_reference;
   TPointSeries *srs_ed_point_reference;
   TPanel *pnl_reference_five;
   TChart *chrt_sevr_reference;
   TLineSeries *srs_sevr_normal_reference;
   TLineSeries *srs_sevr_upper_reference;
   TLineSeries *srs_sevr_lower_reference;
   TPointSeries *srs_sevr_point_reference;
   TPanel *pnl_reference_left;
   TPanel *pnl_reference_one;
   TChart *chrt_sp_reference;
   TLineSeries *srs_sp_normal_reference;
   TLineSeries *srs_sp_upper_reference;
   TLineSeries *srs_sp_lower_reference;
   TPointSeries *srs_sp_point_reference;
   TPanel *pnl_reference_two;
   TChart *chrt_pp_reference;
   TLineSeries *srs_pp_normal_reference;
   TLineSeries *srs_pp_upper_reference;
   TLineSeries *srs_pp_lower_reference;
   TPointSeries *srs_pp_point_reference;
   TTabSheet *tbsht_avi;
   TPanel *pnl_avi_graphs;
   TPanel *pnl_centre_avi_graphs;
   TChart *chrt_avi_flow;
   TLineSeries *srs_avi_flow;
   TPointSeries *srs_avi_flow_ed;
   TPanel *pnl_avi_params_left;
   TLabel *lbl_avi_ipph_title;
   TLabel *lbl_avi_ipph;
   TLabel *lbl_avi_rpph_title;
   TLabel *lbl_avi_rpph;
   TLabel *lbl_avi_ippt_title;
   TLabel *lbl_avi_ippt;
   TLabel *lbl_avi_rppt_title;
   TLabel *lbl_avi_rppt;
   TLabel *lbl_avi_ri_title;
   TLabel *lbl_avi_ri;
   TLabel *lbl_avi_aptt_title;
   TLabel *lbl_avi_aptt;
   TLabel *Label19;
   TLabel *Label20;
   TLabel *lbl_avi_cftt_title;
   TLabel *lbl_avi_cftt;
   TLabel *Label11;
   TLabel *lbl_avi_pwv_title;
   TLabel *lbl_avi_pwv;
   TPanel *pnl_avi_left;
   TChart *chrt_avi_avg_central;
   TLineSeries *srs_avi_avg_central;
   TLineSeries *srs_avi_avg_ed;
   TPointSeries *srs_avi_avg_t1;
   TPointSeries *srs_avi_avg_t2;
   TPanel *pnl_avi_right;
   TChart *chrt_avi_reflected;
   TLineSeries *srs_avi_forward;
   TLineSeries *srs_avi_reflected;
   TLineSeries *srs_avi_reflected_ed;
   TPointSeries *srs_avi_reflected_timing;
   TPointSeries *srs_avi_forward_timing;
   TLineSeries *srs_avi_forward_line;
   TLineSeries *srs_avi_reflected_line;
   TPanel *pnl_avi_study_details;
   TLabel *lbl_avi_study_title;
   TLabel *lbl_avi_date;
   TLabel *lbl_avi_time;
   TLabel *lbl_avi_tonometer_title;
   TLabel *lbl_avi_tonometer;
   TLabel *lbl_avi_distance;
   TLabel *lbl_avi_distance_title;
   TPanel *pnl_avi_reason;
   TLabel *lbl_avi_reason_title;
   TMemo *edt_avi_reason;
   TPanel *pnl_avi_patient_details;
   TLabel *lbl_avi_patient_title;
   TLabel *lbl_avi_pcode_title;
   TLabel *lbl_avi_add_title;
   TLabel *lbl_avi_address1;
   TLabel *lbl_avi_pcode;
   TLabel *lbl_avi_address2;
   TLabel *lbl_avi_address3;
   TPanel *pnl_report_buttons;
   TLabel *lbl_clinical_hr_title;
   TLabel *lbl_clinical_hr;
   TPanel *pnl_status_bar;
   TLabel *lbl_message2;
   TLabel *lbl_message1;
   TLabel *lbl_message3;
   TSpeedButton *bbtn_audit;
   TSpeedButton *bbtn_modify;
   TSpeedButton *bbtn_delete;
   TSpeedButton *bbtn_export;
   TSpeedButton *bbtn_print;
   TSpeedButton *bbtn_repeat;
   TSpeedButton *bbtn_session;
   TLabel *lbl_message4;
  void __fastcall pnl_avgResize(TObject *Sender);
  void __fastcall chrt_avg_periphMouseDown(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall chrt_avg_periphMouseUp(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall chrt_avg_periphMouseMove(TObject *Sender,
        TShiftState Shift, int X, int Y);
  void __fastcall chrt_avg_centralMouseMove(TObject *Sender,
        TShiftState Shift, int X, int Y);
  void __fastcall srs_avg_periphGetMarkText(TChartSeries *Sender,
        int ValueIndex, AnsiString &MarkText);
  void __fastcall chrt_avg_periphZoom(TObject *Sender);
  void __fastcall chrt_avg_periphUndoZoom(TObject *Sender);
  void __fastcall pnl_waveformResize(TObject *Sender);
  void __fastcall chrt_avg_centralMouseDown(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall chrt_avg_centralMouseUp(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall chrt_avg_centralZoom(TObject *Sender);
  void __fastcall chrt_avg_centralUndoZoom(TObject *Sender);
  void __fastcall srs_avg_centralGetMarkText(TChartSeries *Sender,
        int ValueIndex, AnsiString &MarkText);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormHide(TObject *Sender);
  void __fastcall srs_avg_t1_timingGetMarkText(TChartSeries *Sender,
        int ValueIndex, AnsiString &MarkText);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);

  
  void __fastcall lbl_ed_titleDblClick(TObject *Sender);
  
  void __fastcall btn_move_ed_leftClick(TObject *Sender);
  void __fastcall btn_move_ed_rightClick(TObject *Sender);
  void __fastcall btn_move_ed_cancelClick(TObject *Sender);
  void __fastcall btn_move_ed_acceptClick(TObject *Sender);
  
  
  void __fastcall chrt_avg_periphClickSeries(TCustomChart *Sender,
          TChartSeries *Series, int ValueIndex, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall chrt_avg_centralClickSeries(TCustomChart *Sender,
          TChartSeries *Series, int ValueIndex, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    
    void __fastcall mnu_graphicClick(TObject *Sender);
    
    
    
    
    void __fastcall mnu_textClick(TObject *Sender);
   void __fastcall pnl_canvasResize(TObject *Sender);
   void __fastcall pnl_chp_bottomResize(TObject *Sender);
   void __fastcall srs_ap_hr75_pointGetMarkText(TChartSeries *Sender,
          int ValueIndex, AnsiString &MarkText);
   void __fastcall srs_augidx_hr75_pointGetMarkText(TChartSeries *Sender,
          int ValueIndex, AnsiString &MarkText);
   void __fastcall chrt_avg_central_periphMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall chrt_avg_central_periphMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall chrt_avg_central_periphZoom(TObject *Sender);
   void __fastcall chrt_avg_central_periphUndoZoom(TObject *Sender);
   void __fastcall srs_avg_clinical_centralGetMarkText(
          TChartSeries *Sender, int ValueIndex, AnsiString &MarkText);
   void __fastcall chrt_avg_central_periphMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
   void __fastcall lbl_clinical_csp_titleClick(TObject *Sender);
   void __fastcall tbsht_referenceResize(TObject *Sender);
   void __fastcall lbl_clinical_cpp_titleClick(TObject *Sender);
   void __fastcall lbl_clinical_aixhr75_titleClick(TObject *Sender);
   void __fastcall lbl_clinical_ap_titleClick(TObject *Sender);
   void __fastcall lbl_clinical_ed_titleClick(TObject *Sender);
   void __fastcall lbl_clinical_sevr_titleClick(TObject *Sender);
   void __fastcall chrt_sp_referenceClick(TObject *Sender);
   void __fastcall chrt_pp_referenceClick(TObject *Sender);
   void __fastcall chrt_augidx_referenceClick(TObject *Sender);
   void __fastcall chrt_ap_referenceClick(TObject *Sender);
   void __fastcall chrt_ed_referenceClick(TObject *Sender);
   void __fastcall chrt_sevr_referenceClick(TObject *Sender);
   void __fastcall pnl_avi_graphsResize(TObject *Sender);
   void __fastcall chrt_avi_avg_centralZoom(TObject *Sender);
   void __fastcall chrt_avi_avg_centralUndoZoom(TObject *Sender);
   void __fastcall chrt_avi_avg_centralMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall chrt_avi_avg_centralMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall srs_avi_avg_centralGetMarkText(TChartSeries *Sender,
          int ValueIndex, AnsiString &MarkText);
   void __fastcall chrt_avi_reflectedZoom(TObject *Sender);
   void __fastcall chrt_avi_reflectedUndoZoom(TObject *Sender);
   void __fastcall chrt_avi_reflectedMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall chrt_avi_reflectedMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall srs_avi_forwardGetMarkText(TChartSeries *Sender,
          int ValueIndex, AnsiString &MarkText);
   void __fastcall srs_avi_reflectedGetMarkText(TChartSeries *Sender,
          int ValueIndex, AnsiString &MarkText);
   void __fastcall chrt_avi_flowZoom(TObject *Sender);
   void __fastcall chrt_avi_flowUndoZoom(TObject *Sender);
   void __fastcall srs_avi_reflected_timingGetMarkText(
          TChartSeries *Sender, int ValueIndex, AnsiString &MarkText);
   void __fastcall srs_avi_reflected_timingClick(TChartSeries *Sender,
          int ValueIndex, TMouseButton Button, TShiftState Shift, int X,
          int Y);
   void __fastcall lbl_avi_rpph_titleClick(TObject *Sender);
   void __fastcall lbl_avi_rppt_titleClick(TObject *Sender);
   void __fastcall lbl_avi_ipph_titleClick(TObject *Sender);
   void __fastcall lbl_avi_ippt_titleClick(TObject *Sender);
   void __fastcall srs_avi_forward_timingClick(TChartSeries *Sender,
          int ValueIndex, TMouseButton Button, TShiftState Shift, int X,
          int Y);
   void __fastcall srs_avi_forward_timingGetMarkText(TChartSeries *Sender,
          int ValueIndex, AnsiString &MarkText);
   void __fastcall srs_avg_t1_timingClick(TChartSeries *Sender,
          int ValueIndex, TMouseButton Button, TShiftState Shift, int X,
          int Y);
   void __fastcall lbl_t1t2_titleClick(TObject *Sender);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall srs_avg_t2_timingClick(TChartSeries *Sender,
          int ValueIndex, TMouseButton Button, TShiftState Shift, int X,
          int Y);
   void __fastcall srs_avg_t2_timingGetMarkText(TChartSeries *Sender,
          int ValueIndex, AnsiString &MarkText);
   void __fastcall lbl_t1t2_titleDblClick(TObject *Sender);
   void __fastcall btn_move_t1_leftClick(TObject *Sender);
   void __fastcall btn_move_t1_rightClick(TObject *Sender);
   void __fastcall btn_move_t1_acceptClick(TObject *Sender);
   void __fastcall btn_move_t1_cancelClick(TObject *Sender);
   void __fastcall btn_move_t2_leftClick(TObject *Sender);
   void __fastcall btn_move_t2_rightClick(TObject *Sender);
   void __fastcall btn_move_t2_acceptClick(TObject *Sender);
   void __fastcall btn_move_t2_cancelClick(TObject *Sender);
   void __fastcall mnu_allClick(TObject *Sender);
   void __fastcall tbsht_detailedShow(TObject *Sender);
   void __fastcall tbsht_clinicalShow(TObject *Sender);
   void __fastcall bbtn_deleteClick(TObject *Sender);
   void __fastcall bbtn_printClick(TObject *Sender);
   void __fastcall bbtn_modifyClick(TObject *Sender);
   void __fastcall bbtn_auditClick(TObject *Sender);
   void __fastcall bbtn_sessionClick(TObject *Sender);
   void __fastcall bbtn_repeatClick(TObject *Sender);
private:	// User declarations
    void print_report_header(TRect *print_area);
    void print_report_footer(TRect *print_area);
    void print_report_patient(TRect *print_area);
    int  print_report_study(TPrinter *print_ptr, TRect *print_area);
    void print_report_qc(TPrinter *print_ptr, TRect *print_area);
    void print_report_clinical_qc(TPrinter *print_ptr, TRect *print_area);
    void print_report_central_params(TPrinter *print_ptr, TRect *print_area);
    void print_report_clinical_central_params(TPrinter *print_ptr, TRect *print_area);
    void print_report_avi_params(TPrinter *print_ptr, TRect *print_area);
    void print_report_pressures(TPrinter *print_ptr, TRect *print_area, bool is_detailed);
    void print_report_clinical_pressures(TPrinter *print_ptr, TRect *print_area);

public:		// User declarations
    TDateTime FMeasDateTime;
    void report_display_signal(void);
    void report_display_study(void);
    void report_display_average_pulse(void);
    void report_display_ed(void);
    void report_display_t1(void);
    void report_display_t2(void);
    void report_display_central_params(void);
    void report_display_normals_ed(void);
    void report_display_normals_sevr(void);
    void report_display_normals_augidx(void);
    void report_display_normals_aphr75(void);
    void report_display_normals_sp(void);
    void report_display_normals_pp(void);
    void report_display_clinical_normals(void);
    void report_display_avi(void);
    int report_determine_ap_relative_index(float ap, UCOUNT age, PWA_MEASURE_TYPE  MeasureType);
    int report_determine_aixhr75_relative_index(float aixhr75, UCOUNT age, PWA_MEASURE_TYPE  MeasureType);
    int report_determine_sevr_relative_index(float sevr, float hr, UCOUNT age, PWA_MEASURE_TYPE  MeasureType);
    int report_determine_ed_relative_index(float ed, float hr, UCOUNT age, PWA_MEASURE_TYPE  MeasureType);
    int report_determine_sp_relative_index(float sp, UCOUNT age, PWA_MEASURE_TYPE  MeasureType);
    int report_determine_pp_relative_index(float pp, UCOUNT age, PWA_MEASURE_TYPE  MeasureType);
    void __fastcall record_changed(TObject *Sender, TField *Field);
    bool report_export_graphic(Graphics::TBitmap* bmp_image, String jpeg_file_name);
    bool report_export_measurement(String filename);
    bool report_export_pdf();
    void report_display_ap(void);
    void __fastcall ShowForm(TObject *Sender, TPWA *pwa,
                             TDataSource *pDataSource);
                             // DBMGR_ID_TYPE pTableID);

    void __fastcall ClearSeries();
    TADOQuery        *report_qry;
    TPWA          *report_pwa;
    MEAS_ID_TYPE  study_mode;
    AnsiString    export_file;
    int           pwm_session_id;
    String        pdf_file;
    __fastcall Tfrm_report_pwa(TComponent* Owner);
};
extern Tfrm_report_pwa *frm_report_pwa;
#endif
