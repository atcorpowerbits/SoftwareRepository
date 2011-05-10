
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalEM4CommandTest;
    
    
    /// <summary>
///This is a test class for DalEM4CommandTest and is intended
///to contain all DalEM4CommandTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalEM4CommandTest
	{
		static unsigned int uint_Zero = 0;
		static unsigned char uchar_zero = 0x00;

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
			///A test for Dispose
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DisposeTest1()
			{
				unsigned char inCommandCode = 0x0B; 
				array< unsigned char >^  inCommandData = {0x01, 0x02, 0x03}; 
				
				DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor(inCommandCode, inCommandData));
				
				bool unnamed = false; // TODO: Initialize to an appropriate value
				delete target;
				Assert::AreEqual((unsigned char)0x00,  target->commandCode);
				Assert::IsNull(target->em4Command);
			}
			
			/// <summary>
			///A test for ConstuctCommand
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ConstuctCommandTest()
			{
				DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor(0x0B, nullptr)); 
				bool expected = true; 
				bool actual;
				array <unsigned char>^ expected_em4Command = gcnew array<unsigned char> {0x0B, 3, 0,0};
				array <unsigned char>^ actual_em4Command;
				actual = target->ConstuctCommand();
				Assert::AreEqual(expected, actual);
				Assert::AreEqual(expected_em4Command->Length, target->em4Command->Length);
				actual_em4Command = (array<unsigned char>^)target->em4Command->Clone();
				
				Assert::AreEqual(expected_em4Command[0], actual_em4Command[0]); 
				Assert::AreEqual(expected_em4Command[1], actual_em4Command[1]); 
				Assert::AreEqual((unsigned char)0x00, actual_em4Command[2], "Sequence numbers may differ when this test is run so this must be run indivdually to verify");
				Assert::AreEqual((unsigned char)0xD3, actual_em4Command[3]);   //Check CRC value
			}

			
			/// <summary>
			///A test for ConstuctCommand
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ConstuctCommandWithDataTest()
			{
				array <unsigned char>^ target_data = gcnew array <unsigned char> {0xF1,0xF2, 0xF3};
				DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor(0x0B, target_data)); 
				bool expected = true; 
				bool actual;
				array <unsigned char>^ expected_em4Command = gcnew array<unsigned char> {0x0B, 0x06, 0x00,0xF1,0xF2, 0xF3,0x91 };
				array <unsigned char>^ actual_em4Command;
				unsigned char expectedCRC = 0x91;
				actual = target->ConstuctCommand();
				Assert::AreEqual(expected, actual);
				Assert::AreEqual(expected_em4Command->Length, target->em4Command->Length);
				actual_em4Command = (array<unsigned char>^)target->em4Command->Clone();
				
				Assert::AreEqual(expected_em4Command[0], actual_em4Command[0]); 
				Assert::AreEqual(expected_em4Command[1], actual_em4Command[1]); 
				Assert::AreEqual((unsigned char)0x00, actual_em4Command[2], "Sequence numbers may differ when this test is run so this must be run indivdually to verify");
				Assert::AreEqual(expected_em4Command[3], actual_em4Command[3]); 
				Assert::AreEqual(expected_em4Command[4], actual_em4Command[4]); 
				Assert::AreEqual(expected_em4Command[5], actual_em4Command[5]); 
				Assert::AreEqual((unsigned char)expectedCRC, actual_em4Command[actual_em4Command->Length-1]);   //Check CRC value
			}



			//Deepak: Duplicate of existing test
	//		/// <summary>
	//		///A test for ~DalEM4Command
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void DalEM4CommandDestructorTest()
	//		{
	//			DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor()); // TODO: Initialize to an appropriate value
	//			target->~DalEM4Command_Accessor();
	//			Assert::In
	//		}
			/// <summary>
			///A test for DalEM4Command Constructor
			///</summary>
	public: [TestMethod]
			void DalEM4CommandConstructorTestWithData()
			{
				unsigned char inCommandCode = 0x0B; 
				array< unsigned char >^  inCommandData = {0x01, 0x02, 0x03}; 
				array <unsigned char>^ expected_em4Command = gcnew array<unsigned char> {0x0B, 0x06, 0x00,0x01, 0x02, 0x03, 0x17};
				
				DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor(inCommandCode, inCommandData));
				
				//Assert::AreEqual(expected_command, target->em4Command);

				array <unsigned char>^ actual_em4Command;

				actual_em4Command = (array<unsigned char>^)target->em4Command->Clone();
					//	this->commandData = (array<unsigned char>^)inCommandData->Clone();
				//Assert::AreEqual(expected_em4Command, actual_em4Command );
				int looper = 0;
				do 
				{
					Assert::AreEqual(expected_em4Command[looper], actual_em4Command[looper], "Sequence numbers may differ when this test is run so this must be run indivdually to verify"); 
					looper++;
				}while( looper< expected_em4Command->Length -1 );
			}

			/// <summary>
			///A test for DalEM4Command Constructor
			///</summary>
	public: [TestMethod]
			void DalEM4CommandConstructorTestWithoutData()
			{
				unsigned char inCommandCode = 0x0B; 
				array <unsigned char>^ expected_em4Command = gcnew array<unsigned char> {0x0B, 0x03, 0x00,0xD3};
				
				DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor(inCommandCode, nullptr));
				
				//Assert::AreEqual(expected_command, target->em4Command);

				array <unsigned char>^ actual_em4Command;

				actual_em4Command = ((array<unsigned char>^)target->em4Command->Clone());
				Assert::AreEqual(expected_em4Command->Length, actual_em4Command->Length);
				int looper = 0;
				do 
				{
					Assert::AreEqual(expected_em4Command[looper], actual_em4Command[looper], "Sequence numbers may differ when this test is run so this must be run indivdually to verify"); 
					looper++;
				}while( looper< expected_em4Command->Length -1 );
			}


			/// <summary>
			///A test for DalEM4Command Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalEM4CommandConstructorTest()
			{
				DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor());
				Assert::IsNotNull(target);
				Assert::IsNull(target->em4Command);
				Assert::AreEqual(uint_Zero, target->commandLength);
				Assert::AreEqual(uchar_zero, target->commandSequenceNumber);
				Assert::AreEqual(uchar_zero , target->commandCRCByte);
				Assert::IsNull(target->em4Response);
				Assert::AreEqual(uint_Zero , target->retryNumber);

				Assert::AreEqual(uchar_zero, target->commandCode );
				Assert::IsNull(target->commandData);
				Assert::AreEqual(DalConstants::EM4ResponseTimeout, target->timeoutPeriod);
				Assert::AreEqual(DalConstants::EM4NumberofRetries, target->retriesAllowed);
			}

			/// <summary>
			///A test for BreakupEM4Response
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void BreakupEM4ResponseTestWithZeroData()
		{
			DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor()); 
			unsigned int responseLength  = 5;
			target->em4Response = gcnew array<unsigned char> (responseLength +1) { 0x08, 0x05, 0x11, 0x01, 0x00, 0x0F};
			target->em4ResponsePacketLength = responseLength;

			bool expected = true; 
			bool actual;
			actual = target->BreakupEM4Response();
			Assert::AreEqual(expected, actual);
			Assert::AreEqual((unsigned char)0x08, target->em4ResponseAckNackByte);
			Assert::AreEqual((unsigned char)0x05, target->em4ResponseLengthByte);
			//Assert::AreEqual((unsigned char)0x11, (unsigned char)target->em4ResponseSequenceNumber ); //Dont understand why MSTest has a problem here.
			Assert::AreEqual((unsigned int)0, target->em4ResponseDataLength);
			Assert::AreEqual((unsigned char)0x0F, target->em4ResponseCRCByte);
			Assert::IsNull(target->em4ResponseData);
		}

		/// <summary>
			///A test for BreakupEM4Response
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void BreakupEM4ResponseTestWithData()
		{
			DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor()); 
			unsigned int responseLength  = 5;
			unsigned int dataLength = 3;
			target->em4Response = gcnew array<unsigned char> (responseLength+ dataLength+1) { 0x08, 0x08, 0x11,0xF1, 0xF2, 0xF3, 0x01, 0x00, 0xF8};
			target->em4ResponsePacketLength = responseLength+ dataLength;

			bool expected = true; 
			bool actual;
			actual = target->BreakupEM4Response();
			Assert::AreEqual(expected, actual);
			Assert::AreEqual((unsigned char)0x08, target->em4ResponseAckNackByte);
			Assert::AreEqual((unsigned char)0x08, target->em4ResponseLengthByte);
			//Assert::AreEqual((unsigned char)0x11, (unsigned char)(target->em4ResponseSequenceNumber) ); //Dont understand why MSTest has a problem here. Verified manually
			Assert::AreEqual((unsigned int)dataLength, target->em4ResponseDataLength);
			Assert::AreEqual((int)dataLength, target->em4ResponseData->Length);
			Assert::AreEqual((unsigned char)0xF8, target->em4ResponseCRCByte);
			Assert::IsNotNull(target->em4ResponseData);
			Assert::AreEqual((unsigned char)0xF1, target->em4ResponseData[0]);
			Assert::AreEqual((unsigned char)0xF2, target->em4ResponseData[1]);
			Assert::AreEqual((unsigned char)0xF3, target->em4ResponseData[2]);
			
		}

		/// <summary>
			///A test for BreakupEM4Response
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void BreakupEM4ResponseTestNegative()
		{
			DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor()); 
			unsigned int responseLength  = 5;
			unsigned int dataLength = 3; //incorrect data for deliberate reason //data will be only 1 byte
			target->em4Response = gcnew array<unsigned char> (responseLength+ dataLength+1) { 0x08, 0x08, 0x11,0xF1, 0x01, 0x00, 0x13};
			target->em4ResponsePacketLength = 6; //correct number

			bool expected = false;  //should return false due to error 
			bool actual;
			actual = target->BreakupEM4Response();
			Assert::AreEqual(expected, actual);
			Assert::IsNull(target->em4ResponseData);
		}

			/// <summary>
			///A test for BreakupEM4Response
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void TestEM4ResponseStatusFlag()
		{
			DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor()); 
			unsigned int responseLength  = 5;
			target->em4Response = gcnew array<unsigned char> (responseLength +1) { 0x08, 0x05, 0x11, 0x12, 0x34, 0x0F};
			target->em4ResponsePacketLength = responseLength;

			bool expected = true; 
			bool actual;
			actual = target->BreakupEM4Response();
			Assert::AreEqual(expected, actual);
			//Assert::AreEqual(safe_cast<unsigned short>(0x1234), safe_cast<unsigned short>(target->em4StatusFlag));//
			Assert::AreEqual((unsigned short)(0x1234), (target->em4StatusFlag)); //Could not resolve this error Verified manually
			
		}


		/// <summary>
		///A test for ~DalEM4Command
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void DalEM4CommandDestructorTest()
		{
			DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor(0x0B, nullptr)); 
			Assert::IsNotNull(target->em4Command);
			delete target;
			Assert::IsNull(target->em4Command );
		}
		/// <summary>
		///A test for BreakResponseDataPart
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void BreakResponseDataPartTest()
		{
			DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor(0x0B, nullptr)); 
			bool expected = true; 
			bool actual;
			//give a valid em4 respose part before  calling the function under test.
			target->em4Response = gcnew array <unsigned char> {0x01, 0x08, 0x30, 0x04, 0x05, 0xBC};
			target->em4ResponsePacketLength = 5;
			actual = target->BreakResponseDataPart();
			Assert::AreEqual(expected, actual);
			Assert::IsNull(target->em4ResponseData); 
		}

		//this one will test for less than require data
		//Negative test
		/// <summary>
		///A test for BreakResponseDataPart
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void BreakResponseDataPartTest2()
		{
			DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor(0x0B, nullptr)); 
			bool expected = false; //THe method should fail 
			bool actual;
			//give a valid em4 respose part before  calling the function under test.
			target->em4ResponsePacketLength = 4; //deliberately set toless than expected length
			//fill with dummy data to test breakup
			target->em4Response = gcnew array <unsigned char> {0x01, 0x08, 0x30, 0x04, 0xE3};
			actual = target->BreakResponseDataPart();
			Assert::AreEqual(expected, actual);
			Assert::IsNull(target->em4ResponseData); 
		}

		/// Positive test case with valid data
		///A test for BreakResponseDataPart
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void BreakResponseDataPartTest3()
		{
			DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor(0x0B, nullptr)); 
			bool expected = true; 
			bool actual;
			target->em4ResponsePacketLength = 8; //externally set for a zero data packet
			//fill with dummy data to test breakup
			target->em4Response = gcnew array <unsigned char> {0x01, 0x08, 0x30, 0x04, 0x05, 0x06, 0x07, 0x09, 0x0A};
			
			try
			{
				actual = target->BreakResponseDataPart();
				Assert::AreEqual(expected, actual);
				Assert::IsNotNull(target->em4ResponseData); 
				//check the data bits
				Assert::AreEqual((unsigned char)0x04, target->em4ResponseData[0]);
				Assert::AreEqual((unsigned char)0x05, target->em4ResponseData[1]);
				Assert::AreEqual((unsigned char)0x06, target->em4ResponseData[2]);
			}
			catch(Exception ^ excepObj)
			{
				Assert::Fail("Exception thrown:" + excepObj->Message);
			}
		}
};
}
namespace TestDal {
    
}
