
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalResponsePacketQueueTest;
    
    
    /// <summary>
///This is a test class for DalResponsePacketQueueTest and is intended
///to contain all DalResponsePacketQueueTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalResponsePacketQueueTest
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
				DalResponsePacketBuffer^  actual;
				actual = DalResponsePacketBuffer::Instance;
				Assert::IsNotNull(actual);
			}
			/// <summary>
			///A test for op_Assign
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void op_AssignTest()
			{
				DalResponsePacketQueue_Accessor^  target = (gcnew DalResponsePacketQueue_Accessor()); 
				DalResponsePacketQueue_Accessor^  unnamed = target; 
				DalResponsePacketQueue_Accessor^  expected = target; 
				DalResponsePacketQueue_Accessor^  actual;
				actual = (target = unnamed);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for Enqueue
			///</summary>
	public: [TestMethod]
			void EnqueueTest()
			{
				DalResponsePacketQueue_Accessor^  target = gcnew DalResponsePacketQueue_Accessor(); 
				cli::array< unsigned char >^  packet = gcnew array<unsigned char> {0x01, 0x02, 0x03}; 
				target->Enqueue(packet);

				//test that there is data
				Assert::IsNotNull(target->waitingResponse);

				//validate the data
				for (int i = 0; i < packet->Length; i++)
				{
					Assert::AreEqual(packet[i], target->waitingResponse[i]);

				}
			}

	//		/// <summary>
	//		///A test for Dispose
	//		///</summary>
	//public: [TestMethod]
	//		void DisposeTest1()
	//		{
	//			DalResponsePacketQueue_Accessor^  target = (gcnew DalResponsePacketQueue_Accessor()); // TODO: Initialize to an appropriate value
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
	//			DalResponsePacketQueue_Accessor^  target = (gcnew DalResponsePacketQueue_Accessor()); // TODO: Initialize to an appropriate value
	//			bool unnamed = false; // TODO: Initialize to an appropriate value
	//			target->Dispose(unnamed);
	//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}



			/// <summary>
			///A test for Dequeue
			///Case 1 : no data is pressent in queue
	public: [TestMethod]
			void DequeueEmptyQueueTest()
			{
				DalResponsePacketQueue_Accessor^  target = (gcnew DalResponsePacketQueue_Accessor()); 
				cli::array< unsigned char >^  expected = nullptr; 
				cli::array< unsigned char >^  actual;

				//Assert precondition before checking
				Assert::IsNull(target->waitingResponse);

				actual = target->Dequeue();

				Assert::IsNull(actual);
			}

			/// <summary>
			///A test for Dequeue
			///Case 2 : data is pressent in queue
	public: [TestMethod]
			void DequeueWithDataTest()
			{
				DalResponsePacketQueue_Accessor^  target = (gcnew DalResponsePacketQueue_Accessor()); 
				cli::array< unsigned char >^  expected = gcnew array<unsigned char> {0x01, 0x02, 0x03}; 
				cli::array< unsigned char >^  actual;

				//precondition: data should be present in target:
				target->Enqueue(expected);
				//Assert precondition before checking
				Assert::IsNotNull(target->waitingResponse);

				actual = target->Dequeue();

				//Recheck if the buffer is emptied
				Assert::IsNull(target->waitingResponse);

				for (int i = 0; i < expected->Length; i++)
				{
					Assert::AreEqual(expected[i], actual[i]);

				}
			}

			/// <summary>
			///A test for Clear
			///</summary>
	public: [TestMethod]
			void ClearTest()
			{
				DalResponsePacketQueue_Accessor^  target = (gcnew DalResponsePacketQueue_Accessor()); 
				//Preinitialize  by enquing some data to clear
				cli::array< unsigned char >^  expected = gcnew array<unsigned char> {0x01, 0x02, 0x03}; 
				
				//precondition: data should be present in target:
				target->Enqueue(expected);
				
				//Assert precondition before checking
				Assert::IsNotNull(target->waitingResponse);

				//call the method under test
				target->Clear();
				
				//now check that the internal array has been cleared
				Assert::IsNull(target->waitingResponse);
			}

			/// <summary>
			///A test for ~DalResponsePacketBuffer
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalResponsePacketQueueDestructorTest()
			{
				DalResponsePacketQueue_Accessor^  target = (gcnew DalResponsePacketQueue_Accessor()); 

				//Preinitialize  by enquing some data to clear
				cli::array< unsigned char >^  expected = gcnew array<unsigned char> {0x01, 0x02, 0x03}; 
				
				//precondition: data should be present in target:
				target->Enqueue(expected);
				
				//Assert precondition before checking
				Assert::IsNotNull(target->waitingResponse);

				//now call the method under test
				delete target;
				
				Assert::IsNull(target->waitingResponse);
			}
			
			//copy constructor is inaccible and unused 
			//It has been added and made privet to support singleton
			/*/// <summary>
			///A test for DalResponsePacketBuffer Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalResponsePacketQueueConstructorTest1()
			{
				DalResponsePacketBuffer^  unnamed = gcnew DalResponsePacketBuffer(); 
				DalResponsePacketBuffer^  target = (gcnew DalResponsePacketBuffer(unnamed));
				Assert::AreSame(unnamed, target);
			}*/
			/// <summary>
			///A test for DalResponsePacketBuffer Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalResponsePacketQueueConstructorTest()
			{
				DalResponsePacketQueue_Accessor^  target = (gcnew DalResponsePacketQueue_Accessor());
				Assert::IsNotNull(target);
			}
	};
}
namespace TestDal {
    
}
