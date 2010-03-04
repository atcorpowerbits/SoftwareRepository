//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <math.h>

#include <meas/pubserv.h>
#include <dbmgr/pubserv.h>
#include <multdb/pubserv.h>
#include <patient/pubserv.h>
#include <print/pubserv.h>
#include <export/pubserv.h>
#include <report/pubserv.h>
#include <msg/pubserv.h>
#include <config/pubserv.h>
#include <emr/pubserv.h>
#include <scor/form_main.h>
#include <scor/utils.h>
#include "form_report_hrv.h"
#include "attrib.h"
#include "report.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "StatChar"
#pragma link "fourier"
#pragma resource "*.dfm"
Tfrm_report_hrv *frm_report_hrv;

const int REPORT_PANEL_FCHARTS_PRINT_HEIGHT = 168;//259;
const int REPORT_PANEL_FCHARTS_PRINT_WIDTH = 628;
const int REPORT_PANEL_WAVEFORM_PRINT_HEIGHT = 168;
const int REPORT_PANEL_WAVEFORM_PRINT_WIDTH = 628;
const int REPORT_CHART_MANOEUVRE_PRINT_HEIGHT = 169;
const int REPORT_CHART_MANOEUVRE_PRINT_WIDTH =  628;
const int REPORT_HRV_BUFFER = 200;
const int REPORT_PARAMS_PANEL_WIDTH = 130;
bool hrv_first_time = true;
bool hrv_from_manoeuvre = false;

