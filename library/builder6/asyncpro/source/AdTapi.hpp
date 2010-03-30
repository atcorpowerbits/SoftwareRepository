// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdTapi.pas' rev: 6.00

#ifndef AdTapiHPP
#define AdTapiHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdPort.hpp>	// Pascal unit
#include <AdTSel.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <AwUser.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <AdTUtil.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <MMSystem.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Registry.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adtapi
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TTapiState { tsIdle, tsOffering, tsAccepted, tsDialTone, tsDialing, tsRingback, tsBusy, tsSpecialInfo, tsConnected, tsProceeding, tsOnHold, tsConferenced, tsOnHoldPendConf, tsOnHoldPendTransfer, tsDisconnected, tsUnknown };
#pragma option pop

#pragma option push -b-
enum TWaveState { wsIdle, wsPlaying, wsRecording, wsData };
#pragma option pop

#pragma option push -b-
enum TWaveMessage { waPlayOpen, waPlayDone, waPlayClose, waRecordOpen, waDataReady, waRecordClose };
#pragma option pop

#pragma option push -b-
enum TTapiLogCode { ltapiNone, ltapiCallStart, ltapiCallFinish, ltapiDial, ltapiAccept, ltapiAnswer, ltapiConnect, ltapiCancel, ltapiDrop, ltapiBusy, ltapiDialFail, ltapiReceivedDigit };
#pragma option pop

typedef void __fastcall (__closure *TTapiStatusEvent)(System::TObject* CP, bool First, bool Last, int Device, int Message, int Param1, int Param2, int Param3);

typedef void __fastcall (__closure *TTapiLogEvent)(System::TObject* CP, TTapiLogCode Log);

typedef void __fastcall (__closure *TTapiDTMFEvent)(System::TObject* CP, char Digit, int ErrorCode);

typedef void __fastcall (__closure *TTapiCallerIDEvent)(System::TObject* CP, AnsiString ID, AnsiString IDName);

typedef void __fastcall (__closure *TTapiWaveNotify)(System::TObject* CP, TWaveMessage Msg);

typedef void __fastcall (__closure *TTapiWaveSilence)(System::TObject* CP, bool &StopRecording, bool &Hangup);

class DELPHICLASS TApdCustomTapiDevice;
class DELPHICLASS TApdAbstractTapiStatus;
class PASCALIMPLEMENTATION TApdAbstractTapiStatus : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	bool FAnswering;
	AnsiString FCaption;
	bool FCtl3D;
	Forms::TForm* FDisplay;
	Forms::TPosition FPosition;
	bool FVisible;
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	TApdCustomTapiDevice* FTapiDevice;
	void __fastcall SetPosition(const Forms::TPosition NewPosition);
	void __fastcall SetCtl3D(const bool NewCtl3D);
	void __fastcall SetVisible(const bool NewVisible);
	void __fastcall SetCaption(const AnsiString NewCaption);
	void __fastcall GetProperties(void);
	void __fastcall Show(void);
	
public:
	__fastcall virtual TApdAbstractTapiStatus(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdAbstractTapiStatus(void);
	virtual void __fastcall UpdateDisplay(bool First, bool Last, unsigned Device, unsigned Message, unsigned Param1, unsigned Param2, unsigned Param3) = 0 ;
	DYNAMIC void __fastcall CreateDisplay(void) = 0 ;
	DYNAMIC void __fastcall DestroyDisplay(void) = 0 ;
	__property bool Answering = {read=FAnswering, write=FAnswering, nodefault};
	__property Forms::TForm* Display = {read=FDisplay, write=FDisplay};
	
__published:
	__property Forms::TPosition Position = {read=FPosition, write=SetPosition, nodefault};
	__property bool Ctl3D = {read=FCtl3D, write=SetCtl3D, nodefault};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
	__property TApdCustomTapiDevice* TapiDevice = {read=FTapiDevice, write=FTapiDevice};
	__property AnsiString Caption = {read=FCaption, write=SetCaption};
};


class DELPHICLASS TApdTapiLog;
class PASCALIMPLEMENTATION TApdTapiLog : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	AnsiString FTapiHistoryName;
	TApdCustomTapiDevice* FTapiDevice;
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	
public:
	__fastcall virtual TApdTapiLog(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdTapiLog(void);
	virtual void __fastcall UpdateLog(const TTapiLogCode Log);
	
__published:
	__property AnsiString TapiHistoryName = {read=FTapiHistoryName, write=FTapiHistoryName};
	__property TApdCustomTapiDevice* TapiDevice = {read=FTapiDevice, write=FTapiDevice};
};


class PASCALIMPLEMENTATION TApdCustomTapiDevice : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	int LineApp;
	Adtutil::TLineExtensionID LineExt;
	int LineHandle;
	int CallHandle;
	int SelectedLine;
	Adtutil::TVarString VS;
	Extctrls::TTimer* DialTimer;
	int RequestedId;
	int AsyncReply;
	int CallState;
	bool ReplyReceived;
	bool CallStateReceived;
	bool TapiInUse;
	bool TapiHasOpened;
	bool Initializing;
	bool Connected;
	bool StoppingCall;
	bool ShuttingDown;
	bool RetryPending;
	bool TapiFailFired;
	bool ReplyWait;
	bool StateWait;
	bool PassThruMode;
	wavehdr_tag *WaveOutHeader;
	wavehdr_tag *WaveInHeader;
	int WaveOutHandle;
	int WaveInHandle;
	int BytesRecorded;
	int TotalBytesRecorded;
	void *WaveInBuffer1;
	void *WaveInBuffer2;
	void *WaveOutBuffer1;
	void *WaveOutBuffer2;
	Byte ActiveBuffer;
	int MmioInHandle;
	int MmioOutHandle;
	_MMCKINFO RootChunk;
	_MMCKINFO DataChunk;
	AnsiString TempFileName;
	Byte Channels;
	Byte BitsPerSample;
	int SamplesPerSecond;
	int WaveInBufferSize;
	int BytesToPlay;
	int BytesPlayed;
	int BytesInBuffer;
	Byte ActiveWaveOutBuffer;
	int WaveOutBufferSize;
	int FAvgWaveInAmplitude;
	bool FCancelled;
	bool FDialing;
	int FDialTime;
	Classes::TStrings* FTapiDevices;
	AnsiString FSelectedDevice;
	int FApiVersion;
	unsigned FDeviceCount;
	unsigned FTrueDeviceCount;
	bool FOpen;
	Adtutil::TCallInfo *FCallInfo;
	Adport::TApdCustomComPort* FComPort;
	TApdAbstractTapiStatus* FStatusDisplay;
	TApdTapiLog* FTapiLog;
	AnsiString FNumber;
	Word FMaxAttempts;
	Word FAttempt;
	Word FRetryWait;
	Byte FAnsRings;
	HWND FParentHWnd;
	bool FShowTapiDevices;
	bool FShowPorts;
	bool FEnableVoice;
	int FMaxMessageLength;
	AnsiString FWaveFileName;
	bool FInterruptWave;
	HWND FHandle;
	TWaveState FWaveState;
	bool FUseSoundCard;
	Adtutil::TLineMonitorTone FSilence;
	Byte FTrimSeconds;
	int FSilenceThreshold;
	bool FMonitorRecording;
	int FFailCode;
	bool FFilterUnsupportedDevices;
	bool FWaitingForCall;
	TTapiCallerIDEvent FOnTapiCallerID;
	Classes::TNotifyEvent FOnTapiConnect;
	TTapiDTMFEvent FOnTapiDTMF;
	Classes::TNotifyEvent FOnTapiFail;
	TTapiLogEvent FOnTapiLog;
	Classes::TNotifyEvent FOnTapiPortClose;
	Classes::TNotifyEvent FOnTapiPortOpen;
	TTapiStatusEvent FOnTapiStatus;
	TTapiWaveNotify FOnTapiWaveNotify;
	TTapiWaveSilence FOnTapiWaveSilence;
	virtual void __fastcall DoLineCallInfo(int Device, int P1, int P2, int P3);
	virtual void __fastcall DoLineCallState(int Device, int P1, int P2, int P3);
	virtual void __fastcall DoLineClose(int Device, int P1, int P2, int P3);
	virtual void __fastcall DoLineCreate(int Device, int P1, int P2, int P3);
	virtual void __fastcall DoLineDevState(int Device, int P1, int P2, int P3);
	virtual void __fastcall DoLineGenerate(int Device, int P1, int P2, int P3);
	virtual void __fastcall DoLineMonitorDigits(int Device, int P1, int P2, int P3);
	virtual void __fastcall DoLineMonitorMedia(int Device, int P1, int P2, int P3);
	virtual void __fastcall DoLineMonitorTone(int Device, int P1, int P2, int P3);
	virtual void __fastcall DoLineReply(int Device, int P1, int P2, int P3);
	virtual void __fastcall DoLineRequest(int Device, int P1, int P2, int P3);
	bool __fastcall HandleLineErr(int LineErr);
	bool __fastcall HangupCall(bool AbortRetries);
	void __fastcall UpdateCallInfo(int Device);
	int __fastcall WaitForCallState(int DesiredCallState);
	int __fastcall WaitForReply(int ID);
	void __fastcall SetOpen(bool NewOpen);
	void __fastcall AssureTapiReady(void);
	int __fastcall CidFromTapiDevice(void);
	void __fastcall CheckVoiceCapable(void);
	void __fastcall CheckWaveException(int ErrorCode, int Mode);
	void __fastcall CheckWaveInSilence(void);
	bool __fastcall CloseTapiPort(void);
	void __fastcall CloseWaveFile(void);
	void __fastcall CreateDialTimer(void);
	int __fastcall DeviceIDFromName(const AnsiString Name);
	void __fastcall DialPrim(bool PassThru);
	void __fastcall EnumLineDevices(void);
	void __fastcall FreeWaveInBuffers(void);
	void __fastcall FreeWaveOutBuffer(void);
	int __fastcall GetSelectedLine(void);
	unsigned __fastcall GetWaveDeviceId(const bool Play);
	void __fastcall LoadWaveOutBuffer(void);
	void __fastcall MonitorDTMF(int &CallHandle, const int DTMFMode);
	void __fastcall OpenTapiPort(void);
	void __fastcall OpenWaveFile(void);
	void __fastcall PlayWaveOutBuffer(void);
	void __fastcall PrepareWaveInHeader(void);
	bool __fastcall StartTapi(void);
	bool __fastcall StopTapi(void);
	void __fastcall TapiDialTimer(System::TObject* Sender);
	void __fastcall WndProc(Messages::TMessage &Message);
	void __fastcall WriteWaveBuffer(void);
	unsigned __fastcall GetBPSRate(void);
	AnsiString __fastcall GetCalledID();
	AnsiString __fastcall GetCalledIDName();
	AnsiString __fastcall GetCallerID();
	AnsiString __fastcall GetCallerIDName();
	int __fastcall GetComNumber(void);
	HWND __fastcall GetParentHWnd(void);
	TTapiState __fastcall GetTapiState(void);
	void __fastcall SetStatusDisplay(const TApdAbstractTapiStatus* NewDisplay);
	void __fastcall SetTapiLog(const TApdTapiLog* NewLog);
	void __fastcall SetTapiDevices(const Classes::TStrings* Values);
	void __fastcall SetSelectedDevice(const AnsiString NewDevice);
	void __fastcall SetEnableVoice(bool Value);
	void __fastcall SetMonitorRecording(const bool Value);
	void __fastcall SetFilterUnsupportedDevices(const bool Value);
	__property bool Open = {read=FOpen, write=SetOpen, nodefault};
	void __fastcall TapiStatus(bool First, bool Last, unsigned Device, unsigned Message, unsigned Param1, unsigned Param2, unsigned Param3);
	void __fastcall TapiLogging(TTapiLogCode Log);
	void __fastcall TapiPortOpen(void);
	void __fastcall TapiPortClose(void);
	void __fastcall TapiConnect(void);
	void __fastcall TapiFail(void);
	void __fastcall TapiDTMF(char Digit, int ErrorCode);
	void __fastcall TapiCallerID(AnsiString ID, AnsiString IDName);
	void __fastcall TapiWave(TWaveMessage Msg);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TApdCustomTapiDevice(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomTapiDevice(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	void __fastcall Dial(AnsiString ANumber);
	void __fastcall AutoAnswer(void);
	void __fastcall ConfigAndOpen(void);
	bool __fastcall CancelCall(void);
	void __fastcall CopyCallInfo(Adtutil::PCallInfo &CallInfo);
	Oomisc::TTapiConfigRec __fastcall GetDevConfig();
	int __fastcall MontorTones(const Adtutil::TLineMonitorTones * Tones, const int Tones_Size);
	void __fastcall SetDevConfig(const Oomisc::TTapiConfigRec &Config);
	void __fastcall PlayWaveFile(AnsiString FileName);
	void __fastcall StopWaveFile(void);
	void __fastcall StartWaveRecord(void);
	void __fastcall StopWaveRecord(void);
	void __fastcall SaveWaveFile(AnsiString FileName, bool Overwrite);
	void __fastcall SetRecordingParams(Byte NumChannels, int NumSamplesPerSecond, Byte NumBitsPerSample);
	void __fastcall ShowConfigDialog(void);
	Oomisc::TTapiConfigRec __fastcall ShowConfigDialogEdit(const Oomisc::TTapiConfigRec &Init);
	Controls::TModalResult __fastcall SelectDevice(void);
	void __fastcall SendTone(AnsiString Digits);
	void __fastcall Transfer(AnsiString aNumber);
	void __fastcall HoldCall(void);
	void __fastcall UnHoldCall(void);
	void __fastcall AutomatedVoicetoComms(void);
	AnsiString __fastcall TapiStatusMsg(const unsigned Message, const unsigned State, const unsigned Reason);
	AnsiString __fastcall FailureCodeMsg(const int FailureCode);
	AnsiString __fastcall TranslateAddress(AnsiString CanonicalAddr);
	int __fastcall TranslateAddressEx(AnsiString CanonicalAddr, int Flags, AnsiString &DialableStr, AnsiString &DisplayableStr, int &CurrentCountry, int &DestCountry, int &TranslateResults);
	bool __fastcall TranslateDialog(AnsiString CanonicalAddr);
	AnsiString __fastcall TapiLogToString(const TTapiLogCode LogCode);
	__property int ApiVersion = {read=FApiVersion, nodefault};
	__property Word Attempt = {read=FAttempt, nodefault};
	__property unsigned BPSRate = {read=GetBPSRate, nodefault};
	__property AnsiString CalledID = {read=GetCalledID};
	__property AnsiString CalledIDName = {read=GetCalledIDName};
	__property AnsiString CallerID = {read=GetCallerID};
	__property AnsiString CallerIDName = {read=GetCallerIDName};
	__property bool Cancelled = {read=FCancelled, nodefault};
	__property int ComNumber = {read=GetComNumber, nodefault};
	__property bool Dialing = {read=FDialing, nodefault};
	__property int FailureCode = {read=FFailCode, nodefault};
	__property bool WaitingForCall = {read=FWaitingForCall, nodefault};
	__property Classes::TStrings* TapiDevices = {read=FTapiDevices, write=SetTapiDevices};
	__property AnsiString SelectedDevice = {read=FSelectedDevice, write=SetSelectedDevice};
	__property Adport::TApdCustomComPort* ComPort = {read=FComPort, write=FComPort};
	__property TApdAbstractTapiStatus* StatusDisplay = {read=FStatusDisplay, write=SetStatusDisplay};
	__property TApdTapiLog* TapiLog = {read=FTapiLog, write=SetTapiLog};
	__property Byte AnswerOnRing = {read=FAnsRings, write=FAnsRings, default=2};
	__property Word MaxAttempts = {read=FMaxAttempts, write=FMaxAttempts, default=3};
	__property Word RetryWait = {read=FRetryWait, write=FRetryWait, default=60};
	__property bool ShowTapiDevices = {read=FShowTapiDevices, write=FShowTapiDevices, nodefault};
	__property bool ShowPorts = {read=FShowPorts, write=FShowPorts, nodefault};
	__property bool EnableVoice = {read=FEnableVoice, write=SetEnableVoice, nodefault};
	__property bool InterruptWave = {read=FInterruptWave, write=FInterruptWave, nodefault};
	__property bool UseSoundCard = {read=FUseSoundCard, write=FUseSoundCard, nodefault};
	__property Byte TrimSeconds = {read=FTrimSeconds, write=FTrimSeconds, nodefault};
	__property int SilenceThreshold = {read=FSilenceThreshold, write=FSilenceThreshold, nodefault};
	__property bool MonitorRecording = {read=FMonitorRecording, write=SetMonitorRecording, nodefault};
	__property HWND ParentHWnd = {read=GetParentHWnd, write=FParentHWnd, nodefault};
	__property bool FilterUnsupportedDevices = {read=FFilterUnsupportedDevices, write=SetFilterUnsupportedDevices, default=1};
	__property AnsiString Number = {read=FNumber};
	__property unsigned DeviceCount = {read=FDeviceCount, nodefault};
	__property TTapiState TapiState = {read=GetTapiState, nodefault};
	__property AnsiString WaveFileName = {read=FWaveFileName};
	__property int MaxMessageLength = {read=FMaxMessageLength, write=FMaxMessageLength, default=60};
	__property TWaveState WaveState = {read=FWaveState, nodefault};
	__property int AvgWaveInAmplitude = {read=FAvgWaveInAmplitude, nodefault};
	__property TTapiStatusEvent OnTapiStatus = {read=FOnTapiStatus, write=FOnTapiStatus};
	__property TTapiLogEvent OnTapiLog = {read=FOnTapiLog, write=FOnTapiLog};
	__property Classes::TNotifyEvent OnTapiPortOpen = {read=FOnTapiPortOpen, write=FOnTapiPortOpen};
	__property Classes::TNotifyEvent OnTapiPortClose = {read=FOnTapiPortClose, write=FOnTapiPortClose};
	__property Classes::TNotifyEvent OnTapiConnect = {read=FOnTapiConnect, write=FOnTapiConnect};
	__property Classes::TNotifyEvent OnTapiFail = {read=FOnTapiFail, write=FOnTapiFail};
	__property TTapiDTMFEvent OnTapiDTMF = {read=FOnTapiDTMF, write=FOnTapiDTMF};
	__property TTapiCallerIDEvent OnTapiCallerID = {read=FOnTapiCallerID, write=FOnTapiCallerID};
	__property TTapiWaveNotify OnTapiWaveNotify = {read=FOnTapiWaveNotify, write=FOnTapiWaveNotify};
	__property TTapiWaveSilence OnTapiWaveSilence = {read=FOnTapiWaveSilence, write=FOnTapiWaveSilence};
};


class DELPHICLASS TApdTapiDevice;
class PASCALIMPLEMENTATION TApdTapiDevice : public TApdCustomTapiDevice 
{
	typedef TApdCustomTapiDevice inherited;
	
__published:
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
	/* TApdCustomTapiDevice.Create */ inline __fastcall virtual TApdTapiDevice(Classes::TComponent* AOwner) : TApdCustomTapiDevice(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomTapiDevice.Destroy */ inline __fastcall virtual ~TApdTapiDevice(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint Success = 0x0;
static const Shortint WaitErr_WaitAborted = 0x1;
static const Shortint WaitErr_WaitTimedOut = 0x2;
static const Shortint LineCallState_Any = 0x0;
static const Word WaitTimeout = 0x7530;
static const Word TapiErrorBase = 0x35e8;
static const Word TapiStatusBase = 0x34bc;
static const Shortint lcsBase = 0x0;
static const Shortint ldsBase = 0x20;
static const Shortint lrBase = 0x40;
static const Shortint asBase = 0x60;
static const Byte lcsdBase = 0x96;
#define DefTapiHistoryName "APROTAPI.HIS"
static const Shortint DefMaxAttempts = 0x3;
static const Shortint DefAnsRings = 0x2;
static const Shortint DefRetryWait = 0x3c;
static const bool DefShowTapiDevices = true;
static const bool DefShowPorts = true;
static const Shortint DefMaxMessageLength = 0x3c;
#define DefWaveState (TWaveState)(0)
static const bool DefUseSoundCard = false;
static const Shortint DefTrimSeconds = 0x2;
static const Shortint DefSilenceThreshold = 0x32;
static const Shortint DefChannels = 0x1;
static const Shortint DefBitsPerSample = 0x10;
static const Word DefSamplesPerSecond = 0x1f40;
static const bool DefMonitorRecording = false;
static const Shortint WaveInError = 0x1;
static const Shortint WaveOutError = 0x2;
static const Shortint MMioError = 0x3;
static const Shortint BufferSeconds = 0x1;
static const Shortint WaveOutBufferSeconds = 0x3;

}	/* namespace Adtapi */
using namespace Adtapi;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdTapi
