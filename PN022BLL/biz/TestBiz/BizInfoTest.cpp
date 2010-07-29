
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace Biz;
namespace TestBiz {
    using namespace System;
    ref class BizInfoTest;
    
    
    /// <summary>
///This is a test class for BizInfoTest and is intended
///to contain all BizInfoTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizInfoTest
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
				BizInfo^  expected; // TODO: Initialize to an appropriate value
				BizInfo^  actual;
				expected = BizInfo::Instance();
				actual = BizInfo::Instance();
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for GetVersion
			///</summary>
	public: [TestMethod]
			void GetVersionTest()
			{
				BizInfo^  target = BizFacade::Instance()->GetBizInfo(); // TODO: Initialize to an appropriate value
				String^ appVersion = L"blankVersion1234567890"; // TODO: Initialize to an appropriate value
				int len = appVersion->Length;
				target->GetVersion(appVersion, len);
				Assert::AreEqual(L"Version 0.1 (stub)", appVersion);
			}
			/// <summary>
			///A test for GetVersion
			///</summary>
	public: [TestMethod]
			void GetVersionTestZeroLen()
			{
				BizInfo^  target = BizFacade::Instance()->GetBizInfo(); // TODO: Initialize to an appropriate value
				String^ appVersion = L"blankVersion1234567890"; // TODO: Initialize to an appropriate value
				target->GetVersion(appVersion, 0);
				Assert::AreEqual(L"", appVersion);
			}
			/// <summary>
			///A test for GetVersion
			///</summary>
	public: [TestMethod]
			void GetVersionTestTruncated()
			{
				BizInfo^  target = BizFacade::Instance()->GetBizInfo(); // TODO: Initialize to an appropriate value
				String^ appVersion = L"1234567890"; // TODO: Initialize to an appropriate value
				int len = appVersion->Length;
				target->GetVersion(appVersion, len);
				Assert::AreEqual(L"Version 0.", appVersion);
			}
			/// <summary>
			///A test for GetCoName
			///</summary>
	public: [TestMethod]
			void GetCoNameTest()
			{
				BizInfo^  target = BizFacade::Instance()->GetBizInfo(); // TODO: Initialize to an appropriate value
				String^ coName = L"blankCoName1234567890"; // TODO: Initialize to an appropriate value
				int len = coName->Length;
				target->GetCompanyName(coName, len);
				Assert::AreEqual(L"AtCor Medical (stub)", coName);
			}			/// <summary>
			/// <summary>
			///A test for GetCoName
			///</summary>
	public: [TestMethod]
			void GetCoNameTestZeroLen()
			{
				BizInfo^  target = BizFacade::Instance()->GetBizInfo(); // TODO: Initialize to an appropriate value
				String^ coName = L"blankCoName1234567890"; // TODO: Initialize to an appropriate value
				target->GetCompanyName(coName, 0);
				Assert::AreEqual(L"", coName);
			}			/// <summary>
			/// <summary>
			///A test for GetCoName
			///</summary>
	public: [TestMethod]
			void GetCoNameTestTruncated()
			{
				BizInfo^  target = BizFacade::Instance()->GetBizInfo(); // TODO: Initialize to an appropriate value
				String^ coName = L"1234567890"; // TODO: Initialize to an appropriate value
				int len = coName->Length;
				target->GetCompanyName(coName, len);
				Assert::AreEqual(L"AtCor Medi", coName);
			}			/// <summary>
			///A test for BizInfo Constructor
			///</summary>
	public: [TestMethod]
			void BizInfoConstructorTest()
			{
				BizInfo^  target = BizFacade::Instance()->GetBizInfo();
				Assert::AreNotEqual(nullptr, target);
			}
	};
}
namespace TestBiz {
    
}
