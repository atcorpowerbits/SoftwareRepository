//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "maingf.h"
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
#pragma link "Colsel"
#pragma link "NumIO"
#pragma link "GradFl"
#pragma link "gradfl"
#pragma link "colsel"
#pragma link "numio"
#pragma resource "*.dfm"
TFrmGradFill *FrmGradFill;
//---------------------------------------------------------------------------
__fastcall TFrmGradFill::TFrmGradFill(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmGradFill::BButExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TFrmGradFill::SBToggleColorsClick(TObject *Sender)
{
TColor ColorDummy;

GFQuad->ColorFlipped = ! (GFQuad->ColorFlipped);
ColorDummy = ColSel1->SelColor;
ColSel1->SelColor = ColSel2->SelColor;
ColSel2->SelColor = ColorDummy;
}
//---------------------------------------------------------------------------
void __fastcall TFrmGradFill::ColSel1Change(TObject *Sender)
{
GFQuad->ColorFirst = ColSel1->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TFrmGradFill::ColSel2Change(TObject *Sender)
{
GFQuad->ColorLast = ColSel2->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TFrmGradFill::NIONumColorsChange(TObject *Sender)
{
GFQuad->NrColors = int(NIONumColors->Value);
}
//---------------------------------------------------------------------------
void __fastcall TFrmGradFill::CBoxGridModeClick(TObject *Sender)
{
GFQuad->GridMode = TGridMode(CBoxGridMode->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TFrmGradFill::CselGridClick(TObject *Sender)
{
GFQuad->GridColor = CselGrid->SelColor;
}
//---------------------------------------------------------------------------

void __fastcall TFrmGradFill::RGSelectClick(TObject *Sender)
{
GFQuad->FillType = TGradType(RGSelect->ItemIndex);
}
//---------------------------------------------------------------------------

