// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'rchart.pas' rev: 6.00

#ifndef rchartHPP
#define rchartHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <datatable.hpp>	// Pascal unit
#include <scale.hpp>	// Pascal unit
#include <sdlbase.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Rchart
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESDLRChartError;
class PASCALIMPLEMENTATION ESDLRChartError : public Sdlbase::ESDLError 
{
	typedef Sdlbase::ESDLError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLRChartError(const AnsiString Msg) : Sdlbase::ESDLError(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLRChartError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sdlbase::ESDLError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLRChartError(int Ident)/* overload */ : Sdlbase::ESDLError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLRChartError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sdlbase::ESDLError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLRChartError(const AnsiString Msg, int AHelpContext) : Sdlbase::ESDLError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLRChartError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sdlbase::ESDLError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLRChartError(int Ident, int AHelpContext)/* overload */ : Sdlbase::ESDLError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLRChartError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sdlbase::ESDLError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLRChartError(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TCaptionAnchorHoriz { cahControlLeft, cahChartLeft, cahChartCenter, cahChartRight, cahControlRight };
#pragma option pop

#pragma option push -b-
enum TCaptionAnchorVert { cavControlTop, cavChartTop, cavChartCenter, cavChartBottom, cavControlBottom };
#pragma option pop

class DELPHICLASS TBakGndImg;
class PASCALIMPLEMENTATION TBakGndImg : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	AnsiString FName;
	Classes::TNotifyEvent FOnChange;
	bool FIncldPath;
	Sdlbase::TBkgFill FFillMode;
	void __fastcall SetName(AnsiString fn);
	void __fastcall SetIncldPath(bool x);
	void __fastcall SetFillMode(Sdlbase::TBkgFill x);
	
public:
	__fastcall TBakGndImg(Classes::TComponent* AOwner);
	__fastcall virtual ~TBakGndImg(void);
	void __fastcall Changed(void);
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	
__published:
	__property AnsiString Name = {read=FName, write=SetName};
	__property bool IncludePath = {read=FIncldPath, write=SetIncldPath, nodefault};
	__property Sdlbase::TBkgFill FillMode = {read=FFillMode, write=SetFillMode, nodefault};
};


class DELPHICLASS TJointLayers;
class PASCALIMPLEMENTATION TJointLayers : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	int FMasterLayerX[2];
	int FMasterLayerY[2];
	Classes::TNotifyEvent FOnChange;
	Classes::TComponent* FOwner;
	int __fastcall GetControlledLayerX(int Index);
	int __fastcall GetControlledLayerY(int Index);
	void __fastcall SetControlledLayerX(int Index, int Value);
	void __fastcall SetControlledLayerY(int Index, int Value);
	
protected:
	void __fastcall Changed(void);
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	
public:
	__fastcall TJointLayers(Classes::TComponent* AOwner);
	__fastcall virtual ~TJointLayers(void);
	void __fastcall Reset(void);
	
__published:
	__property int L01xControlledBy = {read=GetControlledLayerX, write=SetControlledLayerX, index=1, nodefault};
	__property int L01yControlledBy = {read=GetControlledLayerY, write=SetControlledLayerY, index=1, nodefault};
	__property int L02xControlledBy = {read=GetControlledLayerX, write=SetControlledLayerX, index=2, nodefault};
	__property int L02yControlledBy = {read=GetControlledLayerY, write=SetControlledLayerY, index=2, nodefault};
};


class DELPHICLASS TScaleProps;
class PASCALIMPLEMENTATION TScaleProps : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	AnsiString FCaption;
	int FCaptionPosX;
	int FCaptionPosY;
	Classes::TAlignment FCaptAlign;
	Scale::TScaleUnitAnchor FCaptAnchor;
	Graphics::TColor FColorScale;
	Classes::TNotifyEvent FOnChange;
	Sdlbase::TDTLabel* FDTFormat;
	int FDecPlaces;
	bool FLogAx;
	Sdlbase::TFigType FLabelType;
	Graphics::TFont* FFont;
	int FMinTicks;
	bool FNotYetLoaded;
	double FRangeLow;
	double FRangeHigh;
	bool FShortTicks;
	AnsiString FScaleInscript;
	Sdlbase::TScaleType FScaleType;
	int FScalePosX;
	int FScalePosY;
	double FMinRngDiff;
	AnsiString FUserTickText;
	bool FVisible;
	int __fastcall GetScalePos(void);
	void __fastcall SetCaption(AnsiString txt);
	void __fastcall SetCaptionPosX(int x);
	void __fastcall SetCaptionPosY(int y);
	void __fastcall SetCaptAlign(Classes::TAlignment al);
	void __fastcall SetCaptAnchor(Scale::TScaleUnitAnchor ca);
	void __fastcall SetColorScale(Graphics::TColor color);
	void __fastcall SetDTFormat(Sdlbase::TDTLabel* dtf);
	void __fastcall SetDecPlaces(int dp);
	void __fastcall SetLogAx(bool logar);
	void __fastcall SetLabelType(Sdlbase::TFigType lt);
	void __fastcall SetMinTicks(int nt);
	void __fastcall SetMinRngDiff(double minrng);
	void __fastcall SetScalePos(int p);
	void __fastcall SetRangeLow(double rl);
	void __fastcall SetRangeHigh(double rh);
	void __fastcall SetShortTicks(bool st);
	void __fastcall SetScaleInscript(AnsiString scinsc);
	void __fastcall SetScaleType(Sdlbase::TScaleType sct);
	void __fastcall SetUserTickText(AnsiString utt);
	void __fastcall SetVisible(bool vis);
	void __fastcall SetScaleFont(Graphics::TFont* ft);
	
protected:
	void __fastcall FontStyleChanged(System::TObject* Sender);
	
public:
	__fastcall TScaleProps(void);
	__fastcall virtual ~TScaleProps(void);
	void __fastcall Changed(void);
	__property Sdlbase::TScaleType ScaleType = {read=FScaleType, write=SetScaleType, nodefault};
	
__published:
	__property AnsiString Caption = {read=FCaption, write=SetCaption};
	__property int CaptionPosX = {read=FCaptionPosX, write=SetCaptionPosX, nodefault};
	__property int CaptionPosY = {read=FCaptionPosY, write=SetCaptionPosY, nodefault};
	__property Classes::TAlignment CaptionAlignment = {read=FCaptAlign, write=SetCaptAlign, nodefault};
	__property Scale::TScaleUnitAnchor CaptionAnchor = {read=FCaptAnchor, write=SetCaptAnchor, nodefault};
	__property Graphics::TColor ColorScale = {read=FColorScale, write=SetColorScale, nodefault};
	__property Sdlbase::TDTLabel* DateFormat = {read=FDTFormat, write=SetDTFormat};
	__property int DecPlaces = {read=FDecPlaces, write=SetDecPlaces, nodefault};
	__property Graphics::TFont* Font = {read=FFont, write=SetScaleFont};
	__property bool Logarithmic = {read=FLogAx, write=SetLogAx, nodefault};
	__property Sdlbase::TFigType LabelType = {read=FLabelType, write=SetLabelType, nodefault};
	__property int MinTicks = {read=FMinTicks, write=SetMinTicks, nodefault};
	__property double MinRange = {read=FMinRngDiff, write=SetMinRngDiff};
	__property double RangeLow = {read=FRangeLow, write=SetRangeLow};
	__property double RangeHigh = {read=FRangeHigh, write=SetRangeHigh};
	__property bool ShortTicks = {read=FShortTicks, write=SetShortTicks, nodefault};
	__property AnsiString ScaleInscript = {read=FScaleInscript, write=SetScaleInscript};
	__property int ScalePos = {read=GetScalePos, write=SetScalePos, nodefault};
	__property AnsiString UserTickText = {read=FUserTickText, write=SetUserTickText};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
};


#pragma option push -b-
enum TScaleLocationHoriz { slTop, slBottom };
#pragma option pop

class DELPHICLASS TScalePropsHoriz;
class PASCALIMPLEMENTATION TScalePropsHoriz : public TScaleProps 
{
	typedef TScaleProps inherited;
	
private:
	TScaleLocationHoriz FScaleLoc;
	
public:
	__fastcall TScalePropsHoriz(void);
	void __fastcall SetScaleLoc(TScaleLocationHoriz value);
	
__published:
	__property TScaleLocationHoriz ScaleLocation = {read=FScaleLoc, write=SetScaleLoc, nodefault};
public:
	#pragma option push -w-inl
	/* TScaleProps.Destroy */ inline __fastcall virtual ~TScalePropsHoriz(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TScaleLocationVert { slLeft, slRight };
#pragma option pop

class DELPHICLASS TScalePropsVert;
class PASCALIMPLEMENTATION TScalePropsVert : public TScaleProps 
{
	typedef TScaleProps inherited;
	
private:
	TScaleLocationVert FScaleLoc;
	
public:
	__fastcall TScalePropsVert(void);
	void __fastcall SetScaleLoc(TScaleLocationVert value);
	
__published:
	__property TScaleLocationVert ScaleLocation = {read=FScaleLoc, write=SetScaleLoc, nodefault};
public:
	#pragma option push -w-inl
	/* TScaleProps.Destroy */ inline __fastcall virtual ~TScalePropsVert(void) { }
	#pragma option pop
	
};


class DELPHICLASS TTextLabel;
class PASCALIMPLEMENTATION TTextLabel : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	double FPosX;
	double FPosY;
	int FLayer;
	int FXShadow;
	int FYShadow;
	Graphics::TColor FColorShadow;
	Classes::TAlignment FAlignment;
	bool FAttachDat;
	Graphics::TColor FColorBkg;
	Graphics::TColor FColorBrd;
	bool FTransPar;
	Graphics::TFont* FFont;
	AnsiString FCaption;
	Sdlbase::TTxtLblMode FMode;
	Classes::TNotifyEvent FOnChange;
	void __fastcall SetTxtLblAlignment(Classes::TAlignment al);
	void __fastcall SetTxtLblPosX(double value);
	void __fastcall SetTxtLblPosY(double value);
	void __fastcall SetTxtLblColorBkg(Graphics::TColor value);
	void __fastcall SetTxtLblColorBrd(Graphics::TColor value);
	void __fastcall SetTxtLblColorShadow(Graphics::TColor value);
	void __fastcall SetTxtLblLayer(int value);
	void __fastcall SetTxtLblTranspar(bool value);
	void __fastcall SetTxtLblMode(Sdlbase::TTxtLblMode value);
	void __fastcall SetTxtLblFont(Graphics::TFont* value);
	void __fastcall SetTxtLblCaption(AnsiString value);
	void __fastcall SetTxtLblScreenPos(bool value);
	void __fastcall SetTxtLblShadowDx(int value);
	void __fastcall SetTxtLblShadowDy(int value);
	
public:
	void __fastcall Changed(void);
	
__published:
	__property double PosX = {read=FPosX, write=SetTxtLblPosX};
	__property double PosY = {read=FPosY, write=SetTxtLblPosY};
	__property int Layer = {read=FLayer, write=SetTxtLblLayer, nodefault};
	__property bool AttachToData = {read=FAttachDat, write=SetTxtLblScreenPos, nodefault};
	__property Graphics::TColor ColorBkg = {read=FColorBkg, write=SetTxtLblColorBkg, nodefault};
	__property Graphics::TColor ColorBorder = {read=FColorBrd, write=SetTxtLblColorBrd, nodefault};
	__property Graphics::TColor ColorShadow = {read=FColorShadow, write=SetTxtLblColorShadow, nodefault};
	__property int ShadowDx = {read=FXShadow, write=SetTxtLblShadowDx, nodefault};
	__property int ShadowDy = {read=FYShadow, write=SetTxtLblShadowDy, nodefault};
	__property bool Transparent = {read=FTransPar, write=SetTxtLblTranspar, nodefault};
	__property Classes::TAlignment Alignment = {read=FAlignment, write=SetTxtLblAlignment, nodefault};
	__property Graphics::TFont* Font = {read=FFont, write=SetTxtLblFont};
	__property Sdlbase::TTxtLblMode Mode = {read=FMode, write=SetTxtLblMode, nodefault};
	__property AnsiString Caption = {read=FCaption, write=SetTxtLblCaption};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TTextLabel(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TTextLabel(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


#pragma option push -b-
enum TrcItem { tkNone, tkMarkAt, tkLine, tkLineto, tkRect, tkRectFrame, tk3DBar, tkText, tkMoveTo, tkEllipse, tkEverything, tkNotMoveTo, tkMoveRelPix, tkLineRelPix, tkArrow };
#pragma option pop

struct TrcChartItem
{
	double x;
	double y;
	double x2;
	double y2;
	Graphics::TColor Color;
	Graphics::TColor FillColor;
	Graphics::TColor ShadowColor;
	Graphics::TColor HiLightColor;
	Graphics::TPenStyle PenStyle;
	int Tag;
	int LWid;
	Byte ItemClass;
	TrcItem ItemKind;
	int Layer;
	bool Transp;
	Sdlbase::TFrameStyle FrameStyle;
	System::SmallString<15>  Text;
	int SizeOrAngle;
	int Depth;
	Byte mark;
} ;

#pragma option push -b-
enum GridStyleType { gsNone, gsPoints, gsVertLines, gsHorizLines, gsLines, gsHorizDotLines, gsVertDotLines, gsDotLines };
#pragma option pop

#pragma option push -b-
enum TrcLayout { rcl_X1Bottom_Y1Left, rcl_X1Bottom_Y2Left, rcl_X1Bottom_Y2Both, rcl_X2Bottom_Y2Left, rcl_X2Both_Y2Both };
#pragma option pop

#pragma option push -b-
enum TTextBkg { tbClear, tbSolid };
#pragma option pop

typedef void __fastcall (__closure *TMouseMoveInChartEvent)(System::TObject* Sender, bool InChart, Classes::TShiftState Shift, double rMousePosX, double rMousePosY);

typedef void __fastcall (__closure *TRenderEvent)(System::TObject* Sender, Graphics::TCanvas* &Canvas, int Top, int Left);

typedef void __fastcall (__closure *TCrossHairMoveEvent)(System::TObject* Sender, Sdlbase::TCrossHair* WhichCrossHair);

typedef void __fastcall (__closure *TTextLabelMoveEvent)(System::TObject* Sender, TTextLabel* WhichTextLabel);

typedef DynamicArray<TrcChartItem >  rchart__9;

class DELPHICLASS TCustomRChart;
class PASCALIMPLEMENTATION TCustomRChart : public Controls::TCustomControl 
{
	typedef Controls::TCustomControl inherited;
	
private:
	int FNumChartItems;
	int FNumAllocated;
	int FAllocSize;
	bool LButtonWasDown;
	int FMAnchorScrX[2];
	int FMAnchorScrY[2];
	double FMAnchorRcLoX[2];
	double FMAnchorRcLoY[2];
	double FMAnchorRcHiX[2];
	double FMAnchorRcHiY[2];
	Sdlbase::TZoomState FZoomState;
	TrcLayout FStdLayout;
	Sdlbase::TMouseBoxState MouseBoxState;
	int LastMouseX;
	int LastMouseY;
	int MouseBoxX1;
	int MouseBoxX2;
	int MouseBoxY1;
	int MouseBoxY2;
	int WindAnchorX;
	int WindAnchorY;
	int WindOldCornerX;
	int WindOldCornerY;
	TCustomRChart* FUseDataOf;
	TCustomRChart* FDataUsers[4];
	int FDataUsersNum;
	bool FItClassVisib[256];
	bool FLayerVisib[2];
	TMouseMoveInChartEvent FOnMMvInChart;
	Sdlbase::TZoomPanEvent FOnZoomPan;
	Scale::TScaleTickDrawnEvent FOnScaleTickDrawn;
	TRenderEvent FOnDataRendered;
	TRenderEvent FOnBefRenderData;
	TRenderEvent FOnScalesRendered;
	TCrossHairMoveEvent FOnCrossHMove;
	TTextLabelMoveEvent FOnTxtLblMove;
	Graphics::TBitmap* AuxBmp;
	Graphics::TBitmap* GrafBmp;
	Graphics::TBitmap* ChartBmp;
	TBakGndImg* FBakGndFile;
	TJointLayers* FJointLayers;
	int FDataTag;
	GridStyleType RcGridStyle;
	Graphics::TColor RcGridCol;
	double RcGridDx;
	double RcGridDy;
	int RcLRim;
	int RcRRim;
	int RcTRim;
	int RcBRim;
	int F3DRim;
	Sdlbase::TShadowStyle RcShadowStyle;
	Graphics::TColor FShadowColor;
	Graphics::TColor RcShadowBakCol;
	Sdlbase::TMouseActMode RcMouseAction;
	Graphics::TColor RcDataCol;
	Graphics::TColor FChartFrameCol;
	Graphics::TColor RcFillCol;
	Graphics::TColor RcChartCol;
	Graphics::TPenStyle RcPenStyle;
	Graphics::TColor RcWindCol;
	Byte RcLineWid;
	AnsiString FChartCaption;
	int FCaptPosX;
	int FCaptPosY;
	Classes::TAlignment FCaptAlignment;
	TCaptionAnchorHoriz FCaptAnchorX;
	TCaptionAnchorVert FCaptAnchorY;
	Byte RcClassDefault;
	int FActiveLayer;
	bool FMouseAffLayer[2];
	Extended Cpkx[2];
	Extended Cpdx[2];
	Extended Cpky[2];
	Extended Cpdy[2];
	Sdlbase::TFigType RcXLabelType;
	Sdlbase::TFigType RcYLabelType;
	double FMousePosX;
	double FMousePosY;
	bool FMCurFixed;
	Sdlbase::TCrossHair* FCrossHair[4];
	TTextLabel* FTextLabels[20];
	Scale::TScale* FScalesX[2];
	Scale::TScale* FScalesY[2];
	TScalePropsHoriz* FScalePropsX[2];
	TScalePropsVert* FScalePropsY[2];
	int CHNext;
	int TLNext;
	bool FAutoRedraw;
	int FNumPPa;
	Graphics::TFontStyles FTextFontStyle;
	TTextBkg FTextBkStyle;
	Graphics::TColor FTextBkColor;
	Classes::TAlignment FTextAlignment;
	int Fxasp;
	int Fyasp;
	bool FIsometric;
	bool FSuppressPaint;
	bool FTranspItems;
	Sdlbase::TRectDouble FZoomStack[2][16];
	int FZStackPoi;
	Extended FZoomRange[4];
	AnsiString __fastcall AddScaleInscription(AnsiString Instring, AnsiString Inscr);
	void __fastcall AdjustCanInfoOfSharedCharts(void);
	virtual void __fastcall AdjustScaling(void);
	void __fastcall ConstructChartBmp(Graphics::TCanvas* cv);
	void __fastcall ConstructDataBmp(Graphics::TCanvas* cv, int PosX, int PosY, bool BlkWhite, int FirstItem);
	void __fastcall DrawFinish(int xPos, int yPos, Graphics::TBitmap* SrcBmp);
	AnsiString __fastcall ExtractUserText(AnsiString TickText, int ix);
	void __fastcall ForceRange(int Layer, Extended xLo, Extended yLo, Extended xHi, Extended yHi, bool EnterToZoomStack, bool ConfineRange);
	void __fastcall ForceRngIntern(int Layer, Extended xLo, Extended yLo, Extended xHi, Extended yHi, bool EnterToZoomStack, bool ConfineRange);
	void __fastcall SetRangeIntern(int Layer, Extended xLo, Extended yLo, Extended xHi, Extended yHi, bool EnterToZoomStack, bool ConfineRange);
	TrcItem __fastcall GetTypeOfFirstItem(void);
	TrcItem __fastcall GetTypeOfLastItem(void);
	bool __fastcall GetClassVisib(Byte cnum);
	TrcChartItem __fastcall GetChartItem(int idx);
	double __fastcall GetCHPosX(int chnum);
	double __fastcall GetCHPosY(int chnum);
	Sdlbase::TCrossHair* __fastcall GetCrossHair1(void);
	Sdlbase::TCrossHair* __fastcall GetCrossHair2(void);
	Sdlbase::TCrossHair* __fastcall GetCrossHair3(void);
	Sdlbase::TCrossHair* __fastcall GetCrossHair4(void);
	bool __fastcall GetLayerVisib(int Layer);
	bool __fastcall GetMAffLayer(int layer);
	TScalePropsHoriz* __fastcall GetScalePropsX1(void);
	TScalePropsVert* __fastcall GetScalePropsY1(void);
	TScalePropsHoriz* __fastcall GetScalePropsX2(void);
	TScalePropsVert* __fastcall GetScalePropsY2(void);
	TScalePropsHoriz* __fastcall GetScalePropsX(int sclix);
	TScalePropsVert* __fastcall GetScalePropsY(int sclix);
	int __fastcall GetItemCount(TrcItem it);
	TTextLabel* __fastcall GetFTextLabel(int ix);
	double __fastcall GetTickPosX(int ix);
	int __fastcall GetTickPosXCnt(void);
	double __fastcall GetTickPosY(int ix);
	int __fastcall GetTickPosYCnt(void);
	double __fastcall GetMousePosX(void);
	double __fastcall GetMousePosY(void);
	Sdlbase::TRectDouble __fastcall GetZoomStackEntry(int Layer, int StackIx);
	void __fastcall InitGraf(Graphics::TCanvas* cv, int PosX, int PosY);
	void __fastcall LLCalcExtents(int Layer, double Rim, double &xLo, double &yLo, double &xHi, double &yHi);
	void __fastcall LLCalcMinMax(int Layer, double RangeLoX, double RangeLoY, double RangeHiX, double RangeHiY, double &xLo, double &yLo, double &xHi, double &yHi);
	void __fastcall SetAllocSize(int alloc);
	void __fastcall SetActiveLayer(int lay);
	void __fastcall SetChartitem(int idx, const TrcChartItem &item);
	void __fastcall SetClassVisib(Byte cnum, bool value);
	void __fastcall SetCHPosX(int chnum, double value);
	void __fastcall SetCHPosY(int chnum, double value);
	void __fastcall SetLRim(int r);
	void __fastcall SetRRim(int r);
	void __fastcall SetTRim(int r);
	void __fastcall SetBRim(int r);
	void __fastcall SetIsoMetric(bool im);
	void __fastcall SetLayerVisib(int Layer, bool value);
	void __fastcall SetMAffLayer(int layer, bool value);
	void __fastcall SetUseDataOf(TCustomRChart* orc);
	void __fastcall SetF3DRim(int r);
	void __fastcall SetDataTag(int tag);
	void __fastcall SetShadowStyle(Sdlbase::TShadowStyle ss);
	void __fastcall SetShadowColor(Graphics::TColor c);
	void __fastcall SetShadowBakColor(Graphics::TColor c);
	void __fastcall SetClassDefault(Byte DefClass);
	void __fastcall SetCrossHair1(Sdlbase::TCrossHair* x);
	void __fastcall SetCrossHair2(Sdlbase::TCrossHair* x);
	void __fastcall SetCrossHair3(Sdlbase::TCrossHair* x);
	void __fastcall SetCrossHair4(Sdlbase::TCrossHair* x);
	void __fastcall SetScalePropsX1(TScalePropsHoriz* x);
	void __fastcall SetScalePropsY1(TScalePropsVert* x);
	void __fastcall SetScalePropsX2(TScalePropsHoriz* x);
	void __fastcall SetScalePropsY2(TScalePropsVert* x);
	void __fastcall SetScalePropsX(int sclix, TScalePropsHoriz* x);
	void __fastcall SetScalePropsY(int sclix, TScalePropsVert* x);
	void __fastcall SetScaleProps(Scale::TScale* &Scl, TScaleProps* SclProps);
	void __fastcall SetSuppressPaint(bool supp);
	void __fastcall SetGridStyle(GridStyleType gs);
	void __fastcall SetGridDx(double dx);
	void __fastcall SetGridDy(double dy);
	void __fastcall SetDataCol(Graphics::TColor c);
	void __fastcall SetScaleCol(Graphics::TColor c);
	void __fastcall SetFillCol(Graphics::TColor c);
	void __fastcall SetChartCol(Graphics::TColor c);
	void __fastcall SetWindCol(Graphics::TColor c);
	void __fastcall SetGridCol(Graphics::TColor c);
	void __fastcall SetChartCaption(AnsiString hstr);
	void __fastcall SetCaptPosX(int p);
	void __fastcall SetCaptPosY(int p);
	void __fastcall SetCaptAlignment(Classes::TAlignment al);
	void __fastcall SetCaptAnchorX(TCaptionAnchorHoriz ca);
	void __fastcall SetCaptAnchorY(TCaptionAnchorVert ca);
	void __fastcall SetPenStyle(Graphics::TPenStyle ps);
	void __fastcall SetLineWid(Byte w);
	MESSAGE void __fastcall WMMouseMoveInChart(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &msg);
	MESSAGE void __fastcall WMGetDlgCode(Messages::TWMNoParams &message);
	void __fastcall SetTextFontStyle(Graphics::TFontStyles tfs);
	void __fastcall SetTextBkStyle(TTextBkg bs);
	void __fastcall SetTextBkColor(Graphics::TColor bc);
	void __fastcall SetTextAlignment(Classes::TAlignment al);
	void __fastcall SetFTextLabel(int ix, TTextLabel* value);
	void __fastcall SetJointLayers(TJointLayers* value);
	void __fastcall SetBakGndFile(TBakGndImg* x);
	void __fastcall SetStdLayout(TrcLayout lyt);
	void __fastcall ZoomStateOnStack(void);
	
protected:
	DynamicArray<TrcChartItem >  FDataContainer;
	int FLastElemOnShow;
	int FItemCount[15];
	virtual void __fastcall Paint(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall CreateWnd(void);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	void __fastcall MouseMoveInChart(bool InChart, Classes::TShiftState Shift, double RMousePosX, double RMousePosY);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	void __fastcall StyleChanged(System::TObject* Sender);
	void __fastcall ScalePropsChanged(System::TObject* Sender);
	void __fastcall DoOnScaleTickDrawn(System::TObject* Sender, Graphics::TCanvas* &Canvas, Sdlbase::TScaleType ScaleType, double CurrentTickPos, int ChartX, int ChartY);
	void __fastcall DoZoomPanEvent(void);
	void __fastcall DoCrossHMoveEvent(Sdlbase::TCrossHair* WhichCH);
	void __fastcall DoTxtLblMoveEvent(TTextLabel* WhichTL);
	void __fastcall M2R(int Layer, int xin, int yin, double &xout, double &yout);
	void __fastcall R2M(int Layer, double xin, double yin, int &xout, int &yout);
	void __fastcall ClearGraf(void);
	void __fastcall ConfineZoomRange(double xLo, double yLo, double xHi, double yHi);
	void __fastcall ShowGraf(void);
	void __fastcall ShowGrafNewOnly(void);
	bool __fastcall MouseBox(double &xLo, double &yLo, double &xHi, double &yHi);
	void __fastcall MouseBoxAbort(void);
	__property int ActiveLayer = {read=FActiveLayer, write=SetActiveLayer, nodefault};
	int __fastcall AddTextLabel(double PosX, double PosY, Graphics::TColor TxtColor, AnsiString Txt, int PropertyTemplate);
	void __fastcall AllTextLabelsOff(void);
	void __fastcall Arrow(double x1, double y1, double x2, double y2, int HeadSize);
	void __fastcall Bar3D(double llx, double lly, double urx, double ury, int Depth, int Angle);
	void __fastcall ClearZoomHistory(void);
	void __fastcall CopyToBitmap(Graphics::TBitmap* ABitmap, bool BlkWhite);
	void __fastcall CopyToBMP(AnsiString FName, bool BlkWhite);
	void __fastcall CopyToClipboard(bool BlkWhite);
	void __fastcall CopyToClipboardWMF(bool BlkWhite);
	void __fastcall CopyToWMF(AnsiString FName, bool BlkWhite);
	void __fastcall CopyToOpenPrinter(int &x, int &y, double ScaleF, bool BlkWhite);
	void __fastcall PrintIt(double ScaleF, bool BlkWhite);
	__property TrcChartItem DataContainer[int idx] = {read=GetChartItem, write=SetChartitem};
	__property double CrossHairPosX[int chnum] = {read=GetCHPosX, write=SetCHPosX};
	__property double CrossHairPosY[int chnum] = {read=GetCHPosY, write=SetCHPosY};
	void __fastcall CrossHairSetPos(int chnum, double x, double y);
	void __fastcall CrossHairSetup(int ch, Graphics::TColor chColor, Sdlbase::TCrossHMode Mode, Graphics::TPenStyle LineType, int LineWidth);
	__property int DataTag = {read=FDataTag, write=SetDataTag, nodefault};
	void __fastcall DrawTo(double x, double y);
	void __fastcall DrawToRelPix(int dx, int dy);
	void __fastcall Ellipse(double cx, double cy, double HorizAxLeng, double VertAxLeng);
	void __fastcall Line(double x1, double y1, double x2, double y2);
	void __fastcall MoveTo(double x, double y);
	void __fastcall MoveToRelPix(int dx, int dy);
	void __fastcall MarkAt(double x, double y, Byte mk);
	void __fastcall Rectangle(double x1, double y1, double x2, double y2);
	void __fastcall RectFrame(double x1, double y1, double x2, double y2, Sdlbase::TFrameStyle FrameStyle, Graphics::TColor ShadowColor, Graphics::TColor HiLightColor);
	void __fastcall SaveDataASC(AnsiString FName);
	void __fastcall SaveData(AnsiString FName);
	void __fastcall LoadData(AnsiString FName, bool AppendIt);
	void __fastcall SetRange(int Layer, Extended xLo, Extended yLo, Extended xHi, Extended yHi);
	void __fastcall AutoRange(int Layer, double Margin);
	void __fastcall AutoRangeXOnly(int Layer, double Margin);
	void __fastcall AutoRangeYOnly(int Layer, double Margin);
	HIDESBASE void __fastcall Text(double x, double y, int size, AnsiString txt);
	void __fastcall RemoveLastItem(void);
	void __fastcall RemoveFirstItem(void);
	void __fastcall RemoveItem(int Index);
	int __fastcall RemoveItemsByClass(Byte ClassNumber);
	void __fastcall FindMinMax(int Layer, double RangeLoX, double RangeLoY, double RangeHiX, double RangeHiY, double &MinX, double &MinY, double &MaxX, double &MaxY);
	int __fastcall FindNearestItemReal(double mx, double my, TrcItem ItemID, Byte ClassNumber, double &Dist);
	int __fastcall FindNearestItemScreen(double mx, double my, TrcItem ItemID, Byte ClassNumber, double &Dist);
	TrcChartItem __fastcall GetItemParams(int Item);
	__property int ItemCount[TrcItem it] = {read=GetItemCount};
	void __fastcall SetItemParams(int Item, const TrcChartItem &ItParams);
	void __fastcall ScaleItem(int Item, double kx, double dx, double ky, double dy);
	int __fastcall MarkItemsInWindow(double xLo, double YLo, double XHi, double YHi, TrcItem ItemID, Byte ClassNumber);
	void __fastcall MarkAllItems(TrcItem ItemID, Byte ClassNumber);
	__property bool MouseAffectsLayer[int Layer] = {read=GetMAffLayer, write=SetMAffLayer};
	__property double MousePosX = {read=GetMousePosX};
	__property double MousePosY = {read=GetMousePosY};
	__property int NumItems = {read=FNumChartItems, nodefault};
	__property bool ClassVisible[Byte cnum] = {read=GetClassVisib, write=SetClassVisib};
	__property bool LayerVisible[int layer] = {read=GetLayerVisib, write=SetLayerVisib};
	void __fastcall ScaleAllItems(double kx, double dx, double ky, double dy);
	__property TScalePropsHoriz* ScalePropsX[int SclIx] = {read=GetScalePropsX, write=SetScalePropsX};
	__property TScalePropsVert* ScalePropsY[int SclIx] = {read=GetScalePropsY, write=SetScalePropsY};
	void __fastcall ScaleSelectedItems(double kx, double dx, double ky, double dy, Byte ClassNumber);
	void __fastcall SetTextLabel(int Idx, double PosX, double PosY, Graphics::TColor TxtColor, AnsiString Txt, int PropertyTemplate);
	__property bool SuppressPaint = {read=FSuppressPaint, write=SetSuppressPaint, nodefault};
	__property bool TransparentItems = {read=FTranspItems, write=FTranspItems, nodefault};
	__property TrcItem TypeOfLastItem = {read=GetTypeOfLastItem, nodefault};
	__property TrcItem TypeOfFirstItem = {read=GetTypeOfFirstItem, nodefault};
	void __fastcall NewColorOfClassItems(Graphics::TColor Newcol, Byte ClassNumber);
	__property TTextLabel* TextLabels[int ix] = {read=GetFTextLabel, write=SetFTextLabel};
	__property double TickPosX[int ix] = {read=GetTickPosX};
	__property double TickPosY[int iy] = {read=GetTickPosY};
	__property int TickNumX = {read=GetTickPosXCnt, nodefault};
	__property int TickNumY = {read=GetTickPosYCnt, nodefault};
	__property Sdlbase::TZoomState ZoomState = {read=FZoomState, nodefault};
	void __fastcall ZoomHistory(int Index);
	__property Sdlbase::TRectDouble ZoomStack[int Layer][int StackIx] = {read=GetZoomStackEntry};
	__property Font ;
	__property Align  = {default=0};
	__property Visible  = {default=1};
	__property ShowHint ;
	__property PopupMenu ;
	__property Anchors  = {default=3};
	__property Constraints ;
	__property DragKind  = {default=0};
	__property DragCursor  = {default=-12};
	__property DragMode  = {default=0};
	__property int AllocSize = {read=FAllocSize, write=SetAllocSize, nodefault};
	__property bool AutoRedraw = {read=FAutoRedraw, write=FAutoRedraw, nodefault};
	__property int LRim = {read=RcLRim, write=SetLRim, default=50};
	__property int RRim = {read=RcRRim, write=SetRRim, default=10};
	__property int TRim = {read=RcTRim, write=SetTRim, default=16};
	__property int BRim = {read=RcBRim, write=SetBRim, default=32};
	__property TBakGndImg* BackGroundImg = {read=FBakGndFile, write=SetBakGndFile};
	__property Byte ClassDefault = {read=RcClassDefault, write=SetClassDefault, nodefault};
	__property GridStyleType GridStyle = {read=RcGridStyle, write=SetGridStyle, nodefault};
	__property double GridDx = {read=RcGridDx, write=SetGridDx};
	__property double GridDy = {read=RcGridDy, write=SetGridDy};
	__property bool Isometric = {read=FIsometric, write=SetIsoMetric, nodefault};
	__property Graphics::TColor DataColor = {read=RcDataCol, write=SetDataCol, default=0};
	__property Graphics::TPenStyle PenStyle = {read=RcPenStyle, write=SetPenStyle, default=0};
	__property Graphics::TColor ChartFrameColor = {read=FChartFrameCol, write=SetScaleCol, default=0};
	__property Graphics::TColor FillColor = {read=RcFillCol, write=SetFillCol, default=12632256};
	__property Graphics::TColor ChartColor = {read=RcChartCol, write=SetChartCol, default=16777215};
	__property Graphics::TColor WindColor = {read=RcWindCol, write=SetWindCol, default=-2147483633};
	__property Graphics::TColor GridColor = {read=RcGridCol, write=SetGridCol, default=0};
	__property TJointLayers* JointLayers = {read=FJointLayers, write=SetJointLayers};
	__property Byte LineWidth = {read=RcLineWid, write=SetLineWid, default=1};
	__property AnsiString Caption = {read=FChartCaption, write=SetChartCaption};
	__property int CaptionPosX = {read=FCaptPosX, write=SetCaptPosX, nodefault};
	__property int CaptionPosY = {read=FCaptPosY, write=SetCaptPosY, nodefault};
	__property Classes::TAlignment CaptionAlignment = {read=FCaptAlignment, write=SetCaptAlignment, nodefault};
	__property TCaptionAnchorHoriz CaptionAnchorHoriz = {read=FCaptAnchorX, write=SetCaptAnchorX, nodefault};
	__property TCaptionAnchorVert CaptionAnchorVert = {read=FCaptAnchorY, write=SetCaptAnchorY, nodefault};
	__property Sdlbase::TCrossHair* CrossHair1 = {read=GetCrossHair1, write=SetCrossHair1};
	__property Sdlbase::TCrossHair* CrossHair2 = {read=GetCrossHair2, write=SetCrossHair2};
	__property Sdlbase::TCrossHair* CrossHair3 = {read=GetCrossHair3, write=SetCrossHair3};
	__property Sdlbase::TCrossHair* CrossHair4 = {read=GetCrossHair4, write=SetCrossHair4};
	__property Sdlbase::TMouseActMode MouseAction = {read=RcMouseAction, write=RcMouseAction, nodefault};
	__property bool MouseCursorFixed = {read=FMCurFixed, write=FMCurFixed, nodefault};
	__property TScalePropsHoriz* Scale1X = {read=GetScalePropsX1, write=SetScalePropsX1};
	__property TScalePropsVert* Scale1Y = {read=GetScalePropsY1, write=SetScalePropsY1};
	__property TScalePropsHoriz* Scale2X = {read=GetScalePropsX2, write=SetScalePropsX2};
	__property TScalePropsVert* Scale2Y = {read=GetScalePropsY2, write=SetScalePropsY2};
	__property TrcLayout StandardLayout = {read=FStdLayout, write=SetStdLayout, stored=false, nodefault};
	__property int ShadowWidth = {read=F3DRim, write=SetF3DRim, default=0};
	__property Sdlbase::TShadowStyle ShadowStyle = {read=RcShadowStyle, write=SetShadowStyle, nodefault};
	__property Graphics::TColor ShadowColor = {read=FShadowColor, write=SetShadowColor, nodefault};
	__property Graphics::TColor ShadowBakColor = {read=RcShadowBakCol, write=SetShadowBakColor, nodefault};
	__property TCustomRChart* UseDataOf = {read=FUseDataOf, write=SetUseDataOf};
	__property Graphics::TFontStyles TextFontStyle = {read=FTextFontStyle, write=SetTextFontStyle, nodefault};
	__property TTextBkg TextBkStyle = {read=FTextBkStyle, write=SetTextBkStyle, nodefault};
	__property Graphics::TColor TextBkColor = {read=FTextBkColor, write=SetTextBkColor, nodefault};
	__property Classes::TAlignment TextAlignment = {read=FTextAlignment, write=SetTextAlignment, nodefault};
	__property OnClick ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDrag ;
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property OnKeyDown ;
	__property OnKeyUp ;
	__property OnKeyPress ;
	__property TMouseMoveInChartEvent OnMouseMoveInChart = {read=FOnMMvInChart, write=FOnMMvInChart};
	__property Sdlbase::TZoomPanEvent OnZoomPan = {read=FOnZoomPan, write=FOnZoomPan};
	__property Scale::TScaleTickDrawnEvent OnScaleTickDrawn = {read=FOnScaleTickDrawn, write=FOnScaleTickDrawn};
	__property TRenderEvent OnBeforeRenderData = {read=FOnBefRenderData, write=FOnBefRenderData};
	__property TRenderEvent OnDataRendered = {read=FOnDataRendered, write=FOnDataRendered};
	__property TRenderEvent OnScalesRendered = {read=FOnScalesRendered, write=FOnScalesRendered};
	__property OnStartDrag ;
	__property TCrossHairMoveEvent OnCrossHairMove = {read=FOnCrossHMove, write=FOnCrossHMove};
	__property TTextLabelMoveEvent OnTextLabelMove = {read=FOnTxtLblMove, write=FOnTxtLblMove};
	__property OnCanResize ;
	__property OnResize ;
	
public:
	__fastcall virtual TCustomRChart(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomRChart(void);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TCustomRChart(HWND ParentWindow) : Controls::TCustomControl(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TRChart;
class PASCALIMPLEMENTATION TRChart : public TCustomRChart 
{
	typedef TCustomRChart inherited;
	
public:
	HIDESBASE void __fastcall M2R(int Layer, int xin, int yin, double &xout, double &yout);
	HIDESBASE void __fastcall R2M(int Layer, double xin, double yin, int &xout, int &yout);
	HIDESBASE void __fastcall ClearGraf(void);
	HIDESBASE void __fastcall ConfineZoomRange(double xLo, double yLo, double xHi, double yHi);
	HIDESBASE void __fastcall ShowGraf(void);
	HIDESBASE void __fastcall ShowGrafNewOnly(void);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	HIDESBASE bool __fastcall MouseBox(double &xLo, double &yLo, double &xHi, double &yHi);
	HIDESBASE void __fastcall MouseBoxAbort(void);
	__property ActiveLayer ;
	HIDESBASE int __fastcall AddTextLabel(double PosX, double PosY, Graphics::TColor TxtColor, AnsiString Txt, int PropertyTemplate);
	HIDESBASE void __fastcall AllTextLabelsOff(void);
	HIDESBASE void __fastcall Arrow(double x1, double y1, double x2, double y2, int HeadSize);
	HIDESBASE void __fastcall Bar3D(double llx, double lly, double urx, double ury, int Depth, int Angle);
	HIDESBASE void __fastcall ClearZoomHistory(void);
	HIDESBASE void __fastcall CopyToBitmap(Graphics::TBitmap* ABitmap, bool BlkWhite);
	HIDESBASE void __fastcall CopyToBMP(AnsiString FName, bool BlkWhite);
	HIDESBASE void __fastcall CopyToClipboard(bool BlkWhite);
	HIDESBASE void __fastcall CopyToClipboardWMF(bool BlkWhite);
	HIDESBASE void __fastcall CopyToWMF(AnsiString FName, bool BlkWhite);
	HIDESBASE void __fastcall CopyToOpenPrinter(int &x, int &y, double ScaleF, bool BlkWhite);
	HIDESBASE void __fastcall PrintIt(double ScaleF, bool BlkWhite);
	__property DataContainer ;
	__property CrossHairPosX ;
	__property CrossHairPosY ;
	HIDESBASE void __fastcall CrossHairSetPos(int chnum, double x, double y);
	HIDESBASE void __fastcall CrossHairSetup(int ch, Graphics::TColor chColor, Sdlbase::TCrossHMode Mode, Graphics::TPenStyle LineType, int LineWidth);
	__property DataTag ;
	HIDESBASE void __fastcall DrawTo(double x, double y);
	HIDESBASE void __fastcall DrawToRelPix(int dx, int dy);
	HIDESBASE void __fastcall Ellipse(double cx, double cy, double HorizAxLeng, double VertAxLeng);
	HIDESBASE void __fastcall Line(double x1, double y1, double x2, double y2);
	HIDESBASE void __fastcall MoveTo(double x, double y);
	HIDESBASE void __fastcall MoveToRelPix(int dx, int dy);
	HIDESBASE void __fastcall MarkAt(double x, double y, Byte mk);
	HIDESBASE void __fastcall Rectangle(double x1, double y1, double x2, double y2);
	HIDESBASE void __fastcall RectFrame(double x1, double y1, double x2, double y2, Sdlbase::TFrameStyle FrameStyle, Graphics::TColor ShadowColor, Graphics::TColor HiLightColor);
	HIDESBASE void __fastcall SaveDataASC(AnsiString FName);
	HIDESBASE void __fastcall SaveData(AnsiString FName);
	HIDESBASE void __fastcall LoadData(AnsiString FName, bool AppendIt);
	HIDESBASE void __fastcall SetRange(int Layer, Extended xLo, Extended yLo, Extended xHi, Extended yHi);
	HIDESBASE void __fastcall AutoRange(int Layer, double Margin);
	HIDESBASE void __fastcall AutoRangeXOnly(int Layer, double Margin);
	HIDESBASE void __fastcall AutoRangeYOnly(int Layer, double Margin);
	HIDESBASE void __fastcall Text(double x, double y, int size, AnsiString txt);
	HIDESBASE void __fastcall RemoveLastItem(void);
	HIDESBASE void __fastcall RemoveFirstItem(void);
	HIDESBASE void __fastcall RemoveItem(int Index);
	HIDESBASE int __fastcall RemoveItemsByClass(Byte ClassNumber);
	HIDESBASE void __fastcall FindMinMax(int Layer, double RangeLoX, double RangeLoY, double RangeHiX, double RangeHiY, double &MinX, double &MinY, double &MaxX, double &MaxY);
	HIDESBASE int __fastcall FindNearestItemReal(double mx, double my, TrcItem ItemID, Byte ClassNumber, double &Dist);
	HIDESBASE int __fastcall FindNearestItemScreen(double mx, double my, TrcItem ItemID, Byte ClassNumber, double &Dist);
	HIDESBASE TrcChartItem __fastcall GetItemParams(int Item);
	__property ItemCount ;
	HIDESBASE void __fastcall SetItemParams(int Item, const TrcChartItem &ItParams);
	HIDESBASE void __fastcall ScaleItem(int Item, double kx, double dx, double ky, double dy);
	HIDESBASE int __fastcall MarkItemsInWindow(double xLo, double YLo, double XHi, double YHi, TrcItem ItemID, Byte ClassNumber);
	HIDESBASE void __fastcall MarkAllItems(TrcItem ItemID, Byte ClassNumber);
	__property MouseAffectsLayer ;
	__property MousePosX ;
	__property MousePosY ;
	__property NumItems ;
	__property ClassVisible ;
	__property LayerVisible ;
	HIDESBASE void __fastcall ScaleAllItems(double kx, double dx, double ky, double dy);
	__property ScalePropsX ;
	__property ScalePropsY ;
	HIDESBASE void __fastcall ScaleSelectedItems(double kx, double dx, double ky, double dy, Byte ClassNumber);
	HIDESBASE void __fastcall SetTextLabel(int Idx, double PosX, double PosY, Graphics::TColor TxtColor, AnsiString Txt, int PropertyTemplate);
	__property SuppressPaint ;
	__property TransparentItems ;
	__property TypeOfLastItem ;
	__property TypeOfFirstItem ;
	HIDESBASE void __fastcall NewColorOfClassItems(Graphics::TColor Newcol, Byte ClassNumber);
	__property TextLabels ;
	__property TickPosX ;
	__property TickPosY ;
	__property TickNumX ;
	__property TickNumY ;
	__property ZoomState ;
	HIDESBASE void __fastcall ZoomHistory(int Index);
	__property ZoomStack ;
	
__published:
	__property Font ;
	__property Align  = {default=0};
	__property Visible  = {default=1};
	__property ShowHint ;
	__property PopupMenu ;
	__property Anchors  = {default=3};
	__property Constraints ;
	__property DragKind  = {default=0};
	__property DragCursor  = {default=-12};
	__property DragMode  = {default=0};
	__property AllocSize ;
	__property AutoRedraw ;
	__property LRim  = {default=50};
	__property RRim  = {default=10};
	__property TRim  = {default=16};
	__property BRim  = {default=32};
	__property BackGroundImg ;
	__property ClassDefault ;
	__property GridStyle ;
	__property GridDx ;
	__property GridDy ;
	__property Isometric ;
	__property DataColor  = {default=0};
	__property PenStyle  = {default=0};
	__property ChartFrameColor  = {default=0};
	__property FillColor  = {default=12632256};
	__property ChartColor  = {default=16777215};
	__property WindColor  = {default=-2147483633};
	__property GridColor  = {default=0};
	__property JointLayers ;
	__property LineWidth  = {default=1};
	__property Caption ;
	__property CaptionPosX ;
	__property CaptionPosY ;
	__property CaptionAlignment ;
	__property CaptionAnchorHoriz ;
	__property CaptionAnchorVert ;
	__property CrossHair1 ;
	__property CrossHair2 ;
	__property CrossHair3 ;
	__property CrossHair4 ;
	__property MouseAction ;
	__property MouseCursorFixed ;
	__property Scale1X ;
	__property Scale1Y ;
	__property Scale2X ;
	__property Scale2Y ;
	__property StandardLayout ;
	__property ShadowWidth  = {default=0};
	__property ShadowStyle ;
	__property ShadowColor ;
	__property ShadowBakColor ;
	__property UseDataOf ;
	__property TextFontStyle ;
	__property TextBkStyle ;
	__property TextBkColor ;
	__property TextAlignment ;
	__property OnClick ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDrag ;
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property OnKeyDown ;
	__property OnKeyUp ;
	__property OnKeyPress ;
	__property OnMouseMoveInChart ;
	__property OnZoomPan ;
	__property OnScaleTickDrawn ;
	__property OnBeforeRenderData ;
	__property OnDataRendered ;
	__property OnScalesRendered ;
	__property OnStartDrag ;
	__property OnCrossHairMove ;
	__property OnTextLabelMove ;
	__property OnCanResize ;
	__property OnResize ;
public:
	#pragma option push -w-inl
	/* TCustomRChart.Create */ inline __fastcall virtual TRChart(Classes::TComponent* AOwner) : TCustomRChart(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomRChart.Destroy */ inline __fastcall virtual ~TRChart(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TRChart(HWND ParentWindow) : TCustomRChart(ParentWindow) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TqcChartType { qcXTplot, qcXYplot, qcHistogram };
#pragma option pop

class DELPHICLASS TQuickChart;
class PASCALIMPLEMENTATION TQuickChart : public TCustomRChart 
{
	typedef TCustomRChart inherited;
	
private:
	TqcChartType FChartType;
	Classes::TComponent* FDataSource;
	int FObjIx1;
	int FObjIx2;
	int FVarIx1;
	int FVarIx2;
	double FRangeXLow;
	double FRangeYLow;
	double FRangeXHigh;
	double FRangeYHigh;
	void __fastcall SetDataSource(Classes::TComponent* dsrc);
	void __fastcall SourceDataChanged(System::TObject* Sender);
	void __fastcall SetQCRange(int index, double Value);
	double __fastcall GetQCRange(int index);
	void __fastcall SetChartType(TqcChartType Value);
	
protected:
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TQuickChart(Classes::TComponent* AOwner);
	
__published:
	__property TqcChartType ChartType = {read=FChartType, write=SetChartType, nodefault};
	__property Classes::TComponent* DataSource = {read=FDataSource, write=SetDataSource};
	__property MouseAction ;
	__property double RangeXLow = {read=GetQCRange, write=SetQCRange, index=1};
	__property double RangeYLow = {read=GetQCRange, write=SetQCRange, index=2};
	__property double RangeXHigh = {read=GetQCRange, write=SetQCRange, index=3};
	__property double RangeYHigh = {read=GetQCRange, write=SetQCRange, index=4};
public:
	#pragma option push -w-inl
	/* TCustomRChart.Destroy */ inline __fastcall virtual ~TQuickChart(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TQuickChart(HWND ParentWindow) : TCustomRChart(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint defLRim = 0x32;
static const Shortint defRRim = 0xa;
static const Shortint defTRim = 0x10;
static const Shortint defBRim = 0x20;
static const Shortint defShadowWidth = 0x0;
#define defPenStyle (Graphics::TPenStyle)(0)
static const int defDataCol = 0x0;
static const int defChartFrameCol = 0x0;
static const int defFillCol = 0xc0c0c0;
static const int defChartCol = 0xffffff;
static const int defWindCol = 0x8000000f;
static const int defGridCol = 0x0;
static const Shortint defLineWid = 0x1;
static const Byte defRCHeight = 0xc8;
static const Word defRCWidth = 0x118;
static const Shortint MinRCWidth = 0x50;
static const Shortint MinRCHeight = 0x14;
static const Shortint MaxTickPos = 0x32;
static const Shortint MaxZoomStack = 0x10;
static const Shortint MaxCrossH = 0x4;
static const Shortint MaxTxtLbl = 0x14;
static const Shortint MaxDataUsers = 0x4;
static const Shortint MaxNumLayers = 0x2;
#define SDLVersionInfo "rchart_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE AnsiString __fastcall RCSpecStrf(double r, int FieldWidth, int DecP);

}	/* namespace Rchart */
using namespace Rchart;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// rchart
