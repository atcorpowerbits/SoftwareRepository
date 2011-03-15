
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
				Assert::IsTrue(true);
			}

			static void MyDalErrorAlarmEventHandler(Object ^sender, DalModuleErrorAlarmEventArgs ^args)
			{
				Assert::IsTrue(true);
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
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
				Assert::IsNotNull(actual);
			}


			public: [TestMethod]
			void RegisterEventsTestTest()
			{
				DalEventContainer^  actual;
				actual = DalEventContainer::Instance;
				DalCuffStateFlags cuffStateFlag;
				cuffStateFlag = DalCuffStateFlags::CUFF_STATE_INFLATING;

				DalErrorAlarmStatusFlag errFlag;
				errFlag = DalErrorAlarmStatusFlag::ActiveStatus;

				actual->OnDalCuffStatusEvent += gcnew DalCuffStatusEventHandler(&TestDal::DalEventContainerTest::MyDalCuffStatusEventHandler);
				actual->OnDalModuleErrorAlarmEvent += gcnew DalModuleErrorAlarmEventHandler(&TestDal::DalEventContainerTest::MyDalErrorAlarmEventHandler);

				actual->OnDalCuffStatusEvent(this, gcnew DalCuffStatusEventArgs(cuffStateFlag));
				actual->OnDalModuleErrorAlarmEvent(this, gcnew DalModuleErrorAlarmEventArgs( errFlag));

				actual->OnDalCuffStatusEvent -= gcnew DalCuffStatusEventHandler(&TestDal::DalEventContainerTest::MyDalCuffStatusEventHandler);
				actual->OnDalModuleErrorAlarmEvent -= gcnew DalModuleErrorAlarmEventHandler(&TestDal::DalEventContainerTest::MyDalErrorAlarmEventHandler);

			}
	};
}
namespace TestDal {
    
}
