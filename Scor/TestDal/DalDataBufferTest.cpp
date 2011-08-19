
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting;

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

			//DeepaK; replacing this test with new one below. It should run correctly regardless of whether it is run in a batch
	//		/// <summary>
	//		///A test for DataBuffer
	//		///</summary>
	//public: [TestMethod]
	//		void DataBufferTest()
	//		{
	//			//Thisd test will fail when run  in a batch becuase the DalSimulationHandler class creates a buffer 
	//			//and it will result in the 

	//			DalDataBuffer^  target = (DalDataBuffer::Instance); 
	//			Array^  actual;
	//			actual = target->DataBuffer;
	//			Assert::IsNull(actual, "Run this test individually for it to pass");
	//			Assert::AreEqual(target->ArraySize , -1); //TODO: This test passed when an accessor was created
	//		}

			/// <summary>
			///A test for DataBuffer
			///</summary>
	public: [TestMethod]
			void DataBufferTest()
			{
				DalDataBuffer_Accessor^  target = gcnew DalDataBuffer_Accessor(); 
				Array^  actual;
				actual = target->DataBuffer;
				Assert::IsNull(actual);
				Assert::AreEqual(target->ArraySize , -1); 
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


			//This test shall attemp to write to the buffer withoout first creating a buffer
			//THis should result in an excpetion being thrown
			public: [TestMethod]
			void WriteDataToBufferTestNeg()
			{
				DalDataBuffer_Accessor^  target = (gcnew DalDataBuffer_Accessor()); 

				DalPwvDataStruct dataToWrite; 
				dataToWrite.cuffPulseData = 100;
				dataToWrite.tonometerData = 200;

				bool expected1 = false;
				bool expected2 = true;
				bool actual1;
				bool actual2;

				try
				{
					//target->CreateBuffer(10, 256);
					actual1 = target->WriteDataToBuffer(dataToWrite);
					Assert::AreEqual(expected1, actual1);
				}
				catch(AtCor::Scor::CrossCutting::ScorException^ )
				{
					//Assert::IsTrue(true);
					actual2 = true;
				}
				Assert::AreEqual(expected2, actual2);
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
				bool actual1 = false;
				bool actual2 = true;
				bool expected1;
				bool expected2;

				try
				{
				  expected1	= expected1 = target->CreateBuffer(captureTime, samplingRate);
				  Assert::AreEqual(expected1,actual1);
				}
				catch(AtCor::Scor::CrossCutting::ScorException^ )
				{
					//Assert::IsTrue(true,);
					expected2 = true;	
				}
				Assert::AreEqual(expected2, actual2);
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
				//DalPwvDataStruct^ DataToRead;

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
				DalDataBuffer^  target = (DalDataBuffer::Instance ); 
				int fromIndex, toIndex;
				bool actual1 = false;
				bool actual2 = true;
				bool expected1;
				bool expected2;
				try
				{
				  expected1	= target->GetAllValues(fromIndex, toIndex);
				  if (fromIndex == -1 && toIndex == -1)
				  {
						Assert::AreEqual(expected1, actual1);
				  }
				  else
				  {
						Assert::AreEqual(expected1, actual2);
				  }
				}
				catch(AtCor::Scor::CrossCutting::ScorException ^ )
				{
					//Assert::IsTrue(true);
					expected2 = true;
					Assert::AreEqual(expected2, actual2);
				}
			}



			public: [TestMethod]
			void GetNextValuesTest()
			{
				DalDataBuffer_Accessor^  target = gcnew DalDataBuffer_Accessor(); 
				int readStartIndex = 0; 
				int offsetFromReadStartIndex = 0; 
				DalPwvDataStruct  expected ; 
				//DalPwvDataStruct^  actual;
				expected.cuffPulseData = 100;
				expected.tonometerData = 200;
				//DalPwvDataStruct^ DataToRead;
				DalPwvDataStruct dataToWrite;
		
				bool expected1 = false;
				bool actual1 = false;

				int retValue;
				
				try
				{
					 retValue = target->GetNextValues(1, readStartIndex);
					//throws exception here because before calling this method
					//buffer has to be created. here bufferpointer is always null

				}
				catch(AtCor::Scor::CrossCutting::ScorException ^ )
				{
					//Assert::IsTrue(true);
					actual1 = true;
				}
				Assert::AreEqual(true, actual1);
				try
				{
					retValue= target->GetNextValues(-1, readStartIndex); //test negative parameter
					//throws exception here because before calling this method
					//buffer has to be created. here bufferpointer is always null

				}
				catch( AtCor::Scor::CrossCutting::ScorException^ ) 
				{
					//Assert::IsTrue(true);
					actual1 = true;
				}

				Assert::AreEqual(true, actual1);

				try
				{
					expected1 = target->CreateBuffer(10,1);
					Assert::AreEqual(expected1, true);
				}
				catch( AtCor::Scor::CrossCutting::ScorException^ ) 
				{
					actual1 = false;
					Assert::AreEqual(false, actual1); //TODO
				}
				
				
				target->GetNextValues(1, readStartIndex); //test empty buffer
				Assert::AreEqual(readStartIndex, -1);
				
				try
				{
					expected1 = target->WriteDataToBuffer(expected);
					Assert::AreEqual(expected1, true);
				}
				catch( AtCor::Scor::CrossCutting::ScorException^ )
				{
					//Assert::IsTrue(true);
					actual1 = false;
					Assert::AreEqual(false, actual1);
				}


				try
				{
					retValue = target->GetNextValues(100, readStartIndex); //test array size too large
					//throws exception here because before calling this method
					//buffer has to be created. here bufferpointer is always null

				}
				catch( AtCor::Scor::CrossCutting::ScorException^ )
				{
					//Assert::IsTrue(true);
					actual1 = true;
				}
				Assert::AreEqual(actual1, true);  //neg test
				
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

				bool expected = true;
				//bool actual;
				
				DalPwvDataStruct dataToWrite;

				target->CreateBuffer(10,1);

				for (int i = 0; i<=15; i++)
				{
					dataToWrite.tonometerData =i;
					writen = target->WriteDataToBuffer (dataToWrite);
					//Assert::IsTrue(writen);
					Assert::AreEqual(expected, writen);
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

				bool expected = true;
				
				DalPwvDataStruct dataToWrite;

				target->CreateBuffer(10,1);

				for (int i = 0; i<=12; i++)
				{
					dataToWrite.tonometerData =i;
					writen = target->WriteDataToBuffer (dataToWrite);
					//Assert::IsTrue(writen);
					Assert::AreEqual(expected, writen);
				}

				for (int i = 1; i<=12; i++)
				{
					returnedValues = target->GetNextValues(1, readStartIndex); 
					Assert::AreNotEqual(0,returnedValues);
				}

				returnedValues = target->GetNextValues(3, readStartIndex); 
				Assert::AreEqual(0,returnedValues);
				

			}


			/// test without writing any data
			///A test for IsBufferEmpty
			///</summary>
		public: [TestMethod]
		void IsBufferEmptyTest()
		{
			DalDataBuffer_Accessor^  target = (gcnew DalDataBuffer_Accessor()); 
			target->CreateBuffer(10, 256);
			bool expected = true; 
			bool actual;
			actual = target->IsBufferEmpty();
			Assert::AreEqual(expected, actual);
		}


		/// test without creating buffer. should throw exceptionm
		///A test for IsBufferEmpty
		///</summary>
		public: [TestMethod]
		void IsBufferEmptyTest2()
		{
			DalDataBuffer_Accessor^  target = (gcnew DalDataBuffer_Accessor()); 
			bool actual;
			bool ExceptionThrown = false;
			try
			{
				actual = target->IsBufferEmpty();
			}
			catch(ScorException^)
			{
				ExceptionThrown = true;
			}
			Assert::IsTrue(ExceptionThrown);

			//now create a buffer exception thrown should be false
			target->CreateBuffer(10, 256);
			ExceptionThrown = false;
			try
			{
				actual = target->IsBufferEmpty();
			}
			catch(ScorException^)
			{
				ExceptionThrown = true;
			}
			Assert::IsFalse(ExceptionThrown);
		}

		/// test with data
		///A test for IsBufferEmpty
		///</summary>
		public: [TestMethod]
		void IsBufferEmptyTest3()
		{
			DalDataBuffer_Accessor^  target = (gcnew DalDataBuffer_Accessor()); 
			target->CreateBuffer(10, 256);
			bool expected = true; 
			bool actual;
			//first call without any data
			actual = target->IsBufferEmpty();
			Assert::AreEqual(expected, actual);
			
			//now enter some data
			DalPwvDataStruct pwvstruct ;
			
			target->WriteDataToBuffer(pwvstruct);
			actual = target->IsBufferEmpty();
			Assert::IsFalse(actual);
			int readStartIndex;
			target->GetNextValues(32, readStartIndex);
			target->GetValueAt(readStartIndex, 0);
			//now it shoud retur true again
			actual = target->IsBufferEmpty();
			Assert::IsTrue(actual);


		}




};
}
namespace TestDal {
    
}
