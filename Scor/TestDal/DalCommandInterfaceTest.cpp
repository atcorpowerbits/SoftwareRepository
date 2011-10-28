
#include "StdAfx.h"
using namespace System::Timers;
using namespace AtCor::Scor::DataAccess::StateMachines;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace System::IO::Ports;
using namespace AtCor::Scor::CrossCutting;
using namespace System;
using namespace System::IO;
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
		public: static bool TimeoutErrorAlarmEventRaised = false;
		private: static String^ comPortName  = "COM6";
		private: String^ _currDir;

#pragma region Additional test attributes
			// 
			//You can use the following additional attributes as you write your tests:
			//
			////Use ClassInitialize to run code before running the first test in the class
			//public: [ClassInitialize]
			//static System::Void MyClassInitialize(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  testContext)
			//{
			//	try
			//	{
			//		commInterfaceObject = DalCommandInterface_Accessor::Instance;
			//		commInterfaceObject->SetActivePort(comPortName);
			//	}
			//	catch (AtCor::Scor::CrossCutting::ScorException^ scorExObj)
			//	{
			//		Assert::Fail("MyClassInitialize failed: " + scorExObj->ErrorMessageKey);  
			//	}

			//}

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
			//Use TestInitialize to run code before running each test
			public: [TestInitialize]
			System::Void MyTestInitialize()
			{
				SetPath();
			}
			//
			////Use TestCleanup to run code after each test has run
			//public: [TestCleanup]
			//System::Void MyTestCleanup()
			//{
			//	DalCommandInterface_Accessor ^ target = DalCommandInterface_Accessor::Instance;
			//	try
			//	{
			//		target->CloseActivePort();
			//	}
			//	catch(Exception^ ex)
			//	{
			//		delete ex;
			//	}
			//}

			static void MyDalErrorAlarmEventHandler(Object ^sender, DalModuleErrorAlarmEventArgs ^args)
			{
				if (args->ErrorAlarmStatus == DalErrorAlarmStatusFlag::DataCaptureTimeout )
				{
					TimeoutErrorAlarmEventRaised = true;	
				}
			}
			
#pragma endregion
			/// <summary>
			///A test for Instance
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void InstanceTest()
			{
				DalCommandInterface_Accessor^  actual;
				actual = DalCommandInterface_Accessor::Instance;
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for ValidateResponsePacket
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ValidateResponsePacketTest1()
			{
				DalEM4Command_Accessor^  serialCommand = nullptr; // TODO: Initialize to an appropriate value
				DalReturnValue expected = DalReturnValue(); // TODO: Initialize to an appropriate value
				DalReturnValue actual;
				actual = DalCommandInterface_Accessor::ValidateResponsePacket(serialCommand);
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for ValidateResponsePacket
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ValidateResponsePacketTest()
			{
				EM4DataCapturePacket_Accessor^  capturePacket = nullptr; // TODO: Initialize to an appropriate value
				DalReturnValue expected = DalReturnValue(); // TODO: Initialize to an appropriate value
				DalReturnValue actual;
				actual = DalCommandInterface_Accessor::ValidateResponsePacket(capturePacket);
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for ValidateResponseCRC
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ValidateResponseCRCTest1()
			{
				EM4DataCapturePacket_Accessor^  capturePacket = nullptr; // TODO: Initialize to an appropriate value
				bool expected = false; // TODO: Initialize to an appropriate value
				bool actual;
				actual = DalCommandInterface_Accessor::ValidateResponseCRC(capturePacket);
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for ValidateResponseCRC
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ValidateResponseCRCTest()
			{
				DalEM4Command_Accessor^  serialCommand = nullptr; // TODO: Initialize to an appropriate value
				bool expected = false; // TODO: Initialize to an appropriate value
				bool actual;
				actual = DalCommandInterface_Accessor::ValidateResponseCRC(serialCommand);
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for ValidateCommandResult
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ValidateCommandResultTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); // TODO: Initialize to an appropriate value
				DalEM4Command_Accessor^  serialCommand = nullptr; // TODO: Initialize to an appropriate value
				DalReturnValue responseReturnValue = DalReturnValue(); // TODO: Initialize to an appropriate value
				DalReturnValue expected = DalReturnValue(); // TODO: Initialize to an appropriate value
				DalReturnValue actual;
				actual = target->ValidateCommandResult(serialCommand, responseReturnValue);
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for ValidateCommand
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ValidateCommandTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); // TODO: Initialize to an appropriate value
				DalEM4Command_Accessor^  serialCommand = nullptr; // TODO: Initialize to an appropriate value
				bool expected = false; // TODO: Initialize to an appropriate value
				bool actual;
				actual = target->ValidateCommand(serialCommand);
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for StreamingPacketReadHandler
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void StreamingPacketReadHandlerTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); // TODO: Initialize to an appropriate value
				Object^  sender = nullptr; // TODO: Initialize to an appropriate value
				ElapsedEventArgs^  e = nullptr; // TODO: Initialize to an appropriate value
				target->StreamingPacketReadHandler(sender, e);
				Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for StopDataCaptureModeInternal
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void StopDataCaptureModeInternalTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); // TODO: Initialize to an appropriate value
				bool expected = false; // TODO: Initialize to an appropriate value
				bool actual;
				actual = target->StopDataCaptureModeInternal();
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for StopDataCaptureMode
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void StopDataCaptureModeTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); // TODO: Initialize to an appropriate value
				bool expected = false; // TODO: Initialize to an appropriate value
				bool actual;
				actual = target->StopDataCaptureMode();
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for SignalResponsePacketAvailable
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SignalResponsePacketAvailableTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); // TODO: Initialize to an appropriate value
				target->SignalResponsePacketAvailable();
				Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for SetInstanceObject
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetInstanceObjectTest()
			{
				DalCommandInterface_Accessor^  newObject = gcnew DalCommandInterface_Accessor(); //create a new object
				
				//The singletone pattern will have instantiated an instance
				Assert::IsNotNull( DalCommandInterface_Accessor::_instance); //Not null

				//now create an object of a child type
				DalCommandInterface_Accessor^ childObject = gcnew DalPwvCommandInterface_Accessor();

				DalCommandInterface_Accessor::SetInstanceObject(childObject);
				Assert::AreEqual(childObject, DalCommandInterface_Accessor::_instance);
			}

			/// <summary>
			///A test for SendCommandPacketWithRetries
			///</summary>
			public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SendCommandPacketWithRetries_NoData_Test()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); // TODO: Initialize to an appropriate value
				
				//create a command object
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {0x08};
				DalEM4Command_Accessor^  serialCommand =  gcnew DalEM4Command_Accessor(0x0B, dataCode);

				//Set the port to the virtual port that we have created
				//this will ensure that DalCommandInterface::ValidateCommand() does not fail when it tests the port
				//The actual port is irreleavnt as long as it is a valid port
				DalActivePort_Accessor::Instance->SetActivePort("COM10");

				DalReturnValue expected = DalReturnValue::Timeout ; 
				DalReturnValue actual;
				actual = target->SendCommandPacketWithRetries(serialCommand);
				Assert::AreEqual(expected, actual);
				
			}

			/// <summary>
			///A test for SendCommandPacketWithRetries
			///</summary>
			public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SendCommandPacketWithRetries_DataRecieved_Test()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor());
				
				//create a command object
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {0x08};
				DalEM4Command_Accessor^  serialCommand =  gcnew DalEM4Command_Accessor(0x0B, dataCode);

				DalReturnValue expected = DalReturnValue::Success ; 
				DalReturnValue actual;

				//Force the sequence number to be what we want for processing
				DalSequenceNumberManager_Accessor::_nextCommandSequenceNumber = 0x00;

				//Set the port to the virtual port that we have created
				//this will ensure that DalCommandInterface::ValidateCommand() does not fail when it tests the port
				//The actual port is irreleavnt as long as it is a valid port
				DalActivePort_Accessor::Instance->SetActivePort("COM10");

				//Mock the response keep the response ready in the staging area
				DalStagingQueue_Accessor::Instance->LookForResponseToCommand(0x0B, 17);
				DalStagingQueue_Accessor::Instance->EnqueueArray(gcnew array<unsigned char> {0x8B, 0x11, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x20, 0x00, 0x30});
				DalStagingQueue_Accessor::Instance->SignalDataAvailable();

				actual = target->SendCommandPacketWithRetries(serialCommand);
				Assert::AreEqual(expected, actual);
			}

			/// SendCOmmandAndGetResponse is just a facade for DalCommandInterface::ProcessCommandAndResponse()
			// through the state machine. Hence we are not testing it.
			///A test for SendCommandAndGetResponse
			///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void SendCommandAndGetResponseTest()
	//		{
	//			DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
	//			
	//			//create a command object
	//			array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {0x08};
	//			DalEM4Command_Accessor^  serialCommand =  gcnew DalEM4Command_Accessor(0x0B, dataCode);

	//			DalReturnValue expected = DalReturnValue(); // TODO: Initialize to an appropriate value
	//			DalReturnValue actual;
	//			actual = target->SendCommandAndGetResponse(serialCommand);
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}

			/// <summary>
			///A test for ResponseListenerThreadMethod
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ResponseListenerThreadMethod_NoData_Test()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
				//create a command object
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {0x08};
				DalEM4Command_Accessor^  serialCommand =  gcnew DalEM4Command_Accessor(0x0B, dataCode);
			
				//call the method
				target->ResponseListenerThreadMethod(serialCommand);
				//there is no response from EM4. Hence the data should be numm
				Assert::IsNull(serialCommand->em4Response);
			}

			/// <summary>
			///A test for ResponseListenerThreadMethod
			///</summary>
		public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ResponseListenerThreadMethod_DataRecieved_Test()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
				DalCommandInterface_Accessor::Instance->SetInstanceObject(target);
				//create a command object
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {0x08};
				DalEM4Command_Accessor^  serialCommand =  gcnew DalEM4Command_Accessor(0x0B, dataCode);

				array<unsigned char>^ responseData = gcnew array<unsigned char> {0x8B, 0x11, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x20, 0x00, 0x30};

				//initialise the listenerThread otherwise it will raise an exception
				target->ListenForEM4Response(serialCommand);


				//precondition: Put the data in the response buffer before calling the method under test
				DalResponsePacketBuffer_Accessor::Instance->Enqueue(responseData);
			
				//call the method
				target->ResponseListenerThreadMethod(serialCommand);

				//It should show that it has got the data.
				Assert::IsNotNull(serialCommand->em4Response);
			}


			/// <summary>
			///A test for ProcessStreamingPackets
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ProcessStreamingPacketsTest()
			{
				//Precondition: This test needs at least one packet in the streaming queue

				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
				bool expected = true; 
				bool actual;

				//Precondtition: Create the data  bufffer or else it will throw an exception
				DalDataBuffer_Accessor::Instance->CreateBuffer(10, 10);

				//precondition: put some packet in the input buffer
				cli::array< unsigned char >^  streamingPacket = gcnew array<unsigned char> {0x87, 0x0D, 0x02, 0x00, 0x00, 0x72, 0x33, 0x00, 0x11, 0x00, 0xB4, 0x20, 0x00, 0xEA};  //any valid packet
				DalStreamingPacketQueue_Accessor::Instance->Enqueue(streamingPacket);


				actual = target->ProcessStreamingPackets();
				Assert::AreEqual(expected, actual);
				
			}

			/// <summary>
			///A test for ProcessStreamingPackets
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ProcessStreamingPackets_NoData_Test()
			{
				//Precondition: This test needs at least one packet in the streaming queue

				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
				bool expected = true; 
				bool actual;

				//Precondtition: Create the data  bufffer or else it will throw an exception
				DalDataBuffer_Accessor::Instance->CreateBuffer(10, 10);

				//precondition:there will be no packets to process
				
				actual = target->ProcessStreamingPackets();
				Assert::AreEqual(expected, actual);
				
			}
			/// <summary>
			///A test for ProcessSingleStreamingPacket
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ProcessSingleStreamingPacketTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor());
				cli::array< unsigned char >^  streamingPacket = gcnew array<unsigned char> {0x87, 0x0D, 0x02, 0x00, 0x00, 0x72, 0x33, 0x00, 0x11, 0x00, 0xB4, 0x20, 0x00, 0xEA};  //any valid packet
				bool expected = true; 
				bool actual;
				//Create the data  bufffer or else it will throw an exception
				DalDataBuffer_Accessor::Instance->CreateBuffer(10, 10);
				actual = target->ProcessSingleStreamingPacket(streamingPacket);
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for ProcessSingleStreamingPacket
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ProcessSingleStreamingPacket_NoData_Test()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor());
				cli::array< unsigned char >^  streamingPacket = nullptr;  //specifically pass a null packet
				bool expected = false; //should return false as this is a negative scenario
				bool actual;
				//Create the data  bufffer or else it will throw an exception
				DalDataBuffer_Accessor::Instance->CreateBuffer(10, 10);
				actual = target->ProcessSingleStreamingPacket(streamingPacket);
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for ProcessCommandAndResponse
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ProcessCommandAndResponseTest()
			{

				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 		

				//Force the sequence number to be what we want for processing
				DalSequenceNumberManager_Accessor::_nextCommandSequenceNumber = 0x00;

				//create a command object
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {0x08};
				DalEM4Command_Accessor^  serialCommand =  gcnew DalEM4Command_Accessor(0x0B, dataCode);

				//Set the port to the virtual port that we have created
				//this will ensure that DalCommandInterface::ValidateCommand() does not fail when it tests the port
				//The actual port is irreleavnt as long as it is a valid port
				DalActivePort_Accessor::Instance->SetActivePort("COM10");

				//Mock the response keep the response ready in the staging area
				DalStagingQueue_Accessor::Instance->LookForResponseToCommand(0x0B, 17);
				DalStagingQueue_Accessor::Instance->EnqueueArray(gcnew array<unsigned char> {0x8B, 0x11, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x20, 0x00, 0x30});
				DalStagingQueue_Accessor::Instance->SignalDataAvailable();

				DalReturnValue expected = DalReturnValue::Success ; 
				DalReturnValue actual;
				actual = target->ProcessCommandAndResponse(serialCommand);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for op_Assign
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void op_AssignTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
				DalCommandInterface_Accessor^ unnamed ; 
				DalCommandInterface_Accessor^  expected = target; 
				DalCommandInterface_Accessor^  actual;
				actual = ( unnamed = target);
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for ListenForEM4Response
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ListenForEM4Response_NoDataRecieved_Test()
			{
				SetPath(); //needed to find all system files
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor());
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {0x08};

				DalEM4Command_Accessor^  serialCommand =  gcnew DalEM4Command_Accessor(0x0B, dataCode);
				DalReturnValue expected = DalReturnValue::Timeout ; 
				DalReturnValue actual;
				actual = target->ListenForEM4Response(serialCommand);
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for ListenForEM4Response
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ListenForEM4Response_DataRecieved_Test()
			{
				SetPath(); //needed to find all system files
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor());
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {0x08};

				//DalStagingQueue_Accessor::Instance->dataProcessingThread->Start();
				DalStagingQueue_Accessor::Instance->LookForResponseToCommand(0x0B, 17);
				DalStagingQueue_Accessor::Instance->EnqueueArray(gcnew array<unsigned char> {0x8B, 0x11, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x20, 0x00, 0x30});
				DalStagingQueue_Accessor::Instance->SignalDataAvailable();

				DalEM4Command_Accessor^  serialCommand =  gcnew DalEM4Command_Accessor(0x0B, dataCode);
				DalReturnValue expected = DalReturnValue::Success ; 
				DalReturnValue actual;
				//start the data processing thread

				//ensure that the data is available in the staging area

				//now call the method under test
				actual = target->ListenForEM4Response(serialCommand);
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for InitiateDataCaptureModeInternal
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void InitiateDataCaptureModeInternalTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
				bool expected = true; // TODO: Initialize to an appropriate value
				bool actual;
				actual = target->InitiateDataCaptureModeInternal();
				Assert::AreEqual(expected, actual);
			
			}

			/// <summary>
			///A test for InitiateDataCaptureMode
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void InitiateDataCaptureModeTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 
				bool expected = true; // TODO: Initialize to an appropriate value
				bool actual;
				actual = target->InitiateDataCaptureMode();
				Assert::AreEqual(expected, actual);
			}


			/// <summary>
			///A test for ChangeCommandState
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ChangeCommandStateTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor()); 

				Assert::IsNotNull(target->_currentCommandState); //pretest

				DalCommandState_Accessor^  newCommandState = gcnew DalCommandStateResponseReceived_Accessor ; //give a different state
				DalCommandState_Accessor^ oldCommandState; 

				oldCommandState = target->_currentCommandState; //save the old state for comparison
				target->ChangeCommandState(newCommandState);
				
				Assert::AreEqual(newCommandState, target->_currentCommandState);
				Assert::AreNotEqual(newCommandState, oldCommandState);
			}
			/// <summary>
			///A test for ChangeCaptureState
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ChangeCaptureStateTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor());
				DalCaptureState_Accessor^  newCaptureState = gcnew DalCaptureStateNotListening_Accessor() ; // TODO: Initialize to an appropriate value
				DalCaptureState_Accessor^ oldCaptureState;


				//pre test:
				Assert::IsNotNull(target->_currentCaptureState);
				oldCaptureState = target->_currentCaptureState;
				DalCommandInterface_Accessor::ChangeCaptureState(newCaptureState);
				//check
				Assert::IsNotNull(target->_currentCaptureState);
				Assert::AreEqual(newCaptureState,target->_currentCaptureState);
				Assert::AreNotEqual(oldCaptureState, newCaptureState);
			}
			/// <summary>
			///A test for DalCommandInterface Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalCommandInterfaceConstructorTest()
			{
				DalCommandInterface_Accessor^  target = (gcnew DalCommandInterface_Accessor());

				Assert::IsNotNull(target);
				Assert::IsNotNull(target->_currentCommandState);
				Assert::IsNotNull(target->_currentCaptureState);
			}
	};
}
namespace TestDal {
    
}
