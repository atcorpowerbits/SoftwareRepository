// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdXProt.pas' rev: 6.00

#ifndef AdXProtHPP
#define AdXProtHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdProtcl.hpp>	// Pascal unit
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

namespace Adxprot
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TProtocolOptions;
class PASCALIMPLEMENTATION TProtocolOptions : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TGroupBox* GeneralOptions;
	Stdctrls::TComboBox* gWriteFail;
	Stdctrls::TLabel* Label1;
	Stdctrls::TCheckBox* gHonorDirectory;
	Stdctrls::TCheckBox* gIncludeDirectory;
	Stdctrls::TCheckBox* gRTSLowForWrite;
	Stdctrls::TCheckBox* gAbortNoCarrier;
	Stdctrls::TGroupBox* ZmodemOptions;
	Stdctrls::TCheckBox* zOptionOverride;
	Stdctrls::TCheckBox* zSkipNoFile;
	Stdctrls::TCheckBox* zRecover;
	Stdctrls::TCheckBox* z8K;
	Stdctrls::TComboBox* zFileManagment;
	Stdctrls::TLabel* Label2;
	Stdctrls::TButton* OK;
	Stdctrls::TButton* Cancel;
	Stdctrls::TGroupBox* KermitOptions;
	Stdctrls::TGroupBox* AsciiOptions;
	Stdctrls::TLabel* Label3;
	Stdctrls::TEdit* kBlockLen;
	Stdctrls::TLabel* Label5;
	Stdctrls::TEdit* kWindows;
	Stdctrls::TLabel* Label6;
	Stdctrls::TEdit* kTimeout;
	Stdctrls::TLabel* Label7;
	Stdctrls::TEdit* sInterCharDelay;
	Stdctrls::TLabel* Label8;
	Stdctrls::TEdit* sInterLineDelay;
	Stdctrls::TComboBox* sCRTrans;
	Stdctrls::TLabel* Label9;
	Stdctrls::TLabel* Label10;
	Stdctrls::TComboBox* sLFTrans;
	Stdctrls::TLabel* Label11;
	Stdctrls::TEdit* sEOFTimeout;
	void __fastcall CancelClick(System::TObject* Sender);
	void __fastcall OKClick(System::TObject* Sender);
	
private:
	Adprotcl::TApdProtocol* FProtocol;
	bool Executed;
	
protected:
	Adprotcl::TApdProtocol* __fastcall GetProtocol(void);
	void __fastcall SetProtocol(Adprotcl::TApdProtocol* NewProtocol);
	
public:
	__fastcall virtual TProtocolOptions(Classes::TComponent* AOwner);
	__fastcall virtual ~TProtocolOptions(void);
	bool __fastcall Execute(void);
	__property Adprotcl::TApdProtocol* Protocol = {read=GetProtocol, write=SetProtocol};
public:
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TProtocolOptions(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TProtocolOptions(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TProtocolOptions* ProtocolOptions;

}	/* namespace Adxprot */
using namespace Adxprot;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdXProt
