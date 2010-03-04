// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdFPStat.pas' rev: 6.00

#ifndef AdFPStatHPP
#define AdFPStatHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdFaxPrn.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adfpstat
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TStandardFaxPrinterStatusDisplay;
class PASCALIMPLEMENTATION TStandardFaxPrinterStatusDisplay : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TGroupBox* fpsFaxInfoGroup;
	Stdctrls::TLabel* fpsLabel1;
	Stdctrls::TLabel* fpsLabel2;
	Stdctrls::TLabel* fpsLabel3;
	Stdctrls::TLabel* fpsLabel4;
	Stdctrls::TLabel* fpsFileName;
	Stdctrls::TLabel* fpsTotalPages;
	Stdctrls::TLabel* fpsResolution;
	Stdctrls::TLabel* fpsWidth;
	Stdctrls::TGroupBox* fpsStatusGroup;
	Buttons::TBitBtn* fpsAbortButton;
	Stdctrls::TLabel* fpsStatusLine;
	Stdctrls::TLabel* fpsLabel5;
	Stdctrls::TLabel* fpsLabel6;
	Stdctrls::TLabel* fpsFirstPage;
	Stdctrls::TLabel* fpsLastPage;
	void __fastcall fpsAbortButtonClick(System::TObject* Sender);
	void __fastcall UpdateValues(Adfaxprn::TApdCustomFaxPrinter* FaxStatus);
	
public:
	Adfaxprn::TApdCustomFaxPrinter* FaxPrinter;
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TStandardFaxPrinterStatusDisplay(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TStandardFaxPrinterStatusDisplay(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TStandardFaxPrinterStatusDisplay(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TStandardFaxPrinterStatusDisplay(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TApdFaxPrinterStatus;
class PASCALIMPLEMENTATION TApdFaxPrinterStatus : public Adfaxprn::TApdAbstractFaxPrinterStatus 
{
	typedef Adfaxprn::TApdAbstractFaxPrinterStatus inherited;
	
__published:
	DYNAMIC void __fastcall CreateDisplay(void);
	DYNAMIC void __fastcall DestroyDisplay(void);
	virtual void __fastcall UpdateDisplay(bool First, bool Last);
public:
	#pragma option push -w-inl
	/* TApdAbstractFaxPrinterStatus.Create */ inline __fastcall virtual TApdFaxPrinterStatus(Classes::TComponent* AOwner) : Adfaxprn::TApdAbstractFaxPrinterStatus(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdAbstractFaxPrinterStatus.Destroy */ inline __fastcall virtual ~TApdFaxPrinterStatus(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adfpstat */
using namespace Adfpstat;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdFPStat
