// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdVoipEd.pas' rev: 5.00

#ifndef AdVoipEdHPP
#define AdVoipEdHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdVoIP.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
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

namespace Advoiped
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVoipAudioVideoEditor;
class PASCALIMPLEMENTATION TVoipAudioVideoEditor : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TButton* btnOk;
	Stdctrls::TButton* btnCancel;
	Stdctrls::TGroupBox* GroupBox1;
	Stdctrls::TLabel* Label1;
	Stdctrls::TLabel* Label2;
	Stdctrls::TLabel* Label3;
	Stdctrls::TComboBox* cboxAudioIn;
	Stdctrls::TComboBox* cboxAudioOut;
	Stdctrls::TComboBox* cboxVideoIn;
	Stdctrls::TCheckBox* cboxVideoPlayback;
	Stdctrls::TCheckBox* cboxEnablePreview;
	
protected:
	void __fastcall GetAudioVideoDevices(Advoip::TApdCustomVoIP* Voip);
	
public:
	void __fastcall Initialize(Advoip::TApdCustomVoIP* Voip);
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TVoipAudioVideoEditor(Classes::TComponent* AOwner
		) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TVoipAudioVideoEditor(Classes::TComponent* AOwner
		, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TVoipAudioVideoEditor(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TVoipAudioVideoEditor(HWND ParentWindow) : Forms::TForm(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TVoipAudioVideoEditor* VoipAudioVideoEditor;
extern PACKAGE bool __fastcall EditVoIPAudioVideo(Advoip::TApdCustomVoIP* Voip, const AnsiString Name
	);

}	/* namespace Advoiped */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Advoiped;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdVoipEd
