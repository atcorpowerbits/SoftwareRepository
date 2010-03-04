//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ukohonen.h"
#include "uprogres.h"
#include "filesys.hpp"
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
#pragma link "kohonen"
#pragma link "ntabed"
#pragma link "numio"
#pragma link "numlab"
#pragma link "rchart"
#pragma link "vector"
#pragma resource "*.dfm"
TFrmSom *FrmSom;
const int MaxSteps = 19;
const int Steps[MaxSteps] = {10,15,20,30,50,75,
                             100,150,200,300,500,750,
                             1000,1500,2000,3000,5000,7500,10000};
const int MaxPreDefColors = 16;
const TColor PredefinedColors[MaxPreDefColors] =
              {clRed, clBlue, clLime, clYellow, clFuchsia,
               clBlack, clMaroon, clGreen, clOlive, clNavy,
               clPurple, clTeal, clGray, clSilver, clAqua,
               clWhite};
//---------------------------------------------------------------------------
__fastcall TFrmSom::TFrmSom(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void _fastcall TFrmSom::ShowCurrentNetResponse()
{
int    ix, iy;
double dist;
int    i;

RCKohMap->ClearGraf();
RowVect->NrOfElem = TEData->NrOfColumns;
for (i=1; i<=TEData->NrOfRows; i++)
  {
  TEData->Data->NumericData->CopyRowToVec (RowVect,i,1,TEData->NrOfColumns);
  KohMap1->ApplyIt (RowVect, ix, iy, dist);
  RCKohMap->DataColor = PredefinedColors[TEData->RowAttrib[i]];
  RCKohMap->MarkAt (ix+0.006*random(100)-0.3, iy+0.006*random(100)-0.3, 11);
  }
RCKohMap->SetRange (1, 0, 0, KohMap1->SizeX+1,KohMap1->SizeY+1);
RCKohMap->ShowGraf();
}
//---------------------------------------------------------------------------
void __fastcall TFrmSom::BButExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TFrmSom::BButLoadClick(TObject *Sender)
{
NoteBk->PageIndex = 0;
OpenDialog1->Filter = "Data Files|*.asc";
if (OpenDialog1->Execute())
  {
  TEData->Data->ImportASC (OpenDialog1->FileName);
  BButTrainIt->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFrmSom::BButTrainItClick(TObject *Sender)
{
BButContTrain->Enabled = false;
NoteBk->PageIndex = 1;
SBAlpha->Enabled = false;
SBSteps->Enabled = false;
KohMap1->TrainData = TEData->Data->NumericData;
KohMap1->StandardizeData();
KohMap1->SizeX = int(0.5+NIOxsize->Value);
KohMap1->SizeY = int(0.5+NIOysize->Value);
KohMap1->InitialAlpha = SBAlpha->Position/100;
KohMap1->NrOfTrnSteps = Steps[SBSteps->Position];
KohMap1->InitialNeighbors = int(0.5+NIONeighb->Value);
FrmProgress->Show();
Enabled = false;
KohMap1->Trainit();
FrmProgress->Hide();
Enabled = true;
Show();
ShowCurrentNetResponse();
SBAlpha->Enabled = true;
SBSteps->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFrmSom::SBAlphaChange(TObject *Sender)
{
NLAlpha->Value = SBAlpha->Position/100.0;
}
//---------------------------------------------------------------------------
void __fastcall TFrmSom::SBStepsChange(TObject *Sender)
{
NLSteps->Value = Steps[SBSteps->Position];
}
//---------------------------------------------------------------------------
void __fastcall TFrmSom::BButStoreNetClick(TObject *Sender)
{
SaveDialog1->Filter = "XML Files|*.xml";
if (SaveDialog1->Execute())
  {
  KohMap1->SaveAsXMLFile (StripExtension(SaveDialog1->FileName)+".xml", "");
  }
}
//---------------------------------------------------------------------------
void __fastcall TFrmSom::BButLoadNetClick(TObject *Sender)
{
int i;

OpenDialog1->Filter = "XML Files|*.xml";
if (OpenDialog1->Execute())
  {
  NoteBk->PageIndex = 1;
  KohMap1->LoadFromXMLFile (OpenDialog1->FileName, "");
  NIOxsize->Value = KohMap1->SizeX;
  NIOysize->Value = KohMap1->SizeY;
  NIONeighb->Value = KohMap1->InitialNeighbors;
  SBAlpha->Position = int(0.5+KohMap1->InitialAlpha*100);
  NLAlpha->Value = SBAlpha->Position/100.0;
  i = 1;
  while ((Steps[i] < KohMap1->NrOfTrnSteps) && (i < MaxSteps))
    {
    i++;
    }
  SBSteps->Position = i;
  NLSteps->Value = Steps[SBSteps->Position];
  ShowCurrentNetResponse();
  BButContTrain->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFrmSom::BButContTrainClick(TObject *Sender)
{
FrmProgress->Show();
Enabled = false;
KohMap1->TrainData = TEData->Data->NumericData;
KohMap1->StandardizeData();
KohMap1->ContinueTraining();
FrmProgress->Hide();
Enabled = true;
ShowCurrentNetResponse();
SBAlpha->Enabled = true;
SBSteps->Enabled = true;
Show();
}
//---------------------------------------------------------------------------
void __fastcall TFrmSom::KohMap1Feedback(TObject *Sender, int PercentDone)
{
FrmProgress->Meter->Value = PercentDone;
if (FrmProgress->CBShowTraining->Checked)
  {
  ShowCurrentNetResponse();
  }
Application->ProcessMessages();
}
//---------------------------------------------------------------------------
