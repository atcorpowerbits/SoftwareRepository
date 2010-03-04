// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdVoIP.pas' rev: 5.00

#ifndef AdVoIPHPP
#define AdVoIPHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdITapi3.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <ComObj.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <ActiveX.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <OleServer.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Advoip
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TApdTerminalDeviceClass { dcHandsetTerminal, dcHeadsetTerminal, dcMediaStreamTerminal, dcMicrophoneTerminal, 
	dcSpeakerPhoneTerminal, dcSpeakersTerminal, dcVideoInputTerminal, dcVideoWindowTerminal };
#pragma option pop

#pragma option push -b-
enum TApdTerminalMediaType { mtAudio, mtVideo, mtDataModem, mtG3_Fax };
#pragma option pop

#pragma option push -b-
enum TApdMediaDirection { mdCapture, mdRender, mdBiDirectional };
#pragma option pop

#pragma option push -b-
enum TApdTerminalType { ttStatic, ttDynamic };
#pragma option pop

#pragma option push -b-
enum TApdTerminalState { tsInUse, tsNotInUse };
#pragma option pop

#pragma option push -b-
enum TApdDisconnectCode { dcNormal, dcNoAnswer, dcRejected };
#pragma option pop

#pragma option push -b-
enum TApdQOSServiceLevel { qsBestEffort, qsIfAvailable, qsNeeded };
#pragma option pop

#pragma option push -b-
enum TApdFinishMode { fmAsTransfer, fmAsConference };
#pragma option pop

#pragma option push -b-
enum TApdCallState { csIdle, csInProgress, csConnected, csDisconnected, csOffering, csHold, csQueued 
	};
#pragma option pop

#pragma option push -b-
enum TApdAddressType { atPhoneNumber, atSDP, atEmailName, atDomainName, atIPAddress };
#pragma option pop

#pragma option push -b-
enum TApdCallPriviledge { cpOwner, cpMonitor };
#pragma option pop

#pragma option push -b-
enum TApdCallInfoLong { cilMediaTypesAvailable, cilBearerMode, cilCallerIDAddressType, cilCalledIDAddressType, 
	cilConnectedIDAddressType, cilRedirectionIDAddressType, cilRedirectingIDAddresstype, cilOrigin, cilReason, 
	cilAppSpecific, cilCallParamsFlags, cilCallTreatment, cilMinRate, cilMaxRate, cilCountryCode, cilCallID, 
	cilRelatedCallID, cilCompletionID, cilNumberOfOwners, cilNumberOfMonitors, cilTrunk, cilRate };
#pragma option pop

#pragma option push -b-
enum TApdCallInfoType { cisCallerIDName, cisCallerIDNumber, cisCalledIDName, cisCalledIDNumber, cisConnectedIDName, 
	cisConnectedIDNumber, cisRedirectionIDName, cisRedirectionIDNumber, cisRedirectingIDName, cisRedirectingIDNumber, 
	cisCalledPartyFriendlyName, cisComment, cisDisplayableAddress, cisCallingPartyID };
#pragma option pop

#pragma option push -b-
enum TApdCallInfoBufferType { cibUserUserInfo, cibDevSpecificBuffer, cibCallDataBuffer, cibChargingInfoBuffer, 
	cibHighLevelCompatibilityBuffer, cibLowLevelCompatibilityBuffer };
#pragma option pop

#pragma option push -b-
enum TApdAddressState { asInService, asOutOfService };
#pragma option pop

#pragma option push -b-
enum TApdCallHubState { chsActive, chsIdle };
#pragma option pop

class DELPHICLASS TApdCustomVoIP;
typedef void __fastcall (__closure *TApdVoIPNotifyEvent)(TApdCustomVoIP* VoIP);

typedef void __fastcall (__closure *TApdVoIPFailEvent)(TApdCustomVoIP* VoIP, int ErrorCode);

typedef void __fastcall (__closure *TApdVoIPIncomingCallEvent)(TApdCustomVoIP* VoIP, AnsiString CallerAddr
	, bool &Accept);

typedef void __fastcall (__closure *TApdVoIPStatusEvent)(TApdCustomVoIP* VoIP, Word TapiEvent, Word 
	Status, Word SubStatus);

struct TApdVoIPCallInfo
{
	bool InfoAvailable;
	AnsiString CallerIDName;
	AnsiString CallerIDNumber;
	AnsiString CalledIDName;
	AnsiString CalledIDNumber;
	AnsiString ConnectedIDName;
	AnsiString ConnectedIDNumber;
	AnsiString CalledPartyFriendlyName;
	AnsiString Comment;
	AnsiString DisplayableAddress;
	AnsiString CallingPartyID;
	unsigned MediaTypesAvailable;
	unsigned CallerIDAddressType;
	unsigned CalledIDAddressType;
	unsigned ConnectedIDAddressType;
	unsigned Origin;
	unsigned Reason;
	unsigned MinRate;
	unsigned MaxRate;
	unsigned Rate;
} ;

class DELPHICLASS TApdTerminals;
class PASCALIMPLEMENTATION TApdTerminals : public Classes::TCollection 
{
	typedef Classes::TCollection inherited;
	
public:
	#pragma option push -w-inl
	/* TCollection.Create */ inline __fastcall TApdTerminals(TMetaClass* ItemClass) : Classes::TCollection(
		ItemClass) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCollection.Destroy */ inline __fastcall virtual ~TApdTerminals(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdTapiEventSink;
class PASCALIMPLEMENTATION TApdTapiEventSink : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	int FRefCount;
	TApdCustomVoIP* FOwner;
	bool FAnswer;
	
public:
	__fastcall TApdTapiEventSink(TApdCustomVoIP* AOwner);
	HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj);
	int __stdcall _AddRef(void);
	int __stdcall _Release(void);
	HRESULT __stdcall Event(Activex::TOleEnum TapiEvent, const _di_IDispatch pEvent);
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TApdTapiEventSink(void) { }
	#pragma option pop
	
private:
	void *__ITTAPIEventNotification;	/* Aditapi3::ITTAPIEventNotification */
	
public:
	operator ITTAPIEventNotification*(void) { return (ITTAPIEventNotification*)&__ITTAPIEventNotification; }
		
	operator IUnknown*(void) { return (IUnknown*)&__ITTAPIEventNotification; }
	
};


class DELPHICLASS TApdVoIPTerminal;
class PASCALIMPLEMENTATION TApdVoIPTerminal : public Classes::TCollectionItem 
{
	typedef Classes::TCollectionItem inherited;
	
private:
	TApdTerminalDeviceClass FTerminalDeviceClass;
	AnsiString FDeviceName;
	TApdMediaDirection FMediaDirection;
	TApdTerminalMediaType FMediaType;
	TApdTerminalType FTerminalType;
	TApdTerminalState FTerminalState;
	bool __fastcall GetDeviceInUse(void);
	
__published:
	__property TApdTerminalDeviceClass DeviceClass = {read=FTerminalDeviceClass, nodefault};
	__property bool DeviceInUse = {read=GetDeviceInUse, nodefault};
	__property AnsiString DeviceName = {read=FDeviceName};
	__property TApdMediaDirection MediaDirection = {read=FMediaDirection, nodefault};
	__property TApdTerminalMediaType MediaType = {read=FMediaType, nodefault};
	__property TApdTerminalType TerminalType = {read=FTerminalType, nodefault};
	__property TApdTerminalState TerminalState = {read=FTerminalState, nodefault};
public:
	#pragma option push -w-inl
	/* TCollectionItem.Create */ inline __fastcall virtual TApdVoIPTerminal(Classes::TCollection* Collection
		) : Classes::TCollectionItem(Collection) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TApdVoIPTerminal(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdVoIPLog;
class PASCALIMPLEMENTATION TApdVoIPLog : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	bool FVerboseLog;
	bool FEnabled;
	AnsiString FLogName;
	
public:
	void __fastcall AddLogString(bool Verbose, const AnsiString S);
	void __fastcall ClearLog(void);
	
__published:
	__property AnsiString LogName = {read=FLogName, write=FLogName};
	__property bool VerboseLog = {read=FVerboseLog, write=FVerboseLog, nodefault};
	__property bool Enabled = {read=FEnabled, write=FEnabled, nodefault};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TApdVoIPLog(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TApdVoIPLog(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TApdCustomVoIP : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
private:
	bool FWaitingForCall;
	bool FConnected;
	AnsiString FAudioInDevice;
	AnsiString FVideoInDevice;
	AnsiString FCallerIDName;
	AnsiString FAudioOutDevice;
	AnsiString FCallerIDNumber;
	TApdTerminals* FAvailableTerminalDevices;
	TApdVoIPFailEvent FOnFail;
	TApdVoIPIncomingCallEvent FOnIncomingCall;
	TApdVoIPNotifyEvent FOnDisconnect;
	TApdVoIPNotifyEvent FOnConnect;
	TApdVoIPStatusEvent FOnStatus;
	Controls::TWinControl* FVideoOutWindow;
	Controls::TWinControl* FPreviewWindow;
	bool FEnablePreview;
	bool FEnableVideo;
	bool FVideoOutWindowAutoSize;
	bool FPreviewWindowAutoSize;
	TApdVoIPLog* FEventLog;
	bool FVoIPAvailable;
	AnsiString FCallerDisplayName;
	AnsiString FCallComment;
	AnsiString FCallDisplayableAddress;
	AnsiString FCallCallingPartyID;
	int FConnectTimeout;
	TApdVoIPCallInfo __fastcall GetCallInfo(void);
	void __fastcall SetPreviewWindow(const Controls::TWinControl* Value);
	void __fastcall SetVideoOutDevice(const Controls::TWinControl* Value);
	void __fastcall SetEnablePreview(const bool Value);
	void __fastcall SetVideoInDevice(const AnsiString Value);
	void __fastcall SetAudioInDevice(const AnsiString Value);
	void __fastcall SetAudioOutDevice(const AnsiString Value);
	void __fastcall SetEnableVideo(const bool Value);
	void __fastcall SetVideoOutWindowAutoSize(const bool Value);
	void __fastcall SetPreviewWindowAutoSize(const bool Value);
	Aditapi3::_di_ITCallInfo __fastcall GetCallInfoInterface(void);
	
protected:
	Aditapi3::_di_ITTAPI gpTapi;
	Aditapi3::_di_ITBasicCallControl gpCall;
	Aditapi3::_di_ITAddress gpAddress;
	int gulAdvise;
	TApdTapiEventSink* gpTAPIEventNotification;
	int NotifyRegister;
	HWND FHandle;
	int FErrorCode;
	bool FTapiInitialized;
	int FConnectTimer;
	void __fastcall DoConnectEvent(void);
	void __fastcall DoDisconnectEvent(void);
	void __fastcall DoFailEvent(void);
	void __fastcall DoIncomingCallEvent(void);
	void __fastcall DoStatusEvent(Word TapiEvent, Word Status, Word SubStatus);
	void __fastcall WndProc(Messages::TMessage &Message);
	void __fastcall ProcessTapiEvent(Activex::TOleEnum TapiEvent, _di_IDispatch pEvent);
	bool __fastcall AddressSupportsMediaType(Aditapi3::_di_ITAddress pAddress, Activex::TOleEnum lMediaType
		);
	HRESULT __fastcall AnswerTheCall(void);
	unsigned __fastcall DetermineAddressType(const AnsiString Addr);
	HRESULT __fastcall DisconnectTheCall(void);
	HRESULT __fastcall EnablePreviewWindow(Aditapi3::_di_ITAddress pAddress, Aditapi3::_di_ITStream pStream
		);
	HRESULT __fastcall FindTerminal(AnsiString DevName, Activex::TOleEnum MediaType, Activex::TOleEnum 
		MediaDir, Aditapi3::_di_ITTerminal &ppTerminal);
	HRESULT __fastcall FindTheAddress(void);
	HRESULT __fastcall GetTerminal(Aditapi3::_di_ITAddress pAddress, Aditapi3::_di_ITStream pStream, Aditapi3::_di_ITTerminal 
		&ppTerminal);
	HRESULT __fastcall GetVideoRenderTerminal(Aditapi3::_di_ITAddress pAddress, Aditapi3::_di_ITTerminal 
		&ppTerminal);
	HRESULT __fastcall GetVideoRenderTerminalFromStream(Aditapi3::_di_ITCallMediaEvent pCallMediaEvent, 
		Aditapi3::_di_ITTerminal &ppTerminal, bool &pfRenderStream);
	void __fastcall HostWindow(Aditapi3::_di_IVideoWindow pVideoWindow, bool IsRenderStream);
	HRESULT __fastcall InitializeTapi(void);
	bool __fastcall IsAudioCaptureStream(Aditapi3::_di_ITStream pStream);
	bool __fastcall IsAudioRenderStream(Aditapi3::_di_ITStream pStream);
	bool __fastcall IsVideoCaptureStream(Aditapi3::_di_ITStream pStream);
	bool __fastcall IsVideoRenderStream(Aditapi3::_di_ITStream pStream);
	void __fastcall LoadTerminals(void);
	bool __fastcall MakeTheCall(unsigned dwAddressType, WideString szAddressToCall);
	HRESULT __fastcall RegisterTapiEventInterface(void);
	void __fastcall ReleaseTheCall(void);
	HRESULT __fastcall SelectTerminalOnCall(Aditapi3::_di_ITAddress pAddress, Aditapi3::_di_ITBasicCallControl 
		pCall);
	void __fastcall ShutDownTapi(void);
	
public:
	__fastcall virtual TApdCustomVoIP(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomVoIP(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation
		);
	void __fastcall CancelCall(void);
	void __fastcall Connect(AnsiString DestAddr);
	bool __fastcall ShowMediaSelectionDialog(void);
	__property TApdTerminals* AvailableTerminalDevices = {read=FAvailableTerminalDevices};
	__property AnsiString CallComment = {read=FCallComment, write=FCallComment};
	__property AnsiString CallDisplayableAddress = {read=FCallDisplayableAddress, write=FCallDisplayableAddress
		};
	__property AnsiString CallCallingPartyID = {read=FCallCallingPartyID, write=FCallCallingPartyID};
	__property TApdVoIPCallInfo CallInfo = {read=GetCallInfo};
	__property Aditapi3::_di_ITCallInfo CallInfoInterface = {read=GetCallInfoInterface};
	__property AnsiString CallerIDName = {read=FCallerIDName};
	__property AnsiString CallerIDNumber = {read=FCallerIDNumber};
	__property AnsiString CallerDisplayName = {read=FCallerDisplayName};
	__property bool Connected = {read=FConnected, nodefault};
	__property int ErrorCode = {read=FErrorCode, nodefault};
	__property bool VoIPAvailable = {read=FVoIPAvailable, nodefault};
	__property bool WaitingForCall = {read=FWaitingForCall, nodefault};
	__property AnsiString AudioInDevice = {read=FAudioInDevice, write=SetAudioInDevice};
	__property AnsiString AudioOutDevice = {read=FAudioOutDevice, write=SetAudioOutDevice};
	__property int ConnectTimeout = {read=FConnectTimeout, write=FConnectTimeout, nodefault};
	__property bool EnablePreview = {read=FEnablePreview, write=SetEnablePreview, nodefault};
	__property bool EnableVideo = {read=FEnableVideo, write=SetEnableVideo, nodefault};
	__property AnsiString VideoInDevice = {read=FVideoInDevice, write=SetVideoInDevice};
	__property Controls::TWinControl* VideoOutWindow = {read=FVideoOutWindow, write=SetVideoOutDevice};
		
	__property bool VideoOutWindowAutoSize = {read=FVideoOutWindowAutoSize, write=SetVideoOutWindowAutoSize
		, nodefault};
	__property Controls::TWinControl* PreviewWindow = {read=FPreviewWindow, write=SetPreviewWindow};
	__property bool PreviewWindowAutoSize = {read=FPreviewWindowAutoSize, write=SetPreviewWindowAutoSize
		, nodefault};
	__property TApdVoIPLog* EventLog = {read=FEventLog, write=FEventLog};
	__property TApdVoIPNotifyEvent OnConnect = {read=FOnConnect, write=FOnConnect};
	__property TApdVoIPNotifyEvent OnDisconnect = {read=FOnDisconnect, write=FOnDisconnect};
	__property TApdVoIPFailEvent OnFail = {read=FOnFail, write=FOnFail};
	__property TApdVoIPIncomingCallEvent OnIncomingCall = {read=FOnIncomingCall, write=FOnIncomingCall}
		;
	__property TApdVoIPStatusEvent OnStatus = {read=FOnStatus, write=FOnStatus};
};


class DELPHICLASS TApdVoIP;
class PASCALIMPLEMENTATION TApdVoIP : public TApdCustomVoIP 
{
	typedef TApdCustomVoIP inherited;
	
__published:
	__property AudioInDevice ;
	__property AudioOutDevice ;
	__property ConnectTimeout ;
	__property EnablePreview ;
	__property EnableVideo ;
	__property EventLog ;
	__property PreviewWindow ;
	__property PreviewWindowAutoSize ;
	__property VideoInDevice ;
	__property VideoOutWindow ;
	__property VideoOutWindowAutoSize ;
	__property OnConnect ;
	__property OnDisconnect ;
	__property OnFail ;
	__property OnIncomingCall ;
	__property OnStatus ;
public:
	#pragma option push -w-inl
	/* TApdCustomVoIP.Create */ inline __fastcall virtual TApdVoIP(Classes::TComponent* AOwner) : TApdCustomVoIP(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomVoIP.Destroy */ inline __fastcall virtual ~TApdVoIP(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Advoip */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Advoip;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdVoIP
