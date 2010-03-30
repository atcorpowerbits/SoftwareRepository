//---------------------------------------------------------------------------
#ifndef udistriH
#define udistriH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "RChart.hpp"
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include "NumLab.hpp"
#include "rchart.hpp"
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
class TFrmFDistri : public TForm
{
__published:    // IDE-managed Components
        TRChart *RChart1;
        TPanel *Panel1;
        TBitBtn *BButExit;
        TScrollBar *SBDf1;
        TNumLab *NLabDf1;
        TScrollBar *SBDf2;
        TNumLab *NLabDf2;
        void __fastcall BButExitClick(TObject *Sender);
        void __fastcall SBDf1Change(TObject *Sender);
        void __fastcall SBDf2Change(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:        // User declarations
        void __fastcall PlotDistribution (int df1, int df2);
public:         // User declarations
        __fastcall TFrmFDistri(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFrmFDistri *FrmFDistri;
//---------------------------------------------------------------------------
#endif
