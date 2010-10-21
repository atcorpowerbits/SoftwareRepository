/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	info.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Information
*/

#pragma once
#include <string.h>
#include <biz_namespace.h>

using namespace System;

START_BIZ_NAMESPACE
//	public ref class BizDateFormat: public IFormatProvider
//	{
//	public:
//		virtual Object^ GetFormat( Type^ argType )
//		{
//			return this;
//		}
//	};
	public ref class BizInfo {
	public:
		static BizInfo^ BizInfo::Instance();
		void GetCompanyName(String^ %companyName, unsigned short length);
		void GetVersion(String^ %appVersion, unsigned short length);
		void GetCopyright(String^ %copyRight, unsigned short length);
		void GetModuleType(String^ %moduleType, unsigned short length);
		unsigned short GetModuleConfigID();
		void GetModuleSN(String^ %moduleSN, unsigned short length);
		void GetModuleVersion(String^ %moduleVersion, unsigned short length);
		void GetModuleCalibrationDate(String^ %moduleCalibrationDate, unsigned short length);
		void GetModuleConfigName(String^ %configName, unsigned short length);
		void GetModuleConfigDate(String^ %configDate, unsigned short length);
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
		property unsigned short moduleConfigID;
		property DateTime^ moduleConfigDate;
		static BizInfo^ _instance;
	};
END_BIZ_NAMESPACE
