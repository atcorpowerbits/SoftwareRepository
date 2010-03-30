// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdPackEd.pas' rev: 5.00

#ifndef AdPackEdHPP
#define AdPackEdHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdPacket.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
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

namespace Adpacked
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TPacketEditor;
class PASCALIMPLEMENTATION TPacketEditor : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TGroupBox* GroupBox1;
	Stdctrls::TCheckBox* ChkCharCount;
	Stdctrls::TLabel* Label1;
	Stdctrls::TCheckBox* ChkEndString;
	Stdctrls::TEdit* EdtEndString;
	Stdctrls::TGroupBox* GroupBox2;
	Stdctrls::TRadioButton* rbAnyChar;
	Stdctrls::TRadioButton* rbString;
	Stdctrls::TEdit* EdtStartString;
	Stdctrls::TGroupBox* GroupBox3;
	Stdctrls::TCheckBox* ChkIgnoreCase;
	Stdctrls::TCheckBox* ChkAutoEnable;
	Stdctrls::TLabel* Label5;
	Stdctrls::TLabel* Label6;
	Stdctrls::TCheckBox* ChkIncludeStrings;
	Stdctrls::TCheckBox* ChkEnabled;
	Buttons::TBitBtn* BitBtn1;
	Buttons::TBitBtn* BitBtn2;
	Stdctrls::TEdit* EdtCharCount;
	Stdctrls::TEdit* EdtTimeout;
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TPacketEditor(Classes::TComponent* AOwner) : Forms::TForm(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TPacketEditor(Classes::TComponent* AOwner, int 
		Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TPacketEditor(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TPacketEditor(HWND ParentWindow) : Forms::TForm(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE AnsiString __fastcall CtrlStrToStr(const AnsiString S);
extern PACKAGE AnsiString __fastcall StrToCtrlStr(const AnsiString S);
extern PACKAGE bool __fastcall EditPacket(Adpacket::TApdDataPacket* Packet, const AnsiString Name);

}	/* namespace Adpacked */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Adpacked;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdPackEd
