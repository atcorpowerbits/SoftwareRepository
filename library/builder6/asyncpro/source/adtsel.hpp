// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdTSel.pas' rev: 6.00

#ifndef AdTSelHPP
#define AdTSelHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AwWin32.hpp>	// Pascal unit
#include <AdSelCom.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <AdTUtil.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <AdPort.hpp>	// Pascal unit
#include <AwUser.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adtsel
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TDeviceSelectionForm;
class PASCALIMPLEMENTATION TDeviceSelectionForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TComboBox* dsfComboBox;
	Buttons::TBitBtn* dsfOkBitBtn;
	Buttons::TBitBtn* dsfCancelBitBtn;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall dsfOkBitBtnClick(System::TObject* Sender);
	void __fastcall dsfCancelBitBtnClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	
private:
	Classes::TStringList* FPortItemList;
	Adport::TTapiMode FTapiMode;
	Word FComNumber;
	AnsiString FDeviceName;
	bool FShowTapiDevices;
	bool FShowPorts;
	bool FEnumerated;
	bool FShowOnlySupported;
	bool FEnableVoice;
	
public:
	void __fastcall EnumComPorts(void);
	void __fastcall EnumTapiPorts(void);
	void __fastcall EnumAllPorts(void);
	__fastcall virtual TDeviceSelectionForm(Classes::TComponent* AOwner);
	__property Classes::TStringList* PortItemList = {read=FPortItemList, write=FPortItemList};
	__property Adport::TTapiMode TapiMode = {read=FTapiMode, write=FTapiMode, nodefault};
	__property Word ComNumber = {read=FComNumber, write=FComNumber, nodefault};
	__property AnsiString DeviceName = {read=FDeviceName, write=FDeviceName};
	__property bool EnableVoice = {read=FEnableVoice, write=FEnableVoice, nodefault};
	__property bool ShowTapiDevices = {read=FShowTapiDevices, write=FShowTapiDevices, nodefault};
	__property bool ShowPorts = {read=FShowPorts, write=FShowPorts, nodefault};
	__property bool ShowOnlySupported = {read=FShowOnlySupported, write=FShowOnlySupported, nodefault};
public:
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TDeviceSelectionForm(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TDeviceSelectionForm(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TDeviceSelectionForm(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define DirectTo "Direct to COM"
extern PACKAGE TDeviceSelectionForm* DeviceSelectionForm;

}	/* namespace Adtsel */
using namespace Adtsel;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdTSel
