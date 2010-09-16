// bizmix.h

#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Biz {

public ref class Person
{
public:
   Person(String^ name, DateTime birthDate);
   virtual ~Person();

   property unsigned int Age
   {
      unsigned int get();
   }

   static int CallCFunctionImplicit();
   static int CallCVarImplicit();

   // Sample of direct native API call.
   [DllImport("bizcor.dll")]
   static int fnBizCorNativeDLL();

   // Note that direct call of a variable export is forbidden.

private:
   Person() : _pPerson(NULL) { }

   // NOTE: Declaring a member "CPerson _person2;" would generate a C4368 compiler error
   //       (cannot define 'member' as a member of managed 'type': mixed types are not supported).
   //
   // That's why a pointer (seen as 'unsafe' in C#) is created.
   //
   // What says the documentation:
   // ----------------------------
   // You cannot embed a native data member in a CLR type.
   //
   // You can, however, declare a pointer to a native type and control its lifetime in the
   // constructor and destructor and finalizer of your managed class (see Destructors and Finalizers
   // in Visual C++ for more information).
   CPerson* _pPerson;
};

//} } } }
}
