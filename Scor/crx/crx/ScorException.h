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
* @enum CustomErrorCode
* @brief	Contains the type of error code
*/
public enum class CustomErrorCode
{
	SystemErrorCode = -1,
	SpecialExceptionCode = -2
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
	 array<String^>^ _errorStringArr; //The string array list. Used to contain the string placeholder list.

	 //static const int _systemErrCode = -1;

 public:
	
	// /**
	//* The system error code of the error. Read only value.
	//*/
	//property int SystemErrorCode
	//{
	//	int get()
	//	{
	//		return _systemErrCode;
	//	}
	//}
	
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
	* The String Array. Will return the Array values. Read only value.
	*/
	property array<String^>^ ErrorStringArr
	{
		array<String^>^ get()
		{
			return _errorStringArr;
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

	/**
	* Constructor to raise application exceptions.
	* Should not be used for special exceptions.
	*
	* @param errorType	The severity of the error.
	* @param exceptionObject	The system exception to be re-thrown or exception message can also be used as a placeholder if required..
	* @param arr				The key string from resoruce file corresponding to the error message.
	*/
	ScorException(ErrorSeverity errorType, Exception^ exceptionObject, String^ arr);

	/**
	* Constructor to raise application exceptions.
	* Should not be used for system-raised exceptions.
	*
	* Logic of ScorException Constructor arguments handled in GUI as per araguments provided in the constructor
	* 	
	* If errorCode is not 0, errorKey is not null ,  errorType is not null,  exceptionObject is null and arr is null 
	* then the message will show the combination of errorCode, errorKey(string from resource file)
	* 		
	* If errorCode is not 0, errorKey is not null,  errorType is not null, exceptionObject is null and arr is not null
	* here the errorKey will be considered as string formatter, which will contain placeholder and will be replaced with the array string value provided
	* then the message will show the combination of errorCode, errorKey(string from resource file), exceptionObject message, and array string values
	*
	* @param errorCode			Integer error code to uniquely identify this error.
	* @param errorKey			The key string(Message Format) from resource file corresponding to the error message
	* @param errorType			The severity of the error.
	* @param exceptionObject	The system exception to be re-thrown or exception message can also be used as a placeholder if required..
	* @param arr				The string array list to hold placeholders.
	*/

	// TODO: Replace array with collection
	ScorException(int errorCode, String ^errorKey, ErrorSeverity errorType, Exception^ exceptionObject, ...array<String^>^ arr );

private:
	//made private to prevent "empty" exceptions.
	ScorException();

};

		}
	}
}