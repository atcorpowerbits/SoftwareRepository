// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdPager.pas' rev: 6.00

#ifndef AdPagerHPP
#define AdPagerHPP

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

namespace Adpager
{
//-- type declarations -------------------------------------------------------
typedef Word TTriggerHandle;

typedef AnsiString TCmdString;

class DELPHICLASS TApdAbstractPager;
class DELPHICLASS TApdPagerLog;
class PASCALIMPLEMENTATION TApdPagerLog : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	AnsiString FHistoryName;
	TApdAbstractPager* FPager;
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	
public:
	__fastcall virtual TApdPagerLog(Classes::TComponent* AOwner);
	virtual void __fastcall UpdateLog(const AnsiString LogStr);
	
__published:
	__property TApdAbstractPager* Pager = {read=FPager, write=FPager};
	__property AnsiString HistoryName = {read=FHistoryName, write=FHistoryName};
public:
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TApdPagerLog(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TApdAbstractPager : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
private:
	Adport::TApdCustomComPort* FPort;
	AnsiString FPagerID;
	Classes::TStrings* FMessage;
	TApdPagerLog* FPagerLog;
	bool FExitOnError;
	AnsiString FPageMode;
	AnsiString FFailReason;
	void __fastcall WriteToEventLog(const AnsiString S);
	
protected:
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual void __fastcall Send(void) = 0 ;
	virtual void __fastcall SetMessage(Classes::TStrings* Msg);
	virtual void __fastcall SetPagerID(AnsiString ID);
	void __fastcall SetPagerLog(const TApdPagerLog* NewLog);
	__property Classes::TStrings* Message = {read=FMessage, write=SetMessage};
	__property AnsiString PagerID = {read=FPagerID, write=SetPagerID};
	__property TApdPagerLog* PagerLog = {read=FPagerLog, write=SetPagerLog};
	__property bool ExitOnError = {read=FExitOnError, write=FExitOnError, default=0};
	
public:
	__fastcall virtual TApdAbstractPager(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdAbstractPager(void);
};


#pragma option push -b-
enum TDialingCondition { dsNone, dsOffHook, dsDialing, dsRinging, dsWaitForConnect, dsConnected, dsWaitingToRedial, dsRedialing, dsMsgNotSent, dsCancelling, dsDisconnect, dsCleanup, deNone, deNoDialTone, deLineBusy, deNoConnection };
#pragma option pop

typedef TDialingCondition TDialingStatus;

typedef void __fastcall (__closure *TDialStatusEvent)(System::TObject* Sender, TDialingStatus Event);

typedef TDialingCondition TDialError;

typedef void __fastcall (__closure *TDialErrorEvent)(System::TObject* Sender, TDialError Error);

class DELPHICLASS TApdCustomModemPager;
class PASCALIMPLEMENTATION TApdCustomModemPager : public TApdAbstractPager 
{
	typedef TApdAbstractPager inherited;
	
private:
	Adtapi::TApdTapiDevice* FTapiDev;
	bool mpGotOkay;
	bool FConnected;
	bool FSent;
	bool FAborted;
	bool Waiting;
	bool FCancelled;
	TDialingCondition FDialStatus;
	TDialingCondition FDialError;
	bool FDirectToPort;
	bool FAbortNoConnect;
	bool FBlindDial;
	bool FToneDial;
	Word FDialAttempt;
	Word FDialAttempts;
	Word FDialRetryWait;
	Word FDialWait;
	AnsiString FDialPrefix;
	AnsiString FModemHangup;
	AnsiString FModemInit;
	AnsiString FPhoneNumber;
	bool FUseTapi;
	Word OKTrig;
	Word ErrorTrig;
	Word ConnectTrig;
	Word BusyTrig;
	Word VoiceTrig;
	Word NoCarrierTrig;
	Word NoDialtoneTrig;
	TDialStatusEvent FOnDialStatus;
	TDialErrorEvent FOnDialError;
	void __fastcall AddInitModemDataTrigs(void);
	void __fastcall DoOpenPort(void);
	virtual void __fastcall DoDirect(void);
	
protected:
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual void __fastcall DoCleanup(void);
	virtual void __fastcall DoDial(void);
	virtual void __fastcall DoStartCall(void);
	virtual void __fastcall TerminatePage(void);
	virtual void __fastcall DoFailedToSend(void);
	void __fastcall DoInitializePort(void);
	Adtapi::TApdTapiDevice* __fastcall GetTapiDev(void);
	__property Adtapi::TApdTapiDevice* TapiDev = {read=GetTapiDev};
	void __fastcall SetUseTapi(const bool Value);
	void __fastcall SetTapiDev(const Adtapi::TApdTapiDevice* Value);
	virtual void __fastcall InitProperties(void);
	virtual void __fastcall SetPortOpts(void);
	void __fastcall DoDialStatus(TDialingCondition Event);
	void __fastcall InitCallStateFlags(void);
	void __fastcall SetBlindDial(bool BlindDialVal);
	void __fastcall SetDialPrefix(AnsiString CmdStr);
	void __fastcall SetModemHangup(AnsiString CmdStr);
	void __fastcall SetModemInit(AnsiString CmdStr);
	Adport::TApdCustomComPort* __fastcall GetPort(void);
	virtual void __fastcall SetPort(Adport::TApdCustomComPort* ThePort);
	void __fastcall SetToneDial(bool ToneDial);
	
public:
	__fastcall virtual TApdCustomModemPager(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomModemPager(void);
	virtual void __fastcall Loaded(void);
	AnsiString __fastcall DialStatusMsg(TDialingCondition Status);
	__property Adport::TApdCustomComPort* Port = {read=GetPort, write=SetPort};
	__property bool AbortNoConnect = {read=FAbortNoConnect, write=FAbortNoConnect, default=0};
	__property bool BlindDial = {read=FBlindDial, write=SetBlindDial, default=0};
	__property Word DialAttempt = {read=FDialAttempt, write=FDialAttempt, nodefault};
	__property Word DialAttempts = {read=FDialAttempts, write=FDialAttempts, default=3};
	__property AnsiString DialPrefix = {read=FDialPrefix, write=SetDialPrefix};
	__property Word DialRetryWait = {read=FDialRetryWait, write=FDialRetryWait, default=30};
	__property Word DialWait = {read=FDialWait, write=FDialWait, default=60};
	__property AnsiString ModemHangup = {read=FModemHangup, write=SetModemHangup};
	__property AnsiString ModemInit = {read=FModemInit, write=SetModemInit};
	__property AnsiString PhoneNumber = {read=FPhoneNumber, write=FPhoneNumber};
	__property bool ToneDial = {read=FToneDial, write=SetToneDial, default=1};
	__property bool DirectToPort = {read=FDirectToPort, write=FDirectToPort, default=0};
	__property bool UseTapi = {read=FUseTapi, write=SetUseTapi, default=0};
	__property Adtapi::TApdTapiDevice* TapiDevice = {read=FTapiDev, write=SetTapiDev};
	__property TDialErrorEvent OnDialError = {read=FOnDialError, write=FOnDialError};
	__property TDialStatusEvent OnDialStatus = {read=FOnDialStatus, write=FOnDialStatus};
	virtual void __fastcall CancelCall(void);
};


#pragma option push -b-
enum TTapStatus { psNone, psLoginPrompt, psLoggedIn, psLoginErr, psLoginFail, psMsgOkToSend, psSendingMsg, psMsgAck, psMsgNak, psMsgRs, psMsgCompleted, psDone, psSendTimedOut };
#pragma option pop

typedef void __fastcall (__closure *TTAPStatusEvent)(System::TObject* Sender, TTapStatus Event);

typedef void __fastcall (__closure *TTapGetNextMessageEvent)(System::TObject* Sender, bool &DoneMessages);

class DELPHICLASS TApdTAPPager;
class PASCALIMPLEMENTATION TApdTAPPager : public TApdCustomModemPager 
{
	typedef TApdCustomModemPager inherited;
	
private:
	bool FUseEscapes;
	int FMaxMsgLen;
	AnsiString FPassword;
	Classes::TStrings* FBlocks;
	int FMsgIdx;
	Word FtrgIDPrompt;
	Word FtrgLoginSucc;
	Word FtrgLoginFail;
	Word FtrgLoginErr;
	Word FtrgOkToSend;
	Word FtrgMsgAck;
	Word FtrgMsgNak;
	Word FtrgMsgRs;
	Word FtrgSendTimer;
	Word FtrgDCon;
	Extctrls::TTimer* tpPingTimer;
	int tpPingCount;
	int tpTAPRetries;
	int FTapWait;
	TTapStatus FPageStatus;
	Classes::TNotifyEvent FOnTAPFinish;
	TTAPStatusEvent FOnTAPStatus;
	TTapGetNextMessageEvent FOnGetNextMessage;
	void __fastcall PingTimerOnTimer(System::TObject* Sender);
	void __fastcall StartPingTimer(void);
	void __fastcall DonePingTimer(void);
	
protected:
	virtual void __fastcall DoDirect(void);
	void __fastcall DoTAPStatus(TTapStatus Status);
	virtual void __fastcall DoStartCall(void);
	virtual void __fastcall InitProperties(void);
	virtual void __fastcall SetPort(Adport::TApdCustomComPort* ThePort);
	virtual void __fastcall TerminatePage(void);
	void __fastcall DataTriggerHandler(unsigned Msg, unsigned wParam, int lParam);
	void __fastcall FreeLoginTriggers(void);
	void __fastcall FreeLogoutTriggers(void);
	void __fastcall FreeMsgTriggers(void);
	void __fastcall FreeResponseTriggers(void);
	AnsiString __fastcall HandleToTrigger(Word TriggerHandle);
	void __fastcall InitLoginTriggers(void);
	void __fastcall InitLogoutTriggers(void);
	void __fastcall InitMsgTriggers(void);
	void __fastcall DoCurMessageBlock(void);
	void __fastcall DoFirstMessageBlock(void);
	void __fastcall DoNextMessageBlock(void);
	
public:
	__fastcall virtual TApdTAPPager(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdTAPPager(void);
	virtual void __fastcall Send(void);
	void __fastcall ReSend(void);
	void __fastcall Disconnect(void);
	AnsiString __fastcall TAPStatusMsg(TTapStatus Status);
	
__published:
	__property Port ;
	__property PagerID ;
	__property Message ;
	__property PagerLog ;
	__property AbortNoConnect  = {default=0};
	__property BlindDial  = {default=0};
	__property DialAttempt ;
	__property DialAttempts  = {default=3};
	__property DialPrefix ;
	__property DialRetryWait  = {default=30};
	__property DialWait  = {default=60};
	__property ExitOnError  = {default=0};
	__property ModemHangup ;
	__property ModemInit ;
	__property PhoneNumber ;
	__property ToneDial  = {default=1};
	__property DirectToPort  = {default=0};
	__property TapiDevice ;
	__property UseTapi  = {default=0};
	__property AnsiString TapPassword = {read=FPassword, write=FPassword};
	__property int TapWait = {read=FTapWait, write=FTapWait, default=30};
	__property int MaxMessageLength = {read=FMaxMsgLen, write=FMaxMsgLen, default=80};
	__property bool UseEscapes = {read=FUseEscapes, write=FUseEscapes, default=0};
	__property OnDialError ;
	__property OnDialStatus ;
	__property Classes::TNotifyEvent OnTAPFinish = {read=FOnTAPFinish, write=FOnTAPFinish};
	__property TTAPStatusEvent OnTAPStatus = {read=FOnTAPStatus, write=FOnTAPStatus};
	__property TTapGetNextMessageEvent OnGetNextMessage = {read=FOnGetNextMessage, write=FOnGetNextMessage};
};


class DELPHICLASS TApdCustomINetPager;
class PASCALIMPLEMENTATION TApdCustomINetPager : public TApdAbstractPager 
{
	typedef TApdAbstractPager inherited;
	
protected:
	Adwnport::TApdWinsockPort* __fastcall GetPort(void);
	void __fastcall SetPort(Adwnport::TApdWinsockPort* ThePort);
	
public:
	__fastcall virtual TApdCustomINetPager(Classes::TComponent* AOwner);
	__property Adwnport::TApdWinsockPort* Port = {read=GetPort, write=SetPort};
public:
	#pragma option push -w-inl
	/* TApdAbstractPager.Destroy */ inline __fastcall virtual ~TApdCustomINetPager(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TSNPPMessage)(System::TObject* Sender, int Code, AnsiString Msg);

class DELPHICLASS TApdSNPPPager;
class PASCALIMPLEMENTATION TApdSNPPPager : public TApdCustomINetPager 
{
	typedef TApdCustomINetPager inherited;
	
private:
	bool FSent;
	bool FCancelled;
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
	AnsiString FServerInitString;
	AnsiString FServerDoneString;
	AnsiString FServerSuccStr;
	AnsiString FServerDataInp;
	AnsiString FServerRespFailCont;
	AnsiString FServerRespFailTerm;
	int FCommDelay;
	Classes::TNotifyEvent FOnLogin;
	Classes::TNotifyEvent FOnLogout;
	TSNPPMessage FOnSNPPSuccess;
	TSNPPMessage FOnSNPPError;
	void __fastcall FreePackets(void);
	void __fastcall InitPackets(void);
	void __fastcall DoLoginString(System::TObject* Sender, AnsiString Data);
	void __fastcall DoServerSucc(System::TObject* Sender, AnsiString Data);
	void __fastcall DoServerDataMsg(System::TObject* Sender, AnsiString Data);
	void __fastcall DoServerError(System::TObject* Sender, AnsiString Data);
	void __fastcall DoServerFatalError(System::TObject* Sender, AnsiString Data);
	void __fastcall DoLogoutString(System::TObject* Sender, AnsiString Data);
	void __fastcall PutString(AnsiString S);
	void __fastcall DoMultiLine(void);
	void __fastcall MakePacket(Adpacket::TApdDataPacket* ThePacket, AnsiString StartStr, AnsiString EndStr, Adpacket::TStringPacketNotifyEvent HandlerMethod);
	void __fastcall ReleasePacket(Adpacket::TApdDataPacket* &ThePacket);
	void __fastcall DoClose(void);
	void __fastcall DoStart(void);
	
public:
	virtual void __fastcall PutPagerID(void);
	virtual void __fastcall PutMessage(void);
	virtual void __fastcall PutSend(void);
	virtual void __fastcall PutQuit(void);
	virtual void __fastcall Send(void);
	__fastcall virtual TApdSNPPPager(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdSNPPPager(void);
	void __fastcall Quit(void);
	__property AnsiString ServerInitString = {read=FServerInitString, write=FServerInitString};
	__property AnsiString ServerSuccessString = {read=FServerSuccStr, write=FServerSuccStr};
	__property AnsiString ServerDataInput = {read=FServerDataInp, write=FServerDataInp};
	__property AnsiString ServerResponseFailContinue = {read=FServerRespFailCont, write=FServerRespFailCont};
	__property AnsiString ServerResponseFailTerminate = {read=FServerRespFailTerm, write=FServerRespFailTerm};
	__property AnsiString ServerDoneString = {read=FServerDoneString, write=FServerDoneString};
	
__published:
	__property PagerID ;
	__property Port ;
	__property Message ;
	__property ExitOnError  = {default=0};
	__property PagerLog ;
	__property int CommDelay = {read=FCommDelay, write=FCommDelay, default=0};
	__property Classes::TNotifyEvent OnLogin = {read=FOnLogin, write=FOnLogin};
	__property TSNPPMessage OnSNPPSuccess = {read=FOnSNPPSuccess, write=FOnSNPPSuccess};
	__property TSNPPMessage OnSNPPError = {read=FOnSNPPError, write=FOnSNPPError};
	__property Classes::TNotifyEvent OnLogout = {read=FOnLogout, write=FOnLogout};
};


//-- var, const, procedure ---------------------------------------------------
#define atpCRLF "\r\n"
static const Shortint CmdLen = 0x29;
static const Shortint MAX_MSG_LEN = 0x50;
extern PACKAGE int STD_DELAY;
static const bool adpgDefAbortNoConnect = false;
static const bool adpgDefBlindDial = false;
static const bool adpgDefToneDial = true;
static const bool adpgDefExitOnError = false;
static const Shortint adpgDefDialAttempts = 0x3;
static const Shortint adpgDefDialRetryWait = 0x1e;
static const Shortint adpgDefDialWait = 0x3c;
static const Word adpgDefTimerTrig = 0x438;
#define adpgPulseDialPrefix "DP"
#define adpgToneDialPrefix "DT"
#define adpgDefDialPrefix "DT"
#define adpgDefModemInitCmd "ATZ"
#define adpgDefNormalInit "X4"
#define adpgDefBlindInit "X3"
#define adpgDefNoDetectBusyInit "X2"
#define adpgDefX1Init "X1"
#define adpgDefInit "X4"
#define adpgDefModemHangupCmd "+++~~~ATH"
#define adpgDefPagerHistoryName "APROPAGR.HIS"
static const Word TDS_NONE = 0x11f8;
static const Word TDS_OFFHOOK = 0x11f9;
static const Word TDS_DIALING = 0x11fa;
static const Word TDS_RINGING = 0x11fb;
static const Word TDS_WAITFORCONNECT = 0x11fc;
static const Word TDS_CONNECTED = 0x11fd;
static const Word TDS_WAITINGTOREDIAL = 0x11fe;
static const Word TDS_REDIALING = 0x11ff;
static const Word TDS_MSGNOTSENT = 0x1200;
static const Word TDS_CANCELLING = 0x1201;
static const Word TDS_DISCONNECT = 0x1202;
static const Word TDS_CLEANUP = 0x1203;
static const Word TDE_NONE = 0x1216;
static const Word TDE_NODIALTONE = 0x1217;
static const Word TDE_LINEBUSY = 0x1218;
static const Word TDE_NOCONNECTION = 0x1219;
static const Word TPS_NONE = 0x1234;
static const Word TPS_LOGINPROMPT = 0x1235;
static const Word TPS_LOGGEDIN = 0x1236;
static const Word TPS_LOGINERR = 0x1237;
static const Word TPS_LOGINFAIL = 0x1238;
static const Word TPS_MSGOKTOSEND = 0x1239;
static const Word TPS_SENDINGMSG = 0x123a;
static const Word TPS_MSGACK = 0x123b;
static const Word TPS_MSGNAK = 0x123c;
static const Word TPS_MSGRS = 0x123d;
static const Word TPS_MSGCOMPLETED = 0x123e;
static const Word TPS_DONE = 0x123f;
extern PACKAGE AnsiString FapOKTrig;
extern PACKAGE AnsiString FapErrorTrig;
extern PACKAGE AnsiString FapConnectTrig;
extern PACKAGE AnsiString FapBusyTrig;
extern PACKAGE AnsiString FapVoiceTrig;
extern PACKAGE AnsiString FapNoCarrierTrig;
extern PACKAGE AnsiString FapNoDialtoneTrig;
extern PACKAGE AnsiString TAP_ID_PROMPT;
extern PACKAGE AnsiString TAP_LOGIN_ACK;
extern PACKAGE AnsiString TAP_LOGIN_NAK;
extern PACKAGE AnsiString TAP_LOGIN_FAIL;
extern PACKAGE AnsiString TAP_MSG_OKTOSEND;
extern PACKAGE AnsiString TAP_MSG_ACK;
extern PACKAGE AnsiString TAP_MSG_NAK;
extern PACKAGE AnsiString TAP_MSG_RS;
extern PACKAGE AnsiString TAP_DISCONNECT;
extern PACKAGE AnsiString TAP_AUTO_LOGIN;
extern PACKAGE AnsiString TAP_LOGOUT;
static const Shortint MAX_TAP_RETRIES = 0x3;

}	/* namespace Adpager */
using namespace Adpager;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdPager
