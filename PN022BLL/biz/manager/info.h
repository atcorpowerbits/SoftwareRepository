/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	info.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Information
*/

#pragma once
#include <string.h>

using namespace System;

namespace Biz {
	public ref class BizDateFormat: public IFormatProvider
	{
	public:
		virtual Object^ GetFormat( Type^ argType )
		{
			return this;
		}
	};
	public ref class BizInfo {
	public:
		static String^ STR_BIZ_CO_NAME = gcnew String(L"AtCor Medical [THE PRODUCT]");
		static String^ STR_BIZ_VERSION = gcnew String(L"Version 1.0");
		static String^ STR_BIZ_COPYRIGHT = gcnew String(L"Copyright(c)2011 AtCor Medical Pty Ltd. All Rights Reserved.");

		static BizInfo^ BizInfo::Instance();
		void GetCompanyName(String^ %coName, int len);
		void GetVersion(String^ %appVersion, int len);
		void GetCopyright(String^ %copyRight, int len);
		void GetModuleType(String^ %moduleType, int len);
		unsigned short GetModuleCapability();
		void GetModuleSN(String^ %moduleSN, int len);
		void GetModuleVersion(String^ %moduleVersion, int len);
		void GetModuleCalibrationDate(String^ %moduleCalibrationDate, int len);
	protected:
		BizInfo(void);
	private:
		property String^ company;
		property String^ appVersion;
		property String^ copyRight;
		property String^ moduleType;
		property String^ moduleSN;
		property String^ moduleVersion;
		property DateTime^ moduleCalibrationDate;
		unsigned short moduleCapability;
		static BizInfo^ _instance;
	};
}