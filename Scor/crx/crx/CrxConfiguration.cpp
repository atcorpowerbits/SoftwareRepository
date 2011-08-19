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
using namespace System::Xml;

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
	//objGenSettings->EnvironmentSettings			= CrxConfigStructInternal::DefaultEnvironment;
	objGenSettings->EnvironmentSettings			=  CrxCommon::ApplicationEnvironment;
	objGenSettings->PrinterName					= _gSetInternal->PrinterName;
	objGenSettings->Key							= _gSetInternal->Key;
	/*objGenSettings->Id							= _gSetInternal->Id;
	objGenSettings->Sn							= _gSetInternal->Sn;
	objGenSettings->Verify						= _gSetInternal->Verify;
	objGenSettings->Cksum						= _gSetInternal->Cksum;*/

}

//To get User Settings from the file
void CrxConfigManager::GetGeneralUserSettings()
{
	CrxConfigManager::GetSettings(CrxConfigXmlTag::General,CrxConfigXmlTag::User);
}

//To Set General User Setting 
void CrxConfigManager::SetGeneralUserSettings(CrxStructGeneralSetting^ gs)
{
	//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
	//Added one parameter for PWA
	//CrxConfigManager::SetSettings(CrxConfigXmlTag::General,CrxConfigXmlTag::User,gs,nullptr);
	CrxConfigManager::SetSettings(CrxConfigXmlTag::General,CrxConfigXmlTag::User,gs,nullptr,nullptr,nullptr);
	//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011

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
	objPwvSettings->NormalRange			= _pSetInternal->NormalRange;
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
	//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
	//Added one parameter for PWA
	//CrxConfigManager::SetSettings(CrxConfigXmlTag::Pwv,CrxConfigXmlTag::User,nullptr,ps);
	CrxConfigManager::SetSettings(CrxConfigXmlTag::Pwv,CrxConfigXmlTag::User,nullptr,ps,nullptr,nullptr);
	//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011

}

//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
//To get PWA Default Settings from file
void CrxConfigManager::GetPwaDefaultSettings(CrxStructPwaSetting^ objPwaSettings)
{
	CrxConfigManager::GetSettings(CrxConfigXmlTag::Pwa,CrxConfigXmlTag::Default);
	
	objPwaSettings->CaptureTime				= _pwaSetInternal->CaptureTime;
	objPwaSettings->GuidanceBars			= _pwaSetInternal->GuidanceBars;
	objPwaSettings->AutoCapture				= _pwaSetInternal->AutoCapture;
	objPwaSettings->AugmentationIndex		= _pwaSetInternal->AugmentationIndex;
	objPwaSettings->AugmentationIndexAtHR75	= _pwaSetInternal->AugmentationIndexAtHR75;
	objPwaSettings->CaptureInput			= _pwaSetInternal->CaptureInput;
	//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2245, 17-Jun-2011
	objPwaSettings->SimulationType			= _pwaSetInternal->SimulationType;
	//End  : AtCor-Drop2-Sprint1, TM, SWREQ2245, 17-Jun-2011
	

}

//To get PWA User Settings from the file
void CrxConfigManager::GetPwaUserSettings()
{
	CrxConfigManager::GetSettings(CrxConfigXmlTag::Pwa,CrxConfigXmlTag::User);
}
//To Set PWA User Setting 
void CrxConfigManager::SetPwaUserSettings(CrxStructPwaSetting^ pwas)
{
	CrxConfigManager::SetSettings(CrxConfigXmlTag::Pwa,CrxConfigXmlTag::User,nullptr,nullptr,pwas,nullptr);
}
//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
//To get BP Default Settings from file
void CrxConfigManager::GetBpDefaultSettings(CrxStructBpSetting^ objBpSettings)
{
	CrxConfigManager::GetSettings(CrxConfigXmlTag::BP,CrxConfigXmlTag::Default);
	
	objBpSettings->Device = _bpSetInternal->Device;
	objBpSettings->NumberofAssessments = _bpSetInternal->NumberofAssessments;
	objBpSettings->AutoPWA = _bpSetInternal->AutoPWA;
	objBpSettings->BloodPressure= _bpSetInternal->BloodPressure;
	objBpSettings->AutoPWADP= _bpSetInternal->AutoPWADP;
	objBpSettings->AutoPWASP= _bpSetInternal->AutoPWASP;
	objBpSettings->AutoPWAPP= _bpSetInternal->AutoPWAPP;
	objBpSettings->AutoPWADPThreshold= _bpSetInternal->AutoPWADPThreshold;
	objBpSettings->AutoPWAPPThreshold= _bpSetInternal->AutoPWAPPThreshold;
	objBpSettings->AutoPWASPThreshold= _bpSetInternal->AutoPWASPThreshold;
}

//To get BP User Settings from the file
void CrxConfigManager::GetBpUserSettings()
{
	CrxConfigManager::GetSettings(CrxConfigXmlTag::BP,CrxConfigXmlTag::User);
}
//To Set BP User Setting 
void CrxConfigManager::SetBpUserSettings(CrxStructBpSetting^ bps)
{
	CrxConfigManager::SetSettings(CrxConfigXmlTag::BP,CrxConfigXmlTag::User,nullptr,nullptr,nullptr,bps);
}

//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
//***************************************************************
//Set the node values in XML file as per Section and SubSection
//***************************************************************
//Begin  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
//void CrxConfigManager::SetSettings(String^ Section, String^ SubSection, CrxStructGeneralSetting^ gs , CrxStructPwvSetting^ ps)
void CrxConfigManager::SetSettings(String^ Section, String^ SubSection, CrxStructGeneralSetting^ gs , CrxStructPwvSetting^ ps , CrxStructPwaSetting^ pwas,  CrxStructBpSetting^ bps)
//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
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
		//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
		//CrxConfigManager::SetSettingsNode(Section, SubSection, gs, ps, node);
		CrxConfigManager::SetSettingsNode(Section, SubSection, gs, ps, pwas, bps, node);
		//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
		
		
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

//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
//void CrxConfigManager::SetSettingsNode(String^ Section, String^ SubSection, CrxStructGeneralSetting^ gs,CrxStructPwvSetting^ ps, XmlNode^ node)
void CrxConfigManager::SetSettingsNode(String^ Section, String^ SubSection, CrxStructGeneralSetting^ gs,CrxStructPwvSetting^ ps, CrxStructPwaSetting^ pwas,  CrxStructBpSetting^ bps, XmlNode^ node)
//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
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
							//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
							else if(Section == CrxConfigXmlTag::Pwa)
							{
								CrxConfigManager::SetPwaSettingsNode(pwas, node4);
							}
							//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
							//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
							else if(Section == CrxConfigXmlTag::BP)
							{
								CrxConfigManager::SetBpSettingsNode(bps, node4);
							}
							//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
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
	////Calls function if node element is Blood Pressure Option
 //   else
	//if (SubSectionNodeName == CrxConfigXmlTag::BloodPressureEntryOptions)
	//{	
	//	CrxConfigManager::SetBloodPressureOption(gs, node);		
	//}
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
		//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
		CrxConfigManager::SetStartupMode(gs, node);
		//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
	}
	//Calls function if node element is StartupScreen
	else
	if(SubSectionNodeName == CrxConfigXmlTag::StartupScreen)
	{
		//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
		CrxConfigManager::SetStartupScreen(gs, node);
		//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011

	}
	//Calls function if node element is Config Printer
	else
	if(SubSectionNodeName == CrxConfigXmlTag::PrinterName)
	{
		CrxConfigManager::SetPrinterName(gs, node);
	}
	//Calls function if node element is Config System Key
	else
	if(SubSectionNodeName == CrxConfigXmlTag::SystemKey)
	{
		CrxConfigManager::SetSystemKey(gs, node);
	}
	////Begin: AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011
	////Calls function if node element is Id
	//else
	//if(SubSectionNodeName == CrxConfigXmlTag::Id)
	//{
	//	CrxConfigManager::SetId(gs, node);
	//}
	////Calls function if node element is Sn
	//else
	//if(SubSectionNodeName == CrxConfigXmlTag::Sn)
	//{
	//	CrxConfigManager::SetSn(gs, node);
	//}
	////Calls function if node element is Verify
	//else
	//if(SubSectionNodeName == CrxConfigXmlTag::Verify)
	//{
	//	CrxConfigManager::SetVerify(gs, node);
	//}
	////Calls function if node element is Checksum
	//else
	//if(SubSectionNodeName == CrxConfigXmlTag::Cksum)
	//{
	//	CrxConfigManager::SetCkSum(gs, node);
	//}
	////End  : AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011
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
	//Calls function if node element is Normal Range
	else
	if(SubSectionNodeName == CrxConfigXmlTag::NormalRange)
	{									
		CrxConfigManager::SetNormalRange(ps, node);
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

//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
void CrxConfigManager::SetPwaSettingsNode(CrxStructPwaSetting^ pwas, XmlNode^ node)
{
	String^ SubSectionNodeName = nullptr;

	SubSectionNodeName = node->Name->ToUpper();

   //Calls function if node element is PWA CaptureTime
	if (SubSectionNodeName == CrxConfigXmlTag::CaptureTime)
	{	
		CrxConfigManager::SetPwaCaptureTime(pwas, node);		
	}
	else
	if (SubSectionNodeName == CrxConfigXmlTag::GuidanceBars)
	{	
		CrxConfigManager::SetPwaGuidanceBars(pwas, node);		
	}
	else
	if (SubSectionNodeName == CrxConfigXmlTag::AutoCapture)
	{	
		CrxConfigManager::SetPwaAutoCapture(pwas, node);		
	}
	else
	if (SubSectionNodeName == CrxConfigXmlTag::AugmentationIndex)
	{	
		CrxConfigManager::SetPwaAugmentationIndex(pwas, node);		
	}
	else
	if (SubSectionNodeName == CrxConfigXmlTag::AugmentationIndexAtHR75)
	{	
		CrxConfigManager::SetPwaAugmentationIndexAtHR75(pwas, node);		
	}
	else
	if (SubSectionNodeName == CrxConfigXmlTag::CaptureInput)
	{	
		CrxConfigManager::SetPwaCaptureInput(pwas, node);		
	}
	else
	if(SubSectionNodeName == CrxConfigXmlTag::SimulationType)
	{
		CrxConfigManager::SetPwaSimulationType(pwas, node);
	}

	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file
	}

}
//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
void CrxConfigManager::SetBpSettingsNode(CrxStructBpSetting^ bps, XmlNode^ node)
{
	String^ SubSectionNodeName = nullptr;

	SubSectionNodeName = node->Name->ToUpper();

   	if (SubSectionNodeName == CrxConfigXmlTag::Device)
	{	
		CrxConfigManager::SetBpDevice(bps, node);		
	}
	else
	if (SubSectionNodeName == CrxConfigXmlTag::NumberofAssessments)
	{	
		CrxConfigManager::SetBpNumberofAssessments(bps, node);		
	}
	else
	if (SubSectionNodeName == CrxConfigXmlTag::AutoPWA)
	{	
		CrxConfigManager::SetBpAutoPWA(bps, node);		
	}
	/*else
	if (SubSectionNodeName == CrxConfigXmlTag::BloodPressure)
	{	
		CrxConfigManager::SetBpBloodPressure(bps, node);		
	}	*/
	else
	if (SubSectionNodeName == CrxConfigXmlTag::AutoPWASP)
	{	
		CrxConfigManager::SetBpAutoPWASP(bps, node);		
	}
	else
	if (SubSectionNodeName == CrxConfigXmlTag::AutoPWADP)
	{	
		CrxConfigManager::SetBpAutoPWADP(bps, node);		
	}	
	else
	if (SubSectionNodeName == CrxConfigXmlTag::AutoPWAPP)
	{	
		CrxConfigManager::SetBpAutoPWAPP(bps, node);		
	}
	else
	if (SubSectionNodeName == CrxConfigXmlTag::AutoPWADPThreshold)
	{	
		CrxConfigManager::SetBpAutoPWADPThreshold(bps, node);		
	}
	else
	if (SubSectionNodeName == CrxConfigXmlTag::AutoPWAPPThreshold)
	{	
		CrxConfigManager::SetBpAutoPWAPPThreshold(bps, node);		
	}
	else
	if (SubSectionNodeName == CrxConfigXmlTag::AutoPWASPThreshold)
	{	
		CrxConfigManager::SetBpAutoPWASPThreshold(bps, node);		
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file
	}

}
//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011

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
				//Check if node is for Comment Type
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
	//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
	else
	if(Section == CrxConfigXmlTag::Pwa)
	{
		//Call GetPWVSettingsNode function to get values of PWV Settings
		CrxConfigManager::GetPwaSettingsNode(SubSection,SubSectionNode,ReaderValue);
	}
	//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
	//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 9-Jun-2011
	else
	if(Section == CrxConfigXmlTag::BP)
	{
		//Call GetPWVSettingsNode function to get values of PWV Settings
		CrxConfigManager::GetBpSettingsNode(SubSection,SubSectionNode,ReaderValue);
	}
	//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 13-Jun-2011
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
	////Calls function if node element is Blood Pressure Option
	//else
	//if(SubSectionNode == CrxConfigXmlTag::BloodPressureEntryOptions)
	//{
	//	CrxConfigManager::GetBloodPressureOption(SubSection,ReaderValue);
	//}
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
	//Calls function if node element is Config System Key
	else
	if(SubSectionNode == CrxConfigXmlTag::SystemKey)
	{
		CrxConfigManager::GetSystemKey(SubSection, ReaderValue);
	}
	////Begin: AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011
	//else
	//if(SubSectionNode == CrxConfigXmlTag::Id)
	//{
	//	CrxConfigManager::GetId(SubSection,ReaderValue);
	//}
	//else
	//if(SubSectionNode == CrxConfigXmlTag::Sn)
	//{
	//	CrxConfigManager::GetSn(SubSection,ReaderValue);
	//}
	//else
	//if(SubSectionNode == CrxConfigXmlTag::Verify)
	//{
	//	CrxConfigManager::GetVerify(SubSection,ReaderValue);
	//}
	//else
	//if(SubSectionNode == CrxConfigXmlTag::Cksum)
	//{
	//	CrxConfigManager::GetCkSum(SubSection,ReaderValue);
	//}
	//End   : AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011
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
	//Calls function if node element is Normal Range
	else
	if(SubSectionNode == CrxConfigXmlTag::NormalRange)
	{
		CrxConfigManager::GetNormalRange(SubSection,ReaderValue);
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

//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
void CrxConfigManager::GetPwaSettingsNode(String^ SubSection, String^ SubSectionNode , String^ ReaderValue)
{
	//Calls function if node element is PWA CaptureTime
	if(SubSectionNode == CrxConfigXmlTag::CaptureTime)
	{
		CrxConfigManager::GetPwaCaptureTime(SubSection,ReaderValue);
	}
	//Calls function if node element is PWA GuidanceBars
	else if(SubSectionNode == CrxConfigXmlTag::GuidanceBars)
	{
		CrxConfigManager::GetPwaGuidanceBars(SubSection,ReaderValue);
	}
	//Calls function if node element is PWA AutoCapture
	else if(SubSectionNode == CrxConfigXmlTag::AutoCapture)
	{
		CrxConfigManager::GetPwaAutoCapture(SubSection,ReaderValue);
	}
	//Calls function if node element is PWA AugmentationIndex
	else if(SubSectionNode == CrxConfigXmlTag::AugmentationIndex)
	{
		CrxConfigManager::GetPwaAugmentationIndex(SubSection,ReaderValue);
	}
	//Calls function if node element is PWA AugmentationIndex@HR75
	else if(SubSectionNode == CrxConfigXmlTag::AugmentationIndexAtHR75)
	{
		CrxConfigManager::GetPwaAugmentationIndexAtHR75(SubSection,ReaderValue);
	}
	//Calls function if node element is PWA CaptureInput
	else if(SubSectionNode == CrxConfigXmlTag::CaptureInput)
	{
		CrxConfigManager::GetPwaCaptureInput(SubSection,ReaderValue);
	}
	else if(SubSectionNode == CrxConfigXmlTag::SimulationType)
	{
		CrxConfigManager::GetPwaSimulationType(SubSection,ReaderValue);
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}

}
//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
void CrxConfigManager::GetBpSettingsNode(String^ SubSection, String^ SubSectionNode , String^ ReaderValue)
{
	//Calls function if node element is Device
	if(SubSectionNode == CrxConfigXmlTag::Device)
	{
		CrxConfigManager::GetBpDevice(SubSection,ReaderValue);
	}
	//Calls function if node element is NumberofAssessments
	else if(SubSectionNode == CrxConfigXmlTag::NumberofAssessments)
	{
		CrxConfigManager::GetBpNumberofAssessments(SubSection,ReaderValue);
	}
	//Calls function if node element is AutoPWA
	else if(SubSectionNode == CrxConfigXmlTag::AutoPWA)
	{
		CrxConfigManager::GetBpAutoPWA(SubSection,ReaderValue);
	}
	////Calls function if node element is BloodPressure
	//else if(SubSectionNode == CrxConfigXmlTag::BloodPressure)
	//{
	//	CrxConfigManager::GetBpBloodPressure(SubSection,ReaderValue);
	//}
	else
	if (SubSectionNode == CrxConfigXmlTag::AutoPWASP)
	{	
		CrxConfigManager::GetBpAutoPWASP(SubSection,ReaderValue);		
	}
	else
	if (SubSectionNode == CrxConfigXmlTag::AutoPWADP)
	{	
		CrxConfigManager::GetBpAutoPWADP(SubSection,ReaderValue);		
	}	
	else
	if (SubSectionNode == CrxConfigXmlTag::AutoPWAPP)
	{	
		CrxConfigManager::GetBpAutoPWAPP(SubSection,ReaderValue);		
	}
	else
	if (SubSectionNode == CrxConfigXmlTag::AutoPWASPThreshold)
	{	
		CrxConfigManager::GetBpAutoPWASPThreshold(SubSection,ReaderValue);		
	}
	else
	if (SubSectionNode == CrxConfigXmlTag::AutoPWAPPThreshold)
	{	
		CrxConfigManager::GetBPAutoPWAPPThreshold(SubSection,ReaderValue);		
	}
	else
	if (SubSectionNode == CrxConfigXmlTag::AutoPWADPThreshold)
	{	
		CrxConfigManager::GetBpAutoPWADPThreshold(SubSection,ReaderValue);		
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}

}
//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011

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

//void CrxConfigManager::GetBloodPressureOption(String^ SubSection, String^ ReaderValue)
//{
//	//Get the Get Blood Pressure Details
//	//Temporary variables
//	int BloodPressureValue = 0;
//	String^ tempValue  = nullptr;
//	
//	tempValue  = ReaderValue->ToUpper();
//
//	tempValue = tempValue->Replace(CrxConfigXmlTag::Blank,String::Empty);
//
//	if(tempValue == CrxConfigBloodPressureOption::SPandDP)
//	{
//		//BloodPressureValue = 0;
//		BloodPressureValue = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxGenBPOptSPandDP);
//	}
//	else 
//	if(tempValue == CrxConfigBloodPressureOption::SPandMP)
//	{
//		//BloodPressureValue = 1;
//		BloodPressureValue = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxGenBPOptSPandMP);
//	}
//	else 
//	if(tempValue == CrxConfigBloodPressureOption::MPandDP)
//	{
//		//BloodPressureValue = 2;
//		BloodPressureValue = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxGenBPOptMPandDP);
//	}
//	else
//	{
//		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
//	}
//
//	if(SubSection == CrxConfigXmlTag::Default)
//	{
//		_gSetInternal->BloodPressureEntryOptions = BloodPressureValue;
//	}
//	else
//	{
//		_instance->_generalSettings->BloodPressureEntryOptions = BloodPressureValue;
//	}
//}

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
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigXmlTag::StartUpModeValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}

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
void CrxConfigManager::GetSystemKey(String ^SubSection, String ^ReaderValue)
{
	//Get Id details
	if(SubSection == CrxConfigXmlTag::User)
	{
		_instance->_generalSettings->Key = ReaderValue;
	}
	else if (SubSection == CrxConfigXmlTag::Default)
	{
		_gSetInternal->Key = nullptr;
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
}
////Begin: AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011
//void CrxConfigManager::GetId(String ^SubSection, String ^ReaderValue)
//{
//	//Get Id details
//	if(SubSection == CrxConfigXmlTag::User)
//	{
//		_instance->_generalSettings->Id = ReaderValue;
//	}
//	else if (SubSection == CrxConfigXmlTag::Default)
//	{
//		_gSetInternal->Id = nullptr;
//	}
//	else
//	{
//		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
//	}
//}
//void CrxConfigManager::GetSn(String ^SubSection, String ^ReaderValue)
//{
//	//Get Sn details
//	if(SubSection == CrxConfigXmlTag::User)
//	{
//		_instance->_generalSettings->Sn= ReaderValue;
//	}
//	else if (SubSection == CrxConfigXmlTag::Default)
//	{
//		_gSetInternal->Sn = nullptr;
//	}
//	else
//	{
//		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
//	}
//}
//void CrxConfigManager::GetVerify(String ^SubSection, String ^ReaderValue)
//{
//	//Get Verify details
//	if(SubSection == CrxConfigXmlTag::User)
//	{
//		_instance->_generalSettings->Verify = ReaderValue;
//	}
//	else if (SubSection == CrxConfigXmlTag::Default)
//	{
//		_gSetInternal->Verify = nullptr;
//	}
//	else
//	{
//		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
//	}
//}
//void CrxConfigManager::GetCkSum(String ^SubSection, String ^ReaderValue)
//{
//	//Get CkSum details
//	if(SubSection == CrxConfigXmlTag::User)
//	{
//		_instance->_generalSettings->Cksum = ReaderValue;
//	}
//	else if (SubSection == CrxConfigXmlTag::Default)
//	{
//		_gSetInternal->Cksum = nullptr;
//	}
//	else
//	{
//		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
//	}
//}
//
////End: AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011
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
void CrxConfigManager::GetNormalRange(String^ SubSection, String^ ReaderValue)
{
	//Get the Normal Range Details
	//Temporary variables
	bool NormlRange = false;
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigXmlTag::CheckYesNoValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
	NormlRange = (tempValue == CrxConfigXmlTag::UpperYES);

	if(SubSection == CrxConfigXmlTag::Default)
	{
		_pSetInternal->NormalRange = NormlRange;
	}
	else
	{
		_instance->_pwvSettings->NormalRange = NormlRange;
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
//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
//***********************************************************************
//Get PWA Settings Functions
//***********************************************************************
void CrxConfigManager::GetPwaCaptureTime(String^ SubSection, String^ ReaderValue)
{
		//Get the Get Capture time Details
	//Temporary variables
	int CaptureTime = Convert::ToInt32(CrxGenPwaValue::CrxPwaCapture5Seconds);
	String^ tempValue  = nullptr;

	tempValue  = ReaderValue->ToUpper();

	tempValue = tempValue->Replace(CrxConfigXmlTag::Blank,String::Empty);

	if(tempValue == CrxConfigCaptureTime::FiveSeconds)
	{
		//CaptureTime = 0;
		CaptureTime = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwaValue::CrxPwaCapture5Seconds);
	}
	else if(tempValue == CrxConfigCaptureTime::TenSeconds)
	{
		//CaptureTime = 1;
		CaptureTime = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwaValue::CrxPwaCapture10Seconds);
	}
	else if(tempValue == CrxConfigCaptureTime::TwentySeconds)
	{
		//CaptureTime = 2;
		CaptureTime = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwaValue::CrxPwaCapture20Seconds);
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}

	if(SubSection == CrxConfigXmlTag::Default)
	{
		_pwaSetInternal->CaptureTime = CaptureTime;
	}
	else
	{
		_instance->_pwaSettings->CaptureTime = CaptureTime;
	}
}
void CrxConfigManager::GetPwaGuidanceBars(String^ SubSection, String^ ReaderValue)
{
	//Get the Guidance Bar Details
	//Temporary variables
	bool GuidanceBars = false;
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigXmlTag::CheckYesNoValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
	GuidanceBars = (tempValue == CrxConfigXmlTag::UpperYES);

	if(SubSection == CrxConfigXmlTag::Default)
	{
		_pwaSetInternal->GuidanceBars = GuidanceBars;
	}
	else
	{
		_instance->_pwaSettings->GuidanceBars = GuidanceBars;
	}
}
void CrxConfigManager::GetPwaAutoCapture(String^ SubSection, String^ ReaderValue)
{
	//Get the Auto Capture Details
	//Temporary variables
	bool AutoCapture = false;
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigXmlTag::CheckYesNoValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
	AutoCapture = (tempValue == CrxConfigXmlTag::UpperYES);

	if(SubSection == CrxConfigXmlTag::Default)
	{
		_pwaSetInternal->AutoCapture = AutoCapture;
	}
	else
	{
		_instance->_pwaSettings->AutoCapture = AutoCapture;
	}
}


void CrxConfigManager::GetPwaAugmentationIndex(String^ SubSection, String^ ReaderValue)
{
	//Get the Augmentation Index Details
	//Temporary variables
	bool AugmentationIndex = false;
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigXmlTag::CheckYesNoValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
	AugmentationIndex = (tempValue == CrxConfigXmlTag::UpperYES);

	if(SubSection == CrxConfigXmlTag::Default)
	{
		_pwaSetInternal->AugmentationIndex = AugmentationIndex;
	}
	else
	{
		_instance->_pwaSettings->AugmentationIndex = AugmentationIndex;
	}
}

void CrxConfigManager::GetPwaAugmentationIndexAtHR75(String^ SubSection, String^ ReaderValue)
{
	//Get the Augmentation Index At HR75 Details
	//Temporary variables
	bool AugmentationIndexAtHR75 = false;
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigXmlTag::CheckYesNoValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
	AugmentationIndexAtHR75 = (tempValue == CrxConfigXmlTag::UpperYES);

	if(SubSection == CrxConfigXmlTag::Default)
	{
		_pwaSetInternal->AugmentationIndexAtHR75 = AugmentationIndexAtHR75;
	}
	else
	{
		_instance->_pwaSettings->AugmentationIndexAtHR75 = AugmentationIndexAtHR75;
	}

}

void CrxConfigManager::GetPwaCaptureInput(String^ SubSection, String^ ReaderValue)
{
	//Get the PWA Capture Input Details
	//Temporary variables
	int CaptureInput = 0; 
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigPwaCaptureInput::CompareStr;

	tempValue = tempValue->Replace(CrxConfigXmlTag::Blank,String::Empty);

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}

	//CaptureInput = (tempValue == CrxConfigPwaCaptureInput::PressureCuff ? Convert::ToInt32(CrxPwaCaptureInput::Cuff) : Convert::ToInt32(CrxPwaCaptureInput::Tonometer));
	CaptureInput = (tempValue == CrxConfigPwaCaptureInput::Tonometer);
	if(SubSection == CrxConfigXmlTag::Default)
	{
		_pwaSetInternal->CaptureInput = CaptureInput;
	}
	else
	{
		_instance->_pwaSettings->CaptureInput = CaptureInput;
	}	
}

//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2245, 17-Jun-2011
void CrxConfigManager::GetPwaSimulationType(String^ SubSection, String^ ReaderValue)
{
	//Get the Simulation Type Details
	//Temporary variables
	if(SubSection == CrxConfigXmlTag::User)
	{
		_instance->_pwaSettings->SimulationType = ReaderValue;
	}
	else if (SubSection == CrxConfigXmlTag::Default)
	{
		_pwaSetInternal->SimulationType= ReaderValue;
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
}
//End  : AtCor-Drop2-Sprint1, TM, SWREQ2245, 17-Jun-2011
//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011

//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
//***********************************************************************
//Get BP Settings Functions
//***********************************************************************
void CrxConfigManager::GetBpDevice(String^ SubSection, String^ ReaderValue)
{
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigXmlTag::DeviceValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}

	//Get BP Device details
	if(SubSection == CrxConfigXmlTag::Default)
	{
		_bpSetInternal->Device = ReaderValue;
	}
	else
	{
		_instance->_bpSettings->Device = ReaderValue;
	}	
}
void CrxConfigManager::GetBpNumberofAssessments(String^ SubSection, String^ ReaderValue)
{
	int NumberofAssessments = Convert::ToInt32(NumberofAssessments::One);
	String^ tempValue  = nullptr;
	int temp = 0;

	tempValue  = ReaderValue->ToUpper();

	tempValue = tempValue->Replace(CrxConfigXmlTag::Blank,String::Empty);
	temp = Convert::ToInt32(tempValue);

	if(temp >= Convert::ToInt32(NumberofAssessments::One) && temp <= Convert::ToInt32(NumberofAssessments::Five) )
	{
		NumberofAssessments = temp;
	}
	else
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
	
	//Get Number of Assessments details
	if(SubSection == CrxConfigXmlTag::Default)
	{
		_bpSetInternal->NumberofAssessments = NumberofAssessments;
	}
	else
	{
		_instance->_bpSettings->NumberofAssessments = NumberofAssessments;
	}	
}
void CrxConfigManager::GetBpAutoPWA(String^ SubSection, String^ ReaderValue)
{
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();
	chkVal = CrxConfigXmlTag::CheckYesNoValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}

	//Get Auto PWA details
	if(SubSection == CrxConfigXmlTag::Default)
	{
		_bpSetInternal->AutoPWA = ReaderValue;
	}
	else
	{
		_instance->_bpSettings->AutoPWA = ReaderValue;
	}	
}
//void CrxConfigManager::GetBpBloodPressure(String^ SubSection, String^ ReaderValue)
//{
//	
//	////Get Blood Pressure details
//	//if(SubSection == CrxConfigXmlTag::Default)
//	//{
//	//	_bpSetInternal->BloodPressure = nullptr;
//	//}
//	//else
//	//{
//	//	_instance->_bpSettings->BloodPressure = ReaderValue;
//	//}	
//
//	//Get the Get Blood Pressure Details
//	//Temporary variables
//	int BloodPressureValue = 0;
//	String^ tempValue  = nullptr;
//	
//	tempValue  = ReaderValue->ToUpper();
//
//	tempValue = tempValue->Replace(CrxConfigXmlTag::Blank,String::Empty);
//
//	if(tempValue == CrxConfigBloodPressureOption::SPandDP)
//	{
//		BloodPressureValue = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxBloodPressureInput::CrxGenBPOptSPandDP);
//	}
//	else 
//	if(tempValue == CrxConfigBloodPressureOption::SPandMP)
//	{
//		BloodPressureValue = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxBloodPressureInput::CrxGenBPOptSPandMP);
//	}
//	else 
//	if(tempValue == CrxConfigBloodPressureOption::MPandDP)
//	{
//		BloodPressureValue = Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxBloodPressureInput::CrxGenBPOptMPandDP);
//	}
//	else
//	{
//		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
//	}
//
//	if(SubSection == CrxConfigXmlTag::Default)
//	{
//		_bpSetInternal->BloodPressure = BloodPressureValue;
//	}
//	else
//	{
//		_instance->_bpSettings->BloodPressure = BloodPressureValue;
//	}
//}
void CrxConfigManager::GetBpAutoPWASP(String^ SubSection, String^ ReaderValue)
{
	//Get the Patient Privacy Details
	//Temporary variables
	bool AutoPWAValue = false;
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();

	chkVal = CrxConfigXmlTag::CheckYesNoValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
	AutoPWAValue = (tempValue == CrxConfigXmlTag::UpperYES);

	if(SubSection == CrxConfigXmlTag::Default)
	{
		_bpSetInternal->AutoPWASP = AutoPWAValue;
	}
	else
	{
		_instance->_bpSettings->AutoPWASP = AutoPWAValue;
	}
}
void CrxConfigManager::GetBpAutoPWAPP(String^ SubSection, String^ ReaderValue)
{
	//Get the Patient Privacy Details
	//Temporary variables
	bool AutoPWAValue = false;
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();

	chkVal = CrxConfigXmlTag::CheckYesNoValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
	AutoPWAValue = (tempValue == CrxConfigXmlTag::UpperYES);

	if(SubSection == CrxConfigXmlTag::Default)
	{
		_bpSetInternal->AutoPWAPP = AutoPWAValue;
	}
	else
	{
		_instance->_bpSettings->AutoPWAPP = AutoPWAValue;
	}
}
void CrxConfigManager::GetBpAutoPWADP(String^ SubSection, String^ ReaderValue)
{
	//Get the Patient Privacy Details
	//Temporary variables
	bool AutoPWAValue = false;
	String^ tempValue  = nullptr;
	String^ chkVal = nullptr;

	tempValue  = ReaderValue->ToUpper();

	chkVal = CrxConfigXmlTag::CheckYesNoValue;

	if(chkVal->Contains(CrxConfigXmlTag::TagSeparator + tempValue + CrxConfigXmlTag::TagSeparator) == false)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCorruptErrCd, CrxStructCommonResourceMsg::CrxErrFileCorrupt, ErrorSeverity::Exception);//corrupt file//corrupt file
	}
	AutoPWAValue = (tempValue == CrxConfigXmlTag::UpperYES);

	if(SubSection == CrxConfigXmlTag::Default)
	{
		_bpSetInternal->AutoPWADP = AutoPWAValue;
	}
	else
	{
		_instance->_bpSettings->AutoPWADP = AutoPWAValue;
	}
}
void CrxConfigManager::GetBpAutoPWASPThreshold(String^ SubSection, String^ ReaderValue)
{	
	//Get BpAutoPWASPThreshold details
	if(SubSection == CrxConfigXmlTag::Default)
	{
		_bpSetInternal->AutoPWASPThreshold = Convert::ToInt32(ReaderValue);
	}
	else
	{
		_instance->_bpSettings->AutoPWASPThreshold = Convert::ToInt32(ReaderValue);
	}	
}
void CrxConfigManager::GetBPAutoPWAPPThreshold	(String^ SubSection, String^ ReaderValue)
{	
	//Get BpAutoPWASPThreshold details
	if(SubSection == CrxConfigXmlTag::Default)
	{
		_bpSetInternal->AutoPWAPPThreshold = Convert::ToInt32(ReaderValue);
	}
	else
	{
		_instance->_bpSettings->AutoPWAPPThreshold = Convert::ToInt32(ReaderValue);
	}	
}
void CrxConfigManager::GetBpAutoPWADPThreshold(String^ SubSection, String^ ReaderValue)
{	
	//Get BpAutoPWASPThreshold details
	if(SubSection == CrxConfigXmlTag::Default)
	{
		_bpSetInternal->AutoPWADPThreshold = Convert::ToInt32(ReaderValue);
	}
	else
	{
		_instance->_bpSettings->AutoPWADPThreshold = Convert::ToInt32(ReaderValue);
	}	
}
//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011

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
//void CrxConfigManager::SetBloodPressureOption(CrxStructGeneralSetting^ gs, XmlNode^ node)
//{
//	//if(gs->BloodPressureEntryOptions == 0)
//	if((gs->BloodPressureEntryOptions == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxGenBPOptSPandDP)))
//	{
//		node->InnerText = CrxConfigBloodPressureOption::SPandDPSetValue;								
//	}
//	else
//	//if(gs->BloodPressureEntryOptions == 1)
//	if((gs->BloodPressureEntryOptions == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxGenBPOptSPandMP)))
//	{
//		node->InnerText = CrxConfigBloodPressureOption::SPandMPSetValue;
//	}
//	else
//	//if(gs->BloodPressureEntryOptions == 2)
//	if((gs->BloodPressureEntryOptions == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxGenBPOptMPandDP)))
//	{
//		node->InnerText = CrxConfigBloodPressureOption::MPandDPSetValue;
//	}
//}
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
//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
void CrxConfigManager::SetStartupMode(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	if(gs->StartupMode != nullptr)
	{
		node->InnerText = gs->StartupMode;
	}
	else
	{
		node->InnerText = CrxConfigXmlTag::Blank;
	}
}

