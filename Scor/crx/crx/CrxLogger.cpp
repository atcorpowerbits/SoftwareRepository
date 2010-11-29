/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :      CrxLogger.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      Functionality implementation for Logger
*/

#include "stdafx.h"

#include "CrxLogger.h"

using namespace AtCor::Scor::CrossCutting::Logging;

//Constructor for CrxLogger
CrxLogger::CrxLogger()
{
	//Get the LogWriter from enterprise library
	CrxLogWriter =  EnterpriseLibraryContainer::Current->GetInstance<LogWriter^>();
}

//Write method to write to log file and event logger
void CrxLogger::Write(String^ message)
{
	//Write the passed message to the LogWriter
	CrxLogWriter->Write(message);
}