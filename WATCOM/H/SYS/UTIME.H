/*
 *  sys/utime.h
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef _UTIME_H_INCLUDED
#pragma pack(1);

struct utimbuf {
    time_t	actime; 	/* access time */
    time_t	modtime;	/* modification time */
};

int utime(const char *, struct utimbuf *);

#pragma pack();
#define _UTIME_H_INCLUDED
#endif
