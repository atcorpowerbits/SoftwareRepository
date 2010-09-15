// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AwAbsFax.pas' rev: 6.00

#ifndef AwAbsFaxHPP
#define AwAbsFaxHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AwUser.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Awabsfax
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (*TFaxFunc)(unsigned Msg, unsigned wParam, int lParam);

struct TFaxData;
typedef TFaxData *PFaxData;

#pragma pack(push, 4)
struct TFaxData
{
	int aStatusTrigger;
	int aTimeoutTrigger;
	int aOutBuffFreeTrigger;
	int aOutBuffUsedTrigger;
	int aStatusInterval;
	HWND aHWindow;
	Awuser::TApdBaseDispatcher* aPort;
	TFaxFunc aCurFaxFunc;
	bool aSending;
	bool aSendingCover;
	bool aInProgress;
	unsigned aMaxConnect;
	unsigned aConnectCnt;
	unsigned aRetryCnt;
	unsigned aRetryWait;
	unsigned afFlags;
	unsigned aSaveStatus;
	unsigned aFaxProgress;
	unsigned aFaxListCount;
	int aFaxError;
	int aCurrPage;
	int aPageCount;
	int aCoverCount;
	int aDataCount;
	int aPageSize;
	Oomisc::TFaxEntry *aFaxListHead;
	Oomisc::TFaxEntry *aFaxListTail;
	Oomisc::TFaxEntry *aFaxListNode;
	Oomisc::ClassType aClassInUse;
	Oomisc::Str20 aStationID;
	Oomisc::Str20 aRemoteID;
	char aStNumber[21];
	System::ShortString aDestDir;
	System::ShortString aFaxFileExt;
	System::ShortString aFaxFileName;
	System::ShortString aCoverFile;
	System::SmallString<40>  aPhoneNum;
	Oomisc::EventTimer aStatusTimer;
	System::ShortString aTitle;
	System::ShortString aRecipient;
	System::ShortString aSender;
	Byte aSaveMode;
	bool aSendManual;
	bool aConcatFax;
	bool HaveTriggerHandler;
	bool aUsingTapi;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TFaxRec
{
	TFaxData *aPData;
} ;
#pragma pack(pop)

typedef TFaxRec *PFaxRec;

typedef int __fastcall (*TFaxPrepProc)(PFaxRec P);

typedef void __fastcall (*FaxStatusProc)(PFaxRec FP, bool Starting, bool Ending);

typedef bool __fastcall (*NextFaxFunc)(PFaxRec FP,  System::ShortString &Number,  System::ShortString &FName,  System::ShortString &Cover);

typedef void __fastcall (*FaxLogProc)(PFaxRec FP, Oomisc::TFaxLogCode Log);

typedef System::ShortString __fastcall (*FaxNameFunc)(PFaxRec FP);

typedef bool __fastcall (*AcceptFaxFunc)(PFaxRec FP,  Oomisc::Str20 &RemoteName);

#pragma option push -b-
enum ReceivePageStatus { rpsBadPage, rpsMoreSame, rpsNewPage, rpsNewDocument, rpsEndOfDocument };
#pragma option pop

#pragma option push -b-
enum SendStates { tfNone, tfGetEntry, tfInit, tf1Init1, tf2Init1, tf2Init1A, tf2Init1B, tf2Init2, tf2Init3, tfDial, tfRetryWait, tf1Connect, tf1SendTSI, tf1TSIResponse, tf1DCSResponse, tf1TrainStart, tf1TrainFinish, tf1WaitCFR, tf1WaitPageConnect, tf2Connect, tf2GetParams, tfWaitXon, tfWaitFreeHeader, tfSendPageHeader, tfOpenCover, tfSendCover, tfPrepPage, tfSendPage, tfDrainPage, tf1PageEnd, tf1PrepareEOP, tf1SendEOP, tf1WaitMPS, tf1WaitEOP, tf1WaitMCF, tf1SendDCN, tf1Hangup, tf1WaitHangup, tf2SendEOP, tf2WaitFPTS, tf2WaitFET, tf2WaitPageOK, tf2SendNewParams, tf2NextPage, tf20CheckPage, tfClose, tfCompleteOK, tfAbort, tfDone };
#pragma option pop

#pragma option push -b-
enum ReceiveStates { rfNone, rfInit, rf1Init1, rf2Init1, rf2Init1A, rf2Init1B, rf2Init2, rf2Init3, rfWaiting, rfAnswer, rf1SendCSI, rf1SendDIS, rf1CollectFrames, rf1CollectRetry1, rf1CollectRetry2, rf1StartTrain, rf1CollectTrain, rf1Timeout, rf1Retrain, rf1FinishTrain, rf1SendCFR, rf1WaitPageConnect, rf2ValidConnect, rf2GetSenderID, rf2GetConnect, rfStartPage, rfGetPageData, rf1FinishPage, rf1WaitEOP, rf1WritePage, rf1SendMCF, rf1WaitDCN, rf1WaitHangup, rf2GetPageResult, rf2GetFHNG, rfComplete, rfAbort, rfDone };
#pragma option pop

//-- var, const, procedure ---------------------------------------------------
static const Shortint NSFFrame = 0x20;
static const Shortint EOPFrame = 0x2e;
static const Shortint CSIFrame = 0x40;
static const Shortint TSIFrame = 0x42;
static const Shortint FTTFrame = 0x44;
static const Shortint RTNFrame = 0x4c;
static const Shortint MPSFrame = 0x4e;
static const Byte DISFrame = 0x80;
static const Byte DCSFrame = 0x82;
static const Byte CFRFrame = 0x84;
static const Byte MCFFrame = 0x8c;
static const Byte EOMFrame = 0x8e;
static const Byte DCNFrame = 0xfa;
static const Byte RTPFrame = 0xcc;
static const Word DataBufferSize = 0x1000;
static const Shortint DISGroup1 = 0x0;
static const Shortint DISGroup3_1 = 0x2;
static const Byte DISGroup3_2 = 0x88;
static const Shortint DISGroup3_3 = 0x0;
static const Shortint DISHighResolution = 0x40;
static const Shortint DIS2400BPS = 0x0;
static const Shortint DIS4800BPS = 0x8;
static const Shortint DIS7200BPS = 0xc;
static const Shortint DIS9600BPS = 0x4;
static const Shortint DIS12000BPS = 0x10;
static const Shortint DIS14400BPS = 0x20;
static const Shortint DISWideWidth = 0x1;
static const char AddrField = '\xff';
static const char ControlField = '\x3';
static const char ControlFieldLast = '\x13';
#define C2ClassCmd "CLASS=2"
#define C20ClassCmd "CLASS=2.0"
#define C2ModelCmd "MDL?"
#define C20ModelCmd "MI?"
#define C2MfrCmd "MFR?"
#define C20MfrCmd "MM?"
#define C2RevCmd "REV?"
#define C20RevCmd "MR?"
#define C2DISCmd "DIS"
#define C20DISCmd "IS"
#define C2StationCmd "LID"
#define C20StationCmd "LI"
#define C2DCCCmd "DCC"
#define C20DCCCmd "CC"
#define C2FaxResp "CON"
#define C20FaxResp "CO"
#define C2DISResp "DIS"
#define C20DISResp "IS"
#define C2DCSResp "DCS"
#define C20DCSResp "CS"
#define C2TSIResp "TSI"
#define C20TSIResp "TI"
#define C2CSIResp "CSI"
#define C20CSIResp "CI"
#define C2PageResp "PTS"
#define C20PageResp "PS"
#define C2HangResp "HNG"
#define C20HangResp "HS"
#define DefFaxFileExt "APF"
extern PACKAGE System::Set<char, 0, 255>  DosDelimSet;
extern PACKAGE int __fastcall afInitFaxData(PFaxData &PData,  Oomisc::Str20 &ID, Awuser::TApdBaseDispatcher* ComPort, int Window);
extern PACKAGE int __fastcall afDoneFaxData(PFaxData &PData);
extern PACKAGE void __fastcall afOptionsOn(PFaxRec FP, Word OptionFlags);
extern PACKAGE void __fastcall afOptionsOff(PFaxRec FP, Word OptionFlags);
extern PACKAGE bool __fastcall afOptionsAreOn(PFaxRec FP, Word OptionFlags);
extern PACKAGE void __fastcall afSetConnectAttempts(PFaxRec FP, Word Attempts, Word DelayTicks);
extern PACKAGE void __fastcall afSetNextFax(PFaxRec FP,  System::ShortString &Number,  System::ShortString &FName,  System::ShortString &Cover);
extern PACKAGE void __fastcall afSetComHandle(PFaxRec FP, Awuser::TApdBaseDispatcher* NewHandle);
extern PACKAGE void __fastcall afSetWindow(PFaxRec FP, int NewWindow);
extern PACKAGE void __fastcall afSetTitle(PFaxRec FP,  System::ShortString &NewTitle);
extern PACKAGE void __fastcall afSetRecipientName(PFaxRec FP,  System::ShortString &NewName);
extern PACKAGE void __fastcall afSetSenderName(PFaxRec FP,  System::ShortString &NewName);
extern PACKAGE void __fastcall afSetDestinationDir(PFaxRec FP,  System::ShortString &Dest);
extern PACKAGE void __fastcall afSetStationID(PFaxRec FP,  Oomisc::Str20 &NewID);
extern PACKAGE void __fastcall afFaxStatus(PFaxRec FP, bool Starting, bool Ending);
extern PACKAGE bool __fastcall afNextFax(PFaxRec FP);
extern PACKAGE void __fastcall afLogFax(PFaxRec FP, Oomisc::TFaxLogCode Log);
extern PACKAGE void __fastcall afFaxName(PFaxRec FP);
extern PACKAGE bool __fastcall afAcceptFax(PFaxRec FP,  Oomisc::Str20 &RemoteName);
extern PACKAGE System::ShortString __fastcall afConvertHeaderString(PFaxRec FP,  System::ShortString &S);
extern PACKAGE int __fastcall afAddFaxEntry(PFaxRec FP, const System::ShortString &Number, const System::ShortString &FName, const System::ShortString &Cover);
extern PACKAGE void __fastcall afClearFaxEntries(PFaxRec FP);
extern PACKAGE System::ShortString __fastcall afGetFaxName(PFaxRec FP);
extern PACKAGE void __fastcall afSetFaxName(PFaxRec FP,  System::ShortString &FaxName);
extern PACKAGE Word __fastcall afGetFaxProgress(PFaxRec FP);
extern PACKAGE void __fastcall afReportError(PFaxRec FP, int ErrorCode);
extern PACKAGE void __fastcall afSignalFinish(PFaxRec FP);
extern PACKAGE void __fastcall afStartFax(PFaxRec FP, TFaxPrepProc StartProc, TFaxFunc FaxFunc);
extern PACKAGE void __fastcall afStopFax(PFaxRec FP);
extern PACKAGE char * __fastcall afStatusMsg(char * P, Word Status);
extern PACKAGE bool __fastcall afNextFaxList(PFaxRec FP,  System::ShortString &Number,  System::ShortString &FName,  System::ShortString &Cover);
extern PACKAGE System::ShortString __fastcall afFaxNameMD(PFaxRec FP);
extern PACKAGE System::ShortString __fastcall afFaxNameCount(PFaxRec FP);

}	/* namespace Awabsfax */
using namespace Awabsfax;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AwAbsFax
