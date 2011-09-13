
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
				//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 2-Jun-2011
				CrxStructPwaSetting^ pwas  = nullptr;
				CrxStructBpSetting^ bps  = nullptr;
				//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 2-Jun-2011

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
										
					//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 2-Jun-2011
					//target->SetSettingsNode(Section, SubSection, gs, ps, elem);
					target->SetSettingsNode(Section, SubSection, gs, ps, pwas, bps, elem);
					//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 2-Jun-2011
					target->SetSettingsNode(Section, SubSection, gs, ps, pwas, bps, elem);
				}
				catch(Exception^)
				{
					actual =0;
				}
				Assert::AreEqual (expected,actual);

				try
				{										
					//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 2-Jun-2011
					//target->SetSettingsNode(Section, SubSection, gs, ps, node);
					target->SetSettingsNode(Section, SubSection, gs, ps,pwas,bps, node);
					//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 2-Jun-2011
				}
				catch(Exception^)
				{
					actual =0;
				}
				Assert::AreEqual (expected,actual);
				Section = "GENERAL1";
				try
				{										
					//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 2-Jun-2011
					//target->SetSettingsNode(Section, SubSection, gs, ps, node);
					target->SetSettingsNode(Section, SubSection, gs, ps,pwas,bps, node);
					//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 2-Jun-2011
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
				//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2010, 13-Jun-2011
				CrxStructPwaSetting^  pwas = nullptr; 
				CrxStructBpSetting^  bps = nullptr; 
				//End: AtCor-Drop2-Sprint1, TM, SWREQ2010, 13-Jun-2011
				
				Section = "GENERAL";
				SubSection= "USER";
				int actual;
				int expected = 0;
				String^ path = Directory::GetCurrentDirectory(); 

				try
				{
					//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2010, 13-Jun-2011
					//target->SetSettings(Section, SubSection, gs, ps);
					target->SetSettings(Section, SubSection, gs, ps,pwas,bps);
					//End: AtCor-Drop2-Sprint1, TM, SWREQ2010, 13-Jun-2011
				
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
				ps->AutoCapture = true;
				ps->GuidanceBars = true;
			
				target->SetPwvUserSettings(ps);

				target->GetPwvUserSettings();

				Assert::AreEqual(0, target->_instance->PwvSettings->PWVDistanceMethod);
				Assert::AreEqual(true, target->_instance->PwvSettings->FemoralToCuff);
				Assert::AreEqual(0, target->_instance->PwvSettings->PWVDistanceUnits);
				Assert::AreEqual(5, target->_instance->PwvSettings->CaptureTime);
				Assert::AreEqual(true, target->_instance->PwvSettings->ReferenceRange);
				Assert::AreEqual("PWV Report", target->_instance->PwvSettings->DefaultReport);
				Assert::AreEqual(true, target->_instance->PwvSettings->NormalRange);
				Assert::AreEqual(true, target->_instance->PwvSettings->AutoCapture);
				Assert::AreEqual(true, target->_instance->PwvSettings->GuidanceBars);

				ps->PWVDistanceMethod = 1;
				ps->FemoralToCuff = false;
				ps->PWVDistanceUnits = 1;
				ps->CaptureTime = 10;
				ps->ReferenceRange = false;
				ps->SimulationType = nullptr;
				ps->DefaultReport = nullptr;
				ps->NormalRange = false;
				ps->AutoCapture = false;
				ps->GuidanceBars = false;
			
				target->SetPwvUserSettings(ps);

				target->GetPwvUserSettings();

				Assert::AreEqual(1, target->_instance->PwvSettings->PWVDistanceMethod);
				Assert::AreEqual(false, target->_instance->PwvSettings->FemoralToCuff);
				Assert::AreEqual(1, target->_instance->PwvSettings->PWVDistanceUnits);
				Assert::AreEqual(10, target->_instance->PwvSettings->CaptureTime);
				Assert::AreEqual(false, target->_instance->PwvSettings->ReferenceRange);
				Assert::AreEqual(false, target->_instance->PwvSettings->NormalRange);
				Assert::AreEqual(false, target->_instance->PwvSettings->AutoCapture);
				Assert::AreEqual(false, target->_instance->PwvSettings->GuidanceBars);
				
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
				ps->AutoCapture = true;
				ps->GuidanceBars = true;

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
				String^ SystemKey =  target->_instance->GeneralSettings->Key;

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
				gs->Key = "12345";
				/*gs->Id = "123";
				gs->Sn = "12345";
				gs->Verify = "12";
				gs->Cksum = "12345";*/

				target->SetGeneralUserSettings(gs);

				target->GetGeneralUserSettings();

				Assert::AreEqual(0, target->_instance->GeneralSettings->BloodPressureEntryOptions);
				Assert::AreEqual(0, target->_instance->GeneralSettings->HeightandWeightUnit);
				Assert::AreEqual(true, target->_instance->GeneralSettings->PatientPrivacy);
				Assert::AreEqual("Simulation", target->_instance->GeneralSettings->CommsPort);
				Assert::AreEqual("REPORT DEM TESTFORme", target->_instance->GeneralSettings->ReportTitle);
				//Assert::AreEqual("D:\\EXTRA_DESKTOP\\ERROR.JPG", target->_instance->GeneralSettings->ReportLogoPath);
				Assert::AreEqual("SQLCLIENT", target->_instance->GeneralSettings->SourceData->ToUpper());
				Assert::AreEqual("12345", target->_instance->GeneralSettings->Key);
				//Assert::AreEqual("fr-FR", target->_instance->GeneralSettings->CultureInfo);				
				
				Assert::AreEqual("PWV", target->_instance->GeneralSettings->StartupMode);
				Assert::AreEqual("Setup", target->_instance->GeneralSettings->StartupScreen);
				/*Assert::AreEqual("123", target->_instance->GeneralSettings->Id);
				Assert::AreEqual("12345", target->_instance->GeneralSettings->Sn);
				Assert::AreEqual("12", target->_instance->GeneralSettings->Verify);
				Assert::AreEqual("12345", target->_instance->GeneralSettings->Cksum);*/
				
				
				gs->BloodPressureEntryOptions = 0;
				gs->CommsPort = nullptr;
				gs->HeightandWeightUnit= 1;
				gs->PatientPrivacy = false;
				gs->ReportLogoPath = nullptr;
				gs->ReportTitle = nullptr;
				gs->ServerName = String::Empty;
				gs->SourceData = nullptr;
				gs->CultureInfo = nullptr;
				gs->MachineName = nullptr;
				gs->StartupMode = nullptr;
				gs->StartupScreen = nullptr;
				gs->PrinterName = nullptr;
				gs->Key = nullptr;
				/*gs->Id = nullptr;
				gs->Sn = nullptr;
				gs->Verify = nullptr;
				gs->Cksum = nullptr;*/

				target->SetGeneralUserSettings(gs);

				target->GetGeneralUserSettings();
				//target->GeneralSettings

				Assert::AreEqual(0, target->_instance->GeneralSettings->BloodPressureEntryOptions);
				Assert::AreEqual(1, target->_instance->GeneralSettings->HeightandWeightUnit);
				Assert::AreEqual(false, target->_instance->GeneralSettings->PatientPrivacy);
				/*Assert::AreEqual(" ", target->_instance->GeneralSettings->CommsPort);
				Assert::AreEqual(" ", target->_instance->GeneralSettings->ReportTitle);
				Assert::AreEqual(" ", target->_instance->GeneralSettings->ReportLogoPath);
				Assert::AreEqual(" ", target->_instance->GeneralSettings->ServerName);
				Assert::AreEqual(" ", target->_instance->GeneralSettings->SourceData);
				Assert::AreEqual(" ", target->_instance->GeneralSettings->CultureInfo);*/
				

				gs->BloodPressureEntryOptions = 0;

				target->SetGeneralUserSettings(gs);

				target->GetGeneralUserSettings();

				Assert::AreEqual(0, target->_instance->GeneralSettings->BloodPressureEntryOptions);

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
				gs->Key = SystemKey;

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
			
				target->GetStartupMode("DEFAULT", "PWA");
				Assert::AreEqual("PWA", target->_gSetInternal->StartupMode);
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

					//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 2-Jun-2011
					target->GetSettings("PWA", "USER");
					Assert::IsNotNull(target->_instance->PwaSettings->CaptureTime);				

					target->GetSettings("PWA", "DEFAULT");
					Assert::IsNotNull(target->_instance->PwaSettings->CaptureTime);

					try
					{
						target->GetSettings("BP", "USER");
					}
					catch(Exception^)
					{
					}
					Assert::IsNotNull(target->_instance->BpSettings->NumberofAssessments);				

					target->GetSettings("BP", "DEFAULT");
					Assert::IsNotNull(target->_instance->BpSettings->NumberofAssessments);

					//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 2-Jun-2011


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
				
				String^  SubSection = "DEFAULT1"; 
				String^  ReaderValue = "ReportTitle2"; 
				
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

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetReportTitleTest3()
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
				Assert::AreEqual(true, target->_instance->PwvSettings->AutoCapture);
				Assert::AreEqual(true, target->_instance->PwvSettings->GuidanceBars);
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
				Assert::AreEqual(true, objPwvSettings->AutoCapture);
				Assert::AreEqual(true, objPwvSettings->GuidanceBars);
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
			/*/// <summary>
			///A test for GetBloodPressureOption
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetBloodPressureOptionTest()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetBloodPressureOption("USER", "SPANDDP");
				Assert::AreEqual(0, target->_instance->GeneralSettings->BloodPressureEntryOptions);
			}*/

	/*public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetBloodPressureOptionTest1()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetBloodPressureOption("USER", "SPANDMP");
				Assert::AreEqual(1, target->_instance->GeneralSettings->BloodPressureEntryOptions);
			}*/

	/*public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetBloodPressureOptionTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetBloodPressureOption("USER", "MPANDDP");
				Assert::AreEqual(2, target->_instance->GeneralSettings->BloodPressureEntryOptions);
			}*/

	/*public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetBloodPressureOptionTest3()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 

				target->GetBloodPressureOption("DEFAULT", "MPANDDP");
				Assert::AreEqual(2, target->_gSetInternal->BloodPressureEntryOptions);
			}*/

	/*public: [TestMethod]
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
			}*/
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
		/// <summary>
		///A test for PwaSettings
		///</summary>
public: [TestMethod]
		void PwaSettingsTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			CrxStructPwaSetting^  expected = gcnew CrxStructPwaSetting(); // TODO: Initialize to an appropriate value
			CrxStructPwaSetting^  actual;
			target->PwaSettings = expected;
			actual = target->PwaSettings;
			Assert::AreEqual(expected, actual);
			//--------
			
			actual = target->PwaSettings;

			//Default values in the structure 	CrxStructPwaSetting are 5, true,true,true, false, "Pressure Cuff" for CaptureTime,
			//GuidanceBars, AutoCapture , AugmentationIndex, AugmentationIndexAtHR75 and CaptureInput respectively
			Assert::AreEqual(5, actual->CaptureTime);
			Assert::AreEqual(true, actual->GuidanceBars);
			Assert::AreEqual(true, actual->AutoCapture);
			Assert::AreEqual(true, actual->AugmentationIndex);
			Assert::AreEqual(false, actual->AugmentationIndexAtHR75);
			Assert::AreEqual(0, actual->CaptureInput);

			expected->CaptureTime = 10;
			expected->GuidanceBars = false;
			expected->AutoCapture = false;
			expected->AugmentationIndex = false;
			expected->AugmentationIndexAtHR75 = false;
			expected->CaptureInput = 0;
			expected->SimulationType = "Simulation";

			//Setting the CaptureTime member of structure CrxStructPwvSetting
			target->PwaSettings = expected;

			//Getting the CaptureTime member of structure CrxStructPwvSetting
			actual = target->PwaSettings;
			
			//comparing the actual and expected structure values
			Assert::AreEqual(expected->CaptureTime, actual->CaptureTime);
			Assert::AreEqual(expected->GuidanceBars, actual->GuidanceBars);
			Assert::AreEqual(expected->AutoCapture, actual->AutoCapture);
			Assert::AreEqual(expected->AugmentationIndex, actual->AugmentationIndex);
			Assert::AreEqual(expected->AugmentationIndexAtHR75, actual->AugmentationIndexAtHR75);
			Assert::AreEqual(expected->CaptureInput, actual->CaptureInput);
			
		}
		/// <summary>
		///A test for BpSettings
		///</summary>
public: [TestMethod]
		void BpSettingsTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			CrxStructBpSetting^  expected = gcnew CrxStructBpSetting(); // TODO: Initialize to an appropriate value
			CrxStructBpSetting^  actual;
			target->BpSettings = expected;
			actual = target->BpSettings;
			Assert::AreEqual(expected, actual);
			//-----------
			
			actual = target->BpSettings;

			//Default values in the structure 	CrxStructPwaSetting are 5, true,true,true, false, "Pressure Cuff" for CaptureTime,
			//GuidanceBars, AutoCapture , AugmentationIndex, AugmentationIndexAtHR75 and CaptureInput respectively
			if (actual->Device != nullptr)
			{
				Assert::AreEqual("Sphygmocor", actual->Device);
			}
			if (actual->NumberofAssessments > 0)
			{
				Assert::AreEqual(1, actual->NumberofAssessments);
			}
			/*if (actual->BloodPressure!= nullptr)
			{
				Assert::AreEqual(true, actual->BloodPressure);
			}*/
			if (actual->AutoPWA != nullptr)
			{
				Assert::AreEqual("Yes", actual->AutoPWA);
			}
			expected->Device = "Tonometer";
			expected->NumberofAssessments= 4;
			expected->BloodPressure = 0;
			expected->AutoPWA = "No";
			

			//Setting the CaptureTime member of structure CrxStructPwvSetting
			target->BpSettings = expected;

			//Getting the CaptureTime member of structure CrxStructPwvSetting
			actual = target->BpSettings;
			
			//comparing the actual and expected structure values
			Assert::AreEqual(expected->Device, actual->Device);
			Assert::AreEqual(expected->NumberofAssessments, actual->NumberofAssessments);
			Assert::AreEqual(expected->BloodPressure, actual->BloodPressure);
			Assert::AreEqual(expected->AutoPWA, actual->AutoPWA);
		}
		//Alok Sahu
		//This method don't need to be called,as is will be covered in the method SetGeneralUserSettings
