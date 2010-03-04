// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdPStat.pas' rev: 6.00

#ifndef AdPStatHPP
#define AdPStatHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdProtcl.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <AdMeter.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
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

namespace Adpstat
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TStandardDisplay;
class PASCALIMPLEMENTATION TStandardDisplay : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TLabel* psProtocol;
	Stdctrls::TLabel* psBlockCheck;
	Stdctrls::TLabel* psFileName;
	Stdctrls::TLabel* psFileSize;
	Stdctrls::TLabel* psBlockSize;
	Stdctrls::TLabel* psTotalBlocks;
	Stdctrls::TLabel* psBytesTransferred;
	Stdctrls::TLabel* psBytesRemaining;
	Stdctrls::TLabel* psBlocksTransferred;
	Stdctrls::TLabel* psBlocksRemaining;
	Stdctrls::TLabel* psBlockErrors;
	Stdctrls::TLabel* psTotalErrors;
	Stdctrls::TLabel* psEstimatedTime;
	Stdctrls::TLabel* psElapsedTime;
	Stdctrls::TLabel* psRemainingTime;
	Stdctrls::TLabel* psThroughput;
	Stdctrls::TLabel* psEfficiency;
	Stdctrls::TLabel* psKermitWindows;
	Stdctrls::TLabel* psStatusMsg;
	Stdctrls::TButton* psCancel;
	Extctrls::TPanel* psPanel1;
	Extctrls::TPanel* psPanel6;
	void __fastcall UpdateValues(Adprotcl::TApdCustomProtocol* Protocol);
	void __fastcall CancelClick(System::TObject* Sender);
	
private:
	Admeter::TApdMeter* psProgressBar;
	
public:
	Adprotcl::TApdCustomProtocol* Protocol;
	__fastcall virtual TStandardDisplay(Classes::TComponent* Owner);
public:
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TStandardDisplay(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TStandardDisplay(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TStandardDisplay(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TApdProtocolStatus;
class PASCALIMPLEMENTATION TApdProtocolStatus : public Adprotcl::TApdAbstractStatus 
{
	typedef Adprotcl::TApdAbstractStatus inherited;
	
__published:
	DYNAMIC void __fastcall CreateDisplay(void);
	DYNAMIC void __fastcall DestroyDisplay(void);
	virtual void __fastcall UpdateDisplay(bool First, bool Last);
public:
	#pragma option push -w-inl
	/* TApdAbstractStatus.Create */ inline __fastcall virtual TApdProtocolStatus(Classes::TComponent* AOwner) : Adprotcl::TApdAbstractStatus(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdAbstractStatus.Destroy */ inline __fastcall virtual ~TApdProtocolStatus(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adpstat */
using namespace Adpstat;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdPStat
