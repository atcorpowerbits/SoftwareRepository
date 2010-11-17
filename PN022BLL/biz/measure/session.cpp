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
BizSession::BizSession(void)
{
	// TBD: create a measurement object wrt current mode
	measurement = gcnew BizPWV;

	// aggregate the BizElectronicModule object in BizSession
	module = gcnew BizElectronicModule;
}
BizSession^ BizSession::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew BizSession;
	}
	return _instance;
}
bool BizSession::StartCapture(void)
{
	//TBD: check if a measurement can start
	return measurement->StartCapture();
}
bool BizSession::StopCapture(void)
{
	//TBD: check if a measurement can stop
	return measurement->StopCapture();
}
void BizSession::DispatchCaptureData(void)
{
	module->Dispatch(); // dispatch any alarm, error from the electronic module
	measurement->DispatchCaptureData();
}
void BizSession::ClearMeasurement(void)
{
	// TBD: Default to PWV but create a measurement object wrt current mode later.
	measurement = gcnew BizPWV;
}
END_BIZ_NAMESPACE
