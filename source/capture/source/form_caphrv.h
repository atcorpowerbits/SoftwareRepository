//---------------------------------------------------------------------------

#ifndef form_capture_brsH
#define form_capture_brsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Grids.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <TBuffer.h>
#include <meas/pubserv.h>

//---------------------------------------------------------------------------

class Tfrm_capture_hrv : public TForm
{
__published:	// IDE-managed Components
        TPanel *pnl_control;
        TPanel *pnl_top;
        TImage *img_atcor;
        TPanel *pnl_monitor;
        TChart *chrt_ecg_monitor;
        TFastLineSeries *srs_ecg;
        TPanel *pnl_trend;
        TChart *chrt_btob_trends;
        TPointSeries *srs_event_marker;
        TPointSeries *srs_highlow_rtor;
        TEdit *edtbx_event_comment;
        TPanel *pnl_timing;
        TPanel *pnl_title_timing;
        TLabel *lbl_title_rtor;
        TPanel *pnl_title_mp;
        TLabel *lbl_title_nof_pulses;
        TFastLineSeries *srs_rtor_interval;
        TLabel *lbl_pname_title;
        TLabel *lbl_pname;
        TLabel *lbl_title_time_elapsed;
        TLabel *lbl_title_hr;
   TLabel *lbl_capture_message;
   TLabel *lbl_data_mode;
   TPanel *pnl_mp_pulses;
   TLabel *lbl_nof_pulses;
   TLabel *lbl_time_elapsed;
   TLabel *lbl_heart_rate;
   TLabel *lbl_rtor;
   TSpeedButton *bbtn_stop;
   TSpeedButton *bbtn_calculate;
   TSpeedButton *bbtn_start_session;
   TSpeedButton *bbtn_event_marker;
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormKeyPress(TObject *Sender, char &Key);
        void __fastcall pnl_topClick(TObject *Sender);
        void __fastcall chrt_ecg_monitorClick(TObject *Sender);
        void __fastcall chrt_btob_trendsClick(TObject *Sender);
        void __fastcall pnl_controlClick(TObject *Sender);
   void __fastcall FormResize(TObject *Sender);
   void __fastcall bbtn_stopClick(TObject *Sender);
   void __fastcall bbtn_calculateClick(TObject *Sender);
   void __fastcall bbtn_start_sessionClick(TObject *Sender);
private:	// User declarations
        TBuffer sim_ecg_buffer;

public:		// User declarations
        __fastcall Tfrm_capture_hrv(TComponent* Owner);

         bool __fastcall simulate_start(void);
         void __fastcall simulate_stop(void);
         void __fastcall simulate_data(void);

         THRV           *capture_hrv;
         //THRVTime       *capture_hrvtime;
         unsigned int    display_resolution;
         unsigned int    total_samples;
         bool            first_time;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_capture_hrv *frm_capture_hrv;
//---------------------------------------------------------------------------
#endif
