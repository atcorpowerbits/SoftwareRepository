//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "uplot3d.h"
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
#pragma link "Colsel"
#pragma link "NumLab"
#pragma link "plot3d"
#pragma link "colsel"
#pragma link "numlab"
#pragma resource "*.dfm"
TForm1 *Form1;

const int XRes = 50;
const int YRes = 30;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Plot3D1MouseAction(TObject *Sender, int &CenterX,
      int &CenterY, double &RotXAngle, double &RotZAngle,
      double &Magnification, TShiftState Shift)
{
NLabX->Value = RotXAngle;
NLabZ->Value = RotZAngle;
NLabMag->Value = Magnification;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)

{
int i;
int j;

Plot3D1->GridMat->Resize (XRes,YRes);
for (i=1; i<=XRes; i++)
  {
  for (j=1; j<=YRes; j++)
    {
    Plot3D1->GridMat->Elem[i][j] = sin(i*0.5)*cos(0.15*j)+0.01*(i-(XRes / 2))*(j-(YRes / 2)) +
                                  13*exp(-0.04*((i-(XRes / 2))*(i-(XRes / 2))+(j-(YRes / 2))*(j-(YRes / 2))))+
                                  10*exp(-0.02*((i-(XRes / 3))*(i-(XRes / 3))+(j-3*(YRes / 5))*(j-3*(YRes / 5))))-1;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrBarAngleXChange(TObject *Sender)
{
Plot3D1->ViewAngleX = ScrBarAngleX->Position;
NLabX->Value = ScrBarAngleX->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrBarAngleZChange(TObject *Sender)
{
Plot3D1->ViewAngleZ = ScrBarAngleZ->Position;
NLabZ->Value = ScrBarAngleZ->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrBarMagnifChange(TObject *Sender)
{
Plot3D1->Magnification = 0.01*ScrBarMagnif->Position;
NLabMag->Value = 0.01*ScrBarMagnif->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CSelHighChange(TObject *Sender)
{
Plot3D1->ColorHigh = CSelHigh->SelColor;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CselMidChange(TObject *Sender)
{
Plot3D1->ColorMid = CselMid->SelColor;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CSelLowChange(TObject *Sender)
{
Plot3D1->ColorLow = CSelLow->SelColor;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CSelGridChange(TObject *Sender)
{
Plot3D1->ColorMesh = CSelGrid->SelColor;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CBoxMeshClick(TObject *Sender)
{
Plot3D1->MeshVisible = CBoxMesh->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Rotate1Click(TObject *Sender)
{
Plot3D1->MouseAction = maRotate;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Pan1Click(TObject *Sender)
{
Plot3D1->MouseAction = maPan;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zoom1Click(TObject *Sender)
{
Plot3D1->MouseAction = maZoom;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RotateandZoom1Click(TObject *Sender)
{
Plot3D1->MouseAction = maRotAndZoom;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RotXOnly1Click(TObject *Sender)
{
Plot3D1->MouseAction = maRotXOnly;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RotZOnly1Click(TObject *Sender)
{
Plot3D1->MouseAction = maRotZOnly;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CBox3colmodClick(TObject *Sender)
{
if (CBox3colmod->Checked)
  {
  Plot3D1->ColorCodingMode = ccmThreeColors;
  LblColMid->Enabled = true;
  CselMid->Color = clWhite;
  CselMid->Enabled = true;
  }
  else
  {
  Plot3D1->ColorCodingMode = ccmTwoColors;
  LblColMid->Enabled = false;
  CselMid->Color = clBtnFace;
  CselMid->Enabled = false;
  };
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SbAutoscaleClick(TObject *Sender)
{
Plot3D1->AutoScale();
ScrBarSclX->Position = ceil(Plot3D1->ScaleFactX*100);
ScrBarSclY->Position = ceil(Plot3D1->ScaleFactY*100);
ScrBarSclZ->Position = ceil(Plot3D1->ScaleFactZ*100);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrBarSclXChange(TObject *Sender)
{
Plot3D1->ScaleFactX = 0.01*ScrBarSclX->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrBarSclYChange(TObject *Sender)
{
Plot3D1->ScaleFactY = 0.01*ScrBarSclY->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrBarSclZChange(TObject *Sender)
{
Plot3D1->ScaleFactZ = 0.01*ScrBarSclZ->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SBResetClick(TObject *Sender)
{
Plot3D1->Reset();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrBarColorHighChange(TObject *Sender)
{
Plot3D1->ColorScaleHigh = 0.1*ScrBarColorHigh->Position;
Plot3D1->ColorScaleLow = 0.1*ScrBarColorHigh->Position-15;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RGFrameModeClick(TObject *Sender)
{
Plot3D1->SuppressPaint = true;
switch (RGFrameMode->ItemIndex)
  {
  case 0 : {
           Plot3D1->BoundBoxStyle = bbNone;
           break;
           }
  case 1 : {
           Plot3D1->ColorCubeFrame = 0x00e0e0e0;
           Plot3D1->ColorCubeHidLin = 0x00505050;
           Plot3D1->BoundBoxStyle = bbFrame;
           break;
           }
  case 2 : {
           Plot3D1->ColorCubeFrame = 0x00404040;
           Plot3D1->ColorCubeHidLin = 0x00B0B0B0;
           Plot3D1->BoundBoxStyle = bbFaces;
           break;
           }
  }
Plot3D1->SuppressPaint = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Plot3D1BeforeRenderPolygon(TObject *Sender,
      TCanvas *&Canvas, bool &Handled, int CellX, int CellY, TQuad &quad,
      TColor &color)
{
if (CBoxGridCursor->Checked)
  {
  if ((CellX == MCellX) || (CellY == MCellY))
    {
    color = clBlue;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Plot3D1DataRendered(TObject *Sender,
      TCanvas *&Canvas)
{
Canvas->Brush->Style = bsClear;
Canvas->Font->Color = clWhite;
Canvas->TextOut(50,50,"This is a text drawn in the OnDataRendered event");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Plot3D1MouseMoveOverPlot(TObject *Sender,
      bool OverPlot, TShiftState Shift, int MouseCellX, int MouseCellY)
{
MCellX = MouseCellX;
MCellY = MouseCellY;
if (OverPlot)
  {
  NLabCellX->Value = MouseCellX;
  NLabCellY->Value = MouseCellY;
  NLabCellX->Empty = false;
  NLabCellY->Empty = false;
  }
  else
  {
  NLabCellX->Empty = true;
  NLabCellY->Empty = true;
  };
Plot3D1->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CBoxZCoordsClick(TObject *Sender)
{
Plot3D1->VisibleXCoords = CBoxXCoords->Checked;
Plot3D1->VisibleYCoords = CBoxYCoords->Checked;
Plot3D1->VisibleZCoords = CBoxZCoords->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ColSelZChange(TObject *Sender)
{
Plot3D1->ColorZCoords = ColSelZ->SelColor;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ColSelYChange(TObject *Sender)
{
Plot3D1->ColorYCoords = ColSelY->SelColor;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ColSelXChange(TObject *Sender)
{
Plot3D1->ColorXCoords = ColSelX->SelColor;
}
//---------------------------------------------------------------------------

