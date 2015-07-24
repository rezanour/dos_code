/*
 *  setjmp.h
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _SETJMP_H_INCLUDED

typedef unsigned int jmp_buf[13];

#define setjmp(__env)	  _setjmp(__env)
#if defined(__386__)
 #pragma aux _setjmp parm caller [eax] modify [8087];
#else
 #pragma aux _setjmp modify [8087];
#endif

int  _setjmp( jmp_buf __env );
void longjmp( jmp_buf __env, int __val );

#pragma aux	longjmp aborts;

#define _SETJMP_H_INCLUDED
#endif
