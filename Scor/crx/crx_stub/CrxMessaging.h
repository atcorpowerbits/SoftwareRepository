/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
    Filename     :      facade.h
        
        Author       :  Deepak D'Souza
 
     Description  :      Declaration for Cross-cutting Logger namespace
*/

#include "crx.h"

using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;

//For reading resource file
using namespace System::Resources;
using namespace System::Globalization;
using namespace System::Threading;
using namespace System::Reflection;

/**
 * @namespace	CrxMessaging
 * @brief		This namespace implements messaging related cross-cutting functionalities.
 * 
 */
namespace AtCor {
namespace Scor {
namespace CrossCutting {
namespace Messaging {
	
	/**
	 * @class		CrxResourceFileManager
	 * @brief		CrxResourceFileManager will be used to read values from the Resource file.
	 */
	//TODO:This class is not completed and is not being used at present.
	private ref class CrxResourceFileManager
	{
		private:
			ResXResourceReader ^ResourceFileReader; //Member to hold a pointer to the reader
		public:
			/**
			* Constructor
			* TODO:This method is not yet complete/
			*/
			CrxResourceFileManager(); //Constructor
			/**
			* Gets the message corresponding to the specified key
			* @param messageKey	The key of the message.
			*/
			String ^GetMessageByKey(String ^messageKey); //Pass the message key. The method should search the resource file and return corresponding value.
	};

	/**
	 * @class		CrxMessagingManager
	 * @brief		This class will provide the apis for messaging.
	 */
	public ref class CrxMessagingManager
	{
		private:
			static CrxMessagingManager^ _instance = gcnew CrxMessagingManager(); /**< Instance to implement singleton. */
			
			/*
			* Displays the string passed to it.
			* @param[in] MessageString	The string to be displayed.
			*/
			bool DisplayString(String ^MessageString); //Instance to call the APIs from PL to display the string.
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
			* Displays the message coressponding to the specified key from the resource file.
			*
			* @return @c true if the operation was successful. @n
			*		  @c false if unsuccessful.
			*
			* @param[in] messageKey	The key corresponding to the required message.
			*/
			bool DisplayMessage(String ^messageKey);	//Method to pass a key to CrxResourceFileManager and display a method
			
			/**
			* Returns an error message corresponding to the specified integer error code.
			*
			* @return THe error message for the specified code
			*
			* @param[in] errorCode	The error code for which message is required.
			*/
			String ^GetMessage(int errorCode); //Method to pass an error code as an integer and obtain corresponding error message

	};

	/**
	 * @class		CrxMessagingException
	 * @brief		This class will provide errors for CrxMessaging namespace.
	 */
	public ref class CrxMessagingException:Exception
      {
      private:
            int _errCode;
      public: 
            /**
			* Default constructor
			*/
            CrxMessagingException(): _errCode(0) { }
            
			/**
			* Overloaded constructor
			* @param[in]	exError	The error code to intitialize this constructor with.
			*/
            CrxMessagingException(int exError): _errCode(exError) { }
            
			/**
			* Error code property of the exception
			*/ 
            property int ErrorCode
            {
                  int get()
                  {
                        return _errCode;
                  }

                  void set(int errCode)
                  {
                        _errCode = errCode;
                  }
            }
      };
}}}}


