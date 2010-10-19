/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	session.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Session Class
*/

#pragma once
#include "measure.h"

using namespace System;

namespace Biz {
	public ref class BizSession
	{
	public:
		static BizSession^ BizSession::Instance();
		bool StartCapture();
		bool StopCapture();
		void DispatchCaptureData();
		void ClearMeasurement();
		property BizMeasure^ measurement;
	protected:
		BizSession(void);
	private:
		static BizSession^ _instance;
	};
}