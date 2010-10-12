
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace System::Globalization;
using namespace Biz;
using namespace DataAccess;
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
				BizInfo^  target = BizFacade::Instance()->FindBizInfo(); // TODO: Initialize to an appropriate value
				String^ appVersion = L"blankVersion1234567890"; // TODO: Initialize to an appropriate value
				int len = appVersion->Length;
				target->GetVersion(appVersion, len);
				Assert::AreEqual(L"Version 10.0.0.0", appVersion);
			}
			/// <summary>
			///A test for GetVersion
			///</summary>
	public: [TestMethod]
			void GetVersionTestZeroLen()
			{
				BizInfo^  target = BizFacade::Instance()->FindBizInfo(); // TODO: Initialize to an appropriate value
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
				BizInfo^  target = BizFacade::Instance()->FindBizInfo(); // TODO: Initialize to an appropriate value
				String^ appVersion = L"1234567890"; // TODO: Initialize to an appropriate value
				int len = appVersion->Length;
				target->GetVersion(appVersion, len);
				Assert::AreEqual(L"Version 10", appVersion);
			}
			/// <summary>
			///A test for GetCoName
			///</summary>
	public: [TestMethod]
			void GetCoNameTest()
			{
				BizInfo^  target = BizFacade::Instance()->FindBizInfo(); // TODO: Initialize to an appropriate value
				String^ coName = L"blankCoName12345678901234567890"; // TODO: Initialize to an appropriate value
				int len = coName->Length;
				target->GetCompanyName(coName, len);
				Assert::AreEqual(L"AtCor Medical [THE PRODUCT] (R)", coName);
			}			/// <summary>
			/// <summary>
			///A test for GetCoName
			///</summary>
	public: [TestMethod]
			void GetCoNameTestZeroLen()
			{
				BizInfo^  target = BizFacade::Instance()->FindBizInfo(); // TODO: Initialize to an appropriate value
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
				BizInfo^  target = BizFacade::Instance()->FindBizInfo(); // TODO: Initialize to an appropriate value
				String^ coName = L"1234567890"; // TODO: Initialize to an appropriate value
				int len = coName->Length;
				target->GetCompanyName(coName, len);
				Assert::AreEqual(L"AtCor Medi", coName);
			}			
			/// <summary>
			///A test for GetCopyright
			///</summary>
	public: [TestMethod]
			void GetCopyrightTest()
			{
				BizInfo^  target = BizFacade::Instance()->FindBizInfo(); // TODO: Initialize to an appropriate value
				String^ copyRight = L"blank123456789012345678901234567890123456789012345678901234567"; // TODO: Initialize to an appropriate value
				int len = copyRight->Length;
				target->GetCopyright(copyRight, len);
				Assert::AreEqual(   L"Copyright (c) 2011 AtCor Medical Pty Ltd. All Rights Reserved.", copyRight);
			}
			/// <summary>
			///A test for GetCopyright
			///</summary>
	public: [TestMethod]
			void GetCopyrightTestTruncated()
			{
				BizInfo^  target = BizFacade::Instance()->FindBizInfo(); // TODO: Initialize to an appropriate value
				String^ copyRight = L"blank123456789012345678901234567890123456789012345678901"; // TODO: Initialize to an appropriate value
				int len = copyRight->Length;
				target->GetCopyright(copyRight, len);
				Assert::AreEqual(   L"Copyright (c) 2011 AtCor Medical Pty Ltd. All Rights Res", copyRight);
			}
			/// <summary>
			///A test for BizInfo Constructor
			///</summary>
	public: [TestMethod]
			void BizInfoConstructorTest()
			{
				BizInfo^  target = BizFacade::Instance()->FindBizInfo();
				Assert::AreNotEqual(nullptr, target);
			}
			/// <summary>
			///A test for GetModuleVersion
			///</summary>
public: [TestMethod]
		void GetModuleVersionTest()
		{
			String^  moduleVersion = L"blankVersion1234567890"; // TODO: Initialize to an appropriate value
			String^  moduleVersionExpected = L"0.1 (stub)"; // TODO: Initialize to an appropriate value
			int len = moduleVersion->Length; // TODO: Initialize to an appropriate value
			BizInfo::Instance()->GetModuleVersion(moduleVersion, len);
			Assert::AreEqual(moduleVersionExpected, moduleVersion);
		}
			/// <summary>
			///A test for GetModuleVersion
			///</summary>
public: [TestMethod]
		void GetModuleVersionTestTruncated()
		{
			String^  moduleVersion         = L"1234567"; // TODO: Initialize to an appropriate value
			String^  moduleVersionExpected = L"0.1 (st"; // TODO: Initialize to an appropriate value
			int len = moduleVersion->Length; // TODO: Initialize to an appropriate value
			BizInfo::Instance()->GetModuleVersion(moduleVersion, len);
			Assert::AreEqual(moduleVersionExpected, moduleVersion);
		}
		/// <summary>
		///A test for GetModuleType
		///</summary>
public: [TestMethod]
		void GetModuleTypeTest()
		{
			String^  moduleType = L"blankVersion1234567890"; // TODO: Initialize to an appropriate value
			String^  moduleTypeExpected = L"EM4 (stub)"; // TODO: Initialize to an appropriate value
			int len = moduleType->Length; // TODO: Initialize to an appropriate value
			BizInfo::Instance()->GetModuleType(moduleType, len);
			Assert::AreEqual(moduleTypeExpected, moduleType);
		}
		/// <summary>
		///A test for GetModuleType
		///</summary>
public: [TestMethod]
		void GetModuleTypeTestTruncated()
		{
			String^  moduleType         = L"12345678"; // TODO: Initialize to an appropriate value
			String^  moduleTypeExpected = L"EM4 (stu"; // TODO: Initialize to an appropriate value
			int len = moduleType->Length; // TODO: Initialize to an appropriate value
			BizInfo::Instance()->GetModuleType(moduleType, len);
			Assert::AreEqual(moduleTypeExpected, moduleType);
		}
		/// <summary>
		///A test for GetModuleSN
		///</summary>
public: [TestMethod]
		void GetModuleSNTest()
		{
			String^  moduleSN = L"blankVersion1234567890"; // TODO: Initialize to an appropriate value
			String^  moduleSNExpected = L"1234567890 (stub)"; // TODO: Initialize to an appropriate value
			int len = moduleSN->Length; // TODO: Initialize to an appropriate value
			BizInfo::Instance()->GetModuleSN(moduleSN, len);
			Assert::AreEqual(moduleSNExpected, moduleSN);
		}
		/// <summary>
		///A test for GetModuleSN
		///</summary>
public: [TestMethod]
		void GetModuleSNTestTruncated()
		{
			String^  moduleSN         = L"abcdefghijklm"; // TODO: Initialize to an appropriate value
			String^  moduleSNExpected = L"1234567890 (s"; // TODO: Initialize to an appropriate value
			int len = moduleSN->Length; // TODO: Initialize to an appropriate value
			BizInfo::Instance()->GetModuleSN(moduleSN, len);
			Assert::AreEqual(moduleSNExpected, moduleSN);
		}
		/// <summary>
		///A test for GetModuleConfigID
		///</summary>
public: [TestMethod]
		void GetModuleConfigIDTest()
		{
			unsigned short expected = 99; // TODO: Initialize to an appropriate value
			unsigned short actual;
			actual = BizInfo::Instance()->GetModuleConfigID();
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for GetModuleCalibrationDate
		///</summary>
public: [TestMethod]
		void GetModuleCalibrationDateTest()
		{
			CultureInfo^ culture = gcnew CultureInfo(CultureInfo::CurrentUICulture->ToString());
			String^  moduleCalibrationDate = L"1234567890123456789012"; // TODO: Initialize to an appropriate value
			String^  moduleCalibrationDateExpected = DateTime::Today.Date.ToString(culture); // TODO: Initialize to an appropriate value
			int len = moduleCalibrationDate->Length; // TODO: Initialize to an appropriate value
			BizInfo::Instance()->GetModuleCalibrationDate(moduleCalibrationDate, len);
			Assert::AreEqual(moduleCalibrationDateExpected, moduleCalibrationDate);
		}
		/// <summary>
		///A test for GetModuleCalibrationDate
		///</summary>
public: [TestMethod]
		void GetModuleCalibrationDateTestTruncated()
		{
			CultureInfo^ culture = gcnew CultureInfo(CultureInfo::CurrentUICulture->ToString());
			String^  moduleCalibrationDate = L"1234567"; // TODO: Initialize to an appropriate value
			String^  moduleCalibrationDateExpected = DateTime::Today.Date.ToString(culture)->Substring(0, 7); // TODO: Initialize to an appropriate value
			int len = moduleCalibrationDate->Length; // TODO: Initialize to an appropriate value
			BizInfo::Instance()->GetModuleCalibrationDate(moduleCalibrationDate, len);
			Assert::AreEqual(moduleCalibrationDateExpected, moduleCalibrationDate);
		}
			/// <summary>
			///A test for GetModuleConfigName
			///</summary>
public: [TestMethod]
		void GetModuleConfigNameTest()
		{
			String^  moduleConfigName         = L"blankVersion1234567890"; // TODO: Initialize to an appropriate value
			String^  moduleConfigNameExpected = L"Invalid Config"; // TODO: Initialize to an appropriate value
			int len = moduleConfigName->Length; // TODO: Initialize to an appropriate value
			BizInfo::Instance()->GetModuleConfigName(moduleConfigName, len);
			Assert::AreEqual(moduleConfigNameExpected, moduleConfigName);
			DalFacade::Instance()->FindModuleInfo()->moduleConfigID = 1;
			moduleConfigNameExpected = L"PWV"; // TODO: Initialize to an appropriate value
			BizInfo::Instance()->GetModuleConfigName(moduleConfigName, len);
			Assert::AreEqual(moduleConfigNameExpected, moduleConfigName);
		}
			/// <summary>
			///A test for GetModuleConfigName
			///</summary>
public: [TestMethod]
		void GetModuleConfigNameTestTruncated()
		{
			String^  moduleConfigName         = L"12"; // TODO: Initialize to an appropriate value
			String^  moduleConfigNameExpected = L"In"; // TODO: Initialize to an appropriate value
			int len = moduleConfigName->Length; // TODO: Initialize to an appropriate value
			DalFacade::Instance()->FindModuleInfo()->moduleConfigID =255;
			BizInfo::Instance()->GetModuleConfigName(moduleConfigName, len);
			Assert::AreEqual(moduleConfigNameExpected, moduleConfigName);
		}
		/// <summary>
		///A test for GetModuleConfigDate
		///</summary>
public: [TestMethod]
		void GetModuleConfigDateTest()
		{
			CultureInfo^ culture = gcnew CultureInfo(CultureInfo::CurrentUICulture->ToString());
			String^  moduleConfigDate = L"1234567890123456789012"; // TODO: Initialize to an appropriate value
			String^  moduleConfigDateExpected = DateTime::Today.Date.ToString(culture); // TODO: Initialize to an appropriate value
			int len = moduleConfigDate->Length; // TODO: Initialize to an appropriate value
			BizInfo::Instance()->GetModuleConfigDate(moduleConfigDate, len);
			Assert::AreEqual(moduleConfigDateExpected, moduleConfigDate);
		}
		/// <summary>
		///A test for GetModuleConfigDate
		///</summary>
public: [TestMethod]
		void GetModuleConfigDateTestTruncated()
		{
			CultureInfo^ culture = gcnew CultureInfo(CultureInfo::CurrentUICulture->ToString());
			String^  moduleConfigDate = L"1234567"; // TODO: Initialize to an appropriate value
			String^  moduleConfigDateExpected = DateTime::Today.Date.ToString(culture)->Substring(0, 7); // TODO: Initialize to an appropriate value
			int len = moduleConfigDate->Length; // TODO: Initialize to an appropriate value
			BizInfo::Instance()->GetModuleConfigDate(moduleConfigDate, len);
			Assert::AreEqual(moduleConfigDateExpected, moduleConfigDate);
		}
};
}
namespace TestBiz {
    
}
