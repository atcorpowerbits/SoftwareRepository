/*
** FILE NAME     : INC\STD.H
** 
** PROJECT       : S32 SWCI
**
** OBJECT        : Standard Header
**
** DESCRIPTION   : Standard header file defines global data and data typedef.
**
** AUTHOR        : Peter C. Harpas
**
** 
*/
#ifndef STD_DEF
#define STD_DEF

/*
** VAR_EXPORT is used as a place holder within *.c, .cpp  files to indicate
** that the variable following is used within other *.c, .cpp files and has
** an "extern" definition in a *.h file.
** Note that "VAR_EXPORT" macro replaces to "".
*/
#define VAR_EXPORT

/*
** These types define the basic C data types to be used in the S32 system.
*/
typedef signed char     INT8;   /* signed integer using exactly 8 bits    */
typedef unsigned char   UINT8;  /* unsigned integer using exactly 8 bits  */
typedef signed short    INT16;  /* signed integer using exactly 16 bits   */
typedef unsigned short  UINT16; /* unsigned integer using exactly 16 bits */
typedef signed int      INT32;  /* signed integer using exactly 32 bits   */
typedef unsigned int    UINT32; /* unsigned integer using exactly 32 bits */

typedef signed char     TINY;   /* signed integer for range -128..127 */
typedef unsigned char   UTINY;  /* unsigned integer for range 0..255  */
typedef signed short    COUNT;  /* signed integer for range -32768..32767 */
typedef unsigned short  UCOUNT; /* unsigned integer for range 0..65535    */

#ifndef __WINDOWS_H
   typedef signed long    LONG;
   typedef unsigned char  BYTE;
   typedef char           CHAR;
   typedef unsigned char  UCHAR;
#endif

typedef __int64        VLONG;
typedef unsigned long  ULONG;
typedef float          REAL;   /* signed real number            */
typedef double         LREAL;  /* large signed real number      */
typedef long double    VLREAL; /* very large signed real number */

#endif
