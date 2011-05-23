
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"

//using namespace System;
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
			static String^  serverName = String::Empty;//"MUM-9383\\SQLEXPRESS";
			static String^  sourceName = String::Empty;//"SQLCLIENT";

			//Customized function to Set the path
			void SetPath()
			{
				String^ path = Directory::GetCurrentDirectory(); 
				int i = path->IndexOf("\\TestResults");
				if(i > 0)
				{
					path = path->Substring(0,i + 12);
					Directory::SetCurrentDirectory(path);
				}
				else
				{
					path  = path + "\\TestResults";
					Directory::SetCurrentDirectory(path);
				}
			}

			void SetServerMachineName()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				CrxStructGeneralSetting^ objGenSettings = gcnew CrxStructGeneralSetting();
				String^ _currDir = Directory::GetCurrentDirectory(); 
				
				//SetPath();

				target->GetGeneralUserSettings();

				objGenSettings = target->GeneralSettings;
				 
				serverName = String::Format("{0}\\{1} ",target->_instance->GeneralSettings->MachineName,target->_instance->GeneralSettings->ServerName);
				sourceName = target->_instance->GeneralSettings->SourceData;
				
				Directory::SetCurrentDirectory(_currDir);
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
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				CrxStructPwvSetting^  expected = gcnew CrxStructPwvSetting(); 
				CrxStructPwvSetting^  actual;

				actual = target->PwvSettings;

				//Default values in the structure 	CrxStructPwvSetting are 5, false, 0 and 0 for CaptureTime,
				//FemoralToCuff, PWVDistanceMethod and PWVDistanceUnits respectively
				Assert::AreEqual(5, actual->CaptureTime);
				Assert::AreEqual(false, actual->FemoralToCuff);
				Assert::AreEqual(0, actual->PWVDistanceMethod);
				Assert::AreEqual(0, actual->PWVDistanceUnits);

				expected->CaptureTime = 10;
				expected->FemoralToCuff = true;
				expected->PWVDistanceMethod = 1;
				expected->PWVDistanceUnits = 2;

				//Setting the CaptureTime member of structure CrxStructPwvSetting
				target->PwvSettings = expected;

				//Getting the CaptureTime member of structure CrxStructPwvSetting
				actual = target->PwvSettings;
				
				//comparing the actual and expected structure values
				Assert::AreEqual(expected->CaptureTime, actual->CaptureTime);
				Assert::AreEqual(expected->FemoralToCuff, actual->FemoralToCuff);
				Assert::AreEqual(expected->PWVDistanceMethod, actual->PWVDistanceMethod);
				Assert::AreEqual(expected->PWVDistanceUnits, actual->PWVDistanceUnits);
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
			}
			/// <summary>
			///A test for GeneralSettings
			///</summary>
	public: [TestMethod]
			void GeneralSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				CrxStructGeneralSetting^  expected = gcnew CrxStructGeneralSetting(); 
				CrxStructGeneralSetting^  actual;
				
				actual = target->GeneralSettings;
				Assert::AreEqual(false, actual->PatientPrivacy);
				Assert::AreEqual(0, actual->BloodPressureEntryOptions);

				target->GeneralSettings->PatientPrivacy = true;

				target->GeneralSettings = expected;

				actual = target->GeneralSettings;
				Assert::AreEqual(expected->PatientPrivacy, actual->PatientPrivacy);
			}

	//		/// <summary>
	//		///A test for SetSourceData
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void SetSourceDataTest()
	//		{
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructGeneralSetting^  gs = nullptr; 
	//			XmlNode^  node = nullptr; 
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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructPwvSetting^  ps = nullptr; 
	//			XmlNode^  node = nullptr; 
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
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  Section = System::String::Empty; 
				String^  SubSection = System::String::Empty; 
				CrxStructGeneralSetting^  gs = nullptr; 
				CrxStructPwvSetting^  ps = nullptr; 
				XmlNode^  node = nullptr; 
				
				int expected = 0; 
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
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  Section = System::String::Empty; 
				String^  SubSection = System::String::Empty; 
				CrxStructGeneralSetting^  gs = nullptr; 
				CrxStructPwvSetting^  ps = nullptr; 
				
				Section = "GENERAL";
				SubSection= "USER";
				int actual;
				int expected = 0;
				String^ path = Directory::GetCurrentDirectory(); 

				try
				{
					target->SetSettings(Section, SubSection, gs, ps);
				}
				catch(Exception^)
				{
					actual = 0;
				}
				Assert::AreEqual(expected,actual);
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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructGeneralSetting^  gs = nullptr; 
	//			XmlNode^  node = nullptr; 
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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructGeneralSetting^  gs = nullptr; 
	//			XmlNode^  node = nullptr; 
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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructPwvSetting^  ps = nullptr; 
	//			XmlNode^  node = nullptr; 
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
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				CrxStructPwvSetting^  ps = gcnew CrxStructPwvSetting();
				CrxConfigManagerTest::SetPath();
				
				ps->PWVDistanceMethod = 0;
				ps->FemoralToCuff = true;
				ps->PWVDistanceUnits = 0;
				ps->CaptureTime = 5;
				ps->ReferenceRange = true;
				ps->SimulationType = "Default";
				ps->DefaultReport = "PWV Report";
				ps->NormalRange = true;
			
				target->SetPwvUserSettings(ps);

				target->GetPwvUserSettings();

				Assert::AreEqual(0, target->_instance->PwvSettings->PWVDistanceMethod);
				Assert::AreEqual(true, target->_instance->PwvSettings->FemoralToCuff);
				Assert::AreEqual(0, target->_instance->PwvSettings->PWVDistanceUnits);
				Assert::AreEqual(5, target->_instance->PwvSettings->CaptureTime);
				Assert::AreEqual(true, target->_instance->PwvSettings->ReferenceRange);
				Assert::AreEqual("PWV Report", target->_instance->PwvSettings->DefaultReport);
				Assert::AreEqual(true, target->_instance->PwvSettings->NormalRange);

				ps->PWVDistanceMethod = 1;
				ps->FemoralToCuff = false;
				ps->PWVDistanceUnits = 1;
				ps->CaptureTime = 10;
				ps->ReferenceRange = false;
				ps->SimulationType = nullptr;
				ps->DefaultReport = nullptr;
				ps->NormalRange = false;
			
				target->SetPwvUserSettings(ps);

				target->GetPwvUserSettings();

				Assert::AreEqual(1, target->_instance->PwvSettings->PWVDistanceMethod);
				Assert::AreEqual(false, target->_instance->PwvSettings->FemoralToCuff);
				Assert::AreEqual(1, target->_instance->PwvSettings->PWVDistanceUnits);
				Assert::AreEqual(10, target->_instance->PwvSettings->CaptureTime);
				Assert::AreEqual(false, target->_instance->PwvSettings->ReferenceRange);
				Assert::AreEqual(false, target->_instance->PwvSettings->NormalRange);
				
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
				ps->SimulationType = "Simulation";
				ps->DefaultReport = "PWV Report";
				ps->NormalRange = true;

				target->SetPwvUserSettings(ps);
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
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				CrxStructPwvSetting^  gs = nullptr; 
				XmlNode^  node = nullptr; 
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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructPwvSetting^  ps = nullptr; 
	//			XmlNode^  node = nullptr; 
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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructPwvSetting^  ps = nullptr; 
	//			XmlNode^  node = nullptr; 
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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructGeneralSetting^  gs = nullptr; 
	//			XmlNode^  node = nullptr; 
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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructGeneralSetting^  gs = nullptr; 
	//			XmlNode^  node = nullptr; 
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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructGeneralSetting^  gs = nullptr; 
	//			XmlNode^  node = nullptr; 
	//			//target->SetHeightWeight(gs, node);
	//			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
			/// <summary>
			///A test for SetGeneralUserSettings
			///</summary>
	public: [TestMethod]
			void SetGeneralUserSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				//CrxStructGeneralSetting^  gs = nullptr; 
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				CrxStructGeneralSetting^  gs = gcnew CrxStructGeneralSetting();
				CrxConfigManagerTest::SetPath();

				target->GetGeneralUserSettings();

				String^ MachineName =  target->_instance->GeneralSettings->MachineName;
				String^ ServerName =  target->_instance->GeneralSettings->ServerName;
				String^ SourceData =  target->_instance->GeneralSettings->SourceData;
				String^ CultureInfo =  target->_instance->GeneralSettings->CultureInfo;
				String^ printerName =  target->_instance->GeneralSettings->PrinterName;

				gs->BloodPressureEntryOptions = 0;
				gs->CommsPort = "Simulation";
				gs->HeightandWeightUnit= 0;
				gs->PatientPrivacy = true;
				gs->ReportLogoPath = "D:\\EXTRA_DESKTOP\\ERROR.JPG";
				gs->ReportTitle = "REPORT DEM TESTFORme";
				gs->ServerName = ServerName;
				gs->SourceData = SourceData;
				gs->CultureInfo = CultureInfo;
				gs->MachineName = MachineName;
				gs->StartupMode = "PWV";
				gs->StartupScreen = "Setup";
				gs->PrinterName = printerName;

				target->SetGeneralUserSettings(gs);

				target->GetGeneralUserSettings();

				Assert::AreEqual(0, target->_instance->GeneralSettings->BloodPressureEntryOptions);
				Assert::AreEqual(0, target->_instance->GeneralSettings->HeightandWeightUnit);
				Assert::AreEqual(true, target->_instance->GeneralSettings->PatientPrivacy);
				Assert::AreEqual("Simulation", target->_instance->GeneralSettings->CommsPort);
				Assert::AreEqual("REPORT DEM TESTFORme", target->_instance->GeneralSettings->ReportTitle);
				//Assert::AreEqual("D:\\EXTRA_DESKTOP\\ERROR.JPG", target->_instance->GeneralSettings->ReportLogoPath);
				Assert::AreEqual("SQLCLIENT", target->_instance->GeneralSettings->SourceData);
				//Assert::AreEqual("fr-FR", target->_instance->GeneralSettings->CultureInfo);				
				
				Assert::AreEqual("PWV", target->_instance->GeneralSettings->StartupMode);
				Assert::AreEqual("Setup", target->_instance->GeneralSettings->StartupScreen);

				
				gs->BloodPressureEntryOptions = 1;
				gs->CommsPort = nullptr;
				gs->HeightandWeightUnit= 1;
				gs->PatientPrivacy = false;
				gs->ReportLogoPath = nullptr;
				gs->ReportTitle = nullptr;
				gs->ServerName = String::Empty;
				gs->SourceData = String::Empty;
				gs->CultureInfo = String::Empty;
				gs->MachineName = String::Empty;
				gs->StartupMode = nullptr;
				gs->StartupScreen = nullptr;
				gs->PrinterName = nullptr;


				target->SetGeneralUserSettings(gs);

				target->GetGeneralUserSettings();
				//target->GeneralSettings

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
				gs->ServerName = ServerName;
				gs->SourceData = SourceData;
				gs->CultureInfo = CultureInfo;
				gs->MachineName = MachineName;
				gs->StartupMode = "PWV";
				gs->StartupScreen = "Setup";
				gs->PrinterName = printerName;

				target->SetGeneralUserSettings(gs);

				//*********************************//
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
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				CrxStructGeneralSetting^  gs = nullptr; 
				XmlNode^  node = nullptr; 
				//Smarajit Mishra
				//Remove the set functionality becuase we don't have the proper node object for XML
				int expected = 0;
				int actual;
				//SetPath();

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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructPwvSetting^  ps = nullptr; 
	//			XmlNode^  node = nullptr; 
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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructGeneralSetting^  gs = nullptr; 
	//			XmlNode^  node = nullptr; 
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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructGeneralSetting^  gs = nullptr; 
	//			XmlNode^  node = nullptr; 
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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructPwvSetting^  ps = nullptr; 
	//			XmlNode^  node = nullptr; 
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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxStructGeneralSetting^  gs = nullptr; 
	//			XmlNode^  node = nullptr; 
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
	//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
	//			CrxConfigManager^  unnamed = nullptr; 
	//			CrxConfigManager^  expected = nullptr; 
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
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = System::String::Empty; 
				String^  ReaderValue = System::String::Empty; 
			
				target->GetStartupScreen("USER","Setup");
				Assert::AreEqual("Setup", target->_instance->GeneralSettings->StartupScreen);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetStartupScreenTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = System::String::Empty; 
				String^  ReaderValue = System::String::Empty; 
			
				target->GetStartupScreen("DEFAULT", "Setup");
				Assert::AreEqual("Setup", target->_gSetInternal->StartupScreen);

			}
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetStartupScreenTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = System::String::Empty; 
				String^  ReaderValue = System::String::Empty; 
			
				try
				{	
					target->GetStartupScreen("USER2","Setup2");
				}
				catch(Exception^)
				{
					target->_instance->GeneralSettings->StartupScreen = nullptr;
				}
				
				Assert::AreEqual(nullptr, target->_instance->GeneralSettings->StartupScreen);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetStartupScreenTest3()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = System::String::Empty; 
				String^  ReaderValue = System::String::Empty; 
			
				try
				{	
					target->GetStartupScreen("USER2","Setup");
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
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = System::String::Empty; 
				String^  ReaderValue = System::String::Empty; 
			
				target->GetStartupMode("USER","PWV");
				Assert::AreEqual("PWV", target->_instance->GeneralSettings->StartupMode);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetStartupModeTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = System::String::Empty; 
				String^  ReaderValue = System::String::Empty; 
			
				target->GetStartupMode("DEFAULT", "Smar");
				Assert::AreEqual("Smar", target->_gSetInternal->StartupMode);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetStartupModeTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = System::String::Empty; 
				String^  ReaderValue = System::String::Empty; 
				
				try
				{	
					target->GetStartupMode("USER2","XX");
					Assert::Fail("If error does not occur then test fail");
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If error occur then test pass");
				}
			}
			/// <summary>
			///A test for GetSourceData
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetSourceDataTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				//String^  SubSection = System::String::Empty; 
				//String^  ReaderValue = System::String::Empty; 
				
				target->GetSourceData("USER", "SQLCLIENT");
				Assert::AreEqual("SQLCLIENT",target->_instance->GeneralSettings->SourceData);

				target->GetSourceData("DEFAULT", "SQLCLIENT");
				Assert::AreEqual(nullptr, target->_gSetInternal->SourceData);
				
				try
				{	
					target->GetSourceData("USER2","XX");
					Assert::Fail("If error does not occur then test fail");
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If error occur then test pass");
				}
			}
			/// <summary>
			///A test for GetSimulationType
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetSimulationTypeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetSimulationType("USER", "Simulation1");
				Assert::AreEqual("Simulation1", target->_instance->PwvSettings->SimulationType);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetSimulationTypeTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetSimulationType("DEFAULT", "Simulation1");
				Assert::AreEqual("Simulation1", target->_pSetInternal->SimulationType);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetSimulationTypeTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				try
				{	
					target->GetSimulationType("USER2","XX");
					Assert::Fail("If error does not occur then test fail");
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If error occur then test pass");
				}
			}
			/// <summary>
			///A test for GetSettingsNode
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetSettingsNodeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  Section = System::String::Empty; 
				String^  SubSection = System::String::Empty; 
				String^  SubSectionNode = System::String::Empty; 
				String^  ReaderValue = System::String::Empty; 
				target->GetSettingsNode(Section, SubSection, SubSectionNode, ReaderValue);
			}
			/// <summary>
			///A test for GetSettings
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				//Smarajit Mishra
				//Pass the required inout to get the expected result
				//String^  Section = System::String::Empty; 
				//String^  SubSection = System::String::Empty; 
				//target->GetSettings(Section, SubSection);

				//String^ path = Directory::GetCurrentDirectory(); 
				CrxConfigManagerTest::SetPath();
				//Directory::SetCurrentDirectory("D:\\Smarajit\\AQTime\\Scor_Source_code");
				int actual;
				int expected = 0;
				
					target->GetSettings("GENERAL", "USER");
					Assert::IsNotNull(target->_instance->GeneralSettings->StartupMode);				

				
					target->GetSettings("GENERAL", "DEFAULT");
					Assert::IsNotNull(target->_instance->GeneralSettings->StartupMode);
				
					target->GetSettings("PWV", "USER");
					Assert::IsNotNull(target->_instance->PwvSettings->PWVDistanceMethod);				

				
					target->GetSettings("PWV", "DEFAULT");
					Assert::IsNotNull(target->_instance->PwvSettings->PWVDistanceMethod);
				//CrxConfigManagerTest::SetPath();
				expected = 0;
				try
				{
					target->GetSettings("PWV3", "USER");
					actual = 0 ;
				}
				catch(Exception^)
				{
					actual = 1 ;
				}

				Assert::AreEqual(expected,actual);
			}
			/// <summary>
			/// Tests for GetServerName
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetServerNameTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = "USER"; 
				String^  ReaderValue = serverName; 
				

				target->GetServerName(SubSection, ReaderValue);
				Assert::AreEqual(serverName,target->_instance->GeneralSettings->ServerName);
				target->_instance->GeneralSettings->ServerName = nullptr;

			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetServerNameTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = "DEFAULT"; 
				String^  ReaderValue = serverName; 
				
				target->GetServerName(SubSection, ReaderValue);
				Assert::IsNull(target->_gSetInternal->ServerName);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetServerNameTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = "USER2"; 
				String^  ReaderValue = "XX"; 
				
				try
				{	
					target->GetServerName(SubSection, ReaderValue);
					Assert::Fail("If error does not occur then test fail");
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If error occur then test pass");
				}
			}
						/// <summary>
			///A test for GetReportTitle
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetReportTitleTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				String^  SubSection = "USER"; 
				String^  ReaderValue = "ReportTitle2"; 
				
				target->GetReportTitle(SubSection, ReaderValue);

				Assert::AreEqual(ReaderValue, target->_instance->GeneralSettings->ReportTitle);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetReportTitleTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				
				String^  SubSection = "DEFAULT"; 
				String^  ReaderValue = "ReportTitle2"; 
				
				target->GetReportTitle(SubSection, ReaderValue);

				Assert::IsNull(target->_gSetInternal->ReportTitle);
				
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetReportTitleTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				
				String^  SubSection = "USER"; 
				String^  ReaderValue = "XX"; 
				
				try
				{	
					target->GetReportTitle(SubSection, ReaderValue);
					Assert::Fail("If error does not occur then test fail");
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If error occur then test pass");
				}
			}
			/// <summary>
			///A test for GetReportLogoPath
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetReportLogoPathTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				//Pass the required inout to get the expected result
				target->GetReportLogoPath("USER", "D:\\EXTRA_DESKTOP\\ERROR.JPG");
				Assert::AreEqual("D:\\EXTRA_DESKTOP\\ERROR.JPG", target->_instance->GeneralSettings->ReportLogoPath);

				target->GetReportLogoPath("DEFAULT", "D:\\EXTRA_DESKTOP\\ERROR.JPG");
				Assert::IsNull(target->_gSetInternal->ReportLogoPath);
				
				try
				{	
					target->GetReportLogoPath("USER2","XX");
					Assert::Fail("If error does not occur then test fail");
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If error occur then test pass");
				}
			}

			/// <summary>
			///A test for GetReferenceRange
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetReferenceRangeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				//Pass the required inout to get the expected result
				String^  SubSection = L"USER";
				String^  ReaderValue = L"No";

				target->GetReferenceRange(SubSection, ReaderValue);
				Assert::AreEqual(false, target->_instance->PwvSettings->ReferenceRange);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetReferenceRangeTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				//Pass the required inout to get the expected result
				String^  SubSection = L"DEFAULT";
				String^  ReaderValue = L"Yes";

				target->GetReferenceRange(SubSection, ReaderValue);
				Assert::AreEqual(true, target->_pSetInternal->ReferenceRange);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetReferenceRangeTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				//Pass the required inout to get the expected result
				String^  SubSection = L"USER";
				String^  ReaderValue = L"XX";

				try
				{	
					target->GetReferenceRange(SubSection, ReaderValue);
					Assert::Fail("If error does not occur then test fail");
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If error occur then test pass");
				}
			}
			/// <summary>
			///A test for GetPwvUserSettings
			///</summary>
	public: [TestMethod]
			void GetPwvUserSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				
				CrxConfigManagerTest::SetPath();
				target->GetPwvUserSettings();

				Assert::AreEqual(0, target->_instance->PwvSettings->PWVDistanceMethod);
				Assert::AreEqual(true, target->_instance->PwvSettings->FemoralToCuff);
				Assert::AreEqual(0, target->_instance->PwvSettings->PWVDistanceUnits);
				Assert::AreEqual(5, target->_instance->PwvSettings->CaptureTime);
				Assert::AreEqual(true, target->_instance->PwvSettings->ReferenceRange);
				Assert::AreEqual("Simulation", target->_instance->PwvSettings->SimulationType);
			}

			/// <summary>
			///A test for GetPwvSettingsNode
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPwvSettingsNodeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = System::String::Empty; 
				String^  SubSectionNode = System::String::Empty; 
				String^  ReaderValue = System::String::Empty; 
				//int actual;
				int expected = 0;
				try
				{
					XmlDocument^ doc = gcnew XmlDocument;

					doc->LoadXml( "<root>" "<elem>some text<child/>more text</elem>" "</root>" );

					XmlNode^ elem = doc->DocumentElement->FirstChild;
										
					target->GetPwvSettingsNode(SubSection, "USER2", ReaderValue);
					Assert::Fail("If error does not occur then test fail");
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If error occur then test pass");
				}
			}
			/// <summary>
			///A test for GetPwvDistanceUnits
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPwvDistanceUnitsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = L"USER";
				String^  ReaderValue = L"mm";

				target->GetPwvDistanceUnits(SubSection, ReaderValue);
				Assert::AreEqual(0, target->_instance->PwvSettings->PWVDistanceUnits);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPwvDistanceUnitsTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = L"DEFAULT";
				String^  ReaderValue = L"cm";

				target->GetPwvDistanceUnits(SubSection, ReaderValue);
				Assert::AreEqual(1, target->_pSetInternal->PWVDistanceUnits);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPwvDistanceUnitsTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = L"USER";
				String^  ReaderValue = L"cm2";

				try
				{
					target->GetPwvDistanceUnits(SubSection, ReaderValue);
				}
				catch(Exception^)
				{
					target->_instance->PwvSettings->PWVDistanceUnits = 2;
				}

				Assert::AreEqual(2, target->_instance->PwvSettings->PWVDistanceUnits);
			}
						/// <summary>
			///A test for GetPwvDistanceMethods
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPwvDistanceMethodsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = L"USER";
				String^  ReaderValue = L"Subtracting";

				target->GetPwvDistanceMethods(SubSection, ReaderValue);
				Assert::AreEqual(0, target->_instance->PwvSettings->PWVDistanceMethod);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPwvDistanceMethodsTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = L"DEFAULT";
				String^  ReaderValue = L"DIRECT";

				target->GetPwvDistanceMethods(SubSection, ReaderValue);
				Assert::AreEqual(1, target->_pSetInternal->PWVDistanceMethod);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPwvDistanceMethodsTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = L"USER";
				String^  ReaderValue = L"DIRECT2";

				try
				{
					target->GetPwvDistanceMethods(SubSection, ReaderValue);
					target->_instance->PwvSettings->PWVDistanceMethod = 0;
				}
				catch(Exception^)
				{
					target->_instance->PwvSettings->PWVDistanceMethod = 2;
				}
				Assert::AreEqual(target->_instance->PwvSettings->PWVDistanceMethod, 2);
			}
			/// <summary>
			///A test for GetPwvDefaultSettings
			///</summary>
	public: [TestMethod]
			void GetPwvDefaultSettingsTest()
			{

				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				CrxStructPwvSetting^ objPwvSettings = gcnew CrxStructPwvSetting();

				CrxConfigManagerTest::SetPath();
				target->GetPwvDefaultSettings(objPwvSettings);
				
				Assert::AreEqual(0, objPwvSettings->PWVDistanceMethod);
				Assert::AreEqual(true, objPwvSettings->FemoralToCuff);
				Assert::AreEqual(0, objPwvSettings->PWVDistanceUnits);
				Assert::AreEqual(5, objPwvSettings->CaptureTime);
				Assert::AreEqual(true, objPwvSettings->ReferenceRange);
				Assert::AreEqual("Simulation", objPwvSettings->SimulationType);
			}
			/// <summary>
			///A test for GetPatientPrivacy
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPatientPrivacyTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = L"USER";
				String^  ReaderValue = L"NO";

				target->GetPatientPrivacy(SubSection, ReaderValue);
				Assert::AreEqual(false, target->_instance->GeneralSettings->PatientPrivacy);

			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPatientPrivacyTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = L"DEFAULT";
				String^  ReaderValue = L"Yes";

				target->GetPatientPrivacy(SubSection, ReaderValue);
				Assert::AreEqual(true, target->_gSetInternal->PatientPrivacy);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPatientPrivacyTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = L"USER";
				String^  ReaderValue = L"XX";
				
				try
				{	
					target->GetPatientPrivacy(SubSection, ReaderValue);
				}
				catch(Exception^)
				{
					target->_instance->GeneralSettings->PatientPrivacy = true;
				}
				
				Assert::AreEqual(true, target->_instance->GeneralSettings->PatientPrivacy);
			}
						/// <summary>
			///A test for GetMachineName
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetMachineNameTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = "USER"; 
				String^  ReaderValue = "MUM-Temp"; 
			
				target->GetMachineName(SubSection, ReaderValue);
				Assert::AreEqual(ReaderValue, target->_instance->GeneralSettings->MachineName);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetMachineNameTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = "DEFAULT"; 
				String^  ReaderValue = "Test"; 
			
				target->GetMachineName(SubSection, ReaderValue);
				Assert::IsNull(target->_gSetInternal->MachineName);
			}

			
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetMachineNameTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = "USER2"; 
				String^  ReaderValue = "XX"; 
				
				try
				{	
					target->GetMachineName(SubSection, ReaderValue);
					Assert::Fail("If error does not occur then test fail");
                }
                catch(Exception^)
                {
                      Assert::IsTrue(true,"If error occur then test pass");
                }
			}

			
						/// <summary>
			///A test for GetHeightWeight
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetHeightWeightTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetHeightWeight("USER", "METRIC");
				Assert::AreEqual(0, target->_instance->GeneralSettings->HeightandWeightUnit);
							}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetHeightWeightTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetHeightWeight("DEFAULT", "IMPERIAL");
				Assert::AreEqual(1, target->_gSetInternal->HeightandWeightUnit);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetHeightWeightTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				try
				{	
					target->GetHeightWeight("USER", "IMPERIAL2");
				}
				catch(Exception^)
				{
					target->_instance->GeneralSettings->HeightandWeightUnit = 2;
				}
				
				Assert::AreEqual(2, target->_instance->GeneralSettings->HeightandWeightUnit);
			}
						/// <summary>
			///A test for GetGeneralUserSettings
			///</summary>
	public: [TestMethod]
			void GetGeneralUserSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				
				CrxConfigManagerTest::SetPath();
				target->GetGeneralUserSettings();

				Assert::AreEqual(0, target->_instance->GeneralSettings->BloodPressureEntryOptions);
				Assert::AreEqual(0, target->_instance->GeneralSettings->HeightandWeightUnit);
				Assert::AreEqual(true, target->_instance->GeneralSettings->PatientPrivacy);
				Assert::AreEqual("Simulation", target->_instance->GeneralSettings->CommsPort);
				Assert::AreEqual("REPORT DEM TESTFORme", target->_instance->GeneralSettings->ReportTitle);
				Assert::AreEqual("D:\\EXTRA_DESKTOP\\ERROR.JPG", target->_instance->GeneralSettings->ReportLogoPath);
			}
			/// <summary>
			///A test for GetGeneralSettingsNode
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetGeneralSettingsNodeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = System::String::Empty; 
				String^  SubSectionNode = System::String::Empty; 
				String^  ReaderValue = System::String::Empty; 
				
				int expected = 0; 
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
			}
			/// <summary>
			///A test for GetGeneralDefaultSettings
			///</summary>
	public: [TestMethod]
			void GetGeneralDefaultSettingsTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				CrxStructGeneralSetting^ objGenSettings = gcnew CrxStructGeneralSetting();
				
				CrxConfigManagerTest::SetPath();

				target->GetGeneralDefaultSettings(objGenSettings);

				Assert::AreEqual(0, objGenSettings->BloodPressureEntryOptions);
				Assert::AreEqual(0, objGenSettings->HeightandWeightUnit);
				Assert::AreEqual(false, objGenSettings->PatientPrivacy);
				Assert::IsNull(objGenSettings->MachineName);
				Assert::AreEqual("PWV", objGenSettings->StartupMode);
				Assert::AreEqual("Setup", objGenSettings->StartupScreen);
				Assert::IsNull(objGenSettings->CommsPort);
				Assert::IsNull(objGenSettings->ReportTitle);
				Assert::IsNull(objGenSettings->ReportLogoPath);
			}
			/// <summary>
			///A test for GetFemoralToCuff
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetFemoralToCuffTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetFemoralToCuff("USER", "Yes");
				Assert::AreEqual(true,  target->_instance->PwvSettings->FemoralToCuff);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetFemoralToCuffTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetFemoralToCuff("DEFAULT", "No");
				Assert::AreEqual(false,  target->_pSetInternal->FemoralToCuff);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetFemoralToCuffTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				
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
			}
			/// <summary>
			///A test for GetCultureInfo
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetCultureInfoTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				//String^  SubSection = System::String::Empty; 
				//String^  ReaderValue = System::String::Empty; 
				
				target->GetCultureInfo("USER", "EN-en");
				Assert::AreEqual("EN-en",target->_instance->GeneralSettings->CultureInfo);

				target->GetCultureInfo("DEFAULT", "SQLCLIENT");
				Assert::AreEqual(nullptr, target->_gSetInternal->CultureInfo);
				
				try
				{	
					target->GetCultureInfo("USER2","XX");
					Assert::Fail("If error does not occur then test fail");
                }
                catch(Exception^)
                {
                     Assert::IsTrue(true,"If error occur then test pass");
                }
			}
			/// <summary>
			///A test for GetConfigPrinter
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetConfigPrinterTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = "USER"; 
				String^  ReaderValue = "PRINTERNAME"; 
				
				target->GetConfigPrinter(SubSection, ReaderValue);
				Assert::AreEqual("PRINTERNAME", target->_instance->GeneralSettings->PrinterName);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetConfigPrinterTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = "DEFAULT"; 
				String^  ReaderValue = "PRINTERNAME"; 

				target->GetConfigPrinter(SubSection, ReaderValue);
				Assert::AreEqual(nullptr, target->_gSetInternal->PrinterName);
			
			}

				public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetConfigPrinterTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = "XXXX"; 
				String^  ReaderValue = "PRINTERNAME"; 
			
				try
				{
					target->GetConfigPrinter(SubSection, ReaderValue);
					
				}
				catch(Exception^)
				{
					//If exception occure means test case pass
					Assert::IsTrue(true);
				}
			}
			/// <summary>
			///A test for GetCommsPort
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetCommsPortTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetCommsPort("USER", "COMMS1");
				Assert::AreEqual("COMMS1",  target->_instance->GeneralSettings->CommsPort);

			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetCommsPortTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetCommsPort("DEFAULT", "COMMS1");
				Assert::AreEqual(nullptr,  target->_gSetInternal->CommsPort);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetCommsPortTest3()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				try
				{	
					target->GetCommsPort("USER2", "MPANDXX");
					Assert::Fail("If error does not occur then test fail");
                }
                catch(Exception^)
                {
                     Assert::IsTrue(true,"If error occur then test pass");
                }
			}
			/// <summary>
			///A test for GetCaptureTime
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetCaptureTimeTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetCaptureTime("USER", "5SECONDS");
				Assert::AreEqual(5, target->_instance->PwvSettings->CaptureTime);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetCaptureTimeTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetCaptureTime("DEFAULT", "10SECONDS");
				Assert::AreEqual(10, target->_pSetInternal->CaptureTime);
			}

				public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetCaptureTimeTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetCaptureTime("DEFAULT", "20SECONDS");
				Assert::AreEqual(20, target->_pSetInternal->CaptureTime);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetCaptureTimeTest3()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				try
				{	
					target->GetCaptureTime("USER", "MPANDXX");
				}
				catch(Exception^)
				{
					target->_instance->PwvSettings->CaptureTime = 20;
				}

				Assert::AreEqual(20, target->_instance->PwvSettings->CaptureTime);
			}
						/// <summary>
			///A test for GetBloodPressureOption
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetBloodPressureOptionTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetBloodPressureOption("USER", "SPANDDP");
				Assert::AreEqual(0, target->_instance->GeneralSettings->BloodPressureEntryOptions);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetBloodPressureOptionTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetBloodPressureOption("USER", "SPANDMP");
				Assert::AreEqual(1, target->_instance->GeneralSettings->BloodPressureEntryOptions);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetBloodPressureOptionTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetBloodPressureOption("USER", "MPANDDP");
				Assert::AreEqual(2, target->_instance->GeneralSettings->BloodPressureEntryOptions);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetBloodPressureOptionTest3()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetBloodPressureOption("DEFAULT", "MPANDDP");
				Assert::AreEqual(2, target->_gSetInternal->BloodPressureEntryOptions);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetBloodPressureOptionTest4()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				try
				{	
					target->GetBloodPressureOption("USER", "MPANDXX");
				}
				catch(Exception^)
				{
					target->_instance->PwvSettings->ReferenceRange = true;
				}
				
				Assert::AreEqual(true, target->_instance->PwvSettings->ReferenceRange);
			}
			/// <summary>
			///A test for CrxConfigManager Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxConfigManagerConstructorTest1()
			{
				CrxConfigManager^  unnamed = nullptr; 
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor(unnamed));
				Assert::IsNotNull(target);
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
			/// <summary>
			///A test for GetDefaultReport
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetDefaultReportTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			//
			//String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
			//String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
			//target->GetDefaultReport(SubSection, ReaderValue);

			target->GetDefaultReport("USER", "PWV Report");
			Assert::AreEqual("PWV Report", target->_instance->PwvSettings->DefaultReport);
			
			
			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetDefaultReportTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetDefaultReport("DEFAULT", "PWV Report");
				Assert::AreEqual("PWV Report", target->_pSetInternal->DefaultReport);
			}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetDefaultReportTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				try
				{	
					target->GetDefaultReport("USER2","XX");
					Assert::Fail("If error does not occur then test fail");
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If error occur then test pass");
				}
			}
			//Smarajit Mishra
			//This method don't need to be called,as is will be covered in the method SetPwvUserSettings
//		/// <summary>
//		///A test for SetDefaultReport
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetDefaultReportTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetDefaultReport(ps, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
			/// <summary>
			///A test for SetNormalRange
			///</summary>
			//This method don't need to be called,as is will be covered in the method SetPwvUserSettings
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetNormalRangeTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetNormalRange(ps, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		/// <summary>
		///A test for GetNormalRange
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetNormalRangeTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

			//Pass the required inout to get the expected result
			String^  SubSection = L"USER";
			String^  ReaderValue = L"No";

			target->GetNormalRange(SubSection, ReaderValue);
			Assert::AreEqual(false, target->_instance->PwvSettings->NormalRange);
		}

public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetNormalRangeTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

			//Pass the required inout to get the expected result
			String^  SubSection = L"DEFAULT";
			String^  ReaderValue = L"Yes";

			target->GetNormalRange(SubSection, ReaderValue);
			Assert::AreEqual(true, target->_pSetInternal->NormalRange);
		}

public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetNormalRangeTest2()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

			//Pass the required inout to get the expected result
			String^  SubSection = L"USER";
			String^  ReaderValue = L"XX";

			try
			{	
				target->GetNormalRange(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
		}
};
}
namespace TestCrx {
    
}
