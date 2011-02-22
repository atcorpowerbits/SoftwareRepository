
#include "StdAfx.h"

using namespace System;
using namespace System::IO;// For FileStream
using namespace System::Xml;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting::Configuration;
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
	private: String^ _currDir;

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
				int i = path->IndexOf("\\TestResults");
				path = path->Substring(0,i + 12);
				Directory::SetCurrentDirectory(path);
				
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
			public: [TestInitialize]
			System::Void MyTestInitialize()
			{
				_currDir = Directory::GetCurrentDirectory(); 
			}
			
			//Use TestCleanup to run code after each test has run
			public: [TestCleanup]
			System::Void MyTestCleanup()
			{
				Directory::SetCurrentDirectory(_currDir);
			}

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
				Assert::IsNotNull(actual);
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
	//		/// <summary>
	//		///A test for SetSourceData
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetSourceDataTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			target->SetSourceData(gs, node);
	//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetPwvUserSettings
	//		/// <summary>
	//		///A test for SetSimulationType
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetSimulationTypeTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			//target->SetSimulationType(ps, node);
	//			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetPwvUserSettings/SetGeneralSettings
			///<summary>
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
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;
				Section = "GENERAL";
				SubSection = "USER";
				//Remove the set functionality becuase we don't have the proper node object for XML
				
				//smarajit				
				try
				{
					XmlDocument^ doc = gcnew XmlDocument;

					doc->LoadXml( "<root>" "<elem>some text<child/>more text</elem>" "</root>" );

					XmlNode^ elem = doc->DocumentElement->FirstChild;
										
					target->SetSettingsNode(Section, SubSection, gs, ps, elem);
				}
				catch(Exception^)
				{
					actual =0;
				}
				Assert::AreEqual (expected,actual);

				try
				{										
					target->SetSettingsNode(Section, SubSection, gs, ps, node);
				}
				catch(Exception^)
				{
					actual =0;
				}
				Assert::AreEqual (expected,actual);
				//smarajit			

				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetPwvUserSettings/SetGeneralSettings
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
				
				Section = "GENERAL";
				SubSection= "USER";
				int actual;
				int expected = 0;
				String^ path = Directory::GetCurrentDirectory(); 
				//Directory::SetCurrentDirectory("D:\\Smarajit\\AQTime\\");

				try
				{
					target->SetSettings(Section, SubSection, gs, ps);
				}
				catch(Exception^)
				{
					actual = 0;
				}
				Assert::AreEqual(expected,actual);
				//Assert::AreNotEqual
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetSettings(Section, SubSection, gs, ps);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetGeneralSettings
	//		/// <summary>
	//		///A test for SetReportTitle
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetReportTitleTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			//Smarajit Mishra
	//			//Remove the set functionality becuase we don't have the proper node object for XML
	//			//target->SetReportTitle(gs, node);
	//			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetGeneralSettings

	//		/// <summary>
	//		///A test for SetReportLogoPath
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetReportLogoPathTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			//Smarajit Mishra
	//			//Remove the set functionality becuase we don't have the proper node object for XML
	//			//target->SetReportLogoPath(gs, node);
	//			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetPwvUserSettings
	//		/// <summary>
	//		///A test for SetReferenceRange
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetReferenceRangeTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			//Smarajit Mishra
	//			//Remove the set functionality becuase we don't have the proper node object for XML
	//			//target->SetReferenceRange(ps, node);
	//			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
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
				ps->CaptureTime = 5;
				ps->ReferenceRange = true;
				ps->SimulationType = "Default";
			

				target->SetPwvUserSettings(ps);

				target->GetPwvUserSettings();

				Assert::AreEqual(0, target->_instance->PwvSettings->PWVDistanceMethod);
				Assert::AreEqual(true, target->_instance->PwvSettings->FemoralToCuff);
				Assert::AreEqual(0, target->_instance->PwvSettings->PWVDistanceUnits);
				Assert::AreEqual(5, target->_instance->PwvSettings->CaptureTime);
				Assert::AreEqual(true, target->_instance->PwvSettings->ReferenceRange);
				Assert::AreEqual("Default", target->_instance->PwvSettings->SimulationType);

				ps->PWVDistanceMethod = 1;
				ps->FemoralToCuff = false;
				ps->PWVDistanceUnits = 1;
				ps->CaptureTime = 10;
				ps->ReferenceRange = false;
				ps->SimulationType = nullptr;
			

				target->SetPwvUserSettings(ps);

				target->GetPwvUserSettings();

				Assert::AreEqual(1, target->_instance->PwvSettings->PWVDistanceMethod);
				Assert::AreEqual(false, target->_instance->PwvSettings->FemoralToCuff);
				Assert::AreEqual(1, target->_instance->PwvSettings->PWVDistanceUnits);
				Assert::AreEqual(10, target->_instance->PwvSettings->CaptureTime);
				Assert::AreEqual(false, target->_instance->PwvSettings->ReferenceRange);
				
				ps->CaptureTime = 20;

				target->SetPwvUserSettings(ps);
				target->GetPwvUserSettings();

				Assert::AreEqual(20, target->_instance->PwvSettings->CaptureTime);

				//************************//
				ps->PWVDistanceMethod = 0;
				ps->FemoralToCuff = true;
				ps->PWVDistanceUnits = 0;
				ps->CaptureTime = 5;
				ps->ReferenceRange = true;
				ps->SimulationType = "Default";
			

				target->SetPwvUserSettings(ps);

				/************************************/
				
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetPwvUserSettings

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
				int actual;
				int expected = 0;
				try
				{
					XmlDocument^ doc = gcnew XmlDocument;

					doc->LoadXml( "<root>" "<elem>some text<child/>more text</elem>" "</root>" );

					XmlNode^ elem = doc->DocumentElement->FirstChild;
										
					target->SetPwvSettingsNode(gs, elem);
				}
				catch(Exception^)
				{
					actual =0;
				}
				Assert::AreEqual (expected,actual);
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				//target->SetPwvSettingsNode(gs, node);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetPwvUserSettings

	//		/// <summary>
	//		///A test for SetPwvDistanceUnits
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetPwvDistanceUnitsTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			//Smarajit Mishra
	//			//Remove the set functionality becuase we don't have the proper node object for XML
	//			//target->SetPwvDistanceUnits(ps, node);
	//			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetPwvUserSettings

	//		/// <summary>
	//		///A test for SetPwvDistanceMethods
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetPwvDistanceMethodsTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			//Smarajit Mishra
	//			//Remove the set functionality becuase we don't have the proper node object for XML
	//			//target->SetPwvDistanceMethods(ps, node);
	//			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetGeneralUserSettings

	//		/// <summary>
	//		///A test for SetPatientPrivacy
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetPatientPrivacyTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			//Smarajit Mishra
	//			//Remove the set functionality becuase we don't have the proper node object for XML
	//			//target->SetPatientPrivacy(gs, node);
	//			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
	//		/// <summary>
	//		///A test for SetMachineName
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetMachineNameTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			target->SetMachineName(gs, node);
	//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetGeneralUserSettings

	//		/// <summary>
	//		///A test for SetHeightWeight
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetHeightWeightTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			//target->SetHeightWeight(gs, node);
	//			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
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

				gs->BloodPressureEntryOptions = 0;
				gs->CommsPort = "Simulation";
				gs->HeightandWeightUnit= 0;
				gs->PatientPrivacy = true;
				gs->ReportLogoPath = "D:\\EXTRA_DESKTOP\\ERROR.JPG";
				gs->ReportTitle = "REPORT DEM TESTFORme";
				gs->ServerName = "SQLEXPRESS";
				gs->SourceData = "SQLCLIENT";
				gs->CultureInfo = "fr-FR";
				gs->MachineName = "MUM-9638";
				gs->StartupMode = "PWV";
				gs->StartupScreen = "Setup";

				target->SetGeneralUserSettings(gs);

				target->GetGeneralUserSettings();

				Assert::AreEqual(0, target->_instance->GeneralSettings->BloodPressureEntryOptions);
				Assert::AreEqual(0, target->_instance->GeneralSettings->HeightandWeightUnit);
				Assert::AreEqual(true, target->_instance->GeneralSettings->PatientPrivacy);
				Assert::AreEqual("Simulation", target->_instance->GeneralSettings->CommsPort);
				Assert::AreEqual("REPORT DEM TESTFORme", target->_instance->GeneralSettings->ReportTitle);
				Assert::AreEqual("D:\\EXTRA_DESKTOP\\ERROR.JPG", target->_instance->GeneralSettings->ReportLogoPath);
				Assert::AreEqual("SQLEXPRESS", target->_instance->GeneralSettings->ServerName);
				Assert::AreEqual("SQLCLIENT", target->_instance->GeneralSettings->SourceData);
				Assert::AreEqual("fr-FR", target->_instance->GeneralSettings->CultureInfo);
				
				Assert::AreEqual("MUM-9638", target->_instance->GeneralSettings->MachineName);
				Assert::AreEqual("PWV", target->_instance->GeneralSettings->StartupMode);
				Assert::AreEqual("Setup", target->_instance->GeneralSettings->StartupScreen);

				gs->BloodPressureEntryOptions = 1;
				gs->CommsPort = nullptr;
				gs->HeightandWeightUnit= 1;
				gs->PatientPrivacy = false;
				gs->ReportLogoPath = nullptr;
				gs->ReportTitle = nullptr;
				gs->ServerName = nullptr;
				gs->SourceData = nullptr;
				gs->CultureInfo = nullptr;
				gs->MachineName = nullptr;
				gs->StartupMode = nullptr;
				gs->StartupScreen = nullptr;


				target->SetGeneralUserSettings(gs);

				target->GetGeneralUserSettings();

				Assert::AreEqual(1, target->_instance->GeneralSettings->BloodPressureEntryOptions);
				Assert::AreEqual(1, target->_instance->GeneralSettings->HeightandWeightUnit);
				Assert::AreEqual(false, target->_instance->GeneralSettings->PatientPrivacy);
				/*Assert::AreEqual(" ", target->_instance->GeneralSettings->CommsPort);
				Assert::AreEqual(" ", target->_instance->GeneralSettings->ReportTitle);
				Assert::AreEqual(" ", target->_instance->GeneralSettings->ReportLogoPath);
				Assert::AreEqual(" ", target->_instance->GeneralSettings->ServerName);
				Assert::AreEqual(" ", target->_instance->GeneralSettings->SourceData);
				Assert::AreEqual(" ", target->_instance->GeneralSettings->CultureInfo);*/
				

				gs->BloodPressureEntryOptions = 2;

				target->SetGeneralUserSettings(gs);

				target->GetGeneralUserSettings();

				Assert::AreEqual(2, target->_instance->GeneralSettings->BloodPressureEntryOptions);

				//****************************//
				gs->BloodPressureEntryOptions = 0;
				gs->CommsPort = "Simulation";
				gs->HeightandWeightUnit= 0;
				gs->PatientPrivacy = true;
				gs->ReportLogoPath = "D:\\EXTRA_DESKTOP\\ERROR.JPG";
				gs->ReportTitle = "REPORT DEM TESTFORme";
				gs->ServerName = "SQLEXPRESS";
				gs->SourceData = "SQLCLIENT";
				gs->CultureInfo = "fr-FR";
				gs->MachineName = "MUM-9638";
				gs->StartupMode = "PWV";
				gs->StartupScreen = "Setup";

				target->SetGeneralUserSettings(gs);

				//*********************************//

				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetGeneralUserSettings

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
				int expected = 0;
				int actual;
				try
				{
					XmlDocument^ doc = gcnew XmlDocument;

					doc->LoadXml( "<root>" "<elem>some text<child/>more text</elem>" "</root>" );

					XmlNode^ elem = doc->DocumentElement->FirstChild;
										
					target->SetGeneralSettingsNode(gs, elem);
				}
				catch(Exception^)
				{
					actual =0;
				}
				Assert::AreEqual (expected,actual);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetPwvUserSettings

	//		/// <summary>
	//		///A test for SetFemoralToCuff
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetFemoralToCuffTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			//Smarajit Mishra
	//			//Remove the set functionality becuase we don't have the proper node object for XML
	//			//target->SetFemoralToCuff(ps, node);
	//			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
	//		/// <summary>
	//		///A test for SetCultureInfo
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetCultureInfoTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			target->SetCultureInfo(gs, node);
	//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetGeneralUserSettings

	//		/// <summary>
	//		///A test for SetCommsPort
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetCommsPortTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			//Smarajit Mishra
	//			//Remove the set functionality becuase we don't have the proper node object for XML
	//			//target->SetCommsPort(gs, node);
	//			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetPwvUserSettings

	//		/// <summary>
	//		///A test for SetCaptureTime
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetCaptureTimeTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			//Smarajit Mishra
	//			//Remove the set functionality becuase we don't have the proper node object for XML
	//			///target->SetCaptureTime(ps, node);
	//			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetGeneralUserSettings

	//		/// <summary>
	//		///A test for SetBloodPressureOption
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetBloodPressureOptionTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
	//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
	//			//Smarajit Mishra
	//			//Remove the set functionality becuase we don't have the proper node object for XML
	//			//target->SetBloodPressureOption(gs, node);
	//			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
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
			///A test for GetStartupScreen
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetStartupScreenTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				 //target->GetStartupScreen(SubSection, ReaderValue);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			
				target->GetStartupScreen("USER","Setup");
				Assert::AreEqual("Setup", target->_instance->GeneralSettings->StartupScreen);

				target->GetStartupScreen("DEFAULT", "Setup");
				Assert::AreEqual("Setup", target->_gSetInternal->StartupScreen);
				
				try
				{	
					target->GetStartupScreen("USER2","XX");
				}
				catch(Exception^)
				{
					target->_instance->GeneralSettings->StartupScreen = nullptr;
				}
				
				Assert::AreEqual(nullptr, target->_instance->GeneralSettings->StartupScreen);

			}
			/// <summary>
			///A test for GetStartupMode
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetStartupModeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				//target->GetStartupMode(SubSection, ReaderValue);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			
				target->GetStartupMode("USER","PWV");
				Assert::AreEqual("PWV", target->_instance->GeneralSettings->StartupMode);

				target->GetStartupMode("DEFAULT", "Smar");
				Assert::AreEqual("Smar", target->_gSetInternal->StartupMode);
				
				try
				{	
					target->GetStartupMode("USER2","XX");
				}
				catch(Exception^)
				{
					target->_instance->GeneralSettings->StartupMode = nullptr;
				}
				
				Assert::AreEqual(nullptr, target->_instance->GeneralSettings->StartupMode);
			}
			/// <summary>
			///A test for GetSourceData
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetSourceDataTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				
				target->GetSourceData("USER", "SQLCLIENT");
				Assert::AreEqual("SQLCLIENT",target->_instance->GeneralSettings->SourceData);

				target->GetSourceData("DEFAULT", "SQLCLIENT");
				Assert::AreEqual(nullptr, target->_gSetInternal->SourceData);
				
				try
				{	
					target->GetSourceData("USER2","XX");
				}
				catch(Exception^)
				{
					target->_instance->GeneralSettings->SourceData = nullptr;
				}
				
				Assert::AreEqual(nullptr, target->_instance->GeneralSettings->SourceData);
				//target->GetSourceData(SubSection, ReaderValue);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
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

				target->GetSimulationType("DEFAULT", "Simulation1");
				Assert::AreEqual("Simulation1", target->_pSetInternal->SimulationType);

			
				try
				{	
					target->GetSimulationType("USER2","XX");
				}
				catch(Exception^)
				{
					target->_instance->PwvSettings->SimulationType = nullptr;
				}
				
				Assert::AreEqual(nullptr, target->_instance->PwvSettings->SimulationType);


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

				String^ path = Directory::GetCurrentDirectory(); 
				//Directory::SetCurrentDirectory("D:\\Smarajit\\AQTime\\Scor_Source_code");
				int actual;
				int expected = 0;
				try
				{
					target->GetSettings("GENERAL", "USER");
				}
				catch(Exception^)
				{
					actual = 0 ;
				}

				Assert::AreEqual(expected,actual);

				CrxConfigManagerTest::SetPath();

				try
				{
					target->GetSettings("GENERAL", "USER");
				}
				catch(Exception^)
				{
					actual = 0 ;
				}

				Assert::AreEqual(expected,actual);


				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetServerName
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetServerNameTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				
				target->GetServerName("USER", "MUM-9638\\SQLEXPRESS");
				Assert::AreEqual("MUM-9638\\SQLEXPRESS",target->_instance->GeneralSettings->ServerName);

				target->GetServerName("DEFAULT", "MUM-9638\\SQLEXPRESS");
				Assert::AreEqual(nullptr, target->_gSetInternal->ServerName);
				
				try
				{	
					target->GetServerName("USER2","XX");
				}
				catch(Exception^)
				{
					target->_instance->GeneralSettings->ServerName = nullptr;
				}
				
				Assert::AreEqual(nullptr, target->_gSetInternal->ServerName);

				//target->GetServerName(SubSection, ReaderValue);
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
				
				target->GetReportTitle("DEFAULT", "ReportTitle2");
				Assert::AreEqual(nullptr, target->_gSetInternal->ReportTitle);
				
				try
				{	
					target->GetReportTitle("USER2","XX");
				}
				catch(Exception^)
				{
					target->_instance->GeneralSettings->ReportTitle = nullptr;
				}
				
				Assert::AreEqual(nullptr, target->_instance->GeneralSettings->ReportTitle);

				
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

				target->GetReportLogoPath("DEFAULT", "D:\\EXTRA_DESKTOP\\ERROR.JPG");
				Assert::AreEqual(nullptr, target->_gSetInternal->ReportLogoPath);
				
				try
				{	
					target->GetReportLogoPath("USER2","XX");
				}
				catch(Exception^)
				{
					target->_instance->GeneralSettings->ReportLogoPath = nullptr;
				}
				
				Assert::AreEqual(nullptr, target->_instance->GeneralSettings->ReportLogoPath);
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

				try
				{	
					target->GetReferenceRange("USER","XX");
				}
				catch(Exception^)
				{
					target->_instance->PwvSettings->ReferenceRange = true;
				}
				
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
				Assert::AreEqual(5, target->_instance->PwvSettings->CaptureTime);
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
				int actual;
				int expected = 0;
				try
				{
					XmlDocument^ doc = gcnew XmlDocument;

					doc->LoadXml( "<root>" "<elem>some text<child/>more text</elem>" "</root>" );

					XmlNode^ elem = doc->DocumentElement->FirstChild;
										
					target->GetPwvSettingsNode(SubSection, "USER2", ReaderValue);
				}
				catch(Exception^)
				{
					actual =0;
				}
				Assert::AreEqual (expected,actual);
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
				
				try
				{
					target->GetPwvDistanceUnits("USER","cm2");
				}
				catch(Exception^)
				{
					target->_instance->PwvSettings->PWVDistanceUnits = 2;
				}

				Assert::AreEqual(2, target->_instance->PwvSettings->PWVDistanceUnits);
				//Assert::AreEqual(1, target->_instance->PwvSettings->PWVDistanceUnits);

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

				try
				{
					target->GetPwvDistanceMethods("USER","DIRECT2");
				}
				catch(Exception^)
				{
					target->_instance->PwvSettings->PWVDistanceMethod = 2;
				}
				Assert::AreEqual(2, target->_instance->PwvSettings->PWVDistanceMethod);
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
				Assert::AreEqual(5, objPwvSettings->CaptureTime);
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
				
				try
				{	
					target->GetPatientPrivacy("USER", "XX");
				}
				catch(Exception^)
				{
					target->_instance->GeneralSettings->PatientPrivacy = true;
				}
				
				Assert::AreEqual(true, target->_instance->GeneralSettings->PatientPrivacy);

				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetMachineName
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetMachineNameTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				//target->GetMachineName(SubSection, ReaderValue);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			
				target->GetMachineName("USER","MUM-Temp");
				Assert::AreEqual("MUM-Temp", target->_instance->GeneralSettings->MachineName);

				target->GetMachineName("DEFAULT", "Alok");
				Assert::AreEqual(nullptr, target->_gSetInternal->MachineName);
				
				try
				{	
					target->GetMachineName("USER2","XX");
				}
				catch(Exception^)
				{
					target->_instance->GeneralSettings->MachineName = nullptr;
				}
				
				Assert::AreEqual(nullptr, target->_instance->GeneralSettings->MachineName);
			
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

				try
				{	
					target->GetHeightWeight("USER", "IMPERIAL2");
				}
				catch(Exception^)
				{
					target->_instance->GeneralSettings->HeightandWeightUnit = 2;
				}
				
				Assert::AreEqual(2, target->_instance->GeneralSettings->HeightandWeightUnit);

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

				Assert::AreEqual(0, target->_instance->GeneralSettings->BloodPressureEntryOptions);
				Assert::AreEqual(0, target->_instance->GeneralSettings->HeightandWeightUnit);
				Assert::AreEqual(true, target->_instance->GeneralSettings->PatientPrivacy);
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
				
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;
				SubSection = "USER";
				SubSectionNode= "X2";

				try
				{
					target->GetGeneralSettingsNode(SubSection, SubSectionNode, ReaderValue);
				}
				catch(Exception^)
				{
					actual = 0;
				}

				Assert::AreEqual(expected,actual);
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
				Assert::AreEqual(nullptr, objGenSettings->MachineName);
				Assert::AreEqual("PWV", objGenSettings->StartupMode);
				Assert::AreEqual("Setup", objGenSettings->StartupScreen);
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
				
				try
				{
					target->GetFemoralToCuff("USER", "XX");
				}
				//Catch if any of the exception occurs in XML Reader
				catch (Exception^) 
				{
					target->_instance->PwvSettings->FemoralToCuff = true;
				}
				Assert::AreEqual(true, target->_instance->PwvSettings->FemoralToCuff);
				

				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for GetCultureInfo
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetCultureInfoTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
				//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
				
				target->GetCultureInfo("USER", "EN-en");
				Assert::AreEqual("EN-en",target->_instance->GeneralSettings->CultureInfo);

				target->GetCultureInfo("DEFAULT", "SQLCLIENT");
				Assert::AreEqual(nullptr, target->_gSetInternal->CultureInfo);
				
				try
				{	
					target->GetCultureInfo("USER2","XX");
				}
				catch(Exception^)
				{
					target->_instance->GeneralSettings->CultureInfo = nullptr;
				}
				
				Assert::AreEqual(nullptr, target->_instance->GeneralSettings->CultureInfo);

				//target->GetCultureInfo(SubSection, ReaderValue);
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

				target->GetCommsPort("DEFAULT", "COMMS1");
				Assert::AreEqual(nullptr,  target->_gSetInternal->CommsPort);
				
				try
				{	
					target->GetCommsPort("USER2", "MPANDXX");
				}
				catch(Exception^)
				{
					target->_instance->GeneralSettings->CommsPort = nullptr;
				}
				
				Assert::AreEqual(nullptr, target->_instance->GeneralSettings->CommsPort);

				
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
				Assert::AreEqual(5, target->_instance->PwvSettings->CaptureTime);

				target->GetCaptureTime("DEFAULT", "5SECONDS");
				Assert::AreEqual(5, target->_pSetInternal->CaptureTime);

				try
				{	
					target->GetCaptureTime("USER", "MPANDXX");
				}
				catch(Exception^)
				{
					target->_instance->PwvSettings->CaptureTime = 20;
				}

				Assert::AreEqual(20, target->_instance->PwvSettings->CaptureTime);
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
								
				try
				{	
					target->GetBloodPressureOption("USER", "MPANDXX");
				}
				catch(Exception^)
				{
					target->_instance->PwvSettings->ReferenceRange = true;
				}
				
				Assert::AreEqual(true, target->_instance->PwvSettings->ReferenceRange);

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
				Assert::IsNotNull(target);
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
				Assert::IsNotNull(target->_generalSettings);
				//Smarajit Mishra				
						
			}
	};
}
namespace TestCrx {
    
}
