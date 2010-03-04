//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("kohmap.res");
USEFORM("ukohonen.cpp", FrmSom);
USEFORM("uprogres.cpp", FrmProgress);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TFrmSom), &FrmSom);
                 Application->CreateForm(__classid(TFrmProgress), &FrmProgress);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
