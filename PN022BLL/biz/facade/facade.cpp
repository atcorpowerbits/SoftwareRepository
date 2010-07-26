/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	facade.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Facade Class
*/
#include "stdafx.h"
#include "facade.h"

namespace Biz {
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

	BizFacade::BizFacade(void)
	{
	//	rm = new ResourceManager("app", Assembly.GetExecutingAssembly());
	}
}