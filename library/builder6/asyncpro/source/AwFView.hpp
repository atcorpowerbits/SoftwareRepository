// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AwFView.pas' rev: 6.00

#ifndef AwFViewHPP
#define AwFViewHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AwFaxCvt.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <ShellAPI.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Awfview
{
//-- type declarations -------------------------------------------------------
typedef Oomisc::TMemoryBitmapDesc TFax[5460];

typedef Oomisc::TMemoryBitmapDesc *PFax;

typedef int __stdcall (*TViewerWndProc)(HWND Wnd, unsigned Msg, int wParam, int lParam);

#pragma pack(push, 4)
struct wMsg
{
	HWND hWindow;
	unsigned Message;
	union
	{
		struct 
		{
			Word wParamLo;
			Word wParamHi;
			Word lParamLo;
			Word lParamHi;
			
		};
		struct 
		{
			int wParam;
			int lParam;
			
		};
		
	};
} ;
#pragma pack(pop)

class DELPHICLASS TViewer;
class PASCALIMPLEMENTATION TViewer : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	HWND vWnd;
	Oomisc::TUnpackFax *vUnpacker;
	Oomisc::TMemoryBitmapDesc *vImage;
	unsigned vUnpPage;
	BOOL vLoadWholeFax;
	HICON vBusyCursor;
	BOOL vDragDrop;
	int vFGColor;
	int vBGCOlor;
	unsigned vScaledWidth;
	unsigned vScaledHeight;
	int vVScrollInc;
	int vHScrollInc;
	BOOL vSizing;
	BOOL vVScrolling;
	BOOL vHScrolling;
	unsigned vNumPages;
	unsigned vOnPage;
	unsigned vTopRow;
	unsigned vLeftOfs;
	unsigned vMaxVScroll;
	unsigned vMaxHScroll;
	unsigned vHMult;
	unsigned vHDiv;
	unsigned vVMult;
	unsigned vVDiv;
	unsigned vRotateDir;
	BOOL vMarked;
	BOOL vCaptured;
	unsigned vAnchorCorner;
	BOOL vOutsideEdge;
	unsigned vMarkTimer;
	#pragma pack(push, 1)
	Types::TRect vMarkRect;
	#pragma pack(pop)
	
	BOOL vCtrlDown;
	TViewerWndProc vDefWndProc;
	char vFileName[256];
	char vComponentName[256];
	bool vUpdating;
	bool vDesigning;
	__fastcall TViewer(int AWnd);
	__fastcall virtual ~TViewer(void);
	void __fastcall vAllocFax(unsigned NumPages);
	void __fastcall vDisposeFax(void);
	void __fastcall vInitScrollbars(void);
	void __fastcall vUpdateScrollThumb(BOOL Vert);
	void __fastcall vCalcMaxScrollPos(void);
	void __fastcall vScrollUpPrim(unsigned Delta);
	void __fastcall vScrollDownPrim(unsigned Delta);
	void __fastcall vScrollLeftPrim(unsigned Delta);
	void __fastcall vScrollRightPrim(unsigned Delta);
	void __fastcall vScrollUp(void);
	void __fastcall vScrollDown(void);
	void __fastcall vScrollLeft(void);
	void __fastcall vScrollRight(void);
	void __fastcall vJumpUp(void);
	void __fastcall vJumpDown(void);
	void __fastcall vJumpLeft(void);
	void __fastcall vJumpRight(void);
	void __fastcall vHomeVertical(void);
	void __fastcall vEndVertical(void);
	void __fastcall vHomeHorizontal(void);
	void __fastcall vEndHorizontal(void);
	void __fastcall vInitPage(void);
	void __fastcall vPageUp(void);
	void __fastcall vPageDown(void);
	void __fastcall vFirstPage(void);
	void __fastcall vLastPage(void);
	int __fastcall vRotatePage(const unsigned PageNum, const unsigned Direction);
	void __fastcall vUpdateMarkRect(const Types::TRect &Client, int X, int Y);
	void __fastcall vCopyToClipboard(void);
	void __fastcall vInvalidateAll(void);
	void __fastcall vPaint(HDC PaintDC, tagPAINTSTRUCT &PaintInfo);
	void __fastcall vGetMarkClientIntersection(Types::TRect &R, const Types::TRect &Mark);
	void __fastcall vInitDragDrop(BOOL Enabled);
	int __fastcall apwViewSetFile(char * FName);
	void __fastcall apwViewSetFG(int Color);
	void __fastcall apwViewSetBG(int Color);
	void __fastcall apwViewSetScale(Oomisc::PScaleSettings Settings);
	int __fastcall apwViewSetWhitespace(unsigned FromLines, unsigned ToLines);
	void __fastcall apwViewSetScroll(unsigned HScroll, unsigned VScroll);
	int __fastcall apwViewSelectAll(void);
	int __fastcall apwViewSelect(Types::PRect R);
	int __fastcall apwViewCopy(void);
	HBITMAP __fastcall apwViewGetBitmap(unsigned Page, Types::PPoint Point);
	unsigned __fastcall apwViewGetNumPages(void);
	void __fastcall apwViewStartUpdate(void);
	void __fastcall apwViewEndUpdate(void);
	void __fastcall apwViewSetWndProc(wMsg &Msg);
	int __fastcall apwViewGotoPage(unsigned Page);
	int __fastcall apwViewGetCurPage(void);
	void __fastcall apwViewSetDesignMode(char * Name);
	int __fastcall apwViewSetRotation(unsigned Direction);
	void __fastcall apwViewSetAutoScale(Word Kind);
	void __fastcall apwViewGetPageDim(Types::PRect R);
	Word __fastcall apwViewGetPageFlags(void);
	int __fastcall apwViewSetLoadWholeFax(BOOL LoadWhole);
	void __fastcall apwViewSetBusyCursor(HICON NewCursor);
	void __fastcall wmPaint(wMsg &Msg);
	int __fastcall wmSize(wMsg &Msg);
	int __fastcall wmGetDlgCode(wMsg &Msg);
	int __fastcall wmKeyDown(wMsg &Msg);
	int __fastcall wmKeyUp(wMsg &Msg);
	void __fastcall wmLButtonDown(wMsg &Msg);
	void __fastcall wmLButtonUp(wMsg &Msg);
	void __fastcall wmMouseMove(wMsg &Msg);
	void __fastcall wmTimer(wMsg &Msg);
	void __fastcall wmVScroll(wMsg &Msg);
	void __fastcall wmHScroll(wMsg &Msg);
	void __fastcall wmDropFiles(wMsg &Msg);
};


//-- var, const, procedure ---------------------------------------------------
static const Word MaxFaxPages = 0x1554;
extern PACKAGE void __fastcall RegisterFaxViewerClass(bool Designing);

}	/* namespace Awfview */
using namespace Awfview;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AwFView
