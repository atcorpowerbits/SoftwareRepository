// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdTUtil.pas' rev: 6.00

#ifndef AdTUtilHPP
#define AdTUtilHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <OoMisc.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adtutil
{
//-- type declarations -------------------------------------------------------
struct TVarString;
typedef TVarString *PVarString;

#pragma pack(push, 4)
struct TVarString
{
	
	union
	{
		struct 
		{
			char StringData[1025];
			
		};
		struct 
		{
			unsigned TotalSize;
			unsigned NeededSize;
			unsigned UsedSize;
			unsigned StringFormat;
			unsigned StringSize;
			unsigned StringOffset;
			
		};
		
	};
} ;
#pragma pack(pop)

struct TLineExtensionID;
typedef TLineExtensionID *PLineExtensionID;

#pragma pack(push, 4)
struct TLineExtensionID
{
	unsigned ExtensionID0;
	unsigned ExtensionID1;
	unsigned ExtensionID2;
	unsigned ExtensionID3;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TLineCountryEntry
{
	int CountryID;
	int CountryCode;
	int NextCountryID;
	int CountryNameSize;
	int CountryNameOffset;
	int SameAreaRuleSize;
	int SameAreaRuleOffset;
	int LongDistanceRuleSize;
	int LongDistanceRuleOffset;
	int InternationalRuleSize;
	int InternationalRuleOffset;
} ;
#pragma pack(pop)

struct TLineCountryList;
typedef TLineCountryList *PLineCountryList;

#pragma pack(push, 4)
struct TLineCountryList
{
	int TotalSize;
	int NeededSize;
	int UsedSize;
	int NumCountries;
	int CountryListSize;
	int CountryListOffset;
	union
	{
		struct 
		{
			Byte BufferBytes[44001];
			
		};
		struct 
		{
			TLineCountryEntry Buffer[1001];
			
		};
		
	};
} ;
#pragma pack(pop)

struct TLineDialParams;
typedef TLineDialParams *PLineDialParams;

#pragma pack(push, 4)
struct TLineDialParams
{
	unsigned DialPause;
	unsigned DialSpeed;
	unsigned DigitDuration;
	unsigned WaitForDialtone;
} ;
#pragma pack(pop)

struct TLineDevCaps;
typedef TLineDevCaps *PLineDevCaps;

#pragma pack(push, 4)
struct TLineDevCaps
{
	
	union
	{
		struct 
		{
			char Data[65521];
			
		};
		struct 
		{
			unsigned TotalSize;
			unsigned NeededSize;
			unsigned UsedSize;
			unsigned ProviderInfoSize;
			unsigned ProviderInfoOffset;
			unsigned SwitchInfoSize;
			unsigned SwitchInfoOffset;
			unsigned PermanentLineID;
			unsigned LineNameSize;
			unsigned LineNameOffset;
			unsigned StringFormat;
			unsigned AddressModes;
			unsigned NumAddresses;
			unsigned BearerModes;
			unsigned MaxRate;
			unsigned MediaModes;
			unsigned GenerateToneModes;
			unsigned GenerateToneMaxNumFreq;
			unsigned GenerateDigitModes;
			unsigned MonitorToneMaxNumFreq;
			unsigned MonitorToneMaxNumEntries;
			unsigned MonitorDigitModes;
			unsigned GatherDigitsMinTimeout;
			unsigned GatherDigitsMaxTimeout;
			unsigned MedCtlDigitMaxListSize;
			unsigned MedCtlMediaMaxListSize;
			unsigned MedCtlToneMaxListSize;
			unsigned MedCtlCallStateMaxListSize;
			unsigned DevCapFlags;
			unsigned MaxNumActiveCalls;
			unsigned AnswerMode;
			unsigned RingModes;
			unsigned LineStates;
			unsigned UUIAcceptSize;
			unsigned UUIAnswerSize;
			unsigned UUIMakeCallSize;
			unsigned UUIdropSize;
			unsigned UUISendUserUserInfoSize;
			unsigned UUICallInfoSize;
			TLineDialParams MinDialParams;
			TLineDialParams MaxDialParams;
			TLineDialParams DefaultDialParams;
			unsigned NumTerminals;
			unsigned TerminalCapsSize;
			unsigned TerminalCapsOffset;
			unsigned TerminalTextEntrySize;
			unsigned TerminalTextSize;
			unsigned TerminalTextOffset;
			unsigned DevSpecificSize;
			unsigned DevSpecificOffset;
			unsigned LineFeatures;
			int EndMark;
			
		};
		
	};
} ;
#pragma pack(pop)

struct TLineAddressCaps;
typedef TLineAddressCaps *PLineAddressCaps;

#pragma pack(push, 4)
struct TLineAddressCaps
{
	
	union
	{
		struct 
		{
			char Data[65521];
			
		};
		struct 
		{
			unsigned TotalSize;
			unsigned NeededSize;
			unsigned UsedSize;
			unsigned LineDeviceID;
			unsigned AddressSize;
			unsigned AddressOffset;
			unsigned DevSpecificSize;
			unsigned DevSpecificOffset;
			unsigned AddressSharing;
			unsigned AddressStates;
			unsigned CallInfoStates;
			unsigned CallerIDFlags;
			unsigned CalledIDFlags;
			unsigned ConnectedIDFlags;
			unsigned RedirectionIDFlags;
			unsigned RedirectingIDFlags;
			unsigned CallStates;
			unsigned DialToneModes;
			unsigned BusyModes;
			unsigned SpecialInfo;
			unsigned DisconnectModes;
			unsigned MaxNumActiveCalls;
			unsigned MaxNumOnHoldCalls;
			unsigned MaxNumOnHoldPendingCalls;
			unsigned MaxNumConference;
			unsigned MaxNumTransConf;
			unsigned AddrCapFlags;
			unsigned CallFeatures;
			unsigned RemoveFromConfCaps;
			unsigned RemoveFromConfState;
			unsigned TransferModes;
			unsigned ParkModes;
			unsigned ForwardModes;
			unsigned MaxForwardEntries;
			unsigned MaxSpecificEntries;
			unsigned MinFwdNumRings;
			unsigned MaxFwdNumRings;
			unsigned MaxCallCompletions;
			unsigned CallCompletionConds;
			unsigned CallCompletionModes;
			unsigned NumCompletionMessages;
			unsigned CompletionMsgTextEntrySize;
			unsigned CompletionMsgTextSize;
			unsigned CompletionMsgTextOffset;
			unsigned AddressFeatures;
			unsigned PredictiveAutoTransferStates;
			unsigned NumCallTreatments;
			unsigned CallTreatmentListSize;
			unsigned CallTreatmentListOffset;
			unsigned DeviceClassesSize;
			unsigned DeviceClassesOffset;
			unsigned MaxCallDataSize;
			unsigned CallFeatures2;
			unsigned MaxNoAnswerTimeout;
			unsigned ConnectedModes;
			unsigned OfferingModes;
			unsigned AvailableMediaModes;
			int EndMark;
			
		};
		
	};
} ;
#pragma pack(pop)

struct TLineCallParams;
typedef TLineCallParams *PLineCallParams;

#pragma pack(push, 4)
struct TLineCallParams
{
	unsigned TotalSize;
	unsigned BearerMode;
	unsigned MinRate;
	unsigned MaxRate;
	unsigned MediaMode;
	unsigned CallParamFlags;
	unsigned AddressMode;
	unsigned AddressID;
	TLineDialParams DialParams;
	unsigned OrigAddressSize;
	unsigned OrigAddressOffset;
	unsigned DisplayableAddressSize;
	unsigned DisplayableAddressOffset;
	unsigned CalledPartySize;
	unsigned CalledPartyOffset;
	unsigned CommentSize;
	unsigned CommentOffset;
	unsigned UserUserInfoSize;
	unsigned UserUserInfoOffset;
	unsigned HighLevelCompSize;
	unsigned HighLevelCompOffset;
	unsigned LowLevelCompSize;
	unsigned LowLevelCompOffset;
	unsigned DevSpecificSize;
	unsigned DevSpecificOffset;
} ;
#pragma pack(pop)

struct TLineAddressStatus;
typedef TLineAddressStatus *PLineAddressStatus;

#pragma pack(push, 4)
struct TLineAddressStatus
{
	unsigned TotalSize;
	unsigned NeededSize;
	unsigned UsedSize;
	unsigned NumInUse;
	unsigned NumActiveCalls;
	unsigned NumOnHoldCalls;
	unsigned NumOnHoldPendCalls;
	unsigned AddressFeatures;
	unsigned NumRingsNoAnswer;
	unsigned ForwardNumEntries;
	unsigned ForwardSize;
	unsigned ForwardOffset;
	unsigned TerminalModesSize;
	unsigned TerminalModesOffset;
	unsigned DevSpecificSize;
	unsigned DevSpecificOffset;
} ;
#pragma pack(pop)

struct TLineDevStatus;
typedef TLineDevStatus *PLineDevStatus;

#pragma pack(push, 4)
struct TLineDevStatus
{
	
	union
	{
		struct 
		{
			Byte Data[65521];
			
		};
		struct 
		{
			unsigned TotalSize;
			unsigned NeededSize;
			unsigned UsedSize;
			unsigned NumOpens;
			unsigned OpenMediaModes;
			unsigned NumActiveCalls;
			unsigned NumOnHoldCalls;
			unsigned NumOnHoldPendCalls;
			unsigned LineFeatures;
			unsigned NumCallCompletions;
			unsigned RingMode;
			unsigned SignalLevel;
			unsigned BatteryLevel;
			unsigned RoamMode;
			unsigned DevStatusFlags;
			unsigned TerminalModesSize;
			unsigned TerminalModesOffset;
			unsigned DevSpecificSize;
			unsigned DevSpecificOffset;
			unsigned AvailableMediaModes;
			unsigned AppInfoSize;
			unsigned AppInfoOffset;
			unsigned EndMark;
			
		};
		
	};
} ;
#pragma pack(pop)

typedef int TLineApp;

typedef int *PLineApp;

typedef int TLine;

typedef int *PLine;

typedef int TCall;

typedef int *PCall;

struct TCallInfo;
typedef TCallInfo *PCallInfo;

#pragma pack(push, 4)
struct TCallInfo
{
	
	union
	{
		struct 
		{
			Byte Data[65521];
			
		};
		struct 
		{
			unsigned TotalSize;
			unsigned NeededSize;
			unsigned UsedSize;
			int Line;
			unsigned LineDeviceID;
			unsigned AddressID;
			unsigned BearerMode;
			unsigned Rate;
			unsigned MediaMode;
			unsigned AppSpecific;
			unsigned CallID;
			unsigned RelatedCallID;
			unsigned CallParamFlags;
			unsigned CallStates;
			unsigned MonitorDigitModes;
			unsigned MonitorMediaModes;
			TLineDialParams DialParams;
			unsigned Origin;
			unsigned Reason;
			unsigned CompletionID;
			unsigned NumOwners;
			unsigned NumMonitors;
			unsigned CountryCode;
			unsigned Trunk;
			unsigned CallerIDFlags;
			unsigned CallerIDSize;
			unsigned CallerIDOffset;
			unsigned CallerIDNameSize;
			unsigned CallerIDNameOffset;
			unsigned CalledIDFlags;
			unsigned CalledIDSize;
			unsigned CalledIDOffset;
			unsigned CalledIDNameSize;
			unsigned CalledIDNameOffset;
			unsigned ConnectedIDdFlags;
			unsigned ConnectedIDSize;
			unsigned ConnectedIDOffset;
			unsigned ConnectedIDNameSize;
			unsigned ConnectedIDNameOffset;
			unsigned RedirectionIDFlags;
			unsigned RedirectionIDSize;
			unsigned RedirectionIDOffset;
			unsigned RedirectionIDNameSize;
			unsigned RedirectionIDNameOffset;
			unsigned RedirectingIDFlags;
			unsigned RedirectingIDSize;
			unsigned RedirectingIDOffset;
			unsigned RedirectingIDNameSize;
			unsigned RedirectingIDNameOffset;
			unsigned AppNameSize;
			unsigned AppNameOffset;
			unsigned DisplayableAddressSize;
			unsigned DisplayableAddressOffset;
			unsigned CalledPartySize;
			unsigned CalledPartyOffset;
			unsigned CommentSize;
			unsigned CommentOffset;
			unsigned DisplaySize;
			unsigned DisplayOffset;
			unsigned UserUserInfoSize;
			unsigned UserUserInfoOffset;
			unsigned HighLevelCompSize;
			unsigned HighLevelCompOffset;
			unsigned LowLevelCompSize;
			unsigned LowLevelCompOffset;
			unsigned ChargingInfoSize;
			unsigned ChargingInfoOffset;
			unsigned TerminalModesSize;
			unsigned TerminalModesOffset;
			unsigned DevSpecificSize;
			unsigned DevSpecificOffset;
			int EndMark;
			
		};
		
	};
} ;
#pragma pack(pop)

struct TCallStatus;
typedef TCallStatus *PCallStatus;

#pragma pack(push, 4)
struct TCallStatus
{
	
	union
	{
		struct 
		{
			Byte Data[65521];
			
		};
		struct 
		{
			unsigned TotalSize;
			unsigned NeededSize;
			unsigned UsedSize;
			unsigned CallState;
			unsigned CallStateMode;
			unsigned CallPrivilege;
			unsigned CallFeatures;
			unsigned DevSpecificSize;
			unsigned DevSpecificOffset;
			unsigned EndMark;
			
		};
		
	};
} ;
#pragma pack(pop)

struct TLineTranslateOutput;
typedef TLineTranslateOutput *PLineTranslateOutput;

#pragma pack(push, 4)
struct TLineTranslateOutput
{
	
	union
	{
		struct 
		{
			Byte Data[65521];
			
		};
		struct 
		{
			unsigned TotalSize;
			unsigned NeededSize;
			unsigned UsedSize;
			unsigned DialableStringSize;
			unsigned DialableStringOffset;
			unsigned DisplayableStringSize;
			unsigned DisplayableStringOffset;
			unsigned CurrentCountry;
			unsigned DestCountry;
			unsigned TranslateResults;
			unsigned EndMark;
			
		};
		
	};
} ;
#pragma pack(pop)

struct TLineTranslateCaps;
typedef TLineTranslateCaps *PLineTranslateCaps;

#pragma pack(push, 4)
struct TLineTranslateCaps
{
	
	union
	{
		struct 
		{
			Byte Data[65521];
			
		};
		struct 
		{
			unsigned TotalSize;
			unsigned NeededSize;
			unsigned UsedSize;
			unsigned NumLocations;
			unsigned LocationListSize;
			unsigned LocationListOffset;
			unsigned CurrentLocationID;
			unsigned NumCards;
			unsigned CardListSize;
			unsigned CardListOffset;
			unsigned CurrentPreferredCardID;
			unsigned EndMark;
			
		};
		
	};
} ;
#pragma pack(pop)

struct TLineMonitorTone;
typedef TLineMonitorTone *PLineMonitorTone;

#pragma pack(push, 4)
struct TLineMonitorTone
{
	unsigned AppSpecific;
	unsigned Duration;
	unsigned Frequency1;
	unsigned Frequency2;
	unsigned Frequency3;
} ;
#pragma pack(pop)

struct TLineGenerateTone;
typedef TLineGenerateTone *PLineGenerateTone;

#pragma pack(push, 4)
struct TLineGenerateTone
{
	unsigned Frequency;
	unsigned CadenceOn;
	unsigned CadenceOff;
	unsigned Volume;
} ;
#pragma pack(pop)

typedef void __stdcall (*TLineCallback)(int Device, int Message, int Instance, int Param1, int Param2, int Param3);

typedef int __stdcall (*TLineInitialize)(int &LineApp, unsigned Instance, TLineCallback Callback, char * AppName, unsigned &NumDevs);

typedef int __stdcall (*TLineShutdown)(int LineApp);

typedef int __stdcall (*TLineNegotiateApiVersion)(int LineApp, int DeviceID, int APILowVersion, int APIHighVersion, int &ApiVersion, TLineExtensionID &LE);

typedef int __stdcall (*TLineGetDevCaps)(int LineApp, unsigned DeviceID, unsigned ApiVersion, unsigned ExtVersion, PLineDevCaps LineDevCaps);

typedef int __stdcall (*TLineOpen)(int LineApp, unsigned DeviceID, int &Line, unsigned ApiVersion, unsigned ExtVersion, unsigned CallbackInstance, unsigned Privleges, unsigned MediaModes, unsigned CallParams);

typedef int __stdcall (*TLineMakeCall)(int Line, int &Call, char * DestAddress, unsigned CountryCode, const PLineCallParams CallParams);

typedef int __stdcall (*TLineAccept)(int Call, char * UserUserInfo, unsigned Size);

typedef int __stdcall (*TLineAnswer)(int Call, char * UserUserInfo, unsigned Size);

typedef int __stdcall (*TLineDeallocateCall)(int Call);

typedef int __stdcall (*TLineDrop)(int Call, char * UserInfo, unsigned Size);

typedef int __stdcall (*TLineClose)(int Line);

typedef int __stdcall (*TLineGetCountry)(int CountryID, int ApiVersion, PLineCountryList LineCountryList);

typedef int __stdcall (*TLineConfigDialog)(unsigned DeviceID, HWND Owner, char * DeviceClass);

typedef int __stdcall (*TLineConfigDialogEdit)(unsigned DeviceID, HWND Owner, char * DeviceClass, const void *inDevConfig, unsigned Size, TVarString &DevConfig);

typedef int __stdcall (*TLineGetID)(int Line, unsigned AddressID, int Call, unsigned Select, TVarString &DeviceID, char * DeviceClass);

typedef int __stdcall (*TLineSetStatusMessages)(int Line, unsigned LineStates, unsigned AddressStates);

typedef int __stdcall (*TLineGetStatusMessages)(int Line, unsigned &LineStates, unsigned &AddressStates);

typedef int __stdcall (*TLineGetAddressCaps)(int LineApp, unsigned DeviceID, unsigned AddressId, unsigned ApiVersion, unsigned ExtVersion, PLineAddressCaps LineAddressCaps);

typedef int __stdcall (*TLineGetAddressStatus)(int Line, unsigned AddressID, TLineAddressStatus &AddressStatus);

typedef int __stdcall (*TLineGetLineDevStatus)(int Line, TLineDevStatus &DevStatus);

typedef int __stdcall (*TLineGetDevConfig)(unsigned DeviceID, TVarString &DeviceConfig, char * DeviceClass);

typedef int __stdcall (*TLineSetDevConfig)(unsigned DeviceID, const void *DeviceConfig, unsigned Size, char * DeviceClass);

typedef int __stdcall (*TLineGetCallInfo)(int Call, PCallInfo CallInfo);

typedef int __stdcall (*TLineGetCallStatus)(int Call, PCallStatus CallStatus);

typedef int __stdcall (*TLineSetMediaMode)(int Call, unsigned MediaModes);

typedef int __stdcall (*TLineMonitorDigits)(int Call, unsigned DigitModes);

typedef int __stdcall (*TLineGenerateDigits)(int Call, unsigned DigitModes, char * Digits, unsigned Duration);

typedef int __stdcall (*TLineMonitorMedia)(int Call, unsigned MediaModes);

typedef int __stdcall (*TLineHandoff)(int Call, char * FileName, unsigned MediaMode);

typedef int __stdcall (*TLineSetCallParams)(int Call, unsigned BearerMode, unsigned MinRate, unsigned MaxRate, PLineDialParams DialParams);

typedef int __stdcall (*TLineTranslateAddress)(int Line, unsigned DeviceID, unsigned APIVersion, char * AddressIn, unsigned Card, unsigned TranslateOptions, PLineTranslateOutput TranslateOutput);

typedef int __stdcall (*TLineTranslateDialog)(int Line, unsigned DeviceID, unsigned APIVersion, HWND HwndOwner, char * AddressIn);

typedef int __stdcall (*TLineSetCurrentLocation)(int Line, unsigned Location);

typedef int __stdcall (*TLineSetTollList)(int Line, unsigned DeviceID, char * AddressIn, unsigned TollListOption);

typedef int __stdcall (*TLineGetTranslateCaps)(int Line, unsigned APIVersion, PLineTranslateCaps TranslateCaps);

typedef int __stdcall (*TLineMonitorTones)(int Call, const void *LINEMONITORTONE, unsigned NumEntries);

typedef int __stdcall (*TLineGenerateTones)(int Call, unsigned ToneMode, unsigned Duration, unsigned NumTones, const void *LINEGENERATETONE);

typedef int __stdcall (*TLineHold)(int Call);

typedef int __stdcall (*TLineUnhold)(int Call);

typedef int __stdcall (*TLineTransfer)(int Call, char * DestAddress, unsigned CountryCode);

//-- var, const, procedure ---------------------------------------------------
static const Word MaxCountries = 0x3e8;
static const int TapiLowVer = 0x10004;
static const int TapiHighVer = 0x10004;
static const Word Wom_Open = 0x3bb;
static const Word Wom_Close = 0x3bc;
static const Word Wom_Done = 0x3bd;
static const Shortint Line_AddressState = 0x0;
static const Shortint Line_CallInfo = 0x1;
static const Shortint Line_CallState = 0x2;
static const Shortint Line_Close = 0x3;
static const Shortint Line_DevSpecific = 0x4;
static const Shortint Line_DevSpecificFeature = 0x5;
static const Shortint Line_GatherDigits = 0x6;
static const Shortint Line_Generate = 0x7;
static const Shortint Line_LineDevState = 0x8;
static const Shortint Line_MonitorDigits = 0x9;
static const Shortint Line_MonitorMedia = 0xa;
static const Shortint Line_MonitorTone = 0xb;
static const Shortint Line_Reply = 0xc;
static const Shortint Line_Request = 0xd;
static const Shortint Phone_Button = 0xe;
static const Shortint Phone_Close = 0xf;
static const Shortint Phone_DevSpecific = 0x10;
static const Shortint Phone_Reply = 0x11;
static const Shortint Phone_State = 0x12;
static const Shortint Line_Create = 0x13;
static const Shortint Phone_Create = 0x14;
static const Shortint Line_AgentSpecific = 0x15;
static const Shortint Line_AgentStatus = 0x16;
static const Shortint Line_AppNewCall = 0x17;
static const Shortint Line_ProxyRequest = 0x18;
static const Shortint Line_Remove = 0x19;
static const Shortint Phone_Remove = 0x1a;
static const Shortint Line_APDSpecific = 0x20;
static const Shortint LineAddrCapFlags_FwdNumRings = 0x1;
static const Shortint LineAddrCapFlags_PickupGroupID = 0x2;
static const Shortint LineAddrCapFlags_Secure = 0x4;
static const Shortint LineAddrCapFlags_BlockIDDefault = 0x8;
static const Shortint LineAddrCapFlags_BlockIDOverride = 0x10;
static const Shortint LineAddrCapFlags_Dialed = 0x20;
static const Shortint LineAddrCapFlags_OrigOffHook = 0x40;
static const Byte LineAddrCapFlags_DestOffHook = 0x80;
static const Word LineAddrCapFlags_FwdConsult = 0x100;
static const Word LineAddrCapFlags_SetupConfNull = 0x200;
static const Word LineAddrCapFlags_AutoReconnect = 0x400;
static const Word LineAddrCapFlags_CompletionID = 0x800;
static const Word LineAddrCapFlags_TransferHeld = 0x1000;
static const Word LineAddrCapFlags_TransferMake = 0x2000;
static const Word LineAddrCapFlags_ConferenceHeld = 0x4000;
static const Word LineAddrCapFlags_ConferenceMake = 0x8000;
static const int LineAddrCapFlags_PartialDial = 0x10000;
static const int LineAddrCapFlags_FwdStatusValid = 0x20000;
static const int LineAddrCapFlags_FwdIntextAddr = 0x40000;
static const int LineAddrCapFlags_FwdBusyNaAddr = 0x80000;
static const int LineAddrCapFlags_AcceptToAlert = 0x100000;
static const int LineAddrCapFlags_ConfDrop = 0x200000;
static const int LineAddrCapFlags_PickupCallWait = 0x400000;
static const int LineAddrCapFlags_PredictiveDialer = 0x800000;
static const int LineAddrCapFlags_Queue = 0x1000000;
static const int LineAddrCapFlags_RoutePoint = 0x2000000;
static const int LineAddrCapFlags_HoldMakesNew = 0x4000000;
static const int LineAddrCapFlags_NoInternalCalls = 0x8000000;
static const int LineAddrCapFlags_NoExternalCalls = 0x10000000;
static const int LineAddrCapFlags_SetCallingID = 0x20000000;
static const Shortint LineAddressMode_AddressID = 0x1;
static const Shortint LineAddressMode_DialableAddr = 0x2;
static const Shortint LineAddressSharing_Private = 0x1;
static const Shortint LineAddressSharing_BridgedExcl = 0x2;
static const Shortint LineAddressSharing_BridgedNew = 0x4;
static const Shortint LineAddressSharing_BridgedShared = 0x8;
static const Shortint LineAddressSharing_Monitored = 0x10;
static const Shortint LineAddressState_Other = 0x1;
static const Shortint LineAddressState_DevSpecific = 0x2;
static const Shortint LineAddressState_InUseZero = 0x4;
static const Shortint LineAddressState_InUseOne = 0x8;
static const Shortint LineAddressState_InUseMany = 0x10;
static const Shortint LineAddressState_NumCalls = 0x20;
static const Shortint LineAddressState_Forward = 0x40;
static const Byte LineAddressState_Terminals = 0x80;
static const Word LineAddressState_CapsChange = 0x100;
static const Word AllAddressStates = 0x1ff;
static const Shortint LineAddrFeature_Forward = 0x1;
static const Shortint LineAddrFeature_MakeCall = 0x2;
static const Shortint LineAddrFeature_Pickup = 0x4;
static const Shortint LineAddrFeature_SetMediaControl = 0x8;
static const Shortint LineAddrFeature_SetTerminal = 0x10;
static const Shortint LineAddrFeature_SetupConf = 0x20;
static const Shortint LineAddrFeature_UncompleteCall = 0x40;
static const Byte LineAddrFeature_Unpark = 0x80;
static const Word LineAddrFeature_PickupHeld = 0x100;
static const Word LineAddrFeature_PickupGroup = 0x200;
static const Word LineAddrFeature_PickupDirect = 0x400;
static const Word LineAddrFeature_PickupWaiting = 0x800;
static const Word LineAddrFeature_ForwardFwd = 0x1000;
static const Word LineAddrFeature_ForwardDnd = 0x2000;
static const Shortint LineAgentFeature_SetAgentGroup = 0x1;
static const Shortint LineAgentFeature_SetAgentState = 0x2;
static const Shortint LineAgentFeature_SetAgentActivity = 0x4;
static const Shortint LineAgentFeature_AgentSpecific = 0x8;
static const Shortint LineAgentFeature_GetAgentActivityList = 0x10;
static const Shortint LineAgentFeature_GetAgentGroup = 0x20;
static const Shortint LineAgentState_LoggedOff = 0x1;
static const Shortint LineAgentState_NotReady = 0x2;
static const Shortint LineAgentState_Ready = 0x4;
static const Shortint LineAgentState_BusyAcd = 0x8;
static const Shortint LineAgentState_BusyIncoming = 0x10;
static const Shortint LineAgentState_BusyOutbound = 0x20;
static const Shortint LineAgentState_BusyOther = 0x40;
static const Byte LineAgentState_WorkingAfterCall = 0x80;
static const Word LineAgentState_Unknown = 0x100;
static const Word LineAgentState_Unavail = 0x200;
static const Shortint LineAgentStatus_Group = 0x1;
static const Shortint LineAgentStatus_State = 0x2;
static const Shortint LineAgentStatus_NextState = 0x4;
static const Shortint LineAgentStatus_Activity = 0x8;
static const Shortint LineAgentStatus_ActivityList = 0x10;
static const Shortint LineAgentStatus_GroupList = 0x20;
static const Shortint LineAgentStatus_CapsChange = 0x40;
static const Byte LineAgentStatus_ValidStates = 0x80;
static const Word LineAgentStatus_ValidNextStates = 0x100;
static const Shortint LineAnswerMode_None = 0x1;
static const Shortint LineAnswerMode_Drop = 0x2;
static const Shortint LineAnswerMode_Hold = 0x4;
static const Shortint LineBearerMode_Voice = 0x1;
static const Shortint LineBearerMode_Speech = 0x2;
static const Shortint LineBearerMode_MultiUse = 0x4;
static const Shortint LineBearerMode_Data = 0x8;
static const Shortint LineBearerMode_AltSpeechData = 0x10;
static const Shortint LineBearerMode_NonCallSignaling = 0x20;
static const Shortint LineBearerMode_PassThrough = 0x40;
static const Byte LineBearerMode_RestrictedData = 0x80;
static const Shortint LineBusyMode_Station = 0x1;
static const Shortint LineBusyMode_Trunk = 0x2;
static const Shortint LineBusyMode_Unknown = 0x4;
static const Shortint LineBusyMode_Unavail = 0x8;
static const Shortint LineCallComplCond_Busy = 0x1;
static const Shortint LineCallComplCond_NoAnswer = 0x2;
static const Shortint LineCallComplMode_CampOn = 0x1;
static const Shortint LineCallComplMode_CallBack = 0x2;
static const Shortint LineCallComplMode_Intrude = 0x4;
static const Shortint LineCallComplMode_Message = 0x8;
static const Shortint LineCallFeature_Accept = 0x1;
static const Shortint LineCallFeature_AddToConf = 0x2;
static const Shortint LineCallFeature_Answer = 0x4;
static const Shortint LineCallFeature_BlindTransfer = 0x8;
static const Shortint LineCallFeature_CompleteCall = 0x10;
static const Shortint LineCallFeature_CompleteTransf = 0x20;
static const Shortint LineCallFeature_Dial = 0x40;
static const Byte LineCallFeature_Drop = 0x80;
static const Word LineCallFeature_GatherDigits = 0x100;
static const Word LineCallFeature_GenerateDigits = 0x200;
static const Word LineCallFeature_GenerateTone = 0x400;
static const Word LineCallFeature_Hold = 0x800;
static const Word LineCallFeature_MonitorDigits = 0x1000;
static const Word LineCallFeature_MonitorMedia = 0x2000;
static const Word LineCallFeature_MonitorTones = 0x4000;
static const Word LineCallFeature_Park = 0x8000;
static const int LineCallFeature_PrepareAddConf = 0x10000;
static const int LineCallFeature_ReDirect = 0x20000;
static const int LineCallFeature_RemoveFromConf = 0x40000;
static const int LineCallFeature_SecureCall = 0x80000;
static const int LineCallFeature_SendUserUser = 0x100000;
static const int LineCallFeature_SetCallparams = 0x200000;
static const int LineCallFeature_SetMediaControl = 0x400000;
static const int LineCallFeature_SetTerminal = 0x800000;
static const int LineCallFeature_SetupConf = 0x1000000;
static const int LineCallFeature_SetupTransfer = 0x2000000;
static const int LineCallFeature_SwapHold = 0x4000000;
static const int LineCallFeature_UnHold = 0x8000000;
static const int LineCallFeature_ReleaseUserUserInfo = 0x10000000;
static const int LineCallFeature_SetTreatment = 0x20000000;
static const int LineCallFeature_SetQos = 0x40000000;
static const unsigned LineCallFeature_SetCallData = 0x80000000;
static const Shortint LineCallFeature2_NoHoldConference = 0x1;
static const Shortint LineCallFeature2_OneStepTransfer = 0x2;
static const Shortint LineCallFeature2_ComplCampOn = 0x4;
static const Shortint LineCallFeature2_ComplCallback = 0x8;
static const Shortint LineCallFeature2_ComplIntrude = 0x10;
static const Shortint LineCallFeature2_ComplMessage = 0x20;
static const Shortint LineCallFeature2_TransferNorm = 0x40;
static const Byte LineCallFeature2_TransferConf = 0x80;
static const Word LineCallFeature2_ParkDirect = 0x100;
static const Word LineCallFeature2_ParkNonDirect = 0x200;
static const Shortint LineCallInfoState_Other = 0x1;
static const Shortint LineCallInfoState_DevSpecific = 0x2;
static const Shortint LineCallInfoState_BearerMode = 0x4;
static const Shortint LineCallInfoState_Rate = 0x8;
static const Shortint LineCallInfoState_MediaMode = 0x10;
static const Shortint LineCallInfoState_AppSpecific = 0x20;
static const Shortint LineCallInfoState_CallID = 0x40;
static const Byte LineCallInfoState_RelatedCallID = 0x80;
static const Word LineCallInfoState_Origin = 0x100;
static const Word LineCallInfoState_Reason = 0x200;
static const Word LineCallInfoState_CompletionID = 0x400;
static const Word LineCallInfoState_NumOwnerIncr = 0x800;
static const Word LineCallInfoState_NumOwnerDecr = 0x1000;
static const Word LineCallInfoState_NumMonitors = 0x2000;
static const Word LineCallInfoState_Trunk = 0x4000;
static const Word LineCallInfoState_CallerID = 0x8000;
static const int LineCallInfoState_CalledID = 0x10000;
static const int LineCallInfoState_ConnectedID = 0x20000;
static const int LineCallInfoState_RedirectionID = 0x40000;
static const int LineCallInfoState_RedirectingID = 0x80000;
static const int LineCallInfoState_Display = 0x100000;
static const int LineCallInfoState_UserUserInfo = 0x200000;
static const int LineCallInfoState_HighLevelComp = 0x400000;
static const int LineCallInfoState_LowLevelComp = 0x800000;
static const int LineCallInfoState_ChargingInfo = 0x1000000;
static const int LineCallInfoState_Terminal = 0x2000000;
static const int LineCallInfoState_DialParams = 0x4000000;
static const int LineCallInfoState_MonitorModes = 0x8000000;
static const int LineCallInfoState_Treatment = 0x10000000;
static const int LineCallInfoState_Qos = 0x20000000;
static const int LineCallInfoState_CallData = 0x40000000;
static const Shortint LineCallOrigin_Outbound = 0x1;
static const Shortint LineCallOrigin_Internal = 0x2;
static const Shortint LineCallOrigin_External = 0x4;
static const Shortint LineCallOrigin_Unknown = 0x10;
static const Shortint LineCallOrigin_Unavail = 0x20;
static const Shortint LineCallOrigin_Conference = 0x40;
static const Byte LineCallOrigin_Inbound = 0x80;
static const Shortint LineCallParamFlags_Secure = 0x1;
static const Shortint LineCallParamFlags_Idle = 0x2;
static const Shortint LineCallParamFlags_BlockID = 0x4;
static const Shortint LineCallParamFlags_OrigOffHook = 0x8;
static const Shortint LineCallParamFlags_DestOffHook = 0x10;
static const Shortint LineCallParamFlags_NoHoldConference = 0x20;
static const Shortint LineCallParamFlags_PredictiveDial = 0x40;
static const Byte LineCallParamFlags_OneStepTransfer = 0x80;
static const Shortint LineCallPartyID_Blocked = 0x1;
static const Shortint LineCallPartyID_OutOfArea = 0x2;
static const Shortint LineCallPartyID_Name = 0x4;
static const Shortint LineCallPartyID_Address = 0x8;
static const Shortint LineCallPartyID_Partial = 0x10;
static const Shortint LineCallPartyID_Unknown = 0x20;
static const Shortint LineCallPartyID_Unavail = 0x40;
static const Shortint LineCallPrivilege_None = 0x1;
static const Shortint LineCallPrivilege_Monitor = 0x2;
static const Shortint LineCallPrivilege_Owner = 0x4;
static const Shortint LineCallReason_Direct = 0x1;
static const Shortint LineCallReason_FwdBusy = 0x2;
static const Shortint LineCallReason_FwdNoAnswer = 0x4;
static const Shortint LineCallReason_FwdUnCond = 0x8;
static const Shortint LineCallReason_Pickup = 0x10;
static const Shortint LineCallReason_Unpark = 0x20;
static const Shortint LineCallReason_Redirect = 0x40;
static const Byte LineCallReason_CallCompletion = 0x80;
static const Word LineCallReason_Transfer = 0x100;
static const Word LineCallReason_Reminder = 0x200;
static const Word LineCallReason_Unknown = 0x400;
static const Word LineCallReason_Unavail = 0x800;
static const Word LineCallReason_Intrude = 0x1000;
static const Word LineCallReason_Parked = 0x2000;
static const Word LineCallReason_CampedOn = 0x4000;
static const Word LineCallReason_RouteRequest = 0x8000;
static const Shortint LineCallSelect_Line = 0x1;
static const Shortint LineCallSelect_Address = 0x2;
static const Shortint LineCallSelect_Call = 0x4;
static const Shortint LineCallState_Idle = 0x1;
static const Shortint LineCallState_Offering = 0x2;
static const Shortint LineCallState_Accepted = 0x4;
static const Shortint LineCallState_Dialtone = 0x8;
static const Shortint LineCallState_Dialing = 0x10;
static const Shortint LineCallState_Ringback = 0x20;
static const Shortint LineCallState_Busy = 0x40;
static const Byte LineCallState_SpecialInfo = 0x80;
static const Word LineCallState_Connected = 0x100;
static const Word LineCallState_Proceeding = 0x200;
static const Word LineCallState_OnHold = 0x400;
static const Word LineCallState_Conferenced = 0x800;
static const Word LineCallState_OnHoldPendConf = 0x1000;
static const Word LineCallState_OnHoldPendTransfer = 0x2000;
static const Word LineCallState_Disconnected = 0x4000;
static const Word LineCallState_Unknown = 0x8000;
static const Shortint LineCallTreatment_Silence = 0x1;
static const Shortint LineCallTreatment_Ringback = 0x2;
static const Shortint LineCallTreatment_Busy = 0x3;
static const Shortint LineCallTreatment_Music = 0x4;
static const Shortint LineCardOption_Predefined = 0x1;
static const Shortint LineCardOption_Hidden = 0x2;
static const Shortint LineConnectedMode_Active = 0x1;
static const Shortint LineConnectedMode_Inactive = 0x2;
static const Shortint LineConnectedMode_ActiveHeld = 0x4;
static const Shortint LineConnectedMode_InactiveHeld = 0x8;
static const Shortint LineConnectedMode_Confirmed = 0x10;
static const Shortint LineDevCapFlags_CrossAddrConf = 0x1;
static const Shortint LineDevCapFlags_HighLevComp = 0x2;
static const Shortint LineDevCapFlags_LowLevComp = 0x4;
static const Shortint LineDevCapFlags_MediaControl = 0x8;
static const Shortint LineDevCapFlags_MultipleAddr = 0x10;
static const Shortint LineDevCapFlags_CloseDrop = 0x20;
static const Shortint LineDevCapFlags_DialBilling = 0x40;
static const Byte LineDevCapFlags_DialQuiet = 0x80;
static const Word LineDevCapFlags_DialDialtone = 0x100;
static const Shortint LineDevState_Other = 0x1;
static const Shortint LineDevState_Ringing = 0x2;
static const Shortint LineDevState_Connected = 0x4;
static const Shortint LineDevState_Disconnected = 0x8;
static const Shortint LineDevState_MsgWaitOn = 0x10;
static const Shortint LineDevState_MsgWaitOff = 0x20;
static const Shortint LineDevState_InService = 0x40;
static const Byte LineDevState_OutOfService = 0x80;
static const Word LineDevState_Maintenance = 0x100;
static const Word LineDevState_Open = 0x200;
static const Word LineDevState_Close = 0x400;
static const Word LineDevState_NumCalls = 0x800;
static const Word LineDevState_NumCompletions = 0x1000;
static const Word LineDevState_Terminals = 0x2000;
static const Word LineDevState_RoamMode = 0x4000;
static const Word LineDevState_Battery = 0x8000;
static const int LineDevState_Signal = 0x10000;
static const int LineDevState_DevSpecific = 0x20000;
static const int LineDevState_ReInit = 0x40000;
static const int LineDevState_Lock = 0x80000;
static const int LineDevState_CapsChange = 0x100000;
static const int LineDevState_ConfigChange = 0x200000;
static const int LineDevState_TranslateChange = 0x400000;
static const int LineDevState_ComplCancel = 0x800000;
static const int LineDevState_Removed = 0x1000000;
static const int AllLineDeviceStates = 0x1ffffff;
static const Shortint LineDevStatusFlags_Connected = 0x1;
static const Shortint LineDevStatusFlags_MsgWait = 0x2;
static const Shortint LineDevStatusFlags_InService = 0x4;
static const Shortint LineDevStatusFlags_Locked = 0x8;
static const Shortint LineDialToneMode_Normal = 0x1;
static const Shortint LineDialToneMode_Special = 0x2;
static const Shortint LineDialToneMode_Internal = 0x4;
static const Shortint LineDialToneMode_External = 0x8;
static const Shortint LineDialToneMode_Unknown = 0x10;
static const Shortint LineDialToneMode_Unavail = 0x20;
static const Shortint LineDigitMode_Pulse = 0x1;
static const Shortint LineDigitMode_DTMF = 0x2;
static const Shortint LineDigitMode_DTMFEnd = 0x4;
static const Shortint LineDisconnectMode_Normal = 0x1;
static const Shortint LineDisconnectMode_Unknown = 0x2;
static const Shortint LineDisconnectMode_Reject = 0x4;
static const Shortint LineDisconnectMode_PickUp = 0x8;
static const Shortint LineDisconnectMode_Forwarded = 0x10;
static const Shortint LineDisconnectMode_Busy = 0x20;
static const Shortint LineDisconnectMode_NoAnswer = 0x40;
static const Byte LineDisconnectMode_BadAddress = 0x80;
static const Word LineDisconnectMode_Unreachable = 0x100;
static const Word LineDisconnectMode_Congestion = 0x200;
static const Word LineDisconnectMode_Incompatible = 0x400;
static const Word LineDisconnectMode_Unavail = 0x800;
static const Word LineDisconnectMode_NoDialtone = 0x1000;
static const Word LineDisconnectMode_NumberChanged = 0x2000;
static const Word LineDisconnectMode_OutOfOrder = 0x4000;
static const Word LineDisconnectMode_TempFailure = 0x8000;
static const int LineDisconnectMode_QOSUnavail = 0x10000;
static const int LineDisconnectMode_Blocked = 0x20000;
static const int LineDisconnectMode_DoNotDisturb = 0x40000;
static const int LineDisconnectMode_Cancelled = 0x80000;
static const int LineErr_Allocated = 0x80000001;
static const int LineErr_BadDeviceID = 0x80000002;
static const int LineErr_BearerModeUnavail = 0x80000003;
static const int LineErr_CallUnavail = 0x80000005;
static const int LineErr_CompletionOverRun = 0x80000006;
static const int LineErr_ConferenceFull = 0x80000007;
static const int LineErr_DialBilling = 0x80000008;
static const int LineErr_DialDialtone = 0x80000009;
static const int LineErr_DialPrompt = 0x8000000a;
static const int LineErr_DialQuiet = 0x8000000b;
static const int LineErr_IncompatibleApiVersion = 0x8000000c;
static const int LineErr_IncompatibleExtVersion = 0x8000000d;
static const int LineErr_IniFileCorrupt = 0x8000000e;
static const int LineErr_InUse = 0x8000000f;
static const int LineErr_InvalAddress = 0x80000010;
static const int LineErr_InvalAddressID = 0x80000011;
static const int LineErr_InvalAddressMode = 0x80000012;
static const int LineErr_InvalAddressState = 0x80000013;
static const int LineErr_InvalAppHandle = 0x80000014;
static const int LineErr_InvalAppName = 0x80000015;
static const int LineErr_InvalBearerMode = 0x80000016;
static const int LineErr_InvalCallComplMode = 0x80000017;
static const int LineErr_InvalCallHandle = 0x80000018;
static const int LineErr_InvalCallParams = 0x80000019;
static const int LineErr_InvalCallPrivilege = 0x8000001a;
static const int LineErr_InvalCallSelect = 0x8000001b;
static const int LineErr_InvalCallState = 0x8000001c;
static const int LineErr_InvalCallStateList = 0x8000001d;
static const int LineErr_InvalCard = 0x8000001e;
static const int LineErr_InvalCompletionID = 0x8000001f;
static const int LineErr_InvalConfCallHandle = 0x80000020;
static const int LineErr_InvalConsultCallHandle = 0x80000021;
static const int LineErr_InvalCountryCode = 0x80000022;
static const int LineErr_InvalDeviceClass = 0x80000023;
static const int LineErr_InvalDeviceHandle = 0x80000024;
static const int LineErr_InvalDialParams = 0x80000025;
static const int LineErr_InvalDigitList = 0x80000026;
static const int LineErr_InvalDigitMode = 0x80000027;
static const int LineErr_InvalDigits = 0x80000028;
static const int LineErr_InvalExtVersion = 0x80000029;
static const int LineErr_InvalGroupID = 0x8000002a;
static const int LineErr_InvalLineHandle = 0x8000002b;
static const int LineErr_InvalLineState = 0x8000002c;
static const int LineErr_InvalLocation = 0x8000002d;
static const int LineErr_InvalMediaList = 0x8000002e;
static const int LineErr_InvalMediaMode = 0x8000002f;
static const int LineErr_InvalMessageID = 0x80000030;
static const int LineErr_InvalParam = 0x80000032;
static const int LineErr_InvalParkID = 0x80000033;
static const int LineErr_InvalParkMode = 0x80000034;
static const int LineErr_InvalPointer = 0x80000035;
static const int LineErr_InvalPrivSelect = 0x80000036;
static const int LineErr_InvalRate = 0x80000037;
static const int LineErr_InvalRequestMode = 0x80000038;
static const int LineErr_InvalTerminalID = 0x80000039;
static const int LineErr_InvalTerminalMode = 0x8000003a;
static const int LineErr_InvalTimeout = 0x8000003b;
static const int LineErr_InvalTone = 0x8000003c;
static const int LineErr_InvalToneList = 0x8000003d;
static const int LineErr_InvalToneMode = 0x8000003e;
static const int LineErr_InvalTransferMode = 0x8000003f;
static const int LineErr_LineMapperFailed = 0x80000040;
static const int LineErr_NoConference = 0x80000041;
static const int LineErr_NoDevice = 0x80000042;
static const int LineErr_NoDriver = 0x80000043;
static const int LineErr_NoMem = 0x80000044;
static const int LineErr_NoRequest = 0x80000045;
static const int LineErr_NotOwner = 0x80000046;
static const int LineErr_NotRegistered = 0x80000047;
static const int LineErr_OperationFailed = 0x80000048;
static const int LineErr_OperationUnavail = 0x80000049;
static const int LineErr_RateUnavail = 0x8000004a;
static const int LineErr_ResourceUnavail = 0x8000004b;
static const int LineErr_RequestOverRun = 0x8000004c;
static const int LineErr_StructureTooSmall = 0x8000004d;
static const int LineErr_TargetNotFound = 0x8000004e;
static const int LineErr_TargetSelf = 0x8000004f;
static const int LineErr_Uninitialized = 0x80000050;
static const int LineErr_UserUserInfoTooBig = 0x80000051;
static const int LineErr_ReInit = 0x80000052;
static const int LineErr_AddressBlocked = 0x80000053;
static const int LineErr_BillingRejected = 0x80000054;
static const int LineErr_InvalFeature = 0x80000055;
static const int LineErr_NoMultipleInstance = 0x80000056;
static const int LineErr_InvalAgentID = 0x80000057;
static const int LineErr_InvalAgentGroup = 0x80000058;
static const int LineErr_InvalPassword = 0x80000059;
static const int LineErr_InvalAgentState = 0x8000005a;
static const int LineErr_InvalAgentActivity = 0x8000005b;
static const int LineErr_DialVoiceDetect = 0x8000005c;
static const Shortint LineFeature_DevSpecific = 0x1;
static const Shortint LineFeature_DevSpecificFeat = 0x2;
static const Shortint LineFeature_Forward = 0x4;
static const Shortint LineFeature_MakeCall = 0x8;
static const Shortint LineFeature_SetMediaControl = 0x10;
static const Shortint LineFeature_SetTerminal = 0x20;
static const Shortint LineFeature_SetDevStatus = 0x40;
static const Byte LineFeature_ForwardFwd = 0x80;
static const Word LineFeature_ForwardDnd = 0x100;
static const Shortint LineForwardMode_Uncond = 0x1;
static const Shortint LineForwardMode_UncondInternal = 0x2;
static const Shortint LineForwardMode_UncondExternal = 0x4;
static const Shortint LineForwardMode_UncondSpecific = 0x8;
static const Shortint LineForwardMode_Busy = 0x10;
static const Shortint LineForwardMode_BusyInternal = 0x20;
static const Shortint LineForwardMode_BusyExternal = 0x40;
static const Byte LineForwardMode_BusySpecific = 0x80;
static const Word LineForwardMode_NoAnsw = 0x100;
static const Word LineForwardMode_NoAnswInternal = 0x200;
static const Word LineForwardMode_NoAnswExternal = 0x400;
static const Word LineForwardMode_NoAnswSpecific = 0x800;
static const Word LineForwardMode_BusyNA = 0x1000;
static const Word LineForwardMode_BusyNAInternal = 0x2000;
static const Word LineForwardMode_BusyNAExternal = 0x4000;
static const Word LineForwardMode_BusyNASpecific = 0x8000;
static const int LineForwardMode_Unknown = 0x10000;
static const int LineForwardMode_Unavail = 0x20000;
static const Shortint LineGatherTerm_BufferFull = 0x1;
static const Shortint LineGatherTerm_TermDigit = 0x2;
static const Shortint LineGatherTerm_FirstTimeout = 0x4;
static const Shortint LineGatherTerm_InterTimeout = 0x8;
static const Shortint LineGatherTerm_Cancel = 0x10;
static const Shortint LineGenerateTerm_Done = 0x1;
static const Shortint LineGenerateTerm_Cancel = 0x2;
static const Shortint LineInitializeExOption_UseHiddenWindow = 0x1;
static const Shortint LineInitializeExOption_UseEvent = 0x2;
static const Shortint LineInitializeExOption_UseCompletionPort = 0x3;
static const Shortint LineLocationOption_PulseDial = 0x1;
static const unsigned LineMapper = 0xffffffff;
static const Shortint LineMediaControl_None = 0x1;
static const Shortint LineMediaControl_Start = 0x2;
static const Shortint LineMediaControl_Reset = 0x4;
static const Shortint LineMediaControl_Pause = 0x8;
static const Shortint LineMediaControl_Resume = 0x10;
static const Shortint LineMediaControl_RateUp = 0x20;
static const Shortint LineMediaControl_RateDown = 0x40;
static const Byte LineMediaControl_RateNormal = 0x80;
static const Word LineMediaControl_VolumeUp = 0x100;
static const Word LineMediaControl_VolumeDown = 0x200;
static const Word LineMediaControl_VolumeNormal = 0x400;
static const Shortint LineMediaMode_Unknown = 0x2;
static const Shortint LineMediaMode_InteractiveVoice = 0x4;
static const Shortint LineMediaMode_AutomatedVoice = 0x8;
static const Shortint LineMediaMode_DataModem = 0x10;
static const Shortint LineMediaMode_G3Fax = 0x20;
static const Shortint LineMediaMode_TDD = 0x40;
static const Byte LineMediaMode_G4Fax = 0x80;
static const Word LineMediaMode_DigitalData = 0x100;
static const Word LineMediaMode_Teletex = 0x200;
static const Word LineMediaMode_Videotex = 0x400;
static const Word LineMediaMode_Telex = 0x800;
static const Word LineMediaMode_Mixed = 0x1000;
static const Word LineMediaMode_ADSI = 0x2000;
static const Word LineMediaMode_VoiceView = 0x4000;
static const Word Last_LineMediaMode = 0x4000;
static const Shortint LineOfferingMode_Active = 0x1;
static const Shortint LineOfferingMode_Inactive = 0x2;
static const unsigned LineOpenOption_SingleAddress = 0x80000000;
static const int LineOpenOption_Proxy = 0x40000000;
static const Shortint LineParkMode_Directed = 0x1;
static const Shortint LineParkMode_NonDirected = 0x2;
static const Shortint LineProxyRequest_SetAgentGroup = 0x1;
static const Shortint LineProxyRequest_SetAgentState = 0x2;
static const Shortint LineProxyRequest_SetAgentActivity = 0x3;
static const Shortint LineProxyRequest_GetAgentCaps = 0x4;
static const Shortint LineProxyRequest_GetAgentStatus = 0x5;
static const Shortint LineProxyRequest_AgentSpecific = 0x6;
static const Shortint LineProxyRequest_GetAgentActivityList = 0x7;
static const Shortint LineProxyRequest_GetAgentGroupList = 0x8;
static const Shortint LineRemoveFromConf_None = 0x1;
static const Shortint LineRemoveFromConf_Last = 0x2;
static const Shortint LineRemoveFromConf_Any = 0x3;
static const Shortint LineRequestMode_MakeCall = 0x1;
static const Shortint LineRequestMode_MediaCall = 0x2;
static const Shortint LineRequestMode_Drop = 0x4;
static const Shortint Last_LineRequestMode = 0x2;
static const Shortint LineRoamMode_Unknown = 0x1;
static const Shortint LineRoamMode_Unavail = 0x2;
static const Shortint LineRoamMode_Home = 0x4;
static const Shortint LineRoamMode_RoamA = 0x8;
static const Shortint LineRoamMode_RoamB = 0x10;
static const Shortint LineSpecialInfo_NoCircuit = 0x1;
static const Shortint LineSpecialInfo_CustIrreg = 0x2;
static const Shortint LineSpecialInfo_Reorder = 0x4;
static const Shortint LineSpecialInfo_Unknown = 0x8;
static const Shortint LineSpecialInfo_Unavail = 0x10;
static const Shortint LineTermDev_Phone = 0x1;
static const Shortint LineTermDev_Headset = 0x2;
static const Shortint LineTermDev_Speaker = 0x4;
static const Shortint LineTermMode_Buttons = 0x1;
static const Shortint LineTermMode_Lamps = 0x2;
static const Shortint LineTermMode_Display = 0x4;
static const Shortint LineTermMode_Ringer = 0x8;
static const Shortint LineTermMode_HookSwitch = 0x10;
static const Shortint LineTermMode_MediaToLine = 0x20;
static const Shortint LineTermMode_MediaFromLine = 0x40;
static const Byte LineTermMode_MediaBiDirect = 0x80;
static const Shortint LineTermSharing_Private = 0x1;
static const Shortint LineTermSharing_SharedExcl = 0x2;
static const Shortint LineTermSharing_SharedConf = 0x4;
static const Shortint LineTollListOption_Add = 0x1;
static const Shortint LineTollListOption_Remove = 0x2;
static const Shortint LineToneMode_Custom = 0x1;
static const Shortint LineToneMode_Ringback = 0x2;
static const Shortint LineToneMode_Busy = 0x4;
static const Shortint LineToneMode_Beep = 0x8;
static const Shortint LineToneMode_Billing = 0x10;
static const Shortint LineTransferMode_Transfer = 0x1;
static const Shortint LineTransferMode_Conference = 0x2;
static const Shortint LineTranslateOption_CareOverride = 0x1;
static const Shortint LineTranslateOption_CancelCallWaiting = 0x2;
static const Shortint LineTranslateOption_ForceLocal = 0x4;
static const Shortint LineTranslateOption_ForceLD = 0x8;
static const Shortint LineTranslateResult_Canonical = 0x1;
static const Shortint LineTranslateResult_International = 0x2;
static const Shortint LineTranslateResult_LongDistance = 0x4;
static const Shortint LineTranslateResult_Local = 0x8;
static const Shortint LineTranslateResult_InTollList = 0x10;
static const Shortint LineTranslateResult_NotInTollList = 0x20;
static const Shortint LineTranslateResult_DialBilling = 0x40;
static const Byte LineTranslateResult_DialQuiet = 0x80;
static const Word LineTranslateResult_DialDialTone = 0x100;
static const Word LineTranslateResult_DialPrompt = 0x200;
static const Word LineTranslateResult_VoiceDetect = 0x400;
static const Shortint APDSPECIFIC_TAPIChange = 0x1;
static const Shortint APDSPECIFIC_BUSY = 0x2;
static const Shortint APDSPECIFIC_DIALFAIL = 0x4;
static const Shortint APDSPECIFIC_RETRYWAIT = 0x8;
static const Shortint APDSPECIFIC_DEVICEInUse = 0x10;
extern PACKAGE int __fastcall tuLineGenerateTones(int Call, unsigned ToneMode, unsigned Duration, unsigned NumTones, const void *LINEGENERATETONE);
extern PACKAGE int __fastcall tuLineMonitorTones(int Call, const void *LINEMONITORTONE, unsigned NumEntries);
extern PACKAGE int __fastcall tuLineSetCallParams(int Call, unsigned BearerMode, unsigned MinRate, unsigned MaxRate, PLineDialParams DialParams);
extern PACKAGE int __fastcall tuLineHandoff(int Call, char * FileName, unsigned MediaMode);
extern PACKAGE int __fastcall tuLineMonitorMedia(int Call, unsigned MediaModes);
extern PACKAGE int __fastcall tuLineGenerateDigits(int Call, unsigned DigitModes, char * Digits, unsigned Duration);
extern PACKAGE int __fastcall tuLineMonitorDigits(int Call, unsigned DigitModes);
extern PACKAGE int __fastcall tuLineInitialize(int &LineApp, unsigned Instance, TLineCallback Callback, char * AppName, unsigned &NumDevs);
extern PACKAGE int __fastcall tuLineShutdown(int LineApp);
extern PACKAGE int __fastcall tuLineNegotiateApiVersion(int LineApp, int DeviceID, int APILowVersion, int APIHighVersion, int &ApiVersion, TLineExtensionID &LE);
extern PACKAGE int __fastcall tuLineGetDevCaps(int LineApp, unsigned DeviceID, unsigned ApiVersion, unsigned ExtVersion, PLineDevCaps LineDevCaps);
extern PACKAGE int __fastcall tuLineOpen(int LineApp, unsigned DeviceID, int &Line, unsigned ApiVersion, unsigned ExtVersion, unsigned CallbackInstance, unsigned Privleges, unsigned MediaModes, unsigned CallParams);
extern PACKAGE int __fastcall tuLineMakeCall(int Line, int &Call, char * DestAddress, unsigned CountryCode, const PLineCallParams CallParams);
extern PACKAGE int __fastcall tuLineAccept(int Call, char * UserUserInfo, unsigned Size);
extern PACKAGE int __fastcall tuLineAnswer(int Call, char * UserUserInfo, unsigned Size);
extern PACKAGE int __fastcall tuLineDeallocateCall(int Call);
extern PACKAGE int __fastcall tuLineDrop(int Call, char * UserInfo, unsigned Size);
extern PACKAGE int __fastcall tuLineClose(int Line);
extern PACKAGE int __fastcall tuLineGetCountry(int CountryID, int ApiVersion, PLineCountryList LineCountryList);
extern PACKAGE int __fastcall tuLineConfigDialog(unsigned DeviceID, HWND Owner, char * DeviceClass);
extern PACKAGE int __fastcall tuLineConfigDialogEdit(unsigned DeviceID, HWND Owner, char * DeviceClass, const void *inDevConfig, unsigned Size, TVarString &DevConfig);
extern PACKAGE int __fastcall tuLineGetID(int Line, unsigned AddressID, int Call, unsigned Select, TVarString &DeviceID, char * DeviceClass);
extern PACKAGE int __fastcall tuLineSetStatusMessages(int Line, unsigned LineStates, unsigned AddressStates);
extern PACKAGE int __fastcall tuLineGetStatusMessages(int Line, unsigned &LineStates, unsigned &AddressStates);
extern PACKAGE int __fastcall tuLineGetAddressCaps(int LineApp, unsigned DeviceID, unsigned AddressId, unsigned ApiVersion, unsigned ExtVersion, PLineAddressCaps LineAddressCaps);
extern PACKAGE int __fastcall tuLineGetAddressStatus(int Line, unsigned AddressID, TLineAddressStatus &AddressStatus);
extern PACKAGE int __fastcall tuLineGetLineDevStatus(int Line, PLineDevStatus &DevStatus);
extern PACKAGE int __fastcall tuLineGetDevConfig(unsigned DeviceID, TVarString &DeviceConfig, char * DeviceClass);
extern PACKAGE int __fastcall tuLineSetDevConfig(unsigned DeviceID, const void *DeviceConfig, unsigned Size, char * DeviceClass);
extern PACKAGE int __fastcall tuLineGetCallInfo(int Call, PCallInfo CallInfo);
extern PACKAGE int __fastcall tuLineGetCallStatus(int Call, PCallStatus CallStatus);
extern PACKAGE int __fastcall tuLineSetMediaMode(int Call, unsigned MediaModes);
extern PACKAGE int __fastcall tuLineSetCurrentLocation(int Line, unsigned Location);
extern PACKAGE int __fastcall tuLineSetTollList(int Line, unsigned DeviceID, char * AddressIn, unsigned TollListOption);
extern PACKAGE int __fastcall tuLineGetDevCapsDyn(int LineApp, unsigned DeviceID, unsigned ApiVersion, unsigned ExtVersion, PLineDevCaps &LineDevCaps);
extern PACKAGE int __fastcall tuLineGetLineDevStatusDyn(int Line, PLineDevStatus &DevStatus);
extern PACKAGE int __fastcall tuLineGetCallInfoDyn(int Call, PCallInfo &CallInfo);
extern PACKAGE int __fastcall tuLineGetCallStatusDyn(int Call, PCallStatus &CallStatus);
extern PACKAGE int __fastcall tuLineTranslateAddressDyn(int Line, unsigned DeviceID, unsigned APIVersion, AnsiString AddressIn, unsigned Card, unsigned TranslateOptions, PLineTranslateOutput &TranslateOutput);
extern PACKAGE int __fastcall tuLineTranslateDialog(int Line, unsigned DeviceID, unsigned APIVersion, HWND HwndOwner, AnsiString AddressIn);
extern PACKAGE int __fastcall tuLineHold(int &Call);
extern PACKAGE int __fastcall tuLineUnhold(int &Call);
extern PACKAGE int __fastcall tuLineTransfer(int &Call, char * DestAddress, unsigned CountryCode);

}	/* namespace Adtutil */
using namespace Adtutil;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdTUtil
