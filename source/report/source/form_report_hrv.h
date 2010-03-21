//---------------------------------------------------------------------------

#ifndef form_report_hrvH
#define form_report_hrvH
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
#include "StatChar.hpp"
#include <ComCtrls.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ToolWin.hpp>
#include "fourier.hpp"
#include <ImgList.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <scor\child.h>
#include <meas\source\hrvclass.h>
#include <meas\source\hrvtime.h>
#include <meas\source\HRVfrequency.h>

//---------------------------------------------------------------------------
class Tfrm_report_hrv : public Child_Form
{
__published:	// IDE-managed Components
        TPanel *pnl_form;
   TPopupMenu *ppmnu_report;
   TMenuItem *mnu_text;
   TMenuItem *mnu_graphic;
   TMenuItem *mnu_all;
   TPanel *pnl_grid;
   TPanel *pnl_assessments;
   TLabel *lbl_assessments_title;
   TDBGrid *grd_report;
   TPanel *pnl_study_information;
   TLabel *Label35;
   TLabel *lbl_operator_title;
   TLabel *lbl_operator;
   TLabel *lbl_hwbmi_title;
   TLabel *lbl_hwbmi;
   TLabel *lbl_med_title;
   TLabel *lbl_notes_title;
   TMemo *edt_notes;
   TMemo *edt_med;
   TPanel *pnl_patient_information;
   TLabel *Label36;
   TLabel *lbl_pname;
   TLabel *lbl_pid_title;
   TLabel *lbl_pid;
   TLabel *lbl_birth_date_title;
   TLabel *lbl_age_title;
   TLabel *lbl_sex_title;
   TLabel *lbl_age;
   TLabel *lbl_birth_date;
   TLabel *lbl_sex;
   TPanel *pnl_main;
   TPageControl *pgctrl_reports;
   TTabSheet *tbsht_time;
   TPanel *pnl_waveform;
   TChart *chrt_time_rtor;
   TLineSeries *srs_rtor;
   TPointSeries *srs_highlow_rtor;
   TChart *chrt_ecg_report;
   TFastLineSeries *srs_ecg;
   TPanel *pnl_analysis;
   TChart *chrt_time_rtor_bar;
   TAreaSeries *srs_histogram;
   TChart *chrt_poincare;
   TPointSeries *srs_poincare;
   TPanel *pnl_key_params;
   TPanel *pnl_hr_title;
   TPanel *pnl_hr;
   TPanel *pnl_rmssdd_title;
   TPanel *pnl_rmssdd;
   TPanel *pnl_hrv_index_title;
   TPanel *pnl_hrv_index;
   TPanel *pnl_pnn50_title;
   TPanel *pnl_pnn50;
   TPanel *pnl_bottom;
   TPanel *pnl_parameters;
   TPanel *pnl_title;
   TLabel *lbl_hrv_time_params;
   TPanel *pnl_left;
   TLabel *Label2;
   TLabel *lbl_rtor_range;
   TLabel *Label5;
   TLabel *Label7;
   TLabel *lbl_max;
   TLabel *lbl_min;
   TLabel *Label10;
   TLabel *lbl_maxmin;
   TPanel *pnl_middle_left;
   TLabel *Label3;
   TLabel *lbl_pulses;
   TLabel *Label8;
   TLabel *lbl_cap_time;
   TLabel *Label12;
   TLabel *lbl_high_low;
   TLabel *Label20;
   TLabel *lbl_mode;
   TPanel *pnl_middle_right;
   TLabel *Label6;
   TLabel *lbl_nn50;
   TLabel *Label13;
   TLabel *lbl_tri_index;
   TLabel *Label4;
   TLabel *lbl_rtor_sd;
   TLabel *Label1;
   TLabel *lbl_rtor_mean;
   TPanel *pnl_right;
   TLabel *Label14;
   TLabel *Label15;
   TLabel *Label16;
   TLabel *lbl_segment_length;
   TLabel *lbl_no_segments;
   TLabel *lbl_sdann;
   TLabel *lbl_sdnn;
   TLabel *Label11;
   TLabel *Label17;
   TTabSheet *tbsht_frequency;
   TPanel *pnl_fcharts;
   TChart *chrt_freq_spectrum;
   TAreaSeries *srs_spectrum;
   TChart *chrt_lfhf_pie;
   TPieSeries *srs_frequency_per;
   TPanel *pnl_freq_params;
   TLabel *lbl_lf_mx_freq_title;
   TLabel *lbl_lf_mx_freq;
   TLabel *lbl_hf_mx_freq_title;
   TLabel *lbl_hf_mx_freq;
   TLabel *lbl_lf_hf_ratio_title;
   TLabel *lbl_lf_hf_ratio;
   TLabel *lbl_lf_pnorm;
   TLabel *lbl_hf_pnorm;
   TLabel *lbl_lf_pnorm_title;
   TLabel *lbl_hf_pnorm_title;
   TLabel *lbl_freq_total_power_title;
   TLabel *lbl_freq_total_power;
   TLabel *lbl_lf_power;
   TLabel *lbl_hf_power;
   TLabel *lbl_lf_power_title;
   TLabel *lbl_hf_power_title;
   TTabSheet *tbsht_clinical;
   TPanel *pnl_clinical_graphs;
   TChart *chrt_vagal_index;
   TAreaSeries *srs_area_vagal_index;
   TPointSeries *srs_point_vagal_index;
   TPanel *pnl_patient_details;
   TLabel *lbl_patient_title;
   TLabel *lbl_pcode_title;
   TLabel *lbl_pcode;
   TLabel *lbl_add_title;
   TLabel *lbl_address1;
   TLabel *lbl_address2;
   TLabel *lbl_address3;
   TPanel *pnl_study_details;
   TLabel *lbl_study_title;
   TLabel *lbl_date;
   TLabel *lbl_time;
   TLabel *lbl_pressure_title;
   TLabel *lblSpDpMp;
   TTabSheet *tbsht_manoeuvre;
   TPanel *pnl_manoeuvre_bottom;
   TPanel *pnl_manoeuvre;
   TLabel *lbl_low_title;
   TLabel *lbl_low_manoeuvre;
   TLabel *lbl_high_title;
   TLabel *lbl_high_manoeuvre;
   TLabel *lbl_ratio_title;
   TLabel *lbl_ratio_manoeuvre;
   TLabel *Label24;
   TLabel *lbl_pulses_manoeuvre;
   TLabel *Label26;
   TLabel *lbl_cap_time_manoeuvre;
   TLabel *Label9;
   TLabel *lbl_hr_manoeuvre;
   TLabel *Label19;
   TLabel *Label21;
   TLabel *lbl_rtor_mean_manoeuvre;
   TLabel *lbl_rtor_range_manoeuvre;
   TChart *chrt_manoeuvre_normals;
   TAreaSeries *srs_manoeuvre_ratio_normals;
   TPointSeries *srs_manoeuvre_ratio;
   TPanel *pnl_manoeuvre_waveform;
   TChart *chrt_manoeuvre;
   TLineSeries *srs_hr_manoeuvre;
   TPointSeries *srs_manoeuvre_highlow;
   TChart *chrt_manoeuvre_ecg;
   TFastLineSeries *srs_manoeuvre_ecg;
   TPanel *pnl_status_bar;
   TLabel *lbl_message2;
   TLabel *lbl_message1;
   TLabel *lbl_message3;
   TPanel *pnl_report_buttons;
   TPanel *pnl_patient_manoeuvre;
   TLabel *lbl_patient_title_manoeuvre;
   TLabel *lbl_pcode_title_manoeuvre;
   TLabel *lbl_pcode_manoeuvre;
   TLabel *lbl_add_title_manoeuvre;
   TLabel *lbl_address1_manoeuvre;
   TLabel *lbl_address2_manoeuvre;
   TLabel *lbl_address3_manoeuvre;
   TPanel *pnl_study_manoeuvre;
   TLabel *lbl_study_title_manoeuvre;
   TLabel *lbl_date_manoeuvre;
   TLabel *lbl_time_manoeuvre;
   TLabel *lbl_pressure_title_manoeuvre;
   TLabel *lblSpDpMp_manoeuvre;
   TSpeedButton *bbtn_ecg;
   TSpeedButton *bbtn_modify;
   TSpeedButton *bbtn_delete;
   TSpeedButton *bbtn_export;
   TSpeedButton *bbtn_print;
   TLabel *lbl_message4;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
   void __fastcall tbsht_timeResize(TObject *Sender);
   void __fastcall mnu_graphicClick(TObject *Sender);
   void __fastcall mnu_textClick(TObject *Sender);
   void __fastcall srs_hr_manoeuvreGetMarkText(TChartSeries *Sender,
          int ValueIndex, AnsiString &MarkText);
   void __fastcall srs_hr_manoeuvreBeforeDrawValues(TObject *Sender);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall mnu_allClick(TObject *Sender);
   void __fastcall pnl_fchartsResize(TObject *Sender);
   void __fastcall bbtn_printClick(TObject *Sender);
   void __fastcall bbtn_deleteClick(TObject *Sender);
   void __fastcall bbtn_modifyClick(TObject *Sender);
   void __fastcall bbtn_ecgClick(TObject *Sender);
   void __fastcall pgctrl_reportsChange(TObject *Sender);
   void __fastcall pnl_bottomResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall Tfrm_report_hrv(TComponent* Owner);
        void PlotGraphs();
        void report_display_patient_info(PATIENT_RECORD_TYPE  *pat);
        void report_display_study(void);
        void report_display_params(void);
        void report_display_charts(void);
        void __fastcall record_changed(TObject *Sender, TField  *Field);
        void print_report_study(TPrinter *print_ptr, TRect *print_area);
        void print_report_patient(TRect *print_area);
        void print_report_header(TRect *print_area);
        void print_report_hrv_params(TPrinter *print_ptr, TRect *print_area);
        void print_report_footer(TRect *print_area);
        void print_report_manoeuvre_params(TPrinter *print_ptr, TRect *print_area);
        bool inconclusive_report();
        bool inconclusive_manoeuvre();
        bool report_export_graphic(Graphics::TBitmap* bmp_image, String jpeg_file_name);
        bool report_export_measurement(String filename);
        bool report_export_pdf();

        TADOQuery      *report_qry;
        THRV           *report_hrv;
        THRVTime       *report_hrv_time;
        THRVFrequency  *report_hrv_freq;
        bool           low_after_high;
        int            number_highlow_rtor_graph;
        bool           ecg_is_displayed;
        bool           ecg_manoeuvre;
        String          pdf_file;
};
//---------------------------------------------------------------------------
extern Tfrm_report_hrv *frm_report_hrv;
//---------------------------------------------------------------------------
#endif
