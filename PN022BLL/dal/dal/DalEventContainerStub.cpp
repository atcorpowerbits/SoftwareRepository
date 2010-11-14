#include "Stdafx.h"
#include "dal_stub.h"
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

			DalModuleErrorAlarmEventArgs::DalModuleErrorAlarmEventArgs(unsigned short state, unsigned short source)
			{
				switch (state)
				{
				case DataAccess::NoErrorAlarm:
					this->state = DataAccess::DalConstantsStub::NormalState;
					this->source = "No Error or Alarm";
					break;
				case DataAccess::ErrorState:
					this->state = DataAccess::DalConstantsStub::UnrecoverableState;
					this->source = MapErrorSourceToString(source);
					break;
				case DataAccess::AlarmState:
					this->state = DataAccess::DalConstantsStub::RecoverableState;
					this->source = MapAlarmSourceToString(source);
					break;
				default:
					break;
				}
			}

			String^ DalModuleErrorAlarmEventArgs::MapErrorSourceToString(unsigned short source)
			{
				String^ sourceText;

				// TBD: map to real errors using string resource
				switch (source)
				{
				case 0x0020:
					sourceText = "Dual Sensors Error";
					break;
				case 0x0008:
					sourceText = "Cuff Leak Error";
					break;
				default:
					sourceText = "Module Error Unknown";
					break;
				}
				return sourceText;
			}

			String^ DalModuleErrorAlarmEventArgs::MapAlarmSourceToString(unsigned short source)
			{
				String^ sourceText;

				// TBD: map to real alarms using string resource
				switch (source)
				{
				case 0x0001:
					sourceText = "Over Pressure Alarm";
					break;
				case 0x0004:
					sourceText = "Inflated Over Time";
					break;
				default:
					sourceText = "Module Alarm Unknown";
					break;
				}
				return sourceText;
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
