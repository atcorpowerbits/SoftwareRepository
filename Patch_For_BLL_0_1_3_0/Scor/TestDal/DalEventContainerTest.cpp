
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalEventContainerTest;
    
    
    /// <summary>
///This is a test class for DalEventContainerTest and is intended
///to contain all DalEventContainerTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalEventContainerTest
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

	public: static bool cuffStatusEventRaised = false;
			static bool errorAlarmEventRaised = false;	
			static bool tonoStatusEvenRaised = false;

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

			static void MyDalCuffStatusEventHandler(Object ^sender, DalCuffStatusEventArgs ^args)
			{
				cuffStatusEventRaised = true;
			}

			static void MyDalErrorAlarmEventHandler(Object ^sender, DalModuleErrorAlarmEventArgs ^args)
			{
				errorAlarmEventRaised = true;	
			}

			static void MyDalTonometerStatusEventHandler(Object ^sender, DalTonometerStatusEventArgs  ^args)
			{
				tonoStatusEvenRaised = true;
			}

#pragma endregion
			/// <summary>
			///A test for Instance
			///</summary>
	public: [TestMethod]
			void InstanceTest()
			{
				DalEventContainer^  actual;
				actual = DalEventContainer::Instance;
				Assert::IsNotNull(actual);
			}


			public: [TestMethod]
			void RegisterEventsTestTest()
			{
				DalEventContainer^  actual = DalEventContainer::Instance;
				DalCuffStateFlags cuffStateFlag;
				cuffStateFlag = DalCuffStateFlags::CUFF_STATE_INFLATING;

				DalErrorAlarmStatusFlag errFlag;
				errFlag = DalErrorAlarmStatusFlag::ActiveStatus;

				Assert::AreEqual(false, cuffStatusEventRaised );
				Assert::AreEqual(false, errorAlarmEventRaised );
				Assert::AreEqual(false, tonoStatusEvenRaised );

				actual->OnDalCuffStatusEvent += gcnew DalCuffStatusEventHandler(&TestDal::DalEventContainerTest::MyDalCuffStatusEventHandler);
				actual->OnDalModuleErrorAlarmEvent += gcnew DalModuleErrorAlarmEventHandler(&TestDal::DalEventContainerTest::MyDalErrorAlarmEventHandler);
				actual->OnDalTonometerStatusEvent += gcnew DalTonometerStatusEventHandler(&TestDal::DalEventContainerTest::MyDalTonometerStatusEventHandler);

				actual->OnDalCuffStatusEvent(this, gcnew DalCuffStatusEventArgs(cuffStateFlag));
				actual->OnDalModuleErrorAlarmEvent(this, gcnew DalModuleErrorAlarmEventArgs( errFlag, nullptr)); //TODO: Deepak Put an appropriate string
				actual->OnDalTonometerStatusEvent(this, gcnew DalTonometerStatusEventArgs(DalTonometerState::Connected ));

				Assert::AreEqual(true, cuffStatusEventRaised );
				Assert::AreEqual(true, errorAlarmEventRaised );
				Assert::AreEqual(true, tonoStatusEvenRaised );

				actual->OnDalCuffStatusEvent -= gcnew DalCuffStatusEventHandler(&TestDal::DalEventContainerTest::MyDalCuffStatusEventHandler);
				actual->OnDalModuleErrorAlarmEvent -= gcnew DalModuleErrorAlarmEventHandler(&TestDal::DalEventContainerTest::MyDalErrorAlarmEventHandler);
				
				 
			}
			
			/// <summary>
			///A test for op_Assign
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void op_AssignTest()
			{
				DalEventContainer_Accessor^  target = (gcnew DalEventContainer_Accessor()); 
				DalEventContainer_Accessor^ unnamed; 
				DalEventContainer_Accessor^  actual;
				actual = (unnamed = target);
				Assert::AreEqual(target, actual);
			}
			/// <summary>
			///A test for DalEventContainer Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalEventContainerConstructorTest1()
			{
				DalEventContainer^  unnamed = DalEventContainer::Instance ; 
				Assert::IsNotNull(unnamed);
				DalEventContainer_Accessor^  target = (gcnew DalEventContainer_Accessor(unnamed));
				Assert::IsNotNull(target);
			}
			/// <summary>
			///A test for DalEventContainer Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalEventContainerConstructorTest()
			{
				DalEventContainer_Accessor^  target = (gcnew DalEventContainer_Accessor());
				Assert::IsNotNull(target);
			}


			/*public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void EventsRaisedTest()
			{
				bool eventWasRaised = false;
				DalEventContainer_Accessor^ eventRaiser = gcnew DalAlarmSource_Accessor();
				eventRaiser->add_OnDalCuffPulseEvent+= gcnew DalCuffPulseEventHandler_Accessor(Object ^ sender, DalCuffStatusEventArgs^ e){
					eventWasRaised = true;
				};

				eventRaiser->raise_OnDalCuffStatusEvent(nullptr, nullptr);

				Assert::IsTrue(eventWasRaised );

			}*/
	};
}
namespace TestDal {
    
}
