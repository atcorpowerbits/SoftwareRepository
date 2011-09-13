/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalPwvMode.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for DalMeasurementMode class.
*/

#pragma once


#include "stdafx.h"
#include "DalCommon.h"
//#include "IDalHandler.h"
//#include "DalDeviceHandler.h"
//#include "DalEventContainer.h"
//#include "DalSimulationFile.h"
//#include "DalSimulationHandler.h"
//#include "DalStatusHandler.h"
#include "DalMeasurementMode.h"

using namespace System;
using namespace AtCor::Scor::CrossCutting;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalModule
			* @brief	Exposes main functionality for the DAL module. Singleton class.
			*/
			public ref class DalPwvMode : public DalMeasurementMode
			{
			private:

				static DalPwvMode^ _instance = gcnew DalPwvMode();

				DalPwvMode();
				DalPwvMode(DalPwvMode^);
				DalPwvMode^ operator= (DalPwvMode);

			internal:	
				
			public:
				
				/**
				* Returns the current singleton instance.
				*/
				static property DalPwvMode^ Instance
				{
					DalPwvMode^ get()
					{
						return DalPwvMode::_instance;
					};
				};
			};
		}
	}
}