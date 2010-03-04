//---------------------------------------------------------------------------
#ifndef neditfrmH
#define neditfrmH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include "NTabEd.hpp"
#include "Grids.hpp"
#include <vcl\Dialogs.hpp>
#include "ntabed.hpp"
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
class TForm1 : public TForm
{
__published:    // IDE-managed Components
        TPanel *Panel1;
        TSpeedButton *SBExit;
        TSpeedButton *SBInput;
        TSpeedButton *SBImport;
        TSpeedButton *SBRandFill;
        TSpeedButton *SBColAtt;
        TSpeedButton *SBRowAtt;
        TSpeedButton *SBExport;
        TSpeedButton *SBAutoSize;
        TPanel *Panel2;
        TNTabEd *NTabEd1;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        void __fastcall SBExitClick(TObject *Sender);
        void __fastcall SBInputClick(TObject *Sender);
        void __fastcall SBImportClick(TObject *Sender);
        void __fastcall SBExportClick(TObject *Sender);
        void __fastcall SBRandFillClick(TObject *Sender);
        void __fastcall SBAutoSizeClick(TObject *Sender);
        void __fastcall SBColAttClick(TObject *Sender);
        void __fastcall SBRowAttClick(TObject *Sender);
        void __fastcall NTabEd1ChangeSetup(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:        // User declarations
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
