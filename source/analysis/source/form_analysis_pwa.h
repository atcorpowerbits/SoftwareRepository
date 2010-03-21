//---------------------------------------------------------------------------
#ifndef form_analysis_pwaH
#define form_analysis_pwaH
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
#include <Graphics.hpp>
#include <ImgList.hpp>
#include <scor\child.h>

class Tfrm_analysis_pwa : public Child_Form
{
__published:	// IDE-managed Components
  TPanel *pnl_header;
  TPanel *pnl_footer;
  TLabel *lbl_periph_data;
  TLabel *lbl_central_data;
  TPanel *pnl_separate;
  TLabel *lbl_pat_title;
  TLabel *lbl_art;
  TLabel *lbl_pat;
  TChart *chrt_periph;
  TChart *chrt_central;
   TPanel *pnl_buttons;
   TPanel *Panel2;
   TPanel *Panel3;
   TLabel *lbl_first_last_waveform;
   TPanel *pnl_centre;
   TLabel *lbl_last;
   TLabel *lbl_first;
   TPanel *Panel1;
   TImage *Image1;
   TSpeedButton *bbtn_select;
   TSpeedButton *bbtn_print;
   TSpeedButton *bbtn_trend;
   TSpeedButton *bbtn_export;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall chrt_periphMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall pnl_separateResize(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
   void __fastcall bbtn_printClick(TObject *Sender);
   void __fastcall bbtn_trendClick(TObject *Sender);
   void __fastcall bbtn_selectClick(TObject *Sender);
   void __fastcall bbtn_exportClick(TObject *Sender);
private:	// User declarations
  void __fastcall ClearSeries();
public:		// User declarations
    String Caller; // Who call the form
/*
    String         old_system_id;
    unsigned long  old_patient_number;
    int old_nof_measurements;
*/
    TStringList *analysis_all_measurements;
    TStringList *analysis_input_measurements;
    TStringList *analysis_selected_measurements;
    TPWA *analysis_pwa;

    String analysis_artery;
    TADOQuery *analysis_qry;

    void __fastcall ShowCharts(TDataSet *qry_wave, TStringList *pList);
    __fastcall Tfrm_analysis_pwa(TComponent* Owner);
};
extern Tfrm_analysis_pwa *frm_analysis_pwa;
extern bool analysis_pwa_audit_initialised;
#endif