//---------------------------------------------------------------------------
__fastcall Tfrm_report_hrv::Tfrm_report_hrv(TComponent* Owner)
           : Child_Form(Owner)
{
   report_age = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_hrv::FormShow(TObject *Sender)
{
   TDataSource          *dsrc_report;
   PATIENT_RECORD_TYPE  pat;

   report_hrv = meas_get_current_hrv();
   report_hrv_time = meas_get_current_hrvtime();
   report_hrv_freq = meas_get_current_hrvfreq();

   // Display the time tabsheet first
   if (hrv_first_time)
   {
      if (pgctrl_reports != NULL)
      {
         pgctrl_reports->ActivePage = tbsht_time;
      }
      hrv_first_time = false;
   }

   report_age = 0;
   if (patient_get(&pat))
   {
      dsrc_report = dbmgr_get_data_source(DBMGR_MEASURE_HRV_QUERY, false);
      dsrc_report->AutoEdit = false;

      report_qry = dbmgr_setup_query(DBMGR_MEASURE_HRV_TABLE,
                                     DBMGR_QUERY_KEY,
                                     PATIENT_SYSTEM_ID,
                                     PATIENT_STUDY_ID,
                                     PATIENT_NO,
                                     pat.system_id,
                                     pat.study_id,
                                     IntToStr(pat.number),
                                     MPW_DATETIME);
      if ((report_qry != NULL) && report_qry->RecordCount > 0)
      {
         patient_update_measurement_count((COUNT)(report_qry->RecordCount));
         grd_report->DataSource = dsrc_report;
         //nvg_report->DataSource = dsrc_report;

         report_display_patient_info(&pat);

         dsrc_report->OnDataChange = record_changed;
         report_qry->Last();
         grd_report->SetFocus();
      }
      else
      {
         MsgBox(MSG_NO_REPORTS_TO_DISPLAY, SNOTIFICATION, MB_ICONINFORMATION);
      }
   }
   bbtn_print->Enabled = print_does_printer_exist();

   // PM V9
   // If the EMR patient is active or default EMR mode is set - show the
   // Export All button
   // Make sure this is at the end of Show Form as this may shutdown the
   // software, if specified by the EMR object
   if (emr_patient_is_active() || emr_get_default_mode())
   {
      mnu_all->Visible = true;

      // If report export is enabled, perform an Export All and disable report export
      if (emr_get_report_export())
      {
         mnu_allClick(Sender);
         emr_set_report_export(false);
      }
   }
   else
   {
      mnu_all->Visible = false;
   }

   pdf_file = "";      
}

void __fastcall Tfrm_report_hrv::record_changed(TObject *Sender, TField  *Field)
{
  if (report_qry != NULL)
  {
    if (report_qry->RecordCount > 0)
    {
       if (report_hrv->Populate(report_qry) == true)
       {
          switch (report_hrv->MeasureType)
          {
            case HRV_NORMAL:
               tbsht_time->TabVisible = true;
               tbsht_frequency->TabVisible = true;
               tbsht_clinical->TabVisible = true;
               tbsht_manoeuvre->TabVisible = false;
               break;

            case HRV_VALSALVA:
               tbsht_time->TabVisible = false;
               tbsht_frequency->TabVisible = false;
               tbsht_clinical->TabVisible = false;
               tbsht_manoeuvre->TabVisible = true;
               tbsht_manoeuvre->Caption = "Valsalva";
               chrt_manoeuvre->Title->Text->Strings[0] = "Valsalva Manoeuvre";
               hrv_from_manoeuvre = true;
               break;

            case HRV_STAND:
               tbsht_time->TabVisible = false;
               tbsht_frequency->TabVisible = false;
               tbsht_clinical->TabVisible = false;
               tbsht_manoeuvre->TabVisible = true;
               tbsht_manoeuvre->Caption = "Stand";
               chrt_manoeuvre->Title->Text->Strings[0] = "Stand Manoeuvre";
               hrv_from_manoeuvre = true;
               break;
          }
          // Display new data after hiding the previous tabsheet(s)
          lbl_assessments_title->Caption = " Assessment "
                                                      + IntToStr(report_qry->RecNo) + " of "
                                                      + IntToStr(report_qry->RecordCount);
          bbtn_print->Enabled = true;
          report_display_study();
          report_display_params();
          report_display_charts();

          // Only make the tabsheet active after the new data has been displayed
          if (hrv_from_manoeuvre && report_hrv->MeasureType == HRV_NORMAL)
          {
            pgctrl_reports->ActivePage = tbsht_time;
            hrv_from_manoeuvre = false;
          }

          if (report_hrv->ecg_signal_length != 0 &&
               (pgctrl_reports->ActivePage == tbsht_time ||
               pgctrl_reports->ActivePage == tbsht_manoeuvre))
          {
            bbtn_ecg->Visible = true;
          }
          else
          {
            bbtn_ecg->Visible = false;
          }
       }
       else
       {
          bbtn_print->Enabled = false;
       }
    }
  }
}

void Tfrm_report_hrv::report_display_patient_info(PATIENT_RECORD_TYPE  *pat)
{
   lbl_pname->Caption = patient_get_name();
   lbl_birth_date->Caption = pat->dob.FormatString(REPORT_PAT_DOB_DATE_FORMAT);
   lbl_sex->Caption = pat->sex;
   lbl_pid->Caption = pat->id;
   lbl_pcode->Caption = pat->code;
   lbl_address1->Caption = pat->street;
   lbl_address2->Caption = pat->suburb + " " + pat->state + " " + pat->pcode;
   lbl_address3->Caption = pat->country;

   lbl_pcode_manoeuvre->Caption = lbl_pcode->Caption;
   lbl_address1_manoeuvre->Caption = lbl_address1->Caption;
   lbl_address2_manoeuvre->Caption = lbl_address2->Caption;
   lbl_address3_manoeuvre->Caption = lbl_address3->Caption;
}

void Tfrm_report_hrv::report_display_study(void)
{
   lbl_date->Caption = report_hrv->DateTime.FormatString(REPORT_PAT_DOB_DATE_FORMAT);
   lbl_time->Caption = report_hrv->DateTime.TimeString();

   edt_med->Text = MsgBox_ReplaceCarriage(report_hrv->Medication.SubString(1, REPORT_MAX_PRINTED_MEMO_LENGTH));
   edt_notes->Text = MsgBox_ReplaceCarriage(report_hrv->Notes.SubString(1, REPORT_MAX_PRINTED_MEMO_LENGTH));
   lbl_operator->Caption = report_hrv->Operator;

   if (report_hrv->Height > 0 && report_hrv->Height != DEFAULT_VALUE &&
       report_hrv->Weight > 0 && report_hrv->Weight != DEFAULT_VALUE &&
       report_hrv->Bmi > 0 && report_hrv->Bmi != DEFAULT_VALUE &&
       config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
     lbl_hwbmi->Caption = RoundIntToStr(report_hrv->Height) + "cm, " +
                                        RoundIntToStr(report_hrv->Weight) + "kg (" +
                                        FormatFloat("0.##", report_hrv->Bmi) + " kg/m²)";
   }
   else if (report_hrv->Height > 0 && report_hrv->Height != DEFAULT_VALUE &&
         config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
      // Set bmi captions and colours
     lbl_hwbmi->Caption = RoundIntToStr(report_hrv->Height) + "cm";
   }
   else if (report_hrv->Weight > 0 && report_hrv->Weight != DEFAULT_VALUE &&
         config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
      // Set bmi captions and colours
     lbl_hwbmi->Caption = RoundIntToStr(report_hrv->Weight) + "kg";
   }
   else if (report_hrv->Feet >= 0 && report_hrv->Feet != DEFAULT_VALUE &&
            report_hrv->Inch >= 0 && report_hrv->Inch != DEFAULT_VALUE &&
            report_hrv->Pound > 0 && report_hrv->Pound != DEFAULT_VALUE &&
            report_hrv->Bmi > 0 && report_hrv->Bmi != DEFAULT_VALUE &&
            config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      // Set bmi captions and colours
     lbl_hwbmi->Caption = RoundIntToStr(report_hrv->Feet) + "ft, " +
                                        RoundIntToStr(report_hrv->Inch) + "in, " +
                                        RoundIntToStr(report_hrv->Pound) + "lb (" +
                                        FormatFloat("0.##", report_hrv->Bmi) + " kg/m²)";
   }
   else if (report_hrv->Feet >= 0 && report_hrv->Feet != DEFAULT_VALUE &&
            report_hrv->Inch >= 0 && report_hrv->Inch != DEFAULT_VALUE &&
            config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      // Set bmi captions and colours
     lbl_hwbmi->Caption = RoundIntToStr(report_hrv->Feet) + "ft, " +
                                        RoundIntToStr(report_hrv->Inch) + "in";
   }
   else if (report_hrv->Pound > 0 && report_hrv->Pound != DEFAULT_VALUE &&
            config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      // Set bmi captions and colours
     lbl_hwbmi->Caption = RoundIntToStr(report_hrv->Pound) + "lb";
   }
   else
   {
     lbl_hwbmi->Caption = "";
   }
   if (report_hrv->Sp > 0 && report_hrv->Sp != DEFAULT_VALUE &&
      report_hrv->Dp > 0 && report_hrv->Dp != DEFAULT_VALUE)
   {
      lblSpDpMp->Caption = RoundIntToStr(report_hrv->Sp) + "/" +
                           RoundIntToStr(report_hrv->Dp) + " (-)";
   }
   else if (report_hrv->MeanP > 0 && report_hrv->MeanP != DEFAULT_VALUE &&
            report_hrv->Dp > 0 && report_hrv->Dp != DEFAULT_VALUE)
   {
      lblSpDpMp->Caption = "-/" + RoundIntToStr(report_hrv->Dp) + " (" +
                           RoundIntToStr(report_hrv->MeanP) + ")";
   }
   else
   {
      lblSpDpMp->Caption = "";
   }

   lbl_date_manoeuvre->Caption = lbl_date->Caption;
   lbl_time_manoeuvre->Caption = lbl_time->Caption;
   lblSpDpMp_manoeuvre->Caption = lblSpDpMp->Caption;

   // Check for inconclusive reports
   // PM V9
   // Display messages on the status bar
   if (inconclusive_report())
   {
      emma_display_statusbar_message("Inconclusive", "", "", sphygmocor_maroon);
   }
   else if (inconclusive_manoeuvre())
   {
      emma_display_statusbar_message("Inconclusive", "", "", sphygmocor_maroon);
   }
   else
   {
      emma_display_statusbar_message("", "", "", sphygmocor_white);
   }

   if (report_hrv->Simulation)
   {
      emma_display_statusbar_message(SIMULATION, SIMULATION_NOTE, sphygmocor_maroon);
   }
   else
   {
      emma_display_statusbar_message("", "", sphygmocor_white);
   }
}

void Tfrm_report_hrv::report_display_params()
{
   Word hour, min, sec, msec;

   report_age = patient_get_age_at_date(report_hrv->DateTime);
   lbl_age->Caption = IntToStr(report_age);
   pnl_hr->Caption = FormatFloat("0", 60000/report_hrv_time->RtoR_mean);
   pnl_pnn50->Caption = FormatFloat("0.0", report_hrv_time->PNN50);
   pnl_rmssdd->Caption = FormatFloat("0.0", report_hrv_time->RMS_SD);
   pnl_hrv_index->Caption = FormatFloat("0.0", report_hrv_time->HRV_index);

   report_hrv->time_elapsed = report_hrv->DateTime - report_hrv->StartTime;
   lbl_cap_time->Caption = FormatDateTime("hh:nn:ss",report_hrv->time_elapsed);
   lbl_pulses->Caption = FormatFloat("0", report_hrv->PulsesInSession);
   lbl_high_low->Caption = FormatFloat("0", report_hrv->number_rejected_rtor_tot);
   lbl_mode->Caption = FormatFloat("0", report_hrv_time->RtoR_mode) + " ms";
   lbl_max->Caption = FormatFloat("0", report_hrv_time->RtoR_max) + " ms";
   lbl_min->Caption = FormatFloat("0", report_hrv_time->RtoR_min) + " ms";
   lbl_maxmin->Caption = FormatFloat("0.00", report_hrv_time->RtoR_max_min);
   lbl_rtor_mean->Caption = FormatFloat("0", report_hrv_time->RtoR_mean) + " ms";
   lbl_rtor_range->Caption = FormatFloat("0", report_hrv_time->RtoR_range) + " ms";
   lbl_rtor_sd->Caption = FormatFloat("0.0", report_hrv_time->RtoR_SD) + " ms";
   lbl_nn50->Caption = FormatFloat("0", report_hrv_time->NN50);
   lbl_tri_index->Caption = FormatFloat("0", report_hrv_time->Triangular_index) + " ms";
   lbl_segment_length->Caption = FormatFloat("0", report_hrv_time->Segment_length) + " min";
   if (report_hrv_time->No_of_segments == 0)
   {
      lbl_no_segments->Caption = "n/c";
      lbl_sdann->Caption = "n/c";
      lbl_sdnn->Caption = "n/c";
   }
   else
   {
      lbl_no_segments->Caption = FormatFloat("0", report_hrv_time->No_of_segments);
      lbl_sdann->Caption = FormatFloat("0.00", report_hrv_time->SDANN) + " ms";
      lbl_sdnn->Caption = FormatFloat("0.0", report_hrv_time->SDNN) + " ms";
   }

   DecodeTime(report_hrv->time_elapsed, hour, min, sec, msec);
   Word time = 60*hour + min;
   if (time >= 3)
   {
      // Only display absolute low and high frequency powers after 3 minutes of data capture
      lbl_lf_power->Caption = FormatFloat("0", report_hrv_freq->LF_Power);
      lbl_hf_power->Caption = FormatFloat("0", report_hrv_freq->HF_Power);
   }
   else
   {
      lbl_lf_power->Caption = "n/c";
      lbl_hf_power->Caption = "n/c";
   }

   lbl_lf_pnorm->Caption = FormatFloat("0.0", report_hrv_freq->LF_Power_normlised);
   lbl_hf_pnorm->Caption = FormatFloat("0.0", report_hrv_freq->HF_Power_normlised);
   lbl_lf_hf_ratio->Caption = FormatFloat("0.00", report_hrv_freq->LF_HF_Ratio);
   lbl_lf_mx_freq->Caption = FormatFloat("0.00", report_hrv_freq->LF_Freq_max);
   lbl_hf_mx_freq->Caption = FormatFloat("0.00", report_hrv_freq->HF_Freq_max);
   lbl_freq_total_power->Caption = FormatFloat("0", report_hrv_freq->TotalPower);

   switch (report_hrv->MeasureType)
   {
      case HRV_NORMAL:
         break;

      case HRV_VALSALVA:
         lbl_high_title->Caption = "Valsalva High";
         lbl_low_title->Caption = "Valsalva Low";
         lbl_ratio_title->Caption = "Valsalva Ratio";
         lbl_high_manoeuvre->Caption = RoundIntToStr(report_hrv_time->Valsalva_high) + " bpm";
         lbl_low_manoeuvre->Caption = RoundIntToStr(report_hrv_time->Valsalva_low) + " bpm";
         lbl_ratio_manoeuvre->Caption = FormatFloat("0.00", report_hrv_time->Valsalva_ratio);
         break;

      case HRV_STAND:
         lbl_high_title->Caption = "Stand High";
         lbl_low_title->Caption = "Stand Low";
         lbl_ratio_title->Caption = "Stand Ratio";
         lbl_high_manoeuvre->Caption = RoundIntToStr(report_hrv_time->Stand_high) + " bpm";
         lbl_low_manoeuvre->Caption = RoundIntToStr(report_hrv_time->Stand_low) + " bpm";
         lbl_ratio_manoeuvre->Caption = FormatFloat("0.00", report_hrv_time->Stand_ratio);
         break;
   }

   lbl_cap_time_manoeuvre->Caption = lbl_cap_time->Caption;
   lbl_pulses_manoeuvre->Caption = lbl_pulses->Caption;
   lbl_hr_manoeuvre->Caption = pnl_hr->Caption + " bpm";
   lbl_rtor_mean_manoeuvre->Caption = lbl_rtor_mean->Caption;
   lbl_rtor_range_manoeuvre->Caption = lbl_rtor_range->Caption;
}

void Tfrm_report_hrv::report_display_charts()
{
   int  start;
   int  end;
   int  rejected;
   double   max_y;
   double   min_y;
   double   temp;

   chrt_time_rtor->UndoZoom();
   chrt_ecg_report->UndoZoom();
   chrt_manoeuvre->UndoZoom();
   chrt_manoeuvre_ecg->UndoZoom();

   chrt_ecg_report->Visible = false;
   pnl_analysis->Visible = true;
   bbtn_ecg->Caption = "Show &ECG";
   ecg_is_displayed = false;
   chrt_manoeuvre_ecg->Visible = false;
   pnl_manoeuvre_bottom->Visible = true;
   ecg_manoeuvre = false;

   // Set the chart limits to 5% above and below the series limits
   // Clip the rejected pulses to these values as well
   max_y = 1.05 * report_hrv_time->RtoR_max;
   min_y = 0.95 * report_hrv_time->RtoR_min;
   chrt_time_rtor->LeftAxis->SetMinMax(min_y, max_y);

   // Display R to R intervals
   srs_rtor->Clear();
   for (int i = 0; i < report_hrv->PulsesInSession; i++)
   {
      if (report_hrv->RtoR_raw[i] > max_y)
      {
         srs_rtor->AddXY(i+1, max_y, "" , srs_rtor->SeriesColor);
      }
      else if (report_hrv->RtoR_raw[i] < min_y)
      {
         srs_rtor->AddXY(i+1, min_y, "" , srs_rtor->SeriesColor);
      }
      else
      {
         srs_rtor->AddXY(i+1, report_hrv->RtoR_raw[i], "" , srs_rtor->SeriesColor);
      }
   }

   // Display rejected pulse markers
   srs_highlow_rtor->Clear();
   for (int i = 0; i < report_hrv->number_rejected_rtor_tot; i++)
   {
      rejected = report_hrv->index_rejected_rtor[i];
      if (report_hrv->RtoR_raw[rejected] > max_y)
      {
         srs_highlow_rtor->AddXY(rejected+1, max_y, "", clTeeColor);
      }
      else
      {
         srs_highlow_rtor->AddXY(rejected+1, min_y, "", clTeeColor);
      }
   }

   // Set the chart limits to 5% above and below the series limits
   // Clip the rejected pulses to these values as well
   temp = max_y;
   max_y = 60*1000/min_y;
   min_y = 60*1000/temp;
   chrt_manoeuvre->LeftAxis->SetMinMax(min_y, max_y);

   // Display manoeuvre heart rate
   srs_hr_manoeuvre->Clear();
   for (int i = 0; i < report_hrv->PulsesInSession; i++)
   {
      if (60*1000/report_hrv->RtoR_raw[i] > max_y)
      {
         srs_hr_manoeuvre->AddXY(report_hrv->Time_raw[i], max_y, "" , srs_hr_manoeuvre->SeriesColor);
      }
      else if (60*1000/report_hrv->RtoR_raw[i] < min_y)
      {
         srs_hr_manoeuvre->AddXY(report_hrv->Time_raw[i], min_y, "" , srs_hr_manoeuvre->SeriesColor);
      }
      else
      {
         srs_hr_manoeuvre->AddXY(report_hrv->Time_raw[i], 60*1000/report_hrv->RtoR_raw[i], "" , srs_hr_manoeuvre->SeriesColor);
      }
   }

   // Display manoeuvre rejected pulse markers
   srs_manoeuvre_highlow->Clear();
   for (int i = 0; i < report_hrv->number_rejected_rtor_tot; i++)
   {
      rejected = report_hrv->index_rejected_rtor[i];
      if (60*1000/report_hrv->RtoR_raw[rejected] > max_y)
      {
         srs_manoeuvre_highlow->AddXY(report_hrv->Time_raw[rejected], max_y, "", clTeeColor);
      }
      else
      {
         srs_manoeuvre_highlow->AddXY(report_hrv->Time_raw[rejected], min_y, "", clTeeColor);
      }
   }

   // Display ECG
   srs_ecg->Clear();
   for (int i = 0; i < report_hrv->ecg_signal_length; i++)
   {
      srs_ecg->AddXY((float)(((float)i+1.0)/(float)HRV_MIN_ECG_SAMPLE_RATE), report_hrv->ecg_signal[i], "" , srs_ecg->SeriesColor);
   }
   max_y = srs_ecg->MaxYValue() + REPORT_HRV_BUFFER;
   min_y = srs_ecg->MinYValue() - REPORT_HRV_BUFFER;
   chrt_ecg_report->LeftAxis->SetMinMax(min_y, max_y);

   // Display Manoeuvre ECG
   srs_manoeuvre_ecg->Clear();
   for (int i = 0; i < report_hrv->ecg_signal_length; i++)
   {
      srs_manoeuvre_ecg->AddXY((float)(((float)i+1.0)/(float)HRV_MIN_ECG_SAMPLE_RATE), report_hrv->ecg_signal[i], "" , srs_manoeuvre_ecg->SeriesColor);
   }
   max_y = srs_manoeuvre_ecg->MaxYValue() + REPORT_HRV_BUFFER;
   min_y = srs_manoeuvre_ecg->MinYValue() - REPORT_HRV_BUFFER;
   chrt_manoeuvre_ecg->LeftAxis->SetMinMax(min_y, max_y);

   // Display histogram
   srs_histogram->Clear();
   start = floor(report_hrv_time->RtoR_min/10);
   end = floor(report_hrv_time->RtoR_max/10);

   // Must go one past the final value to create a downward edge for the final value's column
   for (int i = start; i < end + 2; i++)
   {
      srs_histogram->AddXY(10*i, report_hrv_time->RtoR_histogram[i], "", clTeeColor);
   }

   // Display Poincare plot
   srs_poincare->Clear();
   for (int i = 0; i < report_hrv->PulsesInSession_refined - 1; i++)
   {
      srs_poincare->AddXY(report_hrv->RtoR_raw_refined[i], report_hrv->RtoR_raw_refined[i+1], "", srs_poincare->SeriesColor);
   }

   // Display frequency spectrum
   chrt_freq_spectrum->LeftAxis->SetMinMax(0, report_hrv_freq->Spectrum_Max);
   srs_spectrum->Clear();
   for (int i = 1; i < report_hrv_freq->number_of_points_spectrum; i++)
   {
      if (report_hrv_freq->Frequency[i] >= 0.04 && report_hrv_freq->Frequency[i] < 0.15)
      {
         srs_spectrum->AddXY(report_hrv_freq->Frequency[i], report_hrv_freq->Power_Spectrum[i],"", sphygmocor_navy);
      }
      else if (report_hrv_freq->Frequency[i] >= 0.15 && report_hrv_freq->Frequency[i] < 0.4)
      {
         srs_spectrum->AddXY(report_hrv_freq->Frequency[i], report_hrv_freq->Power_Spectrum[i],"", sphygmocor_black);
      }
      else
      {
         srs_spectrum->AddXY(report_hrv_freq->Frequency[i], report_hrv_freq->Power_Spectrum[i],"", clTeeColor);
      }
   }

   // Display frequency pie chart
   srs_frequency_per->Clear();
   srs_frequency_per->Add(report_hrv_freq->LF_Power_normlised /100, "LF" , sphygmocor_navy);
   srs_frequency_per->Add(report_hrv_freq->HF_Power_normlised / 100, "HF" , sphygmocor_black);

   // Define the normal range for vagal index
   srs_area_vagal_index->Clear();
   srs_area_vagal_index->AddXY(15, 41, "", clTeeColor);
   srs_area_vagal_index->AddXY(25, 41, "", clTeeColor);
   srs_area_vagal_index->AddXY(25, 36, "", clTeeColor);
   srs_area_vagal_index->AddXY(35, 36, "", clTeeColor);
   srs_area_vagal_index->AddXY(35, 25, "", clTeeColor);
   srs_area_vagal_index->AddXY(45, 25, "", clTeeColor);
   srs_area_vagal_index->AddXY(45, 20, "", clTeeColor);
   srs_area_vagal_index->AddXY(55, 20, "", clTeeColor);
   srs_area_vagal_index->AddXY(55, 20, "", clTeeColor);
   srs_area_vagal_index->AddXY(100, 20, "", clTeeColor);

   // Plot the patient's vagal index - clipping out of range values
   srs_point_vagal_index->Clear();
   if (report_hrv_time->RMS_SD > chrt_vagal_index->LeftAxis->Maximum)
   {
      srs_point_vagal_index->AddXY(report_age, chrt_vagal_index->LeftAxis->Maximum, "", clTeeColor);
   }
   else if (report_hrv_time->RMS_SD < chrt_vagal_index->LeftAxis->Minimum)
   {
      srs_point_vagal_index->AddXY(report_age, chrt_vagal_index->LeftAxis->Minimum, "", clTeeColor);
   }
   else
   {
      srs_point_vagal_index->AddXY(report_age, report_hrv_time->RMS_SD, "", clTeeColor);
   }

   // If the capture time is less than the clinical minimum - do not display the normals charts
   TDateTime clinical_min_time = EncodeTime(0, HRV_MIN_CLINICAL_TIME, 0, 0);
   if(report_hrv->DateTime - report_hrv->StartTime < clinical_min_time)
   {
      chrt_vagal_index->Visible = false;
   }
   else
   {
      chrt_vagal_index->Visible = true;
   }

   switch (report_hrv->MeasureType)
   {
      case HRV_NORMAL:
         break;

      case HRV_VALSALVA:
         chrt_manoeuvre_normals->Title->Text->Strings[0] = "Valsalva Ratio Reference Range";
         chrt_manoeuvre_normals->LeftAxis->Title->Caption = "Valsalva Ratio";
         chrt_manoeuvre_normals->LeftAxis->SetMinMax(0, 2);

         // Define the normal range for valsalva ratio
         srs_manoeuvre_ratio_normals->Clear();
         srs_manoeuvre_ratio_normals->AddXY(10, 1.5, "", clTeeColor);
         srs_manoeuvre_ratio_normals->AddXY(40, 1.5, "", clTeeColor);
         srs_manoeuvre_ratio_normals->AddXY(40, 1.45, "", clTeeColor);
         srs_manoeuvre_ratio_normals->AddXY(60, 1.45, "", clTeeColor);
         srs_manoeuvre_ratio_normals->AddXY(60, 1.35, "", clTeeColor);
         srs_manoeuvre_ratio_normals->AddXY(100, 1.35, "", clTeeColor);

         // Plot the patient's valsalva ratio - clipping out of range values
         srs_manoeuvre_ratio->Clear();
         if (report_hrv_time->Valsalva_ratio > chrt_manoeuvre_normals->LeftAxis->Maximum)
         {
            srs_manoeuvre_ratio->AddXY(report_age, chrt_manoeuvre_normals->LeftAxis->Maximum, "", clTeeColor);
         }
         else if (report_hrv_time->Valsalva_ratio < chrt_manoeuvre_normals->LeftAxis->Minimum)
         {
            srs_manoeuvre_ratio->AddXY(report_age, chrt_manoeuvre_normals->LeftAxis->Minimum, "", clTeeColor);
         }
         else
         {
            srs_manoeuvre_ratio->AddXY(report_age, report_hrv_time->Valsalva_ratio, "", clTeeColor);
         }
         break;

      case HRV_STAND:
         chrt_manoeuvre_normals->Title->Text->Strings[0] = "Stand Ratio Reference Range";
         chrt_manoeuvre_normals->LeftAxis->Title->Caption = "Stand Ratio";
         chrt_manoeuvre_normals->LeftAxis->SetMinMax(0, 1.8);

         // Define the normal range for stand ratio
         srs_manoeuvre_ratio_normals->Clear();
         srs_manoeuvre_ratio_normals->AddXY(10, 1.1, "", clTeeColor);
         srs_manoeuvre_ratio_normals->AddXY(100, 1.1, "", clTeeColor);

         // Plot the patient's stand ratio - clipping out of range values
         srs_manoeuvre_ratio->Clear();
         if (report_hrv_time->Stand_ratio > chrt_manoeuvre_normals->LeftAxis->Maximum)
         {
            srs_manoeuvre_ratio->AddXY(report_age, chrt_manoeuvre_normals->LeftAxis->Maximum, "", clTeeColor);
         }
         else if (report_hrv_time->Stand_ratio < chrt_manoeuvre_normals->LeftAxis->Minimum)
         {
            srs_manoeuvre_ratio->AddXY(report_age, chrt_manoeuvre_normals->LeftAxis->Minimum, "", clTeeColor);
         }
         else
         {
            srs_manoeuvre_ratio->AddXY(report_age, report_hrv_time->Stand_ratio, "", clTeeColor);
         }
         break;
   }
}

void Tfrm_report_hrv::print_report_study(TPrinter *print_ptr, TRect *print_area)
{
   int          text_width;
   int          xpos;
   int          ypos;
   int          blood_pressure;
   AnsiString   S;
   TRect        chart_rect;
   TFontStyles  font_style;

   TFontStyles  bold_font;
   bold_font.Clear();
   bold_font << fsBold;

   TFontStyles  normal_font;
   normal_font.Clear();

   font_style << fsBold;
   S = "STUDY DATA";
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 12;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top,
                              S);

   ypos = print_area->Top + print_ptr->Canvas->TextHeight(S);

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 8;


   S = lbl_date->Caption + ", " + lbl_time->Caption + "    ";
   print_ptr->Canvas->TextOut(print_area->Left,
                              ypos,
                              S);

   xpos = print_area->Left + print_ptr->Canvas->TextWidth(S);

   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;

   if (lbl_hwbmi->Caption != "")
   {
      S = lbl_hwbmi_title->Caption + " ";

      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
      xpos = xpos + print_ptr->Canvas->TextWidth(S);

      font_style << fsBold;
      print_ptr->Canvas->Font->Style = font_style;
      S = lbl_hwbmi->Caption + "    ";
      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
      xpos = xpos + print_ptr->Canvas->TextWidth(S);

   }
   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;

   S = "Operator ID: ";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   xpos = print_area->Left;
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);
   xpos = xpos + print_ptr->Canvas->TextWidth(S);

   font_style << fsBold;
   print_ptr->Canvas->Font->Style = font_style;
   S = report_hrv->Operator;
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);

   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;
   S = "Blood Pressure: ";
   xpos = xpos + print_ptr->Canvas->TextWidth(S);
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);

   xpos = xpos + print_ptr->Canvas->TextWidth(S);
   font_style << fsBold;
   print_ptr->Canvas->Font->Style = font_style;
   S = lblSpDpMp->Caption;
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);

   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;
   S = "Medications:    ";
   text_width = print_ptr->Canvas->TextWidth(S);
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(print_area->Left,
                              ypos,
                              S);
   print_ptr->Canvas->TextOut(print_area->Left + text_width,
                              ypos,
                              edt_med->Text);

   S = "Notes: ";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(print_area->Left,
                              ypos,
                              S);
   print_ptr->Canvas->TextOut(print_area->Left + text_width,
                              ypos,
                              edt_notes->Text);
}

