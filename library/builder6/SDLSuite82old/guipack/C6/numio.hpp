// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'numio.pas' rev: 6.00

#ifndef numioHPP
#define numioHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <StdCtrls.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
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

namespace Numio
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TInFormat { itExp, itFloat, itFixPoint, itInt, itHex, itOct, itBin, itDynamic };
#pragma option pop

#pragma option push -b-
enum TDecPSep { dsDot, dsComma, dsBoth, dsSystem };
#pragma option pop

class DELPHICLASS TNumIO;
class PASCALIMPLEMENTATION TNumIO : public Stdctrls::TCustomEdit 
{
	typedef Stdctrls::TCustomEdit inherited;
	
private:
	TInFormat FInFormat;
	int FFixPDecPl;
	AnsiString FOldText;
	bool FBeep;
	double FMinimum;
	double FMaximum;
	TDecPSep FDecPSep;
	void __fastcall SetInputFormat(TInFormat value);
	void __fastcall SetRangeLow(double value);
	void __fastcall SetRangeHigh(double value);
	void __fastcall SetLabValue(double x);
	double __fastcall GetLabValue(void);
	void __fastcall SetDecPSep(TDecPSep Value);
	void __fastcall SetFixPDecPl(int value);
	
protected:
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	bool __fastcall ConvertNumString(AnsiString Instring, double &DReslt);
	DYNAMIC void __fastcall Change(void);
	
public:
	__fastcall virtual TNumIO(Classes::TComponent* AOwner);
	__fastcall virtual ~TNumIO(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	__property double Value = {read=GetLabValue, write=SetLabValue};
	
__published:
	__property Anchors  = {default=3};
	__property AutoSelect  = {default=1};
	__property AutoSize  = {default=1};
	__property bool Beep = {read=FBeep, write=FBeep, nodefault};
	__property BorderStyle  = {default=1};
	__property Color  = {default=-2147483643};
	__property Ctl3D ;
	__property ParentCtl3D  = {default=1};
	__property Cursor  = {default=0};
	__property TDecPSep DecPlaceSep = {read=FDecPSep, write=SetDecPSep, nodefault};
	__property Enabled  = {default=1};
	__property int FixPointDecPlaces = {read=FFixPDecPl, write=SetFixPDecPl, nodefault};
	__property Font ;
	__property Height ;
	__property HelpContext  = {default=0};
	__property HideSelection  = {default=1};
	__property Hint ;
	__property TInFormat InputFormat = {read=FInFormat, write=SetInputFormat, nodefault};
	__property Left ;
	__property double RangeHigh = {read=FMaximum, write=SetRangeHigh, stored=true};
	__property double RangeLow = {read=FMinimum, write=SetRangeLow, stored=true};
	__property Name ;
	__property ParentColor  = {default=0};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowHint ;
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=1};
	__property Tag  = {default=0};
	__property Text ;
	__property Top ;
	__property Visible  = {default=1};
	__property Width ;
	__property OnChange ;
	__property OnClick ;
	__property OnDblClick ;
	__property OnEnter ;
	__property OnExit ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TNumIO(HWND ParentWindow) : Stdctrls::TCustomEdit(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define SDLVersionInfo "numio_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Numio */
using namespace Numio;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// numio
