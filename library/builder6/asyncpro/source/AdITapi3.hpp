// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdITapi3.pas' rev: 5.00

#ifndef AdITapi3HPP
#define AdITapi3HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <OoMisc.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <StdVCL.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <ActiveX.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Aditapi3
{
//-- type declarations -------------------------------------------------------
typedef Activex::TOleEnum ADDRESS_STATE;

typedef Activex::TOleEnum CALLHUB_STATE;

typedef Activex::TOleEnum DISCONNECT_CODE;

typedef Activex::TOleEnum QOS_SERVICE_LEVEL;

typedef Activex::TOleEnum FINISH_MODE;

typedef Activex::TOleEnum CALL_STATE;

typedef Activex::TOleEnum CALL_PRIVILEGE;

typedef Activex::TOleEnum CALLINFO_LONG;

typedef Activex::TOleEnum CALLINFO_STRING;

typedef Activex::TOleEnum CALLINFO_BUFFER;

typedef Activex::TOleEnum CALL_STATE_EVENT_CAUSE;

typedef Activex::TOleEnum CALL_NOTIFICATION_EVENT;

typedef Activex::TOleEnum TAPI_EVENT;

typedef Activex::TOleEnum CALLHUB_EVENT;

typedef Activex::TOleEnum ADDRESS_CAPABILITY;

typedef Activex::TOleEnum ADDRESS_CAPABILITY_STRING;

typedef Activex::TOleEnum QOS_EVENT;

typedef Activex::TOleEnum ADDRESS_EVENT;

typedef Activex::TOleEnum TERMINAL_STATE;

typedef Activex::TOleEnum TERMINAL_TYPE;

typedef Activex::TOleEnum TERMINAL_DIRECTION;

typedef Activex::TOleEnum CALL_MEDIA_EVENT;

typedef Activex::TOleEnum CALL_MEDIA_EVENT_CAUSE;

typedef Activex::TOleEnum TAPIOBJECT_EVENT;

typedef Activex::TOleEnum AGENT_SESSION_STATE;

typedef Activex::TOleEnum AGENT_STATE;

typedef Activex::TOleEnum AGENT_EVENT;

typedef Activex::TOleEnum AGENT_SESSION_EVENT;

typedef Activex::TOleEnum ACDGROUP_EVENT;

typedef Activex::TOleEnum ACDQUEUE_EVENT;

typedef Activex::TOleEnum AGENTHANDLER_EVENT;

typedef Activex::TOleEnum CALLINFOCHANGE_CAUSE;

__interface ITTAPI;
typedef System::DelphiInterface<ITTAPI> _di_ITTAPI;
__interface IEnumAddress;
typedef System::DelphiInterface<IEnumAddress> _di_IEnumAddress;
__interface ITAddress;
typedef System::DelphiInterface<ITAddress> _di_ITAddress;
__interface IEnumCallHub;
typedef System::DelphiInterface<IEnumCallHub> _di_IEnumCallHub;
__interface IEnumUnknown;
typedef System::DelphiInterface<IEnumUnknown> _di_IEnumUnknown;
__interface INTERFACE_UUID("{B1EFC382-9355-11D0-835C-00AA003CCABD}") ITTAPI  : public IDispatch 
{
	
public:
	virtual HRESULT __safecall Initialize(void) = 0 ;
	virtual HRESULT __safecall Shutdown(void) = 0 ;
	virtual HRESULT __safecall Get_Addresses(OleVariant &Get_Addresses_result) = 0 ;
	virtual HRESULT __safecall EnumerateAddresses(_di_IEnumAddress &EnumerateAddresses_result) = 0 ;
	virtual HRESULT __safecall RegisterCallNotifications(const _di_ITAddress pAddress, Word fMonitor, Word 
		fOwner, int lMediaTypes, int lCallbackInstance, int &RegisterCallNotifications_result) = 0 ;
	virtual HRESULT __safecall UnregisterNotifications(int lRegister) = 0 ;
	virtual HRESULT __safecall Get_CallHubs(OleVariant &Get_CallHubs_result) = 0 ;
	virtual HRESULT __safecall EnumerateCallHubs(_di_IEnumCallHub &EnumerateCallHubs_result) = 0 ;
	virtual HRESULT __safecall SetCallHubTracking(const OleVariant pAddresses, Word bTracking) = 0 ;
	virtual HRESULT __safecall EnumeratePrivateTAPIObjects(/* out */ _di_IEnumUnknown &ppEnumUnknown) = 0 
		;
	virtual HRESULT __safecall Get_PrivateTAPIObjects(OleVariant &Get_PrivateTAPIObjects_result) = 0 ;
	virtual HRESULT __safecall RegisterRequestRecipient(int lRegistrationInstance, int lRequestMode, Word 
		fEnable) = 0 ;
	virtual HRESULT __safecall SetAssistedTelephonyPriority(const WideString pAppFilename, Word fPriority
		) = 0 ;
	virtual HRESULT __safecall SetApplicationPriority(const WideString pAppFilename, int lMediaType, Word 
		fPriority) = 0 ;
	virtual HRESULT __safecall Set_EventFilter(int plFilterMask) = 0 ;
	virtual HRESULT __safecall Get_EventFilter(int &Get_EventFilter_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_Addresses() { OleVariant r; HRESULT hr = Get_Addresses(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant Addresses = {read=_scw_Get_Addresses};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_CallHubs() { OleVariant r; HRESULT hr = Get_CallHubs(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant CallHubs = {read=_scw_Get_CallHubs};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_PrivateTAPIObjects() { OleVariant r; HRESULT hr = Get_PrivateTAPIObjects(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant PrivateTAPIObjects = {read=_scw_Get_PrivateTAPIObjects};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_EventFilter() { int r; HRESULT hr = Get_EventFilter(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property int EventFilter = {read=_scw_Get_EventFilter, write=Set_EventFilter};
};
typedef ITTAPI TAPI;

__interface ITDispatchMapper;
typedef System::DelphiInterface<ITDispatchMapper> _di_ITDispatchMapper;
__interface INTERFACE_UUID("{E9225295-C759-11D1-A02B-00C04FB6809F}") ITDispatchMapper  : public IDispatch 
	
{
	
public:
	virtual HRESULT __stdcall QueryDispatchInterface(const WideString pIID, const _di_IDispatch pInterfaceToMap
		, /* out */ _di_IDispatch &ppReturnedInterface) = 0 ;
};
typedef ITDispatchMapper DispatchMapper;

__interface ITRequest;
typedef System::DelphiInterface<ITRequest> _di_ITRequest;
__interface INTERFACE_UUID("{AC48FFDF-F8C4-11D1-A030-00C04FB6809F}") ITRequest  : public IDispatch 
{
	
public:
	virtual HRESULT __stdcall MakeCall(const WideString pDestAddress, const WideString pAppName, const 
		WideString pCalledParty, const WideString pComment) = 0 ;
};
typedef ITRequest RequestMakeCall;

typedef Byte *PByte1;

__interface ITCollection;
typedef System::DelphiInterface<ITCollection> _di_ITCollection;
__interface INTERFACE_UUID("{5EC5ACF2-9C02-11D0-8362-00AA003CCABD}") ITCollection  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Count(int &Get_Count_result) = 0 ;
	virtual HRESULT __safecall Get_Item(int Index, OleVariant &Get_Item_result) = 0 ;
	virtual HRESULT __safecall Get__NewEnum(_di_IUnknown &Get__NewEnum_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Count() { int r; HRESULT hr = Get_Count(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property int Count = {read=_scw_Get_Count};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_Item(int Index) { OleVariant r; HRESULT hr = Get_Item(
		Index, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant Item[int Index] = {read=_scw_Get_Item/*, default*/};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IUnknown _scw_Get__NewEnum() { _di_IUnknown r; HRESULT hr = Get__NewEnum(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_IUnknown _NewEnum = {read=_scw_Get__NewEnum};
};

__dispinterface ITCollectionDisp;
typedef System::DelphiInterface<ITCollectionDisp> _di_ITCollectionDisp;
__dispinterface INTERFACE_UUID("{5EC5ACF2-9C02-11D0-8362-00AA003CCABD}") ITCollectionDisp  : public IDispatch 
	
{
	
};

__interface ITCallStateEvent;
typedef System::DelphiInterface<ITCallStateEvent> _di_ITCallStateEvent;
__interface ITCallInfo;
typedef System::DelphiInterface<ITCallInfo> _di_ITCallInfo;
__interface INTERFACE_UUID("{62F47097-95C9-11D0-835D-00AA003CCABD}") ITCallStateEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Call(_di_ITCallInfo &Get_Call_result) = 0 ;
	virtual HRESULT __safecall Get_State(Activex::TOleEnum &Get_State_result) = 0 ;
	virtual HRESULT __safecall Get_Cause(Activex::TOleEnum &Get_Cause_result) = 0 ;
	virtual HRESULT __safecall Get_CallbackInstance(int &Get_CallbackInstance_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITCallInfo _scw_Get_Call() { _di_ITCallInfo r; HRESULT hr = Get_Call(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITCallInfo Call = {read=_scw_Get_Call};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_State() { Activex::TOleEnum r; HRESULT hr = Get_State(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum State = {read=_scw_Get_State};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_Cause() { Activex::TOleEnum r; HRESULT hr = Get_Cause(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum Cause = {read=_scw_Get_Cause};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CallbackInstance() { int r; HRESULT hr = Get_CallbackInstance(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int CallbackInstance = {read=_scw_Get_CallbackInstance};
};

__dispinterface ITCallStateEventDisp;
typedef System::DelphiInterface<ITCallStateEventDisp> _di_ITCallStateEventDisp;
__dispinterface INTERFACE_UUID("{62F47097-95C9-11D0-835D-00AA003CCABD}") ITCallStateEventDisp  : public IDispatch 
	
{
	
};

__interface ITCallHub;
typedef System::DelphiInterface<ITCallHub> _di_ITCallHub;
__interface INTERFACE_UUID("{350F85D1-1227-11D3-83D4-00C04FB6809F}") ITCallInfo  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Address(_di_ITAddress &Get_Address_result) = 0 ;
	virtual HRESULT __safecall Get_CallState(Activex::TOleEnum &Get_CallState_result) = 0 ;
	virtual HRESULT __safecall Get_Privilege(Activex::TOleEnum &Get_Privilege_result) = 0 ;
	virtual HRESULT __safecall Get_CallHub(_di_ITCallHub &Get_CallHub_result) = 0 ;
	virtual HRESULT __safecall Get_CallInfoLong(Activex::TOleEnum CallInfoLong, int &Get_CallInfoLong_result
		) = 0 ;
	virtual HRESULT __safecall Set_CallInfoLong(Activex::TOleEnum CallInfoLong, int plCallInfoLongVal) = 0 
		;
	virtual HRESULT __safecall Get_CallInfoString(Activex::TOleEnum CallInfoString, WideString &Get_CallInfoString_result
		) = 0 ;
	virtual HRESULT __safecall Set_CallInfoString(Activex::TOleEnum CallInfoString, const WideString ppCallInfoString
		) = 0 ;
	virtual HRESULT __safecall Get_CallInfoBuffer(Activex::TOleEnum CallInfoBuffer, OleVariant &Get_CallInfoBuffer_result
		) = 0 ;
	virtual HRESULT __safecall Set_CallInfoBuffer(Activex::TOleEnum CallInfoBuffer, const OleVariant ppCallInfoBuffer
		) = 0 ;
	virtual HRESULT __safecall GetCallInfoBuffer(Activex::TOleEnum CallInfoBuffer, /* out */ unsigned &
		pdwSize, /* out */ PByte1 &ppCallInfoBuffer) = 0 ;
	virtual HRESULT __safecall SetCallInfoBuffer(Activex::TOleEnum CallInfoBuffer, unsigned dwSize, Byte 
		&pCallInfoBuffer) = 0 ;
	virtual HRESULT __safecall ReleaseUserUserInfo(void) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITAddress _scw_Get_Address() { _di_ITAddress r; HRESULT hr = Get_Address(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITAddress Address = {read=_scw_Get_Address};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_CallState() { Activex::TOleEnum r; HRESULT hr = Get_CallState(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum CallState = {read=_scw_Get_CallState};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_Privilege() { Activex::TOleEnum r; HRESULT hr = Get_Privilege(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum Privilege = {read=_scw_Get_Privilege};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITCallHub _scw_Get_CallHub() { _di_ITCallHub r; HRESULT hr = Get_CallHub(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITCallHub CallHub = {read=_scw_Get_CallHub};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CallInfoLong(Activex::TOleEnum CallInfoLong) { int r; HRESULT hr = Get_CallInfoLong(
		CallInfoLong, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int CallInfoLong[Activex::TOleEnum CallInfoLong] = {read=_scw_Get_CallInfoLong, write=Set_CallInfoLong
		};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_CallInfoString(Activex::TOleEnum CallInfoString) { WideString r; HRESULT hr = Get_CallInfoString(
		CallInfoString, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString CallInfoString[Activex::TOleEnum CallInfoString] = {read=_scw_Get_CallInfoString
		, write=Set_CallInfoString};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_CallInfoBuffer(Activex::TOleEnum CallInfoBuffer) { OleVariant r; HRESULT hr = Get_CallInfoBuffer(
		CallInfoBuffer, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant CallInfoBuffer[Activex::TOleEnum CallInfoBuffer] = {read=_scw_Get_CallInfoBuffer
		, write=Set_CallInfoBuffer};
};

__dispinterface ITCallInfoDisp;
typedef System::DelphiInterface<ITCallInfoDisp> _di_ITCallInfoDisp;
__dispinterface INTERFACE_UUID("{350F85D1-1227-11D3-83D4-00C04FB6809F}") ITCallInfoDisp  : public IDispatch 
	
{
	
};

__interface ITBasicCallControl;
typedef System::DelphiInterface<ITBasicCallControl> _di_ITBasicCallControl;
__interface IEnumCall;
typedef System::DelphiInterface<IEnumCall> _di_IEnumCall;
__interface ITForwardInformation;
typedef System::DelphiInterface<ITForwardInformation> _di_ITForwardInformation;
__interface INTERFACE_UUID("{B1EFC386-9355-11D0-835C-00AA003CCABD}") ITAddress  : public IDispatch 
{
	
public:
	virtual HRESULT __safecall Get_State(Activex::TOleEnum &Get_State_result) = 0 ;
	virtual HRESULT __safecall Get_AddressName(WideString &Get_AddressName_result) = 0 ;
	virtual HRESULT __safecall Get_ServiceProviderName(WideString &Get_ServiceProviderName_result) = 0 
		;
	virtual HRESULT __safecall Get_TAPIObject(_di_ITTAPI &Get_TAPIObject_result) = 0 ;
	virtual HRESULT __safecall CreateCall(const WideString pDestAddress, int lAddressType, int lMediaTypes
		, _di_ITBasicCallControl &CreateCall_result) = 0 ;
	virtual HRESULT __safecall Get_Calls(OleVariant &Get_Calls_result) = 0 ;
	virtual HRESULT __safecall EnumerateCalls(_di_IEnumCall &EnumerateCalls_result) = 0 ;
	virtual HRESULT __safecall Get_DialableAddress(WideString &Get_DialableAddress_result) = 0 ;
	virtual HRESULT __safecall CreateForwardInfoObject(_di_ITForwardInformation &CreateForwardInfoObject_result
		) = 0 ;
	virtual HRESULT __safecall Forward(const _di_ITForwardInformation pForwardInfo, const _di_ITBasicCallControl 
		pCall) = 0 ;
	virtual HRESULT __safecall Get_CurrentForwardInfo(_di_ITForwardInformation &Get_CurrentForwardInfo_result
		) = 0 ;
	virtual HRESULT __safecall Set_MessageWaiting(Word pfMessageWaiting) = 0 ;
	virtual HRESULT __safecall Get_MessageWaiting(Word &Get_MessageWaiting_result) = 0 ;
	virtual HRESULT __safecall Set_DoNotDisturb(Word pfDoNotDisturb) = 0 ;
	virtual HRESULT __safecall Get_DoNotDisturb(Word &Get_DoNotDisturb_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_State() { Activex::TOleEnum r; HRESULT hr = Get_State(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum State = {read=_scw_Get_State};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_AddressName() { WideString r; HRESULT hr = Get_AddressName(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString AddressName = {read=_scw_Get_AddressName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_ServiceProviderName() { WideString r; HRESULT hr = Get_ServiceProviderName(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString ServiceProviderName = {read=_scw_Get_ServiceProviderName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITTAPI _scw_Get_TAPIObject() { _di_ITTAPI r; HRESULT hr = Get_TAPIObject(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITTAPI TAPIObject = {read=_scw_Get_TAPIObject};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_Calls() { OleVariant r; HRESULT hr = Get_Calls(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property OleVariant Calls = {read=_scw_Get_Calls};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_DialableAddress() { WideString r; HRESULT hr = Get_DialableAddress(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString DialableAddress = {read=_scw_Get_DialableAddress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITForwardInformation _scw_Get_CurrentForwardInfo() { _di_ITForwardInformation r; HRESULT hr = Get_CurrentForwardInfo(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITForwardInformation CurrentForwardInfo = {read=_scw_Get_CurrentForwardInfo};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Word _scw_Get_MessageWaiting() { Word r; HRESULT hr = Get_MessageWaiting(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Word MessageWaiting = {read=_scw_Get_MessageWaiting, write=Set_MessageWaiting};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Word _scw_Get_DoNotDisturb() { Word r; HRESULT hr = Get_DoNotDisturb(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Word DoNotDisturb = {read=_scw_Get_DoNotDisturb, write=Set_DoNotDisturb};
};

__dispinterface ITAddressDisp;
typedef System::DelphiInterface<ITAddressDisp> _di_ITAddressDisp;
__dispinterface INTERFACE_UUID("{B1EFC386-9355-11D0-835C-00AA003CCABD}") ITAddressDisp  : public IDispatch 
	
{
	
};

__dispinterface ITTAPIDisp;
typedef System::DelphiInterface<ITTAPIDisp> _di_ITTAPIDisp;
__dispinterface INTERFACE_UUID("{B1EFC382-9355-11D0-835C-00AA003CCABD}") ITTAPIDisp  : public IDispatch 
	
{
	
};

__interface INTERFACE_UUID("{1666FCA1-9363-11D0-835C-00AA003CCABD}") IEnumAddress  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ _di_ITAddress &ppElements, unsigned &pceltFetched
		) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumAddress &ppEnum) = 0 ;
};

__interface INTERFACE_UUID("{A3C15450-5B92-11D1-8F4E-00C04FB6809F}") IEnumCallHub  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ _di_ITCallHub &ppElements, unsigned &pceltFetched
		) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumCallHub &ppEnum) = 0 ;
};

__interface INTERFACE_UUID("{A3C1544E-5B92-11D1-8F4E-00C04FB6809F}") ITCallHub  : public IDispatch 
{
	
public:
	virtual HRESULT __safecall Clear(void) = 0 ;
	virtual HRESULT __safecall EnumerateCalls(_di_IEnumCall &EnumerateCalls_result) = 0 ;
	virtual HRESULT __safecall Get_Calls(OleVariant &Get_Calls_result) = 0 ;
	virtual HRESULT __safecall Get_NumCalls(int &Get_NumCalls_result) = 0 ;
	virtual HRESULT __safecall Get_State(Activex::TOleEnum &Get_State_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_Calls() { OleVariant r; HRESULT hr = Get_Calls(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property OleVariant Calls = {read=_scw_Get_Calls};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_NumCalls() { int r; HRESULT hr = Get_NumCalls(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property int NumCalls = {read=_scw_Get_NumCalls};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_State() { Activex::TOleEnum r; HRESULT hr = Get_State(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum State = {read=_scw_Get_State};
};

__dispinterface ITCallHubDisp;
typedef System::DelphiInterface<ITCallHubDisp> _di_ITCallHubDisp;
__dispinterface INTERFACE_UUID("{A3C1544E-5B92-11D1-8F4E-00C04FB6809F}") ITCallHubDisp  : public IDispatch 
	
{
	
};

__interface INTERFACE_UUID("{AE269CF6-935E-11D0-835C-00AA003CCABD}") IEnumCall  : public IUnknown 
{
	
public:
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ _di_ITCallInfo &ppElements, unsigned &pceltFetched
		) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumCall &ppEnum) = 0 ;
};

__interface INTERFACE_UUID("{00000100-0000-0000-C000-000000000046}") IEnumUnknown  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall RemoteNext(unsigned celt, /* out */ _di_IUnknown &rgelt, /* out */ unsigned 
		&pceltFetched) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumUnknown &ppEnum) = 0 ;
};

__interface INTERFACE_UUID("{B1EFC389-9355-11D0-835C-00AA003CCABD}") ITBasicCallControl  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Connect(Word fSync) = 0 ;
	virtual HRESULT __safecall Answer(void) = 0 ;
	virtual HRESULT __safecall Disconnect(Activex::TOleEnum code) = 0 ;
	virtual HRESULT __safecall Hold(Word fHold) = 0 ;
	virtual HRESULT __safecall HandoffDirect(const WideString pApplicationName) = 0 ;
	virtual HRESULT __safecall HandoffIndirect(int lMediaType) = 0 ;
	virtual HRESULT __safecall Conference(const _di_ITBasicCallControl pCall, Word fSync) = 0 ;
	virtual HRESULT __safecall Transfer(const _di_ITBasicCallControl pCall, Word fSync) = 0 ;
	virtual HRESULT __safecall BlindTransfer(const WideString pDestAddress) = 0 ;
	virtual HRESULT __safecall SwapHold(const _di_ITBasicCallControl pCall) = 0 ;
	virtual HRESULT __safecall ParkDirect(const WideString pParkAddress) = 0 ;
	virtual HRESULT __safecall ParkIndirect(WideString &ParkIndirect_result) = 0 ;
	virtual HRESULT __safecall Unpark(void) = 0 ;
	virtual HRESULT __safecall SetQOS(int lMediaType, Activex::TOleEnum ServiceLevel) = 0 ;
	virtual HRESULT __safecall Pickup(const WideString pGroupID) = 0 ;
	virtual HRESULT __safecall Dial(const WideString pDestAddress) = 0 ;
	virtual HRESULT __safecall Finish(Activex::TOleEnum finishMode) = 0 ;
	virtual HRESULT __safecall RemoveFromConference(void) = 0 ;
};

__dispinterface ITBasicCallControlDisp;
typedef System::DelphiInterface<ITBasicCallControlDisp> _di_ITBasicCallControlDisp;
__dispinterface INTERFACE_UUID("{B1EFC389-9355-11D0-835C-00AA003CCABD}") ITBasicCallControlDisp  : public IDispatch 
	
{
	
};

__interface INTERFACE_UUID("{449F659E-88A3-11D1-BB5D-00C04FB6809F}") ITForwardInformation  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Set_NumRingsNoAnswer(int plNumRings) = 0 ;
	virtual HRESULT __safecall Get_NumRingsNoAnswer(int &Get_NumRingsNoAnswer_result) = 0 ;
	virtual HRESULT __safecall SetForwardType(int ForwardType, const WideString pDestAddress, const WideString 
		pCallerAddress) = 0 ;
	virtual HRESULT __safecall Get_ForwardTypeDestination(int ForwardType, WideString &Get_ForwardTypeDestination_result
		) = 0 ;
	virtual HRESULT __safecall Get_ForwardTypeCaller(int ForwardType, WideString &Get_ForwardTypeCaller_result
		) = 0 ;
	virtual HRESULT __safecall GetForwardType(int ForwardType, /* out */ WideString &ppDestinationAddress
		, /* out */ WideString &ppCallerAddress) = 0 ;
	virtual HRESULT __safecall Clear(void) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_NumRingsNoAnswer() { int r; HRESULT hr = Get_NumRingsNoAnswer(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int NumRingsNoAnswer = {read=_scw_Get_NumRingsNoAnswer, write=Set_NumRingsNoAnswer};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_ForwardTypeDestination(int ForwardType) { WideString r; HRESULT hr = Get_ForwardTypeDestination(
		ForwardType, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString ForwardTypeDestination[int ForwardType] = {read=_scw_Get_ForwardTypeDestination
		};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_ForwardTypeCaller(int ForwardType) { WideString r; HRESULT hr = Get_ForwardTypeCaller(
		ForwardType, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString ForwardTypeCaller[int ForwardType] = {read=_scw_Get_ForwardTypeCaller};
};

__dispinterface ITForwardInformationDisp;
typedef System::DelphiInterface<ITForwardInformationDisp> _di_ITForwardInformationDisp;
__dispinterface INTERFACE_UUID("{449F659E-88A3-11D1-BB5D-00C04FB6809F}") ITForwardInformationDisp  : public IDispatch 
	
{
	
};

__interface ITCallNotificationEvent;
typedef System::DelphiInterface<ITCallNotificationEvent> _di_ITCallNotificationEvent;
__interface INTERFACE_UUID("{895801DF-3DD6-11D1-8F30-00C04FB6809F}") ITCallNotificationEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Call(_di_ITCallInfo &Get_Call_result) = 0 ;
	virtual HRESULT __safecall Get_Event(Activex::TOleEnum &Get_Event_result) = 0 ;
	virtual HRESULT __safecall Get_CallbackInstance(int &Get_CallbackInstance_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITCallInfo _scw_Get_Call() { _di_ITCallInfo r; HRESULT hr = Get_Call(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITCallInfo Call = {read=_scw_Get_Call};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_Event() { Activex::TOleEnum r; HRESULT hr = Get_Event(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum Event = {read=_scw_Get_Event};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CallbackInstance() { int r; HRESULT hr = Get_CallbackInstance(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int CallbackInstance = {read=_scw_Get_CallbackInstance};
};

__dispinterface ITCallNotificationEventDisp;
typedef System::DelphiInterface<ITCallNotificationEventDisp> _di_ITCallNotificationEventDisp;
__dispinterface INTERFACE_UUID("{895801DF-3DD6-11D1-8F30-00C04FB6809F}") ITCallNotificationEventDisp 
	 : public IDispatch 
{
	
};

__interface ITTAPIEventNotification;
typedef System::DelphiInterface<ITTAPIEventNotification> _di_ITTAPIEventNotification;
__interface INTERFACE_UUID("{EDDB9426-3B91-11D1-8F30-00C04FB6809F}") ITTAPIEventNotification  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Event(Activex::TOleEnum TapiEvent, const _di_IDispatch pEvent) = 0 ;
};

__interface ITBasicAudioTerminal;
typedef System::DelphiInterface<ITBasicAudioTerminal> _di_ITBasicAudioTerminal;
__interface INTERFACE_UUID("{B1EFC38D-9355-11D0-835C-00AA003CCABD}") ITBasicAudioTerminal  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Set_Volume(int plVolume) = 0 ;
	virtual HRESULT __safecall Get_Volume(int &Get_Volume_result) = 0 ;
	virtual HRESULT __safecall Set_Balance(int plBalance) = 0 ;
	virtual HRESULT __safecall Get_Balance(int &Get_Balance_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Volume() { int r; HRESULT hr = Get_Volume(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property int Volume = {read=_scw_Get_Volume, write=Set_Volume};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Balance() { int r; HRESULT hr = Get_Balance(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property int Balance = {read=_scw_Get_Balance, write=Set_Balance};
};

__dispinterface ITBasicAudioTerminalDisp;
typedef System::DelphiInterface<ITBasicAudioTerminalDisp> _di_ITBasicAudioTerminalDisp;
__dispinterface INTERFACE_UUID("{B1EFC38D-9355-11D0-835C-00AA003CCABD}") ITBasicAudioTerminalDisp  : public IDispatch 
	
{
	
};

__interface ITCallHubEvent;
typedef System::DelphiInterface<ITCallHubEvent> _di_ITCallHubEvent;
__interface INTERFACE_UUID("{A3C15451-5B92-11D1-8F4E-00C04FB6809F}") ITCallHubEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __stdcall Get_Event(/* out */ Activex::TOleEnum &pEvent) = 0 ;
	virtual HRESULT __stdcall Get_CallHub(/* out */ _di_ITCallHub &ppCallHub) = 0 ;
	virtual HRESULT __stdcall Get_Call(/* out */ _di_ITCallInfo &ppCall) = 0 ;
};

__interface ITAddressCapabilities;
typedef System::DelphiInterface<ITAddressCapabilities> _di_ITAddressCapabilities;
__interface IEnumBstr;
typedef System::DelphiInterface<IEnumBstr> _di_IEnumBstr;
__interface INTERFACE_UUID("{8DF232F5-821B-11D1-BB5C-00C04FB6809F}") ITAddressCapabilities  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_AddressCapability(Activex::TOleEnum AddressCap, int &Get_AddressCapability_result
		) = 0 ;
	virtual HRESULT __safecall Get_AddressCapabilityString(Activex::TOleEnum AddressCapString, WideString &Get_AddressCapabilityString_result
		) = 0 ;
	virtual HRESULT __safecall Get_CallTreatments(OleVariant &Get_CallTreatments_result) = 0 ;
	virtual HRESULT __safecall EnumerateCallTreatments(_di_IEnumBstr &EnumerateCallTreatments_result) = 0 
		;
	virtual HRESULT __safecall Get_CompletionMessages(OleVariant &Get_CompletionMessages_result) = 0 ;
	virtual HRESULT __safecall EnumerateCompletionMessages(_di_IEnumBstr &EnumerateCompletionMessages_result
		) = 0 ;
	virtual HRESULT __safecall Get_DeviceClasses(OleVariant &Get_DeviceClasses_result) = 0 ;
	virtual HRESULT __safecall EnumerateDeviceClasses(_di_IEnumBstr &EnumerateDeviceClasses_result) = 0 
		;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_AddressCapability(Activex::TOleEnum AddressCap) { int r; HRESULT hr = Get_AddressCapability(
		AddressCap, r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int AddressCapability[Activex::TOleEnum AddressCap] = {read=_scw_Get_AddressCapability};
		
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_AddressCapabilityString(Activex::TOleEnum AddressCapString
		) { WideString r; HRESULT hr = Get_AddressCapabilityString(AddressCapString, r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property WideString AddressCapabilityString[Activex::TOleEnum AddressCapString] = {read=_scw_Get_AddressCapabilityString
		};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_CallTreatments() { OleVariant r; HRESULT hr = Get_CallTreatments(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant CallTreatments = {read=_scw_Get_CallTreatments};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_CompletionMessages() { OleVariant r; HRESULT hr = Get_CompletionMessages(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant CompletionMessages = {read=_scw_Get_CompletionMessages};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_DeviceClasses() { OleVariant r; HRESULT hr = Get_DeviceClasses(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant DeviceClasses = {read=_scw_Get_DeviceClasses};
};

__dispinterface ITAddressCapabilitiesDisp;
typedef System::DelphiInterface<ITAddressCapabilitiesDisp> _di_ITAddressCapabilitiesDisp;
__dispinterface INTERFACE_UUID("{8DF232F5-821B-11D1-BB5C-00C04FB6809F}") ITAddressCapabilitiesDisp  : public IDispatch 
	
{
	
};

__interface INTERFACE_UUID("{35372049-0BC6-11D2-A033-00C04FB6809F}") IEnumBstr  : public IUnknown 
{
	
public:
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ WideString &ppStrings, unsigned &pceltFetched
		) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumBstr &ppEnum) = 0 ;
};

__interface ITQOSEvent;
typedef System::DelphiInterface<ITQOSEvent> _di_ITQOSEvent;
__interface INTERFACE_UUID("{CFA3357C-AD77-11D1-BB68-00C04FB6809F}") ITQOSEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __stdcall Get_Call(/* out */ _di_ITCallInfo &ppCall) = 0 ;
	virtual HRESULT __stdcall Get_Event(/* out */ Activex::TOleEnum &pQosEvent) = 0 ;
	virtual HRESULT __stdcall Get_MediaType(/* out */ int &plMediaType) = 0 ;
};

__interface ITAddressEvent;
typedef System::DelphiInterface<ITAddressEvent> _di_ITAddressEvent;
__interface ITTerminal;
typedef System::DelphiInterface<ITTerminal> _di_ITTerminal;
__interface INTERFACE_UUID("{831CE2D1-83B5-11D1-BB5C-00C04FB6809F}") ITAddressEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __stdcall Get_Address(/* out */ _di_ITAddress &ppAddress) = 0 ;
	virtual HRESULT __stdcall Get_Event(/* out */ Activex::TOleEnum &pEvent) = 0 ;
	virtual HRESULT __stdcall Get_Terminal(/* out */ _di_ITTerminal &ppTerminal) = 0 ;
};

__interface INTERFACE_UUID("{B1EFC38A-9355-11D0-835C-00AA003CCABD}") ITTerminal  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Name(WideString &Get_Name_result) = 0 ;
	virtual HRESULT __safecall Get_State(Activex::TOleEnum &Get_State_result) = 0 ;
	virtual HRESULT __safecall Get_TerminalType(Activex::TOleEnum &Get_TerminalType_result) = 0 ;
	virtual HRESULT __safecall Get_TerminalClass(WideString &Get_TerminalClass_result) = 0 ;
	virtual HRESULT __safecall Get_MediaType(int &Get_MediaType_result) = 0 ;
	virtual HRESULT __safecall Get_Direction(Activex::TOleEnum &Get_Direction_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_Name() { WideString r; HRESULT hr = Get_Name(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property WideString Name = {read=_scw_Get_Name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_State() { Activex::TOleEnum r; HRESULT hr = Get_State(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum State = {read=_scw_Get_State};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_TerminalType() { Activex::TOleEnum r; HRESULT hr = Get_TerminalType(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum TerminalType = {read=_scw_Get_TerminalType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_TerminalClass() { WideString r; HRESULT hr = Get_TerminalClass(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString TerminalClass = {read=_scw_Get_TerminalClass};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MediaType() { int r; HRESULT hr = Get_MediaType(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property int MediaType = {read=_scw_Get_MediaType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_Direction() { Activex::TOleEnum r; HRESULT hr = Get_Direction(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum Direction = {read=_scw_Get_Direction};
};

__dispinterface ITTerminalDisp;
typedef System::DelphiInterface<ITTerminalDisp> _di_ITTerminalDisp;
__dispinterface INTERFACE_UUID("{B1EFC38A-9355-11D0-835C-00AA003CCABD}") ITTerminalDisp  : public IDispatch 
	
{
	
};

__interface ITCallMediaEvent;
typedef System::DelphiInterface<ITCallMediaEvent> _di_ITCallMediaEvent;
__interface ITStream;
typedef System::DelphiInterface<ITStream> _di_ITStream;
__interface INTERFACE_UUID("{FF36B87F-EC3A-11D0-8EE4-00C04FB6809F}") ITCallMediaEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Call(_di_ITCallInfo &Get_Call_result) = 0 ;
	virtual HRESULT __safecall Get_Event(Activex::TOleEnum &Get_Event_result) = 0 ;
	virtual HRESULT __safecall Get_Error(HRESULT &Get_Error_result) = 0 ;
	virtual HRESULT __safecall Get_Terminal(_di_ITTerminal &Get_Terminal_result) = 0 ;
	virtual HRESULT __safecall Get_Stream(_di_ITStream &Get_Stream_result) = 0 ;
	virtual HRESULT __safecall Get_Cause(Activex::TOleEnum &Get_Cause_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITCallInfo _scw_Get_Call() { _di_ITCallInfo r; HRESULT hr = Get_Call(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITCallInfo Call = {read=_scw_Get_Call};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_Event() { Activex::TOleEnum r; HRESULT hr = Get_Event(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum Event = {read=_scw_Get_Event};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HRESULT _scw_Get_Error() { HRESULT r; HRESULT hr = Get_Error(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property HRESULT Error = {read=_scw_Get_Error};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITTerminal _scw_Get_Terminal() { _di_ITTerminal r; HRESULT hr = Get_Terminal(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITTerminal Terminal = {read=_scw_Get_Terminal};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITStream _scw_Get_Stream() { _di_ITStream r; HRESULT hr = Get_Stream(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITStream Stream = {read=_scw_Get_Stream};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_Cause() { Activex::TOleEnum r; HRESULT hr = Get_Cause(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum Cause = {read=_scw_Get_Cause};
};

__dispinterface ITCallMediaEventDisp;
typedef System::DelphiInterface<ITCallMediaEventDisp> _di_ITCallMediaEventDisp;
__dispinterface INTERFACE_UUID("{FF36B87F-EC3A-11D0-8EE4-00C04FB6809F}") ITCallMediaEventDisp  : public IDispatch 
	
{
	
};

__interface IEnumTerminal;
typedef System::DelphiInterface<IEnumTerminal> _di_IEnumTerminal;
__interface INTERFACE_UUID("{EE3BD605-3868-11D2-A045-00C04FB6809F}") ITStream  : public IDispatch 
{
	
public:
	virtual HRESULT __safecall Get_MediaType(int &Get_MediaType_result) = 0 ;
	virtual HRESULT __safecall Get_Direction(Activex::TOleEnum &Get_Direction_result) = 0 ;
	virtual HRESULT __safecall Get_Name(WideString &Get_Name_result) = 0 ;
	virtual HRESULT __safecall StartStream(void) = 0 ;
	virtual HRESULT __safecall PauseStream(void) = 0 ;
	virtual HRESULT __safecall StopStream(void) = 0 ;
	virtual HRESULT __safecall SelectTerminal(const _di_ITTerminal pTerminal) = 0 ;
	virtual HRESULT __safecall UnselectTerminal(const _di_ITTerminal pTerminal) = 0 ;
	virtual HRESULT __safecall EnumerateTerminals(/* out */ _di_IEnumTerminal &ppEnumTerminal) = 0 ;
	virtual HRESULT __safecall Get_Terminals(OleVariant &Get_Terminals_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MediaType() { int r; HRESULT hr = Get_MediaType(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property int MediaType = {read=_scw_Get_MediaType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_Direction() { Activex::TOleEnum r; HRESULT hr = Get_Direction(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum Direction = {read=_scw_Get_Direction};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_Name() { WideString r; HRESULT hr = Get_Name(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property WideString Name = {read=_scw_Get_Name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_Terminals() { OleVariant r; HRESULT hr = Get_Terminals(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant Terminals = {read=_scw_Get_Terminals};
};

__dispinterface ITStreamDisp;
typedef System::DelphiInterface<ITStreamDisp> _di_ITStreamDisp;
__dispinterface INTERFACE_UUID("{EE3BD605-3868-11D2-A045-00C04FB6809F}") ITStreamDisp  : public IDispatch 
	
{
	
};

__interface INTERFACE_UUID("{AE269CF4-935E-11D0-835C-00AA003CCABD}") IEnumTerminal  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ _di_ITTerminal &ppElements, unsigned &pceltFetched
		) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumTerminal &ppEnum) = 0 ;
};

__interface ITTAPIObjectEvent;
typedef System::DelphiInterface<ITTAPIObjectEvent> _di_ITTAPIObjectEvent;
__interface INTERFACE_UUID("{F4854D48-937A-11D1-BB58-00C04FB6809F}") ITTAPIObjectEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_TAPIObject(_di_ITTAPI &Get_TAPIObject_result) = 0 ;
	virtual HRESULT __safecall Get_Event(Activex::TOleEnum &Get_Event_result) = 0 ;
	virtual HRESULT __safecall Get_Address(_di_ITAddress &Get_Address_result) = 0 ;
	virtual HRESULT __safecall Get_CallbackInstance(int &Get_CallbackInstance_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITTAPI _scw_Get_TAPIObject() { _di_ITTAPI r; HRESULT hr = Get_TAPIObject(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITTAPI TAPIObject = {read=_scw_Get_TAPIObject};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_Event() { Activex::TOleEnum r; HRESULT hr = Get_Event(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum Event = {read=_scw_Get_Event};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITAddress _scw_Get_Address() { _di_ITAddress r; HRESULT hr = Get_Address(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITAddress Address = {read=_scw_Get_Address};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CallbackInstance() { int r; HRESULT hr = Get_CallbackInstance(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int CallbackInstance = {read=_scw_Get_CallbackInstance};
};

__dispinterface ITTAPIObjectEventDisp;
typedef System::DelphiInterface<ITTAPIObjectEventDisp> _di_ITTAPIObjectEventDisp;
__dispinterface INTERFACE_UUID("{F4854D48-937A-11D1-BB58-00C04FB6809F}") ITTAPIObjectEventDisp  : public IDispatch 
	
{
	
};

__interface ITAddressTranslation;
typedef System::DelphiInterface<ITAddressTranslation> _di_ITAddressTranslation;
__interface ITAddressTranslationInfo;
typedef System::DelphiInterface<ITAddressTranslationInfo> _di_ITAddressTranslationInfo;
__interface IEnumLocation;
typedef System::DelphiInterface<IEnumLocation> _di_IEnumLocation;
__interface IEnumCallingCard;
typedef System::DelphiInterface<IEnumCallingCard> _di_IEnumCallingCard;
__interface INTERFACE_UUID("{0C4D8F03-8DDB-11D1-A09E-00805FC147D3}") ITAddressTranslation  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall TranslateAddress(const WideString pAddressToTranslate, int lCard, int lTranslateOptions
		, _di_ITAddressTranslationInfo &TranslateAddress_result) = 0 ;
	virtual HRESULT __safecall TranslateDialog(int hwndOwner, const WideString pAddressIn) = 0 ;
	virtual HRESULT __safecall EnumerateLocations(_di_IEnumLocation &EnumerateLocations_result) = 0 ;
	virtual HRESULT __safecall Get_Locations(OleVariant &Get_Locations_result) = 0 ;
	virtual HRESULT __safecall EnumerateCallingCards(_di_IEnumCallingCard &EnumerateCallingCards_result
		) = 0 ;
	virtual HRESULT __safecall Get_CallingCards(OleVariant &Get_CallingCards_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_Locations() { OleVariant r; HRESULT hr = Get_Locations(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant Locations = {read=_scw_Get_Locations};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_CallingCards() { OleVariant r; HRESULT hr = Get_CallingCards(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant CallingCards = {read=_scw_Get_CallingCards};
};

__dispinterface ITAddressTranslationDisp;
typedef System::DelphiInterface<ITAddressTranslationDisp> _di_ITAddressTranslationDisp;
__dispinterface INTERFACE_UUID("{0C4D8F03-8DDB-11D1-A09E-00805FC147D3}") ITAddressTranslationDisp  : public IDispatch 
	
{
	
};

__interface INTERFACE_UUID("{AFC15945-8D40-11D1-A09E-00805FC147D3}") ITAddressTranslationInfo  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_DialableString(WideString &Get_DialableString_result) = 0 ;
	virtual HRESULT __safecall Get_DisplayableString(WideString &Get_DisplayableString_result) = 0 ;
	virtual HRESULT __safecall Get_CurrentCountryCode(int &Get_CurrentCountryCode_result) = 0 ;
	virtual HRESULT __safecall Get_DestinationCountryCode(int &Get_DestinationCountryCode_result) = 0 ;
		
	virtual HRESULT __safecall Get_TranslationResults(int &Get_TranslationResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_DialableString() { WideString r; HRESULT hr = Get_DialableString(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString DialableString = {read=_scw_Get_DialableString};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_DisplayableString() { WideString r; HRESULT hr = Get_DisplayableString(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString DisplayableString = {read=_scw_Get_DisplayableString};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CurrentCountryCode() { int r; HRESULT hr = Get_CurrentCountryCode(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int CurrentCountryCode = {read=_scw_Get_CurrentCountryCode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_DestinationCountryCode() { int r; HRESULT hr = Get_DestinationCountryCode(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int DestinationCountryCode = {read=_scw_Get_DestinationCountryCode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_TranslationResults() { int r; HRESULT hr = Get_TranslationResults(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int TranslationResults = {read=_scw_Get_TranslationResults};
};

__dispinterface ITAddressTranslationInfoDisp;
typedef System::DelphiInterface<ITAddressTranslationInfoDisp> _di_ITAddressTranslationInfoDisp;
__dispinterface INTERFACE_UUID("{AFC15945-8D40-11D1-A09E-00805FC147D3}") ITAddressTranslationInfoDisp 
	 : public IDispatch 
{
	
};

__interface ITLocationInfo;
typedef System::DelphiInterface<ITLocationInfo> _di_ITLocationInfo;
__interface INTERFACE_UUID("{0C4D8F01-8DDB-11D1-A09E-00805FC147D3}") IEnumLocation  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ _di_ITLocationInfo &ppElements, unsigned &pceltFetched
		) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumLocation &ppEnum) = 0 ;
};

__interface INTERFACE_UUID("{0C4D8EFF-8DDB-11D1-A09E-00805FC147D3}") ITLocationInfo  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_PermanentLocationID(int &Get_PermanentLocationID_result) = 0 ;
	virtual HRESULT __safecall Get_CountryCode(int &Get_CountryCode_result) = 0 ;
	virtual HRESULT __safecall Get_CountryID(int &Get_CountryID_result) = 0 ;
	virtual HRESULT __safecall Get_Options(int &Get_Options_result) = 0 ;
	virtual HRESULT __safecall Get_PreferredCardID(int &Get_PreferredCardID_result) = 0 ;
	virtual HRESULT __safecall Get_LocationName(WideString &Get_LocationName_result) = 0 ;
	virtual HRESULT __safecall Get_CityCode(WideString &Get_CityCode_result) = 0 ;
	virtual HRESULT __safecall Get_LocalAccessCode(WideString &Get_LocalAccessCode_result) = 0 ;
	virtual HRESULT __safecall Get_LongDistanceAccessCode(WideString &Get_LongDistanceAccessCode_result
		) = 0 ;
	virtual HRESULT __safecall Get_TollPrefixList(WideString &Get_TollPrefixList_result) = 0 ;
	virtual HRESULT __safecall Get_CancelCallWaitingCode(WideString &Get_CancelCallWaitingCode_result) = 0 
		;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_PermanentLocationID() { int r; HRESULT hr = Get_PermanentLocationID(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int PermanentLocationID = {read=_scw_Get_PermanentLocationID};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CountryCode() { int r; HRESULT hr = Get_CountryCode(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property int CountryCode = {read=_scw_Get_CountryCode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CountryID() { int r; HRESULT hr = Get_CountryID(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property int CountryID = {read=_scw_Get_CountryID};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Options() { int r; HRESULT hr = Get_Options(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property int Options = {read=_scw_Get_Options};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_PreferredCardID() { int r; HRESULT hr = Get_PreferredCardID(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int PreferredCardID = {read=_scw_Get_PreferredCardID};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_LocationName() { WideString r; HRESULT hr = Get_LocationName(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString LocationName = {read=_scw_Get_LocationName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_CityCode() { WideString r; HRESULT hr = Get_CityCode(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString CityCode = {read=_scw_Get_CityCode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_LocalAccessCode() { WideString r; HRESULT hr = Get_LocalAccessCode(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString LocalAccessCode = {read=_scw_Get_LocalAccessCode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_LongDistanceAccessCode() { WideString r; HRESULT hr = Get_LongDistanceAccessCode(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString LongDistanceAccessCode = {read=_scw_Get_LongDistanceAccessCode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_TollPrefixList() { WideString r; HRESULT hr = Get_TollPrefixList(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString TollPrefixList = {read=_scw_Get_TollPrefixList};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_CancelCallWaitingCode() { WideString r; HRESULT hr = Get_CancelCallWaitingCode(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString CancelCallWaitingCode = {read=_scw_Get_CancelCallWaitingCode};
};

__dispinterface ITLocationInfoDisp;
typedef System::DelphiInterface<ITLocationInfoDisp> _di_ITLocationInfoDisp;
__dispinterface INTERFACE_UUID("{0C4D8EFF-8DDB-11D1-A09E-00805FC147D3}") ITLocationInfoDisp  : public IDispatch 
	
{
	
};

__interface ITCallingCard;
typedef System::DelphiInterface<ITCallingCard> _di_ITCallingCard;
__interface INTERFACE_UUID("{0C4D8F02-8DDB-11D1-A09E-00805FC147D3}") IEnumCallingCard  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ _di_ITCallingCard &ppElements, unsigned &pceltFetched
		) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumCallingCard &ppEnum) = 0 ;
};

__interface INTERFACE_UUID("{0C4D8F00-8DDB-11D1-A09E-00805FC147D3}") ITCallingCard  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_PermanentCardID(int &Get_PermanentCardID_result) = 0 ;
	virtual HRESULT __safecall Get_NumberOfDigits(int &Get_NumberOfDigits_result) = 0 ;
	virtual HRESULT __safecall Get_Options(int &Get_Options_result) = 0 ;
	virtual HRESULT __safecall Get_CardName(WideString &Get_CardName_result) = 0 ;
	virtual HRESULT __safecall Get_SameAreaDialingRule(WideString &Get_SameAreaDialingRule_result) = 0 
		;
	virtual HRESULT __safecall Get_LongDistanceDialingRule(WideString &Get_LongDistanceDialingRule_result
		) = 0 ;
	virtual HRESULT __safecall Get_InternationalDialingRule(WideString &Get_InternationalDialingRule_result
		) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_PermanentCardID() { int r; HRESULT hr = Get_PermanentCardID(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int PermanentCardID = {read=_scw_Get_PermanentCardID};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_NumberOfDigits() { int r; HRESULT hr = Get_NumberOfDigits(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int NumberOfDigits = {read=_scw_Get_NumberOfDigits};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Options() { int r; HRESULT hr = Get_Options(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property int Options = {read=_scw_Get_Options};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_CardName() { WideString r; HRESULT hr = Get_CardName(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString CardName = {read=_scw_Get_CardName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_SameAreaDialingRule() { WideString r; HRESULT hr = Get_SameAreaDialingRule(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString SameAreaDialingRule = {read=_scw_Get_SameAreaDialingRule};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_LongDistanceDialingRule() { WideString r; HRESULT hr = Get_LongDistanceDialingRule(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString LongDistanceDialingRule = {read=_scw_Get_LongDistanceDialingRule};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_InternationalDialingRule() { WideString r; HRESULT hr = Get_InternationalDialingRule(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property WideString InternationalDialingRule = {read=_scw_Get_InternationalDialingRule};
};

__dispinterface ITCallingCardDisp;
typedef System::DelphiInterface<ITCallingCardDisp> _di_ITCallingCardDisp;
__dispinterface INTERFACE_UUID("{0C4D8F00-8DDB-11D1-A09E-00805FC147D3}") ITCallingCardDisp  : public IDispatch 
	
{
	
};

__interface ITAgent;
typedef System::DelphiInterface<ITAgent> _di_ITAgent;
__interface IEnumAgentSession;
typedef System::DelphiInterface<IEnumAgentSession> _di_IEnumAgentSession;
__interface ITAgentSession;
typedef System::DelphiInterface<ITAgentSession> _di_ITAgentSession;
__interface ITACDGroup;
typedef System::DelphiInterface<ITACDGroup> _di_ITACDGroup;
__interface INTERFACE_UUID("{5770ECE5-4B27-11D1-BF80-00805FC147D3}") ITAgent  : public IDispatch 
{
	
public:
	virtual HRESULT __safecall EnumerateAgentSessions(_di_IEnumAgentSession &EnumerateAgentSessions_result
		) = 0 ;
	virtual HRESULT __safecall CreateSession(const _di_ITACDGroup pACDGroup, const _di_ITAddress pAddress
		, _di_ITAgentSession &CreateSession_result) = 0 ;
	virtual HRESULT __safecall CreateSessionWithPIN(const _di_ITACDGroup pACDGroup, const _di_ITAddress 
		pAddress, const WideString pPIN, _di_ITAgentSession &CreateSessionWithPIN_result) = 0 ;
	virtual HRESULT __safecall Get_ID(WideString &Get_ID_result) = 0 ;
	virtual HRESULT __safecall Get_User(WideString &Get_User_result) = 0 ;
	virtual HRESULT __safecall Set_State(Activex::TOleEnum pAgentState) = 0 ;
	virtual HRESULT __safecall Get_State(Activex::TOleEnum &Get_State_result) = 0 ;
	virtual HRESULT __safecall Set_MeasurementPeriod(int plPeriod) = 0 ;
	virtual HRESULT __safecall Get_MeasurementPeriod(int &Get_MeasurementPeriod_result) = 0 ;
	virtual HRESULT __safecall Get_OverallCallRate(System::Currency &Get_OverallCallRate_result) = 0 ;
	virtual HRESULT __safecall Get_NumberOfACDCalls(int &Get_NumberOfACDCalls_result) = 0 ;
	virtual HRESULT __safecall Get_NumberOfIncomingCalls(int &Get_NumberOfIncomingCalls_result) = 0 ;
	virtual HRESULT __safecall Get_NumberOfOutgoingCalls(int &Get_NumberOfOutgoingCalls_result) = 0 ;
	virtual HRESULT __safecall Get_TotalACDTalkTime(int &Get_TotalACDTalkTime_result) = 0 ;
	virtual HRESULT __safecall Get_TotalACDCallTime(int &Get_TotalACDCallTime_result) = 0 ;
	virtual HRESULT __safecall Get_TotalWrapUpTime(int &Get_TotalWrapUpTime_result) = 0 ;
	virtual HRESULT __safecall Get_AgentSessions(OleVariant &Get_AgentSessions_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_ID() { WideString r; HRESULT hr = Get_ID(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property WideString ID = {read=_scw_Get_ID};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_User() { WideString r; HRESULT hr = Get_User(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property WideString User = {read=_scw_Get_User};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_State() { Activex::TOleEnum r; HRESULT hr = Get_State(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum State = {read=_scw_Get_State, write=Set_State};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MeasurementPeriod() { int r; HRESULT hr = Get_MeasurementPeriod(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MeasurementPeriod = {read=_scw_Get_MeasurementPeriod, write=Set_MeasurementPeriod};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Currency _scw_Get_OverallCallRate() { System::Currency r; HRESULT hr = Get_OverallCallRate(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property System::Currency OverallCallRate = {read=_scw_Get_OverallCallRate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_NumberOfACDCalls() { int r; HRESULT hr = Get_NumberOfACDCalls(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int NumberOfACDCalls = {read=_scw_Get_NumberOfACDCalls};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_NumberOfIncomingCalls() { int r; HRESULT hr = Get_NumberOfIncomingCalls(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int NumberOfIncomingCalls = {read=_scw_Get_NumberOfIncomingCalls};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_NumberOfOutgoingCalls() { int r; HRESULT hr = Get_NumberOfOutgoingCalls(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int NumberOfOutgoingCalls = {read=_scw_Get_NumberOfOutgoingCalls};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_TotalACDTalkTime() { int r; HRESULT hr = Get_TotalACDTalkTime(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int TotalACDTalkTime = {read=_scw_Get_TotalACDTalkTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_TotalACDCallTime() { int r; HRESULT hr = Get_TotalACDCallTime(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int TotalACDCallTime = {read=_scw_Get_TotalACDCallTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_TotalWrapUpTime() { int r; HRESULT hr = Get_TotalWrapUpTime(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int TotalWrapUpTime = {read=_scw_Get_TotalWrapUpTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_AgentSessions() { OleVariant r; HRESULT hr = Get_AgentSessions(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant AgentSessions = {read=_scw_Get_AgentSessions};
};

__dispinterface ITAgentDisp;
typedef System::DelphiInterface<ITAgentDisp> _di_ITAgentDisp;
__dispinterface INTERFACE_UUID("{5770ECE5-4B27-11D1-BF80-00805FC147D3}") ITAgentDisp  : public IDispatch 
	
{
	
};

__interface INTERFACE_UUID("{5AFC314E-4BCC-11D1-BF80-00805FC147D3}") IEnumAgentSession  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ _di_ITAgentSession &ppElements, /* out */ unsigned 
		&pceltFetched) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumAgentSession &ppEnum) = 0 ;
};

__interface INTERFACE_UUID("{5AFC3147-4BCC-11D1-BF80-00805FC147D3}") ITAgentSession  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Agent(_di_ITAgent &Get_Agent_result) = 0 ;
	virtual HRESULT __safecall Get_Address(_di_ITAddress &Get_Address_result) = 0 ;
	virtual HRESULT __safecall Get_ACDGroup(_di_ITACDGroup &Get_ACDGroup_result) = 0 ;
	virtual HRESULT __safecall Set_State(Activex::TOleEnum pSessionState) = 0 ;
	virtual HRESULT __safecall Get_State(Activex::TOleEnum &Get_State_result) = 0 ;
	virtual HRESULT __safecall Get_SessionStartTime(System::TDateTime &Get_SessionStartTime_result) = 0 
		;
	virtual HRESULT __safecall Get_SessionDuration(int &Get_SessionDuration_result) = 0 ;
	virtual HRESULT __safecall Get_NumberOfCalls(int &Get_NumberOfCalls_result) = 0 ;
	virtual HRESULT __safecall Get_TotalTalkTime(int &Get_TotalTalkTime_result) = 0 ;
	virtual HRESULT __safecall Get_AverageTalkTime(int &Get_AverageTalkTime_result) = 0 ;
	virtual HRESULT __safecall Get_TotalCallTime(int &Get_TotalCallTime_result) = 0 ;
	virtual HRESULT __safecall Get_AverageCallTime(int &Get_AverageCallTime_result) = 0 ;
	virtual HRESULT __safecall Get_TotalWrapUpTime(int &Get_TotalWrapUpTime_result) = 0 ;
	virtual HRESULT __safecall Get_AverageWrapUpTime(int &Get_AverageWrapUpTime_result) = 0 ;
	virtual HRESULT __safecall Get_ACDCallRate(System::Currency &Get_ACDCallRate_result) = 0 ;
	virtual HRESULT __safecall Get_LongestTimeToAnswer(int &Get_LongestTimeToAnswer_result) = 0 ;
	virtual HRESULT __safecall Get_AverageTimeToAnswer(int &Get_AverageTimeToAnswer_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITAgent _scw_Get_Agent() { _di_ITAgent r; HRESULT hr = Get_Agent(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITAgent Agent = {read=_scw_Get_Agent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITAddress _scw_Get_Address() { _di_ITAddress r; HRESULT hr = Get_Address(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITAddress Address = {read=_scw_Get_Address};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITACDGroup _scw_Get_ACDGroup() { _di_ITACDGroup r; HRESULT hr = Get_ACDGroup(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITACDGroup ACDGroup = {read=_scw_Get_ACDGroup};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_State() { Activex::TOleEnum r; HRESULT hr = Get_State(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum State = {read=_scw_Get_State, write=Set_State};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::TDateTime _scw_Get_SessionStartTime() { System::TDateTime r; HRESULT hr = Get_SessionStartTime(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property System::TDateTime SessionStartTime = {read=_scw_Get_SessionStartTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_SessionDuration() { int r; HRESULT hr = Get_SessionDuration(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int SessionDuration = {read=_scw_Get_SessionDuration};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_NumberOfCalls() { int r; HRESULT hr = Get_NumberOfCalls(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int NumberOfCalls = {read=_scw_Get_NumberOfCalls};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_TotalTalkTime() { int r; HRESULT hr = Get_TotalTalkTime(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int TotalTalkTime = {read=_scw_Get_TotalTalkTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_AverageTalkTime() { int r; HRESULT hr = Get_AverageTalkTime(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int AverageTalkTime = {read=_scw_Get_AverageTalkTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_TotalCallTime() { int r; HRESULT hr = Get_TotalCallTime(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int TotalCallTime = {read=_scw_Get_TotalCallTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_AverageCallTime() { int r; HRESULT hr = Get_AverageCallTime(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int AverageCallTime = {read=_scw_Get_AverageCallTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_TotalWrapUpTime() { int r; HRESULT hr = Get_TotalWrapUpTime(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int TotalWrapUpTime = {read=_scw_Get_TotalWrapUpTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_AverageWrapUpTime() { int r; HRESULT hr = Get_AverageWrapUpTime(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int AverageWrapUpTime = {read=_scw_Get_AverageWrapUpTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Currency _scw_Get_ACDCallRate() { System::Currency r; HRESULT hr = Get_ACDCallRate(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property System::Currency ACDCallRate = {read=_scw_Get_ACDCallRate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_LongestTimeToAnswer() { int r; HRESULT hr = Get_LongestTimeToAnswer(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int LongestTimeToAnswer = {read=_scw_Get_LongestTimeToAnswer};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_AverageTimeToAnswer() { int r; HRESULT hr = Get_AverageTimeToAnswer(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int AverageTimeToAnswer = {read=_scw_Get_AverageTimeToAnswer};
};

__dispinterface ITAgentSessionDisp;
typedef System::DelphiInterface<ITAgentSessionDisp> _di_ITAgentSessionDisp;
__dispinterface INTERFACE_UUID("{5AFC3147-4BCC-11D1-BF80-00805FC147D3}") ITAgentSessionDisp  : public IDispatch 
	
{
	
};

__interface IEnumQueue;
typedef System::DelphiInterface<IEnumQueue> _di_IEnumQueue;
__interface INTERFACE_UUID("{5AFC3148-4BCC-11D1-BF80-00805FC147D3}") ITACDGroup  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Name(WideString &Get_Name_result) = 0 ;
	virtual HRESULT __safecall EnumerateQueues(_di_IEnumQueue &EnumerateQueues_result) = 0 ;
	virtual HRESULT __safecall Get_Queues(OleVariant &Get_Queues_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_Name() { WideString r; HRESULT hr = Get_Name(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property WideString Name = {read=_scw_Get_Name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_Queues() { OleVariant r; HRESULT hr = Get_Queues(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant Queues = {read=_scw_Get_Queues};
};

__dispinterface ITACDGroupDisp;
typedef System::DelphiInterface<ITACDGroupDisp> _di_ITACDGroupDisp;
__dispinterface INTERFACE_UUID("{5AFC3148-4BCC-11D1-BF80-00805FC147D3}") ITACDGroupDisp  : public IDispatch 
	
{
	
};

__interface ITQueue;
typedef System::DelphiInterface<ITQueue> _di_ITQueue;
__interface INTERFACE_UUID("{5AFC3158-4BCC-11D1-BF80-00805FC147D3}") IEnumQueue  : public IUnknown 
{
	
public:
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ _di_ITQueue &ppElements, /* out */ unsigned 
		&pceltFetched) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumQueue &ppEnum) = 0 ;
};

__interface INTERFACE_UUID("{5AFC3149-4BCC-11D1-BF80-00805FC147D3}") ITQueue  : public IDispatch 
{
	
public:
	virtual HRESULT __safecall Set_MeasurementPeriod(int plPeriod) = 0 ;
	virtual HRESULT __safecall Get_MeasurementPeriod(int &Get_MeasurementPeriod_result) = 0 ;
	virtual HRESULT __safecall Get_TotalCallsQueued(int &Get_TotalCallsQueued_result) = 0 ;
	virtual HRESULT __safecall Get_CurrentCallsQueued(int &Get_CurrentCallsQueued_result) = 0 ;
	virtual HRESULT __safecall Get_TotalCallsAbandoned(int &Get_TotalCallsAbandoned_result) = 0 ;
	virtual HRESULT __safecall Get_TotalCallsFlowedIn(int &Get_TotalCallsFlowedIn_result) = 0 ;
	virtual HRESULT __safecall Get_TotalCallsFlowedOut(int &Get_TotalCallsFlowedOut_result) = 0 ;
	virtual HRESULT __safecall Get_LongestEverWaitTime(int &Get_LongestEverWaitTime_result) = 0 ;
	virtual HRESULT __safecall Get_CurrentLongestWaitTime(int &Get_CurrentLongestWaitTime_result) = 0 ;
		
	virtual HRESULT __safecall Get_AverageWaitTime(int &Get_AverageWaitTime_result) = 0 ;
	virtual HRESULT __safecall Get_FinalDisposition(int &Get_FinalDisposition_result) = 0 ;
	virtual HRESULT __safecall Get_Name(WideString &Get_Name_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MeasurementPeriod() { int r; HRESULT hr = Get_MeasurementPeriod(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int MeasurementPeriod = {read=_scw_Get_MeasurementPeriod, write=Set_MeasurementPeriod};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_TotalCallsQueued() { int r; HRESULT hr = Get_TotalCallsQueued(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int TotalCallsQueued = {read=_scw_Get_TotalCallsQueued};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CurrentCallsQueued() { int r; HRESULT hr = Get_CurrentCallsQueued(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int CurrentCallsQueued = {read=_scw_Get_CurrentCallsQueued};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_TotalCallsAbandoned() { int r; HRESULT hr = Get_TotalCallsAbandoned(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int TotalCallsAbandoned = {read=_scw_Get_TotalCallsAbandoned};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_TotalCallsFlowedIn() { int r; HRESULT hr = Get_TotalCallsFlowedIn(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int TotalCallsFlowedIn = {read=_scw_Get_TotalCallsFlowedIn};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_TotalCallsFlowedOut() { int r; HRESULT hr = Get_TotalCallsFlowedOut(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int TotalCallsFlowedOut = {read=_scw_Get_TotalCallsFlowedOut};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_LongestEverWaitTime() { int r; HRESULT hr = Get_LongestEverWaitTime(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int LongestEverWaitTime = {read=_scw_Get_LongestEverWaitTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CurrentLongestWaitTime() { int r; HRESULT hr = Get_CurrentLongestWaitTime(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int CurrentLongestWaitTime = {read=_scw_Get_CurrentLongestWaitTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_AverageWaitTime() { int r; HRESULT hr = Get_AverageWaitTime(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int AverageWaitTime = {read=_scw_Get_AverageWaitTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_FinalDisposition() { int r; HRESULT hr = Get_FinalDisposition(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int FinalDisposition = {read=_scw_Get_FinalDisposition};
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_Name() { WideString r; HRESULT hr = Get_Name(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property WideString Name = {read=_scw_Get_Name};
};

__dispinterface ITQueueDisp;
typedef System::DelphiInterface<ITQueueDisp> _di_ITQueueDisp;
__dispinterface INTERFACE_UUID("{5AFC3149-4BCC-11D1-BF80-00805FC147D3}") ITQueueDisp  : public IDispatch 
	
{
	
};

__interface ITAgentEvent;
typedef System::DelphiInterface<ITAgentEvent> _di_ITAgentEvent;
__interface INTERFACE_UUID("{5AFC314A-4BCC-11D1-BF80-00805FC147D3}") ITAgentEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Agent(_di_ITAgent &Get_Agent_result) = 0 ;
	virtual HRESULT __safecall Get_Event(Activex::TOleEnum &Get_Event_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITAgent _scw_Get_Agent() { _di_ITAgent r; HRESULT hr = Get_Agent(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITAgent Agent = {read=_scw_Get_Agent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_Event() { Activex::TOleEnum r; HRESULT hr = Get_Event(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum Event = {read=_scw_Get_Event};
};

__dispinterface ITAgentEventDisp;
typedef System::DelphiInterface<ITAgentEventDisp> _di_ITAgentEventDisp;
__dispinterface INTERFACE_UUID("{5AFC314A-4BCC-11D1-BF80-00805FC147D3}") ITAgentEventDisp  : public IDispatch 
	
{
	
};

__interface ITAgentSessionEvent;
typedef System::DelphiInterface<ITAgentSessionEvent> _di_ITAgentSessionEvent;
__interface INTERFACE_UUID("{5AFC314B-4BCC-11D1-BF80-00805FC147D3}") ITAgentSessionEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Session(_di_ITAgentSession &Get_Session_result) = 0 ;
	virtual HRESULT __safecall Get_Event(Activex::TOleEnum &Get_Event_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITAgentSession _scw_Get_Session() { _di_ITAgentSession r; HRESULT hr = Get_Session(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITAgentSession Session = {read=_scw_Get_Session};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_Event() { Activex::TOleEnum r; HRESULT hr = Get_Event(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum Event = {read=_scw_Get_Event};
};

__dispinterface ITAgentSessionEventDisp;
typedef System::DelphiInterface<ITAgentSessionEventDisp> _di_ITAgentSessionEventDisp;
__dispinterface INTERFACE_UUID("{5AFC314B-4BCC-11D1-BF80-00805FC147D3}") ITAgentSessionEventDisp  : public IDispatch 
	
{
	
};

__interface ITACDGroupEvent;
typedef System::DelphiInterface<ITACDGroupEvent> _di_ITACDGroupEvent;
__interface INTERFACE_UUID("{297F3032-BD11-11D1-A0A7-00805FC147D3}") ITACDGroupEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Group(_di_ITACDGroup &Get_Group_result) = 0 ;
	virtual HRESULT __safecall Get_Event(Activex::TOleEnum &Get_Event_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITACDGroup _scw_Get_Group() { _di_ITACDGroup r; HRESULT hr = Get_Group(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITACDGroup Group = {read=_scw_Get_Group};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_Event() { Activex::TOleEnum r; HRESULT hr = Get_Event(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum Event = {read=_scw_Get_Event};
};

__dispinterface ITACDGroupEventDisp;
typedef System::DelphiInterface<ITACDGroupEventDisp> _di_ITACDGroupEventDisp;
__dispinterface INTERFACE_UUID("{297F3032-BD11-11D1-A0A7-00805FC147D3}") ITACDGroupEventDisp  : public IDispatch 
	
{
	
};

__interface ITQueueEvent;
typedef System::DelphiInterface<ITQueueEvent> _di_ITQueueEvent;
__interface INTERFACE_UUID("{297F3033-BD11-11D1-A0A7-00805FC147D3}") ITQueueEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Queue(_di_ITQueue &Get_Queue_result) = 0 ;
	virtual HRESULT __safecall Get_Event(Activex::TOleEnum &Get_Event_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITQueue _scw_Get_Queue() { _di_ITQueue r; HRESULT hr = Get_Queue(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITQueue Queue = {read=_scw_Get_Queue};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_Event() { Activex::TOleEnum r; HRESULT hr = Get_Event(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum Event = {read=_scw_Get_Event};
};

__dispinterface ITQueueEventDisp;
typedef System::DelphiInterface<ITQueueEventDisp> _di_ITQueueEventDisp;
__dispinterface INTERFACE_UUID("{297F3033-BD11-11D1-A0A7-00805FC147D3}") ITQueueEventDisp  : public IDispatch 
	
{
	
};

__interface ITTAPICallCenter;
typedef System::DelphiInterface<ITTAPICallCenter> _di_ITTAPICallCenter;
__interface IEnumAgentHandler;
typedef System::DelphiInterface<IEnumAgentHandler> _di_IEnumAgentHandler;
__interface INTERFACE_UUID("{5AFC3154-4BCC-11D1-BF80-00805FC147D3}") ITTAPICallCenter  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall EnumerateAgentHandlers(_di_IEnumAgentHandler &EnumerateAgentHandlers_result
		) = 0 ;
	virtual HRESULT __safecall Get_AgentHandlers(OleVariant &Get_AgentHandlers_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_AgentHandlers() { OleVariant r; HRESULT hr = Get_AgentHandlers(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant AgentHandlers = {read=_scw_Get_AgentHandlers};
};

__dispinterface ITTAPICallCenterDisp;
typedef System::DelphiInterface<ITTAPICallCenterDisp> _di_ITTAPICallCenterDisp;
__dispinterface INTERFACE_UUID("{5AFC3154-4BCC-11D1-BF80-00805FC147D3}") ITTAPICallCenterDisp  : public IDispatch 
	
{
	
};

__interface ITAgentHandler;
typedef System::DelphiInterface<ITAgentHandler> _di_ITAgentHandler;
__interface INTERFACE_UUID("{587E8C28-9802-11D1-A0A4-00805FC147D3}") IEnumAgentHandler  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ _di_ITAgentHandler &ppElements, /* out */ unsigned 
		&pceltFetched) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumAgentHandler &ppEnum) = 0 ;
};

__interface IEnumACDGroup;
typedef System::DelphiInterface<IEnumACDGroup> _di_IEnumACDGroup;
__interface INTERFACE_UUID("{587E8C22-9802-11D1-A0A4-00805FC147D3}") ITAgentHandler  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Name(WideString &Get_Name_result) = 0 ;
	virtual HRESULT __safecall CreateAgent(_di_ITAgent &CreateAgent_result) = 0 ;
	virtual HRESULT __safecall CreateAgentWithID(const WideString pID, const WideString pPIN, _di_ITAgent &CreateAgentWithID_result
		) = 0 ;
	virtual HRESULT __safecall EnumerateACDGroups(_di_IEnumACDGroup &EnumerateACDGroups_result) = 0 ;
	virtual HRESULT __safecall EnumerateUsableAddresses(_di_IEnumAddress &EnumerateUsableAddresses_result
		) = 0 ;
	virtual HRESULT __safecall Get_ACDGroups(OleVariant &Get_ACDGroups_result) = 0 ;
	virtual HRESULT __safecall Get_UsableAddresses(OleVariant &Get_UsableAddresses_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline WideString _scw_Get_Name() { WideString r; HRESULT hr = Get_Name(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property WideString Name = {read=_scw_Get_Name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_ACDGroups() { OleVariant r; HRESULT hr = Get_ACDGroups(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant ACDGroups = {read=_scw_Get_ACDGroups};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_UsableAddresses() { OleVariant r; HRESULT hr = Get_UsableAddresses(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant UsableAddresses = {read=_scw_Get_UsableAddresses};
};

__dispinterface ITAgentHandlerDisp;
typedef System::DelphiInterface<ITAgentHandlerDisp> _di_ITAgentHandlerDisp;
__dispinterface INTERFACE_UUID("{587E8C22-9802-11D1-A0A4-00805FC147D3}") ITAgentHandlerDisp  : public IDispatch 
	
{
	
};

__interface INTERFACE_UUID("{5AFC3157-4BCC-11D1-BF80-00805FC147D3}") IEnumACDGroup  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ _di_ITACDGroup &ppElements, /* out */ unsigned 
		&pceltFetched) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumACDGroup &ppEnum) = 0 ;
};

__interface ITAgentHandlerEvent;
typedef System::DelphiInterface<ITAgentHandlerEvent> _di_ITAgentHandlerEvent;
__interface INTERFACE_UUID("{297F3034-BD11-11D1-A0A7-00805FC147D3}") ITAgentHandlerEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_AgentHandler(_di_ITAgentHandler &Get_AgentHandler_result) = 0 ;
	virtual HRESULT __safecall Get_Event(Activex::TOleEnum &Get_Event_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITAgentHandler _scw_Get_AgentHandler() { _di_ITAgentHandler r; HRESULT hr = Get_AgentHandler(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITAgentHandler AgentHandler = {read=_scw_Get_AgentHandler};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Activex::TOleEnum _scw_Get_Event() { Activex::TOleEnum r; HRESULT hr = Get_Event(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property Activex::TOleEnum Event = {read=_scw_Get_Event};
};

__dispinterface ITAgentHandlerEventDisp;
typedef System::DelphiInterface<ITAgentHandlerEventDisp> _di_ITAgentHandlerEventDisp;
__dispinterface INTERFACE_UUID("{297F3034-BD11-11D1-A0A7-00805FC147D3}") ITAgentHandlerEventDisp  : public IDispatch 
	
{
	
};

__interface ITCallInfoChangeEvent;
typedef System::DelphiInterface<ITCallInfoChangeEvent> _di_ITCallInfoChangeEvent;
__interface INTERFACE_UUID("{5D4B65F9-E51C-11D1-A02F-00C04FB6809F}") ITCallInfoChangeEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __stdcall Get_Call(/* out */ _di_ITCallInfo &ppCall) = 0 ;
	virtual HRESULT __stdcall Get_Cause(/* out */ Activex::TOleEnum &pCIC) = 0 ;
	virtual HRESULT __stdcall Get_CallbackInstance(/* out */ int &plCallbackInstance) = 0 ;
};

__interface ITRequestEvent;
typedef System::DelphiInterface<ITRequestEvent> _di_ITRequestEvent;
__interface INTERFACE_UUID("{AC48FFDE-F8C4-11D1-A030-00C04FB6809F}") ITRequestEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __stdcall Get_RegistrationInstance(/* out */ int &plRegistrationInstance) = 0 ;
	virtual HRESULT __stdcall Get_RequestMode(/* out */ int &plRequestMode) = 0 ;
	virtual HRESULT __stdcall Get_DestAddress(/* out */ WideString &ppDestAddress) = 0 ;
	virtual HRESULT __stdcall Get_AppName(/* out */ WideString &ppAppName) = 0 ;
	virtual HRESULT __stdcall Get_CalledParty(/* out */ WideString &ppCalledParty) = 0 ;
	virtual HRESULT __stdcall Get_Comment(/* out */ WideString &ppComment) = 0 ;
};

__interface ITMediaSupport;
typedef System::DelphiInterface<ITMediaSupport> _di_ITMediaSupport;
__interface INTERFACE_UUID("{B1EFC384-9355-11D0-835C-00AA003CCABD}") ITMediaSupport  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_MediaTypes(int &Get_MediaTypes_result) = 0 ;
	virtual HRESULT __safecall QueryMediaType(int lMediaType, Word &QueryMediaType_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MediaTypes() { int r; HRESULT hr = Get_MediaTypes(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property int MediaTypes = {read=_scw_Get_MediaTypes};
};

__dispinterface ITMediaSupportDisp;
typedef System::DelphiInterface<ITMediaSupportDisp> _di_ITMediaSupportDisp;
__dispinterface INTERFACE_UUID("{B1EFC384-9355-11D0-835C-00AA003CCABD}") ITMediaSupportDisp  : public IDispatch 
	
{
	
};

__interface ITTerminalSupport;
typedef System::DelphiInterface<ITTerminalSupport> _di_ITTerminalSupport;
__interface IEnumTerminalClass;
typedef System::DelphiInterface<IEnumTerminalClass> _di_IEnumTerminalClass;
__interface INTERFACE_UUID("{B1EFC385-9355-11D0-835C-00AA003CCABD}") ITTerminalSupport  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_StaticTerminals(OleVariant &Get_StaticTerminals_result) = 0 ;
	virtual HRESULT __safecall EnumerateStaticTerminals(_di_IEnumTerminal &EnumerateStaticTerminals_result
		) = 0 ;
	virtual HRESULT __safecall Get_DynamicTerminalClasses(OleVariant &Get_DynamicTerminalClasses_result
		) = 0 ;
	virtual HRESULT __safecall EnumerateDynamicTerminalClasses(_di_IEnumTerminalClass &EnumerateDynamicTerminalClasses_result
		) = 0 ;
	virtual HRESULT __safecall CreateTerminal(const WideString pTerminalClass, int lMediaType, Activex::TOleEnum 
		Direction, _di_ITTerminal &CreateTerminal_result) = 0 ;
	virtual HRESULT __safecall GetDefaultStaticTerminal(int lMediaType, Activex::TOleEnum Direction, _di_ITTerminal &GetDefaultStaticTerminal_result
		) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_StaticTerminals() { OleVariant r; HRESULT hr = Get_StaticTerminals(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant StaticTerminals = {read=_scw_Get_StaticTerminals};
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_DynamicTerminalClasses() { OleVariant r; HRESULT hr = Get_DynamicTerminalClasses(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant DynamicTerminalClasses = {read=_scw_Get_DynamicTerminalClasses};
};

__dispinterface ITTerminalSupportDisp;
typedef System::DelphiInterface<ITTerminalSupportDisp> _di_ITTerminalSupportDisp;
__dispinterface INTERFACE_UUID("{B1EFC385-9355-11D0-835C-00AA003CCABD}") ITTerminalSupportDisp  : public IDispatch 
	
{
	
};

__interface INTERFACE_UUID("{AE269CF5-935E-11D0-835C-00AA003CCABD}") IEnumTerminalClass  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ GUID &pElements, unsigned &pceltFetched) = 0 
		;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumTerminalClass &ppEnum) = 0 ;
};

__interface ITStreamControl;
typedef System::DelphiInterface<ITStreamControl> _di_ITStreamControl;
__interface IEnumStream;
typedef System::DelphiInterface<IEnumStream> _di_IEnumStream;
__interface INTERFACE_UUID("{EE3BD604-3868-11D2-A045-00C04FB6809F}") ITStreamControl  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall CreateStream(int lMediaType, Activex::TOleEnum td, _di_ITStream &CreateStream_result
		) = 0 ;
	virtual HRESULT __safecall RemoveStream(const _di_ITStream pStream) = 0 ;
	virtual HRESULT __safecall EnumerateStreams(/* out */ _di_IEnumStream &ppEnumStream) = 0 ;
	virtual HRESULT __safecall Get_Streams(OleVariant &Get_Streams_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_Streams() { OleVariant r; HRESULT hr = Get_Streams(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant Streams = {read=_scw_Get_Streams};
};

__dispinterface ITStreamControlDisp;
typedef System::DelphiInterface<ITStreamControlDisp> _di_ITStreamControlDisp;
__dispinterface INTERFACE_UUID("{EE3BD604-3868-11D2-A045-00C04FB6809F}") ITStreamControlDisp  : public IDispatch 
	
{
	
};

__interface INTERFACE_UUID("{EE3BD606-3868-11D2-A045-00C04FB6809F}") IEnumStream  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ _di_ITStream &ppElements, unsigned &pceltFetched
		) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumStream &ppEnum) = 0 ;
};

__interface ITSubStreamControl;
typedef System::DelphiInterface<ITSubStreamControl> _di_ITSubStreamControl;
__interface ITSubStream;
typedef System::DelphiInterface<ITSubStream> _di_ITSubStream;
__interface IEnumSubStream;
typedef System::DelphiInterface<IEnumSubStream> _di_IEnumSubStream;
__interface INTERFACE_UUID("{EE3BD607-3868-11D2-A045-00C04FB6809F}") ITSubStreamControl  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall CreateSubStream(_di_ITSubStream &CreateSubStream_result) = 0 ;
	virtual HRESULT __safecall RemoveSubStream(const _di_ITSubStream pSubStream) = 0 ;
	virtual HRESULT __safecall EnumerateSubStreams(/* out */ _di_IEnumSubStream &ppEnumSubStream) = 0 ;
		
	virtual HRESULT __safecall Get_SubStreams(OleVariant &Get_SubStreams_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_SubStreams() { OleVariant r; HRESULT hr = Get_SubStreams(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant SubStreams = {read=_scw_Get_SubStreams};
};

__dispinterface ITSubStreamControlDisp;
typedef System::DelphiInterface<ITSubStreamControlDisp> _di_ITSubStreamControlDisp;
__dispinterface INTERFACE_UUID("{EE3BD607-3868-11D2-A045-00C04FB6809F}") ITSubStreamControlDisp  : public IDispatch 
	
{
	
};

__interface INTERFACE_UUID("{EE3BD608-3868-11D2-A045-00C04FB6809F}") ITSubStream  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall StartSubStream(void) = 0 ;
	virtual HRESULT __safecall PauseSubStream(void) = 0 ;
	virtual HRESULT __safecall StopSubStream(void) = 0 ;
	virtual HRESULT __safecall SelectTerminal(const _di_ITTerminal pTerminal) = 0 ;
	virtual HRESULT __safecall UnselectTerminal(const _di_ITTerminal pTerminal) = 0 ;
	virtual HRESULT __safecall EnumerateTerminals(/* out */ _di_IEnumTerminal &ppEnumTerminal) = 0 ;
	virtual HRESULT __safecall Get_Terminals(OleVariant &Get_Terminals_result) = 0 ;
	virtual HRESULT __safecall Get_Stream(_di_ITStream &Get_Stream_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline OleVariant _scw_Get_Terminals() { OleVariant r; HRESULT hr = Get_Terminals(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property OleVariant Terminals = {read=_scw_Get_Terminals};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITStream _scw_Get_Stream() { _di_ITStream r; HRESULT hr = Get_Stream(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITStream Stream = {read=_scw_Get_Stream};
};

__dispinterface ITSubStreamDisp;
typedef System::DelphiInterface<ITSubStreamDisp> _di_ITSubStreamDisp;
__dispinterface INTERFACE_UUID("{EE3BD608-3868-11D2-A045-00C04FB6809F}") ITSubStreamDisp  : public IDispatch 
	
{
	
};

__interface INTERFACE_UUID("{EE3BD609-3868-11D2-A045-00C04FB6809F}") IEnumSubStream  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ _di_ITSubStream &ppElements, unsigned &pceltFetched
		) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumSubStream &ppEnum) = 0 ;
};

__interface ITLegacyAddressMediaControl;
typedef System::DelphiInterface<ITLegacyAddressMediaControl> _di_ITLegacyAddressMediaControl;
__interface INTERFACE_UUID("{AB493640-4C0B-11D2-A046-00C04FB6809F}") ITLegacyAddressMediaControl  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall GetID(const WideString pDeviceClass, /* out */ unsigned &pdwSize, /* out */ 
		PByte1 &ppDeviceID) = 0 ;
	virtual HRESULT __stdcall GetDevConfig(const WideString pDeviceClass, /* out */ unsigned &pdwSize, 
		/* out */ PByte1 &ppDeviceConfig) = 0 ;
	virtual HRESULT __stdcall SetDevConfig(const WideString pDeviceClass, unsigned dwSize, Byte &pDeviceConfig
		) = 0 ;
};

__interface ITLegacyCallMediaControl;
typedef System::DelphiInterface<ITLegacyCallMediaControl> _di_ITLegacyCallMediaControl;
__interface INTERFACE_UUID("{D624582F-CC23-4436-B8A5-47C625C8045D}") ITLegacyCallMediaControl  : public IDispatch 
	
{
	
public:
	virtual HRESULT __stdcall DetectDigits(int DigitMode) = 0 ;
	virtual HRESULT __stdcall GenerateDigits(const WideString pDigits, int DigitMode) = 0 ;
	virtual HRESULT __stdcall GetID(const WideString pDeviceClass, /* out */ unsigned &pdwSize, /* out */ 
		PByte1 &ppDeviceID) = 0 ;
	virtual HRESULT __stdcall SetMediaType(int lMediaType) = 0 ;
	virtual HRESULT __stdcall MonitorMedia(int lMediaType) = 0 ;
};

__interface ITDigitDetectionEvent;
typedef System::DelphiInterface<ITDigitDetectionEvent> _di_ITDigitDetectionEvent;
__interface INTERFACE_UUID("{80D3BFAC-57D9-11D2-A04A-00C04FB6809F}") ITDigitDetectionEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __stdcall Get_Call(/* out */ _di_ITCallInfo &ppCallInfo) = 0 ;
	virtual HRESULT __stdcall Get_Digit(/* out */ Byte &pucDigit) = 0 ;
	virtual HRESULT __stdcall Get_DigitMode(/* out */ int &pDigitMode) = 0 ;
	virtual HRESULT __stdcall Get_TickCount(/* out */ int &plTickCount) = 0 ;
	virtual HRESULT __stdcall Get_CallbackInstance(/* out */ int &plCallbackInstance) = 0 ;
};

__interface ITDigitGenerationEvent;
typedef System::DelphiInterface<ITDigitGenerationEvent> _di_ITDigitGenerationEvent;
__interface INTERFACE_UUID("{80D3BFAD-57D9-11D2-A04A-00C04FB6809F}") ITDigitGenerationEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Call(_di_ITCallInfo &Get_Call_result) = 0 ;
	virtual HRESULT __safecall Get_GenerationTermination(int &Get_GenerationTermination_result) = 0 ;
	virtual HRESULT __safecall Get_TickCount(int &Get_TickCount_result) = 0 ;
	virtual HRESULT __safecall Get_CallbackInstance(int &Get_CallbackInstance_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITCallInfo _scw_Get_Call() { _di_ITCallInfo r; HRESULT hr = Get_Call(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITCallInfo Call = {read=_scw_Get_Call};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_GenerationTermination() { int r; HRESULT hr = Get_GenerationTermination(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int GenerationTermination = {read=_scw_Get_GenerationTermination};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_TickCount() { int r; HRESULT hr = Get_TickCount(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property int TickCount = {read=_scw_Get_TickCount};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CallbackInstance() { int r; HRESULT hr = Get_CallbackInstance(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property int CallbackInstance = {read=_scw_Get_CallbackInstance};
};

__dispinterface ITDigitGenerationEventDisp;
typedef System::DelphiInterface<ITDigitGenerationEventDisp> _di_ITDigitGenerationEventDisp;
__dispinterface INTERFACE_UUID("{80D3BFAD-57D9-11D2-A04A-00C04FB6809F}") ITDigitGenerationEventDisp 
	 : public IDispatch 
{
	
};

__interface ITPrivateEvent;
typedef System::DelphiInterface<ITPrivateEvent> _di_ITPrivateEvent;
__interface INTERFACE_UUID("{0E269CD0-10D4-4121-9C22-9C85D625650D}") ITPrivateEvent  : public IDispatch 
	
{
	
public:
	virtual HRESULT __safecall Get_Address(_di_ITAddress &Get_Address_result) = 0 ;
	virtual HRESULT __safecall Get_Call(_di_ITCallInfo &Get_Call_result) = 0 ;
	virtual HRESULT __safecall Get_CallHub(_di_ITCallHub &Get_CallHub_result) = 0 ;
	virtual HRESULT __safecall Get_EventCode(int &Get_EventCode_result) = 0 ;
	virtual HRESULT __safecall Get_EventInterface(_di_IDispatch &Get_EventInterface_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITAddress _scw_Get_Address() { _di_ITAddress r; HRESULT hr = Get_Address(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITAddress Address = {read=_scw_Get_Address};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITCallInfo _scw_Get_Call() { _di_ITCallInfo r; HRESULT hr = Get_Call(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITCallInfo Call = {read=_scw_Get_Call};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITCallHub _scw_Get_CallHub() { _di_ITCallHub r; HRESULT hr = Get_CallHub(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_ITCallHub CallHub = {read=_scw_Get_CallHub};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_EventCode() { int r; HRESULT hr = Get_EventCode(r); System::CheckSafecallResult(hr); return r; }
		
	#pragma option pop
	__property int EventCode = {read=_scw_Get_EventCode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDispatch _scw_Get_EventInterface() { _di_IDispatch r; HRESULT hr = Get_EventInterface(
		r); System::CheckSafecallResult(hr); return r; }
	#pragma option pop
	__property _di_IDispatch EventInterface = {read=_scw_Get_EventInterface};
};

__dispinterface ITPrivateEventDisp;
typedef System::DelphiInterface<ITPrivateEventDisp> _di_ITPrivateEventDisp;
__dispinterface INTERFACE_UUID("{0E269CD0-10D4-4121-9C22-9C85D625650D}") ITPrivateEventDisp  : public IDispatch 
	
{
	
};

__dispinterface ITTAPIDispatchEventNotification;
typedef System::DelphiInterface<ITTAPIDispatchEventNotification> _di_ITTAPIDispatchEventNotification;
	
__dispinterface INTERFACE_UUID("{9F34325B-7E62-11D2-9457-00C04F8EC888}") ITTAPIDispatchEventNotification 
	 : public IDispatch 
{
	
};

typedef int HSEMAPHORE;

typedef System::Comp TReference_Time;

__interface IReferenceClock;
typedef System::DelphiInterface<IReferenceClock> _di_IReferenceClock;
__interface INTERFACE_UUID("{56A86897-0AD4-11CE-B03A-0020AF0BA770}") IReferenceClock  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall GetTime(System::Comp &pTime) = 0 ;
	virtual HRESULT __stdcall AdviseTime(System::Comp baseTime, System::Comp streamTime, unsigned hEvent
		, unsigned &pdwAdviseCookie) = 0 ;
	virtual HRESULT __stdcall AdvisePeriodic(System::Comp startTime, System::Comp periodTime, int hSemaphore
		, unsigned &pdwAdviseCookie) = 0 ;
	virtual HRESULT __stdcall Unadvise(unsigned dwAdviseCookie) = 0 ;
};

#pragma option push -b-
enum TFilter_State { State_Stopped, State_Paused, State_Running };
#pragma option pop

__interface IMediaFilter;
typedef System::DelphiInterface<IMediaFilter> _di_IMediaFilter;
__interface INTERFACE_UUID("{56A86899-0AD4-11CE-B03A-0020AF0BA770}") IMediaFilter  : public IPersist 
	
{
	
public:
	virtual HRESULT __stdcall Stop(void) = 0 ;
	virtual HRESULT __stdcall Pause(void) = 0 ;
	virtual HRESULT __stdcall Run(System::Comp tStart) = 0 ;
	virtual HRESULT __stdcall GetState(unsigned dwMilliSecsTimeout, TFilter_State &State) = 0 ;
	virtual HRESULT __stdcall SetSyncSource(_di_IReferenceClock pClock) = 0 ;
	virtual HRESULT __stdcall GetSyncSource(/* out */ _di_IReferenceClock &pClock) = 0 ;
};

struct TAM_Media_Type
{
	GUID majortype;
	GUID subtype;
	BOOL bFixedSizeSamples;
	BOOL bTemporalCompression;
	unsigned lSampleSize;
	GUID formattype;
	_di_IUnknown pUnk;
	unsigned cbFormat;
	void *pbFormat;
} ;

typedef TAM_Media_Type *PAM_Media_Type;

#pragma option push -b-
enum TPin_Direction { PINDIR_INPUT, PINDIR_OUTPUT };
#pragma option pop

__interface IBaseFilter;
typedef System::DelphiInterface<IBaseFilter> _di_IBaseFilter;
__interface IEnumPins;
typedef System::DelphiInterface<IEnumPins> _di_IEnumPins;
__interface IPin;
typedef System::DelphiInterface<IPin> _di_IPin;
struct TFilterInfo;
__interface IFilterGraph;
typedef System::DelphiInterface<IFilterGraph> _di_IFilterGraph;
__interface INTERFACE_UUID("{56A86895-0AD4-11CE-B03A-0020AF0BA770}") IBaseFilter  : public IMediaFilter 
	
{
	
public:
	virtual HRESULT __stdcall EnumPins(/* out */ _di_IEnumPins &ppEnum) = 0 ;
	virtual HRESULT __stdcall FindPin(wchar_t * Id, /* out */ _di_IPin &ppPin) = 0 ;
	virtual HRESULT __stdcall QueryFilterInfo(TFilterInfo &pInfo) = 0 ;
	virtual HRESULT __stdcall JoinFilterGraph(_di_IFilterGraph pGraph, wchar_t * pName) = 0 ;
	virtual HRESULT __stdcall QueryVendorInfo(wchar_t * &pVendorInfo) = 0 ;
};

struct TPin_Info
{
	_di_IBaseFilter pFilter;
	TPin_Direction dir;
	wchar_t achName[128];
} ;

__interface IEnumMediaTypes;
typedef System::DelphiInterface<IEnumMediaTypes> _di_IEnumMediaTypes;
__interface INTERFACE_UUID("{89C31040-846B-11CE-97D3-00AA0055595A}") IEnumMediaTypes  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Next(unsigned cMediaTypes, PAM_Media_Type &ppMediaTypes, unsigned &pcFetched
		) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned cMediaTypes) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumMediaTypes &ppEnum) = 0 ;
};

__interface INTERFACE_UUID("{56A86891-0AD4-11CE-B03A-0020AF0BA770}") IPin  : public IUnknown 
{
	
public:
	virtual HRESULT __stdcall Connect(_di_IPin pReceivePin, const TAM_Media_Type &pmt) = 0 ;
	virtual HRESULT __stdcall ReceiveConnection(_di_IPin pConnector, const TAM_Media_Type &pmt) = 0 ;
	virtual HRESULT __stdcall Disconnect(void) = 0 ;
	virtual HRESULT __stdcall ConnectedTo(/* out */ _di_IPin &pPin) = 0 ;
	virtual HRESULT __stdcall ConnectionMediaType(TAM_Media_Type &pmt) = 0 ;
	virtual HRESULT __stdcall QueryPinInfo(TPin_Info &pInfo) = 0 ;
	virtual HRESULT __stdcall QueryDirection(TPin_Direction &pPinDir) = 0 ;
	virtual HRESULT __stdcall QueryId(wchar_t * &Id) = 0 ;
	virtual HRESULT __stdcall QueryAccept(const TAM_Media_Type &pmt) = 0 ;
	virtual HRESULT __stdcall EnumMediaTypes(/* out */ _di_IEnumMediaTypes &ppEnum) = 0 ;
	virtual HRESULT __stdcall QueryInternalConnections(/* out */ _di_IPin &apPin, unsigned &nPin) = 0 ;
		
	virtual HRESULT __stdcall EndOfStream(void) = 0 ;
	virtual HRESULT __stdcall BeginFlush(void) = 0 ;
	virtual HRESULT __stdcall EndFlush(void) = 0 ;
	virtual HRESULT __stdcall NewSegment(System::Comp tStart, System::Comp tStop, double dRate) = 0 ;
};

__interface INTERFACE_UUID("{56A86892-0AD4-11CE-B03A-0020AF0BA770}") IEnumPins  : public IUnknown 
{
	
public:
	virtual HRESULT __stdcall Next(unsigned cPins, /* out */ _di_IPin &ppPins, unsigned &pcFetched) = 0 
		;
	virtual HRESULT __stdcall Skip(unsigned cPins) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumPins &ppEnum) = 0 ;
};

struct TFilterInfo
{
	wchar_t achName[128];
	_di_IFilterGraph pGraph;
} ;

__interface IEnumFilters;
typedef System::DelphiInterface<IEnumFilters> _di_IEnumFilters;
__interface INTERFACE_UUID("{56A86893-0AD4-11CE-B03A-0020AF0BA770}") IEnumFilters  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Next(unsigned cFilters, /* out */ _di_IBaseFilter &ppFilter, unsigned &pcFetched
		) = 0 ;
	virtual HRESULT __stdcall Skip(unsigned cFilters) = 0 ;
	virtual HRESULT __stdcall Reset(void) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumFilters &ppEnum) = 0 ;
};

__interface INTERFACE_UUID("{56A8689F-0AD4-11CE-B03A-0020AF0BA770}") IFilterGraph  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall AddFilter(_di_IBaseFilter pFilter, wchar_t * pName) = 0 ;
	virtual HRESULT __stdcall RemoveFilter(_di_IBaseFilter pFilter) = 0 ;
	virtual HRESULT __stdcall EnumFilters(/* out */ _di_IEnumFilters &ppEnum) = 0 ;
	virtual HRESULT __stdcall FindFilterByName(wchar_t * pName, /* out */ _di_IBaseFilter &ppFilter) = 0 
		;
	virtual HRESULT __stdcall ConnectDirect(_di_IPin ppinOut, _di_IPin ppinIn, const TAM_Media_Type &pmt
		) = 0 ;
	virtual HRESULT __stdcall Reconnect(_di_IPin ppin) = 0 ;
	virtual HRESULT __stdcall Disconnect(_di_IPin ppin) = 0 ;
	virtual HRESULT __stdcall SetDefaultSyncSource(void) = 0 ;
};

__interface IGraphBuilder;
typedef System::DelphiInterface<IGraphBuilder> _di_IGraphBuilder;
__interface INTERFACE_UUID("{56A868A9-0AD4-11CE-B03A-0020AF0BA770}") IGraphBuilder  : public IFilterGraph 
	
{
	
public:
	virtual HRESULT __stdcall Connect(_di_IPin ppinOut, _di_IPin ppinIn) = 0 ;
	virtual HRESULT __stdcall Render(_di_IPin ppinOut) = 0 ;
	virtual HRESULT __stdcall RenderFile(wchar_t * lpcwstrFile, wchar_t * lpcwstrPlayList) = 0 ;
	virtual HRESULT __stdcall AddSourceFilter(wchar_t * lpcwstrFileName, wchar_t * lpcwstrFilterName, /* out */ 
		_di_IBaseFilter &ppFilter) = 0 ;
	virtual HRESULT __stdcall SetLogFile(unsigned hFile) = 0 ;
	virtual HRESULT __stdcall Abort(void) = 0 ;
	virtual HRESULT __stdcall ShouldOperationContinue(void) = 0 ;
};

__interface IFileSinkFilter;
typedef System::DelphiInterface<IFileSinkFilter> _di_IFileSinkFilter;
__interface INTERFACE_UUID("{A2104830-7C70-11CF-8BCE-00AA00A3F1A6}") IFileSinkFilter  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall SetFileName(wchar_t * pszFileName, const TAM_Media_Type &pmt) = 0 ;
	virtual HRESULT __stdcall GetCurFile(wchar_t * &ppszFileName, TAM_Media_Type &pmt) = 0 ;
};

__interface IAMCopyCaptureFileProgress;
typedef System::DelphiInterface<IAMCopyCaptureFileProgress> _di_IAMCopyCaptureFileProgress;
__interface INTERFACE_UUID("{670D1D20-A068-11D0-B3F0-00AA003761C5}") IAMCopyCaptureFileProgress  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall Progress(int iProgress) = 0 ;
};

__interface ICaptureGraphBuilder2;
typedef System::DelphiInterface<ICaptureGraphBuilder2> _di_ICaptureGraphBuilder2;
__interface INTERFACE_UUID("{93E5A4E0-2D50-11D2-ABFA-00A0C9C6E38D}") ICaptureGraphBuilder2  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall SetFiltergraph(_di_IGraphBuilder pfg) = 0 ;
	virtual HRESULT __stdcall GetFiltergraph(/* out */ _di_IGraphBuilder &ppfg) = 0 ;
	virtual HRESULT __stdcall SetOutputFileName(System::PGUID pType, wchar_t * lpstrFile, /* out */ _di_IBaseFilter 
		&ppf, /* out */ _di_IFileSinkFilter &ppSink) = 0 ;
	virtual HRESULT __stdcall FindInterface(System::PGUID pCategory, System::PGUID pType, _di_IBaseFilter 
		pf, System::PGUID riid, /* out */ void *ppint) = 0 ;
	virtual HRESULT __stdcall RenderStream(System::PGUID pCategory, System::PGUID pType, _di_IUnknown pSource
		, _di_IBaseFilter pfCompressor, _di_IBaseFilter pfRenderer) = 0 ;
	virtual HRESULT __stdcall ControlStream(System::PGUID pCategory, System::PGUID pType, _di_IBaseFilter 
		pFilter, System::Comp pstart, System::Comp pstop, Word wStartCookie, Word wStopCookie) = 0 ;
	virtual HRESULT __stdcall AllocCapFile(wchar_t * lpstr, System::Comp dwlSize) = 0 ;
	virtual HRESULT __stdcall CopyCaptureFile(wchar_t * lpwstrOld, wchar_t * lpwstrNew, int fAllowEscAbort
		, _di_IAMCopyCaptureFileProgress pCallback) = 0 ;
	virtual HRESULT __stdcall FindPin(_di_IUnknown pSource, TPin_Direction pindir, System::PGUID pCategory
		, System::PGUID pType, BOOL fUnconnected, int num, /* out */ _di_IPin &ppPin) = 0 ;
};

typedef int OAHWND;

__interface IVideoWindow;
typedef System::DelphiInterface<IVideoWindow> _di_IVideoWindow;
__interface INTERFACE_UUID("{56A868B4-0AD4-11CE-B03A-0020AF0BA770}") IVideoWindow  : public IDispatch 
	
{
	
public:
	virtual HRESULT __stdcall put_Caption(wchar_t * strCaption) = 0 ;
	virtual HRESULT __stdcall get_Caption(wchar_t * &strCaption) = 0 ;
	virtual HRESULT __stdcall put_WindowStyle(int WindowStyle) = 0 ;
	virtual HRESULT __stdcall get_WindowStyle(int &WindowStyle) = 0 ;
	virtual HRESULT __stdcall put_WindowStyleEx(int WindowStyleEx) = 0 ;
	virtual HRESULT __stdcall get_WindowStyleEx(int &WindowStyleEx) = 0 ;
	virtual HRESULT __stdcall put_AutoShow(BOOL AutoShow) = 0 ;
	virtual HRESULT __stdcall get_AutoShow(BOOL &AutoShow) = 0 ;
	virtual HRESULT __stdcall put_WindowState(int WindowState) = 0 ;
	virtual HRESULT __stdcall get_WindowState(int &WindowState) = 0 ;
	virtual HRESULT __stdcall put_BackgroundPalette(int BackgroundPalette) = 0 ;
	virtual HRESULT __stdcall get_BackgroundPalette(int &pBackgroundPalette) = 0 ;
	virtual HRESULT __stdcall put_Visible(BOOL Visible) = 0 ;
	virtual HRESULT __stdcall get_Visible(BOOL &pVisible) = 0 ;
	virtual HRESULT __stdcall put_Left(int Left) = 0 ;
	virtual HRESULT __stdcall get_Left(int &pLeft) = 0 ;
	virtual HRESULT __stdcall put_Width(int Width) = 0 ;
	virtual HRESULT __stdcall get_Width(int &pWidth) = 0 ;
	virtual HRESULT __stdcall put_Top(int Top) = 0 ;
	virtual HRESULT __stdcall get_Top(int &pTop) = 0 ;
	virtual HRESULT __stdcall put_Height(int Height) = 0 ;
	virtual HRESULT __stdcall get_Height(int &pHeight) = 0 ;
	virtual HRESULT __stdcall put_Owner(int Owner) = 0 ;
	virtual HRESULT __stdcall get_Owner(int &Owner) = 0 ;
	virtual HRESULT __stdcall put_MessageDrain(int Drain) = 0 ;
	virtual HRESULT __stdcall get_MessageDrain(int &Drain) = 0 ;
	virtual HRESULT __stdcall get_BorderColor(int &Color) = 0 ;
	virtual HRESULT __stdcall put_BorderColor(int Color) = 0 ;
	virtual HRESULT __stdcall get_FullScreenMode(BOOL &FullScreenMode) = 0 ;
	virtual HRESULT __stdcall put_FullScreenMode(BOOL FullScreenMode) = 0 ;
	virtual HRESULT __stdcall SetWindowForeground(int Focus) = 0 ;
	virtual HRESULT __stdcall NotifyOwnerMessage(int hwnd, int uMsg, int wParam, int lParam) = 0 ;
	virtual HRESULT __stdcall SetWindowPosition(int Left, int Top, int Width, int Height) = 0 ;
	virtual HRESULT __stdcall GetWindowPosition(int &pLeft, int &pTop, int &pWidth, int &pHeight) = 0 ;
		
	virtual HRESULT __stdcall GetMinIdealImageSize(int &pWidth, int &pHeight) = 0 ;
	virtual HRESULT __stdcall GetMaxIdealImageSize(int &pWidth, int &pHeight) = 0 ;
	virtual HRESULT __stdcall GetRestorePosition(int &pLeft, int &pTop, int &pWidth, int &pHeight) = 0 
		;
	virtual HRESULT __stdcall HideCursor(BOOL HideCursor) = 0 ;
	virtual HRESULT __stdcall IsCursorHidden(BOOL &CursorHidden) = 0 ;
};

typedef int OAFilterState;

__interface IMediaControl;
typedef System::DelphiInterface<IMediaControl> _di_IMediaControl;
__interface INTERFACE_UUID("{56A868B1-0AD4-11CE-B03A-0020AF0BA770}") IMediaControl  : public IDispatch 
	
{
	
public:
	virtual HRESULT __stdcall Run(void) = 0 ;
	virtual HRESULT __stdcall Pause(void) = 0 ;
	virtual HRESULT __stdcall Stop(void) = 0 ;
	virtual HRESULT __stdcall GetState(int msTimeout, int &pfs) = 0 ;
	virtual HRESULT __stdcall RenderFile(wchar_t * strFilename) = 0 ;
	virtual HRESULT __stdcall AddSourceFilter(wchar_t * strFilename, _di_IDispatch ppUnk) = 0 ;
	virtual HRESULT __stdcall get_FilterCollection(/* out */ _di_IDispatch &ppUnk) = 0 ;
	virtual HRESULT __stdcall get_RegFilterCollection(/* out */ _di_IDispatch &ppUnk) = 0 ;
	virtual HRESULT __stdcall StopWhenReady(void) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
static const Shortint TAPI3LibMajorVersion = 0x4;
static const Shortint TAPI3LibMinorVersion = 0x0;
extern PACKAGE GUID LIBID_TAPI3Lib;
extern PACKAGE GUID IID_ITCollection;
extern PACKAGE GUID IID_ITCallStateEvent;
extern PACKAGE GUID IID_ITCallInfo;
extern PACKAGE GUID IID_ITAddress;
extern PACKAGE GUID IID_ITTAPI;
extern PACKAGE GUID IID_IEnumAddress;
extern PACKAGE GUID IID_IEnumCallHub;
extern PACKAGE GUID IID_ITCallHub;
extern PACKAGE GUID IID_IEnumCall;
extern PACKAGE GUID IID_IEnumUnknown;
extern PACKAGE GUID IID_ITBasicCallControl;
extern PACKAGE GUID IID_ITForwardInformation;
extern PACKAGE GUID IID_ITCallNotificationEvent;
extern PACKAGE GUID IID_ITTAPIEventNotification;
extern PACKAGE GUID IID_ITBasicAudioTerminal;
extern PACKAGE GUID IID_ITCallHubEvent;
extern PACKAGE GUID IID_ITAddressCapabilities;
extern PACKAGE GUID IID_IEnumBstr;
extern PACKAGE GUID IID_ITQOSEvent;
extern PACKAGE GUID IID_ITAddressEvent;
extern PACKAGE GUID IID_ITTerminal;
extern PACKAGE GUID IID_ITCallMediaEvent;
extern PACKAGE GUID IID_ITStream;
extern PACKAGE GUID IID_IEnumTerminal;
extern PACKAGE GUID IID_ITTAPIObjectEvent;
extern PACKAGE GUID IID_ITAddressTranslation;
extern PACKAGE GUID IID_ITAddressTranslationInfo;
extern PACKAGE GUID IID_IEnumLocation;
extern PACKAGE GUID IID_ITLocationInfo;
extern PACKAGE GUID IID_IEnumCallingCard;
extern PACKAGE GUID IID_ITCallingCard;
extern PACKAGE GUID IID_ITAgent;
extern PACKAGE GUID IID_IEnumAgentSession;
extern PACKAGE GUID IID_ITAgentSession;
extern PACKAGE GUID IID_ITACDGroup;
extern PACKAGE GUID IID_IEnumQueue;
extern PACKAGE GUID IID_ITQueue;
extern PACKAGE GUID IID_ITAgentEvent;
extern PACKAGE GUID IID_ITAgentSessionEvent;
extern PACKAGE GUID IID_ITACDGroupEvent;
extern PACKAGE GUID IID_ITQueueEvent;
extern PACKAGE GUID IID_ITTAPICallCenter;
extern PACKAGE GUID IID_IEnumAgentHandler;
extern PACKAGE GUID IID_ITAgentHandler;
extern PACKAGE GUID IID_IEnumACDGroup;
extern PACKAGE GUID IID_ITAgentHandlerEvent;
extern PACKAGE GUID IID_ITCallInfoChangeEvent;
extern PACKAGE GUID IID_ITRequestEvent;
extern PACKAGE GUID IID_ITMediaSupport;
extern PACKAGE GUID IID_ITTerminalSupport;
extern PACKAGE GUID IID_IEnumTerminalClass;
extern PACKAGE GUID IID_ITStreamControl;
extern PACKAGE GUID IID_IEnumStream;
extern PACKAGE GUID IID_ITSubStreamControl;
extern PACKAGE GUID IID_ITSubStream;
extern PACKAGE GUID IID_IEnumSubStream;
extern PACKAGE GUID IID_ITLegacyAddressMediaControl;
extern PACKAGE GUID IID_ITLegacyCallMediaControl;
extern PACKAGE GUID IID_ITDigitDetectionEvent;
extern PACKAGE GUID IID_ITDigitGenerationEvent;
extern PACKAGE GUID IID_ITPrivateEvent;
extern PACKAGE GUID DIID_ITTAPIDispatchEventNotification;
extern PACKAGE GUID CLASS_TAPI;
extern PACKAGE GUID IID_ITDispatchMapper;
extern PACKAGE GUID CLASS_DispatchMapper;
extern PACKAGE GUID IID_ITRequest;
extern PACKAGE GUID CLASS_RequestMakeCall;
extern PACKAGE GUID CLSID_FilterGraph;
extern PACKAGE GUID CLSID_CaptureGraphBuilder2;
extern PACKAGE GUID IID_IVideoWindow;
extern PACKAGE GUID IID_IMediaControl;
extern PACKAGE GUID IID_IPin;
extern PACKAGE GUID IID_IEnumPins;
extern PACKAGE GUID IID_IEnumMediaTypes;
extern PACKAGE GUID IID_IFilterGraph;
extern PACKAGE GUID IID_IEnumFilters;
extern PACKAGE GUID IID_IMediaFilter;
extern PACKAGE GUID IID_IBaseFilter;
extern PACKAGE GUID IID_IReferenceClock;
extern PACKAGE GUID IID_IReferenceClock2;
extern PACKAGE GUID IID_IMediaSample;
extern PACKAGE GUID IID_IMediaSample2;
extern PACKAGE GUID IID_IMemAllocator;
extern PACKAGE GUID IID_IMemInputPin;
extern PACKAGE GUID IID_IAMovieSetup;
extern PACKAGE GUID IID_IMediaSeeking;
extern PACKAGE GUID IID_IEnumRegFilters;
extern PACKAGE GUID IID_IFilterMapper;
extern PACKAGE GUID IID_IFilterMapper2;
extern PACKAGE GUID IID_IQualityControl;
extern PACKAGE GUID IID_IOverlayNotify;
extern PACKAGE GUID IID_IOverlay;
extern PACKAGE GUID IID_IMediaEventSink;
extern PACKAGE GUID IID_IFileSourceFilter;
extern PACKAGE GUID IID_IFileSinkFilter;
extern PACKAGE GUID IID_IFileSinkFilter2;
extern PACKAGE GUID IID_IFileAsyncIO;
extern PACKAGE GUID IID_IGraphBuilder;
extern PACKAGE GUID IID_ICaptureGraphBuilder;
extern PACKAGE GUID IID_IAMCopyCaptureFileProgress;
extern PACKAGE GUID IID_IFilterGraph2;
extern PACKAGE GUID IID_IStreamBuilder;
extern PACKAGE GUID IID_IAsyncReader;
extern PACKAGE GUID IID_IGraphVersion;
extern PACKAGE GUID IID_IResourceConsumer;
extern PACKAGE GUID IID_IResourceManager;
extern PACKAGE GUID IID_IDistributorNotify;
extern PACKAGE GUID IID_IAMStreamControl;
extern PACKAGE GUID IID_ISeekingPassThru;
extern PACKAGE GUID IID_IAMStreamConfig;
extern PACKAGE GUID IID_IConfigInterleaving;
extern PACKAGE GUID IID_IConfigAviMux;
extern PACKAGE GUID IID_IAMVideoCompression;
extern PACKAGE GUID IID_IAMVfwCaptureDialogs;
extern PACKAGE GUID IID_IAMVfwCompressDialogs;
extern PACKAGE GUID IID_IAMDroppedFrames;
extern PACKAGE GUID IID_IAMAudioInputMixer;
extern PACKAGE GUID IID_IAMAnalogVideoDecoder;
extern PACKAGE GUID IID_IAMVideoProcAmp;
extern PACKAGE GUID IID_IAMCameraControl;
extern PACKAGE GUID IID_IAMCrossbar;
extern PACKAGE GUID IID_IAMTuner;
extern PACKAGE GUID IID_IAMTunerNotification;
extern PACKAGE GUID IID_IAMTVTuner;
extern PACKAGE GUID IID_IBPCSatelliteTuner;
extern PACKAGE GUID IID_IAMTVAudio;
extern PACKAGE GUID IID_IAMTVAudioNotification;
extern PACKAGE GUID IID_IAMAnalogVideoEncoder;
extern PACKAGE GUID IID_IMediaPropertyBag;
extern PACKAGE GUID IID_IPersistMediaPropertyBag;
extern PACKAGE GUID IID_IAMPhysicalPinInfo;
extern PACKAGE GUID IID_IAMExtDevice;
extern PACKAGE GUID IID_IAMExtTransport;
extern PACKAGE GUID IID_IAMTimecodeReader;
extern PACKAGE GUID IID_IAMTimecodeGenerator;
extern PACKAGE GUID IID_IAMTimecodeDisplay;
extern PACKAGE GUID IID_IAMDevMemoryAllocator;
extern PACKAGE GUID IID_IAMDevMemoryControl;
extern PACKAGE GUID IID_IAMStreamSelect;
extern PACKAGE GUID IID_IAMovie;
extern PACKAGE GUID IID_ICreateDevEnum;
extern PACKAGE GUID IID_IDvdControl;
extern PACKAGE GUID IID_IDvdControl2;
extern PACKAGE GUID IID_IDvdInfo;
extern PACKAGE GUID IID_IDvdInfo2;
extern PACKAGE GUID IID_IDvdGraphBuilder;
extern PACKAGE GUID IID_IDvdState;
extern PACKAGE GUID IID_IDvdCmd;
extern PACKAGE GUID IID_IVideoFrameStep;
extern PACKAGE GUID IID_IFilterMapper3;
extern PACKAGE GUID IID_IOverlayNotify2;
extern PACKAGE GUID IID_ICaptureGraphBuilder2;
extern PACKAGE GUID IID_IMemAllocatorCallbackTemp;
extern PACKAGE GUID IID_IMemAllocatorNotifyCallbackTemp;
extern PACKAGE GUID IID_IAMVideoControl;
extern PACKAGE GUID IID_IKsPropertySet;
extern PACKAGE GUID IID_IAMResourceControl;
extern PACKAGE GUID IID_IAMClockAdjust;
extern PACKAGE GUID IID_IAMFilterMiscFlags;
extern PACKAGE GUID IID_IDrawVideoImage;
extern PACKAGE GUID IID_IDecimateVideoImage;
extern PACKAGE GUID IID_IAMVideoDecimationProperties;
extern PACKAGE GUID IID_IAMLatency;
extern PACKAGE GUID IID_IAMPushSource;
extern PACKAGE GUID IID_IAMDeviceRemoval;
extern PACKAGE GUID IID_IDVEnc;
extern PACKAGE GUID IID_IIPDVDec;
extern PACKAGE GUID IID_IDVSplitter;
extern PACKAGE GUID IID_IAMAudioRendererStats;
extern PACKAGE GUID IID_IAMGraphStreams;
extern PACKAGE GUID IID_IAMOverlayFX;
extern PACKAGE GUID IID_IAMOpenProgress;
extern PACKAGE GUID IID_IMpeg2Demultiplexer;
extern PACKAGE GUID IID_IEnumStreamIdMap;
extern PACKAGE GUID IID_IMPEG2StreamIdMap;
extern PACKAGE GUID IID_IDDrawExclModeVideo;
extern PACKAGE GUID IID_IDDrawExclModeVideoCallback;
extern PACKAGE GUID IID_IPinConnection;
extern PACKAGE GUID IID_IPinFlowControl;
extern PACKAGE GUID IID_IGraphConfig;
extern PACKAGE GUID IID_IGraphConfigCallback;
extern PACKAGE GUID IID_IFilterChain;
static const Shortint TAPIMEDIATYPE_AUDIO = 0x8;
static const Word TAPIMEDIATYPE_VIDEO = 0x8000;
static const Shortint TAPIMEDIATYPE_DATAMODEM = 0x10;
static const Shortint TAPIMEDIATYPE_G3FAX = 0x20;
static const Shortint LINEADDRESSTYPE_PHONENUMBER = 0x1;
static const Shortint LINEADDRESSTYPE_SDP = 0x2;
static const Shortint LINEADDRESSTYPE_EMAILNAME = 0x4;
static const Shortint LINEADDRESSTYPE_DOMAINNAME = 0x8;
static const Shortint LINEADDRESSTYPE_IPADDRESS = 0x10;
static const Shortint LINECALLORIGIN_OUTBOUND = 0x1;
static const Shortint LINECALLORIGIN_INTERNAL = 0x2;
static const Shortint LINECALLORIGIN_EXTERNAL = 0x4;
static const Shortint LINECALLORIGIN_UNKNOWN = 0x10;
static const Shortint LINECALLORIGIN_UNAVAIL = 0x20;
static const Shortint LINECALLORIGIN_CONFERENCE = 0x40;
static const Byte LINECALLORIGIN_INBOUND = 0x80;
static const Shortint LINECALLREASON_DIRECT = 0x1;
static const Shortint LINECALLREASON_FWDBUSY = 0x2;
static const Shortint LINECALLREASON_FWDNOANSWER = 0x4;
static const Shortint LINECALLREASON_FWDUNCOND = 0x8;
static const Shortint LINECALLREASON_PICKUP = 0x10;
static const Shortint LINECALLREASON_UNPARK = 0x20;
static const Shortint LINECALLREASON_REDIRECT = 0x40;
static const Byte LINECALLREASON_CALLCOMPLETION = 0x80;
static const Word LINECALLREASON_TRANSFER = 0x100;
static const Word LINECALLREASON_REMINDER = 0x200;
static const Word LINECALLREASON_UNKNOWN = 0x400;
static const Word LINECALLREASON_UNAVAIL = 0x800;
static const Word LINECALLREASON_INTRUDE = 0x1000;
static const Word LINECALLREASON_PARKED = 0x2000;
static const Word LINECALLREASON_CAMPEDON = 0x4000;
static const Word LINECALLREASON_ROUTEREQUEST = 0x8000;
extern PACKAGE GUID IID_IConnectionPointContainer;
extern PACKAGE GUID CLSID_IBasicVideo;
extern PACKAGE GUID CLSID_HandsetTerminal;
extern PACKAGE GUID CLSID_HeadsetTerminal;
extern PACKAGE GUID CLSID_MediaStreamTerminal;
extern PACKAGE GUID CLSID_MicrophoneTerminal;
extern PACKAGE GUID CLSID_SpeakerphoneTerminal;
extern PACKAGE GUID CLSID_SpeakersTerminal;
extern PACKAGE GUID CLSID_VideoInputTerminal;
extern PACKAGE GUID CLSID_VideoWindowTerm;
#define CLSID_String_HandsetTerminal "{AAF578EB-DC70-11d0-8ED3-00C04FB6809F}"
#define CLSID_String_HeadsetTerminal "{AAF578ED-DC70-11d0-8ED3-00C04FB6809F}"
#define CLSID_String_MediaStreamTerminal "{E2F7AEF7-4971-11D1-A671-006097C9A2E8}"
#define CLSID_String_MicrophoneTerminal "{AAF578EF-DC70-11d0-8ED3-00C04FB6809F}"
#define CLSID_String_SpeakerphoneTerminal "{AAF578EE-DC70-11d0-8ED3-00C04FB6809F}"
#define CLSID_String_SpeakersTerminal "{AAF578F0-DC70-11d0-8ED3-00C04FB6809F}"
#define CLSID_String_VideoInputTerminal "{AAF578EC-DC70-11d0-8ED3-00C04FB6809F}"
#define CLSID_String_VideoWindowTerm "{F7438990-D6EB-11d0-82A6-00AA00B5CA1B}"
static const Shortint AS_INSERVICE = 0x0;
static const Shortint AS_OUTOFSERVICE = 0x1;
static const Shortint CHS_ACTIVE = 0x0;
static const Shortint CHS_IDLE = 0x1;
static const Shortint DC_NORMAL = 0x0;
static const Shortint DC_NOANSWER = 0x1;
static const Shortint DC_REJECTED = 0x2;
static const Shortint QSL_NEEDED = 0x1;
static const Shortint QSL_IF_AVAILABLE = 0x2;
static const Shortint QSL_BEST_EFFORT = 0x3;
static const Shortint FM_ASTRANSFER = 0x0;
static const Shortint FM_ASCONFERENCE = 0x1;
static const Shortint CS_IDLE = 0x0;
static const Shortint CS_INPROGRESS = 0x1;
static const Shortint CS_CONNECTED = 0x2;
static const Shortint CS_DISCONNECTED = 0x3;
static const Shortint CS_OFFERING = 0x4;
static const Shortint CS_HOLD = 0x5;
static const Shortint CS_QUEUED = 0x6;
static const Shortint CP_OWNER = 0x0;
static const Shortint CP_MONITOR = 0x1;
static const Shortint CIL_MEDIATYPESAVAILABLE = 0x0;
static const Shortint CIL_BEARERMODE = 0x1;
static const Shortint CIL_CALLERIDADDRESSTYPE = 0x2;
static const Shortint CIL_CALLEDIDADDRESSTYPE = 0x3;
static const Shortint CIL_CONNECTEDIDADDRESSTYPE = 0x4;
static const Shortint CIL_REDIRECTIONIDADDRESSTYPE = 0x5;
static const Shortint CIL_REDIRECTINGIDADDRESSTYPE = 0x6;
static const Shortint CIL_ORIGIN = 0x7;
static const Shortint CIL_REASON = 0x8;
static const Shortint CIL_APPSPECIFIC = 0x9;
static const Shortint CIL_CALLPARAMSFLAGS = 0xa;
static const Shortint CIL_CALLTREATMENT = 0xb;
static const Shortint CIL_MINRATE = 0xc;
static const Shortint CIL_MAXRATE = 0xd;
static const Shortint CIL_COUNTRYCODE = 0xe;
static const Shortint CIL_CALLID = 0xf;
static const Shortint CIL_RELATEDCALLID = 0x10;
static const Shortint CIL_COMPLETIONID = 0x11;
static const Shortint CIL_NUMBEROFOWNERS = 0x12;
static const Shortint CIL_NUMBEROFMONITORS = 0x13;
static const Shortint CIL_TRUNK = 0x14;
static const Shortint CIL_RATE = 0x15;
static const Shortint CIS_CALLERIDNAME = 0x0;
static const Shortint CIS_CALLERIDNUMBER = 0x1;
static const Shortint CIS_CALLEDIDNAME = 0x2;
static const Shortint CIS_CALLEDIDNUMBER = 0x3;
static const Shortint CIS_CONNECTEDIDNAME = 0x4;
static const Shortint CIS_CONNECTEDIDNUMBER = 0x5;
static const Shortint CIS_REDIRECTIONIDNAME = 0x6;
static const Shortint CIS_REDIRECTIONIDNUMBER = 0x7;
static const Shortint CIS_REDIRECTINGIDNAME = 0x8;
static const Shortint CIS_REDIRECTINGIDNUMBER = 0x9;
static const Shortint CIS_CALLEDPARTYFRIENDLYNAME = 0xa;
static const Shortint CIS_COMMENT = 0xb;
static const Shortint CIS_DISPLAYABLEADDRESS = 0xc;
static const Shortint CIS_CALLINGPARTYID = 0xd;
static const Shortint CIB_USERUSERINFO = 0x0;
static const Shortint CIB_DEVSPECIFICBUFFER = 0x1;
static const Shortint CIB_CALLDATABUFFER = 0x2;
static const Shortint CIB_CHARGINGINFOBUFFER = 0x3;
static const Shortint CIB_HIGHLEVELCOMPATIBILITYBUFFER = 0x4;
static const Shortint CIB_LOWLEVELCOMPATIBILITYBUFFER = 0x5;
static const Shortint CEC_NONE = 0x0;
static const Shortint CEC_DISCONNECT_NORMAL = 0x1;
static const Shortint CEC_DISCONNECT_BUSY = 0x2;
static const Shortint CEC_DISCONNECT_BADADDRESS = 0x3;
static const Shortint CEC_DISCONNECT_NOANSWER = 0x4;
static const Shortint CEC_DISCONNECT_CANCELLED = 0x5;
static const Shortint CEC_DISCONNECT_REJECTED = 0x6;
static const Shortint CEC_DISCONNECT_FAILED = 0x7;
static const Shortint CNE_OWNER = 0x0;
static const Shortint CNE_MONITOR = 0x1;
static const Shortint TE_TAPIOBJECT = 0x1;
static const Shortint TE_ADDRESS = 0x2;
static const Shortint TE_CALLNOTIFICATION = 0x4;
static const Shortint TE_CALLSTATE = 0x8;
static const Shortint TE_CALLMEDIA = 0x10;
static const Shortint TE_CALLHUB = 0x20;
static const Shortint TE_CALLINFOCHANGE = 0x40;
static const Byte TE_PRIVATE = 0x80;
static const Word TE_REQUEST = 0x100;
static const Word TE_AGENT = 0x200;
static const Word TE_AGENTSESSION = 0x400;
static const Word TE_QOSEVENT = 0x800;
static const Word TE_AGENTHANDLER = 0x1000;
static const Word TE_ACDGROUP = 0x2000;
static const Word TE_QUEUE = 0x4000;
static const Word TE_DIGITEVENT = 0x8000;
static const int TE_GENERATEEVENT = 0x10000;
static const Shortint CHE_CALLJOIN = 0x0;
static const Shortint CHE_CALLLEAVE = 0x1;
static const Shortint CHE_CALLHUBNEW = 0x2;
static const Shortint CHE_CALLHUBIDLE = 0x3;
static const Shortint AC_ADDRESSTYPES = 0x0;
static const Shortint AC_BEARERMODES = 0x1;
static const Shortint AC_MAXACTIVECALLS = 0x2;
static const Shortint AC_MAXONHOLDCALLS = 0x3;
static const Shortint AC_MAXONHOLDPENDINGCALLS = 0x4;
static const Shortint AC_MAXNUMCONFERENCE = 0x5;
static const Shortint AC_MAXNUMTRANSCONF = 0x6;
static const Shortint AC_MONITORDIGITSUPPORT = 0x7;
static const Shortint AC_GENERATEDIGITSUPPORT = 0x8;
static const Shortint AC_GENERATETONEMODES = 0x9;
static const Shortint AC_GENERATETONEMAXNUMFREQ = 0xa;
static const Shortint AC_MONITORTONEMAXNUMFREQ = 0xb;
static const Shortint AC_MONITORTONEMAXNUMENTRIES = 0xc;
static const Shortint AC_DEVCAPFLAGS = 0xd;
static const Shortint AC_ANSWERMODES = 0xe;
static const Shortint AC_LINEFEATURES = 0xf;
static const Shortint AC_SETTABLEDEVSTATUS = 0x10;
static const Shortint AC_PARKSUPPORT = 0x11;
static const Shortint AC_CALLERIDSUPPORT = 0x12;
static const Shortint AC_CALLEDIDSUPPORT = 0x13;
static const Shortint AC_CONNECTEDIDSUPPORT = 0x14;
static const Shortint AC_REDIRECTIONIDSUPPORT = 0x15;
static const Shortint AC_REDIRECTINGIDSUPPORT = 0x16;
static const Shortint AC_ADDRESSCAPFLAGS = 0x17;
static const Shortint AC_CALLFEATURES1 = 0x18;
static const Shortint AC_CALLFEATURES2 = 0x19;
static const Shortint AC_REMOVEFROMCONFCAPS = 0x1a;
static const Shortint AC_REMOVEFROMCONFSTATE = 0x1b;
static const Shortint AC_TRANSFERMODES = 0x1c;
static const Shortint AC_ADDRESSFEATURES = 0x1d;
static const Shortint AC_PREDICTIVEAUTOTRANSFERSTATES = 0x1e;
static const Shortint AC_MAXCALLDATASIZE = 0x1f;
static const Shortint AC_LINEID = 0x20;
static const Shortint AC_ADDRESSID = 0x21;
static const Shortint AC_FORWARDMODES = 0x22;
static const Shortint AC_MAXFORWARDENTRIES = 0x23;
static const Shortint AC_MAXSPECIFICENTRIES = 0x24;
static const Shortint AC_MINFWDNUMRINGS = 0x25;
static const Shortint AC_MAXFWDNUMRINGS = 0x26;
static const Shortint AC_MAXCALLCOMPLETIONS = 0x27;
static const Shortint AC_CALLCOMPLETIONCONDITIONS = 0x28;
static const Shortint AC_CALLCOMPLETIONMODES = 0x29;
static const Shortint AC_PERMANENTDEVICEID = 0x2a;
static const Shortint ACS_PROTOCOL = 0x0;
static const Shortint ACS_ADDRESSDEVICESPECIFIC = 0x1;
static const Shortint ACS_LINEDEVICESPECIFIC = 0x2;
static const Shortint ACS_PROVIDERSPECIFIC = 0x3;
static const Shortint ACS_SWITCHSPECIFIC = 0x4;
static const Shortint ACS_PERMANENTDEVICEGUID = 0x5;
static const Shortint QE_NOQOS = 0x1;
static const Shortint QE_ADMISSIONFAILURE = 0x2;
static const Shortint QE_POLICYFAILURE = 0x3;
static const Shortint QE_GENERICERROR = 0x4;
static const Shortint AE_STATE = 0x0;
static const Shortint AE_CAPSCHANGE = 0x1;
static const Shortint AE_RINGING = 0x2;
static const Shortint AE_CONFIGCHANGE = 0x3;
static const Shortint AE_FORWARD = 0x4;
static const Shortint AE_NEWTERMINAL = 0x5;
static const Shortint AE_REMOVETERMINAL = 0x6;
static const Shortint TS_INUSE = 0x0;
static const Shortint TS_NOTINUSE = 0x1;
static const Shortint TT_STATIC = 0x0;
static const Shortint TT_DYNAMIC = 0x1;
static const Shortint TD_CAPTURE = 0x0;
static const Shortint TD_RENDER = 0x1;
static const Shortint TD_BIDIRECTIONAL = 0x2;
static const Shortint CME_NEW_STREAM = 0x0;
static const Shortint CME_STREAM_FAIL = 0x1;
static const Shortint CME_TERMINAL_FAIL = 0x2;
static const Shortint CME_STREAM_NOT_USED = 0x3;
static const Shortint CME_STREAM_ACTIVE = 0x4;
static const Shortint CME_STREAM_INACTIVE = 0x5;
static const Shortint CMC_UNKNOWN = 0x0;
static const Shortint CMC_BAD_DEVICE = 0x1;
static const Shortint CMC_CONNECT_FAIL = 0x2;
static const Shortint CMC_LOCAL_REQUEST = 0x3;
static const Shortint CMC_REMOTE_REQUEST = 0x4;
static const Shortint CMC_MEDIA_TIMEOUT = 0x5;
static const Shortint CMC_MEDIA_RECOVERED = 0x6;
static const Shortint TE_ADDRESSCREATE = 0x0;
static const Shortint TE_ADDRESSREMOVE = 0x1;
static const Shortint TE_REINIT = 0x2;
static const Shortint TE_TRANSLATECHANGE = 0x3;
static const Shortint TE_ADDRESSCLOSE = 0x4;
static const Shortint ASST_NOT_READY = 0x0;
static const Shortint ASST_READY = 0x1;
static const Shortint ASST_BUSY_ON_CALL = 0x2;
static const Shortint ASST_BUSY_WRAPUP = 0x3;
static const Shortint ASST_SESSION_ENDED = 0x4;
static const Shortint AS_NOT_READY = 0x0;
static const Shortint AS_READY = 0x1;
static const Shortint AS_BUSY_ACD = 0x2;
static const Shortint AS_BUSY_INCOMING = 0x3;
static const Shortint AS_BUSY_OUTGOING = 0x4;
static const Shortint AS_UNKNOWN = 0x5;
static const Shortint AE_NOT_READY = 0x0;
static const Shortint AE_READY = 0x1;
static const Shortint AE_BUSY_ACD = 0x2;
static const Shortint AE_BUSY_INCOMING = 0x3;
static const Shortint AE_BUSY_OUTGOING = 0x4;
static const Shortint AE_UNKNOWN = 0x5;
static const Shortint ASE_NEW_SESSION = 0x0;
static const Shortint ASE_NOT_READY = 0x1;
static const Shortint ASE_READY = 0x2;
static const Shortint ASE_BUSY = 0x3;
static const Shortint ASE_WRAPUP = 0x4;
static const Shortint ASE_END = 0x5;
static const Shortint ACDGE_NEW_GROUP = 0x0;
static const Shortint ACDGE_GROUP_REMOVED = 0x1;
static const Shortint ACDQE_NEW_QUEUE = 0x0;
static const Shortint ACDQE_QUEUE_REMOVED = 0x1;
static const Shortint AHE_NEW_AGENTHANDLER = 0x0;
static const Shortint AHE_AGENTHANDLER_REMOVED = 0x1;
static const Shortint CIC_OTHER = 0x0;
static const Shortint CIC_DEVSPECIFIC = 0x1;
static const Shortint CIC_BEARERMODE = 0x2;
static const Shortint CIC_RATE = 0x3;
static const Shortint CIC_APPSPECIFIC = 0x4;
static const Shortint CIC_CALLID = 0x5;
static const Shortint CIC_RELATEDCALLID = 0x6;
static const Shortint CIC_ORIGIN = 0x7;
static const Shortint CIC_REASON = 0x8;
static const Shortint CIC_COMPLETIONID = 0x9;
static const Shortint CIC_NUMOWNERINCR = 0xa;
static const Shortint CIC_NUMOWNERDECR = 0xb;
static const Shortint CIC_NUMMONITORS = 0xc;
static const Shortint CIC_TRUNK = 0xd;
static const Shortint CIC_CALLERID = 0xe;
static const Shortint CIC_CALLEDID = 0xf;
static const Shortint CIC_CONNECTEDID = 0x10;
static const Shortint CIC_REDIRECTIONID = 0x11;
static const Shortint CIC_REDIRECTINGID = 0x12;
static const Shortint CIC_USERUSERINFO = 0x13;
static const Shortint CIC_HIGHLEVELCOMP = 0x14;
static const Shortint CIC_LOWLEVELCOMP = 0x15;
static const Shortint CIC_CHARGINGINFO = 0x16;
static const Shortint CIC_TREATMENT = 0x17;
static const Shortint CIC_CALLDATA = 0x18;
static const Shortint CIC_PRIVILEGE = 0x19;
static const Shortint CIC_MEDIATYPE = 0x1a;

}	/* namespace Aditapi3 */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Aditapi3;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdITapi3
