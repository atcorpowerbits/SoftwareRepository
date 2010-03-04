/*
**
** Copyright (C) PWV MEDICAL PTY LTD, 1998
**
**
** FILE NAME     : DBMGR\PUBTYPE.H
**
** PROJECT       : S32 SWCI
**
** OBJECT        : DBMGR (Database Manager)
**
** DESCRIPTION   : Definition of objects Public types.
**
** AUTHOR        : Peter Harpas
**
** DATE CREATED  : 28/04/98
**
*/
#ifndef DBMGR_PUBTYPE
#define DBMGR_PUBTYPE
#include <inc/std.h>

const String DBMGR_DATABASE_NAME =  "SCOR.xyz";//"SCOR.ACCDB" - Access 2007;
const String DBMGR_OLD_DATABASE_NAME =  "SCOR.mdb";//"SCOR.ACCDB" - Access 2007;
const String DBMGR_PRE_DATABASE_NAME =  "PRE_V82_SCOR.mdb";
const String DBMGR_PRE_PACK_DATABASE_NAME =  "PRE_PACK_SCOR.xyz";
const String DBMGR_PACK_DATABASE_NAME =  "SCOR_PACK.xyz";

/*
** The identifiers to use for the different databases the Database
** Manager object can manage.
*/
typedef enum
{
   DBMGR_PATIENT_TABLE = 1,
   DBMGR_MEASURE_PWA_TABLE,
   DBMGR_MEASURE_PWV_TABLE,
   DBMGR_MEASURE_PWM_TABLE,
   DBMGR_MEASURE_PWM_TREND_TABLE,
   DBMGR_MEASURE_PWM_SESSION_TABLE,
   DBMGR_DEVICE_TABLE,
   DBMGR_MEASURE_HRV_TABLE,
   DBMGR_PATIENT_AUDIT_TABLE,
   DBMGR_MEASURE_PWA_AUDIT_TABLE,
   DBMGR_MEASURE_PWV_AUDIT_TABLE,
   DBMGR_LAST_TABLE,
   DBMGR_PATIENT_QUERY,
   DBMGR_MEASURE_PWA_QUERY,
   DBMGR_MEASURE_PWV_QUERY,
   DBMGR_MEASURE_PWM_QUERY,
   DBMGR_MEASURE_PWM_TREND_QUERY,
   DBMGR_MEASURE_PWM_SESSION_QUERY,
   DBMGR_MEASURE_HRV_QUERY,
   DBMGR_PATIENT_AUDIT_QUERY,
   DBMGR_MEASURE_PWA_AUDIT_QUERY,
   DBMGR_MEASURE_PWV_AUDIT_QUERY,
} DBMGR_ID_TYPE;

/*
** The identifiers to use for the different queries the Database
** Manager can perform.
*/
typedef enum
{
   DBMGR_QUERY_KEY = 1,
   DBMGR_QUERY_DATETIME,
   DBMGR_QUERY_PATIENT_NUMBER,
   DBMGR_QUERY_PATIENT_SEARCH,
   DBMGR_QUERY_AUDIT,
   DBMGR_QUERY_AUDIT_FLAG
} DBMGR_QUERY_TYPE;

#define DBMGR_FIELD_LEN_MAX  80
#define DBMGR_EXPRESSION_LEN 40
#define DBMGR_FILE_NAME_LEN   9
#define DBMGR_FIELD_NAME_LEN  10

/*
** This defines the different field types associated with the database.
*/
typedef enum
{
   DBMGR_CHAR = 1,
   DBMGR_NUMERIC,
   DBMGR_DATE,
   DBMGR_LOGICAL,
   DBMGR_MEMO
} DBMGR_FIELD_TYPE;

#endif
