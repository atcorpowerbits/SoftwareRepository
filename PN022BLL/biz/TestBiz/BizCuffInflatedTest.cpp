
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace Biz;
namespace TestBiz {
    using namespace System;
    ref class BizCuffInflatedTest;
    
    
    /// <summary>
///This is a test class for BizCuffInflatedTest and is intended
///to contain all BizCuffInflatedTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizCuffInflatedTest
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
				BizCuffInflated^  expected = nullptr; // TODO: Initialize to an appropriate value
				BizCuffInflated^  actual;
				actual = BizCuffInflated::Instance();
				Assert::AreNotEqual(expected, actual);
				expected = actual;
				actual = BizCuffInflated::Instance();
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for DeflateNow
			///</summary>
	public: [TestMethod]
			void DeflateNowTest()
			{
				BizCuffInflated^  target = BizCuffInflated::Instance(); // TODO: Initialize to an appropriate value
				BizCuff^  client = gcnew BizCuff; // TODO: Initialize to an appropriate value
				BizCuffState^ destinationState = BizCuffDeflating::Instance();
				client->ChangeState(target);
				target->DeflateNow(client);
				Assert::AreEqual(destinationState->internalName, client->currentState->internalName);
			}
	};
}
namespace TestBiz {
    
}
