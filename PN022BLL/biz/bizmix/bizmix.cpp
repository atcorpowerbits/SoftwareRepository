// This is the bizmix.DLL file.

#include "stdafx.h"

#include "bizmix.h"
#include <vcclr.h>

using namespace Biz;


Person::Person(String^ name, DateTime birthDate)
{
   SYSTEMTIME st = { (WORD)birthDate.Year, (WORD)birthDate.Month, (WORD)birthDate.DayOfWeek, (WORD)birthDate.Day,
      (WORD)birthDate.Hour, (WORD)birthDate.Minute, (WORD)birthDate.Second, (WORD)birthDate.Millisecond };

   // Pin 'name' memory before calling unmanaged code
   pin_ptr<const TCHAR> psz = PtrToStringChars(name);

   // Allocate the unmanaged object
   _pPerson = new CPerson(psz, st);
}

Person::~Person()
{
   if (this->_pPerson != 0)
   {
      delete this->_pPerson;
      this->_pPerson = 0;
   }
}

unsigned int Person::Age::get()
{
   return this->_pPerson->get_Age();
}

int Person::CallCFunctionImplicit()
{
   return ::fnBizCorNativeDLL();
}

int Person::CallCVarImplicit()
{
   return ::nBizCorNativeDLL;
}