//---------------------------------------------------------------------------
#ifndef vector1H
#define vector1H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "Grids.hpp"
#include "vector.hpp"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *LblLeng;
	TLabel *LblMin;
	TLabel *LblMax;
	TLabel *LblMean;
	TLabel *LblVar;
	TButton *ButDV;
	TStringGrid *SG1;
	TLabel *LblQuart;
        TVector *Vec1;
	void __fastcall ButDVClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall SG1SetEditText(TObject *Sender, int ACol, int ARow,
	const AnsiString Value);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
