/*
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *%       Copyright (C) 1986, by WATCOM Systems Inc. All rights     %
 *%       reserved. No part of this software may be reproduced      %
 *%       in any form or by any means - graphic, electronic or      %
 *%       mechanical, including photocopying, recording, taping     %
 *%       or information storage and retrieval systems - except     %
 *%       with the written permission of WATCOM Systems Inc.        %
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  Modified:     By:             Reason:
  ---------     ---             -------
  24-aug-87     F.W.Crigger     Initial implementation
------------------------------------------------------Version 6.0--------
  08-apr-88     F.W.Crigger     changed fprintf to fputs
  01-may-88     F.W.Crigger     Add "fputc( '\n', stderr)" to match the fprintf
  18-aug-89     John Dahms      include "newerrno.h" so errno is ok in DOS
                                as well as multi-threaded OS/2 environment
  28-feb-90     F.W.Crigger     call __set_ERANGE() and __set_EDOM to set errno
------------------------------------------------------Version 8.0--------
  19-mar-91     F.W.Crigger     call __matherr which calls matherr
  24-mar-91     F.W.Crigger     __math2err calls _matherr with ptr to struct
                                Perform indirect through __MathErrRtn so that
                                Netware NLM programs can change it to point to
                                a different routine.
*/
#include <stdio.h>
#include <math.h>

extern  void    __set_EDOM();
extern  void    __set_ERANGE();
extern  int     __matherr( struct exception * );
#pragma aux     __matherr "*";

static char *Msgs[] = {
        0,
        "Domain error",
        "Argument singularity",
        "Overflow range error",
        "Underflow range error",
        "Total loss of significance",
        "Partial loss of significance"
   };

int     (*__MathErrRtn)( struct exception * ) = __matherr;      /* 24-mar-91 */

double _matherr( struct exception *excp )
/***************************************/
    {
        if( (*__MathErrRtn)( excp ) == 0 ) {
/*          fprintf( stderr, "%s in %s\n", Msgs[excp->type], excp->name ); */
            fputs( Msgs[excp->type], stderr );
            fputs( " in ", stderr );
            fputs( excp->name, stderr );
            fputc( '\n', stderr );
            excp->type == DOMAIN ? __set_EDOM() : __set_ERANGE();
        }
        return( excp->retval );
    }
