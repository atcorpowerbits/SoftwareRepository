//---------------------------------------------------------------------------
#include <vcl.h>
#include <sysutils.hpp>
#pragma hdrstop

#include <ctype.h>
#include <inc/std.h>
#include "utils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

bool emma_is_space_available(UTINY  drive, VLONG size)
{
   VLONG  available_space;
   bool   is_enough = false;

   available_space = emma_get_disk_space(drive);
   if (available_space > size)
   {
      is_enough = true;
   }
   return (is_enough);
}

bool emma_is_space_available(UTINY  drive, AnsiString file_path)
{
   VLONG        available_space;
   ULONG       size;
   TSearchRec  sr;
   bool       is_enough = false;

   available_space = emma_get_disk_space(drive);

   if (FindFirst(file_path, faAnyFile, sr) == 0)
   {
      size = sr.Size;

      if (available_space > size)
      {
         is_enough = true;
      }
      FindClose(sr);
   }
   return (is_enough);
}

VLONG  emma_get_disk_space(UTINY drive)
{
   UINT8       drive_num;
   VLONG       available_space;

   drive_num = (UINT8)(toupper(drive) - 'A' + 1);
   available_space = DiskFree(drive_num);

   if (available_space == -1)
   {
      available_space = 0;
   }
   return (VLONG)(available_space);
}

ULONG emma_get_file_size(AnsiString file_path)
{
   ULONG      size = 0;
   TSearchRec  sr;

   if (FindFirst(file_path, faAnyFile, sr) == 0)
   {
      size = (ULONG)(sr.Size);
      FindClose(sr);
   }
   return (size);
}

AnsiString emma_build_country_date(AnsiString  day_str,
                                   AnsiString  month_str,
                                   AnsiString  year_str)
{
   AnsiString  country_date;

   country_date = day_str +String(DateSeparator) + month_str +String(DateSeparator) +year_str;
   return (country_date);

}

void emma_set_date_formats(void)
{
   if (DateSeparator == ' ')
   {
      DateSeparator = '/';
   }
   ShortDateFormat = "dd" +String(DateSeparator) +"mm" +String(DateSeparator) +"yyyy";
   LongDateFormat = "MMMM dd, yyyy";
   // PM V9
   Application->UpdateFormatSettings = false;
}


