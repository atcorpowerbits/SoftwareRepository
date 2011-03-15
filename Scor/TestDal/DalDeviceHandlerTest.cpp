
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace System::IO;
namespace TestDal {
    using namespace System;
    ref class DalDeviceHandlerTest;
    
    
    /// <summary>
///This is a test class for DalDeviceHandlerTest and is intended
///to contain all DalDeviceHandlerTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalDeviceHandlerTest
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

		private:	static String^ comPortName  = "COM4";

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
			///A test for StopCapture
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void StopCaptureTest1()
			{
				//Start and then stop capture
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				target->_commandInterface->CreateAndOpenNewSerialPort(comPortName);
				
				bool expected = true; 
				bool actual;
				target->StartCapture(10, 256);
				actual = target->StopCapture();
				Assert::AreEqual(expected, actual);
				
			}
			/// <summary>
			///A test for StartCapture
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void StartCaptureTest3()
			{
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
				int captureTime = 10; // TODO: Initialize to an appropriate value
				int samplingRate = 256; // TODO: Initialize to an appropriate value
				bool expected = true; // TODO: Initialize to an appropriate value
				bool actual;
				actual = target->StartCapture(captureTime, samplingRate);
				Assert::AreEqual(expected, actual);
				System::Threading::Thread::Sleep(1000);
				target->StopCapture();
				Assert::AreEqual(expected, actual);
				Assert::IsNotNull(target->_commandInterface);
				Assert::IsNotNull(target->dataBufferObj); //not available in acceesor
			}
			
			/// <summary>
			///A test for SetPressure
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetPressureTest_Mainboard()
			{
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				target->_commandInterface->CreateAndOpenNewSerialPort(comPortName);
				int newPressure = 30; 
				EM4CuffBoard cuffBoard = EM4CuffBoard::MainBoard;
				bool expected = true; 
				bool actual;
				actual = target->SetPressure(newPressure, cuffBoard);
				Assert::AreEqual(expected, actual);
			
			}

			/// <summary>
			///A test for SetPressure
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetPressureTest_SuntechBoard()
			{
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				target->_commandInterface->CreateAndOpenNewSerialPort(comPortName);
				int newPressure = 30; 
				EM4CuffBoard cuffBoard = EM4CuffBoard::SuntechBoard;
				bool expected = false; 
				bool actual;
				actual = target->SetPressure(newPressure, cuffBoard);
				Assert::AreEqual(expected, actual);
			
			}
			/// <summary>
			///A test for SaveCaptureData
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SaveCaptureDataTest1()
			{
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				target->_commandInterface->CreateAndOpenNewSerialPort(comPortName);
				cli::array< unsigned short >^  tonometerData = gcnew array< unsigned short > {0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6}; 
				cli::array< unsigned short >^  cuffPulse = gcnew array< unsigned short > {0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6}; 
				unsigned short bufferSize = 6; 
				bool expected = true; 
				bool actual;
				bool excepRaised = false;
				actual = target->SaveCaptureData(tonometerData, cuffPulse, bufferSize);
				Assert::AreEqual(expected, actual);
				

				//verify that the file exists in the specified path
				String^ savedFileName = target->GetSavedFileName();
				Assert::IsNotNull(savedFileName);

				StreamReader ^ savedFileReader = gcnew StreamReader(savedFileName);

				try
				{
					for(int i = 0; i<bufferSize; i++)
					{
						Assert::IsNotNull(savedFileReader->ReadLine());

					}
				}
				catch(Exception^)
				{
					excepRaised = true;
				}

				Assert::IsFalse(excepRaised);
				

			}
			/// <summary>
			///A test for GetSavedFileName
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetSavedFileNameTest1()
			{
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				target->_commandInterface->CreateAndOpenNewSerialPort(comPortName);
				cli::array< unsigned short >^  tonometerData = gcnew array< unsigned short > {0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6}; 
				cli::array< unsigned short >^  cuffPulse = gcnew array< unsigned short > {0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6}; 
				unsigned short bufferSize = 6; 
			
				//create a filestring with a wildcard character. Remove the seconds since it is not always reliable
				DateTime currentDateTime;
			currentDateTime = System::DateTime::Now;
				String^ tempCapture = "capture_";
				String  ^ currentDateTimeStr = currentDateTime.ToString("yyyyMMMddHHmm");
				currentDateTimeStr = tempCapture+ currentDateTimeStr ;


				target->SaveCaptureData(tonometerData, cuffPulse, bufferSize);
				
				String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  actual;
				actual = target->GetSavedFileName();
				Assert::IsTrue(actual->Contains(currentDateTimeStr));
			}

			/// <summary>
			///A test for GetErrorAlarmSource
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetErrorAlarmSourceTest1()
			{
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				target->_commandInterface->CreateAndOpenNewSerialPort(comPortName);
				String^  expected = DalAlarmSource::OverPressure.ToString(); 
				String^  actual;
				actual = target->GetErrorAlarmSource();
				Assert::AreEqual(expected, actual);
			}
			
			/// <summary>
			///A test for GetConnectionStatus
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetConnectionStatusTest1()
			{
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				target->_commandInterface->CreateAndOpenNewSerialPort(comPortName);
				bool expected = true; 
				bool actual;
				actual = target->GetConnectionStatus();
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for GetConnectionStatus
			///</summary>
			public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetConnectionStatusTest2()
			{
				//provide a non existing port
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				target->_commandInterface->CreateAndOpenNewSerialPort("COM2");
				bool expected = false; 
				bool actual;
				actual = target->GetConnectionStatus();
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for GetConfigurationInfo
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetConfigurationInfoTest1()
			{
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				target->_commandInterface->CreateAndOpenNewSerialPort(comPortName);
				DalDeviceConfigUsageEnum deviceConfigItem = DalDeviceConfigUsageEnum::ModuleSerialNumber ; 
				DalDeviceConfigUsageStruct^  deviceConfigInfo = gcnew  DalDeviceConfigUsageStruct ; 
				bool expected = true; 
				bool actual;
				actual = target->GetConfigurationInfo(deviceConfigItem, deviceConfigInfo);
				Assert::AreEqual(expected, actual);
				Assert::IsNotNull(deviceConfigInfo->ModuleSerialNumber); 
			}
			/// <summary>
			///A test for FindModule
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void FindModuleTest1()
			{
				Directory::SetCurrentDirectory("D:\\Scor_Source_code\\TestResults");
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				target->_commandInterface->CreateAndOpenNewSerialPort(comPortName);
				String^  comPort =comPortName;
				int expected = 1; 
				int actual;
				actual = target->FindModule(comPort);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for CheckIfTonometerIsConnected
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckIfTonometerIsConnectedTest()
			{
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				target->_commandInterface->SetActivePort(comPortName); 
				bool expected = true; 
				bool actual;
				actual = target->CheckIfTonometerIsConnected();
				Assert::AreEqual(expected, actual);
			}
			/// This method checks on the port in config
			///A test for CheckIfDeviceIsConnected
			///Ensure that the device is connected on the same port as specified in config.
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckIfDeviceIsConnectedTest2()
			{
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor());
				bool expected = true; 
				bool actual;
				actual = target->CheckIfDeviceIsConnected();
				Assert::AreEqual(expected, actual, "Ensure that the device is connected on the same port as specified in config.");
			}
			/// This one calls the parametrized form 
			///A test for CheckIfDeviceIsConnected
			///It should be run with the device connected
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckIfDeviceIsConnectedTest1()
			{
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor());
				String^  comPort = comPortName; 
				//set the DCI port
				target->_commandInterface->SetActivePort(comPort);
				
				bool expected = true; 
				bool actual;
				actual = target->CheckIfDeviceIsConnected(comPort);
				Assert::AreEqual(expected, actual);
			}
			/// This one calls the parametrized form 
			///A test for CheckIfDeviceIsConnected
			///It should be run WITHOUT the device connected 
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckIfDeviceIsConnectedTest1_Neg()
			{
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor());
				String^  comPort = comPortName; 
				//set the DCI port
				target->_commandInterface->SetActivePort(comPort);
				bool expected = false; 
				bool actual;
				actual = target->CheckIfDeviceIsConnected(comPort);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for DalDeviceHandler Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalDeviceHandlerConstructorTest1()
			{
				String^  commPort = comPortName; 
				DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor());
				Assert::IsNotNull(target);
				Assert::IsNotNull(target->_commandInterface);
				Assert::IsNull(target->_commandInterface->_serialPort);
			}
			
			/// <summary>
			///A test for StopCapture
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void StopCaptureTest()
			{
				//negative test case. stop capture without starting cpature
				IDalHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				DalDeviceHandler_Accessor^ target_ddh = (DalDeviceHandler_Accessor^)target;
				target_ddh->_commandInterface->CreateAndOpenNewSerialPort(comPortName);
				bool expected = false; 
				bool actual;
				actual = target->StopCapture();
				Assert::AreEqual(expected, actual);
			}
			
			/// <summary>
			///A test for StartCapture
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void StartCaptureTest()
			{
				IDalHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				DalDeviceHandler_Accessor^ target_ddh = (DalDeviceHandler_Accessor^)target;
				target_ddh->_commandInterface->CreateAndOpenNewSerialPort(comPortName);
				bool expected = true; 
				bool actual;
				actual = target->StartCapture(10, 256);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for SetPressure
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetPressureTest()
			{
				IDalHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				int newPressure = 40; 
				EM4CuffBoard cuffBoard = EM4CuffBoard::MainBoard ;
				bool expected = true; 
				bool actual;
				actual = target->SetPressure(newPressure, cuffBoard);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for SaveCaptureData
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SaveCaptureDataTest()
			{
				IDalHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				cli::array< unsigned short >^  tonometerData = gcnew cli::array< unsigned short > (5) {0x01, 0x02, 0x03, 0x04, 0x05}; 
				cli::array< unsigned short >^  cuffPulse = gcnew cli::array< unsigned short > (5) {0xA1, 0xA2, 0xA3, 0xA4, 0xA5};  
				unsigned short bufferSize = 5; 
				bool expected = true; 
				bool actual;
				actual = target->SaveCaptureData(tonometerData, cuffPulse, bufferSize);
				Assert::AreEqual(expected, actual);
				String ^ savedFilePath = target->GetSavedFileName();
				if (String::IsNullOrEmpty(savedFilePath))
				{
					Assert::Fail();
				}
				else
				{
					Assert::IsTrue(true);
				}
			}
			
			
			//the only difference with GetConfigurationInfoTest1 is that the IDalHandler pointer is used
			//this test will
			/// <summary>
			///A test for GetConfigurationInfo
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetConfigurationInfoTest()
			{
				IDalHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
				DalCommandInterface_Accessor::Instance->CreateAndOpenNewSerialPort(comPortName);
				DalDeviceConfigUsageEnum deviceConfigItem = DalDeviceConfigUsageEnum::ModuleSerialNumber ; 
				DalDeviceConfigUsageStruct^  deviceConfigInfo = gcnew  DalDeviceConfigUsageStruct ; 
				bool expected = true; 
				bool actual;
				actual = target->GetConfigurationInfo(deviceConfigItem, deviceConfigInfo);
				Assert::AreEqual(expected, actual);
				Assert::IsNotNull(deviceConfigInfo->ModuleSerialNumber); 
			}
			//Find Module has been removed
	//		/// <summary>
	//		///A test for FindModule
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void FindModuleTest()
	//		{
	//			IDalHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
	//			String^  comPort = comPortName; 
	//			int expected = 1; 
	//			int actual;
	//			//Deepak:m revisit this
	//			actual = target->FindMOFindModule(comPort); 
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}

	};
}
namespace TestDal {
    
}
