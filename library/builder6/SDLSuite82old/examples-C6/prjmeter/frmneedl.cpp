//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "frmneedl.h"
#include "frmmeter.h"
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
#pragma link "Meter"
#pragma link "Colsel"
#pragma link "colsel"
#pragma link "meter"
#pragma resource "*.dfm"
TFrmNeedLayout *FrmNeedLayout;
//---------------------------------------------------------------------------
__fastcall TFrmNeedLayout::TFrmNeedLayout(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmNeedLayout::SBThicknessChange(TObject *Sender)
{
Meter1->NeedleLayout->Thickness = SBThickness->Position;
}
//---------------------------------------------------------------------------
void __fastcall TFrmNeedLayout::SBNHeadAngleChange(TObject *Sender)
{
Meter1->NeedleLayout->HeadAngle = SBNHeadAngle->Position;
}
//---------------------------------------------------------------------------
void __fastcall TFrmNeedLayout::SBNHeadMidLengChange(TObject *Sender)
{
Meter1->NeedleLayout->HeadMidLeng = SBNHeadMidLeng->Position;
}
//---------------------------------------------------------------------------
void __fastcall TFrmNeedLayout::SBNHeadSizeChange(TObject *Sender)
{
Meter1->NeedleLayout->HeadSize = SBNHeadSize->Position;
}
//---------------------------------------------------------------------------
void __fastcall TFrmNeedLayout::CSNeedleBodyChange(TObject *Sender)
{
Meter1->NeedleLayout->ColorBody = CSNeedleBody->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TFrmNeedLayout::CSNeedleOutlineChange(TObject *Sender)
{
Meter1->NeedleLayout->ColorOutline = CSNeedleOutline->SelColor;
}
//---------------------------------------------------------------------------