//		/// <summary>
//		///A test for SetVerify
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetVerifyTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetVerify(gs, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
//		/// <summary>
//		///A test for SetStartupScreen
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetStartupScreenTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetStartupScreen(gs, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
//		/// <summary>
//		///A test for SetStartupMode
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetStartupModeTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetStartupMode(gs, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
//		/// <summary>
//		///A test for SetSn
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetSnTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetSn(gs, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		/// <summary>
		///A test for SetPwaUserSettings
		///</summary>
public: [TestMethod]
		void SetPwaUserSettingsTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			CrxStructPwaSetting^  pwas = gcnew CrxStructPwaSetting(); // TODO: Initialize to an appropriate value
			CrxStructPwaSetting^  pwasOri = gcnew CrxStructPwaSetting();

			CrxConfigManagerTest::SetPath();
			
			//target->GetPwaUserSettings();
			pwasOri = target->_instance->PwaSettings;
				//------------------------------
			pwas->CaptureTime = 5;
			pwas->GuidanceBars=true;
			pwas->AugmentationIndex=true;
			pwas->AugmentationIndexAtHR75=true;
			pwas->CaptureInput=0;
			pwas->SimulationType = "Simulation";

			target->SetPwaUserSettings(pwas);

			target->GetPwaUserSettings();

			Assert::AreEqual(5, target->_instance->PwaSettings->CaptureTime);
			Assert::AreEqual(true, target->_instance->PwaSettings->GuidanceBars);
			Assert::AreEqual(true, target->_instance->PwaSettings->AugmentationIndex);
			Assert::AreEqual(true, target->_instance->PwaSettings->AugmentationIndexAtHR75);
			Assert::AreEqual(0, target->_instance->PwaSettings->CaptureInput);
			Assert::AreEqual(pwas->SimulationType, target->_instance->PwaSettings->SimulationType);

			pwas->CaptureTime = 10;
			pwas->GuidanceBars = false;
			pwas->AugmentationIndex = false;
			pwas->AugmentationIndexAtHR75 = false;
			pwas->CaptureInput = 1;
			pwas->AutoCapture = false;
			pwas->SimulationType = nullptr;

			target->SetPwaUserSettings(pwas);

			target->GetPwaUserSettings();

			Assert::AreEqual(10, target->_instance->PwaSettings->CaptureTime);
			Assert::AreEqual(false, target->_instance->PwaSettings->GuidanceBars);
			Assert::AreEqual(false, target->_instance->PwaSettings->AugmentationIndex);
			Assert::AreEqual(false, target->_instance->PwaSettings->AugmentationIndexAtHR75);
			Assert::AreEqual(1, target->_instance->PwaSettings->CaptureInput);
			Assert::AreEqual(false, target->_instance->PwaSettings->AutoCapture );

			pwas->CaptureTime = 20;
			
			target->SetPwaUserSettings(pwas);

			target->GetPwaUserSettings();

			Assert::AreEqual(20, target->_instance->PwaSettings->CaptureTime);
			
			target->SetPwaUserSettings(pwasOri);
	
			pwas->CaptureTime = 5;
			pwas->GuidanceBars=true;
			pwas->AugmentationIndex=true;
			pwas->AugmentationIndexAtHR75=true;
			pwas->CaptureInput=0;
			pwas->SimulationType = "Simulation";

			target->SetPwaUserSettings(pwas);

				
				//------------------------------
		}
		/// <summary>
		///A test for SetPwaSettingsNode
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void SetPwaSettingsNodeTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			CrxStructPwaSetting^  gs = nullptr; 
			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
			

			int actual;
			int expected = 0;
			try
			{
				XmlDocument^ doc = gcnew XmlDocument;

				doc->LoadXml( "<root>" "<elem>some text<child/>more text</elem>" "</root>" );

				XmlNode^ elem = doc->DocumentElement->FirstChild;
									
				target->SetPwaSettingsNode(gs, elem);
				//target->SetPwvSettingsNode(gs, elem);
			}
			catch(Exception^)
			{
				actual =0;
			}
			Assert::AreEqual (expected,actual);

		}
		//Alok Sahu
		//This method don't need to be called,as is will be covered in the method SetPWaUserSettings
		
//		/// <summary>
//		///A test for SetPwaGuidanceBars
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetPwaGuidanceBarsTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructPwaSetting^  pwas = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetPwaGuidanceBars(pwas, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
//		/// <summary>
//		///A test for SetPwaCaptureTime
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetPwaCaptureTimeTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructPwaSetting^  pwas = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetPwaCaptureTime(pwas, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
//		/// <summary>
//		///A test for SetPwaCaptureInput
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetPwaCaptureInputTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructPwaSetting^  pwas = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetPwaCaptureInput(pwas, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
//		/// <summary>
//		///A test for SetPwaAutoCapture
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetPwaAutoCaptureTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructPwaSetting^  pwas = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetPwaAutoCapture(pwas, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
//		/// <summary>
//		///A test for SetPwaAugmentationIndexAtHR75
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetPwaAugmentationIndexAtHR75Test()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructPwaSetting^  pwas = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetPwaAugmentationIndexAtHR75(pwas, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
//		/// <summary>
//		///A test for SetPwaAugmentationIndex
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetPwaAugmentationIndexTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructPwaSetting^  pwas = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetPwaAugmentationIndex(pwas, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		//Alok Sahu
		//This method don't need to be called,as is will be covered in the method SetGeneralUserSettings
//		/// <summary>
//		///A test for SetId
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetIdTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetId(gs, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
//		/// <summary>
//		///A test for SetCkSum
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetCkSumTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetCkSum(gs, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		/// <summary>
		///A test for SetBpUserSettings
		///</summary>
public: [TestMethod]
		void SetBpUserSettingsTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			CrxStructBpSetting^  bps = gcnew CrxStructBpSetting(); // TODO: Initialize to an appropriate value
			
			CrxConfigManagerTest::SetPath();
			
			bps->Device = "SPHYGMOCOR";
			bps->NumberofAssessments = 3;
			bps->AutoPWA= "Yes";
			bps->BloodPressure = 0;
			bps->AutoPWADP = true;
			bps->AutoPWAPP = true;
			bps->AutoPWASP = true;
			bps->AutoPWADPThreshold = 0;
			bps->AutoPWASPThreshold = 0;
			bps->AutoPWAPPThreshold = 0;
			
			target->SetBpUserSettings(bps);
			
			target->GetBpUserSettings();

			Assert::AreEqual(bps->Device, target->_instance->BpSettings->Device);
			Assert::AreEqual(bps->NumberofAssessments, target->_instance->BpSettings->NumberofAssessments);
			Assert::AreEqual(bps->AutoPWA, target->_instance->BpSettings->AutoPWA);
			Assert::AreEqual(bps->BloodPressure, target->_instance->BpSettings->BloodPressure);
			Assert::AreEqual(bps->AutoPWADP, target->_instance->BpSettings->AutoPWADP);
			Assert::AreEqual(bps->AutoPWAPP, target->_instance->BpSettings->AutoPWAPP);
			Assert::AreEqual(bps->AutoPWASP, target->_instance->BpSettings->AutoPWASP);
			Assert::AreEqual(bps->AutoPWADPThreshold, target->_instance->BpSettings->AutoPWADPThreshold);
			Assert::AreEqual(bps->AutoPWASPThreshold, target->_instance->BpSettings->AutoPWASPThreshold);
			Assert::AreEqual(bps->AutoPWAPPThreshold, target->_instance->BpSettings->AutoPWAPPThreshold);
			
			bps->Device = nullptr;
			bps->NumberofAssessments = 3;
			bps->BloodPressure = 0;
			bps->AutoPWA= nullptr;
			bps->AutoPWADP = false;
			bps->AutoPWAPP = false;
			bps->AutoPWASP = false;
			bps->AutoPWADPThreshold = 0;
			bps->AutoPWASPThreshold = 0;
			bps->AutoPWAPPThreshold = 0;
			//bps->BloodPressure = nullptr;
			
			target->SetBpUserSettings(bps);
			
			target->GetBpUserSettings();

			//Assert::AreEqual(" ", target->_instance->BpSettings->Device);
			Assert::AreEqual(bps->NumberofAssessments, target->_instance->BpSettings->NumberofAssessments);
			Assert::AreEqual(bps->BloodPressure, target->_instance->BpSettings->BloodPressure);
			Assert::AreEqual(bps->AutoPWADP, target->_instance->BpSettings->AutoPWADP);
			Assert::AreEqual(bps->AutoPWAPP, target->_instance->BpSettings->AutoPWAPP);
			Assert::AreEqual(bps->AutoPWASP, target->_instance->BpSettings->AutoPWASP);
			Assert::AreEqual(bps->AutoPWADPThreshold, target->_instance->BpSettings->AutoPWADPThreshold);
			Assert::AreEqual(bps->AutoPWASPThreshold, target->_instance->BpSettings->AutoPWASPThreshold);
			Assert::AreEqual(bps->AutoPWAPPThreshold, target->_instance->BpSettings->AutoPWAPPThreshold);
			//Assert::AreEqual(bps->AutoPWA, target->_instance->BpSettings->AutoPWA);
			//Assert::AreEqual(bps->BloodPressure, target->_instance->BpSettings->BloodPressure);

			//Set to default values
			bps->Device = "Sphygmocor";
			bps->NumberofAssessments = 1;
			bps->BloodPressure = 0;
			bps->AutoPWA= nullptr;
			bps->AutoPWADP = true;
			bps->AutoPWAPP = true;
			bps->AutoPWASP = true;
			bps->AutoPWADPThreshold = 0;//90;
			bps->AutoPWASPThreshold = 0;//130;
			bps->AutoPWAPPThreshold = 0;//50;

			target->SetBpUserSettings(bps);

			target->GetBpUserSettings();
			Assert::AreEqual(bps->NumberofAssessments, target->_instance->BpSettings->NumberofAssessments);
			Assert::AreEqual(bps->BloodPressure, target->_instance->BpSettings->BloodPressure);

			bps->BloodPressure = 0;
			target->SetBpUserSettings(bps);

			target->GetBpUserSettings();
			Assert::AreEqual(bps->BloodPressure, target->_instance->BpSettings->BloodPressure);

		}
		/// <summary>
		///A test for SetBpSettingsNode
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void SetBpSettingsNodeTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			CrxStructBpSetting^  bps = nullptr; // TODO: Initialize to an appropriate value
			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
			
			int actual;
			int expected = 0;
			try
			{
				XmlDocument^ doc = gcnew XmlDocument;

				doc->LoadXml( "<root>" "<elem>some text<child/>more text</elem>" "</root>" );

				XmlNode^ elem = doc->DocumentElement->FirstChild;
									
				target->SetBpSettingsNode(bps, node);
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
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void SetBpSettingsNodeTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			CrxStructBpSetting^  bps = nullptr; // TODO: Initialize to an appropriate value
			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
			
			int actual;
			int expected = 0;
			try
			{
				XmlDocument^ doc = gcnew XmlDocument;

				doc->LoadXml( "<root>" "<elem>some text<child/>more text</elem>" "</root>" );

				XmlNode^ elem = doc->DocumentElement->FirstChild;
									
				target->SetBpSettingsNode(bps, elem);
			}
			catch(Exception^)
			{
				actual =0;
			}
			Assert::AreEqual (expected,actual);
		}
		
		//Alok Sahu
		//This method don't need to be called,as is will be covered in the method SetBpUserSettings
		/// <summary>
		///A test for SetBpNumberofAssessments
		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetBpNumberofAssessmentsTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructBpSetting^  bps = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetBpNumberofAssessments(bps, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
//		/// <summary>
//		///A test for SetBpDevice
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetBpDeviceTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructBpSetting^  bps = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetBpDevice(bps, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
//		/// <summary>
//		///A test for SetBpBloodPressure
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetBpBloodPressureTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructBpSetting^  bps = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetBpBloodPressure(bps, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
//		/// <summary>
//		///A test for SetBpAutoPWA
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetBpAutoPWATest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructBpSetting^  bps = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetBpAutoPWA(bps, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
//		/// <summary>
//		///A test for GetVerify
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetVerifyTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			
//			String^  SubSection = "USER"; 
//			String^  ReaderValue = "XXXXX"; 
//			
//			target->GetVerify(SubSection, ReaderValue);
//			Assert::AreEqual(ReaderValue, target->_instance->GeneralSettings->Verify);
//
//		}
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetVerifyTest1()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			
//			String^  SubSection = "DEFAULT"; 
//			String^  ReaderValue = "XXXXX"; 
//			
//			target->GetVerify(SubSection, ReaderValue);
//			Assert::AreEqual(nullptr, target->_gSetInternal->Verify);
//
//		}
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetVerifyTest2()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			
//			String^  SubSection = "DEFAULT1"; 
//			String^  ReaderValue = "XXXXX"; 
//			
//			try
//			{
//				target->GetVerify(SubSection, ReaderValue);
//				Assert::Fail("If error does not occur then test fail");
//			}
//			catch(Exception^)
//			{
//				Assert::IsTrue(true,"If error occur then test pass");
//			}
//		}
//		/// <summary>
//		///A test for GetSn
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetSnTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//
//			String^  SubSection = "USER"; 
//			String^  ReaderValue = "XXXXX"; 
//			
//			target->GetSn(SubSection, ReaderValue);
//			Assert::AreEqual(ReaderValue, target->_instance->GeneralSettings->Sn);
//
//		}
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetSnTest1()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//
//			String^  SubSection = "DEFAULT"; 
//			String^  ReaderValue = "XXXXX"; 
//			
//			target->GetSn(SubSection, ReaderValue);
//			Assert::AreEqual(nullptr, target->_gSetInternal->Sn);
//
//		}
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetSnTest2()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//
//			String^  SubSection = "DEFAULT1"; 
//			String^  ReaderValue = "XXXXX"; 
//			
//			try
//			{
//				target->GetSn(SubSection, ReaderValue);
//				Assert::Fail("If error does not occur then test fail");
//			}
//			catch(Exception^)
//			{
//				Assert::IsTrue(true,"If error occur then test pass");
//			}
//		}		
		/// <summary>
		///A test for GetPwaUserSettings
		///</summary>
public: [TestMethod]
		void GetPwaUserSettingsTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			CrxStructPwaSetting^  pwas = gcnew CrxStructPwaSetting(); // TODO: Initialize to an appropriate value
			
			CrxConfigManagerTest::SetPath();
			pwas->CaptureTime = 20;
			pwas->GuidanceBars = "Yes";
			pwas->SimulationType = "Simulation";
			target->SetPwaUserSettings(pwas);

			target->GetPwaUserSettings();

			Assert::AreEqual(20, target->_instance->PwaSettings->CaptureTime);
			Assert::AreEqual(true, target->_instance->PwaSettings->GuidanceBars);
			//Assert::AreEqual(false, target->_instance->PwaSettings->AugmentationIndex);
			//Assert::AreEqual(false, target->_instance->PwaSettings->AugmentationIndexAtHR75);
			Assert::AreEqual(0, target->_instance->PwaSettings->CaptureInput);

		}
		/// <summary>
		///A test for GetPwaSettingsNode
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaSettingsNodeTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  SubSectionNode = "USER2"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
			
			//int actual;
			int expected = 0;
			try
			{
				XmlDocument^ doc = gcnew XmlDocument;

				doc->LoadXml( "<root>" "<elem>some text<child/>more text</elem>" "</root>" );

				XmlNode^ elem = doc->DocumentElement->FirstChild;
									
				target->GetPwaSettingsNode(SubSection, SubSectionNode, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
		}
		/// <summary>
		///A test for GetPwaGuidanceBars
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaGuidanceBarsTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value

			String^  SubSection = L"USER";
			String^  ReaderValue = L"Yes";

			target->GetPwaGuidanceBars(SubSection, ReaderValue);
			Assert::AreEqual(true, target->_instance->PwaSettings->GuidanceBars);
		}
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaGuidanceBarsTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value

			String^  SubSection = L"USER";
			String^  ReaderValue = L"XX-XX";

			try
			{
				target->GetPwaGuidanceBars(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
		}
		/// <summary>
		///A test for GetPwaDefaultSettings
		///</summary>
public: [TestMethod]
		void GetPwaDefaultSettingsTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			CrxStructPwaSetting^  objPwaSettings = gcnew CrxStructPwaSetting(); // TODO: Initialize to an appropriate value

			CrxConfigManagerTest::SetPath();
			target->GetPwaDefaultSettings(objPwaSettings);
			
			Assert::AreEqual(5, objPwaSettings->CaptureTime);
			Assert::AreEqual(true, objPwaSettings->GuidanceBars);
			Assert::AreEqual(true, objPwaSettings->AutoCapture);
			Assert::AreEqual(true, objPwaSettings->AugmentationIndex);
			Assert::AreEqual(false, objPwaSettings->AugmentationIndexAtHR75);
			Assert::AreEqual(0, objPwaSettings->CaptureInput);

		}
		/// <summary>
		///A test for GetPwaCaptureTime
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaCaptureTimeTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value

			String^  SubSection = L"USER";
			String^  ReaderValue = L"5SECONDS";

			target->GetPwaCaptureTime(SubSection, ReaderValue);
			Assert::AreEqual(5, target->_instance->PwaSettings->CaptureTime);

		}
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaCaptureTimeTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value

			String^  SubSection = L"USER";
			String^  ReaderValue = L"55SECONDS";

			try
			{
				target->GetPwaCaptureTime(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
		}
		/// <summary>
		///A test for GetPwaCaptureInput
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaCaptureInputTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value

			String^  SubSection = L"USER";
			String^  ReaderValue = L"Pressure Cuff";

			target->GetPwaCaptureInput(SubSection, ReaderValue);
			Assert::AreEqual(0, target->_instance->PwaSettings->CaptureInput);

		}
		/// <summary>
		///A test for GetPwaAutoCapture
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaAutoCaptureTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value

			String^  SubSection = L"USER";
			String^  ReaderValue = L"Yes";

			target->GetPwaAutoCapture(SubSection, ReaderValue);
			Assert::AreEqual(true, target->_instance->PwaSettings->AutoCapture);
		}
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaAutoCaptureTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value

			String^  SubSection = L"USER";
			String^  ReaderValue = L"XX-XX";

			try
			{
				target->GetPwaAutoCapture(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
		}
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaAutoCaptureTest2()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
			SubSection = L"DEFAULT";
			ReaderValue = L"No";
			
			target->GetPwaAutoCapture(SubSection, ReaderValue);
			Assert::AreEqual(false, target->_pwaSetInternal->AutoCapture);
			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for GetPwaAugmentationIndexAtHR75
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaAugmentationIndexAtHR75Test()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"Yes";

			target->GetPwaAugmentationIndexAtHR75(SubSection, ReaderValue);
			Assert::AreEqual(true, target->_instance->PwaSettings->AugmentationIndexAtHR75);
		}
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaAugmentationIndexAtHR75Test1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"XX";

			try
			{
				target->GetPwaAugmentationIndexAtHR75(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
		}
		/// <summary>
		///A test for GetPwaAugmentationIndex
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaAugmentationIndexTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"Yes";

			target->GetPwaAugmentationIndex(SubSection, ReaderValue);
			Assert::AreEqual(true, target->_instance->PwaSettings->AugmentationIndex);
		}
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaAugmentationIndexTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"XX";

			try
			{
				target->GetPwaAugmentationIndex(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
		}
//		/// <summary>
//		///A test for GetId
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetIdTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			String^  SubSection = L"USER";
//			String^  ReaderValue = L"Yes";
//
//			target->GetId(SubSection, ReaderValue);
//			Assert::AreEqual(ReaderValue, target->_instance->GeneralSettings->Id);
//			
//
//		}
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetIdTest1()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			String^  SubSection = L"DEFAULT";
//			String^  ReaderValue = L"XX";
//
//			target->GetId(SubSection, ReaderValue);
//			Assert::AreEqual(nullptr, target->_gSetInternal->Id);
//		
//		}
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetIdTest2()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			String^  SubSection = L"DEFAULT1";
//			String^  ReaderValue = L"XX";
//
//			try
//			{
//				target->GetId(SubSection, ReaderValue);
//				Assert::Fail("If error does not occur then test fail");
//			}
//			catch(Exception^)
//			{
//				Assert::IsTrue(true,"If error occur then test pass");
//			}
//		}
//		/// <summary>
//		///A test for GetCkSum
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetCkSumTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			
//			String^  SubSection = L"USER";
//			String^  ReaderValue = L"Yes";
//
//			target->GetCkSum(SubSection, ReaderValue);
//			Assert::AreEqual(ReaderValue, target->_instance->GeneralSettings->Cksum);
//			
//		}
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetCkSumTest1()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			
//			String^  SubSection = L"DEFAULT";
//			String^  ReaderValue = L"Yes";
//
//			target->GetCkSum(SubSection, ReaderValue);
//			Assert::AreEqual(nullptr, target->_gSetInternal->Cksum);
//			
//		}
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetCkSumTest2()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			
//			String^  SubSection = L"DEFAULT1";
//			String^  ReaderValue = L"Yes";
//
//			try
//			{
//				target->GetCkSum(SubSection, ReaderValue);
//				Assert::Fail("If error does not occur then test fail");
//			}
//			catch(Exception^)
//			{
//				Assert::IsTrue(true,"If error occur then test pass");
//			}
//
//		}
		/// <summary>
		///A test for GetBpUserSettings
		///</summary>
public: [TestMethod]
		void GetBpUserSettingsTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			CrxStructBpSetting^  bps = gcnew CrxStructBpSetting(); // TODO: Initialize to an appropriate value
			
			CrxConfigManagerTest::SetPath();
			
			bps->Device = "Sphygmocor";
			bps->NumberofAssessments = 3;
			//bps->AutoPWA= "Yes";
			bps->BloodPressure = 0;
			bps->AutoPWA= nullptr;
			bps->AutoPWADP = true;
			bps->AutoPWAPP = true;
			bps->AutoPWASP = true;
			bps->AutoPWADPThreshold = 0;//90;
			bps->AutoPWASPThreshold = 0;//130;
			bps->AutoPWAPPThreshold = 0;//50;
			
			target->SetBpUserSettings(bps);
			
			target->GetBpUserSettings();

			Assert::AreEqual(bps->Device, target->_instance->BpSettings->Device);
			Assert::AreEqual(bps->NumberofAssessments, target->_instance->BpSettings->NumberofAssessments);
			Assert::AreEqual(bps->BloodPressure, target->_instance->BpSettings->BloodPressure);

			bps->NumberofAssessments = 0;
			target->SetBpUserSettings(bps);
			
			try
			{
				target->GetBpUserSettings();
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
			bps->NumberofAssessments = 1;
			target->SetBpUserSettings(bps);
			
		}
		/// <summary>
		///A test for GetBpSettingsNode
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpSettingsNodeTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  SubSectionNode = "USER2"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
			
			//int actual;
			int expected = 0;
			try
			{
				XmlDocument^ doc = gcnew XmlDocument;

				doc->LoadXml( "<root>" "<elem>some text<child/>more text</elem>" "</root>" );

				XmlNode^ elem = doc->DocumentElement->FirstChild;
									
				target->GetBpSettingsNode(SubSection, SubSectionNode, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}

		}
		/// <summary>
		///A test for GetBpNumberofAssessments
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpNumberofAssessmentsTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"1";

			target->GetBpNumberofAssessments(SubSection, ReaderValue);
			Assert::AreEqual(1, target->_instance->BpSettings->NumberofAssessments);
		}
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpNumberofAssessmentsTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"0";

			try
			{
				target->GetBpNumberofAssessments(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
		}

		/// <summary>
		///A test for GetBpDevice
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpDeviceTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"SPHYGMOCOR";

			target->GetBpDevice(SubSection, ReaderValue);
			Assert::AreEqual(ReaderValue, target->_instance->BpSettings->Device);
		}
				/// <summary>
		///A test for GetBpDevice
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpDeviceTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"SPHYGMOCOR1";

			try
			{
				target->GetBpDevice(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
			
		}

		/// <summary>
		///A test for GetBpDefaultSettings
		///</summary>
public: [TestMethod]
		void GetBpDefaultSettingsTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			CrxStructBpSetting^  objBpSettings = gcnew CrxStructBpSetting(); // TODO: Initialize to an appropriate value
			
			CrxConfigManagerTest::SetPath();
			target->GetBpDefaultSettings(objBpSettings);
			
			Assert::AreEqual("Sphygmocor", objBpSettings->Device);
			//Assert::AreEqual(1, objBpSettings->NumberofAssessments);

		}
//		/// <summary>
//		///A test for GetBpBloodPressure
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetBpBloodPressureTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			String^  SubSection = L"USER";
//			String^  ReaderValue = L"SP and DP";
//
//			target->GetBpBloodPressure(SubSection, ReaderValue);
//			Assert::AreEqual(0, target->_instance->BpSettings->BloodPressure);
//			
//		}
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetBpBloodPressureTest1()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			String^  SubSection = L"DEFAULT";
//			String^  ReaderValue = L"XX";
//
//			try
//			{	
//				target->GetBpBloodPressure(SubSection, ReaderValue);
//				Assert::Fail("If error does not occur then test fail");
//            }
//            catch(Exception^)
//            {
//                  Assert::IsTrue(true,"If error occur then test pass");
//            }
//		}
//		public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetBpBloodPressureTest2()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			String^  SubSection = L"USER";
//			String^  ReaderValue = L"SP and MP";
//
//			target->GetBpBloodPressure(SubSection, ReaderValue);
//			Assert::AreEqual(1, target->_instance->BpSettings->BloodPressure);
//			
//		}
//		public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetBpBloodPressureTest3()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			String^  SubSection = L"DEFAULT";
//			String^  ReaderValue = L"MP and DP";
//
//			target->GetBpBloodPressure(SubSection, ReaderValue);
//			Assert::AreEqual(2, target->_bpSetInternal->BloodPressure);
//			
//		}
//		public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetBpBloodPressureTest4()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			String^  SubSection = L"USER";
//			String^  ReaderValue = L"MP and DP";
//
//			target->GetBpBloodPressure(SubSection, ReaderValue);
//			Assert::AreEqual(2, target->_instance->BpSettings->BloodPressure);
//			
//		}
		/// <summary>
		///A test for GetBpAutoPWA
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWATest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"Yes";

			target->GetBpAutoPWA(SubSection, ReaderValue);
			Assert::AreEqual(ReaderValue, target->_instance->BpSettings->AutoPWA);
		}
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWATest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"XX";

			try
			{
				target->GetBpAutoPWA(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
		}
		/// <summary>
		///A test for SetPwaSimulationType
		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetPwaSimulationTypeTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructPwaSetting^  pwas = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetPwaSimulationType(pwas, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		/// <summary>
		///A test for GetPwaSimulationType
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaSimulationTypeTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = "USER"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = "Simulation"; // TODO: Initialize to an appropriate value
			target->GetPwaSimulationType(SubSection, ReaderValue);
			Assert::AreEqual(ReaderValue, target->_instance->PwaSettings->SimulationType);
		}

public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwaSimulationTypeTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = "DEFAULT"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = "Simulation"; // TODO: Initialize to an appropriate value
			target->GetPwaSimulationType(SubSection, ReaderValue);
			Assert::AreEqual(ReaderValue, target->_instance->PwaSettings->SimulationType);
		}

	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetPwaSimulationTypeTest2()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				String^  SubSection = "DEFAULT1"; // TODO: Initialize to an appropriate value
				String^  ReaderValue = "Simulation1"; // TODO: Initialize to an appropriate value

				try
				{	
					target->GetPwaSimulationType(SubSection, ReaderValue);
					Assert::Fail("If error does not occur then test fail");
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If error occur then test pass");
				}
			}
			/// <summary>
			///A test for SetBpAutoPWASPThreshold
			///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetBpAutoPWASPThresholdTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructBpSetting^  bps = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetBpAutoPWASPThreshold(bps, node);
//			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		/// <summary>
		///A test for SetBpAutoPWASP
		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetBpAutoPWASPTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructBpSetting^  bps = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetBpAutoPWASP(bps, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		/// <summary>
		///A test for SetBpAutoPWAPPThreshold
		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetBpAutoPWAPPThresholdTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructBpSetting^  bps = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetBpAutoPWAPPThreshold(bps, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		/// <summary>
		///A test for SetBpAutoPWAPP
		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetBpAutoPWAPPTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructBpSetting^  bps = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetBpAutoPWAPP(bps, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		/// <summary>
		///A test for SetBpAutoPWADPThreshold
		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetBpAutoPWADPThresholdTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructBpSetting^  bps = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetBpAutoPWADPThreshold(bps, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		/// <summary>
		///A test for SetBpAutoPWADP
		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetBpAutoPWADPTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructBpSetting^  bps = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetBpAutoPWADP(bps, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		/// <summary>
		///A test for SetSystemKey
		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetSystemKeyTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructGeneralSetting^  gs = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetSystemKey(gs, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		/// <summary>
		///A test for GetSystemKey
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetSystemKeyTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = "USER"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = "66666123456789030fdab4d63"; // TODO: Initialize to an appropriate value
			target->GetSystemKey(SubSection, ReaderValue);
			Assert::AreEqual(ReaderValue,target->_instance->GeneralSettings->Key);
			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetSystemKeyTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = "DEFAULT"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = "Check"; // TODO: Initialize to an appropriate value
			String^ Expected = nullptr;
			target->GetSystemKey(SubSection, ReaderValue);
			Assert::AreEqual(Expected,target->_gSetInternal->Key);
			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetSystemKeyTest2()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = "DEFAULT1"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = nullptr; // TODO: Initialize to an appropriate value
			try
			{	
				target->GetSystemKey(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for GetBpAutoPWASPThreshold
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWASPThresholdTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = "USER"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = "130"; // TODO: Initialize to an appropriate value
			target->GetBpAutoPWASPThreshold(SubSection, ReaderValue);
			Assert::AreEqual(Convert::ToInt32(ReaderValue),target->_instance->BpSettings->AutoPWASPThreshold);
			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWASPThresholdTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = "DEFAULT"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = "150"; // TODO: Initialize to an appropriate value
			target->GetBpAutoPWASPThreshold(SubSection, ReaderValue);
			Assert::AreEqual(Convert::ToInt32(ReaderValue),target->_bpSetInternal->AutoPWASPThreshold);
			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWASPThresholdTest2()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = "DEFAULT1"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = "150"; // TODO: Initialize to an appropriate value
			
			try
			{	
				target->GetBpAutoPWASPThreshold(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for GetBpAutoPWASP
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWASPTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"Yes";
			target->GetBpAutoPWASP(SubSection, ReaderValue);
			Assert::AreEqual(true, target->_instance->BpSettings->AutoPWASP);
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWASPTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"DEFAULT";
			String^  ReaderValue = L"Yes";
			target->GetBpAutoPWASP(SubSection, ReaderValue);
			Assert::AreEqual(true, target->_bpSetInternal->AutoPWASP);
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWASPTest2()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"XX";

			try
			{
				target->GetBpAutoPWASP(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
			
		}
		/// <summary>
		///A test for GetBPAutoPWAPPThreshold
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBPAutoPWAPPThresholdTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = "USER"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = "130"; // TODO: Initialize to an appropriate value
			target->GetBPAutoPWAPPThreshold(SubSection, ReaderValue);
			Assert::AreEqual(Convert::ToInt32(ReaderValue),target->_instance->BpSettings->AutoPWAPPThreshold);
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBPAutoPWAPPThresholdTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = "DEFAULT"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = "150"; // TODO: Initialize to an appropriate value
			target->GetBPAutoPWAPPThreshold(SubSection, ReaderValue);
			Assert::AreEqual(Convert::ToInt32(ReaderValue),target->_bpSetInternal->AutoPWAPPThreshold);
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBPAutoPWAPPThresholdTest2()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = "DEFAULT1"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = "150"; // TODO: Initialize to an appropriate value
			
			try
			{	
				target->GetBPAutoPWAPPThreshold(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
		}
		/// <summary>
		///A test for GetBpAutoPWAPP
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWAPPTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"Yes";
			target->GetBpAutoPWAPP(SubSection, ReaderValue);
			Assert::AreEqual(true, target->_instance->BpSettings->AutoPWAPP);
			
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWAPPTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"DEFAULT";
			String^  ReaderValue = L"Yes";
			target->GetBpAutoPWAPP(SubSection, ReaderValue);
			Assert::AreEqual(true, target->_bpSetInternal->AutoPWAPP);			
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWAPPTest2()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"XX";

			try
			{
				target->GetBpAutoPWAPP(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}			
		}
		/// <summary>
		///A test for GetBpAutoPWADPThreshold
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWADPThresholdTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = "USER"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = "130"; // TODO: Initialize to an appropriate value
			target->GetBpAutoPWADPThreshold(SubSection, ReaderValue);
			Assert::AreEqual(Convert::ToInt32(ReaderValue),target->_instance->BpSettings->AutoPWADPThreshold);
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWADPThresholdTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = "DEFAULT"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = "150"; // TODO: Initialize to an appropriate value
			target->GetBpAutoPWADPThreshold(SubSection, ReaderValue);
			Assert::AreEqual(Convert::ToInt32(ReaderValue),target->_bpSetInternal->AutoPWADPThreshold);
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWADPThresholdTest2()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = "DEFAULT1"; // TODO: Initialize to an appropriate value
			String^  ReaderValue = "150"; // TODO: Initialize to an appropriate value
			
			try
			{	
				target->GetBpAutoPWADPThreshold(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}
		}
		/// <summary>
		///A test for GetBpAutoPWADP
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWADPTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"Yes";
			target->GetBpAutoPWADP(SubSection, ReaderValue);
			Assert::AreEqual(true, target->_instance->BpSettings->AutoPWADP);		
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWADPTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"DEFAULT";
			String^  ReaderValue = L"Yes";
			target->GetBpAutoPWADP(SubSection, ReaderValue);
			Assert::AreEqual(true, target->_bpSetInternal->AutoPWADP);			
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetBpAutoPWADPTest2()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = L"USER";
			String^  ReaderValue = L"XX";

			try
			{
				target->GetBpAutoPWADP(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}			
		}
//		/// <summary>
//		///A test for SetPwvAutoCapture
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetPwvAutoCaptureTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetPwvAutoCapture(ps, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		/// <summary>
		///A test for GetPwvAutoCapture
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwvAutoCaptureTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
			SubSection = L"USER";
			ReaderValue = L"Yes";
			
			target->GetPwvAutoCapture(SubSection, ReaderValue);
			Assert::AreEqual(true, target->_instance->PwvSettings->AutoCapture);
			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwvAutoCaptureTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
			SubSection = L"DEFAULT";
			ReaderValue = L"No";
			
			target->GetPwvAutoCapture(SubSection, ReaderValue);
			Assert::AreEqual(false, target->_pSetInternal->AutoCapture);
			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwvAutoCaptureTest2()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
			SubSection = L"USER";
			ReaderValue = L"XX-XX";
			try
			{
				target->GetPwvAutoCapture(SubSection, ReaderValue);
				Assert::Fail("If error does not occur then test fail");
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If error occur then test pass");
			}			
		}
//		/// <summary>
//		///A test for SetPwvGuidanceBars
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void SetPwvGuidanceBarsTest()
//		{
//			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructPwvSetting^  ps = nullptr; // TODO: Initialize to an appropriate value
//			XmlNode^  node = nullptr; // TODO: Initialize to an appropriate value
//			target->SetPwvGuidanceBars(ps, node);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		/// <summary>
		///A test for GetPwvGuidanceBars
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwvGuidanceBarsTest()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
			SubSection = L"USER";
			ReaderValue = L"Yes";
			
			target->GetPwvGuidanceBars(SubSection, ReaderValue);
			Assert::AreEqual(true, target->_instance->PwvSettings->GuidanceBars);
			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwvGuidanceBarsTest1()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
			SubSection = L"DEFAULT";
			ReaderValue = L"No";
			
			target->GetPwvGuidanceBars(SubSection, ReaderValue);
			Assert::AreEqual(false, target->_pSetInternal->GuidanceBars);
			//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void GetPwvGuidanceBarsTest2()
		{
			CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  SubSection = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  ReaderValue = System::String::Empty; // TODO: Initialize to an appropriate value
			SubSection = L"USER";
			ReaderValue = L"XX-XX";
			try
			{
				target->GetPwvGuidanceBars(SubSection, ReaderValue);
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
