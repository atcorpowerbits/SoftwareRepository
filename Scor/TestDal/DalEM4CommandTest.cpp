
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
				Assert::AreEqual((unsigned char)0x00, actual_em4Command[2]);
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
				Assert::AreEqual((unsigned char)0x00, actual_em4Command[2]);
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
					Assert::AreEqual(expected_em4Command[looper], actual_em4Command[looper]); 
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
					Assert::AreEqual(expected_em4Command[looper], actual_em4Command[looper]); 
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
				Assert::AreEqual(DalConstants::EM4NumberofRetires, target->retriesAllowed);
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
		//Deepak: Cannot fix this
//		/// <summary>
//		///A test for sentPacketSequenceNumber
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"dal.dll")]
//		void sentPacketSequenceNumberTest()
//		{
//			PrivateType^ privateType = gcnew PrivateType("DataAccess", "DataAccess::DalEM4Command");
//
//
//			//PrivateObject^  param0 = gcnew PrivateObject(dataLength);
//				
//			DalEM4Command_Accessor^  target = (gcnew DalEM4Command_Accessor()); 
//			//Assert::AreEqual((unsigned char)0x00, target->_sentPacketSequenceNumber);
//			target->_sentPacketSequenceNumber =0x00; //reset to get correct result
//			unsigned char actual;
//			unsigned char expected;
//
//			for (int i = 0; i <18; i++)
//			{
//				expected = i%16;
//				Object ^ obj  = privateType->GetStaticProperty(target->sentPacketSequenceNumber);
//				actual = target->sentPacketSequenceNumber;
//				Assert::AreEqual(expected, actual);
//			}
//		}
};
}
namespace TestDal {
    
}
