
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
			}
			/// <summary>
			///A test for DataBuffer
			///</summary>
	public: [TestMethod]
			void DataBufferTest()
			{
				DalDataBuffer^  target = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value
				Array^  actual;
				actual = target->DataBuffer;
				Assert::IsNotNull(actual);
				//Assert::AreEqual(target->ArraySize , -1); //TODO: This test passed when an accessor was created
			}
			
			/// <summary>
			///A test for ArraySize
			///</summary>
	public: [TestMethod]
			void ArraySizeTest()
			{
				int captureTime, samplingrate;
				DalDataBuffer^  target = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value
				
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
				DalDataBuffer^  target = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value

				
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


				public: [TestMethod]
			void WriteDataToBufferTestNeg()
			{
				DalDataBuffer^  target = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value

				DalPwvDataStruct dataToWrite; 
				dataToWrite.cuffPulseData = 100;
				dataToWrite.tonometerData = 200;
				

				try
				{

					target->WriteDataToBuffer(dataToWrite);
				}
				catch(DalException^ dalExObj)
				{
					Assert::IsTrue(true);
				}
			}

			/// <summary>
			///A test for op_Assign
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void op_AssignTest()
			{
				DalDataBuffer^  target = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value
				DalDataBuffer^ unnamed = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value
				//unnamed->_arraySize = 100; //TODO: This test passed when an accessor was created

				DalDataBuffer^  expected = nullptr; // TODO: Initialize to an appropriate value
				DalDataBuffer^  actual;
				actual = (target = unnamed);
				Assert::AreEqual(unnamed, actual);
			}
			/// <summary>
			///A test for GetValueAt
			///</summary>
	public: [TestMethod]
			void GetValueAtTest()
			{
				DalDataBuffer^  target = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value
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
				DalDataBuffer^  target = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value
				int captureTime = 10; // TODO: Initialize to an appropriate value
				int samplingRate = 30; // TODO: Initialize to an appropriate value
				bool expected = true; // TODO: Initialize to an appropriate value
				bool actual;
				actual = target->CreateBuffer(captureTime, samplingRate);
				Assert::AreEqual(expected, actual);
				//Assert::IsNotNull(target->bufferPointer); //TODO: This test passed when an accessor was created
			}

			/// Negative testcase for 
			///A test for CreateBuffer
			///</summary>
	public: [TestMethod]
			void CreateBufferTestNeg()
			{
				DalDataBuffer^  target = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value
				int captureTime = -10; // TODO: Initialize to an appropriate value
				int samplingRate = -30; // TODO: Initialize to an appropriate value
				try
				{
				target->CreateBuffer(captureTime, samplingRate);
				}
				catch(DalException^ dalExcepObj)
				{
					Assert::IsTrue(true);

				}
			}

			/// <summary>
			///A test for DalDataBuffer Constructor
			///</summary>
			//Deepak: This test case cannot be run. 
//	public: [TestMethod]
//			[DeploymentItem(L"dal.dll")]
//			void DalDataBufferConstructorTest1()
//			{
//				DalDataBuffer^  unnamed = DalDataBuffer::Instance; // TODO: Initialize to an appropriate value
////				unnamed->_arraySize = 999;
//				DalDataBuffer^  target = (gcnew DalDataBuffer((unnamed));
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
				DalDataBuffer^  target = (DalDataBuffer::Instance);
				Assert::IsNotNull(target);
			}



			//DalDataBuffer::DalDataBuffer(const AtCor::Scor::DataAccess::DalDataBuffer ^)
			//{
			//	//overloaded copy constructor.
			//	//Does nothing
			//}

			/// <summary>
			///A test for DalDataBuffer Constructor
			///</summary>
			public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalDataBufferConstructorTest2()
			{
				DalDataBuffer^  target = (DalDataBuffer::Instance);
				//DalDataBuffer ^actual = gcnew DalDataBuffer(target);
				Assert::IsNotNull(target);
				//Assert::AreEqual(target, actual);
			}


			

			/// <summary>
			///A test for WriteDataToBuffer
			///</summary>
	public: [TestMethod]
			void GetAllValuesTest()
			{
				DalDataBuffer^  target = (DalDataBuffer::Instance); 

				target->CreateBuffer(10, 1);

				DalPwvDataStruct dataToWrite; 
				dataToWrite.cuffPulseData = 100;
				dataToWrite.tonometerData = 200;
				bool expected = true; // TODO: Initialize to an appropriate value
				bool actual;
				DalPwvDataStruct^ DataToRead;

				int fromIndex, toIndex;
				
				//Before writing
				target->GetAllValues(fromIndex, toIndex);
				Assert::AreEqual(fromIndex, -1);
				Assert::AreEqual(toIndex, -1);

				actual = target->WriteDataToBuffer(dataToWrite);
				Assert::AreEqual(expected, actual);

				target->CreateBuffer(10, 1);
				for (int i = 0; i<10; i++)
				{
					target->WriteDataToBuffer (dataToWrite);
					target->GetAllValues(fromIndex, toIndex);
					Assert::AreEqual(fromIndex, 0);
					Assert::AreEqual(toIndex, i);
					//Assert::AreEqual(dataToWrite.tonometerData, DataToRead->tonometerData);
				}
				target->WriteDataToBuffer (dataToWrite);
				target->WriteDataToBuffer (dataToWrite);
				target->WriteDataToBuffer (dataToWrite);
				target->GetAllValues(fromIndex, toIndex);
				Assert::AreEqual(fromIndex, 0);
					Assert::AreEqual(toIndex, 12);
			}



			public: [TestMethod]
			void GetAllValuesTest2()
			{
				DalDataBuffer^  target = (DalDataBuffer::Instance); 
				int fromIndex, toIndex;
				
				try
				{
					target->GetAllValues(fromIndex, toIndex);
				}
				catch(DalException ^ dalExObj)
				{
					Assert::IsTrue(true);
				}
			}



				public: [TestMethod]
			void GetNextValuesTest()
			{
				DalDataBuffer^  target = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value
				int readStartIndex = 0; // TODO: Initialize to an appropriate value
				int offsetFromReadStartIndex = 0; // TODO: Initialize to an appropriate value
				DalPwvDataStruct  expected ; // TODO: Initialize to an appropriate value
				DalPwvDataStruct^  actual;
				expected.cuffPulseData = 100;
				expected.tonometerData = 200;
				DalPwvDataStruct^ DataToRead;
				DalPwvDataStruct dataToWrite;

				try
				{
					target->GetNextValues(1, readStartIndex);
				}
				catch( DalException^ dalExcepObj)
				{
					Assert::IsTrue(true);
				}

				try
				{
					target->GetNextValues(-1, readStartIndex); //test negative parameter
				}
				catch( DalException^ dalExcepObj)
				{
					Assert::IsTrue(true);
				}

				target->CreateBuffer(10,1);

				
				target->GetNextValues(1, readStartIndex); //test empty buffer
				Assert::AreEqual(readStartIndex, -1);
				

				target->WriteDataToBuffer(expected);

				try
				{
					target->GetNextValues(100, readStartIndex); //test array size too large
				}
				catch( DalException^ dalExcepObj)
				{
					Assert::IsTrue(true);
				}
				
				
				target->CreateBuffer(10, 1);
				for (int i = 0; i<20; i++)
				{
					dataToWrite.tonometerData =i;
					target->WriteDataToBuffer (dataToWrite);
					target->GetNextValues(1, readStartIndex);
					Assert::AreEqual(readStartIndex, i%(target->ArraySize));
				}

				target->GetNextValues(1, readStartIndex);
				target->GetNextValues(1, readStartIndex);
				target->GetNextValues(1, readStartIndex);
				//empty the buffer and then check the result
				Assert::AreEqual(readStartIndex, -1);



			}


				public: [TestMethod]
			void GetNextValues_CheckExcessRequest_Test()
			{
				DalDataBuffer^  target = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value
				int readStartIndex = 0; // TODO: Initialize to an appropriate value
				int offsetFromReadStartIndex = 0; // TODO: Initialize to an appropriate value
				int returnedValues;
				
				DalPwvDataStruct dataToWrite;

				target->CreateBuffer(10,1);

				for (int i = 0; i<5; i++)
				{
					dataToWrite.tonometerData =i;
					target->WriteDataToBuffer (dataToWrite);
				}

				returnedValues = target->GetNextValues(7, readStartIndex); //values asked for are more than recieved
				
				Assert::AreEqual(returnedValues, 5);
			}


			public: [TestMethod]
			void GetNextValues_CheckExcessRequestAfterRollover_Test()
			{
				DalDataBuffer^  target = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value
				int readStartIndex = 0; // TODO: Initialize to an appropriate value
				int offsetFromReadStartIndex = 0; // TODO: Initialize to an appropriate value
				int returnedValues;
				
				DalPwvDataStruct dataToWrite;

				target->CreateBuffer(10,1);

				for (int i = 0; i<10; i++)
				{
					dataToWrite.tonometerData =i;
					target->WriteDataToBuffer (dataToWrite);
				}

				returnedValues = target->GetNextValues(7, readStartIndex); 
				returnedValues = target->GetNextValues(7, readStartIndex); 
				Assert::AreEqual(readStartIndex, 7);
			}


			public: [TestMethod]
			void GetNextValues_CheckExcessRequestAfterRollover_Test2()
			{
				DalDataBuffer^  target = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value
				int readStartIndex = 0; // TODO: Initialize to an appropriate value
				int offsetFromReadStartIndex = 0; // TODO: Initialize to an appropriate value
				int returnedValues;
				
				DalPwvDataStruct dataToWrite;

				target->CreateBuffer(10,1);

				for (int i = 0; i<=13; i++)
				{
					dataToWrite.tonometerData =i;
					target->WriteDataToBuffer (dataToWrite);
				}

				returnedValues = target->GetNextValues(7, readStartIndex); 
				returnedValues = target->GetNextValues(8, readStartIndex); 
				Assert::AreNotEqual(7,returnedValues);
			}

			public: [TestMethod]
			void GetNextValues_CheckExcessRequestAfterRollover_Test3()
			{
				DalDataBuffer^  target = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value
				int readStartIndex = 0; // TODO: Initialize to an appropriate value
				int offsetFromReadStartIndex = 0; // TODO: Initialize to an appropriate value
				int returnedValues;
				bool writen;
				
				DalPwvDataStruct dataToWrite;

				target->CreateBuffer(10,1);

				for (int i = 0; i<=15; i++)
				{
					dataToWrite.tonometerData =i;
					writen = target->WriteDataToBuffer (dataToWrite);
					Assert::IsTrue(writen);
				}

				for (int i = 0; i<=5; i++)
				{
					returnedValues = target->GetNextValues(1, readStartIndex); 
					Assert::AreNotEqual(0,returnedValues);
				}

				returnedValues = target->GetNextValues(5, readStartIndex); 
				Assert::AreNotEqual(0,returnedValues);
				

			}


			public: [TestMethod]
			void GetNextValues_CheckExcessRequestAfterRollover_Test4()
			{
				DalDataBuffer^  target = (DalDataBuffer::Instance); // TODO: Initialize to an appropriate value
				int readStartIndex = 0; // TODO: Initialize to an appropriate value
				int offsetFromReadStartIndex = 0; // TODO: Initialize to an appropriate value
				int returnedValues;
				bool writen;
				
				DalPwvDataStruct dataToWrite;

				target->CreateBuffer(10,1);

				for (int i = 0; i<=12; i++)
				{
					dataToWrite.tonometerData =i;
					writen = target->WriteDataToBuffer (dataToWrite);
					Assert::IsTrue(writen);
				}

				for (int i = 1; i<=12; i++)
				{
					returnedValues = target->GetNextValues(1, readStartIndex); 
					Assert::AreNotEqual(0,returnedValues);
				}

				returnedValues = target->GetNextValues(3, readStartIndex); 
				Assert::AreEqual(0,returnedValues);
				

			}


	};
}
namespace TestDal {
    
}
