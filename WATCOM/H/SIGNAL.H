/*
 *  signal.h
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _SIGNAL_H_INCLUDED

typedef int	sig_atomic_t;

#define SIG_IGN 	(void (*)(int)) 1
#define SIG_DFL 	(void (*)(int)) 2
#define SIG_ERR 	(void (*)(int)) 3

#define SIGABRT 1
#define SIGFPE	2
#define SIGILL	3
#define SIGINT	4
#define SIGSEGV 5
#define SIGTERM 6
#define SIGBREAK 7
/* following are OS/2 process flag A,B and C */
#define SIGUSR1 8
#define SIGUSR2 9
#define SIGUSR3 10

#define _SIGMIN     1
#define _SIGMAX     10

void (*signal( int __sig, void (*__func)() ) )();
int  raise( int __sig );

#define _SIGNAL_H_INCLUDED
#endif
