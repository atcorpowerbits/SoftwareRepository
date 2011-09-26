/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :      CrxCrossCutting.cpp
        
     Description  :      Declaration for Cross-cutting namespace and common methods
*/

#include "stdafx.h"

#include "CrxCrossCutting.h"

using namespace AtCor::Scor::CrossCutting;

CultureInfo^ CrxCommon::GetCommCultureInfo()
{	
	String^ CommCI = nullptr;									
	try
	{
		//Get the General Settings values from the config file
		CrxConfigManager::Instance->GetGeneralUserSettings();
		//Get the Culture code from general settings structure and trim the value 
		CommCI =  CrxConfigManager::Instance->GeneralSettings->CultureInfo->ToString()->Trim();
		//Check for null and empty value
		if (CommCI == nullptr || CommCI->Length == 0) 
		{		
			//Set culture to default culture(en-US)
			CommCI = _defaultCulture;
		}
	}
	catch (Exception^ )
	{
		//if exception occurs
		//Set culture to default culture(en-US)
		CommCI = _defaultCulture;
	}
	try
	{
		//Set application culture to Culture provided in the config file
		gCI = gcnew CultureInfo(CommCI);
	}
	catch (Exception^ )
	{
		//if exception occurs
		//Set application culture to default culture(en-US)
		gCI = gcnew CultureInfo(_defaultCulture);
	}
	return gCI;
}

void CrxCommon::SetNeutralCultureInfo()
{
	//Set the neutral culture object to default culture(en-US)
	nCI = gcnew CultureInfo(_defaultCulture);
}
