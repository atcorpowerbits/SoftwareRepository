// CrxConfiguration.cpp : main project file.

#include "stdafx.h"
#include "CrxConfiguration.h"

using namespace System;// For String, Console
using namespace System::Xml;// For XML classes and enums
using namespace System::IO;// For FileStream

using namespace AtCor::Scor::CrossCutting::Configuration;

//To get General Default Settings from file
void CrxConfigManager::GetGeneralDefaultSettings()
{
	CrxConfigManager::GetSettings("GENERAL","DEFAULT");
}

//To get User Settings from the file
void CrxConfigManager::GetGeneralUserSettings()
{
	CrxConfigManager::GetSettings("GENERAL","USER");
}

//To Set General User Setting 
void CrxConfigManager::SetGeneralUserSettings(CrxStructGeneralSetting^ gs)
{
	CrxConfigManager::SetSettings("GENERAL","USER",gs);
}

//Set data in the file as per Section and Subsection
void CrxConfigManager::SetSettings(String^ Section, String^ SubSection, CrxStructGeneralSetting^ gs)
{
	//Variables Declaration
	File^ CheckFile = nullptr;//Contains Fileinfo, Set it to null
	FileStream^ fs = nullptr;//Contains FileAccessinfo, Set it to null
	XmlReader^ reader = nullptr;//contains the XML data, Set it to null
	XmlDocument^ doc = nullptr;//Contains the XML document, Set it to null
	XmlNode^ node = nullptr;//Contains node list, Set it to null
	XmlNode^ node1 = nullptr;//Contains node list, Set it to null
	XmlNode^ node2 = nullptr;//Contains node list, Set it to null
	XmlNode^ node3 = nullptr;//Contains node list, Set it to null
	XmlNode^ node4 = nullptr;//Contains node list, Set it to null
	bool startflag = false; //bool value containinf true or false
	String^ path = nullptr;//Set the path string value to null

	try
	{
        path = Directory::GetCurrentDirectory();

		//Check whether file is exists or not
		if(!CheckFile->Exists(_nameOfFile))
		{
			throw gcnew ConfigException(100); // File not found
		}		

		//Set to Null value 
		CheckFile = nullptr;
		
		try
		{
			fs = gcnew FileStream(_nameOfFile,FileMode::Open);
		}
		catch(Exception^)
		{
			throw gcnew ConfigException(102); // File not accessable
		}

		//Check whether have the access or not
		if(!fs->CanWrite)
		{
			throw gcnew ConfigException(102); // File not accessable
		}
		
		//Close the file Access Object
		fs->Close();
        fs = nullptr;

		//Read the XML file from the provided path
		reader = XmlReader::Create(_nameOfFile);

		//Create the doc object
		doc = gcnew XmlDocument();

		//Load the XML data from reader to the doc
		doc->Load(reader);
		
		//Close the XML reader data
		reader->Close();
        reader = nullptr;
		
		// get the nodes collection from the file
		node = doc->DocumentElement;

		if (node == nullptr)
		{
			throw gcnew ConfigException(101);
		}
		
		//Processes each node for values
		for each(node1 in node->ChildNodes)
		{
			for each (node2 in node1->ChildNodes)
			{
				 if (node2->Name->ToUpper() == Section)
				 {
					for each (node3 in node2->ChildNodes)
					 {
						if (node3->Name->ToUpper() == SubSection)
						{
							for each (node4 in node3->ChildNodes)
							 {
								startflag = true;
							    if (node4->Name->ToUpper() == "PATIENTPRIVACY")
								{	
									if(gs->PatientPrivacy == false)
									{
										node4->InnerText = "No";								
									}
									else
									if(gs->PatientPrivacy == true)
									{
										node4->InnerText = "Yes";
									}
									else
									{
										throw gcnew ConfigException(101);
									}
								 }
							    else
							    if (node4->Name->ToUpper() == "HEIGHTANDWEIGHTUNITS")
								{	
									if(gs->HeightandWeightUnit == 0)
									{
										node4->InnerText = "Metric";								
									}
									else
									if(gs->HeightandWeightUnit == 1)
									{
										node4->InnerText = "Imperial";
									}
									else
									{
										throw gcnew ConfigException(101);
									}
								 }
							    else
								if (node4->Name->ToUpper() == "BLOODPRESSUREENTRYOPTIONS")
								{	
									if(gs->BloodPressureEntryOptions == 0)
									{
										node4->InnerText = "SP and DP";								
									}
									else
									if(gs->BloodPressureEntryOptions == 1)
									{
										node4->InnerText = "SP and MP";
									}
									else
									if(gs->BloodPressureEntryOptions == 2)
									{
										node4->InnerText = "MP and DP";
									}
									else
									{
										throw gcnew ConfigException(101);
									}
								 }
								 else
								 if(node4->Name->ToUpper() == "COMMSPORT")
								 {
                                    if(gs->CommsPort != nullptr) 
                                    {
                                        node4->InnerText = gs->CommsPort;
                                    }
                                    else 
                                    {
                                         node4->InnerText = " "; 
                                    }
								 }
								 else
								 if(node4->Name->ToUpper() == "REPORTTITLE")
								 {									
                                    if(gs->ReportTitle != nullptr) 
                                    {
                                        node4->InnerText = gs->ReportTitle;
                                    }
                                    else 
                                    {
                                         node4->InnerText = " "; 
                                    }
								 }
								 else
								 if(node4->Name->ToUpper() == "REPORTLOGOPATH")
								 {
									if(gs->ReportLogoPath != nullptr) 
                                    {
                                        node4->InnerText = gs->ReportLogoPath;
                                    }
                                    else 
                                    {
                                         node4->InnerText = " "; 
                                    }
								 }
								 else
								 {
									throw gcnew ConfigException(101);//corrupt file
								 }
							 }
						  }
					 }
				}
			}		  
		}
		if (startflag == false)
		{
			throw gcnew ConfigException(101);//corrupt file
		}
		doc->Save(_nameOfFile);	

	}
	catch (XmlException^) 
	{
		throw gcnew ConfigException(101); // any xml exception is rethrown as corrupt file exception
	}
	finally 
	{
		//Close the file Access Object
		if(fs)
		{
			fs->Close();
		}

		if (reader && (reader->ReadState != ReadState::Closed)) 
		{
			reader->Close();
		}		
	}
}

//Get data from the file as per Section and Subsection
void CrxConfigManager::GetSettings(String^ Section, String^ SubSection)
{
	bool breakflag = false; //bool value containing true or false. True to break the loop
	bool startflag = false; //bool value containing true or false. True to Start to store
	XmlReader^ reader = nullptr;//Store the XML data
	File^ CheckFile = nullptr; //Contains Fileinfo
	String^ GetXMLSection = nullptr;//Gets the XML section name
	String^ GetSectionName = nullptr;//Store section name to get the value

	try 
	{
		//Check whether file is exists or not
		if(!CheckFile->Exists(_nameOfFile))
		{
			throw gcnew ConfigException(100); // File not found
		}

		//Set to Null value 
		CheckFile = nullptr;
		
		//Reads the XML data from filepath and store in reader object
		reader = XmlReader::Create(_nameOfFile); 

		//Get in the loop in each node to get values
		while (reader->Read()) 
		{
			switch (reader->NodeType) 
			{
				case XmlNodeType::Comment:
					break;

				case XmlNodeType::Element: 
					GetXMLSection = reader->Name->ToUpper();

                    if((GetXMLSection != "CONFIGURATION") && (GetXMLSection != "SYSTEMSETTING") && (GetXMLSection != "GENERAL") 
                        && (GetXMLSection != "USER") && (GetXMLSection != "PATIENTPRIVACY") && (GetXMLSection != "HEIGHTANDWEIGHTUNITS") 
                        && (GetXMLSection != "BLOODPRESSUREENTRYOPTIONS") && (GetXMLSection != "COMMSPORT") && (GetXMLSection != "REPORTTITLE") 
                        && (GetXMLSection != "REPORTLOGOPATH") && (GetXMLSection != "DEFAULT")) 
                    {
                        throw gcnew ConfigException(101); //corrupt file
                    }
 
					if(GetXMLSection == Section) 
					{
						GetSectionName = reader->Name->ToUpper();
					}

					if(GetSectionName == Section && reader->Name->ToUpper() == SubSection) 
					{
						startflag = true;
					}
				 
					if (reader->HasAttributes) 
					{
						while (reader->MoveToNextAttribute()) 
						{
						
						}
						reader->MoveToElement();
					}
                    if (reader->IsEmptyElement) 
					{
						throw gcnew ConfigException(101); //corrupt file
					}
					break; 

				case XmlNodeType::EndElement: 
				
					if(GetSectionName == Section && reader->Name->ToUpper() == SubSection) 
					{
						breakflag = true; 
					}
					break; 

				case XmlNodeType::Text: 
				
				if(startflag == true)
				{
					if (GetSectionName = "GENERAL")
					{
						//Get the Patient Privacy Details
						if(GetXMLSection == "PATIENTPRIVACY")
						{
							if(reader->Value->ToUpper() == "NO")
							{
								_instance->_generalSettings->PatientPrivacy = false;
							}
							else 
							if(reader->Value->ToUpper() == "YES")
							{
								_instance->_generalSettings->PatientPrivacy = true;
							}
							else
							{
								throw gcnew ConfigException(101);//corrupt file
							}
							break;
						}
						//Get the Height and Weight Details
						else if(GetXMLSection == "HEIGHTANDWEIGHTUNITS")
						{
							if(reader->Value->ToUpper() == "METRIC")
							{
								_instance->_generalSettings->HeightandWeightUnit = 0;
							}
							else 
							if(reader->Value->ToUpper() == "IMPERIAL")
							{
								_instance->_generalSettings->HeightandWeightUnit = 1;
							}
							else
							{
								throw gcnew ConfigException(101);//corrupt file
							}
							break;
						}
						//Get the Blood Pressure Entry Options
						else if(GetXMLSection == "BLOODPRESSUREENTRYOPTIONS")
						{
							if(reader->Value->ToUpper() == "SP AND DP")
							{
								_instance->_generalSettings->BloodPressureEntryOptions = 0;
							}
							else 
							if(reader->Value->ToUpper() == "SP AND MP")
							{
								_instance->_generalSettings->BloodPressureEntryOptions = 1;
							}
							else 
							if(reader->Value->ToUpper() == "MP AND DP")
							{
								_instance->_generalSettings->BloodPressureEntryOptions = 2;
							}
							else
							{
								throw gcnew ConfigException(101);//corrupt file
							}
							break;
						}
						//Get the Comms Port information
						else if(GetXMLSection == "COMMSPORT")
						{
							if(SubSection == "USER")
							{
								_instance->_generalSettings->CommsPort = reader->Value;
							}
							else if (SubSection == "DEFAULT")
							{
								_instance->_generalSettings->CommsPort = nullptr;
							}	
							else
							{
								throw gcnew ConfigException(101);//corrupt file
							}
							
							break;
						}
						//Gets the report title from the XML
						else if(GetXMLSection == "REPORTTITLE")
						{
							if(SubSection == "USER")
							{
								_instance->_generalSettings->ReportTitle = reader->Value;
							}
							else if (SubSection == "DEFAULT")
							{
								_instance->_generalSettings->ReportTitle = nullptr;
							}
							else
							{
								throw gcnew ConfigException(101);//corrupt file
							}
							break;
						}
						//Get the Report Logo Path
						else if(GetXMLSection == "REPORTLOGOPATH")
						{
							if(SubSection == "USER")
							{
								_instance->_generalSettings->ReportLogoPath = reader->Value;
							}
							else if (SubSection == "DEFAULT")
							{
								_instance->_generalSettings->ReportLogoPath = nullptr;
							}
							else
							{
								throw gcnew ConfigException(101);//corrupt file
							}
							break;
						}					  
						else
						{
							throw gcnew ConfigException(101);//corrupt file
						}
					}
				}				
				
				break; 

				case XmlNodeType::XmlDeclaration: 
				
					if (reader->HasAttributes) 
					{
						while (reader->MoveToNextAttribute()) 
						{
							
						}
					}
					reader->MoveToElement();
				break; 

				case XmlNodeType::Whitespace: 
				
				break; 

				default: 
					throw gcnew ConfigException(); //Unknown error with zero error code
			}
			if (breakflag) 
			{
				break; 
			}
		}
			
	}
	catch (XmlException^) 
	{
		throw gcnew ConfigException(101); // any xml exception is rethrown as corrupt file exception
	}
	
	finally 
	{
		if (reader && (reader->ReadState != ReadState::Closed)) 
		{
			reader->Close();
		}
	}
}
