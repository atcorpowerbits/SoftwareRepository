// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdRas.pas' rev: 6.00

#ifndef AdRasHPP
#define AdRasHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdExcept.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <AdRasUtl.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
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

namespace Adras
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TApdRasDialMode { dmSync, dmAsync };
#pragma option pop

#pragma option push -b-
enum TApdRasSpeakerMode { smDefault, smSpeakerOn, smSpeakerOff };
#pragma option pop

#pragma option push -b-
enum TApdRasCompressionMode { cmDefault, cmCompressionOn, cmCompressionOff };
#pragma option pop

#pragma option push -b-
enum TApdRasDialOption { doPrefixSuffix, doPausedStates, doDisableConnectedUI, doDisableReconnectUI, doNoUser, doPauseOnScript };
#pragma option pop

typedef Set<TApdRasDialOption, doPrefixSuffix, doPauseOnScript>  TApdRasDialOptions;

typedef void __fastcall (__closure *TApdRasStatusEvent)(System::TObject* Sender, int Status);

typedef void __fastcall (__closure *TApdRasErrorEvent)(System::TObject* Sender, int Error);

class DELPHICLASS TApdCustomRasDialer;
class DELPHICLASS TApdAbstractRasStatus;
class PASCALIMPLEMENTATION TApdAbstractRasStatus : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	bool FCtl3D;
	Forms::TForm* FDisplay;
	Forms::TPosition FPosition;
	TApdCustomRasDialer* FRasDialer;
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	void __fastcall SetCtl3D(bool Value);
	void __fastcall SetPosition(Forms::TPosition Value);
	
public:
	__property Forms::TForm* Display = {read=FDisplay, write=FDisplay};
	__fastcall virtual TApdAbstractRasStatus(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdAbstractRasStatus(void);
	DYNAMIC void __fastcall CreateDisplay(const AnsiString EntryName) = 0 ;
	DYNAMIC void __fastcall DestroyDisplay(void) = 0 ;
	virtual void __fastcall UpdateDisplay(const AnsiString StatusMsg) = 0 ;
	
__published:
	__property bool Ctl3D = {read=FCtl3D, write=SetCtl3D, nodefault};
	__property Forms::TPosition Position = {read=FPosition, write=SetPosition, nodefault};
	__property TApdCustomRasDialer* RasDialer = {read=FRasDialer, write=FRasDialer};
};


class PASCALIMPLEMENTATION TApdCustomRasDialer : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	HWND DialEventHandle;
	Word DialEventMsg;
	Adrasutl::TRasDialExtensions DialExtensions;
	Adrasutl::TRasDialParams EntryDialParams;
	Adrasutl::TRasDialDlgInfo DialDlgInfo;
	Adrasutl::TRasMonitorDlgInfo MonitorDlgInfo;
	Adrasutl::TRasPhonebookDlgInfo PhonebookDlgInfo;
	Extctrls::TTimer* DisconnectTimer;
	TApdRasDialOptions FDialOptions;
	TApdRasDialMode FDialMode;
	TApdRasSpeakerMode FSpeakerMode;
	TApdRasCompressionMode FCompressionMode;
	AnsiString FPhonebook;
	AnsiString FEntryName;
	bool FHangupOnDestroy;
	AnsiString FPhoneNumber;
	AnsiString FCallBackNumber;
	AnsiString FUserName;
	AnsiString FPassword;
	AnsiString FDomain;
	unsigned FConnection;
	TApdAbstractRasStatus* FStatusDisplay;
	unsigned FPlatformID;
	Classes::TNotifyEvent FOnConnected;
	TApdRasStatusEvent FOnDialStatus;
	TApdRasErrorEvent FOnDialError;
	Classes::TNotifyEvent FOnDisconnected;
	Adrasutl::PRasDialExtensions __fastcall AssembleDialExtensions(void);
	Adrasutl::PRasDialParams __fastcall AssembleDialParams(void);
	void __fastcall DialEventWindowProc(Messages::TMessage &Msg);
	void __fastcall DoOnDialError(int Error);
	void __fastcall DoOnDialStatus(int Status);
	void __fastcall DoOnConnected(void);
	void __fastcall DoOnDisconnected(void);
	void __fastcall DoDisconnectTimer(System::TObject* Sender);
	unsigned __fastcall GetConnection(void);
	int __fastcall GetConnectState(void);
	AnsiString __fastcall GetDeviceName();
	AnsiString __fastcall GetDeviceType();
	int __fastcall GetFullConnectStatus(Adrasutl::PRasConnStatus PRCS);
	bool __fastcall GetIsRasAvailable(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	void __fastcall SetEntryName(AnsiString Value);
	__property AnsiString CallBackNumber = {read=FCallBackNumber, write=FCallBackNumber};
	__property TApdRasCompressionMode CompressionMode = {read=FCompressionMode, write=FCompressionMode, nodefault};
	__property TApdRasDialMode DialMode = {read=FDialMode, write=FDialMode, nodefault};
	__property TApdRasDialOptions DialOptions = {read=FDialOptions, write=FDialOptions, nodefault};
	__property AnsiString Domain = {read=FDomain, write=FDomain};
	__property AnsiString EntryName = {read=FEntryName, write=SetEntryName};
	__property bool HangupOnDestroy = {read=FHangupOnDestroy, write=FHangupOnDestroy, nodefault};
	__property AnsiString Password = {read=FPassword, write=FPassword};
	__property AnsiString Phonebook = {read=FPhonebook, write=FPhonebook};
	__property AnsiString PhoneNumber = {read=FPhoneNumber, write=FPhoneNumber};
	__property TApdRasSpeakerMode SpeakerMode = {read=FSpeakerMode, write=FSpeakerMode, nodefault};
	__property TApdAbstractRasStatus* StatusDisplay = {read=FStatusDisplay, write=FStatusDisplay};
	__property AnsiString UserName = {read=FUserName, write=FUserName};
	__property Classes::TNotifyEvent OnConnected = {read=FOnConnected, write=FOnConnected};
	__property TApdRasStatusEvent OnDialStatus = {read=FOnDialStatus, write=FOnDialStatus};
	__property TApdRasErrorEvent OnDialError = {read=FOnDialError, write=FOnDialError};
	__property Classes::TNotifyEvent OnDisconnected = {read=FOnDisconnected, write=FOnDisconnected};
	
public:
	__property unsigned Connection = {read=GetConnection, nodefault};
	__property int ConnectState = {read=GetConnectState, nodefault};
	__property AnsiString DeviceName = {read=GetDeviceName};
	__property AnsiString DeviceType = {read=GetDeviceType};
	__property unsigned PlatformID = {read=FPlatformID, nodefault};
	__property bool IsRasAvailable = {read=GetIsRasAvailable, nodefault};
	__fastcall virtual TApdCustomRasDialer(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomRasDialer(void);
	int __fastcall AddPhonebookEntry(AnsiString PBEntryName, const Oomisc::TRasEntry &RasEntry, const Oomisc::TTapiConfigRec &TapiConfigRec);
	int __fastcall CreatePhonebookEntry(void);
	int __fastcall DeletePhonebookEntry(void);
	int __fastcall Dial(void);
	int __fastcall DialDlg(void);
	int __fastcall EditPhonebookEntry(void);
	int __fastcall ClearConnectionStatistics(void);
	int __fastcall GetConnectionStatistics(Oomisc::TRasStatistics &Statistics);
	AnsiString __fastcall GetErrorText(int Error);
	int __fastcall GetPhonebookEntry(AnsiString PBEntryName, Oomisc::TRasEntry &RasEntry, Oomisc::TTapiConfigRec &TapiConfigRec);
	AnsiString __fastcall GetStatusText(int Status);
	void __fastcall Hangup(void);
	int __fastcall ListConnections(Classes::TStrings* List);
	int __fastcall ListEntries(Classes::TStrings* List);
	int __fastcall MonitorDlg(void);
	int __fastcall PhonebookDlg(void);
	int __fastcall GetDialParameters(void);
	int __fastcall SetDialParameters(void);
	int __fastcall ValidateEntryName(AnsiString EntryName);
};


class DELPHICLASS TApdRasDialer;
class PASCALIMPLEMENTATION TApdRasDialer : public TApdCustomRasDialer 
{
	typedef TApdCustomRasDialer inherited;
	
__published:
	__property CallBackNumber ;
	__property CompressionMode ;
	__property DialMode ;
	__property DialOptions ;
	__property Domain ;
	__property EntryName ;
	__property HangupOnDestroy ;
	__property OnConnected ;
	__property OnDialStatus ;
	__property OnDialError ;
	__property OnDisconnected ;
	__property Password ;
	__property Phonebook ;
	__property PhoneNumber ;
	__property SpeakerMode ;
	__property StatusDisplay ;
	__property UserName ;
public:
	#pragma option push -w-inl
	/* TApdCustomRasDialer.Create */ inline __fastcall virtual TApdRasDialer(Classes::TComponent* AOwner) : TApdCustomRasDialer(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomRasDialer.Destroy */ inline __fastcall virtual ~TApdRasDialer(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adras */
using namespace Adras;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdRas
