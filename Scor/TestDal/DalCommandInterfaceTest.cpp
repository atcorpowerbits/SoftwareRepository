
#include "StdAfx.h"
using namespace System::IO::Ports;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalCommandInterfaceTest;
    
    
    /// <summary>
///This is a test class for DalCommandInterfaceTest and is intended
///to contain all DalCommandInterfaceTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalCommandInterfaceTest
	{

	private: static Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  testContextInstance;
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
		private: static String^ comPortName  = "COM4";
		public:	static DalCommandInterface_Accessor ^commInterfaceObject = DalCommandInterface_Accessor::Instance;


#pragma region Additional test attributes
			// 
			//You can use the following additional attributes as you write your tests:
			//
			//Use ClassInitialize to run code before running the first test in the class
			public: [ClassInitialize]
			static System::Void MyClassInitialize(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  testContext)
			{
				commInterfaceObject = DalCommandInterface_Accessor::Instance;
				commInterfaceObject->SetActivePort(comPortName);

			}
			
			//Use ClassCleanup to run code after all tests in a class have run
			//public: [ClassCleanup]
			//static System::Void MyClassCleanup()
			//{
			//}
			//
			////Use TestInitialize to run code before running each test
			//public: [TestInitialize]
			//System::Void MyTestInitialize()
			//{
			//	DalCommandInterface_Accessor ^ target = DalCommandInterface_Accessor::Instance;
			//	//target->CloseActivePort();
			//}
			
			//Use TestCleanup to run code after each test has run
			public: [TestCleanup]
			System::Void MyTestCleanup()
			{
				DalCommandInterface_Accessor ^ target = DalCommandInterface_Accessor::Instance;
				try
				{
					target->CloseActivePort();
				}
				catch(Exception^ ex)
				{
					delete ex;
				}
			}
			
#pragma endregion
			/// <summary>
			///A test for DalCommandInterface Constructor
			///</summary>
			public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalCommandInterfaceConstructorTest()
			{//test for positive scenarion
				bool exceptionOccured = false;
				try
				{

					DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor());
					target->CreateAndOpenNewSerialPort(comPortName);
					Assert::IsNotNull(target->_serialPort);
					Assert::IsTrue(target->_serialPort->IsOpen);

					target->_serialPort->Close();
				}
				catch(Exception^)
				{
					exceptionOccured = true;
				}
				Assert::IsFalse(exceptionOccured, "Run this test individually");
			}
			/// <summary>
			///A test for Instance
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void InstanceTest()
			{
				//// Private Accessor for Instance is not found. Please rebuild the containing project or run the Publicize.exe manually.
				//Assert::Inconclusive(L"Private Accessor for Instance is not found. Please rebuild the containing project" 
				//	L" or run the Publicize.exe manually.");
				//gcnew DalCommandInterface_Accessor();
				DalCommandInterface_Accessor ^ target = DalCommandInterface_Accessor::Instance;
				Assert::IsNotNull(target);
				DalCommandInterface_Accessor ^ actual = DalCommandInterface_Accessor::Instance;
				Assert::AreEqual(target, actual);

			}
			/// <summary>
			///A test for ActiveSerialPortName
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ActiveSerialPortNameTest()
			{
				String^ actual;
				DalCommandInterface_Accessor ^ target = DalCommandInterface_Accessor::Instance;
				Assert::IsNotNull(target);
				actual = target->ActiveSerialPortName;
				Assert::IsNull(actual);
				
			}

			/// <summary>
			///A test for ActiveSerialPortName
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ActiveSerialPortNameTest2()
			{
				String^ actual;
				DalCommandInterface_Accessor ^ target = DalCommandInterface_Accessor::Instance;
				target->CreateAndOpenNewSerialPort(comPortName);
				actual = target->ActiveSerialPortName;
				Assert::IsNotNull(actual);
				
			}
		
		
		
			/// <summary>
		///A test for ValidateCommandResult
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidateCommandResultTest()
		{
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
			target->SetActivePort(comPortName);
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x0b, gcnew array<unsigned char>(1) {0x08});
			DalReturnValue responseReturnValue = DalReturnValue::Failure;  //Intitialized
			DalReturnValue expected = DalReturnValue::Success ; 
			DalReturnValue actual;
			DalReturnValue commandReturnValue = DalReturnValue::Failure;
			commandReturnValue = target->SendCommand(serialCommand);
			Assert::AreEqual(expected, commandReturnValue);
			actual = target->ValidateCommandResult(serialCommand, commandReturnValue); //validate the response recieved from send command
			Assert::AreEqual(expected, actual);

		}
			/// <summary>
			///A test for ValidateCommand
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ValidateCommandTest()
			{
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
			target->SetActivePort(comPortName);
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x0B, gcnew array<unsigned char> {0x08}); 
			
			bool expected = true; 
				bool actual;
				actual = target->ValidateCommand(serialCommand);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for TranslateTwoBytes
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void TranslateTwoBytesTest()
			{
			cli::array< unsigned char >^  sourceArray = gcnew array< unsigned char > {0x01, 0x02};
			int startPostion = 0;
			unsigned short expected = 0x0102; 
				unsigned short actual;
				actual = DalCommandInterface_Accessor::TranslateTwoBytes(sourceArray, startPostion);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for TranslateFourBytes
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void TranslateFourBytesTest()
			{
				cli::array< unsigned char >^  sourceArray = gcnew array< unsigned char > {0x01, 0x02, 0x03, 0x04}; 
				int startPostion = 0; 
				unsigned long expected = 0x01020304; 
				unsigned long actual;
				actual = DalCommandInterface_Accessor::TranslateFourBytes(sourceArray, startPostion);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
		///A test for StopDataCaptureMode
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void StopDataCaptureModeTest()
		{
			DalCommandInterface_Accessor^  target = commInterfaceObject; 
			
			bool expected = true; 
			bool excepThrown = false;
			bool actual;
			target->InitiateDataCaptureMode();
			try
			{
				actual = target->StopDataCaptureMode();
				Assert::AreEqual(expected, actual);
			}
			catch(Exception^)
			{
				excepThrown = true;
			}
			Assert::IsFalse(excepThrown);
		}
			/// <summary>
			///A test for SetSerialPortPorperties
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetSerialPortPorpertiesTest()
			{
				DalCommandInterface_Accessor^ target = gcnew DalCommandInterface_Accessor();
				try
				{
					target->CloseActivePort();
				}
				catch(Exception ^ scorex)
				{
					delete scorex;
				}
				target->CreateAndOpenNewSerialPort(comPortName);
				target->SetSerialPortProperties();
				Assert::AreEqual(115200, target->_serialPort->BaudRate);

			}
			/// <summary>
			///A test for SetActivePortInstance
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetActivePortInstanceTest()
			{
				//SetActivePortInstance is called internally by SetActivePort. 
				//we cannot Call it seperately since SetActivePortName expects that the _serialPort meber is set
				DalCommandInterface_Accessor^ target = commInterfaceObject ;
				//if (nullptr == target->_serialPort)
				//{
				//	try
				//	{
				//		//set any other valid port to create the _serialPort 
				//		target->SetActivePort("COM1");
				//	}
				//	catch(Exception ^)
				//	{
				//		Assert::Fail("Ensure that this portname is valid and is not being used");
				//	}
				//}

				//now call the method
				bool retValue = target->SetActivePortInstance(comPortName);
				Assert::IsTrue(retValue, "Ensure that the portnames are valid and run individually.");
				Assert::AreEqual(comPortName, target->_serialPort->PortName, "Ensure that the portnames are valid and run individually.");
					
			}
			/// <summary>
			///A test for SetActivePort
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetActivePortTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
				Assert::IsNull(target->ActiveSerialPortName);
				target->SetActivePort(comPortName);
				Assert::IsNotNull(target->ActiveSerialPortName);
				Assert::AreEqual(comPortName, target->ActiveSerialPortName);
				
				
			}
			//same test but with another port set
			/// <summary>
			///A test for SetActivePort
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetActivePortTest2()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
				target->SetActivePort(comPortName);
				Assert::AreEqual(comPortName, target->ActiveSerialPortName);
				///now provide any other valid port
				target->SetActivePort(comPortName);
				Assert::AreEqual(comPortName, target->ActiveSerialPortName);
			}
			/// <summary>
			///A test for SendCommand
			///</summary>
			public: [TestMethod]
			void SendCommandTest()
			{
				DalCommandInterface_Accessor^  target = commInterfaceObject ; 
				target->SetActivePort(comPortName);
				DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x40, nullptr); 
				DalReturnValue ^expected = DalReturnValue_Accessor::Success; 
				
				DalReturnValue ^actual;
				
				actual = target->SendCommand(serialCommand);
				Assert::AreEqual(expected, actual);
	
			}

				/// <summary>
			///A test for SendCommand
			///</summary>
public: [TestMethod]
		void SendCommandTestNeg1()
		{
			
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
			target->SetActivePort(comPortName);

			//Ensure that a non-existent command is sent to the Device 
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0xFF, nullptr); 
			DalReturnValue expected = DalReturnValue();
			bool exceptionRaised = false;
			//DalReturnValue_Accessor ^actual;
			DalReturnValue ^actual;
			try
			{
				actual = target->SendCommand(serialCommand);
			}
			catch(Exception^ excepObj)
			{
				exceptionRaised = true;
			}
			Assert::IsFalse(exceptionRaised);
			Assert::AreEqual(DalReturnValue::Timeout , actual, "ensure that SendCommandTest.ptp docklight script is NOT running on the testing system");
		}
			
			/// <summary>
			///A test for SendCommand
			///</summary>
public: [TestMethod]
		void SendCommandTestPos1()
		{
			DalCommandInterface_Accessor^  target = commInterfaceObject ; 
			target->SetActivePort(comPortName);
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x0B, gcnew array<unsigned char> {0x08}); 
			DalReturnValue expected = DalReturnValue::Success ;
			bool exceptionRaised = false;
			//DalReturnValue_Accessor ^actual;
			DalReturnValue ^actual;
			try
			{
				actual = target->SendCommand(serialCommand);
			}
			catch(Exception^)
			{
				exceptionRaised = true;

			}
			Assert::IsFalse(exceptionRaised, "Run Docklight script: getconfiginfo.pst");
			Assert::AreEqual(expected, actual, "Run Docklight script: getconfiginfo.pst");
		}

//Deepak: parametrised constructor has been removied in sprint 8
//		/// <summary>
//		///A test for DalCommandInterface Constructor
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"dal.dll")]
//		void DalCommandInterfaceConstructorTest2()
//		{
//			bool exceptionraised = false;
//			//negative test scenarion
//			try
//			{
//				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor("COM2")); //port isnot present
//			}
//			catch(ScorException^)
//			{
//				exceptionraised = true;
//			}
//
//			Assert::IsTrue(exceptionraised);
//			
//		}


/// <summary>
		///A test for ValidateResponseCRC
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidateResponseCRCTest_EM4DataCapturePacket()
		{
			EM4DataCapturePacket_Accessor^  capturePacket = gcnew EM4DataCapturePacket_Accessor(8); 
			capturePacket->em4Response = gcnew array<unsigned char> {0x87, 0x0D, 0x00, 0xA0, 0xA1, 0xB0, 0xB1, 0xC0, 0xC1, 0xD0, 0xD1, 0x01, 0x00, 0xC9};
			capturePacket->em4ResponsePacketLength = capturePacket->em4Response->Length -1;
			capturePacket->BreakupEM4Response();
			bool expected = true; // TODO: Initialize to an appropriate value
			bool actual;
			actual = DalCommandInterface_Accessor::ValidateResponseCRC(capturePacket);
			Assert::AreEqual(expected, actual);
			
		}


		/// <summary>
		///A test for ValidateResponseCRC
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidateResponseCRCTest_EM4DataCapturePacket_Neg()
		{
			EM4DataCapturePacket_Accessor^  capturePacket = gcnew EM4DataCapturePacket_Accessor(8); 
			capturePacket->em4Response = gcnew array<unsigned char> {0x87, 0x0D, 0x00, 0xA0, 0xA1, 0xB0, 0xB1, 0xC0, 0xC1, 0xD0, 0xD1, 0x01, 0x00, 0xC0};
			capturePacket->em4ResponsePacketLength = capturePacket->em4Response->Length -1;
			capturePacket->BreakupEM4Response();
			bool expected = false; 
			bool actual;
			actual = DalCommandInterface_Accessor::ValidateResponseCRC(capturePacket);
			Assert::AreEqual(expected, actual);
			
		}
		/// <summary>
		///A test for ValidateResponseCRC
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidateResponseCRCTest_DalEM4Command()
		{
			
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x06, nullptr);
			bool expected = true; 
			bool actual;

			serialCommand->em4Response = gcnew array<unsigned char> {0x8B, 0x11, 0x00 ,0xA1 ,0xA2 ,0xA3 ,0xA4 ,0xA5 ,0xA6 ,0xA7 ,0xA8 ,0xA9 ,0xB0 ,0xB1 ,0xB2 ,0x01 ,0x00, 0x4F};
			serialCommand->BreakupEM4Response();
			actual = DalCommandInterface_Accessor::ValidateResponseCRC(serialCommand);
			Assert::AreEqual(expected, actual);
			
		}
		/// <summary>
		///A test for ValidateResponseCRC
		///</summary>
		public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidateResponseCRCTest_DalEM4Command_Neg()
		{
			
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x06, nullptr);
			bool expected = true; 
			bool actual;

			serialCommand->em4Response = gcnew array<unsigned char> {0x8B, 0x11, 0x00 ,0xA1 ,0xA2 ,0xA3 ,0xA4 ,0xA5 ,0xA6 ,0xA7 ,0xA8 ,0xA9 ,0xB0 ,0xB1 ,0xB2 ,0x01 ,0x00, 0x40};
			serialCommand->BreakupEM4Response();
			actual = DalCommandInterface_Accessor::ValidateResponseCRC(serialCommand);
			Assert::AreEqual(expected, actual);
		}

			/// <summary>
			///A test for op_Assign
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void op_AssignTest()
			{
				DalCommandInterface_Accessor ^ target = gcnew DalCommandInterface_Accessor();
				DalCommandInterface_Accessor^ actual = nullptr;
				DalCommandInterface_Accessor^ unnamed = nullptr;
				actual =(unnamed = target);
				Assert::AreEqual(target, actual);
				//// Private Accessor for op_Assign is not found. Please rebuild the containing project or run the Publicize.exe manually.
				//Assert::Inconclusive(L"Private Accessor for op_Assign is not found. Please rebuild the containing projec" 
				//	L"t or run the Publicize.exe manually.");
			}
			/// <summary>
			///A test for ListenForEM4Response
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ListenForEM4ResponseTest()
			{
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
			target->CreateAndOpenNewSerialPort(comPortName);
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x0B, gcnew array<unsigned char> (1) {0x08}); 
			DalReturnValue expected = DalReturnValue::Success ; 
				DalReturnValue actual;
			target->SendCommand(serialCommand);
			target->_serialPort->ReadTimeout = SerialPort::InfiniteTimeout;
				actual = target->ListenForEM4Response(serialCommand);
				Assert::AreEqual(expected, actual, "Start the test tool before running this test");
			
			}
			/// <summary>
		///A test for InitiateDataCaptureMode
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void InitiateDataCaptureModeTest()
		{
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
			target->CreateAndOpenNewSerialPort(comPortName);
			bool expected = true;
			bool excepThrown = false;
			bool actual;
			
			try
			{
				actual = target->InitiateDataCaptureMode();
				Assert::AreEqual(expected, actual);
			}
			catch(Exception^)
			{
				excepThrown = true;
			}
			Assert::IsFalse(excepThrown);
		}

		//Deepak: TODO: cant figure this one
		/// <summary>
		///A test for EM4ResponseHandler
		///</summary>
		public: [TestMethod]
		void DataCaptureMultiplePacketHandlerTest1()
		{

			//Assert::Inconclusive("This test is incorrect");
			//Open a port and call the start data capture command 
			//keep data ready in the port
			bool Exceptionthrown = false;
			

			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
			target->CreateAndOpenNewSerialPort(comPortName);

			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x06, gcnew array<unsigned char> {0x03}); 
			target->InitiateDataCaptureMode();
			target->_serialPort->DataReceived += gcnew SerialDataReceivedEventHandler(DalCommandInterface_Accessor::DataCaptureMultiplePacketHandler);
			try
			{
				target->SendCommand(serialCommand);
			}
			catch(Exception^ excepObj)
			{
				Exceptionthrown = true;
			}
			Assert::IsFalse(Exceptionthrown);
			//Object^ sender = nullptr;
			//Object^  sender = target->_commandInterface->_serialPort;

			/*SerialDataReceivedEventArgs^  e = nullptr; 
			try
			{
				DalCommandInterface_Accessor::DataCaptureHandler(sender, e);
			}
			catch(Exception^ excpeObj)
			{
				Exceptionthrown = true;
			}
			Assert::IsFalse(Exceptionthrown);*/

		}
			/// <summary>
			///A test for CreateAndOpenNewSerialPort
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CreateAndOpenNewSerialPortTest()
			{
				//// Private Accessor for CreateAndOpenNewSerialPort is not found. Please rebuild the containing project or run the Publicize.exe manually.
				//Assert::Inconclusive(L"Private Accessor for CreateAndOpenNewSerialPort is not found. Please rebuild the " 
				//	L"containing project or run the Publicize.exe manually.");
				DalCommandInterface_Accessor^ target = DalCommandInterface_Accessor::Instance;
				Assert::IsNull(target->_serialPort);
				target->CreateAndOpenNewSerialPort(comPortName);
				Assert::IsNotNull(target->_serialPort);
			}
			/// <summary>
			///A test for CloseActivePort
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CloseActivePortTest()
			{
				bool status; 
				DalCommandInterface_Accessor^ target = DalCommandInterface_Accessor::Instance;
				target->SetActivePort(comPortName);
				if (target->_serialPort != nullptr)
				{
					status = target->CloseActivePort();
					Assert::IsTrue(status);
				}
				else
				{
					Assert::Fail("Could not conduct CloseActivePortTest since there is no port");
				}
			}
			/// <summary>
		///A test for CheckStatusFlag
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void CheckStatusFlagTest()
		{
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
			target->SetActivePort(comPortName);
			//initialize all variables to starting values
			target->_currentCuffStatusFlag = 0;
			target->_currentEAStatusFlag = 0;
		
			unsigned long Current_cuffStatusBytes = 0x0400; //first expected value
			unsigned long Current_eaStatusBytes = 0x0000; //first expected value
			unsigned long statusBytes = 0x0400; 
			bool expected = true; 
			bool actual;
			actual = target->CheckStatusFlag(statusBytes);
			Assert::AreEqual(expected, actual);
			Assert::AreEqual(Current_cuffStatusBytes, target->_currentCuffStatusFlag);
			Assert::AreEqual(Current_eaStatusBytes, target->_currentEAStatusFlag);

			//now assign the current values for checking
			Current_cuffStatusBytes = target->_currentCuffStatusFlag;
			Current_eaStatusBytes = target->_currentEAStatusFlag;

			//change alarm flags without changing cuff flags
			statusBytes = 0x0408;
			target->CheckStatusFlag(statusBytes);
			Assert::AreEqual(Current_cuffStatusBytes, target->_currentCuffStatusFlag);
			Assert::AreNotEqual(Current_eaStatusBytes, target->_currentEAStatusFlag);

			//reset back to normal position . we wont chek the status this time
			statusBytes = 0x0400;
			target->CheckStatusFlag(statusBytes);
			Current_cuffStatusBytes = target->_currentCuffStatusFlag;
			Current_eaStatusBytes = target->_currentEAStatusFlag;

			//now change cuff flags without changing alarm
			statusBytes = 0x0900;
			target->CheckStatusFlag(statusBytes);
			Assert::AreNotEqual(Current_cuffStatusBytes, target->_currentCuffStatusFlag);
			Assert::AreEqual(Current_eaStatusBytes, target->_currentEAStatusFlag);
			
		
		}
	};
}
namespace TestDal {
    
}
