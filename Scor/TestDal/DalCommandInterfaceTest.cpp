
#include "StdAfx.h"
using namespace System::Timers;
using namespace System::IO::Ports;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting;
using namespace System;
using namespace System::IO;
namespace TestDal {
    using namespace System;
    ref class DalCommandInterfaceTest;
	   using namespace System;
    
    
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
		public: static bool TimeoutErrorAlarmEventRaised = false;
		private: static String^ comPortName  = "COM3";
		public:	static DalCommandInterface_Accessor ^commInterfaceObject = DalCommandInterface_Accessor::Instance;
		private: String^ _currDir;

#pragma region Additional test attributes
			// 
			//You can use the following additional attributes as you write your tests:
			//
			//Use ClassInitialize to run code before running the first test in the class
			public: [ClassInitialize]
			static System::Void MyClassInitialize(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  testContext)
			{
				try
				{
					commInterfaceObject = DalCommandInterface_Accessor::Instance;
					commInterfaceObject->SetActivePort(comPortName);
				}
				catch (AtCor::Scor::CrossCutting::ScorException^ scorExObj)
				{
					Assert::Fail("MyClassInitialize failed: " + scorExObj->ErrorMessageKey);  
				}

			}

			static void SetPath()
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

			static void MyDalErrorAlarmEventHandler(Object ^sender, DalModuleErrorAlarmEventArgs ^args)
			{
				if (args->ErrorAlarmStatus == DalErrorAlarmStatusFlag::DataCaptureTimeout )
				{
					TimeoutErrorAlarmEventRaised = true;	
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

					//DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor());
					DalCommandInterface_Accessor ^ target = DalCommandInterface_Accessor::Instance;
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
				DalCommandInterface_Accessor ^ target = gcnew DalCommandInterface_Accessor();
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
			//DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
			DalCommandInterface_Accessor ^ target = DalCommandInterface_Accessor::Instance;
			target->SetActivePort(comPortName);
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x0b, gcnew array<unsigned char>(1) {0x08});
			DalReturnValue responseReturnValue = DalReturnValue::Failure;  //Intitialized
			DalReturnValue expected = DalReturnValue::Success ; 
			DalReturnValue actual;
			DalReturnValue commandReturnValue = DalReturnValue::Failure;
			commandReturnValue = target->SendCommandAndGetResponse(serialCommand);
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
				//DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
				DalCommandInterface_Accessor ^ target = DalCommandInterface_Accessor::Instance;
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
				DalCommandInterface_Accessor^ target = commInterfaceObject;
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
				DalCommandInterface_Accessor^  target = commInterfaceObject; 
				//Assert::IsNull(target->ActiveSerialPortName);
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
				DalCommandInterface_Accessor^  target = commInterfaceObject ; 
				target->SetActivePort(comPortName);
				Assert::AreEqual(comPortName, target->ActiveSerialPortName);
				///now provide any other valid port
				target->SetActivePort(comPortName);
				Assert::AreEqual(comPortName, target->ActiveSerialPortName);
			}
			/// <summary>
			///A test for SendCommandAndGetResponse
			///</summary>
			public: [TestMethod]
			void SendCommandAndGetResponseTest()
			{
				DalCommandInterface_Accessor^  target = commInterfaceObject ; 
				//target->SetActivePort(comPortName);
				DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x40, nullptr); 
				DalReturnValue ^expected = DalReturnValue::Success; 
				
				DalReturnValue ^actual;
				
				actual = target->SendCommandAndGetResponse(serialCommand);
				Assert::AreEqual(expected, actual);
	
			}

				/// <summary>
			///A test for SendCommandAndGetResponse
			///</summary>
public: [TestMethod]
		void SendCommandAndGetResponseTestNeg1()
		{
			
			DalCommandInterface_Accessor^  target = commInterfaceObject; 
			
			//Ensure that a non-existent command is sent to the Device 
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0xFF, nullptr); 
			DalReturnValue expected = DalReturnValue();
			bool exceptionRaised = false;
			//DalReturnValue_Accessor ^actual;
			DalReturnValue ^actual;
			try
			{
				actual = target->SendCommandAndGetResponse(serialCommand);
			}
			catch(Exception^ )
			{
				exceptionRaised = true;
			}
			Assert::IsFalse(exceptionRaised);
			Assert::AreEqual(DalReturnValue::Timeout , actual, "ensure that SendCommandAndGetResponseTest.ptp docklight script is NOT running on the testing system");
		}
			
			/// <summary>
			///A test for SendCommandAndGetResponse
			///</summary>
public: [TestMethod]
		void SendCommandAndGetResponseTestPos1()
		{
			DalCommandInterface_Accessor^  target = commInterfaceObject ; 
			//target->SetActivePort(comPortName);
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x0B, gcnew array<unsigned char> {0x08}); 
			DalReturnValue expected = DalReturnValue::Success ;
			bool exceptionRaised = false;
			//DalReturnValue_Accessor ^actual;
			DalReturnValue ^actual;
			try
			{
				actual = target->SendCommandAndGetResponse(serialCommand);
			}
			catch(Exception^)
			{
				exceptionRaised = true;

			}
			Assert::IsFalse(exceptionRaised, "Run EM4 simulation tool");
			Assert::AreEqual(expected, actual, "Run EM4 simulation tool");
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
				try
				{
			DalCommandInterface_Accessor^  target = commInterfaceObject; 
			//target->CreateAndOpenNewSerialPort(comPortName);
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x0B, gcnew array<unsigned char> (1) {0x08}); 
			DalReturnValue expected = DalReturnValue::Success ; 
			DalReturnValue actual;
					
					target->_serialPort->ReadTimeout = 5*DalConstants::EM4ResponseTimeout;
					//target->_serialPort->ReadTimeout = SerialPort::InfiniteTimeout; // changing to infinite timeout 
					//clear the input buffer before sending a command 
					//so that any remenant bits dont get prefixed to the response
					target->_serialPort->DiscardInBuffer();
					target->_serialPort->Write(serialCommand->em4Command,0, serialCommand->commandLength +1); //1 for CRC byte
		
					//wait to allow the response to arrive
					System::Threading::Thread::Sleep(35);
			actual = target->ListenForEM4Response(serialCommand);
					Assert::AreEqual(expected, actual, "Start the test tool before running this test. Change timout if necessary");
				}
				catch(ScorException^ scorExcepObj)
				{
					Assert::Fail("ScorException Raised: " + scorExcepObj->ErrorMessageKey ); 
				}
				catch(Exception^ excepObj)
				{
					Assert::Fail("Exception Raised: " + excepObj->Message); 
				}
			
			}
			/// <summary>
		///A test for InitiateDataCaptureMode
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void InitiateDataCaptureModeTest()
		{
			/*DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
			target->CreateAndOpenNewSerialPort(comPortName);*/
			DalCommandInterface_Accessor ^ target = commInterfaceObject; 
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

			//Open a port and call the start data capture command 
			//keep data ready in the port
			bool Exceptionthrown = false;
			

			/*DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
			target->CreateAndOpenNewSerialPort(comPortName);*/
			DalCommandInterface_Accessor ^ target = commInterfaceObject; 

			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x06, gcnew array<unsigned char> {0x03}); 
			target->InitiateDataCaptureMode();
			target->_serialPort->DataReceived += gcnew SerialDataReceivedEventHandler(DalCommandInterface_Accessor::DataCaptureMultiplePacketHandler);
			try
			{
				target->SendCommandAndGetResponse(serialCommand);
			}
			catch(Exception^)
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
				DalCommandInterface_Accessor^ target = commInterfaceObject;
				//Assert::IsNull(target->_serialPort);
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
		///A test for CheckStatusFlagsChanged
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void CheckStatusFlagsChangedTest()
		{
			/*DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
			target->SetActivePort(comPortName);*/
			DalCommandInterface_Accessor^  target = commInterfaceObject;
			//initialize all variables to starting values
			target->_currentCuffStatusFlag = 0;
			target->_currentAlarmStatusFlag  = 0;
		
			unsigned long Current_cuffStatusBytes = 0x0400; //first expected value
			unsigned long Current_eaStatusBytes = 0x0000; //first expected value
			unsigned long statusBytes = 0x0400; 
			bool expected = true; 
			bool actual;
			actual = target->CheckStatusFlagsChanged(statusBytes);
			Assert::AreEqual(expected, actual);
			Assert::AreEqual(Current_cuffStatusBytes, target->_currentCuffStatusFlag);
			Assert::AreEqual(Current_eaStatusBytes, target->_currentAlarmStatusFlag );

			//now assign the current values for checking
			Current_cuffStatusBytes = target->_currentCuffStatusFlag;
			Current_eaStatusBytes = target->_currentAlarmStatusFlag ;

			//change alarm flags without changing cuff flags
			statusBytes = 0x0408;
			target->CheckStatusFlagsChanged(statusBytes);
			Assert::AreEqual(Current_cuffStatusBytes, target->_currentCuffStatusFlag);
			Assert::AreNotEqual(Current_eaStatusBytes, target->_currentAlarmStatusFlag );

			//reset back to normal position . we wont chek the status this time
			statusBytes = 0x0400;
			target->CheckStatusFlagsChanged(statusBytes);
			Current_cuffStatusBytes = target->_currentCuffStatusFlag;
			Current_eaStatusBytes = target->_currentAlarmStatusFlag ;

			//now change cuff flags without changing alarm
			statusBytes = 0x0900;
			target->CheckStatusFlagsChanged(statusBytes);
			Assert::AreNotEqual(Current_cuffStatusBytes, target->_currentCuffStatusFlag);
			Assert::AreEqual(Current_eaStatusBytes, target->_currentAlarmStatusFlag );
			
		
		}

		/// <summary>
		///A test for ReadFromPortAndWriteToBuffer
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ReadFromPortAndWriteToBufferTest()
		{
			bool Exceptionthrown = false;
			
			DalCommandInterface_Accessor ^ target = commInterfaceObject; 
			DalDataBuffer::Instance->CreateBuffer(10, 256);

			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x06, gcnew array<unsigned char> {0x03}); 
			target->InitiateDataCaptureMode();
			target->_serialPort->DataReceived += gcnew SerialDataReceivedEventHandler(DalCommandInterface_Accessor::DataCaptureMultiplePacketHandler);
			try
			{
				TimeoutErrorAlarmEventRaised = false;
				target->SendCommandAndGetResponse(serialCommand);
				//Assert::IsFalse(DalDataBuffer_Accessor::Instance->IsBufferEmpty());
				System::Threading::Thread::Sleep(300); //sleep for a period longer than expected
				target->CheckIfTimeoutHasOccurred(this, nullptr);
				Assert::IsFalse(TimeoutErrorAlarmEventRaised);
			}
			catch(ScorException^ excepObj)
			{
				Assert::Fail("Test case failed because of " + excepObj->ErrorMessageKey );
			}
			catch(Exception^ excepObj)
			{
				Assert::Fail("Exception thrown: "+ excepObj->Data) ;
			}
			
		}
		/// <summary>
		///A test for ExtractRequiredResponseFromArray
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ExtractRequiredResponseFromArrayTest()
		{
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
			target->_sentPacketSequenceNumber  = 0x01;
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x08, nullptr); 
			serialCommand->expectedResponseLength = 0x05;
			cli::array< unsigned char >^  destinationArray = gcnew array<unsigned char> {0x87, 0x0D, 0x20, 0x01, 0xA8, 0x02, 0xB7, 0x00, 0x46, 0x00, 0x18, 0x09, 0x00, 0xA5, 0x87, 0x0D, 0x30, 0x01, 0xA7, 0x02, 0xCA, 0x00, 0x46, 0x00, 0x18, 0x09, 0x00, 0x8C, 0x88, 0x05, 0x10, 0x01, 0x00, 0x77, 0x87, 0x0D, 0x40, 0x01, 0xC8, 0x01, 0xC2, 0x00, 0x46, 0x00, 0x18, 0x09, 0x00, 0x26}; 
			bool expected = true; 
			bool actual;
			actual = target->ExtractRequiredResponseFromArray(serialCommand, destinationArray);
			Assert::AreEqual(expected, actual);
			Assert::IsNotNull(serialCommand->em4Response);
			Assert::AreEqual((int)serialCommand->expectedResponseLength + 1, serialCommand->em4Response->Length);
			Assert::AreEqual((unsigned char)0x88, serialCommand->em4Response[0]);
			Assert::AreEqual((unsigned char)0x05, serialCommand->em4Response[1]);
			Assert::AreEqual((unsigned char)(serialCommand->commandSequenceNumber<<4), serialCommand->em4Response[2]);
		}
		/// <summary>
		///A test for CheckIfTimeoutHasOccurred
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void CheckIfTimeoutHasOccurredTest()
		{
			SetPath();
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
			DalDataBuffer::Instance->CreateBuffer(10,256);

			DalPwvDataStruct bufferDataInput;
			
			DalEventContainer::Instance->OnDalModuleErrorAlarmEvent += gcnew DalModuleErrorAlarmEventHandler(&TestDal::DalCommandInterfaceTest::MyDalErrorAlarmEventHandler);

			Object^  sender = this; 
			ElapsedEventArgs^  args = nullptr; 
			Assert::IsFalse(TimeoutErrorAlarmEventRaised); //This shoudld be false 
			
			DalCommandInterface_Accessor::CheckIfTimeoutHasOccurred(sender, args);
			Assert::IsFalse(TimeoutErrorAlarmEventRaised); //This shoudld be false 
			
			DalCommandInterface_Accessor::CheckIfTimeoutHasOccurred(sender, args);
			Assert::IsTrue(TimeoutErrorAlarmEventRaised); //This shoudld be TRUE 

			//Now write an element to the array and check
			TimeoutErrorAlarmEventRaised = false; //first reset
			DalDataBuffer::Instance->WriteDataToBuffer(bufferDataInput);
			//Now call the method twice in succession
			DalCommandInterface_Accessor::CheckIfTimeoutHasOccurred(sender, args);
			DalCommandInterface_Accessor::CheckIfTimeoutHasOccurred(sender, args);
			Assert::IsFalse(TimeoutErrorAlarmEventRaised); //This shoudld be false 
			
			//Now read the element and then check
			int readStartIndex;
			DalDataBuffer::Instance->GetNextValues(32, readStartIndex);
			DalDataBuffer::Instance->GetValueAt(readStartIndex, 0);
			DalCommandInterface_Accessor::CheckIfTimeoutHasOccurred(sender, args);
			DalCommandInterface_Accessor::CheckIfTimeoutHasOccurred(sender, args);
			Assert::IsTrue(TimeoutErrorAlarmEventRaised); //This shoudld be TRUE 
		}
};
}
namespace TestDal {
    
}
