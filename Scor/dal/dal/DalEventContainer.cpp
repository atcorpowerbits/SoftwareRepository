/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalEventContainer.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalEventContainer class code
*/

#include "Stdafx.h"
#include "DalEventContainer.h"

using namespace AtCor::Scor::DataAccess;

namespace AtCor{
	namespace Scor{
		namespace DataAccess{

			DalTonometerDataEventArgs::DalTonometerDataEventArgs(unsigned short data)
						{
							//assign the parameter to class member
							this->data = data;
						}

			DalCuffPulseEventArgs::DalCuffPulseEventArgs(unsigned short data) 
			{
				//assign the parameter to class member
				this->data = data;
			}
			

			DalCuffStatusEventArgs::DalCuffStatusEventArgs(DalCuffStateFlags cuffStateFlag)
			{
				//assign the parameter to class member
				this->CuffStateFlag  = cuffStateFlag;
			}

			DalEventContainer::DalEventContainer()
			{
				//Empty code block to implement singleton
			}

			//Overloaded copy contructor. 
			DalEventContainer::DalEventContainer(DalEventContainer^)
			{
				//Does nothing. Made private to implement singleton.
			}

			//overloaded assignment operator. Private to implement singleton.
			DalEventContainer^ DalEventContainer::operator = (DalEventContainer)
			{
				//return the  current instance itself.
				return this;
			}

			DalModuleErrorAlarmEventArgs::DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag data, String^ alarmSource, DalAlarmSource alarmSourceEnum)
			{
				//assign the parameter to class member
				this->ErrorAlarmStatus = data;

				this->AlarmSourceName = alarmSource;
				this->SpecificAlarmSource = alarmSourceEnum;
				
			}

			DalModuleErrorAlarmEventArgs::DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag data, String^ alarmSource, DalAlarmSource alarmSourceEnum, ScorException^ scorExceptionObject)
			{
				//assign the parameter to class member
				this->ErrorAlarmStatus = data;

				this->AlarmSourceName = alarmSource;
				this->SpecificAlarmSource = alarmSourceEnum;

				this->ScorExceptionObject = scorExceptionObject;
				
			}

			DalTonometerStatusEventArgs::DalTonometerStatusEventArgs(DalTonometerState tonometerStateFlag)
			{
				//assign the parameter to class member
				this->TonometerStateFlag = tonometerStateFlag;
			}

			DalUnusedStatusFlagEventArgs::DalUnusedStatusFlagEventArgs(DalUnusedStatusFlagBit changedStatusFlag, bool setResetValue)
			{
				this->UnusedStatusFlagChanged = changedStatusFlag;
				this->ValueSetReset = setResetValue;
			}

			DalNIBPDataEventArgs::DalNIBPDataEventArgs(unsigned short error,
													   unsigned short sp,
													   unsigned short dp,
													   unsigned short mp, 
													   unsigned short hr)
			{
				this->nibpError = error;
				this->nibpSP = sp;
				this->nibpDP = dp;
				this->nibpMP = mp;
				this->nibpHR = hr;
				this->measurementStatus = NibpMeasurementStatus::Unsuccessful; 
			}


			DalNIBPDataEventArgs::DalNIBPDataEventArgs(unsigned short error,
													   unsigned short sp,
													   unsigned short dp,
													   unsigned short mp, 
													   unsigned short hr,
														NibpMeasurementStatus resultStatus,
														String^ errorMessage)
			{
				this->nibpError = error;
				this->nibpSP = sp;
				this->nibpDP = dp;
				this->nibpMP = mp;
				this->nibpHR = hr;
				this->measurementStatus = resultStatus;
				this->ErrorMessage = errorMessage;

			}
		}
	}
}
