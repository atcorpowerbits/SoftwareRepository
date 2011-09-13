/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :      CrxLogger.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      Functionality implementation for Logger
*/
#pragma once

#include "stdafx.h"
#include "CrxLogger.h"
#include "CrxMessaging.h"
#include "ScorException.h"
#include "CrxSystemParametersReader.h"


using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace AtCor::Scor::CrossCutting::Configuration;


//Constructor for CrxLogger
CrxLogger::CrxLogger()
{
	//Temporary code to enable or disable logging from the system Parameters file.
	if (CrxSytemParameters::Instance->GetStringTagValue("Crx.Logging.Enable") == "Y")
	{
		enableLogging = true;
	}
	else
	{
		enableLogging = false;
	}	
	
	if (System::IO::File::Exists(CrxSystemParameterInfo::FilePath))
	{
	  FileInfo^ fi = gcnew FileInfo(CrxSystemParameterInfo::FilePath);
	  log4net::Config::XmlConfigurator::Configure(fi);
	}
	else
	{
	  String^ errMessage = "ScorSystemParameters File Not Found";
	  throw gcnew ScorException(303,errMessage , ErrorSeverity::Exception);// File not found
	}
	log = LogManager::GetLogger("Scor:");

}

//Write method to write to log file and event logger
//void CrxLogger::Write(String^ message)
//{
//	if (!enableLogging)
//	{
//		//If the logging is not enabled in the System Parameters 
//		//file , do not make any log entries
//		return;
//	}
//
//	if (entryLineNumber == 0)
//	{
//		String^ headerString;
//		CrxMessagingManager ^messageMgr = CrxMessagingManager::Instance;
//
//		String ^headerSeperator = messageMgr->GetMessage(CrxStructCommonResourceMsg::CrxLogFileHeaderSeperator);
//
//		//this is the first line write a header
//		//then proceed to next line
//		headerString = messageMgr->GetMessage(CrxStructCommonResourceMsg::CrxLogFileHeaderLine)+ headerSeperator + (DateTime::Today).ToString("dd/MM/yyyy") + headerSeperator + (DateTime::Now).ToString("HH:mm:ss");
//
//
//		//open a stream writer and log an entry directly.
//		//We cant  use the Loggers methods because it formats a log entry from the string.
//		StreamWriter ^curLogFileFileStream;
//		curLogFileFileStream = gcnew StreamWriter(File::Open(CrxLogStructInternal::LogFilePath, FileMode::Append)); //open in append mode.
//		//write the header line
//		curLogFileFileStream->WriteLine(headerString);
//		//insert a blank line
//		curLogFileFileStream->WriteLine("");
//		//close the filestream.
//		curLogFileFileStream->Close();
//
//	}
//	
//	entryLineNumber++; //Increment the number before we actually write it.
//
//	//Create a new log entry and add it to the log
//	LogEntry^ logEnt = gcnew LogEntry();
//	logEnt->Message = message;
//	logEnt->Title = Convert::ToString(entryLineNumber);
//	//Write the passed message to the LogWriter
//	CrxLogWriter->Write(logEnt);
//
//
//	//Deepak: Disabling rollover in order to log packets and prevent rollover related issues
//	//THis will be used for testing by TS. 
//	//TODO: IMPORTANT: DO NOT check in into the delivery code
//  //if (entryLineNumber >= 1600) 
//  //{
//	 // //roll over when the limit of 1600 lines is crossed.
//	 //RollLogFile();
//
//  //}
//}

//void CrxLogger::GetLastWrittenLineNumber()
//{
//	StreamReader ^curLogFileFileStream;
//	 String^ lastLineNumber;
//
//	//check if there is a current log file
//	 if (File::Exists(CrxLogStructInternal::LogFilePath))
//	{
//		try
//		{
//		//open it 
//			
//			curLogFileFileStream =File::OpenText(CrxLogStructInternal::LogFilePath);
//
//			//create a string and read the entire file
//			String ^fileStr = curLogFileFileStream->ReadToEnd();
//			//obtain the last newline. Note THere is always a newline at the end of the file. Hence -5.
//			//then using this penultimate newline get the last line.
//			fileStr = fileStr->Trim();
//			String ^lastLine = fileStr->Substring(fileStr->LastIndexOf('\n',(fileStr->Length) - 5) + 1);
//			lastLine = lastLine->Trim();
//			//get the first part of this string
//			lastLineNumber =  lastLine->Substring(0, lastLine->IndexOf(' '));
//		}
//		catch(Exception^ excepObj)
//		{
//			throw gcnew ScorException(excepObj);
//		}
//
//
//	   if (lastLineNumber != nullptr)
//	   {
//		   try
//		   {
//			   //convert it into a number
//			    entryLineNumber =  Int32::Parse(lastLineNumber);
//		   }
//		   catch(Exception ^)
//		   {
//			   entryLineNumber = 0;
//				curLogFileFileStream->Close();
//		   }
//	   }
//		curLogFileFileStream->Close();
//	}
//	else
//	{
//		//new file or rolled ove withot creating a current file.
//		entryLineNumber = 0;
//	}
//
//}
//
//bool CrxLogger::RollLogFile()
//{
//	//first destroy the logwriter so that it releases the log file
//	 delete CrxLogWriter; 
//	  
//	  DateTime nowDateTime;
//	  nowDateTime = System::DateTime::Now;
//
//	  //create the file name using current date time
//	  String  ^ nowDateTimeStr = nowDateTime.ToString(CrxLogStructInternal::DateTimeFormat);
//	  nowDateTimeStr = CrxLogStructInternal::LogFileName + nowDateTimeStr+ CrxLogStructInternal::LogFileExt; 
//
//	  try
//	  {
//		  //rename the current file to the new filename
//		  File::Move(CrxLogStructInternal::LogFilePath, nowDateTimeStr);
//	  }
//	  catch(Exception ^)
//	  {
//		  throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileAlreadyExistErrCd, CrxStructCommonResourceMsg::CrxErrFileAlreadyExist, ErrorSeverity::Exception);
//	  }
//	
//	  //now recreate the log file again . it will begin from scor.log
//		CrxLogWriter = EnterpriseLibraryContainer::Current->GetInstance<LogWriter^>();
//		
//		//reset coutner.
//		entryLineNumber = 0;
//
//		return true;
//}
//
//CrxLogger::~CrxLogger()
//{
//	delete CrxLogWriter;
//}

void CrxLogger::Write(String^ message)
{
	log->Info(message);	
}

void CrxLogger::Write(System::String ^message, ErrorSeverity lvl)
{	
	switch(lvl)
	{
		case ErrorSeverity::Debug:
			log->Debug(message);
			break;

		case ErrorSeverity::Error:
			log->Error(message);
			break;

		case ErrorSeverity::Exception:
			log->Error(message);
			break;

		case ErrorSeverity::Fatal:
			log->Fatal(message);
			break;

		case ErrorSeverity::Information:
			log->Info(message);
			break;
			
		case ErrorSeverity::Warning:
			log->Warn(message);
			break;

		default:
			break;
	}
}