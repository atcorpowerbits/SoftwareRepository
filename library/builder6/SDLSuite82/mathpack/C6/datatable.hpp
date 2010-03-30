// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'datatable.pas' rev: 6.00

#ifndef datatableHPP
#define datatableHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <matrix.hpp>	// Pascal unit
#include <stringl.hpp>	// Pascal unit
#include <sdlbase.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Datatable
{
//-- type declarations -------------------------------------------------------
typedef SmallString<50>  TDTNameStr;

class DELPHICLASS ESDLDataTableError;
class PASCALIMPLEMENTATION ESDLDataTableError : public Sdlbase::ESDLError 
{
	typedef Sdlbase::ESDLError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLDataTableError(const AnsiString Msg) : Sdlbase::ESDLError(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLDataTableError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sdlbase::ESDLError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLDataTableError(int Ident)/* overload */ : Sdlbase::ESDLError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLDataTableError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sdlbase::ESDLError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLDataTableError(const AnsiString Msg, int AHelpContext) : Sdlbase::ESDLError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLDataTableError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sdlbase::ESDLError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLDataTableError(int Ident, int AHelpContext)/* overload */ : Sdlbase::ESDLError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLDataTableError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sdlbase::ESDLError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLDataTableError(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TDataTableResizeEvent)(System::TObject* Sender, int OldColumns, int OldRows, int NewColumns, int NewRows);

typedef DynamicArray<Byte >  datatable__3;

typedef DynamicArray<Byte >  datatable__4;

typedef DynamicArray<Byte >  datatable__5;

typedef DynamicArray<DynamicArray<Byte > >  datatable__6;

typedef DynamicArray<TDTNameStr >  datatable__7;

typedef DynamicArray<TDTNameStr >  datatable__8;

class DELPHICLASS TDataTable;
class PASCALIMPLEMENTATION TDataTable : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	Classes::TNotifyEvent FOnChange;
	TDataTableResizeEvent FOnResize;
	AnsiString FComment;
	DynamicArray<Byte >  FRowAtt;
	DynamicArray<Byte >  FColAtt;
	DynamicArray<DynamicArray<Byte > >  FCState;
	DynamicArray<TDTNameStr >  FColName;
	DynamicArray<TDTNameStr >  FRowName;
	int FNrOfCols;
	int FNrOfRows;
	Stringl::TQuotedStrState FVNState;
	AnsiString FVNName;
	bool FSortIncludeHd;
	Sdlbase::TSortExchgEvent FOnSortExchange;
	bool FExtMatAssigned;
	void __fastcall ExchangeDuringSort(System::TObject* Sender, Byte ExchgWhat, int index1, int index2, int first, int last);
	Byte __fastcall GetRowAttrib(int RowNr);
	Byte __fastcall GetCellState(int ACol, int ARow);
	Byte __fastcall GetColAttrib(int ColNr);
	TDTNameStr __fastcall GetColName(int ColNr);
	double __fastcall GetElem(int ACol, int ARow);
	TDTNameStr __fastcall GetRowName(int RowNr);
	void __fastcall FDataHasChanged(System::TObject* Sender);
	void __fastcall SetRowAttrib(int RowNr, Byte Attrib);
	void __fastcall SetCellState(int ACol, int ARow, const Byte Value);
	void __fastcall SetColAttrib(int ColNr, Byte Attrib);
	void __fastcall SetColName(int ColNr,  TDTNameStr &HLine);
	void __fastcall SetElem(int ACol, int ARow, const double Value);
	void __fastcall SetFComment(AnsiString cmt);
	void __fastcall SetNrCols(int NrCols);
	void __fastcall SetNrRows(int NrRows);
	void __fastcall SetRowName(int RowNr,  TDTNameStr &HLine);
	
public:
	Matrix::TMatrix* NumericData;
	__fastcall virtual TDataTable(Classes::TComponent* AOwner);
	__fastcall virtual ~TDataTable(void);
	void __fastcall AssignAnotherDataMatrix(Matrix::TMatrix* NewDMat);
	void __fastcall Changed(void);
	void __fastcall Clear(void);
	void __fastcall ExportAsASC(AnsiString FName, int Precision)/* overload */;
	void __fastcall ExportAsASC(Classes::TStream* OutStream, int Precision)/* overload */;
	int __fastcall ImportASC(AnsiString FName)/* overload */;
	int __fastcall ImportASC(Classes::TStream* InStream)/* overload */;
	__property double Elem[int ACol][int ARow] = {read=GetElem, write=SetElem/*, default*/};
	__property Byte CellState[int ACol][int ARow] = {read=GetCellState, write=SetCellState};
	void __fastcall Resize(int NrCols, int NrRows);
	__property Byte RowAttrib[int ix] = {read=GetRowAttrib, write=SetRowAttrib};
	__property Byte ColAttrib[int ix] = {read=GetColAttrib, write=SetColAttrib};
	bool __fastcall IfColHasCellState(int col, Byte CellState);
	bool __fastcall IfRowHasCellState(int row, Byte CellState);
	__property TDTNameStr ColName[int ix] = {read=GetColName, write=SetColName};
	void __fastcall CopyContentsFrom(TDataTable* ExtTab);
	__property TDTNameStr RowName[int ix] = {read=GetRowName, write=SetRowName};
	void __fastcall SortCols(int SortRowIx, bool Ascending, int LowCol, int LowRow, int HighCol, int HighRow, bool IncludeHeaders);
	void __fastcall SortRows(int SortColIx, bool Ascending, int LowCol, int LowRow, int HighCol, int HighRow, bool IncludeHeaders);
	void __fastcall SetAllCellStates(Byte CellState);
	int __fastcall FindColIndex( TDTNameStr &ColID);
	int __fastcall FindRowIndex( TDTNameStr &RowID);
	int __fastcall ReadFromASC(AnsiString FName, int PosX, int PosY, bool ReplaceIDs)/* overload */;
	int __fastcall ReadFromASC(Classes::TStream* InStream, int PosX, int PosY, bool ReplaceIDs)/* overload */;
	
__published:
	__property AnsiString Comment = {read=FComment, write=SetFComment};
	__property int NrOfColumns = {read=FNrOfCols, write=SetNrCols, nodefault};
	__property int NrOfRows = {read=FNrOfRows, write=SetNrRows, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property TDataTableResizeEvent OnResize = {read=FOnResize, write=FOnResize};
	__property Sdlbase::TSortExchgEvent OnSortExchange = {read=FOnSortExchange, write=FOnSortExchange};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint DT_NameWidth = 0x32;
static const int DT_MaxColOrRows = 0x2566246;
#define SDLVersionInfo "datatable_r820_full"
static const bool IsLightEd = false;
static const Word Release = 0x334;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Datatable */
using namespace Datatable;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// datatable
