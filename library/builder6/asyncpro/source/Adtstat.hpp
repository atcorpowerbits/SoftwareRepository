// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdTStat.pas' rev: 6.00

#ifndef AdTStatHPP
#define AdTStatHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdTapi.hpp>	// Pascal unit
#include <AdTUtil.hpp>	// Pascal unit
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

namespace Adtstat
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TApdStandardTapiDisplay;
class PASCALIMPLEMENTATION TApdStandardTapiDisplay : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Extctrls::TPanel* dpPanel1;
	Stdctrls::TLabel* dpLabel1;
	Stdctrls::TLabel* dpLabel2;
	Stdctrls::TLabel* dpLabel3;
	Stdctrls::TLabel* dpLabel4;
	Stdctrls::TButton* dpCancel;
	Extctrls::TPanel* stPanel;
	Stdctrls::TLabel* dpStat1;
	Stdctrls::TLabel* dpStat2;
	Stdctrls::TLabel* dpStat3;
	Stdctrls::TLabel* dpStat4;
	Stdctrls::TLabel* dpStat5;
	Stdctrls::TLabel* dpStat6;
	Stdctrls::TLabel* dpStat7;
	Stdctrls::TLabel* dpStat8;
	Stdctrls::TLabel* dpStat9;
	Stdctrls::TLabel* dpDialing;
	Stdctrls::TLabel* dpUsing;
	Stdctrls::TLabel* dpAttempt;
	Stdctrls::TLabel* dpTotalAttempts;
	void __fastcall dpCancelClick(System::TObject* Sender);
	
private:
	Word LabCount;
	void __fastcall ClearStatusMessages(void);
	void __fastcall AddStatusLine(const AnsiString S);
	void __fastcall Mode(const AnsiString S);
	void __fastcall UpdateStatusLine(const AnsiString S);
	void __fastcall UpdateValues(Adtapi::TApdCustomTapiDevice* TapiDevice, unsigned Device, unsigned Message, unsigned Param1, unsigned Param2, unsigned Param3);
	
public:
	Stdctrls::TLabel* Labels[9];
	Adtapi::TApdCustomTapiDevice* TapiDevice;
	bool Updating;
	__fastcall virtual TApdStandardTapiDisplay(Classes::TComponent* AOwner);
public:
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TApdStandardTapiDisplay(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TApdStandardTapiDisplay(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TApdStandardTapiDisplay(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TApdTapiStatus;
class PASCALIMPLEMENTATION TApdTapiStatus : public Adtapi::TApdAbstractTapiStatus 
{
	typedef Adtapi::TApdAbstractTapiStatus inherited;
	
__published:
	DYNAMIC void __fastcall CreateDisplay(void);
	DYNAMIC void __fastcall DestroyDisplay(void);
	virtual void __fastcall UpdateDisplay(bool First, bool Last, unsigned Device, unsigned Message, unsigned Param1, unsigned Param2, unsigned Param3);
public:
	#pragma option push -w-inl
	/* TApdAbstractTapiStatus.Create */ inline __fastcall virtual TApdTapiStatus(Classes::TComponent* AOwner) : Adtapi::TApdAbstractTapiStatus(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdAbstractTapiStatus.Destroy */ inline __fastcall virtual ~TApdTapiStatus(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint MaxLines = 0x9;

}	/* namespace Adtstat */
using namespace Adtstat;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdTStat
