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

			//Deepak: No event to get EA source. It will be called by method
			//DalErrorAlarmSourceEventArgs::DalErrorAlarmSourceEventArgs(String^ data)
			//{
			//	//assign the parameter to class member
			//	this->ErrorAlarmSource  = data;
			//}

			DalModuleErrorAlarmEventArgs::DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag data, String^ alarmSource)
			{
				//assign the parameter to class member
				this->ErrorAlarmStatus = data;

				this->AlarmSourceName = alarmSource;
				
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

		}
	}
}
