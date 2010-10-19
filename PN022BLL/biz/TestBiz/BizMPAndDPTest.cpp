
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace Biz;
namespace TestBiz {
    using namespace System;
    ref class BizMPAndDPTest;
    
    
    /// <summary>
///This is a test class for BizMPAndDPTest and is intended
///to contain all BizMPAndDPTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizMPAndDPTest
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
			void BizMPAndDPValidateTest()
			{
				BizMPAndDP^  target = (gcnew BizMPAndDP()); // TODO: Initialize to an appropriate value
				bool actual;

				// MP invalid
				target->MP->Reading = 0;
				target->DP->Reading = 80;
				actual = target->Validate();
				Assert::AreEqual(false, actual);

				// DP invalid
				target->MP->Reading = 80;
				target->DP->Reading = 0;
				actual = target->Validate();
				Assert::AreEqual(false, actual);

				// normal MP & DP
				target->MP->Reading = 100;
				target->DP->Reading = 80;
				actual = target->Validate();
				Assert::AreEqual(true, actual);

				// MP & DP too close
				target->MP->Reading = 100;
				target->DP->Reading = 99;
				actual = target->Validate();
				Assert::AreEqual(false, actual);

				// MP is less than DP
				target->MP->Reading = 99;
				target->DP->Reading = 100;
				actual = target->Validate();
				Assert::AreEqual(false, actual);
			}
	};
}
namespace TestBiz {
    
}
