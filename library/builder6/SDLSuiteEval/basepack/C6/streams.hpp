// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'streams.pas' rev: 6.00

#ifndef streamsHPP
#define streamsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Streams
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (*TSRUnknownModifierEvent)(AnsiString Command, AnsiString &Substring);

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall WriteStringStream(Classes::TStream* OutStream, AnsiString AString);
extern PACKAGE void __fastcall WriteExtendedToStream(Classes::TStream* OutStream, Extended value);
extern PACKAGE void __fastcall WriteLongintToStream(Classes::TStream* OutStream, int value);
extern PACKAGE void __fastcall WriteLnStream(Classes::TStream* OutStream, AnsiString Line);
extern PACKAGE AnsiString __fastcall ReadLnStream(Classes::TStream* Instream, bool &eos, int EOLMode);
extern PACKAGE Extended __fastcall ReadExtendedFromStream(Classes::TStream* InStream, bool &eos);
extern PACKAGE int __fastcall ReadLongintFromStream(Classes::TStream* InStream, bool &eos);
extern PACKAGE int __fastcall ReadNextTagInStream(Classes::TStream* AStream, const AnsiString * TagList, const int TagList_Size, AnsiString &Attrib, AnsiString &Contents);
extern PACKAGE int __fastcall ReadNextTagInTextFile(TextFile &AFile, const AnsiString * TagList, const int TagList_Size, AnsiString &Attrib, AnsiString &Contents);
extern PACKAGE AnsiString __fastcall ScanForXMLAttrib(AnsiString Attributes, AnsiString AttribName);
extern PACKAGE bool __fastcall FindInStream(Classes::TStream* Instream, Byte AByte);
extern PACKAGE int __fastcall ScanStreamForXMLTag(Classes::TStream* InStream, AnsiString XMLTag, AnsiString &Attrib, AnsiString &Contents);
extern PACKAGE AnsiString __fastcall ReadStreamUntil(Classes::TStream* InStream, AnsiString SubString, int &Error);
extern PACKAGE AnsiString __fastcall ReadStreamUntilTagList(Classes::TStream* InStream, const AnsiString * TagList, const int TagList_Size, int &TagNr);
extern PACKAGE int __fastcall ScanStreamDecimal(Classes::TStream* InStream);
extern PACKAGE void __fastcall ExtractFromStream(Classes::TStream* InStream, Classes::TMemoryStream* &OutStream, Classes::TStringList* Commands);
extern PACKAGE double __fastcall ScanStreamFPNum(Classes::TStream* Instream, bool AllowExp, int DecPChar);
extern PACKAGE bool __fastcall SearchAndReplace(Classes::TMemoryStream* &InStream, Classes::TMemoryStream* &OutStream, AnsiString SearchExp, AnsiString ReplaceExp, bool IgnoreCase, int CondToken, int Combination, AnsiString CondText, TSRUnknownModifierEvent OnUnknownModifier);
extern PACKAGE AnsiString __fastcall StreamAsString(Classes::TStream* AStream);

}	/* namespace Streams */
using namespace Streams;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// streams
