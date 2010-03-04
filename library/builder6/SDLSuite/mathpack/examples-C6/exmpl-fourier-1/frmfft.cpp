
#include <vcl\vcl.h>
#pragma hdrstop

#include "frmfft.h"
#include "math.h"
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
#pragma link "Fourier"
#pragma link "RChart"
#pragma link "rchart"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
                : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StartFFT()
{

const
  double ChartYRanges [7][2] =
                    {{0,10},        // Magnitude
                     {0,50000},     // PowerSpec
                     {-2,2},        // Phase
                     {-10,10},      // FourSerCosCoeff
                     {-10,10},      // FourSerSinCoeff
                     {-2000,2000},  // RealSpec
                     {-2000,2000}}; // ImagSpec


int      i;
double           y;

RChart1->ClearGraf();
RChart1->DataColor = clBlue;
RChart1->MoveTo (0,0);
FFT1->ClearImag();
for (i=1; i<=FFT1->SpectrumSize; i++)
  {
  y = 10*(sin(0.01*i*(100-SBFreq1->Position))+sin(0.075*i)+cos(0.5*i)+
       0.06*(random(100-ScrollBar1->Position)-0.5*(100-ScrollBar1->Position)));
  FFT1->RealSpec[i] = y;           // real value
  RChart1->DrawTo (i,y);
  }
RChart1->ShowGraf();

FFT1->Transform();

RChart2->ClearGraf();
RChart2->RangeLoY = ChartYRanges[RGSpecType->ItemIndex][0];
RChart2->RangeHiY = ChartYRanges[RGSpecType->ItemIndex][1];
if (! CBLogY->Enabled)
  {
  RChart2->LogScaleY = false;
  }
  else if (CBLogY->Checked)
         {
         if (RGSpecType->ItemIndex == 0)
           {
           RChart2->RangeLoY = 1e-4;
           }
           else RChart2->RangeLoY = 1e-6;
         RChart2->LogScaleY = true;
         }
         else RChart2->LogScaleY = false;
switch (RGSpecType->ItemIndex)
  {
  case 0 : RChart2->Caption = "Magnitude Spectrum"; break;
  case 1 : RChart2->Caption = "Power Spectrum"; break;
  case 2 : RChart2->Caption = "Phase Angle"; break;
  case 3 : RChart2->Caption = "Cosine Terms"; break;
  case 4 : RChart2->Caption = "Sine Terms"; break;
  case 5 : RChart2->Caption = "Real Part of Complex Spectrum"; break;
  case 6 : RChart2->Caption = "Imaginary Part of Complex Spectrum"; break;
  }
RChart2->DataColor = clRed;
RChart2->MoveTo (FFT1->FreqOfLine(1,0.001),0);
for (i=1; i<=FFT1->SpectrumSize/2; i++)
  {
  switch (RGSpecType->ItemIndex)
    {
    case 0 : y = FFT1->Magnitude[i]; break;
    case 1 : y = FFT1->PowerSpec[i]; break;
    case 2 : y = FFT1->Phase[i]; break;
    case 3 : y = FFT1->FourSerCosCoeff[i]; break;
    case 4 : y = FFT1->FourSerSinCoeff[i]; break;
    case 5 : y = FFT1->RealSpec[i+1]; break;
    case 6 : y = FFT1->ImagSpec[i+1]; break;
    }
  RChart2->DrawTo (FFT1->FreqOfLine(i,0.001),y);
  }
RChart2->ShowGraf();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBoxWindChange(TObject *Sender)
{
if (CBoxWind->Text == "Rectangle")
  {
  FFT1->WeightingWindow = fwRectangle;
  }
if (CBoxWind->Text == "Triangle")
  {
  FFT1->WeightingWindow = fwTriangle;
  }
if (CBoxWind->Text == "Gaussian")
  {
  FFT1->WeightingWindow = fwGauss;
  }
if (CBoxWind->Text == "Hamming")
  {
  FFT1->WeightingWindow = fwHamming;
  }
if (CBoxWind->Text == "Blackman")
  {
  FFT1->WeightingWindow = fwBlackman;
  }
if (CBoxWind->Text == "cos2")
  {
  FFT1->WeightingWindow = fwCos2;
  }
StartFFT();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar1Change(TObject *Sender)
{
StartFFT();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBFreq1Change(TObject *Sender)
{
StartFFT();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
CBoxWind->Text = "None";
StartFFT();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBLogYClick(TObject *Sender)
{
StartFFT();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RGSpecTypeClick(TObject *Sender)
{
switch (RGSpecType->ItemIndex)
  {
  case 0,1 : CBLogY->Enabled = true; break;
  case 2,3,4,5,6 : CBLogY->Enabled = false; break;
  }
StartFFT();

}
//---------------------------------------------------------------------------
