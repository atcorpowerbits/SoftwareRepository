#pragma once

#include "stdafx.h"
#include "ScorException.h"


namespace AtCor { 
	namespace Scor { 
		namespace CrossCutting {

			ScorException::ScorException()
			{
				//Empty constructor. Cannot be called.
			}

			/*ScorException::ScorException(ScorException^ scorExceptionObject)
			{
				this->_errorCode = scorExceptionObject->_errorCode;
				this->_exceptionObject = scorExceptionObject->_exceptionObject ; 
				this->_errorType = scorExceptionObject->_errorType; 
				this->_errorKey = scorExceptionObject->_errorKey;

			}*/

			ScorException::ScorException(Exception^ excepObject)
			{
				this->_errorCode = -1; //set error code to -1 so that we know that this is system raised
				this->_exceptionObject = excepObject; //copy the object
				this->_errorType = ErrorSeverity::Exception; //always raise system-generated exceptions with highest severity
				this->_errorKey = nullptr;
			}

			ScorException::ScorException(int errorCode, String ^errorKey, AtCor::Scor::CrossCutting::ErrorSeverity errorType) 
			{

				//copy the passed values to the exception object

				this->_errorCode = errorCode;
				this->_errorKey = errorKey;
				this->_errorType = errorType;
				this->_exceptionObject = nullptr; //set to null to show that this isnt raised by system.

			}

		}
	}
}