/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalnibpStatusHandler.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalNibpStatusHandler class code file.
*/

#include "stdafx.h"
#include "DalNibpStatusHandler.h"
#include "DalModule.h"

using namespace AtCor::Scor::DataAccess;

using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;

using namespace System;
using namespace  System::Collections::Generic;



bool DalNibpStatusHandler::ProcessStatusFlag(unsigned long statusBytes)
{
	//first check if the status flag has changed from the previous value
	if (!(CheckStatusFlagsChanged(statusBytes)))
	{
		//if no  then exit
		return true;
	}

	//if changed				
	//First break the status flag down into its  important sets
	SplitStatusFlagComponents(statusBytes);
	
	//then check individual parts
	
	try
	{
		//process the various parts in order of importance

		//SRB bit is accepted for NIBP
		if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.StopButton") == "Y")
		{
			ProcessStopButtonBitMask();
		}

		//power up bit is accepted for NIBp
		if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.PowerUpBit") == "Y")
		{
			ProcessPowerUpBitMask();
		}

		//Alalrm status bit is valid for NIBP
		//However some of the individual alarms should be ingnored 
		if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.AlarmFlag") == "Y")
		{
			//check alarms bfore anything else
			ProcessAlarmStatusFlag();
		}

		//Cuff status bits are ignored
		//Tonometer bits are ignored

		//All unused flags wont be checked  including BPRR and Resting

	
	}
	catch(ScorException^)
	{
		throw;
	}
	catch (Exception^ excepObj)
	{
		throw gcnew ScorException(excepObj);
	}

	return true;
}


void DalNibpStatusHandler::ProcessAlarmStatusFlag()
{
	
	if (CheckAlarmStatusFlagChanged(_newAlarmStatusBytes) == true)
	 {
		 //raise this event only when bit is on1 not when bit is zero.
		 if (_newAlarmStatusBytes)
		 {
			  String ^ alarmSource;
		 //Get the source of the alarm
		 alarmSource= DalModule::Instance->GetErrorAlarmSource();

		 //Get the alarm flag
		 DalAlarmSource thisAlarmSource = DalBinaryConversions::ConvertAlarmType(alarmSource);


		 //Check if the alarm flag is valid for NIBP. If not then ignore it.
		 if (IsAlarmValidForNibp(thisAlarmSource))
		 {
			 //raise an event only after getting the source of the error
			 DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, gcnew DalModuleErrorAlarmEventArgs(TranslateAlarmStatusBits(_newAlarmStatusBytes), alarmSource, thisAlarmSource ));
			 CrxLogger::Instance->Write("ProcessAlarmStatusFlag>>>OnDalModuleErrorAlarmEvent event raised _newAlarmStatusBytes:" + _newAlarmStatusBytes, ErrorSeverity::Debug);
		 }
		 //else inore it. Dont raise a warning.

		 }
	 }
}

bool DalNibpStatusHandler::IsAlarmValidForNibp(DalAlarmSource alarmSource)
{
	//Create an array of permitted alarms for NIBP
	List<DalAlarmSource>^ validAlarmFlags = gcnew List<DalAlarmSource>();
	validAlarmFlags->Add(DalAlarmSource::PowerUp);
	validAlarmFlags->Add(DalAlarmSource::Temperature);
	validAlarmFlags->Add(DalAlarmSource::SupplyRails);
	validAlarmFlags->Add(DalAlarmSource::SourceID0);
	validAlarmFlags->Add(DalAlarmSource::SourceID1);
	validAlarmFlags->Add(DalAlarmSource::SourceID2);
	//Add any more valid alarm flags here

	if (validAlarmFlags->Contains(alarmSource))
	{
		return true;
	}
	return false;
}

NibpMeasurementStatus DalNibpStatusHandler::ValidateBpData(unsigned short nibpErrorCode, unsigned short nibpStatus, String ^% errorMessage)
{
	NibpMeasurementStatus  resultStatus = NibpMeasurementStatus::Unsuccessful; //Default value
	bool dataCorrect = true;

	if(nibpErrorCode != 0)
	{
		dataCorrect = false;
	}
	if(nibpStatus != 0x01)
	{
		dataCorrect = false;
	}

	CrxLogger::Instance->Write("DAL: DalNibpGetBpDataCommand::GetBpDataAndRaiseEvent CheckRecievedData returned: " + dataCorrect + ". EC andBP ignored. Raising event!." , ErrorSeverity::Debug );
	
	//if(true) //revert this should be for testing only
	if (dataCorrect)
	{
		resultStatus = NibpMeasurementStatus::Successful ;
	}
	else
	{
		resultStatus = NibpMeasurementStatus::Unsuccessful;
		errorMessage = "BP data was extracted but is invalid.";  

		if (88 == nibpErrorCode)
		{
			errorMessage = "Brachial calibration error: {0}. Please turn EM4 off/on before starting a new measurement. Please refer to user manual for further corrective actions if necessary.";
			//TODO: resource file
		}
		else
		{
			errorMessage = "Brachial calibration error: {0}. Please refer to user manual for further corrective actions if necessary.";
			//TODO: resource file
		}
	}

	return resultStatus;
}