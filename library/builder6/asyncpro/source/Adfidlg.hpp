// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdFIDlg.pas' rev: 6.00

#ifndef AdFIDlgHPP
#define AdFIDlgHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Mask.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
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

namespace Adfidlg
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TApdFaxJobInfoDialog;
class PASCALIMPLEMENTATION TApdFaxJobInfoDialog : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TGroupBox* GroupBox1;
	Stdctrls::TLabel* Label1;
	Stdctrls::TLabel* Label2;
	Stdctrls::TLabel* Label3;
	Stdctrls::TLabel* Label4;
	Stdctrls::TLabel* Label5;
	Stdctrls::TLabel* Label6;
	Stdctrls::TLabel* lblFileName;
	Stdctrls::TLabel* lblDateSubmitted;
	Stdctrls::TLabel* lblStatus;
	Stdctrls::TLabel* lblSender;
	Stdctrls::TLabel* lblNumJobs;
	Stdctrls::TLabel* lblNextJob;
	Stdctrls::TGroupBox* GroupBox2;
	Stdctrls::TLabel* Label7;
	Stdctrls::TLabel* Label9;
	Stdctrls::TLabel* Label10;
	Stdctrls::TLabel* Label11;
	Stdctrls::TLabel* Label12;
	Stdctrls::TLabel* Label13;
	Stdctrls::TLabel* lblDateNextSend;
	Stdctrls::TLabel* Label15;
	Stdctrls::TLabel* Label16;
	Stdctrls::TLabel* lblJobStatus;
	Stdctrls::TLabel* lblAttemptNum;
	Stdctrls::TLabel* lblLastResult;
	Stdctrls::TEdit* edtPhoneNum;
	Stdctrls::TEdit* edtHeaderLine;
	Stdctrls::TEdit* edtHeaderRecipient;
	Stdctrls::TEdit* edtHeaderTitle;
	Stdctrls::TButton* btnOK;
	Stdctrls::TButton* btnCancel;
	Stdctrls::TButton* btnApply;
	Buttons::TSpeedButton* btnPrev;
	Buttons::TSpeedButton* btnNext;
	Stdctrls::TLabel* Label14;
	Stdctrls::TLabel* lblJobNumber;
	Stdctrls::TButton* btnReset;
	Stdctrls::TLabel* Label8;
	Stdctrls::TLabel* lblDateSample;
	Stdctrls::TLabel* lblTimeSample;
	Stdctrls::TEdit* edtSchedDate;
	Stdctrls::TEdit* edtSchedTime;
	Stdctrls::TLabel* Label17;
	void __fastcall btnPrevClick(System::TObject* Sender);
	void __fastcall btnNextClick(System::TObject* Sender);
	void __fastcall btnApplyClick(System::TObject* Sender);
	void __fastcall EditBoxChange(System::TObject* Sender);
	void __fastcall btnResetClick(System::TObject* Sender);
	void __fastcall btnOKClick(System::TObject* Sender);
	void __fastcall FormKeyDown(System::TObject* Sender, Word &Key, Classes::TShiftState Shift);
	
private:
	bool IsDirty;
	#pragma pack(push, 1)
	Oomisc::TFaxJobHeaderRec JobHeader;
	#pragma pack(pop)
	
	Classes::TFileStream* JobStream;
	Classes::TMemoryStream* JobInfoStream;
	int CurrentJobNum;
	void __fastcall SetDirty(bool NewDirty);
	
public:
	void __fastcall UpdateJobHeader(const Oomisc::TFaxJobHeaderRec &JobHeader);
	void __fastcall UpdateJobInfo(int JobNum);
	Controls::TModalResult __fastcall ShowDialog( System::ShortString &JobFileName,  System::ShortString &DlgCaption);
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TApdFaxJobInfoDialog(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TApdFaxJobInfoDialog(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TApdFaxJobInfoDialog(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TApdFaxJobInfoDialog(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adfidlg */
using namespace Adfidlg;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdFIDlg
