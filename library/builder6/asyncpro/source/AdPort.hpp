// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdPort.pas' rev: 6.00

#ifndef AdPortHPP
#define AdPortHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdSelCom.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <AwWin32.hpp>	// Pascal unit
#include <AwUser.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adport
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TParity { pNone, pOdd, pEven, pMark, pSpace };
#pragma option pop

typedef Awuser::TApdBaseDispatcher* __fastcall (*TActivationProcedure)(System::TObject* Owner);

#pragma option push -b-
enum TDeviceLayer { dlWin32, dlWinsock };
#pragma option pop

typedef Set<TDeviceLayer, dlWin32, dlWinsock>  TDeviceLayers;

typedef int TBaudRate;

#pragma option push -b-
enum TTapiMode { tmNone, tmAuto, tmOn, tmOff };
#pragma option pop

#pragma option push -b-
enum TPortState { psClosed, psShuttingDown, psOpen };
#pragma option pop

#pragma option push -b-
enum THWFlowOptions { hwfUseDTR, hwfUseRTS, hwfRequireDSR, hwfRequireCTS };
#pragma option pop

typedef Set<THWFlowOptions, hwfUseDTR, hwfRequireCTS>  THWFlowOptionSet;

#pragma option push -b-
enum TSWFlowOptions { swfNone, swfReceive, swfTransmit, swfBoth };
#pragma option pop

#pragma option push -b-
enum TFlowControlState { fcOff, fcOn, fcDsrHold, fcCtsHold, fcDcdHold, fcXOutHold, fcXInHold, fcXBothHold };
#pragma option pop

#pragma option push -b-
enum TTraceLogState { tlOff, tlOn, tlDump, tlAppend, tlClear, tlPause };
#pragma option pop

typedef void __fastcall (__closure *TTriggerEvent)(System::TObject* CP, Word Msg, Word TriggerHandle, Word Data);

typedef void __fastcall (__closure *TTriggerAvailEvent)(System::TObject* CP, Word Count);

typedef void __fastcall (__closure *TTriggerDataEvent)(System::TObject* CP, Word TriggerHandle);

typedef void __fastcall (__closure *TTriggerStatusEvent)(System::TObject* CP, Word TriggerHandle);

typedef void __fastcall (__closure *TTriggerTimerEvent)(System::TObject* CP, Word TriggerHandle);

typedef void __fastcall (__closure *TTriggerLineErrorEvent)(System::TObject* CP, Word Error, bool LineBreak);

typedef void __fastcall (__closure *TWaitCharEvent)(System::TObject* CP, char C);

typedef void __fastcall (__closure *TPortCallback)(System::TObject* CP, bool Opening);

#pragma option push -b-
enum TApdCallbackType { ctOpen, ctClosing, ctClosed };
#pragma option pop

typedef void __fastcall (__closure *TPortCallbackEx)(System::TObject* CP, TApdCallbackType CallbackType);

struct TUserListEntry;
typedef TUserListEntry *PUserListEntry;

struct TUserListEntry
{
	unsigned Handle;
	TPortCallback OpenClose;
	TPortCallbackEx OpenCloseEx;
	bool IsEx;
} ;

#pragma option push -b-
enum TApThreadBoost { tbNone, tbPlusOne, tbPlusTwo };
#pragma option pop

class DELPHICLASS TApdCustomComPort;
class PASCALIMPLEMENTATION TApdCustomComPort : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	bool Force;
	TPortState PortState;
	bool OpenPending;
	bool ForceOpen;
	Classes::TList* UserList;
	bool CopyTriggers;
	Oomisc::TTriggerSave SaveTriggerBuffer;
	bool BusyBeforeWait;
	bool WaitPrepped;
	unsigned fComWindow;
	TActivationProcedure fCustomDispatcher;
	Controls::TWinControl* FMasterTerminal;
	TDeviceLayer FDeviceLayer;
	TDeviceLayers FDeviceLayers;
	Awuser::TApdBaseDispatcher* FDispatcher;
	Word FComNumber;
	int FBaud;
	TParity FParity;
	Word FDatabits;
	Word FStopbits;
	Word FInSize;
	Word FOutSize;
	bool FOpen;
	bool FPromptForPort;
	bool FAutoOpen;
	Word FCommNotificationLevel;
	Word FTapiCid;
	TTapiMode FTapiMode;
	bool FRS485Mode;
	TApThreadBoost FThreadBoost;
	bool FDTR;
	bool FRTS;
	Word FBufferFull;
	Word FBufferResume;
	THWFlowOptionSet FHWFlowOptions;
	TSWFlowOptions FSWFlowOptions;
	char FXOnChar;
	char FXOffChar;
	TTraceLogState FTracing;
	unsigned FTraceSize;
	AnsiString FTraceName;
	bool FTraceHex;
	bool FTraceAllHex;
	TTraceLogState FLogging;
	unsigned FLogSize;
	AnsiString FLogName;
	bool FLogHex;
	bool FLogAllHex;
	bool FUseMSRShadow;
	bool FUseEventWord;
	Word FTriggerLength;
	TTriggerEvent FOnTrigger;
	TTriggerAvailEvent FOnTriggerAvail;
	TTriggerDataEvent FOnTriggerData;
	TTriggerStatusEvent FOnTriggerStatus;
	TTriggerTimerEvent FOnTriggerTimer;
	TTriggerLineErrorEvent FOnTriggerLineError;
	Classes::TNotifyEvent FOnTriggerModemStatus;
	Classes::TNotifyEvent FOnTriggerOutbuffFree;
	Classes::TNotifyEvent FOnTriggerOutbuffUsed;
	Classes::TNotifyEvent FOnTriggerOutSent;
	Classes::TNotifyEvent FOnPortOpen;
	Classes::TNotifyEvent FOnPortClose;
	TWaitCharEvent FOnWaitChar;
	void __fastcall SetDeviceLayer(const TDeviceLayer NewDevice);
	void __fastcall SetComNumber(const Word NewNumber);
	void __fastcall SetBaud(const int NewBaud);
	void __fastcall SetParity(const TParity NewParity);
	void __fastcall SetDatabits(const Word NewBits);
	void __fastcall SetStopbits(const Word NewBits);
	void __fastcall SetInSize(const Word NewSize);
	void __fastcall SetOutSize(const Word NewSize);
	void __fastcall SetTracing(const TTraceLogState NewState);
	void __fastcall SetTraceSize(const unsigned NewSize);
	void __fastcall SetLogging(const TTraceLogState NewState);
	void __fastcall SetLogSize(const unsigned NewSize);
	void __fastcall SetOpen(const bool Enable);
	void __fastcall SetHWFlowOptions(const THWFlowOptionSet NewOpts);
	TFlowControlState __fastcall GetFlowState(void);
	void __fastcall SetSWFlowOptions(const TSWFlowOptions NewOpts);
	void __fastcall SetXonChar(const char NewChar);
	void __fastcall SetXoffChar(const char NewChar);
	void __fastcall SetBufferFull(const Word NewFull);
	void __fastcall SetBufferResume(const Word NewResume);
	void __fastcall SetTriggerLength(const Word NewLength);
	void __fastcall SetDTR(const bool NewDTR);
	void __fastcall SetRTS(const bool NewRTS);
	void __fastcall SetOnTrigger(const TTriggerEvent Value);
	void __fastcall SetOnTriggerAvail(const TTriggerAvailEvent Value);
	void __fastcall SetOnTriggerData(const TTriggerDataEvent Value);
	void __fastcall SetOnTriggerStatus(const TTriggerStatusEvent Value);
	void __fastcall SetOnTriggerTimer(const TTriggerTimerEvent Value);
	void __fastcall SetOnTriggerLineError(const TTriggerLineErrorEvent Value);
	void __fastcall SetOnTriggerModemStatus(const Classes::TNotifyEvent Value);
	void __fastcall SetOnTriggerOutbuffFree(const Classes::TNotifyEvent Value);
	void __fastcall SetOnTriggerOutbuffUsed(const Classes::TNotifyEvent Value);
	void __fastcall SetOnTriggerOutSent(const Classes::TNotifyEvent Value);
	Word __fastcall GetBaseAddress(void);
	Awuser::TApdBaseDispatcher* __fastcall GetDispatcher(void);
	Byte __fastcall GetModemStatus(void);
	bool __fastcall GetDSR(void);
	bool __fastcall GetCTS(void);
	bool __fastcall GetRI(void);
	bool __fastcall GetDCD(void);
	bool __fastcall GetDeltaDSR(void);
	bool __fastcall GetDeltaCTS(void);
	bool __fastcall GetDeltaRI(void);
	bool __fastcall GetDeltaDCD(void);
	Word __fastcall GetLineError(void);
	bool __fastcall GetLineBreak(void);
	Word __fastcall GetInBuffUsed(void);
	Word __fastcall GetInBuffFree(void);
	Word __fastcall GetOutBuffUsed(void);
	Word __fastcall GetOutBuffFree(void);
	void __fastcall SetUseEventWord(bool NewUse);
	void __fastcall SetCommNotificationLevel(Word NewLevel);
	void __fastcall SetRS485Mode(bool NewMode);
	void __fastcall SetBaseAddress(Word NewBaseAddress);
	void __fastcall SetThreadBoost(TApThreadBoost NewBoost);
	virtual Awuser::TApdBaseDispatcher* __fastcall ActivateDeviceLayer(void);
	virtual void __fastcall DeviceLayerChanged(void);
	virtual int __fastcall InitializePort(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall RegisterComPort(bool Enabling);
	virtual void __fastcall ValidateComport(void);
	virtual void __fastcall SetUseMSRShadow(bool NewUse);
	virtual void __fastcall Trigger(Word Msg, Word TriggerHandle, Word Data);
	virtual void __fastcall TriggerAvail(Word Count);
	virtual void __fastcall TriggerData(Word TriggerHandle);
	virtual void __fastcall TriggerStatus(Word TriggerHandle);
	virtual void __fastcall TriggerTimer(Word TriggerHandle);
	virtual void __fastcall UpdateHandlerFlag(void);
	DYNAMIC void __fastcall PortOpen(void);
	DYNAMIC void __fastcall PortClose(void);
	DYNAMIC void __fastcall PortClosing(void);
	virtual void __fastcall TriggerLineError(const Word Error, const bool LineBreak);
	virtual void __fastcall TriggerModemStatus(void);
	virtual void __fastcall TriggerOutbuffFree(void);
	virtual void __fastcall TriggerOutbuffUsed(void);
	virtual void __fastcall TriggerOutSent(void);
	virtual void __fastcall WaitChar(char C);
	void __fastcall InitTracing(const unsigned NumEntries);
	void __fastcall DumpTrace(const System::ShortString &FName, const bool InHex);
	void __fastcall AppendTrace(const System::ShortString &FName, const bool InHex);
	void __fastcall ClearTracing(void);
	void __fastcall AbortTracing(void);
	void __fastcall StartTracing(void);
	void __fastcall StopTracing(void);
	void __fastcall InitLogging(const unsigned Size);
	void __fastcall DumpLog(const System::ShortString &FName, const bool InHex);
	void __fastcall AppendLog(const System::ShortString &FName, const bool InHex);
	void __fastcall ClearLogging(void);
	void __fastcall AbortLogging(void);
	void __fastcall StartLogging(void);
	void __fastcall StopLogging(void);
	
public:
	bool OverrideLine;
	__fastcall virtual TApdCustomComPort(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomComPort(void);
	DYNAMIC void __fastcall InitPort(void);
	virtual void __fastcall DonePort(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	void __fastcall ForcePortOpen(void);
	void __fastcall SendBreak(Word Ticks, bool Yield);
	void __fastcall SetBreak(bool BreakOn);
	void __fastcall RegisterUser(const unsigned H);
	void __fastcall RegisterUserEx(const unsigned H);
	void __fastcall RegisterUserCallback(TPortCallback CallBack);
	void __fastcall RegisterUserCallbackEx(TPortCallbackEx CallBackEx);
	void __fastcall DeregisterUser(const unsigned H);
	void __fastcall DeregisterUserCallback(TPortCallback CallBack);
	void __fastcall DeregisterUserCallbackEx(TPortCallbackEx CallBackEx);
	virtual void __fastcall ProcessCommunications(void);
	void __fastcall FlushInBuffer(void);
	void __fastcall FlushOutBuffer(void);
	Word __fastcall AddDataTrigger(const System::ShortString &Data, const bool IgnoreCase);
	Word __fastcall AddTimerTrigger(void);
	Word __fastcall AddStatusTrigger(const Word SType);
	void __fastcall RemoveTrigger(const Word Handle);
	void __fastcall RemoveAllTriggers(void);
	void __fastcall SetTimerTrigger(const Word Handle, const int Ticks, const bool Activate);
	void __fastcall SetStatusTrigger(const Word Handle, const Word Value, const bool Activate);
	bool __fastcall CharReady(void);
	char __fastcall PeekChar(const Word Count);
	char __fastcall GetChar(void);
	void __fastcall PeekBlock(void *Block, const Word Len);
	void __fastcall GetBlock(void *Block, const Word Len);
	void __fastcall PutChar(const char C);
	void __fastcall PutString(const AnsiString S);
	int __fastcall PutBlock(const void *Block, const Word Len);
	bool __fastcall CheckForString(Byte &Index, char C, const AnsiString S, bool IgnoreCase);
	bool __fastcall WaitForString(const AnsiString S, const int Timeout, const bool Yield, const bool IgnoreCase);
	int __fastcall WaitForMultiString(const AnsiString S, const int Timeout, const bool Yield, const bool IgnoreCase, const char SepChar);
	void __fastcall PrepareWait(void);
	__property Word ComNumber = {read=FComNumber, write=SetComNumber, default=0};
	__property TActivationProcedure CustomDispatcher = {read=fCustomDispatcher, write=fCustomDispatcher};
	__property TDeviceLayer DeviceLayer = {read=FDeviceLayer, write=SetDeviceLayer, default=0};
	__property unsigned ComWindow = {read=fComWindow, nodefault};
	__property int Baud = {read=FBaud, write=SetBaud, default=19200};
	__property TParity Parity = {read=FParity, write=SetParity, default=0};
	__property bool PromptForPort = {read=FPromptForPort, write=FPromptForPort, default=1};
	__property Word DataBits = {read=FDatabits, write=SetDatabits, default=8};
	__property Word StopBits = {read=FStopbits, write=SetStopbits, default=1};
	__property Word InSize = {read=FInSize, write=SetInSize, default=4096};
	__property Word OutSize = {read=FOutSize, write=SetOutSize, default=4096};
	__property bool Open = {read=FOpen, write=SetOpen, default=0};
	__property bool AutoOpen = {read=FAutoOpen, write=FAutoOpen, default=1};
	__property Word CommNotificationLevel = {read=FCommNotificationLevel, write=SetCommNotificationLevel, default=10};
	__property TTapiMode TapiMode = {read=FTapiMode, write=FTapiMode, default=1};
	__property Word TapiCid = {read=FTapiCid, write=FTapiCid, nodefault};
	__property bool RS485Mode = {read=FRS485Mode, write=SetRS485Mode, default=0};
	__property Word BaseAddress = {read=GetBaseAddress, write=SetBaseAddress, default=0};
	__property TApThreadBoost ThreadBoost = {read=FThreadBoost, write=SetThreadBoost, nodefault};
	__property Controls::TWinControl* MasterTerminal = {read=FMasterTerminal, write=FMasterTerminal};
	__property bool DTR = {read=FDTR, write=SetDTR, default=1};
	__property bool RTS = {read=FRTS, write=SetRTS, default=1};
	__property THWFlowOptionSet HWFlowOptions = {read=FHWFlowOptions, write=SetHWFlowOptions, default=0};
	__property TFlowControlState FlowState = {read=GetFlowState, nodefault};
	__property TSWFlowOptions SWFlowOptions = {read=FSWFlowOptions, write=SetSWFlowOptions, default=0};
	__property char XOnChar = {read=FXOnChar, write=SetXonChar, default=17};
	__property char XOffChar = {read=FXOffChar, write=SetXoffChar, default=19};
	__property Word BufferFull = {read=FBufferFull, write=SetBufferFull, default=0};
	__property Word BufferResume = {read=FBufferResume, write=SetBufferResume, default=0};
	__property TTraceLogState Tracing = {read=FTracing, write=SetTracing, default=0};
	__property unsigned TraceSize = {read=FTraceSize, write=SetTraceSize, default=10000};
	__property AnsiString TraceName = {read=FTraceName, write=FTraceName};
	__property bool TraceHex = {read=FTraceHex, write=FTraceHex, default=1};
	__property bool TraceAllHex = {read=FTraceAllHex, write=FTraceAllHex, default=0};
	__property TTraceLogState Logging = {read=FLogging, write=SetLogging, default=0};
	__property unsigned LogSize = {read=FLogSize, write=SetLogSize, default=10000};
	__property AnsiString LogName = {read=FLogName, write=FLogName};
	__property bool LogHex = {read=FLogHex, write=FLogHex, default=1};
	__property bool LogAllHex = {read=FLogAllHex, write=FLogAllHex, default=0};
	__property bool UseMSRShadow = {read=FUseMSRShadow, write=SetUseMSRShadow, default=1};
	__property bool UseEventWord = {read=FUseEventWord, write=SetUseEventWord, default=1};
	void __fastcall AddTraceEntry(const char CurEntry, const char CurCh);
	void __fastcall AddStringToLog(AnsiString S);
	__property Word TriggerLength = {read=FTriggerLength, write=SetTriggerLength, default=1};
	__property TTriggerEvent OnTrigger = {read=FOnTrigger, write=SetOnTrigger};
	__property TTriggerAvailEvent OnTriggerAvail = {read=FOnTriggerAvail, write=SetOnTriggerAvail};
	__property TTriggerDataEvent OnTriggerData = {read=FOnTriggerData, write=SetOnTriggerData};
	__property TTriggerStatusEvent OnTriggerStatus = {read=FOnTriggerStatus, write=SetOnTriggerStatus};
	__property TTriggerTimerEvent OnTriggerTimer = {read=FOnTriggerTimer, write=SetOnTriggerTimer};
	__property Classes::TNotifyEvent OnPortOpen = {read=FOnPortOpen, write=FOnPortOpen};
	__property Classes::TNotifyEvent OnPortClose = {read=FOnPortClose, write=FOnPortClose};
	__property TTriggerLineErrorEvent OnTriggerLineError = {read=FOnTriggerLineError, write=SetOnTriggerLineError};
	__property Classes::TNotifyEvent OnTriggerModemStatus = {read=FOnTriggerModemStatus, write=SetOnTriggerModemStatus};
	__property Classes::TNotifyEvent OnTriggerOutbuffFree = {read=FOnTriggerOutbuffFree, write=SetOnTriggerOutbuffFree};
	__property Classes::TNotifyEvent OnTriggerOutbuffUsed = {read=FOnTriggerOutbuffUsed, write=SetOnTriggerOutbuffUsed};
	__property Classes::TNotifyEvent OnTriggerOutSent = {read=FOnTriggerOutSent, write=SetOnTriggerOutSent};
	__property TWaitCharEvent OnWaitChar = {read=FOnWaitChar, write=FOnWaitChar};
	__property AnsiString Output = {write=PutString};
	__property Awuser::TApdBaseDispatcher* Dispatcher = {read=GetDispatcher};
	Awuser::TApdBaseDispatcher* __fastcall ValidDispatcher(void);
	__property Byte ModemStatus = {read=GetModemStatus, nodefault};
	__property bool DSR = {read=GetDSR, nodefault};
	__property bool CTS = {read=GetCTS, nodefault};
	__property bool RI = {read=GetRI, nodefault};
	__property bool DCD = {read=GetDCD, nodefault};
	__property bool DeltaDSR = {read=GetDeltaDSR, nodefault};
	__property bool DeltaCTS = {read=GetDeltaCTS, nodefault};
	__property bool DeltaRI = {read=GetDeltaRI, nodefault};
	__property bool DeltaDCD = {read=GetDeltaDCD, nodefault};
	__property Word LineError = {read=GetLineError, nodefault};
	__property bool LineBreak = {read=GetLineBreak, nodefault};
	__property Word InBuffUsed = {read=GetInBuffUsed, nodefault};
	__property Word InBuffFree = {read=GetInBuffFree, nodefault};
	__property Word OutBuffUsed = {read=GetOutBuffUsed, nodefault};
	__property Word OutBuffFree = {read=GetOutBuffFree, nodefault};
};


class DELPHICLASS TApdComPort;
class PASCALIMPLEMENTATION TApdComPort : public TApdCustomComPort 
{
	typedef TApdCustomComPort inherited;
	
__published:
	__property DeviceLayer  = {default=0};
	__property ComNumber  = {default=0};
	__property Baud  = {default=19200};
	__property PromptForPort  = {default=1};
	__property Parity  = {default=0};
	__property DataBits  = {default=8};
	__property StopBits  = {default=1};
	__property InSize  = {default=4096};
	__property OutSize  = {default=4096};
	__property AutoOpen  = {default=1};
	__property Open  = {default=0};
	__property DTR  = {default=1};
	__property RTS  = {default=1};
	__property HWFlowOptions  = {default=0};
	__property SWFlowOptions  = {default=0};
	__property XOnChar  = {default=17};
	__property XOffChar  = {default=19};
	__property BufferFull  = {default=0};
	__property BufferResume  = {default=0};
	__property Tracing  = {default=0};
	__property TraceSize  = {default=10000};
	__property TraceName ;
	__property TraceHex  = {default=1};
	__property TraceAllHex  = {default=0};
	__property Logging  = {default=0};
	__property LogSize  = {default=10000};
	__property LogName ;
	__property LogHex  = {default=1};
	__property LogAllHex  = {default=0};
	__property UseMSRShadow  = {default=1};
	__property UseEventWord  = {default=1};
	__property CommNotificationLevel  = {default=10};
	__property TapiMode  = {default=1};
	__property RS485Mode  = {default=0};
	__property OnPortClose ;
	__property OnPortOpen ;
	__property OnTrigger ;
	__property OnTriggerAvail ;
	__property OnTriggerData ;
	__property OnTriggerStatus ;
	__property OnTriggerTimer ;
	__property OnTriggerLineError ;
	__property OnTriggerModemStatus ;
	__property OnTriggerOutbuffFree ;
	__property OnTriggerOutbuffUsed ;
	__property OnTriggerOutSent ;
	__property Tag  = {default=0};
public:
	#pragma option push -w-inl
	/* TApdCustomComPort.Create */ inline __fastcall virtual TApdComPort(Classes::TComponent* AOwner) : TApdCustomComPort(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomComPort.Destroy */ inline __fastcall virtual ~TApdComPort(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE System::SmallString<5>  ParityName[5];
#define adpoDefDeviceLayer (TDeviceLayer)(0)
static const bool adpoDefPromptForPort = true;
static const Shortint adpoDefComNumber = 0x0;
static const Word adpoDefBaudRt = 0x4b00;
#define adpoDefParity (TParity)(0)
static const Shortint adpoDefDatabits = 0x8;
static const Shortint adpoDefStopbits = 0x1;
static const Word adpoDefInSize = 0x1000;
static const Word adpoDefOutSize = 0x1000;
static const bool adpoDefOpen = false;
static const bool adpoDefAutoOpen = true;
static const Shortint adpoDefBaseAddress = 0x0;
#define adpoDefTapiMode (TTapiMode)(1)
static const bool adpoDefDTR = true;
static const bool adpoDefRTS = true;
#define adpoDefTracing (TTraceLogState)(0)
static const Word adpoDefTraceSize = 0x2710;
#define adpoDefTraceName "APRO.TRC"
static const bool adpoDefTraceHex = true;
static const bool adpoDefTraceAllHex = false;
#define adpoDefLogging (TTraceLogState)(0)
static const Word adpoDefLogSize = 0x2710;
#define adpoDefLogName "APRO.LOG"
static const bool adpoDefLogHex = true;
static const bool adpoDefLogAllHex = false;
static const bool adpoDefUseMSRShadow = true;
static const bool adpoDefUseEventWord = true;
#define adpoDefSWFlowOptions (TSWFlowOptions)(0)
static const char adpoDefXonChar = '\x11';
static const char adpoDefXoffChar = '\x13';
static const Shortint adpoDefBufferFull = 0x0;
static const Shortint adpoDefBufferResume = 0x0;
static const Shortint adpoDefTriggerLength = 0x1;
static const Shortint adpoDefCommNotificationLevel = 0xa;
static const bool adpoDefRS485Mode = false;
extern PACKAGE TApdCustomComPort* __fastcall SearchComPort(const Classes::TComponent* C);
extern PACKAGE System::ShortString __fastcall ComName(const Word ComNumber);

}	/* namespace Adport */
using namespace Adport;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdPort
