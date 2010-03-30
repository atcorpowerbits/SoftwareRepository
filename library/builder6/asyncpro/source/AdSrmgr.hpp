// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdSrMgr.pas' rev: 6.00

#ifndef AdSrMgrHPP
#define AdSrMgrHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adsrmgr
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ETpsStringResourceError;
class PASCALIMPLEMENTATION ETpsStringResourceError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ETpsStringResourceError(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETpsStringResourceError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETpsStringResourceError(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETpsStringResourceError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETpsStringResourceError(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETpsStringResourceError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETpsStringResourceError(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETpsStringResourceError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETpsStringResourceError(void) { }
	#pragma option pop
	
};


typedef int TInt32;

struct TIndexRec;
typedef TIndexRec *PIndexRec;

#pragma pack(push, 4)
struct TIndexRec
{
	int id;
	int ofs;
	int len;
} ;
#pragma pack(pop)

typedef TIndexRec TIndexArray[178956969];

struct TResourceRec;
typedef TResourceRec *PResourceRec;

#pragma pack(push, 4)
struct TResourceRec
{
	char id[4];
	int count;
	TIndexRec index[178956969];
} ;
#pragma pack(pop)

class DELPHICLASS TAdStringResource;
class PASCALIMPLEMENTATION TAdStringResource : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	AnsiString operator[](int Ident) { return Strings[Ident]; }
	
private:
	bool FReportError;
	unsigned srHandle;
	TResourceRec *srP;
	void __fastcall srCloseResource(void);
	PIndexRec __fastcall srFindIdent(int Ident);
	void __fastcall srLock(void);
	void __fastcall srLoadResource(unsigned Instance, const AnsiString ResourceName);
	void __fastcall srOpenResource(unsigned Instance, const AnsiString ResourceName);
	void __fastcall srUnLock(void);
	
public:
	__fastcall virtual TAdStringResource(unsigned Instance, const AnsiString ResourceName);
	__fastcall virtual ~TAdStringResource(void);
	void __fastcall ChangeResource(unsigned Instance, const AnsiString ResourceName);
	char * __fastcall GetAsciiZ(int Ident, char * Buffer, int BufChars);
	AnsiString __fastcall GetString(int Ident);
	__property AnsiString Strings[int Ident] = {read=GetString/*, default*/};
	wchar_t * __fastcall GetWideChar(int Ident, wchar_t * Buffer, int BufChars);
	__property bool ReportError = {read=FReportError, write=FReportError, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
static const bool DefReportError = false;
extern PACKAGE char ResID[4];
extern PACKAGE TAdStringResource* TpsResStrings;

}	/* namespace Adsrmgr */
using namespace Adsrmgr;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdSrMgr
