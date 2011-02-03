
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalModuleErrorAlarmEventArgs_ORITest;
    
    
    /// <summary>
///This is a test class for DalModuleErrorAlarmEventArgs_ORITest and is intended
///to contain all DalModuleErrorAlarmEventArgs_ORITest Unit Tests
///</summary>
	[TestClass]
	public ref class DalModuleErrorAlarmEventArgs_ORITest
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
			///A test for ErrorAlarmStatus
			///</summary>
	public: [TestMethod]
			void ErrorAlarmStatusTest()
			{
				DalErrorAlarmStatusFlag data = DalErrorAlarmStatusFlag(); // TODO: Initialize to an appropriate value
				DalModuleErrorAlarmEventArgs_ORI^  target = (gcnew DalModuleErrorAlarmEventArgs_ORI(data)); // TODO: Initialize to an appropriate value
				DalErrorAlarmStatusFlag expected = DalErrorAlarmStatusFlag(); // TODO: Initialize to an appropriate value
				DalErrorAlarmStatusFlag actual;
				target->ErrorAlarmStatus = expected;
				actual = target->ErrorAlarmStatus;
				Assert::AreEqual(expected, actual);
			//	Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for DalModuleErrorAlarmEventArgs_ORI Constructor
			///</summary>
	public: [TestMethod]
			void DalModuleErrorAlarmEventArgs_ORIConstructorTest()
			{
				DalErrorAlarmStatusFlag data = DalErrorAlarmStatusFlag::ActiveStatus ; // TODO: Initialize to an appropriate value
				DalModuleErrorAlarmEventArgs_ORI^  target = (gcnew DalModuleErrorAlarmEventArgs_ORI(data));
				Assert::AreEqual(target->ErrorAlarmStatus, data);
			}
	};
}
namespace TestDal {
    
}
