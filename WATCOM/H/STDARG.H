/*
 *  stdarg.h	Variable argument macros
 *		definitions for use with variable argument lists
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _STDARG_H_INCLUDED

#ifdef	__HUGE__
typedef char __far *va_list[1];
#else
typedef char *va_list[1];
#endif

#ifdef	__HUGE__
#define va_start(ap,pn) ((ap)[0]=(char __far*)&pn+((sizeof(pn)+1)&~1),(void)0)
#define va_arg(ap,type) ((ap)[0]+=((sizeof(type)+1)&~1),\
			(*(type __far *)((ap)[0]-((sizeof(type)+1)&~1))))
#define va_end(ap)	((ap)[0]=0,(void)0)
#else
#define va_start(ap,pn) ((ap)[0]=(char *)&pn+\
    ((sizeof(pn)+sizeof(int)-1)&~(sizeof(int)-1)),(void)0)
#define va_arg(ap,type)     ((ap)[0]+=\
    ((sizeof(type)+sizeof(int)-1)&~(sizeof(int)-1)),\
    (*(type *)((ap)[0]-((sizeof(type)+sizeof(int)-1)&~(sizeof(int)-1)))))
#define va_end(ap)	    ((ap)[0]=0,(void)0)
#endif

#define _STDARG_H_INCLUDED
#endif
