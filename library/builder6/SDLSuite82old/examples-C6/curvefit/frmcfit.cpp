
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
#pragma link "numlab"
#pragma resource "*.dfm"

TForm1 *Form1;
const int ChartXRes = 200;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
                : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DisableElements()
{
SBarSmoothSpline->Enabled = false;
LblSmoothSpline->Enabled = false;
LblPolyOrder->Enabled = false;
SEPolyOrder->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ShowSpline()
{
double  FitQual;
double  xstep;
int     i;
double  x, y;
bool    valid;

while ((RChart1->TypeOfLastItem != tkMarkAt) &&
       (RChart1->TypeOfLastItem != tkNone))  // remove any curve from graph 
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
xstep = (RChart1->Scale1X->RangeHigh-RChart1->Scale1X->RangeLow) / ChartXRes;
x = Stats1->MinX;
Stats1->SplineSmoothingFactor = 0.001*SBarSmoothSpline->Position;
y = Stats1->SmoothedSpline (x, FitQual, valid);
NLabFitQual->Value = FitQual;
RChart1->MoveTo (x,y);
for (i=1; i<=ChartXRes; i++)
  {
  x = RChart1->Scale1X->RangeLow+i*xstep;
  y = Stats1->SmoothedSpline (x, FitQual, valid);
  if (valid)
    {
    RChart1->DrawTo (x,y);
    }
  }
RChart1->ShowGraf();
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
  RChart1->M2R (1, X,Y, rx, ry);
  RChart1->MarkAt (rx,ry,26);
  Stats1->EnterStatValue (rx, ry);
  if (Stats1->NumData <=9)
    {
    SEPolyOrder->MaxValue = Stats1->NumData-1;
    }
  if (SEPolyOrder->Value > SEPolyOrder->MaxValue)
    {
    SEPolyOrder->Value = SEPolyOrder->MaxValue;
    }
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

DisableElements();
while ((RChart1->TypeOfLastItem != tkMarkAt) &&
      (RChart1->TypeOfLastItem != tkNone))   // remove any curve from graph
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
Stats1->CalcParabolFit (k0, k1, k2, FitQual);
NLabFitQual->Value = FitQual;
RChart1->MoveTo (RChart1->Scale1X->RangeLow,k0+k1*RChart1->Scale1X->RangeLow+k2*RChart1->Scale1X->RangeLow*RChart1->Scale1X->RangeLow);
xstep = (RChart1->Scale1X->RangeHigh-RChart1->Scale1X->RangeLow) / ChartXRes;
for (i=1; i<=ChartXRes; i++)
  {
  x = RChart1->Scale1X->RangeLow+i*xstep;
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

DisableElements();
while ((RChart1->TypeOfLastItem != tkMarkAt) &&
       (RChart1->TypeOfLastItem != tkNone)) // remove any curve from graph
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
Stats1->CalcReciLinFit (k0, k1, FitQual);
NLabFitQual->Value = FitQual;
denom = k0+k1*RChart1->Scale1X->RangeLow;
if (denom != 0)
  {
  RChart1->MoveTo (RChart1->Scale1X->RangeLow,1/denom);
  }
xstep = (RChart1->Scale1X->RangeHigh-RChart1->Scale1X->RangeLow) / ChartXRes;
for (i=1; i<=ChartXRes; i++)
  {
  x = RChart1->Scale1X->RangeLow+i*xstep;
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

DisableElements();
while ((RChart1->TypeOfLastItem != tkMarkAt) &&
       (RChart1->TypeOfLastItem != tkNone))      // remove any curve from graph
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
Stats1->CalcHyperbolFit (k0, k1, FitQual);
NLabFitQual->Value = FitQual;
if (RChart1->Scale1X->RangeLow != 0)
  {
  RChart1->MoveTo (RChart1->Scale1X->RangeLow,k0+k1/RChart1->Scale1X->RangeLow);
  }
else
  {
  RChart1->MoveTo (RChart1->Scale1X->RangeLow, 1e6);
  }
xstep = (RChart1->Scale1X->RangeHigh-RChart1->Scale1X->RangeLow) / ChartXRes;
for (i=1; i<=ChartXRes; i++)
  {
  x = RChart1->Scale1X->RangeLow+i*xstep;
  if (x != 0)
    {
    RChart1->DrawTo (x,k0+k1/x);
    }
  else
    {
    RChart1->DrawTo (x,1e6);
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

DisableElements();
while ((RChart1->TypeOfLastItem != tkMarkAt) &&
       (RChart1->TypeOfLastItem != tkNone))  // remove any curve from graph
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
Stats1->CalcLogFit (k0, k1, FitQual);
NLabFitQual->Value = FitQual;
if (RChart1->Scale1X->RangeLow > 0)
  {
  RChart1->MoveTo (RChart1->Scale1X->RangeLow,k0+k1*log(RChart1->Scale1X->RangeLow));
  }
else
  {
  RChart1->MoveTo (0, -1e6);
  }
xstep = (RChart1->Scale1X->RangeHigh-RChart1->Scale1X->RangeLow) / ChartXRes;
for (i=1; i<=ChartXRes; i++)
  {
  x = RChart1->Scale1X->RangeLow+i*xstep;
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

DisableElements();
while ((RChart1->TypeOfLastItem != tkMarkAt) &&
       (RChart1->TypeOfLastItem != tkNone))  // remove any curve from graph
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
Stats1->CalcGaussFit (k0, k1, k2, FitQual);
NLabFitQual->Value = FitQual;
x = RChart1->Scale1X->RangeLow;
RChart1->MoveTo (x,k0*exp(-(x-k1)*(x-k1)/k2));
xstep = (RChart1->Scale1X->RangeHigh-RChart1->Scale1X->RangeLow) / ChartXRes;
for (i=1; i<=ChartXRes; i++)
  {
  x = RChart1->Scale1X->RangeLow+i*xstep;
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

DisableElements();
while ((RChart1->TypeOfLastItem != tkMarkAt) &&
       (RChart1->TypeOfLastItem != tkNone))  // remove any curve from graph
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
Stats1->CalcLinFit (k, d, FitQual);
NLabFitQual->Value = FitQual;
RChart1->MoveTo (RChart1->Scale1X->RangeLow,k*RChart1->Scale1X->RangeLow+d);
RChart1->DrawTo (RChart1->Scale1X->RangeHigh,k*RChart1->Scale1X->RangeHigh+d);
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
double     k[MAXPOLYFITORDER+1];
double     FitQual;
double     xstep;
int        i,j;
double     x, xprod;
double     sum;
AnsiString astr;

DisableElements();
LblPolyOrder->Enabled = true;
SEPolyOrder->Enabled = true;
while ((RChart1->TypeOfLastItem != tkMarkAt) &&
      (RChart1->TypeOfLastItem != tkNone)) // remove any curve from graph
  RChart1->RemoveLastItem();
SBNewPnts->Down = false;
if (Stats1->CalcPolyFit (SEPolyOrder->Value, k, MAXPOLYFITORDER+1, FitQual))
  {
  NLabFitQual->Value = FitQual;
  xstep = (RChart1->Scale1X->RangeHigh-RChart1->Scale1X->RangeLow) / ChartXRes;
  x = RChart1->Scale1X->RangeLow+xstep;
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
    x = RChart1->Scale1X->RangeLow+i*xstep;
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
void __fastcall TForm1::BButSplineClick(TObject *Sender)
{
DisableElements();
SBarSmoothSpline->Enabled = true;
LblSmoothSpline->Enabled = true;
ShowSpline();
LblFormula->Visible = false;
LblParams->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBarSmoothSplineChange(TObject *Sender)
{
ShowSpline();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
Stats1->ExportAsASC ("cfit.asc", "Data exported from SDL TCurveFit", 6);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
int     i;
double  d;

if (Math2::IsLightEd)
  {
  BButCalcReciprLine->Enabled = false;
  BButHyper->Enabled = false;
  BButLogFit->Enabled = false;
  BButGaussFit->Enabled = false;
  BButSpline->Enabled = false;
  }
else
  {
  if (Stats1->ImportASC ("cfit.asc") == 0)
    {
    for (i=1; i<=Stats1->NumData; i++)
      {
      RChart1->MarkAt (Stats1->DataX[i], Stats1->DataY[i], 26);
      }
    d = fabs (Stats1->MaxY - Stats1->MinY);
    RChart1->Scale1Y->RangeLow = Stats1->MinY-0.1*d;
    RChart1->Scale1Y->RangeHigh = Stats1->MaxY+0.1*d;
    }
  }
}
//---------------------------------------------------------------------------
