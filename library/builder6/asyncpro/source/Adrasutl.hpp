// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdRasUtl.pas' rev: 6.00

#ifndef AdRasUtlHPP
#define AdRasUtlHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <OoMisc.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adrasutl
{
//-- type declarations -------------------------------------------------------
typedef unsigned *PHRasConn;

typedef unsigned HRasConn;

typedef unsigned TRasState;

typedef unsigned TRasError;

struct TRasDialParams;
typedef TRasDialParams *PRasDialParams;

#pragma pack(push, 4)
struct TRasDialParams
{
	unsigned dwSize;
	char szEntryName[257];
	char szPhoneNumber[129];
	char szCallbackNumber[129];
	char szUserName[257];
	char szPassword[257];
	char szDomain[16];
} ;
#pragma pack(pop)

struct TRasConn;
typedef TRasConn *PRasConn;

#pragma pack(push, 4)
struct TRasConn
{
	unsigned dwSize;
	unsigned rasConn;
	char szEntryName[257];
	char szDeviceType[17];
	char szDeviceName[129];
} ;
#pragma pack(pop)

typedef TRasConn TRasConnArray[65];

typedef TRasConn *PRasConnArray;

struct TRasConnStatus;
typedef TRasConnStatus *PRasConnStatus;

#pragma pack(push, 4)
struct TRasConnStatus
{
	unsigned dwSize;
	unsigned rasConnState;
	unsigned dwError;
	char szDeviceType[17];
	char szDeviceName[129];
} ;
#pragma pack(pop)

struct TRasEntryName;
typedef TRasEntryName *PRasEntryName;

#pragma pack(push, 4)
struct TRasEntryName
{
	int dwSize;
	char szEntryName[257];
} ;
#pragma pack(pop)

typedef TRasEntryName TRasEntryNameArray[65];

typedef TRasEntryName *PRasEntryNameArray;

struct TRasDialExtensions;
typedef TRasDialExtensions *PRasDialExtensions;

#pragma pack(push, 4)
struct TRasDialExtensions
{
	unsigned dwSize;
	unsigned dwfOptions;
	HWND hwndParent;
	unsigned reserved;
} ;
#pragma pack(pop)

struct TRasDeviceInfo;
typedef TRasDeviceInfo *PRasDeviceInfo;

#pragma pack(push, 4)
struct TRasDeviceInfo
{
	unsigned dwSize;
	char szDeviceType[17];
	char szDeviceName[129];
} ;
#pragma pack(pop)

struct TRasCountryInfo;
typedef TRasCountryInfo *PRasCountryInfo;

#pragma pack(push, 4)
struct TRasCountryInfo
{
	unsigned dwSize;
	unsigned dwCountryID;
	unsigned dwNextCountryID;
	unsigned dwCountryCode;
	unsigned dwCountryNameOffset;
} ;
#pragma pack(pop)

struct TRasDialDlgInfo;
typedef TRasDialDlgInfo *PRasDialDlgInfo;

#pragma pack(push, 4)
struct TRasDialDlgInfo
{
	unsigned dwSize;
	HWND hwndOwner;
	unsigned dwFlags;
	int xDlg;
	int yDlg;
	unsigned dwSubEntry;
	unsigned dwError;
	unsigned reserved;
	unsigned reserved2;
} ;
#pragma pack(pop)

struct TRasMonitorDlgInfo;
typedef TRasMonitorDlgInfo *PRasMonitorDlgInfo;

#pragma pack(push, 4)
struct TRasMonitorDlgInfo
{
	unsigned dwSize;
	HWND hwndOwner;
	unsigned dwFlags;
	unsigned dwStartPage;
	int xDlg;
	int yDlg;
	unsigned dwError;
	unsigned reserved;
	unsigned reserved2;
} ;
#pragma pack(pop)

struct TRasPhonebookDlgInfo;
typedef TRasPhonebookDlgInfo *PRasPhonebookDlgInfo;

#pragma pack(push, 4)
struct TRasPhonebookDlgInfo
{
	unsigned dwSize;
	HWND hwndOwner;
	unsigned dwFlags;
	int xDlg;
	int yDlg;
	unsigned dwCallbackId;
	void *pCallback;
	unsigned dwError;
	unsigned reserved;
	unsigned reserved2;
} ;
#pragma pack(pop)

typedef unsigned __stdcall (*TRasDial)(PRasDialExtensions lpDialExtensions, char * lszPhonebook, PRasDialParams lpDialParams, unsigned dwNotifierType, unsigned lpvNotifier, PHRasConn lpConn);

typedef BOOL __stdcall (*TRasDialDlg)(char * lpszPhonebook, char * lpszEntry, char * lpszPhoneNumber, PRasDialDlgInfo lpDialDlgInfo);

typedef BOOL __stdcall (*TRasMonitorDlg)(char * lpszDeviceName, PRasMonitorDlgInfo lpMonitorDlgInfo);

typedef BOOL __stdcall (*TRasPhonebookDlg)(char * lpszPhonebook, char * lpszEntry, PRasPhonebookDlgInfo lpPBDlgInfo);

typedef unsigned __stdcall (*TRasEnumConnections)(PRasConn lpConn, unsigned &lpBufSize, unsigned &lpNumConnections);

typedef unsigned __stdcall (*TRasEnumEntries)(char * lpReserved, char * lpszPhonebook, PRasEntryName lpEntryName, unsigned &lpEntryNameSize, unsigned &lpNumEntries);

typedef unsigned __stdcall (*TRasClearConnectionStatistics)(unsigned Conn);

typedef unsigned __stdcall (*TRasGetConnectionStatistics)(unsigned Conn, Oomisc::PRasStatistics lpStatistics);

typedef unsigned __stdcall (*TRasGetConnectStatus)(unsigned Conn, PRasConnStatus lpConnStatus);

typedef unsigned __stdcall (*TRasGetErrorString)(unsigned ErrorCode, char * lpszErrorString, unsigned BufSize);

typedef unsigned __stdcall (*TRasHangup)(unsigned RasConn);

typedef unsigned __stdcall (*TRasGetEntryDialParams)(char * lpszPhonebook, PRasDialParams lpDialParams, BOOL &Password);

typedef unsigned __stdcall (*TRasSetEntryDialParams)(char * lpszPhonebook, PRasDialParams lpDialParams, BOOL RemovePassword);

typedef unsigned __stdcall (*TRasCreatePhonebookEntry)(unsigned HWnd, char * lpszPhoneBook);

typedef unsigned __stdcall (*TRasEditPhonebookEntry)(unsigned HWnd, char * lpszPhonebook, char * lpszEntryName);

typedef unsigned __stdcall (*TRasDeleteEntry)(char * lpszPhonebook, char * lpszEntryName);

typedef unsigned __stdcall (*TRasRenameEntry)(char * lpszPhonebook, char * lpszEntryOld, char * lpszEntryNew);

typedef unsigned __stdcall (*TRasEnumDevices)(PRasDeviceInfo lpDeviceInfo, unsigned &lpDeviceInfoSize, unsigned &lpNumDevices);

typedef unsigned __stdcall (*TRasGetCountryInfo)(PRasCountryInfo lpCountryInfo, unsigned &lpCountryInfoSize);

typedef unsigned __stdcall (*TRasGetEntryProperties)(char * lpszPhonebook, char * lpszEntry, Oomisc::PRasEntry lpEntry, unsigned &lpEntrySize, Oomisc::PTapiConfigRec lpDeviceInfo, unsigned &lpDeviceInfoSize);

typedef unsigned __stdcall (*TRasSetEntryProperties)(char * lpszPhonebook, char * lpszEntry, Oomisc::PRasEntry lpEntryInfo, unsigned EntryInfoSize, Oomisc::PTapiConfigRec lpDeviceInfo, unsigned DeviceInfoSize);

typedef unsigned __stdcall (*TRasValidateEntryName)(char * lpszPhonebook, char * lpszEntry);

//-- var, const, procedure ---------------------------------------------------
#define RASDLL "RASAPI32"
#define RasDlgDLL "RASDLG"
#define AdRasDialEvent "RasDialEvent"
static const Word WM_RASDIALEVENT = 0xcccd;
static const Shortint ntNotifyDialFunc1 = 0x0;
static const Shortint ntNotifyDialFunc2 = 0x1;
extern PACKAGE unsigned ntNotifyWindow;
static const Shortint deUsePrefixSuffix = 0x1;
static const Shortint dePausedStates = 0x2;
static const Shortint deIgnoreModemSpeaker = 0x4;
static const Shortint deSetModemSpeaker = 0x8;
static const Shortint deIgnoreSoftwarecompression = 0x10;
static const Shortint deSetSoftwarecompression = 0x20;
static const Shortint deDisableConnectedUI = 0x40;
static const Byte deDisableReconnectUI = 0x80;
static const Word deDisableReconnect = 0x100;
static const Word deNoUser = 0x200;
static const Word dePauseOnScript = 0x400;
static const Word deRouter = 0x800;
static const Shortint ecRasOK = 0x0;
static const Shortint ecRasFunctionNotSupported = 0xffffffff;
static const Word ecRasRasBase = 0x258;
static const Word ecRasPending = 0x258;
static const Word ecRasInvalidPortHandle = 0x259;
static const Word ecRasPortAlreadyOpen = 0x25a;
static const Word ecRasBufferTooSmall = 0x25b;
static const Word ecRasWrongInfoSpecified = 0x25c;
static const Word ecRasCannotSetPortInfo = 0x25d;
static const Word ecRasPortNotConnected = 0x25e;
static const Word ecRasEventInvalid = 0x25f;
static const Word ecRasDeviceDoesNotExist = 0x260;
static const Word ecRasDeviceTypeDoesNotExist = 0x261;
static const Word ecRasInvalidBuffer = 0x262;
static const Word ecRasRouteNotAvailable = 0x263;
static const Word ecRasRouteNotAllocated = 0x264;
static const Word ecRasInvalidCompression = 0x265;
static const Word ecRasOutOfBuffers = 0x266;
static const Word ecRasPortNotFound = 0x267;
static const Word ecRasAsyncRequestPending = 0x268;
static const Word ecRasAlreadyDisconnecting = 0x269;
static const Word ecRasPortNotOpen = 0x26a;
static const Word ecRasPortDisconnected = 0x26b;
static const Word ecRasNoEndPoints = 0x26c;
static const Word ecRasCannotOpenPhonebook = 0x26d;
static const Word ecRasCannotLoadPhonebook = 0x26e;
static const Word ecRasCannotFindPhonebookEntry = 0x26f;
static const Word ecRasCannotWritePhonebook = 0x270;
static const Word ecRasCorruptPhonebook = 0x271;
static const Word ecRasCannotLoadString = 0x272;
static const Word ecRasKeyNotFound = 0x273;
static const Word ecRasDisconnection = 0x274;
static const Word ecRasRemoteDisconnection = 0x275;
static const Word ecRasHardwareFailure = 0x276;
static const Word ecRasUserDisconnection = 0x277;
static const Word ecRasInvalidSize = 0x278;
static const Word ecRasPortNotAvailable = 0x279;
static const Word ecRasCannotProjectClient = 0x27a;
static const Word ecRasUnknown = 0x27b;
static const Word ecRasWrongDeviceAttached = 0x27c;
static const Word ecRasBadString = 0x27d;
static const Word ecRasRequestTimeout = 0x27e;
static const Word ecRasCannotGetLana = 0x27f;
static const Word ecRasNetBiosError = 0x280;
static const Word ecRasServerOutOfResources = 0x281;
static const Word ecRasNameExistsOnNet = 0x282;
static const Word ecRasServerGeneralNetFailure = 0x283;
static const Word ecRasMsgAliasNotAdded = 0x284;
static const Word ecRasAuthInternal = 0x285;
static const Word ecRasRestrictedLogonHours = 0x286;
static const Word ecRasAcctDisabled = 0x287;
static const Word ecRasPasswordExpired = 0x288;
static const Word ecRasNoDialinPermission = 0x289;
static const Word ecRasServerNotResponding = 0x28a;
static const Word ecRasFromDevice = 0x28b;
static const Word ecRasUnrecognizedResponse = 0x28c;
static const Word ecRasMacroNotFound = 0x28d;
static const Word ecRasMacroNotDefined = 0x28e;
static const Word ecRasMessageMacroNotFound = 0x28f;
static const Word ecRasDefaultOffMacroNotFound = 0x290;
static const Word ecRasFilecouldNotBeOpened = 0x291;
static const Word ecRasDeviceNameTooLong = 0x292;
static const Word ecRasDevicenameNotFound = 0x293;
static const Word ecRasNoResponses = 0x294;
static const Word ecRasNoCommandFound = 0x295;
static const Word ecRasWrongKeySpecified = 0x296;
static const Word ecRasUnknownDeviceType = 0x297;
static const Word ecRasAllocatingMemory = 0x298;
static const Word ecRasPortNotConfigured = 0x299;
static const Word ecRasDeviceNotReady = 0x29a;
static const Word ecRasErrorReadingIniFile = 0x29b;
static const Word ecRasNoConnection = 0x29c;
static const Word ecRasBadUsageInIniFile = 0x29d;
static const Word ecRasReadingSectionName = 0x29e;
static const Word ecRasReadingDeviceType = 0x29f;
static const Word ecRasReadingDeviceName = 0x2a0;
static const Word ecRasReadingUsage = 0x2a1;
static const Word ecRasReadingMaxConnectBPS = 0x2a2;
static const Word ecRasReadingMaxCarrierBPS = 0x2a3;
static const Word ecRasLineBusy = 0x2a4;
static const Word ecRasVoiceAnswer = 0x2a5;
static const Word ecRasNoAnswer = 0x2a6;
static const Word ecRasNoCarrier = 0x2a7;
static const Word ecRasNoDialtone = 0x2a8;
static const Word ecRasInCommand = 0x2a9;
static const Word ecRasWritingSectionName = 0x2aa;
static const Word ecRasWritingDeviceType = 0x2ab;
static const Word ecRasWritingDeviceName = 0x2ac;
static const Word ecRasWritingMaxConnectBPS = 0x2ad;
static const Word ecRasWritingMaxCarrierBPS = 0x2ae;
static const Word ecRasWritingUsage = 0x2af;
static const Word ecRasWritingDefaultOff = 0x2b0;
static const Word ecRasReadingDefaultOff = 0x2b1;
static const Word ecRasEmptyIniFile = 0x2b2;
static const Word ecRasAuthenticationFailure = 0x2b3;
static const Word ecRasPortOrDevice = 0x2b4;
static const Word ecRasNotBinaryMacro = 0x2b5;
static const Word ecRasDCBNotFound = 0x2b6;
static const Word ecRasStateMachinesNotStarted = 0x2b7;
static const Word ecRasStateMachinesAlreadyStarted = 0x2b8;
static const Word ecRasPartialResponseLooping = 0x2b9;
static const Word ecRasUnknownResponseKey = 0x2ba;
static const Word ecRasRecvBufFull = 0x2bb;
static const Word ecRasCmdTooLong = 0x2bc;
static const Word ecRasUnsupportedBPS = 0x2bd;
static const Word ecRasUnexpectedResponse = 0x2be;
static const Word ecRasInteractiveMode = 0x2bf;
static const Word ecRasBadCallbackNumber = 0x2c0;
static const Word ecRasInvalidAuthState = 0x2c1;
static const Word ecRasWritingInitBPS = 0x2c2;
static const Word ecRasX25Diagnostic = 0x2c3;
static const Word ecRasAcctExpired = 0x2c4;
static const Word ecRasChangingPassword = 0x2c5;
static const Word ecRasOverrun = 0x2c6;
static const Word ecRasRasBaseManConnotInitialize = 0x2c7;
static const Word ecRasBiplexPortNotAvailable = 0x2c8;
static const Word ecRasNoActiveISDNLines = 0x2c9;
static const Word ecRasNoISDNChannelsAvailable = 0x2ca;
static const Word ecRasTooManyLineErrors = 0x2cb;
static const Word ecRasIPConfiguration = 0x2cc;
static const Word ecRasNoIPAddresses = 0x2cd;
static const Word ecRasPPPTimeout = 0x2ce;
static const Word ecRasPPPRemoteTerminated = 0x2cf;
static const Word ecRasPPPNoProtocolsConfigured = 0x2d0;
static const Word ecRasPPPNoResponse = 0x2d1;
static const Word ecRasPPPInvalidPacket = 0x2d2;
static const Word ecRasPhoneNumberTooLong = 0x2d3;
static const Word ecRasIPXCPNoDialOutConfigured = 0x2d4;
static const Word ecRasIPXCPNoDialInConfigured = 0x2d5;
static const Word ecRasIPXCPDialOutAlreadyActive = 0x2d6;
static const Word ecRasAccessingTCPCFGDLL = 0x2d7;
static const Word ecRasNOIPRasAdapter = 0x2d8;
static const Word ecRasSlipRequiresIP = 0x2d9;
static const Word ecRasProjectionNotComplete = 0x2da;
static const Word ecRasProtocolNotConfigured = 0x2db;
static const Word ecRasPPPNotConverging = 0x2dc;
static const Word ecRasPPPCPRejected = 0x2dd;
static const Word ecRasPPPLCPTerminated = 0x2de;
static const Word ecRasPPPRequiredAddressRejected = 0x2df;
static const Word ecRasPPPNCPTerminated = 0x2e0;
static const Word ecRasPPPLoopbackDetected = 0x2e1;
static const Word ecRasPPPNoAddressAssigned = 0x2e2;
static const Word ecRasCannotUseLogonCredentials = 0x2e3;
static const Word ecRasTapiConfiguration = 0x2e4;
static const Word ecRasNoLocalEncryption = 0x2e5;
static const Word ecRasNoRemoteEncryption = 0x2e6;
static const Word ecRasRemoteRequiresEncryption = 0x2e7;
static const Word ecRasIPXCPNetNumberConflict = 0x2e8;
static const Word ecRasInvalidSMM = 0x2e9;
static const Word ecRasSMMUninitialized = 0x2ea;
static const Word ecRasNoMACForPort = 0x2eb;
static const Word ecRasSMMTimeOut = 0x2ec;
static const Word ecRasBadPhoneNumber = 0x2ed;
static const Word ecRasWrongModule = 0x2ee;
static const Word ecRasInvalidCallBackNumber = 0x2ef;
static const Word ecRasScriptSyntax = 0x2f0;
static const Word ecRasHangupFailed = 0x2f1;
static const Word ecRasRasEnd = 0x2f1;
static const Shortint csRasBase = 0x0;
extern PACKAGE unsigned AdRasPlatformID;
extern PACKAGE void __fastcall LoadRASDLL(void);
extern PACKAGE int __fastcall AdRasDial(PRasDialExtensions PDialExtensions, const AnsiString Phonebook, PRasDialParams PDialParams, unsigned NotifierType, unsigned Notifier, unsigned &HConn);
extern PACKAGE int __fastcall AdRasDialDlg(const AnsiString Phonebook, const AnsiString EntryName, const AnsiString PhoneNumber, PRasDialDlgInfo PDialDlgInfo);
extern PACKAGE int __fastcall AdRasMonitorDlg(const AnsiString DeviceName, PRasMonitorDlgInfo PMonitorDlgInfo);
extern PACKAGE int __fastcall AdRasPhonebookDlg(const AnsiString Phonebook, const AnsiString EntryName, PRasPhonebookDlgInfo PPhonebookDlgInfo);
extern PACKAGE int __fastcall AdRasEnumConnections(PRasConn PConn, unsigned &ConnSize, unsigned &NumConnections);
extern PACKAGE int __fastcall AdRasEnumEntries(const AnsiString Phonebook, PRasEntryName PEntryName, unsigned &EntryNameSize, unsigned &NumEntries);
extern PACKAGE int __fastcall AdRasClearConnectionStatistics(unsigned HConn);
extern PACKAGE int __fastcall AdRasGetConnectionStatistics(unsigned HConn, Oomisc::PRasStatistics PStatistics);
extern PACKAGE int __fastcall AdRasGetConnectStatus(unsigned HConn, PRasConnStatus PConnStatus);
extern PACKAGE AnsiString __fastcall AdRasGetErrorString(int ErrorCode);
extern PACKAGE int __fastcall AdRasHangup(unsigned HConn);
extern PACKAGE int __fastcall AdRasGetEntryDialParams(const AnsiString Phonebook, PRasDialParams PDialParams, bool &GotPassword);
extern PACKAGE int __fastcall AdRasSetEntryDialParams(const AnsiString Phonebook, PRasDialParams PDialParams, bool RemovePassword);
extern PACKAGE int __fastcall AdRasCreatePhonebookEntry(unsigned HWnd, const AnsiString PhoneBook);
extern PACKAGE int __fastcall AdRasEditPhonebookEntry(unsigned HWnd, const AnsiString Phonebook, const AnsiString EntryName);
extern PACKAGE int __fastcall AdRasDeleteEntry(const AnsiString Phonebook, const AnsiString EntryName);
extern PACKAGE int __fastcall AdRasRenameEntry(const AnsiString Phonebook, const AnsiString EntryOld, const AnsiString EntryNew);
extern PACKAGE int __fastcall AdRasEnumDevices(PRasDeviceInfo PDeviceInfo, unsigned &DeviceInfoSize, unsigned &NumDevices);
extern PACKAGE int __fastcall AdRasGetCountryInfo(PRasCountryInfo PCountryInfo, unsigned &CountryInfoSize);
extern PACKAGE int __fastcall AdRasGetEntryProperties(const AnsiString Phonebook, const AnsiString EntryName, Oomisc::PRasEntry PEntry, unsigned &EntrySize, Oomisc::PTapiConfigRec PDeviceInfo, unsigned &DeviceInfoSize);
extern PACKAGE int __fastcall AdRasSetEntryProperties(const AnsiString Phonebook, const AnsiString EntryName, Oomisc::PRasEntry PEntry, unsigned &EntrySize, Oomisc::PTapiConfigRec PDeviceInfo, unsigned &DeviceInfoSize);
extern PACKAGE int __fastcall AdRasValidateEntryName(const AnsiString Phonebook, const AnsiString EntryName);

}	/* namespace Adrasutl */
using namespace Adrasutl;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdRasUtl
