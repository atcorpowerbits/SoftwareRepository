//---------------------------------------------------------------------------

#ifndef frmmainH
#define frmmainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *LblHue;
        TLabel *LblSat;
        TLabel *LblIntens;
        TLabel *LblRed;
        TLabel *LblGreen;
        TLabel *LblBlue;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TScrollBar *SBarHue;
        TScrollBar *SBarSat;
        TScrollBar *SBarIntens;
        TPanel *PnlRed;
        TPanel *PnlGreen;
        TPanel *PnlBlue;
        TPanel *PnlColor;
        TEdit *EdHTML;
        TButton *ButInvert;
        void __fastcall SBarIntensChange(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ButInvertClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
