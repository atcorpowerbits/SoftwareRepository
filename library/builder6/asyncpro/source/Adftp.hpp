// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdFtp.pas' rev: 6.00

#ifndef AdFtpHPP
#define AdFtpHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdExcept.hpp>	// Pascal unit
#include <AdPacket.hpp>	// Pascal unit
#include <AdPort.hpp>	// Pascal unit
#include <AdWnPort.hpp>	// Pascal unit
#include <AdWUtil.hpp>	// Pascal unit
#include <AdSocket.hpp>	// Pascal unit
#include <AwUser.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adftp
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TFtpRetrieveMode { rmAppend, rmReplace, rmRestart };
#pragma option pop

#pragma option push -b-
enum TFtpStoreMode { smAppend, smReplace, smUnique, smRestart };
#pragma option pop

#pragma option push -b-
enum TFtpFileType { ftAscii, ftBinary };
#pragma option pop

#pragma option push -b-
enum TFtpProcessState { psClosed, psLogin, psIdle, psDir, psGet, psPut, psRen, psCmd, psMkDir };
#pragma option pop

#pragma option push -b-
enum TFtpStatusCode { scClose, scOpen, scLogout, scLogin, scComplete, scCurrentDir, scDataAvail, scProgress, scTransferOK, scTimeout };
#pragma option pop

#pragma option push -b-
enum TFtpLogCode { lcClose, lcOpen, lcLogout, lcLogin, lcDelete, lcRename, lcReceive, lcStore, lcComplete, lcRestart, lcTimeout, lcUserAbort };
#pragma option pop

typedef void __fastcall (__closure *TFtpErrorEvent)(System::TObject* Sender, int ErrorCode, char * ErrorText);

typedef void __fastcall (__closure *TFtpLogEvent)(System::TObject* Sender, TFtpLogCode LogCode);

typedef void __fastcall (__closure *TFtpReplyEvent)(System::TObject* Sender, int ReplyCode, char * ReplyText);

typedef void __fastcall (__closure *TFtpStatusEvent)(System::TObject* Sender, TFtpStatusCode StatusCode, char * InfoText);

typedef AnsiString AdFtp__2[32];

class DELPHICLASS TApdCustomFtpClient;
class DELPHICLASS TApdFtpLog;
class PASCALIMPLEMENTATION TApdFtpLog : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	bool FEnabled;
	AnsiString FFtpHistoryName;
	TApdCustomFtpClient* FFtpClient;
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	
public:
	__fastcall virtual TApdFtpLog(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdFtpLog(void);
	virtual void __fastcall UpdateLog(const TFtpLogCode LogCode);
	
__published:
	__property bool Enabled = {read=FEnabled, write=FEnabled, nodefault};
	__property AnsiString FtpHistoryName = {read=FFtpHistoryName, write=FFtpHistoryName};
	__property TApdCustomFtpClient* FtpClient = {read=FFtpClient, write=FFtpClient};
};


class PASCALIMPLEMENTATION TApdCustomFtpClient : public Adwnport::TApdCustomWinsockPort 
{
	typedef Adwnport::TApdCustomWinsockPort inherited;
	
protected:
	bool AbortXfer;
	AnsiString CmdStack[32];
	Byte CmdsStacked;
	#pragma pack(push, 1)
	Adwutil::TSockAddrIn DataName;
	#pragma pack(pop)
	
	int DataSocket;
	HWND hwndFtpEvent;
	Adpacket::TApdDataPacket* ReplyPacket;
	Byte DataBuffer[32769];
	char ReplyBuffer[32769];
	int ListenSocket;
	#pragma pack(push, 1)
	Adwutil::TSockAddrIn ListenName;
	#pragma pack(pop)
	
	Classes::TFileStream* LocalStream;
	bool MultiLine;
	AnsiString MultiLineTerm;
	bool NoEvents;
	TFtpProcessState ProcessState;
	Adsocket::TApdSocket* Sock;
	int Timer;
	AnsiString FAccount;
	int FBytesTransferred;
	int FConnectTimeout;
	int FFileLength;
	TFtpFileType FFileType;
	TApdFtpLog* FFtpLog;
	AnsiString FLocalFile;
	AnsiString FPassword;
	bool FPassiveMode;
	int FTransferTimeout;
	AnsiString FRemoteFile;
	int FRestartAt;
	int FReplyCode;
	bool FUserLoggedIn;
	AnsiString FUserName;
	TFtpErrorEvent FOnFtpError;
	TFtpStatusEvent FOnFtpStatus;
	Classes::TNotifyEvent FOnFtpConnected;
	Classes::TNotifyEvent FOnFtpDisconnected;
	TFtpLogEvent FOnFtpLog;
	TFtpReplyEvent FOnFtpReply;
	void __fastcall ChangeState(TFtpProcessState NewState);
	bool __fastcall DataConnect(void);
	void __fastcall DataConnectPASV(AnsiString IP);
	void __fastcall DataDisconnect(bool FlushBuffer);
	void __fastcall DataShutDown(void);
	virtual void __fastcall DoConnect(void);
	virtual void __fastcall DoDisconnect(void);
	void __fastcall FtpEventHandler(Messages::TMessage &Msg);
	void __fastcall FtpReplyHandler(int ReplyCode, char * PData);
	bool __fastcall GetConnected(void);
	int __fastcall GetData(void);
	bool __fastcall GetInProgress(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	AnsiString __fastcall PopCommand();
	void __fastcall PostError(int Code, char * Info);
	void __fastcall PostLog(TFtpLogCode Code);
	void __fastcall PostStatus(TFtpStatusCode Code, char * Info);
	void __fastcall PushCommand(const AnsiString Cmd);
	int __fastcall PutData(void);
	void __fastcall ReplyPacketHandler(System::TObject* Sender, AnsiString Data);
	void __fastcall ResetTimer(void);
	void __fastcall SendCommand(const AnsiString Cmd);
	void __fastcall SetFtpLog(const TApdFtpLog* NewLog);
	void __fastcall StartTimer(void);
	void __fastcall StopTimer(void);
	void __fastcall TimerTrigger(unsigned Msg, unsigned wParam, int lParam);
	void __fastcall WsDataAccept(System::TObject* Sender, int Socket);
	void __fastcall WsDataDisconnect(System::TObject* Sender, int Socket);
	void __fastcall WsDataError(System::TObject* Sender, int Socket, int ErrorCode);
	void __fastcall WsDataRead(System::TObject* Sender, int Socket);
	void __fastcall WsDataWrite(System::TObject* Sender, int Socket);
	__property AnsiString Account = {read=FAccount, write=FAccount};
	__property int ConnectTimeout = {read=FConnectTimeout, write=FConnectTimeout, nodefault};
	__property TFtpFileType FileType = {read=FFileType, write=FFileType, nodefault};
	__property TApdFtpLog* FtpLog = {read=FFtpLog, write=SetFtpLog};
	__property AnsiString Password = {read=FPassword, write=FPassword};
	__property bool PassiveMode = {read=FPassiveMode, write=FPassiveMode, nodefault};
	__property AnsiString ServerAddress = {read=FWsAddress, write=SetWsAddress};
	__property int TransferTimeout = {read=FTransferTimeout, write=FTransferTimeout, nodefault};
	__property AnsiString UserName = {read=FUserName, write=FUserName};
	__property TFtpErrorEvent OnFtpError = {read=FOnFtpError, write=FOnFtpError};
	__property TFtpLogEvent OnFtpLog = {read=FOnFtpLog, write=FOnFtpLog};
	__property TFtpReplyEvent OnFtpReply = {read=FOnFtpReply, write=FOnFtpReply};
	__property TFtpStatusEvent OnFtpStatus = {read=FOnFtpStatus, write=FOnFtpStatus};
	
public:
	__property int BytesTransferred = {read=FBytesTransferred, nodefault};
	__property bool Connected = {read=GetConnected, nodefault};
	__property bool InProgress = {read=GetInProgress, nodefault};
	__property int FileLength = {read=FFileLength, nodefault};
	__property int ReplyCode = {read=FReplyCode, nodefault};
	__property int RestartAt = {read=FRestartAt, write=FRestartAt, nodefault};
	__property bool UserLoggedIn = {read=FUserLoggedIn, nodefault};
	__fastcall virtual TApdCustomFtpClient(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomFtpClient(void);
	bool __fastcall Abort(void);
	bool __fastcall ChangeDir(const AnsiString RemotePathName);
	bool __fastcall CurrentDir(void);
	bool __fastcall Delete(const AnsiString RemotePathName);
	bool __fastcall ListDir(const AnsiString RemotePathName, bool FullList);
	bool __fastcall Help(const AnsiString Command);
	bool __fastcall Login(void);
	bool __fastcall Logout(void);
	bool __fastcall MakeDir(const AnsiString RemotePathName);
	bool __fastcall RemoveDir(const AnsiString RemotePathName);
	bool __fastcall Rename(const AnsiString RemotePathName, const AnsiString NewPathName);
	bool __fastcall Retrieve(const AnsiString RemotePathName, const AnsiString LocalPathName, TFtpRetrieveMode RetrieveMode);
	bool __fastcall SendFtpCommand(const AnsiString FtpCmd);
	bool __fastcall Status(const AnsiString RemotePathName);
	bool __fastcall Store(const AnsiString RemotePathName, const AnsiString LocalPathName, TFtpStoreMode StoreMode);
};


class DELPHICLASS TApdFtpClient;
class PASCALIMPLEMENTATION TApdFtpClient : public TApdCustomFtpClient 
{
	typedef TApdCustomFtpClient inherited;
	
__published:
	__property Account ;
	__property ConnectTimeout ;
	__property FileType ;
	__property FtpLog ;
	__property Password ;
	__property PassiveMode ;
	__property ServerAddress ;
	__property TransferTimeout ;
	__property UserName ;
	__property OnFtpError ;
	__property OnFtpLog ;
	__property OnFtpReply ;
	__property OnFtpStatus ;
	__property Logging  = {default=0};
	__property LogSize  = {default=10000};
	__property LogName ;
	__property LogHex  = {default=1};
	__property Tracing  = {default=0};
	__property TraceSize  = {default=10000};
	__property TraceName ;
	__property TraceHex  = {default=1};
	__property WsPort ;
	__property OnWsError ;
public:
	#pragma option push -w-inl
	/* TApdCustomFtpClient.Create */ inline __fastcall virtual TApdFtpClient(Classes::TComponent* AOwner) : TApdCustomFtpClient(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomFtpClient.Destroy */ inline __fastcall virtual ~TApdFtpClient(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Word MaxBuffer = 0x8000;
static const Shortint MaxCmdStack = 0x20;

}	/* namespace Adftp */
using namespace Adftp;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdFtp
