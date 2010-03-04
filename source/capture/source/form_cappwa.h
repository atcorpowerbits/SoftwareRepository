//---------------------------------------------------------------------------
#ifndef form_cappwaH
#define form_cappwaH
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
#include <ImgList.hpp>

#include <inc/std.h>
#include <meas/pubserv.h>
#include <TBuffer.h>
//---------------------------------------------------------------------------
class Tfrm_capture_pwa : public TForm
{
__published:	// IDE-managed Components
    TChart *chrt_main;
    TFastLineSeries *srs_capture_main;
    TTimer *tmr_capture;
    TPanel *pnl_bottom;
    TChart *chrt_secondary;
    TFastLineSeries *srs_capture_secondary;
    TPanel *pnl_stats;
    TLabel *lbl_capture_time;
    TLabel *lbl_title_capture;
    TLabel *lbl_level_title;
    TLabel *lbl_level;
    TPanel *pnl_header;
   TLabel *lbl_data_mode;
   TLabel *lbl_capture_prompt;
   TFastLineSeries *srs_rtof_upper;
   TFastLineSeries *srs_rtof_lower;
   TFastLineSeries *srs_rtof_height;
   TSpeedButton *bbtn_ok;
   TSpeedButton *bbtn_cancel;
   TPanel *pnl_rtof;
   TLabel *lbl_baseline_variation;
   TLabel *lbl_pulse_height_variation;
   TLabel *lbl_pulse_height;
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
    void __fastcall tmr_captureTimer(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
   void __fastcall FormResize(TObject *Sender);
   void __fastcall bbtn_okClick(TObject *Sender);
   void __fastcall bbtn_cancelClick(TObject *Sender);
private:	// User declarations
   TBuffer gBuffer;
public:		// User declarations
   TPWA   *pwa;
   UCOUNT  total_samples;
   UCOUNT  calc_samples;
   UCOUNT  display_resolution;
   UCOUNT  display_reset;
   
    __fastcall Tfrm_capture_pwa(TComponent* Owner);
    bool __fastcall simulate_start(void);
    void __fastcall simulate_stop(void);
    void __fastcall simulate_data(void);
};

//---------------------------------------------------------------------------
extern PACKAGE Tfrm_capture_pwa *frm_capture_pwa;
//---------------------------------------------------------------------------
#endif
