// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdXUp.pas' rev: 6.00

#ifndef AdXUpHPP
#define AdXUpHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdProtcl.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adxup
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TUploadDialog;
class PASCALIMPLEMENTATION TUploadDialog : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Extctrls::TRadioGroup* Protocols;
	Extctrls::TPanel* Panel1;
	Stdctrls::TLabel* Label1;
	Stdctrls::TEdit* FileMask;
	Stdctrls::TButton* OK;
	Stdctrls::TButton* Cancel;
	void __fastcall OKClick(System::TObject* Sender);
	void __fastcall CancelClick(System::TObject* Sender);
	
public:
	Adprotcl::TProtocolType __fastcall GetProtocol(void);
	void __fastcall SetProtocol(Adprotcl::TProtocolType NewProt);
	AnsiString __fastcall GetMask();
	void __fastcall SetMask(AnsiString NewMask);
	__property Adprotcl::TProtocolType Protocol = {read=GetProtocol, write=SetProtocol, nodefault};
	__property AnsiString Mask = {read=GetMask, write=SetMask};
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TUploadDialog(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TUploadDialog(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TUploadDialog(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TUploadDialog(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TUploadDialog* UploadDialog;

}	/* namespace Adxup */
using namespace Adxup;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdXUp
