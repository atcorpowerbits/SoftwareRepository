// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'thumbnails.pas' rev: 6.00

#ifndef thumbnailsHPP
#define thumbnailsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <dstruct.hpp>	// Pascal unit
#include <sdlbase.hpp>	// Pascal unit
#include <SyncObjs.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
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

namespace Thumbnails
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TImageRequestProcessing { irpShowEmpty, irpShowSlide, irpShowFrameOnly, irpShowNothing };
#pragma option pop

typedef void __fastcall (__closure *TImageRequestEvent)(System::TObject* Sender, int ThumbID, TImageRequestProcessing &HowToProcess, int &MarkIt, Graphics::TBitmap* &ImgBuffer);

typedef void __fastcall (__closure *TImageClickEvent)(System::TObject* Sender, int X, int Y, int ThumbID);

typedef void __fastcall (__closure *TSlideRenderedEvent)(System::TObject* Sender, Graphics::TCanvas* Canvas, int X, int Y, int ThumbID);

#pragma option push -b-
enum TSlideSelectMode { ssmDisabled, ssmSingle, ssmMultiple };
#pragma option pop

class DELPHICLASS TThumbnails;
class PASCALIMPLEMENTATION TThumbnails : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	Sdlbase::TFrameStyle FFrameStyle;
	Graphics::TColor FColorBG;
	Graphics::TColor FColBlackLine;
	Graphics::TColor FColGrayLine;
	Graphics::TColor FColWhiteLine;
	Sdlbase::TColorScheme FColorScheme;
	double FFirstThumbIx;
	int FMin;
	int FMax;
	int FNumSldX;
	int FNumSldY;
	int FThumbBaseSize;
	int FSLideDist;
	int FSlideMargin;
	Sdlbase::TFrameStyle FOuterFrameStyle;
	Sdlbase::TFrameStyle FInnerFrameStyle;
	TImageRequestEvent FOnImageRequest;
	TSlideRenderedEvent FOnSlideRendered;
	TImageClickEvent FOnImageClick;
	TImageClickEvent FOnImageDblClick;
	Classes::TNotifyEvent FOnHiliteChange;
	Classes::TNotifyEvent FOnFirstImgRequ;
	Classes::TNotifyEvent FOnLastImgRequ;
	bool FAntiAlias;
	Graphics::TColor FColorCover;
	Graphics::TColor FColorSelected;
	Graphics::TColor FColorHilite;
	Graphics::TColor FMarkColor;
	int FLastHiLite;
	int FHiliteThickness;
	bool FIsWorking;
	Dstruct::TBitFld* FSelectedSlide;
	TSlideSelectMode FSelectMode;
	int FLastClickedSlide;
	MESSAGE void __fastcall WMImageClick(Messages::TWMMouse &Msg);
	MESSAGE void __fastcall WMImageDblClick(Messages::TWMMouse &Msg);
	bool __fastcall GetSelectedSlide(int sldnum);
	void __fastcall SetColorBG(Graphics::TColor Value);
	void __fastcall SetColorCover(Graphics::TColor Value);
	void __fastcall SetColorSelected(Graphics::TColor Value);
	void __fastcall SetColorHilite(Graphics::TColor Value);
	void __fastcall SetMarkColor(Graphics::TColor Value);
	void __fastcall SetBaseSize(int Value);
	void __fastcall SetHiliteThickn(int Value);
	void __fastcall SetFirstThumbIx(double Value);
	void __fastcall SetFMin(int Value);
	void __fastcall SetFMax(int Value);
	void __fastcall SetAntiAlias(bool value);
	void __fastcall SetSlideMargin(int Value);
	void __fastcall SetSlideDist(int Value);
	void __fastcall SetColorScheme(Sdlbase::TColorScheme Value);
	void __fastcall SetFrameStyle(Sdlbase::TFrameStyle value);
	void __fastcall SetOuterFrameStyle(Sdlbase::TFrameStyle value);
	void __fastcall SetInnerFrameStyle(Sdlbase::TFrameStyle value);
	void __fastcall SetSelectedSlide(int sldnum, bool value);
	void __fastcall SetSlideSelectMode(TSlideSelectMode value);
	
protected:
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Paint(void);
	void __fastcall HiLite(int ix);
	void __fastcall ResetLastHiLite(void);
	
public:
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	__fastcall virtual TThumbnails(Classes::TComponent* AOwner);
	__fastcall virtual ~TThumbnails(void);
	__property double FirstThumbIdx = {read=FFirstThumbIx, write=SetFirstThumbIx};
	int __fastcall FirstSelectedSlide(void);
	__property int NumSlidesHoriz = {read=FNumSldX, nodefault};
	__property int NumSlidesVert = {read=FNumSldY, nodefault};
	int __fastcall NumSlidesSelected(void);
	int __fastcall CalcSlideIndex(int XPos, int YPos);
	void __fastcall CalcSlidePos(int SldNum, int &XPos, int &YPos);
	void __fastcall ResetAllSelections(void);
	__property bool SlideSelected[int SldNum] = {read=GetSelectedSlide, write=SetSelectedSlide};
	
__published:
	__property Align  = {default=0};
	__property TSlideSelectMode SlideSelectMode = {read=FSelectMode, write=SetSlideSelectMode, nodefault};
	__property Anchors  = {default=3};
	__property bool AntiAlias = {read=FAntiAlias, write=SetAntiAlias, nodefault};
	__property Graphics::TColor ColorBackGnd = {read=FColorBG, write=SetColorBG, nodefault};
	__property Graphics::TColor ColorCover = {read=FColorCover, write=SetColorCover, nodefault};
	__property Graphics::TColor ColorSelected = {read=FColorSelected, write=SetColorSelected, nodefault};
	__property Graphics::TColor ColorFocus = {read=FColorHilite, write=SetColorHilite, nodefault};
	__property Graphics::TColor ColorMark = {read=FMarkColor, write=SetMarkColor, nodefault};
	__property Sdlbase::TColorScheme ColorScheme = {read=FColorScheme, write=SetColorScheme, nodefault};
	__property DragCursor  = {default=-12};
	__property DragMode  = {default=0};
	__property Enabled  = {default=1};
	__property Font ;
	__property Sdlbase::TFrameStyle FrameStyle = {read=FFrameStyle, write=SetFrameStyle, nodefault};
	__property int FocusLinewidth = {read=FHiliteThickness, write=SetHiliteThickn, nodefault};
	__property int FocusedSlide = {read=FLastHiLite, nodefault};
	__property Sdlbase::TFrameStyle InnerFrameStyle = {read=FInnerFrameStyle, write=SetInnerFrameStyle, nodefault};
	__property int Max = {read=FMax, write=SetFMax, nodefault};
	__property int Min = {read=FMin, write=SetFMin, nodefault};
	__property Sdlbase::TFrameStyle OuterFrameStyle = {read=FOuterFrameStyle, write=SetOuterFrameStyle, nodefault};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowHint ;
	__property int SlideSize = {read=FThumbBaseSize, write=SetBaseSize, nodefault};
	__property int SlideDistance = {read=FSLideDist, write=SetSlideDist, nodefault};
	__property int SlideMargin = {read=FSlideMargin, write=SetSlideMargin, nodefault};
	__property Visible  = {default=1};
	__property OnClick ;
	__property OnDblClick ;
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property OnStartDrag ;
	__property OnDragDrop ;
	__property OnEndDrag ;
	__property OnDragOver ;
	__property TImageRequestEvent OnImageRequest = {read=FOnImageRequest, write=FOnImageRequest};
	__property TImageClickEvent OnImageClick = {read=FOnImageClick, write=FOnImageClick};
	__property TImageClickEvent OnImageDblClick = {read=FOnImageDblClick, write=FOnImageDblClick};
	__property Classes::TNotifyEvent OnFocusChange = {read=FOnHiliteChange, write=FOnHiliteChange};
	__property Classes::TNotifyEvent OnFirstImageRequest = {read=FOnFirstImgRequ, write=FOnFirstImgRequ};
	__property Classes::TNotifyEvent OnLastImageRequest = {read=FOnLastImgRequ, write=FOnLastImgRequ};
	__property TSlideRenderedEvent OnSlideRendered = {read=FOnSlideRendered, write=FOnSlideRendered};
	__property OnResize ;
};


//-- var, const, procedure ---------------------------------------------------
#define SDLVersionInfo "thumbnails_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Thumbnails */
using namespace Thumbnails;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// thumbnails
