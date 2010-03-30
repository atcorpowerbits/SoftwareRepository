// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdPEdit0.pas' rev: 5.00

#ifndef AdPEdit0HPP
#define AdPEdit0HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <StdCtrls.hpp>	// Pascal unit
#include <DsgnIntf.hpp>	// Pascal unit
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

namespace Adpedit0
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TAdPEdit;
class PASCALIMPLEMENTATION TAdPEdit : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TComboBox* BaudChoices;
	Stdctrls::TButton* OK;
	Stdctrls::TButton* Cancel;
	void __fastcall OKClick(System::TObject* Sender);
	void __fastcall CancelClick(System::TObject* Sender);
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TAdPEdit(Classes::TComponent* AOwner) : Forms::TForm(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TAdPEdit(Classes::TComponent* AOwner, int Dummy
		) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TAdPEdit(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TAdPEdit(HWND ParentWindow) : Forms::TForm(ParentWindow
		) { }
	#pragma option pop
	
};


class DELPHICLASS TBaudRateProperty;
class PASCALIMPLEMENTATION TBaudRateProperty : public Dsgnintf::TIntegerProperty 
{
	typedef Dsgnintf::TIntegerProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TBaudRateProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : Dsgnintf::TIntegerProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TBaudRateProperty(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TAdPEdit* AdPEdit;

}	/* namespace Adpedit0 */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Adpedit0;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdPEdit0
