// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'rot3d.pas' rev: 6.00

#ifndef rot3dHPP
#define rot3dHPP

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

namespace Rot3d
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESDLRot3DError;
class PASCALIMPLEMENTATION ESDLRot3DError : public Sdlbase::ESDLError 
{
	typedef Sdlbase::ESDLError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLRot3DError(const AnsiString Msg) : Sdlbase::ESDLError(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLRot3DError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sdlbase::ESDLError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLRot3DError(int Ident)/* overload */ : Sdlbase::ESDLError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLRot3DError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sdlbase::ESDLError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLRot3DError(const AnsiString Msg, int AHelpContext) : Sdlbase::ESDLError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLRot3DError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sdlbase::ESDLError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLRot3DError(int Ident, int AHelpContext)/* overload */ : Sdlbase::ESDLError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLRot3DError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sdlbase::ESDLError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLRot3DError(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum Tr3Item { tkNone, tkMarkAt, tkLineto, tkLine, tkMoveto, tkEverything };
#pragma option pop

struct Tr3ChartItem
{
	double x;
	double y;
	double z;
	Graphics::TColor color;
	int tag;
	Tr3Item ItemKind;
	double x2;
	double y2;
	double z2;
	Byte mark;
} ;

#pragma option push -b-
enum TAxDir { adLeftHanded, adRightHanded };
#pragma option pop

typedef AnsiString rot3d__3[3];

typedef DynamicArray<int >  rot3d__4;

typedef DynamicArray<int >  rot3d__5;

typedef DynamicArray<int >  rot3d__6;

typedef DynamicArray<int >  rot3d__7;

typedef DynamicArray<Byte >  rot3d__8;

typedef DynamicArray<Byte >  rot3d__9;

typedef DynamicArray<Tr3ChartItem >  rot3d__01;

class DELPHICLASS TRot3D;
class PASCALIMPLEMENTATION TRot3D : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	int CubeCorners[8][3];
	double FViewAngle[3];
	Graphics::TBitmap* GrafBmp;
	Sdlbase::TMouseActMode FMouseAction;
	Graphics::TColor FDataCol;
	TAxDir FAxDir;
	int FDataTag;
	Graphics::TColor FFrameCol;
	Graphics::TColor FChartCol;
	Graphics::TColor FColBlackLine;
	Graphics::TColor FColGrayLine;
	Graphics::TColor FColWhiteLine;
	Sdlbase::TColorScheme FColorScheme;
	Graphics::TColor FColorCubeFrame;
	Graphics::TColor FColorCubeHidLin;
	Graphics::TColor FColorCubeFaceHi;
	Graphics::TColor FColorCubeFaceLo;
	int FFontPixPerInch;
	Sdlbase::TBoundingBox FBoundBox;
	int FBBSize;
	int FAxSize;
	bool FShowAxes;
	Sdlbase::TFrameStyle FFrameStyle;
	bool FIsoMetric;
	bool FAutoOrigin;
	bool FAutoScale;
	double FOrigin[3];
	AnsiString FAxName[3];
	int FMagnify;
	double FMagAnchor;
	int FMinCoord[3];
	int FMaxCoord[3];
	double FAngleAnchor[3];
	double FScaleFact[3];
	Graphics::TColor FItemColors[32];
	int FCentX;
	int FCentY;
	int FCentXAnchor;
	int FCentYAnchor;
	int FRotMat[3][3];
	int NRotObj;
	DynamicArray<int >  FRotDataX;
	DynamicArray<int >  FRotDataY;
	DynamicArray<int >  FRotDataZ;
	DynamicArray<int >  FBackLink;
	DynamicArray<Byte >  FRotProp;
	DynamicArray<Byte >  FRotMark;
	bool FRotMat3D;
	Graphics::TFontStyles FTextFontStyle;
	Byte FTextMarkSize;
	int MouseAnchorX;
	int MouseAnchorY;
	int FNumChartItems;
	int FNumAllocated;
	int FAllocSize;
	void __fastcall ConstructDataBmp(Graphics::TCanvas* cv, bool BlkWhite);
	void __fastcall InitGraf(Graphics::TCanvas* cv, bool BlkWhite, int AddOn);
	void __fastcall SetDataCol(Graphics::TColor c);
	void __fastcall SetDataTag(int tag);
	void __fastcall SetFrameCol(Graphics::TColor c);
	void __fastcall SetChartCol(Graphics::TColor c);
	void __fastcall SetColCubeFrame(Graphics::TColor c);
	void __fastcall SetColCubeHidLin(Graphics::TColor c);
	void __fastcall SetColCubeFaceLow(Graphics::TColor c);
	void __fastcall SetColCubeFaceHigh(Graphics::TColor c);
	void __fastcall SetMagnify(double mag);
	AnsiString __fastcall GetAxNameX();
	AnsiString __fastcall GetAxNameY();
	AnsiString __fastcall GetAxNameZ();
	Tr3ChartItem __fastcall GetChartItem(int idx);
	double __fastcall GetMagnify(void);
	Tr3Item __fastcall GetTypeOfFirstItem(void);
	Tr3Item __fastcall GetTypeOfLastItem(void);
	double __fastcall GetViewAngleX(void);
	double __fastcall GetViewAngleY(void);
	double __fastcall GetViewAngleZ(void);
	double __fastcall GetOriginX(void);
	double __fastcall GetOriginY(void);
	double __fastcall GetOriginZ(void);
	double __fastcall GetRotMat(int ix, int iy);
	double __fastcall GetScaleFactX(void);
	double __fastcall GetScaleFactY(void);
	double __fastcall GetScaleFactZ(void);
	void __fastcall SetChartitem(int idx, const Tr3ChartItem &item);
	void __fastcall SetColorScheme(Sdlbase::TColorScheme Value);
	void __fastcall SetCubeCorners(void);
	void __fastcall SetFrameStyle(Sdlbase::TFrameStyle value);
	void __fastcall SetBoundBoxStyle(Sdlbase::TBoundingBox value);
	void __fastcall SetBoundBoxSize(int value);
	int __fastcall GetBoundBoxSize(void);
	void __fastcall SetAllocSize(int alloc);
	void __fastcall SetAxSize(int value);
	void __fastcall SetAxDir(TAxDir value);
	void __fastcall SetCentX(int value);
	void __fastcall SetCentY(int value);
	void __fastcall SetIsoMetric(bool value);
	void __fastcall SetAutoOrigin(bool value);
	void __fastcall SetAutoScale(bool value);
	void __fastcall SetShowAxes(bool value);
	void __fastcall SetTextFontStyle(Graphics::TFontStyles tfs);
	void __fastcall SetTextMarkSize(Byte tms);
	void __fastcall SetViewAngleX(double value);
	void __fastcall SetViewAngleY(double value);
	void __fastcall SetViewAngleZ(double value);
	void __fastcall SetOriginX(double value);
	void __fastcall SetOriginY(double value);
	void __fastcall SetOriginZ(double value);
	void __fastcall SetScaleFactX(double value);
	void __fastcall SetScaleFactY(double value);
	void __fastcall SetScaleFactZ(double value);
	void __fastcall SetAxNameX(AnsiString value);
	void __fastcall SetAxNameY(AnsiString value);
	void __fastcall SetAxNameZ(AnsiString value);
	void __fastcall SetMRot3Axes(bool value);
	
protected:
	DynamicArray<Tr3ChartItem >  FDataContainer;
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall CalcRotMatrix_2Ax(void);
	virtual void __fastcall CalcRotMatrix_3Ax(void);
	void __fastcall CalcRotMatrix(void);
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TRot3D(Classes::TComponent* AOwner);
	__fastcall virtual ~TRot3D(void);
	void __fastcall Clear(void);
	__property Graphics::TColor ColorData = {read=FDataCol, write=SetDataCol, default=0};
	void __fastcall CopyToBMP(AnsiString FName, bool IncludeFrame);
	void __fastcall CopyToWMF(AnsiString FName, bool IncludeFrame);
	void __fastcall CopyToClipboardWMF(bool IncludeFrame);
	void __fastcall CopyToClipboard(bool IncludeFrame);
	void __fastcall PrintIt(double ScaleF, bool BlkWhite, bool IncludeFrame);
	void __fastcall CopyToOpenPrinter(int &x, int &y, double ScaleF, bool BlkWhite, bool IncludeFrame);
	__property Tr3ChartItem DataContainer[int idx] = {read=GetChartItem, write=SetChartitem};
	__property int DataTag = {read=FDataTag, write=SetDataTag, nodefault};
	void __fastcall MakeVisible(void);
	void __fastcall Drawto(double x, double y, double z);
	int __fastcall FindNearestItemScreen(int mx, int my, Tr3Item ItemID, double &dist);
	int __fastcall FindNearestItemReal(double mx, double my, double mz, Tr3Item ItemID, double &dist);
	Tr3ChartItem __fastcall GetItemParams(int Item);
	void __fastcall SetItemParams(int Item, const Tr3ChartItem &ItParams);
	void __fastcall Line(double x1, double y1, double z1, double x2, double y2, double z2);
	void __fastcall Moveto(double x, double y, double z);
	void __fastcall MarkAt(double x, double y, double z, Byte mk);
	__property int NumItems = {read=FNumChartItems, nodefault};
	void __fastcall RemoveLastItem(void);
	void __fastcall RemoveFirstItem(void);
	void __fastcall RemoveItem(int Index);
	void __fastcall SetViewAngles(double vax, double vay, double vaz);
	void __fastcall SetOrigins(double vax, double vay, double vaz);
	void __fastcall SetScaleFactors(double sfx, double sfy, double sfz);
	__property Tr3Item TypeOfLastItem = {read=GetTypeOfLastItem, nodefault};
	__property Tr3Item TypeOfFirstItem = {read=GetTypeOfFirstItem, nodefault};
	__property double RotMat[int ix][int iy] = {read=GetRotMat};
	__property double ScaleFactX = {read=GetScaleFactX, write=SetScaleFactX};
	__property double ScaleFactY = {read=GetScaleFactY, write=SetScaleFactY};
	__property double ScaleFactZ = {read=GetScaleFactZ, write=SetScaleFactZ};
	
__published:
	__property Font ;
	__property Align  = {default=0};
	__property Visible  = {default=1};
	__property ShowHint ;
	__property PopupMenu ;
	__property int AllocSize = {read=FAllocSize, write=SetAllocSize, nodefault};
	__property int CentX = {read=FCentX, write=SetCentX, nodefault};
	__property int CentY = {read=FCentY, write=SetCentY, nodefault};
	__property Graphics::TColor ColorFrame = {read=FFrameCol, write=SetFrameCol, default=0};
	__property Graphics::TColor ColorChart = {read=FChartCol, write=SetChartCol, default=16777215};
	__property Sdlbase::TColorScheme ColorScheme = {read=FColorScheme, write=SetColorScheme, nodefault};
	__property Graphics::TColor ColorCubeFrame = {read=FColorCubeFrame, write=SetColCubeFrame, nodefault};
	__property Graphics::TColor ColorCubeHidLin = {read=FColorCubeHidLin, write=SetColCubeHidLin, nodefault};
	__property Graphics::TColor ColorCubeFaceLow = {read=FColorCubeFaceLo, write=SetColCubeFaceLow, nodefault};
	__property Graphics::TColor ColorCubeFaceHigh = {read=FColorCubeFaceHi, write=SetColCubeFaceHigh, nodefault};
	__property bool IsoMetric = {read=FIsoMetric, write=SetIsoMetric, nodefault};
	__property bool AutoOrigin = {read=FAutoOrigin, write=SetAutoOrigin, nodefault};
	__property bool AutoScale = {read=FAutoScale, write=SetAutoScale, nodefault};
	__property Sdlbase::TFrameStyle FrameStyle = {read=FFrameStyle, write=SetFrameStyle, nodefault};
	__property double Magnification = {read=GetMagnify, write=SetMagnify};
	__property Sdlbase::TMouseActMode MouseAction = {read=FMouseAction, write=FMouseAction, nodefault};
	__property bool MouseRot3Axes = {read=FRotMat3D, write=SetMRot3Axes, nodefault};
	__property Sdlbase::TBoundingBox BoundBoxStyle = {read=FBoundBox, write=SetBoundBoxStyle, nodefault};
	__property int BoundBoxSize = {read=GetBoundBoxSize, write=SetBoundBoxSize, nodefault};
	__property TAxDir AxDir = {read=FAxDir, write=SetAxDir, nodefault};
	__property int AxSize = {read=FAxSize, write=SetAxSize, nodefault};
	__property AnsiString AxNameX = {read=GetAxNameX, write=SetAxNameX};
	__property AnsiString AxNameY = {read=GetAxNameY, write=SetAxNameY};
	__property AnsiString AxNameZ = {read=GetAxNameZ, write=SetAxNameZ};
	__property bool ShowAxes = {read=FShowAxes, write=SetShowAxes, nodefault};
	__property Graphics::TFontStyles TextFontStyle = {read=FTextFontStyle, write=SetTextFontStyle, nodefault};
	__property Byte TextMarkSize = {read=FTextMarkSize, write=SetTextMarkSize, nodefault};
	__property double ViewAngleX = {read=GetViewAngleX, write=SetViewAngleX};
	__property double ViewAngleY = {read=GetViewAngleY, write=SetViewAngleY};
	__property double ViewAngleZ = {read=GetViewAngleZ, write=SetViewAngleZ};
	__property double OriginX = {read=GetOriginX, write=SetOriginX};
	__property double OriginY = {read=GetOriginY, write=SetOriginY};
	__property double OriginZ = {read=GetOriginZ, write=SetOriginZ};
	__property OnClick ;
	__property OnDblClick ;
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
};


//-- var, const, procedure ---------------------------------------------------
static const int defDataCol = 0x0;
static const int defFrameCol = 0x0;
static const int defChartCol = 0xffffff;
static const Word defR3Height = 0x12c;
static const Word defR3Width = 0x1c2;
static const Shortint MaxItemColors = 0x1f;
#define SDLVersionInfo "rot3d_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Rot3d */
using namespace Rot3d;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// rot3d
