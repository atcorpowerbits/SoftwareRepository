
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "udistri.h"
#include "statis.hpp"
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
#pragma link "NumLab"
#pragma link "statis"
#pragma link "rchart"
#pragma resource "*.dfm"
TFrmFDistri *FrmFDistri;

const int xRes = 500;
//---------------------------------------------------------------------------
__fastcall TFrmFDistri::TFrmFDistri(TComponent* Owner)
                : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmFDistri::PlotDistribution (int df1, int df2)
{
int      i;
double           F;

RChart1->ClearGraf();
RChart1->MoveTo (0,0);
for (i=1; i<=xRes; i++)
  {
  F = i*RChart1->RangeHiX/xRes;
  RChart1->DrawTo (F, FDistriDensity (F,df1,df2));
  }
RChart1->ShowGraf();
}
//---------------------------------------------------------------------------
void __fastcall TFrmFDistri::BButExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TFrmFDistri::SBDf1Change(TObject *Sender)
{
NLabDf1->Value = SBDf1->Position;
PlotDistribution (SBDf1->Position, SBDf2->Position);
}
//---------------------------------------------------------------------------
void __fastcall TFrmFDistri::SBDf2Change(TObject *Sender)
{
NLabDf2->Value = SBDf2->Position;
PlotDistribution (SBDf1->Position, SBDf2->Position);
}
//---------------------------------------------------------------------------
void __fastcall TFrmFDistri::FormShow(TObject *Sender)
{
PlotDistribution (SBDf1->Position, SBDf2->Position);
}
//---------------------------------------------------------------------------