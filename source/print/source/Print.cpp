#include <vcl.h>
#include <sysutils.hpp>
#pragma hdrstop

#include <inc/std.h>
#include <scor/form_main.h>
#include <scor/utils.h>
#include <meas/pubtype.h>
#include <patient/pubserv.h>
#include <config/pubserv.h>
#include <multdb/pubserv.h>
#include <comms/pubserv.h>
#include <print/pubserv.h>

const String PRINT_FONT_NAME = "Arial";
const String PRINT_DATE_FORMAT = "dd mmm yyyy";
bool  print_initialised;

bool print_initialise(void)
{
   print_initialised = true;
   return (print_initialised);
}

void print_destroy(void)
{
   print_initialised = false;
}

TPrinter *print_get_printer_ptr(void)
{
   TPrinter *printer_ptr;
   printer_ptr = Printer();
   return (printer_ptr);
}

bool print_does_printer_exist()
{
   return (print_get_printer_ptr() != NULL);
}

void print_do_header(TRect       *print_rect,
                     AnsiString  title1,
                     AnsiString  title2)
{
   int          width;
   int          xpos;
   int          text_height;
   AnsiString   S;
   AnsiString   S1;
   TFontStyles  font_style;
   TPrinter     *print_ptr;
   TRect        rect;

   print_ptr = print_get_printer_ptr();

   if (print_ptr != NULL)
   {
      width  = print_rect->Right - print_rect->Left;

      font_style << fsBold;
      print_ptr->Canvas->Font->Name = PRINT_FONT_NAME;
      print_ptr->Canvas->Font->Size = 16;
      print_ptr->Canvas->Font->Style = font_style;

      S = title1;
      text_height = print_ptr->Canvas->TextHeight(S);
      xpos = print_rect->Left + ((width - print_ptr->Canvas->TextWidth(S))  / 2);
      print_ptr->Canvas->TextOut(xpos,
                                 print_rect->Top + 10,
                                 S);

      if (title1 == SOFTWARE_DEFAULT_REPORT_TITLE)
      {
         // PM V9
         // This is a fix for non-unicode operating systems (eg. Japan)
         S = "R";
         rect.Left = xpos + print_ptr->Canvas->TextWidth(title1);
         rect.Right = rect.Left + print_ptr->Canvas->TextWidth(S) / 2;
         rect.Top = print_rect->Top + 10;
         rect.Bottom = rect.Top + print_ptr->Canvas->TextHeight(S) / 3;

         print_ptr->Canvas->StretchDraw(rect, frm_main->img_trademark->Picture->Bitmap);

         /*S = "®";
         xpos = xpos + print_ptr->Canvas->TextWidth(title1);
         print_ptr->Canvas->Font->Size = 8;
         print_ptr->Canvas->TextOut(xpos,
                                 print_rect->Top + 10 - print_ptr->Canvas->TextHeight(title1) / 4,
                                 S);
         print_ptr->Canvas->Font->Size = 16;  */
      }

      S = title2;
      font_style << fsBold;
      print_ptr->Canvas->Font->Name = PRINT_FONT_NAME;
      print_ptr->Canvas->Font->Size = 14;
      print_ptr->Canvas->Font->Style = font_style;
      xpos = print_rect->Left + ((width - print_ptr->Canvas->TextWidth(S))  / 2);
      print_ptr->Canvas->TextOut(xpos,
                                 print_rect->Top + 10 + text_height,
                                 S);
   }
}


void print_do_footer(TRect *print_rect, int maths_revision)
{
   int          xpos;
   AnsiString   S;
   AnsiString   S1;
   AnsiString   S2;
   AnsiString   date_str;
   TFontStyles  font_style;
   TPrinter     *print_ptr;
   TDateTime    dt;

   print_ptr = print_get_printer_ptr();

   if (print_ptr != NULL)
   {
      if (maths_revision == 0)
      {
         maths_revision = MEAS_MATH_DATA_REVISION;
      }
      date_str = dt.CurrentDate().FormatString(PRINT_DATE_FORMAT);

      S2 = "";
      // If the hardware configuration is unknown, request the module string
      if (comms_get_modes_string() == CONFIG_NO_OPTION_STRING)
      {
         if (comms_is_module_available())
         {
            if (comms_request_hwconfig())
            {
               S2 = " " + comms_get_emod_string() + " - " + comms_get_modes_string();
            }
         }
      }
      else
      {
         S2 = " " + comms_get_emod_string() + " - " + comms_get_modes_string();
      }

      S1 = config_get_report_title();
      if (S1 == SOFTWARE_DEFAULT_REPORT_TITLE)
      {
         S = "AtCor Medical " + SOFTWARE_MODEL_TYPE + " " + RELEASE_SOFTWARE_VERSION + config_get_clinical_string() + " (" + config_get_system_id() + ") "
            + IntToStr((int)maths_revision) + " " + multdb_get_active_name() + S2 + "  " + date_str;
      }
      else
      {
         S = SOFTWARE_MODEL_TYPE + " " + RELEASE_SOFTWARE_VERSION + config_get_clinical_string() + " (" + config_get_system_id() + ") "
            + IntToStr((int)maths_revision) + " " + multdb_get_active_name() + S2 + "  " + date_str;
      }

      font_style.Clear();
      print_ptr->Canvas->Font->Name = PRINT_FONT_NAME;
      print_ptr->Canvas->Font->Size = 6;
      print_ptr->Canvas->Font->Style = font_style;

      xpos = print_rect->Right - print_ptr->Canvas->TextWidth(S) * 1.1;
      print_ptr->Canvas->TextOut(xpos,
                                 print_rect->Top + /*1.1*/ 2. * print_ptr->Canvas->TextHeight(S),
                                 S);
   }
}

void print_do_atcor_image(TRect *print_rect)
{
   int          width;
   AnsiString   S;
   TFontStyles  font_style;
   TRect        rect;
   TPrinter     *print_ptr;


   print_ptr = print_get_printer_ptr();

   if (print_ptr != NULL)
   {
      width  = print_rect->Right - print_rect->Left;

      rect.Left = print_rect->Left + 0.92 * width;
      rect.Right = print_rect->Right - 4;
      rect.Top = print_rect->Top;
      rect.Bottom = print_rect->Bottom * 0.96;

      print_ptr->Canvas->StretchDraw(rect, frm_main->img_pwvmed_print->Picture->Bitmap);
   }
}

void print_do_patient_data(TRect *print_rect, UCOUNT age, bool is_invalid, String warning, String hint, int simulation)
{
   int                  width;
   int                  ypos;
   AnsiString           S;
   int                  text_width;
   PATIENT_RECORD_TYPE  pat;
   TFontStyles          font_style;
   TPrinter             *print_ptr;

   print_ptr = print_get_printer_ptr();

   if (print_ptr != NULL)
   {
       width  = print_rect->Right - print_rect->Left;

       patient_get(&pat);

       S = "PATIENT DATA";
       font_style << fsBold;
       print_ptr->Canvas->Font->Name = PRINT_FONT_NAME;
       print_ptr->Canvas->Font->Size = 12;
       print_ptr->Canvas->Font->Style = font_style;
       print_ptr->Canvas->TextOut(print_rect->Left,
                                  print_rect->Top,
                                  S);

       ypos = print_rect->Top + print_ptr->Canvas->TextHeight(S);
       font_style.Clear();
       print_ptr->Canvas->Font->Name = PRINT_FONT_NAME;
       print_ptr->Canvas->Font->Size = 8;
       print_ptr->Canvas->Font->Style = font_style;

       S = "Patient Name:      ";
       text_width = print_ptr->Canvas->TextWidth(S);
       print_ptr->Canvas->TextOut(print_rect->Left,
                                  ypos,
                                  S);
       S = patient_get_name();
       font_style << fsBold;
       print_ptr->Canvas->Font->Style = font_style;
       print_ptr->Canvas->TextOut(print_rect->Left + text_width,
                                  ypos,
                                  S);
       ypos = ypos + print_ptr->Canvas->TextHeight(S);

       font_style.Clear();
       print_ptr->Canvas->Font->Style = font_style;
       S = "Patient ID: ";
       print_ptr->Canvas->TextOut(print_rect->Left,
                                  ypos,
                                  S);
       font_style << fsBold;
       print_ptr->Canvas->Font->Style = font_style;
       print_ptr->Canvas->TextOut(print_rect->Left + text_width,
                                  ypos,
                                  pat.id);

       font_style.Clear();
       print_ptr->Canvas->Font->Style = font_style;
       S = "Address: ";
       print_ptr->Canvas->TextOut(width / 2,
                                  ypos,
                                  S);

       print_ptr->Canvas->TextOut(width / 2 + text_width,
                                  ypos,
                                  pat.street);
       ypos = ypos + print_ptr->Canvas->TextHeight(S);

       S = "Patient Code: ";
       print_ptr->Canvas->TextOut(print_rect->Left,
                                  ypos,
                                  S);
       font_style << fsBold;
       print_ptr->Canvas->Font->Style = font_style;
       print_ptr->Canvas->TextOut(print_rect->Left + text_width,
                                  ypos,
                                  pat.code);

       font_style.Clear();
       print_ptr->Canvas->Font->Style = font_style;
       print_ptr->Canvas->TextOut(width / 2 + text_width,
                                  ypos,
                                  pat.suburb + " " + pat.state + " " + pat.pcode);
       ypos = ypos + print_ptr->Canvas->TextHeight(S);

       S = "Age, Sex: ";
       print_ptr->Canvas->TextOut(print_rect->Left,
                                  ypos,
                                  S);
       if (age)
       {
          S = IntToStr(age) + " (" + pat.dob.FormatString(PRINT_DATE_FORMAT) + "), " + pat.sex;
       }
       else
       {
          S = pat.age + " (" + pat.dob.FormatString(PRINT_DATE_FORMAT) + "), " + pat.sex;
       }
       font_style << fsBold;
       print_ptr->Canvas->Font->Style = font_style;
       print_ptr->Canvas->TextOut(print_rect->Left + text_width,
                                  ypos,
                                  S);

       font_style.Clear();
       print_ptr->Canvas->Font->Style = font_style;
       print_ptr->Canvas->TextOut(width / 2 + text_width,
                                  ypos,
                                  pat.country);
       ypos = ypos + print_ptr->Canvas->TextHeight(S);

       if (is_invalid)
       {
          S = warning;
          font_style.Clear();
          font_style << fsUnderline;
          print_ptr->Canvas->Font->Style = font_style;
          print_ptr->Canvas->Font->Color = sphygmocor_maroon;
          print_ptr->Canvas->Font->Size = 11;
          text_width = print_ptr->Canvas->TextWidth(S);
          print_ptr->Canvas->TextOut(print_rect->Left + (width - text_width),
                                     ypos,
                                     S);
          ypos = ypos + print_ptr->Canvas->TextHeight(S);

          S = hint;
         font_style.Clear();
         print_ptr->Canvas->Font->Style = font_style;
         print_ptr->Canvas->Font->Size = 8;
         text_width = print_ptr->Canvas->TextWidth(S);
         print_ptr->Canvas->TextOut(print_rect->Left + (width - text_width),
                                    ypos,
                                    S);
         ypos = ypos + print_ptr->Canvas->TextHeight(S);

          if (simulation)
          {
            S = SIMULATION;
            font_style.Clear();
            font_style << fsUnderline;
            print_ptr->Canvas->Font->Style = font_style;
            print_ptr->Canvas->Font->Color = sphygmocor_maroon;
            print_ptr->Canvas->Font->Size = 11;
            text_width = print_ptr->Canvas->TextWidth(S);
            ypos = ypos + print_ptr->Canvas->TextHeight(S);
            print_ptr->Canvas->TextOut(print_rect->Left + (width - text_width),
                                       ypos,
                                       S);
          }
       }
       else
       {
          if (simulation)
          {
            S = SIMULATION;
            font_style.Clear();
            font_style << fsUnderline;
            print_ptr->Canvas->Font->Style = font_style;
            print_ptr->Canvas->Font->Color = sphygmocor_maroon;
            print_ptr->Canvas->Font->Size = 11;
            text_width = print_ptr->Canvas->TextWidth(S);
            ypos = ypos + print_ptr->Canvas->TextHeight(S);
            print_ptr->Canvas->TextOut(print_rect->Left + (width - text_width),
                                       ypos,
                                       S);
          }
       }

       font_style.Clear();
       print_ptr->Canvas->Font->Style = font_style;
       print_ptr->Canvas->Font->Color = clBlack;
       print_ptr->Canvas->Font->Size = 10;
   }
}
