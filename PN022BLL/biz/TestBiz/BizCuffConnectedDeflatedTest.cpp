
#include "StdAfx.h"
#include <biz.h>
using namespace BIZ_NAMESPACE;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace TestBiz {
    using namespace System;
    ref class BizCuffConnectedDeflatedTest;
    
    
    /// <summary>
///This is a test class for BizCuffConnectedDeflatedTest and is intended
///to contain all BizCuffConnectedDeflatedTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizCuffConnectedDeflatedTest
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
				BizCuffDeflated^  expected = nullptr; // TODO: Initialize to an appropriate value
				BizCuffDeflated^  actual;
				actual = BizCuffDeflated::Instance();
				Assert::AreNotEqual(expected, actual);
				expected = actual;
				actual = BizCuffDeflated::Instance();
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for InflateNow
			///</summary>
	public: [TestMethod]
			void InflateNowTest()
			{
				BizCuffDeflated^  target = BizCuffDeflated::Instance(); // TODO: Initialize to an appropriate value
				BizCuff^  client = gcnew BizCuff; // TODO: Initialize to an appropriate value
				BizCuffState^ destinationState = BizCuffInflating::Instance();
				client->ChangeState(target);
				target->InflateNow(client);
				Assert::AreEqual(destinationState->internalName, client->currentState->internalName);
			}
			/// <summary>
			///A test for Disconnect
			///</summary>
	public: [TestMethod]
			void DisconnectTest()
			{
				BizCuffDeflated^  target = BizCuffDeflated::Instance(); // TODO: Initialize to an appropriate value
				BizCuff^  client = gcnew BizCuff; // TODO: Initialize to an appropriate value
				BizCuffState^ destinationState = BizCuffDisconnected::Instance();
				client->ChangeState(target);
				target->Disconnect(client);
				Assert::AreEqual(destinationState->internalName, client->currentState->internalName);
			}
	};
}
namespace TestBiz {
    
}
