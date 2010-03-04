// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'rasterlab.pas' rev: 6.00

#ifndef rasterlabHPP
#define rasterlabHPP

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

namespace Rasterlab
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESDLRasterLabError;
class PASCALIMPLEMENTATION ESDLRasterLabError : public Sdlbase::ESDLError 
{
	typedef Sdlbase::ESDLError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLRasterLabError(const AnsiString Msg) : Sdlbase::ESDLError(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLRasterLabError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sdlbase::ESDLError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLRasterLabError(int Ident)/* overload */ : Sdlbase::ESDLError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLRasterLabError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sdlbase::ESDLError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLRasterLabError(const AnsiString Msg, int AHelpContext) : Sdlbase::ESDLError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLRasterLabError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sdlbase::ESDLError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLRasterLabError(int Ident, int AHelpContext)/* overload */ : Sdlbase::ESDLError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLRasterLabError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sdlbase::ESDLError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLRasterLabError(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TRDBlockMode { rdbmOff, rdbmOn, rdbmRaster };
#pragma option pop

#pragma option push -b-
enum TRDScrollMode { rdsmOff, rdsmLeft, rdsmRight, rdsmDown, rdsmUp };
#pragma option pop

#pragma pack(push, 4)
struct TRDCharMatrix
{
	int FontWidth;
	int FontHeight;
	Byte LeftMostBit[256];
	Byte RightMostBit[256];
	int BitData[256][32];
} ;
#pragma pack(pop)

class DELPHICLASS TRasterLab;
class PASCALIMPLEMENTATION TRasterLab : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	TRDCharMatrix FCMat;
	Sdlbase::TFrameStyle FFrameStyle;
	TRDScrollMode FScrollMode;
	int FScrollPosX;
	int FScrollPosY;
	bool FScrollLoop;
	HWND FScrTimerHandle;
	bool FScrTimerEnabled;
	bool FAutoCenter;
	int FTextBitLength;
	Classes::TNotifyEvent FOnScrollTimer;
	int FScrollIv;
	int FScrollInc;
	AnsiString FLabText;
	Graphics::TColor FColorLabBakG;
	Graphics::TColor FColorDotOn;
	Graphics::TColor FColorDotOff;
	Graphics::TColor FColBlackLine;
	Graphics::TColor FColGrayLine;
	Graphics::TColor FColWhiteLine;
	bool FAutoHeight;
	TRDBlockMode FCharBlockMode;
	Sdlbase::TColorScheme FColorScheme;
	Classes::TNotifyEvent FOnScrLoopRestart;
	bool FProportional;
	int FDotSize;
	int FDotSpacing;
	int FXPos;
	int FYPos;
	void __fastcall AdjustAutoHeight(void);
	void __fastcall AdjustAutoCenter(void);
	int __fastcall CalcTextBitLength(AnsiString txt);
	void __fastcall SetColorLabBakG(Graphics::TColor Value);
	void __fastcall SetColorDotOn(Graphics::TColor Value);
	void __fastcall SetColorDotOff(Graphics::TColor Value);
	void __fastcall SetColorScheme(Sdlbase::TColorScheme Value);
	void __fastcall SetFrameStyle(Sdlbase::TFrameStyle value);
	void __fastcall SetLabText(AnsiString value);
	void __fastcall SetCharBlockMode(TRDBlockMode value);
	void __fastcall SetProportional(bool value);
	void __fastcall SetAutoHeight(bool value);
	void __fastcall SetAutoCenter(bool value);
	void __fastcall SetDotSpacing(int value);
	void __fastcall SetDotSize(int value);
	void __fastcall SetOnScrollTimer(Classes::TNotifyEvent Value);
	void __fastcall SetXPos(int value);
	void __fastcall SetYPos(int value);
	void __fastcall SetCharMatrix(const TRDCharMatrix &value);
	void __fastcall SetScrollMode(TRDScrollMode value);
	void __fastcall SetScrollLoop(bool value);
	void __fastcall SetScrollIv(int value);
	void __fastcall SetScrollInc(int value);
	void __fastcall UpdateTimer(void);
	
protected:
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	void __fastcall ScrollTimerEvent(System::TObject* Sender);
	DYNAMIC void __fastcall DoTimer(void);
	DYNAMIC void __fastcall DoScrLoopRestart(void);
	virtual void __fastcall Paint(void);
	HIDESBASE void __fastcall WndProc(Messages::TMessage &Msg);
	HIDESBASE void __fastcall FontChanged(System::TObject* Sender);
	void __fastcall PaintString(Graphics::TCanvas* cv, const TRDCharMatrix &CMat, int PosX, int PosY, AnsiString txt, int DotSize, int DotSpacing, Graphics::TColor ColorFg, Graphics::TColor ColorFgIA, Graphics::TColor ColorBg, TRDBlockMode CharBlocks, bool Proportional, int &TextBitLength);
	int __fastcall PaintChar(Graphics::TCanvas* cv, const TRDCharMatrix &CMat, int PosX, int PosY, char c, int DotSize, int DotSpacing, Graphics::TColor ColorFg, Graphics::TColor ColorFgIA, Graphics::TColor ColorBg, bool FixedWidth);
	
public:
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	__property TRDCharMatrix CharMatrix = {read=FCMat, write=SetCharMatrix};
	__fastcall virtual TRasterLab(Classes::TComponent* AOwner);
	TRDCharMatrix __fastcall CreateBitFont(Graphics::TFont* Font);
	__fastcall virtual ~TRasterLab(void);
	
__published:
	__property Align  = {default=0};
	__property Anchors  = {default=3};
	__property bool AutoHeight = {read=FAutoHeight, write=SetAutoHeight, nodefault};
	__property bool AutoCenter = {read=FAutoCenter, write=SetAutoCenter, nodefault};
	__property Graphics::TColor ColorLabBakG = {read=FColorLabBakG, write=SetColorLabBakG, nodefault};
	__property Graphics::TColor ColorDotOn = {read=FColorDotOn, write=SetColorDotOn, nodefault};
	__property Graphics::TColor ColorDotOff = {read=FColorDotOff, write=SetColorDotOff, nodefault};
	__property Sdlbase::TColorScheme ColorScheme = {read=FColorScheme, write=SetColorScheme, nodefault};
	__property int DotSpacing = {read=FDotSpacing, write=SetDotSpacing, nodefault};
	__property int DotSize = {read=FDotSize, write=SetDotSize, nodefault};
	__property Font ;
	__property Sdlbase::TFrameStyle FrameStyle = {read=FFrameStyle, write=SetFrameStyle, nodefault};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property int PosX = {read=FXPos, write=SetXPos, nodefault};
	__property int PosY = {read=FYPos, write=SetYPos, nodefault};
	__property bool Proportional = {read=FProportional, write=SetProportional, nodefault};
	__property TRDScrollMode ScrollMode = {read=FScrollMode, write=SetScrollMode, nodefault};
	__property int ScrollInterval = {read=FScrollIv, write=SetScrollIv, nodefault};
	__property int ScrollIncrement = {read=FScrollInc, write=SetScrollInc, nodefault};
	__property bool ScrollLoop = {read=FScrollLoop, write=SetScrollLoop, nodefault};
	__property TRDBlockMode CharBlockMode = {read=FCharBlockMode, write=SetCharBlockMode, nodefault};
	__property ShowHint ;
	__property AnsiString Text = {read=FLabText, write=SetLabText};
	__property Visible  = {default=1};
	__property OnClick ;
	__property OnDblClick ;
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property Classes::TNotifyEvent OnScrollTimer = {read=FOnScrollTimer, write=SetOnScrollTimer};
	__property Classes::TNotifyEvent OnScrollLoopRestart = {read=FOnScrLoopRestart, write=FOnScrLoopRestart};
};


//-- var, const, procedure ---------------------------------------------------
static const Word defLabelWidth = 0x190;
#define SDLVersionInfo "rasterlab_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Rasterlab */
using namespace Rasterlab;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// rasterlab
