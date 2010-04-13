#include <vcl.h>
#include <vcl/dstring.h>
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include <stdlib.h>
#include <math.h>
#include <dbmgr/pubserv.h>
#include <multdb/pubserv.h>
#include <log/pubserv.h>
#include <patient/pubserv.h>
#include <meas/pubserv.h>
#include <msg/pubserv.h>
#include <config/pubserv.h>
#include <print/pubserv.h>
#include <export/pubserv.h>
#include <scor/form_main.h>
#include <report/pubserv.h>
#include <scor/utils.h>
#include "form_report_pwm.h"
#include "form_report_pwa.h"
#include "report.h"
#include "attrib.h"
#include <Math.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
Tfrm_report_pwm *frm_report_pwm;
//---------------------------------------------------------------------------
const float CHART_MARGIN = 10; // Percent of vertical margin for a chart
const String REPORT_PWV_SESSION_TIME_FORMAT = "hh:mm:ss";
int series_event_index;
const int REPORT_PANEL_TREND_PRINT_HEIGHT = 317;
const int REPORT_PANEL_TREND_PRINT_WIDTH = 646;
//---------------------------------------------------------------------------
bool report_pwm_batch_print(TPWM                *pwm_info,
                            PATIENT_RECORD_TYPE *patient)
{
   // If the PWM form has not been created we need to create it.
   (void)report_get_form_pointer();

   if (frm_report_pwm == NULL)
   {
      return false;
   }
   frm_report_pwm->pwm = pwm_info;

   frm_report_pwm->ClearSeries();

   patient_set(patient);
   report_age = 0;
   frm_report_pwm->report_display_study();
   frm_report_pwm->bbtn_printClick(Application);

   return true;
}

//---------------------------------------------------------------------------
__fastcall Tfrm_report_pwm::Tfrm_report_pwm(TComponent* Owner)
    : Child_Form(Owner)
{
   ChartHRTitle = ChartHR->Title->Text->Strings[0];
   ChartSEVRTitle = ChartSEVR->Title->Text->Strings[0];
   ChartEDTitle = ChartED->Title->Text->Strings[0];
   ChartAITitle = ChartAI->Title->Text->Strings[0];
   series_event_index = -1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwm::FormShow(TObject *Sender)
{
   TDataSource          *dsrc_report;
   PATIENT_RECORD_TYPE  pat;

   pwm = meas_get_current_pwm();
   ClearSeries();
   report_age = 0;
   FRecNo = 0;
   if (patient_get(&pat))
   {
      if (ChartPressures != NULL)
      {
         ChartPressures->UndoZoom();
      }
      dsrc_report = dbmgr_get_data_source(DBMGR_MEASURE_PWM_SESSION_QUERY, false);
      dsrc_report->AutoEdit = false;

      report_qry = dbmgr_setup_query(DBMGR_MEASURE_PWM_SESSION_TABLE,
                                     DBMGR_QUERY_KEY,
                                     PATIENT_SYSTEM_ID,
                                     PATIENT_STUDY_ID,
                                     PATIENT_NO,
                                     pat.system_id,
                                     pat.study_id,
                                     IntToStr(pat.number),
                                     MPWM_SESSION_START);

      if ((report_qry != NULL) && report_qry->RecordCount > 0)
      {
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
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwm::FormHide(TObject *Sender)
{
   if (grd_report->DataSource != NULL)
   {
      grd_report->DataSource->OnDataChange = NULL;
   }
   if (report_qry != NULL)
   {
      report_qry->Close();
   }
   if (frm_report_pwa->Visible)
   {
      frm_report_pwa->Hide();
   }
   ClearSeries();
   FRecNo = 0;

   emma_display_statusbar_message("", "", "", sphygmocor_white);
   emma_display_statusbar_message("", "", sphygmocor_white);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwm::record_changed(TObject *Sender, TField  *Field)
{
  try
  {
    if (ChartPressures == NULL)
    {
       return;
    }
    Screen->Cursor = crHourGlass;
    edt_event_comment->Text = "";
    pnl_event_comment->Visible = false;
    if (report_qry != NULL)
    {
      if (report_qry->RecordCount > 0)
      {
         if (FRecNo != report_qry->FieldByName(MPWM_SESSION_ID)->AsInteger)
         {
           FRecNo = report_qry->FieldByName(MPWM_SESSION_ID)->AsInteger;
           ClearSeries();
           if (pwm->PopulateSession(report_qry)==true)
           {
              lbl_assessments_title->Caption = " Assessment "
                                                      + IntToStr(report_qry->RecNo) + " of "
                                                      + IntToStr(report_qry->RecordCount);
              bbtn_print->Enabled = true;
              report_display_study();
              if (pwm->TrendSamplePeriod)
              {
                 report_display_trends();
              }
              else
              {
                 ChartHR->Title->Text->Clear();
                 ChartHR->Title->Text->Add("Heart Rate (No Trend)");
                 ChartSEVR->Title->Text->Clear();
                 ChartSEVR->Title->Text->Add("SEVR (No Trend)");
                 ChartED->Title->Text->Clear();
                 ChartED->Title->Text->Add("Ejection Duration (No Trend)");
                 ChartAI->Title->Text->Clear();
                 ChartAI->Title->Text->Add("AIx (No Trend)");
              }
           }
           else
           {
              bbtn_print->Enabled = false;
           }
         }
      }
    }
  }
  catch (Exception &e)
  {
    Application->ShowException(&e);
  }
  Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void Tfrm_report_pwm::ClearSeries()
{
  if (ChartPressures == NULL)
  {
     return;
  }
  for (int np = 0; np < ChartPressures->SeriesCount(); np++)
  {
    ChartPressures->Series[np]->Clear();
  }
  for (int np = 0; np < ChartHR->SeriesCount(); np++)
  {
    ChartHR->Series[np]->Clear();
  }
  for (int np = 0; np < ChartSEVR->SeriesCount(); np++)
  {
    ChartSEVR->Series[np]->Clear();
  }
  for (int np = 0; np < ChartED->SeriesCount(); np++)
  {
    ChartED->Series[np]->Clear();
  }
  for (int np = 0; np < ChartAI->SeriesCount(); np++)
  {
    ChartAI->Series[np]->Clear();
  }
  ChartPressures->UndoZoom();
}
// PM CR
//---------------------------------------------------------------------------
void Tfrm_report_pwm::report_display_patient_info(PATIENT_RECORD_TYPE  *pat)
{
  lbl_pname->Caption = patient_get_name();
  lbl_pid->Caption = pat->id;
  lbl_pcode->Caption = pat->code;
  lbl_address1->Caption = pat->street;
  lbl_address2->Caption = pat->suburb + " " + pat->state + " " + pat->pcode;
  lbl_address3->Caption = pat->country;
  lbl_birth_date->Caption = pat->dob.FormatString(REPORT_PAT_DOB_DATE_FORMAT);
  lbl_sex->Caption = pat->sex;}
//---------------------------------------------------------------------------
void Tfrm_report_pwm::report_display_study()
{
   TFloatFormat format = ffGeneral;

   lbl_session_date->Caption = pwm->SessionStart.FormatString(REPORT_PAT_DOB_DATE_FORMAT) + ", " +
                       pwm->SessionStart.FormatString(REPORT_PWV_SESSION_TIME_FORMAT) + " - " +
                       pwm->SessionFinished.FormatString(REPORT_PAT_DOB_DATE_FORMAT) + ", " +
                       pwm->SessionFinished.FormatString(REPORT_PWV_SESSION_TIME_FORMAT);
   TDateTime lSessionDuration = pwm->SessionFinished - pwm->SessionStart;
   lbl_session_date->Hint = "Duration : " + lSessionDuration.FormatString(REPORT_PWV_SESSION_TIME_FORMAT);

   report_age = patient_get_age_at_date(pwm->SessionStart);
   lbl_age->Caption = IntToStr(report_age);

   edt_med->Text = MsgBox_ReplaceCarriage(pwm->Medication.SubString(1, REPORT_MAX_PRINTED_MEMO_LENGTH));
   edt_notes->Text = MsgBox_ReplaceCarriage(pwm->Notes.SubString(1, REPORT_MAX_PRINTED_MEMO_LENGTH));
   lbl_operator->Caption = pwm->Operator;
   if (pwm->Height > 0 && pwm->Height != DEFAULT_VALUE &&
       pwm->Weight > 0 && pwm->Weight != DEFAULT_VALUE &&
       pwm->Bmi > 0 && pwm->Bmi != DEFAULT_VALUE &&
       config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
     lbl_hwbmi->Caption = RoundIntToStr(pwm->Height) + "cm, " +
                                        RoundIntToStr(pwm->Weight) + "kg (" +
                                        FormatFloat("0.0#", pwm->Bmi) + "kg/m�)";
   }
   else if (pwm->Height > 0 && pwm->Height != DEFAULT_VALUE &&
         config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(pwm->Height) + "cm";
   }
   else if (pwm->Weight > 0 && pwm->Weight != DEFAULT_VALUE &&
         config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(pwm->Weight) + "kg";
   }
   else if (pwm->Feet >= 0 && pwm->Feet != DEFAULT_VALUE &&
            pwm->Inch >= 0 && pwm->Inch != DEFAULT_VALUE &&
            pwm->Pound > 0 && pwm->Pound != DEFAULT_VALUE &&
            pwm->Bmi > 0 && pwm->Bmi != DEFAULT_VALUE &&
            config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(pwm->Feet) + "ft, " +
                                        RoundIntToStr(pwm->Inch) + "in, " +
                                        RoundIntToStr(pwm->Pound) + "lb (" +
                                        FormatFloat("0.##", pwm->Bmi) + " kg/m�)";
   }
   else if (pwm->Feet >= 0 && pwm->Feet != DEFAULT_VALUE &&
            pwm->Inch >= 0 && pwm->Inch != DEFAULT_VALUE &&
            config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(pwm->Feet) + "ft, " +
                                        RoundIntToStr(pwm->Inch) + "in";
   }
   else if (pwm->Pound > 0 && pwm->Pound != DEFAULT_VALUE &&
            config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(pwm->Pound) + "lb";
   }
   else
   {
     lbl_hwbmi->Caption = "";
   }

   // Calibrated
   if (pwm->Calibrated == false)
   {
     lbl_calibrated_title->Caption = "Calibrated by Sp/Dp (Mp):";
     lbl_calibration_ratio->Visible = false;
     lbl_ratio->Visible = false;
     lbl_calibration_offset->Visible = false;
     lbl_offset->Visible = false;

     // Sp, Dp, Mp
     if (pwm->Sp > 0 && pwm->Sp != DEFAULT_VALUE &&
        pwm->Dp > 0 && pwm->Dp != DEFAULT_VALUE)
     {
        lblSpDpMp->Caption = RoundIntToStr(pwm->Sp) + "/" +
                             RoundIntToStr(pwm->Dp) + " (-)";
     }
     else if (pwm->MeanP > 0 && pwm->MeanP != DEFAULT_VALUE &&
              pwm->Dp > 0 && pwm->Dp != DEFAULT_VALUE)
     {
        lblSpDpMp->Caption = "-/" + RoundIntToStr(pwm->Dp) + " (" +
                             RoundIntToStr(pwm->MeanP) + ")";
     }
     else
     {
        lblSpDpMp->Caption = "";
     }
   }
   else
   {
     // Display the device name, calibration ratio and calibration offset.
     lbl_calibrated_title->Caption = "Calibrated by device:";
     lblSpDpMp->Caption = pwm->DeviceName;
     lbl_calibration_ratio->Visible = true;
     lbl_ratio->Visible = true;
     lbl_ratio->Caption = FloatToStrF(pwm->CalibrationRatio, format, 4, 0);
     lbl_calibration_offset->Visible = true;
     lbl_offset->Visible = true;
     lbl_offset->Caption = FloatToStr(pwm->CalibrationOffset);
   }

   // PM V9
   // Display the simulation label on the status bar
   if (pwm->Simulation)
   {
      emma_display_statusbar_message(SIMULATION, SIMULATION_NOTE, sphygmocor_maroon);
   }
   else
   {
      emma_display_statusbar_message("", "", sphygmocor_white);
   }
}

//---------------------------------------------------------------------------
void Tfrm_report_pwm::report_display_trends()
{
   int     max_pressure;
   int     min_pressure;
   bool    series_found = true;

   TADOTable* pTrendTable = dynamic_cast<TADOTable *> (dbmgr_get_dataset(DBMGR_MEASURE_PWM_TREND_TABLE, false));
   if (pTrendTable == NULL)
   {
      return;
   }
   try
   {
      if (pTrendTable->Active)
      {
         pTrendTable->Close();
      }
      pTrendTable->Open();
      if (pTrendTable->Active)
      {
          max_pressure = 0;
          min_pressure = 100;
          for (int np = 0; np < 8; np++)
          {
             if (np != 5 && np != 6)
             {
                if (pwm->CreateTrendSeries(pTrendTable, ChartPressures->Series[np]))
                {
                   if (max_pressure < ChartPressures->Series[np]->MaxYValue())
                   {
                      max_pressure = ChartPressures->Series[np]->MaxYValue();
                   }
                   if (min_pressure > ChartPressures->Series[np]->MinYValue())
                   {
                      min_pressure = ChartPressures->Series[np]->MinYValue();
                   }
                }
                else
                {
                   series_found = false;
                }
             }
          }
          if (!series_found)
          {
             max_pressure = 250;
             min_pressure = 0;
          }
          if (ChartPressures != NULL)
          {
             if (min_pressure >= 10)
             {
                min_pressure = 0;
             }
             ChartPressures->LeftAxis->SetMinMax(min_pressure - 5, max_pressure + 5);
          }
          SetChart(ChartHR, ChartHRTitle, pTrendTable);
          SetChart(ChartSEVR, ChartSEVRTitle, pTrendTable);
          SetChart(ChartED, ChartEDTitle, pTrendTable);
          SetChart(ChartAI, ChartAITitle, pTrendTable);
          pwm->CreateTrendSeries(pTrendTable, ptsrs_event_marker);

          pTrendTable->Close();

          if (!series_found)
          {
             MsgBox("A problem was detected when loading the trend parameters from the database.\n\nTo reduce the risk of data corruption it is advisable that you CLOSE and RESTART SphygmoCor.", SWARNING, MB_ICONEXCLAMATION);
          }
          // Create PP series on-fly
          int lNof = min(srs_periph_sp->Count(), srs_periph_dp->Count());
          for (int i=0; i<lNof; i++)
          {
             if (srs_periph_sp->YValue[i] != NULL && srs_periph_dp->YValue[i] != NULL)
             {
                srs_periph_pp->AddXY((i+1)*pwm->TrendSamplePeriod / 60.,
                                     srs_periph_sp->YValue[i] - srs_periph_dp->YValue[i],
                                     "", srs_periph_pp->SeriesColor);
             }
             else
             {
                srs_periph_pp->AddNullXY((i+1)*pwm->TrendSamplePeriod / 60.,
                                         0., "");
             }
          }
          // Central pp
          lNof = min(srs_central_sp->Count(), srs_central_dp->Count());
          for (int i=0; i<lNof; i++)
          {
             if (srs_central_sp->YValue[i] != NULL && srs_central_dp->YValue[i]!=NULL)
             {
                srs_central_pp->AddXY((i+1)*pwm->TrendSamplePeriod / 60.,
                                      srs_central_sp->YValue[i] - srs_central_dp->YValue[i],
                                      "", srs_central_pp->SeriesColor);
             }
             else
             {
                srs_central_pp->AddNullXY((i+1)*pwm->TrendSamplePeriod / 60.,
                                           0., "");
             }
          }
      }
   }
   catch (Exception &e)
   {
      MsgBox_show(TERROR,
                  MSG_EXCEPTION,
                  LoadStr(MSG_POP_EXC),
                  MSG_POP_EXC,
                  LoadStr(MSG_POP_EXC) +GetCurrentPwmMeasureDetails() +e.Message);
   }
   pTrendTable->Close();
}

//---------------------------------------------------------------------------
bool Tfrm_report_pwm::SetChart(TChart *pChart, const String pTitle, TDataSet *pTrendTable)
{
  String lSubTitle = "?";
  bool   found = true;
  float lAv, lDev;
  if (pwm->CreateTrendSeries(pTrendTable, pChart->Series[0]))
  {
    CalcMeanAndDev(pChart->Series[0], lAv, lDev);
    lSubTitle = FormatFloat("##0.0", lAv) + " � " + FormatFloat("##0.0", lDev);

    /*
    float lMargin = (pChart->Series[0]->MaxYValue() - pChart->Series[0]->MinYValue())
                    *CHART_MARGIN/(100. - 2*CHART_MARGIN);
    pChart->LeftAxis->SetMinMax(pChart->Series[0]->MinYValue() - lMargin,
                                pChart->Series[0]->MaxYValue() + lMargin);
    */
  }
  else
  {
     found = false;
  }
  pChart->Title->Text->Strings[0] = pTitle + ": " + lSubTitle;
  return found;
}
//---------------------------------------------------------------------------
// PM CR
void Tfrm_report_pwm::print_report_header(TRect *print_area)
{
   print_do_header(print_area, "SphygmoCor", "Pulse Wave Monitoring Session Report");
}
//---------------------------------------------------------------------------
void Tfrm_report_pwm::print_report_patient(TRect *print_area)
{
   print_do_patient_data(print_area, report_age, false, "", "", pwm->Simulation);
}
//---------------------------------------------------------------------------

void Tfrm_report_pwm::print_report_session(TPrinter *print_ptr, TRect *print_area)
{
   int          text_width;
   int          xpos;
   int          ypos;
   AnsiString   S;
   TFontStyles  font_style;

   TFontStyles  bold_font;
   bold_font.Clear();
   bold_font << fsBold;

   TFontStyles  normal_font;
   normal_font.Clear();

   font_style << fsBold;
   S = "SESSION DATA";
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 12;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top,
                              S);

   ypos = print_area->Top + print_ptr->Canvas->TextHeight(S);

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;


   S = lbl_session_date->Caption +"     ";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
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
   S = "Medication:    ";
   text_width = print_ptr->Canvas->TextWidth(S);

   S = lbl_calibrated_title->Caption;
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(print_area->Left,
                              ypos,
                              S);

   font_style << fsBold;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left + print_ptr->Canvas->TextWidth(S),
                              ypos,
                              lblSpDpMp->Caption);

   // Print calibration ratio and calibration offset also.
   if (pwm->Calibrated == true)
   {
      font_style.Clear();
      print_ptr->Canvas->Font->Style = font_style;
      S = lbl_calibration_ratio->Caption;
      ypos = ypos + print_ptr->Canvas->TextHeight(S);
      print_ptr->Canvas->TextOut(print_area->Left,
                              ypos,
                              S);

      font_style << fsBold;
      print_ptr->Canvas->Font->Style = font_style;
      print_ptr->Canvas->TextOut(print_area->Left + print_ptr->Canvas->TextWidth(S),
                              ypos,
                              lbl_ratio->Caption);

      font_style.Clear();
      print_ptr->Canvas->Font->Style = font_style;
      S = lbl_calibration_offset->Caption;
      ypos = ypos + print_ptr->Canvas->TextHeight(S);
      print_ptr->Canvas->TextOut(print_area->Left,
                              ypos,
                              S);

      font_style << fsBold;
      print_ptr->Canvas->Font->Style = font_style;
      print_ptr->Canvas->TextOut(print_area->Left + print_ptr->Canvas->TextWidth(S),
                              ypos,
                              lbl_offset->Caption);
   }

   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;
   S = "Operator ID: ";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(print_area->Left,
                              ypos,
                              S);
   font_style << fsBold;
   print_ptr->Canvas->Font->Style = font_style;
   S = lbl_operator->Caption;
   print_ptr->Canvas->TextOut(print_area->Left + text_width,
                              ypos,
                              S);

   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;
   S = "Medication:    ";
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

//---------------------------------------------------------------------------
void Tfrm_report_pwm::print_report_footer(TRect *print_area)
{
  print_do_footer(print_area, pwm->DataRev);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwm::FormKeyPress(TObject *Sender, char &Key)
{
  if (Key == VK_ESCAPE)
  {
    frm_main->spdbtn_patientClick(Sender);
  }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwm::CalcMeanAndDev(TChartSeries* pSeries, float &av, float &dev, float coeff, bool yValue)
{
  static double lValues[30000];
  int size = (pSeries->Count() < 30000 ? pSeries->Count() : 30000);
  int j = 0;
  for (int i=0; i < size; i++)
  {
      if (yValue)
      {
         if (pSeries->YValues->Value[i] != NULL && pSeries->YValues->Value[i] != 0)
         {
            lValues[j] = pSeries->YValues->Value[i] * coeff;
            ++j;
         }
      }
      else
      {
         lValues[i] = pSeries->XValues->Value[i] * coeff;
      }
  }
  if (yValue)
  {
     size = j;
  }
  long double lav = 0., ldev = 0.;
  MeanAndStdDev(lValues, size-1, lav, ldev);
  av = lav; dev = ldev;
}


void __fastcall Tfrm_report_pwm::ChartPressuresZoom(TObject *Sender)
{
   TRect       zoom_rect;

   ChartPressures->ClipPoints = true;
   ChartHR->ClipPoints = true;
   ChartED->ClipPoints = true;
   ChartSEVR->ClipPoints = true;
   ChartAI->ClipPoints = true;

   zoom_rect.Top = ChartHR->LeftAxis->CalcYPosValue(ChartHR->LeftAxis->Maximum);
   zoom_rect.Bottom = ChartHR->LeftAxis->CalcYPosValue(ChartHR->LeftAxis->Minimum);
   zoom_rect.Left = ChartHR->BottomAxis->CalcXPosValue(ChartPressures->BottomAxis->Minimum);
   zoom_rect.Right = ChartHR->BottomAxis->CalcXPosValue(ChartPressures->BottomAxis->Maximum);
   ChartHR->ZoomRect(zoom_rect);

   zoom_rect.Top = ChartSEVR->LeftAxis->CalcYPosValue(ChartSEVR->LeftAxis->Maximum);
   zoom_rect.Bottom = ChartSEVR->LeftAxis->CalcYPosValue(ChartSEVR->LeftAxis->Minimum);
   zoom_rect.Left = ChartSEVR->BottomAxis->CalcXPosValue(ChartPressures->BottomAxis->Minimum);
   zoom_rect.Right = ChartSEVR->BottomAxis->CalcXPosValue(ChartPressures->BottomAxis->Maximum);
   ChartSEVR->ZoomRect(zoom_rect);

   zoom_rect.Top = ChartED->LeftAxis->CalcYPosValue(ChartED->LeftAxis->Maximum);
   zoom_rect.Bottom = ChartED->LeftAxis->CalcYPosValue(ChartED->LeftAxis->Minimum);
   zoom_rect.Left = ChartED->BottomAxis->CalcXPosValue(ChartPressures->BottomAxis->Minimum);
   zoom_rect.Right = ChartED->BottomAxis->CalcXPosValue(ChartPressures->BottomAxis->Maximum);
   ChartED->ZoomRect(zoom_rect);

   zoom_rect.Top = ChartAI->LeftAxis->CalcYPosValue(ChartAI->LeftAxis->Maximum);
   zoom_rect.Bottom = ChartAI->LeftAxis->CalcYPosValue(ChartAI->LeftAxis->Minimum);
   zoom_rect.Left = ChartAI->BottomAxis->CalcXPosValue(ChartPressures->BottomAxis->Minimum);
   zoom_rect.Right = ChartAI->BottomAxis->CalcXPosValue(ChartPressures->BottomAxis->Maximum);
   ChartAI->ZoomRect(zoom_rect);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwm::ChartPressuresUndoZoom(TObject *Sender)
{
   ChartHR->UndoZoom();
   ChartSEVR->UndoZoom();
   ChartED->UndoZoom();
   ChartAI->UndoZoom();
}
//---------------------------------------------------------------------------
// PM CR


void __fastcall Tfrm_report_pwm::spbtn_reject_commentsClick(
      TObject *Sender)
{
   // Place the original event comment back in the edit box and hide the event comment panel.
   edt_event_comment->Text = pwm->GetMarkerString(pwm->event_comment->Strings[series_event_index]);
   pnl_event_comment->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwm::spbtn_accept_commentsClick(
      TObject *Sender)
{
   int event_pulse;

   // Save the changes to database.
   event_pulse = pwm->GetMarkerIndicator(pwm->event_comment->Strings[series_event_index]);
   if (event_pulse >= 0)
   {
      pwm->event_comment->Strings[series_event_index] = IntToStr(event_pulse) +"-" +edt_event_comment->Text;
      if (pwm->UpdateEventComments(report_qry))
      {
         pnl_event_comment->Visible = false;
      }
      else
      {
         edt_event_comment->Text = pwm->GetMarkerString(pwm->event_comment->Strings[series_event_index]);
      }
   }
   else
   {
      edt_event_comment->Text = pwm->GetMarkerString(pwm->event_comment->Strings[series_event_index]);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwm::ptsrs_event_markerClick(
      TChartSeries *Sender, int ValueIndex, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
   // Display the event comment and session time.
   if (pwm->event_comment->Count)
   {
      ptsrs_event_marker->Marks->Visible = true;
      series_event_index = ValueIndex;
      pnl_event_comment->Visible = false;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwm::ptsrs_event_markerGetMarkText(
      TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   // Set the event comment to be displayed.
   if (ValueIndex == series_event_index)
   {
      if (ValueIndex < pwm->event_comment->Count)
      {
         MarkText = pwm->event_comment->Strings[ValueIndex];
      }
   }
   else
   {
      MarkText = "";
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwm::ptsrs_event_markerDblClick(
      TChartSeries *Sender, int ValueIndex, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
   // Display the event comment panel and string.
   if (pwm->event_comment->Count)
   {
      if (ValueIndex < pwm->event_comment->Count)
      {
         pnl_event_comment->Visible = true;
         edt_event_comment->Text = pwm->GetMarkerString(pwm->event_comment->Strings[ValueIndex]);
         series_event_index = ValueIndex;
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwm::ChartPressuresMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   // Clear the event comment mark
   ptsrs_event_marker->Marks->Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_report_pwm::pnl_trendResize(TObject *Sender)
{
   ChartSEVR->Height = pnl_trend_timing->Height/4;
   ChartED->Height = pnl_trend_timing->Height/4;
   ChartAI->Height = pnl_trend_timing->Height/4;

   ChartPressures->Width = pnl_trend->Width/2;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwm::bbtn_printClick(TObject *Sender)
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
      if (MsgBox(MSG_PRINT_REPORT, CONFIRMATION, MB_YESNO | MB_ICONQUESTION) != ID_YES)
      {
        return;
      }
   }
   Screen->Cursor = crHourGlass;
   printer_ptr = print_get_printer_ptr();
   old_orient = printer_ptr->Orientation;
   printer_ptr->Orientation  = poPortrait;
   printer_ptr->Title = "SphygmoCor PWM Report";
   try
   {
       // PM CR
       ChartPressures->UndoZoom();

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
       print_rect.Bottom = report_height * 0.45;
       print_report_session(printer_ptr, &print_rect);

       // Set the charts to the size displayed in 600x800 resolution
       pnl_trend->Align = alNone;
       pnl_trend->Height = REPORT_PANEL_TREND_PRINT_HEIGHT;
       pnl_trend->Width = REPORT_PANEL_TREND_PRINT_WIDTH; 

       print_rect.Top = report_height * 0.46;
       print_rect.Left = left_margin;
       print_rect.Right = report_width * 0.48;
       print_rect.Bottom = report_height * 0.86;
       ChartPressures->PrintResolution = -100;
       ChartPressures->BottomAxis->LabelsFont->Color = sphygmocor_black;
       ChartPressures->BottomAxis->Title->Font->Color = sphygmocor_black;
       ChartPressures->LeftAxis->LabelsFont->Color = sphygmocor_black;
       ChartPressures->LeftAxis->Title->Font->Color = sphygmocor_black;
       ChartPressures->Title->Font->Color = sphygmocor_maroon;
       ChartPressures->PrintPartial(print_rect);

       print_rect.Top = report_height * 0.46;
       print_rect.Left = report_width * 0.52;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.56;
       ChartHR->PrintResolution = -100;                     
       ChartHR->BottomAxis->LabelsFont->Color = sphygmocor_black;
       ChartHR->BottomAxis->Title->Font->Color = sphygmocor_black;
       ChartHR->LeftAxis->LabelsFont->Color = sphygmocor_black;
       ChartHR->LeftAxis->Title->Font->Color = sphygmocor_black;
       ChartHR->Title->Font->Color = sphygmocor_maroon;
       ChartHR->PrintPartial(print_rect);

       print_rect.Top = report_height * 0.56;
       print_rect.Left = report_width * 0.52;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.66;
       ChartSEVR->PrintResolution = -100;
       ChartSEVR->LeftAxis->LabelsFont->Color = sphygmocor_black;
       ChartSEVR->LeftAxis->Title->Font->Color = sphygmocor_black;
       ChartSEVR->Title->Font->Color = sphygmocor_maroon;
       ChartSEVR->PrintPartial(print_rect);

       print_rect.Top = report_height * 0.66;
       print_rect.Left = report_width * 0.52;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.76;
       ChartED->PrintResolution = -100;
       ChartED->LeftAxis->LabelsFont->Color = sphygmocor_black;
       ChartED->LeftAxis->Title->Font->Color = sphygmocor_black;
       ChartED->Title->Font->Color = sphygmocor_maroon;
       ChartED->PrintPartial(print_rect);

       print_rect.Top = report_height * 0.76;
       print_rect.Left = report_width * 0.52;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.86;
       ChartAI->PrintResolution = -100;
       ChartAI->LeftAxis->LabelsFont->Color = sphygmocor_black;
       ChartAI->LeftAxis->Title->Font->Color = sphygmocor_black;
       ChartAI->Title->Font->Color = sphygmocor_maroon;
       ChartAI->PrintPartial(print_rect);

       printer_ptr->EndDoc();

       // Reset the charts to normal
       pnl_trend->Align = alClient;

       ChartPressures->BottomAxis->LabelsFont->Color = sphygmocor_white;
       ChartPressures->BottomAxis->Title->Font->Color = sphygmocor_white;
       ChartPressures->LeftAxis->LabelsFont->Color = sphygmocor_white;
       ChartPressures->LeftAxis->Title->Font->Color = sphygmocor_white;
       ChartPressures->Title->Font->Color = sphygmocor_white;

       ChartHR->BottomAxis->LabelsFont->Color = sphygmocor_white;
       ChartHR->BottomAxis->Title->Font->Color = sphygmocor_white;
       ChartHR->LeftAxis->LabelsFont->Color = sphygmocor_white;
       ChartHR->LeftAxis->Title->Font->Color = sphygmocor_white;
       ChartHR->Title->Font->Color = sphygmocor_white;

       ChartSEVR->LeftAxis->LabelsFont->Color = sphygmocor_white;
       ChartSEVR->LeftAxis->Title->Font->Color = sphygmocor_white;
       ChartSEVR->Title->Font->Color = sphygmocor_white;

       ChartED->LeftAxis->LabelsFont->Color = sphygmocor_white;
       ChartED->LeftAxis->Title->Font->Color = sphygmocor_white;
       ChartED->Title->Font->Color = sphygmocor_white;

       ChartAI->LeftAxis->LabelsFont->Color = sphygmocor_white;
       ChartAI->LeftAxis->Title->Font->Color = sphygmocor_white;
       ChartAI->Title->Font->Color = sphygmocor_white;
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

void __fastcall Tfrm_report_pwm::bbtn_deleteClick(TObject *Sender)
{
   AnsiString S;

   S = lbl_pname->Caption;
   if (report_qry != NULL)
   {
      if (MsgBox(LoadStr(MSG_DELETE_MEAS2) + S + "\n\n" + LoadStr(MSG_ARE_YOU_SURE),
          SCONFIRMATION, MB_YESNO | MB_ICONQUESTION) == ID_YES)
      {
         report_qry->Delete();
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

void __fastcall Tfrm_report_pwm::bbtn_exportClick(TObject *Sender)
{
   PATIENT_RECORD_TYPE  pat;
   TADOQuery               *qry;
   int                  nof_records;
   String               fname;

   qry = dbmgr_setup_query(DBMGR_MEASURE_PWM_TREND_TABLE,
                           DBMGR_QUERY_KEY,
                           PATIENT_SYSTEM_ID,
                           PATIENT_STUDY_ID,
                           PATIENT_NO,
                           MPWM_SESSION_ID,
                           pwm->System_ID,
                           pwm->Study_ID,
                           IntToStr(pwm->Patient_No),
                           IntToStr(pwm->Session_ID),
                           MPWM_PARAM_ID);

   if (qry != NULL)
   {
     nof_records = qry->RecordCount;
     if (nof_records <= 0)
     {
        MsgBox("No Trend parameters fo this session", SWARNING, MB_ICONEXCLAMATION);
     }
     else
     {
        if (patient_get(&pat))
        {
            fname = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR + pat.surname + "_"
              + pwm->SessionStart.FormatString("ddmmmyyyy-hhmmss") + "_pwm_session.txt";
            export_pwm_session(qry, fname, pwm);
        }
     }
     qry->Close();
     //grd_report->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwm::bbtn_reportClick(TObject *Sender)
{
   try
   {
      Screen->Cursor = crHourGlass;
      bbtn_report->Enabled = false;
      TADOQuery *qry = dbmgr_setup_query(DBMGR_MEASURE_PWM_TABLE,
                                      DBMGR_QUERY_KEY,
                                      PATIENT_SYSTEM_ID,
                                      PATIENT_STUDY_ID,
                                      PATIENT_NO,
                                      MPWM_SESSION_ID,
                                      pwm->System_ID,
                                      pwm->Study_ID,
                                      IntToStr(pwm->Patient_No),
                                      IntToStr(pwm->Session_ID));
      int NofRecords = (qry != NULL ? qry->RecordCount : 0);

      if (qry)
      {
         qry->Close();
      }

      if (NofRecords > 0)
      {
         // Do not hide the PWM form. Navigating away from the Report object will
         // close it, AS WELL AS the PWA form.
         frm_report_pwa->Show();
      }
      else
      {
         MsgBox(MSG_NO_REPORTS_TO_DISPLAY, SNOTIFICATION, MB_ICONINFORMATION);
      }
   }
   catch (Exception &exception)
   {
      ;
   }
   Screen->Cursor = crDefault;
   bbtn_report->Enabled = true;
}
//---------------------------------------------------------------------------

