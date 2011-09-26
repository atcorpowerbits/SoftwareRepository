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
			
				//TS STUB
				bool StartBP(DalNIBPMode nibpMode, unsigned short initialPressure);
				bool StartBP(DalNIBPMode nibpMode);
				bool FinishBP();
				bool AbortBP();

			};

		}
	}
}



