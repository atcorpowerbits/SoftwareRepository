/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	session.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Session Class
*/

#pragma once
#include <measure.h>
#include <electronic_module.h>
#include <biz_namespace.h>

using namespace System;

START_BIZ_NAMESPACE
public ref class BizSession
{
public:
	static BizSession^ BizSession::Instance();
	bool StartCapture();
	bool StopCapture();
	void DispatchCaptureData();
	void ClearMeasurement();
	property BizMeasure^ measurement;
	property BizElectronicModule^ module;
protected:
	BizSession(void);
private:
	static BizSession^ _instance;
};
END_BIZ_NAMESPACE
