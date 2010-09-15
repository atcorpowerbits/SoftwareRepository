// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdFaxSrv.pas' rev: 6.00

#ifndef AdFaxSrvHPP
#define AdFaxSrvHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdFIDlg.hpp>	// Pascal unit
#include <AdFStat.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <AdFaxPrn.hpp>	// Pascal unit
#include <AdTapi.hpp>	// Pascal unit
#include <AdPort.hpp>	// Pascal unit
#include <AdFax.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adfaxsrv
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TFaxServerMode { fsmIdle, fsmSend, fsmReceive };
#pragma option pop

typedef void __fastcall (__closure *TFaxServerStatusEvent)(System::TObject* CP, TFaxServerMode FaxMode, bool First, bool Last, Word Status);

typedef void __fastcall (__closure *TFaxServerFatalErrorEvent)(System::TObject* CP, TFaxServerMode FaxMode, int ErrorCode, int HangupCode);

typedef void __fastcall (__closure *TFaxServerFinishEvent)(System::TObject* CP, TFaxServerMode FaxMode, int ErrorCode);

typedef void __fastcall (__closure *TFaxServerPortOpenCloseEvent)(System::TObject* CP, bool Opening);

typedef void __fastcall (__closure *TFaxServerAcceptEvent)(System::TObject* CP, bool &Accept);

typedef void __fastcall (__closure *TFaxServerNameEvent)(System::TObject* CP, AnsiString &Name);

typedef void __fastcall (__closure *TFaxServerLogEvent)(System::TObject* CP, Oomisc::TFaxLogCode LogCode, Oomisc::TFaxServerLogCode ServerCode);

class DELPHICLASS TApdFaxServerManager;
class DELPHICLASS TApdCustomFaxServer;
typedef void __fastcall (__closure *TFaxServerManagerQueriedEvent)(TApdFaxServerManager* Mgr, TApdCustomFaxServer* QueryFrom, const AnsiString JobToSend);

typedef void __fastcall (__closure *TManagerUpdateRecipientEvent)(TApdFaxServerManager* Mgr, AnsiString JobFile, const Oomisc::TFaxJobHeaderRec &JobHeader, Oomisc::TFaxRecipientRec &RecipHeader);

typedef void __fastcall (__closure *TManagerUserGetJobEvent)(TApdFaxServerManager* Mgr, TApdCustomFaxServer* QueryFrom, AnsiString &JobFile, AnsiString &FaxFile, AnsiString &CoverFile, int &RecipientNum);

class DELPHICLASS TFaxListObj;
class PASCALIMPLEMENTATION TFaxListObj : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	int FileTime;
	#pragma pack(push, 1)
	Oomisc::TFaxJobHeaderRec JobHeader;
	#pragma pack(pop)
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TFaxListObj(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TFaxListObj(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdFaxJobHandler;
class PASCALIMPLEMENTATION TApdFaxJobHandler : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
public:
	void __fastcall AddRecipient(AnsiString JobFileName, const Oomisc::TFaxRecipientRec &RecipientInfo);
	void __fastcall MakeJob(AnsiString FaxName, AnsiString CoverName, AnsiString JobName, AnsiString Sender, AnsiString DestName, const Oomisc::TFaxRecipientRec &Recipient);
	Controls::TModalResult __fastcall ShowFaxJobInfoDialog(AnsiString JobFileName, AnsiString DlgCaption);
	void __fastcall ExtractAPF(AnsiString JobFileName, AnsiString FaxName);
	bool __fastcall ExtractCoverFile(AnsiString JobFileName, AnsiString CoverName);
	int __fastcall GetRecipient(AnsiString JobFileName, int Index, Oomisc::TFaxRecipientRec &Recipient);
	void __fastcall GetJobHeader(AnsiString JobFileName, Oomisc::TFaxJobHeaderRec &JobHeader);
	int __fastcall GetRecipientStatus(AnsiString JobFileName, int JobNum);
	void __fastcall CancelRecipient(AnsiString JobFileName, Byte JobNum);
	void __fastcall ConcatFaxes(AnsiString DestFaxFile, const AnsiString * FaxFiles, const int FaxFiles_Size);
	void __fastcall ResetAPJPartials(AnsiString JobFileName, bool ResetAttemptNum);
	void __fastcall ResetAPJStatus(AnsiString JobFileName);
	void __fastcall ResetRecipientStatus(AnsiString JobFileName, Byte JobNum, Byte NewStatus);
	void __fastcall RescheduleJob(AnsiString JobFileName, int JobNum, System::TDateTime NewSchedDT, bool ResetStatus);
public:
	#pragma option push -w-inl
	/* TComponent.Create */ inline __fastcall virtual TApdFaxJobHandler(Classes::TComponent* AOwner) : Oomisc::TApdBaseComponent(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TApdFaxJobHandler(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TApdFaxServerManager : public TApdFaxJobHandler 
{
	typedef TApdFaxJobHandler inherited;
	
private:
	AnsiString FMonitorDir;
	Classes::TStringList* FFaxList;
	AnsiString FJobFileExt;
	bool FPaused;
	Classes::TFileStream* FLockFile;
	bool FDeleteOnComplete;
	bool FFirstGetJob;
	bool FInGetJob;
	TFaxServerManagerQueriedEvent FFaxServerManagerQueriedEvent;
	TManagerUpdateRecipientEvent FManagerUpdateRecipientEvent;
	TManagerUserGetJobEvent FManagerUserGetJobEvent;
	
public:
	__fastcall virtual TApdFaxServerManager(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdFaxServerManager(void);
	AnsiString __fastcall GetNextFax();
	System::TDateTime __fastcall GetSchedTime(AnsiString JobFileName);
	bool __fastcall GetJob(Oomisc::TFaxRecipientRec &Recipient, TApdCustomFaxServer* QueryFrom, AnsiString &JobFileName, AnsiString &FaxFile, AnsiString &CoverFile);
	void __fastcall UpdateStatus(AnsiString JobFileName, Word JobNumber, Word Result, bool Failed);
	void __fastcall Reset(void);
	void __fastcall SetMonitorDir(const AnsiString Value);
	__property Classes::TStringList* FaxList = {read=FFaxList};
	
__published:
	__property bool DeleteOnComplete = {read=FDeleteOnComplete, write=FDeleteOnComplete, nodefault};
	__property AnsiString MonitorDir = {read=FMonitorDir, write=SetMonitorDir};
	__property AnsiString JobFileExt = {read=FJobFileExt, write=FJobFileExt};
	__property bool Paused = {read=FPaused, write=FPaused, default=0};
	__property TFaxServerManagerQueriedEvent OnQueried = {read=FFaxServerManagerQueriedEvent, write=FFaxServerManagerQueriedEvent};
	__property TManagerUpdateRecipientEvent OnRecipientComplete = {read=FManagerUpdateRecipientEvent, write=FManagerUpdateRecipientEvent};
	__property TManagerUserGetJobEvent OnCustomGetJob = {read=FManagerUserGetJobEvent, write=FManagerUserGetJobEvent};
};


class DELPHICLASS TApdFaxClient;
class PASCALIMPLEMENTATION TApdFaxClient : public TApdFaxJobHandler 
{
	typedef TApdFaxJobHandler inherited;
	
private:
	AnsiString FJobName;
	AnsiString FSender;
	AnsiString FCoverFileName;
	AnsiString FJobFileName;
	AnsiString FFaxFileName;
	System::TDateTime __fastcall GetScheduleDateTime(void);
	void __fastcall SetHeaderLine(const AnsiString Value);
	void __fastcall SetHeaderRecipient(const AnsiString Value);
	void __fastcall SetHeaderTitle(const AnsiString Value);
	void __fastcall SetPhoneNumber(const AnsiString Value);
	void __fastcall SetScheduleDateTime(const System::TDateTime Value);
	AnsiString __fastcall GetHeaderLine();
	AnsiString __fastcall GetHeaderRecipient();
	AnsiString __fastcall GetHeaderTitle();
	AnsiString __fastcall GetPhoneNumber();
	
public:
	#pragma pack(push, 1)
	Oomisc::TFaxRecipientRec Recipient;
	#pragma pack(pop)
	
	__fastcall virtual TApdFaxClient(Classes::TComponent* AOwner);
	int __fastcall CopyJobToServer(AnsiString SourceJob, AnsiString DestJob, bool OverWrite);
	void __fastcall MakeFaxJob(void);
	__property System::TDateTime ScheduleDateTime = {read=GetScheduleDateTime, write=SetScheduleDateTime};
	
__published:
	__property AnsiString CoverFileName = {read=FCoverFileName, write=FCoverFileName};
	__property AnsiString FaxFileName = {read=FFaxFileName, write=FFaxFileName};
	__property AnsiString JobFileName = {read=FJobFileName, write=FJobFileName};
	__property AnsiString JobName = {read=FJobName, write=FJobName};
	__property AnsiString Sender = {read=FSender, write=FSender};
	__property AnsiString PhoneNumber = {read=GetPhoneNumber, write=SetPhoneNumber};
	__property AnsiString HeaderLine = {read=GetHeaderLine, write=SetHeaderLine};
	__property AnsiString HeaderRecipient = {read=GetHeaderRecipient, write=SetHeaderRecipient};
	__property AnsiString HeaderTitle = {read=GetHeaderTitle, write=SetHeaderTitle};
public:
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TApdFaxClient(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TApdCustomFaxServer : public Adfax::TApdCustomAbstractFax 
{
	typedef Adfax::TApdCustomAbstractFax inherited;
	
private:
	Adport::TApdCustomComPort* FComPort;
	Adtapi::TApdCustomTapiDevice* FTapiDevice;
	Adfax::TApdAbstractFaxStatus* FStatusDisplay;
	Adfax::TApdFaxLog* FFaxLog;
	Adfax::TApdSendFax* FSendFax;
	Adfax::TApdReceiveFax* FRecvFax;
	Extctrls::TTimer* FSendQueryTimer;
	bool FSoftwareFlow;
	bool FSafeMode;
	bool FExitOnError;
	bool FBlindDial;
	bool FToneDial;
	bool FConstantStatus;
	int FInitBaud;
	int FNormalBaud;
	AnsiString FCoverFile;
	AnsiString FHeaderTitle;
	AnsiString FPhoneNumber;
	AnsiString FHeaderLine;
	AnsiString FHeaderRecipient;
	AnsiString FDestinationDir;
	AnsiString FFaxFile;
	AnsiString FFaxFileExt;
	AnsiString FHeaderSender;
	Adfax::TFaxClass FFaxClass;
	Adfax::TFaxNameMode FFaxNameMode;
	AnsiString FModemInit;
	AnsiString FStationID;
	Word FAnswerOnRing;
	Word FBufferMinimum;
	Word FStatusInterval;
	Word FMaxSendCount;
	bool FMonitoring;
	bool FOldMonitoring;
	Adfaxprn::TApdCustomFaxPrinter* FFaxPrinter;
	bool FPrintOnReceive;
	TFaxServerMode FFaxServerMode;
	bool FFaxInProgress;
	Word FDesiredBPS;
	bool FDesiredECM;
	bool FDetectBusy;
	int FPageLength;
	Word FDelayBetweenSends;
	TApdFaxServerManager* FServerManager;
	int FSendQueryInterval;
	Word FDialAttempts;
	Word FDialWait;
	Word FDialRetryWait;
	AnsiString FDialPrefix;
	Graphics::TFont* FEnhFont;
	Graphics::TFont* FEnhHeaderFont;
	bool FEnhTextEnabled;
	bool WaitingOnTapi;
	Oomisc::TFaxServerLogCode FServerLogCode;
	TFaxServerFatalErrorEvent FFaxServerFatalErrorEvent;
	TFaxServerStatusEvent FFaxServerStatusEvent;
	TFaxServerFinishEvent FFaxServerFinishEvent;
	TFaxServerPortOpenCloseEvent FFaxServerPortOpenCloseEvent;
	TFaxServerAcceptEvent FFaxServerAcceptEvent;
	TFaxServerNameEvent FFaxServerNameEvent;
	TFaxServerLogEvent FFaxServerLogEvent;
	bool FSwitchingModes;
	bool FWaitForRing;
	
protected:
	HIDESBASE void __fastcall SetComPort(const Adport::TApdCustomComPort* Value);
	HIDESBASE void __fastcall SetFaxLog(const Adfax::TApdFaxLog* Value);
	HIDESBASE void __fastcall SetStatusDisplay(const Adfax::TApdAbstractFaxStatus* Value);
	void __fastcall SetAnswerOnRing(const Word Value);
	void __fastcall SetBlindDial(const bool Value);
	void __fastcall SetBufferMinimum(const Word Value);
	void __fastcall SetConstantStatus(const bool Value);
	void __fastcall SetCoverFile(const AnsiString Value);
	void __fastcall SetDestinationDir(const AnsiString Value);
	HIDESBASE void __fastcall SetExitOnError(const bool Value);
	HIDESBASE void __fastcall SetFaxClass(const Adfax::TFaxClass Value);
	virtual void __fastcall SetFaxFile(const AnsiString Value);
	HIDESBASE void __fastcall SetFaxFileExt(const AnsiString Value);
	void __fastcall SetFaxNameMode(const Adfax::TFaxNameMode Value);
	void __fastcall SetHeaderLine(const AnsiString Value);
	void __fastcall SetHeaderRecipient(const AnsiString Value);
	void __fastcall SetHeaderSender(const AnsiString Value);
	void __fastcall SetHeaderTitle(const AnsiString Value);
	HIDESBASE void __fastcall SetInitBaud(const int Value);
	void __fastcall SetMaxSendCount(const Word Value);
	HIDESBASE void __fastcall SetModemInit(const AnsiString Value);
	HIDESBASE void __fastcall SetNormalBaud(const int Value);
	void __fastcall SetPhoneNumber(const AnsiString Value);
	void __fastcall SetSafeMode(const bool Value);
	HIDESBASE void __fastcall SetSoftwareFlow(const bool Value);
	HIDESBASE void __fastcall SetStationID(const AnsiString Value);
	HIDESBASE void __fastcall SetStatusInterval(const Word Value);
	void __fastcall SetToneDial(const bool Value);
	void __fastcall SetMonitoring(const bool Value);
	void __fastcall SetFaxPrinter(const Adfaxprn::TApdCustomFaxPrinter* Value);
	void __fastcall SetPrintOnReceive(const bool Value);
	HIDESBASE void __fastcall SetDesiredBPS(const Word Value);
	HIDESBASE void __fastcall SetDesiredECM(const bool Value);
	void __fastcall SetDetectBusy(const bool Value);
	void __fastcall SetDelayBetweenSends(const Word Value);
	void __fastcall SetServerManager(const TApdFaxServerManager* Value);
	void __fastcall SetSendQueryInterval(const int Value);
	void __fastcall SetFaxServerMode(const TFaxServerMode Value);
	void __fastcall SetDialAttempts(const Word Value);
	void __fastcall SetDialWait(const Word Value);
	void __fastcall SetDialPrefix(const AnsiString Value);
	void __fastcall SetEnhFont(const Graphics::TFont* Value);
	void __fastcall SetEnhHeaderFont(const Graphics::TFont* Value);
	void __fastcall SetEnhTextEnabled(const bool Value);
	void __fastcall SetTapiDevice(const Adtapi::TApdCustomTapiDevice* Value);
	HIDESBASE int __fastcall GetPageLength(void);
	HIDESBASE int __fastcall GetBytesTransferred(void);
	HIDESBASE Word __fastcall GetCurrentPage(void);
	Word __fastcall GetDialAttempt(void);
	Word __fastcall GetDialAttempts(void);
	HIDESBASE unsigned __fastcall GetElapsedTime(void);
	HIDESBASE Word __fastcall GetFaxProgress(void);
	HIDESBASE Word __fastcall GetHangupCode(void);
	HIDESBASE int __fastcall GetModemBPS(void);
	HIDESBASE AnsiString __fastcall GetModemChip();
	HIDESBASE bool __fastcall GetModemECM(void);
	HIDESBASE AnsiString __fastcall GetModemModel();
	HIDESBASE AnsiString __fastcall GetModemRevision();
	HIDESBASE AnsiString __fastcall GetRemoteID();
	HIDESBASE Word __fastcall GetSessionBPS(void);
	HIDESBASE bool __fastcall GetSessionECM(void);
	HIDESBASE bool __fastcall GetSessionResolution(void);
	HIDESBASE bool __fastcall GetSessionWidth(void);
	HIDESBASE Adfax::TFaxClassSet __fastcall GetSupportedFaxClasses(void);
	HIDESBASE Word __fastcall GetTotalPages(void);
	void __fastcall FInternalFaxFinish(System::TObject* CP, int ErrorCode);
	void __fastcall FInternalFaxStatus(System::TObject* CP, bool First, bool Last);
	void __fastcall FInternalSendQueryTimer(System::TObject* Sender);
	void __fastcall FInternalTapiPortOpenClose(System::TObject* Sender);
	void __fastcall FInternalTapiFail(System::TObject* Sender);
	void __fastcall FInternalPortToggle(System::TObject* CP, bool Opening);
	void __fastcall FInternalFaxAccept(System::TObject* CP, bool &Accept);
	void __fastcall FInternalFaxName(System::TObject* CP, AnsiString &Name);
	void __fastcall FInternalFaxLog(System::TObject* CP, Oomisc::TFaxLogCode LogCode);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	HIDESBASE void __fastcall CheckPort(void);
	
public:
	AnsiString CurrentJobFileName;
	int CurrentJobNumber;
	#pragma pack(push, 1)
	Oomisc::TFaxRecipientRec CurrentRecipient;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	Oomisc::TFaxJobHeaderRec CurrentJobHeader;
	#pragma pack(pop)
	
	__fastcall virtual TApdCustomFaxServer(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomFaxServer(void);
	bool __fastcall StartTransmitSingle(void);
	void __fastcall ForceSendQuery(void);
	HIDESBASE void __fastcall CancelFax(void);
	__property Adport::TApdCustomComPort* ComPort = {read=FComPort, write=SetComPort};
	__property Adtapi::TApdCustomTapiDevice* TapiDevice = {read=FTapiDevice, write=SetTapiDevice};
	__property TApdFaxServerManager* ServerManager = {read=FServerManager, write=SetServerManager};
	__property Adfax::TApdAbstractFaxStatus* StatusDisplay = {read=FStatusDisplay, write=SetStatusDisplay};
	__property Adfaxprn::TApdCustomFaxPrinter* FaxPrinter = {read=FFaxPrinter, write=SetFaxPrinter};
	__property Adfax::TApdFaxLog* FaxLog = {read=FFaxLog, write=SetFaxLog};
	__property bool ExitOnError = {read=FExitOnError, write=SetExitOnError, default=0};
	__property Adfax::TFaxClass FaxClass = {read=FFaxClass, write=SetFaxClass, default=1};
	__property AnsiString FaxFile = {read=FFaxFile, write=SetFaxFile};
	__property AnsiString FaxFileExt = {read=FFaxFileExt, write=SetFaxFileExt};
	__property int InitBaud = {read=FInitBaud, write=SetInitBaud, default=0};
	__property AnsiString ModemInit = {read=FModemInit, write=SetModemInit};
	__property int NormalBaud = {read=FNormalBaud, write=SetNormalBaud, default=0};
	__property bool SoftwareFlow = {read=FSoftwareFlow, write=SetSoftwareFlow, default=0};
	__property AnsiString StationID = {read=FStationID, write=SetStationID};
	__property Word StatusInterval = {read=FStatusInterval, write=SetStatusInterval, default=1};
	__property Word DesiredBPS = {read=FDesiredBPS, write=SetDesiredBPS, default=9600};
	__property bool DesiredECM = {read=FDesiredECM, write=SetDesiredECM, default=0};
	__property Word DelayBetweenSends = {read=FDelayBetweenSends, write=SetDelayBetweenSends, default=18};
	__property int SendQueryInterval = {read=FSendQueryInterval, write=SetSendQueryInterval, nodefault};
	__property int BytesTransferred = {read=GetBytesTransferred, nodefault};
	__property Word CurrentPage = {read=GetCurrentPage, nodefault};
	__property unsigned ElapsedTime = {read=GetElapsedTime, nodefault};
	__property Word FaxProgress = {read=GetFaxProgress, nodefault};
	__property Word HangupCode = {read=GetHangupCode, nodefault};
	__property int ModemBPS = {read=GetModemBPS, nodefault};
	__property AnsiString ModemChip = {read=GetModemChip};
	__property bool ModemECM = {read=GetModemECM, nodefault};
	__property AnsiString ModemModel = {read=GetModemModel};
	__property AnsiString ModemRevision = {read=GetModemRevision};
	__property int PageLength = {read=GetPageLength, nodefault};
	__property AnsiString RemoteID = {read=GetRemoteID};
	__property Word SessionBPS = {read=GetSessionBPS, nodefault};
	__property bool SessionECM = {read=GetSessionECM, nodefault};
	__property bool SessionResolution = {read=GetSessionResolution, nodefault};
	__property bool SessionWidth = {read=GetSessionWidth, nodefault};
	__property Adfax::TFaxClassSet SupportedFaxClasses = {read=GetSupportedFaxClasses, nodefault};
	__property Word TotalPages = {read=GetTotalPages, nodefault};
	__property bool BlindDial = {read=FBlindDial, write=SetBlindDial, default=0};
	__property Word BufferMinimum = {read=FBufferMinimum, write=SetBufferMinimum, default=1000};
	__property AnsiString CoverFile = {read=FCoverFile, write=SetCoverFile};
	__property bool DetectBusy = {read=FDetectBusy, write=SetDetectBusy, default=1};
	__property Word DialAttempt = {read=GetDialAttempt, nodefault};
	__property Word DialAttempts = {read=GetDialAttempts, write=SetDialAttempts, default=3};
	__property AnsiString DialPrefix = {read=FDialPrefix, write=SetDialPrefix};
	__property Word DialWait = {read=FDialWait, write=SetDialWait, default=60};
	__property Word DialRetryWait = {read=FDialRetryWait, write=FDialRetryWait, default=60};
	__property AnsiString HeaderLine = {read=FHeaderLine, write=SetHeaderLine};
	__property AnsiString HeaderRecipient = {read=FHeaderRecipient, write=SetHeaderRecipient};
	__property AnsiString HeaderSender = {read=FHeaderSender, write=SetHeaderSender};
	__property AnsiString HeaderTitle = {read=FHeaderTitle, write=SetHeaderTitle};
	__property Word MaxSendCount = {read=FMaxSendCount, write=SetMaxSendCount, default=50};
	__property AnsiString PhoneNumber = {read=FPhoneNumber, write=SetPhoneNumber};
	__property bool SafeMode = {read=FSafeMode, write=SetSafeMode, default=1};
	__property bool ToneDial = {read=FToneDial, write=SetToneDial, default=1};
	__property bool EnhTextEnabled = {read=FEnhTextEnabled, write=SetEnhTextEnabled, nodefault};
	__property Graphics::TFont* EnhHeaderFont = {read=FEnhHeaderFont, write=SetEnhHeaderFont};
	__property Graphics::TFont* EnhFont = {read=FEnhFont, write=SetEnhFont};
	__property Word AnswerOnRing = {read=FAnswerOnRing, write=SetAnswerOnRing, default=1};
	__property bool ConstantStatus = {read=FConstantStatus, write=SetConstantStatus, default=0};
	__property AnsiString DestinationDir = {read=FDestinationDir, write=SetDestinationDir};
	__property Adfax::TFaxNameMode FaxNameMode = {read=FFaxNameMode, write=SetFaxNameMode, default=1};
	__property bool PrintOnReceive = {read=FPrintOnReceive, write=SetPrintOnReceive, nodefault};
	__property bool Monitoring = {read=FMonitoring, write=SetMonitoring, nodefault};
	__property bool FaxInProgress = {read=FFaxInProgress, write=FFaxInProgress, default=0};
	__property TFaxServerMode FaxServerMode = {read=FFaxServerMode, write=SetFaxServerMode, nodefault};
	__property TFaxServerStatusEvent OnFaxServerStatus = {read=FFaxServerStatusEvent, write=FFaxServerStatusEvent};
	__property TFaxServerFatalErrorEvent OnFaxServerFatalError = {read=FFaxServerFatalErrorEvent, write=FFaxServerFatalErrorEvent};
	__property TFaxServerFinishEvent OnFaxServerFinish = {read=FFaxServerFinishEvent, write=FFaxServerFinishEvent};
	__property TFaxServerPortOpenCloseEvent OnFaxServerPortOpenClose = {read=FFaxServerPortOpenCloseEvent, write=FFaxServerPortOpenCloseEvent};
	__property TFaxServerAcceptEvent OnFaxServerAccept = {read=FFaxServerAcceptEvent, write=FFaxServerAcceptEvent};
	__property TFaxServerNameEvent OnFaxServerName = {read=FFaxServerNameEvent, write=FFaxServerNameEvent};
	__property TFaxServerLogEvent OnFaxServerLog = {read=FFaxServerLogEvent, write=FFaxServerLogEvent};
};


class DELPHICLASS TApdFaxServer;
class PASCALIMPLEMENTATION TApdFaxServer : public TApdCustomFaxServer 
{
	typedef TApdCustomFaxServer inherited;
	
__published:
	__property ComPort ;
	__property TapiDevice ;
	__property ServerManager ;
	__property StatusDisplay ;
	__property FaxLog ;
	__property ExitOnError  = {default=0};
	__property FaxClass  = {default=1};
	__property InitBaud  = {default=0};
	__property ModemInit ;
	__property NormalBaud  = {default=0};
	__property SoftwareFlow  = {default=0};
	__property StationID ;
	__property StatusInterval  = {default=1};
	__property DelayBetweenSends  = {default=18};
	__property SendQueryInterval ;
	__property DesiredBPS  = {default=9600};
	__property DesiredECM  = {default=0};
	__property FaxFileExt ;
	__property BlindDial  = {default=0};
	__property BufferMinimum  = {default=1000};
	__property DetectBusy  = {default=1};
	__property DialWait  = {default=60};
	__property DialRetryWait  = {default=60};
	__property DialAttempts  = {default=3};
	__property MaxSendCount  = {default=50};
	__property SafeMode  = {default=1};
	__property ToneDial  = {default=1};
	__property DialPrefix ;
	__property EnhTextEnabled ;
	__property EnhFont ;
	__property EnhHeaderFont ;
	__property AnswerOnRing  = {default=1};
	__property ConstantStatus  = {default=0};
	__property DestinationDir ;
	__property FaxNameMode  = {default=1};
	__property PrintOnReceive ;
	__property FaxPrinter ;
	__property OnFaxServerStatus ;
	__property OnFaxServerFatalError ;
	__property OnFaxServerFinish ;
	__property OnFaxServerPortOpenClose ;
	__property OnFaxServerAccept ;
	__property OnFaxServerName ;
	__property OnFaxServerLog ;
public:
	#pragma option push -w-inl
	/* TApdCustomFaxServer.Create */ inline __fastcall virtual TApdFaxServer(Classes::TComponent* AOwner) : TApdCustomFaxServer(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomFaxServer.Destroy */ inline __fastcall virtual ~TApdFaxServer(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint adfDefDelayBetweenSends = 0x12;
static const Shortint adfDefSendQueryInterval = 0x1e;
#define adfDefJobFileExt "APJ"
static const int apfDefJobHeaderID = 0x304a5041;
static const bool adfDefFaxServerManagerPaused = false;
#define ServerManagerLockFileName "SRVMGR.LCK"
static const Shortint stNone = 0x0;
static const Shortint stPartial = 0x1;
static const Shortint stComplete = 0x2;
static const Shortint stPaused = 0x3;

}	/* namespace Adfaxsrv */
using namespace Adfaxsrv;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdFaxSrv
