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
	property BizMeasure^ measurement;
protected:
	BizSession(void);
	property BizElectronicModule^ module;
private:
	static BizSession^ _instance;
	void ClearMeasurement();
};
END_BIZ_NAMESPACE
