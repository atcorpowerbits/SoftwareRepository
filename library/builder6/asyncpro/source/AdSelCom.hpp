// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdSelCom.pas' rev: 6.00

#ifndef AdSelComHPP
#define AdSelComHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AwWin32.hpp>	// Pascal unit
#include <AwUser.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adselcom
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TComSelectForm;
class PASCALIMPLEMENTATION TComSelectForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TLabel* Label1;
	Stdctrls::TLabel* Label2;
	Buttons::TBitBtn* OkBtn;
	Buttons::TBitBtn* AbortBtn;
	Extctrls::TBevel* Bevel1;
	Stdctrls::TComboBox* PortsComboBox;
	void __fastcall FormCreate(System::TObject* Sender);
	
public:
	AnsiString __fastcall SelectedCom();
	Word __fastcall SelectedComNum(void);
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TComSelectForm(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TComSelectForm(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TComSelectForm(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TComSelectForm(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE bool UseDispatcherForAvail;
extern PACKAGE bool ShowPortsInUse;
extern PACKAGE bool __fastcall IsPortAvailable(unsigned ComNum);

}	/* namespace Adselcom */
using namespace Adselcom;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdSelCom
