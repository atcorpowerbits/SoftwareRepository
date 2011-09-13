/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalModule.h
        
     Author       :		 Deepak D'Souza/Alok Sahu
 
     Description  :      Header file for DalStreamingMode class.
*/

#pragma once


#include "stdafx.h"
#include "DalCommon.h"
#include "IDalHandler.h"
#include "DalDeviceHandler.h"
#include "DalEventContainer.h"
#include "DalSimulationFile.h"
#include "DalSimulationHandler.h"
#include "DalStatusHandler.h"

using namespace System;
using namespace AtCor::Scor::CrossCutting;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{


			/**
			* @class DalStreamingMode
			* @brief	Decide the Streaming mode whether PWV or PWA.
			*/
			public ref class DalStreamingMode
			{
			private:

				static DalStreamingMode^ _instance = gcnew DalStreamingMode();

				DalStreamingMode();
				DalStreamingMode( DalStreamingMode^);
				DalStreamingMode^ operator= ( DalStreamingMode);


			internal:	
				//static IDalHandler^ _currentDevice; 
				
			public:
				
				/**
				* Returns the current singleton instance.
				*/
				static property DalStreamingMode^ Instance
				{
					DalStreamingMode^ get()
					{
						return DalStreamingMode::_instance;
					};
				};

			};
		}
	}
}