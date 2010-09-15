// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdRStat.pas' rev: 6.00

#ifndef AdRStatHPP
#define AdRStatHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ExtCtrls.hpp>	// Pascal unit
#include <AdRas.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adrstat
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TRasStatusDisplay;
class PASCALIMPLEMENTATION TRasStatusDisplay : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TButton* CancelBtn;
	Extctrls::TPanel* Panel1;
	void __fastcall CancelBtnClick(System::TObject* Sender);
	
public:
	Adras::TApdCustomRasDialer* RasDialer;
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TRasStatusDisplay(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TRasStatusDisplay(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TRasStatusDisplay(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TRasStatusDisplay(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TApdRasStatus;
class PASCALIMPLEMENTATION TApdRasStatus : public Adras::TApdAbstractRasStatus 
{
	typedef Adras::TApdAbstractRasStatus inherited;
	
protected:
	HWND FHandle;
	void __fastcall CMRasStatus(Messages::TMessage &Msg);
	
public:
	__fastcall virtual TApdRasStatus(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdRasStatus(void);
	DYNAMIC void __fastcall CreateDisplay(const AnsiString EntryName);
	DYNAMIC void __fastcall DestroyDisplay(void);
	virtual void __fastcall UpdateDisplay(const AnsiString StatusMsg);
	__property HWND Handle = {read=FHandle, write=FHandle, nodefault};
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adrstat */
using namespace Adrstat;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdRStat
