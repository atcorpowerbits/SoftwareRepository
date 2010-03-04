//---------------------------------------------------------------------------
#ifndef ureplistH
#define ureplistH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include "replist.hpp"
#include "Grids.hpp"
#include "Colsel.hpp"
#include <vcl\Dialogs.hpp>
#include "colsel.hpp"
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
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TReportListView *RL1;
        TBitBtn *BButAddRow;
        TBitBtn *BButUnsort;
        TColSel *CSText;
        TColSel *CSBkg1;
        TColSel *CSBkg2;
        TScrollBar *SBarRowPat;
        TBitBtn *BButExit;
        TCheckBox *CBVertLines;
        TCheckBox *CBHorzLines;
        TColorDialog *ColorDialog1;











        void __fastcall BButExitClick(TObject *Sender);
        void __fastcall BButAddRowClick(TObject *Sender);
        void __fastcall BButUnsortClick(TObject *Sender);
        void __fastcall CSTextChange(TObject *Sender);
        void __fastcall CSBkg1Change(TObject *Sender);
        void __fastcall CSBkg2Change(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SBarRowPatChange(TObject *Sender);
        void __fastcall CBVertLinesClick(TObject *Sender);
        void __fastcall CBHorzLinesClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:        // User declarations
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
