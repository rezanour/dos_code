/*
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *%       Copyright (C) 1986,1989 by WATCOM Systems Inc. All rights %
 *%       reserved. No part of this software may be reproduced      %
 *%       in any form or by any means - graphic, electronic or      %
 *%       mechanical, including photocopying, recording, taping     %
 *%       or information storage and retrieval systems - except     %
 *%       with the written permission of WATCOM Systems Inc.        %
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  Modified:     By:             Reason:
  ---------     ---             -------
  22-nov-86     F.W.Crigger     Initial implementation
  16-feb-87     M.Glaum         Fix Command Line
  14-sep-87     F.W.Crigger     Don't remove quotes from parms
  21-oct-87     F.W.Crigger     Added fcloseall routine
  02-nov-87     A.F.Scian       made quoted parms like Microsoft and Turbo
  12-nov-87     F.W.Crigger     Added call to _setenvp()
  16-nov-87     F.W.Crigger     added fflush for stdxxx in exit.
  02-dec-87     F.W.Crigger     added call to _clock_init().
  08-dec-87     M.Glaum         added big data code
  13-dec-87     A.F.Scian       made atexit fail to add more functions
                                if exit handling has been initiated
  04-jan-88     F.W.Crigger     Allow '\\' in _SplitParms
  04-feb-88     F.W.Crigger     Added _init_files routine
---------------------------------------------------------Version 6.0--------
  03-apr-88     F.W.Crigger     set _amblksiz to 1 for memory allocations
                                done during initialization, then 8K for user.
  25-may-88     F.W.Crigger     _init_files exported for Express
  03-aug-88     A.F.Scian       moved DS expansion from CSTART to here
---------------------------------------------------------Version 6.5--------
  24-oct-88     F.W.Crigger     _init_files - add logic for _NFILES > 20
                                _iomode array moved to this file
  07-dec-88     F.W.Crigger     clock initialization done by cstart now
                                Do indirect call through _main_entry_ to
                                get to user's program instead of always
                                calling _init_argv and then main
  19-dec-88     F.W.Crigger     __Null_argv() defined so main works in overlay
  18-jan-89     F.W.Crigger     parms added to prototype for _main_entry
---------------------------------------------------------Version 7.0--------
  17-apr-89     F.W.Crigger     Adapted for 386
  89-05-25      John Dahms      split out _NFiles and iomode variables
  13-jul-89     John Dahms      Added call to brk( _STACKTOP )
  15-jan-91     F.W.Crigger     Must set _curbrk in cstart to _STACKTOP
  03-apr-91     A.F.Scian       changed initial setting of _amblksiz to 32k
*/
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <malloc.h>


extern  void near       *brk( unsigned ); /* set up curbrk variable */
extern  void            _init_files();

extern  int  (*_main_entry_)(char near *, char near *);

#pragma aux     _CMain  "_*"    parm routine [eax] [edx];


extern  unsigned __near _iomode[_NFILES];

void _CMain( parm, pgmname )
        char near *parm;        /* DOS command line string */
        char near *pgmname;     /* program name to be placed in argv[0] */
    {
        _init_files();          /* check first 5 handles */
        _amblksiz = 32 * 1024;   /* set minimum memory block allocation */
/*
        If main is defined with no parms, then _main_entry_ contains the
        address of "__Null_Argv", otherwise it contains the address of
        "__Init_Argv" which parses the command line, and then calls "main"
        directly.  This makes programs that don't use argc, argv smaller.
*/
        exit( (*_main_entry_)( parm, pgmname ) );
    }


int __Null_Argv()
    {
        extern  int main(void);

        return( main() );
    }


void _init_files()
    {
        register int handle;

#if _NFILES > 20

        /* increase the number of file handles beyond 20 */
        /* NOTE: iob.c must also be recompiled */

        long ret_code;
        extern int  _set_errno(unsigned);
        extern long _Set_File_Handle_Count(char,unsigned);

#pragma aux  _Set_File_Handle_Count = 0xcd 0x21 /* int 21h   */\
                                      0xd1 0xd0 /* rcl eax,1 */\
                                      0xd1 0xc8 /* ror eax,1 */\
        parm caller     [ah] [ebx] value [eax];

        ret_code = _Set_File_Handle_Count( 0x67, _NFILES );
        if( ret_code < 0 ) {
            _set_errno( (unsigned short)ret_code );
        }
#endif
        for( handle = 0; handle < 5; ++handle ) {
            if( isatty( handle ) )  _iomode[ handle ] |= _ISTTY;
        }
    }
