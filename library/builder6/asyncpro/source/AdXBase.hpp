// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdXBase.pas' rev: 6.00

#ifndef AdXBaseHPP
#define AdXBaseHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <OoMisc.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adxbase
{
//-- type declarations -------------------------------------------------------
typedef int TApdUcs4Char;

typedef SmallString<6>  TApdUtf8Char;

typedef wchar_t DOMChar;

typedef wchar_t *PDOMChar;

#pragma option push -b-
enum TApdCharEncoding { ceUnknown, ceUTF8 };
#pragma option pop

class DELPHICLASS TApdMemoryStream;
class PASCALIMPLEMENTATION TApdMemoryStream : public Classes::TMemoryStream 
{
	typedef Classes::TMemoryStream inherited;
	
public:
	HIDESBASE void __fastcall SetPointer(void * Ptr, int Size);
public:
	#pragma option push -w-inl
	/* TMemoryStream.Destroy */ inline __fastcall virtual ~TApdMemoryStream(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TApdMemoryStream(void) : Classes::TMemoryStream() { }
	#pragma option pop
	
};


class DELPHICLASS TApdFileStream;
class PASCALIMPLEMENTATION TApdFileStream : public Classes::TFileStream 
{
	typedef Classes::TFileStream inherited;
	
public:
	AnsiString FFileName;
	__fastcall TApdFileStream(Word Mode, const AnsiString FileName);
	__property AnsiString Filename = {read=FFileName};
public:
	#pragma option push -w-inl
	/* TFileStream.Create */ inline __fastcall TApdFileStream(const AnsiString FileName, Word Mode)/* overload */ : Classes::TFileStream(FileName, Mode) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TFileStream.Destroy */ inline __fastcall virtual ~TApdFileStream(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int __fastcall ApxPos(const WideString aSubStr, const WideString aString);
extern PACKAGE int __fastcall ApxRPos(const WideString sSubStr, const WideString sTerm);
extern PACKAGE bool __fastcall ApxIso88591ToUcs4(char aInCh, int &aOutCh);
extern PACKAGE bool __fastcall ApxUcs4ToIso88591(int aInCh, char &aOutCh);
extern PACKAGE bool __fastcall ApxUcs4ToWideChar(const int aInChar, wchar_t &aOutWS);
extern PACKAGE bool __fastcall ApxUtf16ToUcs4(wchar_t aInChI, wchar_t aInChII, int &aOutCh, bool &aBothUsed);
extern PACKAGE bool __fastcall ApxUcs4ToUtf8(int aInCh,  TApdUtf8Char &aOutCh);
extern PACKAGE bool __fastcall ApxUtf8ToUcs4(const TApdUtf8Char &aInCh, int aBytes, int &aOutCh);
extern PACKAGE Byte __fastcall ApxGetLengthUtf8(const char aCh);
extern PACKAGE bool __fastcall ApxIsBaseChar(int aCh);
extern PACKAGE bool __fastcall ApxIsChar(const int aCh);
extern PACKAGE bool __fastcall ApxIsCombiningChar(int aCh);
extern PACKAGE bool __fastcall ApxIsDigit(int aCh);
extern PACKAGE bool __fastcall ApxIsExtender(int aCh);
extern PACKAGE bool __fastcall ApxIsIdeographic(int aCh);
extern PACKAGE bool __fastcall ApxIsLetter(int aCh);
extern PACKAGE bool __fastcall ApxIsNameChar(int aCh);
extern PACKAGE bool __fastcall ApxIsNameCharFirst(int aCh);
extern PACKAGE bool __fastcall ApxIsPubidChar(int aCh);
extern PACKAGE bool __fastcall ApxIsSpace(int aCh);

}	/* namespace Adxbase */
using namespace Adxbase;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdXBase
