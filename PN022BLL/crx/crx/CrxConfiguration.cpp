// CrxConfiguration.cpp : main project file.

#include "stdafx.h"
#include "CrxConfiguration.h"
#include "CrxCrossCutting.h"

using namespace System;// For String, Console
using namespace System::Xml;// For XML classes and enums
using namespace System::IO;// For FileStream
using namespace System::Text; //For String manipulation

// Add application specific namespaces
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;

//To get General Default Settings from file
void CrxConfigManager::GetGeneralDefaultSettings(CrxStructGeneralSetting^ objGenSettings)
{
	CrxConfigManager::GetSettings("GENERAL","DEFAULT");

	// as there is no assignment operator defined, doing memberwise copy
	objGenSettings->PatientPrivacy				= _gSetInternal->PatientPrivacy;
	objGenSettings->BloodPressureEntryOptions	= _gSetInternal->BloodPressureEntryOptions;
	objGenSettings->HeightandWeightUnit			= _gSetInternal->HeightandWeightUnit;
	objGenSettings->CommsPort					= _gSetInternal->CommsPort;
	objGenSettings->ReportTitle					= _gSetInternal->ReportTitle;
	objGenSettings->ReportLogoPath				= _gSetInternal->ReportLogoPath;
}

//To get User Settings from the file
void CrxConfigManager::GetGeneralUserSettings()
{
	CrxConfigManager::GetSettings("GENERAL","USER");
}

//To Set General User Setting 
void CrxConfigManager::SetGeneralUserSettings(CrxStructGeneralSetting^ gs)
{
	CrxConfigManager::SetSettings("GENERAL","USER",gs,nullptr);
}

//To get PWV Default Settings from file
void CrxConfigManager::GetPwvDefaultSettings(CrxStructPwvSetting^ objPwvSettings)
{
	CrxConfigManager::GetSettings("PWV","DEFAULT");

	objPwvSettings->CaptureTime			= _pSetInternal->CaptureTime;
	objPwvSettings->PWVDistanceMethod	= _pSetInternal->PWVDistanceMethod;
	objPwvSettings->FemoralToCuff		= _pSetInternal->FemoralToCuff;
	objPwvSettings->PWVDistanceUnits	= _pSetInternal->PWVDistanceUnits;
	objPwvSettings->ReferenceRange		= _pSetInternal->ReferenceRange;
	objPwvSettings->SimulationType		= _pSetInternal->SimulationType;
}

//To get PWV User Settings from the file
void CrxConfigManager::GetPwvUserSettings()
{
	CrxConfigManager::GetSettings("PWV","USER");
}

//To Set PWV User Setting 
void CrxConfigManager::SetPwvUserSettings(CrxStructPwvSetting^ ps)
{
	CrxConfigManager::SetSettings("PWV","USER",nullptr,ps);
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
			throw gcnew CrxException(CRXERR_FILE_NOT_EXIST); // File not found
		}		
		
		//Check whether File Access is provided or not
		try
		{			
			fs = gcnew FileStream(_nameOfFile,FileMode::Open);
		}
		catch(Exception^)
		{
			throw gcnew CrxException(CRXERR_FILE_NOT_ACCESS); // File not accessable
		}

		//Check whether have the access to write or not
		if(!fs->CanWrite)
		{
			throw gcnew CrxException(CRXERR_FILE_NOT_ACCESS); // File not accessable
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
		throw gcnew CrxException(CRXERR_CORRUPT_FILE); // any xml exception is rethrown as corrupt file exception
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
		throw gcnew CrxException(101);
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
							
							if(Section == "GENERAL")
							{
								CrxConfigManager::SetGeneralSettingsNode(gs, node4);
							}
							else
							if(Section == "PWV")
							{
								CrxConfigManager::SetPwvSettingsNode(ps, node4);
							}
						 }
					  }
				 }
			}
		}		  
	}
	if (startflag == false)
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
	}
}

void CrxConfigManager::SetGeneralSettingsNode(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	String^ SubSectionNodeName = nullptr;////Contains the Subsection name, Set value to null

	//Temporary storing SubSection Settings Element name
	SubSectionNodeName = node->Name->ToUpper();

	//Calls function if node element is Patient Privacy
 	if (SubSectionNodeName == "PATIENTPRIVACY")
	{	
		CrxConfigManager::SetPatientPrivacy(gs, node);		
	}
	//Calls function if node element is Height and Weight
    else
    if (SubSectionNodeName == "HEIGHTANDWEIGHTUNITS")
	{	
		CrxConfigManager::SetHeightWeight(gs, node);
	}
	//Calls function if node element is Blood Pressure Option
    else
	if (SubSectionNodeName == "BLOODPRESSUREENTRYOPTIONS")
	{	
		CrxConfigManager::SetBloodPressureOption(gs, node);		
	}
	//Calls function if node element is Comms Port
	else
	if(SubSectionNodeName == "COMMSPORT")
	{
		CrxConfigManager::SetCommsPort(gs, node);
	}
	//Calls function if node element is Report Title
	else
	if(SubSectionNodeName == "REPORTTITLE")
	{									
		CrxConfigManager::SetReportTitle(gs, node);
	}
	else
	if(SubSectionNodeName == "REPORTLOGOPATH")
	{
		CrxConfigManager::SetReportLogoPath(gs, node);
	}
	else
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file		
	}
}

void CrxConfigManager::SetPwvSettingsNode(CrxStructPwvSetting^ ps, XmlNode^ node)
{
	String^ SubSectionNodeName = nullptr;

	SubSectionNodeName = node->Name->ToUpper();

   //Calls function if node element is PWV Distance Methods
	if (SubSectionNodeName == "PWVDISTANCEMETHOD")
	{	
		CrxConfigManager::SetPwvDistanceMethods(ps, node);		
	}
	//Calls function if node element is FemoralToCuff
    else
    if (SubSectionNodeName == "FEMORALTOCUFF")
	{	
		CrxConfigManager::SetFemoralToCuff(ps, node);
	}
	//Calls function if node element is PWV Distance Units
    else
	if (SubSectionNodeName == "PWVDISTANCEUNITS")
	{	
		CrxConfigManager::SetPwvDistanceUnits(ps, node);		
	}
	//Calls function if node element is Capture Time
	else
	if(SubSectionNodeName == "CAPTURETIME")
	{
		CrxConfigManager::SetCaptureTime(ps, node);
	}
	//Calls function if node element is Reference Range
	else
	if(SubSectionNodeName == "REFERENCERANGE")
	{									
		CrxConfigManager::SetReferenceRange(ps, node);
	}
	//Calls function if node element is Simulation Type
	else
	if(SubSectionNodeName == "SIMULATIONTYPE")
	{
		CrxConfigManager::SetSimulationType(ps, node);
	}
	else
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file		
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
	String^ GetXMLSection		= "'";		//Gets the XML section name
	String^ GetSectionName		= nullptr;  //Store section name to get the value
	String^ ReaderValue			= nullptr;  //Store XML Node Reader value
	String^ configXMLElements   = L"'CONFIGURATION', 'SYSTEMSETTING', 'GENERAL', 'USER', 'PATIENTPRIVACY', 'HEIGHTANDWEIGHTUNITS', 'BLOODPRESSUREENTRYOPTIONS', 'COMMSPORT', 'REPORTTITLE', 'REPORTLOGOPATH', 'DEFAULT', 'PWV', 'PWVDISTANCEMETHOD', 'FEMORALTOCUFF', 'PWVDISTANCEUNITS', 'CAPTURETIME', 'REFERENCERANGE', 'SIMULATIONTYPE'";

	try 
	{
		//Check whether file is exists or not
		if(!File::Exists(_nameOfFile))
		{
			throw gcnew CrxException(CRXERR_FILE_NOT_EXIST); // File not found
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
					if(!configXMLElements->Contains("'" + GetXMLSection + "'"))
					{
						throw gcnew CrxException(CRXERR_CORRUPT_FILE); //corrupt file
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
						throw gcnew CrxException(CRXERR_CORRUPT_FILE); //corrupt file
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
					ReaderValue = reader->Value;
					
					//Call GetSettingsNode to get value
					CrxConfigManager::GetSettingsNode(Section, SubSection, GetXMLSection , ReaderValue);
				
				break; 
				
				//if none of the switch case are valid for node, then default and throw exception
				default: 
					throw gcnew CrxException(); //Unknown error with zero error code
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
		throw gcnew CrxException(CRXERR_CORRUPT_FILE); // any xml exception is rethrown as corrupt file exception
	}
	//Finally stage to close all open files
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
	if(Section == "GENERAL")
	{
		//Call GetGeneralSettingsNode function to get values of General Settings
		CrxConfigManager::GetGeneralSettingsNode(SubSection,SubSectionNode,ReaderValue);
	}
	else 
	if(Section == "PWV")
	{
		//Call GetGeneralSettingsNode function to get values of PWV Settings
		CrxConfigManager::GetPwvSettingsNode(SubSection,SubSectionNode,ReaderValue);
	}

}

void CrxConfigManager::GetGeneralSettingsNode(String^ SubSection, String^ SubSectionNode , String^ ReaderValue)
{
	//Calls function if node element is Patient Privacy
	if(SubSectionNode == "PATIENTPRIVACY")
	{
		CrxConfigManager::GetPatientPrivacy(SubSection,ReaderValue);
	}
	//Calls function if node element is Height and Weight
	else
	if(SubSectionNode == "HEIGHTANDWEIGHTUNITS")
	{
		CrxConfigManager::GetHeightWeight(SubSection,ReaderValue);

	}
	//Calls function if node element is Blood Pressure Option
	else
	if(SubSectionNode == "BLOODPRESSUREENTRYOPTIONS")
	{
		CrxConfigManager::GetBloodPressureOption(SubSection,ReaderValue);
	}
	//Calls function if node element is Comms Port
	else
	if(SubSectionNode == "COMMSPORT")
	{
		CrxConfigManager::GetCommsPort(SubSection,ReaderValue);

	}
	//Calls function if node element is Report Title
	else
	if(SubSectionNode == "REPORTTITLE")
	{
		CrxConfigManager::GetReportTitle(SubSection,ReaderValue);

	}
	//Calls function if node element is Report Logo Path
	else
	if(SubSectionNode == "REPORTLOGOPATH")
	{
		CrxConfigManager::GetReportLogoPath(SubSection,ReaderValue);
	}
	//If none of the node element matches then throw exception
	else
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
	}
}
void CrxConfigManager::GetPwvSettingsNode(String^ SubSection, String^ SubSectionNode , String^ ReaderValue)
{
	//Calls function if node element is PWV Distance Methods
	if(SubSectionNode == "PWVDISTANCEMETHOD")
	{
		CrxConfigManager::GetPwvDistanceMethods(SubSection,ReaderValue);
	}
	//Calls function if node element is FemoralToCuff
	else
	if(SubSectionNode == "FEMORALTOCUFF")
	{
		CrxConfigManager::GetFemoralToCuff(SubSection,ReaderValue);

	}
	//Calls function if node element is PWV Distance Units
	else
	if(SubSectionNode == "PWVDISTANCEUNITS")
	{
		CrxConfigManager::GetPwvDistanceUnits(SubSection,ReaderValue);
	}
	//Calls function if node element is Capture Time
	else
	if(SubSectionNode == "CAPTURETIME")
	{
		CrxConfigManager::GetCaptureTime(SubSection,ReaderValue);

	}
	//Calls function if node element is Reference Range
	else
	if(SubSectionNode == "REFERENCERANGE")
	{
		CrxConfigManager::GetReferenceRange(SubSection,ReaderValue);

	}
	//Calls function if node element is Simulation Type
	else
	if(SubSectionNode == "SIMULATIONTYPE")
	{
		CrxConfigManager::GetSimulationType(SubSection,ReaderValue);
	}	
	else
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
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

	chkVal = "'NO', 'YES'";

	if(chkVal->Contains("'" + tempValue + "'") == false)
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
	}
	PatientPrivacyValue = (tempValue == "YES");

	if(SubSection == "DEFAULT")
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
	chkVal = "'METRIC', 'IMPERIAL'";

	if(chkVal->Contains("'" + tempValue + "'") == false)
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
	}

	HeightWeight = (tempValue == "METRIC" ? 0 : 1);
	if(SubSection == "DEFAULT")
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

	tempValue = tempValue->Replace(" ","");

	if(tempValue == "SPANDDP")
	{
		BloodPressureValue = 0;
	}
	else 
	if(tempValue == "SPANDMP")
	{
		BloodPressureValue = 1;
	}
	else 
	if(tempValue == "MPANDDP")
	{
		BloodPressureValue = 2;
	}
	else
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
	}

	if(SubSection == "DEFAULT")
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
	if(SubSection == "USER")
	{
		_instance->_generalSettings->CommsPort = ReaderValue;
	}
	else if (SubSection == "DEFAULT")
	{
		_gSetInternal->CommsPort = nullptr;
	}	
	else
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
	}
}

void CrxConfigManager::GetReportTitle(String^ SubSection, String^ ReaderValue)
{
	//Get Report Title details
	if(SubSection == "USER")
	{
		_instance->_generalSettings->ReportTitle = ReaderValue;
	}
	else if (SubSection == "DEFAULT")
	{
		_gSetInternal->ReportTitle = nullptr;
	}
	else
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
	}
}

void CrxConfigManager::GetReportLogoPath(String^ SubSection, String^ ReaderValue)
{
	//Get Report logo path details
	if(SubSection == "USER")
	{
		_instance->_generalSettings->ReportLogoPath = ReaderValue;
	}
	else if (SubSection == "DEFAULT")
	{
		_gSetInternal->ReportLogoPath = nullptr;
	}
	else
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
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
	chkVal = "'NO', 'YES'";

	if(chkVal->Contains("'" + tempValue + "'") == false)
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
	}
	FemoralCuff = (tempValue == "YES");

	if(SubSection == "DEFAULT")
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
	chkVal = "'NO', 'YES'";

	if(chkVal->Contains("'" + tempValue + "'") == false)
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
	}
	RefRange = (tempValue == "YES");

	if(SubSection == "DEFAULT")
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
	chkVal = "'MM', 'CM'";

	if(chkVal->Contains("'" + tempValue + "'") == false)
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
	}

	DistanceUnits = (tempValue == "MM" ? 0 : 1);
	if(SubSection == "DEFAULT")
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
	int DistanceMethods = 0; 
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = "'SUBTRACTING', 'DIRECT'";

	if(chkVal->Contains("'" + tempValue + "'") == false)
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
	}

	DistanceMethods = (tempValue == "SUBTRACTING" ? 0 : 1);
	if(SubSection == "DEFAULT")
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
	int CaptureTime = 5;
	String^ tempValue  = nullptr;

	tempValue  = ReaderValue->ToUpper();

	tempValue = tempValue->Replace(" ","");

	if(tempValue == "5SECONDS")
	{
		CaptureTime = 5;
	}
	else 
	if(tempValue == "10SECONDS")
	{
		CaptureTime = 10;
	}
	else 
	if(tempValue == "20SECONDS")
	{
		CaptureTime = 20;
	}
	else
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
	}

	if(SubSection == "DEFAULT")
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
	if(SubSection == "USER")
	{
		_instance->_pwvSettings->SimulationType = ReaderValue;
	}
	else if (SubSection == "DEFAULT")
	{
		_pSetInternal->SimulationType = ReaderValue;
	}
	else
	{
		throw gcnew CrxException(CRXERR_CORRUPT_FILE);//corrupt file
	}
}
//********************************************
//Set General Settings Functions
//********************************************
void CrxConfigManager::SetPatientPrivacy(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	if(gs->PatientPrivacy == false)
	{
		node->InnerText = "No";								
	}
	else
	if(gs->PatientPrivacy == true)
	{
		node->InnerText = "Yes";
	}
}
void CrxConfigManager::SetHeightWeight(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	if(gs->HeightandWeightUnit == 0)
	{
		node->InnerText = "Metric";								
	}
	else
	if(gs->HeightandWeightUnit == 1)
	{
		node->InnerText = "Imperial";
	}
}
void CrxConfigManager::SetBloodPressureOption(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	if(gs->BloodPressureEntryOptions == 0)
	{
		node->InnerText = "SP and DP";								
	}
	else
	if(gs->BloodPressureEntryOptions == 1)
	{
		node->InnerText = "SP and MP";
	}
	else
	if(gs->BloodPressureEntryOptions == 2)
	{
		node->InnerText = "MP and DP";
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
         node->InnerText = " "; 
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
         node->InnerText = " "; 
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
         node->InnerText = " "; 
    }
}

//********************************************
//Set PWV Settings Functions
//********************************************
void CrxConfigManager::SetFemoralToCuff(CrxStructPwvSetting^ ps, XmlNode^ node)
{
	if(ps->FemoralToCuff == false)
	{
		node->InnerText = "No";								
	}
	else
	if(ps->FemoralToCuff == true)
	{
		node->InnerText = "Yes";
	}
}
void CrxConfigManager::SetReferenceRange(CrxStructPwvSetting^ ps, XmlNode^ node)
{
	if(ps->ReferenceRange == false)
	{
		node->InnerText = "No";								
	}
	else
	if(ps->ReferenceRange == true)
	{
		node->InnerText = "Yes";
	}
}
void CrxConfigManager::SetPwvDistanceUnits(CrxStructPwvSetting^ ps, XmlNode^ node)
{
	if(ps->PWVDistanceUnits == 0)
	{
		node->InnerText = "mm";								
	}
	else
	if(ps->PWVDistanceUnits == 1)
	{
		node->InnerText = "cm";
	}
}
void CrxConfigManager::SetPwvDistanceMethods(CrxStructPwvSetting^ ps, XmlNode^ node)
{
	if(ps->PWVDistanceMethod == 0)
	{
		node->InnerText = "Subtracting";								
	}
	else
	if(ps->PWVDistanceMethod == 1)
	{
		node->InnerText = "Direct";
	}
}
void CrxConfigManager::SetCaptureTime(CrxStructPwvSetting^ ps, XmlNode^ node)
{
	if(ps->CaptureTime == 5)
	{
		node->InnerText = "5 seconds";								
	}
	else
	if(ps->CaptureTime == 10)
	{
		node->InnerText = "10 seconds";
	}
	else
	if(ps->CaptureTime == 20)
	{
		node->InnerText = "20 seconds";
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
         node->InnerText = " "; 
    }
}

//***********************************************************************************