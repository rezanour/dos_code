/*
 *  stdlib.h    Standard Library functions
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _STDLIB_H_INCLUDED
#pragma pack(1);

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


#define RAND_MAX        32767u
#define EXIT_SUCCESS    0
#define EXIT_FAILURE    0xff
#define MB_CUR_MAX      1

typedef struct  {
        int     quot;
        int     rem;
} div_t;

typedef struct  {
        long    quot;
        long    rem;
} ldiv_t;

/* min and max macros */

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

/*
 * The following sizes are the maximum sizes of buffers used by the _makepath()
 * and _splitpath() functions. They include space for the '\0' terminator.
 */

#define _MAX_PATH   144 /* maximum length of full pathname */
#define _MAX_DRIVE   3  /* maximum length of drive component */
#define _MAX_DIR    130 /* maximum length of path component */
#define _MAX_FNAME   9  /* maximum length of file name component */
#define _MAX_EXT     5  /* maximum length of extension component */

#ifdef  __INLINE_FUNCTIONS__
 int      abs(int __j);
 div_t    div(int __numer,int __denom);
 long int labs(long int __j);
 unsigned int _rotl(unsigned int __value,unsigned int __shift);
 unsigned int _rotr(unsigned int __value,unsigned int __shift);
 #ifdef __386__
  unsigned long _lrotl(unsigned long __value,unsigned int __shift);
  unsigned long _lrotr(unsigned long __value,unsigned int __shift);
  #define _lrotl(x,n) _inline__lrotl(x,n)
  #define _lrotr(x,n) _inline__lrotr(x,n)
 #endif
 #define abs(x)     _inline_abs(x)
 #define div(x,y)   _inline_div(x,y)
 #define labs(x)    _inline_labs(x)
 #define _rotl(x,n) _inline__rotl(x,n)
 #define _rotr(x,n) _inline__rotr(x,n)
#endif

#pragma aux     abort   aborts;
#pragma aux     exit    aborts;
#pragma aux     _exit   aborts;

void     abort(void);
int      abs(int __j);
int      atexit(void (*__func)(void));
double   atof(const char *__nptr);
int      atoi(const char *__nptr);
long int atol(const char *__nptr);
void    *bsearch(const void *__key,const void *__base,
                 size_t __nmemb,size_t __size,
                 int (*__compar)(const void *__pkey,const void *__pbase));
void    *calloc(size_t __n,size_t __size);
div_t    div(int __numer,int __denom);
char    *ecvt(double __val,int __ndig,int *__dec,int *__sign);
void     exit(int __status);
void     _exit(int __status);
char    *fcvt(double __val,int __ndig,int *__dec,int *__sign);
void     free(void *__ptr);
char	*_fullpath(char *__buf,const char *__path,size_t __size);
char    *gcvt(double __val,int __ndig,char *__buf);
char    *getenv(const char *__name);
char    *itoa(int __value,char *__buf,int __radix);
long int labs(long int __j);
ldiv_t   ldiv(long int __numer,long int __denom);
unsigned long _lrotl(unsigned long __value,unsigned int __shift);
unsigned long _lrotr(unsigned long __value,unsigned int __shift);
char    *ltoa(long int __value,char *__buf,int __radix);
void     _makepath(char *__path,const char *__drive,const char *__dir,
                   const char *__fname,const char *__ext);
void    *malloc(size_t __size);
int      mblen(const char *__s,size_t __n);
size_t   mbstowcs(wchar_t *__pwcs,const char *__s,size_t __n);
int      mbtowc(wchar_t *__pwc,const char *__s,size_t __n);
int      putenv(const char *__string);
void     qsort(void *__base,size_t __nmemb,size_t __size,
                int (*__compar)(const void *,const void *));
int      rand(void);
void    *realloc(void *__ptr,size_t __size);
unsigned int _rotl(unsigned int __value,unsigned int __shift);
unsigned int _rotr(unsigned int __value,unsigned int __shift);
void     _searchenv(const char *__name,const char *__env_var,char *__buf);
void     _splitpath(const char *__path,char *__drive,
                  char *__dir,char *__fname,char *__ext);
void     srand(unsigned int __seed);
double   strtod(const char *__nptr,char **__endptr);
long int strtol(const char *__nptr,char **__endptr,int __base);
unsigned long int strtoul(const char *__nptr,char **__endptr,int __base);
void     swab( char *__src, char *__dest, int __num );
int      system(const char *__string);
char    *utoa(unsigned int __value,char *__buf,int __radix);
char    *ultoa(unsigned long int __value,char *__buf,int __radix);
size_t   wcstombs(char *__s,const wchar_t *__pwcs,size_t __n);
int      wctomb(char *__s,wchar_t __wchar);

#define atof(p) strtod(p,(char **)NULL)

/* external variables */
#ifndef NO_EXT_KEYS     /* extensions enabled */
 void __near *__brk(unsigned __new_brk_value);
 void __near *sbrk(int __increment);
 typedef void (*onexit_t)();
 onexit_t onexit(onexit_t __func);
 extern  char **  __near environ;       /* pointer to environment table */
#endif

#define errno (*__get_errno_ptr())
#define _doserrno (*__get_doserrno_ptr())
extern  volatile int    errno;          /* ANSI error number */
extern  int             _doserrno;      /* DOS system error code value */
extern  unsigned __near _psp;           /* Program Segment Prefix */
extern  unsigned char __near _osmajor;  /* DOS version # */
extern  unsigned char __near _osminor;  /* DOS version # */
#define DOS_MODE 0                      /* Real Address Mode */
#define OS2_MODE 1                      /* Protected Address Mode */
extern  unsigned char __near _osmode;   /* DOS_MODE or OS2_MODE */
extern  int     __near  _fmode;         /* default file translation mode */
extern unsigned __near  _amblksiz;      /* DOS mallocs done in multiples of */
extern char *           sys_errlist[];  /* strerror error message table */
extern int      __near  sys_nerr;       /* # of entries on sys_errlist array */
extern unsigned __near	__minreal;	/* DOS4GW var for WLINK MINREAL option*/

#pragma pack();
#define _STDLIB_H_INCLUDED
#endif
