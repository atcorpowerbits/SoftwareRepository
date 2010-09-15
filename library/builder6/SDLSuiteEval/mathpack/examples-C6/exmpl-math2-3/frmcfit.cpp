
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "frmcfit.h"
#include "math.h"
#include "math2.hpp"
#include "stringl.hpp"
#include "univconst.hpp"
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
#pragma link "RChart"
#pragma link "Math2"
#pragma link "Stringl"
#pragma link "UnivConst"
#pragma link "cspin"
#pragma link "CSPIN"
#pragma link "rchart"
#pragma link "math2"
#pragma resource "*.dfm"

TForm1 *Form1;
const int ChartXRes = 200;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
                : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBClearClick(TObject *Sender)
{
Stats1->Init();
RChart1->ClearGraf();
RChart1->ShowGraf();
SBNewPnts->Down = false;
LblFormula->Visible = false;
LblParams->Visible = true;
LblParams->Caption = "<---- click here to enter data";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RChart1MouseDown(TObject *Sender, TMouseButton Button,
                TShiftState Shift, int X, int Y)
{
double rx;
double ry;

if (SBNewPnts->Down == true)
  {
  RChart1->M2R (X,Y, rx, ry);
  RChart1->MarkAt (rx,ry,4);
  Stats1->EnterStatValue (rx, ry);
  NLabRXY->Value = Stats1->CorrCoeff;
  RChart1->ShowGraf();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBNewPntsClick(TObject *Sender)
{
while ((RChart1->TypeOfLastItem != tkMarkAt) &&
      (RChart1->TypeOfLastItem != tkNone))   // remove any curve from graph
  RChart1->RemoveLastItem();
RChart1->ShowGraf();
LblFormula->Visible = false;
if (SBNewPnts->Down == false)
  {
  LblParams->Caption = "<---- click here to enter data";
  }
else
  {
  LblParams->Caption = "click into chart to enter new data points";
  }
LblParams->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButParabolFitClick(TObject *Sender)
{
double  k0, k1, k2;
double  FitQual;
double  xstep;
double  x;
int     i;

while ((RChart1->TypeOfLastItem != tkMarkAt) &&
      (RChart1->TypeOfLastItem != tkNone))   // remove any curve from graph
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
Stats1->CalcParabolFit (k0, k1, k2, FitQual);
NLabFitQual->Value = FitQual;
RChart1->MoveTo (RChart1->RangeLoX,k0+k1*RChart1->RangeLoX+k2*RChart1->RangeLoX*RChart1->RangeLoX);
xstep = (RChart1->RangeHiX-RChart1->RangeLoX) / ChartXRes;
for (i=1; i<=ChartXRes; i++)
  {
  x = RChart1->RangeLoX+i*xstep;
  RChart1->DrawTo (x,k0+k1*x+k2*x*x);
  }
RChart1->ShowGraf();
LblFormula->Caption = "y = k0 + k1*x + k2*x*x";
LblParams->Caption = "k0 = "+strff(k0,1,3)+"    k1 = "+strff(k1,1,3)+"    k2 = "+strff(k2,1,3);
LblFormula->Visible = True;
LblParams->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButCalcReciprLineClick(TObject *Sender)
{
double k0, k1;
double FitQual;
double xstep;
int    i;
double x;
double denom;

while ((RChart1->TypeOfLastItem != tkMarkAt) &&
       (RChart1->TypeOfLastItem != tkNone)) // remove any curve from graph
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
Stats1->CalcReciLinFit (k0, k1, FitQual);
NLabFitQual->Value = FitQual;
denom = k0+k1*RChart1->RangeLoX;
if (denom != 0)
  {
  RChart1->MoveTo (RChart1->RangeLoX,1/denom);
  }
xstep = (RChart1->RangeHiX-RChart1->RangeLoX) / ChartXRes;
for (i=1; i<=ChartXRes; i++)
  {
  x = RChart1->RangeLoX+i*xstep;
  denom = k0+k1*x;
  if (denom != 0)
    {
    RChart1->DrawTo (x,1/denom);
    }
  }
RChart1->ShowGraf();
LblFormula->Caption = "y = 1/(k0 + k1*x)";
LblParams->Caption = "k0 = "+strff(k0,1,3)+"     k1 = "+strff(k1,1,3);
LblFormula->Visible = true;
LblParams->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButHyperClick(TObject *Sender)
{
double k0, k1;
double FitQual;
double xstep;
int    i;
double x;

while ((RChart1->TypeOfLastItem != tkMarkAt) &&
       (RChart1->TypeOfLastItem != tkNone))      // remove any curve from graph
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
Stats1->CalcHyperbolFit (k0, k1, FitQual);
NLabFitQual->Value = FitQual;
if (RChart1->RangeLoX != 0)
  {
  RChart1->MoveTo (RChart1->RangeLoX,k0+k1/RChart1->RangeLoX);
  }
else
  {
  RChart1->MoveTo (RChart1->RangeLoX, MaxReal);
  }
xstep = (RChart1->RangeHiX-RChart1->RangeLoX) / ChartXRes;
for (i=1; i<=ChartXRes; i++)
  {
  x = RChart1->RangeLoX+i*xstep;
  if (x != 0)
    {
    RChart1->DrawTo (x,k0+k1/x);
    }
  else
    {
    RChart1->DrawTo (x,MaxReal);
    }
  }
RChart1->ShowGraf();
LblFormula->Caption = "y = k0 + k1/x";
LblParams->Caption = "k0 = "+strff(k0,1,3)+"    k1 = "+strff(k1,1,3);
LblFormula->Visible = True;
LblParams->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButLogFitClick(TObject *Sender)
{
double    k0, k1;
double    FitQual;
double    xstep;
int       i;
double    x;

while ((RChart1->TypeOfLastItem != tkMarkAt) &&
       (RChart1->TypeOfLastItem != tkNone))  // remove any curve from graph
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
Stats1->CalcLogFit (k0, k1, FitQual);
NLabFitQual->Value = FitQual;
if (RChart1->RangeLoX > 0)
  {
  RChart1->MoveTo (RChart1->RangeLoX,k0+k1*log(RChart1->RangeLoX));
  }
else
  {
  RChart1->MoveTo (0, -MaxReal);
  }
xstep = (RChart1->RangeHiX-RChart1->RangeLoX) / ChartXRes;
for (i=1; i<=ChartXRes; i++)
  {
  x = RChart1->RangeLoX+i*xstep;
  if (x > 0)
    {
    RChart1->DrawTo (x,k0+k1*log(x));
    }
  }
RChart1->ShowGraf();
LblFormula->Caption = "y = k0 + k1*ln(x)";
LblParams->Caption = "k0 = "+strff(k0,1,3)+"    k1 = "+strff(k1,1,3);
LblFormula->Visible = True;
LblParams->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButGaussFitClick(TObject *Sender)
{
double    k0, k1, k2;
double    FitQual;
double    xstep;
int       i;
double    x;

while ((RChart1->TypeOfLastItem != tkMarkAt) &&
       (RChart1->TypeOfLastItem != tkNone))  // remove any curve from graph
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
Stats1->CalcGaussFit (k0, k1, k2, FitQual);
NLabFitQual->Value = FitQual;
x = RChart1->RangeLoX;
RChart1->MoveTo (x,k0*exp(-(x-k1)*(x-k1)/k2));
xstep = (RChart1->RangeHiX-RChart1->RangeLoX) / ChartXRes;
for (i=1; i<=ChartXRes; i++)
  {
  x = RChart1->RangeLoX+i*xstep;
  RChart1->DrawTo (x,k0*exp(-(x-k1)*(x-k1)/k2));
  }
RChart1->ShowGraf();
LblFormula->Caption = "y = k0*exp(-sqr(x-k1)/k2)";
LblParams->Caption = "k0 = "+strff(k0,1,3)+"    k1 = "+strff(k1,1,3)+"    k2 = "+strff(k2,1,3);
LblFormula->Visible = True;
LblParams->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButLinFitClick(TObject *Sender)
{
double    k,d;
double    FitQual;

while ((RChart1->TypeOfLastItem != tkMarkAt) &&
       (RChart1->TypeOfLastItem != tkNone))  // remove any curve from graph
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
Stats1->CalcLinFit (k, d, FitQual);
NLabFitQual->Value = FitQual;
RChart1->MoveTo (RChart1->RangeLoX,k*RChart1->RangeLoX+d);
RChart1->DrawTo (RChart1->RangeHiX,k*RChart1->RangeHiX+d);
RChart1->ShowGraf();
LblFormula->Caption = "y = k*x + d";
LblParams->Caption = "k = "+strff(k,1,3)+"    d = "+strff(d,1,3);
LblFormula->Visible = True;
LblParams->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X,
                int Y)
{
Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButPolynomialClick(TObject *Sender)
{
double     k[MaxPolyFitOrder+1];
double     FitQual;
double     xstep;
int        i,j;
double     x, xprod;
double     sum;
AnsiString astr;

while ((RChart1->TypeOfLastItem != tkMarkAt) &&
      (RChart1->TypeOfLastItem != tkNone)) // remove any curve from graph
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
if (Stats1->CalcPolyFit (SEPolyOrder->Value, k, MaxPolyFitOrder+1, FitQual))
  {
  NLabFitQual->Value = FitQual;
  xstep = (RChart1->RangeHiX-RChart1->RangeLoX) / ChartXRes;
  x = RChart1->RangeLoX+xstep;
  xprod = 1;
  sum = 0;
  for (j=0; j<=SEPolyOrder->Value; j++)
    {
    sum = sum + k[j]*xprod;
    xprod = xprod*x;
    }
  RChart1->MoveTo (x,sum);
  for (i=1; i<=ChartXRes; i++)
    {
    x = RChart1->RangeLoX+i*xstep;
    xprod = 1;
    sum = 0;
    for (j=0; j<=SEPolyOrder->Value; j++)
      {
      sum = sum + k[j]*xprod;
      xprod = xprod*x;
      }
    RChart1->DrawTo (x,sum);
    }
  RChart1->ShowGraf();
  astr = "y = k0+k1*x";
  for (i=2; i<=SEPolyOrder->Value; i++)
    astr = astr + "+k"+strff(i,1,0)+"*x^"+strff(i,1,0)+" ";
  LblFormula->Caption = astr;
  astr = "";
  for (i=0; i<=SEPolyOrder->Value; i++)
    astr = astr + "k"+strff(i,1,0)+"="+strff(k[i],1,3)+"  ";
  LblParams->Caption = astr;
  LblFormula->Visible = True;
  LblParams->Visible = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SEPolyOrderChange(TObject *Sender)
{
BButPolynomialClick (Sender);
}
//---------------------------------------------------------------------------