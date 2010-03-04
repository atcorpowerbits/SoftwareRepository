// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AwFax.pas' rev: 6.00

#ifndef AwFaxHPP
#define AwFaxHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AwAbsFax.hpp>	// Pascal unit
#include <AwFaxCvt.hpp>	// Pascal unit
#include <AwUser.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Awfax
{
//-- type declarations -------------------------------------------------------
typedef Byte TFaxDataBuffer[65521];

typedef Byte *PFaxDataBuffer;

typedef SmallString<13>  TClass2Str;

typedef SmallString<128>  TModemResponse;

struct TC12AbsData;
typedef TC12AbsData *PC12AbsData;

#pragma pack(push, 4)
struct TC12AbsData
{
	bool cForceStatus;
	bool cMorePages;
	bool cSessionRes;
	bool cSessionWid;
	bool cSessionECM;
	bool cCanDoHighRes;
	bool cCanDoHighWid;
	bool cLastFrame;
	bool cToneDial;
	bool cLastPageOk;
	bool cUseLengthWord;
	bool cCoverIsAPF;
	bool cInitSent;
	bool cSlowBaud;
	bool cGotCFR;
	bool cBlindDial;
	bool cDetectBusy;
	char cCheckChar;
	char cResC;
	char cResCPrev;
	char cFaxAndData;
	Byte cSessionScan;
	Byte cReceivedFrame;
	Byte cCRLFIndex;
	Byte cETXIndex;
	Word cReplyWait;
	Word cTransWait;
	Word cMaxFaxBPS;
	Word cBPSIndex;
	Word cMinBytes;
	Word cHangupCode;
	Word cCurrOfs;
	Word cBadData;
	Word cRetry;
	int cBytesRead;
	int cDialWait;
	int cAnswerOnRing;
	int cRingCounter;
	int cSessionBPS;
	int cNormalBaud;
	int cInitBaud;
	Byte *cDataBuffer;
	file cInFile;
	Oomisc::TFaxHeaderRec cFaxHeader;
	Oomisc::TPageHeaderRec cPageHeader;
	TClass2Str cClassCmd;
	TClass2Str cModelCmd;
	TClass2Str cMfrCmd;
	TClass2Str cRevCmd;
	TClass2Str cDISCmd;
	TClass2Str cStationCmd;
	TClass2Str cDCCCmd;
	TClass2Str cFaxResp;
	TClass2Str cDISResp;
	TClass2Str cDCSResp;
	TClass2Str cTSIResp;
	TClass2Str cCSIResp;
	TClass2Str cPageResp;
	TClass2Str cHangResp;
	System::SmallString<3>  cModCode;
	System::SmallString<40>  cForcedInit;
	System::SmallString<40>  cModemInit;
	System::SmallString<40>  cDialPrefix;
	char cDialTonePulse;
	TModemResponse cResponse;
	System::ShortString cInFileName;
	Oomisc::EventTimer cReplyTimer;
	bool cLocalMods[6];
	bool cRmtMods[6];
	Byte cBufferBlock[8192];
	bool cEnhTextEnabled;
	Graphics::TFont* cEnhSmallFont;
	Graphics::TFont* cEnhStandardFont;
} ;
#pragma pack(pop)

struct TC12FaxData;
typedef TC12FaxData *PC12FaxData;

#pragma pack(push, 4)
struct TC12FaxData
{
	Awabsfax::TFaxData *fPData;
	TC12AbsData *fCData;
} ;
#pragma pack(pop)

struct TC12SendFax;
typedef TC12SendFax *PC12SendFax;

#pragma pack(push, 4)
struct TC12SendFax
{
	Awabsfax::TFaxData *fPData;
	TC12AbsData *fCData;
	bool fSafeMode;
	Word fMaxSendCount;
	Word fBufferMinimum;
	bool fMCFConnect;
	int fRetries;
	int fMaxRetries;
	Oomisc::TAbsFaxCvt *fConverter;
	Awabsfax::SendStates fState;
	System::ShortString fHeaderLine;
	Oomisc::TLineReader* fCvrF;
	bool fCvrOpen;
	bool fRetryPage;
	Word fRetryMax;
	bool fFastPage;
} ;
#pragma pack(pop)

struct TC12ReceiveFax;
typedef TC12ReceiveFax *PC12ReceiveFax;

#pragma pack(push, 4)
struct TC12ReceiveFax
{
	Awabsfax::TFaxData *fPData;
	TC12AbsData *fCData;
	bool fSafeMode;
	bool fOneFax;
	bool fConstantStatus;
	bool fShowStatus;
	char fLast;
	Awabsfax::ReceivePageStatus fPageStatus;
	Awabsfax::ReceiveStates fState;
	Awabsfax::ReceiveStates fFirstState;
	bool fRenegotiate;
} ;
#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
static const Shortint MaxModIndex = 0x6;
extern PACKAGE Word PhysicalTopMargin;
static const Shortint DefMaxSendCnt = 0x32;
static const Word DefBufferMin = 0x3e8;
static const Word awfDefFaxDialTimeout = 0x444;
static const Byte awfDefCmdTimeout = 0xb6;
static const Word awfDefTransTimeout = 0x444;
static const Shortint aDataTrigger = 0x0;
extern PACKAGE Word AbortDelay;
extern PACKAGE Word PreCommandDelay;
extern PACKAGE Word PreFaxDelay;
extern PACKAGE Word ExtraCommandDelay;
extern PACKAGE Word PreEOPDelay;
extern PACKAGE Word InterCharDelay;
extern PACKAGE Word OkDelay;
extern PACKAGE Word BaudChangeDelay;
extern PACKAGE Word Class1Wait;
extern PACKAGE Word MaxClass1Retry;
extern PACKAGE int __fastcall cInitC12AbsData(PC12AbsData &DP);
extern PACKAGE int __fastcall cDoneC12AbsData(PC12AbsData &DP);
extern PACKAGE void __fastcall fSetFaxPort(Awabsfax::PFaxRec FP, Awuser::TApdBaseDispatcher* ComPort);
extern PACKAGE void __fastcall fSetModemInit(Awabsfax::PFaxRec FP,  System::ShortString &MIS);
extern PACKAGE Oomisc::ClassType __fastcall fSetClassType(Awabsfax::PFaxRec FP, Oomisc::ClassType CT);
extern PACKAGE void __fastcall fSetInitBaudRate(Awabsfax::PFaxRec FP, int InitRate, int NormalRate, bool DoIt);
extern PACKAGE bool __fastcall fGetModemClassSupport(Awabsfax::PFaxRec FP, bool &Class1, bool &Class2, bool &Class2_0, bool Reset);
extern PACKAGE bool __fastcall fGetModemInfo(Awabsfax::PFaxRec FP, char &FaxClass, AnsiString &Model, AnsiString &Chip, AnsiString &Rev, bool Reset);
extern PACKAGE int __fastcall fGetModemFeatures(Awabsfax::PFaxRec FP, int &BPS, char &Correction);
extern PACKAGE void __fastcall fSetModemFeatures(Awabsfax::PFaxRec FP, int BPS, char Correction);
extern PACKAGE void __fastcall fGetPageInfoC12(Awabsfax::PFaxRec FP, Word &Pages, Word &Page, int &BytesTransferred, int &PageLength);
extern PACKAGE bool __fastcall fGetLastPageStatus(Awabsfax::PFaxRec FP);
extern PACKAGE System::ShortString __fastcall fGetRemoteID(Awabsfax::PFaxRec FP);
extern PACKAGE void __fastcall fGetSessionParams(Awabsfax::PFaxRec FP, int &BPS, bool &Resolution, bool &Correction);
extern PACKAGE Word __fastcall fGetHangupResult(Awabsfax::PFaxRec FP);
extern PACKAGE int __fastcall fInitC12SendFax(Awabsfax::PFaxRec &FP,  Oomisc::Str20 &ID, Awuser::TApdBaseDispatcher* ComPort, int Window);
extern PACKAGE void __fastcall fDoneC12SendFax(Awabsfax::PFaxRec &FP);
extern PACKAGE void __fastcall fSetHeaderText(Awabsfax::PFaxRec FP,  System::ShortString &S);
extern PACKAGE void __fastcall fSetEnhTextEnabled(Awabsfax::PFaxRec FP, bool Enabled);
extern PACKAGE void __fastcall fSetEnhSmallFont(Awabsfax::PFaxRec FP, Graphics::TFont* SmFont);
extern PACKAGE void __fastcall fSetEnhStandardFont(Awabsfax::PFaxRec FP, Graphics::TFont* StFont);
extern PACKAGE void __fastcall fSetBlindDial(Awabsfax::PFaxRec FP, bool Blind);
extern PACKAGE void __fastcall fSetDetectBusy(Awabsfax::PFaxRec FP, bool DetectBusySignal);
extern PACKAGE void __fastcall fSetToneDial(Awabsfax::PFaxRec FP, bool Tone);
extern PACKAGE void __fastcall fSetDialPrefix(Awabsfax::PFaxRec FP,  System::ShortString &P);
extern PACKAGE void __fastcall fSetDialTime(Awabsfax::PFaxRec FP, int DT);
extern PACKAGE void __fastcall fSetMaxRetries(Awabsfax::PFaxRec FP, int MR);
extern PACKAGE void __fastcall fSetYielding(Awabsfax::PFaxRec FP, Word MaxLines, Word FreeBuffer);
extern PACKAGE void __fastcall fSetSafeMode(Awabsfax::PFaxRec FP, bool SafeMode);
extern PACKAGE void __fastcall fFaxTransmit(unsigned Msg, unsigned wParam, int lParam);
extern PACKAGE int __fastcall fPrepareFaxTransmit(Awabsfax::PFaxRec FP);
extern PACKAGE int __fastcall fInitC12ReceiveFax(Awabsfax::PFaxRec &FP,  Oomisc::Str20 &ID, Awuser::TApdBaseDispatcher* ComPort, int Window);
extern PACKAGE int __fastcall fDoneC12ReceiveFax(Awabsfax::PFaxRec &FP);
extern PACKAGE bool __fastcall fInitModemForFaxReceive(Awabsfax::PFaxRec FP);
extern PACKAGE void __fastcall fSetConnectState(Awabsfax::PFaxRec FP);
extern PACKAGE void __fastcall fSetAnswerOnRing(Awabsfax::PFaxRec FP, int AOR);
extern PACKAGE void __fastcall fSetFaxAndData(Awabsfax::PFaxRec FP, bool OnOff);
extern PACKAGE void __fastcall fSetOneFax(Awabsfax::PFaxRec FP, bool OnOff);
extern PACKAGE void __fastcall fFaxReceive(unsigned Msg, unsigned wParam, int lParam);
extern PACKAGE int __fastcall fPrepareFaxReceive(Awabsfax::PFaxRec FP);

}	/* namespace Awfax */
using namespace Awfax;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AwFax
