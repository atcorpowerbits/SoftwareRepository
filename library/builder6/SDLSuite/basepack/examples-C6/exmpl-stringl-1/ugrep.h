//---------------------------------------------------------------------------
#ifndef ugrepH
#define ugrepH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TBevel *Bevel1;
	TBitBtn *BButExit;
	TEdit *EdRegexp;
	TCheckBox *CBIgnoreCase;
	TBitBtn *BButStartSearch;
	TMemo *MMResult;
	TOpenDialog *OpenDialog1;
	void __fastcall BButExitClick(TObject *Sender);
	void __fastcall CBIgnoreCaseClick(TObject *Sender);
	void __fastcall BButStartSearchClick(TObject *Sender);
	
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
