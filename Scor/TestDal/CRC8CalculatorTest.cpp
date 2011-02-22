
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class CRC8CalculatorTest;
    
    
    /// <summary>
///This is a test class for CRC8CalculatorTest and is intended
///to contain all CRC8CalculatorTest Unit Tests
///</summary>
	[TestClass]
	public ref class CRC8CalculatorTest
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
			///A test for CRC8Calculator Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CRC8CalculatorConstructorTest()
			{
				CRC8Calculator_Accessor^  target = (gcnew CRC8Calculator_Accessor());
				Assert::IsNotNull(target->crc8Table);
			}


			/// <summary>
			///A test for CRC8Calculator Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ComputeCrc8ForArrayTest()
			{
				try
				{
				CRC8Calculator_Accessor^  target = (gcnew CRC8Calculator_Accessor());
				array<unsigned char>^ testArray = gcnew array<unsigned char> {0x10, 0x1F, 0xFF };
				unsigned char expected, actual;
				expected = 0xc5;
				actual = 0x00;
				 target->ComputeCrc8ForArray(testArray, 3 ,&actual );
				 Assert::AreEqual(expected, actual);
				}
				catch(Exception^ excepObj)
				{
					Assert::Fail("Exception raised");
				}
			}
	};
}
namespace TestDal {
    
}
