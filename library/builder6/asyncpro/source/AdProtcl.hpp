// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdProtcl.pas' rev: 6.00

#ifndef AdProtclHPP
#define AdProtclHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdPort.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <AwAscii.hpp>	// Pascal unit
#include <AwKermit.hpp>	// Pascal unit
#include <AwZmodem.hpp>	// Pascal unit
#include <AwYmodem.hpp>	// Pascal unit
#include <AwXmodem.hpp>	// Pascal unit
#include <AwAbsPcl.hpp>	// Pascal unit
#include <AwTPcl.hpp>	// Pascal unit
#include <AwUser.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adprotcl
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TBlockCheckMethod { bcmNone, bcmChecksum, bcmChecksum2, bcmCrc16, bcmCrc32, bcmCrcK };
#pragma option pop

#pragma option push -b-
enum TProtocolType { ptNoProtocol, ptXmodem, ptXmodemCRC, ptXmodem1K, ptXmodem1KG, ptYmodem, ptYmodemG, ptZmodem, ptKermit, ptAscii };
#pragma option pop

#pragma option push -b-
enum TZmodemFileOptions { zfoNoOption, zfoWriteNewerLonger, zfoWriteCrc, zfoWriteAppend, zfoWriteClobber, zfoWriteNewer, zfoWriteDifferent, zfoWriteProtect };
#pragma option pop

#pragma option push -b-
enum TWriteFailAction { wfWriteNone, wfWriteFail, wfWriteRename, wfWriteAnyway, wfWriteResume };
#pragma option pop

#pragma option push -b-
enum TAsciiEOLTranslation { aetNone, aetStrip, aetAddCRBefore, aetAddLFAfter };
#pragma option pop

#pragma option push -b-
enum TDeleteFailed { dfNever, dfAlways, dfNonRecoverable };
#pragma option pop

typedef void __fastcall (__closure *TProtocolErrorEvent)(System::TObject* CP, int ErrorCode);

typedef void __fastcall (__closure *TProtocolFinishEvent)(System::TObject* CP, int ErrorCode);

typedef void __fastcall (__closure *TProtocolLogEvent)(System::TObject* CP, Word Log);

typedef void __fastcall (__closure *TProtocolResumeEvent)(System::TObject* CP, TWriteFailAction &Resume);

typedef void __fastcall (__closure *TProtocolStatusEvent)(System::TObject* CP, Word Options);

typedef void __fastcall (__closure *TProtocolNextFileEvent)(System::TObject* CP, AnsiString &FName);

typedef void __fastcall (__closure *TProtocolAcceptEvent)(System::TObject* CP, bool &Accept, AnsiString &FName);

class DELPHICLASS TApdCustomProtocol;
class DELPHICLASS TApdAbstractStatus;
class PASCALIMPLEMENTATION TApdAbstractStatus : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	Forms::TForm* FDisplay;
	Forms::TPosition FPosition;
	bool FCtl3D;
	bool FVisible;
	AnsiString FCaption;
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	TApdCustomProtocol* FProtocol;
	void __fastcall SetPosition(const Forms::TPosition NewPosition);
	void __fastcall SetCtl3D(const bool NewCtl3D);
	void __fastcall SetVisible(const bool NewVisible);
	void __fastcall SetCaption(const AnsiString NewCaption);
	void __fastcall GetProperties(void);
	void __fastcall Show(void);
	
public:
	__fastcall virtual TApdAbstractStatus(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdAbstractStatus(void);
	virtual void __fastcall UpdateDisplay(bool First, bool Last) = 0 ;
	DYNAMIC void __fastcall CreateDisplay(void) = 0 ;
	DYNAMIC void __fastcall DestroyDisplay(void) = 0 ;
	__property Forms::TForm* Display = {read=FDisplay, write=FDisplay};
	
__published:
	__property Forms::TPosition Position = {read=FPosition, write=SetPosition, nodefault};
	__property bool Ctl3D = {read=FCtl3D, write=SetCtl3D, nodefault};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
	__property TApdCustomProtocol* Protocol = {read=FProtocol, write=FProtocol};
	__property AnsiString Caption = {read=FCaption, write=SetCaption};
};


