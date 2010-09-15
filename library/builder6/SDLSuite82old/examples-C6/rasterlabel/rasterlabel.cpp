//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("rasterlabel.res");
USEFORM("mainfrm.cpp", FrmMain);
USEFORM("control.cpp", FrmControl);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TFrmMain), &FrmMain);
                 Application->CreateForm(__classid(TFrmControl), &FrmControl);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
