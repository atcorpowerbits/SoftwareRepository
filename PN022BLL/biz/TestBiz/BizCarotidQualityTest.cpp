
#include "StdAfx.h"
#include <biz.h>
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::BusinessLogic;
using namespace System::Drawing;
namespace TestBiz {
    using namespace System;
    ref class BizCarotidQualityTest;
    
    
    /// <summary>
///This is a test class for BizCarotidQualityTest and is intended
///to contain all BizCarotidQualityTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizCarotidQualityTest
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
			///A test for BizCarotidQuality Constructor
			///</summary>
	public: [TestMethod]
			void BizCarotidQualityConstructorTest()
			{
				BizBuffer^  buffer = gcnew BizCircularBuffer(10);
				//BizTonometerDataEvent^  carotidData = gcnew BizTonometerDataEvent();
				unsigned short sampleRate = DEFAULT_SAMPLE_RATE;
				BizCarotidQuality^  target = (gcnew BizCarotidQuality(buffer, sampleRate));
				PrivateObject^ accessor = gcnew PrivateObject(target);
				Assert::AreEqual(buffer, accessor->GetProperty("buffer"));
				//Assert::AreEqual(carotidData, accessor->GetProperty("carotidData"));
				Assert::AreEqual(sampleRate, accessor->GetProperty("sampleRate"));
				//Assert::IsNotNull(target->carotidQualityBiz);
			}
			/// <summary>
			///A test for Reset
			///</summary>
	public: [TestMethod]
			void BizCarotidQualityResetTest()
			{
				BizBuffer^  buffer = gcnew BizCircularBuffer(10);
				//BizTonometerDataEvent^  carotidData = gcnew BizTonometerDataEvent();
				unsigned short sampleRate = DEFAULT_SAMPLE_RATE;
				BizCarotidQuality^  target = (gcnew BizCarotidQuality(buffer, sampleRate));
				PrivateObject^ accessor = gcnew PrivateObject(target);
				target->Reset();
				Assert::AreEqual((unsigned short) 0, (unsigned short) accessor->GetProperty("counter"));
			}
			/// <summary>
			///A test for Update
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizCarotidQualityUpdate.csv", L"BizCarotidQualityUpdate#csv", DataAccessMethod::Sequential),
				TestMethod]
			void BizCarotidQualityUpdateTest()
			{
				unsigned int bufferSize = Convert::ToInt32(testContextInstance->DataRow[L"BufferSize"]);
				BizBuffer^  buffer = gcnew BizCircularBuffer(bufferSize);
				//BizTonometerDataEvent^  carotidData = gcnew BizTonometerDataEvent();
				unsigned short sampleRate = 1;
				BizCarotidQuality^  target = (gcnew BizCarotidQuality(buffer, sampleRate));
				PrivateObject^ accessor = gcnew PrivateObject(target);
				PrivateObject^ bufferAccessor = gcnew PrivateObject(buffer);
				unsigned short startIndex = Convert::ToUInt16(testContextInstance->DataRow[L"StartIndex"]);
				unsigned short endIndex = Convert::ToUInt16(testContextInstance->DataRow[L"EndIndex"]);;
				String^ values = Convert::ToString(testContextInstance->DataRow[L"Buffer"]);
				array<String^>^ valuesArray = values->Split(',');
				cli::array< unsigned short >^ signal = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
				bufferAccessor->SetField("_buffer", signal);
				bufferAccessor->SetField("_startIndex", startIndex);
				bufferAccessor->SetField("_endIndex", endIndex);
				unsigned short signalMinimumExpected = Convert::ToUInt16(testContextInstance->DataRow[L"SignalMinimumExpected"]);
				unsigned short signalMaximumExpected = Convert::ToUInt16(testContextInstance->DataRow[L"SignalMaximumExpected"]);
				String^ signalStrengthColor = Convert::ToString(testContextInstance->DataRow[L"signalStrengthColorExpected"]);
				bool enableOkayButtonExpected = Convert::ToBoolean(testContextInstance->DataRow[L"EnableOkayButtonExpected"]);
				Color signalStrengthColorExpected = Color( Color::FromName( signalStrengthColor ) );
				//target->carotidQualityBiz->CarotidQualityEvent += gcnew BizCarotidQualityEvent::BizCarotidQualityEventHandler( this, &BizCarotidQualityTest::Update );
				BizEventContainer::Instance->OnBizCarotidQualityEvent += gcnew BizCarotidQualityEventHandler(this, &BizCarotidQualityTest::Update);
				unsigned short data = 0;
				BizTonometerDataEventArgs^  e = gcnew BizTonometerDataEventArgs( data );
				accessor->Invoke("Update", this, e);
				Assert::AreEqual(signalMinimumExpected, signalMinimumActual);
				Assert::AreEqual(signalMaximumExpected, signalMaximumActual);
				Assert::AreEqual(signalStrengthColorExpected, signalStrengthColorActual);
				Assert::AreEqual(enableOkayButtonExpected, enableOkayButtonActual);
				// remove the handler
				//target->carotidQualityBiz->CarotidQualityEvent -= gcnew BizCarotidQualityEvent::BizCarotidQualityEventHandler( this, &BizCarotidQualityTest::Update );
				BizEventContainer::Instance->OnBizCarotidQualityEvent -= gcnew BizCarotidQualityEventHandler(this, &BizCarotidQualityTest::Update);
			}
	};
}
namespace TestBiz {
    
}
