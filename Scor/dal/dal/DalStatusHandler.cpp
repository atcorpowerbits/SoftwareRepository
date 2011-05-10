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

			String^ DalStatusHandler::GetErrorAlarmSource()
			{
				static DalModuleErrorAlarmBitMask sourceFlagsEnum;
				sourceFlagsEnum = safe_cast<DalModuleErrorAlarmBitMask>(_currentEAStatusFlag & (unsigned long)DalStatusFlagBitMask::ErrorAlarmStatusBitsMask ); //previously 0x00000028
				//CrxLogger::Instance->Write("GetErrorAlarmSource >>>>>>>> _currentEASourceFlag:" + _currentEASourceFlag.ToString("X8") + " sourceFlagsEnum:" + sourceFlagsEnum.ToString()); //Logging only

				dalErrorAlarmSourceName= String::Empty;

				switch (sourceFlagsEnum)
				{
					case DalModuleErrorAlarmBitMask::NoErrorAlarm:
						dalErrorAlarmSourceName = Enum::Format(DalModuleErrorAlarmBitMask::typeid, sourceFlagsEnum, DalFormatterStrings::PrintEnumName);
						break;
					case DalModuleErrorAlarmBitMask::ErrorStatus:
						dalErrorAlarmSourceName = MapErrorSourceToString(_currentEASourceFlag  & (unsigned long)DalStatusFlagBitMask::ErrorAlarmSourceBitMask );
						break;
					case DalModuleErrorAlarmBitMask::AlarmStatus:
						dalErrorAlarmSourceName = MapAlarmSourceToString((_currentEASourceFlag >> 16) & (unsigned long)DalStatusFlagBitMask::ErrorAlarmSourceBitMask);
						break;
					default:
						dalErrorAlarmSourceName = _currentEASourceFlag.ToString();
						//throw gcnew DalException("DAL_ERR_UNKNOWN_BIT_FLAG");
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrUnknownBitFlagErrCd,CrxStructCommonResourceMsg::DalErrUnknownBitFlag, ErrorSeverity::Warning);
						break;
				}
				return dalErrorAlarmSourceName;
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

			bool DalStatusHandler::CheckEAStatusFlagChanged(unsigned long newEAStatusFlag) 
			{
				//CrxLogger::Instance->Write("CheckEAStatusFlagChanged _currentEAStatusFlag:" + _currentEAStatusFlag.ToString("X4") + " newEAStatusFlag:"+newEAStatusFlag.ToString("X4") );
						
				if (newEAStatusFlag != _currentEAStatusFlag  )
				{
					//CrxLogger::Instance->Write("CheckEAStatusFlagChanged>>>Flags have changed");
					//Flags have changed . Assign the new flags 
					_currentEAStatusFlag = newEAStatusFlag;
					return true;
				}
				else
				{
					//no change
					return false;
				}
			}


			String^ DalStatusHandler::MapErrorSourceToString(unsigned long sourceFlags) 
			{
				static DalErrorSource  errorSourceEnum;
				errorSourceEnum = safe_cast<DalErrorSource>(sourceFlags);

				//CrxLogger::Instance->Write("Deepak>>> MapErrorSourceToString sourceFlags:" + sourceFlags.ToString("X8") + " errorSourceEnum: " + errorSourceEnum.ToString());

				try
				{
					dalErrorAlarmSourceName= String::Empty;

					switch( errorSourceEnum)
					{
						case DalErrorSource::CuffLeak :
						case DalErrorSource::DualSensors :
							dalErrorAlarmSourceName = Enum::Format(DalErrorSource::typeid, errorSourceEnum, DalFormatterStrings::PrintEnumName);
							break;
						default:
							dalErrorAlarmSourceName = sourceFlags.ToString();
							//throw gcnew DalException("DAL_ERR_UNKNOWN_BIT_FLAG");
							throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrUnknownBitFlagErrCd,CrxStructCommonResourceMsg::DalErrUnknownBitFlag, ErrorSeverity::Warning );
							break;
					}
				}
				catch(ScorException^ )
				{
					throw;
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

				return dalErrorAlarmSourceName;
			}
			
			String^ DalStatusHandler::MapAlarmSourceToString(unsigned long sourceFlags) 
			{
				static DalAlarmSource alarmSourceEnum;
				alarmSourceEnum = safe_cast<DalAlarmSource>(sourceFlags);

				dalErrorAlarmSourceName= String::Empty;
				//CrxLogger::Instance->Write("Deepak>>> MapAlarmSourceToString sourceFlags:" + sourceFlags.ToString("X8"));

				try
				{
					switch( alarmSourceEnum)
					{
						case DalAlarmSource::OverPressure:
						case DalAlarmSource::InflatedOverTime:
							dalErrorAlarmSourceName = Enum::Format(DalAlarmSource::typeid, alarmSourceEnum, DalFormatterStrings::PrintEnumName);
							break;
						default:
							dalErrorAlarmSourceName = sourceFlags.ToString();
							throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrUnknownBitFlagErrCd,CrxStructCommonResourceMsg::DalErrUnknownBitFlag, ErrorSeverity::Warning);
							break;
					}
				}
				catch(ScorException^ )
				{
					throw;
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

				return dalErrorAlarmSourceName;
			}

		
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

			DalErrorAlarmStatusFlag DalStatusHandler::TranslateErrorAlarmStatusBits(unsigned long statusFlags)
			{

				static DalModuleErrorAlarmBitMask data;
				static DalErrorAlarmStatusFlag retAlarmValue;

				//This was an error and it has been corrected 0x2F00 > 0x0028
				//data = (DalModuleErrorAlarmBitMask)(statusFlags & 0x2F00);
				data = (DalModuleErrorAlarmBitMask)(statusFlags & (unsigned long)DalStatusFlagBitMask::CuffStatusBitsMask);
				//errorAlarmStatusBytes =statusBytes & 0x0028;
				
				switch (data)
				{
					case DalModuleErrorAlarmBitMask::NoErrorAlarm:
						retAlarmValue = DalErrorAlarmStatusFlag::ActiveStatus;
						break;
					case DalModuleErrorAlarmBitMask::ErrorStatus:
						retAlarmValue = DalErrorAlarmStatusFlag::UnrecoverableStatus;
						break;
					case DalModuleErrorAlarmBitMask::AlarmStatus:
						retAlarmValue = DalErrorAlarmStatusFlag::RecoverableStatus;
						break;
					case DalModuleErrorAlarmBitMask::ErrorAndAlarmStatus:
						retAlarmValue = DalErrorAlarmStatusFlag::UnrecoverableStatus;
						break;
					default:
						retAlarmValue = DalErrorAlarmStatusFlag::UnrecoverableStatus;
						//throw gcnew DalException("DAL_ERR_UNKNOWN_BIT_FLAG");
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrUnknownBitFlagErrCd,CrxStructCommonResourceMsg::DalErrUnknownBitFlag, ErrorSeverity::Warning);
						break; 
				}

				//CrxLogger::Instance->Write("Deepak>>> TranslateErrorAlarmStatusBits>>> statusFlags" + statusFlags.ToString("X4") + " data:" + data.ToString() + " retAlarmValue:" + retAlarmValue.ToString());
				
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


		} //End of DataAccess namespace
	}
}
