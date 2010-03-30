// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdMdmCfg.pas' rev: 6.00

#ifndef AdMdmCfgHPP
#define AdMdmCfgHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdPort.hpp>	// Pascal unit
#include <AdMdm.hpp>	// Pascal unit
#include <AdLibMdm.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
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

namespace Admdmcfg
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TApdModemConfigDialog;
class PASCALIMPLEMENTATION TApdModemConfigDialog : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TButton* btnOK;
	Stdctrls::TButton* btnCancel;
	Comctrls::TPageControl* PageControl1;
	Comctrls::TTabSheet* TabSheet1;
	Comctrls::TTabSheet* TabSheet2;
	Comctrls::TTabSheet* TabSheet3;
	Stdctrls::TLabel* lblModemName;
	Stdctrls::TLabel* lblModemModel;
	Stdctrls::TLabel* lblModemManufacturer;
	Stdctrls::TLabel* lblAttachedTo;
	Stdctrls::TGroupBox* GroupBox1;
	Stdctrls::TGroupBox* GroupBox2;
	Extctrls::TRadioGroup* rgpDataBits;
	Extctrls::TRadioGroup* rgpParity;
	Extctrls::TRadioGroup* rgpStopBits;
	Stdctrls::TCheckBox* cbxNotBlindDial;
	Stdctrls::TCheckBox* cbxEnableCallFailTimer;
	Stdctrls::TEdit* edtCallSetupFailTimer;
	Stdctrls::TLabel* Label5;
	Stdctrls::TCheckBox* cbxEnableIdleTimeout;
	Stdctrls::TLabel* Label7;
	Stdctrls::TGroupBox* GroupBox3;
	Stdctrls::TRadioButton* rbFlowNone;
	Stdctrls::TRadioButton* rbFlowHard;
	Stdctrls::TRadioButton* rbFlowSoft;
	Stdctrls::TGroupBox* rgpErrorCorrection;
	Stdctrls::TCheckBox* cbxDataCompress;
	Stdctrls::TGroupBox* GroupBox5;
	Stdctrls::TRadioButton* rbModCCITT;
	Stdctrls::TCheckBox* cbxCellular;
	Stdctrls::TRadioButton* rbModCCITTV23;
	Stdctrls::TRadioButton* rbModBell;
	Stdctrls::TEdit* edtExtraSettings;
	Stdctrls::TLabel* Label4;
	Stdctrls::TCheckBox* cbxUseErrorCorrection;
	Stdctrls::TCheckBox* cbxRequireCorrection;
	Stdctrls::TEdit* edtInactivityTimer;
	Stdctrls::TGroupBox* GroupBox4;
	Stdctrls::TLabel* Label1;
	Comctrls::TTrackBar* tbSpeakerVolume;
	Stdctrls::TLabel* Label2;
	Stdctrls::TLabel* Label3;
	Stdctrls::TRadioButton* rbSpeakerConnect;
	Stdctrls::TRadioButton* rbSpeakerOn;
	Stdctrls::TRadioButton* rbSpeakerOff;
	
private:
	Adlibmdm::TLmModem FLmModem;
	Admdm::TApdModemConfig __fastcall GetModemConfig();
	void __fastcall SetLmModem(const Adlibmdm::TLmModem &Value);
	void __fastcall SetModemConfig(const Admdm::TApdModemConfig &Value);
	
public:
	__property Adlibmdm::TLmModem LmModem = {read=FLmModem, write=SetLmModem};
	__property Admdm::TApdModemConfig ModemConfig = {read=GetModemConfig, write=SetModemConfig};
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TApdModemConfigDialog(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TApdModemConfigDialog(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TApdModemConfigDialog(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TApdModemConfigDialog(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Admdmcfg */
using namespace Admdmcfg;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdMdmCfg
