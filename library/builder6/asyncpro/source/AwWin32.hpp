// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AwWin32.pas' rev: 6.00

#ifndef AwWin32HPP
#define AwWin32HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AwUser.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <AdSocket.hpp>	// Pascal unit
#include <AdWUtil.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Awwin32
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TApdWin32Dispatcher;
class PASCALIMPLEMENTATION TApdWin32Dispatcher : public Awuser::TApdBaseDispatcher 
{
	typedef Awuser::TApdBaseDispatcher inherited;
	
protected:
	_OVERLAPPED ReadOL;
	_OVERLAPPED WriteOL;
	virtual int __fastcall EscapeComFunction(int Func);
	virtual int __fastcall FlushCom(int Queue);
	virtual int __fastcall GetComError(_COMSTAT &Stat);
	virtual unsigned __fastcall GetComEventMask(int EvtMask);
	virtual int __fastcall GetComState(_DCB &DCB);
	virtual int __fastcall SetComState(_DCB &DCB);
	virtual int __fastcall ReadCom(char * Buf, int Size);
	virtual int __fastcall WriteCom(char * Buf, int Size);
	virtual bool __fastcall SetupCom(int InSize, int OutSize);
	virtual void __fastcall StartDispatcher(void);
	virtual void __fastcall StopDispatcher(void);
	virtual bool __fastcall WaitComEvent(unsigned &EvtMask, Windows::POverlapped lpOverlapped);
	
public:
	virtual int __fastcall CloseCom(void);
	virtual int __fastcall OpenCom(char * ComName, unsigned InQueue, unsigned OutQueue);
	virtual int __fastcall ProcessCommunications(void);
public:
	#pragma option push -w-inl
	/* TApdBaseDispatcher.Create */ inline __fastcall TApdWin32Dispatcher(System::TObject* Owner) : Awuser::TApdBaseDispatcher(Owner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdBaseDispatcher.Destroy */ inline __fastcall virtual ~TApdWin32Dispatcher(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdTAPI32Dispatcher;
class PASCALIMPLEMENTATION TApdTAPI32Dispatcher : public TApdWin32Dispatcher 
{
	typedef TApdWin32Dispatcher inherited;
	
public:
	__fastcall TApdTAPI32Dispatcher(System::TObject* Owner, int InCid);
	virtual int __fastcall OpenCom(char * ComName, unsigned InQueue, unsigned OutQueue);
public:
	#pragma option push -w-inl
	/* TApdBaseDispatcher.Destroy */ inline __fastcall virtual ~TApdTAPI32Dispatcher(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Awwin32 */
using namespace Awwin32;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AwWin32
