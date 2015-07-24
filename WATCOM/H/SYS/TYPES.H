/*
 *  sys/types.h
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _TIME_T_DEFINED_
typedef unsigned long time_t;	/* time value */
#define _TIME_T_DEFINED_
#endif

#ifndef _TYPES_H_INCLUDED

typedef unsigned short ino_t;	/* i-node # type */
typedef short dev_t;		/* device code (drive #) */
typedef long  off_t;		/* file offset value */

#define _TYPES_H_INCLUDED
#endif
