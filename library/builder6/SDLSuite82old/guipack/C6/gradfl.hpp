// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'gradfl.pas' rev: 6.00

#ifndef gradflHPP
#define gradflHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ExtCtrls.hpp>	// Pascal unit
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

namespace Gradfl
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TGradType { gtHoriz, gtVert, gtMidBandHoriz, gtMidBandVert };
#pragma option pop

#pragma option push -b-
enum TGridMode { gmNone, gmHoriz, gmVert, gmBoth };
#pragma option pop

class DELPHICLASS TGradFill;
class PASCALIMPLEMENTATION TGradFill : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	int FNrColors;
	TGradType FGradType;
	Graphics::TColor FColorFirst;
	Graphics::TColor FColorLast;
	Graphics::TColor FColFirstOrg;
	Graphics::TColor FColLastOrg;
	bool FColorsFlipped;
	TGridMode FGridMode;
	Graphics::TColor FGridColor;
	Classes::TNotifyEvent FOnPaint;
	void __fastcall SetColorLast(Graphics::TColor Value);
	void __fastcall SetColorFirst(Graphics::TColor Value);
	void __fastcall SeTGradType(TGradType Value);
	void __fastcall SetNrColors(int Value);
	void __fastcall SetColorFlipped(bool Value);
	void __fastcall SetGridColor(Graphics::TColor Value);
	void __fastcall SetGridMode(TGridMode Value);
	
protected:
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TGradFill(Classes::TComponent* AOwner);
	void __fastcall DrawGradient(Graphics::TBitmap* &bmp);
	
__published:
	__property bool ColorFlipped = {read=FColorsFlipped, write=SetColorFlipped, nodefault};
	__property Graphics::TColor ColorFirst = {read=FColorFirst, write=SetColorFirst, nodefault};
	__property Graphics::TColor ColorLast = {read=FColorLast, write=SetColorLast, nodefault};
	__property TGradType FillType = {read=FGradType, write=SeTGradType, default=0};
	__property Graphics::TColor GridColor = {read=FGridColor, write=SetGridColor, nodefault};
	__property TGridMode GridMode = {read=FGridMode, write=SetGridMode, nodefault};
	__property int NrColors = {read=FNrColors, write=SetNrColors, default=16};
	__property Align  = {default=0};
	__property ParentShowHint  = {default=1};
	__property ShowHint ;
	__property Visible  = {default=1};
	__property OnClick ;
	__property OnDblClick ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property Classes::TNotifyEvent OnPaint = {read=FOnPaint, write=FOnPaint};
public:
	#pragma option push -w-inl
	/* TGraphicControl.Destroy */ inline __fastcall virtual ~TGradFill(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define SDLVersionInfo "gradfl_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Gradfl */
using namespace Gradfl;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// gradfl
