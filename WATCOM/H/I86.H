/*
 *  i86.h	Defines the structs and unions used to handle the input and
 *		output registers for the Intel x86 and 386 interrupt interface
 *		routines.
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _I86_H_INCLUDED

#pragma pack(1);
#undef __FILLER
#if defined(__386__) && !defined(__WINDOWS_386__)
/* dword registers */

struct DWORDREGS {
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
	unsigned int esi;
	unsigned int edi;
	unsigned int cflag;
};
 #define __FILLER unsigned short :16;
#else
 #define __FILLER
#endif
/* word registers */

struct WORDREGS {
	unsigned short ax;  __FILLER
	unsigned short bx;  __FILLER
	unsigned short cx;  __FILLER
	unsigned short dx;  __FILLER
	unsigned short si;  __FILLER
	unsigned short di;  __FILLER
#if defined(__WINDOWS_386__)
	unsigned short cflag;
#else
	unsigned int cflag;
#endif
};

/* byte registers */

struct BYTEREGS {
	unsigned char al, ah;  __FILLER
	unsigned char bl, bh;  __FILLER
	unsigned char cl, ch;  __FILLER
	unsigned char dl, dh;  __FILLER
};

/* general purpose registers union - overlays the corresponding dword,
 * word, and byte registers.
 */

union REGS {
#if defined(__386__) && !defined(__WINDOWS_386__)
	struct DWORDREGS x;
#else
	struct WORDREGS  x;
#endif
	struct WORDREGS  w;
	struct BYTEREGS  h;
};

/* segment registers */

struct SREGS {
	unsigned short es, cs, ss, ds;
#if defined(__386__)
	unsigned short fs, gs;
#endif
};

/* intr structs */

struct REGPACKB {
	unsigned char al, ah;  __FILLER
	unsigned char bl, bh;  __FILLER
	unsigned char cl, ch;  __FILLER
	unsigned char dl, dh;  __FILLER
};

struct REGPACKW {
	unsigned short ax;  __FILLER
	unsigned short bx;  __FILLER
	unsigned short cx;  __FILLER
	unsigned short dx;  __FILLER
	unsigned short bp;  __FILLER
	unsigned short si;  __FILLER
	unsigned short di;  __FILLER
	unsigned short ds;
	unsigned short es;
#if defined(__386__) && !defined(__WINDOWS_386__)
	unsigned short fs;
	unsigned short gs;
#endif
#if defined(__WINDOWS_386__) 
	unsigned short flags;
#else
	unsigned int flags;
#endif
};

struct REGPACKX {
	unsigned int   eax, ebx, ecx, edx, ebp, esi, edi;
	unsigned short ds, es, fs, gs;
	unsigned int   flags;
};

union REGPACK {
	struct REGPACKB h;
	struct REGPACKW w;
#if defined(__386__) && !defined(__WINDOWS_386__)
	struct REGPACKX x;
#else
	struct REGPACKW x;
#endif
};

/* input parm to an 'interrupt' function is union INTPACK */
/* e.g.  interrupt int10( union INTPACK r ) {}		  */

struct INTPACKX {
	unsigned gs,fs,es,ds,edi,esi,ebp,esp,ebx,edx,ecx,eax,eip,cs,flags;
};
struct INTPACKW {
#if defined(__386__) && !defined(__WINDOWS_386__)
	unsigned short gs;  __FILLER
	unsigned short fs;  __FILLER
#endif
	unsigned short es;  __FILLER
	unsigned short ds;  __FILLER
	unsigned short di;  __FILLER
	unsigned short si;  __FILLER
	unsigned short bp;  __FILLER
	unsigned short sp;  __FILLER
	unsigned short bx;  __FILLER
	unsigned short dx;  __FILLER
	unsigned short cx;  __FILLER
	unsigned short ax;  __FILLER
	unsigned short ip;  __FILLER
	unsigned short cs;  __FILLER
#if defined(__WINDOWS_386__)
	unsigned short flags;
#else
	unsigned flags;
#endif
};
struct INTPACKB {
#if defined(__386__) && !defined(__WINDOWS_386__)
	unsigned /*gs*/ :32,/*fs*/ :32,
		 /*es*/ :32,/*ds*/ :32,
		 /*edi*/:32,/*esi*/:32,
		 /*ebp*/:32,/*esp*/:32;
#else
	unsigned /*es*/:16,/*ds*/:16,
		 /*di*/:16,/*si*/:16,
		 /*bp*/:16,/*sp*/:16;
#endif
	unsigned char bl, bh; __FILLER
	unsigned char dl, dh; __FILLER
	unsigned char cl, ch; __FILLER
	unsigned char al, ah; __FILLER
};
union  INTPACK {
	struct INTPACKB h;
	struct INTPACKW w;
#if defined(__386__) && !defined(__WINDOWS_386__)
	struct INTPACKX x;
#else
	struct INTPACKW x;
#endif
};

/* bits defined for flags field defined in REGPACKW and INTPACKW */

enum {
    INTR_CF	= 0x0001,	/* carry */
    INTR_PF	= 0x0004,	/* parity */
    INTR_AF	= 0x0010,	/* auxiliary carry */
    INTR_ZF	= 0x0040,	/* zero */
    INTR_SF	= 0x0080,	/* sign */
    INTR_TF	= 0x0100,	/* trace */
    INTR_IF	= 0x0200,	/* interrupt */
    INTR_DF	= 0x0400,	/* direction */
    INTR_OF	= 0x0800	/* overflow */
};


extern	void _disable( void );
extern	void _enable( void );

#ifdef	__INLINE_FUNCTIONS__
 extern void _inline__disable( void );
 extern void _inline__enable( void );
 #define _disable() _inline__disable()
 #define _enable()  _inline__enable()
#endif

void	delay(unsigned int __milliseconds);
#if defined(__386__) && !defined(__WINDOWS_386__)
int	int386( int, union REGS *, union REGS * );
int	int386x( int, union REGS *, union REGS *, struct SREGS * );
#else
int	int86( int, union REGS *, union REGS * );
int	int86x( int, union REGS *, union REGS *, struct SREGS * );
#endif
void	intr( int, union REGPACK * );
void	nosound( void );
void	segread( struct SREGS * );
void	sound( unsigned __frequency );

/* macros to break 'far' pointers into segment and offset components */

#define FP_OFF(__p) ((unsigned)(__p))
#ifdef __386__
  unsigned short FP_SEG( void __far * );
  #pragma aux	 FP_SEG = parm caller [eax dx] value [dx];

  /*	  make a far pointer from segment and offset */
  void __far *MK_FP(unsigned short,unsigned);
  #pragma aux	 MK_FP = parm caller [dx] [eax] value [eax dx];
#else
  #define FP_SEG(__p) ((unsigned)((unsigned long)(void __far*)(__p) >> 16))

  /*	  make a far pointer from segment and offset */
#define MK_FP(__s,__o) ((void __far*)(((unsigned long)(__s)<<16)|(unsigned)(__o)))
#endif

#pragma pack();

#define _I86_H_INCLUDED
#endif
