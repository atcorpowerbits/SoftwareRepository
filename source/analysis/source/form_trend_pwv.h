#ifndef form_trend_pwvH
#define form_trend_pwvH

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
#include "ErrorBar.hpp"
#include <ImgList.hpp>
#include <scor\child.h>

class Tfrm_trend_pwv : public Child_Form
{
__published:	// IDE-managed Components
  TPanel *pnl_middle;
  TChart *chrt_dist;
  TLineSeries *srs_dist_line;
  TChart *chrt_delta;
  TLineSeries *srs_delta_line_a;
  TLineSeries *srs_delta_line_b;
  TChart *chrt_hrate;
  TLineSeries *srs_hrate_a;
  TLineSeries *srs_hrate_b;
  TErrorSeries *srs_delta_error_a;
  TErrorSeries *srs_delta_error_b;
  TLineSeries *srs_delta;
  TErrorSeries *srs_delta_error;
   TPanel *Panel1;
   TLabel *lbl_pat_title;
   TLabel *lbl_pat;
   TPanel *pnl_buttons;
   TBitBtn *bbtn_print;
   TBitBtn *bbtn_wave;
   TBitBtn *bbtn_export;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);

  void __fastcall pnl_middleResize(TObject *Sender);
  void __fastcall chrt_distGetAxisLabel(TChartAxis *Sender,
          TChartSeries *Series, int ValueIndex, AnsiString &LabelText);
  void __fastcall chrt_hrateMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall chrt_hrateMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall chrt_hrateClickSeries(TCustomChart *Sender,
          TChartSeries *Series, int ValueIndex, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall srs_hrate_aGetMarkText(TChartSeries *Sender,
          int ValueIndex, AnsiString &MarkText);
   void __fastcall bbtn_printClick(TObject *Sender);
   void __fastcall bbtn_waveClick(TObject *Sender);
   void __fastcall bbtn_exportClick(TObject *Sender);
private:	// User declarations
    void __fastcall ClearSeries();
public:		// User declarations
  bool   clicked_series;
  long   series_index;
   __fastcall Tfrm_trend_pwv(TComponent* Owner);
   void __fastcall ShowCharts(TStringList *pList, bool is_print);
};
extern Tfrm_trend_pwv *frm_trend_pwv;

#endif
