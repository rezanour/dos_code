/*
 *  float.h	Floating point functions
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _FLOAT_H_INCLUDED

#define FLT_RADIX	2
#define FLT_ROUNDS	1	/* round to nearest */

/* number of base-FLT_RADIX digits in the floating point mantissa */
#define FLT_MANT_DIG	23
#define DBL_MANT_DIG	53
#define LDBL_MANT_DIG	53

/* number of decimal digits of precision */
#define FLT_DIG 	6
#define DBL_DIG 	15
#define LDBL_DIG	15

/* minimum negative integer such that FLT_RADIX raised to that power minus 1
 is a normalized floating point number */
#define FLT_MIN_EXP	(-127)
#define DBL_MIN_EXP	(-1023)
#define LDBL_MIN_EXP	(-1023)

/* minimum negative integer such that 10 raised to that power is in the
   range of normalized floating point numbers */
#define FLT_MIN_10_EXP	(-38)
#define DBL_MIN_10_EXP	(-307)
#define LDBL_MIN_10_EXP (-307)

/* maximum integer such that FLT_RADIX raised to that power minus 1 is a
   representable floating point number */
#define FLT_MAX_EXP	127
#define DBL_MAX_EXP	1023
#define LDBL_MAX_EXP	1023

/* maximum integer such that 10 raised to that power is in the range of
   representable floating point numbers */
#define FLT_MAX_10_EXP	38
#define DBL_MAX_10_EXP	308
#define LDBL_MAX_10_EXP 308

/* maximum representable floating point number */
#define FLT_MAX 	3.402823466e+38f
#define DBL_MAX 	1.79769313486231560e+308
#define LDBL_MAX	DBL_MAX

/* minimum positive floating point number x such that 1.0 + x != 1.0 */
#define FLT_EPSILON	1.192092896e-7f
#define DBL_EPSILON	2.2204460492503131e-16
#define LDBL_EPSILON	DBL_EPSILON

/* minimum representable positive floating point number */
#define FLT_MIN 	1.175494351e-38f
#define DBL_MIN 	2.22507385850720160e-308
#define LDBL_MIN	DBL_MIN


#ifndef NO_EXT_KEYS	/* extensions enabled */
/*
 *  8087/80287/80387 math co-processor control information
 */

/* 80(x)87 Control Word Mask and bit definitions. */

#define MCW_EM		0x003f	/* interrupt Exception Masks */
#define EM_INVALID	0x0001	/*   invalid */
#define EM_DENORMAL	0x0002	/*   denormal */
#define EM_ZERODIVIDE	0x0004	/*   zero divide */
#define EM_OVERFLOW	0x0008	/*   overflow */
#define EM_UNDERFLOW	0x0010	/*   underflow */
#define EM_PRECISION	0x0020	/*   inexact result */

#define MCW_IC		0x1000	/* Infinity Control */
#define IC_AFFINE	0x1000	/*   affine */
#define IC_PROJECTIVE	0x0000	/*   projective */

#define MCW_RC		0x0c00	/* Rounding Control */
#define RC_NEAR 	0x0000	/*   near */
#define RC_DOWN 	0x0400	/*   down */
#define RC_UP		0x0800	/*   up */
#define RC_CHOP 	0x0c00	/*   chop */

#define MCW_PC		0x0300	/* Precision Control */
#define PC_24		0x0000	/*    24 bits */
#define PC_53		0x0200	/*    53 bits */
#define PC_64		0x0300	/*    64 bits */

/* 80(x)87 Status Word bit definitions */

#define SW_INVALID	0x0001	/*   invalid */
#define SW_DENORMAL	0x0002	/*   denormal */
#define SW_ZERODIVIDE	0x0004	/*   zero divide */
#define SW_OVERFLOW	0x0008	/*   overflow */
#define SW_UNDERFLOW	0x0010	/*   underflow */
#define SW_INEXACT	0x0020	/*   inexact (precision) */

/* Floating-point error codes */

#define FPE_INVALID		0x81
#define FPE_DENORMAL		0x82
#define FPE_ZERODIVIDE		0x83
#define FPE_OVERFLOW		0x84
#define FPE_UNDERFLOW		0x85
#define FPE_INEXACT		0x86
#define FPE_UNEMULATED		0x87
#define FPE_SQRTNEG		0x88
#define FPE_STACKOVERFLOW	0x8a
#define FPE_STACKUNDERFLOW	0x8b
#define FPE_EXPLICITGEN 	0x8c

unsigned _clear87(void);
unsigned _control87(unsigned,unsigned);
void	 _fpreset(void);
unsigned _status87(void);
#endif

#define _FLOAT_H_INCLUDED
#endif
