/*
 *  ctype.h	Character Handling
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _CTYPE_H_INCLUDED

#define _LOWER	0x80
#define _UPPER	0x40
#define _DIGIT	0x20
#define _XDIGT	0x10
#define _PRINT	0x08
#define _PUNCT	0x04
#define _SPACE	0x02
#define _CNTRL	0x01

extern	int	isalnum(int);
extern	int	isalpha(int);
extern	int	iscntrl(int);
extern	int	isdigit(int);
extern	int	isgraph(int);
extern	int	islower(int);
extern	int	isprint(int);
extern	int	ispunct(int);
extern	int	isspace(int);
extern	int	isupper(int);
extern	int	isxdigit(int);
extern	int	tolower(int);
extern	int	toupper(int);


#ifndef NO_EXT_KEYS	/* extensions enabled */
 extern  int	isascii(int);
 #define isascii(__c) ((unsigned)(__c) <= 0x7f)
#endif

#ifdef M_I86HM
extern const char __far _IsTable[257];
#else
extern const char __near _IsTable[257];
#endif

#define isalnum(__c) (_IsTable[(__c)+1] & (_LOWER|_UPPER|_DIGIT))
#define isalpha(__c) (_IsTable[(__c)+1] & (_LOWER|_UPPER))
#define iscntrl(__c) (_IsTable[(__c)+1] & _CNTRL)
#define isdigit(__c) (_IsTable[(__c)+1] & _DIGIT)
#define isgraph(__c) ((_IsTable[(__c)+1] & (_PRINT|_SPACE)) == _PRINT)
#define islower(__c) (_IsTable[(__c)+1] & _LOWER)
#define isprint(__c) (_IsTable[(__c)+1] & _PRINT)
#define ispunct(__c) (_IsTable[(__c)+1] & _PUNCT)
#define isspace(__c) (_IsTable[(__c)+1] & _SPACE)
#define isupper(__c) (_IsTable[(__c)+1] & _UPPER)
#define isxdigit(__c) (_IsTable[(__c)+1] & _XDIGT)

#define _CTYPE_H_INCLUDED
#endif