class DELPHICLASS TApdProtocolLog;
class PASCALIMPLEMENTATION TApdProtocolLog : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	TDeleteFailed FDeleteFailed;
	AnsiString FHistoryName;
	TApdCustomProtocol* FProtocol;
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	
public:
	__fastcall virtual TApdProtocolLog(Classes::TComponent* AOwner);
	virtual void __fastcall UpdateLog(const unsigned Log);
	
__published:
	__property TApdCustomProtocol* Protocol = {read=FProtocol, write=FProtocol};
	__property TDeleteFailed DeleteFailed = {read=FDeleteFailed, write=FDeleteFailed, default=2};
	__property AnsiString HistoryName = {read=FHistoryName, write=FHistoryName};
public:
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TApdProtocolLog(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TApdCustomProtocol : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	bool NeedBPS;
	Awtpcl::TProtocolFunc ProtFunc;
	bool Force;
	HWND FMsgHandler;
	Adport::TApdCustomComPort* FComPort;
	TProtocolType FProtocolType;
	TApdAbstractStatus* FStatusDisplay;
	TApdProtocolLog* FProtocolLog;
	unsigned FXYmodemBlockWait;
	bool FZmodemOptionOverride;
	bool FZmodemSkipNoFile;
	TZmodemFileOptions FZmodemFileOption;
	bool FZmodemRecover;
	bool FZmodem8K;
	int FZmodemZRQINITValue;
	unsigned FZmodemFinishRetry;
	unsigned FKermitMaxLen;
	unsigned FKermitMaxWindows;
	unsigned FKermitSWCTurnDelay;
	unsigned FKermitTimeoutSecs;
	char FKermitPadCharacter;
	unsigned FKermitPadCount;
	char FKermitTerminator;
	char FKermitCtlPrefix;
	char FKermitHighbitPrefix;
	char FKermitRepeatPrefix;
	unsigned FAsciiCharDelay;
	unsigned FAsciiLineDelay;
	char FAsciiEOLChar;
	TAsciiEOLTranslation FAsciiCRTranslation;
	TAsciiEOLTranslation FAsciiLFTranslation;
	unsigned FAsciiEOFTimeout;
	TProtocolAcceptEvent FOnProtocolAccept;
	TProtocolErrorEvent FOnProtocolError;
	TProtocolFinishEvent FOnProtocolFinish;
	TProtocolLogEvent FOnProtocolLog;
	TProtocolNextFileEvent FOnProtocolNextFile;
	TProtocolResumeEvent FOnProtocolResume;
	TProtocolStatusEvent FOnProtocolStatus;
	void __fastcall CreateMessageHandler(void);
	void __fastcall CheckPort(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	void __fastcall SetComPort(const Adport::TApdCustomComPort* NewComPort);
	void __fastcall SetProtocolType(const TProtocolType NewProtocol);
	AnsiString __fastcall GetDestinationDirectory();
	void __fastcall SetDestinationDirectory(const AnsiString NewDir);
	AnsiString __fastcall GetFileMask();
	void __fastcall SetFileMask(const AnsiString NewFileMask);
	bool __fastcall GetBatch(void);
	TBlockCheckMethod __fastcall GetBlockCheckMethod(void);
	void __fastcall SetBlockCheckMethod(const TBlockCheckMethod NewMethod);
	unsigned __fastcall GetHandshakeRetry(void);
	void __fastcall SetHandshakeRetry(const unsigned NewRetry);
	unsigned __fastcall GetHandshakeWait(void);
	void __fastcall SetHandshakeWait(const unsigned NewWait);
	unsigned __fastcall GetBlockLength(void);
	unsigned __fastcall GetBlockNumber(void);
	unsigned __fastcall GetTransmitTimeout(void);
	void __fastcall SetTransmitTimeout(const unsigned NewTimeout);
	unsigned __fastcall GetFinishWait(void);
	void __fastcall SetFinishWait(const unsigned NewWait);
	int __fastcall GetActualBPS(void);
	void __fastcall SetActualBPS(const int NewBPS);
	unsigned __fastcall GetTurnDelay(void);
	void __fastcall SetTurnDelay(const unsigned NewDelay);
	unsigned __fastcall GetOverhead(void);
	void __fastcall SetOverhead(const unsigned NewOverhead);
	TWriteFailAction __fastcall GetWriteFailAction(void);
	void __fastcall SetWriteFailAction(const TWriteFailAction NewAction);
	unsigned __fastcall GetProtocolStatus(void);
	short __fastcall GetProtocolError(void);
	int __fastcall GetFileLength(void);
	System::TDateTime __fastcall GetFileDate(void);
	int __fastcall GetInitialPosition(void);
	unsigned __fastcall GetStatusInterval(void);
	void __fastcall SetStatusInterval(const unsigned NewInterval);
	void __fastcall SetStatusDisplay(const TApdAbstractStatus* NewDisplay);
	void __fastcall SetProtocolLog(const TApdProtocolLog* NewLog);
	bool __fastcall GetInProgress(void);
	unsigned __fastcall GetBlockErrors(void);
	unsigned __fastcall GetTotalErrors(void);
	int __fastcall GetBytesRemaining(void);
	int __fastcall GetBytesTransferred(void);
	int __fastcall GetElapsedTicks(void);
	AnsiString __fastcall GetFileName();
	void __fastcall SetFileName(const AnsiString NewName);
	unsigned __fastcall GetXYmodemBlockWait(void);
	void __fastcall SetXYmodemBlockWait(const unsigned NewWait);
	bool __fastcall GetYModem128ByteBlocks(void);
	void __fastcall SetYModem128ByteBlocks(const bool Value);
	bool __fastcall GetZmodemOptionOverride(void);
	void __fastcall SetZmodemOptionOverride(const bool NewOverride);
	bool __fastcall GetZmodemSkipNoFile(void);
	void __fastcall SetZmodemSkipNoFile(const bool NewSkip);
	TZmodemFileOptions __fastcall GetZmodemFileOption(void);
	void __fastcall SetZmodemFileOption(const TZmodemFileOptions NewOpt);
	bool __fastcall GetZmodemRecover(void);
	void __fastcall SetZmodemRecover(const bool NewRecover);
	bool __fastcall GetZmodem8K(void);
	void __fastcall SetZmodem8K(const bool New8K);
	int __fastcall GetZmodemZRQINITValue(void);
	void __fastcall SetZmodemZRQINITValue(const int NewZRQINITValue);
	unsigned __fastcall GetZmodemFinishRetry(void);
	void __fastcall SetZmodemFinishRetry(const unsigned NewRetry);
	unsigned __fastcall GetKermitMaxLen(void);
	void __fastcall SetKermitMaxLen(const unsigned NewLen);
	unsigned __fastcall GetKermitMaxWindows(void);
	void __fastcall SetKermitMaxWindows(const unsigned NewMax);
	unsigned __fastcall GetKermitSWCTurnDelay(void);
	void __fastcall SetKermitSWCTurnDelay(const unsigned NewDelay);
	unsigned __fastcall GetKermitTimeoutSecs(void);
	void __fastcall SetKermitTimeoutSecs(const unsigned NewTimeout);
	char __fastcall GetKermitPadCharacter(void);
	void __fastcall SetKermitPadCharacter(char NewChar);
	unsigned __fastcall GetKermitPadCount(void);
	void __fastcall SetKermitPadCount(unsigned NewCount);
	char __fastcall GetKermitTerminator(void);
	void __fastcall SetKermitTerminator(const char NewTerminator);
	char __fastcall GetKermitCtlPrefix(void);
	void __fastcall SetKermitCtlPrefix(const char NewPrefix);
	char __fastcall GetKermitHighbitPrefix(void);
	void __fastcall SetKermitHighbitPrefix(const char NewPrefix);
	char __fastcall GetKermitRepeatPrefix(void);
	void __fastcall SetKermitRepeatPrefix(const char NewPrefix);
	unsigned __fastcall GetKermitWindowsTotal(void);
	unsigned __fastcall GetKermitWindowsUsed(void);
	bool __fastcall GetKermitLongBlocks(void);
	unsigned __fastcall GetAsciiCharDelay(void);
	void __fastcall SetAsciiCharDelay(const unsigned NewDelay);
	unsigned __fastcall GetAsciiLineDelay(void);
	void __fastcall SetAsciiLineDelay(const unsigned NewDelay);
	char __fastcall GetAsciiEOLChar(void);
	void __fastcall SetAsciiEOLChar(const char NewChar);
	TAsciiEOLTranslation __fastcall GetAsciiCRTranslation(void);
	void __fastcall SetAsciiCRTranslation(const TAsciiEOLTranslation NewTrans);
	TAsciiEOLTranslation __fastcall GetAsciiLFTranslation(void);
	void __fastcall SetAsciiLFTranslation(const TAsciiEOLTranslation NewTrans);
	unsigned __fastcall GetAsciiEOFTimeout(void);
	void __fastcall SetAsciiEOFTimeout(const unsigned NewTimeout);
	bool __fastcall GetHonorDirectory(void);
	void __fastcall SetHonorDirectory(const bool NewOpt);
	bool __fastcall GetIncludeDirectory(void);
	void __fastcall SetIncludeDirectory(const bool NewOpt);
	bool __fastcall GetRTSLowForWrite(void);
	void __fastcall SetRTSLowForWrite(const bool NewOpt);
	bool __fastcall GetAbortNoCarrier(void);
	void __fastcall SetAbortNoCarrier(const bool NewOpt);
	bool __fastcall GetBP2KTransmit(void);
	void __fastcall SetBP2KTransmit(const bool NewOpt);
	bool __fastcall GetAsciiSuppressCtrlZ(void);
	void __fastcall SetAsciiSuppressCtrlZ(const bool NewOpt);
	bool __fastcall GetUpcaseFileNames(void);
	void __fastcall SetUpcaseFileNames(bool NewUpcase);
	void __fastcall apwPortCallbackEx(System::TObject* CP, Adport::TApdCallbackType CallbackType);
	virtual void __fastcall apwProtocolAccept(System::TObject* CP, bool &Accept, AnsiString &FName);
	virtual void __fastcall apwProtocolError(System::TObject* CP, int ErrorCode);
	virtual void __fastcall apwProtocolFinish(System::TObject* CP, int ErrorCode);
	virtual void __fastcall apwProtocolLog(System::TObject* CP, unsigned Log);
	virtual void __fastcall apwProtocolNextFile(System::TObject* CP, AnsiString &FName);
	virtual void __fastcall apwProtocolResume(System::TObject* CP, TWriteFailAction &Resume);
	virtual void __fastcall apwProtocolStatus(System::TObject* CP, unsigned Options);
	
public:
	Awtpcl::TProtocolData *PData;
	__fastcall virtual TApdCustomProtocol(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomProtocol(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	int __fastcall EstimateTransferSecs(const int Size);
	AnsiString __fastcall StatusMsg(const unsigned Status);
	void __fastcall StartTransmit(void);
	void __fastcall StartReceive(void);
	void __fastcall CancelProtocol(void);
	__property Adport::TApdCustomComPort* ComPort = {read=FComPort, write=SetComPort};
	__property TProtocolType ProtocolType = {read=FProtocolType, write=SetProtocolType, nodefault};
	__property AnsiString DestinationDirectory = {read=GetDestinationDirectory, write=SetDestinationDirectory};
	__property AnsiString FileMask = {read=GetFileMask, write=SetFileMask};
	__property TBlockCheckMethod BlockCheckMethod = {read=GetBlockCheckMethod, write=SetBlockCheckMethod, nodefault};
	__property unsigned HandshakeRetry = {read=GetHandshakeRetry, write=SetHandshakeRetry, default=10};
	__property unsigned HandshakeWait = {read=GetHandshakeWait, write=SetHandshakeWait, default=182};
	__property unsigned TransmitTimeout = {read=GetTransmitTimeout, write=SetTransmitTimeout, default=1092};
	__property unsigned FinishWait = {read=GetFinishWait, write=SetFinishWait, default=364};
	__property int ActualBPS = {read=GetActualBPS, write=SetActualBPS, nodefault};
	__property unsigned TurnDelay = {read=GetTurnDelay, write=SetTurnDelay, default=0};
	__property unsigned Overhead = {read=GetOverhead, write=SetOverhead, default=0};
	__property TWriteFailAction WriteFailAction = {read=GetWriteFailAction, write=SetWriteFailAction, default=2};
	__property bool HonorDirectory = {read=GetHonorDirectory, write=SetHonorDirectory, default=0};
	__property bool IncludeDirectory = {read=GetIncludeDirectory, write=SetIncludeDirectory, default=0};
	__property bool RTSLowForWrite = {read=GetRTSLowForWrite, write=SetRTSLowForWrite, default=0};
	__property bool AbortNoCarrier = {read=GetAbortNoCarrier, write=SetAbortNoCarrier, default=0};
	__property bool BP2KTransmit = {read=GetBP2KTransmit, write=SetBP2KTransmit, default=0};
	__property bool AsciiSuppressCtrlZ = {read=GetAsciiSuppressCtrlZ, write=SetAsciiSuppressCtrlZ, default=0};
	__property bool UpcaseFileNames = {read=GetUpcaseFileNames, write=SetUpcaseFileNames, default=1};
	__property bool Batch = {read=GetBatch, nodefault};
	__property unsigned BlockLength = {read=GetBlockLength, nodefault};
	__property unsigned BlockNumber = {read=GetBlockNumber, nodefault};
	__property unsigned ProtocolStatus = {read=GetProtocolStatus, nodefault};
	__property short ProtocolError = {read=GetProtocolError, nodefault};
	__property int FileLength = {read=GetFileLength, nodefault};
	__property System::TDateTime FileDate = {read=GetFileDate};
	__property int InitialPosition = {read=GetInitialPosition, nodefault};
	__property TApdAbstractStatus* StatusDisplay = {read=FStatusDisplay, write=SetStatusDisplay};
	__property TApdProtocolLog* ProtocolLog = {read=FProtocolLog, write=SetProtocolLog};
	__property unsigned StatusInterval = {read=GetStatusInterval, write=SetStatusInterval, default=18};
	__property bool InProgress = {read=GetInProgress, nodefault};
	__property unsigned BlockErrors = {read=GetBlockErrors, nodefault};
	__property unsigned TotalErrors = {read=GetTotalErrors, nodefault};
	__property int BytesRemaining = {read=GetBytesRemaining, nodefault};
	__property int BytesTransferred = {read=GetBytesTransferred, nodefault};
	__property int ElapsedTicks = {read=GetElapsedTicks, nodefault};
	__property AnsiString FileName = {read=GetFileName, write=SetFileName};
	__property unsigned XYmodemBlockWait = {read=GetXYmodemBlockWait, write=SetXYmodemBlockWait, default=91};
	__property bool YModem128ByteBlocks = {read=GetYModem128ByteBlocks, write=SetYModem128ByteBlocks, default=0};
	__property bool ZmodemOptionOverride = {read=GetZmodemOptionOverride, write=SetZmodemOptionOverride, default=0};
	__property bool ZmodemSkipNoFile = {read=GetZmodemSkipNoFile, write=SetZmodemSkipNoFile, default=0};
	__property TZmodemFileOptions ZmodemFileOption = {read=GetZmodemFileOption, write=SetZmodemFileOption, default=5};
	__property bool ZmodemRecover = {read=GetZmodemRecover, write=SetZmodemRecover, default=0};
	__property bool Zmodem8K = {read=GetZmodem8K, write=SetZmodem8K, default=0};
	__property int ZmodemZRQINITValue = {read=GetZmodemZRQINITValue, write=SetZmodemZRQINITValue, default=0};
	__property unsigned ZmodemFinishRetry = {read=GetZmodemFinishRetry, write=SetZmodemFinishRetry, default=0};
	__property unsigned KermitMaxLen = {read=GetKermitMaxLen, write=SetKermitMaxLen, default=80};
	__property unsigned KermitMaxWindows = {read=GetKermitMaxWindows, write=SetKermitMaxWindows, default=0};
	__property unsigned KermitSWCTurnDelay = {read=GetKermitSWCTurnDelay, write=SetKermitSWCTurnDelay, default=0};
	__property unsigned KermitTimeoutSecs = {read=GetKermitTimeoutSecs, write=SetKermitTimeoutSecs, default=5};
	__property char KermitPadCharacter = {read=GetKermitPadCharacter, write=SetKermitPadCharacter, default=32};
	__property unsigned KermitPadCount = {read=GetKermitPadCount, write=SetKermitPadCount, default=0};
	__property char KermitTerminator = {read=GetKermitTerminator, write=SetKermitTerminator, default=13};
	__property char KermitCtlPrefix = {read=GetKermitCtlPrefix, write=SetKermitCtlPrefix, default=35};
	__property char KermitHighbitPrefix = {read=GetKermitHighbitPrefix, write=SetKermitHighbitPrefix, default=89};
	__property char KermitRepeatPrefix = {read=GetKermitRepeatPrefix, write=SetKermitRepeatPrefix, default=126};
	__property unsigned KermitWindowsTotal = {read=GetKermitWindowsTotal, nodefault};
	__property unsigned KermitWindowsUsed = {read=GetKermitWindowsUsed, nodefault};
	__property bool KermitLongBlocks = {read=GetKermitLongBlocks, nodefault};
	__property unsigned AsciiCharDelay = {read=GetAsciiCharDelay, write=SetAsciiCharDelay, default=0};
	__property unsigned AsciiLineDelay = {read=GetAsciiLineDelay, write=SetAsciiLineDelay, default=0};
	__property char AsciiEOLChar = {read=GetAsciiEOLChar, write=SetAsciiEOLChar, default=13};
	__property TAsciiEOLTranslation AsciiCRTranslation = {read=GetAsciiCRTranslation, write=SetAsciiCRTranslation, default=0};
	__property TAsciiEOLTranslation AsciiLFTranslation = {read=GetAsciiLFTranslation, write=SetAsciiLFTranslation, default=0};
	__property unsigned AsciiEOFTimeout = {read=GetAsciiEOFTimeout, write=SetAsciiEOFTimeout, default=364};
	__property TProtocolAcceptEvent OnProtocolAccept = {read=FOnProtocolAccept, write=FOnProtocolAccept};
	__property TProtocolErrorEvent OnProtocolError = {read=FOnProtocolError, write=FOnProtocolError};
	__property TProtocolFinishEvent OnProtocolFinish = {read=FOnProtocolFinish, write=FOnProtocolFinish};
	__property TProtocolLogEvent OnProtocolLog = {read=FOnProtocolLog, write=FOnProtocolLog};
	__property TProtocolNextFileEvent OnProtocolNextFile = {read=FOnProtocolNextFile, write=FOnProtocolNextFile};
	__property TProtocolResumeEvent OnProtocolResume = {read=FOnProtocolResume, write=FOnProtocolResume};
	__property TProtocolStatusEvent OnProtocolStatus = {read=FOnProtocolStatus, write=FOnProtocolStatus};
};


class DELPHICLASS TApdProtocol;
class PASCALIMPLEMENTATION TApdProtocol : public TApdCustomProtocol 
{
	typedef TApdCustomProtocol inherited;
	
__published:
	__property ComPort ;
	__property ProtocolType ;
	__property DestinationDirectory ;
	__property FileMask ;
	__property BlockCheckMethod ;
	__property HandshakeRetry  = {default=10};
	__property HandshakeWait  = {default=182};
	__property TransmitTimeout  = {default=1092};
	__property FinishWait  = {default=364};
	__property TurnDelay  = {default=0};
	__property Overhead  = {default=0};
	__property WriteFailAction  = {default=2};
	__property HonorDirectory  = {default=0};
	__property IncludeDirectory  = {default=0};
	__property RTSLowForWrite  = {default=0};
	__property AbortNoCarrier  = {default=0};
	__property BP2KTransmit  = {default=0};
	__property AsciiSuppressCtrlZ  = {default=0};
	__property StatusDisplay ;
	__property ProtocolLog ;
	__property StatusInterval  = {default=18};
	__property FileName ;
	__property XYmodemBlockWait  = {default=91};
	__property ZmodemOptionOverride  = {default=0};
	__property ZmodemSkipNoFile  = {default=0};
	__property ZmodemFileOption  = {default=5};
	__property ZmodemRecover  = {default=0};
	__property Zmodem8K  = {default=0};
	__property ZmodemFinishRetry  = {default=0};
	__property KermitMaxLen  = {default=80};
	__property KermitMaxWindows  = {default=0};
	__property KermitSWCTurnDelay  = {default=0};
	__property KermitTimeoutSecs  = {default=5};
	__property KermitPadCharacter  = {default=32};
	__property KermitPadCount  = {default=0};
	__property KermitTerminator  = {default=13};
	__property KermitCtlPrefix  = {default=35};
	__property KermitHighbitPrefix  = {default=89};
	__property KermitRepeatPrefix  = {default=126};
	__property AsciiCharDelay  = {default=0};
	__property AsciiLineDelay  = {default=0};
	__property AsciiEOLChar  = {default=13};
	__property AsciiCRTranslation  = {default=0};
	__property AsciiLFTranslation  = {default=0};
	__property AsciiEOFTimeout  = {default=364};
	__property UpcaseFileNames  = {default=1};
	__property OnProtocolAccept ;
	__property OnProtocolError ;
	__property OnProtocolFinish ;
	__property OnProtocolLog ;
	__property OnProtocolNextFile ;
	__property OnProtocolResume ;
	__property OnProtocolStatus ;
public:
	#pragma option push -w-inl
	/* TApdCustomProtocol.Create */ inline __fastcall virtual TApdProtocol(Classes::TComponent* AOwner) : TApdCustomProtocol(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomProtocol.Destroy */ inline __fastcall virtual ~TApdProtocol(void) { }
	#pragma option pop
	
};


struct TProtocolWindowNode;
typedef TProtocolWindowNode *PProtocolWindowNode;

#pragma pack(push, 4)
struct TProtocolWindowNode
{
	int pwWindow;
	TApdCustomProtocol* pwProtocol;
} ;
#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
#define awpDefProtocolType (TProtocolType)(7)
static const Shortint awpDefXYmodemBlockWait = 0x5b;
static const bool awpDefYModem128ByteBlocks = false;
static const bool awpDefZmodemOptionOverride = false;
static const bool awpDefZmodemSkipNoFile = false;
#define awpDefZmodemFileOption (TZmodemFileOptions)(5)
static const bool awpDefZmodemRecover = false;
static const bool awpDefZmodem8K = false;
static const Shortint awpDefZmodemZRQINITValue = 0x0;
static const Shortint awpDefZmodemFinishRetry = 0x0;
static const Shortint awpDefKermitMaxLen = 0x50;
static const Shortint awpDefKermitMaxWindows = 0x0;
static const Shortint awpDefKermitSWCTurnDelay = 0x0;
static const Shortint awpDefKermitTimeoutSecs = 0x5;
static const char awpDefKermitPadCharacter = '\x20';
static const Shortint awpDefKermitPadCount = 0x0;
static const char awpDefKermitTerminator = '\xd';
static const char awpDefKermitCtlPrefix = '\x23';
static const char awpDefKermitHighbitPrefix = '\x59';
static const char awpDefKermitRepeatPrefix = '\x7e';
static const Shortint awpDefAsciiCharDelay = 0x0;
static const Shortint awpDefAsciiLineDelay = 0x0;
static const char awpDefAsciiEOLChar = '\xd';
#define awpDefAsciiCRTranslation (TAsciiEOLTranslation)(0)
#define awpDefAsciiLFTranslation (TAsciiEOLTranslation)(0)
static const Word awpDefAsciiEOFTimeout = 0x16c;
static const bool awpDefHonorDirectory = false;
static const bool awpDefIncludeDirectory = false;
static const bool awpDefRTSLowForWrite = false;
static const bool awpDefAbortNoCarrier = false;
static const bool awpDefBP2KTransmit = false;
static const bool awpDefAsciiSuppressCtrlZ = false;
static const Word awpDefFinishWait = 0x16c;
static const Shortint awpDefTurnDelay = 0x0;
static const Shortint awpDefOverhead = 0x0;
#define awpDefWriteFailAction (TWriteFailAction)(2)
static const Shortint awpDefStatusInterval = 0x12;
static const bool awpDefUpcaseFileNames = true;
#define awpDefHistoryName "APRO.HIS"
#define awpDefDeleteFailed (TDeleteFailed)(2)
static const Word MaxKermitLongLen = 0x400;
static const Shortint MaxKermitWindows = 0x1b;
extern PACKAGE AnsiString __fastcall ProtocolName(const TProtocolType ProtocolType);
extern PACKAGE AnsiString __fastcall CheckNameString(const TBlockCheckMethod Check);
extern PACKAGE AnsiString __fastcall FormatMinSec(const int TotalSecs);

}	/* namespace Adprotcl */
using namespace Adprotcl;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdProtcl
