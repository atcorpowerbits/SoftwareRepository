//---------------------------------------------------------------------------
#ifndef frmcentH
#define frmcentH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include "NumLab.hpp"
#include <vcl\Buttons.hpp>
#include "RChart.hpp"
#include "rchart.hpp"
#include "matrix.hpp"
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
        TNumLab *NLabProcCnt;
        TBitBtn *BButExit;
        TBitBtn *BButCreateD;
        TBitBtn *BButCalcCent;
        TRChart *RChart1;
        TMatrix *Data;
        TMatrix *Centers;
        void __fastcall BButExitClick(TObject *Sender);
        void __fastcall BButCreateDClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BButCalcCentClick(TObject *Sender);
private:        // User declarations
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
