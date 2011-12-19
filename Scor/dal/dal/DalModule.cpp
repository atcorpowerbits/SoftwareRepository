/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalModule.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Code file for DalModule class
*/

#include "stdafx.h"
#include "DalModule.h"
#include "DalActiveDevice.h"
//#include "DalMeasurementMode.h"

using namespace System::ComponentModel;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;

using namespace AtCor::Scor::CrossCutting::Messaging;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			DalModule::DalModule()
			{
				
				// For testing only
				measurementCounterTest = true; //TODO:STUB
				
				//Deliberately call the DalActiveDevice Instance to force the constructor call
				//this will ensure that the CommsPort event handler is registered
				DalActiveDevice::Instance;
				
			}

			DalModule::DalModule(DalModule ^)
			{
				//overloaded copy constructor.
				//Does nothing
			}

			bool DalModule::SetDeviceStrategy()
			{
				return DalActiveDevice::Instance->SetDeviceStrategy();
			}


	                
			bool DalModule::SetDeviceStrategy(String ^commPort,DalStreamingMode streamingMode)
			{
				return DalActiveDevice::Instance->SetDeviceStrategy(commPort, streamingMode);
			}


			DalModule^ DalModule::operator =(DalModule)
			{
				//overloaded assignment operator.
				//used to implement singleton.
				return this;
			}


			bool DalModule::StartMeasurement(int captureTime, int samplingRate)
			{
				//return _currentMeasurementMode->StartMeasurement(captureTime, samplingRate);
				return DalActiveDevice::CurrentDevice->StartCapture(captureTime, samplingRate);
				//return DalMeasurementMode:: StartMeasurement(captureTime, samplingRate);

				//if (_currentDevice)
				//{
				//	//call the active device method
				//	//return _currentDevice->StartCapture(captureTime, samplingRate);
				//	return DalActiveDevice::CurrentDevice->StartCapture(captureTime, samplingRate);
				//}

				//return false;
			}

			bool DalModule::StopMeasurement()
			{
				
				//if (_currentDevice)
				//{
				//	//call the active device method
				//	return _currentDevice->StopCapture();
				//}

				//return false;
				return DalActiveDevice::CurrentDevice->StopCapture();
			}

			bool DalModule::GetConnectionStatus()
			{
				//if (_currentDevice)
				//{
				//	//call the active device method
				//	return _currentDevice->GetConnectionStatus();
				//}
				//return false;

				return DalActiveDevice::CurrentDevice->GetConnectionStatus();
			}

			bool DalModule::GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
											DalDeviceConfigUsageStruct ^deviceConfigInfo )
			{
				//if (_currentDevice)
				//{
				//	//call the active device method
				//	return _currentDevice->GetConfigurationInfo(deviceConfigItem, deviceConfigInfo);
				//}
				//return false;

				return DalActiveDevice::CurrentDevice->GetConfigurationInfo(deviceConfigItem, deviceConfigInfo);
			}

			DalFindModuleResult DalModule::FindModule(String ^%deviceFoundPort)
			{
				return DalActiveDevice::Instance->FindModule(deviceFoundPort);
				
			}
				


			String^ DalModule::GetErrorAlarmSource()
			{
				//if (_currentDevice)
				//{
				//	//call the active device method
				//	return _currentDevice->GetAlarmSource();
				//}
				//return nullptr;
				DalAlarmSource translatedAlarmSource;

				return DalActiveDevice::CurrentDevice->GetAlarmSource(translatedAlarmSource);

			}

				/**
			GetPWVMeasurementCounter()

			DESCRIPTION

				Returns the PWV measurement counter stored in the firmware.

			INPUT

				None.

			OUTPUT

				count.

			RETURN

				boolean success or not.
			*/
			bool DalModule::GetPWVMeasurementCounter( unsigned short% count)
			{
				// If the module is not connected return false, otherwise retrieve the count -
				// value and return true

				count = 0;

				return measurementCounterTest;
			}

			/**
			SetPWVMeasurementCounter()

			DESCRIPTION

				Sets the PWV measurement counter stored in the firmware.

			INPUT

				count.

			OUTPUT

				None.

			RETURN

				boolean success or not.
			*/
			bool DalModule::SetPWVMeasurementCounter( unsigned short count)
			{
				count; //Dummy statement to get rid of C4100 warning

				// If the module is not connected return false, otherwise set the count -
				// value and return true

				return measurementCounterTest;
			}

			bool DalModule::SaveCaptureData(array< unsigned short >^ tonometerData, array< unsigned short >^ cuffPulse, unsigned short bufferSize)
			{
				//return _currentDevice->SaveCaptureData(tonometerData, cuffPulse, bufferSize);

				return DalActiveDevice::CurrentDevice->SaveCaptureData(tonometerData, cuffPulse, bufferSize);
			}

			bool DalModule::SaveCaptureData(array< unsigned short >^ cuffPulse, unsigned short bufferSize)
			{
				return DalActiveDevice::CurrentDevice->SaveCaptureData(cuffPulse, bufferSize);
			}

			bool DalModule::SaveNibpData(array< unsigned short >^ time, array< unsigned short >^ status, array< unsigned short >^ errorCode, array< unsigned short >^ sp, array< unsigned short >^ dp, array< unsigned short >^ map, array< unsigned short >^ hr, unsigned short bufferSize)
			{
				return DalActiveDevice::CurrentDevice->SaveNibpData(time, status, errorCode, sp, dp, map, hr, bufferSize);
			}

			bool DalModule::SaveNibpData(unsigned short time, unsigned short status, unsigned short errorCode, unsigned short sp, unsigned short dp, short map, unsigned short hr)
			{
				return DalActiveDevice::CurrentDevice->SaveNibpData(time, status, errorCode, sp, dp, map, hr);
			}

			String^ DalModule::GetSavedFilePath()
			{
				//return _currentDevice->GetSavedFileName();
				return DalActiveDevice::CurrentDevice->GetSavedFileName();
			}



			//bool DalModule::SearchAllPortsforDevice(String ^%foundPortName, String ^excludePort )
			//{
				
			//	//find all open ports
			//	array<String^>^ listOfSerialPorts = nullptr;
			//	
			//	try
			//	{
			//		listOfSerialPorts = SerialPort::GetPortNames();
			//	}
			//	catch(Win32Exception^ winExcepObj)
			//	{
			//		throw gcnew ScorException(winExcepObj);
			//	}

			//	for each (String ^ portName in listOfSerialPorts)
			//	{
			//		//check if this port is excluded
			//		if ((portName == excludePort ) && (excludePort != nullptr) )
			//		{
			//			continue;
			//		}
			//		////CrxLogger::Instance->Write("Ports Listed: " + portName, ErrorSeverity::Debug);
			//		if (DalDeviceHandler::Instance->CheckIfDeviceIsConnected(portName)) 
			//		{

			//			//found the port with the device
			//			//return the parameter and value;
			//			foundPortName = portName;
			//			return true; 
			//		}
			//	}

			//	return false; 
			//}

			bool DalModule::CheckIfDeviceIsConnected()
			{
				//if (_currentDevice)
				//{
				//	//call the active device method
				//	return _currentDevice->CheckIfDeviceIsConnected();
				//}
				//else
				//{
				//	return false;
				//}

				return DalActiveDevice::CurrentDevice->CheckIfDeviceIsConnected();
			}

			bool DalModule::SetPressure(unsigned int newPressure, EM4CuffBoard cuffBoard)
			{
				/*if (_currentDevice)
				{
					return _currentDevice->SetPressure(newPressure, cuffBoard);
				}
				else
				{
					return false;
				}*/

				return DalActiveDevice::CurrentDevice->SetPressure(newPressure, cuffBoard);
				//return _currentMeasurementMode->SetPressure(newPressure, cuffBoard);
			}

			bool DalModule::SetIdleMode()
			{
				////call the actual method
				//if (_currentDevice)
				//{
				//	return _currentDevice->SetIdleMode();
				//}
				//else
				//{
				//	return false;
				//}

				return DalActiveDevice::CurrentDevice->SetIdleMode();
	
			}

			//Fxcop reccommends that reference parameters should not be used
			//bool DalModule::IsAnnualCalibrationDue(System::DateTime ^%lastCalibrationDate)
			//{
			//	//Stub method. will be replaced by actual code later
			//	lastCalibrationDate = gcnew DateTime(2010, 5, 9);

			//	return true;

			//}

			DateTime DalModule::GetLastCalibrationDate()
			{
				//Stub method. will be replaced by actual code later
				return DateTime::Today;
			}

			void DalModule::SetStreamingMode(DalStreamingMode newMode)
			{
				//Set the current mode
				_currentStreamingMode = newMode;
				SetDeviceStrategy();
			}


			bool DalModule::IsCuffDeflated()
			{
				return DalActiveDevice::CurrentDevice->IsCuffDeflated();
			}



			//TS Stub
			// Unit testing purpose only to force StartCapture to fail when 
			void DalModule::SetDeviceNull()
			{
				//_currentDevice = nullptr;
				DalActiveDevice::Instance->SetDeviceNull();
			}


			// Equivalent to NIBP CONNECT, START_BP & <O>
			bool DalModule::StartBP(DalNIBPMode nibpMode)
			{
				return DalActiveDevice::CurrentDevice->StartBP(nibpMode);
			}

			// Equivalent to NIBP DISCONNECT
			bool DalModule::FinishBP()
			{
				return DalActiveDevice::CurrentDevice->FinishBP();
			}

			// Equivalent to NIBP Abort_BP & <A>
			bool DalModule::AbortBP()
			{
				return DalActiveDevice::CurrentDevice->AbortBP();
			}


			////TS Stub
			//// Equivalent to SET_INITIAL_INFLATE & <O> <K>
			//bool DalModule::SetBPInitialInflate(unsigned short initialPressure)
			//{
			//	initialPressure;

			//	return DalActiveDevice::CurrentDevice
			//	return true;
			//}

			//TS Stub
			// Start NIBP using initial inflate pressure
			bool DalModule::StartBP(DalNIBPMode nibpMode, unsigned short initialPressure)
			{
				return DalActiveDevice::CurrentDevice->StartBP(nibpMode, initialPressure);
			}

		}//end namespaces
	}
}