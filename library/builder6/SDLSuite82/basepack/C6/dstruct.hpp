// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'dstruct.pas' rev: 6.00

#ifndef dstructHPP
#define dstructHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sdlbase.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dstruct
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESDLDStructError;
class PASCALIMPLEMENTATION ESDLDStructError : public Sdlbase::ESDLError 
{
	typedef Sdlbase::ESDLError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLDStructError(const AnsiString Msg) : Sdlbase::ESDLError(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLDStructError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sdlbase::ESDLError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLDStructError(int Ident)/* overload */ : Sdlbase::ESDLError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLDStructError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sdlbase::ESDLError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLDStructError(const AnsiString Msg, int AHelpContext) : Sdlbase::ESDLError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLDStructError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sdlbase::ESDLError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLDStructError(int Ident, int AHelpContext)/* overload */ : Sdlbase::ESDLError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLDStructError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sdlbase::ESDLError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLDStructError(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TLogicOp { loAND, loOR, loXOR, loANDNot, loORNot, loXORNot };
#pragma option pop

typedef Byte TCombination[256];

#pragma option push -b-
enum TCRC16Mode { crcZModem, crcCCITT };
#pragma option pop

typedef DynamicArray<Byte >  dstruct__3;

class DELPHICLASS TBitFld;
class PASCALIMPLEMENTATION TBitFld : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
public:
	bool operator[](int ix) { return Bit[ix]; }
	
private:
	int FSize;
	DynamicArray<Byte >  FBitArray;
	void __fastcall SetSize(int s);
	void __fastcall SetBit(int ix, bool value);
	bool __fastcall GetBit(int ix);
	
public:
	__fastcall virtual TBitFld(Classes::TComponent* AOwner);
	__fastcall virtual ~TBitFld(void);
	void __fastcall Clear(void);
	int __fastcall CountTrueBits(void);
	int __fastcall FirstTrueBit(void);
	void __fastcall ToggleBit(int ix);
	void __fastcall CombineWith(TBitFld* SecondBArray, TLogicOp Operation);
	void __fastcall Invert(void);
	void __fastcall RandomFill(double Percent);
	__property bool Bit[int ix] = {read=GetBit, write=SetBit/*, default*/};
	
__published:
	__property int Size = {read=FSize, write=SetSize, nodefault};
};


typedef DynamicArray<Byte >  dstruct__5;

typedef DynamicArray<DynamicArray<Byte > >  dstruct__6;

class DELPHICLASS TByteMatrix;
class PASCALIMPLEMENTATION TByteMatrix : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	int FNrCols;
	int FNrRows;
	DynamicArray<DynamicArray<Byte > >  FByteMat;
	Classes::TNotifyEvent FOnChange;
	bool __fastcall GetBit(int ix, int iy, int ixBit);
	Byte __fastcall GetByte(int ix, int iy);
	void __fastcall SetNrRows(int nr);
	void __fastcall SetNrCols(int nc);
	void __fastcall SetBit(int ix, int iy, int ixBit, bool value);
	void __fastcall SetByte(int ix, int iy, Byte value);
	
public:
	__fastcall virtual TByteMatrix(Classes::TComponent* AOwner);
	__fastcall virtual ~TByteMatrix(void);
	void __fastcall Changed(void);
	void __fastcall Fill(Byte value);
	bool __fastcall Resize(int NrColumns, int NrRows);
	void __fastcall ToggleBit(int col, int row, int ixBit);
	void __fastcall CombineWith(TByteMatrix* SecondByteMatrix, TLogicOp Operation);
	__property bool Bit[int col][int row][int BitIx] = {read=GetBit, write=SetBit};
	__property Byte Byte[int col][int row] = {read=GetByte, write=SetByte/*, default*/};
	
__published:
	__property int NrOfRows = {read=FNrRows, write=SetNrRows, nodefault};
	__property int NrOfColumns = {read=FNrCols, write=SetNrCols, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
};


typedef DynamicArray<Byte >  dstruct__8;

class DELPHICLASS TFifo;
class PASCALIMPLEMENTATION TFifo : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	int FInPoi;
	int FOutPoi;
	int FLength;
	DynamicArray<Byte >  FData;
	void __fastcall SetSize(int value);
	
public:
	__fastcall virtual TFifo(Classes::TComponent* AOwner);
	__fastcall virtual ~TFifo(void);
	void __fastcall Clear(void);
	bool __fastcall PutByte(Byte InByte);
	bool __fastcall LoadBack(Byte InByte);
	bool __fastcall ForceByte(Byte InByte);
	bool __fastcall GetByte(Byte &OutByte);
	bool __fastcall SenseByte(int ix, Byte &OutByte);
	int __fastcall CountBytes(void);
	
__published:
	__property int Size = {read=FLength, write=SetSize, nodefault};
};


#pragma option push -b-
enum TDecodeSt { rlData, rlLeadin, rlCnt };
#pragma option pop

typedef DynamicArray<Byte >  dstruct__01;

class DELPHICLASS TRLEncoder;
class PASCALIMPLEMENTATION TRLEncoder : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	int FBufLeng;
	DynamicArray<Byte >  FBuffer;
	int FBufPoi;
	Byte FLeadInByte;
	TDecodeSt FDecodeSt;
	Byte FCount;
	Byte FLastB;
	void __fastcall SetBufLeng(int leng);
	
public:
	__fastcall virtual TRLEncoder(Classes::TComponent* AOwner);
	__fastcall virtual ~TRLEncoder(void);
	void __fastcall Reset(void);
	bool __fastcall Decode(Byte InByte);
	bool __fastcall Encode(Byte * InBuf, const int InBuf_Size, int NumBytes);
	void __fastcall GetResult(Byte * OutBuf, const int OutBuf_Size);
	int __fastcall Finish(Byte * OutBuf, const int OutBuf_Size);
	
__published:
	__property int BufLeng = {read=FBufLeng, write=SetBufLeng, nodefault};
};


typedef DynamicArray<Variant >  dstruct__21;

typedef DynamicArray<AnsiString >  dstruct__31;

class DELPHICLASS TAssocArray;
class PASCALIMPLEMENTATION TAssocArray : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	int FNEntries;
	DynamicArray<Variant >  FDataArray;
	DynamicArray<AnsiString >  FKeyArray;
	int FGranularity;
	bool FIgnoreCase;
	AnsiString FDataID;
	AnsiString __fastcall GetKeys(int ix);
	Variant __fastcall GetValues(int ix);
	void __fastcall SetKeys(int ix, AnsiString v);
	void __fastcall SetValues(int ix, const Variant &v);
	
public:
	__fastcall virtual TAssocArray(Classes::TComponent* AOwner);
	__fastcall virtual ~TAssocArray(void);
	void __fastcall Add(AnsiString Key, const Variant &Value);
	void __fastcall Clear(void);
	__property AnsiString Keys[int ix] = {read=GetKeys, write=SetKeys};
	__property int NumEntries = {read=FNEntries, nodefault};
	HIDESBASE bool __fastcall Remove(AnsiString Key);
	Variant __fastcall Resolve(AnsiString Key);
	__property Variant Values[int ix] = {read=GetValues, write=SetValues};
	int __fastcall AddXMLAttributes(AnsiString Attributes);
	bool __fastcall ReadFromXMLStream(const Classes::TStream* InStream, AnsiString DataID);
	void __fastcall WriteToXMLStream(const Classes::TStream* OutStream, bool CreateHeader, AnsiString DataID);
	
__published:
	__property AnsiString DataID = {read=FDataID, write=FDataID};
	__property bool IgnoreCase = {read=FIgnoreCase, write=FIgnoreCase, nodefault};
	__property int Granularity = {read=FGranularity, write=FGranularity, nodefault};
};


typedef Byte TStringPool[32768];

typedef DynamicArray<int >  dstruct__51;

typedef DynamicArray<int >  dstruct__61;

typedef DynamicArray<DynamicArray<int > >  dstruct__71;

typedef DynamicArray<Byte >  dstruct__81;

typedef DynamicArray<int >  dstruct__91;

typedef DynamicArray<Byte >  dstruct__02;

typedef DynamicArray<Byte >  dstruct__12;

class DELPHICLASS TStringArray;
class PASCALIMPLEMENTATION TStringArray : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	int FNCol;
	int FNRow;
	int FAllocRowsBy;
	int FRAllocated;
	int FNumPoolAddr;
	DynamicArray<int >  FFirstFree;
	DynamicArray<DynamicArray<int > >  FPoiArray;
	DynamicArray<Byte >  FStgPool;
	DynamicArray<int >  FSortIx;
	DynamicArray<Byte >  FRowAttrib;
	DynamicArray<Byte >  FColAttrib;
	Classes::TNotifyEvent FOnChange;
	Sdlbase::TOnPercentDoneEvent FOnPercentDone;
	double __fastcall GetAsNumber(int c, int r);
	int __fastcall GetSortOrder(int ix);
	System::ShortString __fastcall GetString(int c, int r);
	void __fastcall SetString(int c, int r,  System::ShortString &s);
	Byte __fastcall GetRowAttrib(int r);
	void __fastcall SetRowAttrib(int r, Byte b);
	Byte __fastcall GetColAttrib(int c);
	void __fastcall SetColAttrib(int c, Byte b);
	void __fastcall SetNrCols(int NrCols);
	void __fastcall SetNrRows(int NrRows);
	void __fastcall SetSortOrder(int ix, int position);
	void __fastcall SetAllocRowsBy(int NrAllocRows);
	bool __fastcall FindCellIntern(AnsiString FindStr, bool MatchCase, int ColLow, int ColHigh, int RowLow, int RowHigh, int &Col, int &row, bool Exact);
	
public:
	__fastcall virtual TStringArray(Classes::TComponent* AOwner);
	__fastcall virtual ~TStringArray(void);
	int __fastcall AddRow(void);
	__property double AsNumber[int ACol][int ARow] = {read=GetAsNumber};
	void __fastcall Changed(void);
	void __fastcall Clear(void);
	__property Byte ColAttrib[int c] = {read=GetColAttrib, write=SetColAttrib};
	bool __fastcall ColumnEmpty(int ACol);
	void __fastcall CommitSorting(void);
	__property System::ShortString Elem[int c][int r] = {read=GetString, write=SetString/*, default*/};
	void __fastcall Fill( System::ShortString &s);
	bool __fastcall FindCell(AnsiString FindStr, bool MatchCase, int ColLow, int ColHigh, int RowLow, int RowHigh, int &Col, int &row);
	bool __fastcall FindCellExact(AnsiString FindStr, bool MatchCase, int ColLow, int ColHigh, int RowLow, int RowHigh, int &Col, int &row);
	bool __fastcall FindCellInSortedColumn(AnsiString FindStr, bool MatchCase, int ColIx, int RowLow, int RowHigh, bool ColIsAscending, int &row);
	void __fastcall GarbageCollection(void);
	void __fastcall InsertRow(int r);
	bool __fastcall LoadFromXMLFile(AnsiString FName, AnsiString DataID);
	__property int NumBuffers = {read=FNumPoolAddr, nodefault};
	bool __fastcall ReadFromOpenXMLFile(TextFile &InFile, AnsiString DataID);
	void __fastcall RemoveRow(int r);
	bool __fastcall Resize(int Nc, int Nr);
	__property Byte RowAttrib[int r] = {read=GetRowAttrib, write=SetRowAttrib};
	bool __fastcall RowEmpty(int ARow);
	void __fastcall SaveAsXMLFile(AnsiString FName, AnsiString DataID);
	void __fastcall WriteToOpenXMLFile(TextFile &OutFile, bool CreateHeader, AnsiString DataID);
	void __fastcall Sort(int Col, bool Ascending);
	__property int SortOrder[int ix] = {read=GetSortOrder, write=SetSortOrder};
	void __fastcall UnSort(void);
	
__published:
	__property int AllocRowsBy = {read=FAllocRowsBy, write=SetAllocRowsBy, nodefault};
	__property int NrOfColumns = {read=FNCol, write=SetNrCols, nodefault};
	__property int NrOfRows = {read=FNRow, write=SetNrRows, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Sdlbase::TOnPercentDoneEvent OnPercentDone = {read=FOnPercentDone, write=FOnPercentDone};
};


//-- var, const, procedure ---------------------------------------------------
static const Word SABuffSize = 0x8000;
#define SDLVersionInfo "dstruct_r820_full"
static const bool IsLightEd = false;
static const Word Release = 0x334;
extern PACKAGE bool __fastcall NextCombination(Byte * CurrentCombi, int MaxVal);
extern PACKAGE bool __fastcall NextPermutation(Byte * CurrentPermut);
extern PACKAGE Word __fastcall CalcNextCRC16(Byte inbyte, Word crc);
extern PACKAGE Word __fastcall CRC16ofBuffer(Sdlbase::TBytes Buffer, int NumData, TCRC16Mode CRC16Mode);
extern PACKAGE int __fastcall CalcNextCRC32(Byte inbyte, int crc);
extern PACKAGE int __fastcall CRC32ofBuffer(Sdlbase::TBytes Buffer, int NumData);
extern PACKAGE int __fastcall CalcCRC32ofFile(AnsiString FName);
extern PACKAGE void __fastcall EncodeASCII85(Classes::TStream* InStream, Classes::TStream* OutStream);
extern PACKAGE int __fastcall DecodeASCII85(Classes::TStream* InStream, Classes::TStream* OutStream);
extern PACKAGE int __fastcall IndexOfNearestArrayValue(double Value, const double * ArrOfValues, const int ArrOfValues_Size)/* overload */;
extern PACKAGE int __fastcall IndexOfNearestArrayValue(int Value, const int * ArrOfValues, const int ArrOfValues_Size)/* overload */;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Dstruct */
using namespace Dstruct;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// dstruct
