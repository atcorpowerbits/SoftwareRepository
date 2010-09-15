// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdSapiPh.pas' rev: 6.00

#ifndef AdSapiPhHPP
#define AdSapiPhHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdPort.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <ComObj.hpp>	// Pascal unit
#include <ActiveX.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit
#include <DateUtils.hpp>	// Pascal unit
#include <AdISapi.hpp>	// Pascal unit
#include <AdSapiGr.hpp>	// Pascal unit
#include <AdTapi.hpp>	// Pascal unit
#include <AdTUtil.hpp>	// Pascal unit
#include <AdSapiEn.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <IniFiles.hpp>	// Pascal unit
#include <MMSystem.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adsapiph
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum AdSapiPh__1 { psVerify, psCanGoBack, psDisableSpeedChange, psEnableOperator, psEnableAskHangup };
#pragma option pop

typedef Set<AdSapiPh__1, psVerify, psEnableAskHangup>  TApdSapiPhoneSettings;

#pragma option push -b-
enum TApdSapiPhoneReply { prOk, prAbort, prNoResponse, prOperator, prHangUp, prBack, prWhere, prHelp, prRepeat, prSpeakFaster, prSpeakSlower, prCheck, prError, prUnknown };
#pragma option pop

#pragma option push -b-
enum TApdPhraseType { ptHelp, ptBack, ptOperator, ptHangup, ptRepeat, ptWhere, ptSpeakFaster, ptSpeakSlower, ptUnknown, ptNone, ptCustom, ptAbort, ptTimeout };
#pragma option pop

#pragma option push -b-
enum TGrammarStringHandler { gshIgnore, gshInsert, gshAutoReplace };
#pragma option pop

typedef void __fastcall (__closure *TApdSapiPhoneEvent)(System::TObject* Sender);

typedef void __fastcall (__closure *TApdOnAskForStringFinish)(System::TObject* Sender, TApdSapiPhoneReply Reply, AnsiString Data, AnsiString SpokenData);

typedef void __fastcall (__closure *TApdOnAskForDateTimeFinish)(System::TObject* Sender, TApdSapiPhoneReply Reply, System::TDateTime Data, AnsiString SpokenData);

typedef void __fastcall (__closure *TApdOnAskForIntegerFinish)(System::TObject* Sender, TApdSapiPhoneReply Reply, int Data, AnsiString SpokenData);

typedef void __fastcall (__closure *TApdOnAskForBooleanFinish)(System::TObject* Sender, TApdSapiPhoneReply Reply, bool Data, AnsiString SpokenData);

typedef void __fastcall (__closure *TApdCustomDataHandler)(TApdPhraseType LastReply, int LastRule, AnsiString LastPhrase);

typedef void __fastcall (__closure *TApdAskForEventTrigger)(TApdSapiPhoneReply Reply, void * Data, AnsiString SpokenData);

class DELPHICLASS ESapiPhoneError;
class PASCALIMPLEMENTATION ESapiPhoneError : public Adsapien::EApdSapiEngineException 
{
	typedef Adsapien::EApdSapiEngineException inherited;
	
public:
	#pragma option push -w-inl
	/* EApdSapiEngineException.Create */ inline __fastcall ESapiPhoneError(const int ErrCode, const AnsiString Msg) : Adsapien::EApdSapiEngineException(ErrCode, Msg) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESapiPhoneError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Adsapien::EApdSapiEngineException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESapiPhoneError(int Ident)/* overload */ : Adsapien::EApdSapiEngineException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESapiPhoneError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Adsapien::EApdSapiEngineException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESapiPhoneError(const AnsiString Msg, int AHelpContext) : Adsapien::EApdSapiEngineException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESapiPhoneError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Adsapien::EApdSapiEngineException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESapiPhoneError(int Ident, int AHelpContext)/* overload */ : Adsapien::EApdSapiEngineException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESapiPhoneError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Adsapien::EApdSapiEngineException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESapiPhoneError(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdSapiGrammarList;
class PASCALIMPLEMENTATION TApdSapiGrammarList : public Classes::TStringList 
{
	typedef Classes::TStringList inherited;
	
public:
	void __fastcall ReadSectionValues(AnsiString Section, Classes::TStringList* List);
	bool __fastcall SectionExists(AnsiString Section);
public:
	#pragma option push -w-inl
	/* TStringList.Destroy */ inline __fastcall virtual ~TApdSapiGrammarList(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TApdSapiGrammarList(void) : Classes::TStringList() { }
	#pragma option pop
	
};


class DELPHICLASS TApdSapiPhonePrompts;
class PASCALIMPLEMENTATION TApdSapiPhonePrompts : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	AnsiString FAskAreaCode;
	AnsiString FAskLastFour;
	AnsiString FAskNextThree;
	AnsiString FCannotGoBack;
	AnsiString FCannotHangUp;
	AnsiString FGoingBack;
	AnsiString FHangingUp;
	AnsiString FHelp;
	AnsiString FHelp2;
	AnsiString FHelpVerify;
	AnsiString FMain;
	AnsiString FMain2;
	AnsiString FMaxSpeed;
	AnsiString FMinSpeed;
	AnsiString FOperator;
	AnsiString FNoOperator;
	AnsiString FNoSpeedChange;
	AnsiString FSpeakingFaster;
	AnsiString FSpeakingSlower;
	AnsiString FTooFewDigits;
	AnsiString FTooManyDigits;
	AnsiString FUnrecognized;
	AnsiString FVerifyPost;
	AnsiString FVerifyPre;
	AnsiString FWhere;
	AnsiString FWhere2;
	
protected:
	void __fastcall SetAskAreaCode(AnsiString v);
	void __fastcall SetAskLastFour(AnsiString v);
	void __fastcall SetAskNextThree(AnsiString v);
	void __fastcall SetCannotGoBack(AnsiString v);
	void __fastcall SetCannotHangUp(AnsiString v);
	void __fastcall SetGoingBack(AnsiString v);
	void __fastcall SetHangingUp(AnsiString v);
	void __fastcall SetHelp(AnsiString v);
	void __fastcall SetHelp2(AnsiString v);
	void __fastcall SetHelpVerify(AnsiString v);
	void __fastcall SetMain(AnsiString v);
	void __fastcall SetMain2(AnsiString v);
	void __fastcall SetMaxSpeed(AnsiString v);
	void __fastcall SetMinSpeed(AnsiString v);
	void __fastcall SetOperator(AnsiString v);
	void __fastcall SetNoOperator(AnsiString v);
	void __fastcall SetNoSpeedChange(AnsiString v);
	void __fastcall SetSpeakingFaster(AnsiString v);
	void __fastcall SetSpeakingSlower(AnsiString v);
	void __fastcall SetTooFewDigits(AnsiString v);
	void __fastcall SetTooManyDigits(AnsiString v);
	void __fastcall SetUnrecognized(AnsiString v);
	void __fastcall SetVerifyPost(AnsiString v);
	void __fastcall SetVerifyPre(AnsiString v);
	void __fastcall SetWhere(AnsiString v);
	void __fastcall SetWhere2(AnsiString v);
	
public:
	__fastcall TApdSapiPhonePrompts(void);
	AnsiString __fastcall GenerateGrammar(AnsiString NewPrompt1, AnsiString NewPrompt2, AnsiString NewHelp1, AnsiString NewHelp2, AnsiString NewWhere1, AnsiString NewWhere2);
	AnsiString __fastcall GenerateExtensionGrammar(AnsiString NewTooFewDigits, AnsiString NewTooManyDigits);
	AnsiString __fastcall GeneratePhoneNumberGrammar(AnsiString NewAskAreaCode, AnsiString NewAskNextThree, AnsiString NewAskLastFour);
	
__published:
	__property AnsiString AskAreaCode = {read=FAskAreaCode, write=SetAskAreaCode};
	__property AnsiString AskLastFour = {read=FAskLastFour, write=SetAskLastFour};
	__property AnsiString AskNextThree = {read=FAskNextThree, write=SetAskNextThree};
	__property AnsiString CannotGoBack = {read=FCannotGoBack, write=SetCannotGoBack};
	__property AnsiString CannotHangUp = {read=FCannotHangUp, write=SetCannotHangUp};
	__property AnsiString HangingUp = {read=FHangingUp, write=SetHangingUp};
	__property AnsiString Help = {read=FHelp, write=SetHelp};
	__property AnsiString Help2 = {read=FHelp2, write=SetHelp2};
	__property AnsiString HelpVerify = {read=FHelpVerify, write=SetHelpVerify};
	__property AnsiString GoingBack = {read=FGoingBack, write=SetGoingBack};
	__property AnsiString Main = {read=FMain, write=SetMain};
	__property AnsiString Main2 = {read=FMain2, write=SetMain2};
	__property AnsiString MaxSpeed = {read=FMaxSpeed, write=SetMaxSpeed};
	__property AnsiString MinSpeed = {read=FMinSpeed, write=SetMinSpeed};
	__property AnsiString Operator = {read=FOperator, write=SetOperator};
	__property AnsiString NoOperator = {read=FNoOperator, write=SetNoOperator};
	__property AnsiString NoSpeedChange = {read=FNoSpeedChange, write=SetNoSpeedChange};
	__property AnsiString SpeakingFaster = {read=FSpeakingFaster, write=SetSpeakingFaster};
	__property AnsiString SpeakingSlower = {read=FSpeakingSlower, write=SetSpeakingSlower};
	__property AnsiString TooFewDigits = {read=FTooFewDigits, write=SetTooFewDigits};
	__property AnsiString TooManyDigits = {read=FTooManyDigits, write=SetTooManyDigits};
	__property AnsiString Unrecognized = {read=FUnrecognized, write=SetUnrecognized};
	__property AnsiString VerifyPost = {read=FVerifyPost, write=SetVerifyPost};
	__property AnsiString VerifyPre = {read=FVerifyPre, write=SetVerifyPre};
	__property AnsiString Where = {read=FWhere, write=SetWhere};
	__property AnsiString Where2 = {read=FWhere2, write=SetWhere2};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TApdSapiPhonePrompts(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdSapiAskForInfo;
class PASCALIMPLEMENTATION TApdSapiAskForInfo : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	unsigned FReplyHandle;
	TApdSapiPhonePrompts* FPrompts;
	Adsapien::TApdCustomSapiEngine* FSapiEngine;
	Classes::TStringList* FAskForGrammar;
	Classes::TStringList* FMainGrammar;
	TApdSapiPhoneSettings FOptions;
	TGrammarStringHandler FStringHandler;
	
protected:
	TApdPhraseType __fastcall DeterminePhraseTypeEx(AnsiString Phrase, AnsiString &Rule);
	bool __fastcall IsAnglePhrase(AnsiString Phrase);
	bool __fastcall IsParenPhrase(AnsiString Phrase);
	bool __fastcall IsQuoted(AnsiString Phrase);
	AnsiString __fastcall KillQuotes(AnsiString Phrase);
	AnsiString __fastcall GetValue(AnsiString Value);
	AnsiString __fastcall GetKey(AnsiString Value);
	bool __fastcall AnalyzeRule(Classes::TStringList* Tokens, AnsiString CurrentRule, TApdSapiGrammarList* INIFile, Classes::TStringList* CurrentSection, int &CurrentWord, AnsiString &MatchingKey);
	bool __fastcall RecurseRules(Classes::TStringList* Tokens, TApdSapiGrammarList* INIFile, AnsiString CurrentSection, int &CurrentWord, AnsiString &MatchingKey);
	AnsiString __fastcall LocateRule(Classes::TStringList* Tokens);
	void __fastcall InitializeMainGrammar(void);
	virtual void __fastcall SapiPhraseFinishHook(System::TObject* Sender, AnsiString Phrase, int Results);
	void __fastcall SetAskForGrammar(Classes::TStringList* v);
	void __fastcall SetMainGrammar(Classes::TStringList* v);
	void __fastcall SetOptions(TApdSapiPhoneSettings v);
	void __fastcall SetReplyHandle(unsigned v);
	
public:
	__fastcall TApdSapiAskForInfo(void);
	__fastcall virtual ~TApdSapiAskForInfo(void);
	void __fastcall AskFor(void);
	TApdPhraseType __fastcall DeterminePhraseType(AnsiString Phrase);
	AnsiString __fastcall FindGrammarRule(AnsiString &Phrase);
	
__published:
	__property Classes::TStringList* AskForGrammar = {read=FAskForGrammar, write=SetAskForGrammar};
	__property Classes::TStringList* MainGrammar = {read=FMainGrammar, write=SetMainGrammar};
	__property TApdSapiPhoneSettings Options = {read=FOptions, write=SetOptions, nodefault};
	__property TApdSapiPhonePrompts* Prompts = {read=FPrompts, write=FPrompts};
	__property unsigned ReplyHandle = {read=FReplyHandle, write=SetReplyHandle, nodefault};
	__property Adsapien::TApdCustomSapiEngine* SapiEngine = {read=FSapiEngine, write=FSapiEngine};
};


class DELPHICLASS TApdCustomSapiPhone;
class PASCALIMPLEMENTATION TApdCustomSapiPhone : public Adtapi::TApdCustomTapiDevice 
{
	typedef Adtapi::TApdCustomTapiDevice inherited;
	
private:
	Adsapien::TApdCustomSapiEngine* FSapiEngine;
	Adisapi::_di_IAudioMultiMediaDevice IAMM;
	Adisapi::_di_IAudioTel IAT;
	int FNumDigits;
	int FNoAnswerMax;
	int FNoAnswerTime;
	TApdSapiPhoneSettings FOptions;
	bool FInAskFor;
	bool FSpellingEchoBack;
	TApdSapiPhonePrompts* FPrompts;
	TApdSapiAskForInfo* FInfo;
	AnsiString FExtension;
	int FDigitCount;
	AnsiString FSpelledWord;
	Classes::TStringList* FList;
	TApdCustomDataHandler FCustomDataHandler;
	TApdAskForEventTrigger FEventTrigger;
	TApdOnAskForDateTimeFinish FOnAskForDateFinish;
	TApdOnAskForStringFinish FOnAskForExtensionFinish;
	TApdOnAskForIntegerFinish FOnAskForListFinish;
	TApdOnAskForStringFinish FOnAskForPhoneNumberFinish;
	TApdOnAskForStringFinish FOnAskForSpellingFinish;
	TApdOnAskForDateTimeFinish FOnAskForTimeFinish;
	TApdOnAskForBooleanFinish FOnAskForYesNoFinish;
	Classes::TNotifyEvent FOnTapiDisconnect;
	
protected:
	void __fastcall AskForDateDataHandler(TApdPhraseType LastReply, int LastRule, AnsiString LastPhrase);
	void __fastcall AskForExtensionDataHandler(TApdPhraseType LastReply, int LastRule, AnsiString LastPhrase);
	void __fastcall AskForListDataHandler(TApdPhraseType LastReply, int LastRule, AnsiString LastPhrase);
	void __fastcall AskForPhoneNumberDataHandler(TApdPhraseType LastReply, int LastRule, AnsiString LastPhrase);
	void __fastcall AskForSpellingDataHandler(TApdPhraseType LastReply, int LastRule, AnsiString LastPhrase);
	void __fastcall AskForTimeDataHandler(TApdPhraseType LastReply, int LastRule, AnsiString LastPhrase);
	void __fastcall AskForYesNoDataHandler(TApdPhraseType LastReply, int LastRule, AnsiString LastPhrase);
	void __fastcall AskForDateTrigger(TApdSapiPhoneReply Reply, void * Data, AnsiString SpokenData);
	void __fastcall AskForExtensionTrigger(TApdSapiPhoneReply Reply, void * Data, AnsiString SpokenData);
	void __fastcall AskForListTrigger(TApdSapiPhoneReply Reply, void * Data, AnsiString SpokenData);
	void __fastcall AskForPhoneNumberTrigger(TApdSapiPhoneReply Reply, void * Data, AnsiString SpokenData);
	void __fastcall AskForSpellingTrigger(TApdSapiPhoneReply Reply, void * Data, AnsiString SpokenData);
	void __fastcall AskForTimeTrigger(TApdSapiPhoneReply Reply, void * Data, AnsiString SpokenData);
	void __fastcall AskForYesNoTrigger(TApdSapiPhoneReply Reply, void * Data, AnsiString SpokenData);
	TApdSapiPhoneReply __fastcall ConvertResponse(int RCode);
	virtual void __fastcall DoLineCallState(int Device, int P1, int P2, int P3);
	void __fastcall ExitAskFor(TApdSapiPhoneReply Reply, void * Data, AnsiString SpokenData);
	AnsiString __fastcall GetPhraseData(int LParam);
	AnsiString __fastcall FixNumerics(AnsiString Phrase);
	virtual System::TDateTime __fastcall InterpretDate(AnsiString Phrase, bool &Trusted);
	AnsiString __fastcall InterpretPhoneNumber(AnsiString Phrase);
	virtual System::TDateTime __fastcall InterpretTime(AnsiString Phrase);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	MESSAGE void __fastcall PhraseHandler(Messages::TMessage &Msg);
	MESSAGE void __fastcall SapiPhoneCallback(Messages::TMessage &Msg);
	void __fastcall SetNoAnswerMax(int v);
	void __fastcall SetNoAnswerTime(int v);
	void __fastcall SetNumDigits(int v);
	void __fastcall SetOptions(TApdSapiPhoneSettings v);
	void __fastcall SetSpellingEchoBack(bool v);
	void __fastcall UpdateStateMachine(TApdPhraseType LastReply, int LastRule, AnsiString LastPhrase);
	
public:
	__fastcall virtual TApdCustomSapiPhone(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomSapiPhone(void);
	void __fastcall AbortAskFor(void);
	void __fastcall AskForDate(AnsiString NewPrompt1);
	void __fastcall AskForDateEx(AnsiString NewPrompt1, AnsiString NewPrompt2, AnsiString NewHelp1, AnsiString NewHelp2, AnsiString NewWhere1, AnsiString NewWhere2);
	void __fastcall AskForExtension(AnsiString NewPrompt1);
	void __fastcall AskForExtensionEx(AnsiString NewPrompt1, AnsiString NewPrompt2, AnsiString NewTooManyDigits, AnsiString NewTooFewDigits, int NewNumDigits, AnsiString NewHelp1, AnsiString NewHelp2, AnsiString NewWhere1, AnsiString NewWhere2);
	void __fastcall AskForList(Classes::TStringList* List, AnsiString NewPrompt1);
	void __fastcall AskForListEx(Classes::TStringList* List, AnsiString NewPrompt1, AnsiString NewPrompt2, AnsiString NewHelp1, AnsiString NewHelp2, AnsiString NewWhere1, AnsiString NewWhere2);
	void __fastcall AskForPhoneNumber(AnsiString NewPrompt1);
	void __fastcall AskForPhoneNumberEx(AnsiString NewPrompt1, AnsiString NewPrompt2, AnsiString NewAskAreaCode, AnsiString NewAskNextThree, AnsiString NewAskLastFour, AnsiString NewHelp1, AnsiString NewHelp2, AnsiString NewWhere1, AnsiString NewWhere2);
	void __fastcall AskForSpelling(AnsiString NewPrompt1);
	void __fastcall AskForSpellingEx(AnsiString NewPrompt1, AnsiString NewPrompt2, AnsiString NewHelp1, AnsiString NewHelp2, AnsiString NewWhere1, AnsiString NewWhere2);
	void __fastcall AskForTime(AnsiString NewPrompt1);
	void __fastcall AskForTimeEx(AnsiString NewPrompt1, AnsiString NewPrompt2, AnsiString NewHelp1, AnsiString NewHelp2, AnsiString NewWhere1, AnsiString NewWhere2);
	void __fastcall AskForYesNo(AnsiString NewPrompt1);
	void __fastcall AskForYesNoEx(AnsiString NewPrompt1, AnsiString NewPrompt2, AnsiString NewHelp1, AnsiString NewHelp2, AnsiString NewWhere1, AnsiString NewWhere2);
	void __fastcall SetDefaultPrompts(AnsiString NewPrompt1, AnsiString NewPrompt2, AnsiString NewHelp1, AnsiString NewHelp2, AnsiString NewWhere1, AnsiString NewWhere2);
	void __fastcall Speak(const AnsiString Text);
	__property TApdSapiPhonePrompts* Prompts = {read=FPrompts, write=FPrompts};
	
__published:
	__property int NoAnswerMax = {read=FNoAnswerMax, write=SetNoAnswerMax, nodefault};
	__property int NoAnswerTime = {read=FNoAnswerTime, write=SetNoAnswerTime, nodefault};
	__property int NumDigits = {read=FNumDigits, write=SetNumDigits, nodefault};
	__property TApdSapiPhoneSettings Options = {read=FOptions, write=SetOptions, nodefault};
	__property Adsapien::TApdCustomSapiEngine* SapiEngine = {read=FSapiEngine, write=FSapiEngine};
	__property bool SpellingEchoBack = {read=FSpellingEchoBack, write=SetSpellingEchoBack, default=1};
	__property TApdOnAskForDateTimeFinish OnAskForDateFinish = {read=FOnAskForDateFinish, write=FOnAskForDateFinish};
	__property TApdOnAskForStringFinish OnAskForExtensionFinish = {read=FOnAskForExtensionFinish, write=FOnAskForExtensionFinish};
	__property TApdOnAskForIntegerFinish OnAskForListFinish = {read=FOnAskForListFinish, write=FOnAskForListFinish};
	__property TApdOnAskForStringFinish OnAskForPhoneNumberFinish = {read=FOnAskForPhoneNumberFinish, write=FOnAskForPhoneNumberFinish};
	__property TApdOnAskForStringFinish OnAskForSpellingFinish = {read=FOnAskForSpellingFinish, write=FOnAskForSpellingFinish};
	__property TApdOnAskForDateTimeFinish OnAskForTimeFinish = {read=FOnAskForTimeFinish, write=FOnAskForTimeFinish};
	__property TApdOnAskForBooleanFinish OnAskForYesNoFinish = {read=FOnAskForYesNoFinish, write=FOnAskForYesNoFinish};
	__property Classes::TNotifyEvent OnTapiDisconnect = {read=FOnTapiDisconnect, write=FOnTapiDisconnect};
	__property SelectedDevice ;
	__property ComPort ;
	__property StatusDisplay ;
	__property TapiLog ;
	__property AnswerOnRing  = {default=2};
	__property RetryWait  = {default=60};
	__property MaxAttempts  = {default=3};
	__property ShowTapiDevices ;
	__property ShowPorts ;
	__property EnableVoice ;
	__property FilterUnsupportedDevices  = {default=1};
	__property OnTapiStatus ;
	__property OnTapiLog ;
	__property OnTapiPortOpen ;
	__property OnTapiPortClose ;
	__property OnTapiConnect ;
	__property OnTapiFail ;
	__property OnTapiDTMF ;
	__property OnTapiCallerID ;
	__property OnTapiWaveNotify ;
	__property OnTapiWaveSilence ;
};


class DELPHICLASS TApdSapiPhone;
class PASCALIMPLEMENTATION TApdSapiPhone : public TApdCustomSapiPhone 
{
	typedef TApdCustomSapiPhone inherited;
	
__published:
	__property NoAnswerMax ;
	__property NoAnswerTime ;
	__property NumDigits ;
	__property Options ;
	__property SapiEngine ;
	__property SelectedDevice ;
	__property ComPort ;
	__property StatusDisplay ;
	__property TapiLog ;
	__property AnswerOnRing  = {default=2};
	__property RetryWait  = {default=60};
	__property MaxAttempts  = {default=3};
	__property ShowTapiDevices ;
	__property ShowPorts ;
	__property EnableVoice ;
	__property FilterUnsupportedDevices  = {default=1};
	__property OnTapiStatus ;
	__property OnTapiLog ;
	__property OnTapiPortOpen ;
	__property OnTapiPortClose ;
	__property OnTapiConnect ;
	__property OnTapiFail ;
	__property OnTapiDTMF ;
	__property OnTapiCallerID ;
	__property OnTapiWaveNotify ;
	__property OnTapiWaveSilence ;
public:
	#pragma option push -w-inl
	/* TApdCustomSapiPhone.Create */ inline __fastcall virtual TApdSapiPhone(Classes::TComponent* AOwner) : TApdCustomSapiPhone(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomSapiPhone.Destroy */ inline __fastcall virtual ~TApdSapiPhone(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint ApdSapiAskOperator = 0xfffffffd;
static const Shortint ApdSapiAskHangUp = 0xfffffffc;
static const Shortint ApdSapiAskBack = 0xfffffffb;
static const Shortint ApdSapiAskWhere = 0xfffffff6;
static const Shortint ApdSapiAskHelp = 0xfffffff5;
static const Shortint ApdSapiAskRepeat = 0xc;
static const Shortint ApdSapiAskSpeakFaster = 0xd;
static const Shortint ApdSapiAskSpeakSlower = 0xfffffff2;
static const Shortint ApdSapiAbort = 0xffffff9e;
static const Shortint ApdSapiTimeout = 0xffffff9d;
static const Shortint ApdSapiSpeedChange = 0x19;
static const Shortint ApdSapiConnect = 0x1;
static const Shortint ApdSapiDisConnect = 0x2;
static const Shortint ApdTCR_ABORT = 0xffffffff;
static const Shortint ApdTCR_NORESPONSE = 0xfffffffe;
static const Shortint ApdTCR_ASKOPERATOR = 0xfffffffd;
static const Shortint ApdTCR_ASKHANGUP = 0xfffffffc;
static const Shortint ApdTCR_ASKBACK = 0xfffffffb;
static const Shortint ApdTCR_ASKWHERE = 0xfffffff6;
static const Shortint ApdTCR_ASKHELP = 0xfffffff5;
static const Shortint ApdTCR_ASKREPEAT = 0xfffffff4;
static const Shortint ApdTCR_ASKSPEAKFASTER = 0xfffffff3;
static const Shortint ApdTCR_ASKSPEAKSLOWER = 0xfffffff2;

}	/* namespace Adsapiph */
using namespace Adsapiph;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdSapiPh
