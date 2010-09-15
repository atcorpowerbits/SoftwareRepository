// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdXPort.pas' rev: 6.00

#ifndef AdXPortHPP
#define AdXPortHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdTSel.hpp>	// Pascal unit
#include <AdTapi.hpp>	// Pascal unit
#include <AdPort.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adxport
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TComPortOptions;
class PASCALIMPLEMENTATION TComPortOptions : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TGroupBox* FlowControlBox;
	Stdctrls::TLabel* Label1;
	Stdctrls::TLabel* Label2;
	Stdctrls::TCheckBox* DTRRTS;
	Stdctrls::TCheckBox* RTSCTS;
	Stdctrls::TCheckBox* SoftwareXmit;
	Stdctrls::TCheckBox* SoftwareRcv;
	Stdctrls::TEdit* Edit1;
	Stdctrls::TEdit* Edit2;
	Extctrls::TRadioGroup* Bauds;
	Extctrls::TRadioGroup* Paritys;
	Extctrls::TRadioGroup* Databits;
	Extctrls::TRadioGroup* Stopbits;
	Stdctrls::TGroupBox* Comports;
	Stdctrls::TButton* OK;
	Stdctrls::TButton* Cancel;
	Stdctrls::TComboBox* PortComboBox;
	void __fastcall OKClick(System::TObject* Sender);
	void __fastcall CancelClick(System::TObject* Sender);
	void __fastcall PortComboBoxChange(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	
private:
	bool FShowTapiDevices;
	bool FShowPorts;
	Adport::TApdComPort* FComPort;
	AnsiString FTapiDevice;
	bool Executed;
	
protected:
	Adport::TApdComPort* __fastcall GetComPort(void);
	void __fastcall SetComPort(Adport::TApdComPort* NewPort);
	
public:
	__fastcall virtual TComPortOptions(Classes::TComponent* AOwner);
	__fastcall virtual ~TComPortOptions(void);
	bool __fastcall Execute(void);
	__property Adport::TApdComPort* ComPort = {read=GetComPort, write=SetComPort};
	__property AnsiString TapiDevice = {read=FTapiDevice, write=FTapiDevice};
	__property bool ShowTapiDevices = {read=FShowTapiDevices, write=FShowTapiDevices, nodefault};
	__property bool ShowPorts = {read=FShowPorts, write=FShowPorts, nodefault};
public:
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TComPortOptions(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TComPortOptions(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TComPortOptions* ComPortOptions;

}	/* namespace Adxport */
using namespace Adxport;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdXPort
