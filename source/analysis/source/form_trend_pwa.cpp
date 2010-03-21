//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <math.h>

#include <dbmgr/pubserv.h>
#include <patient/pubserv.h>
#include <meas/pubserv.h>
#include <report/pubserv.h>
#include <export/pubserv.h>
#include <msg/pubserv.h>
#include <print/pubserv.h>
#include <analysis/pubserv.h>
#include <config/pubserv.h>
#include <scor/form_main.h>
#include <scor/utils.h>
#include "analysis.h"
#include "form_trend_pwa.h"
#include "form_analysis_pwa.h"
#include "form_select.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const int nof_pressure_trends = 7;
const int ANALYSIS_CHART_PRINT_HEIGHT = 100;
const int ANALYSIS_CHART_PRINT_WIDTH = 200;
const int ANALYSIS_PRESSURE_PRINT_HEIGHT = 400;
const int ANALYSIS_PRESSURE_PRINT_WIDTH = 200;

//---------------------------------------------------------------------------
__fastcall Tfrm_trend_pwa::Tfrm_trend_pwa(TComponent* Owner)
    : Child_Form(Owner)
{
   clicked_series = false;
   series_index = 0;
   trend_show_corresponding = false;
   report_age = 0;
}

void  __fastcall Tfrm_trend_pwa::FormShow(TObject *Sender)
{
   int height = pnl_time->Height - chrt_hrate_pressure->Height - 24;
   int width = pnl_time->Width - 8;

   TStringList* lListOfMeasurements =
     (frm_analysis_pwa->analysis_selected_measurements->Count > 0 ?
      frm_analysis_pwa->analysis_selected_measurements : frm_analysis_pwa->analysis_all_measurements);

   if ((lListOfMeasurements->Count > 0) && (frm_analysis_pwa->analysis_qry->RecordCount > 0))
   {
      ClearSeries();
      ShowCharts(lListOfMeasurements, false);
   }

   bbtn_print->Enabled = print_does_printer_exist();
   // If the audit option is set, disable export
   if (config_get_audit_option())
   {
      bbtn_export->Enabled = false;
   }

   // PM V9
   // The Heart Rate charts will always be displayed
   // In Clinical mode, only the selected parameters will be displayed
   // In Research mode, AP, AIx@HR75, ED and SEVR will be displayed
   if (config_get_clinical_option())
   {
      chrt_edpc->Visible = false;
      chrt_svr->Visible = false;

      if (config_get_clinical_aixhr75() && config_get_clinical_aix())
      {
         chrt_aix_norm->Visible = true;
         chrt_aix->Visible = true;

         chrt_hrate_timing->Top = 4;
         chrt_hrate_timing->Left = 4;
         chrt_hrate_timing->Width = width;
         chrt_hrate_timing->Height = chrt_hrate_pressure->Height;

         chrt_ap->Left = 4;
         chrt_ap->Top = chrt_hrate_timing->Top + chrt_hrate_timing->Height + 5;
         chrt_ap->Width = width;
         chrt_ap->Height = height / 3;

         chrt_aix->Left = 4;
         chrt_aix->Top = chrt_ap->Top + height / 3 + 5;
         chrt_aix->Width = width;
         chrt_aix->Height = height / 3;

         chrt_aix_norm->Left = 4;
         chrt_aix_norm->Top = chrt_aix->Top + height / 3 + 5;
         chrt_aix_norm->Width = width;
         chrt_aix_norm->Height = height / 3;
      }
      else if (config_get_clinical_aixhr75())
      {
         chrt_aix_norm->Visible = true;
         chrt_aix->Visible = false;

         chrt_hrate_timing->Top = 4;
         chrt_hrate_timing->Left = 4;
         chrt_hrate_timing->Width = width;
         chrt_hrate_timing->Height = chrt_hrate_pressure->Height;

         chrt_ap->Left = 4;
         chrt_ap->Top = chrt_hrate_timing->Top + chrt_hrate_timing->Height + 6;
         chrt_ap->Width = width;
         chrt_ap->Height = height / 2;

         chrt_aix_norm->Left = 4;
         chrt_aix_norm->Top = chrt_ap->Top + height / 2 + 6;
         chrt_aix_norm->Width = width;
         chrt_aix_norm->Height = height / 2;
      }
      else if (config_get_clinical_aix())
      {
         chrt_aix_norm->Visible = false;
         chrt_aix->Visible = true;

         chrt_hrate_timing->Top = 4;
         chrt_hrate_timing->Left = 4;
         chrt_hrate_timing->Width = width;
         chrt_hrate_timing->Height = chrt_hrate_pressure->Height;

         chrt_ap->Left = 4;
         chrt_ap->Top = chrt_hrate_timing->Top + chrt_hrate_timing->Height + 6;
         chrt_ap->Width = width;
         chrt_ap->Height = height / 2;

         chrt_aix->Left = 4;
         chrt_aix->Top = chrt_ap->Top + height / 2 + 6;
         chrt_aix->Width = width;
         chrt_aix->Height = height / 2;
      }
      else
      {
         chrt_aix_norm->Visible = false;
         chrt_aix->Visible = false;

         chrt_hrate_timing->Top = 4;
         chrt_hrate_timing->Left = 4;
         chrt_hrate_timing->Width = width;
         chrt_hrate_timing->Height = chrt_hrate_pressure->Height;

         chrt_ap->Left = 4;
         chrt_ap->Top = chrt_hrate_timing->Top + chrt_hrate_timing->Height + 10;
         chrt_ap->Width = width;
         chrt_ap->Height = height;
      }

   }
   else
   {
      chrt_aix->Visible = false;

      chrt_hrate_timing->Top = 4;
      chrt_hrate_timing->Left = 4;
      chrt_hrate_timing->Width = width;
      chrt_hrate_timing->Height = chrt_hrate_pressure->Height;

      chrt_ap->Left = 4;
      chrt_ap->Top = chrt_hrate_timing->Top + chrt_hrate_timing->Height + 4;
      chrt_ap->Width = width;
      chrt_ap->Height = height / 4;

      chrt_aix_norm->Left = 4;
      chrt_aix_norm->Top = chrt_ap->Top + height / 4 + 4;
      chrt_aix_norm->Width = width;
      chrt_aix_norm->Height = height / 4;

      chrt_edpc->Left = 4;
      chrt_edpc->Top = chrt_aix_norm->Top + height / 4 + 4;
      chrt_edpc->Width = width;
      chrt_edpc->Height = height / 4;

      chrt_svr->Left = 4;
      chrt_svr->Top =  chrt_edpc->Top + height / 4 + 4;
      chrt_svr->Width = width;
      chrt_svr->Height = height / 4;
   }
   SetFocus();
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwa::FormResize(TObject *Sender)
{
   pnl_pressure->Width = this->Width *0.48;
   pnl_time->Width = this->Width * 0.48;
   pnl_tool->Width = this->Width * 0.04;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwa::pnl_pressureResize(TObject *Sender)
{
   int height;
   height = pnl_pressure->Height - 12;

   chrt_hrate_pressure->Top = 4;
   chrt_hrate_pressure->Left = 4;
   chrt_hrate_pressure->Width = pnl_pressure->Width - 8;
   chrt_hrate_pressure->Height = height / 5;

   chrt_pressure->Left = 4;
   chrt_pressure->Top = chrt_hrate_pressure->Top + height / 5 + 4;
   chrt_pressure->Width = pnl_time->Width - 8;
   chrt_pressure->Height = 4 * height / 5;
}
//------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwa::chrt_hrate_pressureMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TChart *chart;

   chart = dynamic_cast<TChart *>(Sender);

   if (chart != NULL)
   {
      if (chart != chrt_pressure)
      {
         if (chart == chrt_hrate_pressure)
         {
            if (Button == mbLeft)
            {
               chart->Series[1]->Marks->Style = smsValue;
            }
            else
            {
               chart->Series[1]->Marks->Style = smsLabel;
            }
         }
         chart->Series[1]->Marks->Visible = true;
      }
      else
      {
          for (int x = 0; x < nof_pressure_trends; x++)
          {
              chart->Series[x]->Marks->Visible = true;
          }
      }
   }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwa::chrt_hrate_pressureMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TChart *chart;

   chart = dynamic_cast<TChart *>(Sender);

   if (chart != chrt_pressure)
   {
      chart->Series[1]->Marks->Visible = false;
   }
   else
   {
      for (int x = 0; x < nof_pressure_trends; x++)
      {
         chart->Series[x]->Marks->Visible = false;
      }
   }
   if (chart->Series[1] == srs_phrate_line)
   {
      Systolic->Marks->Visible = false;
      Diastolic->Marks->Visible = false;
      srs_p_systolic->Marks->Visible = false;
      srs_p_diastolic->Marks->Visible = false;
      Mean->Marks->Visible = false;
      Pulse->Marks->Visible = false;
      Augmentation->Marks->Visible = false;
   }
   clicked_series = false;
   series_index = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwa::chrt_hrate_pressureClickSeries(
      TCustomChart *Sender, TChartSeries *Series, int ValueIndex,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   clicked_series = true;
   series_index = ValueIndex;
   if (Series == srs_phrate_line)
   {
      if (trend_show_corresponding)
      {
         Systolic->Marks->Visible = true;
         Diastolic->Marks->Visible = true;
         srs_p_systolic->Marks->Visible = true;
         srs_p_diastolic->Marks->Visible = true;
         Pulse->Marks->Visible = true;
         Mean->Marks->Visible = true;
         Augmentation->Marks->Visible = true;
      }
   }
   else
   {
      clicked_series = false;
      if (Series == Systolic)
      {
         Systolic->Marks->Visible = true;
         srs_p_systolic->Marks->Visible = false;
         srs_p_diastolic->Marks->Visible = false;
         Mean->Marks->Visible = false;
         Diastolic->Marks->Visible = false;
         Pulse->Marks->Visible = false;
         Augmentation->Marks->Visible = false;
      }
      else if (Series == Diastolic)
      {
         Diastolic->Marks->Visible = true;
         Systolic->Marks->Visible = false;
         srs_p_systolic->Marks->Visible = false;
         srs_p_diastolic->Marks->Visible = false;
         Mean->Marks->Visible = false;
         Pulse->Marks->Visible = false;
         Augmentation->Marks->Visible = false;
      }
      else if (Series == srs_p_systolic)
      {
         Systolic->Marks->Visible = false;
         Diastolic->Marks->Visible = false;
         srs_p_systolic->Marks->Visible = true;
         srs_p_diastolic->Marks->Visible = false;
         Mean->Marks->Visible = false;
         Pulse->Marks->Visible = false;
         Augmentation->Marks->Visible = false;
      }
      else if (Series == srs_p_diastolic)
      {
         Diastolic->Marks->Visible = false;
         Systolic->Marks->Visible = false;
         srs_p_systolic->Marks->Visible = false;
         srs_p_diastolic->Marks->Visible = true;
         Mean->Marks->Visible = false;
         Pulse->Marks->Visible = false;
         Augmentation->Marks->Visible = false;
      }
      else if (Series == Mean)
      {
         Mean->Marks->Visible = true;
         Systolic->Marks->Visible = false;
         Diastolic->Marks->Visible = false;
         srs_p_systolic->Marks->Visible = false;
         srs_p_diastolic->Marks->Visible = false;
         Pulse->Marks->Visible = false;
         Augmentation->Marks->Visible = false;
      }
      else if (Series == Pulse)
      {
         Systolic->Marks->Visible = false;
         Mean->Marks->Visible = false;
         Diastolic->Marks->Visible = false;
         srs_p_systolic->Marks->Visible = false;
         srs_p_diastolic->Marks->Visible = false;
         Pulse->Marks->Visible = true;
         Augmentation->Marks->Visible = false;
      }
      else if (Series == Augmentation)
      {
         Systolic->Marks->Visible = false;
         Mean->Marks->Visible = false;
         Diastolic->Marks->Visible = false;
         srs_p_systolic->Marks->Visible = false;
         srs_p_diastolic->Marks->Visible = false;
         Pulse->Marks->Visible = false;
         Augmentation->Marks->Visible = true;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwa::srs_phrate_barGetMarkText(TChartSeries *Sender,
                            int ValueIndex, AnsiString &MarkText)
{
   TeeSplitInLines(MarkText, ",");
   if (clicked_series)
   {
      if (ValueIndex != series_index)
      {
         MarkText = "";
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwa::chrt_hrate_timingMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TChart *chart;
   chart = dynamic_cast<TChart *>(Sender);
   if (chart != NULL)
   {
      if (chart == chrt_hrate_timing)
      {
         if (Button == mbLeft)
         {
            chart->Series[1]->Marks->Style = smsValue;
         }
         else
         {
            chart->Series[1]->Marks->Style = smsLabel;
         }
      }
      chart->Series[1]->Marks->Visible = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwa::chrt_hrate_timingMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TChart *chart;

   chart = dynamic_cast<TChart *>(Sender);
   if (chart != NULL)
   {
      chart->Series[1]->Marks->Visible = false;
      if (chart->Series[1] == srs_thrate_line)
      {
         srs_taix_norm_bar->Marks->Visible = false;
         srs_taix_bar->Marks->Visible = false;
         srs_tedpc_bar->Marks->Visible = false;
         srs_tsvr_bar->Marks->Visible = false;
         srs_tap_bar->Marks->Visible = false;
      }
   }
   clicked_series = false;
   series_index = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwa::chrt_hrate_timingClickSeries(
      TCustomChart *Sender, TChartSeries *Series, int ValueIndex,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   clicked_series = true;
   series_index = ValueIndex;
   if (Series == srs_thrate_line)
   {
      if (trend_show_corresponding)
      {
         srs_taix_norm_bar->Marks->Visible = true;
         srs_taix_bar->Marks->Visible = true;
         srs_tedpc_bar->Marks->Visible = true;
         srs_tsvr_bar->Marks->Visible = true;
         srs_tap_bar->Marks->Visible = true;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwa::srs_thrate_barGetMarkText(TChartSeries *Sender,
      int ValueIndex, AnsiString &MarkText)
{
   TeeSplitInLines(MarkText, ",");
   if (clicked_series)
   {
      if (ValueIndex != series_index)
      {
         MarkText = "";
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwa::FormKeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_SPACE || Key == VK_RETURN)
   {
      Hide();
      frm_analysis_pwa->Caller = "Trend";
      frm_analysis_pwa->Show();
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwa::ClearSeries()
{
   AnsiString name_str("TChart");
   TChart     *chrt;
   int        i;

    for (i = 0; i < ComponentCount; i++)
    {
      if (Components[i]->ClassNameIs(name_str))
      {
        chrt = (TChart *)Components[i];
        if (chrt != NULL)
        {
           chrt->Series[0]->Clear();
           chrt->Series[1]->Clear();
           if (chrt == chrt_pressure)
           {
             chrt->Series[2]->Clear();
             chrt->Series[3]->Clear();
             chrt->Series[4]->Clear();
             chrt->Series[5]->Clear();
             chrt->Series[6]->Clear();
           }
        }
      }
    }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwa::ShowCharts(TStringList *pList, bool is_print)
{
  TChart               *chrt;
  TColor               series_color;
  TColor               axis_color;
  TColor               title_color;
  int                  total_records;
  int                  data_value;
  int                  i;
  int                  j;
  int                  k;
  int                  pressure_data[7];
  bool                 is_data_valid;
  double               scaler;
  AnsiString           date_str;
  AnsiString           name_str("TChart");
  CLINICAL_NORMALS_RANGE  range;

  Screen->Cursor = crHourGlass;

  // Prepare progress bar
  frm_main->prgbar_main->Visible = true;
  frm_main->prgbar_main->Min = 0;
  if (frm_analysis_pwa->analysis_qry->RecordCount > ANALYSIS_MAX_PWA_MEASUREMENTS)
  {
     frm_main->prgbar_main->Max = ANALYSIS_MAX_PWA_MEASUREMENTS;
  }
  else
  {
     frm_main->prgbar_main->Max = frm_analysis_pwa->analysis_qry->RecordCount;
  }
  if (pList->Count > ANALYSIS_MAX_PWA_MEASUREMENTS)
  {
     total_records = ANALYSIS_MAX_PWA_MEASUREMENTS;
  }
  else
  {
     total_records = pList->Count;
  }

  frm_main->prgbar_main->Step = 1;
  frm_main->prgbar_main->Position = 0;

  lbl_pat->Caption = patient_get_name();
  if (config_get_clinical_option())
  {
      lbl_art->Caption = "";
  }
  else
  {
      lbl_art->Caption = "  (" + frm_analysis_pwa->analysis_artery + " Arteries)";
  }
  lbl_first_last_trend->Caption = analysis_first_study +" - " +analysis_last_study;

   if (is_print)
   {
      axis_color = sphygmocor_black;
      title_color = sphygmocor_maroon;
   }
   else
   {
      axis_color = sphygmocor_white;
      title_color = sphygmocor_white;
   }

   for (i = 0; i < ComponentCount; i++)
   {
      if (Components[i]->ClassNameIs(name_str))
      {
         chrt = (TChart *)Components[i];
         chrt->LeftAxis->LabelsFont->Color = axis_color;
         chrt->LeftAxis->Title->Font->Color = axis_color;
         chrt->Title->Font->Color = title_color;
         chrt->PrintResolution = -100;
      }
   }
  // Looping selected measurements
  int nr = 0; int NofDrawn = 0; int corrupt_count = 0;
  for (frm_analysis_pwa->analysis_qry->Last(); !frm_analysis_pwa->analysis_qry->Bof && NofDrawn < ANALYSIS_MAX_PWA_MEASUREMENTS; frm_analysis_pwa->analysis_qry->Prior())
  {
    frm_main->prgbar_main->Position = nr++;
    if (pList->IndexOf(frm_analysis_pwa->analysis_qry->FieldByName(MPW_DATETIME)->AsDateTime.FormatString(ANALYSIS_DATETIME_FORMAT)) < 0)
    {
      continue;
    }
    if (frm_analysis_pwa->analysis_pwa->Populate(frm_analysis_pwa->analysis_qry)==false)
    {
      ++corrupt_count;
      continue;
    }
    j = 0;

    while (j < 8)
    {
      date_str = "";
      is_data_valid = true;
      series_color = clTeeColor;
      if (j == 0)
      {
         chrt = chrt_hrate_pressure;
         data_value = math_Round(frm_analysis_pwa->analysis_pwa->Central.HR);
         date_str = frm_analysis_pwa->analysis_pwa->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
      }
      else if (j == 1)
      {
         chrt = chrt_hrate_timing;
         data_value = math_Round(frm_analysis_pwa->analysis_pwa->Central.HR);
         date_str = frm_analysis_pwa->analysis_pwa->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
      }
      else if (j == 2)
      {
         chrt = chrt_pressure;
         pressure_data[0] = math_Round(frm_analysis_pwa->analysis_pwa->Periph.Sp);
         pressure_data[1] = math_Round(frm_analysis_pwa->analysis_pwa->Central.Sp);
         pressure_data[2] = math_Round(frm_analysis_pwa->analysis_pwa->Central.MeanP);
         pressure_data[3] = math_Round(frm_analysis_pwa->analysis_pwa->Central.Dp);
         pressure_data[4] = math_Round(frm_analysis_pwa->analysis_pwa->Periph.Dp);
         pressure_data[5] = math_Round(frm_analysis_pwa->analysis_pwa->Central.PH);
         pressure_data[6] = math_Round(frm_analysis_pwa->analysis_pwa->Central.AP);
      }
      else if (j == 3)
      {
         chrt = chrt_aix_norm;
         data_value = math_Round(frm_analysis_pwa->analysis_pwa->Central.AGPH_HR75);

         // The bar graph is displayed in colours that represent each values normal clinical range
         report_age = patient_get_age_at_date(frm_analysis_pwa->analysis_pwa->DateTime);
         range = report_determine_aixhr75_range(frm_analysis_pwa->analysis_pwa->Central.AGPH_HR75,
                                                report_age, frm_analysis_pwa->analysis_pwa->MeasureType);
         switch (range)
         {
            case RANGE_LOW:
            case RANGE_NORMAL_LOW:
            case RANGE_NORMAL_HIGH:
               series_color = sphygmocor_green;
               break;

            case RANGE_HIGH:
               series_color = sphygmocor_red;
               break;
         }
      }
      else if (j == 4)
      {
         chrt = chrt_edpc;
         data_value = math_Round(frm_analysis_pwa->analysis_pwa->Central.EDPeriod);

         // The bar graph is displayed in colours that represent each values normal clinical range
         range = report_determine_ed_range(frm_analysis_pwa->analysis_pwa->Central.EDPeriod, frm_analysis_pwa->analysis_pwa->Central.HR,
                                           report_age, frm_analysis_pwa->analysis_pwa->MeasureType);
         switch (range)
         {
            case RANGE_VERY_LOW:
            case RANGE_LOW:
               series_color = sphygmocor_yellow;
               break;

            case RANGE_NORMAL_LOW:
            case RANGE_NORMAL_HIGH:
               series_color = sphygmocor_green;
               break;

            case RANGE_HIGH:
            case RANGE_VERY_HIGH:
               series_color = sphygmocor_red;
               break;
         }

         // If the ED has been altered by the user, the value will appear pink
         if ((fabs(frm_analysis_pwa->analysis_pwa->Central.ED -
              frm_analysis_pwa->analysis_pwa->Central.CalcED) > 0.5))
         {
            series_color = sphygmocor_pink;
         }
      }
      else if (j == 5)
      {
         chrt = chrt_svr;
         data_value = math_Round(frm_analysis_pwa->analysis_pwa->Central.SVI);

         // The bar graph is displayed in colours that represent each values normal clinical range
         range = report_determine_sevr_range(frm_analysis_pwa->analysis_pwa->Central.SVI, frm_analysis_pwa->analysis_pwa->Central.HR,
                                             report_age, frm_analysis_pwa->analysis_pwa->MeasureType);
         switch (range)
         {
            case RANGE_LOW:
               series_color = sphygmocor_red;
               break;

            case RANGE_NORMAL_LOW:
               series_color = sphygmocor_yellow;
               break;

            case RANGE_NORMAL_HIGH:
            case RANGE_HIGH:
               series_color = sphygmocor_green;
               break;
         }
         // An SEVR less than 120% should always be abnormal
         // PM CR
         if (data_value < REPORT_SEVR_ABNORMAL)
         {
            series_color = sphygmocor_red;
         }

      }
      else if (j == 6)
      {
         chrt = chrt_ap;
         data_value = math_Round(frm_analysis_pwa->analysis_pwa->Central.AP);

         // The bar graph is displayed in colours that represent each values normal clinical range
         range = report_determine_ap_range(frm_analysis_pwa->analysis_pwa->Central.AP,
                                             report_age, frm_analysis_pwa->analysis_pwa->MeasureType);
         switch (range)
         {
            case RANGE_LOW:
            case RANGE_NORMAL_LOW:
            case RANGE_NORMAL_HIGH:
               series_color = sphygmocor_green;
               break;

            case RANGE_HIGH:
               series_color = sphygmocor_red;
               break;
         }
      }
      else if (j == 7)
      {
         chrt = chrt_aix;
         data_value = math_Round(frm_analysis_pwa->analysis_pwa->Central.AGPH);

         // The bar graph is displayed in colours that represent each values normal clinical range
         report_age = patient_get_age_at_date(frm_analysis_pwa->analysis_pwa->DateTime);
         range = report_determine_aix_range(frm_analysis_pwa->analysis_pwa->Central.AGPH,
                                                report_age, frm_analysis_pwa->analysis_pwa->MeasureType);
         switch (range)
         {
            case RANGE_LOW:
            case RANGE_NORMAL_LOW:
            case RANGE_NORMAL_HIGH:
               series_color = sphygmocor_green;
               break;

            case RANGE_HIGH:
               series_color = sphygmocor_red;
               break;
         }
      }
      if (j != 2)
      {
         for (k = 0; k < 2; k++)
         {
            if (data_value >= DEFAULT_VALUE)
            {
               is_data_valid = false;
            }
            if (is_data_valid)
            {
               if (k == 0)
               {
                  chrt->Series[k]->AddXY((total_records - NofDrawn),
                                         data_value,
                                         "", series_color);
               }
               else
               {
                  chrt->Series[k]->AddXY(total_records - NofDrawn,
                                         data_value,
                                         date_str, clTeeColor);
               }
            }
            else
            {
               ;
            }
         }
      }
      else
      {
         for (k = 0; k < nof_pressure_trends; k++)
         {
            if (pressure_data[k] >= DEFAULT_VALUE)
            {
                is_data_valid = false;
            }
            if (is_data_valid)
            {
                chrt->Series[k]->AddXY(total_records - NofDrawn,
                                       pressure_data[k],
                                       date_str, clTeeColor);
            }
            else
            {
               ;
            }
         }
      }
      ++j;
    }
    NofDrawn++;
  }

  for (i = 0; i < ComponentCount; i++)
  {
     if (Components[i]->ClassNameIs(name_str))
     {
        chrt = (TChart *)Components[i];
        chrt->BottomAxis->SetMinMax(0, chrt_hrate_pressure->Series[1]->MaxXValue() + 1);

        if (chrt->Series[1]->MinYValue() < 0)
        {
           scaler = 1.04;
        }
        else
        {
           scaler = 0.96;
        }

        if (chrt == chrt_pressure)
        {
           int max_pressure = chrt->Series[0]->MaxYValue();
           int min_pressure = chrt->Series[0]->MinYValue();
           for (k = 1; k < nof_pressure_trends; k++)
           {
                if (max_pressure < chrt->Series[k]->MaxYValue())
                        max_pressure = chrt->Series[k]->MaxYValue();
                if (min_pressure > chrt->Series[k]->MinYValue())
                        min_pressure = chrt->Series[k]->MinYValue();
           }
           chrt->LeftAxis->SetMinMax(min_pressure - 5, max_pressure + 5);
        }
        else if (chrt == chrt_ap || chrt == chrt_aix_norm || chrt == chrt_aix)
        {
           chrt->LeftAxis->SetMinMax(chrt->Series[1]->MinYValue() * scaler - 1,
                                     chrt->Series[1]->MaxYValue() * 1.04 + 1);
        }
        else
        {
           chrt->LeftAxis->SetMinMax(chrt->Series[1]->MinYValue() * scaler,
                                     chrt->Series[1]->MaxYValue() * 1.04);
        }
     }
  }
  trend_show_corresponding = false;
  if ((chrt_hrate_timing->Series[0]->Count() == chrt_ap->Series[0]->Count()) &&
      (chrt_hrate_timing->Series[0]->Count() == chrt_aix_norm->Series[0]->Count()))
  {
     trend_show_corresponding = true;
  }
  frm_main->prgbar_main->Visible = false;
  Screen->Cursor = crDefault;
}


void __fastcall Tfrm_trend_pwa::bbtn_printClick(TObject *Sender)
{
   int                  analysis_width;
   int                  analysis_height;
   int                  display_width;
   int                  display_height;
   int                  left_margin;
   TRect                print_rect;
   TStringList          *lList;
   TPrinterOrientation  old_orient;
   TPrinter             *printer_ptr;
   AnsiString           S;
   AnsiString           name_str("TChart");
   TChart               *chrt;
   int                  i;

   if (this->Visible)
   {
      if (MsgBox(MSG_PRINT_REPORT, CONFIRMATION, MB_YESNO | MB_ICONQUESTION) != ID_YES)
      {
         //SetFocus();
         return;
      }
   }
  Screen->Cursor = crHourGlass;

  lList =(frm_analysis_pwa->analysis_selected_measurements->Count > 0 ?
     frm_analysis_pwa->analysis_selected_measurements : frm_analysis_pwa->analysis_all_measurements);

  ClearSeries();
  ShowCharts(lList, true);

  printer_ptr = print_get_printer_ptr();
  if (printer_ptr==NULL)
  {
     return;
  }
  old_orient = printer_ptr->Orientation;
  printer_ptr->Orientation  = poPortrait;
  printer_ptr->Title = "SphygmoCor PWA Trend";

  // PM V9
  try
  {
     printer_ptr->BeginDoc();

     analysis_width =  printer_ptr->PageWidth;
     analysis_width = analysis_width - (analysis_width * 0.02);
     left_margin = analysis_width * 0.06;
     analysis_height = printer_ptr->PageHeight;

     print_rect.Top = analysis_height * 0.9;
     print_rect.Left = left_margin;
     print_rect.Right = analysis_width;
     print_rect.Bottom = analysis_height;
     print_do_footer(&print_rect, 0);

     print_rect.Top = analysis_height * 0.1;
     print_rect.Left = left_margin;
     print_rect.Right = analysis_width;
     print_rect.Bottom = analysis_height * 0.15;
     print_do_header(&print_rect, "SphygmoCor", "Patient Trend Analysis");
     print_do_atcor_image(&print_rect);

     print_rect.Top = print_rect.Bottom;
     print_rect.Left = left_margin;
     print_rect.Right = analysis_width;
     print_rect.Bottom = analysis_height * 0.25;
     print_do_patient_data(&print_rect, 0, false, "", "", false);

     print_rect.Top = print_rect.Bottom;
     print_rect.Left = left_margin;
     print_rect.Right = analysis_width;
     print_rect.Bottom = analysis_height * 0.30;
     analysis_print_study_data(&print_rect);

     for (i = 0; i < ComponentCount; i++)
     {
        if (Components[i]->ClassNameIs(name_str))
        {
           chrt = (TChart *)Components[i];
           if (chrt == chrt_hrate_pressure)
           {
              print_rect.Top = 0.30 * analysis_height;
              print_rect.Left = left_margin;
              print_rect.Right = left_margin + (analysis_width - left_margin) * 0.48;
              print_rect.Bottom = analysis_height * 0.42;
           }
           else if (chrt == chrt_pressure)
           {
              print_rect.Top = analysis_height * 0.42;
              print_rect.Left = left_margin;
              print_rect.Right = left_margin + (analysis_width - left_margin) * 0.48;
              print_rect.Bottom = analysis_height * 0.90;

           }
           else if (chrt == chrt_hrate_timing)
           {
              print_rect.Top = 0.30 * analysis_height;
              print_rect.Left = left_margin + (analysis_width - left_margin) * 0.52;
              print_rect.Right = analysis_width;
              print_rect.Bottom = analysis_height * 0.42;
           }
           else if (chrt == chrt_ap)
           {
              print_rect.Top = analysis_height * 0.42;
              print_rect.Left = left_margin + (analysis_width - left_margin) * 0.52;
              print_rect.Right = analysis_width;
              print_rect.Bottom = analysis_height * 0.54;
           }
           else if (chrt == chrt_aix_norm)
           {
              print_rect.Top = analysis_height * 0.54;
              print_rect.Left = left_margin + (analysis_width - left_margin) * 0.52;
              print_rect.Right = analysis_width;
              print_rect.Bottom = analysis_height * 0.66;
           }
           else if (chrt == chrt_edpc)
           {
              print_rect.Top = analysis_height * 0.66;
              print_rect.Left = left_margin + (analysis_width - left_margin) * 0.52;
              print_rect.Right = analysis_width;
              print_rect.Bottom = analysis_height * 0.78;
           }
           else if (chrt == chrt_svr)
           {
              print_rect.Top = analysis_height * 0.78;
              print_rect.Left = left_margin + (analysis_width - left_margin) * 0.52;
              print_rect.Right = analysis_width;
              print_rect.Bottom = analysis_height * 0.90;
           }
           else if (chrt == chrt_aix)
           {
              print_rect.Top = analysis_height * 0.66;
              print_rect.Left = left_margin + (analysis_width - left_margin) * 0.52;
              print_rect.Right = analysis_width;
              print_rect.Bottom = analysis_height * 0.78;
           }
           if (chrt->Visible)
           {
               display_height = chrt->Height;
               display_width = chrt->Width;
               if (chrt == chrt_pressure)
               {
                  chrt->Height = ANALYSIS_PRESSURE_PRINT_HEIGHT;
                  chrt->Width = ANALYSIS_PRESSURE_PRINT_WIDTH;
               }
               else
               {
                  chrt->Height = ANALYSIS_CHART_PRINT_HEIGHT;
                  chrt->Width = ANALYSIS_CHART_PRINT_WIDTH;
               }
               chrt->PrintPartial(print_rect);
               chrt->Height = display_height;
               chrt->Width = display_width;
           }
        }
     }
     printer_ptr->EndDoc();
  }
  catch (Exception &exception)
  {
    printer_ptr->Abort();
    printer_ptr->EndDoc();
  }
  printer_ptr->Orientation = old_orient;
  Screen->Cursor = crDefault;

  ClearSeries();
  ShowCharts(lList, false);
  //SetFocus();   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_trend_pwa::bbtn_waveClick(TObject *Sender)
{
   Hide();
   char keypress = VK_SPACE;
   FormKeyPress(Sender, keypress);   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_trend_pwa::bbtn_exportClick(TObject *Sender)
{
   Graphics::TBitmap*   bmp_image;
   PATIENT_RECORD_TYPE  pat;
   AnsiString           reptype_str = "TREND_";

   try
   {
      bmp_image = GetFormImage();
      if (bmp_image != NULL)
      {
         if (patient_get(&pat))
         {
            String attach_fname = ExtractFilePath(Application->ExeName) +EXPORT_SUBDIR +"PIC_" +reptype_str +pat.surname +"_"
                      +analysis_first_export +"_" +analysis_last_export +"_pwa.jpg";
            export_graphic(bmp_image, attach_fname);
         }
         delete bmp_image;
      }
   }
   catch (...)
   {
      (void)MsgBox_warning("Could Not Create Graphic.",
                           SWARNING);
   }
}
//---------------------------------------------------------------------------


