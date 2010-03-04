// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdWnPort.pas' rev: 6.00

#ifndef AdWnPortHPP
#define AdWnPortHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdPacket.hpp>	// Pascal unit
#include <AdPort.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <AdWUtil.hpp>	// Pascal unit
#include <AdSocket.hpp>	// Pascal unit
#include <AwWnsock.hpp>	// Pascal unit
#include <AwUser.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adwnport
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TApdSocksVersion { svNone, svSocks4, svSocks4a, svSocks5 };
#pragma option pop

class DELPHICLASS TApdSocksServerInfo;
class PASCALIMPLEMENTATION TApdSocksServerInfo : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	AnsiString FAddress;
	AnsiString FPassword;
	Word FPort;
	TApdSocksVersion FSocksVersion;
	AnsiString FUserCode;
	
protected:
	void __fastcall SetAddress(AnsiString v);
	void __fastcall SetPassword(AnsiString v);
	void __fastcall SetPort(Word v);
	void __fastcall SetSocksVersion(TApdSocksVersion v);
	void __fastcall SetUserCode(AnsiString v);
	
public:
	__fastcall TApdSocksServerInfo(void);
	
__published:
	__property AnsiString Address = {read=FAddress, write=SetAddress};
	__property AnsiString Password = {read=FPassword, write=SetPassword};
	__property Word Port = {read=FPort, write=SetPort, nodefault};
	__property TApdSocksVersion SocksVersion = {read=FSocksVersion, write=SetSocksVersion, default=0};
	__property AnsiString UserCode = {read=FUserCode, write=SetUserCode};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TApdSocksServerInfo(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TWsAcceptEvent)(System::TObject* Sender, Oomisc::TInAddr Addr, bool &Accept);

typedef void __fastcall (__closure *TWsErrorEvent)(System::TObject* Sender, int ErrCode);

class DELPHICLASS TApdCustomWinsockPort;
class PASCALIMPLEMENTATION TApdCustomWinsockPort : public Adport::TApdCustomComPort 
{
	typedef Adport::TApdCustomComPort inherited;
	
protected:
	TWsAcceptEvent FOnWsAccept;
	Classes::TNotifyEvent FOnWsConnect;
	Classes::TNotifyEvent FOnWsDisconnect;
	TWsErrorEvent FOnWsError;
	AnsiString FWsAddress;
	Adsocket::TWsMode FWsMode;
	AnsiString FWsPort;
	bool FWsTelnet;
	void *FSockInstance;
	void *FComWindowProc;
	Classes::TStringList* FWsLocalAddresses;
	int FWsLocalAddressIndex;
	TApdSocksServerInfo* FWsSocksServerInfo;
	Adpacket::TApdDataPacket* FConnectPacket;
	bool FSocksComplete;
	int FTimer;
	bool FConnectFired;
	virtual Awuser::TApdBaseDispatcher* __fastcall ActivateDeviceLayer(void);
	virtual void __fastcall DeviceLayerChanged(void);
	virtual bool __fastcall DoAccept(int Addr);
	virtual void __fastcall DoConnect(void);
	virtual void __fastcall DoDisconnect(void);
	virtual void __fastcall DoError(int ErrCode);
	void __fastcall EnumHostAddresses(void);
	virtual int __fastcall InitializePort(void);
	DYNAMIC void __fastcall PortOpen(void);
	DYNAMIC void __fastcall PortClose(void);
	virtual void __fastcall ValidateComport(void);
	virtual void __fastcall SetUseMSRShadow(bool NewUse);
	void __fastcall SetWsAddress(AnsiString Value);
	void __fastcall SetWsLocalAddresses(Classes::TStringList* Value);
	Classes::TStringList* __fastcall GetWsLocalAddresses(void);
	void __fastcall SetWsLocalAddressIndex(int Value);
	void __fastcall SetWsMode(Adsocket::TWsMode Value);
	void __fastcall SetWsPort(AnsiString Value);
	void __fastcall SockWndProc(Messages::TMessage &Message);
	int __fastcall OpenSocksConnection(void);
	int __fastcall OpenSocksSocket(void);
	void __fastcall ContinueSocksNegotiation(void);
	void __fastcall ConnectToSocks4(void);
	void __fastcall ConnectToSocks4a(void);
	void __fastcall ConnectToSocks5(void);
	void __fastcall EnableSocks4Reply(void);
	void __fastcall EnableSocks5Reply(void);
	void __fastcall EnableSocks5UserNameReply(void);
	void __fastcall EnableSocks5RequestReply(void);
	void __fastcall EnableSocks5RequestEndReply(int Len);
	void __fastcall SendSocks5UserName(void);
	void __fastcall SendSocks5Request(void);
	void __fastcall Socks4Packet(System::TObject* Sender, void * Data, int Size);
	void __fastcall Socks5Packet(System::TObject* Sender, void * Data, int Size);
	void __fastcall Socks5UserNamePacket(System::TObject* Sender, void * Data, int Size);
	void __fastcall Socks5RequestPacket(System::TObject* Sender, void * Data, int Size);
	void __fastcall Socks5RequestEndPacket(System::TObject* Sender, void * Data, int Size);
	
public:
	__property AnsiString WsAddress = {read=FWsAddress, write=SetWsAddress};
	__property Classes::TStringList* WsLocalAddresses = {read=GetWsLocalAddresses, write=SetWsLocalAddresses};
	__property int WsLocalAddressIndex = {read=FWsLocalAddressIndex, write=SetWsLocalAddressIndex, nodefault};
	__property Adsocket::TWsMode WsMode = {read=FWsMode, write=SetWsMode, default=0};
	__property AnsiString WsPort = {read=FWsPort, write=SetWsPort};
	__property TApdSocksServerInfo* WsSocksServerInfo = {read=FWsSocksServerInfo, write=FWsSocksServerInfo};
	__property bool WsTelnet = {read=FWsTelnet, write=FWsTelnet, default=1};
	__property TWsAcceptEvent OnWsAccept = {read=FOnWsAccept, write=FOnWsAccept};
	__property Classes::TNotifyEvent OnWsConnect = {read=FOnWsConnect, write=FOnWsConnect};
	__property Classes::TNotifyEvent OnWsDisconnect = {read=FOnWsDisconnect, write=FOnWsDisconnect};
	__property TWsErrorEvent OnWsError = {read=FOnWsError, write=FOnWsError};
	__fastcall virtual TApdCustomWinsockPort(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomWinsockPort(void);
};


class DELPHICLASS TApdWinsockPort;
class PASCALIMPLEMENTATION TApdWinsockPort : public TApdCustomWinsockPort 
{
	typedef TApdCustomWinsockPort inherited;
	
__published:
	__property WsAddress ;
	__property WsLocalAddresses ;
	__property WsLocalAddressIndex ;
	__property WsMode  = {default=0};
	__property WsPort ;
	__property WsSocksServerInfo ;
	__property WsTelnet  = {default=1};
	__property AutoOpen  = {default=1};
	__property Baud  = {default=19200};
	__property BufferFull  = {default=0};
	__property BufferResume  = {default=0};
	__property CommNotificationLevel  = {default=10};
	__property ComNumber  = {default=0};
	__property DataBits  = {default=8};
	__property DeviceLayer  = {default=0};
	__property DTR  = {default=1};
	__property HWFlowOptions  = {default=0};
	__property InSize  = {default=4096};
	__property RS485Mode  = {default=0};
	__property TraceAllHex  = {default=0};
	__property Tracing  = {default=0};
	__property TraceSize  = {default=10000};
	__property TraceName ;
	__property TraceHex  = {default=1};
	__property LogAllHex  = {default=0};
	__property Logging  = {default=0};
	__property LogSize  = {default=10000};
	__property LogName ;
	__property LogHex  = {default=1};
	__property Open  = {default=0};
	__property OutSize  = {default=4096};
	__property Parity  = {default=0};
	__property PromptForPort  = {default=1};
	__property RTS  = {default=1};
	__property StopBits  = {default=1};
	__property SWFlowOptions  = {default=0};
	__property Tag  = {default=0};
	__property TapiMode  = {default=1};
	__property UseEventWord  = {default=1};
	__property UseMSRShadow  = {default=1};
	__property XOffChar  = {default=19};
	__property XOnChar  = {default=17};
	__property OnWsAccept ;
	__property OnWsConnect ;
	__property OnWsDisconnect ;
	__property OnWsError ;
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
	__property OnWaitChar ;
public:
	#pragma option push -w-inl
	/* TApdCustomWinsockPort.Create */ inline __fastcall virtual TApdWinsockPort(Classes::TComponent* AOwner) : TApdCustomWinsockPort(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomWinsockPort.Destroy */ inline __fastcall virtual ~TApdWinsockPort(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define adwDefWsMode (Adsocket::TWsMode)(0)
#define adwDefWsPort "telnet"
static const bool adwDefWsTelnet = true;

}	/* namespace Adwnport */
using namespace Adwnport;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdWnPort
