// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ADTrmPsr.pas' rev: 6.00

#ifndef ADTrmPsrHPP
#define ADTrmPsrHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <OoMisc.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adtrmpsr
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TAdParserCmdType { pctNone, pctChar, pct8bitChar, pctPending, pctComplete };
#pragma option pop

#pragma option push -b-
enum TAdVTParserState { psIdle, psGotEscape, psParsingANSI, psParsingHash, psParsingLeftParen, psParsingRightParen, psParsingCharSet, psGotCommand, psGotInterCommand, psParsingCUP52 };
#pragma option pop

typedef int TAdIntegerArray[536870911];

typedef int *PAdIntegerArray;

class DELPHICLASS TAdTerminalParser;
class PASCALIMPLEMENTATION TAdTerminalParser : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	int FArgCount;
	Byte FCommand;
	bool FUseWideChar;
	
protected:
	virtual int __fastcall tpGetArgument(int aInx);
	virtual AnsiString __fastcall tpGetSequence();
	
public:
	__fastcall TAdTerminalParser(bool aUseWideChar);
	__fastcall virtual ~TAdTerminalParser(void);
	virtual TAdParserCmdType __fastcall ProcessChar(char aCh);
	virtual TAdParserCmdType __fastcall ProcessWideChar(wchar_t aCh);
	virtual void __fastcall Clear(void);
	void __fastcall ForceCommand(int Command);
	__property int Argument[int aInx] = {read=tpGetArgument};
	__property int ArgumentCount = {read=FArgCount, nodefault};
	__property Byte Command = {read=FCommand, nodefault};
	__property AnsiString Sequence = {read=tpGetSequence};
};


class DELPHICLASS TAdVT100Parser;
class PASCALIMPLEMENTATION TAdVT100Parser : public TAdTerminalParser 
{
	typedef TAdTerminalParser inherited;
	
private:
	int FArgCountMax;
	int *FArgs;
	bool FInVT52Mode;
	void *FSavedSeq;
	TAdVTParserState FSavedState;
	void *FSequence;
	TAdVTParserState FState;
	
protected:
	virtual int __fastcall tpGetArgument(int aInx);
	virtual AnsiString __fastcall tpGetSequence();
	bool __fastcall vtpGetArguments(void);
	TAdParserCmdType __fastcall vtpParseANSISeq(char aCh);
	TAdParserCmdType __fastcall vtpProcessVT52(char aCh);
	bool __fastcall vtpValidateArgsPrim(int aMinArgs, int aMaxArgs, int aDefault);
	void __fastcall vtpGrowArgs(void);
	
public:
	__fastcall TAdVT100Parser(bool aUseWideChar);
	__fastcall virtual ~TAdVT100Parser(void);
	virtual TAdParserCmdType __fastcall ProcessChar(char aCh);
	virtual TAdParserCmdType __fastcall ProcessWideChar(wchar_t aCh);
	virtual void __fastcall Clear(void);
	__property bool InVT52Mode = {read=FInVT52Mode, nodefault};
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adtrmpsr */
using namespace Adtrmpsr;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ADTrmPsr
