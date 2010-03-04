//---------------------------------------------------------------------------
#ifndef form_patlist_selectH
#define form_patlist_selectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class Tfrm_patlist_select : public TForm
{
__published:	// IDE-managed Components
    TButton *Button1;
    TButton *Button2;
    TButton *Button3;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall Tfrm_patlist_select(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_patlist_select *frm_patlist_select;
//---------------------------------------------------------------------------
#endif
