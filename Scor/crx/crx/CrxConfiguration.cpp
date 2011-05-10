/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      CrxConfiguration.cpp
        
     Author       :		 Smarajit Mishra
 
     Description  :      Functionality implementation for configuration manager
*/

#include "stdafx.h"
#include "CrxConfiguration.h"
#include "CrxCrossCutting.h"
#include "ScorException.h"
#include "CrxMessaging.h"

using namespace System;				// For String, Console
using namespace System::IO;			// For FileStream

using namespace AtCor::Scor::CrossCutting::Messaging;
// Add application specific namespaces

//To get General Default Settings from file
void CrxConfigManager::GetGeneralDefaultSettings(CrxStructGeneralSetting^ objGenSettings)
{
	CrxConfigManager::GetSettings(CrxConfigXmlTag::General,CrxConfigXmlTag::Default);

	// as there is no assignment operator defined, doing memberwise copy
	objGenSettings->PatientPrivacy				= _gSetInternal->PatientPrivacy;
	objGenSettings->BloodPressureEntryOptions	= _gSetInternal->BloodPressureEntryOptions;
	objGenSettings->HeightandWeightUnit			= _gSetInternal->HeightandWeightUnit;
	objGenSettings->CommsPort					= _gSetInternal->CommsPort;
	objGenSettings->ReportTitle					= _gSetInternal->ReportTitle;
	objGenSettings->ReportLogoPath				= _gSetInternal->ReportLogoPath;
	objGenSettings->ServerName					= _gSetInternal->ServerName;
	objGenSettings->SourceData					= _gSetInternal->SourceData;
	objGenSettings->CultureInfo					= _gSetInternal->CultureInfo;
	objGenSettings->MachineName					= _gSetInternal->MachineName;
	objGenSettings->StartupMode					= _gSetInternal->StartupMode;
	objGenSettings->StartupScreen				= _gSetInternal->StartupScreen;
	objGenSettings->EnvironmentSettings			= CrxConfigStructInternal::DefaultEnvironment;
	objGenSettings->PrinterName					= _gSetInternal->PrinterName;
}

//To get User Settings from the file
void CrxConfigManager::GetGeneralUserSettings()
{
	CrxConfigManager::GetSettings(CrxConfigXmlTag::General,CrxConfigXmlTag::User);
}

//To Set General User Setting 
void CrxConfigManager::SetGeneralUserSettings(CrxStructGeneralSetting^ gs)
{
	CrxConfigManager::SetSettings(CrxConfigXmlTag::General,CrxConfigXmlTag::User,gs,nullptr);
}

//To get PWV Default Settings from file
void CrxConfigManager::GetPwvDefaultSettings(CrxStructPwvSetting^ objPwvSettings)
{
	CrxConfigManager::GetSettings(CrxConfigXmlTag::Pwv,CrxConfigXmlTag::Default);

	objPwvSettings->CaptureTime			= _pSetInternal->CaptureTime;
	objPwvSettings->PWVDistanceMethod	= _pSetInternal->PWVDistanceMethod;
	objPwvSettings->FemoralToCuff		= _pSetInternal->FemoralToCuff;
	objPwvSettings->PWVDistanceUnits	= _pSetInternal->PWVDistanceUnits;
	objPwvSettings->ReferenceRange		= _pSetInternal->ReferenceRange;
	objPwvSettings->SimulationType		= _pSetInternal->SimulationType;
	objPwvSettings->DefaultReport		= _pSetInternal->DefaultReport;
}

//To get PWV User Settings from the file
void CrxConfigManager::GetPwvUserSettings()
{
	CrxConfigManager::GetSettings(CrxConfigXmlTag::Pwv,CrxConfigXmlTag::User);
}

//To Set PWV User Setting 
void CrxConfigManager::SetPwvUserSettings(CrxStructPwvSetting^ ps)
{
	CrxConfigManager::SetSettings(CrxConfigXmlTag::Pwv,CrxConfigXmlTag::User,nullptr,ps);
}

//***************************************************************
//Set the node values in XML file as per Section and SubSection
//***************************************************************
void CrxConfigManager::SetSettings(String^ Section, String^ SubSection, CrxStructGeneralSetting^ gs ,CrxStructPwvSetting^ ps)
{
	//Variables Declaration
	FileStream^ fs		= nullptr;//Contains FileAccessinfo, Set it to null
	XmlReader^ reader	= nullptr;//contains the XML data, Set it to null
	XmlDocument^ doc	= nullptr;//Contains the XML document, Set it to null
	XmlNode^ node		= nullptr;//Contains node list, Set it to null

	try
	{
		//Check whether file is exists or not
		if(!File::Exists(_nameOfFile))
		{ 
			throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileNotExistErrCd, CrxStructCommonResourceMsg::CrxErrFileNotExist, ErrorSeverity::Exception);// File not found
		}		
		
		//Check whether File Access is provided or not
		try
		{			
			fs = gcnew FileStream(_nameOfFile,FileMode::Open);
		}
		catch(Exception^)
		{
			throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCannotAccessErrCd, CrxStructCommonResourceMsg::CrxErrFileCannotAccess, ErrorSeverity::Exception);// File not accessable
		}

		//Check whether have the access to write or not
		if(!fs->CanWrite)
		{
			throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCannotAccessErrCd, CrxStructCommonResourceMsg::CrxErrFileCannotAccess, ErrorSeverity::Exception);// File not accessable
		}
		
		//Close the file Access Object
		fs->Close();
        fs = nullptr;

		//Read the XML file from the provided path
		reader = XmlReader::Create(_nameOfFile);

		//Create the doc object
		doc = gcnew XmlDocument();

		//Load the XML data from reader to the doc
		doc->Load(reader);
		
		//Close the XML reader data
		reader->Close();
        reader = nullptr;
		
		// get the nodes collection from the file
		node = doc->DocumentElement;
		
		//Calls the SetSettingsNode to Set values in the config file
		CrxConfigManager::SetSettingsNode(Section, SubSection, gs, ps, node);
		
		
		doc->Save(_nameOfFile);	
		
	}
	catch (XmlException^) 
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);// any xml exception is rethrown as corrupt file exception
	}
	
	finally 
	{
		//Close the file Access Object
		if(fs)
		{
			fs->Close();
		}

		if (reader && (reader->ReadState != ReadState::Closed)) 
		{
			reader->Close();
		}		
	}
}

void CrxConfigManager::SetSettingsNode(String^ Section, String^ SubSection, CrxStructGeneralSetting^ gs,CrxStructPwvSetting^ ps, XmlNode^ node)
{
	bool startflag = false;		//bool value containinf true or false
	XmlNode^ node1 = nullptr;	//Contains node1 list, Set it to null
	XmlNode^ node2 = nullptr;	//Contains node2 list, Set it to null
	XmlNode^ node3 = nullptr;	//Contains node3 list, Set it to null
	XmlNode^ node4 = nullptr;	//Contains node4 list, Set it to null

	//Check if node is empty or not, if empty throw exception
	if (node == nullptr)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);
	}

	//Processes each node for values
	//Loop for node1(SystemSetting) containing Elements and values
	for each(node1 in node->ChildNodes)
	{
		//Loop for node2(General/PWV) containing Elements and values
		for each (node2 in node1->ChildNodes)
		{
			//If Node2(General/PWV) matches with Section values then loop will continue
			 if (node2->Name->ToUpper() == Section)
			 {
				//Loop for node3(User/Default) containing Elements and values
				for each (node3 in node2->ChildNodes)
				 {
					//If Node3(User/Default) matches with Section values then loop will continue
					if (node3->Name->ToUpper() == SubSection)
					{
						//Loop for node4(User/Default Settings elements)containing Elements and values
						for each (node4 in node3->ChildNodes)
						 {
							//Flap validating for loop
							startflag = true;
							
							if(Section == CrxConfigXmlTag::General)
							{
								CrxConfigManager::SetGeneralSettingsNode(gs, node4);
							}
							else if(Section == CrxConfigXmlTag::Pwv)
							{
								CrxConfigManager::SetPwvSettingsNode(ps, node4);
							}
							else
							{
								// this is a unknown section, raise exception
								throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);
							}
						 }
					  }
				 }
			}
		}		  
	}
	if (startflag == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);
	}
}

void CrxConfigManager::SetGeneralSettingsNode(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	String^ SubSectionNodeName = nullptr;////Contains the Subsection name, Set value to null

	//Temporary storing SubSection Settings Element name
	SubSectionNodeName = node->Name->ToUpper();

	//Calls function if node element is Patient Privacy
	if (SubSectionNodeName == CrxConfigXmlTag::PatientPrivacy)
	{	
		CrxConfigManager::SetPatientPrivacy(gs, node);		
	}
	//Calls function if node element is Height and Weight
    else
	if (SubSectionNodeName == CrxConfigXmlTag::HeightAndWeightUnits)
	{	
		CrxConfigManager::SetHeightWeight(gs, node);
	}
	//Calls function if node element is Blood Pressure Option
    else
	if (SubSectionNodeName == CrxConfigXmlTag::BloodPressureEntryOptions)
	{	
		CrxConfigManager::SetBloodPressureOption(gs, node);		
	}
	//Calls function if node element is Comms Port
	else
	if(SubSectionNodeName == CrxConfigXmlTag::CommsPort)
	{
		CrxConfigManager::SetCommsPort(gs, node);
	}
	//Calls function if node element is Report Title
	else
	if(SubSectionNodeName == CrxConfigXmlTag::ReportTitle)
	{									
		CrxConfigManager::SetReportTitle(gs, node);
	}
	//Calls function if node element is Report Logo Path
	else
	if(SubSectionNodeName == CrxConfigXmlTag::ReportLogoPath)
	{
		CrxConfigManager::SetReportLogoPath(gs, node);
	}
	//Calls function if node element is Server Name
	else
	if(SubSectionNodeName == CrxConfigXmlTag::ServerName)
	{
		CrxConfigManager::SetServerName(gs, node);
	}
	//Calls function if node element is Source Data
	else
	if(SubSectionNodeName == CrxConfigXmlTag::SourceData)
	{									
		CrxConfigManager::SetSourceData(gs, node);
	}
	//Calls function if node element is Culture Info
	else
	if(SubSectionNodeName == CrxConfigXmlTag::CultureInfo)
	{
		CrxConfigManager::SetCultureInfo(gs, node);
	}
	//Calls function if node element is Machine Name
	else
	if(SubSectionNodeName == CrxConfigXmlTag::MachineName)
	{
		CrxConfigManager::SetMachineName(gs, node);
	}
	//Calls function if node element is StartupMode
	else
	if(SubSectionNodeName == CrxConfigXmlTag::StartupMode)
	{
		
	}
	//Calls function if node element is StartupScreen
	else
		if(SubSectionNodeName == CrxConfigXmlTag::StartupScreen)
	{
		
	}
	//Calls function if node element is Config Printer
	else
	if(SubSectionNodeName == CrxConfigXmlTag::PrinterName)
	{
		CrxConfigManager::SetPrinterName(gs, node);
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file
	}
}

void CrxConfigManager::SetPwvSettingsNode(CrxStructPwvSetting^ ps, XmlNode^ node)
{
	String^ SubSectionNodeName = nullptr;

	SubSectionNodeName = node->Name->ToUpper();

   //Calls function if node element is PWV Distance Methods
	if (SubSectionNodeName == CrxConfigXmlTag::PwvDistanceMethod)
	{	
		CrxConfigManager::SetPwvDistanceMethods(ps, node);		
	}
	//Calls function if node element is FemoralToCuff
    else
	if (SubSectionNodeName == CrxConfigXmlTag::FemoralToCuff)
	{	
		CrxConfigManager::SetFemoralToCuff(ps, node);
	}
	//Calls function if node element is PWV Distance Units
    else
	if (SubSectionNodeName == CrxConfigXmlTag::PwvDistanceUnits)
	{	
		CrxConfigManager::SetPwvDistanceUnits(ps, node);		
	}
	//Calls function if node element is Capture Time
	else
	if(SubSectionNodeName == CrxConfigXmlTag::CaptureTime)
	{
		CrxConfigManager::SetCaptureTime(ps, node);
	}
	//Calls function if node element is Reference Range
	else
	if(SubSectionNodeName == CrxConfigXmlTag::ReferenceRange)
	{									
		CrxConfigManager::SetReferenceRange(ps, node);
	}
	//Calls function if node element is Simulation Type
	else
	if(SubSectionNodeName == CrxConfigXmlTag::SimulationType)
	{
		CrxConfigManager::SetSimulationType(ps, node);
	}
	//Calls function if node element is Default Report
	else
	if(SubSectionNodeName == CrxConfigXmlTag::DefaultReport)
	{
		CrxConfigManager::SetDefaultReport(ps, node);
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file
	}
}

//*********************************************
//Get the node values from XML file as per Section and SubSection
//*********************************************
void CrxConfigManager::GetSettings(String^ Section, String^ SubSection)
{
	bool breakflag				= false;	//bool value containing true or false. True to break the loop
	bool startflag				= false;	//bool value containing true or false. True to Start to store
	XmlReader^ reader			= nullptr;	//Store the XML data
	String^ GetXMLSection		= nullptr;	//Gets the XML section name
	String^ GetSectionName		= nullptr;  //Store section name to get the value
	String^ ReaderValue			= nullptr;  //Store XML Node Reader value
	String^ configXMLElements   = CrxConfigXmlTag::ConfigXmlElementsList;

	try 
	{
		//Check whether file is exists or not
		if(!File::Exists(_nameOfFile))
		{
			throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileNotExistErrCd, CrxStructCommonResourceMsg::CrxErrFileNotExist, ErrorSeverity::Exception);// File not found
		}
	
		//Reads the XML data from filepath and store in reader object
		reader = XmlReader::Create(_nameOfFile); 

		//Get in the loop in each node to get values
		while (reader->Read()) 
		{
			switch (reader->NodeType) 
			{
				//Check if node is for XML Declarations
				case XmlNodeType::XmlDeclaration: 
				//Check if node is for Whitespace Declarations
				case XmlNodeType::Whitespace: 
				//Check if node is foe Comment Type
				case XmlNodeType::Comment:
					break;

				//Check if node is an element
				case XmlNodeType::Element: 					
					//Stores Element name temporarily in Upper Case
					GetXMLSection = reader->Name->ToUpper();
					//Validate if the Element name is valid or not, if not, throws exception
					if(!configXMLElements->Contains(CrxConfigXmlTag::TagSeparator + GetXMLSection + CrxConfigXmlTag::TagSeparator))
					{
						throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file
					}

					if(Section == GetXMLSection)
					{
						GetSectionName = Section;
					}
					//Create flag set when to start Getting value from config file
					if(GetSectionName == Section && reader->Name->ToUpper() == SubSection) 
					{
						startflag = true;
					}	 
					//Check if the Element is Empty or not, if yes, throws exception
                    if (reader->IsEmptyElement) 
					{
						throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file
					}
					break; 

				//Check if node is an end element
				case XmlNodeType::EndElement: 

					//Create flag set when to stop Getting value from config file
					if(GetSectionName == Section && reader->Name->ToUpper() == SubSection) 
					{
						breakflag = true; 
					}
					break; 

				//Check if node have a text value
				case XmlNodeType::Text: 
					//Check whether to start Getting vlaues from config file or not, if false break
					if(startflag == false)
					{
						break;
					}
				
					//Store the Text value temporarily
					ReaderValue = reader->Value->Trim();
					
					//Call GetSettingsNode to get value
					CrxConfigManager::GetSettingsNode(Section, SubSection, GetXMLSection , ReaderValue);
				
				break; 
				
				//if none of the switch case are valid for node, then default and throw exception
				default: 
					throw gcnew ScorException(CrxStructCommonResourceMsg::CrxUnknownExceptionErrCd, CrxStructCommonResourceMsg::CrxUnknownException, ErrorSeverity::Exception);
			}
			if (breakflag) 
			{
				break; 
			}
		} // End While
			
	}
	//Catch if any of the exception occurs in XML Reader
	catch (XmlException^) 
	{
		//Throws again an exception
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);// any xml exception is rethrown as corrupt file exception
	}
	//Close all open files
	finally 
	{
		if (reader && (reader->ReadState != ReadState::Closed)) 
		{
			reader->Close();
		}
	}
}

