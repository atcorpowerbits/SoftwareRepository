
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting;
namespace TestDal {
    using namespace System;
    ref class DalBinaryConversionsTest;
    
    
    /// <summary>
///This is a test class for DalBinaryConversionsTest and is intended
///to contain all DalBinaryConversionsTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalBinaryConversionsTest
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
			///A test for ConvertBytesToString
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ConvertBytesToStringTest()
			{
				cli::array< unsigned char >^  inputArray = gcnew array<unsigned char> {0x01, 0x02, 0x03, 0x0A}; 
				String^  expected = "01 02 03 0A "; 			//There is always a space after each character
				String^  actual;
				actual = DalBinaryConversions_Accessor::ConvertBytesToString(inputArray);
				Assert::AreEqual(expected, actual);
			}


			/// <summary>
			///A test for ConvertBytesToString
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ConvertBytesToStringNullArrayTest()
			{
				cli::array< unsigned char >^  inputArray = nullptr; 
				String^  expected = String::Empty; 			//There is always a space after each character
				String^  actual;
				actual = DalBinaryConversions_Accessor::ConvertBytesToString(inputArray);
				Assert::AreEqual(expected, actual);
			}


			//We dont need the constructor since all methods are static
			//The constructor has only been added to make it private. It doesnt do anything.
			/*/// <summary>
			///A test for DalBinaryConversions Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalBinaryConversionsConstructorTest()
			{
				DalBinaryConversions_Accessor^  target = (gcnew DalBinaryConversions_Accessor());
				Assert::Inconclusive(L"TODO: Implement code to verify target");
			}*/

			/// <summary>
			///A test for ConvertAlarmType
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ConvertAlarmType_DalAlarmFlagBitPosition_Test()
			{
				DalAlarmFlagBitPosition  alarmType = DalAlarmFlagBitPosition::HighDeflationRate ; 
				DalAlarmSource expected = DalAlarmSource::HighDeflationRate ; // should have same name as the source but the result is of a different enum
				DalAlarmSource actual;
				actual = DalBinaryConversions_Accessor::ConvertAlarmType(alarmType);
				Assert::AreEqual(expected, actual);
				
			}
			/// <summary>
			///A test for ConvertAlarmType
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ConvertAlarmType_DalAlarmSupplyRailFlag_Test()
			{
				DalAlarmSupplyRailFlag  alarmType = DalAlarmSupplyRailFlag::Source5VD ; //Taken at random
				DalAlarmSource expected = DalAlarmSource::Source5VD ; // should have same name
				DalAlarmSource actual;
				actual = DalBinaryConversions_Accessor::ConvertAlarmType(alarmType);
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for ConvertAlarmType
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ConvertAlarmType_DalAlarmSupplyRailFlag2_Test()
			{
				DalAlarmSupplyRailFlag  alarmType = DalAlarmSupplyRailFlag::SupplyRailNoAlarm ; //Taken at random
				DalAlarmSource expected = DalAlarmSource::SupplyRailNoAlarm ; // should have same name
				DalAlarmSource actual;
				actual = DalBinaryConversions_Accessor::ConvertAlarmType(alarmType);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for ConvertAlarmType
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ConvertAlarmType_DalErrorAlarmStatusFlag_Test()
			{				
				DalErrorAlarmStatusFlag  alarmType = DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket ; 
				DalAlarmSource expected = DalAlarmSource::DataCaptureErrorInvalidPacket; 
				DalAlarmSource actual;
				actual = DalBinaryConversions_Accessor::ConvertAlarmType(alarmType);
				Assert::AreEqual(expected, actual);
				
			}

			/// <summary>
			///A test for ConvertAlarmType
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ConvertAlarmType_String_Test()
			{				
				String^ alarmName = "RecoverableStatus" ;
				DalAlarmSource expected = DalAlarmSource::RecoverableStatus; 
				DalAlarmSource actual;
				actual = DalBinaryConversions_Accessor::ConvertAlarmType(alarmName);
				Assert::AreEqual(expected, actual);
				
			}


			/// <summary>
			///A test for ConvertAlarmType
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ConvertAlarmType_String_Neg_Test()
			{				
				String^ alarmName = "Garbage" ;
				DalAlarmSource expected = DalAlarmSource::NoAlarmDefined; 
				DalAlarmSource actual;
				actual = DalBinaryConversions_Accessor::ConvertAlarmType(alarmName);
				Assert::AreEqual(expected, actual);
				
			}
			/// <summary>
			///A test for GenerateModulo256Checksum
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void GenerateModulo256ChecksumTest()
		{
			DalBinaryConversions_Accessor^  target = (gcnew DalBinaryConversions_Accessor()); 
			//create an array with set inflate command9180 mmhg). deliberatetly do not make it of leegth 5
			cli::array< unsigned char >^  sourcearray = gcnew array<unsigned char> (4) {0x3a, 0x17, 0xb4, 0x00}; 
			int length = 4; 
			unsigned char expected = 0xFB; // expected value as per doc
			unsigned char actual;
			actual = target->GenerateModulo256Checksum(sourcearray, length);
			Assert::AreEqual(expected, actual);
		}

		/// <summary>
		///A test for GenerateModulo256Checksum
		///same as the previous one but we will add one more empty byte
		//the length will remain the same 
		//This is a typical scenario where we add an empty byte for Checksum
		public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void GenerateModulo256Checksum_WithExtraByte_Test()
		{
			DalBinaryConversions_Accessor^  target = (gcnew DalBinaryConversions_Accessor()); 
			//create an array with set inflate command180 mmhg). make it of leegth 5 with the 5th bit reserved for Checksum
			cli::array< unsigned char >^  sourcearray = gcnew array<unsigned char> (5) {0x3a, 0x17, 0xb4, 0x00}; 
			int length = 4; //this will be the actual length needed to be processed
			unsigned char expected = 0xFB; // expected value as per doc
			unsigned char actual;
			actual = target->GenerateModulo256Checksum(sourcearray, length);
			Assert::AreEqual(expected, actual);
		}


		/// <summary>
			///A test for GenerateModulo256Checksum
			///should throw an expcetion for an illegal parameter
		public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void GenerateModulo256Checksum_ThrowsException_ForNullArray_Test()
		{
			DalBinaryConversions_Accessor^  target = (gcnew DalBinaryConversions_Accessor()); 
			cli::array< unsigned char >^  sourcearray = nullptr; // Deliberately null so that it can throw excpetion
			int length = 8; //Any valid integer. doesnt matter
			unsigned char expected = 0; // Doesnt matter. We are looking for exception
			unsigned char actual;
			bool excptionThrown = false;

			try
			{
				actual = target->GenerateModulo256Checksum(sourcearray, length);
				Assert::AreEqual(expected, actual);
			}
			catch(ScorException ^ )
			{
				excptionThrown = true;
			}

			Assert::IsTrue(excptionThrown);
		}

		/// <summary>
			///A test for GenerateModulo256Checksum
			///should throw an expcetion for an illegal parameter
		public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void GenerateModulo256Checksum_ThrowsException_ForEmptyArray_Test()
		{
			DalBinaryConversions_Accessor^  target = (gcnew DalBinaryConversions_Accessor()); 
			cli::array< unsigned char >^  sourcearray = gcnew array<unsigned char> (0); // create an array of zero size
			int length = 8; //Any valid integer. doesnt matter
			unsigned char expected = 0; // Doesnt matter. We are looking for exception
			unsigned char actual;
			bool excptionThrown = false;

			try
			{
				actual = target->GenerateModulo256Checksum(sourcearray, length);
				Assert::AreEqual(expected, actual);
			}
			catch(ScorException ^ )
			{
				excptionThrown = true;
			}

			Assert::IsTrue(excptionThrown);
		}

		/// <summary>
			///A test for GenerateModulo256Checksum
			///should throw an expcetion for an illegal parameter
		public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void GenerateModulo256Checksum_ThrowsException_ForZeroLength_Test()
		{
			DalBinaryConversions_Accessor^  target = (gcnew DalBinaryConversions_Accessor()); 
			cli::array< unsigned char >^  sourcearray = gcnew array<unsigned char> {0x01,0x02}; // Any valid non-zero array
			int length = 0; //Any valid integer. doesnt matter
			unsigned char expected = 0; // Doesnt matter. We are looking for exception
			unsigned char actual;
			bool excptionThrown = false;

			try
			{
				actual = target->GenerateModulo256Checksum(sourcearray, length);
				Assert::AreEqual(expected, actual);
			}
			catch(ScorException ^ )
			{
				excptionThrown = true;
			}

			Assert::IsTrue(excptionThrown);
		}


		/// <summary>
		///A test for TranslateTwoBytesLsbFirst
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void TranslateTwoBytesLsbFirstTest()
		{
			cli::array< unsigned char >^  sourceArray = gcnew array<unsigned char> {0x02, 0x01}; // should resolve to 258
			int startPostion = 0;
			short expected = 258; //for the specified byte
			short actual;
			actual = DalBinaryConversions_Accessor::TranslateTwoBytesLsbFirst(sourceArray, startPostion);
			Assert::AreEqual(expected, actual);
			
		}

	
		/// <summary>
		///A test for TranslateTwoBytesLsbFirst
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void TranslateTwoBytesLsbFirst_2_Test()
		{
			cli::array< unsigned char >^  sourceArray = gcnew array<unsigned char> {0x8E, 0x00}; // should resolve to 258
			int startPostion = 0;
			short expected = 142; //for the specified byte
			short actual;
			actual = DalBinaryConversions_Accessor::TranslateTwoBytesLsbFirst(sourceArray, startPostion);
			Assert::AreEqual(expected, actual);
			
		}
};
}
namespace TestDal {
    
}
