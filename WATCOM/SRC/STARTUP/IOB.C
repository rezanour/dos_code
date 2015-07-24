/*
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *%	  Copyright (C) 1985,1986 by WATCOM Systems Inc. All rights %
 *%	  reserved. No part of this software may be reproduced	    %
 *%	  in any form or by any means - graphic, electronic or	    %
 *%	  mechanical, including photocopying, recording, taping     %
 *%	  or information storage and retrieval systems - except     %
 *%	  with the written permission of WATCOM Systems Inc.	    %
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  Modified:	By:		Reason:
  ---------	---		-------
  29-May-86	A.C.C.Wai	Initial implementation
  14-jul-87	F.W.Crigger	removed _IONBF flags from stdin, stdout
  20-aug-87	F.W.Crigger	Added stdaux, stdprn, _iomode array
------------------------------------------------------------Version 6.0-----
  08-may-88	F.W.Crigger	moved _iomode array to separate file
  06-sep-89	F.W.Crigger	_iob renamed to __iob for ANSI
  16-oct-90	J.B.Schueler	don't need __tmpfnext for QNX
				don't need stdaux, stdprn for QNX
   2-Dec-90	B.J. Stecher	added __OpenFiles variable for QNX
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef __QNX__
int __near _fmode = O_TEXT;	/* default file translation mode */
#endif

FILE __near __iob[_NFILES] = {
    { NULL, 0, NULL, _READ  ,	    0, 0, 0, 0 }  /* stdin */
   ,{ NULL, 0, NULL, _WRITE ,	    1, 0, 0, 0 }  /* stdout */
   ,{ NULL, 0, NULL, _WRITE ,	    2, 0, 0, 0 }  /* stderr */
#ifndef __QNX__
   ,{ NULL, 0, NULL, _READ|_WRITE , 3, 0, 0, 0 }  /* stdaux */
   ,{ NULL, 0, NULL, _WRITE ,	    4, 0, 0, 0 }  /* stdprn */
#endif
};

#ifndef __QNX__
char	__tmpfnext	= 'a';
#else
FILE	*__OpenFiles;
#endif
