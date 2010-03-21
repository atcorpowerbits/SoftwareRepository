//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
// #include "MsgBox.h"
#include <msg\pubserv.h>
#include <log\pubserv.h>
#include <meas\pubserv.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//  Enabling/disabling messages
//---------------------------------------------------------------------------
bool gShowMsgBox = true;
TMemo* gMemo = NULL;
//---------------------------------------------------------------------------
// Write message in memo field
void memo_write(String pMsg);
//---------------------------------------------------------------------------
void msg_initialise()
{
  msg_enable_messages();
  gMemo = NULL;
}
//---------------------------------------------------------------------------
void msg_enable_messages()
{
  gShowMsgBox = true;
}
//---------------------------------------------------------------------------
void msg_disable_messages()
{
  gShowMsgBox = false;
}
//---------------------------------------------------------------------------
void msg_enable_memo(TMemo *pMemo)
{
  gMemo = pMemo;
}
//---------------------------------------------------------------------------
void msg_disable_memo()
{
  gMemo = NULL;
}

int MsgBox_confirmation(String s_body, String s_caption)
{
   if (gShowMsgBox == false)
   {
      return -1;
   }
   else
   {
      return Application->MessageBox(s_body.c_str(),
                                     s_caption.c_str(),
                                     MB_ICONQUESTION | MB_YESNO);
   }
}

int MsgBox_information(String s_body, String s_caption)
{
   if (gShowMsgBox == false)
   {
      return -1;
   }
   else
   {
      return Application->MessageBox(s_body.c_str(),
                                     s_caption.c_str(),
                                     MB_ICONINFORMATION | MB_OK);
   }
}

