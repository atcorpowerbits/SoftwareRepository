//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include <math.h>

#include "frmmeter.h"
#include "frmneedl.h"
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
#pragma link "NumLab"
#pragma link "Meter"
#pragma link "Colsel"
#pragma link "colsel"
#pragma link "meter"
#pragma link "numlab"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBValueChange(TObject *Sender)

{
Meter1->Value = 0.1*SBValue->Position;
Meter2->Value = 0.1*SBValue->Position;
Meter3->Value = 0.1*SBValue->Position;
NumLab1->Value = 0.1*SBValue->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CSMeterBkgndChange(TObject *Sender)
{
Meter1->ColorBakG = CSMeterBkgnd->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CSColorCoverChange(TObject *Sender)
{
Meter1->ColorCover = CSColorCover->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CSColorScaleChange(TObject *Sender)
{
Meter1->ColorScale = CSColorScale->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CSColorTextChange(TObject *Sender)
{
Meter1->Font->Color = CSColorText->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBRaisedClick(TObject *Sender)
{
Meter1->FrameStyle = fsRaised;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBLoweredClick(TObject *Sender)
{
Meter1->FrameStyle = fsLowered;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RbEmbossedClick(TObject *Sender)
{
Meter1->FrameStyle = fsEmbossed;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBEngravedClick(TObject *Sender)
{
Meter1->FrameStyle = fsEngraved;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBSimpleClick(TObject *Sender)
{
Meter1->FrameStyle = fsSimple;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBNoneClick(TObject *Sender)
{
Meter1->FrameStyle = fsNone;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBColBakClick(TObject *Sender)
{
if (ColorDialog1->Execute())
  {
  CSMeterBkgnd->SelColor = ColorDialog1->Color;
  Meter1->ColorBakG = CSMeterBkgnd->SelColor;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBMinValChange(TObject *Sender)
{
Meter1->MeterMinValue = -SBMinVal->Position;
SBValue->Position = ceil(10*Meter1->Value);
if ((Meter1->MeterMaxValue - Meter1->MeterMinValue) > 20)
  Meter1->MeterDecPlaces = 0;
  else Meter1->MeterDecPlaces = 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBMaxValChange(TObject *Sender)
{
Meter1->MeterMaxValue = 110-SBMaxVal->Position;
SBValue->Position = ceil(10*Meter1->Value);
if ((Meter1->MeterMaxValue - Meter1->MeterMinValue) > 20)
  Meter1->MeterDecPlaces = 0;
  else Meter1->MeterDecPlaces = 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EdCaptionChange(TObject *Sender)
{
Meter1->Caption = EdCaption->Text;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBShortTicksClick(TObject *Sender)
{
Meter1->MeterShortTicks = CBShortTicks->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBScaleLineClick(TObject *Sender)
{
Meter1->MeterScaleLine = CBScaleLine->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBLimHighClick(TObject *Sender)
{
Meter1->LimWatchHighOn = CBLimHigh->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBLimLowClick(TObject *Sender)
{
Meter1->LimWatchLowOn = CBLimLow->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButNeedleLayoutClick(TObject *Sender)
{
FrmNeedLayout->Meter1->ColorBakG = Meter1->ColorBakG;
FrmNeedLayout->Meter1->Font->Color = Meter1->Font->Color;
FrmNeedLayout->Meter1->LimWatchPsvColor = Meter1->LimWatchPsvColor;
FrmNeedLayout->CSNeedleBody->SelColor = Meter1->NeedleLayout->ColorBody;
FrmNeedLayout->CSNeedleOutline->SelColor = Meter1->NeedleLayout->ColorOutline;
FrmNeedLayout->Meter1->NeedleLayout->ColorBody = Meter1->NeedleLayout->ColorBody;
FrmNeedLayout->Meter1->NeedleLayout->ColorOutline = Meter1->NeedleLayout->ColorOutline;
FrmNeedLayout->Meter1->ColorScale = Meter1->ColorScale;
FrmNeedLayout->Meter1->NeedleLayout->HeadSize = Meter1->NeedleLayout->HeadSize;
FrmNeedLayout->Meter1->NeedleLayout->HeadMidLeng = Meter1->NeedleLayout->HeadMidLeng;
FrmNeedLayout->Meter1->NeedleLayout->HeadAngle = Meter1->NeedleLayout->HeadAngle;
FrmNeedLayout->Meter1->NeedleLayout->Thickness = Meter1->NeedleLayout->Thickness;
FrmNeedLayout->Meter1->AnchorCovered = Meter1->AnchorCovered;
FrmNeedLayout->Meter1->AnchorSize = Meter1->AnchorSize;
FrmNeedLayout->SBThickness->Position = Meter1->NeedleLayout->Thickness;
FrmNeedLayout->SBNHeadAngle->Position = Meter1->NeedleLayout->HeadAngle;
FrmNeedLayout->SBNHeadMidLeng->Position = Meter1->NeedleLayout->HeadMidLeng;
FrmNeedLayout->SBNHeadSize->Position = Meter1->NeedleLayout->HeadSize;
if (FrmNeedLayout->ShowModal() == mrOk)
  {
  Meter1->ColorBakG = FrmNeedLayout->Meter1->ColorBakG;
  Meter1->NeedleLayout->ColorBody = FrmNeedLayout->Meter1->NeedleLayout->ColorBody;
  Meter1->NeedleLayout->ColorOutline = FrmNeedLayout->Meter1->NeedleLayout->ColorOutline;
  Meter1->ColorScale = FrmNeedLayout->Meter1->ColorScale;
  Meter1->NeedleLayout->HeadSize = FrmNeedLayout->Meter1->NeedleLayout->HeadSize;
  Meter1->NeedleLayout->HeadMidLeng = FrmNeedLayout->Meter1->NeedleLayout->HeadMidLeng;
  Meter1->NeedleLayout->HeadAngle = FrmNeedLayout->Meter1->NeedleLayout->HeadAngle;
  Meter1->NeedleLayout->Thickness = FrmNeedLayout->Meter1->NeedleLayout->Thickness;
  Meter1->AnchorCovered = FrmNeedLayout->Meter1->AnchorCovered;
  Meter1->AnchorSize = FrmNeedLayout->Meter1->AnchorSize;
  };
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RGLayoutClick(TObject *Sender)
{
switch (RGLayout->ItemIndex)
  {
  case 0: Meter1->MeterLayout = mlCirc90; break;
  case 1: Meter1->MeterLayout = mlCirc120; break;
  case 2: Meter1->MeterLayout = mlCirc180; break;
  case 3: Meter1->MeterLayout = mlCirc270; break;
  case 4: Meter1->MeterLayout = mlCirc300; break;
  case 5: Meter1->MeterLayout = mlCirc360; break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBThreshLowChange(TObject *Sender)
{
Meter1->ThresholdLow = Meter1->MeterMinValue+(100.0-SBThreshLow->Position)/100.0*(Meter1->MeterMaxValue-Meter1->MeterMinValue);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBThreshHighChange(TObject *Sender)
{
Meter1->ThresholdHigh = Meter1->MeterMinValue+(100.0-SBThreshHigh->Position)/100.0*(Meter1->MeterMaxValue-Meter1->MeterMinValue);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBVisThreshClick(TObject *Sender)
{
Meter1->ScaleBkVisible = CBVisThresh->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBarValue2Change(TObject *Sender)
{
Meter1->ValueSec = 0.1*SBarValue2->Position;
Meter2->ValueSec = 0.1*SBarValue2->Position;
Meter3->ValueSec = 0.1*SBarValue2->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBAnchorSizeChange(TObject *Sender)
{
Meter1->AnchorSize = SBAnchorSize->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBAnchorOnClick(TObject *Sender)
{
Meter1->AnchorCovered = CBAnchorOn->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButNeedle2LayoutClick(TObject *Sender)
{
FrmNeedLayout->Meter1->ColorBakG = Meter1->ColorBakG;
FrmNeedLayout->Meter1->Font->Color = Meter1->Font->Color;
FrmNeedLayout->Meter1->LimWatchPsvColor = Meter1->LimWatchPsvColor;
FrmNeedLayout->CSNeedleBody->SelColor = Meter1->NeedleLayoutSec->ColorBody;
FrmNeedLayout->CSNeedleOutline->SelColor = Meter1->NeedleLayoutSec->ColorOutline;
FrmNeedLayout->Meter1->NeedleLayout->ColorBody = Meter1->NeedleLayoutSec->ColorBody;
FrmNeedLayout->Meter1->NeedleLayout->ColorOutline = Meter1->NeedleLayoutSec->ColorOutline;
FrmNeedLayout->Meter1->ColorScale = Meter1->ColorScale;
FrmNeedLayout->Meter1->NeedleLayout->HeadSize = Meter1->NeedleLayoutSec->HeadSize;
FrmNeedLayout->Meter1->NeedleLayout->HeadMidLeng = Meter1->NeedleLayoutSec->HeadMidLeng;
FrmNeedLayout->Meter1->NeedleLayout->HeadAngle = Meter1->NeedleLayoutSec->HeadAngle;
FrmNeedLayout->Meter1->NeedleLayout->Thickness = Meter1->NeedleLayoutSec->Thickness;
FrmNeedLayout->Meter1->AnchorCovered = Meter1->AnchorCovered;
FrmNeedLayout->Meter1->AnchorSize = Meter1->AnchorSize;
FrmNeedLayout->SBThickness->Position = Meter1->NeedleLayoutSec->Thickness;
FrmNeedLayout->SBNHeadAngle->Position = Meter1->NeedleLayoutSec->HeadAngle;
FrmNeedLayout->SBNHeadMidLeng->Position = Meter1->NeedleLayoutSec->HeadMidLeng;
FrmNeedLayout->SBNHeadSize->Position = Meter1->NeedleLayoutSec->HeadSize;
if (FrmNeedLayout->ShowModal() == mrOk)
  {
  Meter1->ColorBakG = FrmNeedLayout->Meter1->ColorBakG;
  Meter1->ColorScale = FrmNeedLayout->Meter1->ColorScale;
  Meter1->NeedleLayoutSec->ColorBody = FrmNeedLayout->Meter1->NeedleLayout->ColorBody;
  Meter1->NeedleLayoutSec->ColorOutline = FrmNeedLayout->Meter1->NeedleLayout->ColorOutline;
  Meter1->NeedleLayoutSec->HeadSize = FrmNeedLayout->Meter1->NeedleLayout->HeadSize;
  Meter1->NeedleLayoutSec->HeadMidLeng = FrmNeedLayout->Meter1->NeedleLayout->HeadMidLeng;
  Meter1->NeedleLayoutSec->HeadAngle = FrmNeedLayout->Meter1->NeedleLayout->HeadAngle;
  Meter1->NeedleLayoutSec->Thickness = FrmNeedLayout->Meter1->NeedleLayout->Thickness;
  Meter1->AnchorCovered = FrmNeedLayout->Meter1->AnchorCovered;
  Meter1->AnchorSize = FrmNeedLayout->Meter1->AnchorSize;
  };

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
if (Meter::IsLightEd)
  {
  SBarValue2->Enabled = false;
  LblSecNeedle->Enabled = false;
  BButNeedle2Layout->Enabled = false;
  }
}
//---------------------------------------------------------------------------

