// dal.h

#pragma once

namespace DataAccess {
	public ref class DalConstants
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
		static const unsigned int CONFIG_MAIN_FW_VERSION = 4;

		static const unsigned int DATA_SAMPLING_INTERVAL = 4; // in msec
	};
}

