
#include "StdAfx.h"
#include <biz.h>
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace TestBiz {
    using namespace System;
    using namespace Biz;
	ref class BizSignalTest;
    
    
    /// <summary>
///This is a test class for BizSignalTest and is intended
///to contain all BizSignalTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizSignalTest
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
		///A test for SetDefaults
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"biz.dll")]
		void SetDefaultsTest()
		{
			BizSignal_Accessor^  target = (gcnew BizSignal_Accessor());
			target->maxOnsetsLength = MAX_ONSETS;
			array<float>^ floatOnsetsExpected = gcnew array<float>(MAX_ONSETS);;
			for (int i = 0; i < MAX_ONSETS; i++)
			{
				floatOnsetsExpected[i] = -1;
			}
			target->floatOnsets = gcnew array<float>(MAX_ONSETS);;
			target->SetDefaults();
			Assert::AreEqual(false, target->readyToCapture);
			Assert::AreEqual((float) DEFAULT_VALUE, target->pulseHeight);
			Assert::AreEqual((float) DEFAULT_VALUE, target->pulseHeightVariation);
			Assert::AreEqual((float) DEFAULT_VALUE, target->pulseLengthVariation);
			Assert::AreEqual((float) DEFAULT_VALUE, target->baseLineVariation);
			Assert::AreEqual((short) 0, target->onsetsLength);
			CollectionAssert::AreEqual(floatOnsetsExpected, target->floatOnsets);
		}
		/// <summary>
		///A test for Initialise
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizSignalInitialise.csv", L"BizSignalInitialise#csv", DataAccessMethod::Sequential),
			TestMethod]
		void InitialiseTest()
		{
			BizSignal_Accessor^  target = (gcnew BizSignal_Accessor());
			target->maxSignalLength = MAX_SIGNAL_LENGTH;
			array<float>^ signalExpected = gcnew array<float>(MAX_SIGNAL_LENGTH);;
			target->signal = gcnew array<float>(MAX_SIGNAL_LENGTH);;
			short inputSampleRate = Convert::ToInt16(testContextInstance->DataRow[L"InputSampleRate"]);
			short sampleRateExpected = Convert::ToInt16(testContextInstance->DataRow[L"SampleRate"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);
			bool actual;
			actual = target->Initialise(inputSampleRate);
			Assert::AreEqual(sampleRateExpected, target->sampleRate);
			Assert::AreEqual(expected, actual);
			CollectionAssert::AreEqual(signalExpected, target->signal);
		}
		/// <summary>
		///A test for Allocate
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizSignalAllocate.csv", L"BizSignalAllocate#csv", DataAccessMethod::Sequential),
			TestMethod]
		void AllocateTest()
		{
			BizSignal_Accessor^  target = (gcnew BizSignal_Accessor());
			short inputMaxSignalLength = Convert::ToInt16(testContextInstance->DataRow[L"InputMaxSignalLength"]);
			short inputMaxOnsetsLength = Convert::ToInt16(testContextInstance->DataRow[L"InputMaxOnsetsLength"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);
			bool actual;
			actual = target->Allocate(inputMaxSignalLength, inputMaxOnsetsLength);
			Assert::AreEqual(expected, actual);
			if (expected)
			{
				Assert::AreEqual(inputMaxSignalLength, target->maxSignalLength);
				Assert::AreEqual(inputMaxOnsetsLength, target->maxOnsetsLength);
				Assert::IsNotNull(target->signal);
				Assert::IsNotNull(target->floatOnsets);
				Assert::IsNotNull(target->derivative1);
				Assert::IsNotNull(target->derivative2);
			}
			else
			{
				Assert::AreEqual((short) 0, target->maxSignalLength);
				Assert::AreEqual((short) 0, target->maxOnsetsLength);
				Assert::IsNull(target->signal);
				Assert::IsNull(target->floatOnsets);
				Assert::IsNull(target->derivative1);
				Assert::IsNull(target->derivative2);
			}
		}
		/// <summary>
		///A test for BizSignal Constructor
		///</summary>					
public: [TestMethod]
		void BizSignalConstructorTest()
		{
			BizSignal_Accessor^  target = (gcnew BizSignal_Accessor());
			Assert::AreEqual((short) 0, target->signalLength);
			Assert::AreEqual((short) 0, target->onsetsLength);
			Assert::AreEqual((short) 0, target->maxSignalLength);
			Assert::AreEqual((short) 0, target->maxOnsetsLength);
			Assert::IsNull(target->signal);
			Assert::IsNull(target->floatOnsets);
			Assert::AreEqual(false, target->readyToCapture);
			Assert::AreEqual((float) DEFAULT_VALUE, target->pulseHeight);
			Assert::AreEqual((float) DEFAULT_VALUE, target->pulseHeightVariation);
			Assert::AreEqual((float) DEFAULT_VALUE, target->pulseLengthVariation);
			Assert::AreEqual((float) DEFAULT_VALUE, target->baseLineVariation);
		}
		/// <summary>
		///A test for CaptureSignal
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizSignalCaptureSignal.csv", L"BizSignalCaptureSignal#csv", DataAccessMethod::Sequential),
			TestMethod]
		void CaptureSignalTest()
		{
			BizSignal_Accessor^  target = (gcnew BizSignal_Accessor());
			short size = Convert::ToInt16(testContextInstance->DataRow[L"Size"]);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Input"]);
			cli::array< short >^  input = nullptr;
			if (values != "nullptr")
			{
				array<String^>^ valuesArray = values->Split(',');
				input = Array::ConvertAll(valuesArray, gcnew Converter<String^, short>(Convert::ToInt16));
			}
			bool readyToCapture = Convert::ToBoolean(testContextInstance->DataRow[L"ReadyToCapture"]);
			if (readyToCapture)
			{
				target->maxSignalLength = size;
				target->signal = gcnew array<float>(size);;
				target->readyToCapture = true;
			}
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = target->CaptureSignal(input, size);
			if (expected)
			{
				cli::array<float>^ signalExpected = Array::ConvertAll(input, gcnew Converter<short, float>(Convert::ToSingle));
				CollectionAssert::AreEqual(target->signal, signalExpected);
			}
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for PrepareToCapture
		///</summary>
public: [TestMethod]
		void PrepareToCaptureTest()
		{
			BizSignal_Accessor^  target = (gcnew BizSignal_Accessor());
			target->PrepareToCapture();
			Assert::IsTrue(target->readyToCapture);
		}
		/// <summary>
		///A test for ValidateSignalLength
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizSignalValidateSignalLength.csv", L"BizSignalValidateSignalLength#csv", DataAccessMethod::Sequential),
			TestMethod]
		void ValidateSignalLengthTest()
		{
			BizSignal_Accessor^  target = (gcnew BizSignal_Accessor());
			target->maxSignalLength = MAX_SIGNAL_LENGTH;
			short minSignalLength = Convert::ToInt16(testContextInstance->DataRow[L"MinSignalLength"]);
			short signalLength = Convert::ToInt16(testContextInstance->DataRow[L"SignalLength"]);
			target->signalLength = signalLength;
			short sampleRate = Convert::ToInt16(testContextInstance->DataRow[L"SampleRate"]);
			target->sampleRate = sampleRate;
			short signalLengthExpected = Convert::ToInt16(testContextInstance->DataRow[L"SignalLengthExpected"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);
			bool actual;
			actual = target->ValidateSignalLength(minSignalLength);
			Assert::AreEqual(signalLengthExpected, target->signalLength);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for ValidateSignalHeight
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizSignalValidateSignalHeight.csv", L"BizSignalValidateSignalHeight#csv", DataAccessMethod::Sequential),
			TestMethod]
		void ValidateSignalHeightTest()
		{
			BizSignal^  target = (gcnew BizSignal()); 
			short minSignalHeight = Convert::ToInt16(testContextInstance->DataRow[L"MinSignalHeight"]);
			short signalLength = Convert::ToInt16(testContextInstance->DataRow[L"SignalLength"]);
			target->signalLength = signalLength;
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Signal"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< float >^ signal = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			target->signal = signal;
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = target->ValidateSignalHeight(minSignalHeight);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for ValidateBeforeStore
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizSignalValidateBeforeStore.csv", L"BizSignalValidateBeforeStore#csv", DataAccessMethod::Sequential),
			TestMethod]
		void ValidateBeforeStoreTest()
		{
			BizSignal_Accessor^  target = (gcnew BizSignal_Accessor());
			target->maxSignalLength = MAX_SIGNAL_LENGTH;
			target->maxOnsetsLength = MAX_ONSETS;
			target->sampleRate = DEFAULT_SAMPLE_RATE;
			target->signalLength = 1359;
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Signal"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< float >^ signal = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			target->signal = signal;
			short minSignalLength = Convert::ToInt16(testContextInstance->DataRow[L"MinSignalLength"]);
			short minOnsetsLength = Convert::ToInt16(testContextInstance->DataRow[L"MinOnsetsLength"]);
			short minSignalHeight = Convert::ToInt16(testContextInstance->DataRow[L"MinSignalHeight"]);
			short onsetsLength = Convert::ToInt16(testContextInstance->DataRow[L"OnsetsLength"]);
			target->onsetsLength = onsetsLength;
			short onsetsLengthExpected = Convert::ToInt16(testContextInstance->DataRow[L"OnsetsLengthExpected"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = target->ValidateBeforeStore(minSignalLength, minOnsetsLength, minSignalHeight);
			Assert::AreEqual(onsetsLengthExpected, target->onsetsLength);
			Assert::AreEqual(expected, actual);
		}
};
}
namespace TestBiz {
    
}
