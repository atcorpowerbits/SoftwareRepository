/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalnibpStatusHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalNibpStatusHandler class header file.
*/

#pragma once

#include "stdafx.h"

#include "DalStatushandler.h"


using namespace System;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			private ref class DalNibpStatusHandler: public DalStatusHandler
			{
				public:

					/**
					* Breaks up the Status flag into its constituent parts and validates them. @n
					* Raises events when necessary.
					* this works differently for NIBP
					*
					* @param	statusBytes	The status flags as an unsigned long integer
					*
					* @returns	A bool value indicating the status of the operation
					*/
					static bool ProcessStatusFlag(unsigned long statusBytes);

					/**
					* Checks if the alarm bit of the status flag has changed.
					* Raises event if needed and performs any other action if needed.
					*/
					static void ProcessAlarmStatusFlag();

					static bool IsAlarmValidForNibp(DalAlarmSource alarmSource);

					/**
					* Checks nibp error code and  nibp status.
					* Returns Value and Message.
					*/
					static NibpMeasurementStatus ValidateBpData(unsigned short nibpErrorCode, unsigned short nibpStatus, String ^% errMessage);
			};


		}//End namespace DataAccess
	}
}
