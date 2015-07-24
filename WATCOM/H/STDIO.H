/*
 *  stdio.h     Standard I/O functions
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _STDIO_H_INCLUDED
#pragma pack(1);

#ifndef _SIZE_T_DEFINED_
 #define _SIZE_T_DEFINED_
 typedef unsigned size_t;
#endif

#if defined(__SMALL__) || defined(__MEDIUM__) || defined(__386__)
 #define NULL   0
#else
 #define NULL   0L
#endif

#ifdef  __HUGE__
 typedef char __far *__va_list[1];
#else
 typedef char *__va_list[1];
#endif

#ifdef __386__
 #define BUFSIZ         4096
#else
 #define BUFSIZ         512
#endif
#define _NFILES         20      /* number of files that can be handled */
#define FILENAME_MAX    80

typedef struct  __iobuf {
        char            *_ptr;          /* next character position */
        int             _cnt;           /* number of characters left */
        char            *_base;         /* location of buffer */
        unsigned        _flag;          /* mode of file access */
        int             _handle;        /* file handle */
        unsigned        _bufsize;       /* size of buffer */
        unsigned char   _ungotten;      /* character placed here by ungetc */
        unsigned char   _tmpfchar;      /* tmpfile number */
} FILE;

typedef long    fpos_t;

#ifndef NO_EXT_KEYS     /* extensions enabled */
 #define FOPEN_MAX      _NFILES
 #define OPEN_MAX       FOPEN_MAX
 #define PATH_MAX       80
#else                   /* extensions not enabled */
 #define FOPEN_MAX      (_NFILES-2)
#endif

extern  FILE   __near __iob[_NFILES];
extern  unsigned __near _iomode[_NFILES];
#define stdin   ((FILE *)&__iob[0])     /* standard input file  */
#define stdout  ((FILE *)&__iob[1])     /* standard output file */
#define stderr  ((FILE *)&__iob[2])     /* standard error file  */
#ifndef NO_EXT_KEYS     /* extensions enabled */
#define stdaux  ((FILE *)&__iob[3])     /* standard auxiliary file  */
#define stdprn  ((FILE *)&__iob[4])     /* standard printer file  */
#endif

/* values for _flag field in FILE struct and _iomode array */

#define _READ   0x0001  /* file opened for reading */
#define _WRITE  0x0002  /* file opened for writing */
#define _UNGET  0x0004  /* ungetc has been done */
#define _BIGBUF 0x0008  /* big buffer allocated */
#define _EOF    0x0010  /* EOF has occurred */
#define _ERR    0x0020  /* error has occurred on this file */
#define _BINARY 0x0040  /* file is binary, skip CRLF processing */
#define _APPEND 0x0080  /* file opened for append */
#define _IOFBF  0x0100  /* full buffering */
#define _IOLBF  0x0200  /* line buffering */
#define _IONBF  0x0400  /* no buffering */
#define _TMPFIL 0x0800  /* this is a temporary file */
#define _DIRTY  0x1000  /* buffer has been modified */
#define _ISTTY  0x2000  /* is console device */

#define EOF     (-1)

#define SEEK_SET        0
#define SEEK_CUR        1
#define SEEK_END        2

#define L_tmpnam        13
#define TMP_MAX         (26*26*26)

int   _bprintf(char *__buf,unsigned int __bufsize,const char *__format,...);
void  clearerr(FILE *__fp);
int   fclose(FILE *__fp);
int   fcloseall(void);
FILE *fdopen(int __handle,const char *__mode);
int   feof(FILE *__fp);
int   ferror(FILE *__fp);
int   fflush(FILE *__fp);
int   fgetc(FILE *__fp);
int   fgetchar(void);
int   fgetpos(FILE *__fp,fpos_t *__pos);
char *fgets(char *__s,int __n,FILE *__fp);
int   flushall(void);
FILE *fopen(const char *__filename,const char *__mode);
int   fprintf(FILE *__fp,const char *__format,...);
int   fputc(int __c,FILE *__fp);
int   fputchar(int __c);
int   fputs(const char *__s,FILE *__fp);
size_t fread(void *__ptr,size_t __size,size_t __n,FILE *__fp);
FILE *freopen(const char *__filename,const char *__mode,FILE *__fp);
int   fscanf(FILE*__fp,const char *__format,...);
int   fseek(FILE *__fp,long int __offset,int __whence);
int   fsetpos(FILE *__fp,const fpos_t *__pos);
long int ftell(FILE *__fp);
size_t fwrite(const void *__ptr,size_t __size,size_t __n,FILE *__fp);
int   getc(FILE *__fp);
int   getchar(void);
char *gets(char *__s);
void  perror(const char *__s);
int   printf(const char *__format,...);
int   putc(int __c,FILE *__fp);
int   putchar(int __c);
int   puts(const char *__s);
int   remove(const char *__filename);
int   rename(const char *__old,const char *__new);
void  rewind(FILE *__fp);
int   scanf(const char *__format,...);
void  setbuf(FILE *__fp,char *__buf);
int   setvbuf(FILE *__fp,char *__buf,int __mode,size_t __size);
int   sprintf(char *__s,const char *__format,...);
int   sscanf(const char *__s,const char *__format,...);
FILE *tmpfile(void);
char *tmpnam(char *__s);
int   _vbprintf(char *__buf,unsigned int __bufsize,const char *__format,
	__va_list __arg);
int   vfprintf(FILE *__fp,const char *__format,__va_list __arg);
int   vprintf(const char *__format,__va_list __arg);
int   vsprintf(char *__s,const char *__format,__va_list __arg);
int   vfscanf(FILE *__fp,const char *__format,__va_list __arg);
int   vscanf(const char *__format,__va_list __arg);
int   vsscanf(const char *__s,const char *__format,__va_list __arg);
int   ungetc(int __c,FILE *__fp);

#define clearerr(fp)    ((fp)->_flag &= ~(_ERR|_EOF))
#define feof(fp)        ((fp)->_flag & _EOF)
#define ferror(fp)      ((fp)->_flag & _ERR)
#define fileno(fp)      ((fp)->_handle)
#define getchar()       fgetc(stdin)
#define getc(fp)        fgetc((fp))
#define putchar(c)      fputc((c),stdout)
#define putc(c,fp)      fputc((c),(fp))

#pragma pack();
#define _STDIO_H_INCLUDED
#endif
