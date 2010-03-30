//---------------------------------------------------------------------------

#ifndef mainfrmH
#define mainfrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "rchart.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TBitBtn *BButExit;
        TCheckBox *CBoxMouseAffectsLayer1;
        TCheckBox *CBoxMouseAffectsLayer2;
        TRadioGroup *RGLayout;
        TRadioGroup *RGMouseAction;
        TBitBtn *BButZoom11;
        TRadioGroup *RGGrid;
        TRChart *RC1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BButExitClick(TObject *Sender);
        void __fastcall CBoxMouseAffectsLayer1Click(TObject *Sender);
        void __fastcall CBoxMouseAffectsLayer2Click(TObject *Sender);
        void __fastcall RGLayoutClick(TObject *Sender);
        void __fastcall RGMouseActionClick(TObject *Sender);
        void __fastcall BButZoom11Click(TObject *Sender);
        void __fastcall RGGridClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
