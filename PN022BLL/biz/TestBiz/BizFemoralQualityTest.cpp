
#include "StdAfx.h"
#include <biz.h>
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::BusinessLogic;
namespace TestBiz {
    using namespace System;
    ref class BizFemoralQualityTest;
    
    
    /// <summary>
///This is a test class for BizFemoralQualityTest and is intended
///to contain all BizFemoralQualityTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizFemoralQualityTest
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
			//actual data received via BizFemoralQualityEvent
			unsigned short signalMinimumActual;
			unsigned short signalMaximumActual;
			bool signalStrengthIsGoodActual;
			bool enableOkayButtonActual;
				
			void Update(Object^ sender, BizFemoralQualityEventArgs^ e)
			{
				signalMinimumActual = e->signalMinimum;
				signalMaximumActual = e->signalMaximum;
				signalStrengthIsGoodActual = e->signalStrengthIsGood;
				enableOkayButtonActual = e->enableOkayButton;
			}
#pragma endregion
			/// <summary>
			///A test for Reset
			///</summary>
	public: [TestMethod]
			void BizFemoralQualityResetTest()
			{
				BizBuffer^  buffer = gcnew BizCircularBuffer(10);
				unsigned short sampleRate = DEFAULT_SAMPLE_RATE;
				BizFemoralQuality^  target = (gcnew BizFemoralQuality(buffer, sampleRate));
				PrivateObject^ accessor = gcnew PrivateObject(target);
				target->Reset();
				Assert::AreEqual((unsigned short) 0, (unsigned short) accessor->GetProperty("counter"));
			}
			/// <summary>
			///A test for BizFemoralQuality Constructor
			///</summary>
	public: [TestMethod]
			void BizFemoralQualityConstructorTest()
			{
				BizBuffer^  buffer = gcnew BizCircularBuffer(10);
				unsigned short sampleRate = DEFAULT_SAMPLE_RATE;
				BizFemoralQuality^  target = (gcnew BizFemoralQuality(buffer, sampleRate));
				PrivateObject^ accessor = gcnew PrivateObject(target);
				Assert::AreEqual(buffer, accessor->GetProperty("buffer"));
				Assert::AreEqual(sampleRate, accessor->GetProperty("sampleRate"));
			}
			/// <summary>
			///A test for Update
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizFemoralQualityUpdate.csv", L"BizFemoralQualityUpdate#csv", DataAccessMethod::Sequential),
				TestMethod]
			void BizFemoralQualityUpdateTest()
			{
				unsigned int bufferSize = Convert::ToInt32(testContextInstance->DataRow[L"BufferSize"]);
				BizBuffer^  buffer = gcnew BizCircularBuffer(bufferSize);
				unsigned short sampleRate = 1;
				BizFemoralQuality^  target = (gcnew BizFemoralQuality(buffer, sampleRate));
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
				bool signalStrengthisGoodExpected = Convert::ToBoolean(testContextInstance->DataRow[L"signalStrengthIsGoodExpected"]);
				bool enableOkayButtonExpected = Convert::ToBoolean(testContextInstance->DataRow[L"EnableOkayButtonExpected"]);
				BizEventContainer::Instance->OnBizFemoralQualityEvent += gcnew BizFemoralQualityEventHandler(this, &BizFemoralQualityTest::Update);
				unsigned short data = 0;
				BizCuffPulseEventArgs^  e = gcnew BizCuffPulseEventArgs( data );
				accessor->Invoke("Update", this, e);
				Assert::AreEqual(signalMinimumExpected, signalMinimumActual);
				Assert::AreEqual(signalMaximumExpected, signalMaximumActual);
				Assert::AreEqual(signalStrengthisGoodExpected, signalStrengthIsGoodActual);
				Assert::AreEqual(enableOkayButtonExpected, enableOkayButtonActual);
				// remove the handler
				BizEventContainer::Instance->OnBizFemoralQualityEvent -= gcnew BizFemoralQualityEventHandler(this, &BizFemoralQualityTest::Update);
			}
	};
}
namespace TestBiz {
    
}
