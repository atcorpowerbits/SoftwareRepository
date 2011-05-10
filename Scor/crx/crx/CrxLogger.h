/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
    Filename     :      CrxLogger.h
        
        Author       :  Deepak D'Souza
 
     Description  :      Declaration for Cross-cutting Logger namespace
*/
 
#include "CrxCrossCutting.h"

#pragma once

//Include namespaces from Enterprise library.
using namespace System;
using namespace System::IO;	
using namespace Microsoft::Practices::EnterpriseLibrary::Logging;
using namespace Microsoft::Practices::EnterpriseLibrary::Common::Configuration;
using namespace Microsoft::Practices::EnterpriseLibrary::Logging::Configuration;

//Namepsace CrxLogging to include all Logging realted functionalities
/**
 * @namespace	AtCor::Scor::CrossCutting::Logging
 * @brief		This namespace implements the cross-cuttinng component for Logging.
 * 
 */
namespace AtCor { 
	namespace Scor {
		namespace CrossCutting {
			namespace Logging {

								/**
								 * @struct CrxLogStructInternal
								 * @brief Container for internal string. 	
								 */
private ref struct CrxLogStructInternal
{
	static	String^	LogFilePath			=	"system\\logs\\scor.log";
	static	String^	DateTimeFormat			=	"yyyyMMMddHHmmss";
	static	String^	LogFileName			=	"system\\logs\\scor_";
	static	String^	LogFileExt			=	".log";
};

								/**
								 * @class		CrxLogger
								 * @brief		This class provides logging funtionality for various laryers
								 */
								public ref class CrxLogger
								{
									private:
										
										//Declaring static variables names for exception numbers
										static const int CRX_ERR_FILE_ALREADY_EXIST = 102;

										LogWriter ^CrxLogWriter; /**< Variable to point to LogWriter instance.*/
										int entryLineNumber;
										

										/**
										* Constructor for this class. @n
										* Made it private so that the user cannot instantiate directly.
										*/
										CrxLogger(); 
										/**
										* An instance variable of the same class.@n
										* Calls the constructor internally to implement singleton class.
										*/
										static CrxLogger^ _instance = gcnew CrxLogger(); 
										/**
										* Copy Constructor @n
										* Made private to avoid being used with new(). Does nothing.
										*/
										  CrxLogger(const CrxLogger^)
										  {
							                    
										  }
							              
										  /**
										  * Overloaded assignment Operator. @n
										  * Returns this pointer to implement singleton.
										  */
										  CrxLogger^ operator=(const CrxLogger^) 
										  {
												 return this;
										  }  

										  /**
										  * Takes the last line nuber number from the current rolling file.
										  */
										  void GetLastWrittenLineNumber();
										  
											/**
											* Archives the current log file and creates a fresh current file.
											*/
										  bool RollLogFile();

											/**
											* Destructor for the class
											*/
										  ~CrxLogger();
										  

										  

									public:
										/**
										* Write method@n
										* User can pass string to write it to log.
										* @param[in]	message	The string to be written to log file.
										*/
										void Write(String^ message); 
									
										/**
										* Add property with custom get method to supply instance.@n
										* Used to implement singleton
										*/
										static property CrxLogger^ Instance
										{
												/**
												* Custom get method. @n
												* Returns a pointer to this singleton instance.
												*
												* @return	Pointer to this instance
												*/
											  CrxLogger^ get()
											  {
													return CrxLogger::_instance;
											  };
										};
								};


}
}
}
}


