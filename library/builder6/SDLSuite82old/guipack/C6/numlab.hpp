// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'numlab.pas' rev: 6.00

#ifndef numlabHPP
#define numlabHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sdlbase.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Numlab
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TDisplay { dtFloat, dtFixP, dtExp, dtHex, dtZeroInt, dtInt, dtDateTime, dtState, dtBin, dtOct, dtDeg, dtDegMin, dtDegMinSec };
#pragma option pop

typedef void __fastcall (__closure *TBeforeDisplayEvent)(System::TObject* Sender, AnsiString &Text);

class DELPHICLASS TNumLab;
class PASCALIMPLEMENTATION TNumLab : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	int FLeftSpace;
	bool FEmpty;
	int FLabWidth;
	int FDecP;
	bool FComma;
	bool FPlusSign;
	AnsiString FLeftText;
	AnsiString FRightText;
	Sdlbase::TFrameStyle FFrameStyle;
	AnsiString FStateText;
	Classes::TAlignment FAlignment;
	Classes::TAlignment FLTAlignment;
	Classes::TAlignment FRTAlignment;
	int FMouseAreaCode;
	AnsiString FOverFlowIndi;
	double FLabValue;
	Graphics::TColor FColorLabBakG;
	Graphics::TColor FColorLabText;
	Graphics::TColor FColorOutBakG;
	Graphics::TColor FColorOutText;
	Graphics::TColor FColBlackLine;
	Graphics::TColor FColGrayLine;
	Graphics::TColor FColWhiteLine;
	Sdlbase::TColorScheme FColorScheme;
	TDisplay FDisplayType;
	AnsiString FDtFormat;
	TBeforeDisplayEvent FOnBeforeDisplay;
	void __fastcall SetLeftSpace(int Value);
	void __fastcall SetColorLabBakG(Graphics::TColor Value);
	void __fastcall SetColorLabText(Graphics::TColor Value);
	void __fastcall SetColorOutBakG(Graphics::TColor Value);
	void __fastcall SetColorOutText(Graphics::TColor Value);
	void __fastcall SetColorScheme(Sdlbase::TColorScheme Value);
	void __fastcall SetFrameStyle(Sdlbase::TFrameStyle value);
	void __fastcall SetFComma(bool value);
	void __fastcall SetFPlusSign(bool value);
	void __fastcall SetAlignment(Classes::TAlignment value);
	void __fastcall SetLTAlignment(Classes::TAlignment value);
	void __fastcall SetRTAlignment(Classes::TAlignment value);
	void __fastcall SetLabWidth(int value);
	void __fastcall SetLabValue(double value);
	void __fastcall SetStateText(AnsiString value);
	void __fastcall SetEmpty(bool value);
	void __fastcall SetDecP(int value);
	void __fastcall SetDtFormat(AnsiString value);
	void __fastcall SetLeftText(AnsiString value);
	void __fastcall SetRightText(AnsiString value);
	void __fastcall SetOverFlowIndi(AnsiString value);
	void __fastcall SetDisplayType(TDisplay value);
	
protected:
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Paint(void);
	
public:
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	__fastcall virtual TNumLab(Classes::TComponent* AOwner);
	__fastcall virtual ~TNumLab(void);
	__property Enabled  = {default=1};
	__property int MouseAreaCode = {read=FMouseAreaCode, nodefault};
	
__published:
	__property Align  = {default=0};
	__property Classes::TAlignment Alignment = {read=FAlignment, write=SetAlignment, nodefault};
	__property Anchors  = {default=3};
	__property Graphics::TColor ColorLabBakG = {read=FColorLabBakG, write=SetColorLabBakG, nodefault};
	__property Graphics::TColor ColorLabText = {read=FColorLabText, write=SetColorLabText, nodefault};
	__property Graphics::TColor ColorOutBakG = {read=FColorOutBakG, write=SetColorOutBakG, nodefault};
	__property Graphics::TColor ColorOutText = {read=FColorOutText, write=SetColorOutText, nodefault};
	__property Sdlbase::TColorScheme ColorScheme = {read=FColorScheme, write=SetColorScheme, nodefault};
	__property bool Comma = {read=FComma, write=SetFComma, nodefault};
	__property TDisplay DisplayType = {read=FDisplayType, write=SetDisplayType, nodefault};
	__property AnsiString DTFormat = {read=FDtFormat, write=SetDtFormat};
	__property bool Empty = {read=FEmpty, write=SetEmpty, nodefault};
	__property Font ;
	__property bool ForcePlusSign = {read=FPlusSign, write=SetFPlusSign, nodefault};
	__property Sdlbase::TFrameStyle FrameStyle = {read=FFrameStyle, write=SetFrameStyle, nodefault};
	__property int LabelWidth = {read=FLabWidth, write=SetLabWidth, nodefault};
	__property int LeftSpace = {read=FLeftSpace, write=SetLeftSpace, nodefault};
	__property AnsiString LeftText = {read=FLeftText, write=SetLeftText};
	__property Classes::TAlignment LeftTextAlignment = {read=FLTAlignment, write=SetLTAlignment, nodefault};
	__property AnsiString OverflowIndicator = {read=FOverFlowIndi, write=SetOverFlowIndi};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property int Precision = {read=FDecP, write=SetDecP, nodefault};
	__property AnsiString RightText = {read=FRightText, write=SetRightText};
	__property Classes::TAlignment RightTextAlignment = {read=FRTAlignment, write=SetRTAlignment, nodefault};
	__property ShowHint ;
	__property AnsiString StateText = {read=FStateText, write=SetStateText};
	__property double Value = {read=FLabValue, write=SetLabValue};
	__property Visible  = {default=1};
	__property OnClick ;
	__property OnDblClick ;
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property TBeforeDisplayEvent OnBeforeDisplay = {read=FOnBeforeDisplay, write=FOnBeforeDisplay};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint defLeftSpace = 0x23;
static const Shortint defPrecision = 0x2;
static const Shortint defLabelWidth = 0x50;
#define SDLVersionInfo "numlab_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Numlab */
using namespace Numlab;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// numlab
