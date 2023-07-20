
#include "StdAfx.h"
#include <biz.h>
using namespace BIZ_NAMESPACE;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace TestBiz {
    using namespace System;
    ref class BizSPAndDPTest;
    
    
    /// <summary>
///This is a test class for BizSPAndDPTest and is intended
///to contain all BizSPAndDPTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizSPAndDPTest
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
			///A test for Validate
			///</summary>
	public: [TestMethod]
			void BizSPAndDPValidateTest()
			{
				BizSPAndDP^  target = (gcnew BizSPAndDP()); // TODO: Initialize to an appropriate value
				bool actual;

				// SP invalid
				target->SP->Reading = 0;
				target->DP->Reading = 80;
				actual = target->Validate();
				Assert::AreEqual(false, actual);

				// DP invalid
				target->SP->Reading = 80;
				target->DP->Reading = 0;
				actual = target->Validate();
				Assert::AreEqual(false, actual);

				// normal SP & DP
				target->SP->Reading = 120;
				target->DP->Reading = 80;
				actual = target->Validate();
				Assert::AreEqual(true, actual);

				// SP & DP too close
				target->SP->Reading = 100;
				target->DP->Reading = 99;
				actual = target->Validate();
				Assert::AreEqual(false, actual);

				// SP is less than DP
				target->SP->Reading = 99;
				target->DP->Reading = 100;
				actual = target->Validate();
				Assert::AreEqual(false, actual);
			}
	};
}
namespace TestBiz {
    
}
