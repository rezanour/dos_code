/*
 *  errno.h	Error numbers
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _ERRNO_H_INCLUDED

#define errno (*__get_errno_ptr())
extern volatile int errno;

/*
 * Error codes
 */
#define ENOENT	1	/* No such file or directory */
#define E2BIG	2	/* Arg list too big */
#define ENOEXEC 3	/* Exec format error */
#define EBADF	4	/* Bad file number */
#define ENOMEM	5	/* Not enough memory */
#define EACCES	6	/* Permission denied */
#define EEXIST	7	/* File exists */
#define EXDEV	8	/* Cross-device link */
#define EINVAL	9	/* Invalid argument */
#define ENFILE	10	/* File table overflow */
#define EMFILE	11	/* Too many open files */
#define ENOSPC	12	/* No space left on device */

/* math errors */
#define EDOM	13	/* Argument too large */
#define ERANGE	14	/* Result too large */

/* file locking error */
#define EDEADLK 15	/* Resource deadlock would occur */
#define EDEADLOCK 15	/* ... */
#define EINTR	16	/* interrupt */
#define ECHILD	17	/* Child does not exist */

#define _ERRNO_H_INCLUDED
#endif