void CrxConfigManager::GetSettingsNode(String^ Section, String^ SubSection, String^ SubSectionNode , String^ ReaderValue)
{
	//Call General or PWV Seeting functions
	if(Section == CrxConfigXmlTag::General)
	{
		//Call GetGeneralSettingsNode function to get values of General Settings
		CrxConfigManager::GetGeneralSettingsNode(SubSection,SubSectionNode,ReaderValue);
	}
	else 
		if(Section == CrxConfigXmlTag::Pwv)
	{
		//Call GetPWVSettingsNode function to get values of PWV Settings
		CrxConfigManager::GetPwvSettingsNode(SubSection,SubSectionNode,ReaderValue);
	}

}

void CrxConfigManager::GetGeneralSettingsNode(String^ SubSection, String^ SubSectionNode , String^ ReaderValue)
{
	//Calls function if node element is Patient Privacy
	if(SubSectionNode == CrxConfigXmlTag::PatientPrivacy)
	{
		CrxConfigManager::GetPatientPrivacy(SubSection,ReaderValue);
	}
	//Calls function if node element is Height and Weight
	else
	if(SubSectionNode == CrxConfigXmlTag::HeightAndWeightUnits)
	{
		CrxConfigManager::GetHeightWeight(SubSection,ReaderValue);

	}
	//Calls function if node element is Blood Pressure Option
	else
	if(SubSectionNode == CrxConfigXmlTag::BloodPressureEntryOptions)
	{
		CrxConfigManager::GetBloodPressureOption(SubSection,ReaderValue);
	}
	//Calls function if node element is Comms Port
	else
	if(SubSectionNode == CrxConfigXmlTag::CommsPort)
	{
		CrxConfigManager::GetCommsPort(SubSection,ReaderValue);

	}
	//Calls function if node element is Report Title
	else
	if(SubSectionNode == CrxConfigXmlTag::ReportTitle)
	{
		CrxConfigManager::GetReportTitle(SubSection,ReaderValue);

	}
	//Calls function if node element is Report Logo Path
	else
	if(SubSectionNode == CrxConfigXmlTag::ReportLogoPath)
	{
		CrxConfigManager::GetReportLogoPath(SubSection,ReaderValue);
	}
	//Calls function if node element is Server Name
	else
	if(SubSectionNode == CrxConfigXmlTag::ServerName)
	{
		CrxConfigManager::GetServerName(SubSection,ReaderValue);
	}
	//Calls function if node element is Source Data
	else
	if(SubSectionNode == CrxConfigXmlTag::SourceData)
	{
		CrxConfigManager::GetSourceData(SubSection,ReaderValue);
	}
	//Calls function if node element is CultureInfo
	else
	if(SubSectionNode == CrxConfigXmlTag::CultureInfo)
	{
		CrxConfigManager::GetCultureInfo(SubSection,ReaderValue);
	}
	//Calls function if node element is MachineName
	else
	if(SubSectionNode == CrxConfigXmlTag::MachineName)
	{
		CrxConfigManager::GetMachineName(SubSection,ReaderValue);
	}
	//Calls function if node element is StartupMode
	else
	if(SubSectionNode == CrxConfigXmlTag::StartupMode)
	{
		CrxConfigManager::GetStartupMode(SubSection,ReaderValue);
	}
	//Calls function if node element is StartupScreen
	else
	if(SubSectionNode == CrxConfigXmlTag::StartupScreen)
	{
		CrxConfigManager::GetStartupScreen(SubSection,ReaderValue);
	}
	//Calls function if node element is Config Printer
	else
	if(SubSectionNode == CrxConfigXmlTag::PrinterName)
	{
		CrxConfigManager::GetConfigPrinter(SubSection,ReaderValue);
	}
	//If none of the node element matches then throw exception
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file
	}
}
void CrxConfigManager::GetPwvSettingsNode(String^ SubSection, String^ SubSectionNode , String^ ReaderValue)
{
	//Calls function if node element is PWV Distance Methods
	if(SubSectionNode == CrxConfigXmlTag::PwvDistanceMethod)
	{
		CrxConfigManager::GetPwvDistanceMethods(SubSection,ReaderValue);
	}
	//Calls function if node element is FemoralToCuff
	else
	if(SubSectionNode == CrxConfigXmlTag::FemoralToCuff)
	{
		CrxConfigManager::GetFemoralToCuff(SubSection,ReaderValue);

	}
	//Calls function if node element is PWV Distance Units
	else
	if(SubSectionNode == CrxConfigXmlTag::PwvDistanceUnits)
	{
		CrxConfigManager::GetPwvDistanceUnits(SubSection,ReaderValue);
	}
	//Calls function if node element is Capture Time
	else
	if(SubSectionNode == CrxConfigXmlTag::CaptureTime)
	{
		CrxConfigManager::GetCaptureTime(SubSection,ReaderValue);

	}
	//Calls function if node element is Reference Range
	else
	if(SubSectionNode == CrxConfigXmlTag::ReferenceRange)
	{
		CrxConfigManager::GetReferenceRange(SubSection,ReaderValue);

	}
	//Calls function if node element is Simulation Type
	else
	if(SubSectionNode == CrxConfigXmlTag::SimulationType)
	{
		CrxConfigManager::GetSimulationType(SubSection,ReaderValue);
	}
	//Calls function if node element is Default Report
	else
	if(SubSectionNode == CrxConfigXmlTag::DefaultReport)
	{
		CrxConfigManager::GetDefaultReport(SubSection,ReaderValue);
	}	
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
}

