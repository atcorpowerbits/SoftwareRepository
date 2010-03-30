// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdPgr.pas' rev: 5.00

#ifndef AdPgrHPP
#define AdPgrHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdPacket.hpp>	// Pascal unit
#include <AdWnPort.hpp>	// Pascal unit
#include <AdTUtil.hpp>	// Pascal unit
#include <AdTapi.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <AdPort.hpp>	// Pascal unit
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

namespace Adpgr
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TPortOpts { p7E1, p8N1, pCustom };
#pragma option pop

typedef Set<TPortOpts, p7E1, pCustom>  TPortOptsSet;

#pragma option push -b-
enum TApdPagerMode { pmTAP, pmSNPP };
#pragma option pop

typedef Set<TApdPagerMode, pmTAP, pmSNPP>  TPagerModeSet;

#pragma option push -b-
enum TPageStatus { psNone, psInitFail, psConnected, psLineBusy, psDisconnect, psNoDialtone, psMsgNotSent, 
	psWaitingToRedial, psLoginPrompt, psLoggedIn, psDialing, psRedialing, psLoginRetry, psMsgOkToSend, 
	psSendingMsg, psMsgAck, psMsgNak, psMsgRs, psMsgCompleted, psSendTimedOut, psLoggingOut, psDone };
#pragma option pop

class DELPHICLASS TApdCustomPager;
typedef void __fastcall (__closure *TPageStatusEvent)(TApdCustomPager* Pager, TPageStatus Event, int 
	Param1, int Param2);

typedef void __fastcall (__closure *TPageErrorEvent)(TApdCustomPager* Pager, int Code);

typedef void __fastcall (__closure *TPageFinishEvent)(TApdCustomPager* Pager, int Code, AnsiString Msg
	);

typedef void __fastcall (__closure *TTapGetNextMessageEvent)(TApdCustomPager* Pager, bool &DoneMessages
	);

class DELPHICLASS TApdPgrLog;
class PASCALIMPLEMENTATION TApdPgrLog : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TApdCustomPager* FOwner;
	bool FVerboseLog;
	bool FEnabled;
	AnsiString FLogName;
	
public:
	__fastcall TApdPgrLog(TApdCustomPager* Owner);
	void __fastcall AddLogString(bool Verbose, const AnsiString StatusString);
	void __fastcall ClearLog(void);
	
__published:
	__property AnsiString LogName = {read=FLogName, write=FLogName};
	__property bool VerboseLog = {read=FVerboseLog, write=FVerboseLog, nodefault};
	__property bool Enabled = {read=FEnabled, write=FEnabled, nodefault};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TApdPgrLog(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TApdCustomPager : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
private:
	Adport::TApdCustomComPort* FPort;
	Adtapi::TApdTapiDevice* FTapiDevice;
	Oomisc::TTapiConfigRec FOrigTapiConfig;
	TApdPgrLog* FEventLog;
	AnsiString FPagerID;
	Classes::TStrings* FMessage;
	bool FExitOnError;
	bool FUseEscapes;
	unsigned FHandle;
	bool mpGotOkay;
	bool FConnected;
	bool FSent;
	bool FAborted;
	bool FRedialFlag;
	bool FLoginRetry;
	bool FTerminating;
	bool FCancelled;
	bool FAbortNoConnect;
	bool FBlindDial;
	bool FToneDial;
	bool FTapHotLine;
	Word FDialAttempt;
	Word FDialAttempts;
	AnsiString FDialPrefix;
	AnsiString FModemHangup;
	AnsiString FModemInit;
	AnsiString FPhoneNumber;
	AnsiString FTonePrefix;
	Word OKTrig;
	Word ErrorTrig;
	Word ConnectTrig;
	Word BusyTrig;
	Word NoCarrierTrig;
	Word NoDialtoneTrig;
	bool FOkayToSend;
	bool FSessionOpen;
	bool FQuit;
	bool FGotSuccess;
	Adpacket::TApdDataPacket* FLoginPacket;
	Adpacket::TApdDataPacket* FServerSuccPacket;
	Adpacket::TApdDataPacket* FServerDataMsgPacket;
	Adpacket::TApdDataPacket* FServerErrorPacket;
	Adpacket::TApdDataPacket* FServerFatalErrorPacket;
	Adpacket::TApdDataPacket* FServerDonePacket;
	AnsiString FPassword;
	Classes::TStringList* FMsgBlockList;
	int FMsgIdx;
	Word FtrgIDPrompt;
	Word FtrgLoginSucc;
	Word FtrgLoginFail;
	Word FtrgLoginRetry;
	Word FtrgOkToSend;
	Word FtrgMsgAck;
	Word FtrgMsgNak;
	Word FtrgMsgRs;
	Word FtrgSendTimer;
	Word FtrgDCon;
	Extctrls::TTimer* tpPingTimer;
	Extctrls::TTimer* tpModemInitTimer;
	Extctrls::TTimer* WaitTimer;
	int tpPingCount;
	int FTapWait;
	int TempWait;
	TPageFinishEvent FOnPageFinish;
	TPageStatusEvent FOnPageStatus;
	TPageErrorEvent FOnPageError;
	TTapGetNextMessageEvent FOnGetNextMessage;
	AnsiString FServerInitString;
	AnsiString FServerDoneString;
	AnsiString FServerSuccStr;
	AnsiString FServerDataInp;
	AnsiString FServerRespFailCont;
	AnsiString FServerRespFailTerm;
	int FCommDelay;
	int FMaxMessageLength;
	TApdPagerMode FPagerMode;
	TPortOpts FPortOpts;
	bool FPortOpenedByUser;
	AnsiString FPageMode;
	AnsiString FLogName;
	void __fastcall DoDial(void);
	void __fastcall DoInitializePort(void);
	void __fastcall DoPortOpenCloseEx(System::TObject* CP, Adport::TApdCallbackType CallbackType);
	void __fastcall InitCallStateFlags(void);
	void __fastcall SetUseEscapes(bool UseEscapesVal);
	void __fastcall AddInitModemDataTrigs(void);
	void __fastcall SetPortOpts(void);
	void __fastcall DoOpenPort(void);
	void __fastcall BuildTapMessages(void);
	void __fastcall ModemInitTimerOnTimer(System::TObject* Sender);
	void __fastcall PingTimerOnTimer(System::TObject* Sender);
	void __fastcall WaitTimerOnTimer(System::TObject* Sender);
	void __fastcall DoneModemInitTimer(void);
	void __fastcall DonePingTimer(void);
	void __fastcall FreeTrigger(Adport::TApdCustomComPort* Port, Word &Trigger);
	void __fastcall FreePackets(void);
	void __fastcall InitPackets(void);
	void __fastcall DoLoginString(System::TObject* Sender, AnsiString Data);
	void __fastcall DoServerSucc(System::TObject* Sender, AnsiString Data);
	void __fastcall DoServerDataMsg(System::TObject* Sender, AnsiString Data);
	void __fastcall DoServerError(System::TObject* Sender, AnsiString Data);
	void __fastcall DoServerFatalError(System::TObject* Sender, AnsiString Data);
	void __fastcall DoLogoutString(System::TObject* Sender, AnsiString Data);
	void __fastcall PutString(const AnsiString S);
	void __fastcall DoMultiLine(void);
	void __fastcall MakePacket(Adpacket::TApdDataPacket* ThePacket, AnsiString StartStr, AnsiString EndStr
		, Adpacket::TStringPacketNotifyEvent HandlerMethod);
	
protected:
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation
		);
	void __fastcall SetMessage(Classes::TStrings* Msg);
	void __fastcall SetPagerID(AnsiString ID);
	void __fastcall DoPageStatus(TPageStatus Status);
	void __fastcall DoPageError(int Error);
	__property unsigned Handle = {read=FHandle, nodefault};
	void __fastcall WndProc(Messages::TMessage &Message);
	void __fastcall DoStartCall(void);
	void __fastcall TerminatePage(void);
	void __fastcall DoFailedToSend(void);
	void __fastcall LogOutTAP(void);
	void __fastcall DataTriggerHandler(unsigned Msg, unsigned wParam, int lParam);
	void __fastcall DoPageStatusTrig(unsigned Trig);
	void __fastcall FreeLoginTriggers(void);
	void __fastcall FreeLogoutTriggers(void);
	void __fastcall FreeMsgTriggers(void);
	void __fastcall FreeResponseTriggers(void);
	void __fastcall InitLoginTriggers(void);
	void __fastcall InitLogoutTriggers(void);
	void __fastcall InitMsgTriggers(void);
	void __fastcall DoCurMessageBlock(void);
	void __fastcall DoFirstMessageBlock(void);
	void __fastcall DoNextMessageBlock(void);
	__property AnsiString ServerInitString = {read=FServerInitString, write=FServerInitString};
	__property AnsiString ServerSuccessString = {read=FServerSuccStr, write=FServerSuccStr};
	__property AnsiString ServerDataInput = {read=FServerDataInp, write=FServerDataInp};
	__property AnsiString ServerResponseFailContinue = {read=FServerRespFailCont, write=FServerRespFailCont
		};
	__property AnsiString ServerResponseFailTerminate = {read=FServerRespFailTerm, write=FServerRespFailTerm
		};
	__property AnsiString ServerDoneString = {read=FServerDoneString, write=FServerDoneString};
	virtual void __fastcall PutMessage(void);
	virtual void __fastcall PutSend(void);
	virtual void __fastcall PutQuit(void);
	
public:
	__property Classes::TStrings* Message = {read=FMessage, write=SetMessage};
	__property AnsiString PagerID = {read=FPagerID, write=SetPagerID};
	__property bool ExitOnError = {read=FExitOnError, write=FExitOnError, nodefault};
	__property bool UseEscapes = {read=FUseEscapes, write=SetUseEscapes, nodefault};
	__property Adport::TApdCustomComPort* Port = {read=FPort, write=FPort};
	__property Adtapi::TApdTapiDevice* TapiDevice = {read=FTapiDevice, write=FTapiDevice};
	__property TApdPagerMode PagerMode = {read=FPagerMode, write=FPagerMode, nodefault};
	__property TPortOpts PortOpts = {read=FPortOpts, write=FPortOpts, nodefault};
	__property bool AbortNoConnect = {read=FAbortNoConnect, write=FAbortNoConnect, nodefault};
	__property AnsiString LogName = {read=FLogName, write=FLogName};
	__property AnsiString Password = {read=FPassword, write=FPassword};
	__fastcall virtual TApdCustomPager(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomPager(void);
	void __fastcall Send(void);
	void __fastcall Disconnect(void);
	void __fastcall CancelCall(void);
	__property Word DialAttempts = {read=FDialAttempts, write=FDialAttempts, nodefault};
	__property AnsiString PhoneNumber = {read=FPhoneNumber, write=FPhoneNumber};
	__property bool ToneDial = {read=FToneDial, write=FToneDial, nodefault};
	__property AnsiString ModemInit = {read=FModemInit, write=FModemInit};
	__property AnsiString ModemHangup = {read=FModemHangup, write=FModemHangup};
	__property bool TapHotLine = {read=FTapHotLine, write=FTapHotLine, nodefault};
	__property AnsiString DialPrefix = {read=FDialPrefix, write=FDialPrefix};
	__property bool BlindDial = {read=FBlindDial, write=FBlindDial, nodefault};
	__property int TapWait = {read=FTapWait, write=FTapWait, nodefault};
	__property int MaxMessageLength = {read=FMaxMessageLength, write=FMaxMessageLength, nodefault};
	void __fastcall Quit(void);
	__property TApdPgrLog* EventLog = {read=FEventLog, write=FEventLog};
	__property TPageStatusEvent OnPageStatus = {read=FOnPageStatus, write=FOnPageStatus};
	__property TPageFinishEvent OnPageFinish = {read=FOnPageFinish, write=FOnPageFinish};
	__property TPageErrorEvent OnPageError = {read=FOnPageError, write=FOnPageError};
	__property TTapGetNextMessageEvent OnGetNextMessage = {read=FOnGetNextMessage, write=FOnGetNextMessage
		};
};


class DELPHICLASS TApdTapProperties;
class PASCALIMPLEMENTATION TApdTapProperties : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TApdCustomPager* FOwner;
	int __fastcall GetTapWait(void);
	void __fastcall SetTapWait(const int Value);
	Adtapi::TApdTapiDevice* __fastcall GetTapiDevice(void);
	void __fastcall SetTapiDevice(const Adtapi::TApdTapiDevice* Value);
	AnsiString __fastcall GetModemInit(void);
	void __fastcall SetModemInit(const AnsiString Value);
	AnsiString __fastcall GetModemHangup(void);
	void __fastcall SetModemHangup(const AnsiString Value);
	Word __fastcall GetDialAttempts(void);
	void __fastcall SetDialAttempts(const Word Value);
	AnsiString __fastcall GetDialPrefix(void);
	void __fastcall SetDialPrefix(const AnsiString Value);
	bool __fastcall GetTapHotLine(void);
	void __fastcall SetTapHotLine(const bool Value);
	bool __fastcall GetBlindDial(void);
	void __fastcall SetBlindDial(const bool Value);
	bool __fastcall GetToneDial(void);
	void __fastcall SetToneDial(const bool Value);
	int __fastcall GetMaxMessageLength(void);
	void __fastcall SetMaxMessageLength(const int Value);
	TPortOpts __fastcall GetPortOpts(void);
	void __fastcall SetPortOpts(const TPortOpts Value);
	
public:
	__fastcall TApdTapProperties(TApdCustomPager* Owner);
	
__published:
	__property int TapWait = {read=GetTapWait, write=SetTapWait, nodefault};
	__property Word DialAttempts = {read=GetDialAttempts, write=SetDialAttempts, nodefault};
	__property AnsiString DialPrefix = {read=GetDialPrefix, write=SetDialPrefix};
	__property int MaxMessageLength = {read=GetMaxMessageLength, write=SetMaxMessageLength, nodefault};
		
	__property bool TapHotLine = {read=GetTapHotLine, write=SetTapHotLine, nodefault};
	__property bool BlindDial = {read=GetBlindDial, write=SetBlindDial, nodefault};
	__property bool ToneDial = {read=GetToneDial, write=SetToneDial, nodefault};
	__property Adtapi::TApdTapiDevice* TapiDevice = {read=GetTapiDevice, write=SetTapiDevice};
	__property AnsiString ModemHangup = {read=GetModemHangup, write=SetModemHangup};
	__property AnsiString ModemInit = {read=GetModemInit, write=SetModemInit};
	__property TPortOpts PortOpts = {read=GetPortOpts, write=SetPortOpts, nodefault};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TApdTapProperties(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdPager;
class PASCALIMPLEMENTATION TApdPager : public TApdCustomPager 
{
	typedef TApdCustomPager inherited;
	
private:
	TApdTapProperties* FTapProperties;
	
public:
	__fastcall virtual TApdPager(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdPager(void);
	
__published:
	__property Port ;
	__property PagerID ;
	__property EventLog ;
	__property Message ;
	__property ExitOnError ;
	__property Name ;
	__property Password ;
	__property PagerMode ;
	__property UseEscapes ;
	__property TApdTapProperties* TapProperties = {read=FTapProperties, write=FTapProperties};
	__property OnPageError ;
	__property OnPageStatus ;
	__property OnPageFinish ;
	__property OnGetNextMessage ;
};


//-- var, const, procedure ---------------------------------------------------
#define atpCRLF "\r\n"
static const Shortint MAX_MSG_LEN = 0x50;
extern PACKAGE int STD_DELAY;
static const bool adpgDefAbortNoConnect = false;
static const bool adpgDefBlindDial = false;
static const bool adpgDefToneDial = true;
static const bool adpgDefExitOnError = false;
static const bool adpgDefUseEscapes = false;
static const Shortint adpgDefDialAttempts = 0x3;
static const Shortint adpgDefDialRetryWait = 0x1e;
static const Word adpgDefTimerTrig = 0x438;
#define adpgDefPagerMode (TApdPagerMode)(0)
#define adpgDefPortOpts (TPortOpts)(0)
#define adpgPulseDialPrefix "DP"
#define adpgToneDialPrefix "DT"
#define adpgDefModemInitCmd "ATZ"
#define adpgDefModemHangupCmd "+++~~~ATH"
extern PACKAGE AnsiString FapOKTrig;
extern PACKAGE AnsiString FapErrorTrig;
extern PACKAGE AnsiString FapConnectTrig;
extern PACKAGE AnsiString FapBusyTrig;
extern PACKAGE AnsiString FapNoCarrierTrig;
extern PACKAGE AnsiString FapNoDialtoneTrig;

}	/* namespace Adpgr */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Adpgr;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdPgr
