// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdFView.pas' rev: 6.00

#ifndef AdFViewHPP
#define AdFViewHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdFaxCvt.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <AwFView.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adfview
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TViewerRotation { vr0, vr90, vr180, vr270 };
#pragma option pop

typedef void __fastcall (__closure *TViewerFileDropEvent)(System::TObject* Sender, AnsiString FileName);

typedef void __fastcall (__closure *TViewerErrorEvent)(System::TObject* Sender, int ErrorCode);

class DELPHICLASS TApdCustomFaxViewer;
class PASCALIMPLEMENTATION TApdCustomFaxViewer : public Oomisc::TApdBaseWinControl 
{
	typedef Oomisc::TApdBaseWinControl inherited;
	
protected:
	Forms::TFormBorderStyle FBorderStyle;
	Graphics::TColor FFGColor;
	Graphics::TColor FBGColor;
	bool FScaling;
	unsigned FHorizMult;
	unsigned FHorizDiv;
	unsigned FVertMult;
	unsigned FVertDiv;
	Adfaxcvt::TAutoScaleMode FAutoScaleMode;
	bool FWhitespaceCompression;
	unsigned FWhitespaceFrom;
	unsigned FWhitespaceTo;
	unsigned FHorizScroll;
	unsigned FVertScroll;
	AnsiString FFileName;
	bool FAcceptDragged;
	bool FLoadWholeFax;
	TViewerRotation FRotation;
	Controls::TCursor FBusyCursor;
	TViewerFileDropEvent FFileDrop;
	Classes::TNotifyEvent FPageChange;
	TViewerErrorEvent FViewerError;
	bool HasBeenCreated;
	virtual void __fastcall CreateWnd(void);
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	virtual void __fastcall SetName(const AnsiString NewName);
	void __fastcall SetBorderStyle(const Forms::TBorderStyle NewStyle);
	void __fastcall SetFGColor(const Graphics::TColor NewColor);
	void __fastcall SetBGColor(const Graphics::TColor NewColor);
	void __fastcall SetScaling(const bool NewScaling);
	void __fastcall SetHorizMult(const unsigned NewHorizMult);
	void __fastcall SetHorizDiv(const unsigned NewHorizDiv);
	void __fastcall SetVertMult(const unsigned NewVertMult);
	void __fastcall SetVertDiv(const unsigned NewVertDiv);
	void __fastcall SetAutoScaleMode(const Adfaxcvt::TAutoScaleMode NewAutoScaleMode);
	void __fastcall SetWhitespaceCompression(const bool NewCompression);
	void __fastcall SetWhitespaceFrom(const unsigned NewWhitespaceFrom);
	void __fastcall SetWhitespaceTo(const unsigned NewWhitespaceTo);
	void __fastcall SetHorizScroll(const unsigned NewHorizScroll);
	void __fastcall SetVertScroll(const unsigned NewVertScroll);
	void __fastcall SetAcceptDragged(const bool NewAccept);
	void __fastcall SetLoadWholeFax(const bool NewLoadWholeFax);
	void __fastcall SetFileName(const AnsiString NewFileName);
	void __fastcall SetRotation(const TViewerRotation NewRotation);
	void __fastcall SetBusyCursor(const Controls::TCursor NewBusyCursor);
	void __fastcall SetActivePage(const unsigned NewPage);
	Graphics::TBitmap* __fastcall GetPageBitmaps(const int PageNum);
	unsigned __fastcall GetNumPages(void);
	unsigned __fastcall GetActivePage(void);
	unsigned __fastcall GetPageWidth(void);
	unsigned __fastcall GetPageHeight(void);
	Word __fastcall GetPageFlags(void);
	virtual void __fastcall FileDropped(void);
	MESSAGE void __fastcall PageChange(Messages::TMessage &Msg);
	MESSAGE void __fastcall ViewerError(Messages::TMessage &Msg);
	void __fastcall FillScaleSettings(Oomisc::TScaleSettings &Settings);
	MESSAGE void __fastcall wmDropFiles(Awfview::wMsg &Msg);
	HIDESBASE MESSAGE void __fastcall wmEraseBkGnd(Messages::TMessage &Msg);
	
public:
	__fastcall virtual TApdCustomFaxViewer(Classes::TComponent* AOwner);
	void __fastcall BeginUpdate(void);
	void __fastcall EndUpdate(void);
	void __fastcall FirstPage(void);
	void __fastcall LastPage(void);
	void __fastcall NextPage(void);
	void __fastcall PrevPage(void);
	void __fastcall SelectRegion(const Types::TRect &R);
	void __fastcall SelectImage(void);
	void __fastcall CopyToClipBoard(void);
	__property Forms::TBorderStyle BorderStyle = {read=FBorderStyle, write=SetBorderStyle, default=1};
	__property Graphics::TColor FGColor = {read=FFGColor, write=SetFGColor, default=0};
	__property Graphics::TColor BGColor = {read=FBGColor, write=SetBGColor, default=16777215};
	__property bool Scaling = {read=FScaling, write=SetScaling, nodefault};
	__property unsigned HorizMult = {read=FHorizMult, write=SetHorizMult, default=1};
	__property unsigned HorizDiv = {read=FHorizDiv, write=SetHorizDiv, default=1};
	__property unsigned VertMult = {read=FVertMult, write=SetVertMult, default=1};
	__property unsigned VertDiv = {read=FVertDiv, write=SetVertDiv, default=1};
	__property Adfaxcvt::TAutoScaleMode AutoScaleMode = {read=FAutoScaleMode, write=SetAutoScaleMode, default=1};
	__property bool WhitespaceCompression = {read=FWhitespaceCompression, write=SetWhitespaceCompression, default=0};
	__property unsigned WhitespaceFrom = {read=FWhitespaceFrom, write=SetWhitespaceFrom, default=0};
	__property unsigned WhitespaceTo = {read=FWhitespaceTo, write=SetWhitespaceTo, default=0};
	__property unsigned HorizScroll = {read=FHorizScroll, write=SetHorizScroll, default=8};
	__property unsigned VertScroll = {read=FVertScroll, write=SetVertScroll, default=8};
	__property bool AcceptDragged = {read=FAcceptDragged, write=SetAcceptDragged, default=1};
	__property bool LoadWholeFax = {read=FLoadWholeFax, write=SetLoadWholeFax, default=0};
	__property AnsiString FileName = {read=FFileName, write=SetFileName};
	__property TViewerRotation Rotation = {read=FRotation, write=SetRotation, default=0};
	__property Controls::TCursor BusyCursor = {read=FBusyCursor, write=SetBusyCursor, default=0};
	__property Graphics::TBitmap* PageBitmaps[int Index] = {read=GetPageBitmaps};
	__property unsigned NumPages = {read=GetNumPages, nodefault};
	__property unsigned ActivePage = {read=GetActivePage, write=SetActivePage, nodefault};
	__property unsigned PageWidth = {read=GetPageWidth, nodefault};
	__property unsigned PageHeight = {read=GetPageHeight, nodefault};
	__property Word PageFlags = {read=GetPageFlags, nodefault};
	__property TViewerFileDropEvent OnDropFile = {read=FFileDrop, write=FFileDrop};
	__property Classes::TNotifyEvent OnPageChange = {read=FPageChange, write=FPageChange};
	__property TViewerErrorEvent OnViewerError = {read=FViewerError, write=FViewerError};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TApdCustomFaxViewer(HWND ParentWindow) : Oomisc::TApdBaseWinControl(ParentWindow) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TWinControl.Destroy */ inline __fastcall virtual ~TApdCustomFaxViewer(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdFaxViewer;
class PASCALIMPLEMENTATION TApdFaxViewer : public TApdCustomFaxViewer 
{
	typedef TApdCustomFaxViewer inherited;
	
__published:
	__property Version ;
	__property BorderStyle  = {default=1};
	__property FGColor  = {default=0};
	__property BGColor  = {default=16777215};
	__property Scaling ;
	__property HorizMult  = {default=1};
	__property HorizDiv  = {default=1};
	__property VertMult  = {default=1};
	__property VertDiv  = {default=1};
	__property AutoScaleMode  = {default=1};
	__property WhitespaceCompression  = {default=0};
	__property WhitespaceFrom  = {default=0};
	__property WhitespaceTo  = {default=0};
	__property HorizScroll  = {default=8};
	__property VertScroll  = {default=8};
	__property AcceptDragged  = {default=1};
	__property LoadWholeFax  = {default=0};
	__property BusyCursor  = {default=0};
	__property FileName ;
	__property OnDropFile ;
	__property OnPageChange ;
	__property OnViewerError ;
	__property Align  = {default=0};
	__property Ctl3D ;
	__property Cursor  = {default=0};
	__property Enabled  = {default=1};
	__property Font ;
	__property ParentColor  = {default=1};
	__property ParentCtl3D  = {default=1};
	__property ParentFont  = {default=1};
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=0};
	__property Visible  = {default=1};
	__property OnClick ;
	__property OnDblClick ;
	__property OnExit ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
public:
	#pragma option push -w-inl
	/* TApdCustomFaxViewer.Create */ inline __fastcall virtual TApdFaxViewer(Classes::TComponent* AOwner) : TApdCustomFaxViewer(AOwner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TApdFaxViewer(HWND ParentWindow) : TApdCustomFaxViewer(ParentWindow) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TWinControl.Destroy */ inline __fastcall virtual ~TApdFaxViewer(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define afvDefViewBorderStyle (Forms::TFormBorderStyle)(1)
static const int afvDefFGColor = 0x0;
static const int afvDefBGColor = 0xffffff;
static const bool afvDefScaling = false;
static const Shortint afvDefHorizMult = 0x1;
static const Shortint afvDefHorizDiv = 0x1;
static const Shortint afvDefVertMult = 0x1;
static const Shortint afvDefVertDiv = 0x1;
#define afvDefViewAutoScaleMode (Adfaxcvt::TAutoScaleMode)(1)
static const bool afvDefWhitespaceCompression = false;
static const Shortint afvDefWhitespaceFrom = 0x0;
static const Shortint afvDefWhitespaceTo = 0x0;
static const Shortint afvDefHorizScroll = 0x8;
static const Shortint afvDefVertScroll = 0x8;
#define afvDefFileName ""
static const bool afvDefAcceptDragged = true;
static const bool afvDefLoadWholeFax = false;
static const Shortint afvDefViewerHeight = 0x32;
static const Shortint afvDefViewerWidth = 0x64;
#define afvDefRotation (TViewerRotation)(0)
static const short afvDefBusyCursor = 0x0;

}	/* namespace Adfview */
using namespace Adfview;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdFView
