/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalSimulationHandler.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalSimulationHandler class
*/

#include "stdafx.h"
#include "DalSimulationHandler.h"
#include "DalEventContainer.h"
#include "DalSimulationFile.h"
#include "DalDataBuffer.h"
#include "DalModule.h"
#include "DalCommon.h"


using namespace System;
using namespace System::Threading;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;

namespace AtCor{
	namespace Scor{
		namespace DataAccess{

			/**
			* Constructor for DalSimulationHandler class
			*/
			DalSimulationHandler::DalSimulationHandler()
			{
				//Initialize all valriables to appropriate values
				_currentAlarmStatusFlag = 0; 
				_currentCuffStatusFlag = 0;
				_currentAlarmStatusFlag = 0;
				_currentStatusFlag = 0;

				dataBufferObj = DalDataBuffer::Instance;
			}

			bool DalSimulationHandler::GetFileNameFromConfgAndOpen()
			{
				bool result = false;
				String^ tempFilePath;
				String^ tempFileExt;

                try
                {
					//First check if the files are open
					//if yes then close them.
					if (_tonometerSimulationFile != nullptr)
					{
						_tonometerSimulationFile->CloseFile();
						_tonometerSimulationFile = nullptr;
					}

					if (_cuffTimerSimulationFile != nullptr)
					{
						_cuffTimerSimulationFile->CloseFile();
						_cuffTimerSimulationFile = nullptr;
					}

                    // Read simulation file name from configuration
                    //obtain the setting from config manager.
			        CrxConfigManager ^configMgr = CrxConfigManager::Instance;

					//Get the file extension
					tempFileExt = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstDatFileExtn);

					//pick the cuff timer sim file from another directory
					//_cuffTimerSimulationFile = gcnew DalSimulationFile(CrxMessagingManager::Instance->GetMessage("DAL_CONST_CUFFTIMER_FILE_PATH"));
					_cuffTimerSimulationFile = gcnew DalSimulationFile(CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstCufftimerFilePath));
							
					//get the streaming mode and open the file for the current mode
					if(DalStreamingMode::Pwv == DalModule::Instance->StreamingMode)
					{
                    configMgr->GetPwvUserSettings();

                    // construct the simulation file path, based on the file name selected
                    // by user in "system - settings - PWV Settings - simulation type"
                   		tempFilePath =CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstSimFolderPath);
                    _tonometerSimulationFile = gcnew DalSimulationFile(tempFilePath + configMgr->PwvSettings->SimulationType + tempFileExt);
				
					}
					else if (DalStreamingMode::cPwa == DalModule::Instance->StreamingMode)
					{
						//get the PWa settings from config file.
						//It contains the file name 
						configMgr->GetPwaUserSettings();

						tempFilePath =CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstSimFolderPathPwa);
                   		_tonometerSimulationFile = gcnew DalSimulationFile(tempFilePath + configMgr->PwaSettings->SimulationType + tempFileExt);

					}
					else
					{
						result = false;
					}

     //               configMgr->GetPwvUserSettings();

     //               // construct the simulation file path, based on the file name selected
     //               // by user in "system - settings - PWV Settings - simulation type"
     //              	String^ tempFilePath =CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstSimFolderPath);
     //              	String^ tempFileExt = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstDatFileExtn);
     //               _tonometerSimulationFile = gcnew DalSimulationFile(tempFilePath + configMgr->PwvSettings->SimulationType + tempFileExt);
				
					////pick the cuff timer sim file from another directory
					////_cuffTimerSimulationFile = gcnew DalSimulationFile(CrxMessagingManager::Instance->GetMessage("DAL_CONST_CUFFTIMER_FILE_PATH"));
					//_cuffTimerSimulationFile = gcnew DalSimulationFile(CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstCufftimerFilePath));


					result = true;
			    }
				catch(ScorException^)
				{
					throw;
				}
                catch(Exception^ sysExObj)
                {
                    throw gcnew ScorException(sysExObj);
                }

				return result;
			}


			//New method to read n numer of element per interval
			//At present we will read 256 elements in 1 second
			void DalSimulationHandler::OnTimerReadMultipleEvents(Object^ sender, ElapsedEventArgs^ args)
			{
				args; //Dummy statement to get rid of C4100 warning

				try
				{
					//using parametrized threadstart to pass parameter
					Thread^ simulationWriterThread = gcnew Thread(gcnew ParameterizedThreadStart(DalSimulationHandler::ReadMultipleEventsInLoop)); 
					simulationWriterThread->Start(sender);
				}
				catch(ScorException^)
				{
					throw;
				}
				
			}

			//new method to to read data in a loop 
			void DalSimulationHandler::ReadMultipleEventsInLoop(Object^ sender)
			{
				sender; //Dummy statement to get rid of C4100 warning

				DalPwvDataStruct tempPWVDataVar;
			
				//variables to hold the tonometer and cuff pulse readings
				static unsigned long tonoData, cuffPulseData;
				static unsigned long cuffAbsolutePressure;
				static unsigned long locCountdownTimer = 0;
				static unsigned long statusBytes, locEASourceFlag;
				static bool currentCuffStateIsInflated = false;
				
				//Pick the number of reads from DalConstants
				int numberOfReads = DalConstants::SimulationNumberOfReadsPerInterval;

				try
				{				
					if (firstReadAfterCaptureStarted == true)
					{
						////CrxLogger::Instance->Write(" ReadMultipleEventsInLoop inside IF firstReadAfterCaptureStarted = " + firstReadAfterCaptureStarted.ToString());
						ResetAllStaticMembers();

						tonoData = cuffPulseData = cuffAbsolutePressure = locCountdownTimer = statusBytes =  0;
						currentCuffStateIsInflated = firstReadAfterCaptureStarted = false;
					}
				
					//Read n elements in a loop. 
					for (int counter = 0; counter < numberOfReads ; counter++)
					{
						if (locCountdownTimer <=0) 
						{
							//get next set of values from the cufff simulation file
							_cuffTimerSimulationFile->GetNextValues(&locCountdownTimer, &cuffAbsolutePressure, &statusBytes, &locEASourceFlag);
							////CrxLogger::Instance->Write("locCountdownTimer" + locCountdownTimer + ", cuffAbsolutePressure:" + cuffAbsolutePressure + ", statusBytes" + statusBytes.ToString("X2) + " ,locEASourceFlag" + locEASourceFlag.ToString("X2));

							//store the Error/alarm SOURCE in the global variable. If an event is raised we need to retrive the stored value to find the source.
							_currentEASourceFlag = locEASourceFlag;

							//The DalSimulationHandler::SchecStatusFlag(,) function has been 
							//replaced by the //DalStatusHandler::ProcessStatusFlag() method
							//CheckStatusFlag(statusBytes, currentCuffStateIsInflated);

							ProcessStatusFlag(statusBytes);

						}

						//check between the modes
						if(DalStreamingMode::Pwv == DalModule::Instance->StreamingMode)
						{
						//get the next set of values from the tonometer simulation file.
						_tonometerSimulationFile->GetNextValues(&tonoData, &cuffPulseData);
						}
						else if (DalStreamingMode::cPwa == DalModule::Instance->StreamingMode)
						{
							//get the next set of values from the CPWA simulation file.
							_tonometerSimulationFile->GetNextValues(&cuffPulseData);
						}

						

						if (DalCuffStateFlags::CUFF_STATE_INFLATED == currentCuffState)
						{
							//value is in miliseconds. The device returns it as seconds hece divide by thousand.
							tempPWVDataVar.countdownTimer = (short)locCountdownTimer/1000;
						}
						else
						{
							tempPWVDataVar.countdownTimer = 0;
						}
						tempPWVDataVar.cuffPressure = (short)cuffAbsolutePressure;
						tempPWVDataVar.tonometerData = (short)tonoData;
						tempPWVDataVar.cuffPulseData = (short)cuffPulseData;
						////CrxLogger::Instance->Write(" Tono : " + tonoData + "cuffPulse: " + cuffPulseData + " cuffAbsolutePressure: " + cuffAbsolutePressure + " tempPWVDataVar.countdownTimer : " + tempPWVDataVar.countdownTimer );

						//write data to buffer
						dataBufferObj->WriteDataToBuffer(tempPWVDataVar);

						//decrement the timer after every write operation
						locCountdownTimer -= DalConstants::DataSamplingInterval;
					}
				}
				catch(ScorException^)
				{
					throw;
				}
				catch(Exception^ excepObj)
				{
					/*if (InvokeRequired)
					{
						System::Windows::
					}*/
					throw gcnew ScorException(excepObj);
				}
			}

			bool DalSimulationHandler::StartCapture(int captureTime, int samplingRate)
			{
				//TODO: clear all static variables  and members before starting capture
				try
				{
					//flag this valiable to true so that we know that 
					//the capture has started fresh and it is not a re-capture
					firstReadAfterCaptureStarted = true;

					dataBufferObj = DalDataBuffer::Instance;
					//create array
					dataBufferObj->CreateBuffer(captureTime, samplingRate);
							
					//call the method which will open the simulation file specified in config.
					GetFileNameFromConfgAndOpen();
					
					//move file to start in case it isn't alreay at start.
					_tonometerSimulationFile->ResetFileStreamPosition();
					_cuffTimerSimulationFile->ResetFileStreamPosition();

					//PWVS-1 create a new timer to tick every 1 ms 
					captureTimer = gcnew Timers::Timer(DalConstants::SimulationWriteTimerInterval);
					
					//specify the event handler to handle timer events
					captureTimer->Elapsed += gcnew ElapsedEventHandler(&DalSimulationHandler::OnTimerReadMultipleEvents); 
					
					//Start the timer.
					captureTimer->Enabled = true;

					return true;
				}
				catch(ScorException^)
				{
					throw;
				}
                catch(Exception^ sysExObj)
                {
                    throw gcnew ScorException(sysExObj);
                }
			}

			bool DalSimulationHandler::StopCapture()
			{
				try
				{
					//Stop the capture timer
					captureTimer->Enabled = false;

					//reset the filestrea position
					_tonometerSimulationFile->ResetFileStreamPosition();
					_cuffTimerSimulationFile->ResetFileStreamPosition();
					return true;
				}
				catch(ScorException^)
				{
					//see note below:
					//throw;
					return false;
				}
                catch(Exception^ )
                {
					//this Exception object is meant to be rethrown. 
					//However if we attempt to start capture using a 
					//null sim file then all the objects are not created. 
					//This causes some problem in the GUI which is not easy 
					//to solve and prevents the user from returning  from 
					//the capture tab using "cancel" button. 
					//So we have temporarily commented out the re-throw part. 
					//It will be added back later. 
                    //throw gcnew ScorException(sysExObj);
					return false;
                }
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
											  DalDeviceConfigUsageStruct ^%deviceConfigInfo )
			{
				switch (deviceConfigItem)
				{
				case DalDeviceConfigUsageEnum::ModuleCalibrationDate:
						//set the calliberation date as today's date. Since this is a simulation it doesnt matter.
						deviceConfigInfo->ModuleCalibrationDate= System::DateTime::Today;
						break;
					case DalDeviceConfigUsageEnum::ModuleConfigDate:
						//set to today's date.
						deviceConfigInfo->ModuleConfigDate= System::DateTime::Today;
						break;
					case DalDeviceConfigUsageEnum::ModuleConfigId:
						deviceConfigInfo->ModuleConfigId = 123; //dummy value
						break;
					case DalDeviceConfigUsageEnum::ModuleMainFirmwareVersion:
						//deviceConfigInfo->ModuleMainFWVersion = CrxMessagingManager::Instance->GetMessage("DAL_CONST_GCI_FIRMWARE_VERSION"); //dummy value for sim device.
						deviceConfigInfo->ModuleMainFWVersion = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstGciFirmwareVersion); //dummy value for sim device.
						break;
					case DalDeviceConfigUsageEnum::ModuleSerialNumber:
						//deviceConfigInfo->ModuleSerialNumber =  CrxMessagingManager::Instance->GetMessage("DAL_CONST_GCI_SERIAL_NUMBER"); //dummy vale
						deviceConfigInfo->ModuleSerialNumber =  CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstGciSerialNumber); //dummy vale
						break;
					case DalDeviceConfigUsageEnum::ModuleType:
						//lets the  requestor know which device it is.
						deviceConfigInfo->ModuleType = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::ComportSimulation);
						break;
					default:
						break;
				}

				return true;
			}


			bool DalSimulationHandler::CheckIfDeviceIsConnected()
			{
				return true;
				//simulation device will alawys be connected.
			}

			bool DalSimulationHandler::SetPressure(unsigned int newPressure, EM4CuffBoard cuffBoard)
			{
				newPressure; //Dummy statement to get rid of C4100 warning
				cuffBoard ; //Dummy statement to get rid of C4100 warning


				//This should always return true 
				//to pretend that the pressure has been set/
				//The actual value will be deciced based on the simulation file.
				return true; 
			}


			bool DalSimulationHandler::SetIdleMode()
			{
				//simulation mode will always retur true .
				return true;
			}


		}//END DataAccess namespace
	}
}

