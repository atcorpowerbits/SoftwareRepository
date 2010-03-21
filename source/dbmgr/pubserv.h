/*
**
** Copyright (C) PWV MEDICAL PTY LTD, 1998
**
**
** FILE NAME     : DBMGR\PUBSERV.H
**
** PROJECT       : S32 SWCI
**
** OBJECT        : DBMGR (Database Manager)
**
** DESCRIPTION   : Definition of objects Public services.
**
** AUTHOR        : Peter Harpas
**
** DATE CREATED  : 28/04/98
**
*/
#ifndef DBMGR_PUBSERV
#define DBMGR_PUBSERV
#include <Db.hpp>
#include <DBTables.hpp>
#include <ADOdb.hpp>
#include <dbmgr/pubtype.h>

//extern "C"
//{
/*
** This service initialises the Database Manager object's internal data
** structures and must be invoked before any other service of the
** Database Manager object.
**
** A status value is returned to indicate the success, or otherwise, of the
** initialisation.
*/
bool dbmgr_initialise(void);

/*
** This service releases all resources which have been allocated by the
** Database Manager object.
**
** After invoking this service, `dbmgr_initialise' must be invoked before any
** other use may be made of the Database Manager object.
*/
void dbmgr_destroy(void);

/*
** This service opens the database specified by 'id'.
**
** A status value is returned to indicate the success of opening the database.
**
*/
bool dbmgr_open(DBMGR_ID_TYPE  id, bool is_copy);

/*
** This service closes an already open database file specified by 'id'.
** In addition any corresponding index file or memo file which was opened
** when the database file was opened will automatically be closed.
**
** A status value is returned to indicate the success of closing the database
** and associated files.
*/
bool dbmgr_close(DBMGR_ID_TYPE  id, bool is_copy);

bool dbmgr_activate_database_set(AnsiString the_path, bool is_copy);

bool dbmgr_disconnect_database_set(bool is_copy);

bool dbmgr_select_index(DBMGR_ID_TYPE  id,
                        AnsiString     idx_name);

bool dbmgr_reindex(DBMGR_ID_TYPE  id);
                        
/*
** This service indicates whether the database specified by 'id' is open.
**
** A status value of TRUE is returned to indicate that the database is
** open otherwise FALSE is returned.
*/
bool dbmgr_is_open(DBMGR_ID_TYPE  id, bool is_copy);

/*
** This service returns a pointer to the table associated with the database
** specified by 'id'.
**
** If no table is associated with the database a NULL pointer is returned.
**
** Objects calling this service must check the returned value of the pointer
** before using it. Objects must not free this pointer.
*/
TDataSet *dbmgr_get_dataset(DBMGR_ID_TYPE id, bool is_copy);

/*
** This service returns a pointer to the data source associated with the
** database specified by 'id'.
**
** If no data source is associated with the database a NULL pointer
** is returned.
**
** Objects calling this service must check the returned value of the pointer
** before using it. Objects must not free this pointer.
*/
TDataSource *dbmgr_get_data_source(DBMGR_ID_TYPE id, bool is_copy);

TADOQuery *dbmgr_setup_query(DBMGR_ID_TYPE    id,
                          DBMGR_QUERY_TYPE qry_type,
                          String           field_name1,
                          String           field_name2,
                          String           field_name3,
                          String           value1,
                          String           value2,
                          String           value3);

TADOQuery *dbmgr_setup_query(DBMGR_ID_TYPE     id,
                          DBMGR_QUERY_TYPE  qry_type,
                          String            field_name1,
                          String            field_name2,
                          String            field_name3,
                          String            field_name4,
                          String            value1,
                          String            value2,
                          String            value3,
                          String            value4);

// The following queries allow the order to be specified
TADOQuery *dbmgr_setup_query(DBMGR_ID_TYPE    id,
                          DBMGR_QUERY_TYPE qry_type,
                          String           field_name1,
                          String           field_name2,
                          String           field_name3,
                          String           value1,
                          String           value2,
                          String           value3,
                          String           order);

TADOQuery *dbmgr_setup_query(DBMGR_ID_TYPE     id,
                          DBMGR_QUERY_TYPE  qry_type,
                          String            field_name1,
                          String            field_name2,
                          String            field_name3,
                          String            field_name4,
                          String            value1,
                          String            value2,
                          String            value3,
                          String            value4,
                          String            order);

bool dbmgr_conversion(TLabel* status, AnsiString the_path);

bool dbmgr_perform_simple_activation(AnsiString the_path, bool is_copy);

//};
#endif
