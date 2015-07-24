/*
 *  assert.h
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#undef	assert

#ifdef NDEBUG
#define assert(__ignore) ((void)0)
#else
extern	void		__assert( int, char *, char *, int );
#define assert(expr)	__assert(expr,#expr,__FILE__,__LINE__)
#endif
