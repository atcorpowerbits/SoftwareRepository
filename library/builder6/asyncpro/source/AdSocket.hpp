// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdSocket.pas' rev: 6.00

#ifndef AdSocketHPP
#define AdSocketHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdWUtil.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adsocket
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 4)
struct TCMAPDSocketMessage
{
	unsigned Msg;
	int Socket;
	Word SelectEvent;
	Word SelectError;
	int Result;
} ;
#pragma pack(pop)

class DELPHICLASS EApdSocketException;
class PASCALIMPLEMENTATION EApdSocketException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	int ErrorCode;
	__fastcall EApdSocketException(int ErrCode, char * Dummy);
	__fastcall EApdSocketException(int ErrCode, int Dummy1, int Dummy2);
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EApdSocketException(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EApdSocketException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EApdSocketException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EApdSocketException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EApdSocketException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EApdSocketException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EApdSocketException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EApdSocketException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EApdSocketException(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TWsMode { wsClient, wsServer };
#pragma option pop

typedef void __fastcall (__closure *TWsNotifyEvent)(System::TObject* Sender, int Socket);

typedef void __fastcall (__closure *TWsSocketErrorEvent)(System::TObject* Sender, int Socket, int ErrCode);

class DELPHICLASS TApdSocket;
class PASCALIMPLEMENTATION TApdSocket : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
protected:
	HWND FHandle;
	TWsNotifyEvent FOnWsAccept;
	TWsNotifyEvent FOnWsConnect;
	TWsNotifyEvent FOnWsDisconnect;
	TWsSocketErrorEvent FOnWsError;
	TWsNotifyEvent FOnWsRead;
	TWsNotifyEvent FOnWsWrite;
	bool asDllLoaded;
	int asStartErrorCode;
	#pragma pack(push, 1)
	Adwutil::TwsaData asWSData;
	#pragma pack(pop)
	
	AnsiString __fastcall GetDescription();
	HWND __fastcall GetHandle(void);
	int __fastcall GetLastError(void);
	AnsiString __fastcall GetLocalHost();
	AnsiString __fastcall GetLocalAddress();
	AnsiString __fastcall GetSystemStatus();
	MESSAGE void __fastcall CMAPDSocketMessage(TCMAPDSocketMessage &Message);
	void __fastcall WndProc(Messages::TMessage &Message);
	DYNAMIC void __fastcall ShowErrorMessage(int Err);
	virtual void __fastcall DoAccept(int Socket);
	virtual void __fastcall DoConnect(int Socket);
	virtual void __fastcall DoDisconnect(int Socket);
	virtual void __fastcall DoError(int Socket, int ErrCode);
	virtual void __fastcall DoRead(int Socket);
	virtual void __fastcall DoWrite(int Socket);
	
public:
	__fastcall virtual TApdSocket(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdSocket(void);
	void __fastcall CheckLoaded(void);
	virtual void __fastcall DefaultHandler(void *Message);
	int __fastcall htonl(int HostLong);
	Word __fastcall htons(Word HostShort);
	int __fastcall ntohl(int NetLong);
	Word __fastcall ntohs(Word NetShort);
	AnsiString __fastcall NetAddr2String(Oomisc::TInAddr InAddr);
	Oomisc::TInAddr __fastcall String2NetAddr(const AnsiString S);
	AnsiString __fastcall LookupAddress(Oomisc::TInAddr InAddr);
	Oomisc::TInAddr __fastcall LookupName(const AnsiString Name);
	AnsiString __fastcall LookupPort(Word Port);
	int __fastcall LookupService(const AnsiString Service);
	int __fastcall AcceptSocket(int Socket, Adwutil::TSockAddrIn &Address);
	int __fastcall BindSocket(int Socket, const Adwutil::TSockAddrIn &Address);
	bool __fastcall CanReadSocket(int Socket, int WaitTime);
	bool __fastcall CanWriteSocket(int Socket, int WaitTime);
	int __fastcall CloseSocket(int Socket);
	int __fastcall ConnectSocket(int Socket, const Adwutil::TSockAddrIn &Address);
	int __fastcall CreateSocket(void);
	int __fastcall ListenSocket(int Socket, int Backlog);
	int __fastcall ReadSocket(int Socket, void *Buf, int BufSize, int Flags);
	int __fastcall ShutdownSocket(int Socket, int How);
	int __fastcall SetSocketOptions(int Socket, unsigned Level, int OptName, void *OptVal, int OptLen);
	int __fastcall SetAsyncStyles(int Socket, int lEvent);
	int __fastcall WriteSocket(int Socket, void *Buf, int BufSize, int Flags);
	__property AnsiString Description = {read=GetDescription};
	__property HWND Handle = {read=GetHandle, nodefault};
	__property Word HighVersion = {read=asWSData.wHighVersion, nodefault};
	__property int LastError = {read=GetLastError, nodefault};
	__property AnsiString LocalHost = {read=GetLocalHost};
	__property AnsiString LocalAddress = {read=GetLocalAddress};
	__property Word MaxSockets = {read=asWSData.iMaxSockets, nodefault};
	__property AnsiString SystemStatus = {read=GetSystemStatus};
	__property Word WsVersion = {read=asWSData.wVersion, nodefault};
	__property TWsNotifyEvent OnWsAccept = {read=FOnWsAccept, write=FOnWsAccept};
	__property TWsNotifyEvent OnWsConnect = {read=FOnWsConnect, write=FOnWsConnect};
	__property TWsNotifyEvent OnWsDisconnect = {read=FOnWsDisconnect, write=FOnWsDisconnect};
	__property TWsSocketErrorEvent OnWsError = {read=FOnWsError, write=FOnWsError};
	__property TWsNotifyEvent OnWsRead = {read=FOnWsRead, write=FOnWsRead};
	__property TWsNotifyEvent OnWsWrite = {read=FOnWsWrite, write=FOnWsWrite};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint IPStrSize = 0xf;
static const Word CM_APDSOCKETMESSAGE = 0xb11;
static const Word CM_APDSOCKETQUIT = 0xb12;
static const Word ADWSBASE = 0x2328;
static const Word ADWSERROR = 0x2329;
static const Word ADWSLOADERROR = 0x232a;
static const Word ADWSVERSIONERROR = 0x232b;
static const Word ADWSNOTINIT = 0x232c;
static const Word ADWSINVPORT = 0x232d;
static const Word ADWSCANTCHANGE = 0x232e;
static const Word ADWSCANTRESOLVE = 0x232f;
static const Word ADWSREQUESTFAILED = 0x2330;
static const Word ADWSREJECTEDIDENTD = 0x2331;
static const Word ADWSREJECTEDUSERID = 0x2332;
static const Word ADWSUNKNOWNERROR = 0x2333;
static const Word ADWSSOCKSERROR = 0x2334;
static const Word ADWSCONNECTIONNOTALLOWED = 0x2335;
static const Word ADWSNETWORKUNREACHABLE = 0x2336;
static const Word ADWSHOSTUNREACHABLE = 0x2337;
static const Word ADWSREFUSED = 0x2338;
static const Word ADWSTTLEXPIRED = 0x2339;
static const Word ADWSBADCOMMAND = 0x233a;
static const Word ADWSBADADDRESSTYPE = 0x233b;
static const Word ADWSUNSUPPORTEDREPLY = 0x233c;
static const Word ADWSINVALIDREPLY = 0x233d;

}	/* namespace Adsocket */
using namespace Adsocket;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdSocket
