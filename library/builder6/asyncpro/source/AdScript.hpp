// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdScript.pas' rev: 6.00

#ifndef AdScriptHPP
#define AdScriptHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdProtcl.hpp>	// Pascal unit
#include <ADTrmEmu.hpp>	// Pascal unit
#include <AdWnPort.hpp>	// Pascal unit
#include <AdPort.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <ShellAPI.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adscript
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EApdScriptError;
class PASCALIMPLEMENTATION EApdScriptError : public Adexcept::EAPDException 
{
	typedef Adexcept::EAPDException inherited;
	
public:
	__fastcall EApdScriptError(unsigned Code, unsigned BadLineNum);
public:
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EApdScriptError(const AnsiString Msg, Byte Dummy) : Adexcept::EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EApdScriptError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Adexcept::EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EApdScriptError(int Ident)/* overload */ : Adexcept::EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EApdScriptError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Adexcept::EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EApdScriptError(const AnsiString Msg, int AHelpContext) : Adexcept::EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EApdScriptError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Adexcept::EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EApdScriptError(int Ident, int AHelpContext)/* overload */ : Adexcept::EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EApdScriptError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Adexcept::EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EApdScriptError(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TApdScriptCommand { scNoCommand, scComment, scLabel, scInitPort, scInitWnPort, scDonePort, scSend, scWait, scWaitMulti, scIf, scDisplay, scGoto, scSendBreak, scDelay, scSetOption, scUpload, scDownload, scChDir, scDelete, scRun, scUserFunction, scExit };
#pragma option pop

#pragma option push -b-
enum TOption { oNone, oBaud, oDataBits, oFlow, oParity, oStopBits, oWsTelnet, oSetRetry, oSetDirectory, oSetFilemask, oSetFilename, oSetWriteFail, oSetWriteRename, oSetWriteAnyway, oSetZWriteClobber, oSetZWriteProtect, oSetZWriteNewer, oSetZSkipNoFile };
#pragma option pop

class DELPHICLASS TApdScriptNode;
class PASCALIMPLEMENTATION TApdScriptNode : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	TApdScriptCommand Command;
	AnsiString Data;
	AnsiString DataEx;
	TOption Option;
	unsigned Timeout;
	unsigned Condition;
	__fastcall TApdScriptNode(TApdScriptCommand ACommand, TOption AnOption, const AnsiString AData, const AnsiString ADataEx, unsigned ATimeout, unsigned ACondition);
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TApdScriptNode(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TScriptState { ssNone, ssReady, ssWait, ssFinished };
#pragma option pop

typedef void __fastcall (__closure *TScriptFinishEvent)(System::TObject* CP, int Condition);

typedef void __fastcall (__closure *TScriptCommandEvent)(System::TObject* CP, TApdScriptNode* Node, int Condition);

typedef void __fastcall (__closure *TScriptDisplayEvent)(System::TObject* CP, const AnsiString Msg);

typedef void __fastcall (__closure *TScriptUserFunctionEvent)(System::TObject* CP, const AnsiString Command, const AnsiString Parameter);

typedef void __fastcall (__closure *TScriptParseVariableEvent)(System::TObject* CP, const AnsiString Variable, AnsiString &NewValue);

typedef void __fastcall (__closure *TScriptExceptionEvent)(System::TObject* Sender, Sysutils::Exception* E, TApdScriptNode* Command, bool &Continue);

class DELPHICLASS TApdCustomScript;
class PASCALIMPLEMENTATION TApdCustomScript : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	Adport::TApdCustomComPort* FComPort;
	Adprotcl::TApdCustomProtocol* FProtocol;
	Oomisc::TApdBaseWinControl* FTerminal;
	AnsiString FScriptFile;
	Classes::TStrings* FScriptCommands;
	unsigned CurrentLine;
	bool Modified;
	Classes::TList* CommandNodes;
	int NodeIndex;
	int NextIndex;
	unsigned TimerTrigger;
	unsigned DataTrigger[20];
	unsigned TriggerCount;
	Adport::TTriggerEvent SaveOnTrigger;
	TScriptState ScriptState;
	bool CreatedPort;
	bool SaveOpen;
	bool OpenedPort;
	bool CreatedProtocol;
	unsigned LastCondition;
	Adprotcl::TProtocolFinishEvent SaveProtocolFinish;
	bool OldActive;
	bool Continuing;
	bool Closing;
	Byte Retry;
	Byte Attempts;
	bool FInProgress;
	bool FDisplayToTerminal;
	TScriptFinishEvent FOnScriptFinish;
	TScriptCommandEvent FOnScriptCommandStart;
	TScriptCommandEvent FOnScriptCommandFinish;
	TScriptDisplayEvent FOnScriptDisplay;
	TScriptUserFunctionEvent FOnScriptUserFunction;
	TScriptParseVariableEvent FOnScriptParseVariable;
	TScriptExceptionEvent FOnScriptException;
	void __fastcall SetScriptFile(const AnsiString NewFile);
	void __fastcall SetScriptCommands(Classes::TStrings* Values);
	void __fastcall ValidateLabels(void);
	virtual void __fastcall CreateCommand(TApdScriptCommand CmdType, const AnsiString Data1, const AnsiString Data2);
	virtual void __fastcall AddToScript(const AnsiString S);
	bool __fastcall CheckProtocol(void);
	bool __fastcall CheckWinsockPort(void);
	AnsiString __fastcall ValidateBaud(const AnsiString Baud);
	AnsiString __fastcall ValidateDataBits(const AnsiString DataBits);
	AnsiString __fastcall ValidateFlow(const AnsiString Flow);
	AnsiString __fastcall ValidateParity(const AnsiString Parity);
	AnsiString __fastcall ValidateStopBits(const AnsiString StopBits);
	void __fastcall AllTriggers(System::TObject* CP, Word Msg, Word TriggerHandle, Word Data);
	virtual void __fastcall ExecuteExternal(const AnsiString S, bool Wait);
	void __fastcall GoContinue(void);
	void __fastcall ParseURL(const AnsiString URL, AnsiString &Addr, AnsiString &Port);
	void __fastcall LogCommand(unsigned Index, TApdScriptCommand Command, const TApdScriptNode* Node);
	void __fastcall ProcessNextCommand(void);
	void __fastcall ProcessTillWait(void);
	void __fastcall ScriptProtocolFinish(System::TObject* CP, int ErrorCode);
	void __fastcall SetFlow(const AnsiString FlowOpt);
	void __fastcall SetParity(const AnsiString ParityOpt);
	virtual void __fastcall ScriptFinish(int Condition);
	void __fastcall ScriptCommandStart(TApdScriptNode* Node, int Condition);
	void __fastcall ScriptCommandFinish(TApdScriptNode* Node, int Condition);
	void __fastcall ScriptDisplay(const AnsiString Msg);
	bool __fastcall GenerateScriptException(Sysutils::Exception* E, TApdScriptNode* Command);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual void __fastcall Loaded(void);
	void __fastcall AddDispatchLogEntry(const AnsiString Msg);
	
public:
	__fastcall virtual TApdCustomScript(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomScript(void);
	void __fastcall PrepareScript(void);
	void __fastcall StartScript(void);
	void __fastcall StopScript(int Condition);
	void __fastcall CancelScript(void);
	__property bool InProgress = {read=FInProgress, nodefault};
	__property Adport::TApdCustomComPort* ComPort = {read=FComPort, write=FComPort};
	__property Adprotcl::TApdCustomProtocol* Protocol = {read=FProtocol, write=FProtocol};
	__property Oomisc::TApdBaseWinControl* Terminal = {read=FTerminal, write=FTerminal};
	__property bool DisplayToTerminal = {read=FDisplayToTerminal, write=FDisplayToTerminal, default=1};
	__property AnsiString ScriptFile = {read=FScriptFile, write=SetScriptFile};
	__property Classes::TStrings* ScriptCommands = {read=FScriptCommands, write=SetScriptCommands, stored=true};
	__property TScriptFinishEvent OnScriptFinish = {read=FOnScriptFinish, write=FOnScriptFinish};
	__property TScriptCommandEvent OnScriptCommandStart = {read=FOnScriptCommandStart, write=FOnScriptCommandStart};
	__property TScriptCommandEvent OnScriptCommandFinish = {read=FOnScriptCommandFinish, write=FOnScriptCommandFinish};
	__property TScriptDisplayEvent OnScriptDisplay = {read=FOnScriptDisplay, write=FOnScriptDisplay};
	__property TScriptParseVariableEvent OnScriptParseVariable = {read=FOnScriptParseVariable, write=FOnScriptParseVariable};
	__property TScriptUserFunctionEvent OnScriptUserFunction = {read=FOnScriptUserFunction, write=FOnScriptUserFunction};
	__property TScriptExceptionEvent OnScriptException = {read=FOnScriptException, write=FOnScriptException};
};


class DELPHICLASS TApdScript;
class PASCALIMPLEMENTATION TApdScript : public TApdCustomScript 
{
	typedef TApdCustomScript inherited;
	
__published:
	__property ComPort ;
	__property Protocol ;
	__property Terminal ;
	__property DisplayToTerminal  = {default=1};
	__property ScriptFile ;
	__property ScriptCommands ;
	__property OnScriptFinish ;
	__property OnScriptCommandStart ;
	__property OnScriptCommandFinish ;
	__property OnScriptDisplay ;
	__property OnScriptParseVariable ;
	__property OnScriptUserFunction ;
public:
	#pragma option push -w-inl
	/* TApdCustomScript.Create */ inline __fastcall virtual TApdScript(Classes::TComponent* AOwner) : TApdCustomScript(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomScript.Destroy */ inline __fastcall virtual ~TApdScript(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint MaxDataTriggers = 0x14;
static const Byte MaxCommandLength = 0x80;
static const Word MaxCommands = 0x12c;
static const Shortint DefRetryCnt = 0x3;
static const Word MaxBufSize = 0x7fff;
static const bool DefDisplayToTerminal = true;
static const char CmdSepChar = '\x7c';
static const Word ecNotACommand = 0x26ad;
static const Word ecBadFormat1 = 0x26ae;
static const Word ecBadFormat2 = 0x26af;
static const Word ecInvalidLabel = 0x26b0;
static const Word ecBadOption = 0x26b1;
static const Word ecTooManyStr = 0x26b2;
static const Word ecNoScriptCommands = 0x26b3;
static const Word ecCommandTooLong = 0x26b4;
static const Word ecNotWinsockPort = 0x26b5;
static const Shortint ccNone = 0x0;
static const Shortint ccSuccess = 0x1;
static const Shortint ccIndexFirst = 0x1;
static const Byte ccIndexLast = 0x80;
static const Word ccTimeout = 0x3e9;
static const Word ccFail = 0x3ea;
static const Word ccBadExitCode = 0x3eb;
extern PACKAGE System::SmallString<14>  ScriptStr[22];

}	/* namespace Adscript */
using namespace Adscript;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdScript
