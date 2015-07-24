/*
 *  direct.h	Defines the types and structures used by the directory routines
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _DIRECT_H_INCLUDED
#pragma pack(1);

#ifndef _TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#define NAME_MAX	12		/* 8 chars + '.' +  3 chars */

typedef struct dirent {
    char	d_dta[ 21 ];		/* disk transfer area */
    char	d_attr; 		/* file's attribute */
    unsigned short int d_time;		/* file's time */
    unsigned short int d_date;		/* file's date */
    long	d_size; 		/* file's size */
    char	d_name[ NAME_MAX + 1 ]; /* file's name */
    ino_t	d_ino;			/* serial number (not used) */
    char	d_first;		/* flag for 1st time */
} DIR;

/* File attribute constants for d_attr field */

#define _A_NORMAL	0x00	/* Normal file - read/write permitted */
#define _A_RDONLY	0x01	/* Read-only file */
#define _A_HIDDEN	0x02	/* Hidden file */
#define _A_SYSTEM	0x04	/* System file */
#define _A_VOLID	0x08	/* Volume-ID entry */
#define _A_SUBDIR	0x10	/* Subdirectory */
#define _A_ARCH 	0x20	/* Archive file */


int	chdir( const char *__path );
int	closedir( DIR * );
char   *getcwd( char *__buf, unsigned __size );
int	mkdir( const char *__path );
DIR	*opendir( const char * );
struct dirent *readdir( DIR * );
int	rmdir( const char *__path );

#pragma pack();
#define _DIRECT_H_INCLUDED
#endif
