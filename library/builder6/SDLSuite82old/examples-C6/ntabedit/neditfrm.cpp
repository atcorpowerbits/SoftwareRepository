//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "neditfrm.h"
#include <stdlib.h>
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
#pragma link "NTabEd"
#pragma link "Grids"
#pragma link "ntabed"
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
void __fastcall TForm1::SBInputClick(TObject *Sender)
{
if (SBInput->Down == true)
  {
  NTabEd1->Options = NTabEd1->Options << goEditing;
  SBImport->Enabled = false;
  }
  else
  {
  NTabEd1->Options = NTabEd1->Options >> goEditing;
  SBImport->Enabled = true;
  };
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBImportClick(TObject *Sender)
{
int error;

if (OpenDialog1->Execute())
  {
  error = NTabEd1->Data->ImportASC(OpenDialog1->FileName);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBExportClick(TObject *Sender)
{
if (SaveDialog1->Execute())
  {
  NTabEd1->Data->ExportAsASC (SaveDialog1->FileName, 4);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBRandFillClick(TObject *Sender)
{
int  i, j;

NTabEd1->SuppressPaint = true;
for (i=1; i<=NTabEd1->NrOfColumns; i++)
  {
  for (j=1; j<=NTabEd1->NrOfRows; j++)
    {
    NTabEd1->Elem[i][j] = 0.01*random(1000);
    }
  }
NTabEd1->SuppressPaint = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBAutoSizeClick(TObject *Sender)
{
int i;

for (i=-1; i<=NTabEd1->NrOfColumns; i++)
  {
  NTabEd1->AutoColWidth (i,true,4);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBColAttClick(TObject *Sender)
{
NTabEd1->AttribColVisible = ! NTabEd1->AttribColVisible;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBRowAttClick(TObject *Sender)
{
NTabEd1->AttribRowVisible = ! NTabEd1->AttribRowVisible;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::NTabEd1ChangeSetup(TObject *Sender)
{
if (NTabEd1->Options.Contains(goEditing))
  {
  SBInput->Down = true;
  }
  else
  {
  SBInput->Down = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
if (Ntabed::IsLightEd)
  {
  SBImport->Enabled = false;
  SBExport->Enabled = false;
  }
}
//---------------------------------------------------------------------------
