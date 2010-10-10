
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace Biz;
namespace TestBiz {
    using namespace System;
    ref class BizTonometerDataEventTest;
    
    
    /// <summary>
///This is a test class for BizTonometerDataEventTest and is intended
///to contain all BizTonometerDataEventTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizTonometerDataEventTest
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
	public:
			unsigned int actualUpdate; //actual data received via BizTonometerDataEvent

			void Update(Object^ sender, BizTonometerDataEventArgs^ e)
			{
				actualUpdate = e->data;
			}
#pragma endregion
			/// <summary>
			///A test for Notify
			///</summary>
	public: [TestMethod]
			void BizTonometerDataEventNotifyTest()
			{
				BizTonometerDataEvent^  target = (gcnew BizTonometerDataEvent()); // TODO: Initialize to an appropriate value
				target->TonometerDataEvent += gcnew BizTonometerDataEvent::BizTonometerDataEventHandler( this, &BizTonometerDataEventTest::Update );
				/* FxCop suggested to use Event<T> but unit test frame work doesn't like it
				target->TonometerDataEvent += gcnew EventHandler<BizTonometerDataEventArgs^(&BizTonometerDataEventTest::Update);
				*/
				unsigned int data = 12345; // TODO: Initialize to an appropriate value
				target->Notify(data);
				Assert::AreEqual(data, actualUpdate);
				// remove the handler
				target->TonometerDataEvent -= gcnew BizTonometerDataEvent::BizTonometerDataEventHandler( this, &BizTonometerDataEventTest::Update );
			}
	};
}
namespace TestBiz {
    
}
