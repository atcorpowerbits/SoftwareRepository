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
	return measurement->DispatchCaptureData();
}
void BizSession::ClearMeasurement(void)
{
	// TBD: Default to PWV but create a measurement object wrt current mode later.
	measurement = gcnew BizPWV;
}
END_BIZ_NAMESPACE
