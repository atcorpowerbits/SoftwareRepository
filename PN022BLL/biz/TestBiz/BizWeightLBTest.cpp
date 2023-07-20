
#include "StdAfx.h"
#include <biz.h>
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace BIZ_NAMESPACE;
namespace TestBiz {
    using namespace System;
    ref class BizWeightLBTest;
    
    
    /// <summary>
///This is a test class for BizWeightLBTest and is intended
///to contain all BizWeightLBTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizWeightLBTest
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
			void BizWeightLBValidateTest()
			{
				BizWeightLB^  target = (gcnew BizWeightLB()); // TODO: Initialize to an appropriate value
				bool actual;

				target->Weight = MEA_WEIGHT_LB_MIN - 1;
				actual = target->Validate();
				Assert::AreEqual(false, actual);

				target->Weight = MEA_WEIGHT_LB_MAX + 1;
				actual = target->Validate();
				Assert::AreEqual(false, actual);

				target->Weight = 80;
				actual = target->Validate();
				Assert::AreEqual(true, actual);
			}
	};
}
namespace TestBiz {
    
}
