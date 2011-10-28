
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class IDalHandlerTest;
    
    
    /// <summary>
///This is a test class for IDalHandlerTest and is intended
///to contain all IDalHandlerTest Unit Tests
///</summary>
	[TestClass]
	public ref class IDalHandlerTest
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
			///A test for StartBP
			///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void StartBPTest1()
	//		{
	//			IDalHandler_Accessor^  target = CreateIDalHandler_Accessor(); // TODO: Initialize to an appropriate value
	//			DalNIBPMode nibpMode = DalNIBPMode(); // TODO: Initialize to an appropriate value
	//			unsigned short initialPressure = 0; // TODO: Initialize to an appropriate value
	//			bool expected = false; // TODO: Initialize to an appropriate value
	//			bool actual;
	//			actual = target->StartBP(nibpMode, initialPressure);
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}
	//		/// <summary>
	//		///A test for StartBP
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void StartBPTest()
	//		{
	//			IDalHandler_Accessor^  target = CreateIDalHandler_Accessor(); // TODO: Initialize to an appropriate value
	//			DalNIBPMode nibpMode = DalNIBPMode(); // TODO: Initialize to an appropriate value
	//			bool expected = false; // TODO: Initialize to an appropriate value
	//			bool actual;
	//			actual = target->StartBP(nibpMode);
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}
	//		/// <summary>
	//		///A test for FinishBP
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void FinishBPTest()
	//		{
	//			IDalHandler_Accessor^  target = CreateIDalHandler_Accessor(); // TODO: Initialize to an appropriate value
	//			bool expected = false; // TODO: Initialize to an appropriate value
	//			bool actual;
	//			actual = target->FinishBP();
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}
	//internal: IDalHandler_Accessor^  CreateIDalHandler_Accessor()
	//		  {
	//			  // TODO: Instantiate an appropriate concrete class.
	//			  IDalHandler_Accessor^  target = nullptr;
	//			  return target;
	//		  }
	//		  /// <summary>
	//		  ///A test for AbortBP
	//		  ///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void AbortBPTest()
	//		{
	//			IDalHandler_Accessor^  target = CreateIDalHandler_Accessor(); // TODO: Initialize to an appropriate value
	//			bool expected = false; // TODO: Initialize to an appropriate value
	//			bool actual;
	//			actual = target->AbortBP();
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}
	};
}
namespace TestDal {
    
}
