/*
 *  wsample.h	WATCOM Execution Sampler include file
 *
 *  Copyright (C) by WATCOM Systems Inc. 1989-1991.  All rights reserved.
 */
#ifndef _WSAMPLE_H_INCLUDED
#ifdef _MARK_ON
  #ifdef __386__
    #pragma aux __mark = 0xcc parm nomemory [dx eax] modify exact nomemory [];
  #else
    #pragma aux __mark = 0xcc parm nomemory [dx ax] modify exact nomemory [];
  #endif
  extern void __mark( char __far * );
  #define _MARK_( x )	__mark( x )
#else
  #define _MARK_( x )
#endif
#define _WSAMPLE_H_INCLUDED
#endif
