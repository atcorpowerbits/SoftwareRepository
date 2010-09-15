//---------------------------------------------------------------------------
#ifndef uplot3dH
#define uplot3dH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Colsel.hpp"
#include "NumLab.hpp"
#include "plot3d.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
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
        TPlot3D *Plot3D1;
        TPanel *Panel2;
        TNumLab *NLabZ;
        TNumLab *NLabX;
        TLabel *Label1;
        TNumLab *NLabMag;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *LblColMid;
        TLabel *Label5;
        TLabel *Label4;
        TSpeedButton *SbAutoscale;
        TSpeedButton *SBReset;
        TScrollBar *ScrBarAngleZ;
        TScrollBar *ScrBarAngleX;
        TColSel *CSelHigh;
        TColSel *CSelLow;
        TColSel *CSelGrid;
        TScrollBar *ScrBarMagnif;
        TBitBtn *BButExit;
        TCheckBox *CBoxMesh;
        TColSel *CselMid;
        TScrollBar *ScrBarColorHigh;
        TCheckBox *CBox3colmod;
        TScrollBar *ScrBarSclZ;
        TScrollBar *ScrBarSclY;
        TScrollBar *ScrBarSclX;
        TPopupMenu *popMenMouse;
        TMenuItem *Rotate1;
        TMenuItem *Pan1;
        TMenuItem *Zoom1;
        TMenuItem *RotateandZoom1;
        TMenuItem *RotXOnly1;
        TMenuItem *RotZOnly1;
        TLabel *Label6;
        TRadioGroup *RGFrameMode;
        TCheckBox *CBoxGridCursor;
        TNumLab *NLabCellX;
        TNumLab *NLabCellY;
        TLabel *Label9;
        TColSel *ColSelX;
        TColSel *ColSelY;
        TColSel *ColSelZ;
        TCheckBox *CBoxXCoords;
        TCheckBox *CBoxYCoords;
        TCheckBox *CBoxZCoords;
        void __fastcall Plot3D1MouseAction(TObject *Sender, int &CenterX,
          int &CenterY, double &RotXAngle, double &RotZAngle,
          double &Magnification, TShiftState Shift);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BButExitClick(TObject *Sender);
        void __fastcall ScrBarAngleXChange(TObject *Sender);
        void __fastcall ScrBarAngleZChange(TObject *Sender);
        void __fastcall ScrBarMagnifChange(TObject *Sender);
        void __fastcall CSelHighChange(TObject *Sender);
        void __fastcall CselMidChange(TObject *Sender);
        void __fastcall CSelLowChange(TObject *Sender);
        void __fastcall CSelGridChange(TObject *Sender);
        void __fastcall CBoxMeshClick(TObject *Sender);
        void __fastcall Rotate1Click(TObject *Sender);
        void __fastcall Pan1Click(TObject *Sender);
        void __fastcall Zoom1Click(TObject *Sender);
        void __fastcall RotateandZoom1Click(TObject *Sender);
        void __fastcall RotXOnly1Click(TObject *Sender);
        void __fastcall RotZOnly1Click(TObject *Sender);
        void __fastcall CBox3colmodClick(TObject *Sender);
        void __fastcall SbAutoscaleClick(TObject *Sender);
        void __fastcall ScrBarSclXChange(TObject *Sender);
        void __fastcall ScrBarSclYChange(TObject *Sender);
        void __fastcall ScrBarSclZChange(TObject *Sender);
        void __fastcall SBResetClick(TObject *Sender);
        void __fastcall ScrBarColorHighChange(TObject *Sender);
        void __fastcall RGFrameModeClick(TObject *Sender);
        void __fastcall Plot3D1BeforeRenderPolygon(TObject *Sender,
          TCanvas *&Canvas, bool &Handled, int CellX, int CellY,
          TQuad &quad, TColor &color);
        void __fastcall Plot3D1DataRendered(TObject *Sender,
          TCanvas *&Canvas);
        void __fastcall Plot3D1MouseMoveOverPlot(TObject *Sender,
          bool OverPlot, TShiftState Shift, int MouseCellX,
          int MouseCellY);
        void __fastcall CBoxZCoordsClick(TObject *Sender);
        void __fastcall ColSelZChange(TObject *Sender);
        void __fastcall ColSelYChange(TObject *Sender);
        void __fastcall ColSelXChange(TObject *Sender);
private:        // User declarations
        int MCellX, MCellY;
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
