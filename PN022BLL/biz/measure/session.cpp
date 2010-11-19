/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	session.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Session Class
*/

#include "StdAfx.h"
#include <session.h>
#include <measure_pwv.h>
#include <biz_namespace.h>

START_BIZ_NAMESPACE
/**
BizSession

DESCRIPTION

	Constructor where BizMeasure and BizElectronicModule clients are aggregated.

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/		
BizSession::BizSession(void)
{
	// TBD: create a measurement object wrt current mode
	measurement = gcnew BizPWV;

	// aggregate the BizElectronicModule object in BizSession
	module = gcnew BizElectronicModule;
}
/**
Instance

DESCRIPTION

	Singleton BizSession instance.

INPUT

	None.

OUTPUT

	None.

RETURN

	Handle to BizSession object.

*/		
BizSession^ BizSession::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew BizSession;
	}
	return _instance;
}
/**
StartCapture

DESCRIPTION

	Start capturing data for the measurement.

INPUT

	None.

OUTPUT

	None.

RETURN

	true  - Start capture is successful.

	false - Start capture failed.

*/		
bool BizSession::StartCapture(void)
{
	//TBD: check if a measurement can start
	return measurement->StartCapture();
}
/**
StopCapture

DESCRIPTION

	Stop capturing data for the measurement.

INPUT

	None.

OUTPUT

	None.

RETURN

	true  - Stop capture is successful.

	false - Stop capture failed.

*/		
bool BizSession::StopCapture(void)
{
	//TBD: check if a measurement can stop
	return measurement->StopCapture();
}
/**
DispatchCaptureData

DESCRIPTION

	Dispatch module status first to see any alarm or error.
	Then dispatch captured data so far for the measurement.

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/		
void BizSession::DispatchCaptureData(void)
{
	module->Dispatch(); // dispatch any alarm, error from the electronic module
	measurement->DispatchCaptureData();
}
/**
ClearMeasurement

DESCRIPTION

	Clear the current measurement.

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/		
void BizSession::ClearMeasurement(void)
{
	// TBD: Default to PWV but create a measurement object wrt current mode later.
	measurement = gcnew BizPWV;
}
END_BIZ_NAMESPACE
