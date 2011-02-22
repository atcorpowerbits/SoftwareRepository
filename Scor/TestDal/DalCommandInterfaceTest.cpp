#include "StdAfx.h"
using namespace System::IO::Ports;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting;
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
			///A test for SendCommand
			///</summary>
			public: [TestMethod]
			void SendCommandTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor("COM1")); 
				DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x40, nullptr); 
				DalReturnValue ^expected = DalReturnValue_Accessor::Success; 
				
				DalReturnValue ^actual;
				
				actual = target->SendCommand(serialCommand);
				Assert::AreEqual(expected, actual);
	
			}
			
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

					DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor("COM1"));
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
			///A test for SendCommand
			///</summary>
public: [TestMethod]
		void SendCommandTestNeg1()
		{
			
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
			DalEM4Command_Accessor^  serialCommand = nullptr; 
			DalReturnValue expected = DalReturnValue();
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
			Assert::AreEqual(true, exceptionRaised);
		}


			/// <summary>
			///A test for SendCommand
			///</summary>
public: [TestMethod]
		void SendCommandTestPos1()
		{
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor("COM1")); 
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

	
		//Deepak: TODO: cant figure this one
		/// <summary>
		///A test for EM4ResponseHandler
		///</summary>
		public: [TestMethod]
		void DataCaptureHandlerTest1()
		{

			Assert::Fail("This test is incorrect");
			//Open a port and call the start data capture command 
			//keep data ready in the port
			bool Exceptionthrown = false;
			

			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor("COM1")); 

			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x06, gcnew array<unsigned char> {0x03}); 
			target->InitiateDataCaptureMode();
			target->_serialPort->DataReceived += gcnew SerialDataReceivedEventHandler(DalCommandInterface_Accessor::DataCaptureHandler);
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
		///A test for DalCommandInterface Constructor
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void DalCommandInterfaceConstructorTest2()
		{
			bool exceptionraised = false;
			//negative test scenarion
			try
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor("COM2")); //port isnot present
			}
			catch(ScorException^)
			{
				exceptionraised = true;
			}

			Assert::IsTrue(exceptionraised);
			
		}

		
		
		/// <summary>
		///A test for ValidateResponsePacket
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidateResponsePacketTest1()
		{
			//valid packet
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x0b, gcnew array <unsigned char> {0x08}); 
			serialCommand->em4Response = gcnew array<unsigned char> {0x8B, 0x11, 0x00 ,0xA1 ,0xA2 ,0xA3 ,0xA4 ,0xA5 ,0xA6 ,0xA7 ,0xA8 ,0xA9 ,0xB0 ,0xB1 ,0xB2 ,0x01 ,0x00, 0x4F};
			serialCommand->em4ResponsePacketLength = serialCommand->em4Response->Length -1;
			serialCommand->BreakupEM4Response();
			DalReturnValue expected = DalReturnValue::Success ; 
			DalReturnValue actual;
			actual = DalCommandInterface_Accessor::ValidateResponsePacket(serialCommand);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for ValidateResponsePacket
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidateResponsePacketTest()
		{
			EM4DataCapturePacket_Accessor^  capturePacket = gcnew EM4DataCapturePacket_Accessor(8); 
			capturePacket->em4Response = gcnew array<unsigned char> {0x87, 0x0D, 0x00, 0xA0, 0xA1, 0xB0, 0xB1, 0xC0, 0xC1, 0xD0, 0xD1, 0x01, 0x00, 0xC9};
			capturePacket->em4ResponsePacketLength = capturePacket->em4Response->Length -1;
			capturePacket->BreakupEM4Response();
			
			DalReturnValue expected = DalReturnValue::Success ; 
			DalReturnValue actual;
			actual = DalCommandInterface_Accessor::ValidateResponsePacket(capturePacket);
			Assert::AreEqual(expected, actual);
		}
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
		///A test for ValidateCommandResult
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidateCommandResultTest()
		{
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor("COM1")); 
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x0b, gcnew array<unsigned char> {0x08});
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
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor("COM1")); 
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
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor("COM1")); 
			bool expected = true; // TODO: Initialize to an appropriate value
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
		///A test for ListenForEM4Response
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ListenForEM4ResponseTest()
		{
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor("COM1")); 
			DalEM4Command_Accessor^  serialCommand = gcnew DalEM4Command_Accessor(0x0B, gcnew array<unsigned char> {0x08}); // TODO: Initialize to an appropriate value
			DalReturnValue expected = DalReturnValue::Success ; 
			DalReturnValue actual;
			//target->SendCommand(serialCommand);
			target->_serialPort->ReadTimeout = SerialPort::InfiniteTimeout;
			actual = target->ListenForEM4Response(serialCommand);
			Assert::AreEqual(expected, actual);
			
		}
		/// <summary>
		///A test for InitiateDataCaptureMode
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void InitiateDataCaptureModeTest()
		{
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor("COM1")); 
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
		/// <summary>
		///A test for CheckStatusFlag
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void CheckStatusFlagTest()
		{
			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor("COM1")); 
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
