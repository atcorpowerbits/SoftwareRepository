//---------------------------------------------------------------------------
#ifndef form_cappwvH
#define form_cappwvH
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
class Tfrm_capture_pwv : public TForm
{
__published:	// IDE-managed Components
    TTimer *tmr_capture;
    TPanel *pnl_bottom;
    TChart *chrt_secondary;
    TFastLineSeries *srs_pressure_secondary;
    TFastLineSeries *srs_ecg_secondary;
    TPanel *pnl_stats;
    TLabel *lbl_capture_time;
    TLabel *lbl_title_capture;
    TLabel *lbl_level_title;
    TLabel *lbl_level;
  TPanel *pnl_main_chart;
  TChart *chrt_pressure;
  TFastLineSeries *srs_pressure_main;
    TLabel *lbl_level_title_ecg;
    TLabel *lbl_level_ecg;
   TChart *chrt_ecg;
   TFastLineSeries *srs_ecg_main;
   TPanel *pnl_header;
   TLabel *lbl_data_mode;
   TLabel *lbl_capture_prompt;
   TSpeedButton *bbtn_ok;
   TSpeedButton *bbtn_cancel;
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
    void __fastcall tmr_captureTimer(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall tbtn_OKClick(TObject *Sender);
    void __fastcall tbtn_CancelClick(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
   void __fastcall FormResize(TObject *Sender);
   void __fastcall pnl_main_chartResize(TObject *Sender);
   void __fastcall bbtn_okClick(TObject *Sender);
   void __fastcall bbtn_cancelClick(TObject *Sender);
private:	// User declarations
   TBuffer gBuffer;
public:		// User declarations
    bool    sitea;
    TPWV    *pwv;
    UCOUNT  total_samples;
    UCOUNT  calc_samples;
    UCOUNT  display_resolution;
    UCOUNT  display_reset;
    UCOUNT  display_rescale;
    bool    pwv_comms_started;

    __fastcall Tfrm_capture_pwv(TComponent* Owner, bool is_sitea);
    bool __fastcall simulate_start(void);
    void __fastcall simulate_stop(void);
    void __fastcall simulate_data(void);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_capture_pwv *frm_capture_pwv;
//---------------------------------------------------------------------------
#endif
