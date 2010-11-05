/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :      CrxMessaging.h
        
	 Author       :      Smarajit Mishra
 
     Description  :      Declaration for Cross-cutting Messaging namespace
*/
#pragma once

//#include "CrxCrossCutting.h"

using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;

//For reading resource file
using namespace System::Resources;
using namespace System::Globalization;
using namespace System::Threading;
using namespace System::Reflection;

//using namespace AtCor::Scor::CrossCutting;

/**
 * @namespace	CrxMessaging
 * @brief		This namespace implements messaging related cross-cutting functionalities.
 * 
 */
namespace AtCor {
	namespace Scor { 
		namespace CrossCutting { 
			namespace Messaging {	
			
			public ref class CrxMessagingManager
			{
				private:
					
					//Declaring Static variables names for GUI number validation
					static const int GUIMGR_ERRORMSGS_MIN_NUMBER = 10000;
					static const int GUIMGR_ERRORMSGS_MAX_NUMBER = 14999;

					//singleton instance
					static CrxMessagingManager^ _instance = gcnew CrxMessagingManager(); /**< Instance to implement singleton. */
					
					// holds the location of the configuration file
					static String^ _nameOfErrorResxfile = L".\\system\\resources\\Scor.ErrorMessages.resources";
					static String^ _nameOfGUIResxfile = L".\\system\\resources\\Scor.GUIMessages.resources";
					
					ResourceManager^ errRsrcErrMsg;
					ResourceManager^ errRsrcGUIMsg;

					/**
					* Default constructor.
					*/
					CrxMessagingManager();
						
					/**
					* Copy Constructor
					*/
					CrxMessagingManager(const CrxMessagingManager^)
					{
					}
		          
					/**
					* Assignment Operator
					*/
					CrxMessagingManager^ operator=(const CrxMessagingManager^) 
				    {
						 return this;
					} 

					/**
					* Returns an error message corresponding to the specified integer error code.
					*
					* @return The error message for the specified code.
					*
					* @param[in] errorCode	The error code for which message is required.
					*/
					String ^GetErrorMessages(String^ stringCode); //Method to pass an error code as an string and obtain corresponding error message

					/**
					* Returns an error message corresponding to the specified integer error code.
					*
					* @return The error message for the specified code.
					*
					* @param[in] errorCode	The error code for which message is required.
					*/
					String ^GetGUIMessages(String^ stringCode); //Method to pass an error code as an string and obtain corresponding error message

				public:
					/**
					* Property with overriden get method to supply instance
					*/
					static property CrxMessagingManager^ Instance
					{
						  CrxMessagingManager^ get()
						  {
								return CrxMessagingManager::_instance;
						  };
					};
										
					/**
					* Returns an error message corresponding to the specified integer error code.
					*
					* @return The error message for the specified code. Calls Overloaded GetMessage String internally
					*
					* @param[in] errorCode	The error code for which message is required.
					*/
					String ^GetMessage(int errorCode); //Method to pass an error code as an integer and obtain corresponding error message
					/**
					* Returns an error message corresponding to the specified integer error code.
					*
					* @return The error message for the specified code
					*
					* @param[in] StringCode	The error string for which message is required.
					* @param[in] fileCode	The resx file to be used.
					*/
					String ^GetMessage(String^ stringCode , bool fileCode); //Method to pass an error Stringcode as a string and obtain corresponding error message

			};

									
}
}
}
}


