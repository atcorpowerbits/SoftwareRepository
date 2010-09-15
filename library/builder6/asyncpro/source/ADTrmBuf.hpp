// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ADTrmBuf.pas' rev: 6.00

#ifndef ADTrmBufHPP
#define ADTrmBufHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdExcept.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adtrmbuf
{
//-- type declarations -------------------------------------------------------
typedef Word TadtWordArray[1073741823];

typedef Word *PadtWordArray;

typedef int TadtLongArray[536870911];

typedef int *PadtLongArray;

#pragma option push -b-
enum TAdTerminalCharAttr { tcaBold, tcaUnderline, tcaStrikethrough, tcaBlink, tcaReverse, tcaInvisible, tcaSelected };
#pragma option pop

typedef Set<TAdTerminalCharAttr, tcaBold, tcaSelected>  TAdTerminalCharAttrs;

typedef void __fastcall (__closure *TAdScrollRowsNotifyEvent)(System::TObject* aSender, int aCount, int aTop, int aBottom);

typedef void __fastcall (__closure *TAdOnCursorMovedEvent)(System::TObject* ASender, int Row, int Col);

class DELPHICLASS TadTerminalArray;
class PASCALIMPLEMENTATION TadTerminalArray : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	int FActColCount;
	int FColCount;
	int FDefaultItem;
	char *FItems;
	int FItemSize;
	int FRowCount;
	
protected:
	void __fastcall taSetColCount(int aNewCount);
	void __fastcall taSetRowCount(int aNewCount);
	void __fastcall taClearRows(char * aBuffer, int aActColCount, int aStartRow, int aEndRow);
	void __fastcall taGrowArray(int aRowCount, int aColCount, int aActColCount);
	
public:
	__fastcall TadTerminalArray(int aItemSize);
	__fastcall virtual ~TadTerminalArray(void);
	void __fastcall Clear(void);
	void __fastcall ClearItems(int aRow, int aFromCol, int aToCol);
	void __fastcall DeleteItems(int aCount, int aRow, int aCol);
	void * __fastcall GetItemPtr(int aRow, int aCol);
	void __fastcall InsertItems(int aCount, int aRow, int aCol);
	void __fastcall ReplaceItems(void * aOldItem, void * aNewItem);
	void __fastcall SetDefaultItem(void * aDefaultItem);
	void __fastcall ScrollRows(int aCount, int aStartRow, int aEndRow);
	void __fastcall WriteItems(void * aItems, int aCount, int aRow, int aCol);
	void __fastcall WriteDupItems(void * aItem, int aCount, int aRow, int aCol);
	__property int ColCount = {read=FColCount, write=taSetColCount, nodefault};
	__property int ItemSize = {read=FItemSize, nodefault};
	__property int RowCount = {read=FRowCount, write=taSetRowCount, nodefault};
};


class DELPHICLASS TAdTerminalBuffer;
class PASCALIMPLEMENTATION TAdTerminalBuffer : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	TAdTerminalCharAttrs FAttr;
	Graphics::TColor FBackColor;
	bool FBeyondMargin;
	Byte FCharSet;
	int FColCount;
	int FCursorCol;
	bool FCursorMoved;
	int FCursorRow;
	char FDefAnsiChar;
	TAdTerminalCharAttrs FDefAttr;
	Byte FDefCharSet;
	Graphics::TColor FDefBackColor;
	Graphics::TColor FDefForeColor;
	wchar_t FDefWideChar;
	int FDisplayOriginCol;
	int FDisplayOriginRow;
	int FDisplayColCount;
	int FDisplayRowCount;
	Graphics::TColor FForeColor;
	Byte *FHorzTabStops;
	void *FInvRectList;
	TAdScrollRowsNotifyEvent FOnScrollRows;
	int FRowCount;
	int FSRStartRow;
	int FSREndRow;
	int FSVRowCount;
	bool FUseAbsAddress;
	bool FUseAutoWrap;
	bool FUseAutoWrapDelay;
	bool FUseInsertMode;
	bool FUseNewLineMode;
	bool FUseScrollRegion;
	bool FUseWideChars;
	Byte *FVertTabStops;
	TadTerminalArray* FCharMatrix;
	TadTerminalArray* FCharSetMatrix;
	TadTerminalArray* FAttrMatrix;
	TadTerminalArray* FForeColorMatrix;
	TadTerminalArray* FBackColorMatrix;
	TAdOnCursorMovedEvent FOnCursorMoved;
	unsigned FTerminalHandle;
	
protected:
	int __fastcall tbGetCol(void);
	int __fastcall tbGetOriginCol(void);
	int __fastcall tbGetOriginRow(void);
	int __fastcall tbGetRow(void);
	void __fastcall tbSetBackColor(Graphics::TColor aValue);
	void __fastcall tbSetCharSet(Byte aValue);
	void __fastcall tbSetDefAnsiChar(char aValue);
	void __fastcall tbSetDefBackColor(Graphics::TColor aValue);
	void __fastcall tbSetDefForeColor(Graphics::TColor aValue);
	void __fastcall tbSetForeColor(Graphics::TColor aValue);
	void __fastcall tbSetSVRowCount(int aNewCount);
	void __fastcall tbSetCol(int aCol);
	void __fastcall tbSetColCount(int aNewCount);
	void __fastcall tbSetRow(int aRow);
	void __fastcall tbSetRowCount(int aNewCount);
	void __fastcall tbSetUseScrollRegion(bool aValue);
	void __fastcall tbInvalidateRect(int aFromRow, int aFromCol, int aToRow, int aToCol);
	int __fastcall tbCvtToInternalCol(int aCol, bool aAbsolute);
	int __fastcall tbCvtToInternalRow(int aRow, bool aAbsolute);
	int __fastcall tbCvtToExternalCol(int aCol, bool aAbsolute);
	int __fastcall tbCvtToExternalRow(int aRow, bool aAbsolute);
	bool __fastcall tbAtLastColumn(void);
	void __fastcall tbMoveCursorLeftRight(int aDirection, bool aWrap, bool aScroll);
	void __fastcall tbMoveCursorUpDown(int aDirection, bool aScroll);
	void __fastcall tbReallocBuffers(int aNewRowCount, int aNewColCount);
	void __fastcall tbScrollRows(int aCount, int aTop, int aBottom);
	void __fastcall tbFireOnCursorMovedEvent(void);
	
public:
	__fastcall TAdTerminalBuffer(bool aUseWideChars);
	__fastcall virtual ~TAdTerminalBuffer(void);
	void __fastcall GetCharAttrs(TAdTerminalCharAttrs &aValue);
	void __fastcall GetDefCharAttrs(TAdTerminalCharAttrs &aValue);
	void __fastcall SetDefCharAttrs(const TAdTerminalCharAttrs aValue);
	void __fastcall SetCharAttrs(const TAdTerminalCharAttrs aValue);
	void __fastcall MoveCursorDown(bool aScroll);
	void __fastcall MoveCursorLeft(bool aWrap, bool aScroll);
	void __fastcall MoveCursorRight(bool aWrap, bool aScroll);
	void __fastcall MoveCursorUp(bool aScroll);
	void __fastcall SetCursorPosition(int aRow, int aCol);
	void __fastcall DeleteChars(int aCount);
	void __fastcall DeleteLines(int aCount);
	void __fastcall InsertChars(int aCount);
	void __fastcall InsertLines(int aCount);
	void __fastcall EraseAll(void);
	void __fastcall EraseChars(int aCount);
	void __fastcall EraseFromBOW(void);
	void __fastcall EraseFromBOL(void);
	void __fastcall EraseLine(void);
	void __fastcall EraseScreen(void);
	void __fastcall EraseToEOL(void);
	void __fastcall EraseToEOW(void);
	void __fastcall SetHorzTabStop(void);
	void __fastcall ClearHorzTabStop(void);
	void __fastcall ClearAllHorzTabStops(void);
	void __fastcall DoHorzTab(void);
	void __fastcall DoBackHorzTab(void);
	void __fastcall SetVertTabStop(void);
	void __fastcall ClearVertTabStop(void);
	void __fastcall ClearAllVertTabStops(void);
	void __fastcall DoVertTab(void);
	void __fastcall DoBackVertTab(void);
	void __fastcall SetScrollRegion(int aTopRow, int aBottomRow);
	void __fastcall WriteChar(char aCh);
	void __fastcall WriteString(const AnsiString aSt);
	void __fastcall DoBackspace(void);
	void __fastcall DoCarriageReturn(void);
	void __fastcall DoLineFeed(void);
	void __fastcall Reset(void);
	void * __fastcall GetLineCharPtr(int aRow);
	void * __fastcall GetLineAttrPtr(int aRow);
	void * __fastcall GetLineForeColorPtr(int aRow);
	void * __fastcall GetLineBackColorPtr(int aRow);
	void * __fastcall GetLineCharSetPtr(int aRow);
	bool __fastcall HasCursorMoved(void);
	bool __fastcall HasDisplayChanged(void);
	bool __fastcall GetInvalidRect(Types::TRect &aRect);
	void __fastcall RegisterTerminalHandle(unsigned AHandle);
	void __fastcall DeregisterTerminalHandle(void);
	__property Graphics::TColor BackColor = {read=FBackColor, write=tbSetBackColor, nodefault};
	__property Byte CharSet = {read=FCharSet, write=tbSetCharSet, nodefault};
	__property char DefAnsiChar = {read=FDefAnsiChar, write=tbSetDefAnsiChar, nodefault};
	__property Graphics::TColor DefBackColor = {read=FDefBackColor, write=tbSetDefBackColor, nodefault};
	__property Byte DefCharSet = {read=FDefCharSet, write=FDefCharSet, nodefault};
	__property Graphics::TColor DefForeColor = {read=FDefForeColor, write=tbSetDefForeColor, nodefault};
	__property Graphics::TColor ForeColor = {read=FForeColor, write=tbSetForeColor, nodefault};
	__property int SVRowCount = {read=FSVRowCount, write=tbSetSVRowCount, nodefault};
	__property int Col = {read=tbGetCol, write=tbSetCol, nodefault};
	__property int ColCount = {read=FColCount, write=tbSetColCount, nodefault};
	__property int OriginCol = {read=tbGetOriginCol, nodefault};
	__property int OriginRow = {read=tbGetOriginRow, nodefault};
	__property int Row = {read=tbGetRow, write=tbSetRow, nodefault};
	__property int RowCount = {read=FRowCount, write=tbSetRowCount, nodefault};
	__property bool UseAbsAddress = {read=FUseAbsAddress, write=FUseAbsAddress, nodefault};
	__property bool UseAutoWrap = {read=FUseAutoWrap, write=FUseAutoWrap, nodefault};
	__property bool UseAutoWrapDelay = {read=FUseAutoWrapDelay, write=FUseAutoWrapDelay, nodefault};
	__property bool UseInsertMode = {read=FUseInsertMode, write=FUseInsertMode, nodefault};
	__property bool UseNewLineMode = {read=FUseNewLineMode, write=FUseNewLineMode, nodefault};
	__property bool UseScrollRegion = {read=FUseScrollRegion, write=tbSetUseScrollRegion, nodefault};
	__property bool UseWideChars = {read=FUseWideChars, nodefault};
	__property TAdScrollRowsNotifyEvent OnScrollRows = {read=FOnScrollRows, write=FOnScrollRows};
	__property TAdOnCursorMovedEvent OnCursorMoved = {read=FOnCursorMoved, write=FOnCursorMoved};
};


//-- var, const, procedure ---------------------------------------------------
static const int adc_TermBufForeColor = 0xc0c0c0;
static const int adc_TermBufBackColor = 0x0;
static const Shortint adc_TermBufColCount = 0x50;
static const Shortint adc_TermBufRowCount = 0x18;
static const Byte adc_TermBufScrollRowCount = 0xc8;
static const bool adc_TermBufUseAbsAddress = true;
static const bool adc_TermBufUseAutoWrap = true;
static const bool adc_TermBufUseAutoWrapDelay = true;
static const bool adc_TermBufUseInsertMode = false;
static const bool adc_TermBufUseNewLineMode = false;
static const bool adc_TermBufUseScrollRegion = false;
extern PACKAGE void __fastcall RaiseTerminalException(TMetaClass* aClass, int aErrorCode, const AnsiString aStrParam1, const AnsiString aStrParam2, const AnsiString aStrParam3, int aIntParam1, int aIntParam2, int aIntParam3);

}	/* namespace Adtrmbuf */
using namespace Adtrmbuf;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ADTrmBuf
