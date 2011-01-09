#include "stdafx.h"

//using namespace System;
//using namespace System::Text;
//using namespace System::Collections::Generic;
//using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;
//using namespace CrxLogging;
//using namespace CrxMessaging;
//using namespace System::IO;
//using namespace CrxConfiguration;
//
//namespace TestCrx
//{
//	[TestClass]
//	public ref class UnitTestLogging
//	{
//	private:
//		TestContext^ testContextInstance;
//
//	public: 
//		/// <summary>
//		///Gets or sets the test context which provides
//		///information about and functionality for the current test run.
//		///</summary>
//		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
//		{
//			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
//			{
//				return testContextInstance;
//			}
//			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
//			{
//				testContextInstance = value;
//			}
//		};
//
//		#pragma region Additional test attributes
//		//
//		//You can use the following additional attributes as you write your tests:
//		//
//		//Use ClassInitialize to run code before running the first test in the class
//		//[ClassInitialize()]
//		//static void MyClassInitialize(TestContext^ testContext) {};
//		//
//		//Use ClassCleanup to run code after all tests in a class have run
//		//[ClassCleanup()]
//		//static void MyClassCleanup() {};
//		//
//		//Use TestInitialize to run code before running each test
//		//[TestInitialize()]
//		//void MyTestInitialize() {};
//		//
//		//Use TestCleanup to run code after each test has run
//		//[TestCleanup()]
//		//void MyTestCleanup() {};
//		//
//		#pragma endregion 
//
//		[TestMethod]
//		void TestLoggerInstantiation()
//		{
//			CrxLogger ^loggerObj = CrxLogger::Instance::get();
//			loggerObj->Write("What the hell");
//			Assert::IsNotNull(loggerObj,L"logobject is null");
//			
//		};
//		/*void TestLoggingCOnstructor()
//		{
//			CrxLogger ^loggerObj = gcnew CrxLogger();
//		Assert::IsNull(loggerObj);
//
//		}*/
//
//		void WriteStringToLog(String ^Teststring)
//		{
//			CrxLogger ^Obj1 = CrxLogger::Instance::get();
//			Obj1->Write(Teststring);
//		}
//		
//		[TestMethod]
//		void TestLoggerWriting()
//		{
//			/*
//			This test case fails because Filestream cannot open the specified log file.
//			The file is present in the specified location and the test string is beign written to the file.
//			This can be verified by manually opening the log file.
//			However it is not possible to verify it using this test case because the logger has a lock on the 
//			scor.log file and when Filestream tries to open it it results in a XXX exception.
//			Enterprise Lib Logger does not allow us to read from the log file, only write to it.
//			In order to test it we will have to add a destructor which releases the log file.
//			This will be done in the next sprint when the specific user story for logging is picked up.
//			*/
//			String ^ TestStr = gcnew String("Testing Log Writing ability");
//			
//			WriteStringToLog(TestStr);
//			
//			FileStream^ LogFS = gcnew FileStream("system\\logs\\scor.log",FileMode::Open);
//			Assert::IsNotNull(LogFS,"FileCould not be opened");
//						
//			StreamReader ^LogReader = gcnew StreamReader(LogFS);
//			String ^TempString;
//
//			TempString = LogReader->ReadLine();
//			if (TempString->EndsWith(TestStr) == false)
//			{
//				Assert::Fail("Failed to write to log file");
//			}
//
//		};
//		[TestMethod]
//		void TestLoggerSingleton()
//		{
//			CrxLogger ^Obj1 = CrxLogger::Instance::get();
//			CrxLogger ^Obj2 = CrxLogger::Instance::get();
//			CrxMessagingManager ^objMgr = CrxMessagingManager::Instance;
//			Assert::AreSame(Obj1, Obj2);
//			Assert::AreNotSame(Obj1, objMgr,"Logger and messaging objects are same");
//		};
//
//	};
//
//
//	[TestClass]
//	public ref class UnitTestMesaging
//	{
//	private:
//		TestContext^ testContextInstance;
//
//	public: 
//		/// <summary>
//		///Gets or sets the test context which provides
//		///information about and functionality for the current test run.
//		///</summary>
//		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
//		{
//			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
//			{
//				return testContextInstance;
//			}
//			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
//			{
//				testContextInstance = value;
//			}
//		};
//
//		#pragma region Additional test attributes
//		//
//		//You can use the following additional attributes as you write your tests:
//		//
//		//Use ClassInitialize to run code before running the first test in the class
//		//[ClassInitialize()]
//		//static void MyClassInitialize(TestContext^ testContext) {};
//		//
//		//Use ClassCleanup to run code after all tests in a class have run
//		//[ClassCleanup()]
//		//static void MyClassCleanup() {};
//		//
//		//Use TestInitialize to run code before running each test
//		//[TestInitialize()]
//		//void MyTestInitialize() {};
//		//
//		//Use TestCleanup to run code after each test has run
//		//[TestCleanup()]
//		//void MyTestCleanup() {};
//		//
//		#pragma endregion 
//
//			[TestMethod]
//		void TestMessageInstantiation()
//		{
//			CrxMessagingManager ^messObj = CrxMessagingManager::Instance;
//			Assert::IsNotNull(messObj);
//
//		};
//
//		[TestMethod]
//		void TestMessagingMgrSingleton()
//		{
//			CrxMessagingManager ^Obj1 = CrxMessagingManager::Instance::get();
//			CrxMessagingManager ^Obj2 = CrxMessagingManager::Instance::get();
//			Assert::AreSame(Obj1, Obj2);
//		};
//
//		[TestMethod]
//		void TestMessagingGetString()
//		{
//			CrxMessagingManager ^messObj = CrxMessagingManager::Instance;
//			String^ tempstring = messObj->GetMessage(200);
//			Assert::AreEqual<String^>(tempstring->ToString(), "An exception occured in Messaging component."); 
//
//		};
//
//	};
//
//
//	[TestClass]
//	public ref class UnitTestConfigManager
//	{
//	private:
//		TestContext^ testContextInstance;
//
//	public: 
//		/// <summary>
//		///Gets or sets the test context which provides
//		///information about and functionality for the current test run.
//		///</summary>
//		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
//		{
//			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
//			{
//				return testContextInstance;
//			}
//			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
//			{
//				testContextInstance = value;
//			}
//		};
//
//		#pragma region Additional test attributes
//		//
//		//You can use the following additional attributes as you write your tests:
//		//
//		//Use ClassInitialize to run code before running the first test in the class
//		//[ClassInitialize()]
//		//static void MyClassInitialize(TestContext^ testContext) {};
//		//
//		//Use ClassCleanup to run code after all tests in a class have run
//		//[ClassCleanup()]
//		//static void MyClassCleanup() {};
//		//
//		//Use TestInitialize to run code before running each test
//		//[TestInitialize()]
//		//void MyTestInitialize() {};
//		//
//		//Use TestCleanup to run code after each test has run
//		//[TestCleanup()]
//		//void MyTestCleanup() {};
//		//
//		#pragma endregion 
//
//		[TestMethod()]
//            void CheckInstance_Manual()
//            {
//                  CrxConfigManager^  actual = CrxConfigManager::Instance;
//                  Assert::IsNotNull(actual);
//                        }
//            [TestMethod()]
//            void GetGeneralUserSettingsTest_Manual()
//            {
//                  CrxConfigManager ^obj = CrxConfigManager::Instance;
//                  try
//                  {
//                        obj->GetGeneralUserSettings();      
//                  }
//                  catch(Exception^)
//                  {
//                        Assert::Fail();
//                  }
//                  Assert::IsNotNull(obj);
//            }
//
//            [TestMethod()]
//            void GetGeneralDefaultSettingsTest_Manual()
//            {
//                  CrxConfigManager ^obj = CrxConfigManager::Instance;
//                  try
//                  {
//                        obj->GetGeneralDefaultSettings();   
//                  }
//                  catch(Exception^)
//                  {
//                        Assert::Fail();
//                  }
//
//                  Assert::IsNotNull(obj);
//            }
//
//            [TestMethod()]
//            void SetGeneralUserSettingsTest_Manual_Positive()
//            {
//                  CrxConfigManager ^obj = CrxConfigManager::Instance;
//
//                  CrxStructGeneralSetting ^sobj = gcnew CrxStructGeneralSetting();              
//                  sobj->PatientPrivacy = false;
//            sobj->HeightandWeightUnit = 1;
//            sobj->BloodPressureEntryOptions = 2;
//            sobj->CommsPort = "Checkout";
//            sobj->ReportTitle = "Test";
//            sobj->ReportLogoPath = "C:\\Documents and Settings\\smarajit.mishra\\Desktop\\Error.JPG";
//
//                  try
//                  {
//                         obj->SetGeneralUserSettings(sobj);
//                  }
//                  catch(Exception^)
//                  {
//                        Assert::Fail();
//                  }
//
//                  Assert::IsNotNull(obj);
//            }
//            
//            [TestMethod()]
//            void SetGeneralUserSettingsTest_Manual_Negative()
//            {
//                  CrxConfigManager ^obj = CrxConfigManager::Instance;
//
//                  CrxStructGeneralSetting ^sobj = gcnew CrxStructGeneralSetting();              
//                  sobj->PatientPrivacy = false;
//            sobj->HeightandWeightUnit = 4;
//            sobj->BloodPressureEntryOptions = 4;
//            sobj->CommsPort = nullptr;
//            sobj->ReportTitle = nullptr;
//            sobj->ReportLogoPath = nullptr;
//
//                  try
//                  {
//                         obj->SetGeneralUserSettings(sobj);
//                  }
//                  catch(Exception^)
//                  {
//                        Assert::Fail();
//                  }
//
//                  Assert::IsNotNull(obj);
//            }
//	};
//}
