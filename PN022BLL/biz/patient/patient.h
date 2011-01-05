/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	patient.h
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Business Logic Layer Patient Class
*/

#pragma once
#include <biz_namespace.h>
#include <biz.h>
#include <biz_constants.h>

using namespace System;

START_BIZ_NAMESPACE
public ref class BizPatient
{
public:
	static BizPatient^ BizPatient::Instance();

	property unsigned int		systemId;			// Customer System ID
	property unsigned int		patientNumber;		// Internal patient number

	property unsigned int		groupStudyId;		// Internal group/study ID
	property String^			patientId;			// User defined patient ID
	property String^			lastName;			// User defined last name
	property String^			firstName;			// User defined first name
	property String^			gender;				// User defined gender
	property DateTime			dateOfBirth;		// User defined date of birth
	
	/* CFR11 data members
	property String^    		operatorId;			// Operator Id
	property String^			reasonForChange;	// notes for changing this patient
	property auditChangeType	auditChange;		// The type of change to this patient
	property DateTime			auditDateTime;		// The date and time of the change to this patient
	*/

	void Initialise();
protected:
	BizPatient(void);
private:
	static BizPatient^ _instance;
};
END_BIZ_NAMESPACE