//***********************************************************************
//Get General Settings Functions
//***********************************************************************
void CrxConfigManager::GetPatientPrivacy(String^ SubSection, String^ ReaderValue)
{
	//Get the Patient Privacy Details
	//Temporary variables
	bool PatientPrivacyValue = false;
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();

	chkVal = CrxConfigXmlTag::CheckYesNoValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
	PatientPrivacyValue = (tempValue == CrxConfigXmlTag::UpperYES);

	if(SubSection == CrxConfigXmlTag::Default)
	{
		_gSetInternal->PatientPrivacy = PatientPrivacyValue;
	}
	else
	{
		_instance->_generalSettings->PatientPrivacy = PatientPrivacyValue;
	}
}

void CrxConfigManager::GetHeightWeight(String^ SubSection, String^ ReaderValue)
{
	//Get the Height and weight Details
	//Temporary variables
	int HeightWeight = 0; 
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigHeightandWeightUnits::CompareStr;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}

	HeightWeight = (tempValue == CrxConfigHeightandWeightUnits::Metric ? Convert::ToInt32(CrxGenPwvValue::CrxGenHeightWeightMetric) : Convert::ToInt32(CrxGenPwvValue::CrxGenHeightWeightImperial));
	if(SubSection == CrxConfigXmlTag::Default)
	{
		_gSetInternal->HeightandWeightUnit = HeightWeight;
	}
	else
	{
		_instance->_generalSettings->HeightandWeightUnit = HeightWeight;
	}
}

void CrxConfigManager::GetBloodPressureOption(String^ SubSection, String^ ReaderValue)
{
	//Get the Get Blood Pressure Details
	//Temporary variables
	int BloodPressureValue = 0;
	String^ tempValue  = nullptr;
	
	tempValue  = ReaderValue->ToUpper();

	tempValue = tempValue->Replace(CrxConfigXmlTag::Blank,String::Empty);

	if(tempValue == CrxConfigBloodPressureOption::SPandDP)
	{
		//BloodPressureValue = 0;
		BloodPressureValue = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxGenBPOptSPandDP);
	}
	else 
	if(tempValue == CrxConfigBloodPressureOption::SPandMP)
	{
		//BloodPressureValue = 1;
		BloodPressureValue = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxGenBPOptSPandMP);
	}
	else 
	if(tempValue == CrxConfigBloodPressureOption::MPandDP)
	{
		//BloodPressureValue = 2;
		BloodPressureValue = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxGenBPOptMPandDP);
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}

	if(SubSection == CrxConfigXmlTag::Default)
	{
		_gSetInternal->BloodPressureEntryOptions = BloodPressureValue;
	}
	else
	{
		_instance->_generalSettings->BloodPressureEntryOptions = BloodPressureValue;
	}
}

void CrxConfigManager::GetCommsPort(String^ SubSection, String^ ReaderValue)
{
	//Get the Comms Port Details
	if(SubSection == CrxConfigXmlTag::User)
	{
		_instance->_generalSettings->CommsPort = ReaderValue;
	}
	else if (SubSection == CrxConfigXmlTag::Default)
	{
		_gSetInternal->CommsPort = nullptr;
	}	
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
}

void CrxConfigManager::GetReportTitle(String^ SubSection, String^ ReaderValue)
{
	//Get Report Title details
	if(SubSection == CrxConfigXmlTag::User)
	{
		_instance->_generalSettings->ReportTitle = ReaderValue;
	}
	else if (SubSection == CrxConfigXmlTag::Default)
	{
		_gSetInternal->ReportTitle = nullptr;
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
}

void CrxConfigManager::GetReportLogoPath(String^ SubSection, String^ ReaderValue)
{
	//Get Report logo path details
	if(SubSection == CrxConfigXmlTag::User)
	{
		_instance->_generalSettings->ReportLogoPath = ReaderValue;
	}
	else if (SubSection == CrxConfigXmlTag::Default)
	{
		_gSetInternal->ReportLogoPath = nullptr;
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
}

void CrxConfigManager::GetServerName(String^ SubSection, String^ ReaderValue)
{
	//Get Server Name details
	if(SubSection == CrxConfigXmlTag::User)
	{
		_instance->_generalSettings->ServerName = ReaderValue;
	}
	else if (SubSection == CrxConfigXmlTag::Default)
	{
		_gSetInternal->ServerName = nullptr;
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
}
void CrxConfigManager::GetSourceData(String^ SubSection, String^ ReaderValue)
{
	//Get Source data details
	if(SubSection == CrxConfigXmlTag::User)
	{
		_instance->_generalSettings->SourceData = ReaderValue;
	}
	else if (SubSection == CrxConfigXmlTag::Default)
	{
		_gSetInternal->SourceData = nullptr;
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
}
void CrxConfigManager::GetCultureInfo(String^ SubSection, String^ ReaderValue)
{
	//Get Culture Info details
	if(SubSection == CrxConfigXmlTag::User)
	{
		_instance->_generalSettings->CultureInfo = ReaderValue;
	}
	else if (SubSection == CrxConfigXmlTag::Default)
	{
		_gSetInternal->CultureInfo = nullptr;
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
}

void CrxConfigManager::GetMachineName(System::String ^SubSection, System::String ^ReaderValue)
{
	//Get Machine Name details
	if(SubSection == CrxConfigXmlTag::User)
	{
		_instance->_generalSettings->MachineName = ReaderValue;
	}
	else if (SubSection == CrxConfigXmlTag::Default)
	{
		_gSetInternal->MachineName = nullptr;
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
}

void CrxConfigManager::GetStartupMode(System::String ^SubSection, System::String ^ReaderValue)
{
	if(SubSection == CrxConfigXmlTag::User)
	{
		_instance->_generalSettings->StartupMode = ReaderValue;
	}
	else if(SubSection == CrxConfigXmlTag::Default)
	{
		_gSetInternal->StartupMode = ReaderValue;
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
}

void CrxConfigManager::GetStartupScreen(System::String ^SubSection, System::String ^ReaderValue)
{
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigXmlTag::StartUpScreenValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}

	if(SubSection == CrxConfigXmlTag::User)
	{
		_instance->_generalSettings->StartupScreen = ReaderValue;
	}
	else if(SubSection == CrxConfigXmlTag::Default)
	{
		_gSetInternal->StartupScreen = ReaderValue;
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
}
void CrxConfigManager::GetConfigPrinter(String^ SubSection, String^ ReaderValue)
{
	//Get Config Printer details
	if(SubSection == CrxConfigXmlTag::User)
	{
		_instance->_generalSettings->PrinterName = ReaderValue;
	}
	else if (SubSection == CrxConfigXmlTag::Default)
	{
		_gSetInternal->PrinterName = nullptr;
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}	
}
//***********************************************************************
//Get PWV Settings Functions
//***********************************************************************
void CrxConfigManager::GetFemoralToCuff(String^ SubSection, String^ ReaderValue)
{
	//Get the Femoral Cuff Details
	//Temporary variables
	bool FemoralCuff = false;
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigXmlTag::CheckYesNoValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
	FemoralCuff = (tempValue == CrxConfigXmlTag::UpperYES);

	if(SubSection == CrxConfigXmlTag::Default)
	{
		_pSetInternal->FemoralToCuff = FemoralCuff;
	}
	else
	{
		_instance->_pwvSettings->FemoralToCuff = FemoralCuff;
	}
}
void CrxConfigManager::GetReferenceRange(String^ SubSection, String^ ReaderValue)
{
	//Get the Reference Range Details
	//Temporary variables
	bool RefRange = false;
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigXmlTag::CheckYesNoValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
	RefRange = (tempValue == CrxConfigXmlTag::UpperYES);

	if(SubSection == CrxConfigXmlTag::Default)
	{
		_pSetInternal->ReferenceRange = RefRange;
	}
	else
	{
		_instance->_pwvSettings->ReferenceRange = RefRange;
	}
}
void CrxConfigManager::GetPwvDistanceUnits(String^ SubSection, String^ ReaderValue)
{
	//Get the PWV Distance Units Details
	//Temporary variables
	int DistanceUnits = 0; 
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigPwvDistanceUnits::CompareStr;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}

	DistanceUnits = (tempValue == CrxConfigPwvDistanceUnits::MM ? Convert::ToInt32(CrxGenPwvValue::CrxPwvDistDistUnitsMM) : Convert::ToInt32(CrxGenPwvValue::CrxPwvDistDistUnitsCM));
	if(SubSection == CrxConfigXmlTag::Default)
	{
		_pSetInternal->PWVDistanceUnits = DistanceUnits;
	}
	else
	{
		_instance->_pwvSettings->PWVDistanceUnits = DistanceUnits;
	}
}
void CrxConfigManager::GetPwvDistanceMethods(String^ SubSection, String^ ReaderValue)
{
	//Get the PWV Distance Methods Details
	//Temporary variables
	int DistanceMethods = Convert::ToInt32(CrxGenPwvValue::CrxPwvDistMethodSubtract); 
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigPwvDistanceMethods::CompareStr;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}

	DistanceMethods = (tempValue == CrxConfigPwvDistanceMethods::Subtracting ? Convert::ToInt32(CrxGenPwvValue::CrxPwvDistMethodSubtract) : Convert::ToInt32(CrxGenPwvValue::CrxPwvDistMethodDirect));
	if(SubSection == CrxConfigXmlTag::Default)
	{
		_pSetInternal->PWVDistanceMethod = DistanceMethods;
	}
	else
	{
		_instance->_pwvSettings->PWVDistanceMethod = DistanceMethods;
	}
}
void CrxConfigManager::GetCaptureTime(String^ SubSection, String^ ReaderValue)
{
	//Get the Get Capture time Details
	//Temporary variables
	int CaptureTime = Convert::ToInt32(CrxGenPwvValue::CrxPwvCapture5Seconds);
	String^ tempValue  = nullptr;

	tempValue  = ReaderValue->ToUpper();

	tempValue = tempValue->Replace(CrxConfigXmlTag::Blank,String::Empty);

	if(tempValue == CrxConfigCaptureTime::FiveSeconds)
	{
		//CaptureTime = 0;
		CaptureTime = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxPwvCapture5Seconds);
	}
	else 
		if(tempValue == CrxConfigCaptureTime::TenSeconds)
	{
		//CaptureTime = 1;
		CaptureTime = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxPwvCapture10Seconds);
	}
	else 
	if(tempValue == CrxConfigCaptureTime::TwentySeconds)
	{
		//CaptureTime = 2;
		CaptureTime = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxPwvCapture20Seconds);
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}

	if(SubSection == CrxConfigXmlTag::Default)
	{
		_pSetInternal->CaptureTime = CaptureTime;
	}
	else
	{
		_instance->_pwvSettings->CaptureTime = CaptureTime;
	}
}
void CrxConfigManager::GetSimulationType(String^ SubSection, String^ ReaderValue)
{
	//Get the Simulation Type Details
	//Temporary variables
	if(SubSection == CrxConfigXmlTag::User)
	{
		_instance->_pwvSettings->SimulationType = ReaderValue;
	}
	else if (SubSection == CrxConfigXmlTag::Default)
	{
		_pSetInternal->SimulationType = ReaderValue;
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
}
void CrxConfigManager::GetDefaultReport(String^ SubSection, String^ ReaderValue)
{
	//Get the Default Report Details
	//Temporary variables
	if(SubSection == CrxConfigXmlTag::User)
	{
		_instance->_pwvSettings->DefaultReport = ReaderValue;
	}
	else if (SubSection == CrxConfigXmlTag::Default)
	{
		_pSetInternal->DefaultReport = ReaderValue;
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
}
//********************************************
//Set General Settings Functions
//********************************************
void CrxConfigManager::SetPatientPrivacy(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	if(gs->PatientPrivacy == false)
	{
		node->InnerText = CrxConfigXmlTag::LowerNo;								
	}
	else
	if(gs->PatientPrivacy == true)
	{
		node->InnerText = CrxConfigXmlTag::LowerYes;
	}
}
void CrxConfigManager::SetHeightWeight(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	//if(gs->HeightandWeightUnit == 0)
	if((gs->HeightandWeightUnit == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxGenHeightWeightMetric)))
	{
		node->InnerText = CrxConfigHeightandWeightUnits::MetricSetValue;								
	}
	else
	//if(gs->HeightandWeightUnit == 1)
	if((gs->HeightandWeightUnit == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxGenHeightWeightImperial)))
	{
		node->InnerText = CrxConfigHeightandWeightUnits::ImperialSetValue;
	}
}
void CrxConfigManager::SetBloodPressureOption(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	//if(gs->BloodPressureEntryOptions == 0)
	if((gs->BloodPressureEntryOptions == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxGenBPOptSPandDP)))
	{
		node->InnerText = CrxConfigBloodPressureOption::SPandDPSetValue;								
	}
	else
	//if(gs->BloodPressureEntryOptions == 1)
	if((gs->BloodPressureEntryOptions == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxGenBPOptSPandMP)))
	{
		node->InnerText = CrxConfigBloodPressureOption::SPandMPSetValue;
	}
	else
	//if(gs->BloodPressureEntryOptions == 2)
	if((gs->BloodPressureEntryOptions == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxGenBPOptMPandDP)))
	{
		node->InnerText = CrxConfigBloodPressureOption::MPandDPSetValue;
	}
}
void CrxConfigManager::SetCommsPort(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	if(gs->CommsPort != nullptr) 
    {
        node->InnerText = gs->CommsPort;
    }
    else 
    {
		node->InnerText = CrxConfigXmlTag::Blank; 
    }
}
void CrxConfigManager::SetReportTitle(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	if(gs->ReportTitle != nullptr && gs->ReportTitle->Length > 0) 
    {
        node->InnerText = gs->ReportTitle;
    }
    else 
    {
		node->InnerText = CrxConfigXmlTag::Blank; 
    }
}
void CrxConfigManager::SetReportLogoPath(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	if(gs->ReportLogoPath != nullptr) 
    {
        node->InnerText = gs->ReportLogoPath;
    }
    else 
    {
		node->InnerText = CrxConfigXmlTag::Blank; 
    }
}

void CrxConfigManager::SetServerName(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	if(gs->ServerName != nullptr) 
    {
        node->InnerText = gs->ServerName;
    }
    else 
    {
		node->InnerText = CrxConfigXmlTag::Blank; 
    }
}
void CrxConfigManager::SetSourceData(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	if(gs->SourceData != nullptr) 
    {
        node->InnerText = gs->SourceData;
    }
    else 
    {
		node->InnerText = CrxConfigXmlTag::Blank; 
    }
}
void CrxConfigManager::SetCultureInfo(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	if(gs->CultureInfo != nullptr) 
    {
        node->InnerText = gs->CultureInfo;
    }
    else 
    {
		node->InnerText = CrxConfigXmlTag::Blank; 
    }
}

void CrxConfigManager::SetMachineName(AtCor::Scor::CrossCutting::Configuration::CrxStructGeneralSetting ^gs, System::Xml::XmlNode ^node)
{
	if(gs->MachineName != nullptr)
	{
		node->InnerText = gs->MachineName;
	}
	else
	{
		node->InnerText = CrxConfigXmlTag::Blank;
	}
}
void CrxConfigManager::SetPrinterName(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	if(gs->PrinterName != nullptr)
	{
		node->InnerText = gs->PrinterName;
	}
	else
	{
		node->InnerText = CrxConfigXmlTag::Blank;
	}
}
//********************************************
//Set PWV Settings Functions
//********************************************
void CrxConfigManager::SetFemoralToCuff(CrxStructPwvSetting^ ps, XmlNode^ node)
{
	if(ps->FemoralToCuff == false)
	{
		node->InnerText = CrxConfigXmlTag::LowerNo;								
	}
	else
	if(ps->FemoralToCuff == true)
	{
		node->InnerText = CrxConfigXmlTag::LowerYes;
	}
}
void CrxConfigManager::SetReferenceRange(CrxStructPwvSetting^ ps, XmlNode^ node)
{
	if(ps->ReferenceRange == false)
	{
		node->InnerText = CrxConfigXmlTag::LowerNo;								
	}
	else
	if(ps->ReferenceRange == true)
	{
		node->InnerText = CrxConfigXmlTag::LowerYes;
	}
}
void CrxConfigManager::SetPwvDistanceUnits(CrxStructPwvSetting^ ps, XmlNode^ node)
{
	//if(ps->PWVDistanceUnits == 0)
	if((ps->PWVDistanceUnits == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxPwvDistDistUnitsMM)))
	{
		node->InnerText = CrxConfigPwvDistanceUnits::MMSetValue;								
	}
	else
	//if(ps->PWVDistanceUnits == 1)
	if((ps->PWVDistanceUnits == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxPwvDistDistUnitsCM)))
	{
		node->InnerText = CrxConfigPwvDistanceUnits::CMSetValue;
	}
}
void CrxConfigManager::SetPwvDistanceMethods(CrxStructPwvSetting^ ps, XmlNode^ node)
{
	//if(ps->PWVDistanceMethod == 0)
	if((ps->PWVDistanceMethod == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxPwvDistMethodSubtract)))
	{
		node->InnerText = CrxConfigPwvDistanceMethods::SubtractingSetValue;								
	}
	else
	//if(ps->PWVDistanceMethod == 1)
	if((ps->PWVDistanceMethod == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxPwvDistMethodDirect)))
	{
		node->InnerText = CrxConfigPwvDistanceMethods::DirectSetValue;
	}
}
void CrxConfigManager::SetCaptureTime(CrxStructPwvSetting^ ps, XmlNode^ node)
{
	//if(ps->CaptureTime == 0)
	if((ps->CaptureTime == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxPwvCapture5Seconds)))
	{
		node->InnerText = CrxConfigCaptureTime::FiveSecondsSetValue;								
	}
	else
	//if(ps->CaptureTime == 1)
	if((ps->CaptureTime == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxPwvCapture10Seconds)))
	{
		node->InnerText = CrxConfigCaptureTime::TenSecondsSetValue;
	}
	else
	//if(ps->CaptureTime == 2)
	if((ps->CaptureTime == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxPwvCapture20Seconds)))
	{
		node->InnerText = CrxConfigCaptureTime::TwentySecondsSetValue;
	}
}
void CrxConfigManager::SetSimulationType(CrxStructPwvSetting^ ps, XmlNode^ node)
{
	if(ps->SimulationType != nullptr) 
    {
        node->InnerText = ps->SimulationType;
    }
    else 
    {
		node->InnerText = CrxConfigXmlTag::Blank; 
    }
}
void CrxConfigManager::SetDefaultReport(AtCor::Scor::CrossCutting::Configuration::CrxStructPwvSetting ^ps, System::Xml::XmlNode ^node)
{
	if(ps->DefaultReport != nullptr) 
    {
        node->InnerText = ps->DefaultReport;
    }
    else 
    {
		node->InnerText = CrxConfigXmlTag::Blank; 
    }
}

//***********************************************************************************