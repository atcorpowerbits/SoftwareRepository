// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdSapiEn.pas' rev: 6.00

#ifndef AdSapiEnHPP
#define AdSapiEnHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ComObj.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Contnrs.hpp>	// Pascal unit
#include <AdSapiGr.hpp>	// Pascal unit
#include <AdISapi.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <StdVCL.hpp>	// Pascal unit
#include <OleCtrls.hpp>	// Pascal unit
#include <OleServer.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <ActiveX.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adsapien
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TApdSapiDuplex { sdFull, sdHalf, sdHalfDelayed };
#pragma option pop

#pragma option push -b-
enum TApdSapiWaitMode { wmNone, wmWaitSpeaking, wmWaitListening, wmRestoreListen };
#pragma option pop

#pragma option push -b-
enum TApdCharacterSet { csText, csIPAPhonetic, csEnginePhonetic };
#pragma option pop

#pragma option push -b-
enum AdSapiEn__1 { toTagged };
#pragma option pop

typedef Set<AdSapiEn__1, toTagged, toTagged>  TApdTTSOptions;

#pragma option push -b-
enum TApdTTSAge { tsBaby, tsToddler, tsChild, tsAdolescent, tsAdult, tsElderly, tsUnknown };
#pragma option pop

#pragma option push -b-
enum AdSapiEn__2 { tfAnyWord, tfVolume, tfSpeed, tfPitch, tfTagged, tfIPAUnicode, tfVisual, tfWordPosition, tfPCOptimized, tfPhoneOptimized, tfFixedAudio, tfSingleInstance, tfThreadSafe, tfIPATextData, tfPreferred, tfTransplanted, tfSAPI4 };
#pragma option pop

typedef Set<AdSapiEn__2, tfAnyWord, tfSAPI4>  TApdTTSFeatures;

#pragma option push -b-
enum TApdTTSGender { tgNeutral, tgFemale, tgMale, tgUnknown };
#pragma option pop

#pragma option push -b-
enum AdSapiEn__3 { tiLexPronounce, tiTTSAttributes, tiTTSCentral, tiTTSDialogs, tiAttributes, tiIAttributes, tiLexPronounce2 };
#pragma option pop

typedef Set<AdSapiEn__3, tiLexPronounce, tiLexPronounce2>  TApdTTSInterfaces;

#pragma option push -b-
enum AdSapiEn__4 { sfIndepSpeaker, sfIndepMicrophone, sfTrainWord, sfTrainPhonetic, sfWildcard, sfAnyWord, sfPCOptimized, sfPhoneOptimized, sfGramList, sfGramLink, sfMultiLingual, sfGramRecursive, sfIPAUnicode, sfSingleInstance, sfThreadSafe, sfFixedAudio, sfIPAWord, sfSAPI4 };
#pragma option pop

typedef Set<AdSapiEn__4, sfIndepSpeaker, sfSAPI4>  TApdSRFeatures;

#pragma option push -b-
enum AdSapiEn__5 { sgCFG, sgDictation, sgLimitedDomain };
#pragma option pop

typedef Set<AdSapiEn__5, sgCFG, sgLimitedDomain>  TApdSRGrammars;

#pragma option push -b-
enum AdSapiEn__6 { siLexPronounce, siSRAttributes, siSRCentral, siSRGramCommon, siSRDialogs, siSRGramCFG, siSRGramDictation, siSRGramInsertionGui, siSREsBasic, siSREsMerge, siSREsAudio, siSREsCorrection, siSREsEval, siSREsGraph, siSREsMemory, siSREsModifyGui, siSREsSpeaker, siSRSpeaker, siSREsScores, siSREsAudioEx, siSRGramLexPron, siSREsGraphEx, siLexPronounce2, siAttributes, siSRSpeaker2, siSRDialogs2 };
#pragma option pop

typedef Set<AdSapiEn__6, siLexPronounce, siSRDialogs2>  TApdSRInterfaces;

#pragma option push -b-
enum TApdSRSequences { ssDiscrete, ssContinuous, ssWordSpot, ssContCFGDiscDict, ssUnknown };
#pragma option pop

#pragma option push -b-
enum TApdSRInterferenceType { itAudioStarted, itAudioStopped, itDeviceOpened, itDeviceClosed, itNoise, itTooLoud, itTooQuiet, itUnknown };
#pragma option pop

#pragma option push -b-
enum AdSapiEn__7 { ttCurrentMic, ttCurrentGrammar, ttGeneral };
#pragma option pop

typedef Set<AdSapiEn__7, ttCurrentMic, ttGeneral>  TApdSRTrainingType;

typedef void __fastcall (__closure *TApdOnSapiError)(System::TObject* Sender, unsigned Error, const AnsiString Details, const AnsiString Message);

typedef void __fastcall (__closure *TApdSapiNotifyEvent)(System::TObject* Sender);

typedef void __fastcall (__closure *TApdSRInterferenceEvent)(System::TObject* Sender, TApdSRInterferenceType InterferenceType);

typedef void __fastcall (__closure *TApdSRPhraseFinishEvent)(System::TObject* Sender, const AnsiString Phrase);

typedef void __fastcall (__closure *TApdSRPhraseHypothesisEvent)(System::TObject* Sender, const AnsiString Phrase);

typedef void __fastcall (__closure *TApdSRTrainingRequestedEvent)(System::TObject* Sender, TApdSRTrainingType Training);

typedef void __fastcall (__closure *TApdSRVUMeterEvent)(System::TObject* Sender, int Level);

typedef void __fastcall (__closure *TApdSSAttributeChanged)(System::TObject* Sender, int Attribute);

typedef void __fastcall (__closure *TApdPhraseFinishMethod)(System::TObject* Sender, AnsiString Phrase, int Results);

typedef TApdPhraseFinishMethod *PApdPhraseFinishMethod;

#pragma option push -b-
enum TApdRegisteredEventTypes { etPhraseFinish };
#pragma option pop

struct TApdRegisteredEvent;
typedef TApdRegisteredEvent *PApdRegisteredEvent;

struct TApdRegisteredEvent
{
	TApdPhraseFinishMethod CallBack;
	TApdRegisteredEventTypes EventType;
	bool Active;
} ;

class DELPHICLASS EApdSapiEngineException;
class PASCALIMPLEMENTATION EApdSapiEngineException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
private:
	int FErrorCode;
	
public:
	__fastcall EApdSapiEngineException(const int ErrCode, const AnsiString Msg);
	
__published:
	__property int ErrorCode = {read=FErrorCode, nodefault};
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EApdSapiEngineException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EApdSapiEngineException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EApdSapiEngineException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EApdSapiEngineException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EApdSapiEngineException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EApdSapiEngineException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EApdSapiEngineException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EApdSapiEngineException(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdSSVoices;
class PASCALIMPLEMENTATION TApdSSVoices : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	AnsiString operator[](int x) { return ModeName[x]; }
	
private:
	int FCurrentVoice;
	Adisapi::TDirectSS* FiDirectSS;
	
protected:
	bool __fastcall CheckIndex(int x);
	TApdTTSAge __fastcall GetAge(int x);
	int __fastcall GetCount(void);
	int __fastcall GetCurrentVoice(void);
	AnsiString __fastcall GetDialect(int x);
	int __fastcall GetEngineFeatures(int x);
	AnsiString __fastcall GetEngineID(int x);
	TApdTTSFeatures __fastcall GetFeatures(int x);
	TApdTTSGender __fastcall GetGender(int x);
	TApdTTSInterfaces __fastcall GetInterfaces(int x);
	int __fastcall GetLanguageID(int x);
	AnsiString __fastcall GetMfgName(int x);
	AnsiString __fastcall GetModeID(int x);
	AnsiString __fastcall GetModeName(int x);
	AnsiString __fastcall GetProductName(int x);
	AnsiString __fastcall GetSpeaker(int x);
	AnsiString __fastcall GetStyle(int x);
	void __fastcall SetCurrentVoice(int v);
	
public:
	int __fastcall Find(AnsiString Criteria);
	__property TApdTTSAge Age[int x] = {read=GetAge};
	__property AnsiString Dialect[int x] = {read=GetDialect};
	__property int EngineFeatures[int x] = {read=GetEngineFeatures};
	__property AnsiString EngineID[int x] = {read=GetEngineID};
	__property TApdTTSFeatures Features[int x] = {read=GetFeatures};
	__property TApdTTSGender Gender[int x] = {read=GetGender};
	__property TApdTTSInterfaces Interfaces[int x] = {read=GetInterfaces};
	__property int LanguageID[int x] = {read=GetLanguageID};
	__property AnsiString MfgName[int x] = {read=GetMfgName};
	__property AnsiString ModeID[int x] = {read=GetModeID};
	__property AnsiString ModeName[int x] = {read=GetModeName/*, default*/};
	__property AnsiString ProductName[int x] = {read=GetProductName};
	__property AnsiString Speaker[int x] = {read=GetSpeaker};
	__property AnsiString Style[int x] = {read=GetStyle};
	
__published:
	__property int Count = {read=GetCount, nodefault};
	__property int CurrentVoice = {read=GetCurrentVoice, write=SetCurrentVoice, nodefault};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TApdSSVoices(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TApdSSVoices(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdSREngines;
class PASCALIMPLEMENTATION TApdSREngines : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	AnsiString operator[](int x) { return ModeName[x]; }
	
private:
	int FCurrentEngine;
	Adisapi::TDirectSR* FiDirectSR;
	
protected:
	bool __fastcall CheckIndex(int x);
	int __fastcall GetCount(void);
	int __fastcall GetCurrentEngine(void);
	AnsiString __fastcall GetDialect(int x);
	int __fastcall GetEngineFeatures(int x);
	AnsiString __fastcall GetEngineId(int x);
	TApdSRFeatures __fastcall GetFeatures(int x);
	TApdSRGrammars __fastcall GetGrammars(int x);
	TApdSRInterfaces __fastcall GetInterfaces(int x);
	int __fastcall GetLanguageID(int x);
	int __fastcall GetMaxWordsState(int x);
	int __fastcall GetMaxWordsVocab(int x);
	AnsiString __fastcall GetMfgName(int x);
	AnsiString __fastcall GetModeID(int x);
	AnsiString __fastcall GetModeName(int x);
	AnsiString __fastcall GetProductName(int x);
	TApdSRSequences __fastcall GetSequencing(int x);
	void __fastcall SetCurrentEngine(int v);
	
public:
	__property AnsiString Dialect[int x] = {read=GetDialect};
	__property int EngineFeatures[int x] = {read=GetEngineFeatures};
	__property AnsiString EngineID[int x] = {read=GetEngineId};
	__property TApdSRFeatures Features[int x] = {read=GetFeatures};
	__property TApdSRGrammars Grammars[int x] = {read=GetGrammars};
	__property TApdSRInterfaces Interfaces[int x] = {read=GetInterfaces};
	__property int LanguageID[int x] = {read=GetLanguageID};
	__property int MaxWordsState[int x] = {read=GetMaxWordsState};
	__property int MaxWordsVocab[int x] = {read=GetMaxWordsVocab};
	__property AnsiString MfgName[int x] = {read=GetMfgName};
	__property AnsiString ModeID[int x] = {read=GetModeID};
	__property AnsiString ModeName[int x] = {read=GetModeName/*, default*/};
	__property AnsiString ProductName[int x] = {read=GetProductName};
	__property TApdSRSequences Sequencing[int x] = {read=GetSequencing};
	
__published:
	__property int Count = {read=GetCount, nodefault};
	__property int CurrentEngine = {read=GetCurrentEngine, write=SetCurrentEngine, nodefault};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TApdSREngines(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TApdSREngines(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdCustomSapiEngine;
class PASCALIMPLEMENTATION TApdCustomSapiEngine : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
private:
	Adisapi::TDirectSR* FiDirectSR;
	Adisapi::TDirectSS* FiDirectSS;
	TApdCharacterSet FCharSet;
	bool FDictation;
	bool FSpeaking;
	bool FListening;
	Word FSRAmplitude;
	int FSRAutoGain;
	TApdTTSOptions FTTSOptions;
	Classes::TStringList* FWordList;
	TApdSREngines* FSREngines;
	TApdSSVoices* FSSVoices;
	Classes::TList* FPhraseFinishClients;
	HWND FHandle;
	bool FAutoTrain;
	TApdSapiDuplex FDuplex;
	TApdSapiWaitMode FWaitMode;
	bool FInitSR;
	bool FInitSS;
	TApdSRInterferenceEvent FOnInterference;
	TApdSRPhraseFinishEvent FOnPhraseFinish;
	TApdSRPhraseHypothesisEvent FOnPhraseHypothesis;
	TApdSapiNotifyEvent FOnSpeakStart;
	TApdSapiNotifyEvent FOnSpeakStop;
	TApdOnSapiError FOnSRError;
	TApdOnSapiError FOnSRWarning;
	TApdSSAttributeChanged FOnSSAttributeChanged;
	TApdOnSapiError FOnSSError;
	TApdOnSapiError FOnSSWarning;
	TApdSRTrainingRequestedEvent FOnTrainingRequested;
	TApdSRVUMeterEvent FOnVUMeter;
	
protected:
	Word __fastcall GetSRAmplitude(void);
	int __fastcall GetSRAutoGain(void);
	void __fastcall InitializeSpeaking(int &CSet, int &Options);
	virtual void __fastcall Loaded(void);
	void __fastcall SetAutoTrain(bool v);
	void __fastcall SetCharSet(TApdCharacterSet v);
	void __fastcall SetDictation(bool v);
	void __fastcall SetDuplex(TApdSapiDuplex v);
	void __fastcall SetInitSR(const bool v);
	void __fastcall SetInitSS(const bool v);
	void __fastcall SetListening(bool v);
	void __fastcall SetSpeaking(bool v);
	void __fastcall SetSRAutoGain(int Value);
	void __fastcall SetTTSOptions(TApdTTSOptions v);
	void __fastcall SetWordList(Classes::TStringList* v);
	void __fastcall TriggerAudioStart(System::TObject* Sender, int hi, int lo);
	void __fastcall TriggerAudioStop(System::TObject* Sender, int hi, int lo);
	void __fastcall TriggerInterference(System::TObject* Sender, int beginhi, int beginlo, int endhi, int endlo, int type_);
	void __fastcall TriggerPhraseFinish(System::TObject* Sender, int flags, int beginhi, int beginlo, int endhi, int endlo, const WideString Phrase, const WideString parsed, int results);
	void __fastcall TriggerPhraseFinishClients(AnsiString Phrase, int Results);
	void __fastcall TriggerPhraseHypothesis(System::TObject* Sender, int flags, int beginhi, int beginlo, int endhi, int endlo, const WideString Phrase, int results);
	void __fastcall TriggerSpeakStart(System::TObject* Sender, int beginhi, int beginlo);
	void __fastcall TriggerSpeakStop(System::TObject* Sender, int beginhi, int beginlo, int endhi, int endlo);
	void __fastcall TriggerSRError(System::TObject* Sender, unsigned Error, const WideString Details, const WideString Message);
	void __fastcall TriggerSRWarning(System::TObject* Sender, unsigned Error, const WideString Details, const WideString Message);
	void __fastcall TriggerSSAttribChanged(System::TObject* Sender, int Attribute);
	void __fastcall TriggerSSError(System::TObject* Sender, unsigned Error, const WideString Details, const WideString Message);
	void __fastcall TriggerSSWarning(System::TObject* Sender, unsigned Error, const WideString Details, const WideString Message);
	void __fastcall TriggerTrainingRequested(System::TObject* Sender, int train);
	void __fastcall TriggerVUMeter(System::TObject* Sender, int beginhi, int beginlo, int level);
	void __fastcall WndProc(Messages::TMessage &Message);
	
public:
	__fastcall virtual TApdCustomSapiEngine(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomSapiEngine(void);
	void __fastcall CheckError(unsigned ErrorCode);
	void __fastcall DeRegisterPhraseFinishHook(TApdPhraseFinishMethod PhraseFinishMethod);
	void __fastcall InitializeSapi(void);
	void __fastcall InitializeSR(void);
	void __fastcall InitializeSS(void);
	bool __fastcall IsSapi4Installed(void);
	void __fastcall Listen(void);
	void __fastcall PauseListening(void);
	void __fastcall PauseSpeaking(void);
	void __fastcall RegisterPhraseFinishHook(TApdPhraseFinishMethod PhraseFinishMethod);
	void __fastcall ResumeListening(void);
	void __fastcall ResumeSpeaking(void);
	void __fastcall ShowAboutDlg(const AnsiString Caption);
	void __fastcall ShowGeneralDlg(const AnsiString Caption);
	void __fastcall ShowLexiconDlg(const AnsiString Caption);
	void __fastcall ShowSRAboutDlg(const AnsiString Caption);
	void __fastcall ShowSRGeneralDlg(const AnsiString Caption);
	void __fastcall ShowSRLexiconDlg(const AnsiString Caption);
	void __fastcall ShowSSAboutDlg(const AnsiString Caption);
	void __fastcall ShowSSGeneralDlg(const AnsiString Caption);
	void __fastcall ShowSSLexiconDlg(const AnsiString Caption);
	void __fastcall ShowTrainGeneralDlg(const AnsiString Caption);
	void __fastcall ShowTrainMicDlg(const AnsiString Caption);
	void __fastcall ShowTranslateDlg(const AnsiString Caption);
	void __fastcall Speak(AnsiString Text);
	void __fastcall SpeakFile(AnsiString FileName);
	void __fastcall SpeakFileToFile(const AnsiString InFile, const AnsiString OutFile);
	void __fastcall SpeakStream(Classes::TStream* Stream, AnsiString FileName);
	void __fastcall SpeakToFile(const AnsiString Text, const AnsiString FileName);
	void __fastcall StopListening(void);
	void __fastcall StopSpeaking(void);
	void __fastcall WaitUntilDoneSpeaking(void);
	__property Adisapi::TDirectSR* DirectSR = {read=FiDirectSR, write=FiDirectSR};
	__property Adisapi::TDirectSS* DirectSS = {read=FiDirectSS, write=FiDirectSS};
	__property bool InitSR = {read=FInitSR, write=SetInitSR, default=1};
	__property bool InitSS = {read=FInitSS, write=SetInitSS, default=1};
	__property bool Listening = {read=FListening, write=SetListening, nodefault};
	__property bool Speaking = {read=FSpeaking, write=SetSpeaking, nodefault};
	__property TApdSREngines* SREngines = {read=FSREngines, write=FSREngines};
	__property TApdSSVoices* SSVoices = {read=FSSVoices, write=FSSVoices};
	
__published:
	__property bool AutoTrain = {read=FAutoTrain, write=SetAutoTrain, default=0};
	__property TApdCharacterSet CharSet = {read=FCharSet, write=SetCharSet, nodefault};
	__property bool Dictation = {read=FDictation, write=SetDictation, nodefault};
	__property TApdSapiDuplex Duplex = {read=FDuplex, write=SetDuplex, default=2};
	__property Word SRAmplitude = {read=GetSRAmplitude, nodefault};
	__property int SRAutoGain = {read=GetSRAutoGain, write=SetSRAutoGain, nodefault};
	__property TApdTTSOptions TTSOptions = {read=FTTSOptions, write=SetTTSOptions, nodefault};
	__property Classes::TStringList* WordList = {read=FWordList, write=SetWordList};
	__property TApdSRInterferenceEvent OnInterference = {read=FOnInterference, write=FOnInterference};
	__property TApdSRPhraseFinishEvent OnPhraseFinish = {read=FOnPhraseFinish, write=FOnPhraseFinish};
	__property TApdSRPhraseHypothesisEvent OnPhraseHypothesis = {read=FOnPhraseHypothesis, write=FOnPhraseHypothesis};
	__property TApdSapiNotifyEvent OnSpeakStart = {read=FOnSpeakStart, write=FOnSpeakStart};
	__property TApdSapiNotifyEvent OnSpeakStop = {read=FOnSpeakStop, write=FOnSpeakStop};
	__property TApdOnSapiError OnSRError = {read=FOnSRError, write=FOnSRError};
	__property TApdOnSapiError OnSRWarning = {read=FOnSRWarning, write=FOnSRWarning};
	__property TApdSSAttributeChanged OnSSAttributeChanged = {read=FOnSSAttributeChanged, write=FOnSSAttributeChanged};
	__property TApdOnSapiError OnSSError = {read=FOnSSError, write=FOnSSError};
	__property TApdOnSapiError OnSSWarning = {read=FOnSSWarning, write=FOnSSWarning};
	__property TApdSRTrainingRequestedEvent OnTrainingRequested = {read=FOnTrainingRequested, write=FOnTrainingRequested};
	__property TApdSRVUMeterEvent OnVUMeter = {read=FOnVUMeter, write=FOnVUMeter};
};


class DELPHICLASS TApdSapiEngine;
class PASCALIMPLEMENTATION TApdSapiEngine : public TApdCustomSapiEngine 
{
	typedef TApdCustomSapiEngine inherited;
	
__published:
	__property CharSet ;
	__property Dictation ;
	__property SRAmplitude ;
	__property SRAutoGain ;
	__property TTSOptions ;
	__property WordList ;
	__property OnInterference ;
	__property OnPhraseFinish ;
	__property OnPhraseHypothesis ;
	__property OnSpeakStart ;
	__property OnSpeakStop ;
	__property OnSRError ;
	__property OnSRWarning ;
	__property OnSSAttributeChanged ;
	__property OnSSError ;
	__property OnSSWarning ;
	__property OnTrainingRequested ;
	__property OnVUMeter ;
public:
	#pragma option push -w-inl
	/* TApdCustomSapiEngine.Create */ inline __fastcall virtual TApdSapiEngine(Classes::TComponent* AOwner) : TApdCustomSapiEngine(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomSapiEngine.Destroy */ inline __fastcall virtual ~TApdSapiEngine(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint ApdCHARSET_TEXT = 0x0;
static const Shortint ApdCHARSET_IPAPHONETIC = 0x1;
static const Shortint ApdCHARSET_ENGINEPHONETIC = 0x2;
static const Shortint ApdTTSDATAFLAG_TAGGED = 0x1;
static const Shortint ApdTTSAGE_BABY = 0x1;
static const Shortint ApdTTSAGE_TODDLER = 0x3;
static const Shortint ApdTTSAGE_CHILD = 0x6;
static const Shortint ApdTTSAGE_ADOLESCENT = 0xe;
static const Shortint ApdTTSAGE_ADULT = 0x1e;
static const Shortint ApdTTSAGE_ELDERLY = 0x46;
static const Shortint ApdTTSFEATURE_ANYWORD = 0x1;
static const Shortint ApdTTSFEATURE_VOLUME = 0x2;
static const Shortint ApdTTSFEATURE_SPEED = 0x4;
static const Shortint ApdTTSFEATURE_PITCH = 0x8;
static const Shortint ApdTTSFEATURE_TAGGED = 0x10;
static const Shortint ApdTTSFEATURE_IPAUNICODE = 0x20;
static const Shortint ApdTTSFEATURE_VISUAL = 0x40;
static const Byte ApdTTSFEATURE_WORDPOSITION = 0x80;
static const Word ApdTTSFEATURE_PCOPTIMIZED = 0x100;
static const Word ApdTTSFEATURE_PHONEOPTIMIZED = 0x200;
static const Word ApdTTSFEATURE_FIXEDAUDIO = 0x400;
static const Word ApdTTSFEATURE_SINGLEINSTANCE = 0x800;
static const Word ApdTTSFEATURE_THREADSAFE = 0x1000;
static const Word ApdTTSFEATURE_IPATEXTDATA = 0x2000;
static const Word ApdTTSFEATURE_PREFERRED = 0x4000;
static const Word ApdTTSFEATURE_TRANSPLANTED = 0x8000;
static const int ApdTTSFEATURE_SAPI4 = 0x10000;
static const Shortint ApdGENDER_NEUTRAL = 0x0;
static const Shortint ApdGENDER_FEMALE = 0x1;
static const Shortint ApdGENDER_MALE = 0x2;
static const Shortint ApdTTSI_ILEXPRONOUNCE = 0x1;
static const Shortint ApdTTSI_ITTSATTRIBUTES = 0x2;
static const Shortint ApdTTSI_ITTSCENTRAL = 0x4;
static const Shortint ApdTTSI_ITTSDIALOGS = 0x8;
static const Shortint ApdTTSI_ATTRIBUTES = 0x10;
static const Shortint ApdTTSI_IATTRIBUTES = 0x10;
static const Shortint ApdTTSI_ILEXPRONOUNCE2 = 0x20;
static const Shortint ApdSRFEATURE_INDEPSPEAKER = 0x1;
static const Shortint ApdSRFEATURE_INDEPMICROPHONE = 0x2;
static const Shortint ApdSRFEATURE_TRAINWORD = 0x4;
static const Shortint ApdSRFEATURE_TRAINPHONETIC = 0x8;
static const Shortint ApdSRFEATURE_WILDCARD = 0x10;
static const Shortint ApdSRFEATURE_ANYWORD = 0x20;
static const Shortint ApdSRFEATURE_PCOPTIMIZED = 0x40;
static const Byte ApdSRFEATURE_PHONEOPTIMIZED = 0x80;
static const Word ApdSRFEATURE_GRAMLIST = 0x100;
static const Word ApdSRFEATURE_GRAMLINK = 0x200;
static const Word ApdSRFEATURE_MULTILINGUAL = 0x400;
static const Word ApdSRFEATURE_GRAMRECURSIVE = 0x800;
static const Word ApdSRFEATURE_IPAUNICODE = 0x1000;
static const Word ApdSRFEATURE_SINGLEINSTANCE = 0x2000;
static const Word ApdSRFEATURE_THREADSAFE = 0x4000;
static const Word ApdSRFEATURE_FIXEDAUDIO = 0x8000;
static const int ApdSRFEATURE_IPAWORD = 0x10000;
static const int ApdSRFEATURE_SAPI4 = 0x20000;
static const Shortint ApdSRGRAM_CFG = 0x1;
static const Shortint ApdSRGRAM_DICTATION = 0x2;
static const Shortint ApdSRGRAM_LIMITEDDOMAIN = 0x4;
static const Shortint ApdSRI_ILEXPRONOUNCE = 0x1;
static const Shortint ApdSRI_ISRATTRIBUTES = 0x2;
static const Shortint ApdSRI_ISRCENTRAL = 0x4;
static const Shortint ApdSRI_ISRDIALOGS = 0x8;
static const Shortint ApdSRI_ISRGRAMCOMMON = 0x10;
static const Shortint ApdSRI_ISRGRAMCFG = 0x20;
static const Shortint ApdSRI_ISRGRAMDICTATION = 0x40;
static const Byte ApdSRI_ISRGRAMINSERTIONGUI = 0x80;
static const Word ApdSRI_ISRESBASIC = 0x100;
static const Word ApdSRI_ISRESMERGE = 0x200;
static const Word ApdSRI_ISRESAUDIO = 0x400;
static const Word ApdSRI_ISRESCORRECTION = 0x800;
static const Word ApdSRI_ISRESEVAL = 0x1000;
static const Word ApdSRI_ISRESGRAPH = 0x2000;
static const Word ApdSRI_ISRESMEMORY = 0x4000;
static const Word ApdSRI_ISRESMODIFYGUI = 0x8000;
static const int ApdSRI_ISRESSPEAKER = 0x10000;
static const int ApdSRI_ISRSPEAKER = 0x20000;
static const int ApdSRI_ISRESSCORES = 0x40000;
static const int ApdSRI_ISRESAUDIOEX = 0x80000;
static const int ApdSRI_ISRGRAMLEXPRON = 0x100000;
static const int ApdSRI_ISRRESGRAPHEX = 0x200000;
static const int ApdSRI_ILEXPRONOUNCE2 = 0x400000;
static const int ApdSRI_IATTRIBUTES = 0x800000;
static const int ApdSRI_ISRSPEAKER2 = 0x1000000;
static const int ApdSRI_ISRDIALOGS2 = 0x2000000;
static const Shortint ApdSRSEQUENCE_DISCRETE = 0x0;
static const Shortint ApdSRSEQUENCE_CONTINUOUS = 0x1;
static const Shortint ApdSRSEQUENCE_WORDSPOT = 0x2;
static const Shortint ApdSRSEQUENCE_CONTCFGDISCDICT = 0x3;
static const Shortint ApdSRMSGINT_NOISE = 0x1;
static const Shortint ApdSRMSGINT_NOSIGNAL = 0x2;
static const Shortint ApdSRMSGINT_TOOLOUD = 0x3;
static const Shortint ApdSRMSGINT_TOOQUIET = 0x4;
static const Shortint ApdSRMSGINT_AUDIODATA_STOPPED = 0x5;
static const Shortint ApdSRMSGINT_AUDIODATA_STARTED = 0x6;
static const Shortint ApdSRMSGINT_IAUDIO_STARTED = 0x7;
static const Shortint ApdSRMSGINT_IAUDIO_STOPPED = 0x8;
static const Shortint ApdSRGNSTRAIN_GENERAL = 0x1;
static const Shortint ApdSRGNSTRAIN_GRAMMAR = 0x2;
static const Shortint ApdSRGNSTRAIN_MICROPHONE = 0x4;
static const Shortint ApdTTSERR_NONE = 0x0;
static const unsigned ApdTTSERR_INVALIDINTERFACE = 0x80004002;
static const unsigned ApdTTSERR_OUTOFDISK = 0x80040205;
static const unsigned ApdTTSERR_NOTSUPPORTED = 0x80004001;
static const unsigned ApdTTSERR_VALUEOUTOFRANGE = 0x8000ffff;
static const unsigned ApdTTSERR_INVALIDWINDOW = 0x8004000f;
static const unsigned ApdTTSERR_INVALIDPARAM = 0x80070057;
static const unsigned ApdTTSERR_INVALIDMODE = 0x80040206;
static const unsigned ApdTTSERR_INVALIDKEY = 0x80040209;
static const unsigned ApdTTSERR_WAVEFORMATNOTSUPPORTED = 0x80040202;
static const unsigned ApdTTSERR_INVALIDCHAR = 0x80040208;
static const unsigned ApdTTSERR_QUEUEFULL = 0x8004020a;
static const unsigned ApdTTSERR_WAVEDEVICEBUSY = 0x80040203;
static const unsigned ApdTTSERR_NOTPAUSED = 0x80040501;
static const unsigned ApdTTSERR_ALREADYPAUSED = 0x80040502;
static const Shortint ApdSRERR_NONE = 0x0;
static const unsigned ApdSRERR_OUTOFDISK = 0x80040205;
static const unsigned ApdSRERR_NOTSUPPORTED = 0x80004001;
static const unsigned ApdSRERR_NOTENOUGHDATA = 0x80040201;
static const unsigned ApdSRERR_VALUEOUTOFRANGE = 0x8000ffff;
static const unsigned ApdSRERR_GRAMMARTOOCOMPLEX = 0x80040406;
static const unsigned ApdSRERR_GRAMMARWRONGTYPE = 0x80040407;
static const unsigned ApdSRERR_INVALIDWINDOW = 0x8004000f;
static const unsigned ApdSRERR_INVALIDPARAM = 0x80070057;
static const unsigned ApdSRERR_INVALIDMODE = 0x80040206;
static const unsigned ApdSRERR_TOOMANYGRAMMARS = 0x8004040b;
static const unsigned ApdSRERR_INVALIDLIST = 0x80040207;
static const unsigned ApdSRERR_WAVEDEVICEBUSY = 0x80040203;
static const unsigned ApdSRERR_WAVEFORMATNOTSUPPORTED = 0x80040202;
static const unsigned ApdSRERR_INVALIDCHAR = 0x80040208;
static const unsigned ApdSRERR_GRAMTOOCOMPLEX = 0x80040406;
static const unsigned ApdSRERR_GRAMTOOLARGE = 0x80040411;
static const unsigned ApdSRERR_INVALIDINTERFACE = 0x80004002;
static const unsigned ApdSRERR_INVALIDKEY = 0x80040209;
static const unsigned ApdSRERR_INVALIDFLAG = 0x80040204;
static const unsigned ApdSRERR_GRAMMARERROR = 0x80040416;
static const unsigned ApdSRERR_INVALIDRULE = 0x80040417;
static const unsigned ApdSRERR_RULEALREADYACTIVE = 0x80040418;
static const unsigned ApdSRERR_RULENOTACTIVE = 0x80040419;
static const unsigned ApdSRERR_NOUSERSELECTED = 0x8004041a;
static const unsigned ApdSRERR_BAD_PRONUNCIATION = 0x8004041b;
static const unsigned ApdSRERR_DATAFILEERROR = 0x8004041c;
static const unsigned ApdSRERR_GRAMMARALREADYACTIVE = 0x8004041d;
static const unsigned ApdSRERR_GRAMMARNOTACTIVE = 0x8004041e;
static const unsigned ApdSRERR_GLOBALGRAMMARALREADYACTIVE = 0x8004041f;
static const unsigned ApdSRERR_LANGUAGEMISMATCH = 0x80040420;
static const unsigned ApdSRERR_MULTIPLELANG = 0x80040421;
static const unsigned ApdSRERR_LDGRAMMARNOWORDS = 0x80040422;
static const unsigned ApdSRERR_NOLEXICON = 0x80040423;
static const unsigned ApdSRERR_SPEAKEREXISTS = 0x80040424;
static const unsigned ApdSRERR_GRAMMARENGINEMISMATCH = 0x80040425;
static const unsigned ApdSRERR_BOOKMARKEXISTS = 0x80040426;
static const unsigned ApdSRERR_BOOKMARKDOESNOTEXIST = 0x80040427;
static const unsigned ApdSRERR_MICWIZARDCANCELED = 0x80040428;
static const unsigned ApdSRERR_WORDTOOLONG = 0x80040429;
static const unsigned ApdSRERR_BAD_WORD = 0x8004042a;
static const unsigned ApdE_WRONGTYPE = 0x8004020c;
static const unsigned ApdE_BUFFERTOOSMALL = 0x8004020d;
extern PACKAGE TApdCustomSapiEngine* __fastcall SearchSapiEngine(const Classes::TComponent* C);

}	/* namespace Adsapien */
using namespace Adsapien;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdSapiEn
