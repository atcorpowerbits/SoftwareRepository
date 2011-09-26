/*
TODO: Remove this code in D2S5
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalMeasurementMode.h
        
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
#include "DalActiveDevice.h"

using namespace System;
using namespace AtCor::Scor::CrossCutting;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalModule
			* @brief	Exposes main functionality for the DAL module. Singleton class.
			*/
			public ref class DalMeasurementMode abstract
			{
			private:

				
			protected:
				DalMeasurementMode()
				{
				};
				//static DalMeasurementMode^ _instance = gcnew DalMeasurementMode();
				DalMeasurementMode(DalMeasurementMode^)
				{
					//overloaded copy counstructor.
					//Does nothing	
				};
				DalMeasurementMode^ operator= (DalMeasurementMode)
				{
					return nullptr;
				};

				DalStreamingMode _currentStreamingMode;	//Enum for Streaming mode(PWV/PWA..)

			internal:	
				
			public:
				
				/**
				* Starts the data capture process from the selected device after creating a 
				* buffer according to the specified parameters.
				* @param[in]	captureTime	The capture window time
				* @param[in]	samplingRate	The number of samples per second.
				*
				* @return	A boolean value specifying the success/failure of the operation.
				*/
				bool StartMeasurement(int captureTime, int samplingRate)
				{
					return DalActiveDevice::CurrentDevice->StartCapture(captureTime, samplingRate);
					
				};

				
				/**
				*  Sets the pressure value of the specified board.
				*
				* @param[in]	newPressure	The new pressure value to be set
				* @param[in]	cuffBoard	The board for which the pressure should be set
				*
				* @return	A boolean value indicating the success/failure of the poration
				*/
				bool SetPressure(unsigned int newPressure, EM4CuffBoard cuffBoard)
				{
					return DalActiveDevice::CurrentDevice->SetPressure(newPressure, cuffBoard);
				};
			};
		}
	}
}