#ifndef EMMA_PUBSERV_UTILS
#define EMMA_PUBSERV_UTILS


#include <inc/std.h>


const String RELEASE_SOFTWARE_VERSION_LONG = "9 (AGSM Prototype)";
const String RELEASE_SOFTWARE_VERSION = "9 (AGSM)";

const String SOFTWARE_MODEL_TYPE = "SCOR-CvMS";
const String SOFTWARE_HELP_FILE = "scorcvms.hlp";
const String SOFTWARE_DEFAULT_REPORT_TITLE = "SphygmoCor";
// PM V9
// Global Colours
const TColor sphygmocor_green = (TColor)(0x00004000);
const TColor sphygmocor_lime = clLime;
const TColor sphygmocor_yellow = clYellow;
const TColor sphygmocor_red = (TColor)(0x002D1EBE);
const TColor sphygmocor_white = clWhite;
const TColor sphygmocor_background = (TColor)(0x00BA968E);
const TColor sphygmocor_navy = (TColor)(0x0091312E);
const TColor sphygmocor_black = clBlack;
const TColor sphygmocor_grey = clGray; //(TColor)(0x00B3B3B3);
const TColor sphygmocor_pink = (TColor)(0x008080FF);
const TColor sphygmocor_maroon = clMaroon;
const TColor sphygmocor_orange = (TColor)(0x004080FF);

bool emma_is_space_available(UTINY  drive, UCOUNT size);

bool emma_is_space_available(UTINY  drive, AnsiString file_path);

VLONG  emma_get_disk_space(UTINY drive);

ULONG emma_get_file_size(AnsiString file_path);

AnsiString emma_build_country_date(AnsiString  day_str,
                                   AnsiString  month_str,
                                   AnsiString  year_str);

void emma_set_date_formats(void);                                   

#endif
