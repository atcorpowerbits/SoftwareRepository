// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'colsel.pas' rev: 6.00

#ifndef colselHPP
#define colselHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <StdCtrls.hpp>	// Pascal unit
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

namespace Colsel
{
//-- type declarations -------------------------------------------------------
typedef AnsiString colsel__2[47];

class DELPHICLASS TColSel;
class PASCALIMPLEMENTATION TColSel : public Stdctrls::TCustomComboBox 
{
	typedef Stdctrls::TCustomComboBox inherited;
	
private:
	int FColorBarWidth;
	int FSelColorIx;
	int FNumColors;
	int FMouseAreaCode;
	Graphics::TColor FColors[47];
	AnsiString FColorNames[47];
	bool FIsUserEditable[47];
	void __fastcall SetSelColor(Graphics::TColor Color);
	Graphics::TColor __fastcall GetSelColor(void);
	void __fastcall SetColorBarWidth(int W);
	AnsiString __fastcall GetSelColorID();
	Graphics::TColor __fastcall GetArrayColor(int Index);
	void __fastcall SetArrayColor(int Index, Graphics::TColor value);
	AnsiString __fastcall GetArrayColorName(int Index);
	void __fastcall SetArrayColorName(int Index, AnsiString value);
	bool __fastcall GetArrayAllowEdit(int Index);
	void __fastcall SetArrayAllowEdit(int Index, bool value);
	void __fastcall SetNumColors(int num);
	
protected:
	DYNAMIC void __fastcall Click(void);
	virtual void __fastcall DrawItem(int Index, const Types::TRect &Rect, Windows::TOwnerDrawState State);
	DYNAMIC void __fastcall DropDown(void);
	virtual void __fastcall Loaded(void);
	void __fastcall LoadColorsIntoComboList(void);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	
public:
	__fastcall virtual TColSel(Classes::TComponent* AOwner);
	void __fastcall SetAllColorEditFlags(void);
	void __fastcall ResetAllColorEditFlags(void);
	__property AnsiString SelColorID = {read=GetSelColorID};
	__property bool ColorEditAllowed[int Index] = {read=GetArrayAllowEdit, write=SetArrayAllowEdit};
	__property Graphics::TColor Colors[int Index] = {read=GetArrayColor, write=SetArrayColor};
	__property AnsiString ColorNames[int Index] = {read=GetArrayColorName, write=SetArrayColorName};
	void __fastcall LoadBasicVGAPalette(void);
	void __fastcall LoadExtendedPalette(void);
	void __fastcall LoadWindowsSystemPalette(void);
	void __fastcall LoadStandardPalette(void);
	
__published:
	__property Color  = {default=-2147483643};
	__property int ColorBarWidth = {read=FColorBarWidth, write=SetColorBarWidth, nodefault};
	__property DropDownCount  = {default=8};
	__property Enabled  = {default=1};
	__property Font ;
	__property int NumColors = {read=FNumColors, write=SetNumColors, nodefault};
	__property ParentColor  = {default=0};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property Graphics::TColor SelColor = {read=GetSelColor, write=SetSelColor, nodefault};
	__property ShowHint ;
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=1};
	__property Visible  = {default=1};
	__property OnChange ;
	__property OnClick ;
	__property OnDropDown ;
	__property OnEnter ;
	__property OnExit ;
public:
	#pragma option push -w-inl
	/* TCustomComboBox.Destroy */ inline __fastcall virtual ~TColSel(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TColSel(HWND ParentWindow) : Stdctrls::TCustomComboBox(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint COLSEL_MAXCOLORS = 0x2f;
#define SDLVersionInfo "colsel_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Colsel */
using namespace Colsel;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// colsel
