/*
 *  process.h	Process spawning and related routines
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _PROCESS_H_INCLUDED

/* mode flags for spawnxxx routines */
extern int __p_overlay;

#define P_WAIT	    0
#define P_NOWAIT    1
#define P_OVERLAY   __p_overlay
#define P_NOWAITO   3

/* values for __action_code used with cwait() */

#define WAIT_CHILD 0
#define WAIT_GRANDCHILD 1

void  abort(void);
int __far _beginthread( void (__far *__start_address)(void __far *),
     void __far *__stack_bottom, unsigned __stack_size,void __far *__arglist );
int   cwait(int *__status,int __process_id,int __action_code);
void __far _endthread();
#ifndef __386__
int   execl(const char *__path, const char *__arg0,...);
int   execle(const char *__path, const char *__arg0,...);
int   execlp(const char *__path, const char *__arg0,...);
int   execlpe(const char *__path, const char *__arg0,...);
int   execv(const char *__path,char **__argv);
int   execve(const char *__path,char **__argv,char **__envp);
int   execvp(const char *__path,char **__argv);
int   execvpe(const char *__path,char **__argv,char **__envp);
#endif
void  exit(int __status);
void  _exit(int __status);
char *getcmd(char *__buffer);
char *getenv(const char *__name);
int   getpid(void);
int   putenv(const char *__string);
int   spawnl(int __mode,const char *__path, const char *__arg0,...);
int   spawnle(int __mode,const char *__path, const char *__arg0,...);
int   spawnlp(int __mode,const char *__path, const char *__arg0,...);
int   spawnlpe(int __mode,const char *__path, const char *__arg0,...);
int   spawnv(int __mode,const char *__path,char **__argv);
int   spawnve(int __mode,const char *__path,char **__argv,char **__envp);
int   spawnvp(int __mode,const char *__path,char **__argv);
int   spawnvpe(int __mode,const char *__path,char **__argv,char **__envp);
int   system(const char *__cmd);
int   wait(int *__status);

#pragma aux	abort	aborts;
#pragma aux	exit	aborts;
#pragma aux	_exit	aborts;

#define _PROCESS_H_INCLUDED
#endif
