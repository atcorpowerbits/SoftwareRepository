/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalDeviceHandler.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalDeviceHandler class code
*/

#include "stdafx.h"
#include "DalDeviceHandler.h"

namespace AtCor{
	namespace Scor{
		namespace DataAccess{

			DalDeviceHandler::DalDeviceHandler()
			{
				//Empty constructor implements singleton pattern.
			}

			DalDeviceHandler::DalDeviceHandler(String ^commPort)
			{
				//inititalize the comm coprt using the provided parameter.
				_commPort = commPort;
			}

			//void DalDeviceHandler::StartCapture() //replaced by parametrized method
			void DalDeviceHandler::StartCapture(int captureTime, int samplingRate)
			{
				//Stub method, needs to be implemented
			}

			void DalDeviceHandler::StopCapture()
			{
				//Stub method, needs to be implemented
			}

			bool DalDeviceHandler::GetConnectionStatus()
			{
				//Stub method, needs to be implemented
				//will return false to show that it is disconnected until the functionality is implemented.
				return false;
			}

			bool DalDeviceHandler::GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
											  DalDeviceConfigUsageStruct ^deviceConfigInfo )
			{
				//Clear existing configuration data
				deviceConfigInfo->ModuleConfigId = 0;
				deviceConfigInfo->ModuleMainFWVersion = "";
				deviceConfigInfo->ModuleSerialNumber = "";
				deviceConfigInfo->ModuleType = "";

				//temporarily assign the same values as the EM4 simulation device until the acutla code is written.
				switch (deviceConfigItem)
				{
					case ModuleCalibrationDate:
						//Dummy value: returns todays date
						deviceConfigInfo->ModuleConfigDate= System::DateTime::Today;
						break;
					case ModuleConfigDate:
						//Dummy value: returns todays date
						deviceConfigInfo->ModuleConfigDate= System::DateTime::Today;
						break;
					case ModuleConfigId:
						deviceConfigInfo->ModuleConfigId = 123; //Dummy value . will be retreived from the EM4 device
						break;
					case ModuleMainFirmwareVersion:
						//Dummy value
						deviceConfigInfo->ModuleMainFWVersion = L"0.1 (stub)";
						break;
					case ModuleSerialNumber:
						//Dummy value
						deviceConfigInfo->ModuleSerialNumber = L"1234567890 (stub)";
						break;
					case ModuleType:
						//Dummy value
						deviceConfigInfo->ModuleType = L"EM4 Device (stub)";
						break;
				}

				//return false until this functionality is implemented
				return false;
			}

			
		}
	}
}