/*
 *  io.h        Low level I/O routines that work with file handles
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _IO_H_INCLUDED

/* Symbolic constants for the access() function */

#define R_OK    4       /*  Test for read permission    */
#define W_OK    2       /*  Test for write permission   */
#define X_OK    1       /*  Test for execute permission */
#define F_OK    0       /*  Test for existence of file  */

#define ACCESS_WR       0x0002
#define ACCESS_RD       0x0004

/* Symbolic constants for the lseek() function */

#define SEEK_SET    0           /* Seek relative to the start of file   */
#define SEEK_CUR    1           /* Seek relative to current position    */
#define SEEK_END    2           /* Seek relative to the end of the file */

/* Symbolic constants for stream I/O */

#define STDIN_FILENO    0
#define STDOUT_FILENO   1
#define STDERR_FILENO   2
#ifndef NO_EXT_KEYS     /* extensions enabled */
#define STDAUX_FILENO   3
#define STDPRN_FILENO   4
#endif

int  access(const char *__path,int __mode);
int  chmod(const char *__path,int __pmode);
int  chsize(int __handle,long __size);
int  close(int __handle);
int  creat(const char *__path,int __pmode);
int  dup(int __handle);
int  dup2(int __handle1,int __handle2);
int  eof(int __handle);
long filelength(int __handle);
int  isatty(int __handle);
int  lock(int __handle,unsigned long __offset,unsigned long __nbytes);
long lseek(int __handle,long __offset,int __origin);
int  open(const char *__path,int __oflag,...);
int  read(int __handle,void *__buf,unsigned int __len);
int  setmode(int __handle,int __mode);
int  sopen(const char *__path,int __oflag,int __shflag,...);
long tell(int __handle);
int  umask(int __permission);
int  unlink(const char *__path);
int  unlock(int __handle,unsigned long __offset,unsigned long __nbytes);
int  write(int __handle,void *__buf,unsigned int __len);
#ifndef _STAT_H_INCLUDED
 #include <sys/stat.h>
#endif

#define _IO_H_INCLUDED
#endif
