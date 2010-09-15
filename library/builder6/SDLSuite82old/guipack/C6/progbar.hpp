// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'progbar.pas' rev: 6.00

#ifndef progbarHPP
#define progbarHPP

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

namespace Progbar
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TColorMapping { cgmCover, cgmStretch, cgmMove };
#pragma option pop

typedef void __fastcall (__closure *TBeforeShowValueEvent)(System::TObject* Sender, AnsiString &ValueText);

class DELPHICLASS TProgBar;
class PASCALIMPLEMENTATION TProgBar : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	Sdlbase::TFrameStyle FOuterFrameSt;
	Sdlbase::TFrameStyle FInnerFrameSt;
	double FProgValue;
	double FProgMax;
	double FProgMin;
	Sdlbase::TDirection FDirection;
	Graphics::TColor FBarColorArray[1024];
	Graphics::TBitmap* AuxBmp;
	Graphics::TColor FColorMargin;
	Graphics::TColor FColorBakG;
	bool FColorGrad;
	Graphics::TColor FColorGrid;
	int FGridDist;
	Graphics::TColor FColBlackLine;
	Graphics::TColor FColGrayLine;
	Graphics::TColor FColWhiteLine;
	Sdlbase::TColorScheme FColorScheme;
	TColorMapping FColorMapMode;
	int FMarginLeft;
	int FMarginRight;
	int FMarginTop;
	int FMarginBottom;
	AnsiString FBakGndFile;
	int FTextPosX;
	int FTextPosY;
	int FTextDecPlaces;
	int FTextAngle;
	Classes::TAlignment FAlignment;
	TBeforeShowValueEvent FOnShowValue;
	bool FShowValue;
	Graphics::TColor __fastcall GetBarColorElem(int ix);
	void __fastcall SetBarColorElem(int ix, Graphics::TColor value);
	void __fastcall SetColorMargin(Graphics::TColor Value);
	void __fastcall SetColorBakG(Graphics::TColor Value);
	void __fastcall SetColorGrad(bool Value);
	void __fastcall SetColorGrid(Graphics::TColor Value);
	void __fastcall SetColorMapMode(TColorMapping Value);
	void __fastcall SetGridDist(int Value);
	void __fastcall SetMarginBottom(int Value);
	void __fastcall SetMarginTop(int Value);
	void __fastcall SetMarginLeft(int Value);
	void __fastcall SetMarginRight(int Value);
	void __fastcall SetColorScheme(Sdlbase::TColorScheme Value);
	Graphics::TColor __fastcall GetColorMin(void);
	Graphics::TColor __fastcall GetColorMax(void);
	void __fastcall SetColorMin(Graphics::TColor value);
	void __fastcall SetColorMax(Graphics::TColor value);
	void __fastcall SetDirection(Sdlbase::TDirection value);
	void __fastcall SetOuterFrameStyle(Sdlbase::TFrameStyle value);
	void __fastcall SetInnerFrameStyle(Sdlbase::TFrameStyle value);
	void __fastcall SetPBarValue(double value);
	void __fastcall SetPBarMin(double value);
	void __fastcall SetPBarMax(double value);
	void __fastcall SetBakGndFile(AnsiString value);
	void __fastcall SetTextPosX(int value);
	void __fastcall SetTextPosY(int value);
	void __fastcall SetTextDecPl(int value);
	void __fastcall SetAlignment(Classes::TAlignment value);
	void __fastcall SetShowValue(bool value);
	void __fastcall SetTextAngle(int value);
	
protected:
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Paint(void);
	
public:
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	__fastcall virtual TProgBar(Classes::TComponent* AOwner);
	__fastcall virtual ~TProgBar(void);
	__property Graphics::TColor BarColors[int ix] = {read=GetBarColorElem, write=SetBarColorElem};
	void __fastcall SetRange(double min, double max);
	
__published:
	__property Align  = {default=0};
	__property Anchors  = {default=3};
	__property Constraints ;
	__property AnsiString BackGroundImg = {read=FBakGndFile, write=SetBakGndFile};
	__property Graphics::TColor ColorBackGnd = {read=FColorBakG, write=SetColorBakG, nodefault};
	__property TColorMapping ColorMapMode = {read=FColorMapMode, write=SetColorMapMode, nodefault};
	__property Graphics::TColor ColorGrid = {read=FColorGrid, write=SetColorGrid, nodefault};
	__property Graphics::TColor ColorMargin = {read=FColorMargin, write=SetColorMargin, nodefault};
	__property Sdlbase::TColorScheme ColorScheme = {read=FColorScheme, write=SetColorScheme, nodefault};
	__property Graphics::TColor ColorMin = {read=GetColorMin, write=SetColorMin, nodefault};
	__property Graphics::TColor ColorMax = {read=GetColorMax, write=SetColorMax, nodefault};
	__property Font ;
	__property Sdlbase::TFrameStyle FrameStyleOuter = {read=FOuterFrameSt, write=SetOuterFrameStyle, nodefault};
	__property Sdlbase::TFrameStyle FrameStyleInner = {read=FInnerFrameSt, write=SetInnerFrameStyle, nodefault};
	__property int GridDist = {read=FGridDist, write=SetGridDist, nodefault};
	__property int MarginBottom = {read=FMarginBottom, write=SetMarginBottom, nodefault};
	__property int MarginLeft = {read=FMarginLeft, write=SetMarginLeft, nodefault};
	__property int MarginRight = {read=FMarginRight, write=SetMarginRight, nodefault};
	__property int MarginTop = {read=FMarginTop, write=SetMarginTop, nodefault};
	__property double Max = {read=FProgMax, write=SetPBarMax};
	__property double Min = {read=FProgMin, write=SetPBarMin};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property Sdlbase::TDirection Direction = {read=FDirection, write=SetDirection, nodefault};
	__property bool ShowColorGradient = {read=FColorGrad, write=SetColorGrad, nodefault};
	__property ShowHint ;
	__property Classes::TAlignment TextAlignment = {read=FAlignment, write=SetAlignment, nodefault};
	__property int TextAngle = {read=FTextAngle, write=SetTextAngle, nodefault};
	__property int TextDecPlaces = {read=FTextDecPlaces, write=SetTextDecPl, nodefault};
	__property int TextPosX = {read=FTextPosX, write=SetTextPosX, nodefault};
	__property int TextPosY = {read=FTextPosY, write=SetTextPosY, nodefault};
	__property bool TextVisible = {read=FShowValue, write=SetShowValue, nodefault};
	__property double Value = {read=FProgValue, write=SetPBarValue};
	__property Visible  = {default=1};
	__property OnClick ;
	__property OnDblClick ;
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property TBeforeShowValueEvent OnShowValue = {read=FOnShowValue, write=FOnShowValue};
};


//-- var, const, procedure ---------------------------------------------------
static const Word MAXBARCOLORS = 0x3ff;
#define SDLVersionInfo "progbar_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Progbar */
using namespace Progbar;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// progbar
