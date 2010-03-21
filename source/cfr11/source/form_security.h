//---------------------------------------------------------------------------

#ifndef form_securityH
#define form_securityH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class Tfrm_security : public TForm
{
__published:	// IDE-managed Components
   TImage *img_security;
   TPanel *pnl_security;
   TLabel *lbl_security;
   TPanel *pnl_security_fields;
   TEdit *edt_security_password;
   TLabel *lbl_security_password;
   TLabel *lbl_security_username;
   TEdit *edt_security_username;
   TSpeedButton *btnCancel;
   TSpeedButton *btnOk;
   void __fastcall btnOkClick(TObject *Sender);
   void __fastcall FormShow(TObject *Sender);
   void __fastcall btnCancelClick(TObject *Sender);
   void __fastcall FormKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
   __fastcall Tfrm_security(TComponent* Owner);
   bool security_validate();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_security *frm_security;

extern String username;
extern String password;
//---------------------------------------------------------------------------
#endif


