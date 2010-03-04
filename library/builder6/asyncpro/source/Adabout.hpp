// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdAbout.pas' rev: 5.00

#ifndef AdAboutHPP
#define AdAboutHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ShellAPI.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
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

namespace Adabout
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TApdAboutForm;
class PASCALIMPLEMENTATION TApdAboutForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Extctrls::TPanel* Panel1;
	Extctrls::TBevel* Bevel2;
	Extctrls::TImage* Image1;
	Stdctrls::TLabel* Label1;
	Stdctrls::TLabel* Label2;
	Stdctrls::TLabel* Label11;
	Stdctrls::TLabel* Label12;
	Stdctrls::TButton* Button1;
	Stdctrls::TLabel* Label3;
	Stdctrls::TLabel* Label9;
	Stdctrls::TLabel* Label10;
	Stdctrls::TLabel* Label13;
	Stdctrls::TLabel* Label14;
	Stdctrls::TLabel* Label15;
	Stdctrls::TLabel* Label4;
	Stdctrls::TLabel* Label6;
	Stdctrls::TLabel* Label5;
	Stdctrls::TLabel* Label7;
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall Label6Click(System::TObject* Sender);
	void __fastcall Label5MouseDown(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState 
		Shift, int X, int Y);
	void __fastcall Label5MouseUp(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState 
		Shift, int X, int Y);
	void __fastcall Label9Click(System::TObject* Sender);
	void __fastcall Label13Click(System::TObject* Sender);
	void __fastcall Label7Click(System::TObject* Sender);
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TApdAboutForm(Classes::TComponent* AOwner) : Forms::TForm(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TApdAboutForm(Classes::TComponent* AOwner, int 
		Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TApdAboutForm(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TApdAboutForm(HWND ParentWindow) : Forms::TForm(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TApdAboutForm* ApdAboutForm;

}	/* namespace Adabout */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Adabout;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdAbout
