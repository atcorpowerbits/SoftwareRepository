/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalPwvSimulationHandler.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalPwvSimulationHandler class.
*/

#pragma once

#include "stdafx.h"
#include "DalSimulationHandler.h"
#include "DalPwvSimulationHandler.h"
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
			DalPwvSimulationHandler::DalPwvSimulationHandler()
			{
				//Initialize all valriables to appropriate values
				//_currentAlarmStatusFlag = 0; 
				//_currentCuffStatusFlag = 0;
				//_currentAlarmStatusFlag = 0;
				//_currentStatusFlag = 0;

				//dataBufferObj = DalDataBuffer::Instance;
			}

			void DalPwvSimulationHandler::CloseFiles()
			{
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
				dataBufferObj = DalDataBuffer::Instance;
			}
			DalPwvSimulationHandler::~DalPwvSimulationHandler()
			{
				/*if (_tonometerSimulationFile != nullptr)
				{
					_tonometerSimulationFile->CloseFile();
					_tonometerSimulationFile = nullptr;
				}

				if (_cuffTimerSimulationFile != nullptr)
				{
					_cuffTimerSimulationFile->CloseFile();
					_cuffTimerSimulationFile = nullptr;
				}*/
			}
			void DalPwvSimulationHandler::OnTimerReadMultipleEvents(Object^ sender, ElapsedEventArgs^ args)
			{
				args; //Dummy statement to get rid of C4100 warning

				try
				{
					//using parametrized threadstart to pass parameter
					Thread^ simulationWriterThread = gcnew Thread(gcnew ParameterizedThreadStart(DalPwvSimulationHandler::ReadMultipleEventsInLoop)); 
					simulationWriterThread->Start(sender);
				}
				catch(ScorException^)
				{
					throw;
				}
				
			}

			//new method to to read data in a loop 
			void DalPwvSimulationHandler::ReadMultipleEventsInLoop(Object^ sender)
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
						//CrxLogger::Instance->Write("DalPwvSimulationHandler::ReadMultipleEventsInLoop forloop  start cuffInUse:" + cuffInUse.ToString() + "locCountdownTimer: " + locCountdownTimer); 
						//if (locCountdownTimer <=0)  //Changed by TS
						if (locCountdownTimer <=0 && cuffInUse) 
						{
							//get next set of values from the cufff simulation file
							_cuffTimerSimulationFile->GetNextValues(&locCountdownTimer, &cuffAbsolutePressure, &statusBytes, &locEASourceFlag);
							////CrxLogger::Instance->Write("locCountdownTimer" + locCountdownTimer + ", cuffAbsolutePressure:" + cuffAbsolutePressure + ", statusBytes" + statusBytes.ToString("X2) + " ,locEASourceFlag" + locEASourceFlag.ToString("X2));

							//store the Error/alarm SOURCE in the global variable. If an event is raised we need to retrive the stored value to find the source.
							_currentEASourceFlag = locEASourceFlag;

							//Added by TS Stub
							if (DalCuffStateFlags::CUFF_STATE_DEFLATED == (DalCuffStateFlags)(statusBytes & 0x7))
							{
								//CrxLogger::Instance->Write("DalPwvSimulationHandler::ReadMultipleEventsInLoop  cuffInUse set to false and locCountdownTimer set to zero");
								// Finished cuff until another inflation
								cuffInUse = false;
								locCountdownTimer = 0;
							}

							//split the status flag into various components and validate them.
							ProcessStatusFlag(statusBytes);
						}

						//check between the modes
						_tonometerSimulationFile->GetNextValues(&tonoData, &cuffPulseData);
						CrxLogger::Instance->Write("tonoData" + tonoData + ", cuffPulseData:" + cuffPulseData );


											

						if (DalCuffStateFlags::CUFF_STATE_INFLATED == currentCuffState)
						{
							//value is in miliseconds. The device returns it as seconds hece divide by thousand.
							tempPWVDataVar.countdownTimer = (short)locCountdownTimer/1000;
						}
						else
						{
							tempPWVDataVar.countdownTimer = 0;
						}

						//CrxLogger::Instance->Write("DalPwvSimulationHandler::ReadMultipleEventsInLoop cuffinUse: " + cuffInUse.ToString());
						//added by TS Stub
						if (cuffInUse)
						{
							//CrxLogger::Instance->Write("DalPwvSimulationHandler::ReadMultipleEventsInLoop cuffinUse: " + cuffInUse.ToString()+ "decremeting locCountdownTimer" );
						
							//decrement the cuff timer as long as it's used
							locCountdownTimer -= DalConstants::DataSamplingInterval;
						}

						tempPWVDataVar.cuffPressure = (short)cuffAbsolutePressure;
						tempPWVDataVar.tonometerData = (short)tonoData;
						tempPWVDataVar.cuffPulseData = (short)cuffPulseData;
						////CrxLogger::Instance->Write(" Tono : " + tonoData + "cuffPulse: " + cuffPulseData + " cuffAbsolutePressure: " + cuffAbsolutePressure + " tempPWVDataVar.countdownTimer : " + tempPWVDataVar.countdownTimer );
						
						//write data to buffer
						dataBufferObj->WriteDataToBuffer(tempPWVDataVar);

						//moved up by TS stub
						////decrement the timer after every write operation
						//locCountdownTimer -= DalConstants::DataSamplingInterval;
					}
				}
				catch(ScorException^ scorExObj)
				{
					CrxLogger::Instance->Write(" Simulation ScorException raised:" + scorExObj->ErrorMessageKey );
					
					//throw; //dont throw an excpetion from a thread . convert it to an event

					DalStatusHandler::RaiseEventForException(DalErrorAlarmStatusFlag::ThreadException, scorExObj);
				}
				catch(Exception^ excepObj)
				{
					CrxLogger::Instance->Write(" Simulation Exception raised:" + excepObj->Message);
					
					//throw gcnew ScorException(excepObj);//dont throw an excpetion from a thread . convert it to an event

					DalStatusHandler::RaiseEventForException(DalErrorAlarmStatusFlag::ThreadException, gcnew ScorException(excepObj));
				}
			}

			bool DalPwvSimulationHandler::GetFileNameFromConfgAndOpen()
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
					_cuffTimerSimulationFile = gcnew DalSimulationFile(CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstCufftimerFilePath));
							
					//get the streaming mode and open the file for the current mode
					configMgr->GetPwvUserSettings();

					// construct the simulation file path, based on the file name selected
					// by user in "system - settings - PWV Settings - simulation type"
               		tempFilePath =CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstSimFolderPath);
               		_tonometerSimulationFile = gcnew DalSimulationFile(tempFilePath + configMgr->PwvSettings->SimulationType + tempFileExt);
					
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
			bool DalPwvSimulationHandler::StartCapture(int captureTime, int samplingRate)
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
					
					if (!(GetFileNameFromConfgAndOpen()))
					{
						return false;
					}
					
					//move file to start in case it isn't alreay at start.
					_tonometerSimulationFile->ResetFileStreamPosition();
					_cuffTimerSimulationFile->ResetFileStreamPosition();

					//PWVS-1 create a new timer to tick every 1 ms 
					captureTimer = gcnew Timers::Timer(DalConstants::SimulationWriteTimerInterval);
					
					//specify the event handler to handle timer events
					captureTimer->Elapsed += gcnew ElapsedEventHandler(&DalPwvSimulationHandler::OnTimerReadMultipleEvents); 
					
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


		}
	}
}