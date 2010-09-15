//---------------------------------------------------------------------------
#ifndef form_report_pwmH
#define form_report_pwmH
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
#include <TeeFunci.hpp>
#include <ImgList.hpp>
#include <meas\pubtype.h>
#include <scor\child.h>

class TPWM;
//---------------------------------------------------------------------------
class Tfrm_report_pwm : public Child_Form
{
__published:	// IDE-managed Components
  TPanel *pnl_form;
  TPanel *pnl_canvas;
  TPanel *pnl_study_details;
  TLabel *lbl_study_title;
  TLabel *lbl_session_date;
  TPopupMenu *mnuReport;
  TMenuItem *mnuPrint;
  TMenuItem *Delete1;
  TMenuItem *Recalculate1;
  TMenuItem *Export1;
  TLabel *lbl_calibrated_title;
  TLabel *lblSpDpMp;
        TLabel *lbl_calibration_ratio;
        TLabel *lbl_calibration_offset;
        TLabel *lbl_ratio;
        TLabel *lbl_offset;
   TPanel *pnl_grid;
   TPanel *pnl_assessments;
   TLabel *lbl_assessments_title;
   TDBGrid *grd_report;
   TPanel *pnl_study_information;
   TLabel *Label3;
   TLabel *lbl_operator_title;
   TLabel *lbl_operator;
   TLabel *lbl_hwbmi_title;
   TLabel *lbl_hwbmi;
   TLabel *lbl_med_title;
   TLabel *lbl_notes_title;
   TMemo *edt_notes;
   TMemo *edt_med;
   TPanel *pnl_patient_information;
   TLabel *Label5;
   TLabel *lbl_pname;
   TLabel *lbl_pid_title;
   TLabel *lbl_pid;
   TLabel *lbl_birth_date_title;
   TLabel *lbl_age_title;
   TLabel *lbl_sex_title;
   TLabel *lbl_age;
   TLabel *lbl_birth_date;
   TLabel *lbl_sex;
   TPanel *pnl_patient_details;
   TLabel *lbl_patient_title;
   TLabel *lbl_pcode_title;
   TLabel *lbl_pcode;
   TLabel *lbl_add_title;
   TLabel *lbl_address1;
   TLabel *lbl_address2;
   TLabel *lbl_address3;
   TPanel *pnl_bottom;
   TPanel *pnl_report_buttons;
   TPanel *pnl_trend;
   TPanel *pnl_trend_timing;
   TChart *ChartHR;
   TLineSeries *srs_cardiac_period;
   TLineSeries *Series1;
   TAverageTeeFunction *TeeFunction1;
   TChart *ChartSEVR;
   TLineSeries *srs_sevr;
   TChart *ChartED;
   TLineSeries *srs_ed;
   TChart *ChartAI;
   TLineSeries *srs_augx;
   TChart *ChartPressures;
   TLineSeries *srs_periph_sp;
   TLineSeries *srs_periph_dp;
   TLineSeries *srs_central_sp;
   TLineSeries *srs_central_dp;
   TLineSeries *srs_mp;
   TLineSeries *srs_central_ap;
   TLineSeries *srs_periph_pp;
   TLineSeries *srs_central_pp;
   TPointSeries *ptsrs_event_marker;
   TPanel *pnl_event_comment;
   TSpeedButton *spbtn_reject_comments;
   TSpeedButton *spbtn_accept_comments;
   TEdit *edt_event_comment;
   TSpeedButton *bbtn_delete;
   TSpeedButton *bbtn_export;
   TSpeedButton *bbtn_print;
   TSpeedButton *bbtn_report;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormHide(TObject *Sender);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall ChartPressuresZoom(TObject *Sender);
  void __fastcall ChartPressuresUndoZoom(TObject *Sender);
        void __fastcall spbtn_reject_commentsClick(TObject *Sender);
        void __fastcall spbtn_accept_commentsClick(TObject *Sender);
        void __fastcall ptsrs_event_markerClick(TChartSeries *Sender,
          int ValueIndex, TMouseButton Button, TShiftState Shift, int X,
          int Y);
        void __fastcall ptsrs_event_markerGetMarkText(TChartSeries *Sender,
          int ValueIndex, AnsiString &MarkText);
        void __fastcall ptsrs_event_markerDblClick(TChartSeries *Sender,
          int ValueIndex, TMouseButton Button, TShiftState Shift, int X,
          int Y);
        void __fastcall ChartPressuresMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall pnl_trendResize(TObject *Sender);
   void __fastcall bbtn_printClick(TObject *Sender);
   void __fastcall bbtn_deleteClick(TObject *Sender);
   void __fastcall bbtn_exportClick(TObject *Sender);
   void __fastcall bbtn_reportClick(TObject *Sender);
    
private:	// User declarations
  int FRecNo;
  //---------------------------------------------------------------------------
  bool SetChart(TChart *pChart, const String pTitle, TDataSet *pTrendTable);
public:		// User declarations
    String ChartHRTitle;
    String ChartSEVRTitle;
    String ChartEDTitle;
    String ChartAITitle;

    void __fastcall record_changed(TObject *Sender, TField  *Field);
    TADOQuery   *report_qry;
    TPWM     *pwm;
    __fastcall Tfrm_report_pwm(TComponent* Owner);
    void print_report_header(TRect *print_area);
    void print_report_footer(TRect *print_area);
    void print_report_patient(TRect *print_area);
    void print_report_session(TPrinter *print_ptr, TRect *print_area);
    void report_display_patient_info(PATIENT_RECORD_TYPE  *pat);
    void report_display_trends();
    void report_display_study();
    // void report_display_average_pulse(void);
    void ClearSeries();
    void __fastcall CalcMeanAndDev(TChartSeries* pSeries, float &av, float &dev,
                                   float coeff = 1., bool yValue = true);
};
extern Tfrm_report_pwm *frm_report_pwm;
#endif
