//---------------------------------------------------------------------------

#ifndef form_mainH
#define form_mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TeeDraw3D.hpp"
#include "TeeProcs.hpp"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrm_main : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *Exit1;
	TMenuItem *File1;
	TMenuItem *Help1;
	TMenuItem *About1;
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrm_main(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_main *frm_main;
//---------------------------------------------------------------------------
#endif
