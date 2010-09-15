// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdMdm.pas' rev: 6.00

#ifndef AdMdmHPP
#define AdMdmHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <FileCtrl.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <AdLibMdm.hpp>	// Pascal unit
#include <AdPacket.hpp>	// Pascal unit
#include <AdPort.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
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

namespace Admdm
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TApdModemState { msUnknown, msIdle, msInitializing, msAutoAnswerBackground, msAutoAnswerWait, msAnswerWait, msDial, msConnectWait, msConnected, msHangup, msCancel };
#pragma option pop

#pragma option push -b-
enum TApdModemLogCode { mlNone, mlDial, mlAutoAnswer, mlAnswer, mlConnect, mlCancel, mlBusy, mlConnectFail };
#pragma option pop

#pragma option push -b-
enum TApdModemStatusAction { msaStart, msaClose, msaUpdate, msaDetailReplace, msaClear };
#pragma option pop

#pragma option push -b-
enum TApdModemSpeakerVolume { svLow, svMed, svHigh };
#pragma option pop

#pragma option push -b-
enum TApdModemSpeakerMode { smOff, smOn, smDial };
#pragma option pop

#pragma option push -b-
enum TApdModemFlowControl { fcOff, fcHard, fcSoft };
#pragma option pop

#pragma option push -b-
enum TApdModemErrorControl { ecOff, ecOn, ecForced, ecCellular };
#pragma option pop

#pragma option push -b-
enum TApdModemModulation { smBell, smCCITT, smCCITT_V23 };
#pragma option pop

#pragma pack(push, 4)
struct TApdModemConfig
{
	System::SmallString<8>  ConfigVersion;
	System::SmallString<20>  AttachedTo;
	System::SmallString<100>  Manufacturer;
	System::SmallString<100>  ModemName;
	System::SmallString<100>  ModemModel;
	Word DataBits;
	Adport::TParity Parity;
	Word StopBits;
	TApdModemSpeakerVolume SpeakerVolume;
	TApdModemSpeakerMode SpeakerMode;
	TApdModemFlowControl FlowControl;
	System::Set<TApdModemErrorControl, ecOff, ecCellular>  ErrorControl;
	bool Compression;
	TApdModemModulation Modulation;
	bool ToneDial;
	bool BlindDial;
	int CallSetupFailTimeout;
	int InactivityTimeout;
	System::SmallString<50>  ExtraSettings;
	Byte Padding[48];
} ;
#pragma pack(pop)

class DELPHICLASS TApdModemNameProp;
class PASCALIMPLEMENTATION TApdModemNameProp : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	AnsiString FManufacturer;
	AnsiString FName;
	AnsiString FModemFile;
	void __fastcall SetManufacturer(const AnsiString Value);
	void __fastcall SetName(const AnsiString Value);
	void __fastcall SetModemFile(const AnsiString Value);
	
public:
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	void __fastcall Clear(void);
	
__published:
	__property AnsiString Manufacturer = {read=FManufacturer, write=SetManufacturer};
	__property AnsiString Name = {read=FName, write=SetName};
	__property AnsiString ModemFile = {read=FModemFile, write=SetModemFile};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TApdModemNameProp(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TApdModemNameProp(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


#pragma pack(push, 4)
struct TApdCallerIDInfo
{
	bool HasData;
	AnsiString Date;
	AnsiString Time;
	AnsiString Number;
	AnsiString Name;
	AnsiString Msg;
} ;
#pragma pack(pop)

class DELPHICLASS TAdCustomModem;
typedef void __fastcall (__closure *TModemCallerIDEvent)(TAdCustomModem* Modem, const TApdCallerIDInfo &CallerID);

typedef void __fastcall (__closure *TModemNotifyEvent)(TAdCustomModem* Modem);

typedef void __fastcall (__closure *TModemFailEvent)(TAdCustomModem* Modem, int FailCode);

typedef void __fastcall (__closure *TModemLogEvent)(TAdCustomModem* Modem, TApdModemLogCode LogCode);

typedef void __fastcall (__closure *TModemStatusEvent)(TAdCustomModem* Modem, TApdModemState ModemState);

class DELPHICLASS TAdAbstractModemStatus;
class PASCALIMPLEMENTATION TAdAbstractModemStatus : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
private:
	Forms::TForm* FStatusDialog;
	AnsiString FCaption;
	bool FStarted;
	TAdCustomModem* FModem;
	void __fastcall SetCaption(const AnsiString Value);
	void __fastcall SetStarted(bool Start);
	void __fastcall SetModem(const TAdCustomModem* Value);
	
public:
	__fastcall virtual TAdAbstractModemStatus(Classes::TComponent* AOwner);
	__fastcall virtual ~TAdAbstractModemStatus(void);
	__property Forms::TForm* StatusDialog = {read=FStatusDialog, write=FStatusDialog};
	__property AnsiString Caption = {read=FCaption, write=SetCaption};
	__property TAdCustomModem* Modem = {read=FModem, write=SetModem};
	__property bool Started = {read=FStarted, nodefault};
	void __fastcall UpdateDisplay(TAdCustomModem* Modem, const AnsiString StatusStr, const AnsiString TimeStr, const AnsiString DetailStr, TApdModemStatusAction Action);
};


class PASCALIMPLEMENTATION TAdCustomModem : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
private:
	int FAnswerOnRing;
	unsigned FBPSRate;
	Adport::TApdCustomComPort* FComPort;
	int FDialTimeout;
	int FFailCode;
	AnsiString FModemCapFolder;
	unsigned FRingWaitTimeout;
	int FRingCount;
	TAdAbstractModemStatus* FStatusDisplay;
	TApdModemNameProp* FSelectedDevice;
	TApdModemState FModemState;
	Classes::TStringList* FNegotiationResponses;
	TModemCallerIDEvent FOnModemCallerID;
	TModemLogEvent FOnModemLog;
	TModemNotifyEvent FOnModemDisconnect;
	TModemNotifyEvent FOnModemConnect;
	TModemFailEvent FOnModemFail;
	TModemStatusEvent FOnModemStatus;
	bool FConnected;
	AnsiString FPhoneNumber;
	unsigned FStartTime;
	bool FDeviceSelected;
	TApdModemConfig FModemConfig;
	TApdCallerIDInfo FCallerIDInfo;
	unsigned FHandle;
	Byte FPortWasOpen;
	Adport::TTriggerEvent FSavedOnTrigger;
	unsigned __fastcall GetElapsedTime(void);
	Classes::TStringList* __fastcall GetNegotiationResponses(void);
	void __fastcall SetAnswerOnRing(const int Value);
	void __fastcall SetComPort(const Adport::TApdCustomComPort* Value);
	void __fastcall SetDialTimeout(const int Value);
	void __fastcall SetModemCapFolder(const AnsiString Value);
	void __fastcall SetRingWaitTimeout(const unsigned Value);
	void __fastcall SetSelectedDevice(const TApdModemNameProp* Value);
	void __fastcall SetStatusDisplay(const TAdAbstractModemStatus* Value);
	bool __fastcall GetDeviceSelected(void);
	void __fastcall PortOpenCloseEx(System::TObject* CP, Adport::TApdCallbackType CallbackType);
	
protected:
	Adpacket::TApdDataPacket* ResponsePacket;
	bool Initialized;
	bool PassthroughMode;
	bool WaitingForResponse;
	bool OKResponse;
	bool ErrorResponse;
	bool ConnectResponse;
	bool TimedOut;
	AnsiString LastCommand;
	Word DcdTrigger;
	Word StatusTimerTrigger;
	bool FCallerIDProvided;
	void __fastcall CheckReady(void);
	void __fastcall DoCallerID(void);
	void __fastcall DoConnect(void);
	void __fastcall DoDisconnect(void);
	void __fastcall DoFail(int Failure);
	void __fastcall DoLog(TApdModemLogCode LogCode);
	void __fastcall DoStatus(TApdModemState NewModemState);
	void __fastcall Initialize(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	void __fastcall ModemMessage(Messages::TMessage &Message);
	void __fastcall PrepForConnect(bool EnableTriggers);
	void __fastcall ResponseStringPacket(System::TObject* Sender, AnsiString Data);
	void __fastcall ResponseTimeout(System::TObject* Sender);
	void __fastcall TriggerEvent(System::TObject* CP, Word Msg, Word TriggerHandle, Word Data);
	bool __fastcall SendCommands(Classes::TList* Commands);
	bool __fastcall CheckResponses(const AnsiString Response, const AnsiString DefResponse, Classes::TList* Responses);
	int __fastcall CheckErrors(const AnsiString Response);
	void __fastcall CheckCallerID(const AnsiString Response);
	bool __fastcall ParseStandardConnect(const AnsiString Response);
	
public:
	Adlibmdm::TLmModem LmModem;
	Adlibmdm::TApdLibModem* LibModem;
	__fastcall virtual TAdCustomModem(Classes::TComponent* AOwner);
	__fastcall virtual ~TAdCustomModem(void);
	__property int AnswerOnRing = {read=FAnswerOnRing, write=SetAnswerOnRing, default=2};
	__property unsigned BPSRate = {read=FBPSRate, nodefault};
	__property TApdCallerIDInfo CallerIDInfo = {read=FCallerIDInfo};
	__property Adport::TApdCustomComPort* ComPort = {read=FComPort, write=SetComPort};
	__property bool Connected = {read=FConnected, nodefault};
	__property bool DeviceSelected = {read=GetDeviceSelected, nodefault};
	__property int DialTimeout = {read=FDialTimeout, write=SetDialTimeout, default=60};
	__property unsigned ElapsedTime = {read=GetElapsedTime, nodefault};
	__property int FailureCode = {read=FFailCode, nodefault};
	__property unsigned Handle = {read=FHandle, nodefault};
	__property AnsiString ModemCapFolder = {read=FModemCapFolder, write=SetModemCapFolder};
	__property TApdModemState ModemState = {read=FModemState, nodefault};
	__property Classes::TStringList* NegotiationResponses = {read=GetNegotiationResponses};
	__property AnsiString PhoneNumber = {read=FPhoneNumber};
	__property int RingCount = {read=FRingCount, nodefault};
	__property unsigned RingWaitTimeout = {read=FRingWaitTimeout, write=SetRingWaitTimeout, default=1200};
	__property TApdModemNameProp* SelectedDevice = {read=FSelectedDevice, write=SetSelectedDevice};
	__property TAdAbstractModemStatus* StatusDisplay = {read=FStatusDisplay, write=SetStatusDisplay};
	void __fastcall AutoAnswer(void);
	void __fastcall CancelCall(void);
	void __fastcall ConfigAndOpen(void);
	TApdModemConfig __fastcall DefaultDeviceConfig();
	void __fastcall Dial(const AnsiString ANumber);
	AnsiString __fastcall FailureCodeMsg(const int FailureCode);
	TApdModemConfig __fastcall GetDevConfig();
	AnsiString __fastcall ModemLogToString(TApdModemLogCode LogCode);
	AnsiString __fastcall ModemStatusMsg(TApdModemState Status);
	bool __fastcall SelectDevice(void);
	bool __fastcall SendCommand(const AnsiString Command);
	void __fastcall SetDevConfig(const TApdModemConfig &Config);
	bool __fastcall ShowConfigDialog(void);
	AnsiString __fastcall ConvertXML(const AnsiString S);
	AnsiString __fastcall StripXML(const AnsiString S);
	__property TModemCallerIDEvent OnModemCallerID = {read=FOnModemCallerID, write=FOnModemCallerID};
	__property TModemNotifyEvent OnModemConnect = {read=FOnModemConnect, write=FOnModemConnect};
	__property TModemNotifyEvent OnModemDisconnect = {read=FOnModemDisconnect, write=FOnModemDisconnect};
	__property TModemFailEvent OnModemFail = {read=FOnModemFail, write=FOnModemFail};
	__property TModemLogEvent OnModemLog = {read=FOnModemLog, write=FOnModemLog};
	__property TModemStatusEvent OnModemStatus = {read=FOnModemStatus, write=FOnModemStatus};
};


class DELPHICLASS TAdModem;
class PASCALIMPLEMENTATION TAdModem : public TAdCustomModem 
{
	typedef TAdCustomModem inherited;
	
__published:
	__property AnswerOnRing  = {default=2};
	__property ComPort ;
	__property DialTimeout  = {default=60};
	__property ModemCapFolder ;
	__property RingWaitTimeout  = {default=1200};
	__property SelectedDevice ;
	__property StatusDisplay ;
	__property OnModemCallerID ;
	__property OnModemConnect ;
	__property OnModemDisconnect ;
	__property OnModemFail ;
	__property OnModemLog ;
	__property OnModemStatus ;
public:
	#pragma option push -w-inl
	/* TAdCustomModem.Create */ inline __fastcall virtual TAdModem(Classes::TComponent* AOwner) : TAdCustomModem(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TAdCustomModem.Destroy */ inline __fastcall virtual ~TAdModem(void) { }
	#pragma option pop
	
};


class DELPHICLASS TAdModemStatus;
class PASCALIMPLEMENTATION TAdModemStatus : public TAdAbstractModemStatus 
{
	typedef TAdAbstractModemStatus inherited;
	
__published:
	__property Caption ;
	__property Modem ;
public:
	#pragma option push -w-inl
	/* TAdAbstractModemStatus.Create */ inline __fastcall virtual TAdModemStatus(Classes::TComponent* AOwner) : TAdAbstractModemStatus(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TAdAbstractModemStatus.Destroy */ inline __fastcall virtual ~TAdModemStatus(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define ApxDefModemCapFolder ""
#define ApxDefModemStatusCaption "Modem status"
#define ApxDefOKResponse "OK\r\n"
#define ApxDefErrorResponse "ERROR\r\n"
#define ApxDefBusyResponse "BUSY\r\n"
#define ApxDefConnectResponse "CONNECT"
#define ApxDefRingResponse "RING\r\n"
#define ApxDefModemEscape "+++"
#define ApxDefAnswerCommand "ATA\r"
#define ApxDefHangupCmd "ATH0\r"
static const Word ApxDefCommandTimeout = 0x7530;
static const Word ApxDefConnectTimeout = 0xea60;
static const Word ApxDefDTRTimeout = 0x3e8;
#define ApxModemConfigVersion "1.00"

}	/* namespace Admdm */
using namespace Admdm;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdMdm
