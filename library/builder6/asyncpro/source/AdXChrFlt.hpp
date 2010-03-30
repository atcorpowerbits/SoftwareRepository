// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdXChrFlt.pas' rev: 6.00

#ifndef AdXChrFltHPP
#define AdXChrFltHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdExcept.hpp>	// Pascal unit
#include <AdXBase.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adxchrflt
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TApdStreamFormat { sfUTF8, sfUTF16LE, sfUTF16BE, sfISO88591 };
#pragma option pop

class DELPHICLASS TApdBaseCharFilter;
class PASCALIMPLEMENTATION TApdBaseCharFilter : public System::TObject 
{
	typedef System::TObject inherited;
	
protected:
	int FBufSize;
	char *FBuffer;
	int FBufPos;
	TApdStreamFormat FFormat;
	bool FFreeStream;
	Classes::TStream* FStream;
	int FStreamPos;
	int FStreamSize;
	virtual int __fastcall csGetSize(void);
	virtual void __fastcall csSetFormat(const TApdStreamFormat aValue) = 0 ;
	
public:
	__fastcall virtual TApdBaseCharFilter(Classes::TStream* aStream, const int aBufSize);
	__fastcall virtual ~TApdBaseCharFilter(void);
	__property int BufSize = {read=FBufSize, nodefault};
	__property bool FreeStream = {read=FFreeStream, write=FFreeStream, nodefault};
	__property Classes::TStream* Stream = {read=FStream};
};


class DELPHICLASS TApdInCharFilter;
class PASCALIMPLEMENTATION TApdInCharFilter : public TApdBaseCharFilter 
{
	typedef TApdBaseCharFilter inherited;
	
private:
	int FBufEnd;
	int FUCS4Char;
	int FLine;
	int FLinePos;
	wchar_t FLastChar;
	bool FEOF;
	int FBufDMZ;
	bool FInTryRead;
	
protected:
	void __fastcall csAdvanceLine(void);
	void __fastcall csAdvanceLinePos(void);
	void __fastcall csGetCharPrim(int &aCh, bool &aIsLiteral);
	bool __fastcall csGetNextBuffer(void);
	bool __fastcall csGetTwoAnsiChars(void *Buffer);
	int __fastcall csGetUtf8Char(void);
	void __fastcall csIdentifyFormat(void);
	void __fastcall csPushCharPrim(int aCh);
	virtual void __fastcall csSetFormat(const TApdStreamFormat aValue);
	void __fastcall csGetChar(int &aCh, bool &aIsLiteral);
	
public:
	__fastcall virtual TApdInCharFilter(Classes::TStream* aStream, const int aBufSize);
	__property TApdStreamFormat Format = {read=FFormat, write=csSetFormat, nodefault};
	__property bool EOF = {read=FEOF, nodefault};
	void __fastcall SkipChar(void);
	bool __fastcall TryRead(const int * S, const int S_Size);
	wchar_t __fastcall ReadChar(void);
	wchar_t __fastcall ReadAndSkipChar(void);
	__property int Line = {read=FLine, nodefault};
	__property int LinePos = {read=FLinePos, nodefault};
public:
	#pragma option push -w-inl
	/* TApdBaseCharFilter.Destroy */ inline __fastcall virtual ~TApdInCharFilter(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdOutCharFilter;
class PASCALIMPLEMENTATION TApdOutCharFilter : public TApdBaseCharFilter 
{
	typedef TApdBaseCharFilter inherited;
	
protected:
	TApdStreamFormat FFormat;
	bool FSetUTF8Sig;
	virtual int __fastcall csGetSize(void);
	void __fastcall csPutUtf8Char(const int aCh);
	virtual void __fastcall csSetFormat(const TApdStreamFormat aValue);
	void __fastcall csWriteBuffer(void);
	
public:
	__fastcall virtual TApdOutCharFilter(Classes::TStream* aStream, const int aBufSize);
	__fastcall virtual ~TApdOutCharFilter(void);
	void __fastcall PutUCS4Char(int aCh);
	bool __fastcall PutChar(wchar_t aCh1, wchar_t aCh2, bool &aBothUsed);
	bool __fastcall PutString(const WideString aText);
	int __fastcall Position(void);
	__property TApdStreamFormat Format = {read=FFormat, write=csSetFormat, nodefault};
	__property bool WriteUTF8Signature = {read=FSetUTF8Sig, write=FSetUTF8Sig, nodefault};
	__property int Size = {read=csGetSize, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
static const char ApxEndOfStream = '\x1';
static const char ApxEndOfReplaceText = '\x2';
static const char ApxNullChar = '\x3';

}	/* namespace Adxchrflt */
using namespace Adxchrflt;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdXChrFlt
