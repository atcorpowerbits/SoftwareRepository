
#include "StdAfx.h"
#include <biz.h>
using namespace BIZ_NAMESPACE;
using namespace DAL_NAMESPACE;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace TestBiz {
    using namespace System;
    ref class BizCuffTest;
    
    
    /// <summary>
///This is a test class for BizCuffTest and is intended
///to contain all BizCuffTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizCuffTest
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
			static String^ actualUpdate; //actual data received via an event

			static void Update(Object^ sender, BizCuffStateEventArgs^ e)
			{
				actualUpdate = e->data;
			}
#pragma endregion
			/// <summary>
			///A test for Dispatch
			///</summary>
	public: [TestMethod]
			void BizCuffDispatchTest()
			{
				BizCuff^  target = (gcnew BizCuff()); // TODO: Initialize to an appropriate value
				PrivateObject^ accessor = gcnew PrivateObject(target);
				DalCuffStatusEventArgs^  e;
				bool rc = false;

				// Update BizCuff with cuff status
				e = gcnew DalCuffStatusEventArgs( 0x0400 ); // TODO: Initialize to an appropriate value
				accessor->Invoke("Update", this, e);
	
				// Setup a delegate (observer) to whom data is updated by BizCuff during dispatch
				BizEventContainer::Instance->OnBizCuffStateEvent += gcnew BizCuffStateEventHandler(&BizCuffTest::Update);

				// Update the observer with data read from circular buffer
				target->Dispatch();
				Assert::AreEqual("Inflating", actualUpdate);
			}
			/// <summary>
			///A test for ChangeState
			///</summary>
	public: [TestMethod]
			void BizCuffChangeStateTest()
			{
				BizCuff^  target = (gcnew BizCuff()); // TODO: Initialize to an appropriate value
				BizCuffState^  state = BizCuffInflated::Instance(); // TODO: Initialize to an appropriate value
				target->ChangeState(state);
				Assert::AreEqual(state->internalName, target->currentState->internalName);
			}
			/// <summary>
			///A test for Update
			///</summary>
	public: [TestMethod]
			void BizCuffUpdateTest()
			{
				BizCuff^  target = (gcnew BizCuff()); // TODO: Initialize to an appropriate value
				PrivateObject^ accessor = gcnew PrivateObject(target);
				unsigned short^ actual = gcnew unsigned short; // = gcnew unsigned short; // TODO: Initialize to an appropriate value
				DalCuffStatusEventArgs^  e;
				bool rc = false;

				// Update BizCuff with cuff status
				e = gcnew DalCuffStatusEventArgs( 0x2000 ); // TODO: Initialize to an appropriate value
				accessor->Invoke("Update", this, e);
				// Verify BizCuff cuff state
				Assert::AreEqual("Disconnected", target->currentState->internalName);
				// Update BizCuff with cuff status
				e = gcnew DalCuffStatusEventArgs( 0x0100 ); // TODO: Initialize to an appropriate value
				accessor->Invoke("Update", this, e);
				// Verify BizCuff cuff state
				Assert::AreEqual("Deflated", target->currentState->internalName);
				// Update BizCuff with cuff status
				e = gcnew DalCuffStatusEventArgs( 0x0400 ); // TODO: Initialize to an appropriate value
				accessor->Invoke("Update", this, e);
				// Verify BizCuff cuff state
				Assert::AreEqual("Inflating", target->currentState->internalName);
				// Update BizCuff with cuff status
				e = gcnew DalCuffStatusEventArgs( 0x0900 ); // TODO: Initialize to an appropriate value
				accessor->Invoke("Update", this, e);
				// Verify BizCuff cuff state
				Assert::AreEqual("Inflated", target->currentState->internalName);
				// Update BizCuff with cuff status
				e = gcnew DalCuffStatusEventArgs( 0x0200 ); // TODO: Initialize to an appropriate value
				accessor->Invoke("Update", this, e);
				// Verify BizCuff cuff state
				Assert::AreEqual("Deflating", target->currentState->internalName);
			}
	};
}
namespace TestBiz {
    
}
