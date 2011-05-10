/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :      CrxMessaging.cpp
        
	 Author       :      Smarajit Mishra
 
     Description  :      Functionality implementation for messaging manager
*/
#include "stdafx.h"
#include "CrxMessaging.h"
#include "ScorException.h"

// Add application specific namespaces
using namespace AtCor::Scor::CrossCutting::Messaging;	

CrxMessagingManager::CrxMessagingManager()
{
	// Initialize the resource managers with appropriate resource files
	errRsrcMsg = gcnew ResourceManager(CrxMsgStructInternal::NameOfAppResxfile, Assembly::GetExecutingAssembly());
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
String ^CrxMessagingManager::GetMessage(String^ strCode) 
{
	String^	errorString		= nullptr;//Get error string and return, set to null
	
	try
	{			
		//Get the message string through resource manager object
		errorString = errRsrcMsg->GetString(strCode);

		//validation to check string is returned or not, 
		//if string length is equals to zero then send the string "Error Code not found"
		if(errorString == nullptr)
		{
			errorString = (String^)CrxStructCommonResourceMsg::ErrorStringNotFound;
		}

		return errorString;
	}
	catch(Exception^ eObj)
	{
		// rethrow the exception
		throw gcnew ScorException(eObj);
	}
	finally 
	{
		// kept here for future reference and use
	}
}


Image ^CrxMessagingManager::GetImage(String^ strCode) 
{
	Image^	imagePrn		= nullptr;//Get error string and return, set to null
	
	try
	{
		//Get the message string through resource manager object
		Bitmap^ b = (Bitmap^) errRsrcMsg->GetObject(strCode);
		imagePrn = (Image^)b;

		return imagePrn;
	}
	catch(Exception^ eObj)
	{
		// rethrow the exception
		throw gcnew ScorException(eObj);
	}
	finally 
	{
		// kept here for future reference and use
	}
}

//TODO: Need to implement the validation for culture specific changes
bool CrxMessagingManager::CheckResourceFileExist()
{
	//bool	result		= true;//Holds the return, set to true

	////Check whether default resource file is exists or not
	//if(!File::Exists(CrxMsgStructInternal::NameOfAppResxfilePath))
	//{ 		
	//	//If not exist, return false
	//	result = false;		
	//}
	//return result;

	return (File::Exists(CrxMsgStructInternal::NameOfAppResxfilePath));
}
