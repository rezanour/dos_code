/*
 *  malloc.h	Memory allocation functions
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _MALLOC_H_INCLUDED
#pragma pack(1);

#ifndef _SIZE_T_DEFINED_
#define _SIZE_T_DEFINED_
typedef unsigned size_t;
#endif

#if defined(__SMALL__) || defined(__MEDIUM__) || defined(__386__)
 #define NULL	0
#else
 #define NULL	0L
#endif

void  *alloca(size_t __size);
void  *_alloca(size_t __size);

#define __ALLOCA_ALIGN( s )	 (((s)+(sizeof(int)-1))&~(sizeof(int)-1))

#define alloca(size) \
( (__ALLOCA_ALIGN(size) < stackavail()) ? _alloca(__ALLOCA_ALIGN(size)) : NULL)

#if defined(__386__)
#pragma aux	_alloca = 0x29 0xc4 /* sub esp,eax */\
			  0x89 0xe0 /* mov eax,esp */\
			parm caller [eax] value[eax] modify [esp];
#elif defined(__SMALL__) || defined(__MEDIUM__) /* small data models */
#pragma aux	_alloca = 0x29 0xc4 /* sub sp,ax */\
			  0x89 0xe0 /* mov ax,sp */\
			parm caller [ax] value[ax] modify [sp];
#else						/* large data models */
#pragma aux	_alloca = 0x29 0xc4 /* sub sp,ax */\
			  0x89 0xe0 /* mov ax,sp */\
			  0x8c 0xd2 /* mov dx,ss */\
			parm caller [ax] value[ax dx] modify [sp];
#endif

#define _HEAPOK 	0
#define _HEAPEMPTY	1	/* heap isn't initialized */
#define _HEAPBADBEGIN	2	/* heap header is corrupted */
#define _HEAPBADNODE	3	/* heap entry is corrupted */
#define _HEAPEND	4	/* end of heap entries (_heapwalk) */
#define _HEAPBADPTR	5	/* invalid heap entry pointer (_heapwalk) */

#define _USEDENTRY	0
#define _FREEENTRY	1

struct _heapinfo {
    void __far		*_pentry;	/* heap pointer */
    size_t		_size;		/* heap entry size */
    int 		_useflag;	/* heap entry 'in-use' flag */
};

int _heapchk( void );
int _nheapchk( void );
int _fheapchk( void );
int _heapset( unsigned int __fill );
int _nheapset( unsigned int __fill );
int _fheapset( unsigned int __fill );
int _heapwalk( struct _heapinfo *__entry );
int _nheapwalk( struct _heapinfo *__entry );
int _fheapwalk( struct _heapinfo *__entry );

void _heapgrow( void );
void _nheapgrow( void );
void _fheapgrow( void );
int _heapmin( void );
int _nheapmin( void );
int _fheapmin( void );
int _heapshrink( void );
int _nheapshrink( void );
int _fheapshrink( void );

int __nmemneed( size_t );
int __fmemneed( size_t );

void *calloc(size_t __n,size_t __size);
void *_expand(void *__ptr,size_t __size);
void __far  *_fexpand(void __far *__ptr,size_t __size);
void __near *_nexpand(void __near *__ptr,size_t __size);
void _ffree(void __far *__ptr);
void __far *_fmalloc(size_t __size);
void free(void *__ptr);
unsigned int _freect(size_t __size);
void __huge *halloc(long __n,size_t __size);
void hfree(void __huge *);
void *malloc(size_t __size);
void _nfree(void __near *__ptr);
void __near *_nmalloc(size_t __size);
void *realloc(void *__ptr,size_t __size);
void __near *_nrealloc(void __near *__ptr,size_t __size);
void __far  *_frealloc(void __far *__ptr,size_t __size);
size_t _msize( void *__ptr );
size_t _nmsize( void __near *__ptr );
size_t _fmsize( void __far *__ptr );
size_t _memavl(void);
size_t _memmax(void);
unsigned stackavail(void);

#pragma pack();
#define _MALLOC_H_INCLUDED
#endif
