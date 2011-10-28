
#include "StdAfx.h"
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace System::IO;
namespace TestDal {
    using namespace System;
    ref class DalNibpCommandInterfaceTest;
    
    
    /// <summary>
///This is a test class for DalNibpCommandInterfaceTest and is intended
///to contain all DalNibpCommandInterfaceTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalNibpCommandInterfaceTest
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

		static bool eventRaised = false;
		static array<unsigned char> ^ recievedArray;

		static void MyNibpPacketEventRaisedTester(Object ^sender, NibPacketArrivedEventArgs^ args)
		 {
			 eventRaised = true;
			// recievedArray = args->nibpPacket;
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
			///A test for SendCommandToNibpModule
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SendCommandToNibpModuleTest()
			{
				DalNibpCommandInterface_Accessor^  target = (gcnew DalNibpCommandInterface_Accessor()); 
				//cli::array< unsigned char >^  nibpCommandByteArray = nullptr; 
				bool expected = true; 
				bool actual;
				//Create an array to embed and send to test 
				array<unsigned char>^ nibpCommandByteArray = gcnew array<unsigned char> {0x3A, 0x17, 0xB4, 0x00, 0xFB}; //Set initial inflate

				DalActivePort_Accessor::Instance->SetActivePort("COM9");

				actual = target->SendCommandToNibpModule(nibpCommandByteArray);
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for DalNibpCommandInterface Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalNibpCommandInterfaceConstructorTest()
			{
				DalNibpCommandInterface_Accessor^  target = (gcnew DalNibpCommandInterface_Accessor());
				Assert::IsNotNull(target);
				
			}
			/// <summary>
			///A test for ProcessNibpToHostPacket
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ProcessNibpToHostPacketTest()
			{
				cli::array< unsigned char >^  nibpToHostPacket = gcnew array<unsigned char> {0x93, 0x09, 0x00, 0x3E, 0x04, 0x4F, 0x6F, 0x00, 0x01, 0xEE }; 

				array<unsigned char>^ nibpSpecificData = gcnew array<unsigned char> {0x3E, 0x04, 0x4F, 0x6F};

				//register the test handler for the expected event
				DalEventContainer::Instance->OnDalNibpPacketEvent +=  gcnew NibPPacketArrivedEventHandler(&MyNibpPacketEventRaisedTester );


				DalNibpCommandInterface_Accessor::ProcessNibpToHostPacket(nibpToHostPacket);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");

				//POST

				//check that the event was raised
				Assert::IsTrue(eventRaised);

				//then check if the args were copied
				Assert::IsNotNull(recievedArray );
				Assert::AreEqual(nibpSpecificData->Length, recievedArray->Length);

				//check the entire array
				for (int i = 0; i < nibpSpecificData->Length; i++)
				{
					Assert::AreEqual(nibpSpecificData[i], recievedArray[i]);
				}
			}
	};
}
namespace TestDal {
    
}
