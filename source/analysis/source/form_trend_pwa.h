#ifndef form_trend_pwaH
#define form_trend_pwaH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <scor\child.h>

class Tfrm_trend_pwa : public Child_Form
{
__published:	// IDE-managed Components
  TPanel *pnl_header;
  TPanel *pnl_pressure;
  TPanel *pnl_time;
  TPanel *pnl_tool;
  TChart *chrt_hrate_pressure;
  TBarSeries *srs_phrate_bar;
  TLineSeries *srs_phrate_line;
  TChart *chrt_hrate_timing;
  TBarSeries *srs_thrate_bar;
  TLineSeries *srs_thrate_line;
    TChart *chrt_aix_norm;
   TBarSeries *srs_taix_norm_bar;
   TLineSeries *srs_taix_norm_line;
  TChart *chrt_svr;
  TBarSeries *srs_tsvr_bar;
  TLineSeries *srs_tsvr_line;
   TChart *chrt_ap;
   TBarSeries *srs_tap_bar;
   TLineSeries *srs_tap_line;
  TChart *chrt_edpc;
  TBarSeries *srs_tedpc_bar;
  TLineSeries *srs_tedpc_line;
  TLabel *lbl_pat_title;
  TLabel *lbl_pat;
  TChart *chrt_pressure;
  TLineSeries *Systolic;
  TLineSeries *Diastolic;
  TLineSeries *Mean;
  TLineSeries *Pulse;
  TLineSeries *Augmentation;
  TLabel *lbl_art;
    TLineSeries *srs_p_systolic;
    TLineSeries *srs_p_diastolic;
    TLabel *lbl_first_last_trend;
   TChart *chrt_aix;
   TBarSeries *srs_taix_bar;
   TLineSeries *srs_taix_line;
   TPanel *pnl_buttons;
   TSpeedButton *bbtn_print;
   TSpeedButton *bbtn_wave;
   TSpeedButton *bbtn_export;
  void __fastcall FormResize(TObject *Sender);
  void __fastcall pnl_pressureResize(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall chrt_hrate_pressureMouseDown(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall chrt_hrate_pressureMouseUp(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall chrt_hrate_pressureClickSeries(TCustomChart *Sender,
        TChartSeries *Series, int ValueIndex, TMouseButton Button,
        TShiftState Shift, int X, int Y);
  void __fastcall srs_phrate_barGetMarkText(TChartSeries *Sender,
        int ValueIndex, AnsiString &MarkText);
  void __fastcall chrt_hrate_timingMouseDown(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall chrt_hrate_timingMouseUp(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall chrt_hrate_timingClickSeries(TCustomChart *Sender,
        TChartSeries *Series, int ValueIndex, TMouseButton Button,
        TShiftState Shift, int X, int Y);
  void __fastcall srs_thrate_barGetMarkText(TChartSeries *Sender,
        int ValueIndex, AnsiString &MarkText);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
   void __fastcall bbtn_printClick(TObject *Sender);
   void __fastcall bbtn_waveClick(TObject *Sender);
   void __fastcall bbtn_exportClick(TObject *Sender);
private:	// User declarations
  void __fastcall ClearSeries();
public:		// User declarations
  bool   clicked_series;
  long   series_index;
  bool   trend_show_corresponding;
  UCOUNT report_age;
  __fastcall Tfrm_trend_pwa(TComponent* Owner);
  void __fastcall ShowCharts(TStringList *pList, bool is_print);
};
extern Tfrm_trend_pwa *frm_trend_pwa;

#endif
