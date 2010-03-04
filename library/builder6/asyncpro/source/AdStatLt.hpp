// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdStatLt.pas' rev: 6.00

#ifndef AdStatLtHPP
#define AdStatLtHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdPort.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adstatlt
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TApdCustomStatusLight;
class PASCALIMPLEMENTATION TApdCustomStatusLight : public Oomisc::TApdBaseGraphicControl 
{
	typedef Oomisc::TApdBaseGraphicControl inherited;
	
protected:
	Graphics::TBitmap* FGlyph;
	bool FLit;
	Graphics::TColor FLitColor;
	Graphics::TColor FNotLitColor;
	bool HaveGlyph;
	void __fastcall SetGlyph(const Graphics::TBitmap* NewGlyph);
	void __fastcall SetLit(const bool IsLit);
	void __fastcall SetLitColor(const Graphics::TColor NewColor);
	void __fastcall SetNotLitColor(const Graphics::TColor NewColor);
	HIDESBASE AnsiString __fastcall GetVersion();
	HIDESBASE void __fastcall SetVersion(const AnsiString Value);
	virtual void __fastcall Paint(void);
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TApdCustomStatusLight(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomStatusLight(void);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	__property AnsiString Version = {read=GetVersion, write=SetVersion, stored=false};
	__property Graphics::TBitmap* Glyph = {read=FGlyph, write=SetGlyph};
	__property bool Lit = {read=FLit, write=SetLit, nodefault};
	__property Graphics::TColor LitColor = {read=FLitColor, write=SetLitColor, default=255};
	__property Graphics::TColor NotLitColor = {read=FNotLitColor, write=SetNotLitColor, default=32768};
};


class DELPHICLASS TApdStatusLight;
class PASCALIMPLEMENTATION TApdStatusLight : public TApdCustomStatusLight 
{
	typedef TApdCustomStatusLight inherited;
	
__published:
	__property Version ;
	__property Glyph ;
	__property Lit ;
	__property LitColor  = {default=255};
	__property NotLitColor  = {default=32768};
public:
	#pragma option push -w-inl
	/* TApdCustomStatusLight.Create */ inline __fastcall virtual TApdStatusLight(Classes::TComponent* AOwner) : TApdCustomStatusLight(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomStatusLight.Destroy */ inline __fastcall virtual ~TApdStatusLight(void) { }
	#pragma option pop
	
};


class DELPHICLASS TLightSet;
class PASCALIMPLEMENTATION TLightSet : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
protected:
	TApdCustomStatusLight* FCTSLight;
	TApdCustomStatusLight* FDSRLight;
	TApdCustomStatusLight* FDCDLight;
	TApdCustomStatusLight* FRINGLight;
	TApdCustomStatusLight* FTXDLight;
	TApdCustomStatusLight* FRXDLight;
	TApdCustomStatusLight* FERRORLight;
	TApdCustomStatusLight* FBREAKLight;
	
public:
	__fastcall TLightSet(void);
	void __fastcall InitLights(const Adport::TApdCustomComPort* ComPort, bool Monitoring);
	
__published:
	__property TApdCustomStatusLight* CTSLight = {read=FCTSLight, write=FCTSLight};
	__property TApdCustomStatusLight* DSRLight = {read=FDSRLight, write=FDSRLight};
	__property TApdCustomStatusLight* DCDLight = {read=FDCDLight, write=FDCDLight};
	__property TApdCustomStatusLight* RINGLight = {read=FRINGLight, write=FRINGLight};
	__property TApdCustomStatusLight* TXDLight = {read=FTXDLight, write=FTXDLight};
	__property TApdCustomStatusLight* RXDLight = {read=FRXDLight, write=FRXDLight};
	__property TApdCustomStatusLight* ERRORLight = {read=FERRORLight, write=FERRORLight};
	__property TApdCustomStatusLight* BREAKLight = {read=FBREAKLight, write=FBREAKLight};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TLightSet(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdCustomSLController;
class PASCALIMPLEMENTATION TApdCustomSLController : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	Adport::TApdCustomComPort* FComPort;
	bool FMonitoring;
	bool MonitoringPending;
	int FErrorOffTimeout;
	int FBreakOffTimeout;
	int FRXDOffTimeout;
	int FTXDOffTimeout;
	int FRingOffTimeout;
	TLightSet* FLights;
	Adport::TTriggerAvailEvent SaveTriggerAvail;
	Adport::TTriggerStatusEvent SaveTriggerStatus;
	Adport::TTriggerTimerEvent SaveTriggerTimer;
	unsigned ModemStatMask;
	int MSTrig;
	int ErrorOnTrig;
	int BreakOnTrig;
	int ErrorOffTrig;
	int BreakOffTrig;
	int RxdOffTrig;
	int TxdOnTrig;
	int TxdOffTrig;
	int RingOffTrig;
	bool __fastcall GetHaveCTSLight(void);
	bool __fastcall GetHaveDSRLight(void);
	bool __fastcall GetHaveDCDLight(void);
	bool __fastcall GetHaveRINGLight(void);
	bool __fastcall GetHaveTXDLight(void);
	bool __fastcall GetHaveRXDLight(void);
	bool __fastcall GetHaveERRORLight(void);
	bool __fastcall GetHaveBREAKLight(void);
	void __fastcall SetComPort(const Adport::TApdCustomComPort* NewPort);
	void __fastcall SetLights(const TLightSet* NewLights);
	void __fastcall SetMonitoring(const bool NewMon);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual void __fastcall Loaded(void);
	void __fastcall InitTriggers(void);
	void __fastcall AddTriggers(void);
	void __fastcall RemoveTriggers(void);
	void __fastcall InitLights(void);
	void __fastcall CheckLight(const bool CurStat, const TApdCustomStatusLight* Light);
	void __fastcall StatTriggerAvail(System::TObject* CP, Word Count);
	void __fastcall StatTriggerStatus(System::TObject* CP, Word TriggerHandle);
	void __fastcall StatTriggerTimer(System::TObject* CP, Word TriggerHandle);
	void __fastcall StatPortClose(System::TObject* CP, bool Opening);
	__property bool HaveCTSLight = {read=GetHaveCTSLight, nodefault};
	__property bool HaveDSRLight = {read=GetHaveDSRLight, nodefault};
	__property bool HaveDCDLight = {read=GetHaveDCDLight, nodefault};
	__property bool HaveRINGLight = {read=GetHaveRINGLight, nodefault};
	__property bool HaveTXDLight = {read=GetHaveTXDLight, nodefault};
	__property bool HaveRXDLight = {read=GetHaveRXDLight, nodefault};
	__property bool HaveERRORLight = {read=GetHaveERRORLight, nodefault};
	__property bool HaveBREAKLight = {read=GetHaveBREAKLight, nodefault};
	
public:
	__fastcall virtual TApdCustomSLController(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomSLController(void);
	__property bool Monitoring = {read=FMonitoring, write=SetMonitoring, nodefault};
	__property Adport::TApdCustomComPort* ComPort = {read=FComPort, write=SetComPort};
	__property int ErrorOffTimeout = {read=FErrorOffTimeout, write=FErrorOffTimeout, default=36};
	__property int BreakOffTimeout = {read=FBreakOffTimeout, write=FBreakOffTimeout, default=36};
	__property int RXDOffTimeout = {read=FRXDOffTimeout, write=FRXDOffTimeout, default=1};
	__property int TXDOffTimeout = {read=FTXDOffTimeout, write=FTXDOffTimeout, default=1};
	__property int RingOffTimeout = {read=FRingOffTimeout, write=FRingOffTimeout, default=8};
	__property TLightSet* Lights = {read=FLights, write=SetLights};
};


class DELPHICLASS TApdSLController;
class PASCALIMPLEMENTATION TApdSLController : public TApdCustomSLController 
{
	typedef TApdCustomSLController inherited;
	
__published:
	__property ComPort ;
	__property ErrorOffTimeout  = {default=36};
	__property BreakOffTimeout  = {default=36};
	__property RXDOffTimeout  = {default=1};
	__property TXDOffTimeout  = {default=1};
	__property RingOffTimeout  = {default=8};
	__property Lights ;
public:
	#pragma option push -w-inl
	/* TApdCustomSLController.Create */ inline __fastcall virtual TApdSLController(Classes::TComponent* AOwner) : TApdCustomSLController(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomSLController.Destroy */ inline __fastcall virtual ~TApdSLController(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint adsDefLightDim = 0xd;
static const Shortint adsDefErrorOffTimeout = 0x24;
static const Shortint adsDefBreakOffTimeout = 0x24;
static const Shortint adsDefRXDOffTimeout = 0x1;
static const Shortint adsDefTXDOffTimeout = 0x1;
static const Shortint adsDefRingOffTimeout = 0x8;
static const int adsDefLitColor = 0xff;
static const int adsDefNotLitColor = 0x8000;

}	/* namespace Adstatlt */
using namespace Adstatlt;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdStatLt
