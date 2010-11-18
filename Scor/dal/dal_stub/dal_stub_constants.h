// dal_stub_constants.h

#pragma once

using namespace System;

namespace AtCor{ 
namespace Scor { 
namespace DataAccess{

	public ref class DalConstantsStub
	{
	public:
		static const unsigned int DATA_TONOMETER = 1;
		static const unsigned int DATA_CUFF_PULSE_COMBO = 2;
		static const unsigned int DATA_TONOMETER_AND_CUFF_PULSE_COMBO = 3;
		static const unsigned int DATA_CUFF_ABS_PRESSURE = 4;
		static const unsigned int DATA_CUFF_NIBP = 5;
		static const unsigned int DATA_CUFF_PULSE = 6;

		static const unsigned int CONFIG_MODULE_TYPE = 1;
		static const unsigned int CONFIG_MODULE_CAPABILITY = 2;
		static const unsigned int CONFIG_MODULE_SN = 3;
		static const unsigned int CONFIG_MODULE_MAIN_FW_VERSION = 4;
		static const unsigned int CONFIG_MODULE_CALIBRATION_DATE = 5;

		static const unsigned int CUFF_STATE_DISCONNECTED = 1;
		static const unsigned int CUFF_STATE_DEFLATED = 2;
		static const unsigned int CUFF_STATE_INFLATING = 3;
		static const unsigned int CUFF_STATE_INFLATED = 4;
		static const unsigned int CUFF_STATE_DEFLATING = 5;

		static const unsigned int CUFF_DISCONNECTED_STATUS_BITS = 0x2000; //00100000;
		static const unsigned int CUFF_DEFLATED_STATUS_BITS     = 0x0100; //00000001;
		static const unsigned int CUFF_INFLATING_STATUS_BITS    = 0x0400; //00000100;
		static const unsigned int CUFF_INFLATED_STATUS_BITS     = 0x0900; //00001001;
		static const unsigned int CUFF_DEFLATING_STATUS_BITS    = 0x0200; //00000010;

		static unsigned int const ActiveStatus = 0;
		static unsigned int const RecoverableStatus = 1;
		static const unsigned int UnrecoverableStatus = 2;

#if 1 // Why can't these be used as case expression constant
		static unsigned short NoErrorAlarm = 0x0000; //0
		static unsigned short ErrorStatus = 0x0020;   //32
		static unsigned short AlarmStatus = 0x0008;   //8
		static unsigned short ErrorAndAlarmStatus = 0x0028; // 40
#endif
	};
}}}
