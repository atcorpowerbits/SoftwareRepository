/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	crx_export_stub.h
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Cross Cutting Export Facade
*/

#pragma once

using namespace System;

namespace CrossCutting {
	
	public ref class CrxExportFacade
	{
	public:
		static CrxExportFacade^ CrxExportFacade::Instance();
		
		// Export class properties from current record
		bool Export(BizPWV^ PWVObject);

		// Export class property titles (usually from the database column titles)
		bool ExportPrintTitle(DataSet dataSet);

	protected:
		CrxExportFacade(void);

	private:
		static CrxExportFacade^ _instance;
	};
}