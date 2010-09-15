// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdFaxCtl.pas' rev: 6.00

#ifndef AdFaxCtlHPP
#define AdFaxCtlHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
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

namespace Adfaxctl
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TMonitorThread;
class DELPHICLASS TApdFaxDriverInterface;
class PASCALIMPLEMENTATION TApdFaxDriverInterface : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
private:
	AnsiString fFileName;
	AnsiString fDocName;
	Classes::TNotifyEvent fOnDocStart;
	Classes::TNotifyEvent fOnDocEnd;
	TMonitorThread* MonitorThread;
	_SECURITY_DESCRIPTOR SecDesc;
	_SECURITY_ATTRIBUTES SecAttr;
	HWND FWindowHandle;
	
protected:
	void __fastcall WndProc(Messages::TMessage &Msg);
	virtual void __fastcall NotifyStartDoc(void);
	virtual void __fastcall NotifyEndDoc(void);
	
public:
	__fastcall virtual TApdFaxDriverInterface(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdFaxDriverInterface(void);
	__property AnsiString DocName = {read=fDocName};
	
__published:
	__property AnsiString FileName = {read=fFileName, write=fFileName};
	__property Classes::TNotifyEvent OnDocStart = {read=fOnDocStart, write=fOnDocStart};
	__property Classes::TNotifyEvent OnDocEnd = {read=fOnDocEnd, write=fOnDocEnd};
};


class PASCALIMPLEMENTATION TMonitorThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
public:
	TApdFaxDriverInterface* Owner;
	unsigned Pipe;
	_OVERLAPPED Overlapped;
	unsigned Semaphore;
	unsigned Events[2];
	virtual void __fastcall Execute(void);
public:
	#pragma option push -w-inl
	/* TThread.Create */ inline __fastcall TMonitorThread(bool CreateSuspended) : Classes::TThread(CreateSuspended) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~TMonitorThread(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adfaxctl */
using namespace Adfaxctl;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdFaxCtl
