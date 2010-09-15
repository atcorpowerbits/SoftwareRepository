//---------------------------------------------------------------------------
#ifndef form_report_pwvH
#define form_report_pwvH
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
#include <TeeFunci.hpp>
#include <meas\pubtype.h>
#include <scor\child.h>

class TPWV;
//---------------------------------------------------------------------------
class Tfrm_report_pwv : public Child_Form
{
__published:	// IDE-managed Components
  TPanel *pnl_form;
  TPanel *pnl_canvas;
  TPanel *pnl_params;
  TPanel *pnl_study_details;
  TLabel *lbl_study_title;
  TLabel *lbl_date;
  TLabel *lbl_time;
  TPanel *pnlAB;
  TPopupMenu *mnuReport;
  TMenuItem *mnuPrint;
  TMenuItem *Delete1;
  TMenuItem *Recalculate1;
    TMenuItem *mnuitm_export1;
  TPanel *pnlB;
  TPanel *pnlBCharts;
  TPanel *pnlBT;
  TPanel *pnlQualTONB;
  TLabel *lblQC_PH_BT;
  TLabel *lblQC_PHV_BT;
  TLabel *lblQC_PLV_BT;
  TLabel *lblQC_BLV_BT;
  TChart *ChartBP;
    TLineSeries *srs_siteb_pressure;
    TPointSeries *srs_siteb_pressure_onsets;
  TPanel *pnlBE;
  TPanel *pnlQualECGB;
  TLabel *lblQC_PH_BE;
  TLabel *lblQC_PHV_BE;
  TLabel *lblQC_PLV_BE;
  TLabel *lblQC_BLV_BE;
  TChart *ChartBE;
    TLineSeries *srs_siteb_ecg;
    TPointSeries *srs_siteb_ecg_onsets;
  TPanel *pnlA;
  TPanel *pnlACharts;
  TPanel *pnlAT;
  TChart *ChartAP;
    TLineSeries *srs_sitea_pressure;
    TPointSeries *srs_sitea_pressure_onsets;
  TPanel *pnlQualTONA;
  TLabel *lblQC_PH_AT;
  TLabel *lblQC_PHV_AT;
  TLabel *lblQC_PLV_AT;
  TLabel *lblQC_BLV_AT;
  TPanel *pnlAE;
  TChart *ChartAE;
    TLineSeries *srs_sitea_ecg;
    TPointSeries *srs_sitea_ecg_onsets;
  TPanel *pnlQualECGA;
  TLabel *lblQC_PH_AE;
  TLabel *lblQC_PHV_AE;
  TLabel *lblQC_PLV_AE;
  TLabel *lblQC_BLV_AE;
  TLabel *lbl_pressure_title;
  TLabel *lblSpDpMp;
   TLabel *lblAlg_title;
  TLabel *lblAlg;
    TPointSeries *srs_sitea_pressure_neg_onsets;
    TPointSeries *srs_sitea_ecg_neg_onsets;
    TPointSeries *srs_siteb_pressure_neg_onsets;
    TPointSeries *srs_siteb_ecg_neg_onsets;
  TLabel *lbl_dist_title;
  TLabel *lbl_dist;
  TChart *ChartDT;
    TPointSeries *srs_deltat;
    TPointSeries *srs_invalid_deltat;
    TPopupMenu *pupmnu_export_pwv;
    TMenuItem *mnuitm_pwv_astext;
    TMenuItem *mnuitm_pwv_asgraphic;
   TPanel *pnl_pwv;
   TStringGrid *grdRes;
   TChart *chrt_pwv_reference;
   TLineSeries *srs_pwv_normal_reference;
   TLineSeries *srs_pwv_upper_reference;
   TLineSeries *srs_pwv_lower_reference;
   TPointSeries *srs_pwv_point_reference;
   TLineSeries *srs_sitea_meandt;
   TLineSeries *srs_siteb_meandt;
   TLabel *lbl_reason_title;
   TLabel *lbl_reason;
   TLabel *lbl_tonometer;
   TLabel *lbl_tonometer_title;
   TMenuItem *mnu_all;
   TPanel *pnl_patient_details;
   TLabel *lbl_patient_title;
   TLabel *lbl_pcode_title;
   TLabel *lbl_pcode;
   TLabel *lbl_add_title;
   TLabel *lbl_address1;
   TLabel *lbl_address2;
   TLabel *lbl_address3;
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
   TPanel *Panel1;
   TLabel *lblPWVSD_title;
   TLabel *lblPWV_title;
   TLabel *lblPWV;
   TLabel *lblPWVSD;
   TPanel *pnl_bottom;
   TPanel *pnl_status_bar;
   TLabel *lbl_message2;
   TLabel *lbl_message1;
   TLabel *lbl_message3;
   TPanel *pnl_report_buttons;
   TSpeedButton *bbtn_audit;
   TSpeedButton *bbtn_createpwa;
   TSpeedButton *bbtn_modify;
   TSpeedButton *bbtn_delete;
   TSpeedButton *bbtn_export;
   TSpeedButton *bbtn_print;
   TLabel *lbl_message4;
  void __fastcall pnlABResize(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormHide(TObject *Sender);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall pnlAChartsResize(TObject *Sender);
  void __fastcall pnlBChartsResize(TObject *Sender);
  void __fastcall grdResDrawCell(TObject *Sender, int Col, int Row,
          TRect &Rect, TGridDrawState State);
    void __fastcall mnuitm_pwv_astextClick(TObject *Sender);
   void __fastcall pnl_paramsResize(TObject *Sender);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall mnu_allClick(TObject *Sender);
   void __fastcall bbtn_printClick(TObject *Sender);
   void __fastcall bbtn_deleteClick(TObject *Sender);
   void __fastcall bbtn_modifyClick(TObject *Sender);
   void __fastcall bbtn_createpwaClick(TObject *Sender);
   void __fastcall bbtn_exportClick(TObject *Sender);
   void __fastcall bbtn_auditClick(TObject *Sender);
    
private:	// User declarations
public:		// User declarations
    void __fastcall record_changed(TObject *Sender, TField  *Field);
    TADOQuery  *report_qry;
    TPWV       *report_pwv;
    String     pdf_file;

    __fastcall Tfrm_report_pwv(TComponent* Owner);
    void print_report_header(TRect *print_area);
    void print_report_footer(TRect *print_area);
    void print_report_patient(TRect *print_area);
    void print_report_study(TPrinter *print_ptr, TRect *print_area);
    void print_report_pwv_params(TPrinter *print_ptr, TRect *print_area);
    void report_display_patient_info(PATIENT_RECORD_TYPE  *pat);
    void report_display_study();
    void report_display_params();
    void report_display_quality();
    void report_display_pwv_normals();
    void ClearSeries();
    void ClearResults();
    void report_display_signal(TChart *ChartP, TChart *ChartE,
                               TChart *ChartDT, TPWVSite* pSite,
                               String pSiteTitle, const int pSampleRate);
    bool report_export_graphic(Graphics::TBitmap* bmp_image, String jpeg_file_name);
    bool report_export_measurement(String filename);
    bool report_export_pdf();
};
extern Tfrm_report_pwv *frm_report_pwv;
#endif
