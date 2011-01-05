
#include "StdAfx.h"
#include <biz.h>
#include "StdAfx.h"
#include "StdAfx.h"
using namespace AtCor::Scor::CrossCutting::DatabaseManager;
using namespace AtCor::Scor::BusinessLogic;
using namespace CRX_DATABASE_MANAGER_NAMESPACE;
using namespace BIZ_NAMESPACE;
using namespace CRX_CONFIG_NAMESPACE;
using namespace DAL_NAMESPACE;
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
				BizPWV^  target = (gcnew BizPWV()); 
				unsigned short methodExpected = Convert::ToUInt16(testContextInstance->DataRow["MethodExpected"]);
				bool expected = Convert::ToBoolean(testContextInstance->DataRow["Expected"]); 
				bool actual;
//				CrxConfigFacade::Instance()->SetDistanceMethod(Convert::ToBoolean(testContextInstance->DataRow["Method"]));
				CrxConfigManager::Instance->PwvSettings->PWVDistanceMethod = Convert::ToUInt16(testContextInstance->DataRow["Method"]);
				target->myCarotidDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["Carotid"]);
				target->myCuffDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["Cuff"]);
				target->myPWVDirectDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["PWVDist"]);
				actual = target->ValidatePWVDistance();
				Assert::AreEqual(expected, actual);
				Assert::AreEqual(methodExpected, target->distanceMethod);
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
				CrxConfigManager::Instance->GeneralSettings->BloodPressureEntryOptions = CrxConfigConstants::GENERAL_BP_ENTRY_SPDP;
				BizPWV^  target = (gcnew BizPWV());
				PrivateObject^ accessor = gcnew PrivateObject(target);
//				CrxConfigFacade::Instance()->SetDistanceMethod(true);
				CrxConfigManager::Instance->PwvSettings->PWVDistanceMethod = 0; // TBD: Replace magic number for subtracting method
				CrxConfigManager::Instance->GeneralSettings->HeightandWeightUnit = CrxConfigConstants::GENERAL_UNIT_METRIC;
				target->heightAndWeight->heightInCentimetres = Convert::ToUInt16(testContextInstance->DataRow["HeightInCentimetres"]);
				target->bloodPressure->SP->Reading = Convert::ToUInt16(testContextInstance->DataRow["SP"]);;
				accessor->SetProperty("systemId", Convert::ToUInt32(testContextInstance->DataRow["SystemID"]));
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
				Assert::IsNotNull(target->normalRange);
				Assert::IsNotNull(target->referenceRange);
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
			Assert::AreEqual((float) BizConstants::DEFAULT_VALUE, target->referenceRangeDistance);
			Assert::AreEqual((float) BizConstants::DEFAULT_VALUE, target->referenceRangePulseWaveVelocity);
			Assert::AreEqual((String^) "", target->bloodPressureRangeTitle);
			array<float>^ normalRangeExpected = gcnew array<float>(BizConstants::NUMBER_OF_REFERENCE_RANGES);;
			array<float>^ referenceRangeExpected = gcnew array<float>(BizConstants::NUMBER_OF_REFERENCE_RANGES);;
			for (unsigned short i = 0; i < BizConstants::NUMBER_OF_REFERENCE_RANGES; i++)
			{
				normalRangeExpected[i] = BizConstants::DEFAULT_FLOAT_VALUE;
				referenceRangeExpected[i] = BizConstants::DEFAULT_FLOAT_VALUE;
			}
			CollectionAssert::AreEqual(normalRangeExpected, target->normalRange);
			CollectionAssert::AreEqual(referenceRangeExpected, target->referenceRange);
		}
		/// <summary>
		///A test for Initialise
		///</summary>
public: [TestMethod]
		void InitialiseTest()
		{
			BizPatient::Instance()->Initialise();
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
			Assert::AreEqual((unsigned int) 0, target->systemId);
			Assert::AreEqual((unsigned int) 0, target->patientNumber);
			Assert::AreEqual((unsigned int) 0, target->groupStudyId);
			Assert::IsNotNull(target->measurementDateTime);
			Assert::AreEqual((unsigned short) 0, target->patientAge);
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
			Assert::AreEqual((unsigned short) CrxConfigConstants::GENERAL_BP_ENTRY_MPDP, target->bloodPressureEntryOption);
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
			Assert::AreEqual((unsigned int) 0, target->systemId);
			Assert::AreEqual((unsigned int) 0, target->patientNumber);
			Assert::AreEqual((unsigned int) 0, target->groupStudyId);
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
			Assert::AreEqual((unsigned short) CrxConfigConstants::GENERAL_BP_ENTRY_SPDP, target->bloodPressureEntryOption);
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
			Assert::AreEqual((unsigned int) 0, target->systemId);
			Assert::AreEqual((unsigned int) 0, target->patientNumber);
			Assert::AreEqual((unsigned int) 0, target->groupStudyId);
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
			Assert::AreEqual((unsigned short) CrxConfigConstants::GENERAL_BP_ENTRY_SPMP, target->bloodPressureEntryOption);
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
			unsigned short carotidSignalLength = Convert::ToUInt16(testContextInstance->DataRow[L"CarotidSignalLength"]);
			unsigned short femoralSignalLength = Convert::ToUInt16(testContextInstance->DataRow[L"FemoralSignalLength"]);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Signal"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< unsigned short >^ signal = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			target->carotidSignal->CaptureSignal(signal, carotidSignalLength, 0, 0);
			target->femoralSignal->CaptureSignal(signal, femoralSignalLength, 0, 0);
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
			target->distanceMethod = Convert::ToUInt16(testContextInstance->DataRow["Method"]);
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
			target->systemId = 00050;
			target->patientNumber = 1;
			CrxConfigManager::Instance->PwvSettings->PWVDistanceMethod = 1; // TBD: Replace magic number for direct method
			unsigned short signalLength = Convert::ToUInt16(testContextInstance->DataRow[L"SignalLength"]);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"CarotidSignal"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< unsigned short >^ carotidSignal = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			values = Convert::ToString(testContextInstance->DataRow[L"FemoralSignal"]);
			valuesArray = values->Split(',');
			cli::array< unsigned short >^ femoralSignal = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			target->carotidSignal->CaptureSignal(carotidSignal, signalLength, 0, 0);
			target->femoralSignal->CaptureSignal(femoralSignal, signalLength, 0, 0);
			target->myPWVDirectDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["DirectDistance"]);
			target->correctionTime = Convert::ToSingle(testContextInstance->DataRow["CorrectionTime"]);
			BizPatient::Instance()->dateOfBirth = Convert::ToDateTime(testContextInstance->DataRow["DateOfBirth"]);
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
			CrxConfigManager::Instance->PwvSettings->PWVDistanceMethod = 1; // TBD: Replace magic number for direct method
			target->systemId = 00050;
			target->patientNumber =  Convert::ToUInt32(testContextInstance->DataRow["PatientNumber"]);
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
		/// <summary>
		///A test for CalculateAge
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVCalculateAge.csv", L"BizPWVCalculateAge#csv", DataAccessMethod::Sequential),
			TestMethod]
		void CalculateAgeTest()
		{
			BizPWV^  target = (gcnew BizPWV());
			PrivateObject^ accessor = gcnew PrivateObject(target);
			BizPatient::Instance()->dateOfBirth = Convert::ToDateTime(testContextInstance->DataRow["DateOfBirth"]);
			target->measurementDateTime = Convert::ToDateTime(testContextInstance->DataRow["MeasurementDateTime"]);
			unsigned short patientAgeExpected = Convert::ToUInt16(testContextInstance->DataRow[L"PatientAgeExpected"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = (bool) accessor->Invoke("CalculateAge");
			Assert::AreEqual(expected, actual);
			Assert::AreEqual(patientAgeExpected, target->patientAge);
		}
		/// <summary>
		///A test for CalculateNormalRange
		///</summary>
public: [TestMethod]
		void CalculateNormalRangeTest()
		{
			BizPWV^  target = (gcnew BizPWV());
			PrivateObject^ accessor = gcnew PrivateObject(target);
			array<float>^ normalRangeExpected = {(float) 7.6180000,(float) 7.6373000,(float) 7.6591997,(float) 7.6836996,(float) 7.7107997,
												(float) 7.7405000,(float) 7.7728000,(float) 7.8076997,(float) 7.8452001,(float) 7.8852997,
												(float) 7.9280000,(float) 7.9733000,(float) 8.0212002,(float) 8.0717001,(float) 8.1247997,
												(float) 8.1805000,(float) 8.2388000,(float) 8.2996998,(float) 8.3632002,(float) 8.4292994,
												(float) 8.4980001,(float) 8.5692997,(float) 8.6431999,(float) 8.7196999,(float) 8.7987995,
												(float) 8.8804998,(float) 8.9647999,(float) 9.0516996,(float) 9.1412001,(float) 9.2333002,
												(float) 9.3280001,(float) 9.4252996,(float) 9.5251999,(float) 9.6276999,(float) 9.7327995,
												(float) 9.8404999,(float) 9.9507999,(float) 10.063700,(float) 10.179200,(float) 10.297299,
												(float) 10.418000,(float) 10.541300,(float) 10.667200,(float) 10.795700,(float) 10.926800,
												(float) 11.060500,(float) 11.196800,(float) 11.335700,(float) 11.477200,(float) 11.621300,
												(float) 11.768000,(float) 11.917300,(float) 12.069200,(float) 12.223700,(float) 12.380799,
												(float) 12.540500,(float) 12.702800,(float) 12.867700,(float) 13.035200,(float) 13.205299,
												(float) 13.377999,(float) 13.553300,(float) 13.731200,(float) 13.911699,(float) 14.094800,
												(float) 14.280499,(float) 14.468800,(float) 14.659699,(float) 14.853200,(float) 15.049300,(float) 15.248000};
			accessor->Invoke("CalculateNormalRange");
			CollectionAssert::AreEqual(normalRangeExpected, target->normalRange);
		}
		/// <summary>
		///A test for CalculateReferenceRange
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVCalculateReferenceRange.csv", L"BizPWVCalculateReferenceRange#csv", DataAccessMethod::Sequential),
			TestMethod]
		void CalculateReferenceRangeTest()
		{
			CrxConfigManager::Instance->GeneralSettings->BloodPressureEntryOptions = Convert::ToUInt16(testContextInstance->DataRow[L"BloodPressureEntryOption"]);
			BizPWV^  target = (gcnew BizPWV());
			PrivateObject^ accessor = gcnew PrivateObject(target);
			target->meanCorrectedTime = 50;
			if ( CrxConfigManager::Instance->GeneralSettings->BloodPressureEntryOptions != CrxConfigConstants::GENERAL_BP_ENTRY_MPDP )
			{
				target->bloodPressure->SP->Reading = Convert::ToUInt16(testContextInstance->DataRow[L"SP"]);
			}
			target->distanceMethod = Convert::ToUInt16(testContextInstance->DataRow[L"DistanceMethod"]);
			target->calculatedDistance = Convert::ToUInt16(testContextInstance->DataRow["CalculatedDistance"]);
			target->heightAndWeight->heightInCentimetres = Convert::ToUInt16(testContextInstance->DataRow["HeightInCentimetres"]);
			String^ bloodPressureRangeExpected = Convert::ToString(testContextInstance->DataRow[L"BloodPressureRangeExpected"]);
			float referenceRangeDistanceExpected = Convert::ToSingle(testContextInstance->DataRow[L"ReferenceRangeDistanceExpected"]);
			float referenceRangePulseWaveVelocityExpected = Convert::ToSingle(testContextInstance->DataRow[L"ReferenceRangePulseWaveVelocityExpected"]);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"ReferenceRangeExpected"]);
			array<String^>^ valuesArray = values->Split(',');
			cli::array< float >^ referenceRangeExpected = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual = (bool) accessor->Invoke("CalculateReferenceRange");
			Assert::AreEqual(expected, actual);
			Assert::AreEqual(bloodPressureRangeExpected, target->bloodPressureRangeTitle);
			Assert::AreEqual(referenceRangeDistanceExpected, target->referenceRangeDistance);
			Assert::AreEqual(referenceRangePulseWaveVelocityExpected, target->referenceRangePulseWaveVelocity);
			CollectionAssert::AreEqual(referenceRangeExpected, target->referenceRange);
		}
		/// <summary>
		///A test for CaptureSignals
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVCaptureSignals.csv", L"BizPWVCaptureSignals#csv", DataAccessMethod::Sequential),
			TestMethod]
		void CaptureSignalsTest()
		{
			BizPWV^ target = gcnew BizPWV();
			unsigned short carotidSize = Convert::ToUInt16(testContextInstance->DataRow[L"CarotidSize"]);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"CarotidInput"]);
			array<String^>^ valuesArray = values->Split(',');;
			cli::array< unsigned short >^  carotidInput = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			for ( unsigned short i = 0; i < carotidSize; i++ )
			{
				DalEventContainer::Instance->OnDalTonometerDataEvent(DalEventContainer::Instance, gcnew DalTonometerDataEventArgs(carotidInput[i]));
			}
			unsigned short femoralSize = Convert::ToUInt16(testContextInstance->DataRow[L"FemoralSize"]);
			values = Convert::ToString(testContextInstance->DataRow[L"FemoralInput"]);
			valuesArray = values->Split(',');;
			cli::array< unsigned short >^  femoralInput = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			for ( unsigned short i = 0; i < femoralSize; i++ )
			{
				DalEventContainer::Instance->OnDalCuffPulseEvent(DalEventContainer::Instance, gcnew DalCuffPulseEventArgs(femoralInput[i]));
			}
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = target->CaptureSignals();
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for Store
		///</summary>
public: [TestMethod]
		void StoreTest()
		{
			BizPWV^  target = (gcnew BizPWV());
			PrivateObject^ accessor = gcnew PrivateObject(target);
			CrxStructPWVMeasurementData^  record = nullptr; 

			// unsuccessful cases
			bool expected = false;
			bool actual = target->Store(record);
			Assert::AreEqual(expected, actual);

			actual = target->BizMeasure::Store(record);
			Assert::AreEqual(expected, actual);
			
			actual = target->bloodPressure->Store(record);
			Assert::AreEqual(expected, actual);
			
			actual = target->heightAndWeight->Store(record);
			Assert::AreEqual(expected, actual);
			
			actual = target->carotidSignal->Store(record, CAROTID_SIGNAL );
			Assert::AreEqual(expected, actual);
			
			actual = target->femoralSignal->Store(record, FEMORAL_SIGNAL );
			Assert::AreEqual(expected, actual);
			
			record = gcnew CrxStructPWVMeasurementData();

			// unsuccessful case
			target->meanPulseWaveVelocity = MIN_ADULT_PWV - 1;
			target->standardDeviation = HIGH_STANDARD_DEVIATION * target->meanPulseWaveVelocity;
			expected = false;
			actual = target->Store(record);
			Assert::AreEqual(expected, actual);
			
			// successful case
			target->meanPulseWaveVelocity = MIN_ADULT_PWV;
			target->standardDeviation = HIGH_STANDARD_DEVIATION * target->meanPulseWaveVelocity;
			expected = true;
			actual = target->Store(record);
			Assert::AreEqual(expected, actual);
			Assert::AreEqual(target->bloodPressure->SP->Reading, (unsigned short) record->SP);
			Assert::AreEqual(target->bloodPressure->DP->Reading, (unsigned short) record->DP);
			Assert::AreEqual(target->bloodPressure->MP->Reading, (unsigned short) record->MP);
			Assert::AreEqual(target->bloodPressureEntryOption, (unsigned short) record->BloodPressureEntryOption);
			Assert::AreEqual(target->bloodPressureRangeTitle, record->BloodPressureRange);
			Assert::AreEqual(target->heightAndWeight->heightInCentimetres, (unsigned short) record->HeightInCentimetres);
			Assert::AreEqual(target->heightAndWeight->heightInInches, (unsigned short) record->HeightInInches);
			Assert::AreEqual(target->heightAndWeight->weightInKilograms, (unsigned short) record->WeightInKilograms);
			Assert::AreEqual(target->heightAndWeight->weightInPounds, (unsigned short) record->WeightInPounds);
			Assert::AreEqual(target->heightAndWeight->bodyMassIndex, record->BodyMassIndex);
			Assert::AreEqual(target->systemId, (unsigned int) record->SystemIdentifier);
			Assert::AreEqual(target->groupStudyId, (unsigned int) record->GroupIdentifier);
			Assert::AreEqual(target->patientNumber, (unsigned int) record->PatientNumberInternal);
			Assert::AreEqual(target->measurementDateTime, record->StudyDateTime);
			Assert::AreEqual(target->dataRevision, (unsigned short) record->DataRevision);
			Assert::AreEqual(target->patientAge, (unsigned short) record->Age);
			Assert::AreEqual(target->notes, record->Notes);
			Assert::AreEqual(target->operatorId, record->Operator);
			Assert::AreEqual(target->captureTime, (unsigned short) record->CaptureTime);
			Assert::AreEqual(target->sampleRate, (unsigned short) record->SampleRate);
			Assert::AreEqual(target->simulation, record->Simulation);
			Assert::AreEqual(target->myCarotidDistance->distance, (unsigned short) record->Carotid);
			Assert::AreEqual(target->myCuffDistance->distance, (unsigned short) record->Cuff);
			Assert::AreEqual(target->myFemoral2CuffDistance->distance, (unsigned short) record->FemoraltoCuff);
			Assert::AreEqual(target->myPWVDirectDistance->distance, (unsigned short) record->Direct);
			Assert::AreEqual(target->calculatedDistance, (unsigned short) record->PWVDistance);
			Assert::AreEqual(target->distanceMethod, (unsigned short) record->PWVDistanceMethod);
			Assert::AreEqual(target->correctionTime, record->CorrectionTime);
			Assert::AreEqual(target->carotidSignal->signalLength, (unsigned short) record->CarotidSignalLength);
			CollectionAssert::AreEqual(target->carotidSignal->signal, record->CarotidSignal);
			Assert::AreEqual(target->carotidSignal->onsetsLength, (unsigned short) record->CarotidSignalOnSetsLength);
			CollectionAssert::AreEqual(target->carotidSignal->floatOnsets, record->CarotidSignalFloatOnSets);
			Assert::AreEqual(target->carotidSignal->pulseHeight, record->CarotidSignalPulseHeight);
			Assert::AreEqual(target->carotidSignal->pulseHeightVariation, record->CarotidSignalPulseHeightVariation);
			Assert::AreEqual(target->femoralSignal->signalLength, (unsigned short) record->FemoralSignalLength);
			CollectionAssert::AreEqual(target->femoralSignal->signal, record->FemoralSignal);
			Assert::AreEqual(target->femoralSignal->onsetsLength, (unsigned short) record->FemoralSignalOnSetsLength);
			CollectionAssert::AreEqual(target->femoralSignal->floatOnsets, record->FemoralSignalFloatOnSets);
			Assert::AreEqual(target->femoralSignal->pulseHeight, record->FemoralSignalPulseHeight);
			Assert::AreEqual(target->femoralSignal->pulseHeightVariation, record->FemoralSignalPulseHeightVariation);
			Assert::AreEqual(target->isFemoralSignalValid, record->IsFemoralSignalValid);
			Assert::AreEqual(target->isCarotidSignalValid, record->IsCarotidSignalValid);
			Assert::AreEqual(target->numberOfDeltas, (unsigned short) record->NumberOfDeltas);
			Assert::AreEqual(target->numberOfValidDeltas, (unsigned short) record->NumberOfValidDeltas);
			Assert::AreEqual(target->meanHeartRate, record->MeanHeartRate);
			Assert::AreEqual(target->meanDeltaTime, record->MeanDeltaTime);
			Assert::AreEqual(target->meanCorrectedTime, record->MeanCorrectedTime);
			Assert::AreEqual(target->meanPulseWaveVelocity, record->MeanPulseWaveVelocity);
			Assert::AreEqual(target->standardDeviation, record->StandardDeviation);
			Assert::AreEqual(target->isStandardDeviationValid, record->IsStandardDeviationValid);
			Assert::AreEqual(target->referenceRangeDistance, record->ReferenceRangeDistance);
			Assert::AreEqual(target->referenceRangePulseWaveVelocity, record->ReferenceRangePulseWaveVelocity);
			CollectionAssert::AreEqual(target->normalRange, record->NormalRange);
			CollectionAssert::AreEqual(target->referenceRange, record->ReferenceRange);			
		}
		/// <summary>
		///A test for IncrementMeasurementCounter
		///</summary>
public: [TestMethod]
		void IncrementMeasurementCounterTest()
		{
			BizPWV^  target = (gcnew BizPWV());

			// successful case
			DalModule::Instance->measurementCounterTest = true;
			bool expected = true;
			bool actual;
			actual = target->IncrementMeasurementCounter();
			Assert::AreEqual(expected, actual);

			// unsuccessful case
			DalModule::Instance->measurementCounterTest = false;
			expected = false;
			actual = target->IncrementMeasurementCounter();
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for CalculatePWVReport
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVCalculatePWVReport.csv", L"BizPWVCalculatePWVReport#csv", DataAccessMethod::Sequential),
			TestMethod]
		void CalculatePWVReportTest()
		{
			BizPatient::Instance()->systemId = 00050;
			BizPatient::Instance()->patientNumber = 1;
			BizPatient::Instance()->dateOfBirth = DateTime(1978, 05, 14);
			CrxConfigManager::Instance->PwvSettings->PWVDistanceMethod = 1; // TBD: Replace magic number for direct method
			BizPWV^  target = (gcnew BizPWV());
			CrxStructPWVMeasurementData^  record = gcnew CrxStructPWVMeasurementData();
			target->myPWVDirectDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["DirectDistance"]);
			unsigned short carotidSize = Convert::ToUInt16(testContextInstance->DataRow[L"CarotidSize"]);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"CarotidInput"]);
			array<String^>^ valuesArray = values->Split(',');;
			cli::array< unsigned short >^  carotidInput = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			for ( unsigned short i = 0; i < carotidSize; i++ )
			{
				DalEventContainer::Instance->OnDalTonometerDataEvent(DalEventContainer::Instance, gcnew DalTonometerDataEventArgs(carotidInput[i]));
			}
			unsigned short femoralSize = Convert::ToUInt16(testContextInstance->DataRow[L"FemoralSize"]);
			values = Convert::ToString(testContextInstance->DataRow[L"FemoralInput"]);
			valuesArray = values->Split(',');;
			cli::array< unsigned short >^  femoralInput = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			for ( unsigned short i = 0; i < femoralSize; i++ )
			{
				DalEventContainer::Instance->OnDalCuffPulseEvent(DalEventContainer::Instance, gcnew DalCuffPulseEventArgs(femoralInput[i]));
			}
			DalModule::Instance->measurementCounterTest = Convert::ToBoolean(testContextInstance->DataRow[L"ModuleConnected"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;
			actual = target->CalculatePWVReport(record);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for RecalculatePWVReport
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizPWVRecalculatePWVReport.csv", L"BizPWVRecalculatePWVReport#csv", DataAccessMethod::Sequential),
			TestMethod]
		void RecalculatePWVReportTest()
		{
			BizPatient::Instance()->systemId = 00050;
			BizPatient::Instance()->patientNumber = 1;
			BizPatient::Instance()->dateOfBirth = DateTime(1978, 05, 14);
			CrxConfigManager::Instance->PwvSettings->PWVDistanceMethod = 1; // TBD: Replace magic number for direct method
			BizPWV^  target = (gcnew BizPWV());
			CrxStructPWVMeasurementData^  record = gcnew CrxStructPWVMeasurementData();
			target->myPWVDirectDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["DirectDistance"]);
			unsigned short carotidSize = Convert::ToUInt16(testContextInstance->DataRow[L"CarotidSize"]);
			String^ values = Convert::ToString(testContextInstance->DataRow[L"CarotidInput"]);
			array<String^>^ valuesArray = values->Split(',');;
			cli::array< unsigned short >^  carotidInput = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			for ( unsigned short i = 0; i < carotidSize; i++ )
			{
				DalEventContainer::Instance->OnDalTonometerDataEvent(DalEventContainer::Instance, gcnew DalTonometerDataEventArgs(carotidInput[i]));
			}
			unsigned short femoralSize = Convert::ToUInt16(testContextInstance->DataRow[L"FemoralSize"]);
			values = Convert::ToString(testContextInstance->DataRow[L"FemoralInput"]);
			valuesArray = values->Split(',');;
			cli::array< unsigned short >^  femoralInput = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			for ( unsigned short i = 0; i < femoralSize; i++ )
			{
				DalEventContainer::Instance->OnDalCuffPulseEvent(DalEventContainer::Instance, gcnew DalCuffPulseEventArgs(femoralInput[i]));
			}
			target->CaptureSignals();
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
			bool actual;actual = target->RecalculatePWVReport(record);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for Populate
		///</summary>
public: [TestMethod]
		void PopulateTest()
		{
			BizPWV^  target = (gcnew BizPWV());
			CrxStructPWVMeasurementData^  record = nullptr; 

			// unsuccessful cases
			bool expected = false;
			bool actual = target->Populate(record);
			Assert::AreEqual(expected, actual);

			actual = target->BizMeasure::Populate(record);
			Assert::AreEqual(expected, actual);
			
			actual = target->bloodPressure->Populate(record);
			Assert::AreEqual(expected, actual);
			
			actual = target->heightAndWeight->Populate(record);
			Assert::AreEqual(expected, actual);
			
			actual = target->carotidSignal->Populate(record, CAROTID_SIGNAL );
			Assert::AreEqual(expected, actual);
			
			actual = target->femoralSignal->Populate(record, FEMORAL_SIGNAL );
			Assert::AreEqual(expected, actual);
			
			record = gcnew CrxStructPWVMeasurementData();

			// successful case
			expected = true;
			actual = target->Populate(record);
			Assert::AreEqual(expected, actual);
			Assert::AreEqual(target->bloodPressure->SP->Reading, (unsigned short) record->SP);
			Assert::AreEqual(target->bloodPressure->DP->Reading, (unsigned short) record->DP);
			Assert::AreEqual(target->bloodPressure->MP->Reading, (unsigned short) record->MP);
			Assert::AreEqual(target->bloodPressureEntryOption, (unsigned short) record->BloodPressureEntryOption);
			Assert::AreEqual(target->bloodPressureRangeTitle, record->BloodPressureRange);
			Assert::AreEqual(target->heightAndWeight->heightInCentimetres, (unsigned short) record->HeightInCentimetres);
			Assert::AreEqual(target->heightAndWeight->heightInInches, (unsigned short) record->HeightInInches);
			Assert::AreEqual(target->heightAndWeight->weightInKilograms, (unsigned short) record->WeightInKilograms);
			Assert::AreEqual(target->heightAndWeight->weightInPounds, (unsigned short) record->WeightInPounds);
			Assert::AreEqual(target->heightAndWeight->bodyMassIndex, record->BodyMassIndex);
			Assert::AreEqual(target->systemId, (unsigned int) record->SystemIdentifier);
			Assert::AreEqual(target->groupStudyId, (unsigned int) record->GroupIdentifier);
			Assert::AreEqual(target->patientNumber, (unsigned int) record->PatientNumberInternal);
			Assert::AreEqual(target->measurementDateTime, record->StudyDateTime);
			Assert::AreEqual(target->dataRevision, (unsigned short) record->DataRevision);
			Assert::AreEqual(target->patientAge, (unsigned short) record->Age);
			Assert::AreEqual(target->notes, record->Notes);
			Assert::AreEqual(target->operatorId, record->Operator);
			Assert::AreEqual(target->captureTime, (unsigned short) record->CaptureTime);
			Assert::AreEqual(target->sampleRate, (unsigned short) record->SampleRate);
			Assert::AreEqual(target->simulation, record->Simulation);
			Assert::AreEqual(target->myCarotidDistance->distance, (unsigned short) record->Carotid);
			Assert::AreEqual(target->myCuffDistance->distance, (unsigned short) record->Cuff);
			Assert::AreEqual(target->myFemoral2CuffDistance->distance, (unsigned short) record->FemoraltoCuff);
			Assert::AreEqual(target->myPWVDirectDistance->distance, (unsigned short) record->Direct);
			Assert::AreEqual(target->calculatedDistance, (unsigned short) record->PWVDistance);
			Assert::AreEqual(target->distanceMethod, (unsigned short) record->PWVDistanceMethod);
			Assert::AreEqual(target->correctionTime, record->CorrectionTime);
			Assert::AreEqual(target->carotidSignal->signalLength, (unsigned short) record->CarotidSignalLength);
			CollectionAssert::AreEqual(target->carotidSignal->signal, record->CarotidSignal);
			Assert::AreEqual(target->carotidSignal->onsetsLength, (unsigned short) record->CarotidSignalOnSetsLength);
			CollectionAssert::AreEqual(target->carotidSignal->floatOnsets, record->CarotidSignalFloatOnSets);
			Assert::AreEqual(target->carotidSignal->pulseHeight, record->CarotidSignalPulseHeight);
			Assert::AreEqual(target->carotidSignal->pulseHeightVariation, record->CarotidSignalPulseHeightVariation);
			Assert::AreEqual(target->femoralSignal->signalLength, (unsigned short) record->FemoralSignalLength);
			CollectionAssert::AreEqual(target->femoralSignal->signal, record->FemoralSignal);
			Assert::AreEqual(target->femoralSignal->onsetsLength, (unsigned short) record->FemoralSignalOnSetsLength);
			CollectionAssert::AreEqual(target->femoralSignal->floatOnsets, record->FemoralSignalFloatOnSets);
			Assert::AreEqual(target->femoralSignal->pulseHeight, record->FemoralSignalPulseHeight);
			Assert::AreEqual(target->femoralSignal->pulseHeightVariation, record->FemoralSignalPulseHeightVariation);
			Assert::AreEqual(target->isFemoralSignalValid, record->IsFemoralSignalValid);
			Assert::AreEqual(target->isCarotidSignalValid, record->IsCarotidSignalValid);
			Assert::AreEqual(target->numberOfDeltas, (unsigned short) record->NumberOfDeltas);
			Assert::AreEqual(target->numberOfValidDeltas, (unsigned short) record->NumberOfValidDeltas);
			Assert::AreEqual(target->meanHeartRate, record->MeanHeartRate);
			Assert::AreEqual(target->meanDeltaTime, record->MeanDeltaTime);
			Assert::AreEqual(target->meanCorrectedTime, record->MeanCorrectedTime);
			Assert::AreEqual(target->meanPulseWaveVelocity, record->MeanPulseWaveVelocity);
			Assert::AreEqual(target->standardDeviation, record->StandardDeviation);
			Assert::AreEqual(target->isStandardDeviationValid, record->IsStandardDeviationValid);
			Assert::AreEqual(target->referenceRangeDistance, record->ReferenceRangeDistance);
			Assert::AreEqual(target->referenceRangePulseWaveVelocity, record->ReferenceRangePulseWaveVelocity);
			CollectionAssert::AreEqual(target->normalRange, record->NormalRange);
			CollectionAssert::AreEqual(target->referenceRange, record->ReferenceRange);	
		}
};
}
