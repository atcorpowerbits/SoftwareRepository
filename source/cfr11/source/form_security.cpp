//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#define SECURITY_WIN32

#include <inc/std.h>
#include <msg/pubserv.h>
#include <config/pubserv.h>
#include <cfr11/pubserv.h>
#include <scor/form_main.h>
#include "windows.h"
#include "form_security.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
VAR_EXPORT Tfrm_security *frm_security;

VAR_EXPORT String username;
VAR_EXPORT String password;

bool security_initialised;
bool first_time;
//---------------------------------------------------------------------------
__fastcall Tfrm_security::Tfrm_security(TComponent* Owner)
   : TForm(Owner)
{

}
//---------------------------------------------------------------------------
bool security_initialise()
{
   security_initialised = true;
   first_time = true;
   username = "";

   return security_initialised;
}
//---------------------------------------------------------------------------
void security_destroy()
{
   security_initialised = false;
}

String security_get_username()
{
   return (username);
}

bool security_show()
{
   bool ret;

   // If the audit option is set, show the security form
   if (config_get_audit_option())
   {
      // Return true if their identity is verified, false otherwise
      frm_security = new Tfrm_security(Application->MainForm);
      frm_security->ShowModal();
      ret = (frm_security->ModalResult == mrYes ? true : false);
      delete frm_security;
   }
   else
   {
      ret = true;
   }

   return ret;
}

void security_lock_workstation()
{
   // If the audit option is set, call the Windows Lock function
   if (config_get_audit_option())
   {
      LockWorkStation();
   }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_security::btnOkClick(TObject *Sender)
{
   // If the identity is verified, allow the form to close and return a positive result
   // Otherwise clear the password and give it focus
   if (security_validate())
   {
      ModalResult = mrYes;
   }
   else
   {
      edt_security_password->Text = "";
      edt_security_password->SetFocus();
   }
}

bool Tfrm_security::security_validate()
{
   DWORD LogonType = LOGON32_LOGON_NETWORK;
   DWORD LogonProvider = LOGON32_PROVIDER_DEFAULT;
   HANDLE UserToken; // Do not use PHANDLE
   String ErrorMessage;
   LPVOID lpMsgBuf;
   SID Guest;
   int Error;
   bool valid = true;
   BOOL guest_account;
   SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
   PSID GuestGroup;

   // Validate inputs
   if (edt_security_username->Text.Length() == 0)
   {
      valid = false;
      edt_security_username->SetFocus();
   }
   else if (edt_security_password->Text.Length() == 0)
   {
      valid = false;
      edt_security_password->SetFocus();
   }
   if (!valid)
   {
      MsgBox(MSG_SECURITY_CHECK_INPUT, SVALIDATION, MB_ICONEXCLAMATION);
   }
   else
   {
      // Authenticate Windows Logon
      try
      {
         if (LogonUser(edt_security_username->Text.c_str(), "", edt_security_password->Text.c_str(),
                        LogonType, LogonProvider, &UserToken))
         {
            // PM V9
            // Do not allow Windows Guest Accounts
            if (AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_GUESTS, 0, 0, 0, 0, 0, 0, &GuestGroup))
            {
               if (CheckTokenMembership(UserToken, GuestGroup, &guest_account))
               {
                  if (guest_account)
                  {
                     MsgBox_show(TNOTIFICATION,
                                 MSG_SECURITY,
                                 LoadStr(MSG_SECURITY_GUEST),
                                 MSG_SECURITY_GUEST,
                                 LoadStr(MSG_SECURITY_GUEST));
                     valid = false;
                  }
                  else
                  {
                     // Populate logon, display notification and write to log
                     username = edt_security_username->Text;
                     password = edt_security_password->Text;
                     /*MsgBox_show(TNOTIFICATION,
                                 MSG_SECURITY,
                                 LoadStr(MSG_SECURITY_SUCCESS) + username,
                                 MSG_SECURITY_SUCCESS,
                                 LoadStr(MSG_SECURITY_SUCCESS) + username);*/
                  }
               }
               else
               {
                  // Display error message and write to log
                  Error = GetLastError();
                  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                                 NULL,
                                 Error,
                                 MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                                 (LPTSTR) &lpMsgBuf,
                                 0,
                                 NULL);

                  ErrorMessage = AnsiString((LPCTSTR) lpMsgBuf);
                  MsgBox_show(TERROR,
                              MSG_SECURITY,
                              ErrorMessage,
                              MSG_SECURITY_FAILED,
                              "");
                  valid = false;
               }
               FreeSid(GuestGroup);
            }
            else
            {
               // Display error message and write to log
               Error = GetLastError();
               FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                              NULL,
                              Error,
                              MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                              (LPTSTR) &lpMsgBuf,
                              0,
                              NULL);

               ErrorMessage = AnsiString((LPCTSTR) lpMsgBuf);
               MsgBox_show(TERROR,
                           MSG_SECURITY,
                           ErrorMessage,
                           MSG_SECURITY_FAILED,
                           "");
               valid = false;
            }
         }
         else
         {
            // Display error message and write to log
            Error = GetLastError();
            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL,
                           Error,
                           MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                           (LPTSTR) &lpMsgBuf,
                           0,
                           NULL);

            ErrorMessage = AnsiString((LPCTSTR) lpMsgBuf);
            MsgBox_show(TERROR,
                        MSG_SECURITY,
                        ErrorMessage,
                        MSG_SECURITY_FAILED,
                        "");
            valid = false;

            // Consecutive failures to logon will lock the system until another
            // user successfully logs in
            if (Error == ERROR_ACCOUNT_LOCKED_OUT)
            {
               MsgBox_show(TERROR,
                           MSG_SECURITY,
                           LoadStr(MSG_SECURITY_LOCKED),
                           MSG_SECURITY_LOCKED,
                           "");
               btnCancel->Enabled = false;
            }
         }
      }
      catch (Exception &exception)
      {
         MsgBox_show(TERROR,
                 MSG_EXCEPTION,
                 LoadStr(MSG_SECURITY_FAILED),
                 MSG_SECURITY_FAILED,
                 LoadStr(MSG_SECURITY_FAILED) + exception.Message);
         valid = false;
      }
   }

   // Protect password privacy
   if (password.Length() != 0)
   {
      ZeroMemory(password.c_str(), sizeof(password));
   }

   // Free memory
   LocalFree(lpMsgBuf);

   return (valid);
}

void __fastcall Tfrm_security::FormShow(TObject *Sender)
{
   if (security_initialised)
   {
      edt_security_username->Text = username;
      edt_security_password->Text = "";
      if (username.Length())
      {
         edt_security_password->SetFocus();
      }
      if (first_time)
      {
         lbl_security->Caption = SECURITY_LOGIN;
         frm_security->Height = 355;
         first_time = false;
      }
      else
      {
         lbl_security->Caption = SECURITY_SIGNATURE;
         frm_security->Height = 445;
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_security::btnCancelClick(TObject *Sender)
{
   // Returns a negative result
   MsgBox_show(TERROR,
               MSG_SECURITY,
               LoadStr(MSG_SECURITY_FAILED),
               MSG_SECURITY_FAILED,
               LoadStr(MSG_SECURITY_FAILED));
   Close();
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_security::FormKeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_RETURN)
   {
      btnOkClick(this);
   }
   else if (Key == VK_ESCAPE)
   {
      btnCancelClick(this);
   }
}
//---------------------------------------------------------------------------

