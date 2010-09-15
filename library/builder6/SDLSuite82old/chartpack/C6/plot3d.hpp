// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'plot3d.pas' rev: 6.00

#ifndef plot3dHPP
#define plot3dHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <sdlbase.hpp>	// Pascal unit
#include <matrix.hpp>	// Pascal unit
#include <math1.hpp>	// Pascal unit
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

namespace Plot3d
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TColorCodingMode { ccmTwoColors, ccmThreeColors };
#pragma option pop

#pragma option push -b-
enum TP3ScaleKind { p3skX, p3skY, p3skZ };
#pragma option pop

typedef void __fastcall (__closure *TMouseActionEvent)(System::TObject* Sender, int &CenterX, int &CenterY, double &RotXAngle, double &RotZAngle, double &Magnification, Classes::TShiftState Shift);

typedef void __fastcall (__closure *TMouseMoveOverPlotEvent)(System::TObject* Sender, bool OverPlot, Classes::TShiftState Shift, int MouseCellX, int MouseCellY);

typedef void __fastcall (__closure *TBeforeRenderPolygonEvent)(System::TObject* Sender, Graphics::TCanvas* &Canvas, bool &Handled, int CellX, int CellY, const Types::TPoint * quad, Graphics::TColor &color);

typedef void __fastcall (__closure *Tp3BeforeDrawScaleLabelEvent)(System::TObject* Sender, Graphics::TCanvas* &Canvas, TP3ScaleKind ScaleType, AnsiString &CurrentTickLabel, int ChartX, int ChartY);

typedef void __fastcall (__closure *TRenderEvent)(System::TObject* Sender, Graphics::TCanvas* &Canvas);

class DELPHICLASS TPlot3D;
class PASCALIMPLEMENTATION TPlot3D : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	double CubeCorners[8][3];
	Graphics::TBitmap* GrafBmp;
	Graphics::TColor FFrameCol;
	Sdlbase::TMouseActMode FMouseAction;
	int FBoxSizeX;
	int FBoxSizeY;
	int FBoxSizeZ;
	double FRangeLowX;
	double FRangeHighX;
	double FRangeLowY;
	double FRangeHighY;
	double FRangeLowZ;
	double FRangeHighZ;
	Graphics::TColor FColorXAx;
	Graphics::TColor FColorYAx;
	Graphics::TColor FColorZAx;
	Graphics::TColor FColorCubeFrame;
	Graphics::TColor FColorCubeHidLin;
	Graphics::TColor FColorCubeFaceHi;
	Graphics::TColor FColorCubeFaceLo;
	int FDecPlaceX;
	int FDecPlaceY;
	int FDecPlaceZ;
	Sdlbase::TBoundingBox FBoundBox;
	Graphics::TColor FColorBakGnd;
	Graphics::TColor FColorMesh;
	Graphics::TColor FColorFillHigh;
	Graphics::TColor FColorFillMid;
	Graphics::TColor FColorFillLow;
	double FColorScaleLow;
	double FColorScaleHigh;
	TColorCodingMode FColorCodingMode;
	Graphics::TColor FColBlackLine;
	Graphics::TColor FColGrayLine;
	Graphics::TColor FColWhiteLine;
	Sdlbase::TColorScheme FColorScheme;
	Sdlbase::TFrameStyle FFrameStyle;
	double FViewAngle[3];
	double FViewAngLimLow[3];
	double FViewAngLimHigh[3];
	bool FVisibleXax;
	bool FVisibleYax;
	bool FVisibleZax;
	double FMagnify;
	double FMagAnchor;
	bool FMeshVisible;
	int FNTicks[3];
	Tp3BeforeDrawScaleLabelEvent FOnBefDrawSclLab;
	TMouseActionEvent FOnMouseAction;
	TRenderEvent FOnDataRendered;
	TMouseMoveOverPlotEvent FOnMMvOverPlot;
	TBeforeRenderPolygonEvent FOnBefRndPolygon;
	double FCalibZk;
	double FCalibZd;
	bool FColorCodeAvg;
	int FCentX;
	int FCentY;
	int FCentXAnchor;
	int FCentYAnchor;
	double FAngleAnchor[3];
	double FMinZ;
	double FMaxZ;
	double FSclXIntern;
	double FSclYIntern;
	double FSclZIntern;
	bool FSuppressPaint;
	double FRotMat[3][3];
	int MouseAnchorX;
	int MouseAnchorY;
	void __fastcall AdjustScaling(void);
	void __fastcall ConstructDataBmp(Graphics::TCanvas* cv, bool BlkWhite);
	double __fastcall CalcIntZ(double zvalue);
	void __fastcall InitGraf(Graphics::TCanvas* cv);
	void __fastcall CalcRotMatrix(void);
	Graphics::TColor __fastcall CalcColorCoding(double value);
	void __fastcall DrawAxis(Graphics::TCanvas* cv, TP3ScaleKind axKind, int xxLow, int yyLow, int xxHigh, int yyHigh, double RangeLow, double RangeHigh, int CubeIx1);
	double __fastcall GetRotMat(int ix, int iy);
	double __fastcall GetMagnify(void);
	void __fastcall SetBoundBoxStyle(Sdlbase::TBoundingBox value);
	void __fastcall SetCentX(int value);
	void __fastcall SetCentY(int value);
	void __fastcall SetColorScheme(Sdlbase::TColorScheme Value);
	void __fastcall SetColorCodingMode(TColorCodingMode Value);
	void __fastcall SetFrameCol(Graphics::TColor c);
	void __fastcall SetColorBakGnd(Graphics::TColor c);
	void __fastcall SetColorXax(Graphics::TColor c);
	void __fastcall SetColorYax(Graphics::TColor c);
	void __fastcall SetColorZax(Graphics::TColor c);
	void __fastcall SetColorCodeAvg(bool value);
	void __fastcall SetColCubeFrame(Graphics::TColor c);
	void __fastcall SetColCubeHidLin(Graphics::TColor c);
	void __fastcall SetColCubeFaceLow(Graphics::TColor c);
	void __fastcall SetColCubeFaceHigh(Graphics::TColor c);
	void __fastcall SetColorFillHigh(Graphics::TColor c);
	void __fastcall SetColorFillMid(Graphics::TColor c);
	void __fastcall SetColorFillLow(Graphics::TColor c);
	void __fastcall SetColorMesh(Graphics::TColor c);
	double __fastcall GetColorScaleHigh(void);
	void __fastcall SetColorScaleHigh(double Level);
	double __fastcall GetColorScaleLow(void);
	void __fastcall SetColorScaleLow(double Level);
	void __fastcall SetCubeCorners(void);
	void __fastcall SetDecPlaceX(int value);
	void __fastcall SetDecPlaceY(int value);
	void __fastcall SetDecPlaceZ(int value);
	void __fastcall SetFrameStyle(Sdlbase::TFrameStyle value);
	void __fastcall SetMagnify(double mag);
	void __fastcall SetMeshVisible(bool meshvis);
	int __fastcall GetNTicksX(void);
	int __fastcall GetNTicksY(void);
	int __fastcall GetNTicksZ(void);
	void __fastcall SetNTicksX(int value);
	void __fastcall SetNTicksY(int value);
	void __fastcall SetNTicksZ(int value);
	void __fastcall SetRangeLowZ(double value);
	void __fastcall SetRangeHighZ(double value);
	void __fastcall SetRangeLowY(double value);
	void __fastcall SetRangeHighY(double value);
	void __fastcall SetRangeLowX(double value);
	void __fastcall SetRangeHighX(double value);
	void __fastcall SetSclX(double fact);
	void __fastcall SetSclY(double fact);
	void __fastcall SetSclZ(double fact);
	double __fastcall GetViewAngleX(void);
	double __fastcall GetViewAngleZ(void);
	void __fastcall SetViewAngleX(double value);
	void __fastcall SetViewAngleZ(double value);
	void __fastcall SetSuppressPaint(bool supp);
	void __fastcall SetVisibleXAx(bool value);
	void __fastcall SetVisibleYAx(bool value);
	void __fastcall SetVisibleZAx(bool value);
	MESSAGE void __fastcall WMMouseMoveOverPlot(Messages::TWMMouse &Message);
	
protected:
	void __fastcall GridMatChanged(System::TObject* Sender);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	void __fastcall MouseActionMove(int &CenterX, int &CenterY, double &RotXAngle, double &RotZAngle, double &Magnification, Classes::TShiftState Shift);
	void __fastcall MouseMoveOverPlot(bool OverPlot, Classes::TShiftState Shift, int MouseCellX, int MouseCellY);
	virtual void __fastcall Paint(void);
	
public:
	Matrix::TIntMatrix* ProjMapX;
	Matrix::TIntMatrix* ProjMapY;
	Matrix::TIntMatrix* ProjMapZ;
	Matrix::TMatrix* GridMat;
	__fastcall virtual TPlot3D(Classes::TComponent* AOwner);
	__fastcall virtual ~TPlot3D(void);
	void __fastcall AutoScale(void);
	void __fastcall Clear(void);
	void __fastcall CopyToBMP(AnsiString FName, bool IncludeFrame);
	void __fastcall CopyToClipboard(bool IncludeFrame);
	void __fastcall CopyToWMF(AnsiString FName, bool IncludeFrame);
	void __fastcall CopyToClipboardWMF(bool IncludeFrame);
	void __fastcall PrintIt(double ScaleF, bool BlkWhite, bool IncludeFrame);
	void __fastcall CopyToOpenPrinter(int &x, int &y, double ScaleF, bool BlkWhite, bool IncludeFrame);
	void __fastcall Reset(void);
	__property double RotMat[int ix][int iy] = {read=GetRotMat};
	void __fastcall SetRange(double xLow, double xHigh, double yLow, double yHigh, double zLow, double zHigh);
	void __fastcall SetViewAngles(double vax, double vaz);
	__property bool SuppressPaint = {read=FSuppressPaint, write=SetSuppressPaint, nodefault};
	
__published:
	__property Align  = {default=0};
	__property Visible  = {default=1};
	__property ShowHint ;
	__property PopupMenu ;
	__property ParentShowHint  = {default=1};
	__property Sdlbase::TBoundingBox BoundBoxStyle = {read=FBoundBox, write=SetBoundBoxStyle, nodefault};
	__property int CentX = {read=FCentX, write=SetCentX, nodefault};
	__property int CentY = {read=FCentY, write=SetCentY, nodefault};
	__property Graphics::TColor ColorFrame = {read=FFrameCol, write=SetFrameCol, default=0};
	__property Graphics::TColor ColorBakGnd = {read=FColorBakGnd, write=SetColorBakGnd, nodefault};
	__property bool ColorCodeAvg = {read=FColorCodeAvg, write=SetColorCodeAvg, nodefault};
	__property Graphics::TColor ColorCubeFrame = {read=FColorCubeFrame, write=SetColCubeFrame, nodefault};
	__property Graphics::TColor ColorCubeHidLin = {read=FColorCubeHidLin, write=SetColCubeHidLin, nodefault};
	__property Graphics::TColor ColorCubeFaceLow = {read=FColorCubeFaceLo, write=SetColCubeFaceLow, nodefault};
	__property Graphics::TColor ColorCubeFaceHigh = {read=FColorCubeFaceHi, write=SetColCubeFaceHigh, nodefault};
	__property Graphics::TColor ColorXCoords = {read=FColorXAx, write=SetColorXax, nodefault};
	__property Graphics::TColor ColorYCoords = {read=FColorYAx, write=SetColorYax, nodefault};
	__property Graphics::TColor ColorZCoords = {read=FColorZAx, write=SetColorZax, nodefault};
	__property Graphics::TColor ColorMesh = {read=FColorMesh, write=SetColorMesh, nodefault};
	__property Graphics::TColor ColorHigh = {read=FColorFillHigh, write=SetColorFillHigh, nodefault};
	__property Graphics::TColor ColorMid = {read=FColorFillMid, write=SetColorFillMid, nodefault};
	__property Graphics::TColor ColorLow = {read=FColorFillLow, write=SetColorFillLow, nodefault};
	__property double ColorScaleHigh = {read=GetColorScaleHigh, write=SetColorScaleHigh};
	__property double ColorScaleLow = {read=GetColorScaleLow, write=SetColorScaleLow};
	__property TColorCodingMode ColorCodingMode = {read=FColorCodingMode, write=SetColorCodingMode, nodefault};
	__property Sdlbase::TColorScheme ColorScheme = {read=FColorScheme, write=SetColorScheme, nodefault};
	__property int DecPlaceX = {read=FDecPlaceX, write=SetDecPlaceX, nodefault};
	__property int DecPlaceY = {read=FDecPlaceY, write=SetDecPlaceY, nodefault};
	__property int DecPlaceZ = {read=FDecPlaceZ, write=SetDecPlaceZ, nodefault};
	__property Sdlbase::TFrameStyle FrameStyle = {read=FFrameStyle, write=SetFrameStyle, nodefault};
	__property bool MeshVisible = {read=FMeshVisible, write=SetMeshVisible, nodefault};
	__property double Magnification = {read=GetMagnify, write=SetMagnify};
	__property Sdlbase::TMouseActMode MouseAction = {read=FMouseAction, write=FMouseAction, nodefault};
	__property int MinTickX = {read=GetNTicksX, write=SetNTicksX, nodefault};
	__property int MinTickY = {read=GetNTicksY, write=SetNTicksY, nodefault};
	__property int MinTickZ = {read=GetNTicksZ, write=SetNTicksZ, nodefault};
	__property double RangeXLow = {read=FRangeLowX, write=SetRangeLowX};
	__property double RangeYLow = {read=FRangeLowY, write=SetRangeLowY};
	__property double RangeZLow = {read=FRangeLowZ, write=SetRangeLowZ};
	__property double RangeXHigh = {read=FRangeHighX, write=SetRangeHighX};
	__property double RangeYHigh = {read=FRangeHighY, write=SetRangeHighY};
	__property double RangeZHigh = {read=FRangeHighZ, write=SetRangeHighZ};
	__property double ScaleFactX = {read=FSclXIntern, write=SetSclX};
	__property double ScaleFactY = {read=FSclYIntern, write=SetSclY};
	__property double ScaleFactZ = {read=FSclZIntern, write=SetSclZ};
	__property double ViewAngleX = {read=GetViewAngleX, write=SetViewAngleX};
	__property double ViewAngleZ = {read=GetViewAngleZ, write=SetViewAngleZ};
	__property bool VisibleXCoords = {read=FVisibleXax, write=SetVisibleXAx, nodefault};
	__property bool VisibleYCoords = {read=FVisibleYax, write=SetVisibleYAx, nodefault};
	__property bool VisibleZCoords = {read=FVisibleZax, write=SetVisibleZAx, nodefault};
	__property TRenderEvent OnDataRendered = {read=FOnDataRendered, write=FOnDataRendered};
	__property TMouseActionEvent OnMouseAction = {read=FOnMouseAction, write=FOnMouseAction};
	__property OnClick ;
	__property OnDblClick ;
	__property TBeforeRenderPolygonEvent OnBeforeRenderPolygon = {read=FOnBefRndPolygon, write=FOnBefRndPolygon};
	__property Tp3BeforeDrawScaleLabelEvent OnBeforeDrawScaleLabel = {read=FOnBefDrawSclLab, write=FOnBefDrawSclLab};
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property TMouseMoveOverPlotEvent OnMouseMoveOverPlot = {read=FOnMMvOverPlot, write=FOnMMvOverPlot};
};


//-- var, const, procedure ---------------------------------------------------
static const int defFrameCol = 0x0;
static const int defBakGndCol = 0xffffff;
static const int defFillCol = 0xffff;
static const int defMeshCol = 0x0;
static const Word defHeight = 0x1f4;
static const Word defWidth = 0x28a;
#define SDLVersionInfo "plot3d_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Plot3d */
using namespace Plot3d;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// plot3d
