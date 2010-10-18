
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace Biz;
namespace TestBiz {
    using namespace System;
    ref class BizCuffDeflatingTest;
    
    
    /// <summary>
///This is a test class for BizCuffDeflatingTest and is intended
///to contain all BizCuffDeflatingTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizCuffDeflatingTest
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
				BizCuffDeflating^  expected = nullptr; // TODO: Initialize to an appropriate value
				BizCuffDeflating^  actual;
				actual = BizCuffDeflating::Instance();
				Assert::AreNotEqual(expected, actual);
				expected = actual;
				actual = BizCuffDeflating::Instance();
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for FinishDeflating
			///</summary>
	public: [TestMethod]
			void FinishDeflatingTest()
			{
				BizCuffDeflating^  target = BizCuffDeflating::Instance(); // TODO: Initialize to an appropriate value
				BizCuff^  client = gcnew BizCuff; // TODO: Initialize to an appropriate value
				BizCuffState^ destinationState = BizCuffResting::Instance();
				client->ChangeState(target);
				target->FinishDeflating(client);
				Assert::AreEqual(destinationState->internalName, client->currentState->internalName);
			}
	};
}
namespace TestBiz {
    
}
