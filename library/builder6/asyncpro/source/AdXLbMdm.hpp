// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdXLbMdm.pas' rev: 6.00

#ifndef AdXLbMdmHPP
#define AdXLbMdmHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdLibMdm.hpp>	// Pascal unit
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
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adxlbmdm
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TApdModemCapDetail;
class PASCALIMPLEMENTATION TApdModemCapDetail : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
private:
	Classes::TFileStream* DetailStream;
	bool __fastcall AtEOF(void);
	int __fastcall ExportDetailXML(const Adlibmdm::TLmModem &Modem);
	void __fastcall FixupModemcap(Classes::TStringList* &List);
	AnsiString __fastcall ReadLine();
	void __fastcall WriteLine(const AnsiString Str);
	void __fastcall WriteXMLStr(const AnsiString Str, const AnsiString sVal);
	AnsiString __fastcall XMLize(const AnsiString S);
	AnsiString __fastcall XMLizeInt(int I);
	AnsiString __fastcall XMLizeBool(bool B);
	AnsiString __fastcall UnXMLize(const AnsiString S);
	
public:
	__fastcall virtual TApdModemCapDetail(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdModemCapDetail(void);
	int __fastcall CreateNewDetailFile(const AnsiString ModemDetailFile);
	int __fastcall AddModem(const AnsiString ModemDetailFile, const Adlibmdm::TLmModem &Modem);
	int __fastcall DeleteModem(const AnsiString ModemDetailFile, const AnsiString ModemName);
	int __fastcall AddModemRecord(const AnsiString ModemCapIndex, const Adlibmdm::TLmModemName &ModemRecord);
	int __fastcall DeleteModemRecord(const AnsiString ModemCapIndex, const Adlibmdm::TLmModemName &ModemRecord);
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adxlbmdm */
using namespace Adxlbmdm;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdXLbMdm
