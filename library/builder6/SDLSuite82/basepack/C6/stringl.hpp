// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'stringl.pas' rev: 6.00

#ifndef stringlHPP
#define stringlHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sdlbase.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Stringl
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESDLStringlError;
class PASCALIMPLEMENTATION ESDLStringlError : public Sdlbase::ESDLError 
{
	typedef Sdlbase::ESDLError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLStringlError(const AnsiString Msg) : Sdlbase::ESDLError(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLStringlError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sdlbase::ESDLError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLStringlError(int Ident)/* overload */ : Sdlbase::ESDLError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLStringlError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sdlbase::ESDLError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLStringlError(const AnsiString Msg, int AHelpContext) : Sdlbase::ESDLError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLStringlError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sdlbase::ESDLError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLStringlError(int Ident, int AHelpContext)/* overload */ : Sdlbase::ESDLError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLStringlError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sdlbase::ESDLError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLStringlError(void) { }
	#pragma option pop
	
};


typedef char TCharArr256[256];

#pragma option push -b-
enum TQuotedStrState { vsStart, vs1stQuote, vsQuote, vsNormal, vsEnd };
#pragma option pop

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
class PASCALIMPLEMENTATION TGrep : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
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
	__fastcall virtual TGrep(Classes::TComponent* AOwner);
	__fastcall virtual ~TGrep(void);
	void __fastcall PrintRegExp(AnsiString FName);
	bool __fastcall MatchString(AnsiString Instring, int &MatchPos);
	__property TGrepToken RegExpToken[int regix] = {read=GetRegExpToken};
	__property int MatchEndPos = {read=FMatchEndPos, nodefault};
	__property int MatchStartPos = {read=FMatchStartPos, nodefault};
	__property int NrOfRegExpTokens = {read=FLengRegExp, nodefault};
	__property int LastError = {read=FError, nodefault};
	
__published:
	__property bool IgnoreCase = {read=FIgnoreCase, write=SetIgnoreCase, nodefault};
	__property AnsiString RegExp = {read=FRegExpStr, write=SetRegExp};
	__property int SearchStartPos = {read=FSrcStartPos, write=FSrcStartPos, nodefault};
	__property bool StopOnError = {read=FStopOnError, write=FStopOnError, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint MaxGrepTokens = 0x40;
extern PACKAGE System::Set<char, 0, 255>  WordSeps;
#define SDLVersionInfo "stringl_r820_full"
static const bool IsLightEd = false;
static const Word Release = 0x334;
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
extern PACKAGE AnsiString __fastcall StripTrailingChars(char cc, AnsiString Instring);
extern PACKAGE AnsiString __fastcall StripLeadingChars(char cc, AnsiString Instring);
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
extern PACKAGE AnsiString __fastcall Scramble(AnsiString Instring);
extern PACKAGE AnsiString __fastcall DeScramble(AnsiString Instring);
extern PACKAGE void __fastcall InitScramble(int Key);
extern PACKAGE AnsiString __fastcall ReadLnString(AnsiString Instring, int &StartPos, bool &eos, int EOLMode);
extern PACKAGE AnsiString __fastcall ReduceStringToAZ09(AnsiString InString);
extern PACKAGE AnsiString __fastcall ReduceStringToFN83CompliantChars(AnsiString InString);
extern PACKAGE AnsiString __fastcall ReverseString(AnsiString InString);
extern PACKAGE AnsiString __fastcall CapitalizeString(AnsiString Instring);
extern PACKAGE bool __fastcall IsAbbreviation(AnsiString InString);
extern PACKAGE AnsiString __fastcall ExtractWordFromString(const AnsiString InString, const int Pos)/* overload */;
extern PACKAGE AnsiString __fastcall ExtractWordFromString(const AnsiString InString, const int Pos, int &FirstIdx, int &LastIdx)/* overload */;
extern PACKAGE AnsiString __fastcall ExtractSubString(const AnsiString Instring, const int occ, const AnsiString Separator);
extern PACKAGE bool __fastcall EqualAnsiStrings(const AnsiString String1, const AnsiString String2);
extern PACKAGE int __fastcall FindFirstNonBlank(const AnsiString InString);
extern PACKAGE AnsiString __fastcall ChangeCase(const AnsiString InString);
extern PACKAGE bool __fastcall ParseQuotedName(char cc, char QuoteChar, AnsiString &CurrentName, TQuotedStrState &State);
extern PACKAGE AnsiString __fastcall MakeStringHTMLCompatible(AnsiString InString);
extern PACKAGE AnsiString __fastcall ResolveHTMLEntities(AnsiString InString);
extern PACKAGE char __fastcall HTMLEntityToAnsi(AnsiString Entity);
extern PACKAGE AnsiString __fastcall AnsiToHTMLEntity(char cc);
extern PACKAGE AnsiString __fastcall ExtractParam(AnsiString ParamId, int StartPos, char AssignChar, char Terminator, AnsiString InString);
extern PACKAGE AnsiString __fastcall UUEncodeStr(AnsiString Instring);
extern PACKAGE AnsiString __fastcall UUDecodeStr(AnsiString Instring);
extern PACKAGE void __fastcall TextLineCoords(const AnsiString InString, const int Pos, int &X, int &Y);
extern PACKAGE int __fastcall ReadNextTagInString(const AnsiString InString, int &StartAt, const AnsiString * TagList, const int TagList_Size, AnsiString &Attrib, AnsiString &Contents);
extern PACKAGE int __fastcall DetectNextTagInString(const AnsiString InString, int &StartIdx, int &StopIdx, const AnsiString * TagList, const int TagList_Size, AnsiString &Attrib, bool &IsClosingTag);
extern PACKAGE void __fastcall Register(void);

}	/* namespace Stringl */
using namespace Stringl;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// stringl
