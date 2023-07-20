/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	facade.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Facade
*/

#pragma once
#include <string.h>
#include <info.h>
#include <data_events.h>
#include <biz_namespace.h>

START_BIZ_NAMESPACE

// A singleton to interface Business Logic Layer
public ref class BizFacade {
public:
	static BizFacade^ BizFacade::Instance();
	BizInfo^ FindBizInfo();
	bool StartCapture();
	bool StopCapture();
	void SimulateCaptureData();
	void StopCaptureSimulation();
	void SimulateCaptureOneShot(); // simulate a single data capture
	void Dispatch();
	bool CalculateReport();
	BizTonometerDataEvent^ FindTonometerDataEvent();
	BizCuffPulseEvent^ FindCuffPulseEvent();
	BizCountdownTimerEvent^ FindCountdownTimerEvent();
	BizCuffStateEvent^ FindCuffStateEvent();

protected:
	BizFacade(void);

private:
	static BizFacade^ _instance;
};

END_BIZ_NAMESPACE
