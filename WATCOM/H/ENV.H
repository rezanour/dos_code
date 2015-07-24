/*
 *  env.h	Environment string operations
 *
 *  Copyright (C) by WATCOM Systems Inc. 1990.	All rights reserved.
 */
#ifndef _ENV_H_INCLUDED

/*
 *  POSIX 1003.1 Prototypes.
 */
 int	clearenv( void );
 char  *getenv( const char *__name );
 int	setenv( const char *__name, const char *__newvalue, int __overwrite );
#if !defined(NO_EXT_KEYS)
 int	putenv( const char *__env_string );
#endif

#define _ENV_H_INCLUDED
#endif
