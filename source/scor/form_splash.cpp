//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <config/pubserv.h>
#include <scor/utils.h>
#include "form_splash.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_splash *frm_splash;
//---------------------------------------------------------------------------
__fastcall Tfrm_splash::Tfrm_splash(TComponent* Owner)
    : TForm(Owner)
{
   lbl_version->Caption = "Version " + RELEASE_SOFTWARE_VERSION;
   lbl_model->Caption = SOFTWARE_MODEL_TYPE;
}
//---------------------------------------------------------------------------



