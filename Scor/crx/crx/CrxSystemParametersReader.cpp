#include "stdafx.h"
#include "CrxSystemParametersReader.h"
#include "CrxConfiguration.h"
#include "CrxMessaging.h"
#include "CrxLogger.h"
#include "CrxEventContainer.h"

using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting;

namespace AtCor { 
	namespace Scor { 
		namespace CrossCutting { 
			namespace Configuration 
{

CrxSytemParameters::CrxSytemParameters(CrxSytemParameters ^)
{
	//overloaded copy constructor.
	//Does nothing
}

CrxSytemParameters^ CrxSytemParameters::operator= (CrxSytemParameters)
{

	//implementing private assignment operator for singleton.
	return this;
}

CrxSytemParameters::CrxSytemParameters()
{
	try
	{
		//load the XML file inot an XElement and store
		this->parameters = XElement::Load(CrxSystemParameterInfo::FilePath);
	}
	catch(Exception^ excepObj)
	{
		//file may not be present
		throw gcnew ScorException(excepObj);
	}
}

String^ CrxSytemParameters::GetStringTagValue(System::String ^tagName)
{
	//call the base method
	return GetNestedTagValue(tagName);
}

int CrxSytemParameters::GetIntegerTagValue(System::String ^tagName)
{
	String ^ stringValue;

	//call the base method
	stringValue = GetNestedTagValue(tagName);

	try
	{
		//convert the result to integer
		return Convert::ToInt32(stringValue);
	}
	catch(Exception^ excepObj)
	{
		//attempted to convert a non integer type 
		throw gcnew ScorException(excepObj);
	}
}

String^ CrxSytemParameters::GetNestedTagValue(System::String ^nestedTags)
{
	array<String^>^ tagNameArray ;
	CrxLogger^ objLog				= nullptr;	// Object used to access logger class
	CrxMessagingManager^ objMsg		= nullptr;  // Object used to access messaging class

	//Create logger object
	objLog = CrxLogger::Instance;

	//Create messaging object
	objMsg = CrxMessagingManager::Instance;

	try
	{
		//get the individual tokens into an array of strings
		tagNameArray = nestedTags->Split('.');

		parentElement = parameters; //assign top level tag to parentElement

		//now loop through the array and look for each subtag
		for each (String^ tagName in tagNameArray)
		{
			//XElement requestedElement = this->parameters->Element(tagName); 
			parentElement = parentElement->Element(tagName);
			}

		//return the value of the last element
		return parentElement->Value;

	}
	catch(Exception^ )
	{
		StringBuilder^ errorMessage = gcnew StringBuilder(String::Empty);
		errorMessage = errorMessage->AppendFormat("{0} {1} ",Convert::ToString(CrxStructCommonResourceMsg::CrxErrXmlTagIncorrectErrCd),objMsg->GetMessage(CrxStructCommonResourceMsg::GuiDisplayColon));
		errorMessage = errorMessage->AppendFormat(objMsg->GetMessage(CrxStructCommonResourceMsg::CrxErrXmlTagIncorrectText),nestedTags);
		
		objLog->Write(errorMessage->ToString(),ErrorSeverity::Information);
		
		//The tagname may not be in the correct format or it may not be present in the XML file
		Object^ obj;
		ScorException^ check = gcnew ScorException (CrxStructCommonResourceMsg::CrxErrXmlTagIncorrectErrCd, CrxStructCommonResourceMsg::CrxErrXmlTagIncorrect, ErrorSeverity::Exception,nullptr,objMsg->GetMessage(CrxStructCommonResourceMsg::ContactAtcorSupportCommon));      
		CrxEventContainer::Instance->OnShowStatusEvent(obj, gcnew CrxShowStatusEventArgs(check));

		return String::Empty;
		//The tagname may not be in the correct format or it may not be present in the XML file
		//throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrXmlTagIncorrectErrCd, CrxStructCommonResourceMsg::CrxErrXmlTagIncorrect, ErrorSeverity::Exception );
	}

}
			}//End namespaces
		}
	}
}