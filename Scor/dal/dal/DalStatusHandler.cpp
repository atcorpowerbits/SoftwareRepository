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

			//String^ DalStatusHandler::GetAlarmSource()
			//{
			//	static DalAlarmStatusBitMask sourceFlagsEnum;
			//	sourceFlagsEnum = safe_cast<DalAlarmStatusBitMask>(_currentAlarmStatusFlag & (unsigned long)DalStatusFlagBitMask::AlarmStatusBitsMask ); 
			//	//CrxLogger::Instance->Write("GetErrorAlarmSource >>>>>>>> _currentEASourceFlag:" + _currentEASourceFlag.ToString("X8") + " sourceFlagsEnum:" + sourceFlagsEnum.ToString()); //Logging only

			//	dalErrorAlarmSourceName= String::Empty;

			//	switch (sourceFlagsEnum)
			//	{
			//		case DalAlarmStatusBitMask::NoAlarm:
			//			dalErrorAlarmSourceName = Enum::Format(DalAlarmStatusBitMask::typeid, sourceFlagsEnum, DalFormatterStrings::PrintEnumName);
			//			break;
			//			//Error status is obsolete
			//		/*case DalAlarmStatusBitMask::ErrorStatus:
			//			dalErrorAlarmSourceName = MapErrorSourceToString(_currentEASourceFlag  & (unsigned long)DalAlarmSourceFlagBitMask::AlarmSourceBitMask );
			//			break;*/
			//			//TODO merge MapErrorSourceToString into MapAlarmSourceToString
			//		case DalAlarmStatusBitMask::AlarmStatus:
			//			dalErrorAlarmSourceName = MapAlarmSourceToString((_currentEASourceFlag >> 16) & (unsigned long)DalAlarmSourceFlagBitMask::AlarmSourceBitMask );
			//			break;
			//		default:
			//			dalErrorAlarmSourceName = _currentEASourceFlag.ToString();
			//			throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrUnknownBitFlagErrCd,CrxStructCommonResourceMsg::DalErrUnknownBitFlag, ErrorSeverity::Warning);
			//			break;
			//	}
			//	return dalErrorAlarmSourceName;
			//}

			String^ DalStatusHandler::GetAlarmSource()
			{
				String ^ alarmSourceName;
				if ( _currentEASourceFlag  & (int)DalAlarmSourceFlagBitMask::SupplyRailsBitMask)
				{
					alarmSourceName =  GetSupplyRailsAlarmSource();
				}
				else
				{
					alarmSourceName = GetNameofRaisedAlarmFlag();
				}

				if (String::IsNullOrEmpty(alarmSourceName))
				{
					alarmSourceName = Enum::Format(DalAlarmStatusBitMask::typeid, DalAlarmStatusBitMask::NoAlarm, DalFormatterStrings::PrintEnumName);

				}

				return alarmSourceName;
			}

			String^ DalStatusHandler::GetSupplyRailsAlarmSource()
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
						return Enum::Format(DalAlarmSupplyRailFlag::typeid, railAlarmFlag, DalFormatterStrings::PrintEnumName);
					}
					else
					{
						//no error return empty.
						return  String::Empty ;
					}
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
			}

			String ^ DalStatusHandler::GetNameofRaisedAlarmFlag()
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
				//CrxLogger::Instance->Write("CheckCuffStatusFlagsChanged currentflag " + _currentCuffStatusFlag.ToString("X") + " newCuffStatusFlags: " + newCuffStatusFlags.ToString("X"));
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
				//CrxLogger::Instance->Write("CheckAlarmStatusFlagChanged _currentAlarmStatusFlag:" + _currentAlarmStatusFlag.ToString("X4") + " newEAStatusFlag:"+newEAStatusFlag.ToString("X4") );
						
				if (newAlarmStatusFlag != _currentAlarmStatusFlag  )
				{
					//CrxLogger::Instance->Write("CheckAlarmStatusFlagChanged>>>Flags have changed");
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


			//obsolete
			//MapAlarmsourcetoString 
			//String^ DalStatusHandler::MapErrorSourceToString(unsigned long sourceFlags) 
			//{
			//	static DalErrorSource  errorSourceEnum;
			//	errorSourceEnum = safe_cast<DalErrorSource>(sourceFlags);

			//	//CrxLogger::Instance->Write("Deepak>>> MapErrorSourceToString sourceFlags:" + sourceFlags.ToString("X8") + " errorSourceEnum: " + errorSourceEnum.ToString());

			//	try
			//	{
			//		dalErrorAlarmSourceName= String::Empty;

			//		switch( errorSourceEnum)
			//		{
			//			case DalErrorSource::CuffLeak :
			//			case DalErrorSource::DualSensors :
			//				dalErrorAlarmSourceName = Enum::Format(DalErrorSource::typeid, errorSourceEnum, DalFormatterStrings::PrintEnumName);
			//				break;
			//			default:
			//				dalErrorAlarmSourceName = sourceFlags.ToString();
			//				//throw gcnew DalException("DAL_ERR_UNKNOWN_BIT_FLAG");
			//				throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrUnknownBitFlagErrCd,CrxStructCommonResourceMsg::DalErrUnknownBitFlag, ErrorSeverity::Warning );
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
			
			//String^ DalStatusHandler::MapAlarmSourceToString(unsigned long sourceFlags) 
			//{
			//	static DalAlarmSource alarmSourceEnum;
			//	alarmSourceEnum = safe_cast<DalAlarmSource>(sourceFlags);

			//	dalErrorAlarmSourceName= String::Empty;
			//	//CrxLogger::Instance->Write("Deepak>>> MapAlarmSourceToString sourceFlags:" + sourceFlags.ToString("X8"));

			//	try
			//	{
			//		switch( alarmSourceEnum)
			//		{
			//			case DalAlarmSource::CuffLeak :
			//			case DalAlarmSource::DualSensors :
			//			case DalAlarmSource::OverPressure:
			//			case DalAlarmSource::InflatedOverTime:
			//				dalErrorAlarmSourceName = Enum::Format(DalAlarmSource::typeid, alarmSourceEnum, DalFormatterStrings::PrintEnumName);
			//				break;
			//			default:
			//				dalErrorAlarmSourceName = sourceFlags.ToString();
			//				throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrUnknownBitFlagErrCd,CrxStructCommonResourceMsg::DalErrUnknownBitFlag, ErrorSeverity::Warning);
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

		
			DalCuffStateFlags DalStatusHandler::TranslateCuffStatusBits(unsigned long cuffStatusFlags) 
			{
				static DalCuffStateFlags data;
				data = (DalCuffStateFlags)(cuffStatusFlags & (unsigned long)DalStatusFlagBitMask::CuffStatusBitsMask );
	
				switch (data)
				{
					case DalCuffStatusBitMask::CUFF_DISCONNECTED_STATUS_BITS:
						data = DalCuffStateFlags::CUFF_STATE_DISCONNECTED;
						break;
					case DalCuffStatusBitMask::CUFF_INFLATING_STATUS_BITS:
						data = DalCuffStateFlags::CUFF_STATE_INFLATING;
						break;
					case DalCuffStatusBitMask::CUFF_INFLATED_STATUS_BITS:
						data = DalCuffStateFlags::CUFF_STATE_INFLATED;
						break;
					case DalCuffStatusBitMask::CUFF_DEFLATING_STATUS_BITS:
						data = DalCuffStateFlags::CUFF_STATE_DEFLATING;
						break;
					case DalCuffStatusBitMask::CUFF_DEFLATED_STATUS_BITS:
						data = DalCuffStateFlags::CUFF_STATE_DEFLATED;
						break;
					default:
						data = DalCuffStateFlags::CUFF_STATE_UNKNOWN;
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrUnknownBitFlagErrCd,CrxStructCommonResourceMsg::DalErrUnknownBitFlag,ErrorSeverity::Warning);
						break;
				}
				return data;
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
					/*case DalAlarmStatusBitMask::ErrorStatus:
						retAlarmValue = DalErrorAlarmStatusFlag::UnrecoverableStatus;
						break;*/
					
					//TODO: confirm with Victor if Alram status should be marked as recvoerable or not
					case DalAlarmStatusBitMask::AlarmStatus:
						retAlarmValue = DalErrorAlarmStatusFlag::RecoverableStatus;
						break;
					/*case DalAlarmStatusBitMask::ErrorAndAlarmStatus:
						retAlarmValue = DalErrorAlarmStatusFlag::UnrecoverableStatus;
						break;*/
					default:
						retAlarmValue = DalErrorAlarmStatusFlag::UnrecoverableStatus;
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrUnknownBitFlagErrCd,CrxStructCommonResourceMsg::DalErrUnknownBitFlag, ErrorSeverity::Warning);
						break; 
				}

				//CrxLogger::Instance->Write("Deepak>>> TranslateAlarmStatusBits>>> statusFlags" + statusFlags.ToString("X4") + " data:" + data.ToString() + " retAlarmValue:" + retAlarmValue.ToString());
				
				return retAlarmValue;
			}

			String^ DalStatusHandler::ConvertBytesToString(array<unsigned char>^ inputArray)
			{
				String ^ packetData = String::Empty ;

				for each (unsigned char singleByte in inputArray)
				{
					packetData += singleByte.ToString(DalFormatterStrings::PrintByte);
				}

				return packetData;

			}


			bool DalStatusHandler::SaveCaptureData(array< unsigned short >^ tonometerData, array< unsigned short >^ cuffPulse, unsigned short bufferSize)
			{
				
				unsigned short index = 0;
				
				// construct the file path, file contains captured waveform data and of same format
				// as of the simulation file. (capture_DateTime.Dat).
				//String^ tempFilePath = ".\\simulation\\pwv\\";
				//String^ tempFilePath = CrxMessagingManager::Instance->GetMessage("DAL_CONST_SIM_FOLDER_PATH"); //TODO: put this somewhere too
				String^ tempFilePath = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstSimFolderPath); //TODO: put this somewhere too
				//String^ tempCapture = "capture_";
				//String^ tempCapture =  CrxMessagingManager::Instance->GetMessage("DAL_CONST_CAPTURE_FILE_PREFIX"); //TODO
				String^ tempCapture =  CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstCaptureFilePrefix); //TODO
				//String^ tempFileExt = ".dat";
				//String^ tempFileExt = CrxMessagingManager::Instance->GetMessage("DAL_CONST_DAT_FILE_EXTN");
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
			
			String^ DalStatusHandler::GetSavedFileName()
			{
				String^ returnValue = _savedDataFilePath;
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
					ProcessStopButtonBitMask();
					ProcessPowerUpBitMask();

					//check alarms bfore anything else
					ProcessAlarmStatusFlag();
					ProcessCuffStatusFlag();
					ProcessTonoStatusFlag();

					//least important
					ProcessUnusedBitsStatusFlag(statusBytes);
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
					//CrxLogger::Instance->Write("CheckStatusFlagsChanged currentflag " + _currentStatusFlag.ToString("X") + " newStatusFlags: " + newStatusFlag.ToString("X"));
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
				cuffStatusBytes = statusBytes & (unsigned long)DalStatusFlagBitMask::CuffStatusBitsMask;
				
				//Alarm event related bits
				alarmStatusBytes =statusBytes & (unsigned long)DalStatusFlagBitMask::AlarmStatusBitsMask;

				//tonometer related bits
				tonoStatusBytes = statusBytes & (unsigned long) DalStatusFlagBitMask::TonoStatusBitsMask;

				powerUpStatusBytes = statusBytes & (unsigned long) DalStatusFlagBitMask::PowerUpBitMask;
				
				stopButtonStatusBytes = statusBytes & (unsigned long) DalStatusFlagBitMask::StopButtonBitMask;

				unusedStatusBytes = statusBytes & (unsigned long) DalStatusFlagBitMask::UnusedStatusBitsMask;
								
				//CrxLogger::Instance->Write("statusBytes:" + statusBytes.ToString("X4") +" cuffStatusBytes:" + cuffStatusBytes.ToString("X4") + " alarmStatusBytes:"+eaStatusBytes.ToString("X4") ); //debugging only
			}

			 void DalStatusHandler::ProcessCuffStatusFlag()
			{
				if (CheckCuffStatusFlagsChanged(cuffStatusBytes) ==  true)
				{
					currentCuffState = TranslateCuffStatusBits(cuffStatusBytes);//TODO

					//map the status bytes to a state flag
					//	raise a staus change event and update the new flag.
					DalEventContainer::Instance->OnDalCuffStatusEvent(nullptr, gcnew DalCuffStatusEventArgs(currentCuffState));
				}
			}

			void DalStatusHandler::ProcessTonoStatusFlag()
			{

				if (_currentTonoStatusFlag != tonoStatusBytes)
				{
					//assing the new status bytes
					_currentTonoStatusFlag = tonoStatusBytes;

					DalTonometerState tonoState;

					tonoState = (DalTonometerState)(tonoStatusBytes & (unsigned short)DalTonometerStatusBitMask::TonometerNotConnectedBits);
					if (DalTonometerState::Disconnected  == tonoState)
					{
						DalEventContainer::Instance->OnDalTonometerStatusEvent(nullptr, gcnew DalTonometerStatusEventArgs(tonoState));
					}
				}
			}

			void DalStatusHandler::ProcessAlarmStatusFlag()
			{
				 if (CheckAlarmStatusFlagChanged(alarmStatusBytes) == true)
				 {
					 String ^ alarmSource;
					 //Get the source of the alarm
					alarmSource= DalDeviceHandler::Instance->GetAlarmSource();

					 //raise an event only after getting the source of the error
					 DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, gcnew DalModuleErrorAlarmEventArgs(TranslateAlarmStatusBits(alarmStatusBytes), alarmSource));
					 //CrxLogger::Instance->Write("CheckAlarmStatusFlagChanged>>>OnDalModuleErrorAlarmEvent event raised");
				 }
			}

			void DalStatusHandler::ProcessStopButtonBitMask()
			{
				if (stopButtonStatusBytes)
				{
					//If a capture operation is in progress ,
					//it must be stopped
					//DalDeviceHandler::Instance->StopCapture(); //the bit can also be raised during simulation mode
					DalModule::Instance->StopMeasurement();

					String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::StopButtonPressed, DalFormatterStrings::PrintEnumName);
					DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::StopButtonPressed, sourceName);
					DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);

					
				}
			}

			void DalStatusHandler::ProcessPowerUpBitMask()
			{
				if (powerUpStatusBytes)
				{
					//If a capture operation is in progress ,
					//it must be stopped
					//DalDeviceHandler::Instance->StopCapture();
					DalModule::Instance->StopMeasurement();

					String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::PowerUpEvent , DalFormatterStrings::PrintEnumName);
					DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::PowerUpEvent, sourceName);
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


				if (_currentUnusedStatusFlag != unusedStatusBytes)
				{
					//change the current flag
					_currentUnusedStatusFlag = unusedStatusBytes;
					
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
				_currentCuffStatusFlag   = 0;
				_currentTonoStatusFlag = 0;
				_currentStatusFlag = 0;
				_currentUnusedStatusFlag = 0;
				
				//reseting the flag masks to a value which is not used
				cuffStatusBytes = 0xFFFF; 
				alarmStatusBytes = 0xFFFF;
				tonoStatusBytes = 0xFFFF;
				powerUpStatusBytes = 0xFFFF;
				stopButtonStatusBytes = 0xFFFF;
				unusedStatusBytes = 0xFFFF;
			}


		} //End of DataAccess namespace
	}
}
