// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AwUser.pas' rev: 6.00

#ifndef AwUserHPP
#define AwUserHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdExcept.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <MMSystem.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Awuser
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TApHandlerFlagUpdate { fuKeepPort, fuEnablePort, fuDisablePort };
#pragma option pop

class DELPHICLASS TApdDispatcherThread;
class DELPHICLASS TApdBaseDispatcher;
class DELPHICLASS TComThread;
class PASCALIMPLEMENTATION TApdDispatcherThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
private:
	TApdBaseDispatcher* H;
	unsigned pMsg;
	unsigned pTrigger;
	int plParam;
	Oomisc::TApdNotifyEvent pTriggerEvent;
	void __fastcall SyncEvent(void);
	
public:
	__fastcall TApdDispatcherThread(TApdBaseDispatcher* Disp);
	void __fastcall SyncNotify(unsigned Msg, unsigned Trigger, int lParam, Oomisc::TApdNotifyEvent Event);
	void __fastcall Sync(Classes::TThreadMethod Method);
public:
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~TApdDispatcherThread(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TComThread : public TApdDispatcherThread 
{
	typedef TApdDispatcherThread inherited;
	
public:
	virtual void __fastcall Execute(void);
public:
	#pragma option push -w-inl
	/* TApdDispatcherThread.Create */ inline __fastcall TComThread(TApdBaseDispatcher* Disp) : TApdDispatcherThread(Disp) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~TComThread(void) { }
	#pragma option pop
	
};


class DELPHICLASS TDispThread;
class PASCALIMPLEMENTATION TDispThread : public TApdDispatcherThread 
{
	typedef TApdDispatcherThread inherited;
	
public:
	virtual void __fastcall Execute(void);
public:
	#pragma option push -w-inl
	/* TApdDispatcherThread.Create */ inline __fastcall TDispThread(TApdBaseDispatcher* Disp) : TApdDispatcherThread(Disp) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~TDispThread(void) { }
	#pragma option pop
	
};


class DELPHICLASS TOutThread;
class PASCALIMPLEMENTATION TOutThread : public TApdDispatcherThread 
{
	typedef TApdDispatcherThread inherited;
	
public:
	virtual void __fastcall Execute(void);
public:
	#pragma option push -w-inl
	/* TApdDispatcherThread.Create */ inline __fastcall TOutThread(TApdBaseDispatcher* Disp) : TApdDispatcherThread(Disp) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~TOutThread(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TApdBaseDispatcher : public System::TObject 
{
	typedef System::TObject inherited;
	
protected:
	System::TObject* fOwner;
	int fHandle;
	bool OpenHandle;
	int CidEx;
	int LastError;
	unsigned InQue;
	unsigned OutQue;
	unsigned ModemStatus;
	_COMSTAT ComStatus;
	#pragma pack(push, 1)
	_DCB DCB;
	#pragma pack(pop)
	
	int LastBaud;
	unsigned Flags;
	bool DTRState;
	bool DTRAuto;
	bool RTSState;
	bool RTSAuto;
	unsigned fDispatcherWindow;
	unsigned LastModemStatus;
	unsigned LastLineErr;
	bool RS485Mode;
	Word BaseAddress;
	bool PortHandlerInstalled;
	bool HandlerServiceNeeded;
	Classes::TList* WndTriggerHandlers;
	Classes::TList* ProcTriggerHandlers;
	Classes::TList* EventTriggerHandlers;
	Classes::TList* TimerTriggers;
	Classes::TList* DataTriggers;
	Classes::TList* StatusTriggers;
	unsigned LastTailData;
	unsigned LastTailLen;
	unsigned LenTrigger;
	bool GlobalStatHit;
	bool InAvailMessage;
	unsigned GetCount;
	unsigned MaxGetCount;
	bool DispatchFull;
	unsigned NotifyTail;
	bool KillThreads;
	TComThread* ComThread;
	TDispThread* fDispThread;
	TOutThread* OutThread;
	Byte ThreadBoost;
	_RTL_CRITICAL_SECTION DataSection;
	_RTL_CRITICAL_SECTION OutputSection;
	_RTL_CRITICAL_SECTION DispSection;
	unsigned ComEvent;
	unsigned ReadyEvent;
	unsigned GeneralEvent;
	unsigned OutputEvent;
	unsigned SentEvent;
	unsigned OutFlushEvent;
	unsigned OutWaitObjects1[2];
	unsigned OutWaitObjects2[2];
	unsigned CurrentEvent;
	bool RingFlag;
	char *OBuffer;
	unsigned OBufHead;
	unsigned OBufTail;
	bool OBufFull;
	char *DBuffer;
	unsigned DBufHead;
	unsigned DBufTail;
	bool fEventBusy;
	bool DeletePending;
	bool ClosePending;
	bool OutSentPending;
	bool TracingOn;
	Oomisc::TTraceRecord *TraceQueue;
	unsigned TraceIndex;
	unsigned TraceMax;
	bool TraceWrapped;
	bool DLoggingOn;
	Byte *DLoggingQueue;
	unsigned DLoggingHead;
	unsigned DLoggingTail;
	unsigned DLoggingFree;
	unsigned DLoggingMax;
	Byte *DLogPopBuf;
	unsigned TimeBase;
	unsigned TimerID;
	unsigned TriggerCounter;
	bool DispActive;
	bool DoDonePortPrim;
	int ActiveThreads;
	void __fastcall ThreadGone(System::TObject* Sender);
	virtual int __fastcall EscapeComFunction(int Func) = 0 ;
	virtual int __fastcall FlushCom(int Queue) = 0 ;
	virtual int __fastcall GetComError(_COMSTAT &Stat) = 0 ;
	virtual unsigned __fastcall GetComEventMask(int EvtMask) = 0 ;
	virtual int __fastcall GetComState(_DCB &DCB) = 0 ;
	virtual int __fastcall ReadCom(char * Buf, int Size) = 0 ;
	virtual int __fastcall SetComState(_DCB &DCB) = 0 ;
	virtual int __fastcall WriteCom(char * Buf, int Size) = 0 ;
	virtual bool __fastcall WaitComEvent(unsigned &EvtMask, Windows::POverlapped lpOverlapped) = 0 ;
	virtual bool __fastcall SetupCom(int InSize, int OutSize) = 0 ;
	bool __fastcall CheckReceiveTriggers(void);
	bool __fastcall CheckStatusTriggers(void);
	bool __fastcall CheckTimerTriggers(void);
	bool __fastcall CheckTriggers(void);
	void __fastcall CreateDispatcherWindow(void);
	virtual void __fastcall DonePortPrim(void);
	int __fastcall DumpDispatchLogPrim(char * FName, bool AppendFile, bool InHex, bool AllHex);
	int __fastcall DumpTracePrim(char * FName, bool AppendFile, bool InHex, bool AllHex);
	bool __fastcall ExtractData(void);
	int __fastcall FindTriggerFromHandle(unsigned TriggerHandle, bool Delete, Oomisc::TTriggerType &T, void * &Trigger);
	unsigned __fastcall GetDispatchTime(void);
	Byte __fastcall GetModemStatusPrim(Byte ClearMask);
	unsigned __fastcall GetTriggerHandle(void);
	void __fastcall MapEventsToMS(int Events);
	int __fastcall PeekBlockPrim(char * Block, unsigned Offset, unsigned Len, unsigned &NewTail);
	int __fastcall PeekCharPrim(char &C, unsigned Count);
	bool __fastcall PopLastDLEntry(Oomisc::TDispatchRecord &DR, Oomisc::PByteBuffer Buffer, unsigned &BufLen);
	bool __fastcall PushDLEntry(void *Buffer, unsigned BufLen);
	void __fastcall RefreshStatus(void);
	void __fastcall ResetStatusHits(void);
	void __fastcall ResetDataTriggers(void);
	bool __fastcall SendNotify(unsigned Msg, unsigned Trigger, unsigned Data);
	int __fastcall SetCommStateFix(_DCB &DCB);
	virtual void __fastcall StartDispatcher(void) = 0 ;
	virtual void __fastcall StopDispatcher(void) = 0 ;
	void __fastcall WaitTxSent(void);
	
public:
	void *DataPointers[3];
	AnsiString DeviceName;
	__property bool Active = {read=DispActive, nodefault};
	__property bool Logging = {read=DLoggingOn, nodefault};
	void __fastcall AddDispatchEntry(Oomisc::TDispatchType DT, Oomisc::TDispatchSubType DST, unsigned Data, void * Buffer, unsigned BufferLen);
	void __fastcall AddStringToLog(AnsiString S);
	__property int ComHandle = {read=CidEx, nodefault};
	virtual int __fastcall OpenCom(char * ComName, unsigned InQueue, unsigned OutQueue) = 0 ;
	virtual int __fastcall CloseCom(void) = 0 ;
	__property unsigned DispatcherWindow = {read=fDispatcherWindow, nodefault};
	__property TDispThread* DispThread = {read=fDispThread};
	__property bool EventBusy = {read=fEventBusy, write=fEventBusy, nodefault};
	__property int Handle = {read=fHandle, nodefault};
	__property System::TObject* Owner = {read=fOwner};
	__fastcall TApdBaseDispatcher(System::TObject* Owner);
	__fastcall virtual ~TApdBaseDispatcher(void);
	void __fastcall AbortDispatchLogging(void);
	void __fastcall AbortTracing(void);
	int __fastcall AddDataTrigger(char * Data, bool IgnoreCase);
	int __fastcall AddDataTriggerLen(char * Data, bool IgnoreCase, unsigned Len);
	int __fastcall AddStatusTrigger(unsigned SType);
	int __fastcall AddTimerTrigger(void);
	void __fastcall AddTraceEntry(char CurEntry, char CurCh);
	int __fastcall AppendDispatchLog(char * FName, bool InHex, bool AllHex);
	int __fastcall AppendTrace(char * FName, bool InHex, bool AllHEx);
	void __fastcall BufferSizes(unsigned &InSize, unsigned &OutSize);
	int __fastcall ChangeBaud(int NewBaud);
	void __fastcall ChangeLengthTrigger(unsigned Length);
	bool __fastcall CheckCTS(void);
	bool __fastcall CheckDCD(void);
	bool __fastcall CheckDeltaCTS(void);
	bool __fastcall CheckDeltaDSR(void);
	bool __fastcall CheckDeltaRI(void);
	bool __fastcall CheckDeltaDCD(void);
	bool __fastcall CheckDSR(void);
	bool __fastcall CheckLineBreak(void);
	bool __fastcall CheckRI(void);
	unsigned __fastcall ClassifyStatusTrigger(unsigned TriggerHandle);
	void __fastcall ClearDispatchLogging(void);
	/*         class method */ static void __fastcall ClearSaveBuffers(TMetaClass* vmt, Oomisc::TTriggerSave &Save);
	int __fastcall ClearTracing(void);
	void __fastcall DeregisterWndTriggerHandler(int HW);
	void __fastcall DeregisterProcTriggerHandler(Oomisc::TApdNotifyProc NP);
	void __fastcall DeregisterEventTriggerHandler(Oomisc::TApdNotifyEvent NP);
	void __fastcall DonePort(void);
	int __fastcall DumpDispatchLog(char * FName, bool InHex, bool AllHex);
	int __fastcall DumpTrace(char * FName, bool InHex, bool AllHex);
	int __fastcall ExtendTimer(unsigned TriggerHandle, int Ticks);
	int __fastcall FlushInBuffer(void);
	int __fastcall FlushOutBuffer(void);
	bool __fastcall CharReady(void);
	Word __fastcall GetBaseAddress(void);
	int __fastcall GetBlock(char * Block, unsigned Len);
	int __fastcall GetChar(char &C);
	int __fastcall GetDataPointer(void * &P, unsigned Index);
	int __fastcall GetFlowOptions(unsigned &HWOpts, unsigned &SWOpts, unsigned &BufferFull, unsigned &BufferResume, char &OnChar, char &OffChar);
	void __fastcall GetLine(int &Baud, Word &Parity, Oomisc::TDatabits &DataBits, Oomisc::TStopbits &StopBits);
	int __fastcall GetLineError(void);
	Byte __fastcall GetModemStatus(void);
	int __fastcall HWFlowOptions(unsigned BufferFull, unsigned BufferResume, unsigned Options);
	int __fastcall HWFlowState(void);
	unsigned __fastcall InBuffUsed(void);
	unsigned __fastcall InBuffFree(void);
	void __fastcall InitDispatchLogging(unsigned QueueSize);
	int __fastcall InitPort(char * AComName, int Baud, unsigned Parity, Oomisc::TDatabits DataBits, Oomisc::TStopbits StopBits, unsigned InSize, unsigned OutSize, unsigned FlowOpts);
	int __fastcall InitSocket(unsigned InSize, unsigned OutSize);
	int __fastcall InitTracing(unsigned NumEntries);
	bool __fastcall OptionsAreOn(unsigned Options);
	void __fastcall OptionsOn(unsigned Options);
	void __fastcall OptionsOff(unsigned Options);
	unsigned __fastcall OutBuffUsed(void);
	unsigned __fastcall OutBuffFree(void);
	int __fastcall PeekBlock(char * Block, unsigned Len);
	int __fastcall PeekChar(char &C, unsigned Count);
	virtual int __fastcall ProcessCommunications(void) = 0 ;
	int __fastcall PutBlock(const void *Block, unsigned Len);
	int __fastcall PutChar(char C);
	int __fastcall PutString(AnsiString S);
	void __fastcall RegisterWndTriggerHandler(int HW);
	void __fastcall RegisterProcTriggerHandler(Oomisc::TApdNotifyProc NP);
	void __fastcall RegisterSyncEventTriggerHandler(Oomisc::TApdNotifyEvent NP);
	void __fastcall RegisterEventTriggerHandler(Oomisc::TApdNotifyEvent NP);
	void __fastcall RemoveAllTriggers(void);
	int __fastcall RemoveTrigger(unsigned TriggerHandle);
	void __fastcall RestoreTriggers(Oomisc::TTriggerSave &Save);
	void __fastcall SaveTriggers(Oomisc::TTriggerSave &Save);
	void __fastcall SetBaseAddress(Word NewBaseAddress);
	void __fastcall SendBreak(unsigned Ticks, bool Yield);
	void __fastcall SetBreak(bool BreakOn);
	virtual void __fastcall SetThreadBoost(Byte Boost);
	int __fastcall SetDataPointer(void * P, unsigned Index);
	int __fastcall SetDtr(bool OnOff);
	void __fastcall SetEventBusy(bool &WasOn, bool SetOn);
	void __fastcall SetRS485Mode(bool OnOff);
	int __fastcall SetRts(bool OnOff);
	int __fastcall SetLine(int Baud, unsigned Parity, Oomisc::TDatabits DataBits, Oomisc::TStopbits StopBits);
	int __fastcall SetModem(bool DTR, bool RTS);
	int __fastcall SetStatusTrigger(unsigned TriggerHandle, unsigned Value, bool Activate);
	int __fastcall SetTimerTrigger(unsigned TriggerHandle, int Ticks, bool Activate);
	int __fastcall SetCommBuffers(int InSize, int OutSize);
	void __fastcall StartDispatchLogging(void);
	void __fastcall StartTracing(void);
	void __fastcall StopDispatchLogging(void);
	void __fastcall StopTracing(void);
	int __fastcall SWFlowChars(char OnChar, char OffChar);
	int __fastcall SWFlowDisable(void);
	int __fastcall SWFlowEnable(unsigned BufferFull, unsigned BufferResume, unsigned Options);
	int __fastcall SWFlowState(void);
	int __fastcall TimerTicksRemaining(unsigned TriggerHandle, int &TicksRemaining);
	virtual void __fastcall UpdateHandlerFlags(TApHandlerFlagUpdate FlagUpdate);
};



typedef TMetaClass*TApdDispatcherClass;

//-- var, const, procedure ---------------------------------------------------
static const Shortint FirstTriggerCounter = 0x1;
static const Word MaxTriggerHandle = 0x1000;
static const Shortint StatusTypeMask = 0x7;
static const Word ThreadStartWait = 0xbb8;
extern PACKAGE Classes::TList* PortList;
extern PACKAGE void * __fastcall GetTComRecPtr(int Cid, TMetaClass* DeviceLayerClass);
extern PACKAGE void __fastcall LockPortList(void);
extern PACKAGE void __fastcall UnlockPortList(void);

}	/* namespace Awuser */
using namespace Awuser;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AwUser
