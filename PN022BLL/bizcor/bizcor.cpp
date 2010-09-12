// bizcor.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "bizcor.h"


// This is an example of an exported variable
BIZCORNATIVEDLL_API int nBizCorNativeDLL=0;

// This is an example of an exported function.
BIZCORNATIVEDLL_API int fnBizCorNativeDLL(void)
{
	return 42;
}

// ctor
CPerson::CPerson()
{
   *m_sName = 0;
   ::ZeroMemory(&m_birthDate, sizeof(m_birthDate));
}

CPerson::CPerson(LPCTSTR pszName, SYSTEMTIME birthDate): m_birthDate(birthDate)
{
   if (pszName != 0)
      ::lstrcpy(m_sName, pszName);
}

unsigned int CPerson::get_Age(void)
{
   SYSTEMTIME st;
   unsigned int age;

   ::GetSystemTime(&st);

   age = (unsigned int)(st.wYear - m_birthDate.wYear);

   if ((m_birthDate.wMonth > st.wMonth) ||
      ((m_birthDate.wMonth == st.wMonth) && (m_birthDate.wDay > st.wDay)))
   {
      --age;
      ::MessageBeep(0);
   }

   return age;
}
