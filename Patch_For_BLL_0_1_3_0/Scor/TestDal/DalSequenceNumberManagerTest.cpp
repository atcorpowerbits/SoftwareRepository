
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace System::IO;
namespace TestDal {
    using namespace System;
    ref class DalSequenceNumberManagerTest;
    
    
    /// <summary>
///This is a test class for DalSequenceNumberManagerTest and is intended
///to contain all DalSequenceNumberManagerTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalSequenceNumberManagerTest
	{
		private: String^ _currDir;

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

			void SetPath()
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
				_currDir = Directory::GetCurrentDirectory(); 
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
			/// Test for single value
			///A test for NextCommandSequenceNumber
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void NextCommandSequenceNumberTest()
			{
				static unsigned char actual;
				//DalSequenceNumberManager_Accessor ^target;
				actual = DalSequenceNumberManager_Accessor::NextCommandSequenceNumber;
				//actual =(target->NextCommandSequenceNumber);
				Assert::AreEqual((unsigned char)0, actual);
			}

			/// Test for entire range in a loop. 
			//This test will NOT have a capture resurved number
			///A test for NextCommandSequenceNumber
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void NextCommandSequenceNumberLoopTest()
			{
				unsigned char actual;

				//Some other test case may have reserved the number. Free it befor the test
				DalSequenceNumberManager_Accessor::ReleaseReservedCommandNumber();
				//reset the first number
				DalSequenceNumberManager_Accessor::ResetCommandSequenceNumber();

				//run it for more than 0-F to check for valdity
				for (int i = 0; i < 18; i++)
				{
					actual = DalSequenceNumberManager_Accessor::NextCommandSequenceNumber;
					Assert::AreEqual((unsigned char)(i%16), actual);
				}
			}

			/// Test for entire range in a loop. 
			//This test WILL a capture resurved number
			///A test for NextCommandSequenceNumber
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void NextCommandSequenceNumberLoopTestWithCaptureNumberReserved()
			{
				unsigned char actual;
				unsigned char captureReserved = 0x07; //picked a number at random

				//clear the number which may be modified by previous tests
				DalSequenceNumberManager_Accessor::_nextCommandSequenceNumber = 0x00; 
				
				//First set a number as capture reserved
				DalSequenceNumberManager_Accessor::ReserveCommandNumberDuringStreaming(captureReserved);

				//pre verification:
				Assert::IsTrue(DalSequenceNumberManager_Accessor::reserveSequenceNumberForCapture );
				Assert::AreEqual(captureReserved, DalSequenceNumberManager_Accessor::reservedCommandSequenceNumber);

				//run it for more than 0-F to check for valdity
				for (int i = 0; i < 19; i++)
				{
					actual = DalSequenceNumberManager_Accessor::NextCommandSequenceNumber;

					if( (unsigned char)(i%16) == captureReserved)
					{
						Assert::AreNotEqual(captureReserved, actual); 
						//since the number is locked it should not be returned
						//the next number will be returned
						
						//test that the number is really the next before goign ahead
						Assert::AreEqual((unsigned char)((i+1)%16), actual); 

						i++; //increment the number to test

					}
					Assert::AreEqual((unsigned char)(i%16), actual);
				
				}

				//now we will check if the number has been released or not
				DalSequenceNumberManager_Accessor::ReleaseReservedCommandNumber();
				
				//for testing we will loop from zero again and check all numbers/
				//but first we will reset the number to ensure that we pass the loop
				DalSequenceNumberManager_Accessor::ResetCommandSequenceNumber(); 

				for (int i = 0; i < 18; i++)
				{
					//this will pass throug all the numbers
					actual = DalSequenceNumberManager_Accessor::NextCommandSequenceNumber;
					Assert::AreEqual((unsigned char)(i%16), actual);

					//for sureity we will check that the last reserved number was freed.
					if( (unsigned char)(i%16) == captureReserved)
					{
						//captureReserved was previoisly locked it should not be locked any more
						Assert::AreEqual(captureReserved, actual); 

					}
				}
			}

			/// Test for entire range in a loop. 
			//This test WILL a capture resurved number
			///A test for NextCommandSequenceNumber
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void NextCommandSequenceNumberTestWithRolloverCaptureNumberReserved()
			{
				unsigned char actual;
				unsigned char captureReserved = 0x0F; //borderline

				//clear the number which may be modified by previous tests
				DalSequenceNumberManager_Accessor::_nextCommandSequenceNumber = captureReserved;

				
				//First set a number as capture reserved
				DalSequenceNumberManager_Accessor::ReserveCommandNumberDuringStreaming(captureReserved);

				//pre verification:
				Assert::IsTrue(DalSequenceNumberManager_Accessor::reserveSequenceNumberForCapture );
				Assert::AreEqual(captureReserved, DalSequenceNumberManager_Accessor::reservedCommandSequenceNumber);

				actual = DalSequenceNumberManager_Accessor::NextCommandSequenceNumber;
				Assert::AreEqual((unsigned char)0x00, actual);
			}


			/// <summary>
			///A test for CheckStreamingSequenceNumber
			///A correct values and verify that the method does not fail for correct data
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckStreamingSequenceNumberSinglePositiveTest()
			{
				unsigned char streamingPacketSequenceNumber = 0; // the streaming starts from zero so first expected value is zero
				bool expected = true; // Method should pass
				bool actual;

				//pre test verification
				Assert::AreEqual(DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber , (unsigned char)0x00);
				//now call the method
				actual = DalSequenceNumberManager_Accessor::CheckStreamingSequenceNumber(streamingPacketSequenceNumber);
				Assert::AreEqual(expected, actual);

				//post test verification
				Assert::AreEqual(DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber , (unsigned char)0x01); //number should have incrementd
			}

			/// <summary>
			///A test for CheckStreamingSequenceNumber
			///A correct values and verify that the method does not fail for correct data
			//The _nextStreamingPacketSequnceNumber should be 0x0F and after recieving a valid entry shoudl rollover to 0x00
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckStreamingSequenceNumberSinglePositiveTestwithRollover()
			{
				unsigned char borderValue = 0x0F;
				unsigned char streamingPacketSequenceNumber = borderValue; // after getting ox0F it shoudl roll over
				bool expected = true; // Method should pass
				bool actual;

				//set the border condition
				DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber = borderValue; 
				
				//pre test verification
				Assert::AreEqual(DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber , borderValue);
				
				//now call the method
				actual = DalSequenceNumberManager_Accessor::CheckStreamingSequenceNumber(borderValue); //pass the same value as a parameter they should match
				Assert::AreEqual(expected, actual);

				//post test verification
				Assert::AreEqual(DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber , (unsigned char)0x00); //number should have rolled to 0x00
			}

			/// <summary>
			///A test for CheckStreamingSequenceNumber
			///A correct values and verify that the method does not fail for correct data
			//The _nextStreamingPacketSequnceNumber should be 0x0F and But it recives a 0x00 and should fail
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckStreamingSequenceNumberSingleNegativeTestwithRollover()
			{
				unsigned char borderValue = 0x0F;
				unsigned char streamingPacketSequenceNumber = 0x00; // skip one nuumber, the test should also fail for rollover with missing packet
				bool expected = false; // Method should FAIL
				bool actual;

				//set the border condition
				DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber = borderValue; 
				
				//pre test verification
				Assert::AreEqual(borderValue, DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber);
				
				//now call the method
				actual = DalSequenceNumberManager_Accessor::CheckStreamingSequenceNumber(streamingPacketSequenceNumber); //pass the invalid value
				Assert::AreEqual(expected, actual);

				//post test verification
				Assert::AreEqual(borderValue, DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber); //number should have rolled to 0x00

			}

			/// <summary>
			///A test for CheckStreamingSequenceNumber
			///Negative test: will skip a value and verify that the method fails 
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckStreamingSequenceNumberSingleNegativeTest()
			{
				unsigned char streamingPacketSequenceNumber =1; // the streaming starts from zero so first expected value is zero
				bool expected = false; // Method should fail
				bool actual;

				DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber = DalSequenceNumberManager_Accessor::_packetSequenceMinValue;

				//pre test verification
				Assert::AreEqual((unsigned char)0x00, DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber );

				actual = DalSequenceNumberManager_Accessor::CheckStreamingSequenceNumber(streamingPacketSequenceNumber);
				Assert::AreEqual(expected, actual);

				//post test verification
				Assert::AreEqual((unsigned char)0x00, DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber); //number will remain the same
			}

			/// <summary>
			///A test for CheckStreamingSequenceNumber
			///Poritive test: will pass all currect values in a loop and verify that the method does not fail for correct data
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckStreamingSequenceNumberLoopPositiveTest()
			{
				unsigned char streamingPacketSequenceNumber = 0; // the streaming starts from zero so first expected value is zero
				bool expected = true; // Method should pass
				bool actual;
				
				//reset before testing
				DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber = DalSequenceNumberManager_Accessor::_packetSequenceMinValue;

				//pre test verification
				Assert::AreEqual((unsigned char)0x00, DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber );
				
				//loop though 0 to F +1 and verify that the data is accepted
				for (unsigned char i = 0; i < 18; i++)
				{
					actual = DalSequenceNumberManager_Accessor::CheckStreamingSequenceNumber(i%16);
					Assert::AreEqual(expected, actual);
				}
			}

			/// <summary>
			///A test for CheckStreamingSequenceNumber
			///Negative test: will pass values in a loop with ONE MISSING number and verify that the method returns false
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckStreamingSequenceNumberLoopNegativeTest()
			{
				bool expected = true; // Method should pass for all values except 1 missing value
				bool actual;
				unsigned char missingNumber = 0x0A;

				//reset before testing
				DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber = DalSequenceNumberManager_Accessor::_packetSequenceMinValue;

				//pre test verification
				Assert::AreEqual((unsigned char)0x00, DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber );
				
				
				//loop though 0 to F +1 and verify that the data is accepted
				for (unsigned char i = 0; i < 18; i++)
				{
					if ( i == missingNumber ) //the value under test
					{
						i++; //skip to the next number and thgen test
					}
					actual = DalSequenceNumberManager_Accessor::CheckStreamingSequenceNumber(i%16);

					if ( i == missingNumber + 1) //numbewr will have rolled to next so we cannot validate on same i value
					{
						

						Assert::IsFalse(actual); //This one should be FALSE

						//post test verification
						Assert::AreEqual(missingNumber, DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber ); 

						return;// no need to run the test any more
					}
					else
					{
						//True for any other value
						Assert::AreEqual(expected, actual);
					}
				}
			}



			/// <summary>
			///A test for ValidateCommandResponseSequenceNumber
			///Test with eqal values
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ValidateCommandResponseSequenceNumberPositiveTest()
			{
				unsigned char commandSequenceNumber = 0x0D; 
				unsigned char responseSequenceNumber = 0x0D; //same value 
				bool expected = true; // true expected here. data valid
				bool actual;
				actual = DalSequenceNumberManager_Accessor::ValidateCommandResponseSequenceNumber(commandSequenceNumber, responseSequenceNumber);
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for ValidateCommandResponseSequenceNumber
			///Test with unequal values
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ValidateCommandResponseSequenceNumbernegativeTest()
			{
				unsigned char commandSequenceNumber = 0x0D; 
				unsigned char responseSequenceNumber = 0x0C; //different value
				bool expected = false; //shoudl fail
				bool actual;
				actual = DalSequenceNumberManager_Accessor::ValidateCommandResponseSequenceNumber(commandSequenceNumber, responseSequenceNumber);
				Assert::AreEqual(expected, actual);
			}


			/// <summary>
			///A test for ResetStreamingSequenceNumber
			///should reset the number to the min value
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ResetStreamingSequenceNumberTest()
			{
				//first set the sequence number to some non-MIN value
				DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber = 0x09;

				//pre verification
				Assert::AreNotEqual(DalSequenceNumberManager_Accessor::_packetSequenceMinValue, DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber);
				DalSequenceNumberManager_Accessor::ResetStreamingSequenceNumber();
				
				//now the value should be rest
				Assert::AreEqual(DalSequenceNumberManager_Accessor::_packetSequenceMinValue, DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber);
			}


			/// <summary>
			///A test for ResetCommandSequenceNumber
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ResetCommandSequenceNumberTest()
			{
				//first set the sequence number to some non-MIN value
				DalSequenceNumberManager_Accessor::_nextCommandSequenceNumber = 0x09;

				//pre verification
				Assert::AreNotEqual(DalSequenceNumberManager_Accessor::_packetSequenceMinValue, DalSequenceNumberManager_Accessor::_nextCommandSequenceNumber);
				
				DalSequenceNumberManager_Accessor::ResetCommandSequenceNumber();

				//now the value should be reset
				Assert::AreEqual(DalSequenceNumberManager_Accessor::_packetSequenceMinValue, DalSequenceNumberManager_Accessor::_nextCommandSequenceNumber);
		
			}


			/// <summary>
			///A test for ReserveCommandNumberDuringStreaming
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ReserveCommandNumberDuringStreamingTest()
			{
				unsigned char captureCommandSequenceNumber = 0x05; 

				DalSequenceNumberManager_Accessor::ReleaseReservedCommandNumber();//free the value before testing it again
				
				Assert::IsFalse(DalSequenceNumberManager_Accessor::reserveSequenceNumberForCapture); //pre verification
				Assert::AreEqual((unsigned char)0xFF, DalSequenceNumberManager_Accessor::reservedCommandSequenceNumber);

				//call the method under test
				DalSequenceNumberManager_Accessor::ReserveCommandNumberDuringStreaming(captureCommandSequenceNumber);
				
				Assert::AreEqual(captureCommandSequenceNumber, DalSequenceNumberManager_Accessor::reservedCommandSequenceNumber);
				Assert::IsTrue(DalSequenceNumberManager_Accessor::reserveSequenceNumberForCapture);
			}

			/// <summary>
			///A test for ReleaseReservedCommandNumber
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ReleaseReservedCommandNumberTest()
			{
				DalSequenceNumberManager_Accessor::reservedCommandSequenceNumber = 0x05;
				DalSequenceNumberManager_Accessor::reserveSequenceNumberForCapture = true;
				Assert::IsTrue(DalSequenceNumberManager_Accessor::reserveSequenceNumberForCapture); //should be true since number is reserved
				
				//now call the method under test
				DalSequenceNumberManager_Accessor::ReleaseReservedCommandNumber();

				Assert::IsFalse(DalSequenceNumberManager_Accessor::reserveSequenceNumberForCapture); //must be false now
				Assert::AreEqual((unsigned char)0xFF, DalSequenceNumberManager_Accessor::reservedCommandSequenceNumber);
			}

			/// <summary>
			///A test for DalSequenceNumberManager Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalSequenceNumberManagerConstructorTest()
			{
				DalSequenceNumberManager_Accessor^  target = (gcnew DalSequenceNumberManager_Accessor());
				Assert::AreEqual((unsigned char)0x00,target->_nextCommandSequenceNumber);
				Assert::AreEqual((unsigned char)0xFF, target->reservedCommandSequenceNumber);
				Assert::AreEqual((unsigned char)0x00,target->_nextStreamingPacketSequnceNumber );
				Assert::IsFalse(target->reserveSequenceNumberForCapture);
			}
			
			/// <summary>
			///A test for ExtractStreamingSequenceNumber
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ExtractStreamingSequenceNumberTest()
		{
			unsigned char streamingPacketSequenceNumber = 0xF8; 
			unsigned char expected = 0x0F; // Number should be shifted
			unsigned char actual;
			actual = DalSequenceNumberManager_Accessor::ExtractStreamingSequenceNumber(streamingPacketSequenceNumber);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for ValidateStreamingSequenceNumber
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ValidateStreamingSequenceNumberSingleTest()
		{
			unsigned char streamingPacketSequenceNumber = 0x4C; // 4 is the sequence number C is for capture command(any number will do)
			bool expected = true; 
			bool actual;

			//first set a sequnce number that is expected
			DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber =0x04;

			actual = DalSequenceNumberManager_Accessor::ValidateStreamingSequenceNumber(streamingPacketSequenceNumber);
			Assert::AreEqual(expected, actual);

			//post test verification
			Assert::AreEqual(DalSequenceNumberManager_Accessor::_nextStreamingPacketSequnceNumber , (unsigned char)0x05); //number should have incrementd
		}
};
}
namespace TestDal {
    
}
