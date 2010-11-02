
#include "StdAfx.h"
using namespace System::Drawing;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::BusinessLogic;
namespace TestBiz {
    using namespace System;
    ref class BizCarotidQualityEventTest;
    
    
    /// <summary>
///This is a test class for BizCarotidQualityEventTest and is intended
///to contain all BizCarotidQualityEventTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizCarotidQualityEventTest
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
			//actual data received via BizCarotidQualityEvent
			unsigned short signalMinimumActual;
			unsigned short signalMaximumActual;
			Color signalStrengthColorActual;
			bool enableOkayButtonActual;
				
			void Update(Object^ sender, BizCarotidQualityEventArgs^ e)
			{
				signalMinimumActual = e->signalMinimum;
				signalMaximumActual = e->signalMaximum;
				signalStrengthColorActual = e->signalStrengthColor;
				enableOkayButtonActual = e->enableOkayButton;
			}
#pragma endregion
			/// <summary>
			///A test for Notify
			///</summary>
	public: [TestMethod]
			void BizCarotidQualityEventNotifyTest()
			{
				BizCarotidQualityEvent^  target = (gcnew BizCarotidQualityEvent());
				target->CarotidQualityEvent += gcnew BizCarotidQualityEvent::BizCarotidQualityEventHandler( this, &BizCarotidQualityEventTest::Update );
				/* FxCop suggested to use Event<T> but unit test frame work doesn't like it
				target->TonometerDataEvent += gcnew EventHandler<BizTonometerDataEventArgs^(&BizTonometerDataEventTest::Update);
				*/
				unsigned short signalMinimum = 2000;
				unsigned short signalMaximum = 2500;
				Color signalStrengthColor = Color(Color::Green);
				bool enableOkayButton = true;
				target->Notify(signalMinimum, signalMaximum, signalStrengthColor, enableOkayButton);
				Assert::AreEqual(signalMinimum, signalMinimumActual);
				Assert::AreEqual(signalMaximum, signalMaximumActual);
				Assert::AreEqual(signalStrengthColor, signalStrengthColorActual);
				Assert::AreEqual(enableOkayButton, enableOkayButtonActual);
				// remove the handler
				target->CarotidQualityEvent -= gcnew BizCarotidQualityEvent::BizCarotidQualityEventHandler( this, &BizCarotidQualityEventTest::Update );
			}
	};
}
namespace TestBiz {
    
}
