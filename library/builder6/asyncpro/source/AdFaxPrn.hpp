// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdFaxPrn.pas' rev: 6.00

#ifndef AdFaxPrnHPP
#define AdFaxPrnHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdFaxCvt.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Printers.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adfaxprn
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TFaxPLCode { lcStart, lcFinish, lcAborted, lcFailed };
#pragma option pop

#pragma option push -b-
enum TFaxPrintScale { psNone, psFitToPage };
#pragma option pop

#pragma option push -b-
enum TFaxPrintProgress { ppIdle, ppComposing, ppRendering, ppSubmitting, ppConverting };
#pragma option pop

typedef void __fastcall (__closure *TFaxPrnNextPageEvent)(System::TObject* Sender, Word CP, Word TP);

typedef void __fastcall (__closure *TFaxPLEvent)(System::TObject* Sender, TFaxPLCode FaxPLCode);

typedef void __fastcall (__closure *TFaxPrintStatusEvent)(System::TObject* Sender, TFaxPrintProgress StatusCode);

class DELPHICLASS TApdCustomFaxPrinterLog;
class DELPHICLASS TApdCustomFaxPrinter;
class DELPHICLASS TApdAbstractFaxPrinterStatus;
class PASCALIMPLEMENTATION TApdAbstractFaxPrinterStatus : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	Forms::TForm* FDisplay;
	Forms::TPosition FPosition;
	bool FCtl3D;
	bool FVisible;
	AnsiString FCaption;
	TApdCustomFaxPrinter* FFaxPrinter;
	void __fastcall SetPosition(const Forms::TPosition Value);
	void __fastcall SetCtl3D(const bool Value);
	void __fastcall SetVisible(const bool Value);
	void __fastcall SetCaption(const AnsiString Value);
	void __fastcall GetProperties(void);
	void __fastcall Show(void);
	
public:
	__fastcall virtual TApdAbstractFaxPrinterStatus(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdAbstractFaxPrinterStatus(void);
	virtual void __fastcall UpdateDisplay(bool First, bool Last) = 0 ;
	DYNAMIC void __fastcall CreateDisplay(void) = 0 ;
	DYNAMIC void __fastcall DestroyDisplay(void) = 0 ;
	__property Forms::TForm* Display = {read=FDisplay, write=FDisplay};
	__property TApdCustomFaxPrinter* FaxPrinter = {read=FFaxPrinter};
	
__published:
	__property Forms::TPosition Position = {read=FPosition, write=SetPosition, nodefault};
	__property bool Ctl3D = {read=FCtl3D, write=SetCtl3D, nodefault};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
	__property AnsiString Caption = {read=FCaption, write=SetCaption};
};


class DELPHICLASS TApdFaxPrinterLog;
class PASCALIMPLEMENTATION TApdCustomFaxPrinterLog : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	TApdCustomFaxPrinter* FFaxPrinter;
	AnsiString FLogFileName;
	
public:
	__fastcall virtual TApdCustomFaxPrinterLog(Classes::TComponent* AOwner);
	void __fastcall UpdateLog(const TFaxPLCode LogCode);
	__property TApdCustomFaxPrinter* FaxPrinter = {read=FFaxPrinter};
	__property AnsiString LogFileName = {read=FLogFileName, write=FLogFileName};
public:
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TApdCustomFaxPrinterLog(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TApdFaxPrinterLog : public TApdCustomFaxPrinterLog 
{
	typedef TApdCustomFaxPrinterLog inherited;
	
__published:
	__property LogFileName ;
public:
	#pragma option push -w-inl
	/* TApdCustomFaxPrinterLog.Create */ inline __fastcall virtual TApdFaxPrinterLog(Classes::TComponent* AOwner) : TApdCustomFaxPrinterLog(AOwner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TApdFaxPrinterLog(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdFaxPrinterMargin;
class DELPHICLASS TApdCustomFaxPrinterMargin;
class PASCALIMPLEMENTATION TApdCustomFaxPrinterMargin : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
protected:
	AnsiString FCaption;
	bool FEnabled;
	Graphics::TFont* FFont;
	Word FHeight;
	
public:
	__fastcall virtual TApdCustomFaxPrinterMargin(void);
	__fastcall virtual ~TApdCustomFaxPrinterMargin(void);
	void __fastcall SetFont(const Graphics::TFont* NewFont);
	__property AnsiString Caption = {read=FCaption, write=FCaption};
	__property bool Enabled = {read=FEnabled, write=FEnabled, nodefault};
	__property Graphics::TFont* Font = {read=FFont, write=SetFont};
	__property Word Height = {read=FHeight, write=FHeight, default=0};
};


class PASCALIMPLEMENTATION TApdFaxPrinterMargin : public TApdCustomFaxPrinterMargin 
{
	typedef TApdCustomFaxPrinterMargin inherited;
	
__published:
	__property Caption ;
	__property Enabled ;
	__property Font ;
public:
	#pragma option push -w-inl
	/* TApdCustomFaxPrinterMargin.Create */ inline __fastcall virtual TApdFaxPrinterMargin(void) : TApdCustomFaxPrinterMargin() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomFaxPrinterMargin.Destroy */ inline __fastcall virtual ~TApdFaxPrinterMargin(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TApdCustomFaxPrinter : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
public:
	AnsiString FFileName;
	Word FTotalFaxPages;
	Word FCurrentPrintingPage;
	Word FFirstPageToPrint;
	Word FLastPageToPrint;
	Adfaxcvt::TFaxResolution FFaxResolution;
	Adfaxcvt::TFaxWidth FFaxWidth;
	TFaxPrintScale FPrintScale;
	bool FMultiPage;
	TApdAbstractFaxPrinterStatus* FStatusDisplay;
	TFaxPrintProgress FFaxPrintProgress;
	TApdFaxPrinterLog* FFaxPrinterLog;
	Dialogs::TPrintDialog* FPrintDialog;
	Adfaxcvt::TApdFaxUnpacker* FFaxUnpack;
	TApdFaxPrinterMargin* FFaxHeader;
	TApdFaxPrinterMargin* FFaxFooter;
	TFaxPrnNextPageEvent FOnNextPage;
	TFaxPLEvent FOnFaxPrintLog;
	TFaxPrintStatusEvent FOnFaxPrintStatus;
	
protected:
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	void __fastcall SetCaption(const AnsiString Value);
	AnsiString __fastcall GetCaption();
	void __fastcall SetFaxFileName(const AnsiString Value);
	void __fastcall SetStatusDisplay(const TApdAbstractFaxPrinterStatus* Value);
	void __fastcall SetFaxPrintLog(const TApdFaxPrinterLog* Value);
	AnsiString __fastcall ReplaceHFParams(AnsiString Value, Word Page);
	virtual void __fastcall CreateFaxHeader(Graphics::TCanvas* FaxCanvas, Word PN, Types::TRect &AreaRect);
	virtual void __fastcall CreateFaxFooter(Graphics::TCanvas* FaxCanvas, Word PN, Types::TRect &AreaRect);
	void __fastcall SetFaxPrintProgress(const TFaxPrintProgress NewProgress);
	void __fastcall FaxPrintLog(TFaxPLCode LogCode);
	
public:
	__fastcall virtual TApdCustomFaxPrinter(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomFaxPrinter(void);
	bool __fastcall PrintSetup(void);
	void __fastcall PrintFax(void);
	void __fastcall PrintAbort(void);
	__property Adfaxcvt::TFaxWidth FaxWidth = {read=FFaxWidth, default=0};
	__property Adfaxcvt::TFaxResolution FaxResolution = {read=FFaxResolution, default=0};
	__property Word TotalFaxPages = {read=FTotalFaxPages, default=0};
	__property Word CurrentPrintingPage = {read=FCurrentPrintingPage, default=0};
	__property Word FirstPageToPrint = {read=FFirstPageToPrint, write=FFirstPageToPrint, default=0};
	__property Word LastPageToPrint = {read=FLastPageToPrint, write=FLastPageToPrint, default=0};
	__property TFaxPrintProgress PrintProgress = {read=FFaxPrintProgress, write=FFaxPrintProgress, nodefault};
	__property AnsiString Caption = {read=GetCaption, write=SetCaption};
	__property TApdFaxPrinterMargin* FaxFooter = {read=FFaxFooter, write=FFaxFooter};
	__property TApdFaxPrinterMargin* FaxHeader = {read=FFaxHeader, write=FFaxHeader};
	__property TApdFaxPrinterLog* FaxPrinterLog = {read=FFaxPrinterLog, write=SetFaxPrintLog};
	__property AnsiString FileName = {read=FFileName, write=SetFaxFileName};
	__property bool MultiPage = {read=FMultiPage, write=FMultiPage, nodefault};
	__property TFaxPrintScale PrintScale = {read=FPrintScale, write=FPrintScale, default=1};
	__property TApdAbstractFaxPrinterStatus* StatusDisplay = {read=FStatusDisplay, write=SetStatusDisplay};
	__property TFaxPrnNextPageEvent OnNextPage = {read=FOnNextPage, write=FOnNextPage};
	__property TFaxPLEvent OnFaxPrintLog = {read=FOnFaxPrintLog, write=FOnFaxPrintLog};
	__property TFaxPrintStatusEvent OnFaxPrintStatus = {read=FOnFaxPrintStatus, write=FOnFaxPrintStatus};
};



class DELPHICLASS TApdFaxPrinter;
class PASCALIMPLEMENTATION TApdFaxPrinter : public TApdCustomFaxPrinter 
{
	typedef TApdCustomFaxPrinter inherited;
	
__published:
	__property Caption ;
	__property FaxFooter ;
	__property FaxHeader ;
	__property FaxPrinterLog ;
	__property FileName ;
	__property MultiPage ;
	__property PrintScale  = {default=1};
	__property StatusDisplay ;
	__property OnNextPage ;
	__property OnFaxPrintLog ;
	__property OnFaxPrintStatus ;
public:
	#pragma option push -w-inl
	/* TApdCustomFaxPrinter.Create */ inline __fastcall virtual TApdFaxPrinter(Classes::TComponent* AOwner) : TApdCustomFaxPrinter(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomFaxPrinter.Destroy */ inline __fastcall virtual ~TApdFaxPrinter(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define afpDefFPLFileName "FAXPRINT.LOG"
#define afpDefFaxHeaderCaption "FILE: $F"
static const bool afpDefFaxHeaderEnabled = true;
#define afpDefFaxFooterCaption "PAGE: $P of $N"
static const bool afpDefFaxFooterEnabled = true;
#define afpDefFaxPrnCaption "APro Fax Printer"
#define afpDefFaxPrintScale (TFaxPrintScale)(1)
static const bool afpDefFaxMultiPage = false;

}	/* namespace Adfaxprn */
using namespace Adfaxprn;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdFaxPrn
