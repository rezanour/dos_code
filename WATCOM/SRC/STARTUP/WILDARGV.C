/*
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *%	  Copyright (C) 1989, by WATCOM Systems Inc. All rights     %
 *%	  reserved. No part of this software may be reproduced	    %
 *%	  in any form or by any means - graphic, electronic or	    %
 *%	  mechanical, including photocopying, recording, taping     %
 *%	  or information storage and retrieval systems - except     %
 *%	  with the written permission of WATCOM Systems Inc.	    %
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  WILDARGV - split DOS command line into individual arguments expanding
	     those that contain ? or *.
  This module is a substitute for the "initargv" module contained in the
  library.

  Modified:	By:		Reason:
  ---------	---		-------
  23-aug-89	John Dahms	was ignoring files with Archive or
				read only attributes turned on. (Bug fix)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include <malloc.h>

extern	int	main();
extern	void	_Not_Enough_Memory();
static	void	*_allocate(unsigned);

int __Init_Argv( parm, pgmname )
	char  *parm;	    /* DOS command line string */
	char  *pgmname;     /* program name to be placed in argv[0] */
    {
	int	argc;		/* argument count */
	char	**argv; 	/* argument vector */

	argv = (char **) _allocate( 2 * sizeof( char * ) );
	argv[0] = pgmname;	/* fill in program name */
	argc = _make_argv( parm, &argv );
	argv[argc] = NULL;
	return( main( argc, argv ) );
    }


static int _make_argv( char *p, char ***argv )
    {
	int		argc;
	char		*start;
	char		*new;
	char		wildcard;
	char		lastchar;
	DIR *		dir;
	struct dirent * dirent;
	char		drive[_MAX_DRIVE];
	char		directory[_MAX_DIR];
	char		name[_MAX_FNAME];
	char		extin[_MAX_EXT];
	char		pathin[_MAX_PATH];

	argc = 1;
	for(;;) {
	    while( *p == ' ' ) ++p;	/* skip over blanks */
	    if( *p == '\0' ) break;
	    /* we are at the start of a parm */
	    wildcard = 0;
	    if( *p == '\"' ) {
		p++;
		new = start = p;
		for(;;) {
		    /* end of parm: NULLCHAR or quote */
		    if( *p == '\"' ) break;
		    if( *p == '\0' ) break;
		    if( *p == '\\' ) {
			if( p[1] == '\"'  ||  p[1] == '\\' )  ++p;
		    }
		    *new++ = *p++;
		}
	    } else {
		new = start = p;
		for(;;) {
		    /* end of parm: NULLCHAR or blank */
		    if( *p == '\0' ) break;
		    if( *p == ' ' ) break;
		    if(( *p == '\\' )&&( p[1] == '\"' )) {
			++p;
		    } else if( *p == '?'  ||  *p == '*' ) {
			wildcard = 1;
		    }
		    *new++ = *p++;
		}
	    }
	    *argv = realloc( *argv, (argc+2) * sizeof( char * ) );
	    if( *argv == NULL )  _Not_Enough_Memory();
	    (*argv)[ argc ] = start;
	    ++argc;
	    lastchar = *p;
	    *new = '\0';
	    ++p;
	    if( wildcard ) {
		/* expand file names */
		dir = opendir( start );
		if( dir != NULL ) {
		    --argc;
		    _splitpath( start, drive, directory, name, extin );
		    for(;;) {
			dirent = readdir( dir );
			if( dirent == NULL ) break;
			if( dirent->d_attr &
			  (_A_HIDDEN+_A_SYSTEM+_A_VOLID+_A_SUBDIR) ) continue;
			_splitpath( dirent->d_name, NULL, NULL, name, extin );
			_makepath( pathin, drive, directory, name, extin );
			*argv = realloc( *argv, (argc+2) * sizeof( char * ) );
			if( *argv == NULL )  _Not_Enough_Memory();
			new = _allocate( strlen( pathin ) + 1 );
			strcpy( new, pathin );
			(*argv)[argc++] = new;
		    }
		    closedir( dir );
		}
	    }
	    if( lastchar == '\0' ) break;
	}
	return( argc );
    }


static void *_allocate( unsigned amount )
    {
	void *p;

	p = _nmalloc( amount );
#if defined(__COMPACT__) || defined(__LARGE__) || defined(__HUGE__)
	if( p == NULL )  p = malloc( amount );
#endif
	if( p == NULL )  _Not_Enough_Memory();
	return( p );
    }
