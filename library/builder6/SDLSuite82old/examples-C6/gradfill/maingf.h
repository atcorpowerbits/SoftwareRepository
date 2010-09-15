//---------------------------------------------------------------------------
#ifndef maingfH
#define maingfH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include "Colsel.hpp"
#include "NumIO.hpp"
#include "GradFl.hpp"
#include <vcl\ExtCtrls.hpp>
#include "gradfl.hpp"
#include "colsel.hpp"
#include "numio.hpp"
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
class TFrmGradFill : public TForm
{
__published:    // IDE-managed Components
        TSpeedButton *SBToggleColors;
        TLabel *Label2;
        TBitBtn *BButExit;
        TColSel *ColSel1;
        TColSel *ColSel2;
        TNumIO *NIONumColors;
        TGradFill *GradFill3;
        TGradFill *GFQuad;
        TLabel *Label3;
        TLabel *Label1;
        TLabel *Label4;
        TLabel *Label5;
        TComboBox *CBoxGridMode;
        TColSel *CselGrid;
        TRadioGroup *RGSelect;
        void __fastcall BButExitClick(TObject *Sender);
        void __fastcall SBToggleColorsClick(TObject *Sender);
        void __fastcall ColSel1Change(TObject *Sender);
        void __fastcall ColSel2Change(TObject *Sender);
        void __fastcall NIONumColorsChange(TObject *Sender);
        void __fastcall CBoxGridModeClick(TObject *Sender);
        void __fastcall CselGridClick(TObject *Sender);
        void __fastcall RGSelectClick(TObject *Sender);

private:        // User declarations
public:         // User declarations
        __fastcall TFrmGradFill(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFrmGradFill *FrmGradFill;
//---------------------------------------------------------------------------
#endif
