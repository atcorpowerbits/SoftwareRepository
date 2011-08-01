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
		CrxConfigManager::Instance->GetGeneralUserSettings();
		CommCI =  CrxConfigManager::Instance->GeneralSettings->CultureInfo->ToString()->Trim();
		if (CommCI == nullptr || CommCI->Length == 0) 
		{			
			CommCI = _defaultCulture;
		}
	}
	catch (Exception^ )
	{
		CommCI = _defaultCulture;
	}		
	gCI = gcnew CultureInfo(CommCI);
	return gCI;
}

void CrxCommon::SetNeutralCultureInfo()
{
	nCI = gcnew CultureInfo(_defaultCulture);
}
