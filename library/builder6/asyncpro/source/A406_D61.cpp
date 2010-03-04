//---------------------------------------------------------------------------

#include <basepch.h>
#pragma hdrstop
USEFORMNS("AdAbout.pas", Adabout, ApdAboutForm);
USEFORMNS("AdPEdit0.pas", Adpedit0, AdPEdit);
USEFORMNS("AdStatE0.pas", Adstate0, frmConditionEdit);
USEFORMNS("AdStatEd.pas", Adstated, frmStateEdit);
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
        return 1;
}
//---------------------------------------------------------------------------
