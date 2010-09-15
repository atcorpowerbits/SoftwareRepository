#ifndef LOG_ATTRIB
#define LOG_ATTRIB

class TDispLog : public TObject
{
   public:
           __fastcall  TDispLog(void);                            // constructor
           __fastcall ~TDispLog(void);                            // destructor
      void __fastcall  AddLine(AnsiString);                       // add line to log or display
      void __fastcall WriteStartToLog(void);
      void __fastcall WriteEndToLog(void);
      void __fastcall WriteHeader(void);
      void __fastcall CheckIntegrity(void);

    __published:
      __property unsigned int MaxLines = { read = fMaxLines, write = fMaxLines   };
      __property unsigned int MaxLineLength = { read = fMaxLineLength, write = fMaxLineLength   };
      __property AnsiString   LogFilename  = { read = fLogFilename,  write = SetLogFilename  };
      __property bool         LogLine      = { read = fLogLine,      write = SetLogLine      };
      __property bool         AppendToLog  = { read = fAppendToLog,  write = SetAppendToLog  };
      __property bool         LogTime      = { read = fLogTime,      write = fLogTime        };
      __property bool         LogMSecs     = { read = fLogMSecs,     write = fLogMSecs       };
      __property bool         LogDate      = { read = fLogDate,      write = fLogDate        };
      __property unsigned int LogDTPos     = { read = fLogDTPos,     write = SetLogDTPos     };
      __property bool         KeepLogOpen  = { read = fKeepLogOpen,  write = SetKeepLogOpen  };
      __property AnsiString   SepString    = { read = fSepString,    write = fSepString      };

    protected:
      int          LogFileLinesNow;              // count of lines written to log file in current session
      int          LogFileLineCurrent;            // count of lines written to log file in total
      int          LogFileHandle;                // log file handle
      char         *log_pad_buff;

      unsigned int fMaxLines;                    // max number of messages to keep in memo
      unsigned int fMaxLineLength;               // max length of messages to keep in memo
      AnsiString   fLogFilename;                 // name of file to which to write log lines
      bool         fLogLine;                     // true if lines are logged
      bool         fAppendToLog;                 // true if existing log should be appended to
      bool         fLogTime;                     // log time at end of line
      bool         fLogMSecs;                    // log milliseconds as part of time string
      bool         fLogDate;                     // log date at end of line
      unsigned int fLogDTPos;                    // positoin of date and/or time in log
      bool         fKeepLogOpen;                 // keep log file open between writes
      AnsiString   fSepString;                   // string seperates date and time from line

      void         __fastcall WriteToLog(AnsiString msg);
      void         __fastcall UpdateHeader(void);
      void         __fastcall AddDateTime(AnsiString *, bool, bool, bool, int);
      void         __fastcall OpenLogFile(void);
      void         __fastcall CloseLogFile(void);
      void         __fastcall PadString(AnsiString *, int);
      // property get/set functions
      void         __fastcall SetLogFilename(AnsiString);
      void         __fastcall SetLogLine(bool);
      void         __fastcall SetAppendToLog(bool);
      void         __fastcall SetLogDTPos(unsigned int);
      void         __fastcall SetKeepLogOpen(bool);
};
extern TDispLog *log;

#endif

