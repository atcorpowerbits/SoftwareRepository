/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	session.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Session Class
*/

#include "StdAfx.h"
#include "session.h"
#include "measure_pwv.h"

namespace Biz {
	BizSession::BizSession(void)
	{
		// TBD: create a measurement object wrt current mode
		_measurement = gcnew BizPWV;
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
		return _measurement->StartCapture();
	}
}