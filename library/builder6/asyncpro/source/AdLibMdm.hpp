// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdLibMdm.pas' rev: 6.00

#ifndef AdLibMdmHPP
#define AdLibMdmHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdExcept.hpp>	// Pascal unit
#include <AdXParsr.hpp>	// Pascal unit
#include <AdXBase.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adlibmdm
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TApdLoadModemRecord)(AnsiString ModemName, AnsiString Manufacturer, AnsiString Model, AnsiString ModemFile, bool &CanLoad);

typedef void __fastcall (__closure *TApdLoadModem)(AnsiString ModemName, AnsiString Manufacturer, AnsiString Model, bool &CanLoad);

struct TLmModemName;
typedef TLmModemName *PLmModemName;

#pragma pack(push, 4)
struct TLmModemName
{
	AnsiString ModemName;
	AnsiString Manufacturer;
	AnsiString Model;
	AnsiString ModemFile;
} ;
#pragma pack(pop)

struct TLmResponseData;
typedef TLmResponseData *PLmResponseData;

#pragma pack(push, 4)
struct TLmResponseData
{
	AnsiString Response;
	AnsiString ResponseType;
} ;
#pragma pack(pop)

struct TLmResponses;
typedef TLmResponses *PLmResponses;

#pragma pack(push, 4)
struct TLmResponses
{
	Classes::TList* OK;
	Classes::TList* NegotiationProgress;
	Classes::TList* Connect;
	Classes::TList* Error;
	Classes::TList* NoCarrier;
	Classes::TList* NoDialTone;
	Classes::TList* Busy;
	Classes::TList* NoAnswer;
	Classes::TList* Ring;
	Classes::TList* VoiceView1;
	Classes::TList* VoiceView2;
	Classes::TList* VoiceView3;
	Classes::TList* VoiceView4;
	Classes::TList* VoiceView5;
	Classes::TList* VoiceView6;
	Classes::TList* VoiceView7;
	Classes::TList* VoiceView8;
	Classes::TList* RingDuration;
	Classes::TList* RingBreak;
	Classes::TList* Date;
	Classes::TList* Time;
	Classes::TList* Number;
	Classes::TList* Name;
	Classes::TList* Msg;
	Classes::TList* SingleRing;
	Classes::TList* DoubleRing;
	Classes::TList* TripleRing;
	Classes::TList* Voice;
	Classes::TList* Fax;
	Classes::TList* Data;
	Classes::TList* Other;
} ;
#pragma pack(pop)

struct TLmModemCommand;
typedef TLmModemCommand *PLmModemCommand;

#pragma pack(push, 4)
struct TLmModemCommand
{
	AnsiString Command;
	int Sequence;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TLmFaxClassDetails
{
	AnsiString ModemResponseFaxDetect;
	AnsiString ModemResponseDataDetect;
	AnsiString SerialSpeedFaxDetect;
	AnsiString SerialSpeedDataDetect;
	AnsiString HostCommandFaxDetect;
	AnsiString HostCommandDataDetect;
	AnsiString ModemResponseFaxConnect;
	AnsiString ModemResponseDataConnect;
	Classes::TList* AnswerCommand;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TLmFaxDetails
{
	AnsiString ExitCommand;
	AnsiString PreAnswerCommand;
	AnsiString PreDialCommand;
	AnsiString ResetCommand;
	AnsiString SetupCommand;
	AnsiString EnableV17Recv;
	AnsiString EnableV17Send;
	AnsiString FixModemClass;
	AnsiString FixSerialSpeed;
	AnsiString HighestSendSpeed;
	AnsiString LowestSendSpeed;
	AnsiString HardwareFlowControl;
	AnsiString SerialSpeedInit;
	AnsiString Cl1FCS;
	AnsiString Cl2DC2;
	AnsiString Cl2lsEx;
	AnsiString Cl2RecvBOR;
	AnsiString Cl2SendBOR;
	AnsiString Cl2SkipCtrlQ;
	AnsiString Cl2SWBOR;
	AnsiString Class2FlowOff;
	AnsiString Class2FlowHW;
	AnsiString Class2FlowSW;
	TLmFaxClassDetails FaxClass1;
	TLmFaxClassDetails FaxClass2;
	TLmFaxClassDetails FaxClass2_0;
} ;
#pragma pack(pop)

struct TLmWaveFormat;
typedef TLmWaveFormat *PLmWaveFormat;

#pragma pack(push, 4)
struct TLmWaveFormat
{
	AnsiString ChipSet;
	AnsiString Speed;
	AnsiString SampleSize;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TLmWaveDriver
{
	AnsiString BaudRate;
	AnsiString WaveHardwareID;
	AnsiString WaveDevices;
	AnsiString LowerMid;
	AnsiString LowerWaveInPid;
	AnsiString LowerWaveOutPid;
	AnsiString WaveOutMixerDest;
	AnsiString WaveOutMixerSource;
	AnsiString WaveInMixerDest;
	AnsiString WaveInMixerSource;
	Classes::TList* WaveFormat;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TLmVoiceSettings
{
	AnsiString VoiceProfile;
	int HandsetCloseDelay;
	AnsiString SpeakerPhoneSpecs;
	AnsiString AbortPlay;
	AnsiString CallerIDOutSide;
	AnsiString CallerIDPrivate;
	AnsiString TerminatePlay;
	AnsiString TerminateRecord;
	AnsiString VoiceManufacturerID;
	AnsiString VoiceProductIDWaveIn;
	AnsiString VoiceProductIDWaveOut;
	AnsiString VoiceSwitchFeatures;
	int VoiceBaudRate;
	AnsiString VoiceMixerMid;
	AnsiString VoiceMixerPid;
	AnsiString VoiceMixerLineID;
	Classes::TList* CloseHandset;
	Classes::TList* EnableCallerID;
	Classes::TList* EnableDistinctiveRing;
	Classes::TList* GenerateDigit;
	Classes::TList* HandsetPlayFormat;
	Classes::TList* HandsetRecordFormat;
	Classes::TList* LineSetPlayFormat;
	Classes::TList* LineSetRecordFormat;
	Classes::TList* OpenHandset;
	Classes::TList* SpeakerPhoneDisable;
	Classes::TList* SpeakerPhoneEnable;
	Classes::TList* SpeakerPhoneMute;
	Classes::TList* SpeakerPhoneSetVolumeGain;
	Classes::TList* SpeakerPhoneUnMute;
	Classes::TList* StartPlay;
	Classes::TList* StartRecord;
	Classes::TList* StopPlay;
	Classes::TList* StopRecord;
	Classes::TList* VoiceAnswer;
	Classes::TList* VoiceDialNumberSetup;
	Classes::TList* VoiceToDataAnswer;
	TLmWaveDriver WaveDriver;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TLmModemSettings
{
	AnsiString Prefix;
	AnsiString Terminator;
	AnsiString DialPrefix;
	AnsiString DialSuffix;
	AnsiString SpeakerVolume_High;
	AnsiString SpeakerVolume_Low;
	AnsiString SpeakerVolume_Med;
	AnsiString SpeakerMode_Dial;
	AnsiString SpeakerMode_Off;
	AnsiString SpeakerMode_On;
	AnsiString SpeakerMode_Setup;
	AnsiString FlowControl_Hard;
	AnsiString FlowControl_Off;
	AnsiString FlowControl_Soft;
	AnsiString ErrorControl_Forced;
	AnsiString ErrorControl_Off;
	AnsiString ErrorControl_On;
	AnsiString ErrorControl_Cellular;
	AnsiString ErrorControl_Cellular_Forced;
	AnsiString Compression_Off;
	AnsiString Compression_On;
	AnsiString Modulation_Bell;
	AnsiString Modulation_CCITT;
	AnsiString Modulation_CCITT_V23;
	AnsiString SpeedNegotiation_On;
	AnsiString SpeedNegotiation_Off;
	AnsiString Pulse;
	AnsiString Tone;
	AnsiString Blind_Off;
	AnsiString Blind_On;
	AnsiString CallSetupFailTimer;
	AnsiString InactivityTimeout;
	AnsiString CompatibilityFlags;
	int ConfigDelay;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TLmModemHardware
{
	AnsiString AutoConfigOverride;
	AnsiString ComPort;
	AnsiString InvalidRDP;
	int IoBaseAddress;
	int InterruptNumber;
	bool PermitShare;
	AnsiString RxFIFO;
	int RxTxBufferSize;
	AnsiString TxFIFO;
	AnsiString Pcmcia;
	AnsiString BusType;
	int PCCARDAttributeMemoryAddress;
	int PCCARDAttributeMemorySize;
	int PCCARDAttributeMemoryOffset;
} ;
#pragma pack(pop)

struct TLmModem;
typedef TLmModem *PLmModem;

#pragma pack(push, 4)
struct TLmModem
{
	AnsiString Inheritance;
	AnsiString AttachedTo;
	AnsiString FriendlyName;
	AnsiString Manufacturer;
	AnsiString Model;
	AnsiString ModemID;
	AnsiString InactivityFormat;
	AnsiString Reset;
	AnsiString DCB;
	AnsiString Properties;
	int ForwardDelay;
	AnsiString VariableTerminator;
	AnsiString InfPath;
	AnsiString InfSection;
	AnsiString ProviderName;
	AnsiString DriverDesc;
	AnsiString ResponsesKeyName;
	AnsiString Default;
	int CallSetupFailTimeout;
	int InactivityTimeout;
	bool SupportsWaitForBongTone;
	bool SupportsWaitForQuiet;
	bool SupportsWaitForDialTone;
	bool SupportsSpeakerVolumeLow;
	bool SupportsSpeakerVolumeMed;
	bool SupportsSpeakerVolumeHigh;
	bool SupportsSpeakerModeOff;
	bool SupportsSpeakerModeDial;
	bool SupportsSpeakerModeOn;
	bool SupportsSpeakerModeSetup;
	bool SupportsSetDataCompressionNegot;
	bool SupportsSetErrorControlProtNegot;
	bool SupportsSetForcedErrorControl;
	bool SupportsSetCellular;
	bool SupportsSetHardwareFlowControl;
	bool SupportsSetSoftwareFlowControl;
	bool SupportsCCITTBellToggle;
	bool SupportsSetSpeedNegotiation;
	bool SupportsSetTonePulse;
	bool SupportsBlindDial;
	bool SupportsSetV21V23;
	bool SupportsModemDiagnostics;
	int MaxDTERate;
	int MaxDCERate;
	AnsiString CurrentCountry;
	int MaximumPortSpeed;
	int PowerDelay;
	int ConfigDelay;
	int BaudRate;
	TLmResponses Responses;
	Classes::TList* Answer;
	Classes::TList* Fax;
	TLmFaxDetails FaxDetails;
	TLmVoiceSettings Voice;
	Classes::TList* Hangup;
	Classes::TList* Init;
	Classes::TList* Monitor;
	TLmModemSettings Settings;
	TLmModemHardware Hardware;
	Classes::TStringList* BaudRates;
	Classes::TStringList* Options;
} ;
#pragma pack(pop)

#pragma option push -b-
enum TApdModemLoadState { mlsGeneral, mlsResponses, mlsAnswer, mlsFax, mlsFaxDetails, mlsVoice, mlsHangup, mlsInit, mlsMonitor, mlsSettings, mlsHardware, mlsBaudRates, mlsOptions, mlsISDN, mlsGSM, mlsNone };
#pragma option pop

#pragma option push -b-
enum TApdResponseLoadState { rlsOK, rlsNegotiationProgress, rlsConnect, rlsError, rlsNoCarrier, rlsNoDialTone, rlsBusy, rlsNoAnswer, rlsRing, rlsVoiceView1, rlsVoiceView2, rlsVoiceView3, rlsVoiceView4, rlsVoiceView5, rlsVoiceView6, rlsVoiceView7, rlsVoiceView8, rlsRingDuration, rlsRingBreak, rlsDate, rlsTime, rlsNumber, rlsName, rlsMessage, rlsSingleRing, rlsDoubleRing, rlsTripleRing, rlsVoice, rlsFax, rlsData, rlsOther, rlsNone };
#pragma option pop

#pragma option push -b-
enum TApdVoiceLoadState { vlsCloseHandset, vlsEnableCallerID, vlsEnableDistinctiveRing, vlsGenerateDigit, vlsHandsetPlayFormat, vlsHandsetRecordFormat, vlsLineSetPlayFormat, vlsLineSetRecordFormat, vlsOpenHandset, vlsSpeakerPhoneDisable, vlsSpeakerPhoneEnable, vlsSpeakerPhoneMute, vlsSpeakerPhoneSetVolumeGain, vlsSpeakerPhoneUnMute, vlsStartPlay, vlsStartRecord, vlsStopPlay, vlsStopRecord, vlsVoiceAnswer, vlsVoiceDialNumberSetup, vlsVoiceToDataAnswer, vlsWaveDriver, vlsWaveFormat, vlsNone };
#pragma option pop

#pragma option push -b-
enum TApdFaxLoadState { flsClass1, flsClass2, flsClass2_0, flsClass1Answer, flsClass2Answer, flsClass2_0Answer, flsNone };
#pragma option pop

class DELPHICLASS TLmModemClass;
class PASCALIMPLEMENTATION TLmModemClass : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	TLmModem LmModem;
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TLmModemClass(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TLmModemClass(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdLmModemNameClass;
class PASCALIMPLEMENTATION TApdLmModemNameClass : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	AnsiString ModemName;
	AnsiString Manufacturer;
	AnsiString Model;
	AnsiString ModemFile;
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TApdLmModemNameClass(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TApdLmModemNameClass(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdLmModemCollectionItem;
class PASCALIMPLEMENTATION TApdLmModemCollectionItem : public Classes::TCollectionItem 
{
	typedef Classes::TCollectionItem inherited;
	
private:
	AnsiString FModemName;
	AnsiString FManufacturer;
	AnsiString FModel;
	AnsiString FModemFile;
	
__published:
	__property AnsiString ModemName = {read=FModemName, write=FModemName};
	__property AnsiString Manufacturer = {read=FManufacturer, write=FManufacturer};
	__property AnsiString Model = {read=FModel, write=FModel};
	__property AnsiString ModemFile = {read=FModemFile, write=FModemFile};
public:
	#pragma option push -w-inl
	/* TCollectionItem.Create */ inline __fastcall virtual TApdLmModemCollectionItem(Classes::TCollection* Collection) : Classes::TCollectionItem(Collection) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TApdLmModemCollectionItem(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdLmModemCollection;
class PASCALIMPLEMENTATION TApdLmModemCollection : public Classes::TCollection 
{
	typedef Classes::TCollection inherited;
	
public:
	TApdLmModemCollectionItem* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TApdLmModemCollectionItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, const TApdLmModemCollectionItem* Value);
	
public:
	HIDESBASE TApdLmModemCollectionItem* __fastcall Add(void);
	__property TApdLmModemCollectionItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	#pragma option push -w-inl
	/* TCollection.Create */ inline __fastcall TApdLmModemCollection(TMetaClass* ItemClass) : Classes::TCollection(ItemClass) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCollection.Destroy */ inline __fastcall virtual ~TApdLmModemCollection(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdLibModem;
class PASCALIMPLEMENTATION TApdLibModem : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	AnsiString FLibModemPath;
	bool FCompleteDbs;
	bool FReadingAttributes;
	Classes::TList* FModemList;
	Classes::TList* FModem;
	int FCurIndex;
	TApdModemLoadState FModemLoadState;
	TApdResponseLoadState FResponseLoadState;
	TApdVoiceLoadState FVoiceLoadState;
	TApdFaxLoadState FFaxLoadState;
	int FCurModemIdx;
	TApdLoadModemRecord FOnLoadModemRecord;
	TApdLoadModem FOnLoadModem;
	int FLastSeq;
	
protected:
	void __fastcall SetLibModemPath(AnsiString v);
	void __fastcall LoadModemListAttribute(System::TObject* oOwner, WideString sName, WideString sValue, bool bSpecified);
	void __fastcall LoadModemListElementBegin(System::TObject* oOwner, WideString sValue);
	void __fastcall LoadModemListElementStart(System::TObject* oOwner, WideString sValue);
	void __fastcall LoadModemListElementEnd(System::TObject* oOwner, WideString sValue);
	void __fastcall AddCommand(Classes::TList* CmdList, WideString sValue);
	void __fastcall LoadModemGeneral(System::TObject* oOwner, WideString sName, WideString sValue, bool bSpecified);
	void __fastcall LoadVoiceSettings(System::TObject* oOwner, WideString sName, WideString sValue, bool bSpecified);
	void __fastcall LoadModemSettings(System::TObject* oOwner, WideString sName, WideString sValue, bool bSpecified);
	void __fastcall LoadHardwareSettings(System::TObject* oOwner, WideString sName, WideString sValue, bool bSpecified);
	void __fastcall LoadFaxClassDetails(const TLmFaxClassDetails &FaxClass, WideString sName, WideString sValue);
	void __fastcall LoadFaxDetails(System::TObject* oOwner, WideString sName, WideString sValue, bool bSpecified);
	void __fastcall LoadModemResponses(System::TObject* oOwner, WideString sName, WideString sValue, bool bSpecified);
	void __fastcall LoadModemAttribute(System::TObject* oOwner, WideString sName, WideString sValue, bool bSpecified);
	void __fastcall LoadModemBeginElement(System::TObject* oOwner, WideString sValue);
	void __fastcall CharData(System::TObject* oOwner, WideString sValue);
	void __fastcall LoadModemElementEnd(System::TObject* oOwner, WideString sValue);
	int __fastcall GetXMLInteger(AnsiString Value, int Default);
	bool __fastcall GetXMLBoolean(AnsiString Value, bool Default);
	void __fastcall LoadModemList(void);
	void __fastcall FreeModemList(void);
	PLmModem __fastcall CreateModem(void);
	void __fastcall FreeModemEntry(int Value);
	void __fastcall FreeModem(void);
	void __fastcall LoadModem(AnsiString FileName, bool Append);
	
public:
	__fastcall virtual TApdLibModem(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdLibModem(void);
	bool __fastcall SelectModem(AnsiString &ModemFile, AnsiString &ModemManufacturer, AnsiString &ModemName, TLmModem &LmModem);
	bool __fastcall IsModemValid(AnsiString ModemFile, AnsiString ModemName);
	int __fastcall CreateNewDetailFile(const AnsiString ModemDetailFile);
	int __fastcall AddModem(const AnsiString ModemDetailFile, const TLmModem &Modem);
	int __fastcall DeleteModem(const AnsiString ModemDetailFile, const AnsiString ModemName);
	int __fastcall GetModem(const AnsiString ModemDetailFile, const AnsiString ModemName, TLmModem &Modem);
	Classes::TStringList* __fastcall GetModems(const AnsiString ModemDetailFile);
	int __fastcall AddModemRecord(const TLmModemName &ModemRecord);
	int __fastcall DeleteModemRecord(const TLmModemName &ModemRecord);
	TApdLmModemCollection* __fastcall GetModemRecords(void);
	__property Classes::TList* Modem = {read=FModem, write=FModem};
	
__published:
	__property AnsiString LibModemPath = {read=FLibModemPath, write=SetLibModemPath};
	__property bool CompleteDbs = {read=FCompleteDbs, nodefault};
	__property TApdLoadModemRecord OnLoadModemRecord = {read=FOnLoadModemRecord, write=FOnLoadModemRecord};
	__property TApdLoadModem OnLoadModem = {read=FOnLoadModem, write=FOnLoadModem};
};


class DELPHICLASS TApdModemSelectionDialog;
class PASCALIMPLEMENTATION TApdModemSelectionDialog : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TButton* btnOK;
	Stdctrls::TButton* btnCancel;
	Stdctrls::TComboBox* cbxManufacturer;
	Stdctrls::TComboBox* cbxName;
	Stdctrls::TLabel* lblText;
	Stdctrls::TLabel* lblManufacturer;
	Stdctrls::TLabel* lblModemName;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormActivate(System::TObject* Sender);
	void __fastcall FormClose(System::TObject* Sender, Forms::TCloseAction &Action);
	void __fastcall cbxManufacturerSelect(System::TObject* Sender);
	void __fastcall btnOKClick(System::TObject* Sender);
	void __fastcall cbxNameChange(System::TObject* Sender);
	
private:
	bool Activated;
	TApdLibModem* ModemList;
	Classes::TStringList* AvailableModems;
	TApdLoadModem OldOnLoadModem;
	TApdLoadModemRecord OldOnLoadModemRecord;
	void __fastcall LoadModemEvent(AnsiString ModemName, AnsiString Manufacturer, AnsiString Model, bool &CanLoad);
	void __fastcall LoadModemRecordEvent(AnsiString ModemName, AnsiString Manufacturer, AnsiString Model, AnsiString ModemFile, bool &CanLoad);
	
public:
	TLmModem LmModem;
	AnsiString SelectedModemName;
	AnsiString SelectedModemManufacturer;
	AnsiString SelectedModemFile;
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TApdModemSelectionDialog(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TApdModemSelectionDialog(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TApdModemSelectionDialog(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TApdModemSelectionDialog(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adlibmdm */
using namespace Adlibmdm;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdLibMdm
