
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalStreamingPacketQueueTest;
    
    
    /// <summary>
///This is a test class for DalStreamingPacketQueueTest and is intended
///to contain all DalStreamingPacketQueueTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalStreamingPacketQueueTest
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
				DalStreamingPacketQueue^  actual;
				actual = DalStreamingPacketQueue::Instance;
				Assert::IsNotNull(actual);
			}

			/// <summary>
			///A test for op_Assign
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void op_AssignTest()
			{
				DalStreamingPacketQueue_Accessor^  target = (gcnew DalStreamingPacketQueue_Accessor()); 
				DalStreamingPacketQueue_Accessor^  unnamed = target;
				DalStreamingPacketQueue_Accessor^  expected = target; 
				DalStreamingPacketQueue_Accessor^  actual;
				actual = (target = unnamed);
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for Enqueue
			///</summary>
	public: [TestMethod]
			void EnqueueTest()
			{
				DalStreamingPacketQueue_Accessor^  target = (gcnew DalStreamingPacketQueue_Accessor()); 
				array< unsigned char >^  packet = gcnew array<unsigned char> {0x01, 0x02, 0x03}; 
				//First assert precondition
				Assert::AreEqual(0, target->streamingPacketQueue->Count);
				
				//ow call the method under test
				target->Enqueue(packet);

				Assert::AreEqual(1, target->streamingPacketQueue->Count);

				//since there is only one packet inqueue
				array<unsigned char>^ actual = target->streamingPacketQueue->Peek();

				Assert::AreSame(packet, actual);
			}


	//		/// <summary>
	//		///A test for Dispose
	//		///</summary>
	//public: [TestMethod]
	//		void DisposeTest1()
	//		{
	//			DalStreamingPacketQueue_Accessor^  target = (gcnew DalStreamingPacketQueue_Accessor()); // TODO: Initialize to an appropriate value
	//			target->Dispose();
	//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
	//		/// <summary>
	//		///A test for Dispose
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void DisposeTest()
	//		{
	//			DalStreamingPacketQueue_Accessor^  target = (gcnew DalStreamingPacketQueue_Accessor()); // TODO: Initialize to an appropriate value
	//			bool unnamed = false; // TODO: Initialize to an appropriate value
	//			target->Dispose(unnamed);
	//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}

			/// <summary>
			///A test for Dequeue
			///</summary>
	public: [TestMethod]
			void DequeueWithNoDataTest()
			{
				DalStreamingPacketQueue_Accessor^  target = (gcnew DalStreamingPacketQueue_Accessor()); 
				cli::array< unsigned char >^  expected =  nullptr; 
				cli::array< unsigned char >^  actual;
				
				actual = target->Dequeue();
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive("Code not written yet. Remove this line after coding");
			}

			/// <summary>
			///A test for Dequeue
			///</summary>
	public: [TestMethod]
			void DequeueTest()
			{
				DalStreamingPacketQueue_Accessor^  target = (gcnew DalStreamingPacketQueue_Accessor()); 
				cli::array< unsigned char >^  expected =  gcnew array<unsigned char> {0x01, 0x02, 0x03}; 
				cli::array< unsigned char >^  actual;
				//Precondition: data must be present before dequing
				target->Enqueue(expected);
				Assert::AreEqual(1, target->streamingPacketQueue->Count);

				//Now call the method under test
				actual = target->Dequeue();

				Assert::AreSame(expected, actual);
				Assert::AreEqual(0, target->streamingPacketQueue->Count);
			}

			/// <summary>
			///A test for Clear
			///</summary>
	public: [TestMethod]
			void ClearTest()
			{
				DalStreamingPacketQueue_Accessor^  target = (gcnew DalStreamingPacketQueue_Accessor()); 
				cli::array< unsigned char >^  expected =  gcnew array<unsigned char> {0x01, 0x02, 0x03}; 
				cli::array< unsigned char >^  actual;

				//Precondition: data must be present before dequing
				target->Enqueue(expected); //Enque three times
				target->Enqueue(expected);
				target->Enqueue(expected);

				//Test precondition
				Assert::AreEqual(3, target->streamingPacketQueue->Count);

				target->Clear();

				//verify that there is nothing left in the queue
				Assert::AreEqual(0, target->streamingPacketQueue->Count);
				actual = target->Dequeue();
				Assert::IsNull(actual);
			}


			/// <summary>
			///A test for ~DalStreamingPacketQueue
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalStreamingPacketQueueDestructorTest()
			{
				DalStreamingPacketQueue_Accessor^  target = (gcnew DalStreamingPacketQueue_Accessor()); // TODO: Initialize to an appropriate value

				//Preinitialize  by enquing some data to clear
				cli::array< unsigned char >^  expected = gcnew array<unsigned char> {0x01, 0x02, 0x03}; 
				
				//precondition: data should be present in target:
				target->Enqueue(expected);

				//Assert precondition before checking
				Assert::IsNotNull(target->streamingPacketQueue);

				delete target;
				
				Assert::IsNull(target->streamingPacketQueue);
			}


			//Method is p[rivate. copy constructor is unused
			/*/// <summary>
			///A test for DalStreamingPacketQueue Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalStreamingPacketQueueConstructorTest1()
			{
				DalStreamingPacketQueue^  unnamed = gcnew DalStreamingPacketQueue(); 
				DalStreamingPacketQueue_Accessor^  target = (gcnew DalStreamingPacketQueue_Accessor(unnamed));
				Assert::AreSame(unnamed, target);
			}*/


			/// <summary>
			///A test for DalStreamingPacketQueue Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalStreamingPacketQueueConstructorTest()
			{
				DalStreamingPacketQueue_Accessor^  target = (gcnew DalStreamingPacketQueue_Accessor());
				Assert::IsNotNull(target);
				//Assert::Inconclusive("Code not written yet. Remove this line after coding");
			}
	};
}
namespace TestDal {
    
}
