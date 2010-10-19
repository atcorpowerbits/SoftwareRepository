﻿
#include "StdAfx.h"
#include <biz.h>
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace Biz;
namespace TestBiz {
    using namespace System;
    ref class BizHeightCMTest;
    
    
    /// <summary>
///This is a test class for BizHeightCMTest and is intended
///to contain all BizHeightCMTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizHeightCMTest
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
			void BizHeightCMValidateTest()
			{
				BizHeightCM^  target = (gcnew BizHeightCM()); // TODO: Initialize to an appropriate value
				bool actual;

				target->Height = MEA_HEIGHT_CM_MIN - 1;
				actual = target->Validate();
				Assert::AreEqual(false, actual);

				target->Height = MEA_HEIGHT_CM_MAX + 1;
				actual = target->Validate();
				Assert::AreEqual(false, actual);

				target->Height = 180;
				actual = target->Validate();
				Assert::AreEqual(true, actual);
			}
	};
}
namespace TestBiz {
    
}