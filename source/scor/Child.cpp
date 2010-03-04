#include <vcl.h>
#pragma hdrstop

#pragma package(smart_init)
#include "form_main.h"
#include "child.h"

Child_Form *child_form;

__fastcall Child_Form::Child_Form(TComponent* Owner)
  : TForm(Owner)
{
}

void __fastcall Child_Form::Loaded(void)
{
   TForm::Loaded();
   Visible = False;
   Position = poDefault;
   BorderIcons = TBorderIcons();
   BorderStyle = bsNone;
   HandleNeeded();
   //SetBounds(0, 0, Width, Height);
}

void __fastcall Child_Form::CreateParams(Controls::TCreateParams &Params)
{
   TForm::CreateParams(Params);

   /*
   if (dynamic_cast<TForm*>(Owner))
   {
      Params.WndParent = dynamic_cast<TForm*>(Owner)->Handle;
   }
   */
   if (frm_main != NULL)
   {
      Params.WndParent = frm_main->Handle;
      Params.Style = WS_CHILD | WS_CLIPSIBLINGS;
      Params.X = 0;
      Params.Y = frm_main->pnl_main_tool->Height;// + 1;
      Params.Width = frm_main->ClientRect.Right;
      Params.Height = (frm_main->pnl_status_bar->Top) - Params.Y;
   }
   else
   {
      Params.X = 0;
      Params.Y = 0;
   }
}

