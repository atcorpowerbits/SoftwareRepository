
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "mainfrm.h"
#include "math.h"
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
#pragma link "RChart"
#pragma link "Fourier"
#pragma link "rchart"
#pragma link "fourier"
#pragma resource "*.dfm"
TForm1 *Form1;

bool UpdateSignal;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
                : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar1Change(TObject *Sender)
{
int i, j;

FastFourier1->Clear();
FastFourier1->RealSpec[1] = -0.01*ScrollBar1->Position*FastFourier1->SpectrumSize;
FastFourier1->RealSpec[2] = -0.01*ScrollBar2->Position*FastFourier1->SpectrumSize;
FastFourier1->RealSpec[3] = -0.01*ScrollBar3->Position*FastFourier1->SpectrumSize;
FastFourier1->RealSpec[4] = -0.01*ScrollBar4->Position*FastFourier1->SpectrumSize;
FastFourier1->RealSpec[5] = -0.01*ScrollBar5->Position*FastFourier1->SpectrumSize;
FastFourier1->RealSpec[6] = -0.01*ScrollBar6->Position*FastFourier1->SpectrumSize;
FastFourier1->RealSpec[7] = -0.01*ScrollBar7->Position*FastFourier1->SpectrumSize;
FastFourier1->RealSpec[8] = -0.01*ScrollBar8->Position*FastFourier1->SpectrumSize;
FastFourier1->ImagSpec[2] = -0.01*ScrollBar10->Position*FastFourier1->SpectrumSize;
FastFourier1->ImagSpec[3] = -0.01*ScrollBar11->Position*FastFourier1->SpectrumSize;
FastFourier1->ImagSpec[4] = -0.01*ScrollBar12->Position*FastFourier1->SpectrumSize;
FastFourier1->ImagSpec[5] = -0.01*ScrollBar13->Position*FastFourier1->SpectrumSize;
FastFourier1->ImagSpec[6] = -0.01*ScrollBar14->Position*FastFourier1->SpectrumSize;
FastFourier1->ImagSpec[7] = -0.01*ScrollBar15->Position*FastFourier1->SpectrumSize;
FastFourier1->ImagSpec[8] = -0.01*ScrollBar16->Position*FastFourier1->SpectrumSize;
if (UpdateSignal == true)
  {
  FastFourier1->InverseTransform();
  RChart1->ClearGraf();
  RChart1->DataColor =clNavy;
  RChart1->MoveTo (1,FastFourier1->RealSpec[1]);
  for (i=1; i<=512; i++)
    {
    j = 1 + fmod((i-1),256);
    RChart1->DrawTo (i,FastFourier1->RealSpec[j]);
    }
  RChart1->ShowGraf();
  };
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButResetClick(TObject *Sender)
{
UpdateSignal = false;
ScrollBar1->Position = 0;
ScrollBar2->Position = 0;
ScrollBar3->Position = 0;
ScrollBar4->Position = 0;
ScrollBar5->Position = 0;
ScrollBar6->Position = 0;
ScrollBar7->Position = 0;
ScrollBar8->Position = 0;
ScrollBar10->Position = 0;
ScrollBar11->Position = 0;
ScrollBar12->Position = 0;
ScrollBar13->Position = 0;
ScrollBar14->Position = 0;
ScrollBar15->Position = 0;
ScrollBar16->Position = 0;
UpdateSignal = true;
ScrollBar1Change (Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
UpdateSignal = True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButSquareClick(TObject *Sender)
{
UpdateSignal = false;
ScrollBar1->Position = 0;
ScrollBar2->Position = 100;
ScrollBar3->Position = 0;
ScrollBar4->Position = -33;
ScrollBar5->Position = 0;
ScrollBar6->Position = 20;
ScrollBar7->Position = 0;
ScrollBar8->Position = -16;
ScrollBar10->Position = 0;
ScrollBar11->Position = 0;
ScrollBar12->Position = 0;
ScrollBar13->Position = 0;
ScrollBar14->Position = 0;
ScrollBar15->Position = 0;
ScrollBar16->Position = 0;
UpdateSignal = true;
ScrollBar1Change (Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButSawClick(TObject *Sender)
{
UpdateSignal = false;
ScrollBar1->Position = 0;
ScrollBar2->Position = 0;
ScrollBar3->Position = 0;
ScrollBar4->Position = 0;
ScrollBar5->Position = 0;
ScrollBar6->Position = 0;
ScrollBar7->Position = 0;
ScrollBar8->Position = 0;
ScrollBar10->Position = -64;
ScrollBar11->Position = -32;
ScrollBar12->Position = -21;
ScrollBar13->Position = -16;
ScrollBar14->Position = -13;
ScrollBar15->Position = -11;
ScrollBar16->Position = -9;
UpdateSignal = true;
ScrollBar1Change (Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButHalfSineClick(TObject *Sender)
{
UpdateSignal = false;
ScrollBar1->Position = -32;
ScrollBar2->Position = -50;
ScrollBar3->Position = -21;
ScrollBar4->Position = 0;
ScrollBar5->Position = 4;
ScrollBar6->Position = 0;
ScrollBar7->Position = -2;
ScrollBar8->Position = 0;
ScrollBar10->Position = 0;
ScrollBar11->Position = 0;
ScrollBar12->Position = 0;
ScrollBar13->Position = 0;
ScrollBar14->Position = 0;
ScrollBar15->Position = 0;
ScrollBar16->Position = 0;
UpdateSignal = true;
ScrollBar1Change (Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButTriangleClick(TObject *Sender)
{
UpdateSignal = false;
ScrollBar1->Position = 0;
ScrollBar2->Position = 0;
ScrollBar3->Position = 0;
ScrollBar4->Position = 0;
ScrollBar5->Position = 0;
ScrollBar6->Position = 0;
ScrollBar7->Position = 0;
ScrollBar8->Position = 0;
ScrollBar10->Position = -81;
ScrollBar11->Position = 0;
ScrollBar12->Position = 9;
ScrollBar13->Position = 0;
ScrollBar14->Position = -3;
ScrollBar15->Position = 0;
ScrollBar16->Position = 2;
UpdateSignal = true;
ScrollBar1Change (Sender);
}
//---------------------------------------------------------------------------