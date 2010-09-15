// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdFStat.pas' rev: 6.00

#ifndef AdFStatHPP
#define AdFStatHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdFax.hpp>	// Pascal unit
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

namespace Adfstat
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TStandardFaxDisplay;
class PASCALIMPLEMENTATION TStandardFaxDisplay : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TLabel* fsPhoneNumber;
	Stdctrls::TLabel* fsFaxFileName;
	Stdctrls::TLabel* fsCoverFileName;
	Stdctrls::TLabel* fsTotalPages;
	Stdctrls::TLabel* fsRemoteID;
	Stdctrls::TLabel* fsConnectBPS;
	Stdctrls::TLabel* fsResolution;
	Stdctrls::TLabel* fsWidth;
	Stdctrls::TLabel* fsErrorControl;
	Stdctrls::TLabel* fsCurrentPage;
	Stdctrls::TLabel* fsPageLength;
	Stdctrls::TLabel* fsBytesTransferred;
	Stdctrls::TLabel* fsElapsedTime;
	Stdctrls::TLabel* fsStatusMsg;
	Stdctrls::TButton* fsCancel;
	Extctrls::TPanel* fsPanel1;
	Stdctrls::TLabel* fsLabel5;
	Stdctrls::TLabel* fsLabel19;
	Stdctrls::TLabel* fsDialAttempt;
	Extctrls::TPanel* fsPanel6;
	Stdctrls::TLabel* fsLabel2;
	Stdctrls::TLabel* fsLabel3;
	void __fastcall UpdateValues(Adfax::TApdCustomAbstractFax* Fax);
	void __fastcall CancelClick(System::TObject* Sender);
	
public:
	Adfax::TApdCustomAbstractFax* Fax;
	Admeter::TApdMeter* fsMeter1;
	__fastcall virtual TStandardFaxDisplay(Classes::TComponent* AOwner);
	
private:
	Oomisc::EventTimer Timer;
	bool Timing;
	Oomisc::EventTimer BusyTimer;
	bool BusyTiming;
public:
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TStandardFaxDisplay(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TStandardFaxDisplay(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TStandardFaxDisplay(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TApdFaxStatus;
class PASCALIMPLEMENTATION TApdFaxStatus : public Adfax::TApdAbstractFaxStatus 
{
	typedef Adfax::TApdAbstractFaxStatus inherited;
	
__published:
	DYNAMIC void __fastcall CreateDisplay(void);
	DYNAMIC void __fastcall DestroyDisplay(void);
	virtual void __fastcall UpdateDisplay(const bool First, const bool Last);
public:
	#pragma option push -w-inl
	/* TApdAbstractFaxStatus.Create */ inline __fastcall virtual TApdFaxStatus(Classes::TComponent* AOwner) : Adfax::TApdAbstractFaxStatus(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdAbstractFaxStatus.Destroy */ inline __fastcall virtual ~TApdFaxStatus(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adfstat */
using namespace Adfstat;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdFStat
