
#include "StdAfx.h"
#include "dal_stub.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::BusinessLogic;
using namespace AtCor::Scor::DataAccess;
namespace TestBiz {
    using namespace System;
    ref class BizElectronicModuleErrorTest;
    
    
    /// <summary>
///This is a test class for BizElectronicModuleErrorTest and is intended
///to contain all BizElectronicModuleErrorTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizElectronicModuleErrorTest
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
			//actual data received via an event
			static String^ actualSource;

			static void Update(Object^ sender, BizErrorEventArgs^ e)
			{
				actualSource = e->data;
			}
#pragma endregion
			/// <summary>
			///A test for ReceiveNewStatus
			///</summary>
	public: [TestMethod]
			void BizElectronicModuleErrorReceiveNewStatusTest()
			{
				BizElectronicModuleError^  target = BizElectronicModuleError::Instance(); // TODO: Initialize to an appropriate value
				BizElectronicModule^  client = gcnew BizElectronicModule; // TODO: Initialize to an appropriate value
				BizElectronicModuleState^ destinationState = BizElectronicModuleNormal::Instance();
				DalErrorAlarmStatusFlag newStatus = DalErrorAlarmStatusFlag::ActiveStatus; // TODO: Initialize to an appropriate value
				client->ChangeState(target);
				target->ReceiveNewStatus(client, newStatus);
				Assert::AreEqual(destinationState, client->currentState);

				destinationState = BizElectronicModuleWarning::Instance();
				newStatus = DalErrorAlarmStatusFlag::RecoverableStatus; // TODO: Initialize to an appropriate value
				client->ChangeState(target);
				target->ReceiveNewStatus(client, newStatus);
				Assert::AreEqual(destinationState, client->currentState);

				destinationState = BizElectronicModuleError::Instance();
				newStatus = DalErrorAlarmStatusFlag::UnrecoverableStatus; // TODO: Initialize to an appropriate value
				client->ChangeState(target);
				target->ReceiveNewStatus(client, newStatus);
				Assert::AreEqual(destinationState, client->currentState);
			}
			/// <summary>
			///A test for Instance
			///</summary>
	public: [TestMethod]
			void BizElectronicModuleErrorInstanceTest()
			{
				BizElectronicModuleError^  expected = nullptr; // TODO: Initialize to an appropriate value
				BizElectronicModuleError^  actual;
				actual = BizElectronicModuleError::Instance();
				Assert::AreNotEqual(expected, actual);
				expected = actual;
				actual = BizElectronicModuleError::Instance();
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for Dispatch
			///</summary>
	public: [TestMethod]
			void BizElectronicModuleErrorDispatchTest()
			{
				BizElectronicModule^  target = (gcnew BizElectronicModule()); // TODO: Initialize to an appropriate value
				target->currentState = BizElectronicModuleError::Instance();
				DalFacade::Instance()->status = ErrorStatus; // simulate error status;
				DalFacade::Instance()->source = DualSensors; // simulate error source;
				BizEventContainer::Instance->OnBizErrorEvent += gcnew BizErrorEventHandler(&BizElectronicModuleErrorTest::Update);
				target->Dispatch(); //TBD: Waiting for advice from TM on CrxLogger exception durijg logging to be resolved.
				Assert::AreEqual("DualSensors", actualSource); // TBD: get the string from crx string resource
			}
	};
}
namespace TestBiz {
    
}
