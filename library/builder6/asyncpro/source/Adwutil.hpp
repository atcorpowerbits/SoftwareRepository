// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdWUtil.pas' rev: 6.00

#ifndef AdWUtilHPP
#define AdWUtilHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <OoMisc.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adwutil
{
//-- type declarations -------------------------------------------------------
typedef int TSocket;

struct TFDSet;
typedef TFDSet *PFDSet;

#pragma pack(push, 1)
struct TFDSet
{
	int fd_count;
	int fd_array[64];
} ;
#pragma pack(pop)

struct TTimeVal;
typedef TTimeVal *PTimeVal;

#pragma pack(push, 1)
struct TTimeVal
{
	int tv_sec;
	int tv_usec;
} ;
#pragma pack(pop)

typedef Oomisc::TInAddr *TAddrArray[256];

typedef Oomisc::PInAddr *PAddrArray;

typedef char *TAliasArray[256];

typedef char * *PAliasArray;

struct THostEnt;
typedef THostEnt *PHostEnt;

#pragma pack(push, 1)
struct THostEnt
{
	char *h_name;
	char * *h_aliases;
	short h_addrtype;
	short h_length;
	Oomisc::PInAddr *h_addr_list;
} ;
#pragma pack(pop)

struct TNetEnt;
typedef TNetEnt *PNetEnt;

#pragma pack(push, 1)
struct TNetEnt
{
	char *n_name;
	char * *n_aliases;
	short n_addrtype;
	int n_net;
} ;
#pragma pack(pop)

struct TServEnt;
typedef TServEnt *PServEnt;

#pragma pack(push, 1)
struct TServEnt
{
	char *s_name;
	char * *s_aliases;
	short s_port;
	char *s_proto;
} ;
#pragma pack(pop)

struct TProtoEnt;
typedef TProtoEnt *PProtoEnt;

#pragma pack(push, 1)
struct TProtoEnt
{
	char *p_name;
	char * *p_aliases;
	short p_proto;
} ;
#pragma pack(pop)

struct TSockAddrIn;
typedef TSockAddrIn *PSockAddrIn;

#pragma pack(push, 1)
struct TSockAddrIn
{
	
	union
	{
		struct 
		{
			Word sa_family;
			char sa_data[14];
			
		};
		struct 
		{
			Word sin_family;
			Word sin_port;
			Oomisc::TInAddr sin_addr;
			char sin_zero[8];
			
		};
		
	};
} ;
#pragma pack(pop)

struct TwsaData;
typedef TwsaData *PwsaData;

#pragma pack(push, 1)
struct TwsaData
{
	Word wVersion;
	Word wHighVersion;
	char szDescription[257];
	char szSystemStatus[129];
	Word iMaxSockets;
	Word iMaxUdpDg;
	char *lpVendorInfo;
} ;
#pragma pack(pop)

struct TTransmitFileBuffers;
typedef TTransmitFileBuffers *PTransmitFileBuffers;

#pragma pack(push, 1)
struct TTransmitFileBuffers
{
	void *Head;
	unsigned HeadLength;
	void *Tail;
	unsigned TailLength;
} ;
#pragma pack(pop)

typedef TSockAddrIn *PSockAddr;

typedef TSockAddrIn  TSockAddr;

struct TSockProto;
typedef TSockProto *PSockProto;

#pragma pack(push, 1)
struct TSockProto
{
	Word sp_family;
	Word sp_protocol;
} ;
#pragma pack(pop)

struct TLinger;
typedef TLinger *PLinger;

#pragma pack(push, 1)
struct TLinger
{
	Word l_onoff;
	Word l_linger;
} ;
#pragma pack(pop)

struct TWsDataRec;
typedef TWsDataRec *PWsDataRec;

#pragma pack(push, 1)
struct TWsDataRec
{
	TSockAddrIn WsSockAddr;
	TSockAddrIn WsHostAddr;
	bool WsIsClient;
	bool WsIsTelnet;
} ;
#pragma pack(pop)

typedef int __stdcall (*TfnAccept)(int S, TSockAddrIn &Addr, int &Addrlen);

typedef int __stdcall (*TfnBind)(int S, TSockAddrIn &Addr, int NameLen);

typedef int __stdcall (*TfnCloseSocket)(int S);

typedef int __stdcall (*TfnConnect)(int S, TSockAddrIn &Name, int NameLen);

typedef int __stdcall (*TfnIOCtlSocket)(int S, int Cmd, int &Arg);

typedef int __stdcall (*TfnGetPeerName)(int S, TSockAddrIn &Name, int &NameLen);

typedef int __stdcall (*TfnGetSockName)(int S, TSockAddrIn &Name, int &NameLen);

typedef int __stdcall (*TfnGetSockOpt)(int S, int Level, int OptName, void *OptVal, int &OptLen);

typedef int __stdcall (*Tfnhtonl)(int HostLong);

typedef Word __stdcall (*Tfnhtons)(Word HostShort);

typedef int __stdcall (*TfnINet_Addr)(char * Cp);

typedef char * __stdcall (*TfnINet_NtoA)(Oomisc::TInAddr InAddr);

typedef int __stdcall (*TfnListen)(int S, int Backlog);

typedef int __stdcall (*Tfnntohl)(int NetLong);

typedef Word __stdcall (*Tfnntohs)(Word NetShort);

typedef int __stdcall (*TfnRecv)(int S, void *Buf, int Len, int Flags);

typedef int __stdcall (*TfnRecvFrom)(int S, void *Buf, int Len, int Flags, TSockAddrIn &From, int &FromLen);

typedef int __stdcall (*TfnSelect)(int Nfds, PFDSet Readfds, PFDSet Writefds, PFDSet Exceptfds, PTimeVal Timeout);

typedef int __stdcall (*TfnSend)(int S, void *Buf, int Len, int Flags);

typedef int __stdcall (*TfnSendTo)(int S, void *Buf, int Len, int Flags, TSockAddrIn &AddrTo, int ToLen);

typedef int __stdcall (*TfnSetSockOpt)(int S, int Level, int OptName, void *OptVal, int OptLen);

typedef int __stdcall (*TfnShutdown)(int S, int How);

typedef int __stdcall (*TfnSocket)(int Af, int Struct, int Protocol);

typedef PHostEnt __stdcall (*TfnGetHostByAddr)(void *Addr, int Len, int Struct);

typedef PHostEnt __stdcall (*TfnGetHostByName)(char * Name);

typedef int __stdcall (*TfnGetHostName)(char * Name, int Len);

typedef PServEnt __stdcall (*TfnGetServByPort)(Word Port, char * Proto);

typedef PServEnt __stdcall (*TfnGetServByName)(char * Name, char * Proto);

typedef PProtoEnt __stdcall (*TfnGetProtoByNumber)(int Proto);

typedef PProtoEnt __stdcall (*TfnGetProtoByName)(char * Name);

typedef int __stdcall (*TfnwsaStartup)(Word wVersionRequired, TwsaData &WSData);

typedef int __stdcall (*TfnwsaCleanup)(void);

typedef void __stdcall (*TfnwsaSetLastError)(int iError);

typedef int __stdcall (*TfnwsaGetLastError)(void);

typedef BOOL __stdcall (*TfnwsaIsBlocking)(void);

typedef int __stdcall (*TfnwsaUnhookBlockingHook)(void);

typedef void * __stdcall (*TfnwsaSetBlockingHook)(void * lpBlockFunc);

typedef int __stdcall (*TfnwsaCancelBlockingCall)(void);

typedef unsigned __stdcall (*TfnwsaAsyncGetServByName)(HWND HWindow, int wMsg, char * Name, char * Proto, char * Buf, int BufLen);

typedef unsigned __stdcall (*TfnwsaAsyncGetServByPort)(HWND HWindow, int wMsg, int Port, char * Proto, char * Buf, int BufLen);

typedef unsigned __stdcall (*TfnwsaAsyncGetProtoByName)(HWND HWindow, int wMsg, char * Name, char * Buf, int BufLen);

typedef unsigned __stdcall (*TfnwsaAsyncGetProtoByNumber)(HWND HWindow, int wMsg, int Number, char * Buf, int BufLen);

typedef unsigned __stdcall (*TfnwsaAsyncGetHostByName)(HWND HWindow, int wMsg, char * Name, char * Buf, int BufLen);

typedef unsigned __stdcall (*TfnwsaAsyncGetHostByAddr)(HWND HWindow, int wMsg, char * Addr, int Len, int Struct, char * Buf, int BufLen);

typedef int __stdcall (*TfnwsaCancelAsyncRequest)(unsigned hAsyncTaskHandle);

typedef int __stdcall (*TfnwsaAsyncSelect)(int S, HWND HWindow, int wMsg, int lEvent);

typedef int __stdcall (*TfnwsaRecvEx)(int S, void *Buf, int Len, int &Flags);

typedef BOOL __stdcall (*TfnTransmitFile)(int hSocket, unsigned hFile, unsigned nNumberOfBytesToWrite, unsigned nNumberOfBytesPerSend, Windows::POverlapped lpOverlapped, PTransmitFileBuffers lpTransmitBuffers, unsigned dwReserved);

#pragma pack(push, 4)
struct TSocketFuncs
{
	TfnAccept Accept;
	TfnBind Bind;
	TfnCloseSocket CloseSocket;
	TfnConnect Connect;
	TfnIOCtlSocket IOCtlSocket;
	TfnGetPeerName GetPeerName;
	TfnGetSockName GetSockName;
	TfnGetSockOpt GetSockOpt;
	Tfnhtonl htonl;
	Tfnhtons htons;
	TfnINet_Addr INet_Addr;
	TfnINet_NtoA INet_Ntoa;
	TfnListen Listen;
	Tfnntohl ntohl;
	Tfnntohs ntohs;
	TfnRecv Recv;
	TfnRecvFrom RecvFrom;
	TfnSelect Select;
	TfnSend Send;
	TfnSendTo SendTo;
	TfnSetSockOpt SetSockOpt;
	TfnShutdown Shutdown;
	TfnSocket Socket;
	TfnGetHostByAddr GetHostByAddr;
	TfnGetHostByName GetHostByName;
	TfnGetHostName GetHostName;
	TfnGetServByPort GetServByPort;
	TfnGetServByName GetServByName;
	TfnGetProtoByNumber GetProtoByNumber;
	TfnGetProtoByName GetProtoByName;
	TfnwsaStartup wsaStartup;
	TfnwsaCleanup wsaCleanup;
	TfnwsaSetLastError wsaSetLastError;
	TfnwsaGetLastError wsaGetLastError;
	TfnwsaIsBlocking wsaIsBlocking;
	TfnwsaUnhookBlockingHook wsaUnhookBlockingHook;
	TfnwsaSetBlockingHook wsaSetBlockingHook;
	TfnwsaCancelBlockingCall wsaCancelBlockingCall;
	TfnwsaAsyncGetServByName wsaAsyncGetServByName;
	TfnwsaAsyncGetServByPort wsaAsyncGetServByPort;
	TfnwsaAsyncGetProtoByName wsaAsyncGetProtoByName;
	TfnwsaAsyncGetProtoByNumber wsaAsyncGetProtoByNumber;
	TfnwsaAsyncGetHostByName wsaAsyncGetHostByName;
	TfnwsaAsyncGetHostByAddr wsaAsyncGetHostByAddr;
	TfnwsaCancelAsyncRequest wsaCancelAsyncRequest;
	TfnwsaAsyncSelect wsaAsyncSelect;
	TfnwsaRecvEx wsaRecvEx;
	TfnTransmitFile TransmitFile;
} ;
#pragma pack(pop)

typedef TSocketFuncs *PSocketFuncs;

//-- var, const, procedure ---------------------------------------------------
static const Word Sock_Version = 0x101;
static const Shortint Fd_Setsize = 0x40;
static const Shortint IocParm_Mask = 0x7f;
static const int Ioc_Void = 0x20000000;
static const int Ioc_Out = 0x40000000;
static const unsigned Ioc_In = 0x80000000;
static const unsigned Ioc_InOut = 0xc0000000;
static const Shortint IpProto_Ip = 0x0;
static const Shortint IpProto_Icmp = 0x1;
static const Shortint IpProto_Igmp = 0x2;
static const Shortint IpProto_Ggp = 0x3;
static const Shortint IpProto_Tcp = 0x6;
static const Shortint IpProto_Pup = 0xc;
static const Shortint IpProto_Udp = 0x11;
static const Shortint IpProto_Idp = 0x16;
static const Shortint IpProto_Nd = 0x4d;
static const Byte IpProto_Raw = 0xff;
static const Word IpProto_Max = 0x100;
static const Shortint IpPort_Echo = 0x7;
static const Shortint IpPort_Discard = 0x9;
static const Shortint IpPort_SyStat = 0xb;
static const Shortint IpPort_Daytime = 0xd;
static const Shortint IpPort_NetStat = 0xf;
static const Shortint IpPort_Ftp = 0x15;
static const Shortint IpPort_Telnet = 0x17;
static const Shortint IpPort_Smtp = 0x19;
static const Shortint IpPort_TimeServer = 0x25;
static const Shortint IpPort_NameServer = 0x2a;
static const Shortint IpPort_WhoIs = 0x2b;
static const Shortint IpPort_Mtp = 0x39;
static const Shortint IpPort_Tftp = 0x45;
static const Shortint IpPort_Rje = 0x4d;
static const Shortint IpPort_Finger = 0x4f;
static const Shortint IpPort_TtyLink = 0x57;
static const Shortint IpPort_SupDup = 0x5f;
static const Word IpPort_ExecServer = 0x200;
static const Word IpPort_LoginServer = 0x201;
static const Word IpPort_CmdServer = 0x202;
static const Word IpPort_EfsServer = 0x208;
static const Word IpPort_BiffUdp = 0x200;
static const Word IpPort_WhoServer = 0x201;
static const Word IpPort_RouteServer = 0x208;
static const Word IpPort_Reserved = 0x400;
static const Byte ImpLink_Ip = 0x9b;
static const Byte ImpLink_LowExper = 0x9c;
static const Byte ImpLink_HighExper = 0x9e;
static const int FiOnRead = 0x4004667f;
static const unsigned FiOnBio = 0x8004667e;
static const unsigned FioAsync = 0x8004667d;
static const Shortint InAddr_Any = 0x0;
static const int InAddr_LoopBack = 0x7f000001;
static const unsigned InAddr_BroadCast = 0xffffffff;
static const unsigned InAddr_None = 0xffffffff;
static const Word wsaDescription_Len = 0x100;
static const Byte wsaSys_Status_Len = 0x80;
static const Shortint Ip_Options = 0x1;
static const Shortint Ip_Multicast_If = 0x2;
static const Shortint Ip_Multicast_Ttl = 0x3;
static const Shortint Ip_Multicast_Loop = 0x4;
static const Shortint Ip_Add_Membership = 0x5;
static const Shortint Ip_Drop_Membership = 0x6;
static const Shortint Ip_Default_Multicast_Ttl = 0x1;
static const Shortint Ip_Default_Multicast_Loop = 0x1;
static const Shortint Ip_Max_Memberships = 0x14;
static const int Invalid_Socket = 0xffffffff;
static const Shortint Socket_Error = 0xffffffff;
static const Shortint Sock_Stream = 0x1;
static const Shortint Sock_DGram = 0x2;
static const Shortint Sock_Raw = 0x3;
static const Shortint Sock_Rdm = 0x4;
static const Shortint Sock_SeqPacket = 0x5;
static const Shortint So_Debug = 0x1;
static const Shortint So_AcceptConn = 0x2;
static const Shortint So_ReuseAddr = 0x4;
static const Shortint So_KeepAlive = 0x8;
static const Shortint So_DontRoute = 0x10;
static const Shortint So_Broadcast = 0x20;
static const Shortint So_UseLoopback = 0x40;
static const Byte So_Linger = 0x80;
static const Word So_OobInline = 0x100;
static const Word So_DontLinger = 0xff7f;
static const Shortint SD_Receive = 0x0;
static const Shortint SD_Send = 0x1;
static const Shortint SD_Both = 0x2;
static const Word So_SndBuf = 0x1001;
static const Word So_RcvBuf = 0x1002;
static const Word So_SndLoWat = 0x1003;
static const Word So_RcvLoWat = 0x1004;
static const Word So_SndTimeO = 0x1005;
static const Word So_RcvTimeO = 0x1006;
static const Word So_Error = 0x1007;
static const Word So_Type = 0x1008;
static const Word So_ConnData = 0x7000;
static const Word So_ConnOpt = 0x7001;
static const Word So_DISCData = 0x7002;
static const Word So_DISCOpt = 0x7003;
static const Word So_ConnDataLen = 0x7004;
static const Word So_ConnOptLen = 0x7005;
static const Word So_DISCDataLen = 0x7006;
static const Word So_DISCOptLen = 0x7007;
static const Word So_OpenType = 0x7008;
static const Shortint So_Synchronous_Alert = 0x10;
static const Shortint So_Synchronous_NonAlert = 0x20;
static const Word So_MaxDG = 0x7009;
static const Word So_MaxPathDG = 0x700a;
static const Shortint Tcp_NoDelay = 0x1;
static const Word Tcp_BsdUrgent = 0x7000;
static const Shortint Af_Unspec = 0x0;
static const Shortint Af_Unix = 0x1;
static const Shortint Af_Inet = 0x2;
static const Shortint Af_ImpLink = 0x3;
static const Shortint Af_Pup = 0x4;
static const Shortint Af_Chaos = 0x5;
static const Shortint Af_Ipx = 0x6;
static const Shortint Af_Ns = 0x6;
static const Shortint Af_Iso = 0x7;
static const Shortint Af_Osi = 0x7;
static const Shortint Af_Ecma = 0x8;
static const Shortint Af_DataKit = 0x9;
static const Shortint Af_CcItt = 0xa;
static const Shortint Af_Sna = 0xb;
static const Shortint Af_DecNet = 0xc;
static const Shortint Af_Dli = 0xd;
static const Shortint Af_Lat = 0xe;
static const Shortint Af_HyLink = 0xf;
static const Shortint Af_AppleTalk = 0x10;
static const Shortint Af_NetBios = 0x11;
static const Shortint Af_VoiceView = 0x12;
static const Shortint Af_Max = 0x13;
static const Shortint Pf_Unspec = 0x0;
static const Shortint Pf_Unix = 0x1;
static const Shortint Pf_Inet = 0x2;
static const Shortint Pf_ImpLink = 0x3;
static const Shortint Pf_Pup = 0x4;
static const Shortint Pf_Chaos = 0x5;
static const Shortint Pf_Ns = 0x6;
static const Shortint Pf_Ipx = 0x6;
static const Shortint Pf_Iso = 0x7;
static const Shortint Pf_Osi = 0x7;
static const Shortint Pf_Ecma = 0x8;
static const Shortint Pf_DataKit = 0x9;
static const Shortint Pf_CcItt = 0xa;
static const Shortint Pf_Sna = 0xb;
static const Shortint Pf_DecNet = 0xc;
static const Shortint Pf_Dli = 0xd;
static const Shortint Pf_Lat = 0xe;
static const Shortint Pf_HyLink = 0xf;
static const Shortint Pf_AppleTalk = 0x10;
static const Shortint Pf_VoiceView = 0x12;
static const Shortint Pf_Max = 0x13;
static const Word Sol_Socket = 0xffff;
static const Shortint SoMaxConn = 0x5;
static const Shortint Msg_Oob = 0x1;
static const Shortint Msg_Peek = 0x2;
static const Shortint Msg_DontRoute = 0x4;
static const Shortint Msg_MaxIovLen = 0x10;
static const Word Msg_Partial = 0x8000;
static const Word MaxGetHostStruct = 0x400;
static const Shortint Fd_Read = 0x1;
static const Shortint Fd_Write = 0x2;
static const Shortint Fd_Oob = 0x4;
static const Shortint Fd_Accept = 0x8;
static const Shortint Fd_Connect = 0x10;
static const Shortint Fd_Close = 0x20;
static const Word EWouldBlock = 0x2733;
static const Word EInProgress = 0x2734;
static const Word EAlreadY = 0x2735;
static const Word ENotSock = 0x2736;
static const Word EDestAddrReq = 0x2737;
static const Word EMsgSize = 0x2738;
static const Word EPrototype = 0x2739;
static const Word ENoProtoOpt = 0x273a;
static const Word EProtoNoSupport = 0x273b;
static const Word ESocktNoSupport = 0x273c;
static const Word EOpNotSupp = 0x273d;
static const Word EPfNoSupport = 0x273e;
static const Word EAfNoSupport = 0x273f;
static const Word EAddrInUse = 0x2740;
static const Word EAddrNotAvail = 0x2741;
static const Word ENetDown = 0x2742;
static const Word ENetUnreach = 0x2743;
static const Word ENetReset = 0x2744;
static const Word EConnAborted = 0x2745;
static const Word EConnReset = 0x2746;
static const Word ENoBufs = 0x2747;
static const Word EIsConn = 0x2748;
static const Word ENotConn = 0x2749;
static const Word EShutDown = 0x274a;
static const Word ETooManyRefs = 0x274b;
static const Word ETimedOut = 0x274c;
static const Word EConnRefused = 0x274d;
static const Word ELoop = 0x274e;
static const Word ENameTooLong = 0x274f;
static const Word EHostDown = 0x2750;
static const Word EHostUnreach = 0x2751;
static const Word ENotEmpty = 0x2752;
static const Word EProcLim = 0x2753;
static const Word EUsers = 0x2754;
static const Word EDQuot = 0x2755;
static const Word EStale = 0x2756;
static const Word ERemote = 0x2757;
static const Word MaxAddrs = 0x100;
static const Word MaxAlias = 0x100;
extern PACKAGE TSocketFuncs SockFuncs;
extern PACKAGE bool __fastcall LoadWinsock(void);
extern PACKAGE int __fastcall wsaMakeSyncReply(Word Buflen, Word Error);
extern PACKAGE int __fastcall wsaMakeSelectReply(Word Event, Word Error);
extern PACKAGE Word __fastcall wsaGetAsyncBuflen(int Param);
extern PACKAGE Word __fastcall wsaGetAsyncError(int Param);
extern PACKAGE Word __fastcall wsaGetSelectEvent(int Param);
extern PACKAGE Word __fastcall wsaGetSelectError(int Param);

}	/* namespace Adwutil */
using namespace Adwutil;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdWUtil
