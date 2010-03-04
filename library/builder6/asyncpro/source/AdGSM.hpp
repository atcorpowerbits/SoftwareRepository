// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'adgsm.pas' rev: 6.00

#ifndef adgsmHPP
#define adgsmHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdExcept.hpp>	// Pascal unit
#include <AdPacket.hpp>	// Pascal unit
#include <AdPort.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adgsm
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TGSMStates { gsNone, gsConfig, gsSendAll, gsListAll, gsSend, gsSendFStore, gsWrite, gsDelete, gsNofify };
#pragma option pop

#pragma option push -b-
enum TApdSMSStatus { srUnread, srRead, ssUnsent, ssSent, ssAll, ssUnknown };
#pragma option pop

#pragma option push -b-
enum TGSMMode { gmDetect, gmPDU, gmText };
#pragma option pop

typedef Set<TGSMMode, gmDetect, gmText>  TGSMModeSet;

class DELPHICLASS TApdCustomGSMPhone;
typedef void __fastcall (__closure *TApdGSMNextMessageEvent)(TApdCustomGSMPhone* Pager, int ErrorCode, bool &NextMessageReady);

typedef void __fastcall (__closure *TApdGSMNewMessageEvent)(TApdCustomGSMPhone* Pager, int FIndex, AnsiString Message);

typedef void __fastcall (__closure *TApdGSMMessageListEvent)(System::TObject* Sender);

typedef void __fastcall (__closure *TApdGSMCompleteEvent)(TApdCustomGSMPhone* Pager, TGSMStates State, int ErrorCode);

class DELPHICLASS TApdSMSMessage;
class PASCALIMPLEMENTATION TApdSMSMessage : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	int FMessageIndex;
	AnsiString FAddress;
	AnsiString FMessage;
	AnsiString FName;
	TApdSMSStatus FStatus;
	AnsiString FTimeStampStr;
	System::TDateTime FTimeStamp;
	
protected:
	AnsiString __fastcall GetMessageAsPDU();
	void __fastcall SetMessageAsPDU(AnsiString v);
	
public:
	__property AnsiString Address = {read=FAddress, write=FAddress};
	__property AnsiString Message = {read=FMessage, write=FMessage};
	__property AnsiString MessageAsPDU = {read=GetMessageAsPDU, write=SetMessageAsPDU};
	__property int MessageIndex = {read=FMessageIndex, write=FMessageIndex, nodefault};
	__property AnsiString Name = {read=FName, write=FName};
	__property TApdSMSStatus Status = {read=FStatus, write=FStatus, nodefault};
	__property System::TDateTime TimeStamp = {read=FTimeStamp, write=FTimeStamp};
	__property AnsiString TimeStampStr = {read=FTimeStampStr, write=FTimeStampStr};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TApdSMSMessage(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TApdSMSMessage(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdMessageStore;
class PASCALIMPLEMENTATION TApdMessageStore : public Classes::TStringList 
{
	typedef Classes::TStringList inherited;
	
public:
	TApdSMSMessage* operator[](int Index) { return Messages[Index]; }
	
private:
	int FCapacity;
	TApdCustomGSMPhone* FGSMPhone;
	TApdSMSMessage* __fastcall GetSMSMessage(int Index);
	void __fastcall SetMessage(int Index, const TApdSMSMessage* Value);
	void __fastcall SetMSCapacity(const int Value);
	
protected:
	bool JustClearStore;
	virtual int __fastcall GetCapacity(void);
	void __fastcall ClearStore(void);
	
public:
	__fastcall TApdMessageStore(TApdCustomGSMPhone* GSMPhone);
	int __fastcall AddMessage(const AnsiString Dest, const AnsiString Msg);
	virtual void __fastcall Clear(void);
	virtual void __fastcall Delete(int PhoneIndex);
	__property TApdSMSMessage* Messages[int Index] = {read=GetSMSMessage, write=SetMessage/*, default*/};
	__property int Capacity = {read=FCapacity, write=SetMSCapacity, nodefault};
public:
	#pragma option push -w-inl
	/* TStringList.Destroy */ inline __fastcall virtual ~TApdMessageStore(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TApdCustomGSMPhone : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
private:
	TApdGSMNewMessageEvent FOnNewMessage;
	TApdGSMNextMessageEvent FOnNextMessage;
	TApdGSMMessageListEvent FOnMessageList;
	TApdGSMCompleteEvent FOnGSMComplete;
	Adport::TApdCustomComPort* FComPort;
	int FNeedNewMessage;
	AnsiString FRecNewMess;
	bool FConnected;
	int FErrorCode;
	TGSMStates FGSMState;
	TGSMMode FGSMMode;
	unsigned FHandle;
	AnsiString FMessage;
	TApdMessageStore* FMessageStore;
	bool FNotifyOnNewMessage;
	bool FQueryModemOnly;
	bool FQuickConnect;
	bool FConfigList;
	AnsiString FSMSAddress;
	AnsiString FSMSCenter;
	AnsiString FTempWriteMess;
	bool FPDUMode;
	Adpacket::TApdDataPacket* ResponsePacket;
	Adpacket::TApdDataPacket* ErrorPacket;
	Adpacket::TApdDataPacket* NotifyPacket;
	TApdSMSMessage* TempSMSMessage;
	void __fastcall SetMessage(const AnsiString Value);
	void __fastcall SetCenter(const AnsiString Value);
	void __fastcall SetNotifyOnNewMessage(const bool Value);
	void __fastcall SetGSMMode(const TGSMMode NewMode);
	
protected:
	int CmdIndex;
	AnsiString ResponseStr;
	AnsiString NotifyStr;
	TGSMModeSet FSupportedGSMModes;
	void __fastcall CheckPort(void);
	void __fastcall WndProc(Messages::TMessage &Message);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	void __fastcall ResponseStringPacket(System::TObject* Sender, AnsiString Data);
	void __fastcall NotifyStringPacket(System::TObject* Sender, AnsiString Data);
	void __fastcall SetPDUMode(bool v);
	TGSMMode __fastcall GetGSMMode(void);
	void __fastcall ErrorStringPacket(System::TObject* Sender, AnsiString Data);
	void __fastcall DoFail(const AnsiString Msg, const int ErrCode);
	void __fastcall DeleteFromMemoryIndex(int PhoneIndex);
	__property unsigned Handle = {read=FHandle, nodefault};
	void __fastcall SetState(TGSMStates NewState);
	
public:
	__fastcall virtual TApdCustomGSMPhone(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomGSMPhone(void);
	void __fastcall SendSMSMessage(void);
	void __fastcall SendAllMessages(void);
	void __fastcall ListAllMessages(void);
	void __fastcall Connect(void);
	void __fastcall SendFromMemory(int TheIndex);
	void __fastcall WriteToMemory(const AnsiString Dest, const AnsiString Msg);
	void __fastcall ProcessResponse(void);
	void __fastcall Synchronize(void);
	void __fastcall QueryModem(void);
	AnsiString __fastcall StatusToStr(TApdSMSStatus StatusString);
	__property Adport::TApdCustomComPort* ComPort = {read=FComPort, write=FComPort};
	__property AnsiString SMSAddress = {read=FSMSAddress, write=FSMSAddress};
	__property AnsiString SMSMessage = {read=FMessage, write=SetMessage};
	__property AnsiString SMSCenter = {read=FSMSCenter, write=SetCenter};
	__property bool NotifyOnNewMessage = {read=FNotifyOnNewMessage, write=SetNotifyOnNewMessage, default=0};
	__property TApdMessageStore* MessageStore = {read=FMessageStore, write=FMessageStore};
	__property bool QuickConnect = {read=FQuickConnect, write=FQuickConnect, default=0};
	__property TGSMMode GSMMode = {read=GetGSMMode, write=SetGSMMode, nodefault};
	__property int SMSErrorCode = {read=FErrorCode, nodefault};
	__property TGSMStates GSMState = {read=FGSMState, nodefault};
	__property TApdGSMNewMessageEvent OnNewMessage = {read=FOnNewMessage, write=FOnNewMessage};
	__property TApdGSMNextMessageEvent OnNextMessage = {read=FOnNextMessage, write=FOnNextMessage};
	__property TApdGSMMessageListEvent OnMessageList = {read=FOnMessageList, write=FOnMessageList};
	__property TApdGSMCompleteEvent OnGSMComplete = {read=FOnGSMComplete, write=FOnGSMComplete};
};


class DELPHICLASS TApdGSMPhone;
class PASCALIMPLEMENTATION TApdGSMPhone : public TApdCustomGSMPhone 
{
	typedef TApdCustomGSMPhone inherited;
	
public:
	__fastcall virtual TApdGSMPhone(Classes::TComponent* Owner);
	__fastcall virtual ~TApdGSMPhone(void);
	
__published:
	__property ComPort ;
	__property QuickConnect  = {default=0};
	__property GSMMode ;
	__property SMSAddress ;
	__property SMSMessage ;
	__property SMSCenter ;
	__property NotifyOnNewMessage  = {default=0};
	__property OnNewMessage ;
	__property OnNextMessage ;
	__property OnMessageList ;
	__property OnGSMComplete ;
};


//-- var, const, procedure ---------------------------------------------------
static const Word ApdGSMResponse = 0x464;
extern PACKAGE AnsiString __fastcall PDUToString(AnsiString v);
extern PACKAGE AnsiString __fastcall StringToPDU(AnsiString v);

}	/* namespace Adgsm */
using namespace Adgsm;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// adgsm
