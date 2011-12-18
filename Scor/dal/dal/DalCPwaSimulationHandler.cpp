/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCPwaSimulationHandler.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalPwvSimulationHandler class.
*/

#pragma once

#include "stdafx.h"
#include "DalModule.h"
#include "DalCommon.h"
#include "DalDataBuffer.h"
#include "DalEventContainer.h"
#include "DalSimulationFile.h"
#include "DalSimulationHandler.h"
#include "DalCPwaSimulationHandler.h"
#include "DalNibpSimulationHandler.h"

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
			DalCPwaSimulationHandler::DalCPwaSimulationHandler()
			{
				//Initialize all valriables to appropriate values
				//_currentAlarmStatusFlag = 0; 
				//_currentCuffStatusFlag = 0;
				//_currentAlarmStatusFlag = 0;
				//_currentStatusFlag = 0;

				nibpBufferObj = DalDataBuffer::Instance;
				_nibp = DalNibpSimulationHandler::Instance;
			}

			void DalCPwaSimulationHandler::CloseFiles()
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

			DalCPwaSimulationHandler::~DalCPwaSimulationHandler()
			{
				//if (_cuffTimerSimulationFile != nullptr)
				//{
				//	_cuffTimerSimulationFile->CloseFile();
				//	_cuffTimerSimulationFile = nullptr;
				//}
			}

			void DalCPwaSimulationHandler::OnTimerReadMultipleEvents(Object^ sender, ElapsedEventArgs^ args)
			{
				args; //Dummy statement to get rid of C4100 warning

				try
				{
					//using parametrized threadstart to pass parameter
					Thread^ simulationWriterThread = gcnew Thread(gcnew ParameterizedThreadStart(DalCPwaSimulationHandler::ReadMultipleEventsInLoop)); 
					simulationWriterThread->Start(sender);
				}
				catch(ScorException^)
				{
					throw;
				}
				
			}

			//new method to to read data in a loop 
			void DalCPwaSimulationHandler::ReadMultipleEventsInLoop(Object^)
			{
				DalPwvDataStruct tempPWVDataVar;
			
				//variables to hold the tonometer and cuff pulse readings
				static unsigned short tonoData, cuffPulseData;
				static unsigned short cuffAbsolutePressure;
				static unsigned long locCountdownTimer = 0;
				static unsigned short statusBytes, locEASourceFlag;
				static bool currentCuffStateIsInflated = false;
				
				//Pick the number of reads from DalConstants
				//int numberOfReads = DalConstants::SimulationNumberOfReadsPerInterval;

				try
				{				
					if (firstReadAfterCaptureStarted == true)
					{
						//CrxLogger::Instance->Write(" ReadMultipleEventsInLoop inside IF firstReadAfterCaptureStarted = " + firstReadAfterCaptureStarted.ToString(), ErrorSeverity::Debug);
						ResetAllStaticMembers();

						tonoData = cuffPulseData = cuffAbsolutePressure = statusBytes =  0;
						locCountdownTimer = 0;
						currentCuffStateIsInflated = firstReadAfterCaptureStarted = false;
						//CrxLogger::Instance->Write(" ReadMultipleEventsInLoop inside IInd = " + firstReadAfterCaptureStarted.ToString(), ErrorSeverity::Debug);
					}
				
					//Read n elements in a loop. 
					for (int counter = 0; counter < DalConstants::SimulationNumberOfReadsPerInterval ; counter++)
					{
						//CrxLogger::Instance->Write(" for loop = " + counter.ToString() + " " +numberOfReads.ToString() + " " + locCountdownTimer.ToString(), ErrorSeverity::Debug);
						//CrxLogger::Instance->Write(" cuffInUse = " + cuffInUse.ToString(), ErrorSeverity::Debug);
						//if (locCountdownTimer <=0)  //Changed by TS
						if (locCountdownTimer <=0 && cuffInUse) 
						{
							//CrxLogger::Instance->Write(" locCountdownTimer <=0 && cuffInUse = " + locCountdownTimer.ToString() +" " + cuffInUse.ToString(), ErrorSeverity::Debug);

							//get next set of values from the cufff simulation file
							_cuffTimerSimulationFile->GetNextValues(&locCountdownTimer, &cuffAbsolutePressure, &statusBytes, &locEASourceFlag);
							//CrxLogger::Instance->Write("locCountdownTimer" + locCountdownTimer + ", cuffAbsolutePressure:" + cuffAbsolutePressure + ", statusBytes" + statusBytes.ToString("X2") + " ,locEASourceFlag" + locEASourceFlag.ToString("X2"), ErrorSeverity::Debug);

							//store the Error/alarm SOURCE in the global variable. If an event is raised we need to retrive the stored value to find the source.
							_currentEASourceFlag = locEASourceFlag;

							//Added by TS Stub
							if (DalCuffStatusBitMask::CUFF_DEFLATED_STATUS_BITS == (DalCuffStatusBitMask)(statusBytes & 0x0700))
							{
								// Finished cuff until another inflation
								cuffInUse = false;
								locCountdownTimer = 0;
							}

							//The DalSimulationHandler::SchecStatusFlag(,) function has been 
							//replaced by the //DalStatusHandler::ProcessStatusFlag() method
							//CheckStatusFlag(statusBytes, currentCuffStateIsInflated);

							ProcessStatusFlag(statusBytes);

						}

						_tonometerSimulationFile->GetNextValues(&cuffPulseData);

						SetCountDownTimer(currentCuffState, locCountdownTimer, %tempPWVDataVar);
						//if (DalCuffStateFlags::CUFF_STATE_INFLATED == currentCuffState)
						//{
						//	//value is in miliseconds. The device returns it as seconds hece divide by thousand.
						//	tempPWVDataVar.countdownTimer = (short)locCountdownTimer/1000;
						//}
						//else
						//{
						//	tempPWVDataVar.countdownTimer = 0;
						//}

						//added by TS Stub
						if (cuffInUse)
						{
							//decrement the cuff timer as long as it's used
							locCountdownTimer -= DalConstants::DataSamplingInterval;
							//CrxLogger::Instance->Write(" locCountdownTimer = " + locCountdownTimer, ErrorSeverity::Debug);
							//CrxLogger::Instance->Write(" DalConstants::DataSamplingInterval = " + DalConstants::DataSamplingInterval, ErrorSeverity::Debug);
						}

						tempPWVDataVar.cuffPressure = (short)cuffAbsolutePressure;
						//tempPWVDataVar.tonometerData = (short)tonoData;
						tempPWVDataVar.cuffPulseData = (short)cuffPulseData;
						////CrxLogger::Instance->Write(" Tono : " + tonoData + "cuffPulse: " + cuffPulseData + " cuffAbsolutePressure: " + cuffAbsolutePressure + " tempPWVDataVar.countdownTimer : " + tempPWVDataVar.countdownTimer , ErrorSeverity::Debug);
						
						//write data to buffer
						dataBufferObj->WriteDataToBuffer(tempPWVDataVar);

						//moved up by TS stub
						////decrement the timer after every write operation
						//locCountdownTimer -= DalConstants::DataSamplingInterval;
					}
				}
				catch(ScorException^ scorExObj)
				{
					CrxLogger::Instance->Write("DAL:Deepak>>> Raising event for ScorException: " + scorExObj->ErrorMessageKey + scorExObj->StackTrace, ErrorSeverity::Debug);
					DalStatusHandler::RaiseEventForException(DalErrorAlarmStatusFlag::ThreadException, scorExObj);
				}
				catch(Exception^ excepObj)
				{
					CrxLogger::Instance->Write("DAL:Deepak>>> Raising event for exception: " + excepObj->Data + excepObj->StackTrace, ErrorSeverity::Debug);
					DalStatusHandler::RaiseEventForException(DalErrorAlarmStatusFlag::ThreadException, gcnew ScorException(excepObj));
				}
			}

			bool DalCPwaSimulationHandler::GetFileNameFromConfgAndOpen()
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
					//get the PWa settings from config file.
					//It contains the file name 
					configMgr->GetPwaUserSettings();

					tempFilePath =CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstSimFolderPathPwa);
               		_tonometerSimulationFile = gcnew DalSimulationFile(tempFilePath + configMgr->PwaSettings->SimulationType + tempFileExt);
					
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

			bool DalCPwaSimulationHandler::StartCapture(int captureTime, int samplingRate)
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
					captureTimer->Elapsed += gcnew ElapsedEventHandler(&DalCPwaSimulationHandler::OnTimerReadMultipleEvents); 
					
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

			
			bool DalCPwaSimulationHandler::StartBP(DalNIBPMode nibpMode, unsigned short initialPressure)
			{
				DalPwvDataStruct tempNibpDataVar;
				nibpBufferObj->CreateBuffer(1,5);	//This will creat buffer for 16 elements
				
				for(int i=1; i <= 16; i++)
				{
					tempNibpDataVar.cuffPressure = (unsigned short) i * 10;
					nibpBufferObj->WriteDataToBuffer(tempNibpDataVar);
				}

				return NIBP->StartBP(nibpMode, initialPressure);		//DalNibpSimulationHandler::Instance->StartBP(nibpMode, initialPressure);
			}

			bool DalCPwaSimulationHandler::StartBP(DalNIBPMode nibpMode)
			{
				return NIBP->StartBP(nibpMode);	// DalNibpSimulationHandler::Instance->StartBP(nibpMode);
			}

			bool DalCPwaSimulationHandler::FinishBP()
			{
				return NIBP->FinishBP();	// DalNibpSimulationHandler::Instance->FinishBP();
			}

			bool DalCPwaSimulationHandler::AbortBP()
			{
				return NIBP->AbortBP();		//DalNibpSimulationHandler::Instance->AbortBP();
			}
		}
	}
}