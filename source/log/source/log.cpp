#include <vcl.h>
#include <sysutils.hpp>
#include <classes.hpp>
#include <stdio.h>
#include <stdlib.h>
#pragma hdrstop

#include <inc/std.h>
#include <scor/utils.h>
#include <config/pubserv.h>
#include <dbmgr/pubtype.h>
#include <log/pubserv.h>
#include <meas/pubserv.h>
#include <comms/pubserv.h>
#include "log.h"

#pragma package(smart_init)

VAR_EXPORT TDispLog  *log;

const String SPHYGMOCOR = "SphygmoCor ";

bool log_corrupted;
bool log_initialised;

bool log_initialise(void)
{
   log_initialised = false;
   log_corrupted = true;

   log = new TDispLog();
   if (log != NULL)
   {
      log_initialised = true;
      log_corrupted = false;
      log->LogLine = true;
      log->LogDate = true;
      log->LogTime = true;
      log->CheckIntegrity();
      log->WriteHeader();
   }
   return (log_initialised);
}

void log_destroy(void)
{
   if (log_initialised)
   {
      if (log != NULL)
      {
         log->WriteEndToLog();
         delete log;
         log_initialised = false;
      }
   }
}

void log_write(AnsiString  log_msg)
{
   log->AddLine(log_msg);
}

void log_write_start(void)
{
   log->WriteStartToLog();
}

void log_write(int msg_number)
{
   log->AddLine(LoadStr(msg_number));
}

AnsiString log_get_system_details(void)
{
   AnsiString  file_path;
   AnsiString  sys_details;
   VLONG         free_disk_space;
   ULONG         database_size;
   ULONG         total_physical_mem;
   ULONG         avail_physical_mem;
   MEMORYSTATUS  mem_status;

   file_path = ExtractFilePath(ParamStr(0));
   free_disk_space = emma_get_disk_space(file_path[1]);
   free_disk_space = free_disk_space / 1024;

   file_path = file_path +CONFIG_DATA_SUBDIR +"\\" +DBMGR_DATABASE_NAME;
   database_size = emma_get_file_size(file_path);

   database_size = database_size / 1024;

   mem_status.dwLength = sizeof(MEMORYSTATUS);
   GlobalMemoryStatus(&mem_status);

   total_physical_mem = mem_status.dwTotalPhys / 1024;
   avail_physical_mem  = mem_status.dwAvailPhys / 1024;

   sys_details = "- FDS "+RoundIntToStr(free_disk_space) +", DBS " +
      RoundIntToStr(database_size) +",  TPM " +RoundIntToStr(total_physical_mem) +
      ", APM " +RoundIntToStr(avail_physical_mem) +", ML " +
      RoundIntToStr(mem_status.dwMemoryLoad) +"   " +config_get_system_id();
   return (sys_details);
}

__fastcall TDispLog::TDispLog(void) : TObject()
{
  LogFileHandle     = -1;
  LogFileLinesNow   = 0;
  LogFileLineCurrent  = 0;
  fMaxLines        = 1600;
  fMaxLineLength   = 240;
  fLogFilename     = ExtractFilePath(ParamStr(0)) +CONFIG_SYSTEM_SUBDIR + "\\scor.log";
  fLogLine         = false;
  fAppendToLog     = true;
  fLogTime         = false;
  fLogMSecs        = false;
  fLogDate         = false;
  fLogDTPos        = 0;
  fKeepLogOpen     = false;
  fSepString       = " ~ ";

  log_pad_buff = new char[fMaxLineLength];
}

//==================================================================================================
// TDispLog Destructor
//==================================================================================================
__fastcall TDispLog::~TDispLog(void)
{
   if (fKeepLogOpen == true)
   {                                   // log file was kept open
      CloseLogFile();                  // so close it
   }

   if (log_pad_buff != NULL)
   {
      delete [] log_pad_buff;
   }
}


//==================================================================================================
// AddLine - add line to log and/or memo
//==================================================================================================
void __fastcall TDispLog::AddLine(AnsiString Msg)
{
   AnsiString log_line;

   if (!log_corrupted && fLogLine == true)
   {
      log_line = Msg;

      if (fLogTime || fLogDate)
      {
         AddDateTime(&log_line,
                     fLogDate,
                     fLogTime,
                     fLogMSecs,
                     fLogDTPos);   // add date and/or time
      }

      WriteToLog(log_line + "\n");
   }
}

// WriteHeader - write header string to log file
void __fastcall TDispLog::WriteHeader(void)
{
   AnsiString header_msg;

   if (!(FileExists(fLogFilename)) || !(fAppendToLog))
   {
      LogFileLinesNow   = 0;
      LogFileLineCurrent  = 0;
      header_msg = "Line (0001) " +SPHYGMOCOR + "Log File " +RELEASE_SOFTWARE_VERSION + config_get_clinical_string();
      fLogDTPos = header_msg.Length();
      AddLine(header_msg);
      fLogDTPos = 0;
   }
}

// CheckIntegrity -
void __fastcall TDispLog::CheckIntegrity(void)
{
   char *header_str;
   FILE *stream_ptr;
   int  current_line;
   bool create_new = false;

   if (FileExists(fLogFilename))
   {
      header_str = new char[fMaxLineLength];
      if ((stream_ptr = fopen(fLogFilename.c_str(), "rt")) != NULL)
      {
         fgets(header_str, fMaxLineLength, stream_ptr);
         if (strstr(header_str, "SphygmoCor Log File") == NULL)
         {
            create_new = true;
         }
         else
         {
            header_str[10] = '\0';
            current_line = atoi(&header_str[6]);
            if (current_line <= 0 || (unsigned int)current_line >= fMaxLines)
            {
               create_new = true;
            }
            else
            {
               LogFileLineCurrent = (unsigned int)current_line;
            }
         }
         fclose(stream_ptr);
      }
      if (create_new)
      {
         LogFileLineCurrent = 0;
         LogFileLinesNow = 0;
         DeleteFile(fLogFilename);
      }
      delete [] header_str;
   }
}

// WriteStartToLog - write specified string to log file
void __fastcall TDispLog::WriteStartToLog(void)
{
   AnsiString start_msg;

   start_msg = SOFTWARE_MODEL_TYPE +" " +RELEASE_SOFTWARE_VERSION + config_get_clinical_string() + " Start " + log_get_system_details();
   AddLine(start_msg);
}

// WriteEndToLog - write specified string to log file
void __fastcall TDispLog::WriteEndToLog(void)
{
   AnsiString end_msg;

   end_msg = SOFTWARE_MODEL_TYPE +" " +RELEASE_SOFTWARE_VERSION + config_get_clinical_string() + " End " + log_get_system_details();
   AddLine(end_msg);
}

// UpdateHeader - Update the current line number, if the log file is full,
//                archive the log file and write a header on new log file
void __fastcall TDispLog::UpdateHeader(void)
{
   AnsiString line_str;
   AnsiString date;
   AnsiString ArchiveLogFilename;
   if ((unsigned int)LogFileLineCurrent >= fMaxLines)
   {
      date = Now().FormatString("ddmmmyyyy");
      ArchiveLogFilename = ExtractFilePath(ParamStr(0)) +CONFIG_SYSTEM_SUBDIR + "\\scor_" + date + ".log";
      if (LogFileHandle >= 0)
      {
         FileClose(LogFileHandle);
         LogFileHandle = -1;
         if (RenameFile(fLogFilename, ArchiveLogFilename))
         {
            LogFileLineCurrent = 0;
            LogFileLinesNow = 0;
            DeleteFile(fLogFilename);
            WriteHeader();
         }
      }
   }
   else
   {
      FileSeek(LogFileHandle, 6, 0);
      line_str =  FormatFloat("0000", (float)LogFileLineCurrent);
      FileWrite(LogFileHandle,
               line_str.c_str(),
               line_str.Length());
   }
}
// WriteToLog - write specified string to log file
void __fastcall TDispLog::WriteToLog(AnsiString msg)
{
   if (fKeepLogOpen == false)
   {
       OpenLogFile();
   }

   try
   {
      FileSeek(LogFileHandle, (int)(LogFileLineCurrent * fMaxLineLength), 0);
      FileWrite(LogFileHandle,
                msg.c_str(),
                msg.Length());
      LogFileLinesNow++;
      LogFileLineCurrent++;
      UpdateHeader();

   }
   catch (...)
   {
      log_corrupted = true;
   }

   if (fKeepLogOpen == false)
   {
      CloseLogFile();
   }
}

// OpenLogFile - open for append, or create new log file                                   EXCEPTION
void __fastcall TDispLog::OpenLogFile(void)
{
   if (LogFileLinesNow == 0)
   {
      if (fAppendToLog)
      {
         if (FileExists(fLogFilename))
         {
            LogFileHandle = FileOpen(fLogFilename, fmOpenWrite);
         }
         else
         {
            LogFileHandle = FileCreate(fLogFilename);
         }

         if (LogFileHandle >= 0)
         {
            // seek to the end of the file
            FileSeek(LogFileHandle, 0, 2);
         }
      }
      else
      {
         LogFileHandle = FileCreate(fLogFilename);
      }
   }
   else
   {
      LogFileHandle = FileOpen(fLogFilename, fmOpenWrite);

      if (LogFileHandle >= 0)
      {
         FileSeek(LogFileHandle, 0, 2);
      }
   }

   if (LogFileHandle < 0)
   {
      //throw Exception("File I/O error:" + GetSystemErrorMessage());
   }
}

// CloseLogFile - close the log file if it is open, reset file handle
void __fastcall TDispLog::CloseLogFile(void)
{
   if (LogFileHandle >= 0)
   {
      FileClose(LogFileHandle);
      LogFileHandle = -1;
   }
}

// AddDateTime - pad line, add date and time stamps, as specified
void __fastcall TDispLog::AddDateTime(AnsiString *Msg,bool AddDate,bool AddTime,bool AddMS, int Pos)
{
   unsigned short Hour;                                     // decoded hour value
   unsigned short Minute;                                   // decoded minute value
   unsigned short Second;                                   // decoded second value
   unsigned short mSecond;                                  // decoded millisecond value
   char           TimeBuf[30];                              // formatted time buffer
   TDateTime      DT = Now();                               // get, store date and time
   AnsiString     DateFmt = "dd/mm/yyyy";                   // date format string
   AnsiString     TimeFmt = "hh:nn:ss";                     // time format string


   if (AddDate == true || AddTime == true)
   {                 // adding date or time
      if (Pos == 0)
      {                                         // date/time at start of line
         AnsiString Buffer = "";                              // line buffer
         Buffer = IntToStr(LogFileLineCurrent) + " ";
         if (AddDate == true)
         {                                // date wanted
            Buffer += DT.FormatString(DateFmt) + fSepString;   // put date in buffer
         }

         if (AddTime == true)
         {                                // time wanted
            if (AddMS == true)
            {
               DecodeTime(DT, Hour, Minute, Second, mSecond);   // decode current time
               sprintf(TimeBuf,
                       "%2.2d:%2.2d:%2.2d.%3.3d",
                       Hour, Minute, Second, mSecond);
               Buffer += TimeBuf;
            }
            else
            {
               Buffer += DT.FormatString(TimeFmt);
            }
            Buffer = Buffer + fSepString;
         }

         Buffer += *Msg;
         *Msg    = Buffer;
         PadString(Msg, fMaxLineLength);
      }
      else
      {
         *Msg += fSepString;

         if (AddDate == true)
         {                                // if date is to be added
            *Msg += Now().FormatString(DateFmt);               // add formatted date
         }

         if (AddTime == true)
         {
            if (AddDate == true)
            {
               *Msg += fSepString;
            }

            if (AddMS == true)
            {
               DecodeTime(DT, Hour, Minute, Second, mSecond);
               sprintf(TimeBuf,
                       "%2.2d:%2.2d:%2.2d.%3.3d",
                        Hour, Minute, Second, mSecond);
               *Msg += TimeBuf;
            }
            else
            {
               *Msg += DT.FormatString(TimeFmt);
            }
         }
         PadString(Msg, fMaxLineLength);
      }
   }
}

// PadString - pad the specified AnsiString w/spaces to the specified length
void __fastcall TDispLog::PadString(AnsiString *Msg, int Len)
{
   int  pad_size;   // get padding length

   if (Len > (Msg->Length() + 1))
   {
      pad_size = Len - Msg->Length() - 1;
      memset((void *)log_pad_buff, ' ', pad_size);
      log_pad_buff[pad_size] = '\0';
      *Msg += log_pad_buff;
   }
   else
   {
      Msg->SetLength(fMaxLineLength - 1);
   }
}

// SetLogFilename - set the name of the log file
void __fastcall TDispLog::SetLogFilename(AnsiString Name)
{
   fLogFilename = Name;

   if (fLogLine == true && fKeepLogOpen == true)
   {
      CloseLogFile();
      OpenLogFile();
   }
}

// SetLogLine - set the log-line-to-disk flag to the specified value
void __fastcall TDispLog::SetLogLine(bool Flag)
{
   if (fLogLine != Flag)
   {
      fLogLine = Flag;

      if (fKeepLogOpen == true)
      {
         if (fLogLine == true)
         {
            OpenLogFile();
         }
         else
         {
            CloseLogFile();
         }
      }
   }
}

// SetAppendToLog - set the append-to-log flag to specified value                          EXCEPTION
void __fastcall TDispLog::SetAppendToLog(bool Flag)
{
   if (fLogLine == true || LogFileLinesNow > 0)
   {
      ;
   }
   else
   {
      fAppendToLog = Flag;
   }
}

// SetLogDTPos - set the character position of the date and/or time in the log line        EXCEPTION
void __fastcall TDispLog::SetLogDTPos(unsigned int Value)
{
   if (Value > fMaxLineLength)
   {
      ;
   }
   else
   {
      fLogDTPos = Value;
   }
}

// SetKeepLogOpen - set the keep-log-open flag to the specified value                      EXCEPTION
void __fastcall TDispLog::SetKeepLogOpen(bool Flag)
{
   if (fLogLine == true)
   {
      ;
   }
   fKeepLogOpen = Flag;
}