int MsgBox_warning(String s_body, String s_caption)
{
   if (gShowMsgBox == false)
   {
      return -1;
   }
   else
   {
      return Application->MessageBox(s_body.c_str(),
                                     s_caption.c_str(),
                                     MB_ICONEXCLAMATION | MB_OK);
   }
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// These overloaded functions are used for printing messages with
// Strings picked up from System Messages resource file
//---------------------------------------------------------------------------

// 3 parameters

int MsgBox(int id_body, int id_caption, unsigned short Flag)
{
   if (gShowMsgBox == false)
   {
      return -1;
   }
   String s_body, s_caption;

   return Application->MessageBox((s_body.LoadStr(id_body)).c_str(),
                                  (s_caption.LoadStr(id_caption)).c_str(),
                                  Flag);
}
//---------------------------------------------------------------------------
int MsgBox(String s_body, int id_caption, unsigned short Flag)
{
   if (gShowMsgBox == false)
   {
      return -1;
   }
   String s_caption;
   return Application->MessageBox(s_body.c_str(),
                                 (s_caption.LoadStr(id_caption)).c_str(),
                                 Flag);
}
//---------------------------------------------------------------------------
int MsgBox(int id_body, String s_caption, unsigned short Flag)
{
   if (gShowMsgBox == false)
   {
      return -1;
   }
   String s_body;
   return Application->MessageBox((s_body.LoadStr(id_body)).c_str(),
                                   s_caption.c_str(),
                                   Flag);
}
//---------------------------------------------------------------------------
int MsgBox(String s_body, String s_caption, unsigned short Flag)
{
  if (gShowMsgBox == false)
  {
     return -1;
  }
  return Application->MessageBox(s_body.c_str(),
                                 s_caption.c_str(),
                                 Flag);
}

// 2 parameters

//---------------------------------------------------------------------------
int MsgBox(String s_body, int id_caption)
{
  if (gShowMsgBox == false)
  {
     return -1;
  }
  String s_caption;

  return Application->MessageBox(s_body.c_str(),
                                (s_caption.LoadStr(id_caption)).c_str(),
                                MB_ICONSTOP);
}
//---------------------------------------------------------------------------
int MsgBox(int id_body, String s_caption)
{
   if (gShowMsgBox == false)
   {
      return -1;
   }
   String s_body;
   return Application->MessageBox((s_body.LoadStr(id_body)).c_str(),
                                   s_caption.c_str(),
                                   MB_ICONSTOP);
}
//---------------------------------------------------------------------------
int MsgBox(int id_body, int id_caption)
{
   if (gShowMsgBox == false)
   {
      return -1;
   }
   String s_body, s_caption;
   return Application->MessageBox((s_body.LoadStr(id_body)).c_str(),
                                  (s_caption.LoadStr(id_caption)).c_str(),
                                  MB_ICONSTOP);
}
//---------------------------------------------------------------------------
int MsgBox(String s_body, String s_caption)
{
   if (gShowMsgBox == false)
   {
      return -1;
   }
   return Application->MessageBox(s_body.c_str(),
                                  s_caption.c_str(),
                                  MB_ICONSTOP);
}

// 1 parameters

//---------------------------------------------------------------------------
int MsgBox(int id_body)
{
   if (gShowMsgBox == false)
   {
      return -1;
   }
   String s_body;
   return Application->MessageBox((s_body.LoadStr(id_body)).c_str(),
                                   SWARNING.c_str(),
                                   MB_ICONSTOP);
}
//---------------------------------------------------------------------------
int MsgBox(String s_body)
{
   if (gShowMsgBox == false)
   {
      return -1;
   }
   return Application->MessageBox(s_body.c_str(),
                                  SWARNING.c_str(),
                                  MB_ICONSTOP);
}

//---------------------------------------------------------------------------
void MsgBox(TMsgType MsgType, int MsgForUser, int NumMsgForLog)
{
  MsgBox(MsgType, "", MsgForUser, NumMsgForLog, LoadStr(NumMsgForLog));
}
//---------------------------------------------------------------------------
void MsgBox(TMsgType MsgType, int MsgForUser,
            int NumMsgForLog, String MsgForLog)
{
  MsgBox(MsgType, "", MsgForUser, NumMsgForLog, MsgForLog);
}
//---------------------------------------------------------------------------
void MsgBox(TMsgType MsgType, String MsgPatientInfo, int MsgForUser,
            int NumMsgForLog)
{
  MsgBox(MsgType, MsgPatientInfo, MsgForUser, NumMsgForLog, LoadStr(NumMsgForLog));
}
//---------------------------------------------------------------------------
void MsgBox(TMsgType MsgType, String MsgPatientInfo, int MsgForUser,
            int MsgErrorNum, String MsgForLog)
{
   String MsgDisp, MsgLog;
   String Hook = ".\r\n\r\n";
   String MeasInfo = "";

   if (MsgPatientInfo != "")
   {
      MeasInfo = MsgPatientInfo + Hook;
   }

   String Title2 = " (#" + IntToStr(MsgErrorNum) + ")";

   if (MsgForLog != "")
   {
      MsgDisp = MeasInfo + LoadStr(MsgForUser) + Hook + MsgForLog;
      MsgLog  = MsgBox_ReplaceCarriage(MeasInfo + LoadStr(MsgForUser) + ": " + MsgForLog);
   }
   else
   {
      MsgDisp = MeasInfo + LoadStr(MsgForUser);
      MsgLog = MsgBox_ReplaceCarriage(MsgDisp);
   }
   // Switch
   switch (MsgType)
   {
     case TFATAL:
      if (gShowMsgBox == true)
      {
         MsgBox(MsgDisp, SFATAL + Title2, MB_ICONSTOP);
      }
      log_write(SFATAL + Title2 + ": "+ MsgLog);
      memo_write(SFATAL + Title2 + ": "+ MsgDisp);
      break;

    case TERROR:
      if (gShowMsgBox == true)
      {
         MsgBox(MsgDisp, SERROR + Title2, MB_ICONSTOP);
      }
      log_write(SERROR + Title2 + ": " +MsgLog);
      memo_write(SERROR + Title2 + ": " +MsgDisp);
      break;

    case TWARNING:
      if (gShowMsgBox == true)
      {
         MsgBox(MsgDisp, SWARNING + Title2, MB_ICONEXCLAMATION);
      }
      break;

    case TNOTIFICATION:
      if (gShowMsgBox == true)
      {
         MsgBox(MsgDisp, SNOTIFICATION + Title2, MB_ICONINFORMATION);
      }
      break;

    default:
      break;
  }
}

int MsgBox_show(TMsgType  msg_type,
                int       msg_caption_num,
                String    user_msg,
                int       msg_error_num,
                String    log_msg)
{
   String  msg_for_log;
   String  caption_str = "";
   int     user_response;
   bool    write_to_log;


   write_to_log = false;
   if (msg_caption_num)
   {
      caption_str = "  " +LoadStr(msg_caption_num);
   }

   if (msg_error_num)
   {
      caption_str = caption_str + " (#" + IntToStr(msg_error_num) + ")";
   }

   if (log_msg != "")
   {
      msg_for_log = MsgBox_ReplaceCarriage(log_msg);
      write_to_log = true;
   }
   else
   {
      msg_for_log = MsgBox_ReplaceCarriage(user_msg);
   }

   switch (msg_type)
   {
     case TFATAL:
      if (gShowMsgBox == true)
      {
         user_response = MsgBox(user_msg,
                                SFATAL +caption_str,
                                MB_ICONSTOP | MB_OK);
      }
      log_write(SFATAL +caption_str +": " +msg_for_log);
      memo_write(SFATAL +caption_str +": " +user_msg);
      break;

    case TERROR:
      if (gShowMsgBox == true)
      {
         user_response = MsgBox(user_msg,
                                SERROR +caption_str,
                                MB_ICONSTOP | MB_OK);
      }
      log_write(SERROR +caption_str +": " +msg_for_log);
      memo_write(SERROR +caption_str +": " +user_msg);
      break;

    case TWARNING:
      if (gShowMsgBox == true)
      {
         user_response = MsgBox(user_msg,
                                SWARNING +caption_str,
                                MB_ICONEXCLAMATION | MB_OK);
      }
      if (write_to_log)
      {
         log_write(SWARNING +caption_str +": " +msg_for_log);
      }

      break;

    case TNOTIFICATION:
      if (gShowMsgBox == true)
      {
         user_response = MsgBox(user_msg,
                                SNOTIFICATION,
                                MB_ICONINFORMATION | MB_OK);
      }
      if (write_to_log)
      {
         log_write(SNOTIFICATION +caption_str +": " +msg_for_log);
      }
      break;

    default:
      user_response = -1;
      break;
  }
  return (user_response);
}

//---------------------------------------------------------------------------
// replace carriage return on skip
//---------------------------------------------------------------------------
String MsgBox_ReplaceCarriage(const String pIn)
{
  int Ind = 1;
  String Out(pIn.c_str());
  while (Ind > 0)
  {
    Ind = Out.Pos('\r');
    if (Ind > 0) Out[Ind] = ' ';
    Ind = Out.Pos('\n');
    if (Ind > 0) Out[Ind] = ' ';
  }
  return Out;
}
//---------------------------------------------------------------------------
// Write message in memo field
//---------------------------------------------------------------------------
void memo_write(String pMsg)
{
  // Validate
  if (gMemo==NULL)
    return;
  if (!gMemo->HandleAllocated())
  {
    gMemo = NULL;
    return;
  }
  try
  {
    // try to write in memo
    gMemo->Lines->Add(pMsg);
    gMemo->Lines->Add("------------------------------------");
  }
  catch (...)
  {
    gMemo = NULL;
    return;
  }
}


