/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	facade.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Facade Class
*/
#include "stdafx.h"
#include "facade.h"
//?#include "..\measure\measure.h"
#include "..\measure\session.h"

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
//		rm = new ResourceManager("app", Assembly.GetExecutingAssembly());

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
		DalFacade::Instance();
		return false; // temp UT stub
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

		Simulate data capturing for unit  testing
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/
	void BizFacade::SimulateCaptureData()
	{
		DalFacade::Instance()->DispatchCaptureData();
	}
	/**
	FindTonoData

	DESCRIPTION

		Find a tonometer data event in bussines logic context.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		BizTonoDataEvent^ - Handle to tonometer data event in the business logic.
	
	*/
	BizTonoDataEvent^ BizFacade::FindTonoData() 
	{ 
		BizPWV^ measurePWV = (BizPWV^)BizSession::Instance()->measurement;

		return measurePWV->myTonoDataObserver->tonoDataBiz; 
	}
	void BizFacade::SimulateCaptureOneShot()
	{
		DalFacade::Instance()->DispatchCaptureOneShot();
	}
	void BizFacade::DisplayCaptureData() 
	{ 
		BizSession::Instance()->DisplayCaptureData(); 
	}
}