/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	facade.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Facade
*/

#pragma once
#include <string.h>
#include "..\manager\info.h"

namespace Biz {
	public ref class BizFacade {
	public:
		static BizFacade^ BizFacade::Instance();
		static BizInfo^ GetBizInfo(void);
	protected:
		BizFacade(void);
	private:
		static BizFacade^ _instance;
	};
}