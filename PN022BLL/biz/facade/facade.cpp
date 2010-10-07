/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	facade.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Facade Class
*/
#include "stdafx.h"
#include <facade.h>
#include <session.h>
#include <measure_pwv.h>

using namespace DataAccess;

namespace Biz {
	/**
	BizFacade

	DESCRIPTION

		Constructor
	
	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/
	BizFacade::BizFacade(void)
	{
	}
	/**
	Instance

	DESCRIPTION

		Get the BizFacade singleton instance.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		BizFacade^ - Handle to BizFacade object
	
	*/
	BizFacade^ BizFacade::Instance()
	{
		if (_instance == nullptr) 
		{
			_instance = gcnew BizFacade;
		}
		return _instance;
	}
	/**
	FindBizInfo

	DESCRIPTION

		Find the object that contains business logic layer information.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		BizInfo^ - Handle to BizInfo object.
	
	*/
	BizInfo^ BizFacade::FindBizInfo()
	{
		return BizInfo::Instance();
	}
	/**
	StartCapture

	DESCRIPTION

		Start capturing data in current measurement mode.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		true - Data capture started successfully
	
		false - Data capture failed to start
	
	*/
	bool BizFacade::StartCapture(void)
	{
		return BizSession::Instance()->StartCapture();
	}
	/**
	StopCapture

	DESCRIPTION

		Stop capturing data in current measurement mode.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		true - Data capture stopped successfully
	
		false - Data capture failed to stop
	
	*/
	bool BizFacade::StopCapture(void)
	{
		return BizSession::Instance()->StopCapture();
	}
	/**
	CalculateReport

	DESCRIPTION

		Calculate a report for the current measurement.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		true - Measurement report is calculated successfully
	
		false - Measurement report failed to calculate
	
	*/
	bool BizFacade::CalculateReport(void)
	{
		return false; // temp UT stub
	}
	/**
	SimulateCaptureData

	DESCRIPTION

		Simulate data capturing for testing.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/
	void BizFacade::SimulateCaptureData()
	{
		DalFacade::Instance()->SimulateCaptureData();
	}
	/**
	StopSimulation

	DESCRIPTION

		Stop simulation of data capturing.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/
	void BizFacade::StopCaptureSimulation(void)
	{
		return DalFacade::Instance()->StopCaptureSimulation();
	}
	/**
	FindTonometerData

	DESCRIPTION

		Find a tonometer data event in bussines logic context.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		BizTonometerDataEvent^ - Handle to tonometer data event in the business logic.
	
	*/
	BizTonometerDataEvent^ BizFacade::FindTonometerDataEvent() 
	{ 
		BizPWV^ measurePWV = (BizPWV^)BizSession::Instance()->measurement;

		return measurePWV->myTonometerDataObserver->tonometerDataBiz; 
	}
	/**
	FindCuffPulse

	DESCRIPTION

		Find a cuff pulse data event in business logic context.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		BizCuffPulseEvent^ - Handle to cuff pulse data event in the business logic.
	
	*/
	BizCuffPulseEvent^ BizFacade::FindCuffPulseEvent() 
	{ 
		BizPWV^ measurePWV = (BizPWV^)BizSession::Instance()->measurement;

		return measurePWV->myCuffPulseObserver->cuffPulseBiz; 
	}
	/**
	FindCountdown

	DESCRIPTION

		Find a countdown data event in business logic context.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		BizCountdownEvent^ - Handle to countdown data event in the business logic.
	
	*/
	BizCountdownEvent^ BizFacade::FindCountdownEvent() 
	{ 
		BizPWV^ measurePWV = (BizPWV^)BizSession::Instance()->measurement;

		return measurePWV->myCountdownObserver->countdownBiz; 
	}
	/**
	SimulateCaptureOneShot

	DESCRIPTION

		Trigger one capture data event for testing.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/
	void BizFacade::SimulateCaptureOneShot()
	{
		DalFacade::Instance()->SimulateCaptureOneShot();
	}
	/**
	DispatchCaptureData

	DESCRIPTION

		Dispatch data captured in business logic for current measurement mode.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/
	void BizFacade::DispatchCaptureData() 
	{ 
		BizSession::Instance()->DispatchCaptureData(); 
	}
	/**
	SimulateDeflationTimer

	DESCRIPTION

		Simulate cuff deflation count down timer.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/
	void BizFacade::SimulateDeflationTimer()
	{
		DalFacade::Instance()->SimulateDeflationTimer();
	}
	/**
	StopDeflationTimerSimulation

	DESCRIPTION

		Stop simulation of cuff deflation count down timer.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/
	void BizFacade::StopDeflationTimerSimulation(void)
	{
		return DalFacade::Instance()->StopDeflationTimerSimulation();
	}
}