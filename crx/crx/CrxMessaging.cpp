#include "stdafx.h"
#include "CrxMessaging.h"
#include "crxCrossCutting.h"

using namespace System;// For String, Console
using namespace System::Text; //For String manipulation

// Add application specific namespaces
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace System::Xml;// For XML classes and enums
using namespace System::IO;// For FileStream


CrxMessagingManager::CrxMessagingManager()
{
	// Initialize the resource managers with appropriate resource files
	errRsrcErrMsg = gcnew ResourceManager("Scor.ErrorMessages", Assembly::GetExecutingAssembly());
	errRsrcGUIMsg = gcnew ResourceManager("Scor.GUIMessages", Assembly::GetExecutingAssembly());

}

//Returns an error message corresponding to the specified errorcode.Calling to main overloaded function
String ^CrxMessagingManager::GetMessage(int errorCode) 
{
	Boolean resFileData		= false;//value to set which file to use, set to false
	String^ tempValue		= nullptr;//Temporary string to convert int to string, set to null
	String^ retErrorString	= nullptr;//Get error string and return, set to null

	//Validation to use which resx file by checking the errorcode
	//if the error code is greater than 10000 and smaller than 14999 then resFiledaat is true and futher GUIMessages resx fiel will be used.
	//if the error code is not between the range then the ErrorMessages resx file will be used.
	if(errorCode >= GUIMGR_ERRORMSGS_MIN_NUMBER && errorCode <= GUIMGR_ERRORMSGS_MAX_NUMBER)
	{
		resFileData = true;
	}

	//converts error code to string
	tempValue = Convert::ToString(errorCode);
	
	//get the string from the related resx file
	retErrorString = CrxMessagingManager::GetMessage(tempValue , resFileData);

	//return the string to gui layer
	return retErrorString;
}

//Returns an error message corresponding to the specified errorcode.
String ^CrxMessagingManager::GetMessage(String^ stringCode, Boolean fileCode) 
{
	String^	errorString			   = nullptr;//Get error string and return, set to null
	
	try
	{	
		//validation to use the resx file as per the filecode
		//if filecode is true then access the GUIMessages.resx file else access the ErrorMessages.resx file
		if(fileCode == true)
		{
			errorString = GetGUIMessages(stringCode);
		}		
		else
		{
			errorString = GetErrorMessages(stringCode);
		}
		
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

//Returns an error message from GUIMessages resouce file corresponding to the specified errorcode.
String ^CrxMessagingManager::GetErrorMessages(String^ stringCode) 
{
	String^	errorMsgString		   = nullptr;//Get error string and return, set to null

	//Check whether default resource file is exists or not
	if(!File::Exists(_nameOfErrorResxfile))
	{ 
		throw gcnew CrxException(L"Resource file not found"); // File not found
	}

	errorMsgString = errRsrcErrMsg->GetString(stringCode);

	return errorMsgString;
}

//Returns an error message from ErrorMessages resource file corresponding to the specified errorcode.
String ^CrxMessagingManager::GetGUIMessages(String^ stringCode) 
{
	String^	errorGUIString		   = nullptr;//Get error string and return, set to null

	//Check whether default resource file is exists or not
	if(!File::Exists(_nameOfGUIResxfile))
	{ 
		throw gcnew CrxException(L"Resource file not found"); // File not found
	}

	errorGUIString = errRsrcGUIMsg->GetString(stringCode);

	return errorGUIString;
}