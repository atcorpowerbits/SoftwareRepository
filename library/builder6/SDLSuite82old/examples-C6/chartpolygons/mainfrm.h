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
        TRadioGroup *RadioGroup1;
        TRadioGroup *RGzPos;
        TRChart *RChart1;
        void __fastcall BButExitClick(TObject *Sender);
        void __fastcall RadioGroup1Click(TObject *Sender);
        void __fastcall RChart1DataRendered(TObject *Sender,
          TCanvas *&Canvas, int Top, int Left);
        void __fastcall RChart1BeforeRenderData(TObject *Sender,
          TCanvas *&Canvas, int Top, int Left);
        void __fastcall RGzPosClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:
        void __fastcall DrawPolygon (TCanvas *Canvas, const int Top, const int Left);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
