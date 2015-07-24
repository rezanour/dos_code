/*
 *  stddef.h	Standard definitions
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _STDDEF_H_INCLUDED

#ifndef _SIZE_T_DEFINED_
#define _SIZE_T_DEFINED_
typedef unsigned size_t;
#endif

#ifndef _WCHAR_T_DEFINED_
#define _WCHAR_T_DEFINED_
typedef unsigned short wchar_t;
#endif

#if defined(__SMALL__) || defined(__MEDIUM__) || defined(__386__)
 #define NULL   0
#else
 #define NULL   0L
#endif

#if defined(__HUGE__)
 typedef long	ptrdiff_t;
#else
 typedef int	ptrdiff_t;
#endif

#define offsetof(typ,id) (size_t)&(((typ*)0)->id)

/* define pragma for 'cdecl'  keyword to match Microsoft conventions */
/* define pragma for 'pascal' keyword to match Microsoft conventions */
#if defined( __WINDOWS_386__ )
 #pragma aux cdecl "_*" parm caller []\
   value struct float struct routine [eax]  modify [eax ebx ecx edx fs gs];
 #pragma aux pascal "^" parm routine reverse []\
   value struct float struct routine [eax]  modify [eax ebx ecx edx fs gs];
 #pragma aux fortran "^";
#elif defined( __386__ )
 #pragma aux cdecl "_*" parm caller []\
   value struct float struct routine [eax]  modify [eax ebx ecx edx];
 #pragma aux pascal "^" parm routine reverse []\
   value struct float struct routine [eax]  modify [eax ebx ecx edx];
 #pragma aux fortran "^";
#else
 #pragma aux cdecl "_*" parm caller loadds []\
   value struct float struct routine [ax]  modify [ax bx cx dx es];
 #pragma aux pascal "^" parm routine reverse []\
   value struct float struct routine [ax]  modify [ax bx cx dx es];
 #pragma aux fortran "^";
#endif
#ifndef NO_EXT_KEYS	/* extensions enabled */
 extern int __far *_threadid;	/* pointer to thread id */
#endif

#define _STDDEF_H_INCLUDED
#endif
