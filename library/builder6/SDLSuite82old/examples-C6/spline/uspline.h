//---------------------------------------------------------------------------

#ifndef usplineH
#define usplineH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "math2.hpp"
#include "numlab.hpp"
#include "rchart.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TNumLab *NLab1;
        TNumLab *NLabN;
        TNumLab *NLabSmoothing;
        TCheckBox *CBNat1;
        TCheckBox *CBNatN;
        TScrollBar *SBDeriv1;
        TScrollBar *SBDerivN;
        TBitBtn *BButExit;
        TScrollBar *SBarSmoothFact;
        TRChart *RChart1;
        TCurveFit *CurveFit;
        void __fastcall CBNat1Click(TObject *Sender);
        void __fastcall CBNatNClick(TObject *Sender);
        void __fastcall SBDeriv1Change(TObject *Sender);
        void __fastcall SBDerivNChange(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall RChart1MouseMoveInChart(TObject *Sender,
          bool InChart, TShiftState Shift, double rMousePosX,
          double rMousePosY);
        void __fastcall BButExitClick(TObject *Sender);
        void __fastcall SBarSmoothFactChange(TObject *Sender);
private:	// User declarations
        bool SuppressCalc;
        void _fastcall CalcAndShowSpline();
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
