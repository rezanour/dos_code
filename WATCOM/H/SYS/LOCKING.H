/*
 *  sys/locking.h	Flags for locking() function
 *
 *  Copyright (C) by WATCOM Systems Inc. 1990-1991.  All rights reserved.
 */
#ifndef _LOCKING_H_INCLUDED

#define LK_UNLCK    0	/* unlock region of a file */
#define LK_LOCK     1	/* lock a region of a file */
#define LK_NBLCK    2	/* non-blocking lock */
#define LK_RLCK     3	/* lock for writing */
#define LK_NBRLCK   4	/* non-blocking lock for writing */

int locking(int __handle,int __mode,unsigned long __nbyte);

#define _LOCKING_H_INCLUDED
#endif
