// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdISapi.pas' rev: 6.00

#ifndef AdISapiHPP
#define AdISapiHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit
#include <StdVCL.hpp>	// Pascal unit
#include <OleServer.hpp>	// Pascal unit
#include <OleCtrls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <ActiveX.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adisapi
{
//-- type declarations -------------------------------------------------------
typedef __int64 QWORD;

#pragma pack(push, 4)
struct SDATA
{
	void *pData;
	unsigned dwSize;
} ;
#pragma pack(pop)

typedef SDATA  TSData;

struct LANGUAGEW;
typedef LANGUAGEW *PLanguageW;

#pragma pack(push, 2)
struct LANGUAGEW
{
	Word LanguageID;
	wchar_t szDialect[64];
} ;
#pragma pack(pop)

typedef LANGUAGEW  TLanguageW;

typedef unsigned SRGRMFMT;

struct SRPHRASEW;
typedef SRPHRASEW *PSRPhraseW;

#pragma pack(push, 1)
struct AdISapi__1
{
	
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct SRPHRASEW
{
	unsigned dwSize;
	AdISapi__1 abWords;
} ;
#pragma pack(pop)

typedef SRPHRASEW  TSRPhraseW;

typedef void __fastcall (__closure *TDirectSRClickIn)(System::TObject* Sender, int x, int y);

typedef void __fastcall (__closure *TDirectSRClickOut)(System::TObject* Sender, int x, int y);

typedef void __fastcall (__closure *TDirectSRPhraseFinish)(System::TObject* Sender, int flags, int beginhi, int beginlo, int endhi, int endlo, const WideString Phrase, const WideString parsed, int results);

typedef void __fastcall (__closure *TDirectSRPhraseStart)(System::TObject* Sender, int hi, int lo);

typedef void __fastcall (__closure *TDirectSRBookMark)(System::TObject* Sender, int MarkID);

typedef void __fastcall (__closure *TDirectSRPhraseHypothesis)(System::TObject* Sender, int flags, int beginhi, int beginlo, int endhi, int endlo, const WideString Phrase, int results);

typedef void __fastcall (__closure *TDirectSRReEvaluate)(System::TObject* Sender, int results);

typedef void __fastcall (__closure *TDirectSRTraining)(System::TObject* Sender, int train);

typedef void __fastcall (__closure *TDirectSRUnArchive)(System::TObject* Sender, int results);

typedef void __fastcall (__closure *TDirectSRAttribChanged)(System::TObject* Sender, int Attribute);

typedef void __fastcall (__closure *TDirectSRInterference)(System::TObject* Sender, int beginhi, int beginlo, int endhi, int endlo, int type_);

typedef void __fastcall (__closure *TDirectSRSound)(System::TObject* Sender, int beginhi, int beginlo, int endhi, int endlo);

typedef void __fastcall (__closure *TDirectSRUtteranceBegin)(System::TObject* Sender, int beginhi, int beginlo);

typedef void __fastcall (__closure *TDirectSRUtteranceEnd)(System::TObject* Sender, int beginhi, int beginlo, int endhi, int endlo);

typedef void __fastcall (__closure *TDirectSRVUMeter)(System::TObject* Sender, int beginhi, int beginlo, int level);

typedef void __fastcall (__closure *TDirectSRError)(System::TObject* Sender, unsigned warning, const WideString Details, const WideString Message);

typedef void __fastcall (__closure *TDirectSRwarning)(System::TObject* Sender, unsigned warning, const WideString Details, const WideString Message);

typedef void __fastcall (__closure *TDirectSSClickIn)(System::TObject* Sender, int x, int y);

typedef void __fastcall (__closure *TDirectSSClickOut)(System::TObject* Sender, int x, int y);

typedef void __fastcall (__closure *TDirectSSAudioStart)(System::TObject* Sender, int hi, int lo);

typedef void __fastcall (__closure *TDirectSSAudioStop)(System::TObject* Sender, int hi, int lo);

typedef void __fastcall (__closure *TDirectSSAttribChanged)(System::TObject* Sender, int which_attribute);

typedef void __fastcall (__closure *TDirectSSVisual)(System::TObject* Sender, int timehi, int timelo, short Phoneme, short EnginePhoneme, int hints, short MouthHeight, short bMouthWidth, short bMouthUpturn, short bJawOpen, short TeethUpperVisible, short TeethLowerVisible, short TonguePosn, short LipTension);

typedef void __fastcall (__closure *TDirectSSWordPosition)(System::TObject* Sender, int hi, int lo, int byteoffset);

typedef void __fastcall (__closure *TDirectSSBookMark)(System::TObject* Sender, int hi, int lo, int MarkNum);

typedef void __fastcall (__closure *TDirectSSTextDataStarted)(System::TObject* Sender, int hi, int lo);

typedef void __fastcall (__closure *TDirectSSTextDataDone)(System::TObject* Sender, int hi, int lo, int Flags);

typedef void __fastcall (__closure *TDirectSSActiveVoiceStartup)(System::TObject* Sender, int init, int init2);

typedef void __fastcall (__closure *TDirectSSError)(System::TObject* Sender, unsigned warning, const WideString Details, const WideString Message);

typedef void __fastcall (__closure *TDirectSSwarning)(System::TObject* Sender, unsigned warning, const WideString Details, const WideString Message);

typedef void __fastcall (__closure *TDirectSSVisualFuture)(System::TObject* Sender, int milliseconds, int timehi, int timelo, short Phoneme, short EnginePhoneme, int hints, short MouthHeight, short bMouthWidth, short bMouthUpturn, short bJawOpen, short TeethUpperVisible, short TeethLowerVisible, short TonguePosn, short LipTension);

__interface IAudioMultiMediaDevice;
typedef System::DelphiInterface<IAudioMultiMediaDevice> _di_IAudioMultiMediaDevice;
__interface INTERFACE_UUID("{B68AD320-C743-11CD-80E5-00AA003E4B50}") IAudioMultiMediaDevice  : public IInterface 
{
	
public:
	virtual HRESULT __stdcall CustomMessage(unsigned uMsg, const SDATA dData) = 0 ;
	virtual HRESULT __stdcall DeviceNumGet(unsigned &dwDeviceID) = 0 ;
	virtual HRESULT __stdcall DeviceNumSet(unsigned dwDeviceID) = 0 ;
};

typedef _di_IAudioMultiMediaDevice *PIAUDIOMULTIMEDIADEVICE;

__interface IAudioTel;
typedef System::DelphiInterface<IAudioTel> _di_IAudioTel;
__interface INTERFACE_UUID("{2EC5A8A7-E65B-11D0-8FAC-08002BE4E62A}") IAudioTel  : public IInterface 
{
	
public:
	virtual HRESULT __stdcall AudioObject(System::_di_IInterface AudioObject) = 0 ;
	virtual HRESULT __stdcall WaveFormatSet(const SDATA dWFEX) = 0 ;
};

typedef _di_IAudioTel *PIAUDIOTEL;

__interface IDirectSR;
typedef System::DelphiInterface<IDirectSR> _di_IDirectSR;
typedef IDirectSR DirectSR;
;

__interface IDirectSS;
typedef System::DelphiInterface<IDirectSS> _di_IDirectSS;
typedef IDirectSS DirectSS;
;

typedef IInterface VoiceProp;
;

typedef int *PInteger1;

typedef WideString *PWideString1;

__dispinterface _DirectSREvents;
typedef System::DelphiInterface<_DirectSREvents> _di__DirectSREvents;
__dispinterface INTERFACE_UUID("{4E3D9D20-0C63-11D1-8BFB-0060081841DE}") _DirectSREvents  : public IDispatch 
{
	
};

__interface INTERFACE_UUID("{4E3D9D1E-0C63-11D1-8BFB-0060081841DE}") IDirectSR  : public IDispatch 
{
	
public:
	virtual HRESULT __safecall Get_debug(short &Get_debug_result) = 0 ;
	virtual HRESULT __safecall Set_debug(short pVal) = 0 ;
	virtual HRESULT __safecall Get_Initialized(short &Get_Initialized_result) = 0 ;
	virtual HRESULT __safecall Set_Initialized(short pVal) = 0 ;
	virtual HRESULT __safecall Deactivate(void) = 0 ;
	virtual HRESULT __safecall Activate(void) = 0 ;
	virtual HRESULT __safecall Get_LastHeard(WideString &Get_LastHeard_result) = 0 ;
	virtual HRESULT __safecall Set_LastHeard(const WideString pVal) = 0 ;
	virtual HRESULT __safecall GrammarFromString(const WideString grammar) = 0 ;
	virtual HRESULT __safecall GrammarFromFile(const WideString FileName) = 0 ;
	virtual HRESULT __safecall GrammarFromResource(int Instance, int ResID) = 0 ;
	virtual HRESULT __safecall GrammarFromStream(int Stream) = 0 ;
	virtual HRESULT __safecall Get_AutoGain(int &Get_AutoGain_result) = 0 ;
	virtual HRESULT __safecall Set_AutoGain(int pVal) = 0 ;
	virtual HRESULT __safecall Get_MinAutoGain(int &Get_MinAutoGain_result) = 0 ;
	virtual HRESULT __safecall Get_MaxAutoGain(int &Get_MaxAutoGain_result) = 0 ;
	virtual HRESULT __safecall Get_Echo(short &Get_Echo_result) = 0 ;
	virtual HRESULT __safecall Set_Echo(short pVal) = 0 ;
	virtual HRESULT __safecall Get_EnergyFloor(int &Get_EnergyFloor_result) = 0 ;
	virtual HRESULT __safecall Set_EnergyFloor(int pVal) = 0 ;
	virtual HRESULT __safecall Get_MaxEnergyFloor(int &Get_MaxEnergyFloor_result) = 0 ;
	virtual HRESULT __safecall Get_MinEnergyFloor(int &Get_MinEnergyFloor_result) = 0 ;
	virtual HRESULT __safecall Get_Microphone(WideString &Get_Microphone_result) = 0 ;
	virtual HRESULT __safecall Set_Microphone(const WideString pVal) = 0 ;
	virtual HRESULT __safecall Get_Speaker(WideString &Get_Speaker_result) = 0 ;
	virtual HRESULT __safecall Set_Speaker(const WideString pVal) = 0 ;
	virtual HRESULT __safecall Get_RealTime(int &Get_RealTime_result) = 0 ;
	virtual HRESULT __safecall Set_RealTime(int pVal) = 0 ;
	virtual HRESULT __safecall Get_MaxRealTime(int &Get_MaxRealTime_result) = 0 ;
	virtual HRESULT __safecall Get_MinRealTime(int &Get_MinRealTime_result) = 0 ;
	virtual HRESULT __safecall Get_Threshold(int &Get_Threshold_result) = 0 ;
	virtual HRESULT __safecall Set_Threshold(int pVal) = 0 ;
	virtual HRESULT __safecall Get_MaxThreshold(int &Get_MaxThreshold_result) = 0 ;
	virtual HRESULT __safecall Get_MinThreshold(int &Get_MinThreshold_result) = 0 ;
	virtual HRESULT __safecall Get_CompleteTimeOut(int &Get_CompleteTimeOut_result) = 0 ;
	virtual HRESULT __safecall Set_CompleteTimeOut(int pVal) = 0 ;
	virtual HRESULT __safecall Get_IncompleteTimeOut(int &Get_IncompleteTimeOut_result) = 0 ;
	virtual HRESULT __safecall Set_IncompleteTimeOut(int pVal) = 0 ;
	virtual HRESULT __safecall Get_MaxCompleteTimeOut(int &Get_MaxCompleteTimeOut_result) = 0 ;
	virtual HRESULT __safecall Get_MinCompleteTimeOut(int &Get_MinCompleteTimeOut_result) = 0 ;
	virtual HRESULT __safecall Get_MaxIncompleteTimeOut(int &Get_MaxIncompleteTimeOut_result) = 0 ;
	virtual HRESULT __safecall Get_MinIncompleteTimeOut(int &Get_MinIncompleteTimeOut_result) = 0 ;
	virtual HRESULT __safecall Pause(void) = 0 ;
	virtual HRESULT __safecall Resume(void) = 0 ;
	virtual HRESULT __safecall PosnGet(/* out */ int &hi, /* out */ int &lo) = 0 ;
	virtual HRESULT __safecall AboutDlg(int hwnd, const WideString title) = 0 ;
	virtual HRESULT __safecall GeneralDlg(int hwnd, const WideString title) = 0 ;
	virtual HRESULT __safecall LexiconDlg(int hwnd, const WideString title) = 0 ;
	virtual HRESULT __safecall TrainGeneralDlg(int hwnd, const WideString title) = 0 ;
	virtual HRESULT __safecall TrainMicDlg(int hwnd, const WideString title) = 0 ;
	virtual HRESULT __safecall Get_Wave(int results, int &Get_Wave_result) = 0 ;
	virtual HRESULT __safecall Get_Phrase(int results, int rank, WideString &Get_Phrase_result) = 0 ;
	virtual HRESULT __safecall Get_CreateResultsObject(int results, int &Get_CreateResultsObject_result) = 0 ;
	virtual HRESULT __safecall DestroyResultsObject(int resobj) = 0 ;
	virtual HRESULT __safecall Select(int index) = 0 ;
	virtual HRESULT __safecall Listen(void) = 0 ;
	virtual HRESULT __safecall SelectEngine(int index) = 0 ;
	virtual HRESULT __safecall FindEngine(const WideString EngineId, const WideString MfgName, const WideString ProductName, const WideString ModeID, const WideString ModeName, int LanguageID, const WideString dialect, int Sequencing, int MaxWordsVocab, int MaxWordsState, int Grammars, int Features, int Interfaces, int EngineFeatures, int RankEngineID, int RankMfgName, int RankProductName, int RankModeID, int RankModeName, int RankLanguage, int RankDialect, int RankSequencing, int RankMaxWordsVocab, int RankMaxWordsState, int RankGrammars, int RankFeatures, int RankInterfaces, int RankEngineFeatures, int &FindEngine_result) = 0 ;
	virtual HRESULT __safecall Get_CountEngines(int &Get_CountEngines_result) = 0 ;
	virtual HRESULT __safecall ModeName(int index, WideString &ModeName_result) = 0 ;
	virtual HRESULT __safecall EngineId(int index, WideString &EngineId_result) = 0 ;
	virtual HRESULT __safecall MfgName(int index, WideString &MfgName_result) = 0 ;
	virtual HRESULT __safecall ProductName(int index, WideString &ProductName_result) = 0 ;
	virtual HRESULT __safecall ModeID(int index, WideString &ModeID_result) = 0 ;
	virtual HRESULT __safecall Features(int index, int &Features_result) = 0 ;
	virtual HRESULT __safecall Interfaces(int index, int &Interfaces_result) = 0 ;
	virtual HRESULT __safecall EngineFeatures(int index, int &EngineFeatures_result) = 0 ;
	virtual HRESULT __safecall LanguageID(int index, int &LanguageID_result) = 0 ;
	virtual HRESULT __safecall dialect(int index, WideString &dialect_result) = 0 ;
	virtual HRESULT __safecall Sequencing(int index, int &Sequencing_result) = 0 ;
	virtual HRESULT __safecall MaxWordsVocab(int index, int &MaxWordsVocab_result) = 0 ;
	virtual HRESULT __safecall MaxWordsState(int index, int &MaxWordsState_result) = 0 ;
	virtual HRESULT __safecall Grammars(int index, int &Grammars_result) = 0 ;
	virtual HRESULT __safecall InitAudioSourceDirect(int direct) = 0 ;
	virtual HRESULT __safecall InitAudioSourceObject(int object_) = 0 ;
	virtual HRESULT __safecall Get_FileName(WideString &Get_FileName_result) = 0 ;
	virtual HRESULT __safecall Set_FileName(const WideString pVal) = 0 ;
	virtual HRESULT __safecall Get_FlagsGet(int results, int rank, int &Get_FlagsGet_result) = 0 ;
	virtual HRESULT __safecall Get_Identify(int results, WideString &Get_Identify_result) = 0 ;
	virtual HRESULT __safecall TimeGet(int results, int &beginhi, int &beginlo, int &endhi, int &endlo) = 0 ;
	virtual HRESULT __safecall Correction(int results, const WideString Phrase, short confidence) = 0 ;
	virtual HRESULT __safecall Validate(int results, short confidence) = 0 ;
	virtual HRESULT __safecall Get_ReEvaluate(int results, int &Get_ReEvaluate_result) = 0 ;
	virtual HRESULT __safecall Get_GetPhraseScore(int results, int rank, int &Get_GetPhraseScore_result) = 0 ;
	virtual HRESULT __safecall Archive(int keepresults, /* out */ int &size, /* out */ int &pVal) = 0 ;
	virtual HRESULT __safecall DeleteArchive(int Archive) = 0 ;
	virtual HRESULT __safecall GrammarFromMemory(int grammar, int size) = 0 ;
	virtual HRESULT __safecall GrammarDataSet(int Data, int size) = 0 ;
	virtual HRESULT __safecall GrammarToMemory(int &grammar, int &size) = 0 ;
	virtual HRESULT __safecall ActivateAndAssignWindow(int hwnd) = 0 ;
	virtual HRESULT __safecall Get_LastError(int &Get_LastError_result) = 0 ;
	virtual HRESULT __safecall Set_LastError(int pVal) = 0 ;
	virtual HRESULT __safecall Get_SuppressExceptions(int &Get_SuppressExceptions_result) = 0 ;
	virtual HRESULT __safecall Set_SuppressExceptions(int pVal) = 0 ;
	virtual HRESULT __safecall Get_hwnd(int &Get_hwnd_result) = 0 ;
	virtual HRESULT __safecall Find(const WideString RankList, int &Find_result) = 0 ;
	virtual HRESULT __safecall Get_SRMode(int &Get_SRMode_result) = 0 ;
	virtual HRESULT __safecall Set_SRMode(int pVal) = 0 ;
	virtual HRESULT __safecall Get_GetAllArcStrings(int punk, int results, WideString &Get_GetAllArcStrings_result) = 0 ;
	virtual HRESULT __safecall Get_Attributes(int Attrib, int &Get_Attributes_result) = 0 ;
	virtual HRESULT __safecall Set_Attributes(int Attrib, int pVal) = 0 ;
	virtual HRESULT __safecall Get_AttributeString(int Attrib, WideString &Get_AttributeString_result) = 0 ;
	virtual HRESULT __safecall Set_AttributeString(int Attrib, const WideString pVal) = 0 ;
	virtual HRESULT __safecall Get_AttributeMemory(int Attrib, int &size, int &Get_AttributeMemory_result) = 0 ;
	virtual HRESULT __safecall Set_AttributeMemory(int Attrib, int &size, int pVal) = 0 ;
	virtual HRESULT __safecall Get_WaveEx(int results, int beginhi, int beginlo, int endhi, int endlo, int &Get_WaveEx_result) = 0 ;
	virtual HRESULT __safecall Get_NodeStart(int results, int &Get_NodeStart_result) = 0 ;
	virtual HRESULT __safecall Get_NodeEnd(int results, int &Get_NodeEnd_result) = 0 ;
	virtual HRESULT __safecall ArcEnum(int results, int node, int Outgoing, int &nodelist, int &countnodes) = 0 ;
	virtual HRESULT __safecall BestPathEnum(int results, int rank, int &startpath, int startpathsteps, int &endpath, int endpathsteps, int exactmatch, int &arclist, int &arccount) = 0 ;
	virtual HRESULT __safecall Get_DataGetString(int results, int id, const WideString Attrib, WideString &Get_DataGetString_result) = 0 ;
	virtual HRESULT __safecall DataGetTime(int results, int id, const WideString Attrib, int &hi, int &lo) = 0 ;
	virtual HRESULT __safecall Get_score(int results, int scoretype, int &path, int pathsteps, int pathindexstart, int pathindexcount, int &Get_score_result) = 0 ;
	virtual HRESULT __safecall GetAllArcs(int results, int &arcids, int &arccount) = 0 ;
	virtual HRESULT __safecall GetAllNodes(int results, int &Nodes, int &countnodes) = 0 ;
	virtual HRESULT __safecall Get_NodeGet(int results, int arc, int destination, int &Get_NodeGet_result) = 0 ;
	virtual HRESULT __safecall Get_GraphDWORDGet(int results, int id, const WideString Attrib, int &Get_GraphDWORDGet_result) = 0 ;
	virtual HRESULT __safecall RenameSpeaker(const WideString OldName, const WideString newName) = 0 ;
	virtual HRESULT __safecall DeleteSpeaker(const WideString Speaker) = 0 ;
	virtual HRESULT __safecall CommitSpeaker(void) = 0 ;
	virtual HRESULT __safecall RevertSpeaker(const WideString Speaker) = 0 ;
	virtual HRESULT __safecall Get_SpeakerInfoChanged(int &filetimehi, int &filetimelo, int &Get_SpeakerInfoChanged_result) = 0 ;
	virtual HRESULT __safecall TrainPhrasesDlg(int hwnd, const WideString title) = 0 ;
	virtual HRESULT __safecall LexAddTo(unsigned lex, int charset, const WideString text, const WideString pronounce, int partofspeech, int EngineInfo, int engineinfosize) = 0 ;
	virtual HRESULT __safecall LexGetFrom(int lex, int charset, const WideString text, int sense, WideString &pronounce, int &partofspeech, int &EngineInfo, int &sizeofengineinfo) = 0 ;
	virtual HRESULT __safecall LexRemoveFrom(int lex, const WideString text, int sense) = 0 ;
	virtual HRESULT __safecall QueryLexicons(int f, int &pdw) = 0 ;
	virtual HRESULT __safecall ChangeSpelling(int lex, const WideString stringa, const WideString stringb) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_debug() { short r; HRESULT hr = Get_debug(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short debug = {read=_scw_Get_debug, write=Set_debug};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_Initialized() { short r; HRESULT hr = Get_Initialized(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short Initialized = {read=_scw_Get_Initialized, write=Set_Initialized};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_LastHeard() { WideString r; HRESULT hr = Get_LastHeard(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString LastHeard = {read=_scw_Get_LastHeard, write=Set_LastHeard};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_AutoGain() { int r; HRESULT hr = Get_AutoGain(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int AutoGain = {read=_scw_Get_AutoGain, write=Set_AutoGain};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MinAutoGain() { int r; HRESULT hr = Get_MinAutoGain(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MinAutoGain = {read=_scw_Get_MinAutoGain};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MaxAutoGain() { int r; HRESULT hr = Get_MaxAutoGain(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MaxAutoGain = {read=_scw_Get_MaxAutoGain};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_Echo() { short r; HRESULT hr = Get_Echo(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short Echo = {read=_scw_Get_Echo, write=Set_Echo};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_EnergyFloor() { int r; HRESULT hr = Get_EnergyFloor(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int EnergyFloor = {read=_scw_Get_EnergyFloor, write=Set_EnergyFloor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MaxEnergyFloor() { int r; HRESULT hr = Get_MaxEnergyFloor(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MaxEnergyFloor = {read=_scw_Get_MaxEnergyFloor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MinEnergyFloor() { int r; HRESULT hr = Get_MinEnergyFloor(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MinEnergyFloor = {read=_scw_Get_MinEnergyFloor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_Microphone() { WideString r; HRESULT hr = Get_Microphone(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString Microphone = {read=_scw_Get_Microphone, write=Set_Microphone};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_Speaker() { WideString r; HRESULT hr = Get_Speaker(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString Speaker = {read=_scw_Get_Speaker, write=Set_Speaker};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_RealTime() { int r; HRESULT hr = Get_RealTime(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int RealTime = {read=_scw_Get_RealTime, write=Set_RealTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MaxRealTime() { int r; HRESULT hr = Get_MaxRealTime(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MaxRealTime = {read=_scw_Get_MaxRealTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MinRealTime() { int r; HRESULT hr = Get_MinRealTime(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MinRealTime = {read=_scw_Get_MinRealTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Threshold() { int r; HRESULT hr = Get_Threshold(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int Threshold = {read=_scw_Get_Threshold, write=Set_Threshold};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MaxThreshold() { int r; HRESULT hr = Get_MaxThreshold(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MaxThreshold = {read=_scw_Get_MaxThreshold};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MinThreshold() { int r; HRESULT hr = Get_MinThreshold(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MinThreshold = {read=_scw_Get_MinThreshold};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CompleteTimeOut() { int r; HRESULT hr = Get_CompleteTimeOut(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int CompleteTimeOut = {read=_scw_Get_CompleteTimeOut, write=Set_CompleteTimeOut};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_IncompleteTimeOut() { int r; HRESULT hr = Get_IncompleteTimeOut(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int IncompleteTimeOut = {read=_scw_Get_IncompleteTimeOut, write=Set_IncompleteTimeOut};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MaxCompleteTimeOut() { int r; HRESULT hr = Get_MaxCompleteTimeOut(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MaxCompleteTimeOut = {read=_scw_Get_MaxCompleteTimeOut};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MinCompleteTimeOut() { int r; HRESULT hr = Get_MinCompleteTimeOut(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MinCompleteTimeOut = {read=_scw_Get_MinCompleteTimeOut};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MaxIncompleteTimeOut() { int r; HRESULT hr = Get_MaxIncompleteTimeOut(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MaxIncompleteTimeOut = {read=_scw_Get_MaxIncompleteTimeOut};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MinIncompleteTimeOut() { int r; HRESULT hr = Get_MinIncompleteTimeOut(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MinIncompleteTimeOut = {read=_scw_Get_MinIncompleteTimeOut};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Wave(int results) { int r; HRESULT hr = Get_Wave(results, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int Wave[int results] = {read=_scw_Get_Wave};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_Phrase(int results, int rank) { WideString r; HRESULT hr = Get_Phrase(results, rank, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString Phrase[int results][int rank] = {read=_scw_Get_Phrase};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CreateResultsObject(int results) { int r; HRESULT hr = Get_CreateResultsObject(results, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int CreateResultsObject[int results] = {read=_scw_Get_CreateResultsObject};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CountEngines() { int r; HRESULT hr = Get_CountEngines(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int CountEngines = {read=_scw_Get_CountEngines};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_FileName() { WideString r; HRESULT hr = Get_FileName(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString FileName = {read=_scw_Get_FileName, write=Set_FileName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_FlagsGet(int results, int rank) { int r; HRESULT hr = Get_FlagsGet(results, rank, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int FlagsGet[int results][int rank] = {read=_scw_Get_FlagsGet};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_Identify(int results) { WideString r; HRESULT hr = Get_Identify(results, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString Identify[int results] = {read=_scw_Get_Identify};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_ReEvaluate(int results) { int r; HRESULT hr = Get_ReEvaluate(results, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int ReEvaluate[int results] = {read=_scw_Get_ReEvaluate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_GetPhraseScore(int results, int rank) { int r; HRESULT hr = Get_GetPhraseScore(results, rank, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int GetPhraseScore[int results][int rank] = {read=_scw_Get_GetPhraseScore};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_LastError() { int r; HRESULT hr = Get_LastError(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int LastError = {read=_scw_Get_LastError, write=Set_LastError};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_SuppressExceptions() { int r; HRESULT hr = Get_SuppressExceptions(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int SuppressExceptions = {read=_scw_Get_SuppressExceptions, write=Set_SuppressExceptions};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_hwnd() { int r; HRESULT hr = Get_hwnd(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int hwnd = {read=_scw_Get_hwnd};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_SRMode() { int r; HRESULT hr = Get_SRMode(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int SRMode = {read=_scw_Get_SRMode, write=Set_SRMode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_GetAllArcStrings(int punk, int results) { WideString r; HRESULT hr = Get_GetAllArcStrings(punk, results, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString GetAllArcStrings[int punk][int results] = {read=_scw_Get_GetAllArcStrings};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Attributes(int Attrib) { int r; HRESULT hr = Get_Attributes(Attrib, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int Attributes[int Attrib] = {read=_scw_Get_Attributes, write=Set_Attributes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_AttributeString(int Attrib) { WideString r; HRESULT hr = Get_AttributeString(Attrib, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString AttributeString[int Attrib] = {read=_scw_Get_AttributeString, write=Set_AttributeString};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_AttributeMemory(int Attrib, int &size) { int r; HRESULT hr = Get_AttributeMemory(Attrib, size, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int AttributeMemory[int Attrib][int size] = {read=_scw_Get_AttributeMemory, write=Set_AttributeMemory};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_WaveEx(int results, int beginhi, int beginlo, int endhi, int endlo) { int r; HRESULT hr = Get_WaveEx(results, beginhi, beginlo, endhi, endlo, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int WaveEx[int results][int beginhi][int beginlo][int endhi][int endlo] = {read=_scw_Get_WaveEx};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_NodeStart(int results) { int r; HRESULT hr = Get_NodeStart(results, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int NodeStart[int results] = {read=_scw_Get_NodeStart};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_NodeEnd(int results) { int r; HRESULT hr = Get_NodeEnd(results, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int NodeEnd[int results] = {read=_scw_Get_NodeEnd};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_DataGetString(int results, int id, const WideString Attrib) { WideString r; HRESULT hr = Get_DataGetString(results, id, Attrib, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString DataGetString[int results][int id][WideString Attrib] = {read=_scw_Get_DataGetString};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_score(int results, int scoretype, int &path, int pathsteps, int pathindexstart, int pathindexcount) { int r; HRESULT hr = Get_score(results, scoretype, path, pathsteps, pathindexstart, pathindexcount, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int score[int results][int scoretype][int path][int pathsteps][int pathindexstart][int pathindexcount] = {read=_scw_Get_score};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_NodeGet(int results, int arc, int destination) { int r; HRESULT hr = Get_NodeGet(results, arc, destination, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int NodeGet[int results][int arc][int destination] = {read=_scw_Get_NodeGet};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_GraphDWORDGet(int results, int id, const WideString Attrib) { int r; HRESULT hr = Get_GraphDWORDGet(results, id, Attrib, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int GraphDWORDGet[int results][int id][WideString Attrib] = {read=_scw_Get_GraphDWORDGet};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_SpeakerInfoChanged(int &filetimehi, int &filetimelo) { int r; HRESULT hr = Get_SpeakerInfoChanged(filetimehi, filetimelo, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int SpeakerInfoChanged[int filetimehi][int filetimelo] = {read=_scw_Get_SpeakerInfoChanged};
};

__dispinterface IDirectSRDisp;
typedef System::DelphiInterface<IDirectSRDisp> _di_IDirectSRDisp;
__dispinterface INTERFACE_UUID("{4E3D9D1E-0C63-11D1-8BFB-0060081841DE}") IDirectSRDisp  : public IDispatch 
{
	
};

class DELPHICLASS TDirectSR;
class PASCALIMPLEMENTATION TDirectSR : public Olectrls::TOleControl 
{
	typedef Olectrls::TOleControl inherited;
	
private:
	TDirectSRClickIn FOnClickIn;
	TDirectSRClickOut FOnClickOut;
	TDirectSRPhraseFinish FOnPhraseFinish;
	TDirectSRPhraseStart FOnPhraseStart;
	TDirectSRBookMark FOnBookMark;
	Classes::TNotifyEvent FOnPaused;
	TDirectSRPhraseHypothesis FOnPhraseHypothesis;
	TDirectSRReEvaluate FOnReEvaluate;
	TDirectSRTraining FOnTraining;
	TDirectSRUnArchive FOnUnArchive;
	TDirectSRAttribChanged FOnAttribChanged;
	TDirectSRInterference FOnInterference;
	TDirectSRSound FOnSound;
	TDirectSRUtteranceBegin FOnUtteranceBegin;
	TDirectSRUtteranceEnd FOnUtteranceEnd;
	TDirectSRVUMeter FOnVUMeter;
	TDirectSRError FOnError;
	TDirectSRwarning FOnwarning;
	_di_IDirectSR FIntf;
	_di_IDirectSR __fastcall GetControlInterface();
	
protected:
	HIDESBASE void __fastcall CreateControl(void);
	virtual void __fastcall InitControlData(void);
	int __fastcall Get_Wave(int results);
	WideString __fastcall Get_Phrase(int results, int rank);
	int __fastcall Get_CreateResultsObject(int results);
	int __fastcall Get_FlagsGet(int results, int rank);
	WideString __fastcall Get_Identify(int results);
	int __fastcall Get_ReEvaluate(int results);
	int __fastcall Get_GetPhraseScore(int results, int rank);
	WideString __fastcall Get_GetAllArcStrings(int punk, int results);
	int __fastcall Get_Attributes(int Attrib);
	void __fastcall Set_Attributes(int Attrib, int pVal);
	WideString __fastcall Get_AttributeString(int Attrib);
	void __fastcall Set_AttributeString(int Attrib, const WideString pVal);
	int __fastcall Get_AttributeMemory(int Attrib, int &size);
	void __fastcall Set_AttributeMemory(int Attrib, int &size, int pVal);
	int __fastcall Get_WaveEx(int results, int beginhi, int beginlo, int endhi, int endlo);
	int __fastcall Get_NodeStart(int results);
	int __fastcall Get_NodeEnd(int results);
	WideString __fastcall Get_DataGetString(int results, int id, const WideString Attrib);
	int __fastcall Get_score(int results, int scoretype, int &path, int pathsteps, int pathindexstart, int pathindexcount);
	int __fastcall Get_NodeGet(int results, int arc, int destination);
	int __fastcall Get_GraphDWORDGet(int results, int id, const WideString Attrib);
	int __fastcall Get_SpeakerInfoChanged(int &filetimehi, int &filetimelo);
	
public:
	void __fastcall Deactivate(void);
	void __fastcall Activate(void);
	void __fastcall GrammarFromString(const WideString grammar);
	void __fastcall GrammarFromFile(const WideString FileName);
	void __fastcall GrammarFromResource(int Instance, int ResID);
	void __fastcall GrammarFromStream(int Stream);
	void __fastcall Pause(void);
	void __fastcall Resume(void);
	void __fastcall PosnGet(/* out */ int &hi, /* out */ int &lo);
	void __fastcall AboutDlg(int hwnd, const WideString title);
	void __fastcall GeneralDlg(int hwnd, const WideString title);
	void __fastcall LexiconDlg(int hwnd, const WideString title);
	void __fastcall TrainGeneralDlg(int hwnd, const WideString title);
	void __fastcall TrainMicDlg(int hwnd, const WideString title);
	void __fastcall DestroyResultsObject(int resobj);
	void __fastcall Select(int index);
	void __fastcall Listen(void);
	void __fastcall SelectEngine(int index);
	int __fastcall FindEngine(const WideString EngineId, const WideString MfgName, const WideString ProductName, const WideString ModeID, const WideString ModeName, int LanguageID, const WideString dialect, int Sequencing, int MaxWordsVocab, int MaxWordsState, int Grammars, int Features, int Interfaces, int EngineFeatures, int RankEngineID, int RankMfgName, int RankProductName, int RankModeID, int RankModeName, int RankLanguage, int RankDialect, int RankSequencing, int RankMaxWordsVocab, int RankMaxWordsState, int RankGrammars, int RankFeatures, int RankInterfaces, int RankEngineFeatures);
	WideString __fastcall ModeName(int index);
	WideString __fastcall EngineId(int index);
	WideString __fastcall MfgName(int index);
	WideString __fastcall ProductName(int index);
	WideString __fastcall ModeID(int index);
	int __fastcall Features(int index);
	int __fastcall Interfaces(int index);
	int __fastcall EngineFeatures(int index);
	int __fastcall LanguageID(int index);
	WideString __fastcall dialect(int index);
	int __fastcall Sequencing(int index);
	int __fastcall MaxWordsVocab(int index);
	int __fastcall MaxWordsState(int index);
	int __fastcall Grammars(int index);
	void __fastcall InitAudioSourceDirect(int direct);
	void __fastcall InitAudioSourceObject(int object_);
	void __fastcall TimeGet(int results, int &beginhi, int &beginlo, int &endhi, int &endlo);
	void __fastcall Correction(int results, const WideString Phrase, short confidence);
	void __fastcall Validate(int results, short confidence);
	void __fastcall Archive(int keepresults, /* out */ int &size, /* out */ int &pVal);
	void __fastcall DeleteArchive(int Archive);
	void __fastcall GrammarFromMemory(int grammar, int size);
	void __fastcall GrammarDataSet(int Data, int size);
	void __fastcall GrammarToMemory(int &grammar, int &size);
	void __fastcall ActivateAndAssignWindow(int hwnd);
	int __fastcall Find(const WideString RankList);
	void __fastcall ArcEnum(int results, int node, int Outgoing, int &nodelist, int &countnodes);
	void __fastcall BestPathEnum(int results, int rank, int &startpath, int startpathsteps, int &endpath, int endpathsteps, int exactmatch, int &arclist, int &arccount);
	void __fastcall DataGetTime(int results, int id, const WideString Attrib, int &hi, int &lo);
	void __fastcall GetAllArcs(int results, int &arcids, int &arccount);
	void __fastcall GetAllNodes(int results, int &Nodes, int &countnodes);
	void __fastcall RenameSpeaker(const WideString OldName, const WideString newName);
	void __fastcall DeleteSpeaker(const WideString Speaker);
	void __fastcall CommitSpeaker(void);
	void __fastcall RevertSpeaker(const WideString Speaker);
	void __fastcall TrainPhrasesDlg(int hwnd, const WideString title);
	void __fastcall LexAddTo(unsigned lex, int charset, const WideString text, const WideString pronounce, int partofspeech, int EngineInfo, int engineinfosize);
	void __fastcall LexGetFrom(int lex, int charset, const WideString text, int sense, WideString &pronounce, int &partofspeech, int &EngineInfo, int &sizeofengineinfo);
	void __fastcall LexRemoveFrom(int lex, const WideString text, int sense);
	void __fastcall QueryLexicons(int f, int &pdw);
	void __fastcall ChangeSpelling(int lex, const WideString stringa, const WideString stringb);
	__property _di_IDirectSR ControlInterface = {read=GetControlInterface};
	__property _di_IDirectSR DefaultInterface = {read=GetControlInterface};
	__property int MinAutoGain = {read=GetIntegerProp, index=12, nodefault};
	__property int MaxAutoGain = {read=GetIntegerProp, index=13, nodefault};
	__property int MaxEnergyFloor = {read=GetIntegerProp, index=16, nodefault};
	__property int MinEnergyFloor = {read=GetIntegerProp, index=17, nodefault};
	__property int MaxRealTime = {read=GetIntegerProp, index=21, nodefault};
	__property int MinRealTime = {read=GetIntegerProp, index=22, nodefault};
	__property int MaxThreshold = {read=GetIntegerProp, index=24, nodefault};
	__property int MinThreshold = {read=GetIntegerProp, index=25, nodefault};
	__property int MaxCompleteTimeOut = {read=GetIntegerProp, index=28, nodefault};
	__property int MinCompleteTimeOut = {read=GetIntegerProp, index=29, nodefault};
	__property int MaxIncompleteTimeOut = {read=GetIntegerProp, index=30, nodefault};
	__property int MinIncompleteTimeOut = {read=GetIntegerProp, index=31, nodefault};
	__property int Wave[int results] = {read=Get_Wave};
	__property WideString Phrase[int results][int rank] = {read=Get_Phrase};
	__property int CreateResultsObject[int results] = {read=Get_CreateResultsObject};
	__property int CountEngines = {read=GetIntegerProp, index=48, nodefault};
	__property int FlagsGet[int results][int rank] = {read=Get_FlagsGet};
	__property WideString Identify[int results] = {read=Get_Identify};
	__property int ReEvaluate[int results] = {read=Get_ReEvaluate};
	__property int GetPhraseScore[int results][int rank] = {read=Get_GetPhraseScore};
	__property int hwnd = {read=GetIntegerProp, index=81, nodefault};
	__property WideString GetAllArcStrings[int punk][int results] = {read=Get_GetAllArcStrings};
	__property int Attributes[int Attrib] = {read=Get_Attributes, write=Set_Attributes};
	__property WideString AttributeString[int Attrib] = {read=Get_AttributeString, write=Set_AttributeString};
	__property int AttributeMemory[int Attrib][int size] = {read=Get_AttributeMemory, write=Set_AttributeMemory};
	__property int WaveEx[int results][int beginhi][int beginlo][int endhi][int endlo] = {read=Get_WaveEx};
	__property int NodeStart[int results] = {read=Get_NodeStart};
	__property int NodeEnd[int results] = {read=Get_NodeEnd};
	__property WideString DataGetString[int results][int id][WideString Attrib] = {read=Get_DataGetString};
	__property int score[int results][int scoretype][int path][int pathsteps][int pathindexstart][int pathindexcount] = {read=Get_score};
	__property int NodeGet[int results][int arc][int destination] = {read=Get_NodeGet};
	__property int GraphDWORDGet[int results][int id][WideString Attrib] = {read=Get_GraphDWORDGet};
	__property int SpeakerInfoChanged[int filetimehi][int filetimelo] = {read=Get_SpeakerInfoChanged};
	
__published:
	__property TabStop  = {default=1};
	__property Align  = {default=0};
	__property DragCursor  = {default=-12};
	__property DragMode  = {default=0};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowHint ;
	__property TabOrder  = {default=-1};
	__property Visible  = {default=1};
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnStartDrag ;
	__property short debug = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=1, nodefault};
	__property short Initialized = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=2, nodefault};
	__property WideString LastHeard = {read=GetWideStringProp, write=SetWideStringProp, stored=false, index=6};
	__property int AutoGain = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=11, nodefault};
	__property short Echo = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=14, nodefault};
	__property int EnergyFloor = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=15, nodefault};
	__property WideString Microphone = {read=GetWideStringProp, write=SetWideStringProp, stored=false, index=18};
	__property WideString Speaker = {read=GetWideStringProp, write=SetWideStringProp, stored=false, index=19};
	__property int RealTime = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=20, nodefault};
	__property int Threshold = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=23, nodefault};
	__property int CompleteTimeOut = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=26, nodefault};
	__property int IncompleteTimeOut = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=27, nodefault};
	__property WideString FileName = {read=GetWideStringProp, write=SetWideStringProp, stored=false, index=65};
	__property int LastError = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=79, nodefault};
	__property int SuppressExceptions = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=80, nodefault};
	__property int SRMode = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=83, nodefault};
	__property TDirectSRClickIn OnClickIn = {read=FOnClickIn, write=FOnClickIn};
	__property TDirectSRClickOut OnClickOut = {read=FOnClickOut, write=FOnClickOut};
	__property TDirectSRPhraseFinish OnPhraseFinish = {read=FOnPhraseFinish, write=FOnPhraseFinish};
	__property TDirectSRPhraseStart OnPhraseStart = {read=FOnPhraseStart, write=FOnPhraseStart};
	__property TDirectSRBookMark OnBookMark = {read=FOnBookMark, write=FOnBookMark};
	__property Classes::TNotifyEvent OnPaused = {read=FOnPaused, write=FOnPaused};
	__property TDirectSRPhraseHypothesis OnPhraseHypothesis = {read=FOnPhraseHypothesis, write=FOnPhraseHypothesis};
	__property TDirectSRReEvaluate OnReEvaluate = {read=FOnReEvaluate, write=FOnReEvaluate};
	__property TDirectSRTraining OnTraining = {read=FOnTraining, write=FOnTraining};
	__property TDirectSRUnArchive OnUnArchive = {read=FOnUnArchive, write=FOnUnArchive};
	__property TDirectSRAttribChanged OnAttribChanged = {read=FOnAttribChanged, write=FOnAttribChanged};
	__property TDirectSRInterference OnInterference = {read=FOnInterference, write=FOnInterference};
	__property TDirectSRSound OnSound = {read=FOnSound, write=FOnSound};
	__property TDirectSRUtteranceBegin OnUtteranceBegin = {read=FOnUtteranceBegin, write=FOnUtteranceBegin};
	__property TDirectSRUtteranceEnd OnUtteranceEnd = {read=FOnUtteranceEnd, write=FOnUtteranceEnd};
	__property TDirectSRVUMeter OnVUMeter = {read=FOnVUMeter, write=FOnVUMeter};
	__property TDirectSRError OnError = {read=FOnError, write=FOnError};
	__property TDirectSRwarning Onwarning = {read=FOnwarning, write=FOnwarning};
public:
	#pragma option push -w-inl
	/* TOleControl.Create */ inline __fastcall virtual TDirectSR(Classes::TComponent* AOwner) : Olectrls::TOleControl(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TOleControl.Destroy */ inline __fastcall virtual ~TDirectSR(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TDirectSR(HWND ParentWindow) : Olectrls::TOleControl(ParentWindow) { }
	#pragma option pop
	
};


__dispinterface _DirectSSEvents;
typedef System::DelphiInterface<_DirectSSEvents> _di__DirectSSEvents;
__dispinterface INTERFACE_UUID("{EEE78597-FE22-11D0-8BEF-0060081841DE}") _DirectSSEvents  : public IDispatch 
{
	
};

__interface INTERFACE_UUID("{EEE78590-FE22-11D0-8BEF-0060081841DE}") IDirectSS  : public IDispatch 
{
	
public:
	virtual HRESULT __safecall Get_debug(short &Get_debug_result) = 0 ;
	virtual HRESULT __safecall Set_debug(short pVal) = 0 ;
	virtual HRESULT __safecall Get_Initialized(short &Get_Initialized_result) = 0 ;
	virtual HRESULT __safecall Set_Initialized(short pVal) = 0 ;
	virtual HRESULT __safecall Speak(const WideString text) = 0 ;
	virtual HRESULT __safecall Get_Pitch(int &Get_Pitch_result) = 0 ;
	virtual HRESULT __safecall Set_Pitch(int pVal) = 0 ;
	virtual HRESULT __safecall Get_MaxPitch(int &Get_MaxPitch_result) = 0 ;
	virtual HRESULT __safecall Set_MaxPitch(int pVal) = 0 ;
	virtual HRESULT __safecall Get_MinPitch(int &Get_MinPitch_result) = 0 ;
	virtual HRESULT __safecall Set_MinPitch(int pVal) = 0 ;
	virtual HRESULT __safecall Get_Speed(int &Get_Speed_result) = 0 ;
	virtual HRESULT __safecall Set_Speed(int pVal) = 0 ;
	virtual HRESULT __safecall Get_MaxSpeed(int &Get_MaxSpeed_result) = 0 ;
	virtual HRESULT __safecall Set_MaxSpeed(int pVal) = 0 ;
	virtual HRESULT __safecall Get_MinSpeed(int &Get_MinSpeed_result) = 0 ;
	virtual HRESULT __safecall Set_MinSpeed(int pVal) = 0 ;
	virtual HRESULT __safecall Get_VolumeRight(int &Get_VolumeRight_result) = 0 ;
	virtual HRESULT __safecall Set_VolumeRight(int pVal) = 0 ;
	virtual HRESULT __safecall Get_MinVolumeRight(int &Get_MinVolumeRight_result) = 0 ;
	virtual HRESULT __safecall Set_MinVolumeRight(int pVal) = 0 ;
	virtual HRESULT __safecall Get_MaxVolumeRight(int &Get_MaxVolumeRight_result) = 0 ;
	virtual HRESULT __safecall Set_MaxVolumeRight(int pVal) = 0 ;
	virtual HRESULT __safecall Select(int index) = 0 ;
	virtual HRESULT __safecall EngineID(int index, WideString &EngineID_result) = 0 ;
	virtual HRESULT __safecall Get_CountEngines(int &Get_CountEngines_result) = 0 ;
	virtual HRESULT __safecall ModeName(int index, WideString &ModeName_result) = 0 ;
	virtual HRESULT __safecall MfgName(int index, WideString &MfgName_result) = 0 ;
	virtual HRESULT __safecall ProductName(int index, WideString &ProductName_result) = 0 ;
	virtual HRESULT __safecall ModeID(int index, WideString &ModeID_result) = 0 ;
	virtual HRESULT __safecall Speaker(int index, WideString &Speaker_result) = 0 ;
	virtual HRESULT __safecall Style(int index, WideString &Style_result) = 0 ;
	virtual HRESULT __safecall Gender(int index, int &Gender_result) = 0 ;
	virtual HRESULT __safecall Age(int index, int &Age_result) = 0 ;
	virtual HRESULT __safecall Features(int index, int &Features_result) = 0 ;
	virtual HRESULT __safecall Interfaces(int index, int &Interfaces_result) = 0 ;
	virtual HRESULT __safecall EngineFeatures(int index, int &EngineFeatures_result) = 0 ;
	virtual HRESULT __safecall LanguageID(int index, int &LanguageID_result) = 0 ;
	virtual HRESULT __safecall Dialect(int index, WideString &Dialect_result) = 0 ;
	virtual HRESULT __safecall Get_RealTime(int &Get_RealTime_result) = 0 ;
	virtual HRESULT __safecall Set_RealTime(int pVal) = 0 ;
	virtual HRESULT __safecall Get_MaxRealTime(int &Get_MaxRealTime_result) = 0 ;
	virtual HRESULT __safecall Get_MinRealTime(int &Get_MinRealTime_result) = 0 ;
	virtual HRESULT __safecall Set_MinRealTime(int pVal) = 0 ;
	virtual HRESULT __safecall AudioPause(void) = 0 ;
	virtual HRESULT __safecall AudioReset(void) = 0 ;
	virtual HRESULT __safecall AudioResume(void) = 0 ;
	virtual HRESULT __safecall Inject(const WideString value) = 0 ;
	virtual HRESULT __safecall Get_Tagged(int &Get_Tagged_result) = 0 ;
	virtual HRESULT __safecall Set_Tagged(int pVal) = 0 ;
	virtual HRESULT __safecall Phonemes(int charset, int Flags, const WideString input, WideString &Phonemes_result) = 0 ;
	virtual HRESULT __safecall PosnGet(int &hi, int &lo) = 0 ;
	virtual HRESULT __safecall TextData(int characterset, int Flags, const WideString text) = 0 ;
	virtual HRESULT __safecall InitAudioDestMM(int deviceid) = 0 ;
	virtual HRESULT __safecall AboutDlg(int hWnd, const WideString title) = 0 ;
	virtual HRESULT __safecall GeneralDlg(int hWnd, const WideString title) = 0 ;
	virtual HRESULT __safecall LexiconDlg(int hWnd, const WideString title) = 0 ;
	virtual HRESULT __safecall TranslateDlg(int hWnd, const WideString title) = 0 ;
	virtual HRESULT __safecall FindEngine(const WideString EngineID, const WideString MfgName, const WideString ProductName, const WideString ModeID, const WideString ModeName, int LanguageID, const WideString Dialect, const WideString Speaker, const WideString Style, int Gender, int Age, int Features, int Interfaces, int EngineFeatures, int RankEngineID, int RankMfgName, int RankProductName, int RankModeID, int RankModeName, int RankLanguage, int RankDialect, int RankSpeaker, int RankStyle, int RankGender, int RankAge, int RankFeatures, int RankInterfaces, int RankEngineFeatures, int &FindEngine_result) = 0 ;
	virtual HRESULT __safecall Get_MouthHeight(short &Get_MouthHeight_result) = 0 ;
	virtual HRESULT __safecall Set_MouthHeight(short pVal) = 0 ;
	virtual HRESULT __safecall Get_MouthWidth(short &Get_MouthWidth_result) = 0 ;
	virtual HRESULT __safecall Set_MouthWidth(short pVal) = 0 ;
	virtual HRESULT __safecall Get_MouthUpturn(short &Get_MouthUpturn_result) = 0 ;
	virtual HRESULT __safecall Set_MouthUpturn(short pVal) = 0 ;
	virtual HRESULT __safecall Get_JawOpen(short &Get_JawOpen_result) = 0 ;
	virtual HRESULT __safecall Set_JawOpen(short pVal) = 0 ;
	virtual HRESULT __safecall Get_TeethUpperVisible(short &Get_TeethUpperVisible_result) = 0 ;
	virtual HRESULT __safecall Set_TeethUpperVisible(short pVal) = 0 ;
	virtual HRESULT __safecall Get_TeethLowerVisible(short &Get_TeethLowerVisible_result) = 0 ;
	virtual HRESULT __safecall Set_TeethLowerVisible(short pVal) = 0 ;
	virtual HRESULT __safecall Get_TonguePosn(short &Get_TonguePosn_result) = 0 ;
	virtual HRESULT __safecall Set_TonguePosn(short pVal) = 0 ;
	virtual HRESULT __safecall Get_LipTension(short &Get_LipTension_result) = 0 ;
	virtual HRESULT __safecall Set_LipTension(short pVal) = 0 ;
	virtual HRESULT __safecall Get_CallBacksEnabled(short &Get_CallBacksEnabled_result) = 0 ;
	virtual HRESULT __safecall Set_CallBacksEnabled(short pVal) = 0 ;
	virtual HRESULT __safecall Get_MouthEnabled(short &Get_MouthEnabled_result) = 0 ;
	virtual HRESULT __safecall Set_MouthEnabled(short pVal) = 0 ;
	virtual HRESULT __safecall Get_LastError(int &Get_LastError_result) = 0 ;
	virtual HRESULT __safecall Set_LastError(int pVal) = 0 ;
	virtual HRESULT __safecall Get_SuppressExceptions(short &Get_SuppressExceptions_result) = 0 ;
	virtual HRESULT __safecall Set_SuppressExceptions(short pVal) = 0 ;
	virtual HRESULT __safecall Get_Speaking(short &Get_Speaking_result) = 0 ;
	virtual HRESULT __safecall Set_Speaking(short pVal) = 0 ;
	virtual HRESULT __safecall Get_LastWordPosition(int &Get_LastWordPosition_result) = 0 ;
	virtual HRESULT __safecall Set_LastWordPosition(int pVal) = 0 ;
	virtual HRESULT __safecall Get_LipType(short &Get_LipType_result) = 0 ;
	virtual HRESULT __safecall Set_LipType(short pVal) = 0 ;
	virtual HRESULT __safecall GetPronunciation(int charset, const WideString text, int Sense, WideString &Pronounce, int &PartOfSpeech, WideString &EngineInfo) = 0 ;
	virtual HRESULT __safecall InitAudioDestDirect(int direct) = 0 ;
	virtual HRESULT __safecall Get_Sayit(WideString &Get_Sayit_result) = 0 ;
	virtual HRESULT __safecall Set_Sayit(const WideString newVal) = 0 ;
	virtual HRESULT __safecall InitAudioDestObject(int object_) = 0 ;
	virtual HRESULT __safecall Get_FileName(WideString &Get_FileName_result) = 0 ;
	virtual HRESULT __safecall Set_FileName(const WideString pVal) = 0 ;
	virtual HRESULT __safecall Get_CurrentMode(int &Get_CurrentMode_result) = 0 ;
	virtual HRESULT __safecall Set_CurrentMode(int pVal) = 0 ;
	virtual HRESULT __safecall Get_hWnd(int &Get_hWnd_result) = 0 ;
	virtual HRESULT __safecall Find(const WideString RankList, int &Find_result) = 0 ;
	virtual HRESULT __safecall Get_VolumeLeft(int &Get_VolumeLeft_result) = 0 ;
	virtual HRESULT __safecall Set_VolumeLeft(int pVal) = 0 ;
	virtual HRESULT __safecall Get_MinVolumeLeft(int &Get_MinVolumeLeft_result) = 0 ;
	virtual HRESULT __safecall Set_MinVolumeLeft(int pVal) = 0 ;
	virtual HRESULT __safecall Get_MaxVolumeLeft(int &Get_MaxVolumeLeft_result) = 0 ;
	virtual HRESULT __safecall Set_MaxVolumeLeft(int pVal) = 0 ;
	virtual HRESULT __safecall Get_AudioDest(int &Get_AudioDest_result) = 0 ;
	virtual HRESULT __safecall Get_Attributes(int Attrib, int &Get_Attributes_result) = 0 ;
	virtual HRESULT __safecall Set_Attributes(int Attrib, int pVal) = 0 ;
	virtual HRESULT __safecall Get_AttributeString(int Attrib, WideString &Get_AttributeString_result) = 0 ;
	virtual HRESULT __safecall Set_AttributeString(int Attrib, const WideString pVal) = 0 ;
	virtual HRESULT __safecall Get_AttributeMemory(int Attrib, int &size, int &Get_AttributeMemory_result) = 0 ;
	virtual HRESULT __safecall Set_AttributeMemory(int Attrib, int &size, int pVal) = 0 ;
	virtual HRESULT __safecall LexAddTo(unsigned lex, int charset, const WideString text, const WideString Pronounce, int PartOfSpeech, int EngineInfo, int engineinfosize) = 0 ;
	virtual HRESULT __safecall LexGetFrom(int lex, int charset, const WideString text, int Sense, WideString &Pronounce, int &PartOfSpeech, int &EngineInfo, int &sizeofengineinfo) = 0 ;
	virtual HRESULT __safecall LexRemoveFrom(int lex, const WideString text, int Sense) = 0 ;
	virtual HRESULT __safecall QueryLexicons(int f, int &pdw) = 0 ;
	virtual HRESULT __safecall ChangeSpelling(int lex, const WideString stringa, const WideString stringb) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_debug() { short r; HRESULT hr = Get_debug(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short debug = {read=_scw_Get_debug, write=Set_debug};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_Initialized() { short r; HRESULT hr = Get_Initialized(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short Initialized = {read=_scw_Get_Initialized, write=Set_Initialized};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Pitch() { int r; HRESULT hr = Get_Pitch(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int Pitch = {read=_scw_Get_Pitch, write=Set_Pitch};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MaxPitch() { int r; HRESULT hr = Get_MaxPitch(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MaxPitch = {read=_scw_Get_MaxPitch, write=Set_MaxPitch};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MinPitch() { int r; HRESULT hr = Get_MinPitch(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MinPitch = {read=_scw_Get_MinPitch, write=Set_MinPitch};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Speed() { int r; HRESULT hr = Get_Speed(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int Speed = {read=_scw_Get_Speed, write=Set_Speed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MaxSpeed() { int r; HRESULT hr = Get_MaxSpeed(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MaxSpeed = {read=_scw_Get_MaxSpeed, write=Set_MaxSpeed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MinSpeed() { int r; HRESULT hr = Get_MinSpeed(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MinSpeed = {read=_scw_Get_MinSpeed, write=Set_MinSpeed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_VolumeRight() { int r; HRESULT hr = Get_VolumeRight(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int VolumeRight = {read=_scw_Get_VolumeRight, write=Set_VolumeRight};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MinVolumeRight() { int r; HRESULT hr = Get_MinVolumeRight(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MinVolumeRight = {read=_scw_Get_MinVolumeRight, write=Set_MinVolumeRight};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MaxVolumeRight() { int r; HRESULT hr = Get_MaxVolumeRight(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MaxVolumeRight = {read=_scw_Get_MaxVolumeRight, write=Set_MaxVolumeRight};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CountEngines() { int r; HRESULT hr = Get_CountEngines(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int CountEngines = {read=_scw_Get_CountEngines};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_RealTime() { int r; HRESULT hr = Get_RealTime(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int RealTime = {read=_scw_Get_RealTime, write=Set_RealTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MaxRealTime() { int r; HRESULT hr = Get_MaxRealTime(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MaxRealTime = {read=_scw_Get_MaxRealTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MinRealTime() { int r; HRESULT hr = Get_MinRealTime(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MinRealTime = {read=_scw_Get_MinRealTime, write=Set_MinRealTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Tagged() { int r; HRESULT hr = Get_Tagged(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int Tagged = {read=_scw_Get_Tagged, write=Set_Tagged};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_MouthHeight() { short r; HRESULT hr = Get_MouthHeight(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short MouthHeight = {read=_scw_Get_MouthHeight, write=Set_MouthHeight};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_MouthWidth() { short r; HRESULT hr = Get_MouthWidth(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short MouthWidth = {read=_scw_Get_MouthWidth, write=Set_MouthWidth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_MouthUpturn() { short r; HRESULT hr = Get_MouthUpturn(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short MouthUpturn = {read=_scw_Get_MouthUpturn, write=Set_MouthUpturn};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_JawOpen() { short r; HRESULT hr = Get_JawOpen(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short JawOpen = {read=_scw_Get_JawOpen, write=Set_JawOpen};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_TeethUpperVisible() { short r; HRESULT hr = Get_TeethUpperVisible(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short TeethUpperVisible = {read=_scw_Get_TeethUpperVisible, write=Set_TeethUpperVisible};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_TeethLowerVisible() { short r; HRESULT hr = Get_TeethLowerVisible(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short TeethLowerVisible = {read=_scw_Get_TeethLowerVisible, write=Set_TeethLowerVisible};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_TonguePosn() { short r; HRESULT hr = Get_TonguePosn(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short TonguePosn = {read=_scw_Get_TonguePosn, write=Set_TonguePosn};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_LipTension() { short r; HRESULT hr = Get_LipTension(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short LipTension = {read=_scw_Get_LipTension, write=Set_LipTension};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_CallBacksEnabled() { short r; HRESULT hr = Get_CallBacksEnabled(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short CallBacksEnabled = {read=_scw_Get_CallBacksEnabled, write=Set_CallBacksEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_MouthEnabled() { short r; HRESULT hr = Get_MouthEnabled(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short MouthEnabled = {read=_scw_Get_MouthEnabled, write=Set_MouthEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_LastError() { int r; HRESULT hr = Get_LastError(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int LastError = {read=_scw_Get_LastError, write=Set_LastError};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_SuppressExceptions() { short r; HRESULT hr = Get_SuppressExceptions(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short SuppressExceptions = {read=_scw_Get_SuppressExceptions, write=Set_SuppressExceptions};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_Speaking() { short r; HRESULT hr = Get_Speaking(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short Speaking = {read=_scw_Get_Speaking, write=Set_Speaking};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_LastWordPosition() { int r; HRESULT hr = Get_LastWordPosition(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int LastWordPosition = {read=_scw_Get_LastWordPosition, write=Set_LastWordPosition};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_LipType() { short r; HRESULT hr = Get_LipType(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property short LipType = {read=_scw_Get_LipType, write=Set_LipType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_Sayit() { WideString r; HRESULT hr = Get_Sayit(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString Sayit = {read=_scw_Get_Sayit, write=Set_Sayit};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_FileName() { WideString r; HRESULT hr = Get_FileName(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString FileName = {read=_scw_Get_FileName, write=Set_FileName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CurrentMode() { int r; HRESULT hr = Get_CurrentMode(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int CurrentMode = {read=_scw_Get_CurrentMode, write=Set_CurrentMode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_hWnd() { int r; HRESULT hr = Get_hWnd(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int hWnd = {read=_scw_Get_hWnd};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_VolumeLeft() { int r; HRESULT hr = Get_VolumeLeft(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int VolumeLeft = {read=_scw_Get_VolumeLeft, write=Set_VolumeLeft};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MinVolumeLeft() { int r; HRESULT hr = Get_MinVolumeLeft(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MinVolumeLeft = {read=_scw_Get_MinVolumeLeft, write=Set_MinVolumeLeft};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MaxVolumeLeft() { int r; HRESULT hr = Get_MaxVolumeLeft(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MaxVolumeLeft = {read=_scw_Get_MaxVolumeLeft, write=Set_MaxVolumeLeft};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_AudioDest() { int r; HRESULT hr = Get_AudioDest(r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int AudioDest = {read=_scw_Get_AudioDest};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Attributes(int Attrib) { int r; HRESULT hr = Get_Attributes(Attrib, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int Attributes[int Attrib] = {read=_scw_Get_Attributes, write=Set_Attributes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_AttributeString(int Attrib) { WideString r; HRESULT hr = Get_AttributeString(Attrib, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString AttributeString[int Attrib] = {read=_scw_Get_AttributeString, write=Set_AttributeString};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_AttributeMemory(int Attrib, int &size) { int r; HRESULT hr = Get_AttributeMemory(Attrib, size, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int AttributeMemory[int Attrib][int size] = {read=_scw_Get_AttributeMemory, write=Set_AttributeMemory};
};

__dispinterface IDirectSSDisp;
typedef System::DelphiInterface<IDirectSSDisp> _di_IDirectSSDisp;
__dispinterface INTERFACE_UUID("{EEE78590-FE22-11D0-8BEF-0060081841DE}") IDirectSSDisp  : public IDispatch 
{
	
};

class DELPHICLASS TDirectSS;
class PASCALIMPLEMENTATION TDirectSS : public Olectrls::TOleControl 
{
	typedef Olectrls::TOleControl inherited;
	
private:
	TDirectSSClickIn FOnClickIn;
	TDirectSSClickOut FOnClickOut;
	TDirectSSAudioStart FOnAudioStart;
	TDirectSSAudioStop FOnAudioStop;
	TDirectSSAttribChanged FOnAttribChanged;
	TDirectSSVisual FOnVisual;
	TDirectSSWordPosition FOnWordPosition;
	TDirectSSBookMark FOnBookMark;
	TDirectSSTextDataStarted FOnTextDataStarted;
	TDirectSSTextDataDone FOnTextDataDone;
	TDirectSSActiveVoiceStartup FOnActiveVoiceStartup;
	Classes::TNotifyEvent FOnDebugging;
	TDirectSSError FOnError;
	TDirectSSwarning FOnwarning;
	TDirectSSVisualFuture FOnVisualFuture;
	_di_IDirectSS FIntf;
	_di_IDirectSS __fastcall GetControlInterface();
	
protected:
	HIDESBASE void __fastcall CreateControl(void);
	virtual void __fastcall InitControlData(void);
	int __fastcall Get_Attributes(int Attrib);
	void __fastcall Set_Attributes(int Attrib, int pVal);
	WideString __fastcall Get_AttributeString(int Attrib);
	void __fastcall Set_AttributeString(int Attrib, const WideString pVal);
	int __fastcall Get_AttributeMemory(int Attrib, int &size);
	void __fastcall Set_AttributeMemory(int Attrib, int &size, int pVal);
	
public:
	__fastcall virtual TDirectSS(Classes::TComponent* AOwner);
	void __fastcall Speak(const WideString text);
	void __fastcall Select(int index);
	WideString __fastcall EngineID(int index);
	WideString __fastcall ModeName(int index);
	WideString __fastcall MfgName(int index);
	WideString __fastcall ProductName(int index);
	WideString __fastcall ModeID(int index);
	WideString __fastcall Speaker(int index);
	WideString __fastcall Style(int index);
	int __fastcall Gender(int index);
	int __fastcall Age(int index);
	int __fastcall Features(int index);
	int __fastcall Interfaces(int index);
	int __fastcall EngineFeatures(int index);
	int __fastcall LanguageID(int index);
	WideString __fastcall Dialect(int index);
	void __fastcall AudioPause(void);
	void __fastcall AudioReset(void);
	void __fastcall AudioResume(void);
	void __fastcall Inject(const WideString value);
	WideString __fastcall Phonemes(int charset, int Flags, const WideString input);
	void __fastcall PosnGet(int &hi, int &lo);
	void __fastcall TextData(int characterset, int Flags, const WideString text);
	void __fastcall InitAudioDestMM(int deviceid);
	void __fastcall AboutDlg(int hWnd, const WideString title);
	void __fastcall GeneralDlg(int hWnd, const WideString title);
	void __fastcall LexiconDlg(int hWnd, const WideString title);
	void __fastcall TranslateDlg(int hWnd, const WideString title);
	int __fastcall FindEngine(const WideString EngineID, const WideString MfgName, const WideString ProductName, const WideString ModeID, const WideString ModeName, int LanguageID, const WideString Dialect, const WideString Speaker, const WideString Style, int Gender, int Age, int Features, int Interfaces, int EngineFeatures, int RankEngineID, int RankMfgName, int RankProductName, int RankModeID, int RankModeName, int RankLanguage, int RankDialect, int RankSpeaker, int RankStyle, int RankGender, int RankAge, int RankFeatures, int RankInterfaces, int RankEngineFeatures);
	void __fastcall GetPronunciation(int charset, const WideString text, int Sense, WideString &Pronounce, int &PartOfSpeech, WideString &EngineInfo);
	void __fastcall InitAudioDestDirect(int direct);
	void __fastcall InitAudioDestObject(int object_);
	int __fastcall Find(const WideString RankList);
	void __fastcall LexAddTo(unsigned lex, int charset, const WideString text, const WideString Pronounce, int PartOfSpeech, int EngineInfo, int engineinfosize);
	void __fastcall LexGetFrom(int lex, int charset, const WideString text, int Sense, WideString &Pronounce, int &PartOfSpeech, int &EngineInfo, int &sizeofengineinfo);
	void __fastcall LexRemoveFrom(int lex, const WideString text, int Sense);
	void __fastcall QueryLexicons(int f, int &pdw);
	void __fastcall ChangeSpelling(int lex, const WideString stringa, const WideString stringb);
	__property _di_IDirectSS ControlInterface = {read=GetControlInterface};
	__property _di_IDirectSS DefaultInterface = {read=GetControlInterface};
	__property int CountEngines = {read=GetIntegerProp, index=18, nodefault};
	__property int MaxRealTime = {read=GetIntegerProp, index=33, nodefault};
	__property int hWnd = {read=GetIntegerProp, index=70, nodefault};
	__property int AudioDest = {read=GetIntegerProp, index=75, nodefault};
	__property int Attributes[int Attrib] = {read=Get_Attributes, write=Set_Attributes};
	__property WideString AttributeString[int Attrib] = {read=Get_AttributeString, write=Set_AttributeString};
	__property int AttributeMemory[int Attrib][int size] = {read=Get_AttributeMemory, write=Set_AttributeMemory};
	
__published:
	__property TabStop  = {default=1};
	__property Align  = {default=0};
	__property DragCursor  = {default=-12};
	__property DragMode  = {default=0};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowHint ;
	__property TabOrder  = {default=-1};
	__property Visible  = {default=1};
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnStartDrag ;
	__property short debug = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=1, nodefault};
	__property short Initialized = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=2, nodefault};
	__property int Pitch = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=7, nodefault};
	__property int MaxPitch = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=8, nodefault};
	__property int MinPitch = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=9, nodefault};
	__property int Speed = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=10, nodefault};
	__property int MaxSpeed = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=11, nodefault};
	__property int MinSpeed = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=12, nodefault};
	__property int VolumeRight = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=13, nodefault};
	__property int MinVolumeRight = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=14, nodefault};
	__property int MaxVolumeRight = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=15, nodefault};
	__property int RealTime = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=32, nodefault};
	__property int MinRealTime = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=34, nodefault};
	__property int Tagged = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=39, nodefault};
	__property short MouthHeight = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=49, nodefault};
	__property short MouthWidth = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=50, nodefault};
	__property short MouthUpturn = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=51, nodefault};
	__property short JawOpen = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=52, nodefault};
	__property short TeethUpperVisible = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=53, nodefault};
	__property short TeethLowerVisible = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=54, nodefault};
	__property short TonguePosn = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=55, nodefault};
	__property short LipTension = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=56, nodefault};
	__property short CallBacksEnabled = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=57, nodefault};
	__property short MouthEnabled = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=58, nodefault};
	__property int LastError = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=59, nodefault};
	__property short SuppressExceptions = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=60, nodefault};
	__property short Speaking = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=61, nodefault};
	__property int LastWordPosition = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=62, nodefault};
	__property short LipType = {read=GetSmallintProp, write=SetSmallintProp, stored=false, index=63, nodefault};
	__property WideString Sayit = {read=GetWideStringProp, write=SetWideStringProp, stored=false, index=66};
	__property WideString FileName = {read=GetWideStringProp, write=SetWideStringProp, stored=false, index=68};
	__property int CurrentMode = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=69, nodefault};
	__property int VolumeLeft = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=72, nodefault};
	__property int MinVolumeLeft = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=73, nodefault};
	__property int MaxVolumeLeft = {read=GetIntegerProp, write=SetIntegerProp, stored=false, index=74, nodefault};
	__property TDirectSSClickIn OnClickIn = {read=FOnClickIn, write=FOnClickIn};
	__property TDirectSSClickOut OnClickOut = {read=FOnClickOut, write=FOnClickOut};
	__property TDirectSSAudioStart OnAudioStart = {read=FOnAudioStart, write=FOnAudioStart};
	__property TDirectSSAudioStop OnAudioStop = {read=FOnAudioStop, write=FOnAudioStop};
	__property TDirectSSAttribChanged OnAttribChanged = {read=FOnAttribChanged, write=FOnAttribChanged};
	__property TDirectSSVisual OnVisual = {read=FOnVisual, write=FOnVisual};
	__property TDirectSSWordPosition OnWordPosition = {read=FOnWordPosition, write=FOnWordPosition};
	__property TDirectSSBookMark OnBookMark = {read=FOnBookMark, write=FOnBookMark};
	__property TDirectSSTextDataStarted OnTextDataStarted = {read=FOnTextDataStarted, write=FOnTextDataStarted};
	__property TDirectSSTextDataDone OnTextDataDone = {read=FOnTextDataDone, write=FOnTextDataDone};
	__property TDirectSSActiveVoiceStartup OnActiveVoiceStartup = {read=FOnActiveVoiceStartup, write=FOnActiveVoiceStartup};
	__property Classes::TNotifyEvent OnDebugging = {read=FOnDebugging, write=FOnDebugging};
	__property TDirectSSError OnError = {read=FOnError, write=FOnError};
	__property TDirectSSwarning Onwarning = {read=FOnwarning, write=FOnwarning};
	__property TDirectSSVisualFuture OnVisualFuture = {read=FOnVisualFuture, write=FOnVisualFuture};
public:
	#pragma option push -w-inl
	/* TOleControl.Destroy */ inline __fastcall virtual ~TDirectSS(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TDirectSS(HWND ParentWindow) : Olectrls::TOleControl(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint ACTIVEVOICEPROJECTLibMajorVersion = 0x1;
static const Shortint ACTIVEVOICEPROJECTLibMinorVersion = 0x0;
static const Shortint ACTIVELISTENPROJECTLibMajorVersion = 0x1;
static const Shortint ACTIVELISTENPROJECTLibMinorVersion = 0x0;
static const Shortint TELLibMajorVersion = 0x1;
static const Shortint TELLibMinorVersion = 0x0;
extern PACKAGE GUID LIBID_ACTIVEVOICEPROJECTLib;
extern PACKAGE GUID DIID__DirectSSEvents;
extern PACKAGE GUID IID_IDirectSS;
extern PACKAGE GUID CLASS_DirectSS;
extern PACKAGE GUID CLASS_VoiceProp;
extern PACKAGE GUID LIBID_ACTIVELISTENPROJECTLib;
extern PACKAGE GUID DIID__DirectSREvents;
extern PACKAGE GUID IID_IDirectSR;
extern PACKAGE GUID CLASS_DirectSR;
extern PACKAGE GUID LIBID_TELLib;
static const Shortint LANG_LEN = 0x40;
#define SID_IAudioMultiMediaDevice "{B68AD320-C743-11cd-80E5-00AA003E4B50}"
#define SID_IAudioTel "{2EC5A8A7-E65B-11D0-8FAC-08002BE4E62A}"

}	/* namespace Adisapi */
using namespace Adisapi;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdISapi
