#include "stdafx.h"
#include "DalSimulationHandler.h"
#include "DalEventContainer.h"
#include "DalSimulationFile.h"

using namespace System;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;


namespace AtCor{
	namespace Scor{
		namespace DataAccess{

			/**
			* Constructor for DalSimulationHandler class
			*/
			DalSimulationHandler::DalSimulationHandler()
			{
				//Make both pointers null.
				_simulationFile1 = nullptr;
				_simulationFile2 = nullptr;

                try
                {
                    // Read simulation file name from configuration
                    //obtain the setting from config manager.
			        CrxConfigManager ^configMgr = CrxConfigManager::Instance;
                    configMgr->GetPwvUserSettings();

                    // construct the simulation file path, based on the file name selected
                    // by user in "system - settings - PWV Settings - simulation type"
                    String^ tempFilePath = ".\\simulation\\pwv\\";
                    String^ tempFileExt = ".dat";
                    _simulationFile1 = gcnew DalSimulationFile(tempFilePath + configMgr->PwvSettings->SimulationType + tempFileExt);
                }
                catch(CrxException^ exErr)
                {
                    //rethrow the exception
                    throw gcnew DalException(exErr->ErrorCode, exErr->ErrorString, exErr->ExceptionObject);
                }
                
                
			}

			void DalSimulationHandler::OnTimerGetValuesAndRaiseEvents(Object^ sender, ElapsedEventArgs^ args)
			{
				//variables to hold the tonometer and cuff pulse readings
				static signed int tonoData, cuffPulseData;
				
				//get the next set of values from the simulation file.
				_simulationFile1->GetNextValues(&tonoData, &cuffPulseData);
				
				//raise the tonometer event
				DalEventContainer::Instance->OnDalTonometerDataEvent(sender, gcnew DalTonometerDataEventArgs(tonoData));
				//raise the cuff event
				DalEventContainer::Instance->OnDalCuffPulseEvent(sender, gcnew DalCuffPulseEventArgs(cuffPulseData));
			}

			void DalSimulationHandler::StartCapture()
			{
				//move file to start in case it isn't alreay at start.
				_simulationFile1->ResetFileStreamPosition();

				//The interval should come from a global value
				//initialize a new timer object
				captureTimer = gcnew Timers::Timer(DalConstants::SimulationTimerInterval);
				
				//specify the event handler to handle timer events
				captureTimer->Elapsed += gcnew ElapsedEventHandler(&DalSimulationHandler::OnTimerGetValuesAndRaiseEvents); 
				
				//Start the timer.
				captureTimer->Enabled = true;

			}

			void DalSimulationHandler::StopCapture()
			{
				//Stop the capture timer
				captureTimer->Enabled = false;

				//reset the filestrea position
				_simulationFile1->ResetFileStreamPosition();

			}

			/**
			* Returns the current configuration status. @n
			* For a simulation device this is always @c true.
			*/
			bool DalSimulationHandler::GetConnectionStatus()
			{
				//This is a dummy method. So we will return true to signify that the device is connected.
				return true;
			}

			bool DalSimulationHandler::GetConfigurationInfo (DalDeviceConfigUsageEnum deviceConfigItem, 
											  DalDeviceConfigUsageStruct ^deviceConfigInfo )
			{
				//clear all variables
				deviceConfigInfo->ModuleConfigId = 0;
				deviceConfigInfo->ModuleMainFWVersion = "";
				deviceConfigInfo->ModuleSerialNumber = "";
				deviceConfigInfo->ModuleType = "";

				switch (deviceConfigItem)
				{
					case ModuleCalibrationDate:
						//set the calliberation date as today's date. Since this is a simulation it doesnt matter.
						deviceConfigInfo->ModuleCalibrationDate= System::DateTime::Today;
						break;
					case ModuleConfigDate:
						//set to today's date.
						deviceConfigInfo->ModuleConfigDate= System::DateTime::Today;
						break;
					case ModuleConfigId:
						deviceConfigInfo->ModuleConfigId = 123; //dummy value
						break;
					case ModuleMainFirmwareVersion:
						deviceConfigInfo->ModuleMainFWVersion = L"Sim - 0.1"; //dummy value for sim device.
						break;
					case ModuleSerialNumber:
						deviceConfigInfo->ModuleSerialNumber = L"Sim - 1234567890"; //dummy vale
						break;
					case ModuleType:
						//lets the  requestor know which device it is.
						deviceConfigInfo->ModuleType = L"Simulation";
						break;
				}

				return true;
			}
		
		}
	}
}

