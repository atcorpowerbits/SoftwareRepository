﻿
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalCRC8CalculatorTest;
    
    
    /// <summary>
///This is a test class for DalCRC8CalculatorTest and is intended
///to contain all DalCRC8CalculatorTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalCRC8CalculatorTest
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
			///A test for DalDalCRC8Calculator Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalCRC8CalculatorConstructorTest()
			{
				DalCRC8Calculator_Accessor^  target = (gcnew DalCRC8Calculator_Accessor());
				Assert::IsNotNull(target->crc8Table);
			}


			/// This test causes MSTest to abort so it has been  commented out
			///A test for DalDalCRC8Calculator Constructor
			///</summary>
			/*public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CRC8forNextByteTest()
			{
				DalCRC8Calculator_Accessor^  target = (gcnew DalCRC8Calculator_Accessor());
				unsigned char nextByte = 0x00;
				unsigned char currentCrc  = 0x00;
				target->Crc8forNextByte(&currentCrc, 0x00);
				Assert::AreEqual((unsigned char)0x07, currentCrc);

				currentCrc  = 0x00;
				target->Crc8forNextByte(&currentCrc, 0x02);
				Assert::AreEqual((unsigned char)0x0E, currentCrc);

			}*/


			//Deepak: This test causes the Test framework to crash and prevents all tests from running
			/// All attempts to get this to work have failed.
			///A test for DalDalCRC8Calculator Constructor
			///</summary>
	/*public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ComputeCrc8ForArrayTest()
			{
				try
				{
					DalCRC8Calculator_Accessor^  target = (gcnew DalCRC8Calculator_Accessor());
					array<unsigned char>^ testArray = gcnew array<unsigned char> (3) {0x10, 0x1F, 0xFF };
					unsigned char expected, actual;
					expected = 0xc5;
					actual = 0x00;
					 target->ComputeCrc8ForArray(testArray, 3 ,&actual );
					 Assert::AreEqual(expected, actual);
				}
				catch(Exception^ excepObj)
				{
					Assert::Fail("Exception raised: " + excepObj->Message );
				}
			}*/
	};
}
namespace TestDal {
    
}