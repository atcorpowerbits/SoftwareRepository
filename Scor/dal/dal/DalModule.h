/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalModule.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for DalModule class.
*/

#pragma once


#include "stdafx.h"
//#include "DalCommon.h"
//#include "IDalHandler.h"
#include "DalDeviceHandler.h"
#include "DalEventContainer.h"
//#include "DalSimulationFile.h"
//#include "DalSimulationHandler.h"
//#include "DalStatusHandler.h"
//#include "DalMeasurementMode.h"

using namespace System;
using namespace System::Threading;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{


			/**
			* @class DalModule
			* @brief	Exposes main functionality for the DAL module. Singleton class.
			*/
			public ref class DalModule
			{
			private:
                // constant declarations
                static const unsigned int DAL_NULLCOMMPORT_ERR      = 303;  //TODO:STUB
                static const unsigned int DAL_SIMULATION            = 10056;  //TODO:STUB

				static DalModule^ _instance = gcnew DalModule();
				DalModule();
				DalModule( DalModule^);
				DalModule^ operator= ( DalModule);

				DalStreamingMode _currentStreamingMode;

			internal:	
				//static IDalHandler^ _currentDevice;  //A pointer to the current device
				//SetMeasurementMode(DalMeasurementMode^ newMeasurmentMode); //TODO: Deepak
				
			public:
				
				/**
				* Returns the current singleton instance.
				*/
				static property DalModule^ Instance
				{
					DalModule^ get()
					{
						return DalModule::_instance;
					};
				};

				/**
				* Returns the current streaming mode.
				*/
				property DalStreamingMode StreamingMode
				{
					DalStreamingMode get()
					{
						//return this->_currentStreamingMode;
						return DalModule::_currentStreamingMode;
					};
				};

				/**
				* Returns the Nibp Cuff Data Interval.
				*/
				property unsigned short NibpCuffDataInterval
				{
					unsigned short get()
					{
						return (unsigned short)CrxSytemParameters::Instance->GetIntegerTagValue(DalSystemParameterNames::TagNibpCuffDataInterval);
					};
				};

				/**
				* Obtains the current com port settig from Configuration and sets the current strategy.
				*
				* @return	A boolean value specifying the success/failure of the operation.
				*/
				bool SetDeviceStrategy();

				///*
				//* Obtains the current com port settig from Configuration and sets the current strategy.
				//* @param[in] commPort The Comm port setting.
				//*
				//* @return	A boolean value specifying the success/failure of the operation.
				//*/
				//static bool SetDeviceStrategy(String^ commPort);

				static bool SetDeviceStrategy(String^ commPort, DalStreamingMode streamingMode);

				/**
				* Starts the data capture process from the selected device after creating a 
				* buffer according to the specified parameters.
				* @param[in]	captureTime	The capture window time
				* @param[in]	samplingRate	The number of samples per second.
				*
				* @return	A boolean value specifying the success/failure of the operation.
				*/
				bool StartMeasurement(int captureTime, int samplingRate);

				/**
				* Stops the data capture process.
				*
				* @return	A boolean value specifying the success/failure of the operation.
				*/
				bool StopMeasurement();

				/**
				* Checks the status for the current device.
				*
				* @return	A boolean value specifying the success/failure of the operation
				*/
				bool GetConnectionStatus();

				/**
				* Gets the configuration info for the specifed configruation item .
				* @param[in]	deviceConfigItem	The configuration item to be obtained
				* @param[in,out]	deviceConfigInfo	The structure to return the configuration info into.
				*
				* @return	A boolean value specifying the success/failure of the operation
				*/
				bool GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
											DalDeviceConfigUsageStruct ^deviceConfigInfo ); 

				/**
				* Returns the name of the first comm port on which the EM4 device is connected. @n
				* Should only be used for DalDeviceHandler
				*
				* @param[out]	deviceFoundPort	The port on which the device was found
				*
				* @return	A DalFindModuleResult value specifying whether the EM4 device was found or not.
				*/
				DalFindModuleResult FindModule(String ^%deviceFoundPort);

				// Returns the PWV measurement counter stored in the firmware
				bool GetPWVMeasurementCounter( unsigned short% count); //TODO:STUB

				// Sets the PWV measurement counter stored in the firmware
				bool SetPWVMeasurementCounter( unsigned short count); //TODO:STUB

				property bool measurementCounterTest; //TODO:STUB

				/**
				* Returns the name of the last error or alarm source
				* @return	A string contianing the name of the source
				*/
				String^ GetErrorAlarmSource(); 

				/**
				* Dumps the tonometer and cuff data to a backup file @n
				* Obtain the name using @c GetSavedFileName
				* @param[in]	tonometerData	Array with tonometer data values
				* @param[in]	cuffPulse	Array with cuff pulse data values
				* @param[in]	bufferSize	The size of the buffer to be dumped
				* @return	 @c true if the operation was successful
				*/
				virtual bool SaveCaptureData(array< unsigned short >^ tonometerData, array< unsigned short >^ cuffPulse, unsigned short bufferSize);

				/**
				* Dumps the tonometer and cuff data to a backup file @n
				* Obtain the name using @c GetSavedFileName
				* @param[in]	cuffPulse	Array with cuff pulse data values
				* @param[in]	bufferSize	The size of the buffer to be dumped
				* @return	 @c true if the operation was successful
				*/
				virtual bool SaveCaptureData(array< unsigned short >^ cuffPulse, unsigned short bufferSize);

				/**
				* Returns the name and filepath of the dump file saved by @c SaveNibpData
				* @param[in]	time		Array with time data values
				* @param[in]	status		Array with stats data values
				* @param[in]	errorCode	Array with errorCode values
				* @param[in]	sp			Array with sp data values
				* @param[in]	dp			Array with dp data values
				* @param[in]	map			Array with map data values
				* @param[in]	hr			Array with hr data values
				* @param[in]	bufferSize	The size of the buffer to be dumped
				*
				* @return	The filepath of the saved file
				*/

				virtual bool SaveNibpData(array< unsigned short >^ time, array< unsigned short >^ status, array< unsigned short >^ errorCode, array< unsigned short >^ sp, array< unsigned short >^ dp, array< unsigned short >^ map, array< unsigned short >^ hr, unsigned short bufferSize);
				virtual bool SaveNibpData(unsigned short time, unsigned short status, unsigned short errorCode, unsigned short sp, unsigned short dp, short map, unsigned short hr);

				/**
				* Returns the name and filepath of the dump file saved by @c SaveCaptureData
				* @return	The filepath of the saved file
				* @see	SaveCaptureData
				*/
				String^ GetSavedFilePath();

				/**
				* Checks if the device is connected on the same port as mentioned in Config
				* @return	@c true if the device is connected on the same port
				*/
				bool CheckIfDeviceIsConnected();

				/**
				*  Sets the pressure value of the specified board.
				*
				* @param[in]	newPressure	The new pressure value to be set
				* @param[in]	cuffBoard	The board for which the pressure should be set
				*
				* @return	A boolean value indicating the success/failure of the poration
				*/
				bool SetPressure(unsigned int newPressure, EM4CuffBoard cuffBoard);

				/**
				* Sets the EM4 device to Idle mode.
				*
				* @return	A boolean value indicating success/failue.
				*/
				bool SetIdleMode(); 

				/**
				* Gets the last callibration date from EM4.
				*
				* @return	The date when the system was last calibrated.
				*/
				DateTime GetLastCalibrationDate();

				/**
				* Sets the current streaming mode
				*
				* @param[in]	newMode	The new mode of operation
				*/
				void SetStreamingMode(DalStreamingMode newMode);

				
				bool IsCuffDeflated(); 
				
				// TS stub
				void SetDeviceNull();

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