
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalExceptionTest;
    
    
    /// <summary>
///This is a test class for DalExceptionTest and is intended
///to contain all DalExceptionTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalExceptionTest
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
				DalException^  target = (gcnew DalException()); // TODO: Initialize to an appropriate value
				Exception^  actual;
				actual = target->ExceptionObject;
				Assert::AreEqual(target->ExceptionObject , actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for ErrorString
			///</summary>
	public: [TestMethod]
			void ErrorStringTest()
			{
				DalException^  target = (gcnew DalException()); // TODO: Initialize to an appropriate value
				String^  expected = "This is an error."; // TODO: Initialize to an appropriate value
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
				DalException^  target = (gcnew DalException()); // TODO: Initialize to an appropriate value
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;
				target->ErrorCode = expected;
				actual = target->ErrorCode;
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for DalException Constructor
			///</summary>
	public: [TestMethod]
			void DalExceptionConstructorTest4()
			{
				String^  errExpStr = "CONFIG_NAME_PWV"; // TODO: Initialize to an appropriate value
				DalException^  target = (gcnew DalException(errExpStr));
				Assert::AreEqual(target->ErrorString, errExpStr);
			//	Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
			/// <summary>
			///A test for DalException Constructor
			///</summary>
	public: [TestMethod]
			void DalExceptionConstructorTest3()
			{
				int exError = 1; // TODO: Initialize to an appropriate value
				String^  errExpStr = "CONFIG_NAME_PWV"; // TODO: Initialize to an appropriate value
				Exception^  errExp = gcnew Exception("Default exception"); // TODO: Initialize to an appropriate value
				DalException^  target = (gcnew DalException(exError, errExpStr, errExp));
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
				Assert::AreEqual(target->ExceptionObject , errExp);
				Assert::AreEqual(errExpStr, target->ErrorString);
			}
			/// <summary>
			///A test for DalException Constructor
			///</summary>
	public: [TestMethod]
			void DalExceptionConstructorTest2()
			{
				Exception^  errExp = gcnew Exception("Default exception");; // TODO: Initialize to an appropriate value
				DalException^  target = (gcnew DalException(errExp));
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
				Assert::AreEqual(target->ExceptionObject, errExp);
			}
			/// <summary>
			///A test for DalException Constructor
			///</summary>
	public: [TestMethod]
			void DalExceptionConstructorTest1()
			{
				DalException^  target = (gcnew DalException());
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
				Assert::IsNull(target->ExceptionObject);
			}
			/// <summary>
			///A test for DalException Constructor
			///</summary>
	public: [TestMethod]
			void DalExceptionConstructorTest()
			{
				int exError = 0; // TODO: Initialize to an appropriate value
				DalException^  target = (gcnew DalException(exError));
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
				Assert::AreEqual(target->ErrorCode, exError);
			}
	};
}
namespace TestDal {
    
}
