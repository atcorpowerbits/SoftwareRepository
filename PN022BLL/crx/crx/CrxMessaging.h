/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :      CrxMessaging.h
        
	 Author       :      Smarajit Mishra
 
     Description  :      Declaration for Cross-cutting Messaging namespace
*/

#include "CrxCrossCutting.h"

using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;

//For reading resource file
using namespace System::Resources;
using namespace System::Globalization;
using namespace System::Threading;
using namespace System::Reflection;

/**
 * @namespace	AtCor::Scor::CrossCutting::Messaging
 * @brief		This namespace implements messaging related cross-cutting functionalities.
 * 
 */
namespace AtCor {
	namespace Scor { 
		namespace CrossCutting { 
			namespace Messaging {	

			/**
			* @class CrxMessagingManager
			* @brief Class to manage message handling related functions. @n
			* This Class is mainly responsible for maintaining Scor.ApplicationMessages.resources file located in \“system\\Resources\” folder. @n
			* It has methods that enable read the value related to provided string.
			*/
			public ref class CrxMessagingManager
			{
				private:					
					
					//singleton instance
					static CrxMessagingManager^ _instance = gcnew CrxMessagingManager(); /**< Instance to implement singleton. */
					
					// holds the location of the configuration file
					static String^ _nameOfAppResxfile = L".\\system\\resources\\biz.ApplicationMessages.resources";
					
					//Create Resource manager object
					ResourceManager^ errRsrcMsg;

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
					* @param[in] strCode	The error string for which message is required.
					*/
					String ^GetMessage(String^ strCode); //Method to pass an error Stringcode as a string and obtain corresponding error message

			};

									
}
}
}
}


