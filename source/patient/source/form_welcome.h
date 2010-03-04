//---------------------------------------------------------------------------
#ifndef form_welcomeH
#define form_welcomeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class Tfrm_patient_welcome : public TForm
{
__published:	// IDE-managed Components
  TPanel *pnl_footer;
  TBitBtn *btnImport;
  TBitBtn *btnEnter;
  TPanel *Panel1;
  TAnimate *anmt_welcome;
  TPanel *pnl_image;
  TLabel *lbl_text2;
  TLabel *lbl_text1;
  TLabel *Label1;
  TImage *img_welcome;
  void __fastcall btnEnterClick(TObject *Sender);
  void __fastcall btnImportClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_patient_welcome(TComponent* Owner);
};

void patient_show_welcome(void);
//---------------------------------------------------------------------------
//extern PACKAGE Tfrm_patient_welcome *frm_patient_welcome;
//---------------------------------------------------------------------------
#endif
