// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdFax.pas' rev: 6.00

#ifndef AdFaxHPP
#define AdFaxHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdTUtil.hpp>	// Pascal unit
#include <AdTapi.hpp>	// Pascal unit
#include <AdPort.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <AwFaxCvt.hpp>	// Pascal unit
#include <AwFax.hpp>	// Pascal unit
#include <AwAbsFax.hpp>	// Pascal unit
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

namespace Adfax
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TFaxClass { fcUnknown, fcDetect, fcClass1, fcClass2, fcClass2_0 };
#pragma option pop

typedef Set<TFaxClass, fcUnknown, fcClass2_0>  TFaxClassSet;

typedef void __fastcall (__closure *TFaxStatusEvent)(System::TObject* CP, bool First, bool Last);

typedef void __fastcall (__closure *TFaxLogEvent)(System::TObject* CP, Oomisc::TFaxLogCode LogCode);

typedef void __fastcall (__closure *TFaxErrorEvent)(System::TObject* CP, int ErrorCode);

typedef void __fastcall (__closure *TFaxFinishEvent)(System::TObject* CP, int ErrorCode);

typedef void __fastcall (__closure *TFaxAcceptEvent)(System::TObject* CP, bool &Accept);

typedef void __fastcall (__closure *TFaxNameEvent)(System::TObject* CP, AnsiString &Name);

typedef void __fastcall (__closure *TFaxNextEvent)(System::TObject* CP, AnsiString &APhoneNumber, AnsiString &AFaxFile, AnsiString &ACoverFile);

typedef AnsiString TModemString;

typedef AnsiString TStationID;

#pragma option push -b-
enum TFaxMode { fmNone, fmSend, fmReceive };
#pragma option pop

#pragma option push -b-
enum TFaxNameMode { fnNone, fnCount, fnMonthDay };
#pragma option pop

class DELPHICLASS TApdCustomAbstractFax;
class DELPHICLASS TApdAbstractFaxStatus;
class PASCALIMPLEMENTATION TApdAbstractFaxStatus : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	Forms::TForm* FDisplay;
	Forms::TPosition FPosition;
	bool FCtl3D;
	bool FVisible;
	AnsiString FCaption;
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	TApdCustomAbstractFax* FFax;
	void __fastcall SetPosition(const Forms::TPosition NewPosition);
	void __fastcall SetCtl3D(const bool NewCtl3D);
	void __fastcall SetVisible(const bool NewVisible);
	void __fastcall GetProperties(void);
	void __fastcall SetCaption(const AnsiString NewCaption);
	void __fastcall Show(void);
	
public:
	__fastcall virtual TApdAbstractFaxStatus(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdAbstractFaxStatus(void);
	virtual void __fastcall UpdateDisplay(const bool First, const bool Last) = 0 ;
	DYNAMIC void __fastcall CreateDisplay(void) = 0 ;
	DYNAMIC void __fastcall DestroyDisplay(void) = 0 ;
	__property Forms::TForm* Display = {read=FDisplay, write=FDisplay};
	
__published:
	__property Forms::TPosition Position = {read=FPosition, write=SetPosition, nodefault};
	__property bool Ctl3D = {read=FCtl3D, write=SetCtl3D, nodefault};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
	__property TApdCustomAbstractFax* Fax = {read=FFax, write=FFax};
	__property AnsiString Caption = {read=FCaption, write=SetCaption};
};


class DELPHICLASS TApdFaxLog;
class PASCALIMPLEMENTATION TApdFaxLog : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	AnsiString FFaxHistoryName;
	TApdCustomAbstractFax* FFax;
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	
public:
	__fastcall virtual TApdFaxLog(Classes::TComponent* AOwner);
	virtual AnsiString __fastcall GetLogString(const Oomisc::TFaxLogCode Log, TApdCustomAbstractFax* aFax);
	virtual void __fastcall UpdateLog(const Oomisc::TFaxLogCode Log);
	
__published:
	__property AnsiString FaxHistoryName = {read=FFaxHistoryName, write=FFaxHistoryName};
	__property TApdCustomAbstractFax* Fax = {read=FFax, write=FFax};
public:
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TApdFaxLog(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TApdCustomAbstractFax : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	Awabsfax::TFaxRec *Fax;
	TFaxMode FaxMode;
	HWND MsgHandler;
	Awabsfax::TFaxPrepProc PrepProc;
	Awabsfax::TFaxFunc FaxFunc;
	bool FWaitForTapi;
	bool FTapiPrepared;
	Classes::TNotifyEvent FUserOnTapiPortOpen;
	Classes::TNotifyEvent FUserOnTapiPortClose;
	Adtapi::TTapiStatusEvent FUserOnTapiStatus;
	AnsiString FModemModel;
	AnsiString FModemChip;
	AnsiString FModemRevision;
	int FModemBPS;
	bool FCorrection;
	Adport::TApdCustomComPort* FComPort;
	Adtapi::TApdCustomTapiDevice* FTapiDevice;
	TApdAbstractFaxStatus* FStatusDisplay;
	TApdFaxLog* FFaxLog;
	AnsiString FFaxFile;
	TFaxClassSet FSupportedFaxClasses;
	int FVersion;
	AnsiString FTempFile;
	unsigned FStartTime;
	TFaxStatusEvent FOnFaxStatus;
	TFaxLogEvent FOnFaxLog;
	TFaxErrorEvent FOnFaxError;
	TFaxFinishEvent FOnFaxFinish;
	unsigned __fastcall GetElapsedTime(void);
	virtual AnsiString __fastcall GetFaxFile();
	virtual void __fastcall SetFaxFile(const AnsiString NewFile);
	int __fastcall GetInitBaud(void);
	void __fastcall SetInitBaud(const int NewBaud);
	bool __fastcall GetInProgress(void);
	int __fastcall GetNormalBaud(void);
	void __fastcall SetNormalBaud(const int NewBaud);
	TFaxClass __fastcall GetFaxClass(void);
	void __fastcall SetFaxClass(const TFaxClass NewClass);
	AnsiString __fastcall GetModemInit();
	void __fastcall SetModemInit(const AnsiString NewInit);
	AnsiString __fastcall GetStationID();
	void __fastcall SetStationID(const AnsiString NewID);
	void __fastcall SetComPort(const Adport::TApdCustomComPort* NewPort);
	void __fastcall SetStatusDisplay(const TApdAbstractFaxStatus* NewDisplay);
	void __fastcall SetFaxLog(const TApdFaxLog* NewLog);
	AnsiString __fastcall GetRemoteID();
	TFaxClassSet __fastcall GetSupportedFaxClasses(void);
	Word __fastcall GetFaxProgress(void);
	int __fastcall GetFaxError(void);
	Word __fastcall GetSessionBPS(void);
	bool __fastcall GetSessionResolution(void);
	bool __fastcall GetSessionWidth(void);
	bool __fastcall GetSessionECM(void);
	Word __fastcall GetHangupCode(void);
	bool __fastcall GetLastPageStatus(void);
	AnsiString __fastcall GetModemModel();
	AnsiString __fastcall GetModemRevision();
	AnsiString __fastcall GetModemChip();
	int __fastcall GetModemBPS(void);
	bool __fastcall GetModemECM(void);
	Word __fastcall GetTotalPages(void);
	Word __fastcall GetCurrentPage(void);
	int __fastcall GetBytesTransferred(void);
	int __fastcall GetPageLength(void);
	bool __fastcall GetAbortNoConnect(void);
	void __fastcall SetAbortNoConnect(bool NewValue);
	bool __fastcall GetExitOnError(void);
	void __fastcall SetExitOnError(bool NewValue);
	bool __fastcall GetSoftwareFlow(void);
	void __fastcall SetSoftwareFlow(bool NewValue);
	Word __fastcall GetStatusInterval(void);
	void __fastcall SetStatusInterval(Word NewValue);
	Word __fastcall GetDesiredBPS(void);
	void __fastcall SetDesiredBPS(Word NewBPS);
	bool __fastcall GetDesiredECM(void);
	void __fastcall SetDesiredECM(bool NewECM);
	AnsiString __fastcall GetFaxFileExt();
	void __fastcall SetFaxFileExt(const AnsiString NewExt);
	void __fastcall CheckPort(void);
	void __fastcall CreateFaxMessageHandler(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual void __fastcall PrepareTapi(void);
	virtual void __fastcall UnprepareTapi(void);
	void __fastcall OpenTapiPort(void);
	void __fastcall CloseTapiPort(void);
	void __fastcall WaitForTapi(void);
	void __fastcall FaxTapiPortOpenClose(System::TObject* Sender);
	virtual void __fastcall Loaded(void);
	void __fastcall ReadVersionCheck(Classes::TReader* Reader);
	void __fastcall WriteVersionCheck(Classes::TWriter* Writer);
	virtual void __fastcall DefineProperties(Classes::TFiler* Filer);
	virtual void __fastcall apwFaxStatus(System::TObject* CP, bool First, bool Last);
	virtual void __fastcall apwFaxLog(System::TObject* CP, Oomisc::TFaxLogCode LogCode);
	virtual void __fastcall apwFaxError(System::TObject* CP, int ErrorCode);
	virtual void __fastcall apwFaxFinish(System::TObject* CP, int ErrorCode);
	
public:
	__property int InitBaud = {read=GetInitBaud, write=SetInitBaud, default=0};
	__property int NormalBaud = {read=GetNormalBaud, write=SetNormalBaud, default=0};
	__property TFaxClass FaxClass = {read=GetFaxClass, write=SetFaxClass, default=1};
	__property AnsiString ModemInit = {read=GetModemInit, write=SetModemInit};
	__property AnsiString StationID = {read=GetStationID, write=SetStationID};
	__property Adport::TApdCustomComPort* ComPort = {read=FComPort, write=SetComPort};
	__property Adtapi::TApdCustomTapiDevice* TapiDevice = {read=FTapiDevice, write=FTapiDevice};
	__property TApdAbstractFaxStatus* StatusDisplay = {read=FStatusDisplay, write=SetStatusDisplay};
	__property TApdFaxLog* FaxLog = {read=FFaxLog, write=SetFaxLog};
	__property AnsiString FaxFile = {read=GetFaxFile, write=SetFaxFile};
	__property bool AbortNoConnect = {read=GetAbortNoConnect, write=SetAbortNoConnect, default=0};
	__property bool ExitOnError = {read=GetExitOnError, write=SetExitOnError, default=0};
	__property bool SoftwareFlow = {read=GetSoftwareFlow, write=SetSoftwareFlow, default=0};
	__property Word StatusInterval = {read=GetStatusInterval, write=SetStatusInterval, default=1};
	__property Word DesiredBPS = {read=GetDesiredBPS, write=SetDesiredBPS, default=9600};
	__property bool DesiredECM = {read=GetDesiredECM, write=SetDesiredECM, default=0};
	__property AnsiString FaxFileExt = {read=GetFaxFileExt, write=SetFaxFileExt};
	__property TFaxStatusEvent OnFaxStatus = {read=FOnFaxStatus, write=FOnFaxStatus};
	__property TFaxLogEvent OnFaxLog = {read=FOnFaxLog, write=FOnFaxLog};
	__property TFaxErrorEvent OnFaxError = {read=FOnFaxError, write=FOnFaxError};
	__property TFaxFinishEvent OnFaxFinish = {read=FOnFaxFinish, write=FOnFaxFinish};
	__property TFaxClassSet SupportedFaxClasses = {read=GetSupportedFaxClasses, nodefault};
	__property Word FaxProgress = {read=GetFaxProgress, nodefault};
	__property int FaxError = {read=GetFaxError, nodefault};
	__property Word SessionBPS = {read=GetSessionBPS, nodefault};
	__property bool SessionResolution = {read=GetSessionResolution, nodefault};
	__property bool SessionWidth = {read=GetSessionWidth, nodefault};
	__property bool SessionECM = {read=GetSessionECM, nodefault};
	__property Word HangupCode = {read=GetHangupCode, nodefault};
	__property bool LastPageStatus = {read=GetLastPageStatus, nodefault};
	__property AnsiString ModemModel = {read=GetModemModel};
	__property AnsiString ModemRevision = {read=GetModemRevision};
	__property AnsiString ModemChip = {read=GetModemChip};
	__property int ModemBPS = {read=GetModemBPS, nodefault};
	__property bool ModemECM = {read=GetModemECM, nodefault};
	__property Word TotalPages = {read=GetTotalPages, nodefault};
	__property Word CurrentPage = {read=GetCurrentPage, nodefault};
	__property int BytesTransferred = {read=GetBytesTransferred, nodefault};
	__property int PageLength = {read=GetPageLength, nodefault};
	__property AnsiString RemoteID = {read=GetRemoteID};
	__property unsigned ElapsedTime = {read=GetElapsedTime, nodefault};
	__property bool InProgress = {read=GetInProgress, nodefault};
	__fastcall virtual TApdCustomAbstractFax(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomAbstractFax(void);
	void __fastcall CancelFax(void);
	AnsiString __fastcall StatusMsg(const Word Status);
	AnsiString __fastcall LogMsg(const Oomisc::TFaxLogCode LogCode);
};


class DELPHICLASS TApdAbstractFax;
class PASCALIMPLEMENTATION TApdAbstractFax : public TApdCustomAbstractFax 
{
	typedef TApdCustomAbstractFax inherited;
	
__published:
	__property InitBaud  = {default=0};
	__property NormalBaud  = {default=0};
	__property FaxClass  = {default=1};
	__property ModemInit ;
	__property StationID ;
	__property ComPort ;
	__property TapiDevice ;
	__property StatusDisplay ;
	__property FaxLog ;
	__property FaxFile ;
	__property AbortNoConnect  = {default=0};
	__property ExitOnError  = {default=0};
	__property SoftwareFlow  = {default=0};
	__property StatusInterval  = {default=1};
	__property DesiredBPS  = {default=9600};
	__property DesiredECM  = {default=0};
	__property FaxFileExt ;
	__property OnFaxStatus ;
	__property OnFaxLog ;
	__property OnFaxError ;
	__property OnFaxFinish ;
public:
	#pragma option push -w-inl
	/* TApdCustomAbstractFax.Create */ inline __fastcall virtual TApdAbstractFax(Classes::TComponent* AOwner) : TApdCustomAbstractFax(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomAbstractFax.Destroy */ inline __fastcall virtual ~TApdAbstractFax(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdCustomReceiveFax;
class PASCALIMPLEMENTATION TApdCustomReceiveFax : public TApdAbstractFax 
{
	typedef TApdAbstractFax inherited;
	
protected:
	TFaxNameMode FFaxNameMode;
	Word RingCount;
	TFaxAcceptEvent FOnFaxAccept;
	TFaxNameEvent FOnFaxName;
	Word __fastcall GetAnswerOnRing(void);
	void __fastcall SetAnswerOnRing(const Word NewVal);
	bool __fastcall GetFaxAndData(void);
	void __fastcall SetFaxAndData(const bool NewVal);
	bool __fastcall GetOneFax(void);
	void __fastcall SetOneFax(bool NewValue);
	bool __fastcall GetConstantStatus(void);
	void __fastcall SetConstantStatus(const bool NewValue);
	AnsiString __fastcall GetDestinationDir();
	void __fastcall SetDestinationDir(const AnsiString NewDir);
	virtual void __fastcall apwFaxAccept(System::TObject* CP, bool &Accept);
	virtual void __fastcall apwFaxName(System::TObject* CP, AnsiString &Name);
	
public:
	__property Word AnswerOnRing = {read=GetAnswerOnRing, write=SetAnswerOnRing, default=1};
	__property bool FaxAndData = {read=GetFaxAndData, write=SetFaxAndData, default=0};
	__property TFaxNameMode FaxNameMode = {read=FFaxNameMode, write=FFaxNameMode, default=1};
	__property bool OneFax = {read=GetOneFax, write=SetOneFax, default=0};
	__property bool ConstantStatus = {read=GetConstantStatus, write=SetConstantStatus, default=0};
	__property AnsiString DestinationDir = {read=GetDestinationDir, write=SetDestinationDir};
	__property TFaxAcceptEvent OnFaxAccept = {read=FOnFaxAccept, write=FOnFaxAccept};
	__property TFaxNameEvent OnFaxName = {read=FOnFaxName, write=FOnFaxName};
	virtual void __fastcall PrepareTapi(void);
	virtual void __fastcall UnprepareTapi(void);
	void __fastcall TapiPassiveAnswer(void);
	void __fastcall FaxTapiStatus(System::TObject* CP, bool First, bool Last, int Device, int Message, int Param1, int Param2, int Param3);
	__fastcall virtual TApdCustomReceiveFax(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomReceiveFax(void);
	void __fastcall InitModemForFaxReceive(void);
	void __fastcall PrepareConnectInProgress(void);
	void __fastcall StartReceive(void);
	void __fastcall StartManualReceive(bool SendATAToModem);
};


class DELPHICLASS TApdReceiveFax;
class PASCALIMPLEMENTATION TApdReceiveFax : public TApdCustomReceiveFax 
{
	typedef TApdCustomReceiveFax inherited;
	
__published:
	__property AnswerOnRing  = {default=1};
	__property FaxAndData  = {default=0};
	__property FaxNameMode  = {default=1};
	__property OneFax  = {default=0};
	__property ConstantStatus  = {default=0};
	__property DestinationDir ;
	__property OnFaxAccept ;
	__property OnFaxName ;
public:
	#pragma option push -w-inl
	/* TApdCustomReceiveFax.Create */ inline __fastcall virtual TApdReceiveFax(Classes::TComponent* AOwner) : TApdCustomReceiveFax(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomReceiveFax.Destroy */ inline __fastcall virtual ~TApdReceiveFax(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdCustomSendFax;
class PASCALIMPLEMENTATION TApdCustomSendFax : public TApdAbstractFax 
{
	typedef TApdAbstractFax inherited;
	
protected:
	bool WasSent;
	AnsiString FCoverFile;
	Classes::TStringList* FFaxFileList;
	AnsiString FPhoneNumber;
	TFaxNextEvent FOnFaxNext;
	bool __fastcall GetFastPage(void);
	void __fastcall SetFastPage(const bool NewVal);
	bool __fastcall GetEnhTextEnabled(void);
	void __fastcall SetEnhTextEnabled(const bool NewVal);
	Graphics::TFont* __fastcall GetEnhHeaderFont(void);
	void __fastcall SetEnhHeaderFont(const Graphics::TFont* NewVal);
	Graphics::TFont* __fastcall GetEnhFont(void);
	void __fastcall SetEnhFont(const Graphics::TFont* NewVal);
	void __fastcall SetFaxFileList(const Classes::TStringList* NewVal);
	virtual AnsiString __fastcall GetFaxFile();
	virtual void __fastcall SetFaxFile(const AnsiString NewFile);
	bool __fastcall GetBlindDial(void);
	void __fastcall SetBlindDial(const bool NewVal);
	bool __fastcall GetDetectBusy(void);
	void __fastcall SetDetectBusy(const bool NewVal);
	bool __fastcall GetToneDial(void);
	void __fastcall SetToneDial(const bool NewVal);
	AnsiString __fastcall GetDialPrefix();
	void __fastcall SetDialPrefix(const AnsiString NewPrefix);
	Word __fastcall GetDialWait(void);
	void __fastcall SetDialWait(const Word NewWait);
	Word __fastcall GetDialAttempts(void);
	void __fastcall SetDialAttempts(const Word NewAttempts);
	Word __fastcall GetDialRetryWait(void);
	void __fastcall SetDialRetryWait(const Word NewWait);
	Word __fastcall GetMaxSendCount(void);
	void __fastcall SetMaxSendCount(const Word NewCount);
	Word __fastcall GetBufferMinimum(void);
	void __fastcall SetBufferMinimum(const Word NewMin);
	AnsiString __fastcall GetHeaderLine();
	void __fastcall SetHeaderLine(const AnsiString S);
	Word __fastcall GetDialAttempt(void);
	bool __fastcall GetSafeMode(void);
	void __fastcall SetSafeMode(bool NewMode);
	AnsiString __fastcall GetHeaderSender();
	void __fastcall SetHeaderSender(const AnsiString NewSender);
	AnsiString __fastcall GetHeaderRecipient();
	void __fastcall SetHeaderRecipient(const AnsiString NewRecipient);
	AnsiString __fastcall GetHeaderTitle();
	void __fastcall SetHeaderTitle(const AnsiString NewTitle);
	virtual void __fastcall apwFaxNext(System::TObject* CP, AnsiString &APhoneNumber, AnsiString &AFaxFile, AnsiString &ACoverFile);
	
public:
	__property bool FastPage = {read=GetFastPage, write=SetFastPage, nodefault};
	__property bool EnhTextEnabled = {read=GetEnhTextEnabled, write=SetEnhTextEnabled, nodefault};
	__property Graphics::TFont* EnhHeaderFont = {read=GetEnhHeaderFont, write=SetEnhHeaderFont};
	__property Graphics::TFont* EnhFont = {read=GetEnhFont, write=SetEnhFont};
	__property Classes::TStringList* FaxFileList = {read=FFaxFileList, write=SetFaxFileList};
	__property bool BlindDial = {read=GetBlindDial, write=SetBlindDial, default=0};
	__property bool DetectBusy = {read=GetDetectBusy, write=SetDetectBusy, default=1};
	__property bool ToneDial = {read=GetToneDial, write=SetToneDial, default=1};
	__property AnsiString DialPrefix = {read=GetDialPrefix, write=SetDialPrefix};
	__property Word DialWait = {read=GetDialWait, write=SetDialWait, default=60};
	__property Word DialAttempts = {read=GetDialAttempts, write=SetDialAttempts, default=3};
	__property Word DialRetryWait = {read=GetDialRetryWait, write=SetDialRetryWait, default=60};
	__property Word MaxSendCount = {read=GetMaxSendCount, write=SetMaxSendCount, default=50};
	__property Word BufferMinimum = {read=GetBufferMinimum, write=SetBufferMinimum, default=1000};
	__property AnsiString HeaderLine = {read=GetHeaderLine, write=SetHeaderLine};
	__property AnsiString CoverFile = {read=FCoverFile, write=FCoverFile};
	__property AnsiString PhoneNumber = {read=FPhoneNumber, write=FPhoneNumber};
	__property bool SafeMode = {read=GetSafeMode, write=SetSafeMode, default=1};
	__property AnsiString HeaderSender = {read=GetHeaderSender, write=SetHeaderSender};
	__property AnsiString HeaderRecipient = {read=GetHeaderRecipient, write=SetHeaderRecipient};
	__property AnsiString HeaderTitle = {read=GetHeaderTitle, write=SetHeaderTitle};
	__property Word DialAttempt = {read=GetDialAttempt, nodefault};
	__property TFaxNextEvent OnFaxNext = {read=FOnFaxNext, write=FOnFaxNext};
	__fastcall virtual TApdCustomSendFax(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomSendFax(void);
	void __fastcall ConvertCover(const AnsiString InCover, const AnsiString OutCover);
	void __fastcall ConcatFaxes(AnsiString FileName);
	void __fastcall StartTransmit(void);
	void __fastcall StartManualTransmit(void);
};


class DELPHICLASS TApdSendFax;
class PASCALIMPLEMENTATION TApdSendFax : public TApdCustomSendFax 
{
	typedef TApdCustomSendFax inherited;
	
__published:
	__property EnhTextEnabled ;
	__property EnhHeaderFont ;
	__property EnhFont ;
	__property FaxFileList ;
	__property BlindDial  = {default=0};
	__property DetectBusy  = {default=1};
	__property ToneDial  = {default=1};
	__property DialPrefix ;
	__property DialWait  = {default=60};
	__property DialAttempts  = {default=3};
	__property DialRetryWait  = {default=60};
	__property MaxSendCount  = {default=50};
	__property BufferMinimum  = {default=1000};
	__property HeaderLine ;
	__property CoverFile ;
	__property PhoneNumber ;
	__property SafeMode  = {default=1};
	__property DialAttempt ;
	__property OnFaxNext ;
	__property HeaderSender ;
	__property HeaderRecipient ;
	__property HeaderTitle ;
public:
	#pragma option push -w-inl
	/* TApdCustomSendFax.Create */ inline __fastcall virtual TApdSendFax(Classes::TComponent* AOwner) : TApdCustomSendFax(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomSendFax.Destroy */ inline __fastcall virtual ~TApdSendFax(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define adfDefFaxHistoryName "APROFAX.HIS"
static const Shortint adfDefInitBaud = 0x0;
static const Shortint adfDefNormalBaud = 0x0;
#define adfDefFaxClass (TFaxClass)(1)
static const bool adfDefAbortNoConnect = false;
static const bool adfDefExitOnError = false;
static const bool adfDefSoftwareFlow = false;
static const Shortint adfDefFaxStatusInterval = 0x1;
static const Word adfDefDesiredBPS = 0x2580;
static const bool adfDefDesiredECM = false;
static const Shortint adfDefAnswerOnRing = 0x1;
static const bool adfDefFaxAndData = false;
static const bool adfDefOneFax = false;
static const bool adfDefConstantStatus = false;
static const bool adfDefSafeMode = true;
#define adfDefFaxFileExt "APF"
static const bool adfDefBlindDial = false;
static const bool adfDefDetectBusy = true;
static const bool adfDefToneDial = true;
static const Shortint adfDefDialWait = 0x3c;
static const Shortint adfDefDialAttempts = 0x3;
static const Shortint adfDefDialRetryWait = 0x3c;
static const Shortint adfDefMaxSendCount = 0x32;
static const Word adfDefBufferMinimum = 0x3e8;
#define adfDefFaxNameMode (TFaxNameMode)(1)
#define adfDefDestinationDir ""

}	/* namespace Adfax */
using namespace Adfax;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdFax
