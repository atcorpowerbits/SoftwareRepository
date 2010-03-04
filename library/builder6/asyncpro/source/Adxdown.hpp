// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdXDown.pas' rev: 6.00

#ifndef AdXDownHPP
#define AdXDownHPP

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

namespace Adxdown
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TDownloadDialog;
class PASCALIMPLEMENTATION TDownloadDialog : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Extctrls::TPanel* Panel1;
	Stdctrls::TLabel* DestDirLabel;
	Stdctrls::TEdit* Directory;
	Stdctrls::TLabel* FileNameLabel;
	Stdctrls::TEdit* FileName;
	Extctrls::TRadioGroup* Protocols;
	Stdctrls::TButton* OK;
	Stdctrls::TButton* Cancel;
	void __fastcall OKClick(System::TObject* Sender);
	void __fastcall CancelClick(System::TObject* Sender);
	void __fastcall ProtocolsClick(System::TObject* Sender);
	
public:
	AnsiString __fastcall GetDestDirectory();
	void __fastcall SetDestDirectory(AnsiString NewDir);
	AnsiString __fastcall GetReceiveName();
	void __fastcall SetReceiveName(AnsiString NewName);
	Adprotcl::TProtocolType __fastcall GetProtocol(void);
	void __fastcall SetProtocol(Adprotcl::TProtocolType NewProt);
	__property AnsiString DestDirectory = {read=GetDestDirectory, write=SetDestDirectory};
	__property AnsiString ReceiveName = {read=GetReceiveName, write=SetReceiveName};
	__property Adprotcl::TProtocolType Protocol = {read=GetProtocol, write=SetProtocol, nodefault};
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TDownloadDialog(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TDownloadDialog(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TDownloadDialog(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TDownloadDialog(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TDownloadDialog* DownloadDialog;

}	/* namespace Adxdown */
using namespace Adxdown;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdXDown
