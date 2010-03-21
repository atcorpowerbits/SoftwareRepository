#ifndef CHILD_PUBTYPE
#define CHILD_PUBTYPE

#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>

class Child_Form : public TForm
{
__published: // IDE-managed Components
private:	 // User declarations
protected:
   virtual void __fastcall Loaded(void);
   virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
public:		// User declarations
  virtual __fastcall Child_Form(TComponent* Owner);
};

extern Child_Form *child_form;

#endif
