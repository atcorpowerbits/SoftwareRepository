
#include "StdAfx.h"
#include <biz.h>
using namespace BIZ_NAMESPACE;
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
		void SetDefaultsTest()
		{
			BizSignal^ target = gcnew BizSignal();
			PrivateObject^ accessor = gcnew PrivateObject(target);
			accessor->SetProperty("maximumOnsetsLength", MAX_ONSETS);
			array<float>^ floatOnsetsExpected = gcnew array<float>(MAX_ONSETS);;
			for (int i = 0; i < MAX_ONSETS; i++)
			{
				floatOnsetsExpected[i] = DEFAULT_FLOAT_VALUE;
			}
			accessor->SetProperty("floatOnsets", gcnew array<float>(MAX_ONSETS));
			target->SetDefaults();
			Assert::AreEqual(false, (bool) accessor->GetProperty("_readyToCapture"));
			Assert::AreEqual((float) DEFAULT_VALUE, target->pulseHeight);
			Assert::AreEqual((float) DEFAULT_VALUE, target->pulseHeightVariation);
			Assert::AreEqual((float) DEFAULT_VALUE, target->pulseLengthVariation);
			Assert::AreEqual((float) DEFAULT_VALUE, target->pulseBaselineVariation);
			Assert::AreEqual((unsigned short) 0, target->onsetsLength);
			CollectionAssert::AreEqual(floatOnsetsExpected, target->floatOnsets);
		}
		/// <summary>
		///A test for Initialise
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizSignalInitialise.csv", L"BizSignalInitialise#csv", DataAccessMethod::Sequential),
			TestMethod]
		void InitialiseTest()
		{
			BizSignal^ target = gcnew BizSignal();
			PrivateObject^ accessor = gcnew PrivateObject(target);
			accessor->SetProperty("maximumSignalLength", MAX_SIGNAL_LENGTH);
			array<unsigned short>^ signalExpected = gcnew array<unsigned short>(MAX_SIGNAL_LENGTH);
			accessor->SetProperty("signal", gcnew array<unsigned short>(MAX_SIGNAL_LENGTH));
			unsigned short inputSampleRate = Convert::ToUInt16(testContextInstance->DataRow[L"InputSampleRate"]);
			unsigned short sampleRateExpected = Convert::ToUInt16(testContextInstance->DataRow[L"SampleRate"]);
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
			BizSignal^ target = gcnew BizSignal();
			PrivateObject^ accessor = gcnew PrivateObject(target);
			unsigned short inputMaximumSignalLength = Convert::ToUInt16(testContextInstance->DataRow[L"InputMaxSignalLength"]);
			unsigned short inputMaximumOnsetsLength = Convert::ToUInt16(testContextInstance->DataRow[L"InputMaxOnsetsLength"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);
			bool actual;
			actual = target->Allocate(inputMaximumSignalLength, inputMaximumOnsetsLength);
			Assert::AreEqual(expected, actual);
			if (expected)
			{
				Assert::AreEqual(inputMaximumSignalLength, (unsigned short) accessor->GetProperty("maximumSignalLength"));
				Assert::AreEqual(inputMaximumOnsetsLength, (unsigned short) accessor->GetProperty("maximumOnsetsLength"));
				Assert::IsNotNull(target->signal);
				Assert::IsNotNull(target->floatOnsets);
				Assert::IsNotNull(target->firstDerivative);
			}
			else
			{
				Assert::AreEqual((unsigned short) 0, (unsigned short) accessor->GetProperty("maximumSignalLength"));
				Assert::AreEqual((unsigned short) 0, (unsigned short) accessor->GetProperty("maximumOnsetsLength"));
				Assert::IsNull(target->signal);
				Assert::IsNull(target->floatOnsets);
				Assert::IsNull(target->firstDerivative);
			}
		}
		/// <summary>
		///A test for BizSignal Constructor
		///</summary>					
public: [TestMethod]
		void BizSignalConstructorTest()
		{
			BizSignal^ target = gcnew BizSignal();
			PrivateObject^ accessor = gcnew PrivateObject(target);
			Assert::AreEqual((unsigned short) 0, target->signalLength);
			Assert::AreEqual((unsigned short) 0, target->onsetsLength);
			Assert::AreEqual((unsigned short) 0, (unsigned short) accessor->GetProperty("maximumSignalLength"));
			Assert::AreEqual((unsigned short) 0, (unsigned short) accessor->GetProperty("maximumOnsetsLength"));
			Assert::IsNull(target->signal);
			Assert::IsNull(target->floatOnsets);
			Assert::IsNull(target->firstDerivative);
			Assert::AreEqual(false, (bool) accessor->GetProperty("_readyToCapture"));
			Assert::AreEqual((float) DEFAULT_VALUE, target->pulseHeight);
			Assert::AreEqual((float) DEFAULT_VALUE, target->pulseHeightVariation);
			Assert::AreEqual((float) DEFAULT_VALUE, target->pulseLengthVariation);
			Assert::AreEqual((float) DEFAULT_VALUE, target->pulseBaselineVariation);
		}
		/// <summary>
		///A test for CaptureSignal
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizSignalCaptureSignal.csv", L"BizSignalCaptureSignal#csv", DataAccessMethod::Sequential),
			TestMethod]
		void CaptureSignalTest()
		{
			BizSignal^ target = gcnew BizSignal();
			PrivateObject^ accessor = gcnew PrivateObject(target);
			unsigned short size = Convert::ToUInt16(testContextInstance->DataRow[L"Size"]);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Input"]);
			cli::array< unsigned short >^  input = nullptr;
			if (values != "nullptr")
			{
				array<String^>^ valuesArray = values->Split(',');
				input = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			}
			bool _readyToCapture = Convert::ToBoolean(testContextInstance->DataRow[L"ReadyToCapture"]);
			if (_readyToCapture)
			{
				accessor->SetProperty("maximumSignalLength", size);
				accessor->SetProperty("signal", gcnew array<unsigned short>(size));
				accessor->SetProperty("_readyToCapture", true);
			}
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = target->CaptureSignal(input, size);
			if (expected)
			{
				//cli::array<float>^ signalExpected = Array::ConvertAll(input, gcnew Converter<short, float>(Convert::ToSingle));
				CollectionAssert::AreEqual(target->signal, input);
			}
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for PrepareToCapture
		///</summary>
public: [TestMethod]
		void PrepareToCaptureTest()
		{
			BizSignal^ target = gcnew BizSignal();
			PrivateObject^ accessor = gcnew PrivateObject(target);
			target->PrepareToCapture();
			Assert::IsTrue((bool) accessor->GetProperty("_readyToCapture"));
		}
		/// <summary>
		///A test for ValidateSignalLength
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizSignalValidateSignalLength.csv", L"BizSignalValidateSignalLength#csv", DataAccessMethod::Sequential),
			TestMethod]
		void ValidateSignalLengthTest()
		{
			BizSignal^ target = gcnew BizSignal();
			PrivateObject^ accessor = gcnew PrivateObject(target);
			accessor->SetProperty("maximumSignalLength", MAX_SIGNAL_LENGTH);
			unsigned short minimumSignalLength = Convert::ToUInt16(testContextInstance->DataRow[L"MinSignalLength"]);
			unsigned short signalLength = Convert::ToUInt16(testContextInstance->DataRow[L"SignalLength"]);
			target->signalLength = signalLength;
			unsigned short sampleRate = Convert::ToUInt16(testContextInstance->DataRow[L"SampleRate"]);
			target->sampleRate = sampleRate;
			unsigned short signalLengthExpected = Convert::ToUInt16(testContextInstance->DataRow[L"SignalLengthExpected"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);
			bool actual;
			actual = target->ValidateSignalLength(minimumSignalLength);
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
			PrivateObject^ accessor = gcnew PrivateObject(target);
			unsigned short minimumSignalHeight = Convert::ToUInt16(testContextInstance->DataRow[L"MinSignalHeight"]);
			unsigned short signalLength = Convert::ToUInt16(testContextInstance->DataRow[L"SignalLength"]);
			target->signalLength = signalLength;
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Signal"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< unsigned short >^ signal = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			accessor->SetProperty("signal", signal);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = target->ValidateSignalHeight(minimumSignalHeight);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for ValidateBeforeStore
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizSignalValidateBeforeStore.csv", L"BizSignalValidateBeforeStore#csv", DataAccessMethod::Sequential),
			TestMethod]
		void ValidateBeforeStoreTest()
		{
			BizSignal^ target = gcnew BizSignal();
			PrivateObject^ accessor = gcnew PrivateObject(target);
			accessor->SetProperty("maximumSignalLength", MAX_SIGNAL_LENGTH);
			accessor->SetProperty("maximumOnsetsLength", MAX_ONSETS);
			target->sampleRate = DEFAULT_SAMPLE_RATE;
			target->signalLength = 1359;
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Signal"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< unsigned short >^ signal = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			accessor->SetProperty("signal", signal);
			unsigned short minimumSignalLength = Convert::ToUInt16(testContextInstance->DataRow[L"MinSignalLength"]);
			unsigned short minimumOnsetsLength = Convert::ToUInt16(testContextInstance->DataRow[L"MinOnsetsLength"]);
			unsigned short minimumSignalHeight = Convert::ToUInt16(testContextInstance->DataRow[L"MinSignalHeight"]);
			unsigned short onsetsLength = Convert::ToUInt16(testContextInstance->DataRow[L"OnsetsLength"]);
			target->onsetsLength = onsetsLength;
			unsigned short onsetsLengthExpected = Convert::ToUInt16(testContextInstance->DataRow[L"OnsetsLengthExpected"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = target->ValidateBeforeStore(minimumSignalLength, minimumOnsetsLength, minimumSignalHeight);
			Assert::AreEqual(onsetsLengthExpected, target->onsetsLength);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for ValidateSignal
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizSignalValidateSignal.csv", L"BizSignalValidateSignal#csv", DataAccessMethod::Sequential),
			TestMethod]
		void ValidateSignalTest()
		{
			BizSignal^ target = gcnew BizSignal();
			PrivateObject^ accessor = gcnew PrivateObject(target);
			accessor->SetProperty("maximumSignalLength", MAX_SIGNAL_LENGTH);
			target->sampleRate = DEFAULT_SAMPLE_RATE;
			target->signalLength = 1359;
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Signal"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< unsigned short >^ signal = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			accessor->SetProperty("signal", signal);
			unsigned short minimumSignalLength = Convert::ToUInt16(testContextInstance->DataRow[L"MinSignalLength"]);
			unsigned short minimumSignalHeight = Convert::ToUInt16(testContextInstance->DataRow[L"MinSignalHeight"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = target->ValidateSignal(minimumSignalLength, minimumSignalHeight);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for FindOnsets
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizSignalFindOnsets.csv", L"BizSignalFindOnsets#csv", DataAccessMethod::Sequential),
			TestMethod]
		void FindOnsetsTest()
		{
			BizSignal^ target = gcnew BizSignal();
			PrivateObject^ accessor = gcnew PrivateObject(target);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Signal"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< unsigned short >^ signal = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			accessor->SetProperty("signal", signal);
			target->signalLength = Convert::ToInt16(testContextInstance->DataRow[L"SignalLength"]);
			unsigned short onsetsLengthExpected = Convert::ToUInt16(testContextInstance->DataRow[L"OnsetsLengthExpected"]);
			unsigned short onsetsLength = Convert::ToUInt16(testContextInstance->DataRow[L"OnsetsLength"]);
			String^ onsets = Convert::ToString(testContextInstance->DataRow[L"FloatOnsets"]);
			cli::array< float >^ floatOnsetsExpected = nullptr;
			//accessor->SetProperty("floatOnsets", nullptr);
			array<String^>^ onsetsArray = onsets->Split(',');
			floatOnsetsExpected = Array::ConvertAll(onsetsArray, gcnew Converter<String^, float>(Convert::ToSingle));
			accessor->SetProperty("floatOnsets", gcnew array<float>(onsetsLength));
			target->sampleRate = DEFAULT_SAMPLE_RATE;
			accessor->SetProperty("maximumOnsetsLength", onsetsLengthExpected);
			accessor->SetProperty("firstDerivative", gcnew array<float>(MAX_SIGNAL_LENGTH));
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = target->FindOnsets();
			Assert::AreEqual(expected, actual);
			Assert::AreEqual(onsetsLengthExpected, target->onsetsLength);
			CollectionAssert::AreEqual(floatOnsetsExpected, target->floatOnsets);
		}
		/// <summary>
		///A test for TangentAlgorithm
		///</summary>
/*public: [
			DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizSignalTangentAlgorithm.csv", L"BizSignalTangentAlgorithm#csv", DataAccessMethod::Sequential),
				TestMethod]
		void TangentAlgorithmTest()
		{
			BizSignal^ target = gcnew BizSignal();
			PrivateObject^ accessor = gcnew PrivateObject(target);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Signal"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< float >^ signal = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			accessor->SetProperty("signal", signal);
			target->signalLength = Convert::ToInt16(testContextInstance->DataRow[L"SignalLength"]);
			short onsetsLengthExpected = Convert::ToInt16(testContextInstance->DataRow[L"OnsetsLength"]);
			String^ onsets = Convert::ToString(testContextInstance->DataRow[L"FloatOnsets"]);
			cli::array< float >^ floatOnsetsExpected = nullptr;
			accessor->SetProperty("floatOnsets", nullptr);
			if (onsets != "nullptr")
			{
				array<String^>^ onsetsArray = onsets->Split(',');
				floatOnsetsExpected = Array::ConvertAll(onsetsArray, gcnew Converter<String^, float>(Convert::ToSingle));
				accessor->SetProperty("floatOnsets", gcnew array<float>(onsetsLengthExpected));
			}
			target->sampleRate = DEFAULT_SAMPLE_RATE;
			accessor->SetProperty("maximumOnsetsLength", onsetsLengthExpected);
			accessor->SetProperty("firstDerivative", gcnew array<float>(MAX_SIGNAL_LENGTH));
			float maximumFirstDerivative;
			BizMath::SmoothFirstDerivative(signal, target->signalLength, 
			SIGNAL_SMOOTH_ORDER, SIGNAL_STEP, target->firstDerivative, maximumFirstDerivative);
			float inputMaximumFirstDerivative = Convert::ToSingle(testContextInstance->DataRow[L"MaxFirstDerivative"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);
			bool actual;
			actual = target->TangentAlgorithm(inputMaximumFirstDerivative);
			CollectionAssert::AreEqual(floatOnsetsExpected, target->floatOnsets);
			Assert::AreEqual(onsetsLengthExpected, target->onsetsLength);
			Assert::AreEqual(expected, actual);
		}*/
		/// <summary>
		///A test for CalculateQualityControls
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizSignalCalculateQualityControls.csv", L"BizSignalCalculateQualityControls#csv", DataAccessMethod::Sequential),
			TestMethod]
		void CalculateQualityControlsTest()
		{
			BizSignal^ target = gcnew BizSignal();
			PrivateObject^ accessor = gcnew PrivateObject(target);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Signal"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< unsigned short >^ signal = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			accessor->SetProperty("signal", signal);
			String^ onsets = Convert::ToString(testContextInstance->DataRow[L"FloatOnsets"]);
			array<String^>^ onsetsArray = onsets->Split(',');
			cli::array< float >^ floatOnsets = Array::ConvertAll(onsetsArray, gcnew Converter<String^, float>(Convert::ToSingle));
			accessor->SetProperty("floatOnsets", floatOnsets);
			target->signalLength = Convert::ToInt16(testContextInstance->DataRow[L"SignalLength"]);
			target->onsetsLength = Convert::ToInt16(testContextInstance->DataRow[L"OnsetsLength"]);
			float pulseHeight = Convert::ToSingle(testContextInstance->DataRow[L"PulseHeight"]);
			float pulseHeightVariation = Convert::ToSingle(testContextInstance->DataRow[L"PulseHeightVariation"]);
			float pulseLengthVariation = Convert::ToSingle(testContextInstance->DataRow[L"PulseLengthVariation"]);
			float pulseBaselineVariation = Convert::ToSingle(testContextInstance->DataRow[L"PulseBaselineVariation"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);
			bool actual;
			actual = target->CalculateQualityControls();
			Assert::AreEqual(pulseHeight, target->pulseHeight);
			Assert::AreEqual(pulseHeightVariation, target->pulseHeightVariation);
			Assert::AreEqual(pulseLengthVariation, target->pulseLengthVariation);
			Assert::AreEqual(pulseBaselineVariation, target->pulseBaselineVariation);
			Assert::AreEqual(expected, actual);
		}
};
}
namespace TestBiz {
    
}
