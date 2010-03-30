// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdPacket.pas' rev: 6.00

#ifndef AdPacketHPP
#define AdPacketHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AwUser.hpp>	// Pascal unit
#include <AdPort.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adpacket
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TPacketStartCond { scString, scAnyData };
#pragma option pop

#pragma option push -b-
enum TPacketEndCond { ecString, ecPacketSize };
#pragma option pop

typedef Set<TPacketEndCond, ecString, ecPacketSize>  TPacketEndSet;

class DELPHICLASS TApdDataPacketManagerList;
class DELPHICLASS TApdDataPacketManager;
class PASCALIMPLEMENTATION TApdDataPacketManagerList : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Classes::TList* ManagerList;
	
public:
	__fastcall TApdDataPacketManagerList(void);
	__fastcall virtual ~TApdDataPacketManagerList(void);
	void __fastcall Insert(TApdDataPacketManager* Value);
	void __fastcall Remove(TApdDataPacketManager* Value);
	TApdDataPacketManager* __fastcall GetPortManager(Adport::TApdCustomComPort* ComPort);
};


class DELPHICLASS TApdDataPacket;
#pragma option push -b-
enum TPacketMode { dpIdle, dpWaitStart, dpCollecting };
#pragma option pop

typedef void __fastcall (__closure *TPacketNotifyEvent)(System::TObject* Sender, void * Data, int Size);

typedef void __fastcall (__closure *TStringPacketNotifyEvent)(System::TObject* Sender, AnsiString Data);

class PASCALIMPLEMENTATION TApdDataPacket : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
private:
	TApdDataPacketManager* fManager;
	TPacketStartCond fStartCond;
	TPacketEndSet fEndCond;
	AnsiString fStartString;
	AnsiString fEndString;
	Adport::TApdCustomComPort* fComPort;
	TPacketMode fMode;
	int fPacketSize;
	TPacketNotifyEvent fOnPacket;
	TStringPacketNotifyEvent fOnStringPacket;
	Classes::TNotifyEvent fOnTimeOut;
	int fTimeOut;
	int fDataSize;
	int fBeginMatch;
	bool fAutoEnable;
	bool fIgnoreCase;
	bool fEnabled;
	bool fIncludeStrings;
	char *PacketBuffer;
	int StartMatchPos;
	int EndMatchPos;
	int EndMatchStart;
	int LocalPacketSize;
	AnsiString WildStartString;
	AnsiString WildEndString;
	AnsiString InternalStartString;
	AnsiString InternalEndString;
	bool WillCollect;
	bool EnablePending;
	bool HaveCapture;
	bool FSyncEvents;
	bool FDataMatch;
	bool FTimedOut;
	int FEnableTimeout;
	int FEnableTimer;
	bool FFlushOnTimeout;
	
protected:
	void __fastcall SetComPort(const Adport::TApdCustomComPort* NewComPort);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	void __fastcall SetEnabled(bool Value);
	void __fastcall SetMode(TPacketMode Value);
	void __fastcall SetEndCond(const TPacketEndSet Value);
	void __fastcall SetEndString(AnsiString Value);
	void __fastcall SetFlushOnTimeout(const bool v);
	void __fastcall ProcessData(int StartPtr);
	void __fastcall Packet(TPacketEndCond Reason);
	void __fastcall TimedOut(void);
	void __fastcall DoTimeout(void);
	void __fastcall DoPacket(void);
	void __fastcall NotifyRemove(int Data);
	void __fastcall Resync(void);
	void __fastcall CancelMatch(void);
	virtual void __fastcall Loaded(void);
	void __fastcall LogPacketEvent(Oomisc::TDispatchSubType Event, void * Data, int DataSize);
	__property int BeginMatch = {read=fBeginMatch, nodefault};
	__property TApdDataPacketManager* Manager = {read=fManager, write=fManager};
	__property TPacketMode Mode = {read=fMode, write=SetMode, nodefault};
	void __fastcall Enable(void);
	void __fastcall Disable(void);
	void __fastcall TriggerHandler(unsigned Msg, unsigned wParam, int lParam);
	
public:
	__fastcall virtual TApdDataPacket(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdDataPacket(void);
	void __fastcall GetCollectedString(AnsiString &Data);
	void __fastcall GetCollectedData(void * &Data, int &Size);
	__property TApdDataPacketManager* InternalManager = {read=fManager};
	__property int EnableTimeout = {read=FEnableTimeout, write=FEnableTimeout, default=0};
	__property bool FlushOnTimeout = {read=FFlushOnTimeout, write=SetFlushOnTimeout, default=1};
	__property bool SyncEvents = {read=FSyncEvents, write=FSyncEvents, nodefault};
	__property TPacketMode PacketMode = {read=fMode, nodefault};
	bool __fastcall WaitForString(AnsiString &Data);
	bool __fastcall WaitForPacket(void * &Data, int &Size);
	
__published:
	__property bool Enabled = {read=fEnabled, write=SetEnabled, nodefault};
	__property bool AutoEnable = {read=fAutoEnable, write=fAutoEnable, default=1};
	__property TPacketStartCond StartCond = {read=fStartCond, write=fStartCond, default=0};
	__property TPacketEndSet EndCond = {read=fEndCond, write=SetEndCond, default=0};
	__property AnsiString StartString = {read=fStartString, write=fStartString};
	__property AnsiString EndString = {read=fEndString, write=SetEndString};
	__property bool IgnoreCase = {read=fIgnoreCase, write=fIgnoreCase, default=1};
	__property Adport::TApdCustomComPort* ComPort = {read=fComPort, write=SetComPort};
	__property int PacketSize = {read=fPacketSize, write=fPacketSize, nodefault};
	__property bool IncludeStrings = {read=fIncludeStrings, write=fIncludeStrings, default=1};
	__property int TimeOut = {read=fTimeOut, write=fTimeOut, default=2184};
	__property TPacketNotifyEvent OnPacket = {read=fOnPacket, write=fOnPacket};
	__property TStringPacketNotifyEvent OnStringPacket = {read=fOnStringPacket, write=fOnStringPacket};
	__property Classes::TNotifyEvent OnTimeout = {read=fOnTimeOut, write=fOnTimeOut};
};


class PASCALIMPLEMENTATION TApdDataPacketManager : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Classes::TList* PacketList;
	Adport::TApdCustomComPort* fComPort;
	bool HandlerInstalled;
	bool fEnabled;
	int BufferPtr;
	char *fDataBuffer;
	int dpDataBufferSize;
	TApdDataPacket* fCapture;
	int Timer;
	bool fInEvent;
	bool NotifyPending;
	int NotifyStart;
	bool EnablePending;
	bool FKeepAlive;
	HWND FWindowHandle;
	
protected:
	void __fastcall WndProc(Messages::TMessage &Msg);
	void __fastcall DisposeBuffer(void);
	void __fastcall NotifyData(int NewDataStart);
	void __fastcall EnablePackets(void);
	void __fastcall DisablePackets(void);
	void __fastcall PacketTriggerHandler(unsigned Msg, unsigned wParam, int lParam);
	void __fastcall PortOpenClose(System::TObject* CP, bool Opening);
	void __fastcall PortOpenCloseEx(System::TObject* CP, Adport::TApdCallbackType CallbackType);
	void __fastcall SetInEvent(bool Value);
	void __fastcall SetEnabled(bool Value);
	
public:
	__fastcall TApdDataPacketManager(Adport::TApdCustomComPort* ComPort);
	__fastcall virtual ~TApdDataPacketManager(void);
	void __fastcall Enable(void);
	void __fastcall EnableIfPending(void);
	void __fastcall Disable(void);
	void __fastcall Insert(TApdDataPacket* Value);
	void __fastcall Remove(TApdDataPacket* Value);
	void __fastcall RemoveData(int Start, int Size);
	void __fastcall SetCapture(TApdDataPacket* Value, int TimeOut);
	void __fastcall ReleaseCapture(TApdDataPacket* Value);
	__property char * DataBuffer = {read=fDataBuffer};
	__property Adport::TApdCustomComPort* ComPort = {read=fComPort};
	__property bool Enabled = {read=fEnabled, write=SetEnabled, nodefault};
	__property bool InEvent = {read=fInEvent, write=SetInEvent, nodefault};
	__property bool KeepAlive = {read=FKeepAlive, write=FKeepAlive, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
static const char EscapeCharacter = '\x5c';
static const char WildCardCharacter = '\x3f';
static const bool adpDefEnabled = true;
static const bool adpDefIgnoreCase = true;
static const bool adpDefIncludeStrings = true;
static const bool adpDefAutoEnable = true;
#define adpDefStartCond (TPacketStartCond)(0)
static const Word adpDefTimeOut = 0x888;
static const bool apdDefFlushOnTimeout = true;

}	/* namespace Adpacket */
using namespace Adpacket;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdPacket
