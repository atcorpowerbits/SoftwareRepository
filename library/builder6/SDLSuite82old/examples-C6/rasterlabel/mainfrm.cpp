//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mainfrm.h"
#include "control.h"
/********************** set-up of include pathes ****************************
Please note: you have to set up the pathes to the include files before
this sample program can be compiled:
Use the command "Project/Options", select the "Directories/Conditional"
tab, and add the required packages to the "include path"

example:
   if you installed the packages into the default directory, the
   include path for the BasePack will be: "C:\SDLSuite\basepack\C6"

More information can be found in the following FAQ article:
   http://forum.sdlsuite.com/read.php?f=2&i=21&t=21
*****************************************************************************/
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "rasterlab"
#pragma resource "*.dfm"
TFrmMain *FrmMain;
//---------------------------------------------------------------------------
__fastcall TFrmMain::TFrmMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::Timer1Timer(TObject *Sender)
{
AnsiString astr;

astr = FrmControl->FillPlaceholder (FrmControl->EdText->Text);
RLab1->Text = astr;
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::RLab1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (Shift.Contains(ssRight))
  {
  FrmControl->Show();
  BorderStyle = bsSizeable;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::RLab1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if (Shift.Contains(ssLeft))
  {
  FrmMain->RLab1->PosX = X;
  FrmMain->RLab1->PosY = Y;
  }
}
//---------------------------------------------------------------------------
