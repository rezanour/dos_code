/*
 *  search.h	Function prototypes for searching functions
 *
 *  Copyright (C) by WATCOM Systems Inc. 1990-1991.  All rights reserved.
 */
#ifndef _SEARCH_H_INCLUDED

void *lfind(const void *__key, const void *__base, unsigned *__num,
	    unsigned __width, int (* __compare)(const void *, const void *));
void *lsearch(const void *__key, const void *__base, unsigned *__num,
	    unsigned __width, int (* __compare)(const void *, const void *));
#define _SEARCH_H_INCLUDED
#endif
