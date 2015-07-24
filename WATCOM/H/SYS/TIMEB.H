/*
 *  sys/timeb.h
 *
 *  Copyright (C) by WATCOM Systems Inc. 1991.	All rights reserved.
 */
#ifndef _TIME_T_DEFINED_
typedef unsigned long time_t;	/* time value */
#define _TIME_T_DEFINED_
#endif

#ifndef _TIMEB_H_INCLUDED

struct timeb {
	time_t	time;		/* time in seconds since Jan 1, 1970 GMT */
	unsigned short millitm; /* milliseconds */
	short	timezone;	/* difference in minutes from GMT to local */
	short	dstflag;	/* nonzero if we are in daylight savings time */
};

void ftime(struct timeb *);
#define _TIMEB_H_INCLUDED
#endif
