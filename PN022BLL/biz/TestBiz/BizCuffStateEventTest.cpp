
#include "StdAfx.h"
#include <biz.h>
using namespace BIZ_NAMESPACE;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace TestBiz {
    using namespace System;
    ref class BizCuffStateEventTest;
    
    
    /// <summary>
///This is a test class for BizCuffStateEventTest and is intended
///to contain all BizCuffStateEventTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizCuffStateEventTest
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
			String^ actualUpdate; //actual data received via BizTonometerDataEvent

			void Update(Object^ sender, BizCuffStateEventArgs^ e)
			{
				actualUpdate = e->data;
			}
#pragma endregion
			/// <summary>
			///A test for Notify
			///</summary>
	public: [TestMethod]
			void BizCuffStateEventNotifyTest()
			{
				BizCuffStateEvent^  target = (gcnew BizCuffStateEvent()); // TODO: Initialize to an appropriate value
				target->CuffStateEvent += gcnew BizCuffStateEvent::BizCuffStateEventHandler( this, &BizCuffStateEventTest::Update );
				/* FxCop suggested to use Event<T> but unit test frame work doesn't like it
				target->CuffStateEvent += gcnew EventHandler<BizCuffStateEventArgs^(&BizCuffStateEventTest::Update);
				*/
				String^ data = "Resting"; // TODO: Initialize to an appropriate value
				target->Notify(data);
				Assert::AreEqual(data, actualUpdate);
				// remove the handler
				target->CuffStateEvent -= gcnew BizCuffStateEvent::BizCuffStateEventHandler( this, &BizCuffStateEventTest::Update );
			}
	};
}
namespace TestBiz {
    
}
