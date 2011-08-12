/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      ScorException.h
        
     Author       :		 Deepak D'Souza	
 
     Description  :      Contains the scor exception class
*/

#pragma once
#include "Stdafx.h"

using namespace System;
using namespace System::Runtime::Serialization;

namespace AtCor { 
	namespace Scor { 
		namespace CrossCutting {

/**
* @enum ErrorSeverity
* @brief	Contains the type of exception/error/raised
*/
public enum class ErrorSeverity
{
	Information,
	Warning,
	Exception
};

/**
* @class ScorException
* @brief Exception class for Scor application.
*/
public ref class ScorException:Exception
{
	
 private:
	 int			_errorCode; //Integer error code. Set by capplication. Should be -1 for system raised exception.
	 ErrorSeverity	_errorType;	//The type of error, severity
	 String^		_errorKey;	//The string key used to obtains the localized resource from resx file
	 Exception^		_exceptionObject; //Exception object . Used to contain the system raised exception.

 public:


	/**
	* The error code of the error. Read only value.
	*/
	property int ErrorCode
	{
		int get()
		{
			return _errorCode;
		}
	}

	/**
	* The error severity . Read only value.
	*/
	property ErrorSeverity	ErrorType
	{
		ErrorSeverity get()
		{
			return _errorType;
		}

	}

	/**
	* The key string. Used to obtain the localised error string from resource file. Read only value.
	*/
	property String^ ErrorMessageKey
	{
		String^ get()
		{
			return _errorKey;
		}
	}

	/**
	* The exception object. Will be null for application raised exceptions. Read only value.
	*/
	property Exception^	ExceptionObject
	{
		Exception^ get()
		{
			return _exceptionObject;
		}
	}
	
	/**
	* Constructor to raise wrapped system exceptions.
	* Wrapps the system exception into a ScorException object.
	*
	* @param exceptionObject The system exception to be rethrown.
	*/
	ScorException(Exception^ exceptionObject);

	/**
	* Constructor to raise application exceptions.
	* Should not be used for system-raised exceptions.
	*
	* @param errorCode Integer error code to uniquely identify this error.
	* @param errorKey	The key string from resoruce file corresponding to the error message
	* @param errorType	The severity of the error.
	*/
	ScorException(int errorCode, String^ errorKey, ErrorSeverity errorType);

private:
	//made private to prevent "empty" exceptions.
	ScorException();

};

		}
	}
}