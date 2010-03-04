// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'replist.pas' rev: 6.00

#ifndef replistHPP
#define replistHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <dstruct.hpp>	// Pascal unit
#include <sdlbase.hpp>	// Pascal unit
#include <Grids.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Replist
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESDLRepListError;
class PASCALIMPLEMENTATION ESDLRepListError : public Sdlbase::ESDLError 
{
	typedef Sdlbase::ESDLError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLRepListError(const AnsiString Msg) : Sdlbase::ESDLError(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLRepListError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sdlbase::ESDLError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLRepListError(int Ident)/* overload */ : Sdlbase::ESDLError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLRepListError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sdlbase::ESDLError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLRepListError(const AnsiString Msg, int AHelpContext) : Sdlbase::ESDLError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLRepListError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sdlbase::ESDLError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLRepListError(int Ident, int AHelpContext)/* overload */ : Sdlbase::ESDLError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLRepListError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sdlbase::ESDLError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLRepListError(void) { }
	#pragma option pop
	
};


typedef SmallString<50>  TNameStrType;

typedef SmallString<80>  TColFmtString;

#pragma option push -b-
enum TRepListXmlTag { xmlNumCols, xmlNumRows, xmlColName, xmlCheckedColumn, xmlColumnFormat, xmlCell, xmlComment, xmlEndReplist, xmlInvalid };
#pragma option pop

typedef void __fastcall (__closure *TCheckStateChangeEvent)(System::TObject* Sender, bool State, int Col, int Row);

typedef void __fastcall (__closure *TRequestEditFormatEvent)(System::TObject* Sender, int Col, int Row, AnsiString &Format);

typedef void __fastcall (__closure *TRenderCellEvent)(System::TObject* Sender, int ACol, int ARow, Graphics::TColor &PenColor, Graphics::TColor &BrushColor, Graphics::TColor &FontColor, Graphics::TFontStyles &FontStyles, AnsiString &Text);

typedef DynamicArray<TNameStrType >  replist__3;

typedef DynamicArray<TColFmtString >  replist__4;

typedef DynamicArray<bool >  replist__5;

typedef DynamicArray<Byte >  replist__6;

typedef DynamicArray<bool >  replist__7;

typedef DynamicArray<bool >  replist__8;

class DELPHICLASS TReportListView;
class PASCALIMPLEMENTATION TReportListView : public Grids::TCustomDrawGrid 
{
	typedef Grids::TCustomDrawGrid inherited;
	
private:
	bool FAutoAdvance;
	AnsiString FComment;
	int FLastMousePosX;
	int FLastMousePosY;
	Classes::TNotifyEvent FOnChange;
	Classes::TNotifyEvent FOnChangeSetup;
	Classes::TNotifyEvent FOnSelectedChange;
	DynamicArray<TNameStrType >  FColName;
	DynamicArray<TColFmtString >  FColDefaultVal;
	DynamicArray<bool >  FColChecked;
	DynamicArray<Byte >  FColAlignment;
	DynamicArray<bool >  FColumnEditable;
	DynamicArray<bool >  FColumnIsPwd;
	int FNrOfCols;
	int FNrOfRows;
	int FSelectAnchor;
	int FRowSelectMode;
	bool FSortEnabled;
	int FSortColumn;
	bool FSortOrder;
	TCheckStateChangeEvent FOnChkStChange;
	TRequestEditFormatEvent FOnRequestEdFmt;
	Grids::TGetEditEvent FOnGetEditText;
	Grids::TSetEditEvent FOnSetEditText;
	Graphics::TColor FSelRowColor;
	Graphics::TColor FSelRowTextColor;
	Graphics::TColor FSelColColor;
	Graphics::TColor FSelColTextColor;
	Graphics::TColor FSelBothColor;
	Graphics::TColor FSelBothTextColor;
	Graphics::TColor FHiLgtColor;
	Graphics::TColor FHiLgtTextColor;
	bool FHiLgtBold;
	int FHiLgtRow;
	int FHiLgtColumn;
	int FFeedbkNumCells;
	int FFeedbkStep;
	Sdlbase::TOnPercentDoneEvent FOnPercentDone;
	TRenderCellEvent FOnBefRenderCell;
	bool FSuppressPaint;
	AnsiString FDataID;
	bool FSortToggle;
	Graphics::TColor FColorNormal;
	Graphics::TColor FRColorNormal;
	Graphics::TColor FRColorShaded;
	int FRowColPattern;
	int FInterRowIndi;
	Graphics::TColor FInterRowColor;
	int FInterRowWidth;
	Forms::TForm* FContainerForm;
	Buttons::TSpeedButton* FSBERCancel;
	double __fastcall GetAsNumber(int ACol, int ARow);
	TNameStrType __fastcall GetColName(int ColNr);
	bool __fastcall GetCheckedCol(int ColNr);
	HIDESBASE int __fastcall GetColWidths(int Index);
	int __fastcall GetDefColWidth(void);
	int __fastcall GetDefRowHeight(void);
	TColFmtString __fastcall GetColumnFormat(int ColNr);
	System::ShortString __fastcall GetElem(int ACol, int ARow);
	bool __fastcall GetElemChecked(int ACol, int ARow);
	bool __fastcall GetColumnEditable(int ColNr);
	bool __fastcall GetColumnIsPwd(int ColNr);
	bool __fastcall GetColSelect(int c);
	Classes::TAlignment __fastcall GetColAlignment(int ColNr);
	bool __fastcall GetRowSelect(int r);
	int __fastcall GetTopRow(void);
	int __fastcall GetLeftCol(void);
	AnsiString __fastcall GetCellDefaultValue(int ACol, int ARow);
	void __fastcall StringsHasChanged(System::TObject* Sender);
	void __fastcall StringsPercDone(System::TObject* Sender, int Percent);
	void __fastcall SetSuppressPaint(bool supp);
	void __fastcall SetColName(int ColNr,  TNameStrType &HLine);
	void __fastcall SetCheckedCol(int ColNr, bool Value);
	void __fastcall SetColAlignment(int ColNr, Classes::TAlignment Value);
	void __fastcall SetColorNormal(Graphics::TColor color);
	HIDESBASE void __fastcall SetColWidths(int Index, int Value);
	void __fastcall SetDefColWidth(int DefW);
	void __fastcall SetDefRowHeight(int DefH);
	void __fastcall SetColPattern(int colpat);
	void __fastcall SetElem(int ACol, int ARow, const System::ShortString &Value);
	void __fastcall SetElemChecked(int ACol, int ARow, const bool Value);
	void __fastcall SetNrCols(int NrCols);
	void __fastcall SetNrRows(int NrRows);
	void __fastcall SetRColorNormal(Graphics::TColor color);
	void __fastcall SetRColorShaded(Graphics::TColor color);
	void __fastcall SetColumnEditable(int ColNr, bool Value);
	void __fastcall SetColumnIsPwd(int ColNr, bool Value);
	void __fastcall SetColSelect(int c, bool value);
	void __fastcall SetInterRowIndi(int r);
	HIDESBASE void __fastcall SetLeftCol(int lc);
	HIDESBASE void __fastcall SetTopRow(int tr);
	void __fastcall SetRowSelect(int r, bool value);
	void __fastcall SetRowSelectMode(int mode);
	void __fastcall SetColorSelectedRow(Graphics::TColor color);
	void __fastcall SetColorSelectedRowText(Graphics::TColor color);
	void __fastcall SetColorSelectedCol(Graphics::TColor color);
	void __fastcall SetColorSelectedColText(Graphics::TColor color);
	void __fastcall SetColorSelectedBoth(Graphics::TColor color);
	void __fastcall SetColorSelectedBothText(Graphics::TColor color);
	void __fastcall SetColumnFormat(int ColNr,  TColFmtString &DefValue);
	void __fastcall SetInterRowColor(Graphics::TColor Color);
	void __fastcall SetInterRowWidth(int Width);
	void __fastcall SetColorHi(Graphics::TColor color);
	void __fastcall SetColorHiText(Graphics::TColor color);
	void __fastcall SetHighLightBold(bool Bold);
	void __fastcall SetHighLightRow(int ARow);
	void __fastcall SetHighLightColumn(int ACol);
	void __fastcall EdRowCancelClick(System::TObject* Sender);
	void __fastcall EdRowOKClick(System::TObject* Sender);
	void __fastcall EdRowKeyPress(System::TObject* Sender, char &Key);
	int __fastcall EditRowEntriesIntern(int Row, Forms::TForm* ContainerForm, int PosLeft, int PosTop, AnsiString FormCaption, AnsiString ButOKCaption, AnsiString ButCancelCaption);
	
protected:
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall Keypress(char &Key);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	DYNAMIC AnsiString __fastcall GetEditText(int ACol, int ARow);
	DYNAMIC void __fastcall SetEditText(int ACol, int ARow, const AnsiString Value);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	void __fastcall CheckStateHasChanged(bool State, int col, int row);
	DYNAMIC void __fastcall DblClick(void);
	virtual bool __fastcall SelectCell(int ACol, int ARow);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall DrawCell(int ACol, int ARow, const Types::TRect &ARect, Grids::TGridDrawState AState);
	
public:
	Dstruct::TStringArray* Strings;
	__fastcall virtual TReportListView(Classes::TComponent* AOwner);
	__fastcall virtual ~TReportListView(void);
	int __fastcall AddRow(void);
	__property double AsNumber[int ACol][int ARow] = {read=GetAsNumber};
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	void __fastcall AutoColWidth(int ColNr, bool IncludeHeader, int Addon);
	HIDESBASE void __fastcall Changed(void);
	void __fastcall ChangedSetup(void);
	void __fastcall ChangedSelection(void);
	int __fastcall ColumnIndex(AnsiString Head, bool PartialMatch);
	__property AnsiString Comment = {read=FComment, write=FComment};
	void __fastcall CopyToClipBoard(int LeftCol, int TopRow, int RightCol, int BottomRow, bool AddHeader, bool UseTabs);
	__property AnsiString DataID = {read=FDataID, write=FDataID};
	__property AnsiString DefaultValue[int ACol][int ARow] = {read=GetCellDefaultValue};
	void __fastcall DeselectAllRows(void);
	void __fastcall DeselectAllColumns(void);
	__property System::ShortString Elem[int ACol][int ARow] = {read=GetElem, write=SetElem/*, default*/};
	__property bool ElemChecked[int ACol][int ARow] = {read=GetElemChecked, write=SetElemChecked};
	void __fastcall Fill( System::ShortString &s);
	int __fastcall FirstSelectedColumn(void);
	int __fastcall FirstSelectedRow(void);
	void __fastcall Clear(void);
	__property int ColWidths[int Index] = {read=GetColWidths, write=SetColWidths};
	__property TColFmtString ColumnFormat[int ColNr] = {read=GetColumnFormat, write=SetColumnFormat};
	__property bool ColumnSelected[int r] = {read=GetColSelect, write=SetColSelect};
	int __fastcall CountCheckedElemsInCol(int Column);
	int __fastcall CountCheckedElemsInRow(int Row);
	int __fastcall EditRowEntries(int Row, int PosLeft, int PosTop, AnsiString FormCaption, AnsiString ButOKCaption, AnsiString ButCancelCaption)/* overload */;
	int __fastcall EditRowEntries(int Row, int PosLeft, int PosTop)/* overload */;
	int __fastcall EditRowEntries(int Row, Forms::TForm* ContainerForm, int PosLeft, int PosTop)/* overload */;
	void __fastcall ExpandColWidth(int ColIx, int RightMargin);
	__property TNameStrType Header[int ColNr] = {read=GetColName, write=SetColName};
	int __fastcall InsertRow(int r);
	__property bool IsCheckedColumn[int ColNr] = {read=GetCheckedCol, write=SetCheckedCol};
	__property Classes::TAlignment ColumnAlignment[int ColNr] = {read=GetColAlignment, write=SetColAlignment};
	__property bool ColumnEditable[int ColNr] = {read=GetColumnEditable, write=SetColumnEditable};
	__property bool ColumnIsPwd[int ColNr] = {read=GetColumnIsPwd, write=SetColumnIsPwd};
	__property int LastSortColumn = {read=FSortColumn, nodefault};
	__property bool LastSortOrder = {read=FSortOrder, nodefault};
	bool __fastcall LoadFromXMLFile(AnsiString FName, AnsiString DataID);
	int __fastcall LoadLinesFromFile(int Column, int FirstRow, AnsiString FName);
	int __fastcall NumSelectedRows(void);
	int __fastcall NumSelectedColumns(void);
	bool __fastcall ReadFromXMLString(AnsiString InString, AnsiString DataID);
	bool __fastcall ReadFromXMLStream(Classes::TStream* InStream, AnsiString DataID);
	bool __fastcall ReadFromOpenXMLFile(TextFile &InFile, AnsiString DataID);
	void __fastcall RemoveRow(int r);
	__property bool RowSelected[int r] = {read=GetRowSelect, write=SetRowSelect};
	__property int InterRowIndicatorPos = {read=FInterRowIndi, write=SetInterRowIndi, nodefault};
	void __fastcall SaveAsXMLFile(AnsiString FName, AnsiString DataID);
	void __fastcall SelectAllColumns(void);
	void __fastcall SelectAllRows(void);
	__property Selection ;
	__property InplaceEditor ;
	void __fastcall Sort(int Col, bool Ascending);
	void __fastcall UnSort(void);
	__property bool SuppressPaint = {read=FSuppressPaint, write=SetSuppressPaint, nodefault};
	void __fastcall WriteToOpenXMLFile(TextFile &OutFile, bool CreateHeader, AnsiString DataID);
	void __fastcall WriteToXMLStream(Classes::TStream* OutStream, bool CreateHeader, AnsiString DataID);
	
__published:
	__property int NrOfColumns = {read=FNrOfCols, write=SetNrCols, nodefault};
	__property int NrOfRows = {read=FNrOfRows, write=SetNrRows, nodefault};
	__property Align  = {default=0};
	__property Anchors  = {default=3};
	__property Constraints ;
	__property BiDiMode ;
	__property ParentBiDiMode  = {default=1};
	__property DragCursor  = {default=-12};
	__property OnEndDock ;
	__property DragKind  = {default=0};
	__property OnStartDock ;
	__property OnStartDrag ;
	__property DragMode  = {default=0};
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDrag ;
	__property OnContextPopup ;
	__property bool AutoAdvance = {read=FAutoAdvance, write=FAutoAdvance, nodefault};
	__property BorderStyle  = {default=1};
	__property Color  = {default=-2147483643};
	__property Graphics::TColor ColorHigh = {read=FHiLgtColor, write=SetColorHi, nodefault};
	__property Graphics::TColor ColorText = {read=FColorNormal, write=SetColorNormal, nodefault};
	__property Graphics::TColor ColorBkgdNormal = {read=FRColorNormal, write=SetRColorNormal, nodefault};
	__property Graphics::TColor ColorBkgdShaded = {read=FRColorShaded, write=SetRColorShaded, nodefault};
	__property Graphics::TColor ColorHighText = {read=FHiLgtTextColor, write=SetColorHiText, nodefault};
	__property Graphics::TColor ColorSelectedRow = {read=FSelRowColor, write=SetColorSelectedRow, nodefault};
	__property Graphics::TColor ColorSelectedRowText = {read=FSelRowTextColor, write=SetColorSelectedRowText, nodefault};
	__property Graphics::TColor ColorSelectedCol = {read=FSelColColor, write=SetColorSelectedCol, nodefault};
	__property Graphics::TColor ColorSelectedColText = {read=FSelColTextColor, write=SetColorSelectedColText, nodefault};
	__property Graphics::TColor ColorSelectedBoth = {read=FSelBothColor, write=SetColorSelectedBoth, nodefault};
	__property Graphics::TColor ColorSelectedBothText = {read=FSelBothTextColor, write=SetColorSelectedBothText, nodefault};
	__property Ctl3D ;
	__property ParentCtl3D  = {default=1};
	__property int DefaultColWidth = {read=GetDefColWidth, write=SetDefColWidth, nodefault};
	__property int DefaultRowHeight = {read=GetDefRowHeight, write=SetDefRowHeight, nodefault};
	__property DefaultDrawing  = {default=1};
	__property Enabled  = {default=1};
	__property FixedColor  = {default=-2147483633};
	__property Font ;
	__property bool HighLightBold = {read=FHiLgtBold, write=SetHighLightBold, nodefault};
	__property int HighLightRow = {read=FHiLgtRow, write=SetHighLightRow, nodefault};
	__property int HighLightColumn = {read=FHiLgtColumn, write=SetHighLightColumn, nodefault};
	__property Graphics::TColor InterRowIndicatorColor = {read=FInterRowColor, write=SetInterRowColor, nodefault};
	__property int InterRowIndicatorWidth = {read=FInterRowWidth, write=SetInterRowWidth, nodefault};
	__property int LeftCol = {read=GetLeftCol, write=SetLeftCol, nodefault};
	__property Options  = {default=31};
	__property ParentColor  = {default=0};
	__property ParentShowHint  = {default=1};
	__property ParentFont  = {default=1};
	__property PopupMenu ;
	__property int RowSelectMode = {read=FRowSelectMode, write=SetRowSelectMode, nodefault};
	__property int RowColPattern = {read=FRowColPattern, write=SetColPattern, nodefault};
	__property ShowHint ;
	__property TabOrder  = {default=-1};
	__property ScrollBars  = {default=3};
	__property bool SortEnabled = {read=FSortEnabled, write=FSortEnabled, nodefault};
	__property int TopRow = {read=GetTopRow, write=SetTopRow, nodefault};
	__property Visible  = {default=1};
	__property VisibleColCount ;
	__property VisibleRowCount ;
	__property Grids::TGetEditEvent OnGetEditText = {read=FOnGetEditText, write=FOnGetEditText};
	__property Grids::TSetEditEvent OnSetEditText = {read=FOnSetEditText, write=FOnSetEditText};
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property OnMouseMove ;
	__property OnMouseWheel ;
	__property OnMouseWheelDown ;
	__property OnMouseWheelUp ;
	__property OnClick ;
	__property TCheckStateChangeEvent OnCheckedChange = {read=FOnChkStChange, write=FOnChkStChange};
	__property TRequestEditFormatEvent OnRequestEditFormat = {read=FOnRequestEdFmt, write=FOnRequestEdFmt};
	__property Classes::TNotifyEvent OnSelectedChange = {read=FOnSelectedChange, write=FOnSelectedChange};
	__property TRenderCellEvent OnBeforeRenderCell = {read=FOnBefRenderCell, write=FOnBefRenderCell};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Classes::TNotifyEvent OnChangeSetup = {read=FOnChangeSetup, write=FOnChangeSetup};
	__property OnDblClick ;
	__property OnDrawCell ;
	__property OnEnter ;
	__property OnExit ;
	__property OnGetEditMask ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property Sdlbase::TOnPercentDoneEvent OnPercentDone = {read=FOnPercentDone, write=FOnPercentDone};
	__property OnRowMoved ;
	__property OnSelectCell ;
	__property OnTopLeftChanged ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TReportListView(HWND ParentWindow) : Grids::TCustomDrawGrid(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint NameWidth = 0x32;
static const Shortint ColFormatWidth = 0x50;
#define SDLVersionInfo "replist_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE bool __fastcall CheckIfValidReplist(AnsiString FName, AnsiString DataID)/* overload */;
extern PACKAGE bool __fastcall CheckIfValidReplist(Classes::TStream* InStream, AnsiString DataID)/* overload */;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Replist */
using namespace Replist;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// replist
