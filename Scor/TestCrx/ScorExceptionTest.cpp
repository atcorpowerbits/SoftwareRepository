
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting;
namespace TestCrx {
    using namespace System;
    ref class ScorExceptionTest;
    
    
    /// <summary>
///This is a test class for ScorExceptionTest and is intended
///to contain all ScorExceptionTest Unit Tests
///</summary>
	[TestClass]
	public ref class ScorExceptionTest
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
				String ^ excepMessage = "This is a test excpetion";
				ScorException^  target = (gcnew ScorException(gcnew Exception(excepMessage))); // TODO: Initialize to an appropriate value
				Exception^  actual;
				actual = target->ExceptionObject;
				Assert::IsNotNull(actual);
				Assert::AreEqual(excepMessage, actual->Message);
			}
			/// <summary>
			///A test for ErrorType
			///</summary>
	public: [TestMethod]
			void ErrorTypeTest()
			{
				ScorException^  target = (gcnew ScorException(111, "TestKey", ErrorSeverity::Warning )); // TODO: Initialize to an appropriate value
				ErrorSeverity actual;
				actual = target->ErrorType;
				Assert::AreEqual(ErrorSeverity::Warning , actual);
			}
			/// <summary>
			///A test for ErrorMessageKey
			///</summary>
	public: [TestMethod]
			void ErrorMessageKeyTest()
			{
				String^ testKey = "SCOR_TEST_KEY";
				ScorException^  target = (gcnew ScorException(111,testKey, ErrorSeverity::Warning)); // TODO: Initialize to an appropriate value
				String^  actual;
				actual = target->ErrorMessageKey;
				Assert::AreEqual(testKey, actual);
			}
			/// <summary>
			///A test for ErrorCode
			///</summary>
	public: [TestMethod]
			void ErrorCodeTest()
			{
				int testErrorCode = 999;
				ScorException^  target = (gcnew ScorException(testErrorCode, "TestKey", ErrorSeverity::Warning )); // TODO: Initialize to an appropriate value
				int actual;
				actual = target->ErrorCode;
				Assert::AreEqual(testErrorCode, actual);
			}
			/// <summary>
			///A test for ScorException Constructor
			///</summary>
	public: [TestMethod]
			void ScorExceptionConstructorTest3()
			{
				int errorCode = 100; // TODO: Initialize to an appropriate value
				String^  errorKey = "Scor_Key"; // TODO: Initialize to an appropriate value
				ErrorSeverity errorType = ErrorSeverity(); // TODO: Initialize to an appropriate value
				Exception^  exceptionObject = gcnew Exception(); // TODO: Initialize to an appropriate value
				cli::array< String^  >^  arr = gcnew array<String^>(1); // TODO: Initialize to an appropriate value
				
				//Begin: Smarajit(04-Mar-2011)
				errorType = ErrorSeverity::Information ;
				//exceptionObject-> = "ScorExceptionConstructorTest3";
				arr[0] = "Arr_ScorExceptionConstructorTest3";
				ScorException^  target = (gcnew ScorException(errorCode, errorKey, errorType, exceptionObject, arr));

				Assert::AreEqual(errorCode, target->ErrorCode);
				Assert::AreEqual(errorKey, target->ErrorMessageKey);
				Assert::AreEqual(errorType, target->ErrorType);
				Assert::AreEqual(exceptionObject->Message, target->ExceptionObject->Message);
				Assert::AreEqual(arr[0], target->ErrorStringArr[0]);
				
				arr = gcnew array<String^>(0);
				target = (gcnew ScorException(errorCode, errorKey, errorType, exceptionObject, nullptr));
				Assert::AreEqual(arr->Length, target->ErrorStringArr->Length);

				//End: Smarajit(04-Mar-2011)
			}
			/// <summary>
			///A test for ScorException Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void ScorExceptionConstructorTest2()
			{
				ScorException_Accessor^  target = (gcnew ScorException_Accessor());
				Assert::IsNotNull(target);
				Assert::AreEqual(0, target->ErrorCode);
			}
			/// <summary>
			///A test for ScorException Constructor
			///</summary>
	public: [TestMethod]
			void ScorExceptionConstructorTest1()
			{
				int errorCode = 999; // TODO: Initialize to an appropriate value
				String^  errorKey = "SCOR_TEST_EXCEP_KEY"; // TODO: Initialize to an appropriate value
				ErrorSeverity errorType = ErrorSeverity();
				errorType = ErrorSeverity::Information ;
				ScorException^  target = (gcnew ScorException(errorCode, errorKey, errorType));
				Assert::AreEqual(errorCode, target->ErrorCode);
				Assert::AreEqual(errorKey, target->ErrorMessageKey);
				Assert::AreEqual(errorType, target->ErrorType);
			}
			/// <summary>
			///A test for ScorException Constructor
			///</summary>
	public: [TestMethod]
			void ScorExceptionConstructorTest()
			{
				String^ testExceptionString = "TEST_KEY";
				Exception^  exceptionObject = gcnew Exception(testExceptionString); // TODO: Initialize to an appropriate value
				ScorException^  target = (gcnew ScorException(exceptionObject));
				Assert::AreEqual(testExceptionString, target->ExceptionObject->Message);
			}
	};
}
namespace TestCrx {
    
}
