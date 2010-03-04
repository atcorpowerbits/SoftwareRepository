// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'meter.pas' rev: 6.00

#ifndef meterHPP
#define meterHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sdlbase.hpp>	// Pascal unit
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

namespace Meter
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TMeterLayout { mlCirc90, mlCirc120, mlCirc180, mlCirc270, mlCirc300, mlCirc360 };
#pragma option pop

typedef void __fastcall (__closure *TmtBeforeDrawScaleLabelEvent)(System::TObject* Sender, Graphics::TCanvas* Canvas, AnsiString &CurrentTickLabel, int ChartX, int ChartY);

typedef void __fastcall (__closure *TMeterRenderedEvent)(System::TObject* Sender, Graphics::TCanvas* Canvas);

typedef void __fastcall (__closure *TMouseMoveInMeterEvent)(System::TObject* Sender, bool WithinRange, Classes::TShiftState Shift, double MeterValue);

typedef void __fastcall (__closure *TBeforeDrawNeedleEvent)(System::TObject* Sender, Graphics::TCanvas* Canvas, bool &NeedleDrawn);

class DELPHICLASS TNeedleLayout;
class PASCALIMPLEMENTATION TNeedleLayout : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	Graphics::TColor FColorFill;
	Graphics::TColor FColorLine;
	int FSize1;
	int FThickness;
	int FPctNeedleLeng;
	int FAngle1;
	int FBackShift1;
	int FShadowDx;
	int FShadowDy;
	Graphics::TColor FShadowColor;
	Classes::TNotifyEvent FOnChange;
	bool FVisible;
	void __fastcall SetArrowSize1(int Value);
	void __fastcall SetBackShift1(int Value);
	void __fastcall SetArrowThick(int Value);
	void __fastcall SetArrowAngle1(int Value);
	void __fastcall SetColorFill(Graphics::TColor Value);
	void __fastcall SetColorLine(Graphics::TColor Value);
	void __fastcall SetNeedleLength(int Value);
	void __fastcall SetShadowDx(int Value);
	void __fastcall SetShadowDy(int Value);
	void __fastcall SetShadowColor(Graphics::TColor Value);
	void __fastcall SetVisible(bool Value);
	
public:
	__fastcall TNeedleLayout(void);
	__fastcall virtual ~TNeedleLayout(void);
	void __fastcall Changed(void);
	
__published:
	__property int HeadSize = {read=FSize1, write=SetArrowSize1, nodefault};
	__property int HeadAngle = {read=FAngle1, write=SetArrowAngle1, nodefault};
	__property int HeadMidLeng = {read=FBackShift1, write=SetBackShift1, nodefault};
	__property int Thickness = {read=FThickness, write=SetArrowThick, nodefault};
	__property Graphics::TColor ColorBody = {read=FColorFill, write=SetColorFill, nodefault};
	__property Graphics::TColor ColorOutline = {read=FColorLine, write=SetColorLine, nodefault};
	__property int PercentNeedleLength = {read=FPctNeedleLeng, write=SetNeedleLength, nodefault};
	__property int ShadowDx = {read=FShadowDx, write=SetShadowDx, nodefault};
	__property int ShadowDy = {read=FShadowDy, write=SetShadowDy, nodefault};
	__property Graphics::TColor ShadowColor = {read=FShadowColor, write=SetShadowColor, nodefault};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
};


class DELPHICLASS TMeter;
class PASCALIMPLEMENTATION TMeter : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	bool FAnchorCovrd;
	Graphics::TBitmap* AuxBGBmp;
	Graphics::TBitmap* AuxACBmp;
	Graphics::TBitmap* AuxACMaskBmp;
	AnsiString FBakGndFName;
	Sdlbase::TBkgFill FBGFillMode;
	AnsiString FACoverFName;
	bool FScaleVis;
	int FSizeAnchor;
	bool FLimWatHighOn;
	bool FLimWatLowOn;
	Graphics::TColor FLimWatActCol;
	Graphics::TColor FLimWatPsvCol;
	bool FOFL;
	bool FUFL;
	Graphics::TColor FColorScale;
	AnsiString FCaption;
	Sdlbase::TFrameStyle FFrameStyle;
	int FDecPlaces;
	int FNrTicks;
	int FBRim;
	int FSRim;
	int FTRim;
	bool FShortTicks;
	bool FScaleLine;
	Graphics::TColor FColorBakG;
	Graphics::TColor FColorCover;
	Graphics::TColor FColBlackLine;
	Graphics::TColor FColGrayLine;
	Graphics::TColor FColWhiteLine;
	Sdlbase::TColorScheme FColorScheme;
	Graphics::TColor FColorBakGLow;
	Graphics::TColor FColorBakGNorm;
	Graphics::TColor FColorBakGHigh;
	Graphics::TFont* FFontCaption;
	double FScaleBakWidth;
	bool FScaleBkVis;
	double FLowThreshold;
	double FHighThreshold;
	TNeedleLayout* FNeedleLayout;
	TNeedleLayout* FNeedle2Layout;
	TMeterLayout FMeterLayout;
	int FMeterAngle;
	double FMeterRadius;
	int FMeterCenterX;
	int FMeterCenterY;
	double FValue;
	double FValue2;
	double FMinValue;
	double FMaxValue;
	TMouseMoveInMeterEvent FOnMMvInMeter;
	Classes::TNotifyEvent FOnOverFlow;
	Classes::TNotifyEvent FOnUnderFlow;
	Classes::TNotifyEvent FOnNormalRange;
	TmtBeforeDrawScaleLabelEvent FOnBefDrawSclLab;
	TMeterRenderedEvent FOnMeterRendered;
	TBeforeDrawNeedleEvent FOnBefDrawNeedle;
	void __fastcall SetAnchorCovrd(bool Value);
	void __fastcall SetACoverFname(AnsiString Value);
	void __fastcall SetBakGndFname(AnsiString Value);
	void __fastcall SetBGFillMode(Sdlbase::TBkgFill Value);
	void __fastcall SetSizeAnchor(int Value);
	void __fastcall SetColorScale(Graphics::TColor Value);
	void __fastcall SetColorBakG(Graphics::TColor Value);
	void __fastcall SetColorCover(Graphics::TColor Value);
	void __fastcall SetColorScheme(Sdlbase::TColorScheme Value);
	void __fastcall SetColorBakgLow(Graphics::TColor Value);
	void __fastcall SetColorBakgNorm(Graphics::TColor Value);
	void __fastcall SetColorBakgHigh(Graphics::TColor Value);
	void __fastcall SetFrameStyle(Sdlbase::TFrameStyle value);
	void __fastcall SetDecPlaces(int Value);
	void __fastcall SetNrTicks(int Value);
	void __fastcall SetBRim(int Value);
	void __fastcall SetTRim(int Value);
	void __fastcall SetSRim(int Value);
	void __fastcall SetValue(double Value);
	void __fastcall SetValue2(double Value);
	void __fastcall SetFontCaption(Graphics::TFont* Value);
	void __fastcall SetMeterLayout(TMeterLayout Value);
	void __fastcall SetMinValue(double Value);
	void __fastcall SetMaxValue(double Value);
	void __fastcall SetLowThreshold(double Value);
	void __fastcall SetHighThreshold(double Value);
	void __fastcall SetLimWatHighOn(bool Value);
	void __fastcall SetLimWatLowOn(bool Value);
	void __fastcall SetLimWatActCol(Graphics::TColor Value);
	void __fastcall SetLimWatPsvCol(Graphics::TColor Value);
	void __fastcall SetNeedleLayout(TNeedleLayout* x);
	void __fastcall SetNeedle2Layout(TNeedleLayout* x);
	void __fastcall SetShortTicks(bool Value);
	void __fastcall SetScaleLine(bool Value);
	void __fastcall SetScaleBkWidth(double Value);
	void __fastcall SetScaleBkVis(bool Value);
	void __fastcall SetScaleVis(bool Value);
	void __fastcall SetUnitLabel(AnsiString astr);
	int __fastcall CalcM(int DecPlaces, double lo, double hi);
	MESSAGE void __fastcall WMMouseMoveInMeter(Messages::TWMMouse &Message);
	
protected:
	virtual void __fastcall Paint(void);
	void __fastcall StyleChanged(System::TObject* Sender);
	void __fastcall CalcMeterLayoutParams(void);
	virtual void __fastcall Loaded(void);
	void __fastcall DoOverFlowEvent(void);
	void __fastcall DoUnderFlowEvent(void);
	void __fastcall DoNormalRangeEvent(void);
	void __fastcall MouseMoveInMeter(bool InRange, Classes::TShiftState Shift, double MeterValue);
	
public:
	__fastcall virtual TMeter(Classes::TComponent* AOwner);
	__fastcall virtual ~TMeter(void);
	double __fastcall CalcNeedleAngle(double value);
	void __fastcall ConvertToPixelCoords(double value, double pctradius, int &X, int &Y);
	bool __fastcall ConvertPixelToValue(int XPos, int YPos, double &MeterValue);
	__property int OriginX = {read=FMeterCenterX, nodefault};
	__property int OriginY = {read=FMeterCenterY, nodefault};
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	__property double ScaleRadius = {read=FMeterRadius};
	
__published:
	__property Align  = {default=0};
	__property int AnchorSize = {read=FSizeAnchor, write=SetSizeAnchor, nodefault};
	__property bool AnchorCovered = {read=FAnchorCovrd, write=SetAnchorCovrd, nodefault};
	__property AnsiString AnchorImage = {read=FACoverFName, write=SetACoverFname};
	__property AnsiString BackGroundImg = {read=FBakGndFName, write=SetBakGndFname};
	__property Sdlbase::TBkgFill BkgndFillMode = {read=FBGFillMode, write=SetBGFillMode, nodefault};
	__property AnsiString Caption = {read=FCaption, write=SetUnitLabel};
	__property Graphics::TColor ColorBakG = {read=FColorBakG, write=SetColorBakG, nodefault};
	__property Graphics::TColor ColorCover = {read=FColorCover, write=SetColorCover, nodefault};
	__property Graphics::TColor ColorScale = {read=FColorScale, write=SetColorScale, nodefault};
	__property Sdlbase::TColorScheme ColorScheme = {read=FColorScheme, write=SetColorScheme, nodefault};
	__property Graphics::TColor ColorSclBkLow = {read=FColorBakGLow, write=SetColorBakgLow, nodefault};
	__property Graphics::TColor ColorSclBkNorm = {read=FColorBakGNorm, write=SetColorBakgNorm, nodefault};
	__property Graphics::TColor ColorSclBkHigh = {read=FColorBakGHigh, write=SetColorBakgHigh, nodefault};
	__property DragKind  = {default=0};
	__property DragCursor  = {default=-12};
	__property DragMode  = {default=0};
	__property Font ;
	__property Graphics::TFont* FontCaption = {read=FFontCaption, write=SetFontCaption};
	__property Sdlbase::TFrameStyle FrameStyle = {read=FFrameStyle, write=SetFrameStyle, nodefault};
	__property Hint ;
	__property bool LimWatchHighOn = {read=FLimWatHighOn, write=SetLimWatHighOn, nodefault};
	__property bool LimWatchLowOn = {read=FLimWatLowOn, write=SetLimWatLowOn, nodefault};
	__property Graphics::TColor LimWatchActColor = {read=FLimWatActCol, write=SetLimWatActCol, nodefault};
	__property Graphics::TColor LimWatchPsvColor = {read=FLimWatPsvCol, write=SetLimWatPsvCol, nodefault};
	__property double ThresholdLow = {read=FLowThreshold, write=SetLowThreshold};
	__property double ThresholdHigh = {read=FHighThreshold, write=SetHighThreshold};
	__property double MeterMinValue = {read=FMinValue, write=SetMinValue};
	__property double MeterMaxValue = {read=FMaxValue, write=SetMaxValue};
	__property int MeterDecPlaces = {read=FDecPlaces, write=SetDecPlaces, nodefault};
	__property int MeterNrTicks = {read=FNrTicks, write=SetNrTicks, nodefault};
	__property TMeterLayout MeterLayout = {read=FMeterLayout, write=SetMeterLayout, nodefault};
	__property bool MeterShortTicks = {read=FShortTicks, write=SetShortTicks, nodefault};
	__property bool MeterScaleLine = {read=FScaleLine, write=SetScaleLine, nodefault};
	__property TNeedleLayout* NeedleLayout = {read=FNeedleLayout, write=SetNeedleLayout};
	__property TNeedleLayout* NeedleLayoutSec = {read=FNeedle2Layout, write=SetNeedle2Layout};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property int RimBottom = {read=FBRim, write=SetBRim, nodefault};
	__property int RimTop = {read=FTRim, write=SetTRim, nodefault};
	__property int RimSide = {read=FSRim, write=SetSRim, nodefault};
	__property double ScaleBkWidth = {read=FScaleBakWidth, write=SetScaleBkWidth};
	__property bool ScaleBkVisible = {read=FScaleBkVis, write=SetScaleBkVis, nodefault};
	__property bool ScaleVisible = {read=FScaleVis, write=SetScaleVis, nodefault};
	__property ShowHint ;
	__property double Value = {read=FValue, write=SetValue};
	__property double ValueSec = {read=FValue2, write=SetValue2};
	__property Visible  = {default=1};
	__property TBeforeDrawNeedleEvent OnBeforeDrawNeedle = {read=FOnBefDrawNeedle, write=FOnBefDrawNeedle};
	__property TmtBeforeDrawScaleLabelEvent OnBeforeDrawScaleLabel = {read=FOnBefDrawSclLab, write=FOnBefDrawSclLab};
	__property OnClick ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDrag ;
	__property TMeterRenderedEvent OnMeterRendered = {read=FOnMeterRendered, write=FOnMeterRendered};
	__property OnMouseMove ;
	__property TMouseMoveInMeterEvent OnMouseMoveInMeter = {read=FOnMMvInMeter, write=FOnMMvInMeter};
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property Classes::TNotifyEvent OnNormalRange = {read=FOnNormalRange, write=FOnNormalRange};
	__property Classes::TNotifyEvent OnOverFlow = {read=FOnOverFlow, write=FOnOverFlow};
	__property OnStartDrag ;
	__property Classes::TNotifyEvent OnUnderFlow = {read=FOnUnderFlow, write=FOnUnderFlow};
};


//-- var, const, procedure ---------------------------------------------------
#define defWidth  (1.000000E+01)
#define SDLVersionInfo "meter_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;

}	/* namespace Meter */
using namespace Meter;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// meter
