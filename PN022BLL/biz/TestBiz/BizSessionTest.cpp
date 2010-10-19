
#include "StdAfx.h"
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace Biz;
namespace TestBiz {
    using namespace System;
    ref class BizSessionTest;
    
    
    /// <summary>
///This is a test class for BizSessionTest and is intended
///to contain all BizSessionTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizSessionTest
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
			///A test for StartCapture
			///</summary>
	public: [TestMethod]
			void BizSessionStartCaptureTest()
			{
				BizSession^  target = BizSession::Instance(); // TODO: Initialize to an appropriate value
				bool expected = true; // TODO: Initialize to an appropriate value
				bool actual;
				actual = target->StartCapture();
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for Instance
			///</summary>
	public: [TestMethod]
			void BizSessionInstanceTest()
			{
				BizSession^  expected = nullptr; // TODO: Initialize to an appropriate value
				BizSession^  actual;
				actual = BizSession::Instance();
				Assert::AreNotEqual(expected, actual);
				Assert::AreNotEqual(expected, actual->measurement);// to test measurement object is created.
			}
			/// <summary>
			///A test for ClearMeasurement
			///</summary>
	public: [TestMethod]
			void ClearMeasurementTest()
			{
				BizSession^  target = BizSession::Instance(); // TODO: Initialize to an appropriate value
				BizMeasure^ old = target->measurement;
				target->ClearMeasurement();
				Assert::AreNotEqual(old, target->measurement);
			}
	};
}
namespace TestBiz {
    
}
