// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AwWnsock.pas' rev: 6.00

#ifndef AwWnsockHPP
#define AwWnsockHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AwUser.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <AdSocket.hpp>	// Pascal unit
#include <AdWUtil.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Awwnsock
{
//-- type declarations -------------------------------------------------------
struct TServerClientRec;
typedef TServerClientRec *PServerClientRec;

#pragma pack(push, 4)
struct TServerClientRec
{
	int ServerSocket;
	int ClientSocket;
} ;
#pragma pack(pop)

#pragma option push -b-
enum TWsConnectionState { wcsInit, wcsConnected };
#pragma option pop

#pragma option push -b-
enum TTelnetOpt { tnoFalse, tnoNegotiating, tnoTrue };
#pragma option pop

class DELPHICLASS TWsConnection;
class DELPHICLASS TApdWinsockDispatcher;
class PASCALIMPLEMENTATION TApdWinsockDispatcher : public Awuser::TApdBaseDispatcher 
{
	typedef Awuser::TApdBaseDispatcher inherited;
	
private:
	bool InDispatcher;
	#pragma pack(push, 1)
	Adwutil::TSockAddrIn WsSockAddr;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	Adwutil::TSockAddrIn WsHostAddr;
	#pragma pack(pop)
	
	bool WsIsClient;
	bool WsIsTelnet;
	
protected:
	virtual int __fastcall EscapeComFunction(int Func);
	virtual int __fastcall FlushCom(int Queue);
	virtual int __fastcall GetComError(_COMSTAT &Stat);
	virtual unsigned __fastcall GetComEventMask(int EvtMask);
	virtual int __fastcall GetComState(_DCB &DCB);
	virtual int __fastcall SetComState(_DCB &DCB);
	virtual void __fastcall StartDispatcher(void);
	virtual void __fastcall StopDispatcher(void);
	virtual int __fastcall ReadCom(char * Buf, int Size);
	virtual int __fastcall WriteCom(char * Buf, int Size);
	virtual bool __fastcall SetupCom(int InSize, int OutSize);
	virtual bool __fastcall WaitComEvent(unsigned &EvtMask, Windows::POverlapped lpOverlapped);
	unsigned __fastcall Dispatcher(unsigned Msg, unsigned wParam, int lParam);
	
public:
	virtual int __fastcall CloseCom(void);
	void __fastcall InitSocketData(int LocalAddress, int Address, unsigned Port, bool IsClient, bool IsTelnet);
	virtual int __fastcall OpenCom(char * ComName, unsigned InQueue, unsigned OutQueue);
	virtual int __fastcall ProcessCommunications(void);
public:
	#pragma option push -w-inl
	/* TApdBaseDispatcher.Create */ inline __fastcall TApdWinsockDispatcher(System::TObject* Owner) : Awuser::TApdBaseDispatcher(Owner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdBaseDispatcher.Destroy */ inline __fastcall virtual ~TApdWinsockDispatcher(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TWsConnection : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	unsigned FSimBuf;
	int FCommSocket;
	TApdWinsockDispatcher* FDispatcher;
	TWsConnectionState FConnectionState;
	char *FInBuf;
	char *FInBufEnd;
	bool FInBufFull;
	unsigned FInSize;
	char *FInStart;
	char *FInCursor;
	char *FInEnd;
	bool FIsClient;
	bool FIsTelnet;
	char *FOutBuf;
	char *FOutBufEnd;
	bool FOutBufFull;
	unsigned FOutSize;
	char *FOutStart;
	char *FOutEnd;
	int FSocketHandle;
	TTelnetOpt FOptBinary;
	TTelnetOpt FOptSupga;
	TTelnetOpt FOptEcho;
	
protected:
	bool __fastcall GetConnected(void);
	unsigned __fastcall GetInChars(void);
	unsigned __fastcall GetOutChars(void);
	void __fastcall SetConnectionState(TWsConnectionState Value);
	
public:
	__fastcall virtual TWsConnection(Classes::TComponent* AOwner, unsigned InSize, unsigned OutSize);
	__fastcall virtual ~TWsConnection(void);
	char * __fastcall FindIAC(char * Start, unsigned Size);
	void __fastcall FlushInBuffer(void);
	void __fastcall FlushOutBuffer(void);
	bool __fastcall HandleCommand(char Command, char Option);
	int __fastcall ProcessCommands(char * Dest, unsigned Size);
	int __fastcall ReadBuf(void *Buf, int Size);
	void __fastcall SendDo(char Option);
	void __fastcall SendDont(char Option);
	void __fastcall SendWill(char Option);
	void __fastcall SendWont(char Option);
	void __fastcall SendTerminal(void);
	int __fastcall Shutdown(void);
	int __fastcall WriteBuf(void *Buf, int Size);
	__property int CommSocket = {read=FCommSocket, nodefault};
	__property bool Connected = {read=GetConnected, nodefault};
	__property TWsConnectionState ConnectionState = {read=FConnectionState, write=SetConnectionState, nodefault};
	__property unsigned InChars = {read=GetInChars, nodefault};
	__property unsigned InSize = {read=FInSize, nodefault};
	__property bool IsClient = {read=FIsClient, write=FIsClient, nodefault};
	__property bool IsTelnet = {read=FIsTelnet, write=FIsTelnet, nodefault};
	__property unsigned OutChars = {read=GetOutChars, nodefault};
	__property unsigned OutSize = {read=FOutSize, nodefault};
	__property int SocketHandle = {read=FSocketHandle, nodefault};
public:
	#pragma option push -w-inl
	/* TComponent.Create */ inline __fastcall virtual TWsConnection(Classes::TComponent* AOwner) : Classes::TComponent(AOwner) { }
	#pragma option pop
	
};


class DELPHICLASS TApdDeviceSocket;
class PASCALIMPLEMENTATION TApdDeviceSocket : public Adsocket::TApdSocket 
{
	typedef Adsocket::TApdSocket inherited;
	
private:
	AnsiString FWsTerminal;
	_RTL_CRITICAL_SECTION SockSection;
	
protected:
	int __fastcall DoDispMessage(int Socket, unsigned Event, int LP);
	int __fastcall DoWsMessage(int Socket, unsigned Event, int LP);
	virtual void __fastcall DoAccept(int Socket);
	virtual void __fastcall DoConnect(int Socket);
	virtual void __fastcall DoDisconnect(int Socket);
	virtual void __fastcall DoError(int Socket, int ErrCode);
	virtual void __fastcall DoRead(int Socket);
	virtual void __fastcall DoWrite(int Socket);
	int __fastcall TweakSocket(int Socket);
	
public:
	__fastcall virtual TApdDeviceSocket(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdDeviceSocket(void);
	void __fastcall LockList(void);
	void __fastcall UnLockList(void);
	TWsConnection* __fastcall FindConnection(int Socket);
	__property AnsiString WsTerminal = {read=FWsTerminal, write=FWsTerminal};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint DefAsyncStyles = 0x3b;
#define DefWsTerminal "vt100"
static const bool DefOptSupga = true;
static const bool DefOptEcho = true;
static const char TELNET_IAC = '\xff';
static const char TELNET_DONT = '\xfe';
static const char TELNET_DO = '\xfd';
static const char TELNET_WONT = '\xfc';
static const char TELNET_WILL = '\xfb';
static const char TELNET_SB = '\xfa';
static const char TELNET_GA = '\xf9';
static const char TELNET_EL = '\xf8';
static const char TELNET_EC = '\xf7';
static const char TELNET_AYT = '\xf6';
static const char TELNET_AO = '\xf5';
static const char TELNET_IP = '\xf4';
static const char TELNET_BRK = '\xf3';
static const char TELNET_DM = '\xf2';
static const char TELNET_NOP = '\xf1';
static const char TELNET_SE = '\xf0';
static const char TELNET_EOR = '\xef';
static const char TELNET_ABORT = '\xee';
static const char TELNET_SUSP = '\xed';
static const char TELNET_EOF = '\xec';
static const char TELNET_NULL = '\x0';
static const char TELNET_LF = '\xa';
static const char TELNET_CR = '\xd';
static const char TELNETOPT_BINARY = '\x0';
static const char TELNETOPT_ECHO = '\x1';
static const char TELNETOPT_SUPGA = '\x3';
static const char TELNETOPT_TERM = '\x18';
static const char TELNETOPT_SPEED = '\x20';
extern PACKAGE TApdDeviceSocket* ApdSocket;

}	/* namespace Awwnsock */
using namespace Awwnsock;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AwWnsock
