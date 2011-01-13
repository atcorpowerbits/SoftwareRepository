/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :      CrxLogger.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      Functionality implementation for Logger
*/
#pragma once

#include "stdafx.h"
#include "CrxLogger.h"


using namespace AtCor::Scor::CrossCutting::Logging;
using namespace System::Diagnostics;
using namespace System;
using namespace System::Collections::Generic;
using namespace  Microsoft::Practices::EnterpriseLibrary::Logging;
using namespace System::IO;


//Constructor for CrxLogger
CrxLogger::CrxLogger()
{
	
	GetLastWrittenLineNumber();

	//Get the LogWriter from enterprise library
	CrxLogWriter =  EnterpriseLibraryContainer::Current->GetInstance<LogWriter^>();

}

//Write method to write to log file and event logger
void CrxLogger::Write(String^ message)
{

	if (entryLineNumber == 0)
	{
		//this is the first line write a header
		//then proceed to next line
		String^ headerString = "Line SphygmoCor Log File ~ " + (DateTime::Today).ToString("d") + " ~ " + (DateTime::Now).ToString("HH:mm:ss");
	
		LogEntry^ logEnt = gcnew LogEntry();
		logEnt->Message = headerString;
		//Write the passed message to the LogWriter
		CrxLogWriter->Write(logEnt);
	}
	
	entryLineNumber++; //Increment the number before we actually write it.

	//Create a new log entry and add it to the log
	LogEntry^ logEnt = gcnew LogEntry();
	logEnt->Message = message;
	logEnt->Title = Convert::ToString(entryLineNumber);
	//Write the passed message to the LogWriter
	CrxLogWriter->Write(logEnt);

  if (entryLineNumber >= 1600) 
  {
	  //roll over when the limit of 1600 lines is crossed.
	 RollLogFile();

  }
}

void CrxLogger::GetLastWrittenLineNumber()
{
	//check if there is a current log file
	if (File::Exists("system\\logs\\scor.log"))
	{
		//open it 
		StreamReader ^curLogFileFileStream;
		curLogFileFileStream =File::OpenText("system\\logs\\scor.log");

		//create a string and read the entire file
		String ^fileStr = curLogFileFileStream->ReadToEnd();
		//obtain the last newline. Note THere is always a newline at the end of the file. Hence -5.
		//then using this penultimate newline get the last line.
       String ^lastLine = fileStr->Substring(fileStr->LastIndexOf('\n',(fileStr->Length) - 5) + 1);
		//get the first part of this string
	   String^ lastLineNumber =  lastLine->Substring(0, lastLine->IndexOf(' '));

	   if (lastLineNumber != nullptr)
	   {
		   try
		   {
			   //convert it into a number
			    entryLineNumber =  Int32::Parse(lastLineNumber);
		   }
		   catch(Exception ^)
		   {
			   entryLineNumber = 0;
				curLogFileFileStream->Close();
		   }
	   }
		curLogFileFileStream->Close();
	}
	else
	{
		//new file or rolled ove withot creating a current file.
		entryLineNumber = 0;
	}

}

bool CrxLogger::RollLogFile()
{
	//first destroy the logwriter so that it releases the log file
	 delete CrxLogWriter; 
	  
	  DateTime nowDateTime;
	  nowDateTime = System::DateTime::Now;

	  //create the file name using current date time
	  String  ^ nowDateTimeStr = nowDateTime.ToString("yyyyMMMddHHmmss");
	  nowDateTimeStr = "system\\logs\\scor_"+ nowDateTimeStr+".log"; 

	  try
	  {
		  //rename the current file to the new filename
		File::Move("system\\logs\\scor.log", nowDateTimeStr);
	  }
	  catch(Exception ^)
	  {
		  throw gcnew CrxException("CRX_ERR_FILE_ALREADY_EXIST");
	  }
	
	  //now recreate the log file again . it will begin from scor.log
		CrxLogWriter = EnterpriseLibraryContainer::Current->GetInstance<LogWriter^>();
		
		//reset coutner.
		entryLineNumber = 0;

		return true;
}