void Tfrm_report_hrv::print_report_patient(TRect *print_area)
{
   switch (report_hrv->MeasureType)
   {
      case HRV_NORMAL:
         print_do_patient_data(print_area, report_age, (frm_main->lbl_message1->Caption != ""), "Inconclusive Report", "", report_hrv->Simulation);
         break;

      case HRV_VALSALVA:
      case HRV_STAND:
         print_do_patient_data(print_area, report_age, (frm_main->lbl_message1->Caption != ""), "Inconclusive Report", "", report_hrv->Simulation);
         break;
   }
}

void Tfrm_report_hrv::print_report_header(TRect *print_area)
{
   switch (report_hrv->MeasureType)
   {
      case HRV_NORMAL:
         print_do_header(print_area, "SphygmoCor", "Heart Rate Variability Report");
         break;

      case HRV_VALSALVA:
         print_do_header(print_area, "SphygmoCor", "Valsalva Manoeuvre Report");
         break;

      case HRV_STAND:
         print_do_header(print_area, "SphygmoCor", "Stand Manoeuvre Report");
         break;
   }
}

void Tfrm_report_hrv::print_report_hrv_params(TPrinter *print_ptr, TRect *print_area)
{
   // Prints all time parameters except for hrv mode and triangular index (equivalent to range)
   // Prints all frequency parameters

   int          width;
   int          xpos;
   int          text_width;
   int          text_height;
   int          line_num = 1;
   AnsiString   S;
   TFontStyles  font_style;
   TFontStyles  bold_font;

   bold_font.Clear();
   bold_font << fsBold;

   width = print_area->Right - print_area->Left;
   font_style.Clear();

   font_style << fsBold;
   S = "TIME PARAMETERS";
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 11;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(width / 4 + print_area->Left,
                              print_area->Top,
                              S);

   S = "FREQUENCY PARAMETERS";
   text_width = print_ptr->Canvas->TextWidth(S);
   print_ptr->Canvas->TextOut(print_area->Right - text_width,
                              print_area->Top,
                              S);

   ++line_num;
   font_style.Clear();
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 8;
   print_ptr->Canvas->Font->Style = font_style;

   S = "Number of Pulses    ";
   text_width = print_ptr->Canvas->TextWidth(S);
   text_height = print_ptr->Canvas->TextHeight(S);
   xpos = print_area->Left + text_width;

   S = "Heart Rate ";
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              pnl_hr->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Capture Time ";
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
    print_ptr->Canvas->Font->Style = bold_font;
    print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_cap_time->Caption);
    print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Number of Pulses ";
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_pulses->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Rejected Pulses ";
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_high_low->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "NN50 ";
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
    print_ptr->Canvas->Font->Style = bold_font;
    print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_nn50->Caption);
    print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "PNN50 ";
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              pnl_pnn50->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   line_num = 2;

   S = "Standard Deviation    ";
   text_width = print_ptr->Canvas->TextWidth(S);
   xpos = width / 4 + text_width;

   S = "Mean ";
   print_ptr->Canvas->TextOut(width / 4 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_rtor_mean->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;
   // PM V9
   S = "SDNN ";
   print_ptr->Canvas->TextOut(width / 4 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_rtor_sd->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Range  ";
   print_ptr->Canvas->TextOut(width / 4 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_rtor_range->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Maximum ";
   print_ptr->Canvas->TextOut(width / 4 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_max->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Minimum ";
   print_ptr->Canvas->TextOut(width / 4 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_min->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Max./Min.  ";
   print_ptr->Canvas->TextOut(width / 4 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_maxmin->Caption);
   print_ptr->Canvas->Font->Style = font_style;

   line_num = 2;

   S = "HRV Triangular Index    ";
   text_width = print_ptr->Canvas->TextWidth(S);
   xpos = width / 2 + text_width;

   S = "RMSSD ";
   print_ptr->Canvas->TextOut(width / 2 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              pnl_rmssdd->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   // PM CR
   S = "HRV Triangular Index ";
   print_ptr->Canvas->TextOut(width / 2 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              pnl_hrv_index->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Segment Length ";
   print_ptr->Canvas->TextOut(width / 2 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_segment_length->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "No. of Segments ";
   print_ptr->Canvas->TextOut(width / 2 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_no_segments->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;
   // PM V9
   S = "SDNN Index ";
   print_ptr->Canvas->TextOut(width / 2 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_sdnn->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "SDANN ";
   print_ptr->Canvas->TextOut(width / 2 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_sdann->Caption);
   print_ptr->Canvas->Font->Style = font_style;

   line_num = 2;

   S = "HF Power Normalised    ";
   text_width = print_ptr->Canvas->TextWidth(S);
   xpos = 3 * width / 4 + text_width;

   S = "LF Maximum ";
   print_ptr->Canvas->TextOut(3 * width / 4 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_lf_mx_freq->Caption + " Hz");
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "HF Maximum ";
   print_ptr->Canvas->TextOut(3 * width / 4 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_hf_mx_freq->Caption + " Hz");
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "LF, HF Power Norm ";
   print_ptr->Canvas->TextOut(3 * width / 4 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_lf_pnorm->Caption + ", " + lbl_hf_pnorm->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "LF/HF Ratio  ";
   print_ptr->Canvas->TextOut(3 * width / 4 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_lf_hf_ratio->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "LF, HF Power Abs ";
   print_ptr->Canvas->TextOut(3 * width / 4 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_lf_power->Caption + ", " + lbl_hf_power->Caption + " ms²");
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Total Power  ";
   print_ptr->Canvas->TextOut(3 * width / 4 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),     
                              lbl_freq_total_power->Caption + " ms²");
   print_ptr->Canvas->Font->Style = font_style;
}

void Tfrm_report_hrv::print_report_manoeuvre_params(TPrinter *print_ptr, TRect *print_area)
{
   // Prints capture time, number of pulses, average heart rate, mean R to R and R to R range time parameters
   // Prints all manoeuvre parameters

   int          width;
   int          xpos;
   int          text_width;
   int          text_height;
   int          line_num = 1;
   AnsiString   S;
   AnsiString   Manoeuvre;
   TFontStyles  font_style;
   TFontStyles  bold_font;

   bold_font.Clear();
   bold_font << fsBold;

   width = print_area->Right - print_area->Left;
   font_style.Clear();

   font_style << fsBold;
   switch (report_hrv->MeasureType)
   {
      case HRV_NORMAL:
         return;

      case HRV_VALSALVA:
         S = "VALSALVA PARAMETERS";
         Manoeuvre = "Valsalva";
         break;

      case HRV_STAND:
         S = "STAND PARAMETERS";
         Manoeuvre = "Stand";
         break;

      default:
         return;
   }
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 11;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(width / 8 + print_area->Left,
                              print_area->Top,
                              S);

   S = "TIME PARAMETERS";
   print_ptr->Canvas->TextOut(width * 5 / 8 + print_area->Left,
                              print_area->Top,
                              S);

   ++line_num;
   font_style.Clear();
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;

   S = Manoeuvre + " Ratio    ";
   text_width = print_ptr->Canvas->TextWidth(S);
   text_height = print_ptr->Canvas->TextHeight(S);
   xpos = width / 8 + print_area->Left + text_width;

   S = Manoeuvre + " High ";
   print_ptr->Canvas->TextOut(width / 8 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_high_manoeuvre->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = Manoeuvre + " Low ";
   print_ptr->Canvas->TextOut(width / 8 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
    print_ptr->Canvas->Font->Style = bold_font;
    print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_low_manoeuvre->Caption);
    print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = Manoeuvre + " Ratio ";
   print_ptr->Canvas->TextOut(width / 8 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_ratio_manoeuvre->Caption);
   print_ptr->Canvas->Font->Style = font_style;

   line_num = 2;

   print_ptr->Canvas->Font->Size = 8;
   S = "Average Heart Rate    ";
   text_width = print_ptr->Canvas->TextWidth(S);
   xpos = width * 5 / 8 + print_area->Left + text_width;

   S = "Capture Time ";
   print_ptr->Canvas->TextOut(width * 5 / 8 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_cap_time_manoeuvre->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Number of Pulses ";
   print_ptr->Canvas->TextOut(width * 5 / 8 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_pulses_manoeuvre->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Average Heart Rate  ";
   print_ptr->Canvas->TextOut(width * 5 / 8 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_hr_manoeuvre->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Mean R to R ";
   print_ptr->Canvas->TextOut(width * 5 / 8 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_rtor_mean_manoeuvre->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "R to R Range ";
   print_ptr->Canvas->TextOut(width * 5 / 8 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_rtor_range_manoeuvre->Caption);
   print_ptr->Canvas->Font->Style = font_style;
}

void Tfrm_report_hrv::print_report_footer(TRect *print_area)
{
  print_do_footer(print_area, report_hrv->DataRev);
}


void __fastcall Tfrm_report_hrv::FormHide(TObject *Sender)
{
   if (grd_report->DataSource != NULL)
   {
      grd_report->DataSource->OnDataChange = NULL;
   }
   if (report_qry != NULL)
   {
      report_qry->Close();
   }

   emma_display_statusbar_message("", "", "", sphygmocor_white);
   emma_display_statusbar_message("", "", sphygmocor_white);
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_report_hrv::tbsht_timeResize(TObject *Sender)
{
   // Ensures the time tabsheet displays consistently at multiple resolutions
   chrt_time_rtor_bar->Width = (pnl_analysis->Width - REPORT_PARAMS_PANEL_WIDTH)/2;
   chrt_poincare->Width = (pnl_analysis->Width - REPORT_PARAMS_PANEL_WIDTH)/2;
}
//---------------------------------------------------------------------------





void __fastcall Tfrm_report_hrv::mnu_graphicClick(TObject *Sender)
{
   // Exports a graphic of the current report screen
   Graphics::TBitmap*   bmp_image;
   PATIENT_RECORD_TYPE  pat;
   String               reptype_str = "";
   String               attach_fname;

   try
   {
      // PM V9
      // Display the status bar messages on the report form for the exported graphic
      pnl_status_bar->Visible = true;
      pnl_report_buttons->Visible = false;
      lbl_message1->Caption = frm_main->lbl_message1->Caption;
      lbl_message2->Caption = frm_main->lbl_message2->Caption;
      lbl_message3->Caption = frm_main->lbl_message3->Caption;
      lbl_message4->Caption = frm_main->lbl_message4->Caption;
      lbl_message1->Font->Color = frm_main->lbl_message1->Font->Color;
      lbl_message2->Font->Color = frm_main->lbl_message2->Font->Color;
      lbl_message3->Font->Color = frm_main->lbl_message3->Font->Color;
      lbl_message4->Font->Color = frm_main->lbl_message4->Font->Color;
      bmp_image = GetFormImage();
      if (bmp_image != NULL)
      {
         if (patient_get(&pat))
         {
            if (pgctrl_reports->ActivePage == tbsht_time)
            {
               reptype_str = "TIME_";
            }
            else if (pgctrl_reports->ActivePage == tbsht_frequency)
            {
               reptype_str = "FREQUENCY_";
            }
            else if (pgctrl_reports->ActivePage == tbsht_clinical)
            {
               reptype_str = "CLINICAL_";
            }
            // PM V9
            // If the EMR patient is active or default EMR mode is set - get the
            // export directory from the EMR object
            if (emr_patient_is_active() || emr_get_default_mode())
            {
               attach_fname = emr_get_outbound() + "PIC_" +reptype_str +pat.surname +"_"
                           +report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.jpg";
            }
            else
            {
               attach_fname = ExtractFilePath(Application->ExeName) +EXPORT_SUBDIR +"PIC_" +reptype_str +pat.surname +"_"
                              +report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") +"_hrv.jpg";
            }

            // If successful, notify the EMR object
            if (export_graphic(bmp_image, attach_fname))
            {
               emr_export();
            }
         }
         delete bmp_image;
      }
   }
   catch (...)
   {
      (void)MsgBox_warning("Could Not Create Graphic.",
                           SWARNING);
   }
   pnl_report_buttons->Visible = true;
   pnl_status_bar->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_hrv::mnu_textClick(TObject *Sender)
{
   PATIENT_RECORD_TYPE  pat;
   String               lFileName;

   if (patient_get(&pat))
   {
      // PM V9
      // If the EMR patient is active or default EMR mode is set - get the
      // export directory from the EMR object
      if (emr_patient_is_active() || emr_get_default_mode())
      {
         lFileName = emr_get_outbound() + pat.surname + "_"
                  + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.txt";
      }
      else
      {
         lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR + pat.surname + "_"
                         + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") +"_hrv.txt";
      }

      // If successful, notify the EMR object
      if (export_measurement(grd_report->DataSource->DataSet,
                         lFileName,
                         report_hrv))
      {
         emr_export();
      }
      /*if (grd_report->Visible)
      {
         grd_report->SetFocus();
      }*/
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_hrv::srs_hr_manoeuvreGetMarkText(
      TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   // Ignore rejected pulses
   for (int i = 0; i < report_hrv->number_rejected_rtor_tot; i++)
   {
      if (ValueIndex == report_hrv->index_rejected_rtor[i])
      {
         MarkText = "";
         number_highlow_rtor_graph++;
         return;
      }
   }

   switch (report_hrv->MeasureType)
   {
      case HRV_NORMAL:
         break;

      case HRV_VALSALVA:
         // 0.00001 is added or subtracted because the comparison of floating point numbers is unreliable
        // The low mark must be after the high mark
         if (60*1000/report_hrv->RtoR_raw[ValueIndex] + 0.00001 >= report_hrv_time->Valsalva_high)
         {
            MarkText = "High";
            low_after_high = true;
         }
         else if (60*1000/report_hrv->RtoR_raw[ValueIndex] - 0.00001 <= report_hrv_time->Valsalva_low)
         {
            if (low_after_high)
            {
               MarkText = "Low";
               low_after_high = false;
            }
            else
            {
               MarkText = "";
            }
         }
         else
         {
            MarkText = "";
         }
         break;

      // High and low values can only be within these ranges
      case HRV_STAND:
         if (!low_after_high)
         {
            if (ValueIndex > 3 + number_highlow_rtor_graph && ValueIndex < 25 + number_highlow_rtor_graph)
            {
               if (60*1000/report_hrv->RtoR_raw[ValueIndex] + 0.00001 >= report_hrv_time->Stand_high)
               {
                  MarkText = "High";
                  low_after_high = true;
                  return;
               }
            }
            MarkText = "";
         }
         if (low_after_high)
         {
            if (ValueIndex > 19 + number_highlow_rtor_graph && ValueIndex < 45 + number_highlow_rtor_graph)
            {
               if (60*1000/report_hrv->RtoR_raw[ValueIndex] - 0.00001 <= report_hrv_time->Stand_low)
               {
                  MarkText = "Low";
                  low_after_high = false;
                  return;
               }
            }
            MarkText = "";
         }
         break;
   }
}
//---------------------------------------------------------------------------
bool Tfrm_report_hrv::inconclusive_report()
{
   bool report_hrv_is_inconclusive = false;

   if (report_hrv->PulsesInSession)
   {
      if (100 * (float)((float)report_hrv->number_rejected_rtor_tot/(float)report_hrv->PulsesInSession) > HRV_MAX_REJECTED_PERCENTAGE)
      {
         report_hrv_is_inconclusive = true;
      }
      if (report_hrv_time->RMS_SD > HRV_MAX_RMS_SD)
      {
         report_hrv_is_inconclusive = true;
      }
      if (report_hrv_time->PNN50 > HRV_MAX_PNN50)
      {
         report_hrv_is_inconclusive = true;
      }
   }
      return (report_hrv_is_inconclusive);
}

bool Tfrm_report_hrv::inconclusive_manoeuvre()
{
   bool report_hrv_is_inconclusive = false;

   if (report_hrv->PulsesInSession)
   {
      if (100 * (float)((float)report_hrv->number_rejected_rtor_tot / (float)report_hrv->PulsesInSession) > HRV_MAX_REJECTED_PERCENTAGE)
      {
         report_hrv_is_inconclusive = true;
      }
   }
   return (report_hrv_is_inconclusive);
}


void __fastcall Tfrm_report_hrv::srs_hr_manoeuvreBeforeDrawValues(
      TObject *Sender)
{
   low_after_high = false;
   number_highlow_rtor_graph = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_hrv::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (Shift.Contains(ssAlt) && Key == 'X')
   {
      TPoint point = bbtn_export->ClientOrigin;
      int X = point.x;
      int Y = point.y + bbtn_export->Height;

      ppmnu_report->Popup(X, Y);
   }   
}
//---------------------------------------------------------------------------
// PM V9
void __fastcall Tfrm_report_hrv::mnu_allClick(TObject *Sender)
{
   Graphics::TBitmap*   bmp_image;
   TTabSheet            *previous;
   String               filename;
   String               outbound_directory;
   PATIENT_RECORD_TYPE  pat;
   bool                 success = true;
   int                  page_count;
   String               retype_str;

   if (emr_get_enabled())
   {
      outbound_directory = emr_get_outbound();
      if (patient_get(&pat) && outbound_directory != "")
      {
         // Display the status bar messages on the report form for the exported graphic
         Screen->Cursor = crHourGlass;
         pnl_status_bar->Visible = true;
         pnl_report_buttons->Visible = false;
         lbl_message1->Caption = frm_main->lbl_message1->Caption;
         lbl_message2->Caption = frm_main->lbl_message2->Caption;
         lbl_message3->Caption = frm_main->lbl_message3->Caption;
         lbl_message4->Caption = frm_main->lbl_message4->Caption;
         lbl_message1->Font->Color = frm_main->lbl_message1->Font->Color;
         lbl_message2->Font->Color = frm_main->lbl_message2->Font->Color;
         lbl_message3->Font->Color = frm_main->lbl_message3->Font->Color;
         lbl_message4->Font->Color = frm_main->lbl_message4->Font->Color;
         switch (report_hrv->MeasureType)
         {
            case HRV_NORMAL:
               previous = pgctrl_reports->ActivePage;
               switch (emr_get_option())
               {
                  // Standard option exports all 3 graphics and the text file
                  case EMR_STANDARD:
                     try
                     {
                        page_count = pgctrl_reports->PageCount;
                        for (int i = 0; i < page_count; i++)
                        {
                           pgctrl_reports->ActivePageIndex = i;
                           // The tabsheet hints contain the export prefixes
                           // So DO NOT change tabsheet hints!!!
                           retype_str = pgctrl_reports->ActivePage->Hint;
                           if (retype_str == "MANOEUVRE")
                           {
                              break;
                           }
                           bmp_image = GetFormImage();
                           if (bmp_image != NULL)
                           {
                              filename = outbound_directory + "PIC_" + retype_str + "_" + pat.surname + "_"
                                       + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.jpg";
                              if (report_export_graphic(bmp_image, filename) == false)
                              {
                                 success = false;
                              }
                              delete bmp_image;
                           }
                        }
                        
                        filename = outbound_directory + pat.surname + "_"
                                 + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.txt";
                        if (report_export_measurement(filename) == false)
                        {
                           success = false;
                        }
                     }
                     catch (...)
                     {
                        (void)MsgBox_warning("Could Not Create Graphic.", SWARNING);
                        success = false;
                     }
                     break;

                  // Clinical option exports the Time Report graphic and the text file
                  case EMR_CLINICAL:
                     try
                     {
                        pgctrl_reports->ActivePage = tbsht_time;
                        bmp_image = GetFormImage();
                        if (bmp_image != NULL)
                        {
                           filename = outbound_directory + "PIC_TIME_" + pat.surname + "_"
                                    + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.jpg";
                           if (report_export_graphic(bmp_image, filename) == false)
                           {
                              success = false;
                           }
                           delete bmp_image;
                        }

                        filename = outbound_directory + pat.surname + "_"
                                 + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.txt";
                        if (report_export_measurement(filename) == false)
                        {
                           success = false;
                        }
                     }
                     catch (...)
                     {
                        (void)MsgBox_warning("Could Not Create Graphic.", SWARNING);
                        success = false;
                     }
                     break;

                  // Detailed option exports the Frequency Report graphic and the text file
                  case EMR_DETAILED:
                     try
                     {
                        pgctrl_reports->ActivePage = tbsht_frequency;
                        bmp_image = GetFormImage();
                        if (bmp_image != NULL)
                        {
                           filename = outbound_directory + "PIC_FREQUENCY_" + pat.surname + "_"
                                    + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.jpg";
                           if (report_export_graphic(bmp_image, filename) == false)
                           {
                              success = false;
                           }
                           delete bmp_image;
                        }

                        filename = outbound_directory + pat.surname + "_"
                                 + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.txt";
                        if (report_export_measurement(filename) == false)
                        {
                           success = false;
                        }
                     }
                     catch (...)
                     {
                        (void)MsgBox_warning("Could Not Create Graphic.", SWARNING);
                        success = false;
                     }
                     break;

                  // These options export the Reports to pdf and the text file
                  case EMR_ALL_PDF:
                  case EMR_CLINICAL_PDF:
                  case EMR_DETAILED_PDF:
                     pdf_file = "REPORT_" + pat.surname + "_"
                              + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv";
                     if (report_export_pdf() == false)
                     {
                        success = false;
                     }

                     filename = outbound_directory + pat.surname + "_"
                              + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.txt";
                     if (report_export_measurement(filename) == false)
                     {
                        success = false;
                     }
                     break;

                  // All option exports all 3 reports as graphics, plus the pdf report and text file
                  case EMR_ALL:
                     try
                     {
                        page_count = pgctrl_reports->PageCount;
                        for (int i = 0; i < page_count; i++)
                        {
                           pgctrl_reports->ActivePageIndex = i;
                           // The tabsheet hints contain the export prefixes
                           // So DO NOT change tabsheet hints!!!
                           retype_str = pgctrl_reports->ActivePage->Hint;
                           if (retype_str == "MANOEUVRE")
                           {
                              break;
                           }
                           bmp_image = GetFormImage();
                           if (bmp_image != NULL)
                           {
                              filename = outbound_directory + "PIC_" + retype_str + "_" + pat.surname + "_"
                                       + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.jpg";
                              if (report_export_graphic(bmp_image, filename) == false)
                              {
                                 success = false;
                              }
                              delete bmp_image;
                           }
                        }

                        pdf_file = "REPORT_" + pat.surname + "_"
                                 + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv";
                        if (report_export_pdf() == false)
                        {
                           success = false;
                        }

                        filename = outbound_directory + pat.surname + "_"
                                 + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.txt";
                        if (report_export_measurement(filename) == false)
                        {
                           success = false;
                        }
                     }
                     catch (...)
                     {
                        (void)MsgBox_warning("Could Not Create Graphic.", SWARNING);
                        success = false;
                     }
                     break;
               }
               pgctrl_reports->ActivePage = previous;
               break;

            case HRV_VALSALVA:
            case HRV_STAND:
               switch (emr_get_option())
               {
                  // These options export the Report graphic and the text file
                  case EMR_STANDARD:
                  case EMR_CLINICAL:
                  case EMR_DETAILED:
                     try
                     {
                        bmp_image = GetFormImage();
                        if (bmp_image != NULL)
                        {
                           filename = outbound_directory + "PIC_" + pat.surname + "_"
                                    + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.jpg";
                           if (report_export_graphic(bmp_image, filename) == false)
                           {
                              success = false;
                           }
                           delete bmp_image;
                        }

                        filename = outbound_directory + pat.surname + "_"
                                 + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.txt";
                        if (report_export_measurement(filename) == false)
                        {
                           success = false;
                        }
                     }
                     catch (...)
                     {
                        (void)MsgBox_warning("Could Not Create Graphic.", SWARNING);
                        success = false;
                     }
                     break;

                  // These options export the Report to pdf and a text file
                  case EMR_ALL_PDF:
                  case EMR_CLINICAL_PDF:
                  case EMR_DETAILED_PDF:
                     pdf_file = "REPORT_" + pat.surname + "_"
                              + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv";
                     if (report_export_pdf() == false)
                     {
                        success = false;
                     }

                     filename = outbound_directory + pat.surname + "_"
                              + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.txt";
                     if (report_export_measurement(filename) == false)
                     {
                        success = false;
                     }
                     break;

                  // All option exports the Report as a graphic, pdf and a text file
                  case EMR_ALL:
                     try
                     {
                        bmp_image = GetFormImage();
                        if (bmp_image != NULL)
                        {
                           filename = outbound_directory + "PIC_" + pat.surname + "_"
                                    + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.jpg";
                           if (report_export_graphic(bmp_image, filename) == false)
                           {
                              success = false;
                           }
                           delete bmp_image;
                        }

                        pdf_file = "REPORT_" + pat.surname + "_"
                                 + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv";
                        if (report_export_pdf() == false)
                        {
                           success = false;
                        }

                        filename = outbound_directory + pat.surname + "_"
                                 + report_hrv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_hrv.txt";
                        if (report_export_measurement(filename) == false)
                        {
                           success = false;
                        }
                     }
                     catch (...)
                     {
                        (void)MsgBox_warning("Could Not Create Graphic.", SWARNING);
                        success = false;
                     }
                     break;
               }
               break;
         }
         pnl_report_buttons->Visible = true;
         pnl_status_bar->Visible = false;
         Screen->Cursor = crDefault;

         // If successful, notify the user and the EMR object
         if (success)
         {
            MsgBox_information("Files successfully exported to: " + outbound_directory, "Export All Successful");
            emr_export();
         }
         else
         {
            MsgBox_information("Some files were not exported successfully", "Export All Failed");
         }
      }
   }
}
// PM V9
/* ###########################################################################
// Exports the graphic bmp_image to the file jpeg_file_name without requiring
// user confirmation
*/
bool Tfrm_report_hrv::report_export_graphic(Graphics::TBitmap*   bmp_image,
                                                  String jpeg_file_name)
{
   bool         created = false;
   TJPEGImage*  jpg_image;

   Application->ProcessMessages();
   jpg_image = new TJPEGImage();
   if (jpg_image)
   {
      jpg_image->CompressionQuality = 75;
      jpg_image->Performance = jpBestSpeed;
      jpg_image->PixelFormat = jf24Bit;
      jpg_image->Smoothing = false;
      jpg_image->Assign(bmp_image);
      jpg_image->SaveToFile(jpeg_file_name);
      created = true;
      delete jpg_image;
      jpg_image = (TJPEGImage *)0;
   }
   return created;
}
// PM V9
/* ###########################################################################
// Exports the current HRV report as a text file to filename without requiring
// user confirmation
*/
bool Tfrm_report_hrv::report_export_measurement(String filename)
{
   int      lFileHandle;
   String   lOut = "";

   // Create the file
   if (FileExists(filename))
   {
      DeleteFile(filename);
   }
   lFileHandle = FileCreate(filename);
   if (lFileHandle <= 0)
   {
      MsgBox(TERROR, MSG_EXPORT_ERROR, MSG_EXPORT_ERROR_FILE, LoadStr(MSG_EXPORT_ERROR_FILE) + filename);
      return false;
   }

   Application->ProcessMessages();

   // Export the titles
   if (report_hrv->ExportPrintTitle(grd_report->DataSource->DataSet, lOut) == false)
   {
      return false;
   }

   lOut = lOut + "\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
   Application->ProcessMessages();

   // Export the parameters
   lOut = "";
   if (report_hrv->Export(lOut)== false)
   {
      return false;
   }
   lOut = lOut + "\r\n\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());

   // Export the Arrays
   if (report_hrv->ExportArrays(lFileHandle) == false)
   {
      return false;
   }

   FileClose(lFileHandle);
   return true;
}
// PM V9
/* ###########################################################################
// Exports the current HRV report as a pdf file without requiring user confirmation
*/
bool Tfrm_report_hrv::report_export_pdf()
{
   TPrinter *printer_ptr;
   int      index;
   bool     success = false;
   String   pdf_printer;

   Application->ProcessMessages();
   //Application->HandleMessage();

   printer_ptr = print_get_printer_ptr();
   if (printer_ptr == NULL)
   {
      return false;
   }

   // Get the printer from the EMR object
   pdf_printer = emr_get_printer();
   index = printer_ptr->Printers->IndexOf(pdf_printer);
   
   if (index >=0)
   {
      printer_ptr->PrinterIndex = index;

      // Then call the print function
      bbtn_printClick(this);
      Screen->Cursor = crHourGlass;
      success = true;
   }
   else
   {
      MsgBox_show(TERROR,
                  MSG_EMR_ERROR,
                  "The Printer: " + pdf_printer + LoadStr(MSG_EMR_PDF_ERROR),
                  MSG_EMR_PDF_ERROR,
                  "The Printer: " + pdf_printer + LoadStr(MSG_EMR_PDF_ERROR));
      success = false;
   }

   return success;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_hrv::pnl_fchartsResize(TObject *Sender)
{
   // Ensures the frequency tabsheet displays consistently at multiple resolutions
   // and while printing
   chrt_lfhf_pie->Width = pnl_fcharts->Width * 0.4;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_hrv::bbtn_printClick(TObject *Sender)
{
   int                  report_width;
   int                  report_height;
   int                  left_margin;
   TRect                print_rect;
   TPrinterOrientation  old_orient;
   TPrinter             *printer_ptr;
   AnsiString           S;

   if (this->Visible)
   {
      // PM V9
      // Do not ask for user confirmation when printing to pdf
      if (pdf_file == "")
      {
         if (MsgBox(MSG_PRINT_REPORT, CONFIRMATION, MB_YESNO | MB_ICONQUESTION) != ID_YES)
         {
           return;
         }
      }
   }
   printer_ptr = print_get_printer_ptr();
   if (printer_ptr == NULL)
   {
      return;
   }

   Screen->Cursor = crHourGlass;
   old_orient = printer_ptr->Orientation;
   printer_ptr->Orientation  = poPortrait;
   // PM V9
   // Set the title for pdf reports
   if (pdf_file == "")
   {
      printer_ptr->Title = "SphygmoCor HRV Report";
   }
   else
   {
      printer_ptr->Title = pdf_file;
      pdf_file = "";
   }
   if (ecg_is_displayed)
   {
      bbtn_ecgClick(Sender);
   }
   try
   {
       // PM CR
       chrt_time_rtor->UndoZoom();
       chrt_manoeuvre->UndoZoom();
       
       printer_ptr->BeginDoc();

       report_width =  printer_ptr->PageWidth;
       report_width = report_width - (report_width * 0.02);
       report_height = printer_ptr->PageHeight;
       left_margin = report_width * 0.06;

       print_rect.Top = report_height * 0.87;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height;
       print_report_footer(&print_rect);

       print_rect.Top = report_height * 0.1;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.15;
       print_report_header(&print_rect);
       print_do_atcor_image(&print_rect);

       print_rect.Top = print_rect.Bottom;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.25;
       print_report_patient(&print_rect);

       print_rect.Top = report_height * 0.25;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.35;
       print_report_study(printer_ptr, &print_rect);

       switch (report_hrv->MeasureType)
       {
         case HRV_NORMAL:
            print_rect.Top = report_height * 0.76;
            print_rect.Left = left_margin;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.9;
            print_report_hrv_params(printer_ptr, &print_rect);

            // Changes the R to R chart's size to that displayed on 600x800 resolution
            pnl_waveform->Align = alNone;
            pnl_waveform->Height = REPORT_PANEL_WAVEFORM_PRINT_HEIGHT;
            pnl_waveform->Width = REPORT_PANEL_WAVEFORM_PRINT_WIDTH;

            print_rect.Top = report_height * 0.34;
            print_rect.Left = left_margin;
            print_rect.Right = report_width * 0.7;
            print_rect.Bottom = report_height * 0.54;

            chrt_time_rtor->PrintResolution = -100;
            chrt_time_rtor->BottomAxis->LabelsFont->Color = sphygmocor_black;
            chrt_time_rtor->BottomAxis->Title->Font->Color = sphygmocor_black;
            chrt_time_rtor->LeftAxis->LabelsFont->Color = sphygmocor_black;
            chrt_time_rtor->LeftAxis->Title->Font->Color = sphygmocor_black;
            chrt_time_rtor->Title->Font->Color = sphygmocor_maroon;
            chrt_time_rtor->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.34;
            print_rect.Left = report_width * 0.7;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.54;

            // The histogram size is constant - no need to change
            chrt_time_rtor_bar->PrintResolution = -100;
            chrt_time_rtor_bar->BottomAxis->LabelsFont->Color = sphygmocor_black;
            chrt_time_rtor_bar->BottomAxis->Title->Font->Color = sphygmocor_black;
            chrt_time_rtor_bar->LeftAxis->LabelsFont->Color = sphygmocor_black;
            chrt_time_rtor_bar->LeftAxis->Title->Font->Color = sphygmocor_black;
            chrt_time_rtor_bar->Title->Visible = true;
            chrt_time_rtor_bar->PrintPartial(print_rect);

            // Changes both frequency chart sizes to that displayed at 600x800 resolution
            pnl_fcharts->Align = alNone;
            pnl_fcharts->Height = REPORT_PANEL_FCHARTS_PRINT_HEIGHT;
            pnl_fcharts->Width = REPORT_PANEL_FCHARTS_PRINT_WIDTH;
            
            print_rect.Top = report_height * 0.54;
            print_rect.Left = left_margin;
            print_rect.Right = report_width * 0.7;
            print_rect.Bottom = report_height * 0.74;

            // PM V9
            // Setting print resolution to -100 fixes the HRV printing problem
            chrt_freq_spectrum->PrintResolution = -100;
            chrt_freq_spectrum->BottomAxis->LabelsFont->Color = sphygmocor_black;
            chrt_freq_spectrum->BottomAxis->Title->Font->Color = sphygmocor_black;
            chrt_freq_spectrum->LeftAxis->LabelsFont->Color = sphygmocor_black;
            chrt_freq_spectrum->LeftAxis->Title->Font->Color = sphygmocor_black;
            chrt_freq_spectrum->Title->Font->Color = sphygmocor_maroon;
            chrt_freq_spectrum->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.54;
            print_rect.Left = report_width * 0.7;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.74;

            chrt_lfhf_pie->PrintResolution = -100;
            chrt_lfhf_pie->Title->Font->Color = sphygmocor_maroon;
            chrt_lfhf_pie->PrintPartial(print_rect);

            printer_ptr->EndDoc();

            // Set charts back to original size and display
            pnl_waveform->Align = alClient;
            pnl_fcharts->Align = alClient;

            chrt_time_rtor->BottomAxis->LabelsFont->Color = sphygmocor_white;
            chrt_time_rtor->BottomAxis->Title->Font->Color = sphygmocor_white;
            chrt_time_rtor->LeftAxis->LabelsFont->Color = sphygmocor_white;
            chrt_time_rtor->LeftAxis->Title->Font->Color = sphygmocor_white;
            chrt_time_rtor->Title->Font->Color = sphygmocor_white;

            chrt_time_rtor_bar->BottomAxis->LabelsFont->Color = sphygmocor_white;
            chrt_time_rtor_bar->BottomAxis->Title->Font->Color = sphygmocor_white;
            chrt_time_rtor_bar->LeftAxis->LabelsFont->Color = sphygmocor_white;
            chrt_time_rtor_bar->LeftAxis->Title->Font->Color = sphygmocor_white;
            chrt_time_rtor_bar->Title->Visible = false;

            chrt_freq_spectrum->BottomAxis->LabelsFont->Color = sphygmocor_white;
            chrt_freq_spectrum->BottomAxis->Title->Font->Color = sphygmocor_white;
            chrt_freq_spectrum->LeftAxis->LabelsFont->Color = sphygmocor_white;
            chrt_freq_spectrum->LeftAxis->Title->Font->Color = sphygmocor_white;
            chrt_freq_spectrum->Title->Font->Color = sphygmocor_white;

            chrt_lfhf_pie->Title->Font->Color = sphygmocor_white;
            break;

         case HRV_VALSALVA:
         case HRV_STAND:
            print_rect.Top = report_height * 0.76;
            print_rect.Left = left_margin;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.9;
            print_report_manoeuvre_params(printer_ptr, &print_rect);

            // Changes the Heart Rate chart's size to that displayed on 600x800 resolution
            chrt_manoeuvre->Align = alNone;
            chrt_manoeuvre->Height = REPORT_CHART_MANOEUVRE_PRINT_HEIGHT;
            chrt_manoeuvre->Width = REPORT_CHART_MANOEUVRE_PRINT_WIDTH;
            chrt_manoeuvre_normals->Align = alNone;
            chrt_manoeuvre_normals->Height = REPORT_CHART_MANOEUVRE_PRINT_HEIGHT / 2;
            chrt_manoeuvre_normals->Width = REPORT_CHART_MANOEUVRE_PRINT_WIDTH;

            print_rect.Top = report_height * 0.34;
            print_rect.Left = left_margin;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.64;

            chrt_manoeuvre->PrintResolution = -100;
            chrt_manoeuvre->BottomAxis->LabelsFont->Color = sphygmocor_black;
            chrt_manoeuvre->BottomAxis->Title->Font->Color = sphygmocor_black;
            chrt_manoeuvre->LeftAxis->LabelsFont->Color = sphygmocor_black;
            chrt_manoeuvre->LeftAxis->Title->Font->Color = sphygmocor_black;
            chrt_manoeuvre->Title->Font->Color = sphygmocor_maroon;
            chrt_manoeuvre->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.64;
            print_rect.Left = left_margin;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.74;

            chrt_manoeuvre_normals->PrintResolution = -100;
            chrt_manoeuvre_normals->BottomAxis->LabelsFont->Color = sphygmocor_black;
            chrt_manoeuvre_normals->BottomAxis->Title->Font->Color = sphygmocor_black;
            chrt_manoeuvre_normals->LeftAxis->LabelsFont->Color = sphygmocor_black;
            chrt_manoeuvre_normals->LeftAxis->Title->Font->Color = sphygmocor_black;
            chrt_manoeuvre_normals->Title->Font->Color = sphygmocor_maroon;
            chrt_manoeuvre_normals->PrintPartial(print_rect);

            printer_ptr->EndDoc();
                                                   
            // Set charts back to original size and display
            chrt_manoeuvre->Align = alClient;
            chrt_manoeuvre_normals->Align = alClient;

            chrt_manoeuvre->BottomAxis->LabelsFont->Color = sphygmocor_white;
            chrt_manoeuvre->BottomAxis->Title->Font->Color = sphygmocor_white;
            chrt_manoeuvre->LeftAxis->LabelsFont->Color = sphygmocor_white;
            chrt_manoeuvre->LeftAxis->Title->Font->Color = sphygmocor_white;
            chrt_manoeuvre->Title->Font->Color = sphygmocor_white;

            chrt_manoeuvre_normals->BottomAxis->LabelsFont->Color = sphygmocor_white;
            chrt_manoeuvre_normals->BottomAxis->Title->Font->Color = sphygmocor_white;
            chrt_manoeuvre_normals->LeftAxis->LabelsFont->Color = sphygmocor_white;
            chrt_manoeuvre_normals->LeftAxis->Title->Font->Color = sphygmocor_white;
            chrt_manoeuvre_normals->Title->Font->Color = sphygmocor_white;
            break;

         default:
            printer_ptr->EndDoc();                                                    
            break;
       }
   }
   catch (Exception &exception)
   {
      printer_ptr->Abort();
      printer_ptr->EndDoc();
   }
   printer_ptr->Orientation = old_orient;
   Screen->Cursor = crDefault;
   /*if (this->Visible)
   {
      grd_report->SetFocus();
   }*/   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_hrv::bbtn_deleteClick(TObject *Sender)
{
   AnsiString S;

   S = lbl_pname->Caption;
   if (report_qry != NULL)
   {
      if (MsgBox(LoadStr(MSG_DELETE_MEAS2) + S + "\n\n" + LoadStr(MSG_ARE_YOU_SURE),
          SCONFIRMATION, MB_YESNO | MB_ICONWARNING) == ID_YES)
      {
         try
         {
            report_qry->Delete();
         }
         catch (...)
         {
            return;
         }

         if (report_qry->RecordCount == 0)
         {
            MsgBox(MSG_NO_REPORTS_TO_DISPLAY, SNOTIFICATION, MB_ICONINFORMATION);
            patient_update_measurement_count(0);
            multdb_set_delete_status(false);
            Hide();
            frm_main->spdbtn_patientClick(Sender);
         }
         else
         {
            patient_update_measurement_count((short)(report_qry->RecordCount));
         }
      }
   }   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_hrv::bbtn_modifyClick(TObject *Sender)
{
   MEAS_SENDER_TYPE  report_sender;

   // Disable OnChange event to protect rewriting HRV
   grd_report->DataSource->OnDataChange = NULL;

   // PM V9
   // The field that opens the modify form will be selected on the modify form
   if (Sender == lbl_operator_title || Sender == lbl_operator)
   {
      report_sender = MEAS_OPERATOR;
   }
   else if (Sender == lbl_hwbmi_title || Sender == lbl_hwbmi)
   {
      report_sender = MEAS_BMI;
   }
   else if (Sender == lbl_med_title || Sender == edt_med)
   {
      report_sender = MEAS_MEDICATIONS;
   }
   else if (Sender == lbl_notes_title || Sender == edt_notes)
   {
      report_sender = MEAS_NOTES;
   }
   else if (Sender == lbl_pressure_title || Sender == lblSpDpMp ||
            Sender == lbl_pressure_title_manoeuvre || Sender == lblSpDpMp_manoeuvre)
   {
      report_sender = MEAS_PRESSURES;
   }
   else
   {
      report_sender = MEAS_PRESSURES;
   }

   // Call recalculate form
   bool ret = meas_recalculate_hrv_show_form(this,
                                         report_hrv,
                                         report_qry,
                                         lbl_pname->Caption,
                                         report_sender);
   // Restore OnChange event
   grd_report->DataSource->OnDataChange = record_changed;

   // Refresh grid and charts
   if (ret)
   {
      record_changed(this, NULL);
   }
   /*if (grd_report->Visible)
   {
      grd_report->SetFocus();
   }*/   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_hrv::bbtn_ecgClick(TObject *Sender)
{
   if (pgctrl_reports->ActivePage == tbsht_time)
   {
      if (ecg_is_displayed)
      {
         chrt_ecg_report->Visible = false;
         pnl_analysis->Visible = true;
         bbtn_ecg->Caption = "Show &ECG";
         ecg_is_displayed = false;
      }
      else
      {
         chrt_ecg_report->Visible = true;
         pnl_analysis->Visible = false;
         bbtn_ecg->Caption = "Hide &ECG";
         chrt_ecg_report->Height = pnl_waveform->Height/2;
         ecg_is_displayed = true;
      }
   }
   else if (pgctrl_reports->ActivePage == tbsht_manoeuvre)
   {
      if (ecg_manoeuvre)
      {
         chrt_manoeuvre_ecg->Visible = false;
         pnl_manoeuvre_bottom->Visible = true;
         bbtn_ecg->Caption = "Show &ECG";
         ecg_manoeuvre = false;
      }
      else
      {
         chrt_manoeuvre_ecg->Visible = true;
         pnl_manoeuvre_bottom->Visible = false;
         bbtn_ecg->Caption = "Hide &ECG";
         chrt_manoeuvre_ecg->Height = pnl_manoeuvre_waveform->Height/2;
         ecg_manoeuvre = true;
      }
   }
   grd_report->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_hrv::pgctrl_reportsChange(TObject *Sender)
{
   if (report_hrv->ecg_signal_length != 0 &&
      (pgctrl_reports->ActivePage == tbsht_time ||
      pgctrl_reports->ActivePage == tbsht_manoeuvre))
   {
      bbtn_ecg->Visible = true;
   }
   else
   {
      bbtn_ecg->Visible = false;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_hrv::pnl_bottomResize(TObject *Sender)
{
   pnl_right->Width = pnl_bottom->Width / 4;
   pnl_left->Width = pnl_bottom->Width / 4;
   pnl_middle_left->Width = pnl_bottom->Width / 4;
}
//---------------------------------------------------------------------------

