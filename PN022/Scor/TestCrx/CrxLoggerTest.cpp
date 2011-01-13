
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting::Logging;
namespace TestCrx {
    using namespace System;
    ref class CrxLoggerTest;
    
    
    /// <summary>
///This is a test class for CrxLoggerTest and is intended
///to contain all CrxLoggerTest Unit Tests
///</summary>
	[TestClass]
	public ref class CrxLoggerTest
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
			///A test for Instance
			///</summary>
	public: [TestMethod]
			void InstanceTest()
			{
				CrxLogger^  actual;
				actual = CrxLogger::Instance;
				Assert::IsNull(actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for Write
			///</summary>
	public: [TestMethod]
			void WriteTest()
			{
				CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); // TODO: Initialize to an appropriate value
				String^  message = System::String::Empty; // TODO: Initialize to an appropriate value
				target->Write(message);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
	//		/// <summary>
	//		///A test for op_Assign
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void op_AssignTest()
	//		{
	//			CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxLogger^  unnamed = nullptr; // TODO: Initialize to an appropriate value
	//			CrxLogger^  expected = nullptr; // TODO: Initialize to an appropriate value
	//			CrxLogger^  actual;
	//			actual = (target = unnamed);
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}
			/// <summary>
			///A test for GetLastWrittenLineNumber
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetLastWrittenLineNumberTest()
			{
				CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); // TODO: Initialize to an appropriate value
				target->GetLastWrittenLineNumber();
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for CrxLogger Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxLoggerConstructorTest1()
			{
				CrxLogger^  unnamed = nullptr; // TODO: Initialize to an appropriate value
				CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor(unnamed));
				Assert::IsNotNull(target);
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
			/// <summary>
			///A test for CrxLogger Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxLoggerConstructorTest()
			{
				CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor());
				Assert::IsNotNull(target);
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
	};
}
namespace TestCrx {
    
}
