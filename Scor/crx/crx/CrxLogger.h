/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
    Filename     :      facade.h
        
        Author       :  Deepak D'Souza
 
     Description  :      Declaration for Cross-cutting Logger namespace
*/
 

// CrxLogger.h

#pragma once

//Include namespaces from Enterprise library.
using namespace System;
using namespace System::Configuration;
using namespace Microsoft::Practices::EnterpriseLibrary::Logging;
using namespace Microsoft::Practices::EnterpriseLibrary::Common::Configuration;

//Namepsace CrxLogging to include all Logging realted functionalities
/**
 * @namespace	CrxLogging
 * @brief		This namespace implements the cross-cuttinng component for Logging.
 * 
 */
namespace AtCor {
namespace Scor {
namespace CrossCutting {
namespace Logging {

	/**
	 * @class		CrxLogger
	 * @brief		This class provides logging funtionality for various laryers
	 */
	public ref class CrxLogger
	{
		private:
			
			LogWriter ^CrxLogWriter; /**< Variable to point to LogWriter instance.*/
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

	/**
	 * @class		CrxLoggingException
	 * @brief		This class is used to implement exceptions for CrxLogging namespace.
	 */
      public ref class CrxLoggingException:Exception
      {
      private:
            int _errCode; /**< Private variable for error code.*/
      public: 
            /**
			* Default constructor
			*/
            CrxLoggingException(): _errCode(0) { }
            /**
			* Overloaded constructor
			* @param[in]	exError	The error code to intitialize this constructor with.
			*/
            CrxLoggingException(int exError): _errCode(exError) { }
            
			/**
			* Error code property of the exception
			*/ 
            property int ErrorCode
            {
				/**
				* Gets the error code of this instance
				*
				* @return The error code 
				*/ 
                  int get()
                  {
                        return _errCode;
                  }
				
					/**
					* Sets the error code for this instance
					*
					* @param[in] exError The error code to set for this instance.
					*/
                  void set(int exError)
                  {
                        _errCode = exError;
                  }
            }
      };

}
}
}
}