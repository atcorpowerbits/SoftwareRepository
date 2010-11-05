
#include "StdAfx.h"

using namespace System;
using namespace System::IO;// For FileStream
using namespace System::Xml;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting::Configuration;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::DataAccess;

namespace TestCrx {
    using namespace System;
    ref class CrxConfigManagerTest;
    
    
    /// <summary>
///This is a test class for CrxConfigManagerTest and is intended
///to contain all CrxConfigManagerTest Unit Tests
///</summary>
	[TestClass]
	public ref class CrxConfigManagerTest
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

			//Smarajit Mishra
			//Customized function to Set the path
			void SetPath()
			{
				String^ path = Directory::GetCurrentDirectory(); 
				Directory::SetCurrentDirectory("D:\\Atcor_2008\\Deepak\\Sprint1-Scor-Code\\Scor\\TestResults");
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
			///A test for PwvSettings
			///</summary>
	public: [TestMethod]
			void PwvSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructPwvSetting^  expected = nullptr; // TODO: Initialize to an appropriate value
				CrxStructPwvSetting^  actual;
				target->PwvSettings = expected;
				actual = target->PwvSettings;
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for Instance
			///</summary>
	public: [TestMethod]
			void InstanceTest()
			{
				CrxConfigManager^  actual;
				actual = CrxConfigManager::Instance;
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for GeneralSettings
			///</summary>
	public: [TestMethod]
			void GeneralSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructGeneralSetting^  expected = nullptr; // TODO: Initialize to an appropriate value
				CrxStructGeneralSetting^  actual;
				target->GeneralSettings = expected;
				actual = target->GeneralSettings;
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for SetSimulationType
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetSimulationTypeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//target->SetSimulationType(ps, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetSettingsNode
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetSettingsNodeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				String^  Section = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
				CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetSettingsNode(Section, SubSection, gs, ps, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetSettings
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				String^  Section = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
				CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetSettings(Section, SubSection, gs, ps);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetReportTitle
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetReportTitleTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetReportTitle(gs, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetReportLogoPath
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetReportLogoPathTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetReportLogoPath(gs, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetReferenceRange
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetReferenceRangeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetReferenceRange(ps, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetPwvUserSettings
			///</summary>
	public: [TestMethod]
			void SetPwvUserSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit
				//Set the PWV User Settings by passing object
				CrxStructPwvSetting^  ps = gcnew CrxStructPwvSetting();
				CrxConfigManagerTest::SetPath();

				ps->PWVDistanceMethod = 0;
				ps->FemoralToCuff = true;
				ps->PWVDistanceUnits = 0;
				ps->CaptureTime = 0;
				ps->ReferenceRange = true;
				ps->SimulationType = "Default";

				target->SetPwvUserSettings(ps);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetPwvSettingsNode
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetPwvSettingsNodeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructPwvSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetPwvSettingsNode(gs, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetPwvDistanceUnits
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetPwvDistanceUnitsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetPwvDistanceUnits(ps, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetPwvDistanceMethods
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetPwvDistanceMethodsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetPwvDistanceMethods(ps, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetPatientPrivacy
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetPatientPrivacyTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetPatientPrivacy(gs, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetHeightWeight
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetHeightWeightTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//target->SetHeightWeight(gs, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetGeneralUserSettings
			///</summary>
	public: [TestMethod]
			void SetGeneralUserSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				CrxStructGeneralSetting^  gs = gcnew CrxStructGeneralSetting();
				CrxConfigManagerTest::SetPath();

				gs->BloodPressureEntryOptions = 1;
				gs->CommsPort = "Simulation";
				gs->HeightandWeightUnit= 1;
				gs->PatientPrivacy = false;
				gs->ReportLogoPath = "D:\\EXTRA_DESKTOP\\ERROR.JPG";
				gs->ReportTitle = "REPORT DEM TESTFORme";

				target->SetGeneralUserSettings(gs);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetGeneralSettingsNode
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetGeneralSettingsNodeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetGeneralSettingsNode(gs, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetFemoralToCuff
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetFemoralToCuffTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetFemoralToCuff(ps, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetCommsPort
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetCommsPortTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetCommsPort(gs, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetCaptureTime
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetCaptureTimeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				///target->SetCaptureTime(ps, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetBloodPressureOption
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void SetBloodPressureOptionTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
				XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetBloodPressureOption(gs, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
// This tests the assigment operator which is private and blank implmentation
// we do not need to test this as of now: 11/02/2010: Smarajit Mishra

	//		/// <summary>
	//		///A test for op_Assign
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void op_AssignTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxConfigManager^  unnamed = nullptr; // TODO: Initialize to an appropriate value
	//			CrxConfigManager^  expected = nullptr; // TODO: Initialize to an appropriate value
	//			CrxConfigManager^  actual;
	//			actual = (target = unnamed);
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}
			/// <summary>
			///A test for GetSimulationType
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetSimulationTypeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				//target->GetSimulationType(SubSection, ReaderValue);

				target->GetSimulationType("USER", "Simulation1");
				Assert::AreEqual("Simulation1", target->_instance->PwvSettings->SimulationType);
				
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetSettingsNode
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetSettingsNodeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				String^  Section = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  SubSectionNode = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				target->GetSettingsNode(Section, SubSection, SubSectionNode, ReaderValue);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetSettings
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				//String^  Section = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//target->GetSettings(Section, SubSection);
				target->GetSettings("GENERAL", "USER");

				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetReportTitle
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetReportTitleTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				
				//target->GetReportTitle(SubSection, ReaderValue);

				target->GetReportTitle("USER", "ReportTitle2");
				Assert::AreEqual("ReportTitle2", target->_instance->GeneralSettings->ReportTitle);
				
				
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetReportLogoPath
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetReportLogoPathTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				//target->GetReportLogoPath(SubSection, ReaderValue);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
				target->GetReportLogoPath("USER", "D:\\EXTRA_DESKTOP\\ERROR.JPG");
				Assert::AreEqual("D:\\EXTRA_DESKTOP\\ERROR.JPG", target->_instance->GeneralSettings->ReportLogoPath);
			}
			/// <summary>
			///A test for GetReferenceRange
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetReferenceRangeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  SubSection = L"USER";
				String^  ReaderValue = L"No";

				target->GetReferenceRange("USER","NO");
				Assert::AreEqual(false, target->_instance->PwvSettings->ReferenceRange);

				target->GetReferenceRange("USER","Yes");
				Assert::AreEqual(true, target->_instance->PwvSettings->ReferenceRange);

				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetPwvUserSettings
			///</summary>
	public: [TestMethod]
			void GetPwvUserSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				CrxConfigManagerTest::SetPath();
				target->GetPwvUserSettings();

				Assert::AreEqual(0, target->_instance->PwvSettings->PWVDistanceMethod);
				Assert::AreEqual(true, target->_instance->PwvSettings->FemoralToCuff);
				Assert::AreEqual(0, target->_instance->PwvSettings->PWVDistanceUnits);
				Assert::AreEqual(0, target->_instance->PwvSettings->CaptureTime);
				Assert::AreEqual(true, target->_instance->PwvSettings->ReferenceRange);
				Assert::AreEqual("Default", target->_instance->PwvSettings->SimulationType);

				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetPwvSettingsNode
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPwvSettingsNodeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  SubSectionNode = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				//target->GetPwvSettingsNode(SubSection, SubSectionNode, ReaderValue);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetPwvDistanceUnits
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPwvDistanceUnitsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  SubSection = L"USER";
				String^  ReaderValue = L"mm";

				target->GetPwvDistanceUnits(SubSection, ReaderValue);
				Assert::AreEqual(0, target->_instance->PwvSettings->PWVDistanceUnits);

				target->GetPwvDistanceUnits("USER","cm");
				Assert::AreEqual(1, target->_instance->PwvSettings->PWVDistanceUnits);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetPwvDistanceMethods
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPwvDistanceMethodsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  SubSection = L"USER";
				String^  ReaderValue = L"Subtracting";

				target->GetPwvDistanceMethods(SubSection, ReaderValue);
				Assert::AreEqual(0, target->_instance->PwvSettings->PWVDistanceMethod);

				target->GetPwvDistanceMethods("USER","DIRECT");
				Assert::AreEqual(1, target->_instance->PwvSettings->PWVDistanceMethod);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetPwvDefaultSettings
			///</summary>
	public: [TestMethod]
			void GetPwvDefaultSettingsTest()
			{

				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//CrxStructPwvSetting^  objPwvSettings = nullptr; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				CrxStructPwvSetting^ objPwvSettings = gcnew CrxStructPwvSetting();
				CrxConfigManagerTest::SetPath();
				target->GetPwvDefaultSettings(objPwvSettings);
				
				Assert::AreEqual(0, objPwvSettings->PWVDistanceMethod);
				Assert::AreEqual(true, objPwvSettings->FemoralToCuff);
				Assert::AreEqual(0, objPwvSettings->PWVDistanceUnits);
				Assert::AreEqual(0, objPwvSettings->CaptureTime);
				Assert::AreEqual(true, objPwvSettings->ReferenceRange);
				Assert::AreEqual("Default Simulation file", objPwvSettings->SimulationType);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetPatientPrivacy
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPatientPrivacyTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  SubSection = L"USER";
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  ReaderValue = L"YES";

				target->GetPatientPrivacy("USER","NO");
				Assert::AreEqual(false, target->_instance->GeneralSettings->PatientPrivacy);

				target->GetPatientPrivacy("USER","Yes");
				Assert::AreEqual(true, target->_instance->GeneralSettings->PatientPrivacy);
				

				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetHeightWeight
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetHeightWeightTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				//target->GetHeightWeight(SubSection, ReaderValue);
				//Smarajit Mishra
				//Pass the required inout to get the expected result

				target->GetHeightWeight("USER", "METRIC");
				Assert::AreEqual(0, target->_instance->GeneralSettings->HeightandWeightUnit);
				
				target->GetHeightWeight("USER", "IMPERIAL");
				Assert::AreEqual(1, target->_instance->GeneralSettings->HeightandWeightUnit);

				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetGeneralUserSettings
			///</summary>
	public: [TestMethod]
			void GetGeneralUserSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				CrxConfigManagerTest::SetPath();
				target->GetGeneralUserSettings();

				Assert::AreEqual(1, target->_instance->GeneralSettings->BloodPressureEntryOptions);
				Assert::AreEqual(1, target->_instance->GeneralSettings->HeightandWeightUnit);
				Assert::AreEqual(false, target->_instance->GeneralSettings->PatientPrivacy);
				Assert::AreEqual("Simulation", target->_instance->GeneralSettings->CommsPort);
				Assert::AreEqual("REPORT DEM TESTFORme", target->_instance->GeneralSettings->ReportTitle);
				Assert::AreEqual("D:\\EXTRA_DESKTOP\\ERROR.JPG", target->_instance->GeneralSettings->ReportLogoPath);

				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetGeneralSettingsNode
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetGeneralSettingsNodeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  SubSectionNode = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				//target->GetGeneralSettingsNode(SubSection, SubSectionNode, ReaderValue);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetGeneralDefaultSettings
			///</summary>
	public: [TestMethod]
			void GetGeneralDefaultSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//CrxStructGeneralSetting^  objGenSettings; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				CrxStructGeneralSetting^ objGenSettings = gcnew CrxStructGeneralSetting();
				CrxConfigManagerTest::SetPath();

				target->GetGeneralDefaultSettings(objGenSettings);

				Assert::AreEqual(0, objGenSettings->BloodPressureEntryOptions);
				Assert::AreEqual(0, objGenSettings->HeightandWeightUnit);
				Assert::AreEqual(true, objGenSettings->PatientPrivacy);
				Assert::AreEqual(nullptr, objGenSettings->CommsPort);
				Assert::AreEqual(nullptr, objGenSettings->ReportTitle);
				Assert::AreEqual(nullptr, objGenSettings->ReportLogoPath);


				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetFemoralToCuff
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetFemoralToCuffTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				//target->GetFemoralToCuff(SubSection, ReaderValue);
				//Smarajit Mishra
				//Pass the required inout to get the expected result

				target->GetFemoralToCuff("USER", "Yes");
				Assert::AreEqual(true,  target->_instance->PwvSettings->FemoralToCuff);

				target->GetFemoralToCuff("USER", "No");
				Assert::AreEqual(false,  target->_instance->PwvSettings->FemoralToCuff);

				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetCommsPort
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetCommsPortTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				//target->GetCommsPort(SubSection, ReaderValue);
				//Smarajit Mishra
				//Pass the required inout to get the expected result

				target->GetCommsPort("USER", "COMMS1");
				Assert::AreEqual("COMMS1",  target->_instance->GeneralSettings->CommsPort);
				
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetCaptureTime
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetCaptureTimeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				//target->GetCaptureTime(SubSection, ReaderValue);
				//Smarajit Mishra
				//Pass the required inout to get the expected result

				target->GetCaptureTime("USER", "5SECONDS");
				Assert::AreEqual(0, target->_instance->PwvSettings->CaptureTime);

				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetBloodPressureOption
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetBloodPressureOptionTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				target->GetBloodPressureOption("USER", "SPANDDP");
				Assert::AreEqual(0, target->_instance->GeneralSettings->BloodPressureEntryOptions);
				
				target->GetBloodPressureOption("USER", "SPANDMP");
				Assert::AreEqual(1, target->_instance->GeneralSettings->BloodPressureEntryOptions);

				target->GetBloodPressureOption("USER", "MPANDDP");
				Assert::AreEqual(2, target->_instance->GeneralSettings->BloodPressureEntryOptions);
								
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for CrxConfigManager Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxConfigManagerConstructorTest1()
			{
				CrxConfigManager^  unnamed = nullptr; // TODO: Initialize to an appropriate value
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor(unnamed));
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
			/// <summary>
			///A test for CrxConfigManager Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxConfigManagerConstructorTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor());
				//Smarajit Mishra				
				target->_nameOfFile = L"D:\\Atcor_2008\\Deepak\\Sprint1-Scor-Code\\Scor\\TestResults\\system\\config\\scor.config";
				//target->_nameOfFile = L"D:\\Atcor_2008\\Deepak\\Sprint1-Scor-Code\\Scor\\TestResults";

				//Create instance General Settings Structure
				target->_generalSettings = gcnew CrxStructGeneralSetting();
				
				//Create instance PWV Settings Structure
				target->_pwvSettings = gcnew CrxStructPwvSetting();

				//Create internal instance General Settings Structure
				target->_gSetInternal = gcnew CrxStructGeneralSetting();

				//Create internal instance PWV Settings Structure
				target->_pSetInternal = gcnew CrxStructPwvSetting();
			
			}
	};
}
namespace TestCrx {
    
}
