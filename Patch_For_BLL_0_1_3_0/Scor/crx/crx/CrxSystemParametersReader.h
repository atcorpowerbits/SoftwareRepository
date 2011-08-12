#include "stdafx.h"
#include "ScorException.h"

using namespace System;
using namespace System::Xml::Linq;
using namespace AtCor::Scor::CrossCutting;

namespace AtCor { 
	namespace Scor { 
		namespace CrossCutting { 
			namespace Configuration {

public ref class CrxSytemParameters
{
private:
	XElement^ parameters; //points to the XML file, specifically the topmost XML tag. Do not change this value.
	XElement^ parentElement; //Holds the current tag vaue. This is used as a temporary variable.
	 
	 static CrxSytemParameters^ _instance = gcnew CrxSytemParameters(); //Singleton pointer
	 	 
	 CrxSytemParameters(); //Contructor

	 //Overloaded copy constructor to implement singleton
	 CrxSytemParameters(CrxSytemParameters^); 

	 //overloaded assignment operator. made private to implement singleton
	 CrxSytemParameters^ operator= (CrxSytemParameters);

	 //base method that extracts the actual value of the XML file
	 //this does the actual work
	 String^ GetNestedTagValue(String^ nestedTags);

	
public:

	/**
	* Returns the current singleton instance.
	*/
	static property CrxSytemParameters^ Instance
	{
		CrxSytemParameters^ get()
		{
			return CrxSytemParameters::_instance;
		};
	};
	

	/**
	* Gets the value of the specified tag as an integer.
	* 
	* @param[in] The name of the tag whose value is required. @n
	*				The string must be in a @c "ParenTag.ChildTag" format,
	*				excluding the "Parameters" tag. 
	* @return The value of the tag if it is an integer. 
	* @warning	Ensure that the Tag has a numeric value before callig this.
	*			Throws an exception if the tag value cannot be converted to integer.
	*/
	 int GetIntegerTagValue(String^ tagName);

	/**
	* Gets the value of the specified tag as an string.
	* 
	* @param[in] The name of the tag whose value is required. @n
	*				The string must be in a @c "ParenTag.ChildTag" format,
	*				excluding the "Parameters" tag. 
	* @return The value of the tag. 
	*/
	 String^ GetStringTagValue(String^ tagName);
};

			}
		}
	}
}
