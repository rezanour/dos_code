/*
 *  time.h	Time functions
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _TIME_H_INCLUDED
#pragma pack(1);

#ifndef _SIZE_T_DEFINED_
 #define _SIZE_T_DEFINED_
 typedef unsigned size_t;
#endif

#if defined(__SMALL__) || defined(__MEDIUM__) || defined(__386__)
 #define NULL   0
#else
 #define NULL   0L
#endif

#ifndef _TIME_T_DEFINED_
 #define _TIME_T_DEFINED_
 typedef unsigned long time_t;	 /* time value */
#endif

#define CLK_TCK 	100
#define CLOCKS_PER_SEC	100
typedef unsigned long	clock_t;

struct	tm {
	int  tm_sec;	/* seconds after the minute -- [0,61] */
	int  tm_min;	/* minutes after the hour   -- [0,59] */
	int  tm_hour;	/* hours after midnight     -- [0,23] */
	int  tm_mday;	/* day of the month	    -- [1,31] */
	int  tm_mon;	/* months since January     -- [0,11] */
	int  tm_year;	/* years since 1900		      */
	int  tm_wday;	/* days since Sunday	    -- [0,6]  */
	int  tm_yday;	/* days since January 1     -- [0,365]*/
	int  tm_isdst;	/* Daylight Savings Time flag */
};

char   *asctime( const struct tm *__timeptr );
clock_t clock(void);
char   *ctime( const time_t *__timer );
double	difftime( time_t __t1, time_t __t0 );
struct tm *gmtime( const time_t *__timer );
struct tm *localtime( const time_t *__timer );
time_t	mktime( struct tm *__timeptr );
size_t	strftime(char *__s,size_t __maxsiz,const char *__fmt,
		 const struct tm *__tp );
time_t	time( time_t *__timer );

#define difftime(t1,t0) ((double)(t1)-(double)(t0))

#ifndef NO_EXT_KEYS	/* extensions enabled */
 void	tzset(void);
 extern long	timezone;	/* # of seconds from GMT */
 extern int	daylight;	/* d.s.t. indicator */
 extern char	*tzname[2];	/* time zone names */
#endif

#pragma pack();
#define _TIME_H_INCLUDED
#endif
