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
#pragma option push -b-
enum TLogicOp { loAND, loOR, loXOR, loANDNot, loORNot, loXORNot };
#pragma option pop

typedef Byte TCombination[256];

#pragma option push -b-
enum TCRC16Mode { crcZModem, crcCCITT };
#pragma option pop

class DELPHICLASS TBitFld;
class PASCALIMPLEMENTATION TBitFld : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
public:
	bool operator[](int ix) { return Bit[ix]; }
	
private:
	int FSize;
	void *FBitArray;
	void __fastcall SetSize(int s);
	void __fastcall SetBit(int ix, bool value);
	bool __fastcall GetBit(int ix);
	
public:
	__fastcall virtual TBitFld(Classes::TComponent* AOwner);
	__fastcall virtual ~TBitFld(void);
	void __fastcall Clear(void);
	int __fastcall CountTrueBits(void);
	void __fastcall ToggleBit(int ix);
	void __fastcall CombineWith(TBitFld* SecondBArray, TLogicOp Operation);
	void __fastcall Invert(void);
	void __fastcall RandomFill(double Percent);
	__property bool Bit[int ix] = {read=GetBit, write=SetBit/*, default*/};
	
__published:
	__property int Size = {read=FSize, write=SetSize, nodefault};
};


class DELPHICLASS TFifo;
class PASCALIMPLEMENTATION TFifo : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	int FInPoi;
	int FOutPoi;
	int FLength;
	void *FData;
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

class DELPHICLASS TRLEncoder;
class PASCALIMPLEMENTATION TRLEncoder : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	int FBufLeng;
	void *FBuffer;
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


class DELPHICLASS TStringArray;
class PASCALIMPLEMENTATION TStringArray : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	int FNCol;
	int FNRow;
	int FAllocRowsBy;
	int FRAllocated;
	int FNumPoolAddr;
	void *FFirstFree;
	void *FPoiArray;
	void *FStgPool;
	void *FPooladdr;
	void *FSortIx;
	void *FRowAttrib;
	void *FColAttrib;
	Classes::TNotifyEvent FOnChange;
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
	__fastcall TStringArray(int Nc, int Nr, int AllocRowsBy);
	__fastcall virtual ~TStringArray(void);
	int __fastcall AddRow(void);
	__property double AsNumber[int ACol][int ARow] = {read=GetAsNumber};
	void __fastcall Changed(void);
	void __fastcall Clear(void);
	__property Byte ColAttrib[int c] = {read=GetColAttrib, write=SetColAttrib};
	bool __fastcall ColumnEmpty(int ACol);
	__property System::ShortString Elem[int c][int r] = {read=GetString, write=SetString/*, default*/};
	void __fastcall Fill( System::ShortString &s);
	bool __fastcall FindCell(AnsiString FindStr, bool MatchCase, int ColLow, int ColHigh, int RowLow, int RowHigh, int &Col, int &row);
	bool __fastcall FindCellExact(AnsiString FindStr, bool MatchCase, int ColLow, int ColHigh, int RowLow, int RowHigh, int &Col, int &row);
	bool __fastcall FindCellInSortedColumn(AnsiString FindStr, bool MatchCase, int ColIx, int RowLow, int RowHigh, bool ColIsAscending, int &row);
	void __fastcall GarbageCollection(void);
	void __fastcall InsertRow(int r);
	bool __fastcall LoadFromXMLFile(AnsiString FName, AnsiString DataID);
	__property int NrOfColumns = {read=FNCol, write=SetNrCols, nodefault};
	__property int NrOfRows = {read=FNRow, write=SetNrRows, nodefault};
	__property int NumBuffers = {read=FNumPoolAddr, nodefault};
	bool __fastcall ReadFromOpenXMLFile(TextFile &InFile, AnsiString DataID);
	void __fastcall RemoveRow(int r);
	bool __fastcall Resize(int Nc, int Nr);
	__property Byte RowAttrib[int r] = {read=GetRowAttrib, write=SetRowAttrib};
	bool __fastcall RowEmpty(int ARow);
	void __fastcall SaveAsXMLFile(AnsiString FName, AnsiString DataID);
	void __fastcall WriteToOpenXMLFile(TextFile &OutFile, bool CreateHeader, AnsiString DataID);
	__property int AllocRowsBy = {read=FAllocRowsBy, write=SetAllocRowsBy, nodefault};
	void __fastcall Sort(int Col, bool Ascending);
	__property int SortOrder[int ix] = {read=GetSortOrder, write=SetSortOrder};
	void __fastcall UnSort(void);
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
};


//-- var, const, procedure ---------------------------------------------------
static const Word SABuffSize = 0x8000;
static const Shortint MAXPGONCONTAINER = 0x20;
extern PACKAGE bool __fastcall NextCombination(Byte * CurrentCombi, int MaxVal);
extern PACKAGE Word __fastcall CalcNextCRC16(Byte inbyte, Word crc);
extern PACKAGE Word __fastcall CRC16ofBuffer(void * BufPoi, int NumData, TCRC16Mode CRC16Mode);
extern PACKAGE int __fastcall CalcNextCRC32(Byte inbyte, int crc);
extern PACKAGE int __fastcall CRC32ofBuffer(void * BufPoi, int NumData);
extern PACKAGE int __fastcall CalcCRC32ofFile(AnsiString FName);
extern PACKAGE void __fastcall EncodeASCII85(Classes::TStream* InStream, Classes::TStream* OutStream);
extern PACKAGE int __fastcall DecodeASCII85(Classes::TStream* InStream, Classes::TStream* OutStream);
extern PACKAGE void __fastcall Register(void);

}	/* namespace Dstruct */
using namespace Dstruct;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// dstruct
