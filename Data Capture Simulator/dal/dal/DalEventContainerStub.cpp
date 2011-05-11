#include "Stdafx.h"
#include "DalEventContainerStub.h"

using namespace AtCor::Scor::DataAccess;

namespace AtCor{
	namespace Scor{
		namespace DataAccess{

			DalCountdownTimerEventArgs::DalCountdownTimerEventArgs(unsigned short data)
			{
				this->data = data;
			}

			DalCuffStatusEventArgs::DalCuffStatusEventArgs(unsigned short data)
			{
				switch (data)
				{
				case DalConstantsStub::CUFF_DISCONNECTED_STATUS_BITS:
					this->data = DalConstantsStub::CUFF_STATE_DISCONNECTED;
					break;
				case DalConstantsStub::CUFF_INFLATING_STATUS_BITS:
					this->data = DalConstantsStub::CUFF_STATE_INFLATING;
					break;
				case DalConstantsStub::CUFF_INFLATED_STATUS_BITS:
					this->data = DalConstantsStub::CUFF_STATE_INFLATED;
					break;
				case DalConstantsStub::CUFF_DEFLATING_STATUS_BITS:
					this->data = DalConstantsStub::CUFF_STATE_DEFLATING;
					break;
				case DalConstantsStub::CUFF_DEFLATED_STATUS_BITS:
					this->data = DalConstantsStub::CUFF_STATE_DEFLATED;
					break;
				default:
					this->data = 0;
					break;
				}
			}

			DalModuleErrorAlarmEventArgs::DalModuleErrorAlarmEventArgs(unsigned short state)
			{
				switch (state)
				{
				case DataAccess::NoErrorAlarm:
					this->errorAlarmStatus = DataAccess::DalConstantsStub::ActiveStatus;
//					this->source = "No Error or Alarm";
					break;
				case DataAccess::ErrorStatus:
					this->errorAlarmStatus = DataAccess::DalConstantsStub::UnrecoverableStatus;
//					this->source = MapErrorSourceToString((source >> 16) && 0xFFFF);
					break;
				case DataAccess::AlarmStatus:
					this->errorAlarmStatus = DataAccess::DalConstantsStub::RecoverableStatus;
//					this->source = MapAlarmSourceToString(source && 0x0000FFFF);
					break;
				default:
					break;
				}
			}

			DalEventContainerStub::DalEventContainerStub()
			{
			}

			DalEventContainerStub::DalEventContainerStub(const DalEventContainerStub^)
			{
			}

			DalEventContainerStub^ DalEventContainerStub::operator = (const DalEventContainerStub)
			{
				return this;
			}

		}
	}
}
