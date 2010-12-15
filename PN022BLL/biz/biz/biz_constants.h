// biz_constants.h

#pragma once

#include <biz_namespace.h>

using namespace System;

START_BIZ_NAMESPACE

public ref class BizConstants
{
public:

	static const unsigned short DEFAULT_VALUE = 9999;					// Default value for properties
	static const float DEFAULT_FLOAT_VALUE = (float) -1;				// Default value for properties

	static const unsigned short CAPTURE_EXTRA_FOR_HANDSHAKE = 2;		// Time delay to allow the user to release the tonometer and press Okay

	static const DateTime PATIENT_INITIAL_DATE = DateTime(1900,1,1);	// Initial Date of Birth is 1/1/1900

	static const unsigned short MINIMUM_REFERENCE_RANGE_PWV	= 2;
	static const unsigned short MAXIMUM_REFERENCE_RANGE_PWV	= 17;
	static const unsigned short MINIMUM_REFERENCE_RANGE_AGE	= 20;
	static const unsigned short MAXIMUM_REFERENCE_RANGE_AGE	= 90;
	static const unsigned short NUMBER_OF_REFERENCE_RANGES	= MAXIMUM_REFERENCE_RANGE_AGE - MINIMUM_REFERENCE_RANGE_AGE + 1;

};

END_BIZ_NAMESPACE
