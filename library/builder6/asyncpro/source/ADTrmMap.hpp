// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ADTrmMap.pas' rev: 6.00

#ifndef ADTrmMapHPP
#define ADTrmMapHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <OoMisc.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adtrmmap
{
//-- type declarations -------------------------------------------------------
typedef SmallString<63>  TAdKeyString;

typedef TAdKeyString *PadKeyString;

class DELPHICLASS TAdKeyboardMapping;
class PASCALIMPLEMENTATION TAdKeyboardMapping : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Classes::TList* FTable;
	int FCount;
	
protected:
	bool __fastcall kbmFindPrim(const TAdKeyString &aKey, int &aInx, void * &aNode);
	
public:
	__fastcall TAdKeyboardMapping(void);
	__fastcall virtual ~TAdKeyboardMapping(void);
	bool __fastcall Add(const TAdKeyString &aKey, const TAdKeyString &aValue);
	void __fastcall Clear(void);
	TAdKeyString __fastcall Get(const TAdKeyString &aKey);
	void __fastcall LoadFromFile(const AnsiString aFileName);
	void __fastcall LoadFromRes(unsigned aInstance, const AnsiString aResName);
	void __fastcall StoreToBinFile(const AnsiString aFileName);
	__property int Count = {read=FCount, nodefault};
};


class DELPHICLASS TAdCharSetMapping;
class PASCALIMPLEMENTATION TAdCharSetMapping : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Classes::TList* FTable;
	void *FCharQueue;
	int FCount;
	void *FScript;
	void *FScriptEnd;
	void *FScriptFreeList;
	
protected:
	void __fastcall csmAddScriptNode(PadKeyString aFont);
	bool __fastcall csmFindPrim(const TAdKeyString &aCharSet, char aChar, int &aInx, void * &aNode);
	void __fastcall csmFreeScript(void);
	
public:
	__fastcall TAdCharSetMapping(void);
	__fastcall virtual ~TAdCharSetMapping(void);
	bool __fastcall Add(const TAdKeyString &aCharSet, char aFromCh, char aToCh, const TAdKeyString &aFont, char aGlyph);
	void __fastcall Clear(void);
	void __fastcall GetFontNames(Classes::TStrings* aList);
	void __fastcall GenerateDrawScript(const TAdKeyString &aCharSet, char * aText);
	bool __fastcall GetNextDrawCommand( TAdKeyString &aFont, char * aText);
	void __fastcall LoadFromFile(const AnsiString aFileName);
	void __fastcall LoadFromRes(unsigned aInstance, const AnsiString aResName);
	void __fastcall StoreToBinFile(const AnsiString aFileName);
	__property int Count = {read=FCount, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE System::SmallString<9>  DefaultFontName;

}	/* namespace Adtrmmap */
using namespace Adtrmmap;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ADTrmMap
