/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :      CrxCrossCutting.cpp
        
     Description  :      Declaration for Cross-cutting namespace and common methods
*/

#include "stdafx.h"

#include "CrxCrossCutting.h"
#include "CrxMessaging.h"


using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;
using namespace AtCor::Scor::CrossCutting::Messaging;

CultureInfo^ CrxCommon::GetCommCultureInfo()
{	
	String^ CommCI = nullptr;									
	try
	{
		CrxConfigManager::Instance->GetGeneralUserSettings();
		CommCI =  CrxConfigManager::Instance->GeneralSettings->CultureInfo->ToString()->Trim();
		if (CommCI == nullptr || CommCI->Length == 0) 
		{			
			CommCI = "en-US";
		}
	}
	catch (Exception^ )
	{
		CommCI = "en-US";
	}		
	gCI = gcnew CultureInfo(CommCI);
	return gCI;
}
