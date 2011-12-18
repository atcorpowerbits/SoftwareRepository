/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCPwaDeviceHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalCPwaDeviceHandler class defintition
*/

#pragma once

#include "stdafx.h"
#include "DalDevicehandler.h"
#include "IDalNibpHandler.h"
#include "DalNibpDevicehandler.h"


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalCPwaDeviceHandler
			* @brief	Main handler class for CPWA to EM4 interface
			*/
			private ref class DalCPwaDeviceHandler: public DalDeviceHandler
			{	
			internal:
				
					/**
					* Constructor for this class
					*/
				DalCPwaDeviceHandler();
					IDalNibpHandler^ _nibpHandler; /**< Instance pointer*/
			public:

				/**
				* Start the data capture fromt the device. @n
				* Creates a buffer suitable for the specified time and sampling rate.
				* @param[in]	captureTime	the time frame in seconds for the capture window
				* @param[in]	samplingRate	The number of samples per second
				* @return A boolean value indicating succes of the operation
				*
				*/
				virtual bool StartCapture(int captureTime, int samplingRate) override;

				/**
				* Starts a BP measurement process with the specified initial pressure.
				* @param[in]	nibpMode	The age group for which measurement is to be taken as an enum
				* @param[in]	initialPressure	The inital pressure to set for this capture instance
				* @return	A boolean value indicating the success or failure of this process
				*/
				virtual bool StartBP(DalNIBPMode nibpMode, unsigned short initialPressure) override;

				/**
				* Starts a BP measurement process.
				* @param[in]	nibpMode	The age group for which measurement is to be taken as an enum
				* @return	A boolean value indicating the success or failure of this process
				*/
					virtual bool StartBP(DalNIBPMode nibpMode) override;
				
				/**
				* Stops a BP measurement and disconnects the NIBP module
				* @return	A boolean value indicating the success or failure of this process
				*/
					virtual bool FinishBP() override;

				/**
				* Aborts an ongoing BP measurement.
				* @return	A boolean value indicating the success or failure of this process
				*/
					virtual bool AbortBP() override;
			};

		} //End namespaces
	}
}