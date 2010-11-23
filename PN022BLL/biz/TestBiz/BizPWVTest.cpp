
#include "StdAfx.h"
#include <biz.h>
#include "StdAfx.h"
using namespace AtCor::Scor::BusinessLogic;
using namespace BIZ_NAMESPACE;
using namespace CRX_CONFIG_NAMESPACE;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace TestBiz {
    using namespace System;
	using namespace System::IO;
    ref class BizPWVTest;
    
#define USHRT_MAX 0xffff
    
    /// <summary>
///This is a test class for BizPWVTest and is intended
///to contain all BizPWVTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizPWVTest
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
			///A test for PWVDistance
			///</summary>
	public: [TestMethod]
			void PWVDistanceTest()
			{
				BizPWV^  target = (gcnew BizPWV()); // TODO: Initialize to an appropriate value
				unsigned short expected = USHRT_MAX; // TODO: Initialize to an appropriate value
				unsigned short actual;
				target->myPWVDirectDistance->distance = expected;
				actual = target->myPWVDirectDistance->distance;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for Femoral2CuffDistance
			///</summary>
	public: [TestMethod]
			void Femoral2CuffDistanceTest()
			{
				BizPWV^  target = (gcnew BizPWV()); // TODO: Initialize to an appropriate value
				unsigned short expected = USHRT_MAX; // TODO: Initialize to an appropriate value
				unsigned short actual;
				target->myFemoral2CuffDistance->distance = expected;
				actual = target->myFemoral2CuffDistance->distance;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for CuffDistance
			///</summary>
	public: [TestMethod]
			void CuffDistanceTest()
			{
				BizPWV^  target = (gcnew BizPWV()); // TODO: Initialize to an appropriate value
				unsigned short expected = USHRT_MAX; // TODO: Initialize to an appropriate value
				unsigned short actual;
				target->myCuffDistance->distance = expected;
				actual = target->myCuffDistance->distance;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for CarotidDistance
			///</summary>
	public: [TestMethod]
			void CarotidDistanceTest()
			{
				BizPWV^  target = (gcnew BizPWV()); // TODO: Initialize to an appropriate value
				unsigned short expected = USHRT_MAX; // TODO: Initialize to an appropriate value
				unsigned short actual;
				target->myCarotidDistance->distance = expected;
				actual = target->myCarotidDistance->distance;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for ValidatePWVDistance
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\ValidatePWVDistance.csv", L"ValidatePWVDistance#csv", DataAccessMethod::Sequential),
				TestMethod]
			void ValidatePWVDistanceTest()
			{
				BizPWV^  target = (gcnew BizPWV()); // TODO: Initialize to an appropriate value
				bool expected = Convert::ToBoolean(testContextInstance->DataRow["Expected"]); // TODO: Initialize to an appropriate value
				bool actual;
//				CrxConfigFacade::Instance()->SetDistanceMethod(Convert::ToBoolean(testContextInstance->DataRow["Method"]));
				CrxConfigManager::Instance->PwvSettings->PWVDistanceMethod = Convert::ToUInt16(testContextInstance->DataRow["Method"]);
				target->myCarotidDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["Carotid"]);
				target->myCuffDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["Cuff"]);
				target->myPWVDirectDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["PWVDist"]);
				actual = target->ValidatePWVDistance();
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for Validate
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVValidate.csv", L"BizPWVValidate#csv", DataAccessMethod::Sequential),
				TestMethod]
			void BizPWVValidateTest()
			{
				BizPWV^  target = (gcnew BizPWV());
				bool expected = true; 
				bool actual;
				actual = target->myFemoral2CuffDistance->Validate();
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for Validate
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVValidate.csv", L"BizPWVValidate#csv", DataAccessMethod::Sequential),
				TestMethod]
			void ValidateTest()
			{
				BizPWV^  target = (gcnew BizPWV());
				PrivateObject^ accessor = gcnew PrivateObject(target);
//				CrxConfigFacade::Instance()->SetDistanceMethod(true);
				CrxConfigManager::Instance->PwvSettings->PWVDistanceMethod = 0; // TBD: Replace magic number for subtracting method
				accessor->SetProperty("systemId", Convert::ToString(testContextInstance->DataRow["SystemID"]));
				accessor->SetProperty("patientNumber", Convert::ToUInt32(testContextInstance->DataRow["PatientNumber"]));
				accessor->SetProperty("measurementDateTime", Convert::ToDateTime(testContextInstance->DataRow["MeasurementDateTime"]));
				accessor->SetProperty("dataRevision", Convert::ToUInt16(testContextInstance->DataRow["DataRevision"]));
				accessor->SetProperty("sampleRate", Convert::ToUInt16(testContextInstance->DataRow["SampleRate"]));
				accessor->SetProperty("captureTime", Convert::ToUInt16(testContextInstance->DataRow["CaptureTime"]));
				target->myCarotidDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["Carotid"]);
				target->myCuffDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["Cuff"]);
				target->myFemoral2CuffDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["FemoralToCuff"]);
				unsigned short distanceExpected = Convert::ToUInt16(testContextInstance->DataRow[L"CalculatedDistanceExpected"]);
				bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
				bool actual;
				actual = target->Validate();
				Assert::AreEqual(expected, actual);
				Assert::AreEqual(distanceExpected, target->calculatedDistance);
			}
			/// <summary>
			///A test for BizPWV Constructor
			///</summary>
	public: [TestMethod]
			void BizPWVConstructorTest()
			{
				// Metric Test
				BizPWV^  target = (gcnew BizPWV());
				Assert::IsNotNull(target);
				Assert::IsNotNull(target->myCarotidDistance);
				Assert::IsNotNull(target->myCuffDistance);
				Assert::IsNotNull(target->myPWVDirectDistance);
				Assert::IsNotNull(target->myFemoral2CuffDistance);
				Assert::IsNotNull(target->tonometerDataObserver);
				Assert::IsNotNull(target->cuffPulseObserver);
				Assert::IsNotNull(target->countdownTimerObserver);
				Assert::IsNotNull(target->carotidSignal);
				Assert::IsNotNull(target->femoralSignal);
				Assert::IsNotNull(target->pulseWaveVelocity);
			}
			/// <summary>
			///A test for SetDefaults
			///</summary>
public: [TestMethod]
		void SetDefaultsTest()
		{
			BizPWV^  target = (gcnew BizPWV());
			PrivateObject^ accessor = gcnew PrivateObject(target);
			accessor->Invoke("SetDefaults");
			Assert::AreEqual((float) BizConstants::DEFAULT_VALUE, target->meanDeltaTime);
			Assert::AreEqual((float) BizConstants::DEFAULT_VALUE, target->meanCorrectedTime);
			Assert::AreEqual((float) BizConstants::DEFAULT_VALUE, target->meanPulseWaveVelocity);
			Assert::AreEqual((float) BizConstants::DEFAULT_VALUE, target->standardDeviation);
			Assert::AreEqual((unsigned short) 0, target->numberOfDeltas);
			Assert::AreEqual((unsigned short) 0, target->numberOfValidDeltas);
			Assert::IsFalse(target->isCarotidSignalValid);
			Assert::IsFalse(target->isFemoralSignalValid);
			Assert::IsFalse(target->isStandardDeviationValid);	
			Assert::AreEqual((float) BizConstants::DEFAULT_VALUE, target->meanHeartRate);
		}
		/// <summary>
		///A test for Initialise
		///</summary>
public: [TestMethod]
		void InitialiseTest()
		{
			BizPWV^  target = (gcnew BizPWV());
			// MPDP Test
			CrxConfigManager::Instance->GeneralSettings->BloodPressureEntryOptions = CrxConfigConstants::GENERAL_BP_ENTRY_MPDP;
			target->Initialise();
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->myCarotidDistance->distance);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->myCuffDistance->distance);
			Assert::AreEqual((unsigned short) DEFAULT_FEMORAL_TO_CUFF_DISTANCE, target->myFemoral2CuffDistance->distance);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->myPWVDirectDistance->distance);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->calculatedDistance);
			Assert::AreEqual((float) DEFAULT_CORRECTION_TIME, target->correctionTime);
			Assert::AreEqual((String^) "", target->systemId);
			Assert::AreEqual((unsigned int) 0, target->patientNumber);
			Assert::AreEqual((String^) "", target->groupStudyId);
			Assert::IsNotNull(target->measurementDateTime);
			Assert::AreEqual((unsigned short) DATA_REVISION, target->dataRevision);
			Assert::AreEqual((String^) "", target->medication);
			Assert::AreEqual((String^) "", target->notes);
			Assert::AreEqual((String^) "", target->operatorId);
			Assert::AreEqual((String^) "", target->interpretation);
			Assert::AreEqual((float) BizConstants::DEFAULT_VALUE, target->heightAndWeight->bodyMassIndex);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->heightAndWeight->heightInCentimetres);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->heightAndWeight->heightInInches);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->heightAndWeight->weightInKilograms);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->heightAndWeight->weightInPounds);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->bloodPressure->MP->Reading);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->bloodPressure->DP->Reading);
			Assert::AreEqual((unsigned short) DEFAULT_CAPTURE_TIME, target->captureTime);
			Assert::AreEqual((unsigned short) DEFAULT_SAMPLE_RATE, target->sampleRate);
			Assert::IsFalse(target->simulation);

			// SPDP Test
			CrxConfigManager::Instance->GeneralSettings->BloodPressureEntryOptions = CrxConfigConstants::GENERAL_BP_ENTRY_SPDP;
			target->Initialise();
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->myCarotidDistance->distance);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->myCuffDistance->distance);
			Assert::AreEqual((unsigned short) DEFAULT_FEMORAL_TO_CUFF_DISTANCE, target->myFemoral2CuffDistance->distance);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->myPWVDirectDistance->distance);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->calculatedDistance);
			Assert::AreEqual((float) DEFAULT_CORRECTION_TIME, target->correctionTime);
			Assert::AreEqual((String^) "", target->systemId);
			Assert::AreEqual((unsigned int) 0, target->patientNumber);
			Assert::AreEqual((String^) "", target->groupStudyId);
			Assert::IsNotNull(target->measurementDateTime);
			Assert::AreEqual((unsigned short) DATA_REVISION, target->dataRevision);
			Assert::AreEqual((String^) "", target->medication);
			Assert::AreEqual((String^) "", target->notes);
			Assert::AreEqual((String^) "", target->operatorId);
			Assert::AreEqual((String^) "", target->interpretation);
			Assert::AreEqual((float) BizConstants::DEFAULT_VALUE, target->heightAndWeight->bodyMassIndex);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->heightAndWeight->heightInCentimetres);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->heightAndWeight->heightInInches);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->heightAndWeight->weightInKilograms);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->heightAndWeight->weightInPounds);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->bloodPressure->SP->Reading);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->bloodPressure->DP->Reading);
			Assert::AreEqual((unsigned short) DEFAULT_CAPTURE_TIME, target->captureTime);
			Assert::AreEqual((unsigned short) DEFAULT_SAMPLE_RATE, target->sampleRate);
			Assert::IsFalse(target->simulation);

			// SPMP Test
			CrxConfigManager::Instance->GeneralSettings->BloodPressureEntryOptions = CrxConfigConstants::GENERAL_BP_ENTRY_SPMP;
			target->Initialise();
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->myCarotidDistance->distance);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->myCuffDistance->distance);
			Assert::AreEqual((unsigned short) DEFAULT_FEMORAL_TO_CUFF_DISTANCE, target->myFemoral2CuffDistance->distance);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->myPWVDirectDistance->distance);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->calculatedDistance);
			Assert::AreEqual((float) DEFAULT_CORRECTION_TIME, target->correctionTime);
			Assert::AreEqual((String^) "", target->systemId);
			Assert::AreEqual((unsigned int) 0, target->patientNumber);
			Assert::AreEqual((String^) "", target->groupStudyId);
			Assert::IsNotNull(target->measurementDateTime);
			Assert::AreEqual((unsigned short) DATA_REVISION, target->dataRevision);
			Assert::AreEqual((String^) "", target->medication);
			Assert::AreEqual((String^) "", target->notes);
			Assert::AreEqual((String^) "", target->operatorId);
			Assert::AreEqual((String^) "", target->interpretation);
			Assert::AreEqual((float) BizConstants::DEFAULT_VALUE, target->heightAndWeight->bodyMassIndex);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->heightAndWeight->heightInCentimetres);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->heightAndWeight->heightInInches);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->heightAndWeight->weightInKilograms);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->heightAndWeight->weightInPounds);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->bloodPressure->MP->Reading);
			Assert::AreEqual((unsigned short) BizConstants::DEFAULT_VALUE, target->bloodPressure->SP->Reading);
			Assert::AreEqual((unsigned short) DEFAULT_CAPTURE_TIME, target->captureTime);
			Assert::AreEqual((unsigned short) DEFAULT_SAMPLE_RATE, target->sampleRate);
			Assert::IsFalse(target->simulation);
		}
		/// <summary>
		///A test for ValidateSignals
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVValidateSignals.csv", L"BizPWVValidateSignals#csv", DataAccessMethod::Sequential),
			TestMethod]
		void ValidateSignalsTest()
		{
			BizPWV^  target = (gcnew BizPWV());
			target->carotidSignal->PrepareToCapture();
			target->femoralSignal->PrepareToCapture();
			unsigned short carotidSignalLength = Convert::ToUInt16(testContextInstance->DataRow[L"CarotidSignalLength"]);
			unsigned short femoralSignalLength = Convert::ToUInt16(testContextInstance->DataRow[L"FemoralSignalLength"]);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Signal"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< unsigned short >^ signal = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			target->carotidSignal->CaptureSignal(signal, carotidSignalLength);
			target->femoralSignal->CaptureSignal(signal, femoralSignalLength);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = target->ValidateSignals();
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for CalculateDistance
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVCalculateDistance.csv", L"BizPWVCalculateDistance#csv", DataAccessMethod::Sequential),
			TestMethod]
		void CalculateAndValidateDistanceTest()
		{
			BizPWV^  target = (gcnew BizPWV());
			PrivateObject^ accessor = gcnew PrivateObject(target);
//			CrxConfigFacade::Instance()->SetDistanceMethod(Convert::ToBoolean(testContextInstance->DataRow["Method"]));
			CrxConfigManager::Instance->PwvSettings->PWVDistanceMethod = Convert::ToUInt16(testContextInstance->DataRow["Method"]);
			target->myCarotidDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["Carotid"]);
			target->myCuffDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["Cuff"]);
			target->myPWVDirectDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["DirectDistance"]);
			target->myFemoral2CuffDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["FemoralToCuff"]);
			unsigned short distanceExpected = Convert::ToUInt16(testContextInstance->DataRow[L"CalculatedDistanceExpected"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = (bool) accessor->Invoke("CalculateAndValidateDistance");
			Assert::AreEqual(expected, actual);
			Assert::AreEqual(distanceExpected, target->calculatedDistance);
		}
		/// <summary>
		///A test for CalculateHeartRate
		///</summary>
/*public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVCalculateHeartRate.csv", L"BizPWVCalculateHeartRate#csv", DataAccessMethod::Sequential),
			TestMethod]
		
		void CalculateHeartRateTest()
		{
			BizPWV^  target = (gcnew BizPWV());
			PrivateObject^ accessor = gcnew PrivateObject(target);
			BizSignal^ femoral = target->femoralSignal;
			PrivateObject^ femoralAccessor = gcnew PrivateObject(femoral);
			accessor->SetProperty("sampleRate", Convert::ToUInt16(testContextInstance->DataRow[L"SampleRate"]));
			target->femoralSignal->onsetsLength = Convert::ToUInt16(testContextInstance->DataRow[L"OnsetsLength"]);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"FloatOnsets"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< float >^ floatOnsets = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			femoralAccessor->SetProperty("floatOnsets", floatOnsets);
			float meanHeartRateExpected = Convert::ToSingle(testContextInstance->DataRow[L"HeartRateExpected"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = (bool) accessor->Invoke("CalculateHeartRate");
			Assert::AreEqual(expected, actual);
			Assert::AreEqual(meanHeartRateExpected, target->meanHeartRate);
		}*/
		/// <summary>
		///A test for CalculateBizDeltaArray
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVCalculateBizDeltaArray.csv", L"BizPWVCalculateBizDeltaArray#csv", DataAccessMethod::Sequential),
			TestMethod]
		void CalculateBizDeltaArrayTest()
		{
			BizPWV^  target = (gcnew BizPWV());
			PrivateObject^ accessor = gcnew PrivateObject(target);
			BizSignal^ femoral = target->femoralSignal;
			PrivateObject^ femoralAccessor = gcnew PrivateObject(femoral);
			BizSignal^ carotid = target->carotidSignal;
			PrivateObject^ carotidAccessor = gcnew PrivateObject(carotid);
			accessor->SetProperty("sampleRate", Convert::ToUInt16(testContextInstance->DataRow[L"SampleRate"]));
			target->calculatedDistance = Convert::ToUInt16(testContextInstance->DataRow[L"CalculatedDistance"]);
			unsigned short numberOfDeltasExpected = Convert::ToUInt16(testContextInstance->DataRow[L"NumberOfDeltas"]);
			unsigned short numberOfValidDeltasExpected = Convert::ToUInt16(testContextInstance->DataRow[L"NumberOfValidDeltas"]);
			target->femoralSignal->onsetsLength = Convert::ToUInt16(testContextInstance->DataRow[L"FemoralOnsetsLength"]);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"FemoralFloatOnsets"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< float >^ floatOnsets = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			femoralAccessor->SetProperty("floatOnsets", floatOnsets);
			target->carotidSignal->onsetsLength = Convert::ToUInt16(testContextInstance->DataRow[L"CarotidOnsetsLength"]);
			values = Convert::ToString(testContextInstance->DataRow[L"CarotidFloatOnsets"]);
			valuesArray = values->Split(',');
			floatOnsets = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			carotidAccessor->SetProperty("floatOnsets", floatOnsets);
			values = Convert::ToString(testContextInstance->DataRow[L"HeartRate"]);
			valuesArray = values->Split(',');
			cli::array< float >^ heartRateExpected = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			values = Convert::ToString(testContextInstance->DataRow[L"DeltaTime"]);
			valuesArray = values->Split(',');
			cli::array< float >^ deltaTimeExpected = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			values = Convert::ToString(testContextInstance->DataRow[L"CorrectedTime"]);
			valuesArray = values->Split(',');
			cli::array< float >^ correctedTimeExpected = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			values = Convert::ToString(testContextInstance->DataRow[L"PulseWaveVelocity"]);
			valuesArray = values->Split(',');
			cli::array< float >^ pulseWaveVelocityExpected = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			values = Convert::ToString(testContextInstance->DataRow[L"IsValid"]);
			valuesArray = values->Split(',');
			cli::array< bool >^ isValidExpected = Array::ConvertAll(valuesArray, gcnew Converter<String^, bool>(Convert::ToBoolean));
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = (bool) accessor->Invoke("CalculateBizDeltaArray");
			Assert::AreEqual(expected, actual);
			Assert::AreEqual(numberOfDeltasExpected, target->numberOfDeltas);
			Assert::AreEqual(numberOfValidDeltasExpected, target->numberOfValidDeltas);
			for (int i = 0; i < numberOfDeltasExpected; i++)
			{
				Assert::AreEqual(heartRateExpected[i], target->pulseWaveVelocity[i]->heartRate);
				Assert::AreEqual(deltaTimeExpected[i], target->pulseWaveVelocity[i]->deltaTime);
				Assert::AreEqual(correctedTimeExpected[i], target->pulseWaveVelocity[i]->correctedTime);
				Assert::AreEqual(pulseWaveVelocityExpected[i], target->pulseWaveVelocity[i]->pulseWaveVelocity);
				Assert::AreEqual(isValidExpected[i], target->pulseWaveVelocity[i]->isValid);
			}
		}
		/// <summary>
		///A test for CalculateFeatures
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVCalculateFeatures.csv", L"BizPWVCalculateFeatures#csv", DataAccessMethod::Sequential),
			TestMethod]
		void CalculateFeaturesTest()
		{
			BizPWV^  target = (gcnew BizPWV());
			PrivateObject^ accessor = gcnew PrivateObject(target);
			target->numberOfDeltas = Convert::ToUInt16(testContextInstance->DataRow[L"NumberOfDeltas"]);
			target->numberOfValidDeltas = Convert::ToUInt16(testContextInstance->DataRow[L"NumberOfValidDeltas"]);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"HeartRate"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< float >^ heartRateInput = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			values = Convert::ToString(testContextInstance->DataRow[L"DeltaTime"]);
			valuesArray = values->Split(',');
			cli::array< float >^ deltaTimeInput = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			values = Convert::ToString(testContextInstance->DataRow[L"CorrectedTime"]);
			valuesArray = values->Split(',');
			cli::array< float >^ correctedTimeInput = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			values = Convert::ToString(testContextInstance->DataRow[L"PulseWaveVelocity"]);
			valuesArray = values->Split(',');
			cli::array< float >^ pulseWaveVelocityInput= Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			values = Convert::ToString(testContextInstance->DataRow[L"IsValid"]);
			valuesArray = values->Split(',');
			cli::array< bool >^ isValidInput = Array::ConvertAll(valuesArray, gcnew Converter<String^, bool>(Convert::ToBoolean));
			for (int i = 0; i < target->numberOfDeltas; i++)
			{
				target->pulseWaveVelocity[i]->heartRate = heartRateInput[i];
				target->pulseWaveVelocity[i]->deltaTime = deltaTimeInput[i];
				target->pulseWaveVelocity[i]->correctedTime = correctedTimeInput[i];
				target->pulseWaveVelocity[i]->pulseWaveVelocity = pulseWaveVelocityInput[i];
				target->pulseWaveVelocity[i]->isValid = isValidInput[i];
			}
			float meanHeartRateExpected = Convert::ToSingle(testContextInstance->DataRow[L"MeanHeartRate"]);
			float meanDeltaTimeExpected = Convert::ToSingle(testContextInstance->DataRow[L"MeanDeltaTime"]);
			float meanCorrectedTimeExpected = Convert::ToSingle(testContextInstance->DataRow[L"MeanCorrectedTime"]);
			float meanPulseWaveVelocityExpected = Convert::ToSingle(testContextInstance->DataRow[L"MeanPulseWaveVelocity"]);
			float standardDeviationExpected = Convert::ToSingle(testContextInstance->DataRow[L"StandardDeviation"]);
			bool isStandardDeviationValidExpected = Convert::ToBoolean(testContextInstance->DataRow[L"IsStandardDeviationValid"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = (bool) accessor->Invoke("CalculateFeatures");
			Assert::AreEqual(expected, actual);
			Assert::AreEqual(meanHeartRateExpected, target->meanHeartRate);
			Assert::AreEqual(meanDeltaTimeExpected, target->meanDeltaTime);
			Assert::AreEqual(meanCorrectedTimeExpected, target->meanCorrectedTime);
			Assert::AreEqual(meanPulseWaveVelocityExpected, target->meanPulseWaveVelocity);
			Assert::AreEqual(standardDeviationExpected, target->standardDeviation);
			Assert::AreEqual(isStandardDeviationValidExpected, target->isStandardDeviationValid);
		}
		/// <summary>
		///A test for Calculate
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVCalculate.csv", L"BizPWVCalculate#csv", DataAccessMethod::Sequential),
			TestMethod]
		void CalculateTest()
		{
			BizPWV^  target = (gcnew BizPWV());
			PrivateObject^ accessor = gcnew PrivateObject(target);
			accessor->SetProperty("systemId", "00050");
			accessor->SetProperty("patientNumber", (unsigned int) 1);
			target->PrepareToCaptureSignal();
//			CrxConfigFacade::Instance()->SetDistanceMethod(false);
			CrxConfigManager::Instance->PwvSettings->PWVDistanceMethod = 1; // TBD: Replace magic number for direct method
			unsigned short signalLength = Convert::ToUInt16(testContextInstance->DataRow[L"SignalLength"]);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"CarotidSignal"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< unsigned short >^ carotidSignal = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			values = Convert::ToString(testContextInstance->DataRow[L"FemoralSignal"]);
			valuesArray = values->Split(',');
			cli::array< unsigned short >^ femoralSignal = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			target->carotidSignal->CaptureSignal(carotidSignal, signalLength);
			target->femoralSignal->CaptureSignal(femoralSignal, signalLength);
			target->myPWVDirectDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["DirectDistance"]);
			target->correctionTime = Convert::ToSingle(testContextInstance->DataRow["CorrectionTime"]);
			float meanHeartRateExpected = Convert::ToSingle(testContextInstance->DataRow[L"HeartRate"]);
			float meanDeltaTimeExpected = Convert::ToSingle(testContextInstance->DataRow[L"MeanDeltaTime"]);
			float meanCorrectedTimeExpected = Convert::ToSingle(testContextInstance->DataRow[L"MeanCorrectedTime"]);
			float meanPulseWaveVelocityExpected = Convert::ToSingle(testContextInstance->DataRow[L"MeanPulseWaveVelocity"]);
			float standardDeviationExpected = Convert::ToSingle(testContextInstance->DataRow[L"StandardDeviation"]);
			bool isStandardDeviationValidExpected = Convert::ToBoolean(testContextInstance->DataRow[L"IsStandardDeviationValid"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = target->Calculate();
			Assert::AreEqual(expected, actual);
			Assert::AreEqual(meanHeartRateExpected, target->meanHeartRate);
			Assert::AreEqual(meanDeltaTimeExpected, target->meanDeltaTime);
			Assert::AreEqual(meanCorrectedTimeExpected, target->meanCorrectedTime);
			Assert::AreEqual(meanPulseWaveVelocityExpected, target->meanPulseWaveVelocity);
			Assert::AreEqual(standardDeviationExpected, target->standardDeviation);
			Assert::AreEqual(isStandardDeviationValidExpected, target->isStandardDeviationValid);
		}
		/// <summary>
		///A test for CalculateQualityControls
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVCalculateQualityControls.csv", L"BizPWVCalculateQualityControls#csv", DataAccessMethod::Sequential),
			TestMethod]
		void CalculateQualityControlsTest()
		{
			BizPWV^  target = (gcnew BizPWV());
			PrivateObject^ accessor = gcnew PrivateObject(target);
			BizSignal^ femoral = target->femoralSignal;
			PrivateObject^ femoralAccessor = gcnew PrivateObject(femoral);
			BizSignal^ carotid = target->carotidSignal;
			PrivateObject^ carotidAccessor = gcnew PrivateObject(carotid);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"CarotidSignal"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< unsigned short >^ carotidSignal = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			values = Convert::ToString(testContextInstance->DataRow[L"FemoralSignal"]);
			valuesArray = values->Split(',');
			cli::array< unsigned short >^ femoralSignal = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			values = Convert::ToString(testContextInstance->DataRow[L"CarotidFloatOnsets"]);
			valuesArray = values->Split(',');
			cli::array< float >^ carotidFloatOnsets = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			values = Convert::ToString(testContextInstance->DataRow[L"FemoralFloatOnsets"]);
			valuesArray = values->Split(',');
			cli::array< float >^ femoralFloatOnsets = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			carotidAccessor->SetProperty("signal", carotidSignal);
			femoralAccessor->SetProperty("signal", femoralSignal);
			target->carotidSignal->signalLength = Convert::ToUInt16(testContextInstance->DataRow[L"CarotidSignalLength"]);
			target->femoralSignal->signalLength = Convert::ToUInt16(testContextInstance->DataRow[L"FemoralSignalLength"]);
			carotidAccessor->SetProperty("floatOnsets", carotidFloatOnsets);
			femoralAccessor->SetProperty("floatOnsets", femoralFloatOnsets);
			target->carotidSignal->onsetsLength = Convert::ToUInt16(testContextInstance->DataRow[L"CarotidOnsetsLength"]);
			target->femoralSignal->onsetsLength = Convert::ToUInt16(testContextInstance->DataRow[L"FemoralOnsetsLength"]);
			bool isCarotidSignalValidExpected = Convert::ToBoolean(testContextInstance->DataRow[L"IsCarotidSignalValid"]);
			bool isFemoralSignalValidExpected = Convert::ToBoolean(testContextInstance->DataRow[L"IsFemoralSignalValid"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = (bool) accessor->Invoke("CalculateQualityControls");
			Assert::AreEqual(expected, actual);
			Assert::AreEqual(isCarotidSignalValidExpected, target->isCarotidSignalValid);
			Assert::AreEqual(isFemoralSignalValidExpected, target->isFemoralSignalValid);
		}
		/// <summary>
		///A test for ValidateBeforeStore
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVValidateBeforeStore.csv", L"BizPWVValidateBeforeStore#csv", DataAccessMethod::Sequential),
			TestMethod]
		void ValidateBeforeStoreTest()
		{
			BizPWV^  target = (gcnew BizPWV());
			PrivateObject^ accessor = gcnew PrivateObject(target);
//			CrxConfigFacade::Instance()->SetDistanceMethod(false);
			CrxConfigManager::Instance->PwvSettings->PWVDistanceMethod = 1; // TBD: Replace magic number for direct method
			accessor->SetProperty("systemId", "00050");
			accessor->SetProperty("patientNumber", Convert::ToUInt32(testContextInstance->DataRow["PatientNumber"]));
			target->myPWVDirectDistance->distance = (unsigned short) 600;
			target->meanPulseWaveVelocity = Convert::ToUInt16(testContextInstance->DataRow[L"MeanPulseWaveVelocity"]);
			target->standardDeviation = Convert::ToUInt16(testContextInstance->DataRow[L"StandardDeviation"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = target->ValidateBeforeStore();
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for SaveCaptureData
		///</summary>
public: [TestMethod]
		void SaveCaptureDataTest()
		{
			BizPWV^  target = (gcnew BizPWV()); // TODO: Initialize to an appropriate value
#if 0
			PrivateObject^ accessorTonometerObserver = gcnew PrivateObject(target->tonometerDataObserver);
			PrivateObject^ accessorCuffPulseObserver = gcnew PrivateObject(target->tonometerDataObserver);
			BizBuffer^ tonometerBuffer;
			BizBuffer^ cuffBuffer;

			accessorTonometerObserver->GetProperty("buffer", tonometerBuffer); 
			accessorCuffPulseObserver->GetProperty("buffer", cuffBuffer); 

			tonometerBuffer->Append(1);
			tonometerBuffer->Append(2);
			tonometerBuffer->Append(3);
			tonometerBuffer->Append(4);
			tonometerBuffer->Append(5);
			cuffBuffer->Append(6);
			cuffBuffer->Append(7);
			cuffBuffer->Append(8);
			cuffBuffer->Append(9);
			cuffBuffer->Append(10);
#endif
			BizFacade::Instance()->SimulateCaptureOneShot();
			BizFacade::Instance()->SimulateCaptureOneShot();
			BizFacade::Instance()->SimulateCaptureOneShot();
			BizFacade::Instance()->SimulateCaptureOneShot();
			BizFacade::Instance()->SimulateCaptureOneShot();
		
			Directory::SetCurrentDirectory("C:\\Projects\\PN022BLL\\gui\\gui\\bin\\Debug"); //where the resource file is read by CRX
			bool expected = target->SaveCaptureData();
			Assert::AreEqual(expected, true);
			// Also inspect ./simulation/pwv/<date tiem now>.dat file which is written with above simulated data
		}
	};
}
