/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      IDalNibpHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      IDalNibpHandler interface file.
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"


using namespace System;
using namespace System::Timers;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{
			/**
			* @interface IDalNibpHandler
			* @brief Interface class to implement managers for EM4 and simulation devices.
			*
			* @see DalNibpSimulationHanlder, DalNibpDeviceHandler
			*/
			private interface class IDalNibpHandler
			{
				public:
			
				/**
				* Starts a BP measurement process with the specified initial pressure.
				* @param[in]	nibpMode	The age group for which measurement is to be taken as an enum
				* @param[in]	initialPressure	The inital pressure to set for this capture instance
				* @return	A boolean value indicating the success or failure of this process
				*/
				bool StartBP(DalNIBPMode nibpMode, unsigned short initialPressure);

				/**
				* Starts a BP measurement process.
				* @param[in]	nibpMode	The age group for which measurement is to be taken as an enum
				* @return	A boolean value indicating the success or failure of this process
				*/
				bool StartBP(DalNIBPMode nibpMode);

				/**
				* Stops a BP measurement and disconnects the NIBP module
				* @return	A boolean value indicating the success or failure of this process
				*/
				bool FinishBP();

				/**
				* Aborts an ongoing BP measurement.
				* @return	A boolean value indicating the success or failure of this process
				*/
				bool AbortBP();

			};

		}
	}
}



