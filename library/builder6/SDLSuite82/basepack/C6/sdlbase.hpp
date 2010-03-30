// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sdlbase.pas' rev: 6.00

#ifndef sdlbaseHPP
#define sdlbaseHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SysUtils.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Sdlbase
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TBkgFill { bfSimple, bfStretch, bfTile };
#pragma option pop

#pragma option push -b-
enum TBoundingBox { bbNone, bbFrame, bbFaces };
#pragma option pop

#pragma option push -b-
enum TTxtLblMode { tlOff, tlsimple, tlBox, tlUnderline, tlShadow };
#pragma option pop

#pragma option push -b-
enum TColorScheme { csBWG, csSystem };
#pragma option pop

#pragma option push -b-
enum TFigType { ftNoFigs, ftNum, ftTime, ftDateTime, ftUserText };
#pragma option pop

#pragma option push -b-
enum TScaleType { sctXB, sctXT, sctYL, sctYR };
#pragma option pop

#pragma option push -b-
enum TYearLength { ylNone, ylYY, ylYYYY };
#pragma option pop

#pragma option push -b-
enum TDateOrder { doMMDDYY, doDDMMYY, doYYMMDD };
#pragma option pop

#pragma option push -b-
enum TDateForTime { dtNone, dtOnePerChart, dtOnePerDay, dtAllTicks };
#pragma option pop

#pragma option push -b-
enum TShadowStyle { ssFlying, ssBox };
#pragma option pop

#pragma option push -b-
enum TFrameStyle { fsNone, fsSimple, fsLowered, fsRaised, fsEmbossed, fsEngraved };
#pragma option pop

#pragma option push -b-
enum TTimeFormat { tfHHMMSS, tfHHhMM, tfAMPM };
#pragma option pop

#pragma option push -b-
enum TDirection { dirUpward, dirDownward, dirLeftward, dirRightward };
#pragma option pop

struct TPointDouble
{
	double X;
	double Y;
} ;

typedef DynamicArray<TPointDouble >  TPDblArray;

typedef void __fastcall (__closure *TSortExchgEvent)(System::TObject* Sender, Byte ExchgWhat, int index1, int index2, int first, int last);

#pragma option push -b-
enum TLanguage { lgEnglish, lgGerman, lgFrench, lgSpanish };
#pragma option pop

typedef Types::TPoint TQuad[4];

struct TRectDouble
{
	
	union
	{
		struct 
		{
			TPointDouble TopLeft;
			TPointDouble BottomRight;
			
		};
		struct 
		{
			double Left;
			double Top;
			double Right;
			double Bottom;
			
		};
		
	};
} ;

#pragma option push -b-
enum TVarKind { rnum, dnum, snum, inum, lnum, Bool, strg };
#pragma option pop

typedef void __fastcall (*FeedBackProcType)(int StateCnt);

#pragma option push -b-
enum TMouseBoxState { msNormal, msFirstCorner, msRectDraw, msFinished };
#pragma option pop

#pragma option push -b-
enum TMouseActMode { maNone, maPan, maPanHoriz, maPanVert, maRubberBand, maZoom, maZoomWind, maZoomWindPos, maZoomDrag, maDragCrossH, maDragLabel, maRotate, maRotAndZoom, maRotXOnly, maRotZOnly };
#pragma option pop

#pragma option push -b-
enum TZoomState { zsNormal, zsDrawWin };
#pragma option pop

typedef void __fastcall (__closure *TZoomPanEvent)(System::TObject* Sender);

typedef void __fastcall (__closure *TOnPercentDoneEvent)(System::TObject* Sender, int PercentDone);

typedef void __fastcall (*TFeedbackProc)(System::TObject* Sender, int StateCnt, double PercentDone);

class DELPHICLASS ESDLError;
class PASCALIMPLEMENTATION ESDLError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLError(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLError(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLError(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLError(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLError(void) { }
	#pragma option pop
	
};


class DELPHICLASS TDTLabel;
class PASCALIMPLEMENTATION TDTLabel : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TTimeFormat FTimeFormat;
	char FDateSeparator;
	char FTimeSeparator;
	TYearLength FYearLength;
	bool FMonthName;
	TDateOrder FDateOrder;
	TDateForTime FDateForTime;
	Classes::TNotifyEvent FOnChange;
	void __fastcall SetTimeFormat(TTimeFormat Value);
	void __fastcall SetDateForTime(TDateForTime value);
	void __fastcall SetDateSeparator(char Value);
	void __fastcall SetTimeSeparator(char Value);
	void __fastcall SetYearLength(TYearLength value);
	void __fastcall SetMonthName(bool value);
	void __fastcall SetDAteOrder(TDateOrder value);
	
public:
	void __fastcall Changed(void);
	
__published:
	__property TTimeFormat TimeFormat = {read=FTimeFormat, write=SetTimeFormat, nodefault};
	__property char DateSeparator = {read=FDateSeparator, write=SetDateSeparator, nodefault};
	__property char TimeSeparator = {read=FTimeSeparator, write=SetTimeSeparator, nodefault};
	__property TYearLength YearLength = {read=FYearLength, write=SetYearLength, nodefault};
	__property bool MonthName = {read=FMonthName, write=SetMonthName, nodefault};
	__property TDateOrder DateOrder = {read=FDateOrder, write=SetDAteOrder, nodefault};
	__property TDateForTime DateForTime = {read=FDateForTime, write=SetDateForTime, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TDTLabel(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TDTLabel(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


typedef Byte TBuf4096[4096];

typedef Byte TBuf16K[16384];

typedef Byte TDataBuffer[2147483647];

typedef DynamicArray<Byte >  TBytes;

#pragma option push -b-
enum TCrossHMode { chOff, chHoriz, chVert, chBoth };
#pragma option pop

class DELPHICLASS TCrossHair;
class PASCALIMPLEMENTATION TCrossHair : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	double FPosX;
	double FPosY;
	Graphics::TColor FColor;
	TCrossHMode FMode;
	Graphics::TPenStyle FLineType;
	int FLineWid;
	int FLayer;
	Classes::TNotifyEvent FOnChange;
	void __fastcall SetCrossHPosX(double value);
	void __fastcall SetCrossHPosY(double value);
	void __fastcall SetCrossHColor(Graphics::TColor value);
	void __fastcall SetCrossHMode(TCrossHMode value);
	void __fastcall SetCrossHLineType(Graphics::TPenStyle value);
	void __fastcall SetCrossHLineWid(int value);
	void __fastcall SetCrossHLayer(int value);
	
public:
	void __fastcall Changed(void);
	
__published:
	__property double PosX = {read=FPosX, write=SetCrossHPosX};
	__property double PosY = {read=FPosY, write=SetCrossHPosY};
	__property Graphics::TColor Color = {read=FColor, write=SetCrossHColor, nodefault};
	__property int Layer = {read=FLayer, write=SetCrossHLayer, nodefault};
	__property TCrossHMode Mode = {read=FMode, write=SetCrossHMode, nodefault};
	__property Graphics::TPenStyle LineType = {read=FLineType, write=SetCrossHLineType, nodefault};
	__property int LineWid = {read=FLineWid, write=SetCrossHLineWid, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TCrossHair(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TCrossHair(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define SDLVersionInfo "sdlbase_r820_full"
static const bool IsLightEd = false;
static const Word Release = 0x334;
extern PACKAGE System::SmallString<4>  MonthShort[4][12];
extern PACKAGE System::SmallString<10>  MonthLong[4][12];
extern PACKAGE System::SmallString<3>  WeekDayShort[4][7];
extern PACKAGE System::SmallString<10>  WeekDayLong[4][7];
extern PACKAGE System::SmallString<6>  NumWords[4][13];
extern PACKAGE System::SmallString<8>  HTMLLat1Entities[96];
static const Word LENGBUF4096 = 0x1000;
static const Word LENGBUF16K = 0x4000;
static const Shortint MAXCANVASMARKS = 0x2f;
extern PACKAGE int ProcStat;
extern PACKAGE FeedBackProcType MathFeedBackProc;
extern PACKAGE void __fastcall PrintBitmap(Graphics::TBitmap* Bitmap, int X, int Y);
extern PACKAGE void __fastcall DrawFrame(Graphics::TCanvas* cv, TFrameStyle fs, int Left, int Top, int Right, int Bottom, Graphics::TColor White, Graphics::TColor Silver, Graphics::TColor Gray, Graphics::TColor Black, Graphics::TColor SimpleFCol);
extern PACKAGE void __fastcall DrawRectangle(const Graphics::TCanvas* cv, int Left, int Top, int Right, int Bottom);
extern PACKAGE void __fastcall DrawMarkOnCanvas(const Graphics::TCanvas* canv, Byte Mark, int x, int y);

}	/* namespace Sdlbase */
using namespace Sdlbase;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sdlbase
