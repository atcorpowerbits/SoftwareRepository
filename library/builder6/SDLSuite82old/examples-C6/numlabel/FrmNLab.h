//---------------------------------------------------------------------------
#ifndef FrmNLabH
#define FrmNLabH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include "NumLab.hpp"
#include "Colsel.hpp"
#include <vcl\Buttons.hpp>
#include "colsel.hpp"
#include "numlab.hpp"
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
        TBevel *Bevel1;
        TNumLab *NumLab1;
        TBevel *Bevel2;
        TNumLab *NLabPreci;
        TScrollBar *SBPrecis;
        TScrollBar *ScrollBar1;
        TGroupBox *GroupBox1;
        TRadioButton *RBRaised;
        TRadioButton *RBLowered;
        TRadioButton *RbEmbossed;
        TRadioButton *RBEngraved;
        TRadioButton *RBSimple;
        TRadioButton *RBNone;
        TGroupBox *GroupBox2;
        TRadioButton *RBFixP;
        TRadioButton *RBFloat;
        TRadioButton *RBInt;
        TRadioButton *RBZeroInt;
        TRadioButton *RBExp;
        TRadioButton *RBHex;
        TColSel *ColSel3;
        TBevel *Bevel6;
        TColSel *ColSel1;
        TColSel *ColSel2;
        TColSel *ColSel4;
        TGroupBox *GroupBox3;
        TRadioButton *RBCenter;
        TRadioButton *RBLeft;
        TRadioButton *RBRight;
        TBitBtn *BButExit;
        TBevel *Bevel3;
        TNumLab *NLabWidth;
        TScrollBar *SBWidth;
        TBevel *Bevel4;
        TNumLab *NLabLeftSpace;
        TScrollBar *SBLeftSpace;
        TNumLab *NLabLabelWidth;
        TScrollBar *ScrollBar2;
        TBevel *Bevel5;
        TGroupBox *GroupBox4;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TGroupBox *GroupBox5;
        TRadioButton *RadioButton4;
        TRadioButton *RadioButton5;
        TRadioButton *RadioButton6;
        TCheckBox *CBForcePlusSign;
        TRadioButton *RBDateTime;
        TEdit *EdDateTime;
        TRadioButton *RBBin;
        TRadioButton *RBOct;
        TRadioButton *RBState;
        TRadioButton *RBLatDeg;
        TRadioButton *RBLatDegMin;
        TRadioButton *RBLatDegMinSec;
        void __fastcall BButExitClick(TObject *Sender);
        void __fastcall ScrollBar1Change(TObject *Sender);
        void __fastcall RBRaisedClick(TObject *Sender);
        void __fastcall RBLoweredClick(TObject *Sender);
        void __fastcall RbEmbossedClick(TObject *Sender);
        void __fastcall RBEngravedClick(TObject *Sender);
        void __fastcall RBSimpleClick(TObject *Sender);
        void __fastcall RBNoneClick(TObject *Sender);
        void __fastcall RBFixPClick(TObject *Sender);
        void __fastcall RBFloatClick(TObject *Sender);
        void __fastcall RBIntClick(TObject *Sender);
        void __fastcall RBZeroIntClick(TObject *Sender);
        void __fastcall RBExpClick(TObject *Sender);
        void __fastcall RBHexClick(TObject *Sender);
        void __fastcall RBCenterClick(TObject *Sender);
        void __fastcall RBLeftClick(TObject *Sender);
        void __fastcall RBRightClick(TObject *Sender);
        void __fastcall ColSel1Change(TObject *Sender);
        void __fastcall ColSel2Change(TObject *Sender);
        void __fastcall ColSel3Change(TObject *Sender);
        void __fastcall ColSel4Change(TObject *Sender);
        void __fastcall SBPrecisChange(TObject *Sender);
        void __fastcall SBWidthChange(TObject *Sender);
        void __fastcall SBLeftSpaceChange(TObject *Sender);
        void __fastcall ScrollBar2Change(TObject *Sender);
        void __fastcall RBDateTimeClick(TObject *Sender);
        void __fastcall CBForcePlusSignClick(TObject *Sender);
        void __fastcall EdDateTimeChange(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall RadioButton3Click(TObject *Sender);
        void __fastcall RadioButton4Click(TObject *Sender);
        void __fastcall RadioButton5Click(TObject *Sender);
        void __fastcall RadioButton6Click(TObject *Sender);
        void __fastcall RBBinClick(TObject *Sender);
        void __fastcall RBOctClick(TObject *Sender);
        void __fastcall RBStateClick(TObject *Sender);
        void __fastcall RBLatDegClick(TObject *Sender);
        void __fastcall RBLatDegMinClick(TObject *Sender);
        void __fastcall RBLatDegMinSecClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:        // User declarations
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
