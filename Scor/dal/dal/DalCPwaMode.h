/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCPwvMode.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for DalMeasurementMode class.
*/

#pragma once


#include "stdafx.h"
//#include "DalCommon.h"
//#include "IDalHandler.h"
//#include "DalDeviceHandler.h"
//#include "DalEventContainer.h"
//#include "DalSimulationFile.h"
//#include "DalSimulationHandler.h"
//#include "DalStatusHandler.h"

using namespace System;
using namespace AtCor::Scor::CrossCutting;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalModule
			* @brief	Exposes main functionality for the DAL module. Singleton class.
			*/
			public ref class DalCPwvMode : public DalMeasurementMode
			{
			private:

				static DalCPwvMode^ _instance = gcnew DalCPwvMode();

				DalCPwvMode();
				DalCPwvMode(DalCPwvMode^);
				DalCPwvMode^ operator= (DalCPwvMode);

			internal:	
				
			public:
				
				/**
				* Returns the current singleton instance.
				*/
				static property DalCPwvMode^ Instance
				{
					DalCPwvMode^ get()
					{
						return DalCPwvMode::_instance;
					};
				};

			};
		}
	}
}