/*
 *  varargs.h	Variable argument macros (UNIX System V definition)
 *		definitions for use with variable argument lists
 *
 *  Copyright (C) by WATCOM Systems Inc. 1991.  All rights reserved.
 */
#ifndef _VARARGS_H_INCLUDED

#define va_alist	void *__va_alist, ...
#define va_dcl

#ifdef	__HUGE__
typedef char __far *va_list;
#define va_start(ap)	((ap)=(char __far*)&__va_alist,(void)0)
#define va_arg(ap,type) ((ap)+=((sizeof(type)+1)&~1),\
			(*(type __far *)((ap)-((sizeof(type)+1)&~1))))
#define va_end(ap)	((ap)=0,(void)0)
#else
typedef char *va_list;
#define va_start(ap)	((ap)=(char *)&__va_alist,(void)0)
#define va_arg(ap,type)	((ap)+=\
    ((sizeof(type)+sizeof(int)-1)&~(sizeof(int)-1)),\
    (*(type *)((ap)-((sizeof(type)+sizeof(int)-1)&~(sizeof(int)-1)))))
#define va_end(ap)	((ap)=0,(void)0)
#endif

#define _VARARGS_H_INCLUDED
#endif
