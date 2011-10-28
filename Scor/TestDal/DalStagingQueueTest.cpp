
#include "StdAfx.h"

using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting;
using namespace System::IO;

namespace TestDal {
    using namespace System;
    ref class DalStagingQueueTest;
    
    
    /// <summary>
///This is a test class for DalStagingQueueTest and is intended
///to contain all DalStagingQueueTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalStagingQueueTest
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

	public:

		static bool eventRaised = false;
		static array<unsigned char> ^ recievedArray;

		static void MyNibpPacketEventRaisedTester(Object ^sender, NibPacketArrivedEventArgs_Accessor ^ args)
		 {
			 eventRaised = true;
			 recievedArray = args->nibpPacket;
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
			public: [TestInitialize]
			System::Void MyTestInitialize()
			{
				SetPath();
			}
			//
			//Use TestCleanup to run code after each test has run
			//public: [TestCleanup]
			//System::Void MyTestCleanup()
			//{
			//}
			//
#pragma endregion
			/// <summary>
			///A test for Instance
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void InstanceTest()
			{
				DalStagingQueue_Accessor^  actual;
				actual = DalStagingQueue_Accessor::Instance;
				Assert::IsNotNull(actual);
			}
	//		/// <summary>
	//		///A test for ProcessQueue
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void ProcessQueueTest()
	//		{
	//			DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
	//			bool expected = false; // Que is empty so we are not going to process any data
	//			//bool actual;
	//			/*actual = target->ProcessQueue();
	//			Assert::AreEqual(expected, actual);*/
	//			Assert::Inconclusive("Test needs to be rewritten due to changes in code");
	//		
	//		}
			/// <summary>
			///A test for op_Assign
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void op_AssignTest()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); // TODO: Initialize to an appropriate value
				DalStagingQueue_Accessor^  unnamed = nullptr; // TODO: Initialize to an appropriate value
				DalStagingQueue_Accessor^  expected = nullptr; // TODO: Initialize to an appropriate value
				DalStagingQueue_Accessor^  actual;
				actual = (target = unnamed);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for LookForResponseToCommand
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void LookForResponseToCommandTest()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				unsigned char commandCodeToLocate = 0x0B; //any value will do for testing 
				unsigned char expectedResponseLengthToLocate = 0x05; //any value will do for testing 
				unsigned char expectedSequenceNumberToLocate = 0x0A; //any value will do for testing 
				
				target->LookForResponseToCommand(commandCodeToLocate, expectedResponseLengthToLocate);

				Assert::IsTrue(target->checkForCommand);
				Assert::AreEqual(commandCodeToLocate, target->commandCodeToLocate);
				Assert::AreEqual(expectedResponseLengthToLocate, target->expectedResponseLengthToLocate);
				//Assert::AreEqual(expectedSequenceNumberToLocate, target->expectedSequenceNumberToLocate);
			}
			/// <summary>
			///A test for ExtractStreamingDataPacket
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ExtractStreamingDataPacketTest()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				cli::array< unsigned char >^  expected =gcnew array<unsigned char> {0x87, 0x0D, 0x06, 0x00, 0x00, 0x8B, 0x57, 0x0F, 0x82, 0x00, 0xB4, 0x60, 0x00, 0x7E }; // enqueue a streaming packet
				cli::array< unsigned char >^  actual;

				//PRECONDIIONS
				//First push the streaming packet onto the array
				target->EnqueueArray(expected);

				actual = target->ExtractStreamingDataPacket();

				//POST
				//check the entire array
				for (int i = 0; i < expected->Length; i++)
				{
					Assert::AreEqual(expected[i], actual[i]);
				}
			
			}
			/// <summary>
			///A test for ExtractNackedResponsePacket
			/////ACKed response will vary so the data picked by this method should be dependandt on the lenght pro
			//provided by the LookFor... method
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ExtractAckedResponsePacketTest()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				cli::array< unsigned char >^  expected =gcnew array<unsigned char> {0x8B, 0x11, 0x01, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xB0, 0xB1, 0xB2, 0x60, 0x01, 0x1D }; // TODO: Initialize to an appropriate value
				cli::array< unsigned char >^  actual;

				//PRECONDIIONS
				//First push the response onto the array
				target->EnqueueArray(expected);

				//set the "lookout command"
				//sequence number doesnt matter ut length does since the expected response is a nack
				target->LookForResponseToCommand(0x0B, 0x11); 
				
				//First verify that the Lookout flag has been turned off
				Assert::IsTrue(target->checkForCommand);


				//TEST
				actual = target->ExtractAckedResponsePakcet();

				//POST
				//check the entire array
				for (int i = 0; i < expected->Length; i++)
				{
					Assert::AreEqual(expected[i], actual[i]);
				}

				//now verify that the Lookout flag has been turned off
				Assert::IsFalse(target->checkForCommand);
		
			}
			/// <summary>
			///A test for ExtractAckedResponsePakcet
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ExtractNackedResponsePakcetTest()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 

				cli::array< unsigned char >^  expected = gcnew array<unsigned char> {0x0B, 0x01,0x06, 0x01, 0x02, 0x03, 0xFF}; // seetig to nack of GetConfig. All values excep CC are incorrect
				cli::array< unsigned char >^  actual;
				//First push the response onto the array
				target->EnqueueArray(expected);
				//set the "lookout command"
				target->LookForResponseToCommand(0x0B, 0x11); //sequence number and length dont matter since the expected response is a nack
				actual = target->ExtractNackedResponsePacket();
				//Assert::AreEqual(expected, actual);

				//check the entire array
				for (int i = 0; i < expected->Length; i++)
				{
					Assert::AreEqual(expected[i], actual[i]);
				}

				//now verify that the Lookout flag has been turned off
				Assert::IsFalse(target->checkForCommand);
		
			}
			//Already covered in Destructor test
	//		/// <summary>
	//		///A test for Dispose
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void DisposeTest1()
	//		{
	//			DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); // TODO: Initialize to an appropriate value
	//			//target->Dispose(); TODO: come back to this later
	//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
	//		/// <summary>
	//		///A test for Dispose
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void DisposeTest()
	//		{
	//			DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); // TODO: Initialize to an appropriate value
	//			bool unnamed = false; // TODO: Initialize to an appropriate value
	//			//target->Dispose(unnamed); TODO: come back to this later
	//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}

			/// <summary>
			///A test for DeterminePacketType
			///Should return a value based on the commandCodeByte provided
			//Case 1 is for a streaming pakcet
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DeterminePacketTypeTest()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				unsigned char commandCodeByte = 0x87; // value shoud return a streaming type
				DalPacketType_Accessor^  expected = DalPacketType_Accessor::StreamingDataPacket; 
				DalPacketType_Accessor^  actual;
				actual = target->DeterminePacketType(commandCodeByte);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Test passes without code being written");
			}

			/// <summary>
			///A test for DeterminePacketType
			///Should return a value based on the commandCodeByte provided
			//Case 2 is for a valid Command ACK which is expected
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DeterminePacketTypeTestAckedCommandExpected()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				unsigned char commandCodeByte = 0x8B; // acked GetConfig response
				
				//set the values which will tell that the command response is expected.
				target->checkForCommand = true;
				target->commandCodeToLocate = 0x0B; //code to look for

				DalPacketType_Accessor^  expected = DalPacketType_Accessor::AckedResponsePakcet; //shold be an acked response packet 
				DalPacketType_Accessor^  actual;
				actual = target->DeterminePacketType(commandCodeByte);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Test passes without code being written");
			}


			/// <summary>
			///A test for DeterminePacketType
			///Should return a value based on the commandCodeByte provided
			//Case 7 is for a valid NIBP Packet which is expected
			public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DeterminePacketTypeTestNibpCommandExpected()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				unsigned char commandCodeByte = 0x93; // Valid NIBP response header
				
				//set the values which will tell that the command response is expected.
				target->checkForCommand = true;
				target->commandCodeToLocate = 0x00; //Can be anything. We are not looking for a particular command respinse

				DalPacketType_Accessor^  expected = DalPacketType_Accessor::NibpPacket ; //shold be an NIBP response packet 
				DalPacketType_Accessor^  actual;
				actual = target->DeterminePacketType(commandCodeByte);
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for DeterminePacketType
			///Should return a value based on the commandCodeByte provided
			//Case 3 is for a valid Command NACK which is expected
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DeterminePacketTypeTestNackedCommandExpected()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				unsigned char commandCodeByte = 0x0B; // NACKED GetConfig response
				
				//set the values which will tell that the command response is expected.
				target->checkForCommand = true;
				target->commandCodeToLocate = 0x0B; //code to look for

				DalPacketType_Accessor^  expected = DalPacketType_Accessor::NackedResponsePacket ; //shold be an acked response packet 
				DalPacketType_Accessor^  actual;
				actual = target->DeterminePacketType(commandCodeByte);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Test passes without code being written");
			}

			/// <summary>
			///A test for DeterminePacketType
			///Should return a value based on the commandCodeByte provided
			//Case 4 is for a valid Command ACK which is NOT expected
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DeterminePacketTypeTestAckedCommandNotExpected()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				unsigned char commandCodeByte = 0x8B; // acked GetConfig response
				
				//We are NOT looking for a response.
				target->checkForCommand = false; 
	
				DalPacketType_Accessor^  expected = DalPacketType_Accessor::Unknown; //should mark that the packet type is unknown
				DalPacketType_Accessor^  actual;
				actual = target->DeterminePacketType(commandCodeByte);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Test passes without code being written");
			}

			/// <summary>
			///A test for DeterminePacketType
			///Should return a value based on the commandCodeByte provided
			//Case 5 is for a valid Command NACK which is NOT expected
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DeterminePacketTypeTestNackCommandNotExpected()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				unsigned char commandCodeByte = 0x0B; // acked GetConfig response
				
				//We are NOT looking for a response.
				target->checkForCommand = false; 
	
				DalPacketType_Accessor^  expected = DalPacketType_Accessor::Unknown; //should mark that the packet type is unknown
				DalPacketType_Accessor^  actual;
				actual = target->DeterminePacketType(commandCodeByte);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Test passes without code being written");
			}

			/// <summary>
			///A test for DeterminePacketType
			///Should return a value based on the commandCodeByte provided
			//Case 6 is for a pakcet command byte which is not recognized
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DeterminePacketTypeInvalidCommandTest()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				unsigned char commandCodeByte = 0x85; // Command 05 does not exist
				DalPacketType_Accessor^  expected = DalPacketType_Accessor::Unknown ;  //should be of this type
				DalPacketType_Accessor^  actual;
				actual = target->DeterminePacketType(commandCodeByte);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Test passes without code being written");
			}


			/// <summary>
			///A test for DequeueArray
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DequeueAsArrayTest()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				int numberOfBytes = 3; 
				cli::array< unsigned char >^  expected = gcnew array<unsigned char> {0x01, 0x02, 0x03}; 
				cli::array< unsigned char >^  actual;

				//First enque the expected values into the array 
				target->stagingQueue->AddRange(expected);

				//pre test
				Assert::AreEqual(3, target->stagingQueue->Count);
				

				//call the method under test
				actual = target->DequeueArray(numberOfBytes);

				
				//now since all the values have been recieved test that the internal array is empty
				Assert::AreEqual(0, target->stagingQueue->Count);

				//verify the values recieved
				for (int i = 0; i< numberOfBytes; i++)
				{
					Assert::AreEqual(expected[i], actual[i]);
				}

			}

	//		/// <summary>
	//		///A test for DequeueArray
	//		/// Should throw exception if you attempt to read from empty buffer
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void DequeueAsArrayExceptionTest()
	//		{
	//			DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
	//			int numberOfBytes = 3; //ask for a number of bytes but dont input any
	//			cli::array< unsigned char >^  expected = gcnew array<unsigned char> {0x01, 0x02, 0x03}; 
	//			cli::array< unsigned char >^  actual;

	//			bool ExceptionRaised = false;

	//			//No need to input should throw exception

	//			try
	//			{

	//				actual = target->DequeueArray(numberOfBytes);
	//			}
	//			catch(ScorException^)
	//			{
	//				ExceptionRaised = true;
	//			}
	//			Assert::IsTrue(ExceptionRaised);
	//		}

			/// <summary>
			///A test for DequeueArray
			/// Should return nullif you attempt to read from empty buffer
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DequeueAsArrayNegativeTest()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				int numberOfBytes = 3; //ask for a number of bytes but dont input any
				//cli::array< unsigned char >^  expected = gcnew array<unsigned char> {0x01, 0x02, 0x03}; 
				cli::array< unsigned char >^  actual;

				//No need to input should throw exception

				try
				{

					actual = target->DequeueArray(numberOfBytes);
				}
				catch(ScorException^)
				{
					Assert::Fail("Exception raised");
				}
				Assert::IsNull(actual);
			
			}

			/// <summary>
			///A test for AddBytes
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void EnqueueArrayTest()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				cli::array< unsigned char >^  sourceArray = gcnew array<unsigned char> {0x01, 0x02, 0x03}; 
				target->EnqueueArray(sourceArray); //call the method under test
								
				//now that the elements have been added deque them and check
				Assert::AreEqual( (unsigned char)0x01, target->stagingQueue[0]);
				Assert::AreEqual( (unsigned char)0x02, target->stagingQueue[1]);
				Assert::AreEqual( (unsigned char)0x03, target->stagingQueue[2]);
			}
			/// <summary>
			///A test for ~DalStagingQueue
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalStagingQueueDestructorTest()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				delete target;
				Assert::IsNull(target->stagingQueue);
				Assert::IsNull( target->stagingMutex);
			}
			/// <summary>
			///A test for DalStagingQueue Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalStagingQueueConstructorTest()
			{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor());
				Assert::IsNotNull(target->stagingQueue);
				Assert::IsNotNull(target->stagingMutex);
			}
			/// <summary>
			///A test for ProcessSinglePacket
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ProcessSinglePacketTest()
		{
			DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
			bool expected = false; 
			bool actual;
			actual = target->ProcessSinglePacket();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for ExtractNibpPacket
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ExtractNibpPacketTest()
		{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				//Assuming a valid NIBP packet
				cli::array< unsigned char >^  expected =gcnew array<unsigned char> {0x93, 0x09, 0x00, 0x3E, 0x04, 0x4F, 0x6F, 0x00, 0x01, 0xEE  }; 
				cli::array< unsigned char >^  actual;

				//PRECONDIIONS
				//First push the response onto the array
				target->EnqueueArray(expected);

				//TEST
				actual = target->ExtractNibpPacket();

				//POST
				//check the entire array
				for (int i = 0; i < expected->Length; i++)
				{
					Assert::AreEqual(expected[i], actual[i]);
				}

				//check that nothing is left in the buffer
				Assert::AreEqual(0, target->stagingQueue->Count);

		}

		/// <summary>
		///A test for ExtractNibpPacket
		///In this case the NIBP packet will be followed by another valid NIBP pakcet
		//but with a different sequence number(to differentiate the packets.
		//The method should only pull out the first packet
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ExtractNibpPacket_FromLargerDataStreamTest()
		{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				//put two NIBP packets. The method shoudl only extract the first
				cli::array< unsigned char >^  testarray =gcnew array<unsigned char> {0x93, 0x09, 0x00, 0x3E, 0x04, 0x4F, 0x6F, 0x00, 0x01, 0xEE , 0x93, 0x09, 0x01, 0x3E, 0x04, 0x4F, 0x6F, 0x00, 0x01, 0x05 }; 
				
				//Assuming a valid NIBP packet
				cli::array< unsigned char >^  expected =gcnew array<unsigned char> {0x93, 0x09, 0x00, 0x3E, 0x04, 0x4F, 0x6F, 0x00, 0x01, 0xEE  }; 
				cli::array< unsigned char >^  actual;

				//PRECONDIIONS
				//First push the response onto the array
				target->EnqueueArray(testarray); //test array should be put in

				//TEST
				actual = target->ExtractNibpPacket();

				//POST
				//check the entire array
				for (int i = 0; i < expected->Length; i++)
				{
					Assert::AreEqual(expected[i], actual[i]);
				}

				//verify that the second command packet is not extracted from the queue
				Assert::AreNotEqual(0, target->stagingQueue->Count);

		}


		/// <summary>
		///A test for ExtractNibpPacket
		///Tests whether the event was raised or not
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ExtractNibpPacket_EventRaisedCheck_Test()
		{
				DalStagingQueue_Accessor^  target = (gcnew DalStagingQueue_Accessor()); 
				//Assuming a valid NIBP packet
				cli::array< unsigned char >^  expected =gcnew array<unsigned char> {0x3E, 0x04, 0x4F, 0x6F}; 
				cli::array< unsigned char >^  actual;
				cli::array< unsigned char >^  em4NibpToHostPacket =gcnew array<unsigned char> {0x93, 0x09, 0x00, 0x3E, 0x04, 0x4F, 0x6F, 0x00, 0x01, 0xEE  }; 
				

				//PRECONDIIONS
				//First push the response onto the array
				target->EnqueueArray(em4NibpToHostPacket);
				
				//ensure that the flag variable is false
				eventRaised = false;

				//register the test handler for the expected event
				//DalEventContainer::Instance->OnDalNibpPacketEvent +=  gcnew NibPPacketArrivedEvent_Accessor(&MyNibpPacketEventRaisedTester );
				//doesnt work anyway

				//TEST
				actual = target->ExtractNibpPacket();

				//POST

				//check that the event was raised
				Assert::IsTrue(eventRaised);

				//then check if the args were copied
				Assert::IsNotNull(recievedArray );

				//check the entire array
				for (int i = 0; i < expected->Length; i++)
				{
					Assert::AreEqual(expected[i], recievedArray[i]);
				}

				//check that nothing is left in the buffer
				Assert::AreEqual(0, target->stagingQueue->Count);

		}
};
}
namespace TestDal {
    
}
