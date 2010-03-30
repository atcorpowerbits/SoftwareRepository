//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uprogres.h"
#include "ukohonen.h"
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
#pragma link "meter"
#pragma resource "*.dfm"
TFrmProgress *FrmProgress;
//---------------------------------------------------------------------------
__fastcall TFrmProgress::TFrmProgress(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmProgress::BButAbortClick(TObject *Sender)
{
FrmSom->KohMap1->AbortTraining();
FrmSom->BButContTrain->Enabled = true;
FrmSom->BButStoreNet->Enabled = true;
}
//---------------------------------------------------------------------------
