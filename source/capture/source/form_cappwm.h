//---------------------------------------------------------------------------
#ifndef form_cappwmH
#define form_cappwmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Buttons.hpp>
#include <ToolWin.hpp>
#include "TBuffer.h"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class Tfrm_capture_pwm : public TForm
{
__published:	// IDE-managed Components
    TTimer *tmr_capture;
  TPanel *pnl_header;
  TLabel *lbl_capture_prompt;
  TPanel *pnl_main_chart;
  TChart *chrt_pressure;
    TFastLineSeries *srs_periph_pressure;
    TFastLineSeries *srs_central_pressure;
    TPanel *Panel1;
    TPanel *pnl_trend;
    TPanel *pnl_trend_timing;
    TChart *chrt_trend_pressure;
    TFastLineSeries *srs_periph_sp;
    TFastLineSeries *srs_periph_dp;
    TFastLineSeries *srs_central_sp;
    TFastLineSeries *srs_central_dp;
  TChart *ChartHR;
    TFastLineSeries *srs_cardiac_period;
  TChart *ChartSEVR;
    TFastLineSeries *srs_sevr;
  TChart *ChartED;
    TFastLineSeries *srs_ed;
  TChart *ChartAI;
    TFastLineSeries *srs_augx;
  TPanel *pnl_pressures;
  TPanel *pnl_ra;
  TPanel *pnl_ra_pp;
  TPanel *pnl_mp;
  TPanel *pnl_rad;
  TLabel *Label1;
  TLabel *lbl_pdp;
  TLabel *lbl_psp;
  TPanel *pnl_aor;
  TLabel *Label2;
  TLabel *lbl_cdp;
  TLabel *lbl_csp;
  TPanel *pnl_ppp;
  TPanel *pnl_cpp;
  TFastLineSeries *srs_mp;
  TFastLineSeries *srs_periph_pp;
  TFastLineSeries *srs_central_pp;
  TFastLineSeries *srs_central_ap;
  TPanel *pnl_time;
    TEdit *edt_pwa_notes;
    TEdit *edt_uncal_sp;
    TEdit *edt_uncal_mp;
    TEdit *edt_uncal_dp;
    TLabel *lbl_uncal_sp;
    TLabel *lbl_uncal_mp;
    TLabel *lbl_uncal_dp;
    TLabel *lbl_notes;
    TSpeedButton *spdbtn_update_pressures;
   TSpeedButton *bbtn_event_mark;
   TSpeedButton *bbtn_start;
   TSpeedButton *bbtn_ok;
   TSpeedButton *bbtn_stop;
   TSpeedButton *bbtn_snapshot;
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
    void __fastcall tmr_captureTimer(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall pnl_raResize(TObject *Sender);
  void __fastcall pnl_ra_ppResize(TObject *Sender);
    
    
    void __fastcall spdbtn_update_pressuresClick(TObject *Sender);
    void __fastcall edt_pwa_notesKeyPress(TObject *Sender, char &Key);
    void __fastcall edt_uncal_spChange(TObject *Sender);
    void __fastcall edt_uncal_mpChange(TObject *Sender);
    void __fastcall edt_uncal_dpChange(TObject *Sender);
    void __fastcall bbtn_event_markClick(TObject *Sender);
    void __fastcall ChartAIZoom(TObject *Sender);
    void __fastcall ChartAIUndoZoom(TObject *Sender);
    void __fastcall ChartEDZoom(TObject *Sender);
    void __fastcall ChartEDUndoZoom(TObject *Sender);
    void __fastcall ChartSEVRZoom(TObject *Sender);
    void __fastcall ChartSEVRUndoZoom(TObject *Sender);
    void __fastcall ChartHRZoom(TObject *Sender);
    void __fastcall ChartHRUndoZoom(TObject *Sender);
   void __fastcall pnl_headerClick(TObject *Sender);
   void __fastcall chrt_pressureClick(TObject *Sender);
   void __fastcall chrt_trend_pressureClick(TObject *Sender);
   void __fastcall ChartHRClick(TObject *Sender);
   void __fastcall ChartSEVRClick(TObject *Sender);
   void __fastcall ChartEDClick(TObject *Sender);
   void __fastcall ChartAIClick(TObject *Sender);
   void __fastcall pnl_trendResize(TObject *Sender);
   void __fastcall pnl_main_chartResize(TObject *Sender);
   void __fastcall bbtn_startClick(TObject *Sender);
   void __fastcall bbtn_okClick(TObject *Sender);
   void __fastcall bbtn_stopClick(TObject *Sender);
   void __fastcall bbtn_snapshotClick(TObject *Sender);
private:	// User declarations
   TBuffer gBuffer;
public:		// User declarations
    String ChartHRTitle;
    String ChartSEVRTitle;
    String ChartEDTitle;
    String ChartAITitle;
    TPWM    *pwm;
    TPWA    *pwa;
    UCOUNT  total_samples;
    UCOUNT  calc_samples;
    UCOUNT  display_resolution;
    UCOUNT  display_reset;
    UCOUNT  display_rescale;
    UCOUNT  display_trend_refresh_rate;
    UCOUNT  report_generation_period;
    COUNT   trend_counter;
    COUNT   calculated_trend_counter;
    COUNT   last_report_time;
    bool    pwm_trend_autoscale;
    int     display_counter;
    TDateTime   initial_time;
    TDateTime   real_time;
    int         count;

    __fastcall Tfrm_capture_pwm(TComponent* Owner);
    bool __fastcall simulate_start(void);
    void __fastcall simulate_stop(void);
    bool __fastcall create_pwm_report(void);
    void __fastcall simulate_data(void);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_capture_pwm *frm_capture_pwm;
//---------------------------------------------------------------------------
#endif
