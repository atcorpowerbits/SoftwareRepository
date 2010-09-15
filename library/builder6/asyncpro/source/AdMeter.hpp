// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdMeter.pas' rev: 6.00

#ifndef AdMeterHPP
#define AdMeterHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <OoMisc.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
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

namespace Admeter
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TBevelStyle { bsLowered, bsRaised, bsNone };
#pragma option pop

class DELPHICLASS TApdMeter;
class PASCALIMPLEMENTATION TApdMeter : public Oomisc::TApdBaseGraphicControl 
{
	typedef Oomisc::TApdBaseGraphicControl inherited;
	
private:
	Graphics::TColor FBarColor;
	Graphics::TColor FBevelColor1;
	Graphics::TColor FBevelColor2;
	TBevelStyle FBevelStyle;
	int FMax;
	int FMin;
	Classes::TNotifyEvent FOnPosChange;
	int FPosition;
	int FSegments;
	int FStep;
	bool NeedPartial;
	int PartialSize;
	void __fastcall SetBarColor(Graphics::TColor Value);
	void __fastcall SetBevelStyle(TBevelStyle Value);
	void __fastcall SetBevelColor1(Graphics::TColor Value);
	void __fastcall SetBevelColor2(Graphics::TColor Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetStep(int Value);
	
protected:
	DYNAMIC void __fastcall DoOnPosChange(void);
	virtual void __fastcall Paint(void);
	void __fastcall UpdatePosition(bool Force);
	
public:
	__fastcall virtual TApdMeter(Classes::TComponent* AOwner);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	
__published:
	__property Graphics::TColor BarColor = {read=FBarColor, write=SetBarColor, default=-2147483635};
	__property Graphics::TColor BevelColor1 = {read=FBevelColor1, write=SetBevelColor1, default=-2147483628};
	__property Graphics::TColor BevelColor2 = {read=FBevelColor2, write=SetBevelColor2, default=-2147483632};
	__property TBevelStyle BevelStyle = {read=FBevelStyle, write=SetBevelStyle, default=0};
	__property int Max = {read=FMax, write=FMax, default=100};
	__property int Min = {read=FMin, write=FMin, default=0};
	__property int Position = {read=FPosition, write=SetPosition, nodefault};
	__property int Step = {read=FStep, write=SetStep, default=8};
	__property Classes::TNotifyEvent OnPosChange = {read=FOnPosChange, write=FOnPosChange};
	__property Align  = {default=0};
	__property DragCursor  = {default=-12};
	__property DragMode  = {default=0};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowHint ;
	__property Visible  = {default=1};
	__property OnClick ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDrag ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDrag ;
public:
	#pragma option push -w-inl
	/* TGraphicControl.Destroy */ inline __fastcall virtual ~TApdMeter(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const int admDefBarColor = 0x8000000d;
static const int admDefBevelColor1 = 0x80000014;
static const int admDefBevelColor2 = 0x80000010;
static const Shortint admDefMeterHeight = 0x10;
static const Shortint admDefMax = 0x64;
static const Shortint admDefMin = 0x0;
static const Shortint admDefStep = 0x8;
static const Byte admDefMeterWidth = 0x96;

}	/* namespace Admeter */
using namespace Admeter;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdMeter
