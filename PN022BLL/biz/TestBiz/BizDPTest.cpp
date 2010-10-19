
#include "StdAfx.h"
#include <biz.h>
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace Biz;
namespace TestBiz {
    using namespace System;
    ref class BizDPTest;
    
    
    /// <summary>
///This is a test class for BizDPTest and is intended
///to contain all BizDPTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizDPTest
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
			void BizDPValidateTest()
			{
				BizDP^  target = (gcnew BizDP()); // TODO: Initialize to an appropriate value
				bool actual;

				target->Reading = MEA_BP_MIN - 1; // below min boundary test 
				actual = target->Validate();
				Assert::AreEqual(false, actual);

				target->Reading = MEA_BP_MIN; // min boundary test
				actual = target->Validate();
				Assert::AreEqual(true, actual);

				target->Reading = 80; // normal test
				actual = target->Validate();
				Assert::AreEqual(true, actual);

				target->Reading = MEA_BP_MAX; // max boundary test
				actual = target->Validate();
				Assert::AreEqual(true, actual);

				target->Reading = MEA_BP_MAX + 1; // beyond max boundary test
				actual = target->Validate();
				Assert::AreEqual(false, actual);
			}
	};
}
namespace TestBiz {
    
}
