
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::BusinessLogic;
using namespace AtCor::Scor::DataAccess;
namespace TestBiz {
    using namespace System;
    ref class BizElectronicModuleTest;
    
    
    /// <summary>
///This is a test class for BizElectronicModuleTest and is intended
///to contain all BizElectronicModuleTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizElectronicModuleTest
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
			unsigned short actualState;
			String^ actualSource;

			void Update(Object^ sender, DalModuleErrorAlarmEventArgs^ e)
			{
				actualState = e->state;
				actualSource = e->source;
			}
#pragma endregion
			/// <summary>
			///A test for ChangeState
			///</summary>
	public: [TestMethod]
			void BizElectronicModuleChangeStateTest()
			{
				BizElectronicModule^  target = (gcnew BizElectronicModule()); // TODO: Initialize to an appropriate value
				BizElectronicModuleState^  expected = BizElectronicModuleAbnormal::Instance(); // TODO: Initialize to an appropriate value
				target->ChangeState(expected);
				Assert::AreEqual(expected, target->currentState);
			}
			/// <summary>
			///A test for Update
			///</summary>
#if 0 // Seeing Exception: InvalidOperationException - The type LogWriter cannot be constructed. You must configure the container to supply this value.
	public: [TestMethod]
			void BizElectronicModuleUpdateTest()
			{
				BizElectronicModule^  target = (gcnew BizElectronicModule()); // TODO: Initialize to an appropriate value
				PrivateObject^ accessor = gcnew PrivateObject(target);
				unsigned short^ actual = gcnew unsigned short; // = gcnew unsigned short; // TODO: Initialize to an appropriate value
				DalModuleErrorAlarmEventArgs^  e;
				bool rc = false;

				// Update BizElectronicModule with module error / alarm
				e = gcnew DalModuleErrorAlarmEventArgs( 8 /* Why can't use AtCor::Scor::DataAccess::AlarmState */, 1); // TODO: Initialize to an appropriate value
				accessor->Invoke("Update", this, e);
				// Verify BizElectronicModule abnormal state
				Assert::AreEqual(AtCor::Scor::DataAccess::DalConstants::RecoverableState, actualState);
				Assert::AreEqual("Over Pressure Alarm", actualSource);
			}
#endif
	};
}
namespace TestBiz {
    
}
