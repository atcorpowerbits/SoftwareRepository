//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uspline.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "math2"
#pragma link "numlab"
#pragma link "rchart"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void _fastcall TForm1::CalcAndShowSpline()
{
int             i;
double          x, y;
bool            valid;
double          adouble;

if (!SuppressCalc)
  {
  CurveFit->Init();
  for (i=0; i<RChart1->NumItems; i++)    // loop through all items and enter MarkAt coords into CurveFit
    {
    if (RChart1->DataContainer[i].ItemKind == tkMarkAt)
      {
      CurveFit->EnterStatValue (RChart1->DataContainer[i].x, RChart1->DataContainer[i].y);
      }
    }
  if (CurveFit->NumData > 0)   // draw spline
    {
    RChart1->RemoveItemsByClass (100);   // remove the previous spline curve
    RChart1->DataColor = clBlue;
    RChart1->ClassDefault = 100;
    if (SBarSmoothFact->Position != 0)
      {                        // draw the smoothed spline
      CurveFit->SplineSmoothingFactor = 0.001*SBarSmoothFact->Position;
      x = CurveFit->MinX;
      y = CurveFit->SmoothedSpline (x, adouble, valid);
      RChart1->MoveTo (x,y);
      for (i=1; i<400; i++)
        {
        x = CurveFit->MinX+i*0.25;
        y = CurveFit->SmoothedSpline (x, adouble, valid);
        if (valid)
          RChart1->DrawTo (x,y);
        }
      }
    else
      {
      RChart1->MoveTo (0, CurveFit->CubicSpline (0));  //now draw the new spline
      for (i=1; i<400; i++)
        {
        y = CurveFit->CubicSpline (0.25*i);
        RChart1->DrawTo(0.25*i,y);
        }
      }
    RChart1->ShowGraf();
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBNat1Click(TObject *Sender)
{
if (CBNat1->Checked)
  {
  NLab1->Visible = false;
  SBDeriv1->Visible = false;
  }
else
  {
  NLab1->Visible = true;
  SBDeriv1->Visible = true;
  }
CurveFit->SplineNatural1 = CBNat1->Checked;
CalcAndShowSpline();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBNatNClick(TObject *Sender)
{
if (CBNatN->Checked)
  {
  NLabN->Visible = false;
  SBDerivN->Visible = false;
  }
else
  {
  NLabN->Visible = true;
  SBDerivN->Visible = true;
  }
CurveFit->SplineNaturalN = CBNatN->Checked;
CalcAndShowSpline();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBDeriv1Change(TObject *Sender)
{
CurveFit->SplineDerivY1 = 0.001*SBDeriv1->Position;
NLab1->Value = CurveFit->SplineDerivY1;
CalcAndShowSpline();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBDerivNChange(TObject *Sender)
{
CurveFit->SplineDerivYN = 0.001*SBDerivN->Position;
NLabN->Value = CurveFit->SplineDerivYN;
CalcAndShowSpline();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
const MaxDPoints = 6;
const double DPoints[MaxDPoints][2]  =
             {{20, 2}, {44,3} , {30,5}, {64,6}, {33,7}, {53,5.2}};

int  i;

RChart1->ClearGraf();
RChart1->DataColor = clRed;
for (i=0; i<MaxDPoints; i++) 
  RChart1->MarkAt (DPoints[i][0],DPoints[i][1],24);
SuppressCalc = false;
CurveFit->SplineNatural1 = CBNat1->Checked;
CurveFit->SplineNaturalN = CBNatN->Checked;
CalcAndShowSpline();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RChart1MouseMoveInChart(TObject *Sender,
      bool InChart, TShiftState Shift, double rMousePosX,
      double rMousePosY)
{
int           GElem;
int           i;
TrcChartItem  ElemPar;
TrcChartItem  ElemPar2;
double        Dist;
bool          equal;

if (Shift.Contains(ssLeft))
  {
  GElem = RChart1->FindNearestItemScreen (rMousePosX, rMousePosY, tkMarkAt, 255, Dist);
  if (GElem >= 0) 
    {
    ElemPar = RChart1->GetItemParams (GElem);
      // since splines cannot be calculated if two points have the same x-coordinates
      // we have to prevent equal x-coordinates
    equal = false;
    for (i=0; i<RChart1->NumItems-1; i++)     // loop through all items and check if any x-coord. equals the mouse position
      {
      ElemPar2 = RChart1->GetItemParams(i);
      if ((ElemPar2.ItemKind == tkMarkAt) && (i != GElem))
        {
        if (ElemPar2.x == rMousePosX) 
          equal = true;
        }
      }
    if (! equal)
      {
      ElemPar.x = rMousePosX;   // move mark to mouse cursor
      ElemPar.y = rMousePosY;
      RChart1->SetItemParams (GElem, ElemPar);
      }
    }
  CalcAndShowSpline();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButExitClick(TObject *Sender)
{
Close();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBarSmoothFactChange(TObject *Sender)
{
NLabSmoothing->Value = 0.001*SBarSmoothFact->Position;
if (SBarSmoothFact->Position == 0)
  {
  CBNat1->Enabled = true;
  CBNatN->Enabled = true;
  NLab1->Enabled = true;
  SBDeriv1->Enabled = true;
  NLabN->Enabled = true;
  SBDerivN->Enabled = true;
  }
else
  {
  CBNat1->Enabled = false;
  CBNatN->Enabled = false;
  NLab1->Enabled = false;
  SBDeriv1->Enabled = false;
  NLabN->Enabled = false;
  SBDerivN->Enabled = false;
  }
CalcAndShowSpline();
}
//---------------------------------------------------------------------------
