/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      IDalHandler.cpp
        
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
#include "IDalHandler.h"


using namespace System;
using namespace System::Threading;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;

namespace AtCor{
	namespace Scor{
		namespace DataAccess{

			String^ DalStatusHandler::GetErrorAlarmSource()
			{
				static DalModuleErrorAlarmBitMask sourceFlagsEnum;
				sourceFlagsEnum = safe_cast<DalModuleErrorAlarmBitMask>(_currentEAStatusFlag & 0x00000028);
				//CrxLogger::Instance->Write("GetErrorAlarmSource >>>>>>>> _currentEASourceFlag:" + _currentEASourceFlag.ToString("X8") + " sourceFlagsEnum:" + sourceFlagsEnum.ToString()); //Logging only

				dalErrorAlarmSourceName= "";

				switch (sourceFlagsEnum)
				{
					case DalModuleErrorAlarmBitMask::NoErrorAlarm:
						dalErrorAlarmSourceName = Enum::Format(DalModuleErrorAlarmBitMask::typeid, sourceFlagsEnum, "G");
						break;
					case DalModuleErrorAlarmBitMask::ErrorStatus:
						dalErrorAlarmSourceName = MapErrorSourceToString(_currentEASourceFlag  & 0x0000FFFF);
						break;
					case DalModuleErrorAlarmBitMask::AlarmStatus:
						dalErrorAlarmSourceName = MapAlarmSourceToString((_currentEASourceFlag >> 16) & 0x0000FFFF);
						break;
					default:
						dalErrorAlarmSourceName = _currentEASourceFlag.ToString();
						//throw gcnew DalException("DAL_ERR_UNKNOWN_BIT_FLAG");
						throw gcnew ScorException(1007,"DAL_ERR_UNKNOWN_BIT_FLAG", ErrorSeverity::Warning);
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
					dalErrorAlarmSourceName= "";

					switch( errorSourceEnum)
					{
						case DalErrorSource::CuffLeak :
						case DalErrorSource::DualSensors :
							dalErrorAlarmSourceName = Enum::Format(DalErrorSource::typeid, errorSourceEnum, "G");
							break;
						default:
							dalErrorAlarmSourceName = sourceFlags.ToString();
							//throw gcnew DalException("DAL_ERR_UNKNOWN_BIT_FLAG");
							throw gcnew ScorException(1007, "DAL_ERR_UNKNOWN_BIT_FLAG", ErrorSeverity::Warning );
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

				dalErrorAlarmSourceName= "";
				//CrxLogger::Instance->Write("Deepak>>> MapAlarmSourceToString sourceFlags:" + sourceFlags.ToString("X8"));

				try
				{
					switch( alarmSourceEnum)
					{
						case DalAlarmSource::OverPressure:
						case DalAlarmSource::InflatedOverTime:
							dalErrorAlarmSourceName = Enum::Format(DalAlarmSource::typeid, alarmSourceEnum, "G");
							break;
						default:
							dalErrorAlarmSourceName = sourceFlags.ToString();
							//throw gcnew DalException("DAL_ERR_UNKNOWN_BIT_FLAG");
							throw gcnew ScorException(1007,"DAL_ERR_UNKNOWN_BIT_FLAG", ErrorSeverity::Warning);
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
				data = (DalCuffStateFlags)(cuffStatusFlags & 0x2F00);
	
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
						//throw gcnew DalException("DAL_ERR_UNKNOWN_BIT_FLAG");
						throw gcnew ScorException(1007,"DAL_ERR_UNKNOWN_BIT_FLAG", ErrorSeverity::Warning);
						break;
				}
				//CrxLogger::Instance->Write("Deepak>>> TranslateCuffStatusBits, data = " + data.ToString());
				return data;
			}

			DalErrorAlarmStatusFlag DalStatusHandler::TranslateErrorAlarmStatusBits(unsigned long statusFlags)
			{

				static DalModuleErrorAlarmBitMask data;
				static DalErrorAlarmStatusFlag retAlarmValue;

				//This was an error and it has been corrected 0x2F00 > 0x0028
				//data = (DalModuleErrorAlarmBitMask)(statusFlags & 0x2F00);
				data = (DalModuleErrorAlarmBitMask)(statusFlags & 0x0028);
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
						throw gcnew ScorException(1007,"DAL_ERR_UNKNOWN_BIT_FLAG", ErrorSeverity::Warning);
						break; 
				}

				//CrxLogger::Instance->Write("Deepak>>> TranslateErrorAlarmStatusBits>>> statusFlags" + statusFlags.ToString("X4") + " data:" + data.ToString() + " retAlarmValue:" + retAlarmValue.ToString());
				
				return retAlarmValue;
			}
		}
	}
}
