/*
 *  share.h	Define file sharing modes for sopen()
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */

#define SH_COMPAT   0x00    /* compatibility mode   */
#define SH_DENYRW   0x10    /* deny read/write mode */
#define SH_DENYWR   0x20    /* deny write mode	    */
#define SH_DENYRD   0x30    /* deny read mode	    */
#define SH_DENYNO   0x40    /* deny none mode	    */
