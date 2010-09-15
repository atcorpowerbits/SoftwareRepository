// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'scale.pas' rev: 6.00

#ifndef scaleHPP
#define scaleHPP

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

namespace Scale
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TScaleTickDrawnEvent)(System::TObject* Sender, Graphics::TCanvas* &Canvas, Sdlbase::TScaleType ScaleType, double CurrentTickPos, int ChartX, int ChartY);

typedef void __fastcall (__closure *TScaleRenderedEvent)(System::TObject* Sender, Graphics::TCanvas* Canvas);

#pragma option push -b-
enum TScaleUnitAnchor { uaSclTopLft, uaSclCenter, uaSclBotRgt };
#pragma option pop

typedef DynamicArray<double >  scale__2;

class DELPHICLASS TScale;
class PASCALIMPLEMENTATION TScale : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	Sdlbase::TFrameStyle FFrameStyle;
	Graphics::TColor FColorFG;
	Graphics::TColor FColorBG;
	Graphics::TColor FColBlackLine;
	Graphics::TColor FColGrayLine;
	Graphics::TColor FColWhiteLine;
	Sdlbase::TColorScheme FColorScheme;
	TScaleTickDrawnEvent FOnScaleTickDrawn;
	bool FAxLog;
	double FTransf_k;
	double FTransf_d;
	double FRangeHigh;
	double FRangeLow;
	bool FShortTicks;
	int FTickCount;
	int FNumTicks;
	int FDecPlaces;
	bool FNotYetLoaded;
	bool FDrawBaseLine;
	bool FTransparent;
	Sdlbase::TFigType FLabelType;
	Sdlbase::TDTLabel* FDTFormat;
	int FMarginTop;
	int FMarginBottom;
	int FMarginRight;
	int FMarginLeft;
	bool FIsHelper;
	int FLblPosX;
	int FLblPosY;
	Classes::TAlignment FLblAlign;
	TScaleUnitAnchor FLblAnchor;
	AnsiString FUserTicktext;
	AnsiString FScaleInscript;
	DynamicArray<double >  FScaleTickPos;
	AnsiString FUnitLabel;
	Graphics::TCanvas* FForeignCv;
	int FForCvPosX;
	int FForCvPosY;
	Sdlbase::TScaleType FScaleType;
	TScaleRenderedEvent FOnBeforeSclRend;
	TScaleRenderedEvent FOnAfterSclRend;
	bool FSuppressPaint;
	void __fastcall AdjustScalePars(void);
	double __fastcall GetTickPos(int ix);
	void __fastcall SetColorBG(Graphics::TColor Value);
	void __fastcall SetColorFG(Graphics::TColor Value);
	void __fastcall SetColorScheme(Sdlbase::TColorScheme Value);
	void __fastcall SetFrameStyle(Sdlbase::TFrameStyle value);
	void __fastcall SetScaleType(Sdlbase::TScaleType Value);
	void __fastcall SetUnitLabel(AnsiString Value);
	void __fastcall SetCaptAlign(Classes::TAlignment al);
	void __fastcall SetCaptAnchor(TScaleUnitAnchor ca);
	void __fastcall SetIsHelper(bool value);
	void __fastcall SetMarginTop(int Value);
	void __fastcall SetMarginBottom(int Value);
	void __fastcall SetMarginLeft(int Value);
	void __fastcall SetMarginRight(int Value);
	void __fastcall SetRangeHigh(double Value);
	void __fastcall SetRangeLow(double Value);
	void __fastcall SetDecPlaces(int Value);
	void __fastcall SetShowBaseLine(bool Value);
	void __fastcall SetTransparent(bool Value);
	void __fastcall SetUserTickText(AnsiString txt);
	void __fastcall SetAxLinLog(bool Value);
	void __fastcall SetLabelType(Sdlbase::TFigType Value);
	void __fastcall SetShortTicks(bool st);
	void __fastcall SetScaleInscript(AnsiString x);
	void __fastcall SetDTFormat(Sdlbase::TDTLabel* value);
	void __fastcall SetNumTicks(int d);
	void __fastcall SetUnitLabelPosX(int value);
	void __fastcall SetUnitLabelPosY(int value);
	void __fastcall SetSuppressPaint(bool supp);
	void __fastcall SetForCvPosX(int value);
	void __fastcall SetForCvPosY(int value);
	
protected:
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Paint(void);
	AnsiString __fastcall ExtractUserText(AnsiString TickText, int ix);
	AnsiString __fastcall AddScaleInscription(AnsiString Instring, AnsiString Inscr);
	void __fastcall DrawYScale(Graphics::TCanvas* cv, int XPos);
	void __fastcall DrawXScale(Graphics::TCanvas* cv, int YPos);
	virtual void __fastcall Loaded(void);
	int __fastcall R2M(double xin);
	void __fastcall TriggerPaint(void);
	
public:
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	__fastcall virtual TScale(Classes::TComponent* AOwner);
	__fastcall virtual ~TScale(void);
	HIDESBASE void __fastcall Changed(System::TObject* Sender);
	__property Enabled  = {default=1};
	__property bool IsHelperComponent = {read=FIsHelper, write=SetIsHelper, nodefault};
	__property double TickPos[int ix] = {read=GetTickPos};
	void __fastcall UseForeignCanvas(Graphics::TCanvas* ForeignCv, int x, int y);
	void __fastcall ForcePaint(void);
	__property int ForeignCanvasPosX = {read=FForCvPosX, write=SetForCvPosX, nodefault};
	__property int ForeignCanvasPosY = {read=FForCvPosY, write=SetForCvPosY, nodefault};
	int __fastcall ConvertToPixelCoords(double Value);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	__property bool SuppressPaint = {read=FSuppressPaint, write=SetSuppressPaint, nodefault};
	
__published:
	__property Align  = {default=0};
	__property Anchors  = {default=3};
	__property AnsiString Caption = {read=FUnitLabel, write=SetUnitLabel};
	__property int CaptionPosX = {read=FLblPosX, write=SetUnitLabelPosX, nodefault};
	__property int CaptionPosY = {read=FLblPosY, write=SetUnitLabelPosY, nodefault};
	__property Classes::TAlignment CaptionAlignment = {read=FLblAlign, write=SetCaptAlign, nodefault};
	__property TScaleUnitAnchor CaptionAnchor = {read=FLblAnchor, write=SetCaptAnchor, nodefault};
	__property Graphics::TColor ColorBackGnd = {read=FColorBG, write=SetColorBG, nodefault};
	__property Graphics::TColor ColorScale = {read=FColorFG, write=SetColorFG, nodefault};
	__property Sdlbase::TColorScheme ColorScheme = {read=FColorScheme, write=SetColorScheme, nodefault};
	__property Sdlbase::TDTLabel* DateFormat = {read=FDTFormat, write=SetDTFormat};
	__property int DecPlaces = {read=FDecPlaces, write=SetDecPlaces, nodefault};
	__property Font ;
	__property Sdlbase::TFrameStyle FrameStyle = {read=FFrameStyle, write=SetFrameStyle, nodefault};
	__property Sdlbase::TFigType LabelType = {read=FLabelType, write=SetLabelType, nodefault};
	__property bool Logarithmic = {read=FAxLog, write=SetAxLinLog, nodefault};
	__property int MarginTop = {read=FMarginTop, write=SetMarginTop, nodefault};
	__property int MarginBottom = {read=FMarginBottom, write=SetMarginBottom, nodefault};
	__property int MarginLeft = {read=FMarginLeft, write=SetMarginLeft, nodefault};
	__property int MarginRight = {read=FMarginRight, write=SetMarginRight, nodefault};
	__property int MinTicks = {read=FNumTicks, write=SetNumTicks, nodefault};
	__property int NumTicks = {read=FTickCount, nodefault};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property double RangeLow = {read=FRangeLow, write=SetRangeLow};
	__property double RangeHigh = {read=FRangeHigh, write=SetRangeHigh};
	__property bool ShortTicks = {read=FShortTicks, write=SetShortTicks, nodefault};
	__property bool ShowBaseLine = {read=FDrawBaseLine, write=SetShowBaseLine, nodefault};
	__property ShowHint ;
	__property AnsiString ScaleInscript = {read=FScaleInscript, write=SetScaleInscript};
	__property Sdlbase::TScaleType ScaleType = {read=FScaleType, write=SetScaleType, nodefault};
	__property bool Transparent = {read=FTransparent, write=SetTransparent, nodefault};
	__property AnsiString UserTickText = {read=FUserTicktext, write=SetUserTickText};
	__property Visible  = {default=1};
	__property OnClick ;
	__property OnDblClick ;
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property OnContextPopup ;
	__property TScaleTickDrawnEvent OnScaleTickDrawn = {read=FOnScaleTickDrawn, write=FOnScaleTickDrawn};
	__property TScaleRenderedEvent OnAfterScaleRendered = {read=FOnAfterSclRend, write=FOnAfterSclRend};
	__property TScaleRenderedEvent OnBeforeScaleRendered = {read=FOnBeforeSclRend, write=FOnBeforeSclRend};
};


//-- var, const, procedure ---------------------------------------------------
#define SDLVersionInfo "scale_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;

}	/* namespace Scale */
using namespace Scale;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// scale
