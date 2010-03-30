
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "rot3data.h"
#include "uinfo.h"
#include "stdlib.h"
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
#pragma link "Rot3D"
#pragma link "NumLab"
#pragma link "numlab"
#pragma link "rot3d"
#pragma resource "*.dfm"
TForm1 *Form1;

double    vax = 0;
double    vay = 0;
double    vaxold, vayold;
double    dvax, dvay;
int       MousePosX, MousePosY;
int       LastItemFound;
TColor    LastFoundColor;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
                : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBAngXChange(TObject *Sender)
{
Rot3D1->ViewAngleX = SBAngX->Position;
NLabAlpha->Value = SBAngX->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBAngYChange(TObject *Sender)
{
Rot3D1->ViewAngleY = SBAngY->Position;
NLabBeta->Value = SBAngY->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBAngZChange(TObject *Sender)
{
Rot3D1->ViewAngleZ = SBAngZ->Position;
NLabGamma->Value = SBAngZ->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar4Change(TObject *Sender)
{
Rot3D1->Magnification = 1-ScrollBar4->Position/100.0;
NumLab4->Value = Rot3D1->Magnification;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
int     i;
double  rx, ry, rz;

Rot3D1->ColorData = clBlue;
for (i=1; i<=100; i++)     /* banana */
  {
  rx = random(200);
  ry = 0.1*rx + random(5);
  rz = random(30)+0.0007*(rx+ry)*(rx+ry);
  Rot3D1->MarkAt (rx,ry,rz,10);
  }
Rot3D1->ColorData = clGreen;
for (i=1; i<=50; i++)
  Rot3D1->MarkAt (2+random(7),10+random(3),120+random(30),12);
Rot3D1->MakeVisible();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Rot3D1MouseMove(TObject *Sender, TShiftState Shift,
                int X, int Y)
{
MousePosX = X;
MousePosY = Y;
if (Shift.Contains(ssLeft))
  {
  vaxold = vax;
  vayold = vay;
  vax = Rot3D1->ViewAngleX;
  vay = Rot3D1->ViewAngleY;
  dvax = (vax - vaxold)/3;
  dvay = (vay - vayold)/3;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButExitClick(TObject *Sender)
{
SBAutoRot->Down = false;
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
Rot3D1->BoundBoxStyle = bbNone;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
Rot3D1->BoundBoxStyle = bbFrame;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
Rot3D1->BoundBoxStyle = bbFaces;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
Rot3D1->ShowAxes = CheckBox1->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBAxSizeChange(TObject *Sender)
{
Rot3D1->AxSize = SBAxSize->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Rotate1Click(TObject *Sender)
{
Rot3D1->MouseAction = maRotate;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Zoom1Click(TObject *Sender)
{
Rot3D1->MouseAction = maZoom;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Pan1Click(TObject *Sender)
{
Rot3D1->MouseAction = maPan;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ToClipboard1Click(TObject *Sender)
{
Rot3D1->CopyToClipboard(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ToBMPFile1Click(TObject *Sender)
{
SaveDialog1->FileName = "*.bmp";
if (SaveDialog1->Execute())
  Rot3D1->CopyToBMP (SaveDialog1->FileName, false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBBBSizeChange(TObject *Sender)
{
Rot3D1->BoundBoxSize = SBBBSize->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBAutoRotClick(TObject *Sender)
{
dvax = vax - vaxold;
dvay = vay - vayold;
while (SBAutoRot->Down)
  {
  Application->ProcessMessages();
  vax = vax + dvax;
  if (vax > 360)
    vax = vax-360;
  vay = vay + dvay;
  if (vay > 360)
    vay = vay - 360;
  Rot3D1->SetViewAngles (vax, vay, 90);
  }
Rot3D1->SetViewAngles (SBAngX->Position, SBAngY->Position, SBAngZ->Position);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBIsoMetricClick(TObject *Sender)
{
Rot3D1->IsoMetric = CBIsoMetric->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButPrintitClick(TObject *Sender)
{
Rot3D1->PrintIt (1.0,false,false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Rot3D1MouseDown(TObject *Sender, TMouseButton Button,
                TShiftState Shift, int X, int Y)
{
int          ItemP;
Tr3ChartItem ItPar;
double       dist;

if (Shift.Contains(ssLeft) && (Rot3D1->MouseAction == Sdlbase::maNone))
  {
  ItemP = Rot3D1->FindNearestItemScreen (X, Y, tkEverything, dist);
  if (ItemP != NULL)
    {
    LastItemFound = ItemP;                  // mark found item red
    ItPar = Rot3D1->GetItemParams (ItemP);
    LastFoundColor = ItPar.color;
    ItPar.color = clRed;
    Rot3D1->SetItemParams (ItemP, ItPar);
    Rot3D1->MakeVisible();
    FrmInfo->Left = Form1->Left+X+30; // display coords of found item
    FrmInfo->Top = Form1->Top+Y+30;
    FrmInfo->NLXCoord->Value = ItPar.x;
    FrmInfo->NLYCoord->Value = ItPar.y;
    FrmInfo->NLZCoord->Value = ItPar.z;
    FrmInfo->Show();
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Rot3D1MouseUp(TObject *Sender, TMouseButton Button,
                TShiftState Shift, int X, int Y)
{
Tr3ChartItem  ItPar;

if (LastItemFound != NULL)
  {
  ItPar = Rot3D1->GetItemParams (LastItemFound);
  ItPar.color = LastFoundColor;
  Rot3D1->SetItemParams (LastItemFound, ItPar);
  Rot3D1->MakeVisible();
  FrmInfo->Hide();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RGCoordSystemClick(TObject *Sender)
{
Rot3D1->AxDir = TAxDir(RGCoordSystem->ItemIndex);
}
//---------------------------------------------------------------------------

