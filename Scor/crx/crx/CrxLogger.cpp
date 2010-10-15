// This is the main DLL file.

#include "stdafx.h"

#include "CrxLogger.h"

using namespace CrxLogging;

//Constructor for CrxLogger
CrxLogging::CrxLogger::CrxLogger()
{
	//Get the LogWriter from enterprise library
	CrxLogWriter =  EnterpriseLibraryContainer::Current->GetInstance<LogWriter^>();
}

//Write method to write to log file and event logger
void CrxLogging::CrxLogger::Write(String^ message)
{
	//Write the passed message to the LogWriter
	CrxLogWriter->Write(message);
}