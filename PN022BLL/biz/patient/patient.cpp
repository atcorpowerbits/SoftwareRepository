/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	patient.cpp
	
	Author       :  Paul McBryde

    Description  :	Business Logic Layer Patient Class
*/

#include "StdAfx.h"
#include "patient.h"

START_BIZ_NAMESPACE

/**
 Constructor()
 
 DESCRIPTION:
 
 Constructor for patient class.

 INPUT:
 
 none.

 OUTPUT:
 
 none.

 RETURN:
 
 none.

*/
BizPatient::BizPatient(void)
{
	Initialise();
}

/**
Instance

DESCRIPTION

	Get the BizPatient singleton instance.

INPUT

	none.

OUTPUT

	None.

RETURN

	BizPatient^ - Handle to BizPatient object

*/
BizPatient^ BizPatient::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew BizPatient;
	}
	return _instance;
}

/**
 Initialise()
 
 DESCRIPTION:
 
 Initialse the members of the patient class.

 INPUT:
 
 none.

 OUTPUT:
 
 none.

 RETURN:
 
 none.

*/
void BizPatient::Initialise(void)
{
	// TBD: systemId will be decrypted from the Key
	systemId = 0;
	patientNumber = 0;                          
	groupStudyId = "";
	patientId = "";
	lastName = "";
	firstName = "";
	gender = "";
	dateOfBirth = BizConstants::PATIENT_INITIAL_DATE;		
}
END_BIZ_NAMESPACE
