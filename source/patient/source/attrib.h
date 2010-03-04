/*
**
** Copyright (C) PWV MEDICAL PTY LTD, 1998
**
**
** FILE NAME     : PATIENT\ATTRIB.H
**
** PROJECT       : TITAN SWCI
**
** OBJECT        : PATIENT
**
** DESCRIPTION   : Definition of objects attributes.
**
** AUTHOR        : Peter Harpas
**
** DATE CREATED  : 19/05/98
**
*/
#ifndef PATIENT_ATTRIB
#define PATIENT_ATTRIB
#include <vcl/db.hpp>

#include <patient/pubtype.h>

class Patient_Data_Event_Class
{
   public:
      void __fastcall validate_record(TDataSet *DataSet);
      void __fastcall validate_field(TField *Field);
      void __fastcall record_changed(TObject *Sender,
                                     TField  *Field);
      void __fastcall state_changed(TObject *Sender);
      void __fastcall search_changed(TObject *Sender,
                                     TField  *Field);
};

extern COUNT                patient_nof_measure;

extern PATIENT_RECORD_TYPE  patient_active;

#endif
