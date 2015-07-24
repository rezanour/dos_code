/*
 *  conio.h	Console and Port I/O functions
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _CONIO_H_INCLUDED

#ifdef	__INLINE_FUNCTIONS__
 extern unsigned inp(unsigned __port);
 extern unsigned inpw(unsigned __port);
 extern unsigned outp(unsigned __port, unsigned __value);
 extern unsigned outpw(unsigned __port,unsigned __value);
 #define inp(__x)	_inline_inp(__x)
 #define inpw(__x)	_inline_inpw(__x)
 #define outp(__x,__y)	_inline_outp(__x,__y)
 #define outpw(__x,__y) _inline_outpw(__x,__y)
#endif

extern char *cgets(char *__buf);
extern int cputs(const char *__buf);
extern int cprintf(const char *__fmt,...);
extern int cscanf(const char *__fmt,...);
extern int getch(void);
extern int getche(void);
extern unsigned inp(unsigned __port);
extern unsigned inpw(unsigned __port);
extern int kbhit(void);
extern unsigned outp(unsigned __port, unsigned __value);
extern unsigned outpw(unsigned __port,unsigned __value);
extern int putch(int __c);
extern int ungetch(int __c);

#define _CONIO_H_INCLUDED
#endif
