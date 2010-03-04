// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdStatE0.pas' rev: 5.00

#ifndef AdStatE0HPP
#define AdStatE0HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdStMach.hpp>	// Pascal unit
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

namespace Adstate0
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfrmConditionEdit;
class PASCALIMPLEMENTATION TfrmConditionEdit : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TButton* Button1;
	Stdctrls::TButton* Button2;
	Stdctrls::TGroupBox* GroupBox2;
	Stdctrls::TLabel* Label6;
	Stdctrls::TLabel* Label7;
	Stdctrls::TLabel* Label8;
	Stdctrls::TEdit* edtCaption;
	Stdctrls::TComboBox* cbxColor;
	Stdctrls::TEdit* edtWidth;
	Stdctrls::TGroupBox* GroupBox3;
	Stdctrls::TLabel* Label1;
	Stdctrls::TLabel* Label2;
	Stdctrls::TLabel* Label3;
	Stdctrls::TLabel* Label5;
	Stdctrls::TLabel* Label4;
	Stdctrls::TLabel* Label9;
	Stdctrls::TEdit* edtStartString;
	Stdctrls::TEdit* edtEndString;
	Stdctrls::TEdit* edtPacketSize;
	Stdctrls::TEdit* edtTimeout;
	Stdctrls::TComboBox* cbxNextState;
	Stdctrls::TCheckBox* chkIgnoreCase;
	Stdctrls::TEdit* edtErrorCode;
	Stdctrls::TLabel* Label12;
	Stdctrls::TCheckBox* DefaultNext;
	Stdctrls::TCheckBox* DefaultError;
	Stdctrls::TEdit* edtOutputOnActivate;
	void __fastcall cbxColorDrawItem(Controls::TWinControl* Control, int Index, const Windows::TRect &Rect
		, Windows::TOwnerDrawState State);
	void __fastcall FormCreate(System::TObject* Sender);
	
private:
	Classes::TStringList* FAvailStates;
	void __fastcall ColorCallback(const AnsiString S);
	void __fastcall SetAvailStates(const Classes::TStringList* Value);
	
public:
	void __fastcall Clear(void);
	void __fastcall SetNextState(AnsiString S);
	HIDESBASE void __fastcall SetColor(AnsiString C);
	__property Classes::TStringList* AvailStates = {read=FAvailStates, write=SetAvailStates};
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TfrmConditionEdit(Classes::TComponent* AOwner) : 
		Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmConditionEdit(Classes::TComponent* AOwner
		, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmConditionEdit(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TfrmConditionEdit(HWND ParentWindow) : Forms::TForm(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TfrmConditionEdit* frmConditionEdit;

}	/* namespace Adstate0 */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Adstate0;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdStatE0
