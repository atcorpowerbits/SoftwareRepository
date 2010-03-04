//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "interview.h"
#include <config/pubserv.h>
#include <msg/pubserv.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)

TStringList *interview;
TStringList *questions;
TStringList *responses;
TStringList *codes;

// Displays the questions and stores the codes from the "questions.txt" file

bool interview_start(TCheckListBox *lstbox)
{
   bool status = true;
   bool found = false;
   int line_counter;
   String code;

   interview->Clear();
   questions->Clear();
   responses->Clear();
   codes->Clear();
   
   AnsiString interview_path = ExtractFilePath(ParamStr(0)) + CONFIG_DATA_SUBDIR + "\\questions.txt";
   if (FileExists(interview_path))
   {
      interview->LoadFromFile(interview_path);
      lstbox->Items->Clear();

      if (interview->Count > 2)
      {
         line_counter = 0;
         while (line_counter < interview->Count && !found)
         {
            if (interview->Strings[line_counter] == "CODES")
            {
               found = true;
            }
            if (!found)
            {
               questions->Add(interview->Strings[line_counter]);
            }
            ++line_counter;
         }

         if (found)
         {
            while (line_counter < interview->Count)
            {
               code = interview->Strings[line_counter];

               // If the code is not unique or 3 letters in length, then stop
               if (codes->IndexOf(code) != -1 || code.Length() != 3)
               {
                  status = false;
                  MsgBox_show(TWARNING,
                                 MSG_PATIENT_ERROR,
                                 LoadStr(MSG_INTERVIEW_CODE),
                                 MSG_INTERVIEW_CODE,
                                 LoadStr(MSG_INTERVIEW_CODE));
                  break;
               }

               codes->Add(code.UpperCase());
               ++line_counter;
            }
            for (int i = 0; i < questions->Count; i++)
            {
               responses->Add("No");
               lstbox->Items->Add(questions->Strings[i]);
            }
         }
      }
   }
   else
   {
      // The questions text file does not exist
      status = false;
      MsgBox_show(TWARNING,
                    MSG_PATIENT_ERROR,
                    LoadStr(MSG_INTERVIEW_FILE),
                    MSG_INTERVIEW_FILE,
                    LoadStr(MSG_INTERVIEW_FILE));
   }

   if (!found && status)
   {
      // The line CODES was not found
      status = false;
      MsgBox_show(TWARNING,
                    MSG_PATIENT_ERROR,
                    LoadStr(MSG_INTERVIEW_CODES),
                    MSG_INTERVIEW_CODES,
                    LoadStr(MSG_INTERVIEW_CODES));
   }
   if (questions->Count != codes->Count && status)
   {
      // There is not an equal number of questions and codes
      status = false;
      MsgBox_show(TWARNING,
                    MSG_PATIENT_ERROR,
                    LoadStr(MSG_INTERVIEW_QUESTIONS),
                    MSG_INTERVIEW_QUESTIONS,
                    LoadStr(MSG_INTERVIEW_QUESTIONS));
   }

   return status;
}

// Create resources used by the interview object
void interview_create(void)
{
   interview = new TStringList();
   questions = new TStringList();
   responses = new TStringList();
   codes = new TStringList();
}

// Frees resources used by the interview object
void interview_end(void)
{
   if (interview != NULL)
   {
      interview->Clear();
      delete interview;
   }

   if (questions != NULL)
   {
      questions->Clear();
      delete questions;
   }

   if (responses != NULL)
   {
      responses->Clear();
      delete responses;
   }

   if (codes != NULL)
   {
      codes->Clear();
      delete codes;
   }
}

int interview_get_count(void)
{
   return (questions->Count);
}

// Returns the codes associated with the selected responses

String interview_get_codes(TCheckListBox *lstbox)
{
   int count;
   String interview_line;
   bool first = true;

   count = interview_get_count();
   for (int i = 0; i<count; i++)
   {
      if (lstbox->Checked[i])
      {
         if (first)
         {
            first = false;
            interview_line = "Profile: " + codes->Strings[i];
         }
         else
         {
            interview_line = interview_line + ", " + codes->Strings[i];
         }
         responses->Strings[i] = "Yes";
      }
      else
      {
         responses->Strings[i] = "No";
      }
   }
   return interview_line;
}

// Displays the responses associated with the codes given

void interview_set_codes(TCheckListBox *lstbox, String notes)
{
   String code;
   int index;

   for (;;)
   {
      code = notes.SubString(1, 3);
      index = codes->IndexOf(code);
      if (index != -1)
      {
         lstbox->Checked[index] = true;
      }
      if (notes.Length() > 4)
      {
         notes = notes.SubString(6, notes.Length() - 5);
      }
      else
      {
         break;
      }
   }
}

