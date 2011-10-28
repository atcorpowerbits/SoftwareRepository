
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace System::IO;

namespace TestDal {
    using namespace System;
    ref class DalEM4NibpToHostPacketTest;
    
    
    /// <summary>
///This is a test class for DalEM4NibpToHostPacketTest and is intended
///to contain all DalEM4NibpToHostPacketTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalEM4NibpToHostPacketTest
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
			///A test for DalEM4NibpToHostPacket Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalEM4NibpToHostPacketConstructorTest1()
			{
				//Valid NIBP Packet embeded in a host command
				cli::array< unsigned char >^  byteArray = gcnew array<unsigned char> {0x93, 0x09, 0x05, 0x3E, 0x04, 0x4F, 0x6F, 0x00, 0x01, 0x44 }; 

				array<unsigned char>^ nibpDataPartExpected = gcnew array<unsigned char> {0x3E, 0x04, 0x4F, 0x6F};
				//array< unsigned char >^  nibpDataPartActual; //needed commented due to warning

				DalEM4NibpToHostPacket_Accessor^  target = (gcnew DalEM4NibpToHostPacket_Accessor(byteArray));
				Assert::IsNotNull(target);


				//validate the various data parts
				Assert::AreEqual(byteArray->Length , target->em4Response->Length );
				Assert::IsNotNull(target->em4ResponseData);


				Assert::AreEqual(4, target->em4ResponseData->Length); //this particular data packet is of length 4
				Assert::AreEqual((unsigned char)0x05, target->em4ResponseSequenceNumber);
				Assert::AreEqual((unsigned short)0x0001, target->em4StatusFlag);
				Assert::AreEqual((unsigned char)0x44 , target->em4ResponseCRCByte);
				Assert::AreEqual((unsigned char)0x93, target->em4ResponseAckNackByte);
				Assert::AreEqual((unsigned char)0x09, target->em4ResponseLengthByte);

				//validate the entire Em4 host pacet
				//check the entire array
				for (int i = 0; i < byteArray->Length; i++)
				{
					Assert::AreEqual(byteArray[i], target->em4Response[i]);
				}

				//now validate the nibpDataPart
				for (int i = 0; i < nibpDataPartExpected->Length; i++)
				{
					Assert::AreEqual(nibpDataPartExpected[i], target->em4ResponseData[i]);
				}

			}
			/// <summary>
			///A test for DalEM4NibpToHostPacket Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalEM4NibpToHostPacketConstructor_NoParameters_Test()
			{
				DalEM4NibpToHostPacket_Accessor^  target = (gcnew DalEM4NibpToHostPacket_Accessor());
				Assert::IsNotNull(target);
			}
			/// <summary>
			///A test for ValidateResponseCRC
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidateResponseCRCTest()
		{
			//Valid array and CRC
			cli::array< unsigned char >^  byteArray = gcnew array<unsigned char> {0x93, 0x09, 0x00, 0x3E, 0x04, 0x4F, 0x6F, 0x00, 0x01, 0xEE  }; 

			DalEM4NibpToHostPacket_Accessor^  target = (gcnew DalEM4NibpToHostPacket_Accessor(byteArray)); 

			
			bool expected = true; // true espected
			bool actual;
			actual = target->ValidateResponseCRC();
			Assert::AreEqual(expected, actual);
		}

		/// <summary>
		///A Negative test for ValidateResponseCRC
		///should ffail
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidateResponseCRC_Negative_Test()
		{
			//Modified CRC from 0xEE to 0xD9(incorrect value)
			cli::array< unsigned char >^  byteArray = gcnew array<unsigned char> {0x93, 0x09, 0x00, 0x3E, 0x04, 0x4F, 0x6F, 0x00, 0x01, 0xD9 }; 

			DalEM4NibpToHostPacket_Accessor^  target = (gcnew DalEM4NibpToHostPacket_Accessor(byteArray)); 

			
			bool expected = false; // should fail
			bool actual;
			actual = target->ValidateResponseCRC();
			Assert::AreEqual(expected, actual);
		}


		/// <summary>
		///A test for ValidatePacket
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidatePacketTest()
		{
			//Valid array and CRC
			cli::array< unsigned char >^  byteArray = gcnew array<unsigned char> {0x93, 0x09, 0x00, 0x3E, 0x04, 0x4F, 0x6F, 0x00, 0x01, 0xEE  }; 

			DalEM4NibpToHostPacket_Accessor^  target = (gcnew DalEM4NibpToHostPacket_Accessor(byteArray)); 
			DalReturnValue expected = DalReturnValue::Success ; //Success Expected
			DalReturnValue actual;
			actual = target->ValidatePacket();
			Assert::AreEqual(expected, actual);
			
		}


		/// <summary>
		///A test for ValidatePacket
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidatePacket_Negative_BadCRC_Test()
		{
			//Bad CRC
			cli::array< unsigned char >^  byteArray = gcnew array<unsigned char> {0x93, 0x09, 0x00, 0x3E, 0x04, 0x4F, 0x6F, 0x00, 0x01, 0xD9}; 

			DalEM4NibpToHostPacket_Accessor^  target = (gcnew DalEM4NibpToHostPacket_Accessor(byteArray)); 
			DalReturnValue expected = DalReturnValue::Failure ; //Failure Expected
			DalReturnValue actual;
			actual = target->ValidatePacket();
			Assert::AreEqual(expected, actual);
			
		}

			/// <summary>
		///A test for ValidatePacket
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidatePacket_Negative_CodeIncorrect_Test()
		{
			//Bad CRC
			cli::array< unsigned char >^  byteArray = gcnew array<unsigned char> {0x14, 0x09, 0x00, 0x3E, 0x04, 0x4F, 0x6F, 0x00, 0x01, 0xDA}; 

			DalEM4NibpToHostPacket_Accessor^  target = (gcnew DalEM4NibpToHostPacket_Accessor(byteArray)); 
			DalReturnValue expected = DalReturnValue::Failure ; //Failure Expected
			DalReturnValue actual;
			actual = target->ValidatePacket();
			Assert::AreEqual(expected, actual);
			
		}

		/// <summary>
		///A test for ValidatePacket
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidatePacket_neg_IncorrectLength_Test()
		{
			//one byte less
			cli::array< unsigned char >^  byteArray = gcnew array<unsigned char> {0x93, 0x09, 0x00, 0x3E, 0x04, 0x4F, 0x6F, 0x00, 0x01 }; 

			DalEM4NibpToHostPacket_Accessor^  target = (gcnew DalEM4NibpToHostPacket_Accessor(byteArray)); 
			DalReturnValue expected = DalReturnValue::Failure ; //Success Expected
			DalReturnValue actual;
			actual = target->ValidatePacket();
			Assert::AreEqual(expected, actual);
			
		}
};
}
namespace TestDal {
    
}
