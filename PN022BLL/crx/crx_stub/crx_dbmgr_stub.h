/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	crx_dbmgr_stub.h
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Cross Cutting Database Manager Facade
*/

#pragma once

using namespace System;

namespace CrossCutting {
	
	public ref class CrxDbMgrFacade
	{
	public:
		static CrxDbMgrFacade^ CrxDbMgrFacade::Instance();
		
		// populate class properties from current record
		bool Populate(BizPWV^ PWVObject);
    
		// Store class properties to current record
		bool Store(BizPWV^ PWVObject, bool pRewriteKeyFields, bool pRewriteDate);

	protected:
		CrxDbMgrFacade(void);

	private:
		static CrxDbMgrFacade^ _instance;
	};
}