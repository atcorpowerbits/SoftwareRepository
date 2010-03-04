// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'stringl.pas' rev: 6.00

#ifndef stringlHPP
#define stringlHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Stringl
{
//-- type declarations -------------------------------------------------------
typedef char TCharArr256[256];

typedef ShortString ShortStr;
;

#pragma option push -b-
enum TGrepTokenAct { taNormal, taAnyByte, taEol, taBol, taSet, taMult0, taMult1, taOpti };
#pragma option pop

#pragma pack(push, 4)
struct TGrepToken
{
	TGrepTokenAct Action;
	int NumChars;
	char Params[256];
	int ValidFrom;
} ;
#pragma pack(pop)

typedef TGrepToken TRegExp[64];

class DELPHICLASS TGrep;
class PASCALIMPLEMENTATION TGrep : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	int FLengRegExp;
	bool FStopOnError;
	TGrepToken FregExp[64];
	AnsiString FRegExpStr;
	bool FIgnoreCase;
	int FError;
	int FMatchEndPos;
	int FMatchStartPos;
	int FSrcStartPos;
	int __fastcall CompileRegExp(AnsiString regexp);
	void __fastcall SetRegExp(AnsiString regexp);
	void __fastcall SetIgnoreCase(bool ic);
	TGrepToken __fastcall GetRegExpToken(int regix);
	
public:
	__fastcall TGrep(void);
	__fastcall virtual ~TGrep(void);
	void __fastcall PrintRegExp(AnsiString FName);
	__property AnsiString RegExp = {read=FRegExpStr, write=SetRegExp};
	__property bool IgnoreCase = {read=FIgnoreCase, write=SetIgnoreCase, nodefault};
	bool __fastcall MatchString(AnsiString Instring, int &MatchPos);
	__property TGrepToken RegExpToken[int regix] = {read=GetRegExpToken};
	__property int MatchEndPos = {read=FMatchEndPos, nodefault};
	__property int MatchStartPos = {read=FMatchStartPos, nodefault};
	__property int NrOfRegExpTokens = {read=FLengRegExp, nodefault};
	__property int SearchStartPos = {read=FSrcStartPos, write=FSrcStartPos, nodefault};
	__property bool StopOnError = {read=FStopOnError, write=FStopOnError, nodefault};
	__property int LastError = {read=FError, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint MaxGrepTokens = 0x40;
extern PACKAGE AnsiString __fastcall strff(Extended r, int FieldWidth, int DecP);
extern PACKAGE int __fastcall StringIx(AnsiString InString, const AnsiString * SArray, const int SArray_Size);
extern PACKAGE AnsiString __fastcall BoolToStr(bool ABool, int Format);
extern PACKAGE AnsiString __fastcall ReplaceCharInString(AnsiString Instring, char OldChar, char NewChar);
extern PACKAGE AnsiString __fastcall ReplaceStringInString(AnsiString Instring, AnsiString OldStr, AnsiString NewStr, bool IgnoreCase);
extern PACKAGE AnsiString __fastcall StripLTBlanks(AnsiString Instring);
extern PACKAGE AnsiString __fastcall FormatData(double data, int NumWidth, int NDecP);
extern PACKAGE int __fastcall NumberedPos(AnsiString SubStr, AnsiString MainStr, int StartIx, int Count, bool IgnoreCase);
extern PACKAGE bool __fastcall IsDigit(char c);
extern PACKAGE bool __fastcall IsLetter(char c);
extern PACKAGE bool __fastcall IsDigitLetter(char c);
extern PACKAGE bool __fastcall IsHexChar(char c);
extern PACKAGE AnsiString __fastcall StripTrailingBlanks(AnsiString Instring);
extern PACKAGE AnsiString __fastcall StripLeadingBlanks(AnsiString Instring);
extern PACKAGE int __fastcall CountCharInString(char cc, AnsiString Instring, bool CaseSensitive);
extern PACKAGE AnsiString __fastcall RemoveControlChars(AnsiString Instring);
extern PACKAGE int __fastcall PosLast(AnsiString SubStr, AnsiString Instring);
extern PACKAGE AnsiString __fastcall EnsureTrailingBkSlash(AnsiString instring);
extern PACKAGE AnsiString __fastcall EnsureTrailingChar(char cc, AnsiString instring);
extern PACKAGE AnsiString __fastcall MultiChar(char cc, int RepCnt);
extern PACKAGE AnsiString __fastcall CenterString(AnsiString Instring, Byte Width);
extern PACKAGE AnsiString __fastcall RightString(AnsiString Instring, Byte Width);
extern PACKAGE AnsiString __fastcall LeftString(AnsiString Instring, Byte Width);
extern PACKAGE AnsiString __fastcall RemoveCharInString(AnsiString Instring, char CharToRemove);
extern PACKAGE AnsiString __fastcall AbbrevString(AnsiString Instring, int width);
extern PACKAGE AnsiString __fastcall TimeString(double Time, Byte Fmt);
extern PACKAGE bool __fastcall TestAllChar(AnsiString Instr, char cc);
extern PACKAGE AnsiString __fastcall ExpandDiphthongs(AnsiString line);
extern PACKAGE System::ShortString __fastcall WinAnsiString( System::ShortString &Instring);
extern PACKAGE System::ShortString __fastcall OEMString( System::ShortString &Instring);
extern PACKAGE AnsiString __fastcall UUEncodeStr(AnsiString Instring);
extern PACKAGE AnsiString __fastcall UUDecodeStr(AnsiString Instring);
extern PACKAGE AnsiString __fastcall Scramble(AnsiString Instring);
extern PACKAGE AnsiString __fastcall DeScramble(AnsiString Instring);
extern PACKAGE void __fastcall InitScramble(int Key);
extern PACKAGE AnsiString __fastcall ReadLnString(AnsiString Instring, int &StartPos, bool &eos, int EOLMode);
extern PACKAGE AnsiString __fastcall ReduceStringToAZ09(AnsiString InString);

}	/* namespace Stringl */
using namespace Stringl;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// stringl
