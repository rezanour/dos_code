#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <errno.h>
#include <string.h>

/* Add environment strings to be searched here */
char *paths_to_check[] = {
	"DOS4GPATH",
	"PATH"};

char *dos4g_path()
{
    static char fullpath[80];
    int i;
    
    for( i = 0;
         i < sizeof( paths_to_check ) / sizeof( paths_to_check[0] ); i++ ) {
	_searchenv( "dos4gw.exe", paths_to_check[i], fullpath );
	if( fullpath[0] ) return( &fullpath );
    }	
    return( "\dos4gw.exe" );
}

main(int argc, char **argv)
{
    /* Allocate arg vector with room for new av[0] and terminal NULL */
    char **av = malloc( sizeof( char* ) * ( argc + 2 ) );
    int ac;
    
    if( !av ) {
	puts( "Stub failed to allocate argv" );
	exit( 1 );
    }
    av[0] = dos4g_path();		/* Locate the DOS/4G loader */
    /* Copy arguments */
    for( ac = 0; ac < argc; ac++ ) av[ac+1] = argv[ac];
    av[ac+1] = (void *)0;		/* Terminate list */
#ifdef QUIET
    putenv( "DOS4G=QUIET" );	/* disables DOS/4G Copyright banner */
#endif
    execvp( av[0], av );
    puts( "Stub exec failed:" );
    puts( av[0] );
    puts( strerror( errno ) );
    exit( 1 );			/* indicate error */
}
