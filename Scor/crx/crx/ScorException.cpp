/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      ScorException.cpp
        
     Author       :		 Smarajit Mishra
 
     Description  :      Declaration for Cross-cutting Scor Exception class
*/


#include "stdafx.h"
#include "ScorException.h"


namespace AtCor { 
	namespace Scor { 
		namespace CrossCutting {

			ScorException::ScorException()
			{
				//Empty constructor. Cannot be called.
			}

			ScorException::ScorException(Exception^ excepObject)
			{
				this->_errorCode = Convert::ToInt32(CustomErrorCode::SystemErrorCode);//set error code to -1 so that we know that this is system raised
				this->_exceptionObject = excepObject; //copy the object
				this->_errorType = ErrorSeverity::Exception; //always raise system-generated exceptions with highest severity
				this->_errorKey = nullptr;
				this->_errorStringArr = gcnew array<String^>(0);
			}

			ScorException::ScorException(int errorCode, String ^errorKey, AtCor::Scor::CrossCutting::ErrorSeverity errorType) 
			{

				//copy the passed values to the exception object

				this->_errorCode = errorCode;
				this->_errorKey = errorKey;
				this->_errorType = errorType;
				this->_exceptionObject = nullptr; //set to null to show that this isnt raised by system.
				this->_errorStringArr = gcnew array<String^>(0);

			}

			ScorException::ScorException(int errorCode, String ^errorKey, AtCor::Scor::CrossCutting::ErrorSeverity errorType, Exception^ excepObject, ... cli::array<String^> ^arr)
			{
				//Checks array is null or not. 
				//If not null put the values from the array to the scorexception object array
				if(arr != nullptr)
				{
					this->_errorStringArr = gcnew array<String^>(arr->Length);
					for( int i = 0 ; i < arr->Length; i++)
					{
						this->_errorStringArr[i] = arr[i];
					}
				}
				//else set the length of scorexception object array to 0
				else
				{
					this->_errorStringArr = gcnew array<String^>(0);
				}
				this->_errorKey = errorKey;//set the error key from function parameter to scorexception object
				this->_errorCode = errorCode;//Set error code provided from the function paramter to scorexception object 
				this->_errorType = errorType;//Set the error code provided from the parameter to scorexception object 
				this->_exceptionObject = excepObject;//copy the object from the function parameter to scorexception object				
			}

			ScorException::ScorException(AtCor::Scor::CrossCutting::ErrorSeverity errorType, System::Exception ^exceptionObject, String ^arr)
			{
				//Checks array is null or not. 
				//If not null put the values from the array to the scorexception object array
				if(arr != nullptr)
				{
					this->_errorStringArr = gcnew array<String^>(1);
					this->_errorStringArr[0] = arr;
				}
				//else set the length of scorexception object array to 0
				else
				{
					this->_errorStringArr = gcnew array<String^>(0);
				}
				this->_errorKey = nullptr;//set the error key to nullptr
				this->_errorCode = Convert::ToInt32(CustomErrorCode::SpecialExceptionCode);//Set error code provided from the function paramter to scorexception object 
				this->_errorType = errorType;//Set the error code provided from the parameter to scorexception object 
				this->_exceptionObject = exceptionObject;//copy the object from the function parameter to scorexception object	
			}			

		}
	}
}