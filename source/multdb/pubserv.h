#ifndef MULTDB_PUBSERV
#define MULTDB_PUBSERV

#include <inc\std.h>
#include <Db.hpp>
#include <DBTables.hpp>

bool        multdb_initialise(void);
void        multdb_destroy(void);
void        multdb_show_form(void);
AnsiString  multdb_get_active_name(void);
void        multdb_set_delete_status(bool status);
bool        multb_merge_database_tables(TADOTable  *tbl_patient,
                                        TADOTable  *tbl_meas_pwa,
                                        TADOTable  *tbl_meas_pwv);
bool        multdb_pack(void);
#endif
