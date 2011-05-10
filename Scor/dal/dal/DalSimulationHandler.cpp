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
				_currentEAStatusFlag = 0; //-1;
				_currentCuffStatusFlag = 0;
				_currentEAStatusFlag = 0;

				dataBufferObj = DalDataBuffer::Instance;
			}

			bool DalSimulationHandler::GetFileNameFromConfgAndOpen()
			{
				bool result = false;
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
                    configMgr->GetPwvUserSettings();

                    // construct the simulation file path, based on the file name selected
                    // by user in "system - settings - PWV Settings - simulation type"
                    //String^ tempFilePath =CrxMessagingManager::Instance->GetMessage("DAL_CONST_SIM_FOLDER_PATH");
					String^ tempFilePath =CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstSimFolderPath);
                    //String^ tempFileExt = CrxMessagingManager::Instance->GetMessage("DAL_CONST_DAT_FILE_EXTN");
					String^ tempFileExt = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstDatFileExtn);
                    _tonometerSimulationFile = gcnew DalSimulationFile(tempFilePath + configMgr->PwvSettings->SimulationType + tempFileExt);
				
					//pick the cuff timer sim file from another directory
					//_cuffTimerSimulationFile = gcnew DalSimulationFile(CrxMessagingManager::Instance->GetMessage("DAL_CONST_CUFFTIMER_FILE_PATH"));
					_cuffTimerSimulationFile = gcnew DalSimulationFile(CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstCufftimerFilePath));


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

			void DalSimulationHandler::OnTimerGetValuesAndRaiseEvents(Object^ sender, ElapsedEventArgs^ args)
			{
				//variables to hold the tonometer and cuff pulse readings
				static unsigned long tonoData, cuffPulseData;
				
				//get the next set of values from the simulation file.
				_tonometerSimulationFile->GetNextValues(&tonoData, &cuffPulseData);
				
				//raise the tonometer event
				DalEventContainer::Instance->OnDalTonometerDataEvent(sender, gcnew DalTonometerDataEventArgs((unsigned short)tonoData));
				//raise the cuff event
				DalEventContainer::Instance->OnDalCuffPulseEvent(sender, gcnew DalCuffPulseEventArgs((unsigned short)cuffPulseData));
			}			

			bool DalSimulationHandler::StartCapture()
			{
				try
				{
					firstReadAfterCaptureStarted = true;

					//move file to start in case it isn't alreay at start.
					_tonometerSimulationFile->ResetFileStreamPosition();
					_cuffTimerSimulationFile->ResetFileStreamPosition();
					
					//The interval should come from a global value
					//initialize a new timer object
					captureTimer = gcnew Timers::Timer(DalConstants::SimulationTimerInterval);
					
					//specify the event handler to handle timer events
					captureTimer->Elapsed += gcnew ElapsedEventHandler(&DalSimulationHandler::OnTimerGetValuesAndRaiseEvents); 
					
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

			//New method to read n numer of element per interval
			//At present we will read 256 elements in 1 second
			void DalSimulationHandler::OnTimerReadMultipleEvents(Object^ sender, ElapsedEventArgs^ args)
			{
				//using parametrized threadstart to pass parameter
				Thread^ simulationWriterThread = gcnew Thread(gcnew ParameterizedThreadStart(DalSimulationHandler::ReadMultipleEventsInLoop)); 
				simulationWriterThread->Start(sender);
				
			}

			//new method to to read data in a loop 
			void DalSimulationHandler::ReadMultipleEventsInLoop(Object^ sender)
			{
				DalPwvDataStruct tempPWVDataVar;
			
				//variables to hold the tonometer and cuff pulse readings
				static unsigned long tonoData, cuffPulseData;
				static unsigned long cuffAbsolutePressure;
				static unsigned long locCountdownTimer = 0;
				static unsigned long statusBytes, locEASourceFlag;
				static bool currentCuffStateIsInflated = false;
				
				//Pick the number of reads from DalConstants
				int numberOfReads = DalConstants::SimulationNumberOfReadsPerInterval;
				
				
				if (firstReadAfterCaptureStarted == true)
				{
					//CrxLogger::Instance->Write(" ReadMultipleEventsInLoop inside IF firstReadAfterCaptureStarted = " + firstReadAfterCaptureStarted.ToString());

					tonoData = cuffPulseData = cuffAbsolutePressure = locCountdownTimer = statusBytes =  0;
					_currentEASourceFlag = _currentEAStatusFlag  = _currentCuffStatusFlag = 0;
					currentCuffStateIsInflated = firstReadAfterCaptureStarted = false;
				}
				
				//Read n elements in a loop. 
				for (int counter = 0; counter < numberOfReads ; counter++)
				{
					if (locCountdownTimer <=0) 
					{
						//get next set of values from the cufff simulation file
						_cuffTimerSimulationFile->GetNextValues(&locCountdownTimer, &cuffAbsolutePressure, &statusBytes, &locEASourceFlag);
						//CrxLogger::Instance->Write("locCountdownTimer" + locCountdownTimer + ", cuffAbsolutePressure:" + cuffAbsolutePressure + ", statusBytes" + statusBytes.ToString("X") + " ,locEASourceFlag" + locEASourceFlag.ToString("X"));

						//store the Error/alarm SOURCE in the global variable. If an event is raised we need to retrive the stored value to find the source.
						_currentEASourceFlag = locEASourceFlag;

						CheckStatusFlag(statusBytes, currentCuffStateIsInflated);
					}

					//get the next set of values from the tonometer simulation file.
					_tonometerSimulationFile->GetNextValues(&tonoData, &cuffPulseData);

					if (currentCuffStateIsInflated == true)
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
					//CrxLogger::Instance->Write(" Tono : " + tonoData + "cuffPulse: " + cuffPulseData + " cuffAbsolutePressure: " + cuffAbsolutePressure + " tempPWVDataVar.countdownTimer : " + tempPWVDataVar.countdownTimer );

					//write data to buffer
					dataBufferObj->WriteDataToBuffer(tempPWVDataVar);

					//decrement the timer after every write operation
					locCountdownTimer -= DalConstants::DataSamplingInterval;
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

			//bool DalSimulationHandler::CheckCuffStatusFlagsChanged(unsigned long newCuffStatusFlags) 
			//{
			//	CrxLogger::Instance->Write("CheckCuffStatusFlagsChanged currentflag " + _currentCuffStatusFlag.ToString("X") + " newCuffStatusFlags: " + newCuffStatusFlags.ToString("X"));
			//	if (newCuffStatusFlags != _currentCuffStatusFlag )
			//	{
			//		//Flags have changed . Assign the new flags 
			//		_currentCuffStatusFlag = newCuffStatusFlags;
			//		return true;
			//	}
			//	else
			//	{
			//		//no change
			//		return false;
			//	}
			//	
			//}
			
			//bool DalSimulationHandler::CheckEAStatusFlagChanged(unsigned long newEAStatusFlag) 
			//{
			//	CrxLogger::Instance->Write("CheckEAStatusFlagChanged _currentEAStatusFlag:" + _currentEAStatusFlag.ToString("X4") + " newEAStatusFlag:"+newEAStatusFlag.ToString("X4") );
			//			
			//	if (newEAStatusFlag != _currentEAStatusFlag  )
			//	{
			//		CrxLogger::Instance->Write("CheckEAStatusFlagChanged>>>Flags have changed");
			//		//Flags have changed . Assign the new flags 
			//		_currentEAStatusFlag = newEAStatusFlag;
			//		return true;
			//	}
			//	else
			//	{
			//		//no change
			//		return false;
			//	}
			//}
			
			//String^ DalSimulationHandler::MapErrorSourceToString(unsigned long sourceFlags) 
			//{
			//	static DalErrorSource  errorSourceEnum;
			//	errorSourceEnum = safe_cast<DalErrorSource>(sourceFlags);

			//	CrxLogger::Instance->Write("Deepak>>> MapErrorSourceToString sourceFlags:" + sourceFlags.ToString("X8") + " errorSourceEnum: " + errorSourceEnum.ToString());

			//	try
			//	{
			//		dalErrorAlarmSourceName= String::Empty;

			//		switch( errorSourceEnum)
			//		{
			//			case DalErrorSource::CuffLeak :
			//			case DalErrorSource::DualSensors :
			//				dalErrorAlarmSourceName = Enum::Format(DalErrorSource::typeid, errorSourceEnum, "G");
			//				break;
			//			default:
			//				dalErrorAlarmSourceName = "AlarmSourceUnknown";
			//				dalErrorAlarmSourceName = dalErrorAlarmSourceName + sourceFlags.ToString();
			//				//throw gcnew DalException("DAL_ERR_UNKNOWN_BIT_FLAG");
			//				throw gcnew ScorException(1007, "DAL_ERR_UNKNOWN_BIT_FLAG", ErrorSeverity::Warning );
			//				break;
			//		}
			//	}
			//	catch(ScorException^ )
			//	{
			//		throw;
			//	}
			//	catch(Exception^ excepObj)
			//	{
			//		throw gcnew ScorException(excepObj);
			//	}

			//	return dalErrorAlarmSourceName;
			//}
			
			//String^ DalSimulationHandler::MapAlarmSourceToString(unsigned long sourceFlags) 
			//{
			//	static DalAlarmSource alarmSourceEnum;
			//	alarmSourceEnum = safe_cast<DalAlarmSource>(sourceFlags);

			//	dalErrorAlarmSourceName= String::Empty;
			//	CrxLogger::Instance->Write("Deepak>>> MapAlarmSourceToString sourceFlags:" + sourceFlags.ToString("X8"));

			//	try
			//	{
			//		switch( alarmSourceEnum)
			//		{
			//			case DalAlarmSource::OverPressure:
			//			case DalAlarmSource::InflatedOverTime:
			//				dalErrorAlarmSourceName = Enum::Format(DalAlarmSource::typeid, alarmSourceEnum, "G");
			//				break;
			//			default:
			//				dalErrorAlarmSourceName = "AlarmSourceUnknown";
			//				dalErrorAlarmSourceName = dalErrorAlarmSourceName + sourceFlags.ToString();
			//				//throw gcnew DalException("DAL_ERR_UNKNOWN_BIT_FLAG");
			//				throw gcnew ScorException(1007,"DAL_ERR_UNKNOWN_BIT_FLAG", ErrorSeverity::Warning);
			//				break;
			//		}
			//	}
			//	catch(ScorException^ )
			//	{
			//		throw;
			//	}
			//	catch(Exception^ excepObj)
			//	{
			//		throw gcnew ScorException(excepObj);
			//	}

			//	return dalErrorAlarmSourceName;
			//}
			

			//DalCuffStateFlags DalSimulationHandler::TranslateCuffStatusBits(unsigned long cuffStatusFlags) 
			//{
			//	static DalCuffStateFlags data;
			//	data = (DalCuffStateFlags)(cuffStatusFlags & 0x2F00);
	
			//	switch (data)
			//	{
			//	case DalCuffStatusBitMask::CUFF_DISCONNECTED_STATUS_BITS:
			//		data = DalCuffStateFlags::CUFF_STATE_DISCONNECTED;
			//			break;
			//	case DalCuffStatusBitMask::CUFF_INFLATING_STATUS_BITS:
			//			data = DalCuffStateFlags::CUFF_STATE_INFLATING;
			//			break;
			//		case DalCuffStatusBitMask::CUFF_INFLATED_STATUS_BITS:
			//			data = DalCuffStateFlags::CUFF_STATE_INFLATED;
			//			break;
			//		case DalCuffStatusBitMask::CUFF_DEFLATING_STATUS_BITS:
			//			data = DalCuffStateFlags::CUFF_STATE_DEFLATING;
			//			break;
			//		case DalCuffStatusBitMask::CUFF_DEFLATED_STATUS_BITS:
			//			data = DalCuffStateFlags::CUFF_STATE_DEFLATED;
			//			break;
			//		default:
			//			data = DalCuffStateFlags::CUFF_STATE_UNKNOWN;
			//			//throw gcnew DalException("DAL_ERR_UNKNOWN_BIT_FLAG");
			//			throw gcnew ScorException(1007,"DAL_ERR_UNKNOWN_BIT_FLAG", ErrorSeverity::Warning);
			//			break;
			//	}
			//	//CrxLogger::Instance->Write("Deepak>>> TranslateCuffStatusBits, data = " + data.ToString());
			//	return data;
			//}

			//DalErrorAlarmStatusFlag DalSimulationHandler::TranslateErrorAlarmStatusBits(unsigned long statusFlags)
			//{

			//	static DalModuleErrorAlarmBitMask data;
			//	static DalErrorAlarmStatusFlag retAlarmValue;
			//	//This was an error and it has been corrected 0x2F00 > 0x0028
			//	//data = (DalModuleErrorAlarmBitMask)(statusFlags & 0x2F00);
			//	data = (DalModuleErrorAlarmBitMask)(statusFlags & 0x0028);
			//	//errorAlarmStatusBytes =statusBytes & 0x0028;
			//	
			//	switch (data)
			//	{
			//		case DalModuleErrorAlarmBitMask::NoErrorAlarm:
			//			retAlarmValue = DalErrorAlarmStatusFlag::ActiveStatus;
			//			break;
			//		case DalModuleErrorAlarmBitMask::ErrorStatus:
			//			retAlarmValue = DalErrorAlarmStatusFlag::UnrecoverableStatus;
			//			break;
			//		case DalModuleErrorAlarmBitMask::AlarmStatus:
			//			retAlarmValue = DalErrorAlarmStatusFlag::RecoverableStatus;
			//			break;
			//		case DalModuleErrorAlarmBitMask::ErrorAndAlarmStatus:
			//			retAlarmValue = DalErrorAlarmStatusFlag::UnrecoverableStatus;
			//			break;
			//		default:
			//			retAlarmValue = DalErrorAlarmStatusFlag::UnrecoverableStatus;
			//			//throw gcnew DalException("DAL_ERR_UNKNOWN_BIT_FLAG");
			//			throw gcnew ScorException(1007,"DAL_ERR_UNKNOWN_BIT_FLAG", ErrorSeverity::Warning);
			//			break; 
			//	}

			//	CrxLogger::Instance->Write("Deepak>>> TranslateErrorAlarmStatusBits>>> statusFlags" + statusFlags.ToString("X4") + " data:" + data.ToString() + " retAlarmValue:" + retAlarmValue.ToString());
			//	
			//	return retAlarmValue;
			//}

			//Deepak: we are removing this method > 
			//It should not be called when device is in simulation.
			//int DalSimulationHandler::FindModule(String^ comPort)
			//{
			//	// stub method
			//	//return true and make comPort null to signify that the port is avalaiable
			//	comPort = nullptr;
			//	return true;
			//}

			bool DalSimulationHandler::CheckIfDeviceIsConnected()
			{
				return true;
				//simulation device will alawys be connected.
			}


	//bool DalSimulationHandler::SaveCaptureData(array< unsigned short >^ tonometerData, array< unsigned short >^ cuffPulse, unsigned short bufferSize)
	//{	
	//	unsigned short index = 0;
	//	
	//	// construct the file path, file contains captured waveform data and of same format
	//	// as of the simulation file. (capture_DateTime.Dat).
	//	String^ tempFilePath = ".\\simulation\\pwv\\";
	//	String^ tempCapture = "capture_";
	//	String^ tempFileExt = ".dat";

	//	DateTime currentDateTime;
	//	currentDateTime = System::DateTime::Now;

	//	try
	//	{

	//		//create the file name using current date time
	//		String  ^ currentDateTimeStr = currentDateTime.ToString("yyyyMMMddHHmmss");
	//		currentDateTimeStr = tempFilePath + tempCapture + currentDateTimeStr+ tempFileExt; 
	//		
	//		DalSimulationFile^ simulationOutputFile; //Pointer to first simulation file
	//		simulationOutputFile = gcnew DalSimulationFile();

	//		if(simulationOutputFile->CreateFile(currentDateTimeStr))
	//		{
	//			_savedDataFilePath = Directory::GetCurrentDirectory() + simulationOutputFile->filePath->Substring(1);

	//			while (index < bufferSize)
	//			{
	//				simulationOutputFile->SaveCurrentValues(tonometerData[index], cuffPulse[index]);
	//				index++;
	//			}
	//		}
	//		simulationOutputFile->CloseFile();
	//		return true;
	//	}
	//	catch(ScorException ^)
	//	{
	//		throw;
	//	}
	//	catch(Exception ^excepObj)
	//	{
	//		throw gcnew ScorException(excepObj);
	//	}
	//}

			bool DalSimulationHandler::SetPressure(int newPressure, EM4CuffBoard cuffBoard)
			{
				return false; //not a valid command for simulation
			}

			/*String^ DalSimulationHandler::GetSavedFileName()
			{
				return _savedDataFilePath;
			}*/


			bool DalSimulationHandler::CheckStatusFlag(unsigned long statusBytes, bool %cuffIsInflated)
			{
				static unsigned long cuffStatusBytes, errorAlarmStatusBytes; 
				
				//First break the status flag down into its two important sets
				//cuff status related bits
				cuffStatusBytes = statusBytes & (unsigned long)DalStatusFlagBitMask::CuffStatusBitsMask;
				//and Error-Alarm event related bits
				errorAlarmStatusBytes =statusBytes & (unsigned long)DalStatusFlagBitMask::ErrorAlarmStatusBitsMask;
				//CrxLogger::Instance->Write("statusBytes:" + statusBytes.ToString("X4") +" cuffStatusBytes:" + cuffStatusBytes.ToString("X4") + " errorAlarmStatusBytes:"+errorAlarmStatusBytes.ToString("X4") );
				
			
				 if (CheckCuffStatusFlagsChanged(cuffStatusBytes) ==  true)
				 {
					  //Code to check if the new status is cuff inflated/
					 //If yes then the countdown timer value should be decremented. If not then return 0.

					DalCuffStateFlags currentCuffState = TranslateCuffStatusBits(cuffStatusBytes);
					 if (currentCuffState == DalCuffStateFlags::CUFF_STATE_INFLATED)
					 {
						 cuffIsInflated = true;
					 }
					 else
					 {
						 cuffIsInflated = false;
					 }
					
					 //map the status bytes to a state flag
					 //	raise a staus change event and update the new flag.
					DalEventContainer::Instance->OnDalCuffStatusEvent(nullptr, gcnew DalCuffStatusEventArgs(currentCuffState));
					
				 }

				 if (CheckEAStatusFlagChanged(errorAlarmStatusBytes) == true)
				 {
					 //if a change has occured in the error/alarm bits first raise an event 
					 DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, gcnew DalModuleErrorAlarmEventArgs(TranslateErrorAlarmStatusBits(errorAlarmStatusBytes)));
					 //CrxLogger::Instance->Write("CheckEAStatusFlagChanged>>>OnDalModuleErrorAlarmEvent event raised");
				}
				return true;
			}

		}//END DataAccess namespace
	}
}

