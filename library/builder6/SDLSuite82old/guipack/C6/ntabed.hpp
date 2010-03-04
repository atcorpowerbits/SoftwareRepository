// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ntabed.pas' rev: 6.00

#ifndef ntabedHPP
#define ntabedHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <datatable.hpp>	// Pascal unit
#include <matrix.hpp>	// Pascal unit
#include <sdlbase.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Grids.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Ntabed
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESDLNTabedError;
class PASCALIMPLEMENTATION ESDLNTabedError : public Sdlbase::ESDLError 
{
	typedef Sdlbase::ESDLError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLNTabedError(const AnsiString Msg) : Sdlbase::ESDLError(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLNTabedError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sdlbase::ESDLError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLNTabedError(int Ident)/* overload */ : Sdlbase::ESDLError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLNTabedError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sdlbase::ESDLError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLNTabedError(const AnsiString Msg, int AHelpContext) : Sdlbase::ESDLError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLNTabedError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sdlbase::ESDLError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLNTabedError(int Ident, int AHelpContext)/* overload */ : Sdlbase::ESDLError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLNTabedError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sdlbase::ESDLError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLNTabedError(void) { }
	#pragma option pop
	
};


typedef DynamicArray<Shortint >  ntabed__3;

class DELPHICLASS TNTabEd;
class PASCALIMPLEMENTATION TNTabEd : public Grids::TCustomGrid 
{
	typedef Grids::TCustomGrid inherited;
	
private:
	bool FAutoAdvance;
	Classes::TNotifyEvent FOnChange;
	Classes::TNotifyEvent FOnChangeSetup;
	int FClassColWidth;
	int FColOffset;
	int FRowOffset;
	DynamicArray<Shortint >  FDecP;
	bool FExtMatAssigned;
	int FNumWidth;
	Grids::TGetEditEvent FOnGetEditText;
	Grids::TSetEditEvent FOnSetEditText;
	bool FSortIncludeHd;
	bool FSuppressPaint;
	bool FInternSuppPaint;
	Menus::TPopupMenu* FPopupD;
	int FPopupDMask;
	Menus::TPopupMenu* FPopupH;
	int FPopupHMask;
	int FPopupMMask;
	int FPopupUMask;
	Graphics::TColor FColorBkgnd;
	Graphics::TColor FColorFixed;
	Graphics::TColor FColorNormal;
	Graphics::TColor FColorMarked1;
	Graphics::TColor FColorMarked2;
	Graphics::TColor FColorMarkedBoth;
	Graphics::TColor FColorSelected;
	bool FNameEdActive;
	Stdctrls::TEdit* FNameEd;
	bool FCommentMMActive;
	Stdctrls::TMemo* FCommentMM;
	int FLastCellX;
	int FLastCellY;
	void __fastcall CommentMemoKeyPress(System::TObject* Sender, char &Key);
	void __fastcall ExchangeDuringSort(System::TObject* Sender, Byte ExchgWhat, int index1, int index2, int first, int last);
	bool __fastcall GetColAttVis(void);
	bool __fastcall GetRowAttVis(void);
	Byte __fastcall GetRowAttrib(int RowNr);
	Byte __fastcall GetCellState(int ACol, int ARow);
	Byte __fastcall GetColAttrib(int ColNr);
	Datatable::TDTNameStr __fastcall GetColName(int ColNr);
	HIDESBASE int __fastcall GetColWidths(int Index);
	AnsiString __fastcall GetComment();
	Shortint __fastcall GetDecPlaces(int ColNr);
	int __fastcall GetDefColWidth(void);
	double __fastcall GetElem(int ACol, int ARow);
	bool __fastcall GetElemMarkedA(int ACol, int ARow);
	bool __fastcall GetElemMarkedB(int ACol, int ARow);
	Datatable::TDTNameStr __fastcall GetRowName(int RowNr);
	int __fastcall GetNrCols(void);
	int __fastcall GetNrRows(void);
	void __fastcall DataHasChanged(System::TObject* Sender);
	void __fastcall NameEdKeyPress(System::TObject* Sender, char &Key);
	void __fastcall DataHasBeenResized(System::TObject* Sender, int OldColumns, int OldRows, int NewColumns, int NewRows);
	void __fastcall SetSuppressPaint(bool supp);
	void __fastcall SetRowAttrib(int RowNr, Byte Attrib);
	void __fastcall SetCellState(int ACol, int ARow, const Byte Value);
	void __fastcall SetColAttrib(int ColNr, Byte Attrib);
	void __fastcall SetColAttVis(bool vis);
	void __fastcall SetRowAttVis(bool vis);
	void __fastcall SetColName(int ColNr,  Datatable::TDTNameStr &HLine);
	void __fastcall SetColorBackground(Graphics::TColor color);
	void __fastcall SetColorFixed(Graphics::TColor color);
	void __fastcall SetColorMarkedA(Graphics::TColor color);
	void __fastcall SetColorMarkedB(Graphics::TColor color);
	void __fastcall SetColorMarkedBoth(Graphics::TColor color);
	void __fastcall SetColorNormal(Graphics::TColor color);
	void __fastcall SetColorSelected(Graphics::TColor color);
	HIDESBASE void __fastcall SetColWidths(int Index, int Value);
	void __fastcall SetDecPlaces(int ColNr, Shortint Dp);
	void __fastcall SetDefColWidth(int DefW);
	void __fastcall SetElem(int ACol, int ARow, const double Value);
	void __fastcall SetElemMarkedA(int ACol, int ARow, const bool Value);
	void __fastcall SetElemMarkedB(int ACol, int ARow, const bool Value);
	void __fastcall SetComment(AnsiString cmt);
	void __fastcall SetNrCols(int NrCols);
	void __fastcall SetNrRows(int NrRows);
	void __fastcall SetNumWidth(int nw);
	void __fastcall SetPopupDMask(int mask);
	void __fastcall SetPopupHMask(int mask);
	void __fastcall SetRowName(int RowNr,  Datatable::TDTNameStr &HLine);
	void __fastcall PopupMenuDLoadPopup(System::TObject* Sender);
	
protected:
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall Keypress(char &Key);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	DYNAMIC AnsiString __fastcall GetEditText(int ACol, int ARow);
	DYNAMIC void __fastcall SetEditText(int ACol, int ARow, const AnsiString Value);
	void __fastcall HighLightSelCell(int cx, int cy);
	virtual void __fastcall DrawCell(int ACol, int ARow, const Types::TRect &ARect, Grids::TGridDrawState AState);
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	
public:
	Datatable::TDataTable* Data;
	__fastcall virtual TNTabEd(Classes::TComponent* AOwner);
	__fastcall virtual ~TNTabEd(void);
	void __fastcall AssignAnotherDataMatrix(Datatable::TDataTable* NewDTab);
	void __fastcall AutoColWidth(int ColNr, bool IncludeHeader, int Addon);
	HIDESBASE void __fastcall Changed(void);
	void __fastcall ChangedSetup(void);
	void __fastcall Fill(double value);
	__property double Elem[int ACol][int ARow] = {read=GetElem, write=SetElem/*, default*/};
	__property Byte CellState[int ACol][int ARow] = {read=GetCellState, write=SetCellState};
	__property bool ElemMarkedA[int ACol][int ARow] = {read=GetElemMarkedA, write=SetElemMarkedA};
	__property bool ElemMarkedB[int ACol][int ARow] = {read=GetElemMarkedB, write=SetElemMarkedB};
	void __fastcall Redimension(int NrCols, int NrRows);
	__property Byte RowAttrib[int ix] = {read=GetRowAttrib, write=SetRowAttrib};
	__property Byte ColAttrib[int ix] = {read=GetColAttrib, write=SetColAttrib};
	bool __fastcall IfColumnMarked(int col);
	bool __fastcall IfRowMarked(int row);
	void __fastcall Clear(void);
	__property Datatable::TDTNameStr ColName[int ix] = {read=GetColName, write=SetColName};
	__property int ColWidths[int Index] = {read=GetColWidths, write=SetColWidths};
	void __fastcall CopyContentsFrom(TNTabEd* ExtTab);
	void __fastcall PopupMenuClickClear(System::TObject* Sender);
	void __fastcall PopupMenuClickMarkARange(System::TObject* Sender);
	void __fastcall PopupMenuClickMarkARow(System::TObject* Sender);
	void __fastcall PopupMenuClickMarkAAll(System::TObject* Sender);
	void __fastcall PopupMenuClickMarkAColumn(System::TObject* Sender);
	void __fastcall PopupMenuClickMarkBRange(System::TObject* Sender);
	void __fastcall PopupMenuClickMarkBRow(System::TObject* Sender);
	void __fastcall PopupMenuClickMarkBAll(System::TObject* Sender);
	void __fastcall PopupMenuClickMarkBColumn(System::TObject* Sender);
	void __fastcall PopupMenuClickUnMarkARange(System::TObject* Sender);
	void __fastcall PopupMenuClickUnMarkARow(System::TObject* Sender);
	void __fastcall PopupMenuClickUnMarkAAll(System::TObject* Sender);
	void __fastcall PopupMenuClickUnMarkAColumn(System::TObject* Sender);
	void __fastcall PopupMenuClickUnMarkBRange(System::TObject* Sender);
	void __fastcall PopupMenuClickUnMarkBRow(System::TObject* Sender);
	void __fastcall PopupMenuClickUnMarkBAll(System::TObject* Sender);
	void __fastcall PopupMenuClickUnMarkBColumn(System::TObject* Sender);
	void __fastcall PopupMenuClickUnMarkAll(System::TObject* Sender);
	void __fastcall PopupMenuClickCopy(System::TObject* Sender);
	void __fastcall PopupMenuClickPaste(System::TObject* Sender);
	void __fastcall PopupMenuClickEdit(System::TObject* Sender);
	void __fastcall PopupMenuClickExtClip(System::TObject* Sender);
	void __fastcall PopupMenuClickChangeID(System::TObject* Sender);
	void __fastcall PopupMenuClickPrecision(System::TObject* Sender);
	__property Shortint Precision[int ColNr] = {read=GetDecPlaces, write=SetDecPlaces};
	__property Datatable::TDTNameStr RowName[int ix] = {read=GetRowName, write=SetRowName};
	__property RowHeights ;
	__property Selection ;
	void __fastcall SortCols(int SortRowIx, bool Ascending, int LowCol, int LowRow, int HighCol, int HighRow, bool IncludeHeaders);
	void __fastcall SortRows(int SortColIx, bool Ascending, int LowCol, int LowRow, int HighCol, int HighRow, bool IncludeHeaders);
	void __fastcall MarkAllElemsA(void);
	void __fastcall MarkAllElemsB(void);
	void __fastcall UnMarkAllElems(void);
	int __fastcall FindColIndex( Datatable::TDTNameStr &ColID);
	int __fastcall FindRowIndex( Datatable::TDTNameStr &RowID);
	__property bool SuppressPaint = {read=FSuppressPaint, write=SetSuppressPaint, nodefault};
	__property int PopupDMask = {read=FPopupDMask, write=SetPopupDMask, nodefault};
	__property int PopupHMask = {read=FPopupHMask, write=SetPopupHMask, nodefault};
	
__published:
	__property Align  = {default=0};
	__property bool AutoAdvance = {read=FAutoAdvance, write=FAutoAdvance, nodefault};
	__property bool AttribRowVisible = {read=GetRowAttVis, write=SetRowAttVis, nodefault};
	__property bool AttribColVisible = {read=GetColAttVis, write=SetColAttVis, nodefault};
	__property AnsiString Comment = {read=GetComment, write=SetComment};
	__property Graphics::TColor ColorBackground = {read=FColorBkgnd, write=SetColorBackground, nodefault};
	__property Graphics::TColor ColorFixed = {read=FColorFixed, write=SetColorFixed, nodefault};
	__property Graphics::TColor ColorNormal = {read=FColorNormal, write=SetColorNormal, nodefault};
	__property Graphics::TColor ColorSelected = {read=FColorSelected, write=SetColorSelected, nodefault};
	__property Graphics::TColor ColorMarkedA = {read=FColorMarked1, write=SetColorMarkedA, nodefault};
	__property Graphics::TColor ColorMarkedB = {read=FColorMarked2, write=SetColorMarkedB, nodefault};
	__property Graphics::TColor ColorMarkedBoth = {read=FColorMarkedBoth, write=SetColorMarkedBoth, nodefault};
	__property int DefaultColWidth = {read=GetDefColWidth, write=SetDefColWidth, nodefault};
	__property DefaultRowHeight  = {default=24};
	__property Font ;
	__property ParentFont  = {default=1};
	__property PopupMenu ;
	__property int NrOfColumns = {read=GetNrCols, write=SetNrCols, nodefault};
	__property int NrOfRows = {read=GetNrRows, write=SetNrRows, nodefault};
	__property int NumWidth = {read=FNumWidth, write=SetNumWidth, nodefault};
	__property Options  = {stored=true, default=31};
	__property Visible  = {default=1};
	__property Grids::TGetEditEvent OnGetEditText = {read=FOnGetEditText, write=FOnGetEditText};
	__property Grids::TSetEditEvent OnSetEditText = {read=FOnSetEditText, write=FOnSetEditText};
	__property OnMouseDown ;
	__property OnClick ;
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Classes::TNotifyEvent OnChangeSetup = {read=FOnChangeSetup, write=FOnChangeSetup};
	__property OnDblClick ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TNTabEd(HWND ParentWindow) : Grids::TCustomGrid(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define SDLVersionInfo "ntabed_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
static const Shortint csNAN = 0x1;
static const Shortint csUndefined = 0x2;
static const Shortint csMarkedA = 0x40;
static const Byte csMarkedB = 0x80;
static const Shortint pdMarkA = 0x1;
static const Shortint pdMarkB = 0x2;
static const Shortint pdUnMarkA = 0x4;
static const Shortint pdUnMarkB = 0x8;
static const Shortint pdUnMarkAll = 0x10;
static const Shortint pdClear = 0x20;
static const Shortint pdCopy = 0x40;
static const Byte pdPaste = 0x80;
static const Word pdEdit = 0x100;
static const Word pdExtClip = 0x200;
static const int pdAllCmds = 0x7fffffff;
static const Shortint phEditIdentifier = 0x1;
static const Shortint phChangePrecision = 0x2;
static const int phAllCmds = 0x7fffffff;
static const Shortint pmMarkRange = 0x1;
static const Shortint pmMarkColumn = 0x2;
static const Shortint pmMarkRow = 0x4;
static const Shortint pmMarkAll = 0x8;
static const int pmAllCmds = 0x7fffffff;
static const Shortint puMarkRange = 0x1;
static const Shortint puMarkColumn = 0x2;
static const Shortint puMarkRow = 0x4;
static const Shortint puMarkAll = 0x8;
static const int puAllCmds = 0x7fffffff;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Ntabed */
using namespace Ntabed;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ntabed