void CrxConfigManager::SetStartupScreen(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	if(gs->StartupScreen != nullptr)
	{
		node->InnerText = gs->StartupScreen;
	}
	else
	{
		node->InnerText = CrxConfigXmlTag::Blank;
	}
}
void CrxConfigManager::SetSystemKey(CrxStructGeneralSetting^ gs, XmlNode^ node)
{
	if(gs->Key != nullptr)
	{
		node->InnerText = gs->Key;
	}
	else
	{
		node->InnerText = CrxConfigXmlTag::Blank;
	}
}
//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
////Begin: AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011
//void CrxConfigManager::SetId(CrxStructGeneralSetting^ gs, XmlNode^ node)
//{
//	if(gs->Id != nullptr)
//	{
//		node->InnerText = gs->Id;
//	}
//	else
//	{
//		node->InnerText = CrxConfigXmlTag::Blank;
//	}
//}
//void CrxConfigManager::SetSn(CrxStructGeneralSetting^ gs, XmlNode^ node)
//{
//	if(gs->Sn != nullptr)
//	{
//		node->InnerText = gs->Sn;
//	}
//	else
//	{
//		node->InnerText = CrxConfigXmlTag::Blank;
//	}
//}
//void CrxConfigManager::SetVerify(CrxStructGeneralSetting^ gs, XmlNode^ node)
//{
//	if(gs->Verify != nullptr)
//	{
//		node->InnerText = gs->Verify;
//	}
//	else
//	{
//		node->InnerText = CrxConfigXmlTag::Blank;
//	}
//}
//void CrxConfigManager::SetCkSum(CrxStructGeneralSetting^ gs, XmlNode^ node)
//{
//	if(gs->Cksum != nullptr)
//	{
//		node->InnerText = gs->Cksum;
//	}
//	else
//	{
//		node->InnerText = CrxConfigXmlTag::Blank;
//	}
//}
//
////End  : AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011


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
void CrxConfigManager::SetNormalRange(CrxStructPwvSetting^ ps, XmlNode^ node)
{
	if(ps->NormalRange == false)
	{
		node->InnerText = CrxConfigXmlTag::LowerNo;								
	}
	else
	if(ps->NormalRange == true)
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
//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
//********************************************
//Set PWA Settings Functions
//********************************************
void CrxConfigManager::SetPwaCaptureTime(CrxStructPwaSetting^ pwas, XmlNode^ node)
{
	//if(ps->CaptureTime == 0)
	if((pwas->CaptureTime == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxPwvCapture5Seconds)))
	{
		node->InnerText = CrxConfigCaptureTime::FiveSecondsSetValue;								
	}
	else
	//if(ps->CaptureTime == 1)
	if((pwas->CaptureTime == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxPwvCapture10Seconds)))
	{
		node->InnerText = CrxConfigCaptureTime::TenSecondsSetValue;
	}
	else
	//if(ps->CaptureTime == 2)
	if((pwas->CaptureTime == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxGenPwvValue::CrxPwvCapture20Seconds)))
	{
		node->InnerText = CrxConfigCaptureTime::TwentySecondsSetValue;
	}
}
void CrxConfigManager::SetPwaGuidanceBars(CrxStructPwaSetting^ pwas, XmlNode^ node)
{
	if(pwas->GuidanceBars == false)
	{
		node->InnerText = CrxConfigXmlTag::LowerNo;								
	}
	else
		if(pwas->GuidanceBars == true)
	{
		node->InnerText = CrxConfigXmlTag::LowerYes;
	}
}
void CrxConfigManager::SetPwaAutoCapture(CrxStructPwaSetting^ pwas, XmlNode^ node)
{
	if(pwas->AutoCapture == false)
	{
		node->InnerText = CrxConfigXmlTag::LowerNo;								
	}
	else
		if(pwas->AutoCapture == true)
	{
		node->InnerText = CrxConfigXmlTag::LowerYes;
	}

}
void CrxConfigManager::SetPwaAugmentationIndex(CrxStructPwaSetting^ pwas, XmlNode^ node)
{
	if(pwas->AugmentationIndex == false)
	{
		node->InnerText = CrxConfigXmlTag::LowerNo;								
	}
	else
		if(pwas->AugmentationIndex == true)
	{
		node->InnerText = CrxConfigXmlTag::LowerYes;
	}
}
void CrxConfigManager::SetPwaAugmentationIndexAtHR75(CrxStructPwaSetting^ pwas, XmlNode^ node)
{
	if(pwas->AugmentationIndexAtHR75 == false)
	{
		node->InnerText = CrxConfigXmlTag::LowerNo;								
	}
	else
		if(pwas->AugmentationIndexAtHR75 == true)
	{
		node->InnerText = CrxConfigXmlTag::LowerYes;
	}
}

void CrxConfigManager::SetPwaCaptureInput(CrxStructPwaSetting^ pwas, XmlNode^ node)
{	
	/*if((pwas->CaptureInput == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxPwaCaptureInput::Cuff)))
	{
		node->InnerText = CrxConfigPwaCaptureInput::CuffSetValue;								
	}
	else
	if((pwas->CaptureInput == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxPwaCaptureInput::Tonometer)))
	{
		node->InnerText = CrxConfigPwaCaptureInput::TonometerSetValue;
	}*/
	if(pwas->CaptureInput)
	{
		node->InnerText = CrxConfigPwaCaptureInput::TonometerSetValue;
	}
	else
	{
		node->InnerText = CrxConfigPwaCaptureInput::CuffSetValue;
	}
}

//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2245, 17-Jun-2011
void CrxConfigManager::SetPwaSimulationType(CrxStructPwaSetting^ pwas, XmlNode^ node)
{
	if(pwas->SimulationType != nullptr) 
    {
        node->InnerText = pwas->SimulationType;
    }
    else 
    {
		node->InnerText = CrxConfigXmlTag::Blank; 
    }
}
//End  : AtCor-Drop2-Sprint1, TM, SWREQ2245, 17-Jun-2011

//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
//********************************************
//Set BP Settings Functions
//********************************************
void CrxConfigManager::SetBpDevice(CrxStructBpSetting^ bps, XmlNode^ node)
{
	if(bps->Device != nullptr) 
    {
        node->InnerText = bps->Device;
    }
    else 
    {
		node->InnerText = CrxConfigXmlTag::Blank; 
    }

}
//Set Number of Assessments from config file
void CrxConfigManager::SetBpNumberofAssessments(CrxStructBpSetting^ bps, XmlNode^ node)
{
	int Ass = bps->NumberofAssessments;
	if(bps->NumberofAssessments >= 1 && bps->NumberofAssessments <= 5 ) 
    {
		node->InnerText = Convert::ToString(Ass);//->ToString();
    }
    else 
    {
		node->InnerText = "0"; 
    }
}

//Set Auto PWA from config file
void CrxConfigManager::SetBpAutoPWA(CrxStructBpSetting^ bps, XmlNode^ node)
{
	if(bps->AutoPWA != nullptr) 
    {
        node->InnerText = bps->AutoPWA;
    }
    else 
    {
		node->InnerText = CrxConfigXmlTag::Blank; 
    }
}

//Set Blood Pressure from config file
//void CrxConfigManager::SetBpBloodPressure(CrxStructBpSetting^ bps, XmlNode^ node)
//{
//	/*if(bps->BloodPressure != nullptr) 
//    {
//        node->InnerText = bps->BloodPressure;
//    }
//    else 
//    {
//		node->InnerText = CrxConfigXmlTag::Blank; 
//    }*/	
//	if((bps->BloodPressure == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxBloodPressureInput::CrxGenBPOptSPandDP)))
//	{
//		node->InnerText = CrxConfigBloodPressureOption::SPandDPSetValue;								
//	}
//	else
//	if((bps->BloodPressure == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxBloodPressureInput::CrxGenBPOptSPandMP)))
//	{
//		node->InnerText = CrxConfigBloodPressureOption::SPandMPSetValue;
//	}
//	else
//	if((bps->BloodPressure == Convert::ToInt32(AtCor::Scor::CrossCutting::Configuration::CrxBloodPressureInput::CrxGenBPOptMPandDP)))
//	{
//		node->InnerText = CrxConfigBloodPressureOption::MPandDPSetValue;
//	}
//	
//}
void CrxConfigManager::SetBpAutoPWASP(CrxStructBpSetting^ bps, XmlNode^ node)
{
	if(bps->AutoPWASP == false)
	{
		node->InnerText = CrxConfigXmlTag::LowerNo;								
	}
	else
	if(bps->AutoPWASP == true)
	{
		node->InnerText = CrxConfigXmlTag::LowerYes;
	}
}
void CrxConfigManager::SetBpAutoPWAPP(CrxStructBpSetting^ bps, XmlNode^ node)
{
	if(bps->AutoPWAPP == false)
	{
		node->InnerText = CrxConfigXmlTag::LowerNo;								
	}
	else
	if(bps->AutoPWAPP == true)
	{
		node->InnerText = CrxConfigXmlTag::LowerYes;
	}
}
void CrxConfigManager::SetBpAutoPWADP(CrxStructBpSetting^ bps, XmlNode^ node)
{
	if(bps->AutoPWADP == false)
	{
		node->InnerText = CrxConfigXmlTag::LowerNo;								
	}
	else
	if(bps->AutoPWADP == true)
	{
		node->InnerText = CrxConfigXmlTag::LowerYes;
	}
}
void CrxConfigManager::SetBpAutoPWASPThreshold(CrxStructBpSetting^ bps, XmlNode^ node)
{
	if(bps->AutoPWASPThreshold != 0) 
    {
		node->InnerText = Convert::ToString(bps->AutoPWASPThreshold);
    }
    else 
    {
		node->InnerText = "0"; 
    }	
}
void CrxConfigManager::SetBpAutoPWAPPThreshold(CrxStructBpSetting^ bps, XmlNode^ node)
{
	if(bps->AutoPWAPPThreshold != 0) 
    {
		node->InnerText = Convert::ToString(bps->AutoPWAPPThreshold);
    }
    else 
    {
		node->InnerText = "0"; 
    }	
}
void CrxConfigManager::SetBpAutoPWADPThreshold(CrxStructBpSetting^ bps, XmlNode^ node)
{
	if(bps->AutoPWADPThreshold != 0) 
    {
		node->InnerText = Convert::ToString(bps->AutoPWADPThreshold);
    }
    else 
    {
		node->InnerText = "0"; 
    }	
}
//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011