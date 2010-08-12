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
	BizFacade::BizFacade(void)
	{
//		rm = new ResourceManager("app", Assembly.GetExecutingAssembly());
	}
	BizFacade^ BizFacade::Instance()
	{
		if (_instance == nullptr) 
		{
			_instance = gcnew BizFacade;
		}
		return _instance;
	}
	BizInfo^ BizFacade::GetBizInfo(void)
	{
		return BizInfo::Instance();
	}
	bool BizFacade::StartCapture(void)
	{
		return BizSession::Instance()->StartCapture();
	}
	bool BizFacade::StopCapture(void)
	{
		return false; // temp UT stub
	}
	bool BizFacade::CalculateReport(void)
	{
		return false; // temp UT stub
	}
	void BizFacade::SimulateCaptureData()
	{
		DalFacade::Instance()->DispatchCaptureData();
	}
}