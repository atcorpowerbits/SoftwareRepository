
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting;
namespace TestCrx {
    using namespace System;
    ref class CrxExceptionTest;
    
    
    /// <summary>
///This is a test class for CrxExceptionTest and is intended
///to contain all CrxExceptionTest Unit Tests
///</summary>
	[TestClass]
	public ref class CrxExceptionTest
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
			///A test for ExceptionObject
			///</summary>
	public: [TestMethod]
			void ExceptionObjectTest()
			{
				CrxException^  target = (gcnew CrxException()); // TODO: Initialize to an appropriate value
				Exception^  actual;
				actual = target->ExceptionObject;
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for ErrorString
			///</summary>
	public: [TestMethod]
			void ErrorStringTest()
			{
				CrxException^  target = (gcnew CrxException()); // TODO: Initialize to an appropriate value
				String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  actual;
				target->ErrorString = expected;
				actual = target->ErrorString;
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for ErrorCode
			///</summary>
	public: [TestMethod]
			void ErrorCodeTest()
			{
				CrxException^  target = (gcnew CrxException()); // TODO: Initialize to an appropriate value
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;
				target->ErrorCode = expected;
				actual = target->ErrorCode;
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for CrxException Constructor
			///</summary>
	public: [TestMethod]
			void CrxExceptionConstructorTest4()
			{
				String^  errExpStr = System::String::Empty; // TODO: Initialize to an appropriate value
				CrxException^  target = (gcnew CrxException(errExpStr));
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
			/// <summary>
			///A test for CrxException Constructor
			///</summary>
	public: [TestMethod]
			void CrxExceptionConstructorTest3()
			{
				int exError = 0; // TODO: Initialize to an appropriate value
				String^  errExpStr = System::String::Empty; // TODO: Initialize to an appropriate value
				Exception^  errExp = nullptr; // TODO: Initialize to an appropriate value
				CrxException^  target = (gcnew CrxException(exError, errExpStr, errExp));
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
			/// <summary>
			///A test for CrxException Constructor
			///</summary>
	public: [TestMethod]
			void CrxExceptionConstructorTest2()
			{
				//Exception^  errExp = nullptr; // TODO: Initialize to an appropriate value
				//CrxException^  target = (gcnew CrxException(errExp));
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
			/// <summary>
			///A test for CrxException Constructor
			///</summary>
	public: [TestMethod]
			void CrxExceptionConstructorTest1()
			{
				CrxException^  target = (gcnew CrxException());
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
			/// <summary>
			///A test for CrxException Constructor
			///</summary>
	public: [TestMethod]
			void CrxExceptionConstructorTest()
			{
				int exError = 0; // TODO: Initialize to an appropriate value
				CrxException^  target = (gcnew CrxException(exError));
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
	};
}
namespace TestCrx {
    
}
