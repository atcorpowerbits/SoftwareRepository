#include "stdafx.h"
#include "CrxMessaging.h"

using namespace System;// For String, Console
using namespace System::Text; //For String manipulation

// Add application specific namespaces
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace System::Xml;// For XML classes and enums
using namespace System::IO;// For FileStream


CrxMessagingManager::CrxMessagingManager()
{
	// Initialize the resource managers with appropriate resource files
	errRsrcMsg = gcnew ResourceManager("Scor.ApplicationMessages", Assembly::GetExecutingAssembly());

}

//Returns an error message corresponding to the specified errorcode.Calling to main overloaded function
String ^CrxMessagingManager::GetMessage(int errorCode) 
{
	String^ tempValue		= nullptr;//Temporary string to convert int to string, set to null
	String^ retErrorString	= nullptr;//Get error string and return, set to null

	//converts error code to string
	tempValue = Convert::ToString(errorCode);
	
	//get the string from the related resx file
	retErrorString = CrxMessagingManager::GetMessage(tempValue);

	//return the string to gui layer
	return retErrorString;
}

//Returns an error message corresponding to the specified errorcode.
String ^CrxMessagingManager::GetMessage(String^ stringCode) 
{
	String^	errorString		= nullptr;//Get error string and return, set to null
	
	try
	{	
		//Check whether default resource file is exists or not
		if(!File::Exists(_nameOfAppResxfile))
		{ 
			throw gcnew CrxException(L"Resource file not found"); // File not found
		}

		//Get the message string through resource manager object
		errorString = errRsrcMsg->GetString(stringCode);

		//validation to check string is returned or not, 
		//if string length is equals to zero then send the string "Error Code not found"
		if(errorString->Length == 0)
		{
			errorString = L"Error Code not found";
		}

		return errorString;
	}
	catch(Exception^ eObj)
	{
		// rethrow the exception
		throw gcnew CrxException(eObj);
	}
	finally 
	{
		// kept here for future reference and use
	}
}

