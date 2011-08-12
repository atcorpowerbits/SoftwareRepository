
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting;
namespace TestCrx {
    using namespace System;
    ref class CrxShowStatusEventArgsTest;
    
    
    /// <summary>
///This is a test class for CrxShowStatusEventArgsTest and is intended
///to contain all CrxShowStatusEventArgsTest Unit Tests
///</summary>
	[TestClass]
	public ref class CrxShowStatusEventArgsTest
	{

	private: Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  testContextInstance;
			 /// <summary>
			 ///Gets or sets the test context which provides
			 ///information about and functionality for the current test run.
			 ///</summary>
	public: property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  TestContext
			{
				Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  get()
				{
					return testContextInstance;
				}
				System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  value)
				{
					testContextInstance = value;
				}
			}

#pragma region Additional test attributes
			// 
			//You can use the following additional attributes as you write your tests:
			//
			//Use ClassInitialize to run code before running the first test in the class
			//public: [ClassInitialize]
			//static System::Void MyClassInitialize(TestContext^  testContext)
			//{
			//}
			//
			//Use ClassCleanup to run code after all tests in a class have run
			//public: [ClassCleanup]
			//static System::Void MyClassCleanup()
			//{
			//}
			//
			//Use TestInitialize to run code before running each test
			//public: [TestInitialize]
			//System::Void MyTestInitialize()
			//{
			//}
			//
			//Use TestCleanup to run code after each test has run
			//public: [TestCleanup]
			//System::Void MyTestCleanup()
			//{
			//}
			//
#pragma endregion
			/// <summary>
			///A test for objScorException
			///</summary>
	public: [TestMethod]
			void objScorExceptionTest()
			{
				ScorException^  objScorException = nullptr; // TODO: Initialize to an appropriate value
				CrxShowStatusEventArgs^  target = (gcnew CrxShowStatusEventArgs(objScorException)); // TODO: Initialize to an appropriate value
				//ScorException^  expected = nullptr; // TODO: Initialize to an appropriate value
				ScorException^  actual;
				ScorException^  expected = gcnew ScorException(1020,"SCOR_TEST_EXCEP_KEY",ErrorSeverity::Information);
				target->ObjScorException = expected;
				actual = target->ObjScorException;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for CrxShowStatusEventArgs Constructor
			///</summary>
	public: [TestMethod]
			void CrxShowStatusEventArgsConstructorTest()
			{
				ScorException^  objScorException = nullptr; // TODO: Initialize to an appropriate value
				CrxShowStatusEventArgs^  target = (gcnew CrxShowStatusEventArgs(objScorException));
				// check if object is created
				Assert::IsNotNull(target);
			}
	};
}
namespace TestCrx {
    
}
