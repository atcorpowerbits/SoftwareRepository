// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdMdmDlg.pas' rev: 6.00

#ifndef AdMdmDlgHPP
#define AdMdmDlgHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ImgList.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <AdMdm.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
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

namespace Admdmdlg
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TApdModemStatusDialog;
class PASCALIMPLEMENTATION TApdModemStatusDialog : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TGroupBox* gbxStatus;
	Stdctrls::TButton* btnCancel;
	Buttons::TBitBtn* btnDetail;
	Stdctrls::TLabel* Label1;
	Stdctrls::TLabel* Label2;
	Stdctrls::TLabel* lblStatus;
	Stdctrls::TLabel* lblUsingDevice;
	Stdctrls::TLabel* lblUsingPort;
	Stdctrls::TLabel* lblElapsedTime;
	Stdctrls::TGroupBox* gbxDetail;
	Stdctrls::TMemo* memDetail;
	Controls::TImageList* ImageList1;
	void __fastcall btnDetailClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall btnCancelClick(System::TObject* Sender);
	
private:
	Admdm::TAdCustomModem* FModem;
	void __fastcall SetModem(const Admdm::TAdCustomModem* NewModem);
	
public:
	__property Admdm::TAdCustomModem* Modem = {read=FModem, write=SetModem};
	void __fastcall UpdateDisplay(const AnsiString StatusStr, const AnsiString TimeStr, const AnsiString DetailStr, Admdm::TApdModemStatusAction Action);
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TApdModemStatusDialog(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TApdModemStatusDialog(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TApdModemStatusDialog(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TApdModemStatusDialog(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TApdModemStatusDialog* ApxModemStatusDialog;

}	/* namespace Admdmdlg */
using namespace Admdmdlg;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdMdmDlg
