
#include "StdAfx.h"
#include <biz.h>
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace BIZ_NAMESPACE;
namespace TestBiz {
    using namespace System;
    ref class BizSPAndMPTest;
    
    
    /// <summary>
///This is a test class for BizSPAndMPTest and is intended
///to contain all BizSPAndMPTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizSPAndMPTest
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
			void BizSPAndMPValidateTest()
			{
				BizSPAndMP^  target = (gcnew BizSPAndMP()); // TODO: Initialize to an appropriate value
				bool actual;

				// SP invalid
				target->SP->Reading = 0;
				target->MP->Reading = 70;
				actual = target->Validate();
				Assert::AreEqual(false, actual);

				// MP invalid
				target->SP->Reading = 120;
				target->MP->Reading = 0;
				actual = target->Validate();
				Assert::AreEqual(false, actual);

				// normal SP & MP
				target->SP->Reading = 120;
				target->MP->Reading = 70;
				actual = target->Validate();
				Assert::AreEqual(true, actual);

				// SP & MP too close
				target->SP->Reading = 100;
				target->MP->Reading = 99;
				actual = target->Validate();
				Assert::AreEqual(false, actual);

				// SP is less than MP
				target->SP->Reading = 99;
				target->MP->Reading = 100;
				actual = target->Validate();
				Assert::AreEqual(false, actual);
			}
	};
}
namespace TestBiz {
    
}
