#include "stdafx.h"
#include "CrxMessaging.h"

using namespace System;

using namespace CrxMessaging;

//TODO:under construction
CrxResourceFileManager::CrxResourceFileManager()
{
	String ^tempstr;
	try
	{
		ResourceManager ^rm = ResourceManager::CreateFileBasedResourceManager("Resource.resx","D:\\My Docs\\Visual Studio 2008\\Projects\\DeepaksApp\\DeepaksApp\\",nullptr);
		tempstr = rm->GetString("S1");
		ResourceFileReader = gcnew ResXResourceReader("Resources.resx");
	}
	catch (Exception^)
	{
		throw gcnew CrxMessagingException(201);

	}
		
}

//TODO:under construction
String ^CrxResourceFileManager::GetMessageByKey(String^ messageKey)
{
	
//TODO: Under construction. 
	//This method is only used as a test stub but it can be used to 
	//develop a method for reading from a resource file.
	for each( DictionaryEntry d in ResourceFileReader)
	{
		//loop through all keys and ouptut them to console 
		try{
				Console::WriteLine(d.Key->ToString() + ":\t" + d.Value->ToString());
		}
		catch (Exception^)
		{
			//Handle any exception in this by throwing a Messaging excpetion
			throw gcnew CrxMessagingException(201);

		}
	}
	//No string to return right now . Have to change this
	return nullptr;
}

CrxMessagingManager::CrxMessagingManager()
{
	//TODO: Empty. Nothing to do right now but need to create an instance of CrxResourceFileManager here
}

//Takes a string and displays it directly using a message box
//TODO:This stub has to be developed.
bool CrxMessagingManager::DisplayString(String ^MessageString)
{
	MessageBox::Show(MessageString);
	return true;
}


//Stub: This method takes a message key and displays it directly on the screen.
//TODO: Implement functionalityto search for the speicifed key in a resource file and then pass it to DisplayString() 
bool CrxMessagingManager::DisplayMessage(String ^messageKey)
{
	DisplayString(messageKey);
	return true;
}

//Returns an error message corresponding to the specified errorcode.
String ^CrxMessagingManager::GetMessage(int errorCode) 
{
	//Todo: for the tiembeing we will pass the error code and obtain the message by a switch-case. Should be implemented via the resource file.
	switch(errorCode)
	{
	case 100:
		return L"Scor configuration file does not exist.";		
	case 101:
		return L"Scor configuration file is corrupted.";
	case 102:
		return L"Scor configuration file cannot be accessed.";
	case 200:
		return L"An exception occured in Messaging component.";
	case 201:
		return L"An error occured while trying to access the resource file.";
    case 10000:
        return L"Scor application loaded successfully.";
    case 10001:
        return L"Application exited successfully.";
	default:
		return L"Error Code not found";

	}

	//Todo: return the value from the resource file using the specified keystring
	return L"";
}