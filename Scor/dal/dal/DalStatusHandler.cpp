/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalStatusHandler.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalStatusHandler class
*/

#include "stdafx.h"
#include "DalSimulationHandler.h"
#include "DalEventContainer.h"
#include "DalSimulationFile.h"
#include "DalDataBuffer.h"
#include "DalModule.h"
#include "DalCommon.h"
#include "DalStatusHandler.h"
#include "DalActiveDevice.h"
#include "DalBinaryConversions.h"


using namespace System;
using namespace System::Threading;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace System::Text;
using namespace System::Globalization;



namespace AtCor{
	namespace Scor{
		namespace DataAccess{

			String^ DalStatusHandler::GetAlarmSource(DalAlarmSource% translatedAlarmSource)
			{
				String ^ alarmSourceName;
				
				if ( _currentEASourceFlag  & (int)DalAlarmSourceFlagBitMask::SupplyRailsBitMask)
				{
					alarmSourceName =  GetSupplyRailsAlarmSource(translatedAlarmSource);
				}
				else
				{
					alarmSourceName = GetNameofRaisedAlarmFlag(translatedAlarmSource); //add the enum here too TODO
				}

				if (String::IsNullOrEmpty(alarmSourceName))
				{
					translatedAlarmSource = DalAlarmSource::NoAlarmDefined; //give a null indicator
					alarmSourceName = Enum::Format(DalAlarmStatusBitMask::typeid, DalAlarmStatusBitMask::NoAlarm, DalFormatterStrings::PrintEnumName);

				}

				return alarmSourceName;
			}

			String^ DalStatusHandler::GetSupplyRailsAlarmSource(DalAlarmSource% translatedAlarmSource)
			{
				DalAlarmSupplyRailFlag railAlarmFlag;

				try
				{
					//first convert to an enum of the same type even if the value doesnt exit.
					railAlarmFlag = (DalAlarmSupplyRailFlag)_currentEASourceFlag;

					//first check if the source flag is present
					if (Enum::IsDefined(DalAlarmSupplyRailFlag::typeid , railAlarmFlag))
					{
						//then convert to the appropriate rail source
						railAlarmFlag = (DalAlarmSupplyRailFlag)_currentEASourceFlag;

						//return the reference parameter
						translatedAlarmSource = DalBinaryConversions::ConvertAlarmType(railAlarmFlag);
						return Enum::Format(DalAlarmSupplyRailFlag::typeid, railAlarmFlag, DalFormatterStrings::PrintEnumName);
					}
					else
					{
						//signal the enum as a false data
						translatedAlarmSource = DalAlarmSource::NoAlarmDefined;
						//no error return empty.
						return  String::Empty ;
					}
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
			}

			String ^ DalStatusHandler::GetNameofRaisedAlarmFlag(DalAlarmSource% translatedAlarmSource)
			{
				String ^ alarmSourceName;
				int alarmFlagBitIndex;
				unsigned long bitCheckMask = 0x0001;
				DalAlarmFlagBitPosition raisedFlag;
				try
				{
					//rotate through the entier range of bits
					for ( alarmFlagBitIndex = (int)DalAlarmFlagBitPosition::PowerUp; alarmFlagBitIndex < (int)DalAlarmFlagBitPosition::TotalBitCount; alarmFlagBitIndex++)
					{
						 if ( (bitCheckMask & _currentEASourceFlag) != 0)
						 {
							 //it means that one alarm flag is raised 
							 //find the number and convert to a string

							 raisedFlag = safe_cast<DalAlarmFlagBitPosition>(alarmFlagBitIndex);

							 //translate it to DalAlarmSource
							 translatedAlarmSource = DalBinaryConversions::ConvertAlarmType(raisedFlag);

							 //now that we have the enum name , return the string form
							alarmSourceName = Enum::Format(DalAlarmFlagBitPosition::typeid, raisedFlag, DalFormatterStrings::PrintEnumName);
							return alarmSourceName;
						 }

						//shift the bit by 1 to the left before checking next flag
						bitCheckMask = bitCheckMask<<1;

					}
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

				return String::Empty;
			}

			bool DalStatusHandler::CheckCuffStatusFlagsChanged(unsigned long newCuffStatusFlags) 
			{
				////CrxLogger::Instance->Write("CheckCuffStatusFlagsChanged currentflag " + _currentCuffStatusFlag.ToString("X2) + " newCuffStatusFlags: " + newCuffStatusFlags.ToString("X2), ErrorSeverity::Debug);
				if (newCuffStatusFlags != _currentCuffStatusFlag )
				{
					//Flags have changed . Assign the new flags 
					_currentCuffStatusFlag = newCuffStatusFlags;
					return true;
				}
				else
				{
					//no change
					return false;
				}
				
			}

			bool DalStatusHandler::CheckAlarmStatusFlagChanged(unsigned long newAlarmStatusFlag) 
			{
				////CrxLogger::Instance->Write("CheckAlarmStatusFlagChanged _currentAlarmStatusFlag:" + _currentAlarmStatusFlag.ToString("X4") + " newEAStatusFlag:"+newEAStatusFlag.ToString("X4") , ErrorSeverity::Debug);
						
				if (newAlarmStatusFlag != _currentAlarmStatusFlag  )
				{
					CrxLogger::Instance->Write("DAL:CheckAlarmStatusFlagChanged>>>Flags have changed _currentAlarmStatusFlag:" + _currentAlarmStatusFlag.ToString("X4") + " newAlarmStatusFlag:"+newAlarmStatusFlag.ToString("X4") , ErrorSeverity::Debug);
				
					////CrxLogger::Instance->Write("CheckAlarmStatusFlagChanged>>>Flags have changed", ErrorSeverity::Debug);
					
					//Flags have changed . Assign the new flags 
					_currentAlarmStatusFlag = newAlarmStatusFlag;
					return true;
				}
				else
				{
					//no change
					return false;
				}
			}


	
			DalCuffStateFlags DalStatusHandler::TranslateCuffStatusBits(unsigned long cuffStatusFlags) 
			{
				DalCuffStatusBitMask currentCuffStatusBitMask;
				DalCuffStateFlags currentCuffStateFlags;

				currentCuffStatusBitMask = (DalCuffStatusBitMask)cuffStatusFlags;
				//First check if the cuff strate flag passed to us is valid
				if (!(Enum::IsDefined(DalCuffStatusBitMask::typeid, currentCuffStatusBitMask)))
				{
					//no: throw an exception
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrUnknownBitFlagErrCd,CrxStructCommonResourceMsg::DalErrUnknownBitFlag,ErrorSeverity::Warning);
				}

				switch (currentCuffStatusBitMask)
				{
					/*case DalCuffStatusBitMask::CUFF_DISCONNECTED_STATUS_BITS:
						currentCuffStateFlags = DalCuffStateFlags::CUFF_STATE_DISCONNECTED;
						break;*/
					case DalCuffStatusBitMask::CUFF_INFLATING_STATUS_BITS:
					//case DalCuffStatusBitMask::CUFF_DISCONNECTED_INFLATING_STATUS_BITS:
						currentCuffStateFlags = DalCuffStateFlags::CUFF_STATE_INFLATING;
						break;
					case DalCuffStatusBitMask::CUFF_INFLATED_STATUS_BITS:
						currentCuffStateFlags = DalCuffStateFlags::CUFF_STATE_INFLATED;
						break;
					case DalCuffStatusBitMask::CUFF_DEFLATING_STATUS_BITS:
					//case DalCuffStatusBitMask::CUFF_DISCONNECTED_DEFLATING_STATUS_BITS:
						currentCuffStateFlags = DalCuffStateFlags::CUFF_STATE_DEFLATING;
						break;
					case DalCuffStatusBitMask::CUFF_DEFLATED_STATUS_BITS:
						currentCuffStateFlags = DalCuffStateFlags::CUFF_STATE_DEFLATED;
						break;
					default:
						currentCuffStateFlags = DalCuffStateFlags::CUFF_STATE_UNKNOWN;
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrUnknownBitFlagErrCd,CrxStructCommonResourceMsg::DalErrUnknownBitFlag,ErrorSeverity::Warning);
						break;
				}

				return currentCuffStateFlags;
			}

			DalErrorAlarmStatusFlag DalStatusHandler::TranslateAlarmStatusBits(unsigned long statusFlags)
			{

				static DalAlarmStatusBitMask data;
				static DalErrorAlarmStatusFlag retAlarmValue;

				data = (DalAlarmStatusBitMask)(statusFlags & (unsigned long)DalStatusFlagBitMask::AlarmStatusBitsMask);
				
				switch (data)
				{
					case DalAlarmStatusBitMask::NoAlarm  :
						retAlarmValue = DalErrorAlarmStatusFlag::ActiveStatus;
						break;
					
						//TS has suggested using Unrecoverable status until PWVSW-395 is complete.
					case DalAlarmStatusBitMask::AlarmStatus:
						//retAlarmValue = DalErrorAlarmStatusFlag::RecoverableStatus;
						retAlarmValue = DalErrorAlarmStatusFlag::UnrecoverableStatus;
						break;
					
					default:
						retAlarmValue = DalErrorAlarmStatusFlag::UnrecoverableStatus;
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrUnknownBitFlagErrCd,CrxStructCommonResourceMsg::DalErrUnknownBitFlag, ErrorSeverity::Warning);
						break; 
				}

				////CrxLogger::Instance->Write("DAL>>> TranslateAlarmStatusBits>>> statusFlags" + statusFlags.ToString("X4") + " data:" + data.ToString() + " retAlarmValue:" + retAlarmValue.ToString(), ErrorSeverity::Debug);
				
				return retAlarmValue;
			}


			bool DalStatusHandler::SaveCaptureData(array< unsigned short >^ tonometerData, array< unsigned short >^ cuffPulse, unsigned short bufferSize)
			{
				
				unsigned short index = 0;
				
				// construct the file path, file contains captured waveform data and of same format
				// as of the simulation file. (capture_DateTime.Dat).
				String^ tempFilePath = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstSimFolderPath); //TODO: put this somewhere too
				String^ tempCapture =  CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstCaptureFilePrefix); //TODO
				String^ tempFileExt = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstDatFileExtn);

				DateTime currentDateTime;
				currentDateTime = System::DateTime::Now;
				

				try
				{

					//create the file name using current date time
					String  ^ currentDateTimeStr = currentDateTime.ToString(DalFormatterStrings::FullDateTimeFormat );
					currentDateTimeStr = tempFilePath + tempCapture + currentDateTimeStr+ tempFileExt; 
					
					DalSimulationFile^ simulationOutputFile; //Pointer to first simulation file
					simulationOutputFile = gcnew DalSimulationFile();

					if(simulationOutputFile->CreateFile(currentDateTimeStr))
					{
						//Remove the duplicate backslashes from the string 
						String^ str = simulationOutputFile->filePath->Replace(DalFormatterStrings::FourSlashes , DalFormatterStrings::TwoSlashes );  
													
						//save the filepath to a variable.
						//this variable will be called by another funciton to get the value

						//remove the dot at the begining
						_savedDataFilePath = Directory::GetCurrentDirectory() + str->Substring(1);  

						while (index < bufferSize)
						{
							simulationOutputFile->SaveCurrentValues(tonometerData[index], cuffPulse[index]);
							index++;
						}
					}
					simulationOutputFile->CloseFile();
					return true;
				}
				catch(ScorException ^)
				{
					return false;
				}
				catch(Exception ^)
				{
					return false;
				}
			}
			
			bool DalStatusHandler::SaveCaptureData(array< unsigned short >^ cuffPulse, unsigned short bufferSize)
			{
				unsigned short index = 0;
				
				String^ tempFilePath = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstSimFolderPathPwa); //TODO: put this somewhere too
				String^ tempCapture	 = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstCaptureFilePrefix); //TODO
				String^ tempFileExt  = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstDatFileExtn);

				DateTime currentDateTime = System::DateTime::Now;;
				//currentDateTime = System::DateTime::Now;
				DalStatusHandler::cPwaFileDateTime = currentDateTime;
				try
				{

					//create the file name using current date time
					String^ currentDateTimeStr = currentDateTime.ToString(DalFormatterStrings::FullDateTimeFormat);
	
					//currentDateTimeStr = tempFilePath + tempCapture + currentDateTimeStr+ tempFileExt; 
					currentDateTimeStr = String::Concat(tempFilePath, tempCapture, currentDateTimeStr, tempFileExt); 
					
					DalSimulationFile^ simulationOutputFile = gcnew DalSimulationFile();; //Pointer to first simulation file
					//simulationOutputFile = gcnew DalSimulationFile();

					if(simulationOutputFile->CreateFile(currentDateTimeStr))
					{
						//Remove the duplicate backslashes from the string 
						String^ str = simulationOutputFile->filePath->Replace(DalFormatterStrings::FourSlashes, DalFormatterStrings::TwoSlashes );  
													
						//save the filepath to a variable.
						//this variable will be called by another funciton to get the value

						//remove the dot at the begining
						_savedDataFilePath = String::Concat(Directory::GetCurrentDirectory(), str->Substring(1));  

						while (index < bufferSize)
						{
							simulationOutputFile->SaveCurrentValues(cuffPulse[index]);
							index++;
						}
					}
					simulationOutputFile->CloseFile();
					return true;
				}
				catch(ScorException ^)
				{
					return false;
				}
				catch(Exception ^)
				{
					return false;
				}
			}

			bool DalStatusHandler::SaveNibpData(array< unsigned short >^ time, array< unsigned short >^ status, array< unsigned short >^ errorCode, array< unsigned short >^ sp, array< unsigned short >^ dp, array< unsigned short >^ map, array< unsigned short >^ hr, unsigned short bufferSize)
			{
				unsigned short index = 0;
				
				String^ tempFilePath = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstSimFolderPathNibp); //TODO: put this somewhere too
				String^ tempCapture	 = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstCaptureFilePrefix); //TODO
				String^ tempFileExt  = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstDatFileExtn);
				
				//To Do: time should be the pwa file time
				DateTime currentDateTime = DalStatusHandler::cPwaFileDateTime;
				//DateTime currentDateTime = System::DateTime::Now;

				try
				{
					//create the file name using current date time
					String^ currentDateTimeStr = currentDateTime.ToString(DalFormatterStrings::FullDateTimeFormat);
	
					//currentDateTimeStr = tempFilePath + tempCapture + currentDateTimeStr+ tempFileExt; 
					currentDateTimeStr = String::Concat(tempFilePath, tempCapture, currentDateTimeStr, tempFileExt); 
					
					DalSimulationFile^ simulationOutputFile = gcnew DalSimulationFile();; //Pointer to first simulation file
					//simulationOutputFile = gcnew DalSimulationFile();

					if(simulationOutputFile->CreateFile(currentDateTimeStr))
					{
						//Remove the duplicate backslashes from the string 
						String^ str = simulationOutputFile->filePath->Replace(DalFormatterStrings::FourSlashes, DalFormatterStrings::TwoSlashes );  
													
						//save the filepath to a variable. This variable will be called by another funciton to get the value
						//remove the dot at the begining
						_savedDataFilePathNibp = String::Concat(Directory::GetCurrentDirectory(), str->Substring(1));  

						while (index < bufferSize)
						{
							simulationOutputFile->SaveCurrentValues(time[index],
																	status[index], 
																	errorCode[index], 
																	sp[index], 
																	dp[index], 
																	map[index], 
																	hr[index]);
							index++;
						}
					}
					simulationOutputFile->CloseFile();
					return true;
				}
				catch(ScorException ^)
				{
					return false;
				}
				catch(Exception ^)
				{
					return false;
				}
			}

			bool DalStatusHandler::SaveNibpData(unsigned short time, unsigned short status, unsigned short errorCode, unsigned short sp, unsigned short dp, short map, unsigned short hr)
			{
				//unsigned short index = 0; unused parameter
				
				String^ tempFilePath = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstSimFolderPathNibp); //TODO: put this somewhere too
				String^ tempCapture	 = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstCaptureFilePrefix); //TODO
				String^ tempFileExt  = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstDatFileExtn);
				
				//To Do: time should be the pwa file time
				DateTime currentDateTime = DalStatusHandler::cPwaFileDateTime;
				//DateTime currentDateTime = System::DateTime::Now;

				try
				{
					//create the file name using current date time
					String^ currentDateTimeStr = currentDateTime.ToString(DalFormatterStrings::FullDateTimeFormat);
	
					//currentDateTimeStr = tempFilePath + tempCapture + currentDateTimeStr+ tempFileExt; 
					currentDateTimeStr = String::Concat(tempFilePath, tempCapture, currentDateTimeStr, tempFileExt); 
					
					DalSimulationFile^ simulationOutputFile = gcnew DalSimulationFile();; //Pointer to first simulation file
					//simulationOutputFile = gcnew DalSimulationFile();

					if(simulationOutputFile->CreateFile(currentDateTimeStr))
					{
						//Remove the duplicate backslashes from the string 
						String^ str = simulationOutputFile->filePath->Replace(DalFormatterStrings::FourSlashes, DalFormatterStrings::TwoSlashes );  
													
						//save the filepath to a variable. This variable will be called by another funciton to get the value
						//remove the dot at the begining
						_savedDataFilePathNibp = String::Concat(Directory::GetCurrentDirectory(), str->Substring(1));  

						simulationOutputFile->SaveCurrentValues(time, status, errorCode, sp, dp, map, hr);
						
					}
					simulationOutputFile->CloseFile();
					return true;
				}
				catch(ScorException ^)
				{
					return false;
				}
				catch(Exception ^)
				{
					return false;
				}
			}

			String^ DalStatusHandler::GetSavedFileName()
			{
				String^ returnValue = _savedDataFilePath;
				_savedDataFilePath  = String::Empty;
				return returnValue;
			}

			String^ DalStatusHandler::GetSavedFileNameNibp()
			{
				String^ returnValue = _savedDataFilePathNibp;
				_savedDataFilePath  = String::Empty;
				return returnValue;
			}

			bool DalStatusHandler::ProcessStatusFlag(unsigned long statusBytes)
			{
				//first check if the status flag has changed from the previous value
				if (!(CheckStatusFlagsChanged(statusBytes)))
				{
					//if no  then exit
					return true;
				}

				//if changed				
				//First break the status flag down into its  important sets
				SplitStatusFlagComponents(statusBytes);
				
				//then check individual parts
				
				try
				{
					//process the various parts in order of importance

					//if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.StopButton") == "Y")
					if(sysparamProcessStatusFlagPartsStopButton)
					{
						ProcessStopButtonBitMask();
					}
					
					//if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.PowerUpBit") == "Y")
					if(sysparamProcessStatusFlagPartsPowerUpBit)
					{
						ProcessPowerUpBitMask();
					}

					//if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.AlarmFlag") == "Y")
					if(sysparamProcessStatusFlagPartsAlarmFlag)
					{
						//check alarms bfore anything else
						ProcessAlarmStatusFlag();
					}

					//if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.CuffStatusFlags") == "Y")
					if(sysparamProcessStatusFlagPartsCuffStatusFlags)
					{
						ProcessCuffStatusFlag();
					}

					//if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.TonometerFlags") == "Y")
					if(sysparamProcessStatusFlagPartsTonometerFlags)
					{
						ProcessTonoStatusFlag();
					}

					//if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.UnusedBits") == "Y")
					if(sysparamProcessStatusFlagPartsUnusedBits)
					{
						//least important
						ProcessUnusedBitsStatusFlag(statusBytes);
					}
				}
				catch(ScorException^)
				{
					throw;
				}
				catch (Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

				return true;
			}


			bool DalStatusHandler::CheckStatusFlagsChanged(const unsigned long newStatusFlag)
			{
				if (newStatusFlag != _currentStatusFlag)
				{
					////CrxLogger::Instance->Write("CheckStatusFlagsChanged currentflag " + _currentStatusFlag.ToString("X2) + " newStatusFlags: " + newStatusFlag.ToString("X2), ErrorSeverity::Debug);
					//Flags have changed . Assign the new flags 
					_currentStatusFlag  = newStatusFlag;
					return true;
				}
				else
				{
					//no change
					return false;
				}
			}

			void DalStatusHandler::SplitStatusFlagComponents(const unsigned long statusBytes)
			{
				//break the individual parts

				//cuff status related bits
				_newCuffStatusBytes = statusBytes & (unsigned long)DalStatusFlagBitMask::CuffStatusBitsMask;
				
				//Alarm event related bits
				_newAlarmStatusBytes =statusBytes & (unsigned long)DalStatusFlagBitMask::AlarmStatusBitsMask;

				//tonometer related bits
				_newTonoStatusBytes = statusBytes & (unsigned long) DalStatusFlagBitMask::TonoStatusBitsMask;

				_newPowerUpStatusBytes = statusBytes & (unsigned long) DalStatusFlagBitMask::PowerUpBitMask;
				
				_newStopButtonStatusBytes = statusBytes & (unsigned long) DalStatusFlagBitMask::StopButtonBitMask;

				_newUnusedStatusBytes = statusBytes & (unsigned long) DalStatusFlagBitMask::UnusedStatusBitsMask;
								
				////CrxLogger::Instance->Write("statusBytes:" + statusBytes.ToString("X4") +" cuffStatusBytes:" + cuffStatusBytes.ToString("X4") + " alarmStatusBytes:"+eaStatusBytes.ToString("X4") ); //debugging on, ErrorSeverity::Debugly
			}

			 void DalStatusHandler::ProcessCuffStatusFlag()
			{
				if (CheckCuffStatusFlagsChanged(_newCuffStatusBytes) ==  true)
				{
					currentCuffState = TranslateCuffStatusBits(_newCuffStatusBytes);

					//map the status bytes to a state flag
					//	raise a staus change event and update the new flag.
					DalEventContainer::Instance->OnDalCuffStatusEvent(nullptr, gcnew DalCuffStatusEventArgs(currentCuffState));
				}
			}

			void DalStatusHandler::ProcessTonoStatusFlag()
			{

				if (_currentTonoStatusFlag != _newTonoStatusBytes)
				{
					//assing the new status bytes
					_currentTonoStatusFlag = _newTonoStatusBytes;

					DalTonometerState tonoState = TranslateTonoStatusBits(_newTonoStatusBytes);

					//raise event for both connected and disconnected states.
					DalEventContainer::Instance->OnDalTonometerStatusEvent(nullptr, gcnew DalTonometerStatusEventArgs(tonoState));
				}
			}

			void DalStatusHandler::ProcessAlarmStatusFlag()
			{
				 if (CheckAlarmStatusFlagChanged(_newAlarmStatusBytes) == true)
				 {
					 //raise this event only when bit is on1 not when bit is zero.
					 if (_newAlarmStatusBytes)
					 {
						  String ^ alarmSource;
					 //Get the source of the alarm
					 alarmSource= DalModule::Instance->GetErrorAlarmSource();

					 //raise an event only after getting the source of the error
					 DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, gcnew DalModuleErrorAlarmEventArgs(TranslateAlarmStatusBits(_newAlarmStatusBytes), alarmSource, DalBinaryConversions::ConvertAlarmType(alarmSource)));
					 CrxLogger::Instance->Write("DAL:ProcessAlarmStatusFlag>>>OnDalModuleErrorAlarmEvent event raised _newAlarmStatusBytes:" + _newAlarmStatusBytes, ErrorSeverity::Debug);

					 }
				 }
			}

			void DalStatusHandler::ProcessStopButtonBitMask()
			{
				if (_newStopButtonStatusBytes)
				{
					CrxLogger::Instance->Write("DAL:DalStatusHandler::ProcessStopButtonBitMask >>> Raising OnDalModuleErrorAlarmEvent with StopButtonPressed", ErrorSeverity::Debug);

					//Just raise the event . let the handler decidethe current mode and decide what actions need to be taken.
					
					String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::StopButtonPressed, DalFormatterStrings::PrintEnumName);
					DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::StopButtonPressed, sourceName, DalBinaryConversions::ConvertAlarmType(DalErrorAlarmStatusFlag::StopButtonPressed));
					DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);

					
				}
			}

			void DalStatusHandler::ProcessPowerUpBitMask()
			{
				if (_newPowerUpStatusBytes)
				{
					CrxLogger::Instance->Write("DAL:DalStatusHandler::ProcessPowerUpBitMask >>> Raising OnDalModuleErrorAlarmEvent with PowerUpEvent", ErrorSeverity::Debug);


					//Just raise the event. 
					//Let the handler decidethe current mode and decide what actions need to be taken.
					
					String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::PowerUpEvent , DalFormatterStrings::PrintEnumName);
					DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::PowerUpEvent, sourceName, DalBinaryConversions::ConvertAlarmType(DalErrorAlarmStatusFlag::PowerUpEvent));
					DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);
				}
			}

			void DalStatusHandler::ProcessUnusedBitsStatusFlag(const unsigned long statusBytes)
			{
				static unsigned long unusedFlagBPRRCurrent, unusedFlagBPRRNew;
				static unsigned long unusedFlagReservedLSB7Current, unusedFlagReservedLSB7New;
				static unsigned long unusedFlagReservedLSB6Current, unusedFlagReservedLSB6New;
				static unsigned long unusedFlagReservedLSB4Current, unusedFlagReservedLSB4New;
				static unsigned long unusedFlagReservedLSB3Current, unusedFlagReservedLSB3New;

				//bool setResetValue;


				if (_currentUnusedStatusFlag != _newUnusedStatusBytes)
				{
					//change the current flag
					_currentUnusedStatusFlag = _newUnusedStatusBytes;
					
					//split the various bits
					unusedFlagBPRRNew = statusBytes & (unsigned long)DalUnusedStatusFlagBit::UnusedBitBprr;
					unusedFlagReservedLSB7New = statusBytes & (unsigned long)DalUnusedStatusFlagBit::UnusedBitReservedLSB7 ;
					unusedFlagReservedLSB6New = statusBytes & (unsigned long)DalUnusedStatusFlagBit::UnusedBitReservedLSB6;
					unusedFlagReservedLSB4New = statusBytes & (unsigned long)DalUnusedStatusFlagBit::UnusedBitReservedLSB4 ;
					unusedFlagReservedLSB3New = statusBytes & (unsigned long)DalUnusedStatusFlagBit::UnusedBitReservedLSB3 ;

					//Now process each bit and raise event on a change			
					ProcessUnusedBit(unusedFlagBPRRCurrent , unusedFlagBPRRNew , DalUnusedStatusFlagBit::UnusedBitBprr);
					ProcessUnusedBit(unusedFlagReservedLSB3Current , unusedFlagReservedLSB3New , DalUnusedStatusFlagBit::UnusedBitReservedLSB3);
					ProcessUnusedBit(unusedFlagReservedLSB4Current , unusedFlagReservedLSB4New , DalUnusedStatusFlagBit::UnusedBitReservedLSB4);
					ProcessUnusedBit(unusedFlagReservedLSB7Current , unusedFlagReservedLSB7New , DalUnusedStatusFlagBit::UnusedBitReservedLSB7);
				}
			}
			

			void DalStatusHandler::ProcessUnusedBit( unsigned long & oldFlag , const unsigned long  & newFlag, DalUnusedStatusFlagBit unusedFlagType)
			{
				bool setResetValue;

				if (oldFlag != newFlag)
				{
					oldFlag = newFlag;

					setResetValue = (newFlag != 0);

					DalUnusedStatusFlagEventArgs^ eventArg = gcnew DalUnusedStatusFlagEventArgs( unusedFlagType, setResetValue);

					DalEventContainer::Instance->OnDalUnusedStatusFlagChangedEvent(nullptr, eventArg);

				}
			}


			void DalStatusHandler::ResetAllStaticMembers()
			{
				_currentEASourceFlag = 0;
				_currentAlarmStatusFlag  = 0;
				_currentCuffStatusFlag   = 0xFFFF; 
				_currentTonoStatusFlag = 0xFFFF;
				_currentStatusFlag = 0;
				_currentUnusedStatusFlag = 0;
				
				//reseting the flag masks to a value which is not used
				_newCuffStatusBytes = 0xFFFF; 
				_newAlarmStatusBytes = 0xFFFF;
				_newTonoStatusBytes = 0xFFFF;
				_newPowerUpStatusBytes = 0xFFFF;
				_newStopButtonStatusBytes = 0xFFFF;
				_newUnusedStatusBytes = 0xFFFF;
			}

			DalTonometerState DalStatusHandler::TranslateTonoStatusBits(unsigned long tonoStatusFlags)
			{
				DalTonometerState currentTonoMeterState ;
				DalTonometerStatusBitMask currentTonometerStatusBitMask;

				currentTonometerStatusBitMask = (DalTonometerStatusBitMask)tonoStatusFlags;

				//First check if the tonometer state flag passed to us is valid
				if (!(Enum::IsDefined(DalTonometerStatusBitMask::typeid, currentTonometerStatusBitMask)))
				{
					//no: throw an exception
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrUnknownBitFlagErrCd,CrxStructCommonResourceMsg::DalErrUnknownBitFlag,ErrorSeverity::Warning);
				}

				//next translate it to the correct state
				switch(currentTonometerStatusBitMask)
				{
					case DalTonometerStatusBitMask::TonometerNotConnectedBits :
						currentTonoMeterState = DalTonometerState::Disconnected;
						break;
					case DalTonometerStatusBitMask::TonometerConnectedBits :
						currentTonoMeterState = DalTonometerState::Connected;
						break;
					default:
						currentTonoMeterState = DalTonometerState::Unknown;
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrUnknownBitFlagErrCd,CrxStructCommonResourceMsg::DalErrUnknownBitFlag,ErrorSeverity::Warning);
						break;
				}

				return currentTonoMeterState;
			}

			void DalStatusHandler::RaiseEventForException(DalErrorAlarmStatusFlag alarmType, ScorException^ excptionObject)
			{
				String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, alarmType, DalFormatterStrings::PrintEnumName);
				DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(alarmType, sourceName, DalBinaryConversions::ConvertAlarmType(alarmType), excptionObject);
				DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);
			}


			DalStatusHandler::DalStatusHandler()
			{
				//clear all variables before accesing their values from file
				sysparamProcessStatusFlagPartsStopButton = false;
				sysparamProcessStatusFlagPartsPowerUpBit = false;
				sysparamProcessStatusFlagPartsAlarmFlag = false;
				sysparamProcessStatusFlagPartsCuffStatusFlags = false;
				sysparamProcessStatusFlagPartsTonometerFlags = false;
				sysparamProcessStatusFlagPartsUnusedBits = false;
			
				if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.StopButton") == "Y")
				{
					sysparamProcessStatusFlagPartsStopButton = true;
				}
				
				if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.PowerUpBit") == "Y")
				{
					sysparamProcessStatusFlagPartsPowerUpBit = true;
				}

				if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.AlarmFlag") == "Y")
				{
					sysparamProcessStatusFlagPartsAlarmFlag = true;
				}

				if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.CuffStatusFlags") == "Y")
				{
					sysparamProcessStatusFlagPartsCuffStatusFlags = true;
				}

				if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.TonometerFlags") == "Y")
				{
					sysparamProcessStatusFlagPartsTonometerFlags = true;
				}

				if (CrxSytemParameters::Instance->GetStringTagValue("ProcessStatusFlagParts.UnusedBits") == "Y")
				{
					sysparamProcessStatusFlagPartsUnusedBits = true;
				}
			}



		} //End of DataAccess namespace
	}
}