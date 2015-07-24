/*
 *  limits.h    Machine and OS limits
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _LIMITS_H_INCLUDED

#define CHAR_BIT        8
#ifdef __CHAR_SIGNED__
 #define CHAR_MIN        (-128)
 #define CHAR_MAX        127
#else
 #define CHAR_MIN        0
 #define CHAR_MAX        255
#endif
#define MB_LEN_MAX      1
#define SCHAR_MAX       127
#define SCHAR_MIN       (-128)
#define UCHAR_MAX       255U
#define SHRT_MAX        32767
#define SHRT_MIN        (-32767-1)
#define USHRT_MAX       65535U
#ifdef __386__
 #define INT_MAX         2147483647
 #define INT_MIN         (-2147483647-1)
 #define UINT_MAX        4294967295U
#else
 #define INT_MAX         32767
 #define INT_MIN         (-32767-1)
 #define UINT_MAX        65535U
#endif
#define LONG_MAX        2147483647
#define LONG_MIN        (-2147483647-1)
#define ULONG_MAX       4294967295U

#define TZNAME_MAX  30              /*  The maximum number of bytes         */
                                    /*  supported for the name of a time    */
                                    /*  zone (not of the TZ variable).      */

#define _LIMITS_H_INCLUDED
#endif
