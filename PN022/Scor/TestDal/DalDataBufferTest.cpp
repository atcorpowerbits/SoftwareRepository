
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalDataBufferTest;
    
    
    /// <summary>
///This is a test class for DalDataBufferTest and is intended
///to contain all DalDataBufferTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalDataBufferTest
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
			///A test for Instance
			///</summary>
	public: [TestMethod]
			void InstanceTest()
			{
				DalDataBuffer^  actual;
				actual = DalDataBuffer::Instance;
				DalDataBuffer^ target;
				target = DalDataBuffer::Instance;
				Assert::AreSame(target, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for DataBuffer
			///</summary>
	public: [TestMethod]
			void DataBufferTest()
			{
				DalDataBuffer_Accessor^  target = (gcnew DalDataBuffer_Accessor()); // TODO: Initialize to an appropriate value
				Array^  actual;
				actual = target->DataBuffer;
				Assert::IsNull(actual);
				Assert::AreEqual(target->_arraySize, -1);
			}
			
			/// <summary>
			///A test for ArraySize
			///</summary>
	public: [TestMethod]
			void ArraySizeTest()
			{
				int captureTime, samplingrate;
				DalDataBuffer_Accessor^  target = (gcnew DalDataBuffer_Accessor()); // TODO: Initialize to an appropriate value
				
				captureTime = 10;
				samplingrate = 20;
				int expectedArraySize = (captureTime +2)*samplingrate +1;
				
				target->CreateBuffer(captureTime, samplingrate);
				
				int actual;
				actual = target->ArraySize;
				Assert::AreEqual(expectedArraySize, actual);
			}
			
			
			/// <summary>
			///A test for WriteDataToBuffer
			///</summary>
	public: [TestMethod]
			void WriteDataToBufferTest()
			{
				DalDataBuffer_Accessor^  target = (gcnew DalDataBuffer_Accessor()); // TODO: Initialize to an appropriate value

				target->CreateBuffer(10, 1);

				DalPwvDataStruct dataToWrite; 
				dataToWrite.cuffPulseData = 100;
				dataToWrite.tonometerData = 200;
				bool expected = true; // TODO: Initialize to an appropriate value
				bool actual;
				DalPwvDataStruct^ DataToRead;
				
				
				actual = target->WriteDataToBuffer(dataToWrite);
				Assert::AreEqual(expected, actual);

				target->CreateBuffer(10, 1);
				for (int i = 0; i<15; i++)
				{
					dataToWrite.tonometerData =i;
					target->WriteDataToBuffer (dataToWrite);
					DataToRead = target->GetValueAt(0, i);
					Assert::AreEqual(dataToWrite.tonometerData, DataToRead->tonometerData);
				}
			}

			/// <summary>
			///A test for op_Assign
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void op_AssignTest()
			{
				DalDataBuffer_Accessor^  target = (gcnew DalDataBuffer_Accessor()); // TODO: Initialize to an appropriate value
				DalDataBuffer_Accessor^ unnamed = (gcnew DalDataBuffer_Accessor()); // TODO: Initialize to an appropriate value
				unnamed->_arraySize = 100;

				DalDataBuffer_Accessor^  expected = nullptr; // TODO: Initialize to an appropriate value
				DalDataBuffer_Accessor^  actual;
				actual = (target = unnamed);
				Assert::AreEqual(unnamed, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for GetValueAt
			///</summary>
	public: [TestMethod]
			void GetValueAtTest()
			{
				DalDataBuffer_Accessor^  target = (gcnew DalDataBuffer_Accessor()); // TODO: Initialize to an appropriate value
				int readStartIndex = 0; // TODO: Initialize to an appropriate value
				int offsetFromReadStartIndex = 0; // TODO: Initialize to an appropriate value
				DalPwvDataStruct  expected ; // TODO: Initialize to an appropriate value
				DalPwvDataStruct^  actual;
				expected.cuffPulseData = 100;
				expected.tonometerData = 200;
				DalPwvDataStruct^ DataToRead;
				DalPwvDataStruct dataToWrite;

				target->CreateBuffer(10,1);
				target->WriteDataToBuffer(expected);
				
				actual = target->GetValueAt(readStartIndex, offsetFromReadStartIndex);
				Assert::AreEqual(expected.tonometerData , actual->tonometerData);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");


				target->CreateBuffer(10, 1);
				for (int i = 0; i<15; i++)
				{
					dataToWrite.tonometerData =i;
					target->WriteDataToBuffer (dataToWrite);
					DataToRead = target->GetValueAt(0, i);
					Assert::AreEqual(dataToWrite.tonometerData, DataToRead->tonometerData);
				}

			}
			/// <summary>
			///A test for CreateBuffer
			///</summary>
	public: [TestMethod]
			void CreateBufferTest()
			{
				DalDataBuffer_Accessor^  target = (gcnew DalDataBuffer_Accessor()); // TODO: Initialize to an appropriate value
				int captureTime = 10; // TODO: Initialize to an appropriate value
				int samplingRate = 30; // TODO: Initialize to an appropriate value
				bool expected = true; // TODO: Initialize to an appropriate value
				bool actual;
				actual = target->CreateBuffer(captureTime, samplingRate);
				Assert::AreEqual(expected, actual);
				Assert::IsNotNull(target->bufferPointer); 
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}

			/// <summary>
			///A test for DalDataBuffer Constructor
			///</summary>
			//Deepak: This test case cannot be run. 
//	public: [TestMethod]
//			[DeploymentItem(L"dal.dll")]
//			void DalDataBufferConstructorTest1()
//			{
//				DalDataBuffer_Accessor^  unnamed = gcnew DalDataBuffer_Accessor(); // TODO: Initialize to an appropriate value
////				unnamed->_arraySize = 999;
//				DalDataBuffer_Accessor^  target = (gcnew DalDataBuffer_Accessor((unnamed));
//				Assert::AreEqual(unnamed, target);
//				
//				Assert::AreEqual (unnamed->ArraySize, target->ArraySize);
//			}
			
			/// <summary>
			///A test for DalDataBuffer Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalDataBufferConstructorTest()
			{
				DalDataBuffer_Accessor^  target = (gcnew DalDataBuffer_Accessor());
				Assert::IsNotNull(target);
			}
	};
}
namespace TestDal {
    
}
