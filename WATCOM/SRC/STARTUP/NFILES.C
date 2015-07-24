/*
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *%	  Copyright (C) 1986,1988 by WATCOM Systems Inc. All rights %
 *%	  reserved. No part of this software may be reproduced	    %
 *%	  in any form or by any means - graphic, electronic or	    %
 *%	  mechanical, including photocopying, recording, taping     %
 *%	  or information storage and retrieval systems - except     %
 *%	  with the written permission of WATCOM Systems Inc.	    %
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  Modified:	By:		Reason:
  ---------	---		-------
  89-05-25	John Dahms	split out of cmain
  90/10/25	J.B.Schueler	Conditional on __iomode array
  90/12/02	B.J. Stecher	Conditional on __NFiles
*/
#include <stdio.h>

#ifndef __QNX__
unsigned __NFiles = _NFILES;		/* maximum # of files we can open */

unsigned __near _iomode[_NFILES] = {	/* file mode information (flags) */
	_READ,		/* stdin */
	_WRITE, 	/* stdout */
	_WRITE, 	/* stderr */
	_READ|_WRITE,	/* stdaux */
	_WRITE		/* stdprn */
};
#endif
