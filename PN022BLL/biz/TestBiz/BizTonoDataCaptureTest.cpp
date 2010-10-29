
#include "StdAfx.h"
#include <biz.h>
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace BIZ_NAMESPACE;
using namespace DAL_NAMESPACE;

namespace TestBiz {
    using namespace System;
    ref class BizTonometerDataCaptureTest;
    
    
    /// <summary>
///This is a test class for BizTonometerDataCaptureTest and is intended
///to contain all BizTonometerDataCaptureTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizTonometerDataCaptureTest
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
			unsigned int actualUpdate; //actual data received via an event

			void Update(Object^ sender, BizTonometerDataEventArgs^ e)
			{
				actualUpdate = e->data;
			}
#pragma endregion
			/// <summary>
			///A test for Dispatch
			///</summary>
	public: [TestMethod]
			void BizTonometerDataCaptureDispatchTest()
			{
				BizCircularBuffer^  buffer = (gcnew BizCircularBuffer(2)); 
				BizTonometerDataCapture^  target = (gcnew BizTonometerDataCapture(buffer)); 
				PrivateObject^ accessor = gcnew PrivateObject(target);
				unsigned int data; 
				unsigned int lastData = 10; 

				for (data = 0; data <= lastData; data++)
				{
					DalTonometerDataEventArgs^ tonoArgs = gcnew DalTonometerDataEventArgs( data );
					// Update BizTonometerDataCapture with data so it's saved in circular buffer
					accessor->Invoke("Update", this, tonoArgs);
				}

				// Setup a delegate (observer) to whom data is updated by BizTonometerDataCapture during dispatch
//				target->tonometerDataBiz->TonometerDataEvent += gcnew BizTonometerDataEvent::BizTonometerDataEventHandler( this, &BizTonometerDataCaptureTest::Update );
				BizEventContainer::Instance->OnBizTonometerDataEvent += gcnew BizTonometerDataEventHandler(this, &BizTonometerDataCaptureTest::Update);

				// Update the observer with data read from circular buffer
				target->Dispatch();
				Assert::AreEqual(lastData, actualUpdate);
			}
			/// <summary>
			///A test for Update
			///</summary>
	public: [TestMethod]
			void BizTonometerDataCaptureUpdateTest()
			{
				BizCircularBuffer^  buffer = (gcnew BizCircularBuffer(2)); // TODO: Initialize to an appropriate value
				BizTonometerDataCapture^  target = (gcnew BizTonometerDataCapture(buffer)); // TODO: Initialize to an appropriate value
				PrivateObject^ accessor = gcnew PrivateObject(target);
				unsigned short data = 12345; // TODO: Initialize to an appropriate value
				unsigned short actual; // = gcnew unsigned short; // TODO: Initialize to an appropriate value
				DalTonometerDataEventArgs^  e = gcnew DalTonometerDataEventArgs( data ); // TODO: Initialize to an appropriate value
				bool rc = false;

				// Update BizTonometerDataCapture with data so it's saved in circular buffer
				accessor->Invoke("Update", this, e);

				// Verify the data in the circular buffer
				rc = buffer->ReadNext(actual);
				Assert::AreEqual(true, rc);
				Assert::AreEqual(data, actual);
			}
	};
}
namespace TestBiz {
    
}
