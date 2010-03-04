// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'rcproped.pas' rev: 6.00

#ifndef rcpropedHPP
#define rcpropedHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <DesignIntf.hpp>	// Pascal unit
#include <DesignEditors.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <rchart.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Rcproped
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TrcBakBMPEditor;
class PASCALIMPLEMENTATION TrcBakBMPEditor : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TCheckBox* CBIncldPath;
	Stdctrls::TComboBox* CBFillMode;
	Buttons::TSpeedButton* SBLoadBMP;
	Buttons::TSpeedButton* SBOK;
	Stdctrls::TEdit* EdName;
	Stdctrls::TLabel* Label1;
	Buttons::TSpeedButton* SBCancel;
	Extctrls::TImage* Image1;
	Extctrls::TBevel* Bevel1;
	Stdctrls::TLabel* LblDims;
	void __fastcall SBLoadBMPClick(System::TObject* Sender);
	void __fastcall CBIncldPathClick(System::TObject* Sender);
	void __fastcall SBOKClick(System::TObject* Sender);
	void __fastcall SBCancelClick(System::TObject* Sender);
	
public:
	AnsiString FullName;
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TrcBakBMPEditor(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TrcBakBMPEditor(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TrcBakBMPEditor(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TrcBakBMPEditor(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Rcproped */
using namespace Rcproped;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// rcproped
