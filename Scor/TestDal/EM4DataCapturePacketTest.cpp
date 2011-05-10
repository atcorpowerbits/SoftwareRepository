
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
    ref class EM4DataCapturePacketTest;
    
    
    /// <summary>
///This is a test class for EM4DataCapturePacketTest and is intended
///to contain all EM4DataCapturePacketTest Unit Tests
///</summary>
	[TestClass]
	public ref class EM4DataCapturePacketTest
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
			///A test for Dispose
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DisposeTest1()
			{
				unsigned int  dataLength = 4; 
				PrivateObject^  param0 = gcnew PrivateObject(dataLength);
				EM4DataCapturePacket_Accessor^  target = (gcnew EM4DataCapturePacket_Accessor(dataLength)); 
				Assert::IsNotNull(target->em4ResponseData);
				Assert::IsNotNull(target->em4Response);
				delete target;
				Assert::IsNull(target->em4ResponseData);
				Assert::IsNull(target->em4Response);
			}

			/// <summary>
			///A test for Dispose
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DisposeTest()
			{
				unsigned int  dataLength = 0; // TODO: Initialize to an appropriate value
				EM4DataCapturePacket_Accessor^  target = (gcnew EM4DataCapturePacket_Accessor(dataLength)); 
				Assert::IsNull(target->em4ResponseData);
				Assert::IsNotNull(target->em4Response);
				delete target;
				Assert::IsNull(target->em4ResponseData);
				Assert::IsNull(target->em4Response);
			}
			/// <summary>
			///A test for BreakupEM4Response
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void BreakupEM4ResponseTest()
			{
				unsigned int  dataLength = 3;
				EM4DataCapturePacket_Accessor^  target = (gcnew EM4DataCapturePacket_Accessor(dataLength)); 
				target->em4ResponsePacketLength = 8; //this is set externally in the listener
				//fill with dummy data to test breakup
				target->em4Response = gcnew array <unsigned char> {0x01, 0x08, 0x30, 0x04, 0x05, 0x06, 0x07, 0x09, 0x0A};
				bool expected = true; 
				bool actual;
				actual = target->BreakupEM4Response();

				Assert::AreEqual(expected, actual);
				Assert::AreEqual((int)(dataLength + DalConstants::EM4ZeroDataResponsePacketSize +1), target->em4Response->Length ); //+1 for CRC
				Assert::IsNotNull(target->em4ResponseData);
				Assert::AreEqual(dataLength, target->em4ResponseDataLength);
				Assert::AreEqual((int)dataLength, target->em4ResponseData->Length);
				
				Assert::AreEqual((unsigned char)0x01, target->em4ResponseAckNackByte);
				Assert::AreEqual((unsigned char)0x08, target->em4ResponseLengthByte);
				Assert::AreEqual((unsigned char)0x03, target->em4ResponseSequenceNumber);
				//check the data bits
				Assert::AreEqual((unsigned char)0x04, target->em4ResponseData[0]);
				Assert::AreEqual((unsigned char)0x05, target->em4ResponseData[1]);
				Assert::AreEqual((unsigned char)0x06, target->em4ResponseData[2]);

				Assert::AreEqual((unsigned short)0x0709, target->em4StatusFlag);
				Assert::AreEqual((unsigned char)0x0A, target->em4ResponseCRCByte);
			}






			/// <summary>
			///A test for ~EM4DataCapturePacket
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DestructorEM4DataCapturePacketTestWithData()
			{
				unsigned int  dataLength = 5 ; 
				EM4DataCapturePacket_Accessor^  target = (gcnew EM4DataCapturePacket_Accessor(dataLength)); 
				Assert::IsNotNull(target->em4Response);
				Assert::IsNotNull(target->em4ResponseData);
				delete target;
				Assert::IsNull(target->em4Response);
				Assert::IsNull(target->em4ResponseData);
			}

			/// <summary>
			///A test for ~EM4DataCapturePacket
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DestructorEM4DataCapturePacketTestZeroData()
			{
				unsigned int  dataLength = 0 ; 
				EM4DataCapturePacket_Accessor^  target = (gcnew EM4DataCapturePacket_Accessor(dataLength)); // TODO: Initialize to an appropriate value
				Assert::IsNotNull(target->em4Response);
				Assert::IsNull(target->em4ResponseData);
				delete target;
				Assert::IsNull(target->em4Response);
				Assert::IsNull(target->em4ResponseData);
			}

			/// <summary>
			///A test for EM4DataCapturePacket Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void EM4DataCapturePacketConstructorTest()
			{
				unsigned int  dataLength = 5 ; 
				EM4DataCapturePacket_Accessor^  target = (gcnew EM4DataCapturePacket_Accessor(dataLength));
				Assert::AreEqual(11, target->em4Response->Length );
				Assert::IsNotNull(target->em4ResponseData);
				Assert::AreEqual((int)dataLength, target->em4ResponseData->Length);
				Assert::AreEqual((unsigned char)0x00, target->em4ResponseSequenceNumber);
				Assert::AreEqual((unsigned short)0x00, target->em4StatusFlag);
				Assert::AreEqual((unsigned char)0x00, target->em4ResponseCRCByte);
				Assert::AreEqual((unsigned char)0x00, target->em4ResponseAckNackByte);
				Assert::AreEqual((unsigned char)0x00, target->em4ResponseLengthByte);
				
			}

			/// <summary>
			///A test for EM4DataCapturePacket Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void EM4DataCapturePacketConstructorTestZeroData()
			{
				unsigned int dataLength = 0 ; 
				EM4DataCapturePacket_Accessor^  target = (gcnew EM4DataCapturePacket_Accessor(dataLength));
				Assert::AreEqual(6, target->em4Response->Length );
				Assert::AreEqual((unsigned int)0, target->em4ResponseDataLength);
				Assert::IsNull(target->em4ResponseData);
				Assert::AreEqual(dataLength, target->em4ResponseDataLength);
				Assert::AreEqual((unsigned char)0x00, target->em4ResponseSequenceNumber);
				Assert::AreEqual((unsigned short)0x00, target->em4StatusFlag);
				Assert::AreEqual((unsigned char)0x00, target->em4ResponseCRCByte);
				Assert::AreEqual((unsigned char)0x00, target->em4ResponseAckNackByte);
				Assert::AreEqual((unsigned char)0x00, target->em4ResponseLengthByte);
			}
			
		
		
			//This one will test for data
			/// <summary>
			///A test for BreakResponseDataPart
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void BreakResponseDataPartTest()
		{
			//PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			
			EM4DataCapturePacket_Accessor^  target = (gcnew EM4DataCapturePacket_Accessor(0)); // Packet with zero data
			bool expected = true; 
			bool actual;
			target->em4ResponsePacketLength = 5; //externally set for a zero data packet
			//fill with dummy data to test breakup
			target->em4Response = gcnew array <unsigned char> {0x01, 0x08, 0x30, 0x04, 0x05, 0xBC};
				
			actual = target->BreakResponseDataPart();
			Assert::AreEqual(expected, actual);
			Assert::IsNull(target->em4ResponseData); 
		}

		//This one will test for zero data
		/// <summary>
			///A test for BreakResponseDataPart
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void BreakResponseDataPartTest2()
		{
			EM4DataCapturePacket_Accessor^  target = (gcnew EM4DataCapturePacket_Accessor(0)); // Packet with zero data
			bool expected = false; 
			bool actual;
			target->em4ResponsePacketLength = 4; //deliberately set toless than expected length
			//fill with dummy data to test breakup
			target->em4Response = gcnew array <unsigned char> {0x01, 0x08, 0x30, 0x04, 0xE3};
				
			actual = target->BreakResponseDataPart();
			Assert::AreEqual(expected, actual);
			Assert::IsNull(target->em4ResponseData); 
		}

		//This one will test for insufficient size
		/// <summary>
			///A test for BreakResponseDataPart
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void BreakResponseDataPartTest3()
		{
			EM4DataCapturePacket_Accessor^  target = (gcnew EM4DataCapturePacket_Accessor(3)); //3 data bits
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
