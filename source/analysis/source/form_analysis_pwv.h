//---------------------------------------------------------------------------
#ifndef form_analysis_pwvH
#define form_analysis_pwvH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include "TeeSurfa.hpp"
#include <Series.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include "ErrorBar.hpp"
#include <ImgList.hpp>
#include <scor\child.h>

class Tfrm_analysis_pwv : public Child_Form
{
__published:	// IDE-managed Components
  TPanel *pnl_separate;
  TPanel *pnl_time;
  TChart *chrt_pwv;
  TLineSeries *srs_pwv_line;
  TErrorBarSeries *srs_pwv_bar;
  TChart *chrt_hrate;
  TLineSeries *srs_hrate_a;
  TLineSeries *srs_hrate_b;
   TPanel *Panel1;
   TLabel *lbl_pat_title;
   TLabel *lbl_pat;
   TPanel *pnl_buttons;
   TChart *chrt_delta;
   TErrorSeries *srs_delta_error_a;
   TErrorSeries *srs_delta_error_b;
   TErrorSeries *srs_delta_error;
   TLineSeries *srs_delta_line_a;
   TLineSeries *srs_delta_line_b;
   TLineSeries *srs_delta;
   TChart *chrt_dist;
   TLineSeries *srs_dist_line;
   TSpeedButton *bbtn_export;
   TSpeedButton *bbtn_select;
   TSpeedButton *bbtn_print;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall chrt_pwvMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall chrt_pwvGetAxisLabel(TChartAxis *Sender,
          TChartSeries *Series, int ValueIndex, AnsiString &LabelText);
  void __fastcall pnl_separateResize(TObject *Sender);
  void __fastcall chrt_hrateMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall chrt_hrateClickSeries(TCustomChart *Sender,
          TChartSeries *Series, int ValueIndex, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall srs_hrate_aGetMarkText(TChartSeries *Sender,
          int ValueIndex, AnsiString &MarkText);
   void __fastcall bbtn_printClick(TObject *Sender);
   void __fastcall bbtn_selectClick(TObject *Sender);
   void __fastcall bbtn_exportClick(TObject *Sender);
private:	// User declarations
  bool   clicked_series;
  long   series_index;
  void __fastcall ClearSeries();
public:		// User declarations
    String Caller; // Who call the form
/*
    String         old_system_id;
    unsigned long  old_patient_number;
    int            old_nof_measurements;
*/
    TStringList *analysis_all_measurements;
    TStringList *analysis_input_measurements;
    TStringList *analysis_selected_measurements;
    TPWV *analysis_pwv;

    String analysis_artery;
    TADOQuery *analysis_qry;

    void __fastcall ShowCharts(TDataSet *qry_wave, TStringList *pList,
                                             const bool is_print);
    __fastcall Tfrm_analysis_pwv(TComponent* Owner);
};
extern Tfrm_analysis_pwv *frm_analysis_pwv;
extern bool analysis_pwv_audit_initialised;
#endif
