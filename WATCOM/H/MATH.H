/*
 *  math.h	Math functions
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _MATH_H_INCLUDED
#pragma pack(1);
extern	double		_HugeValue;
#define HUGE_VAL	_HugeValue

double	acos( double __x );
double	asin( double __x );
double	atan( double __x );
double	atan2( double __y, double __x );
double	ceil( double __x );
double	cos( double __x );
double	cosh( double __x );
double	exp( double __x );
double	fabs( double __x );
double	floor( double __x );
double	fmod( double __x, double __y );
double	frexp( double __value, int *__exp );
double	ldexp( double __x, int __exp );
double	log( double __x );
double	log10( double __x );
double	modf( double __value, double *__iptr );
double	pow( double __x, double __y );
double	sin( double __x );
double	sinh( double __x );
double	sqrt( double __x );
double	tan( double __x );
double	tanh( double __x );

/* non-ANSI */
#ifndef NO_EXT_KEYS	/* extensions enabled */

struct	complex {
	double	real;
	double	imag;
};

double	acosh( double __x );
double	asinh( double __x );
double	atanh( double __x );
double	cabs( struct complex );
double	hypot( double __x, double __y );
double	j0( double __x );
double	j1( double __x );
double	jn( int __n, double __x );
double	log2( double __x );
double	y0( double __x );
double	y1( double __x );
double	yn( int __n, double __x );

/* The following struct is used to record errors detected in the math library.
 * matherr is called with a pointer to this struct for possible error recovery.
 */

struct	exception {
	int	type;		/* type of error, see below */
	char	*name;		/* name of math function */
	double	arg1;		/* value of first argument to function */
	double	arg2;		/* second argument (if indicated) */
	double	retval; 	/* default return value */
};

#define DOMAIN		1	/* argument domain error */
#define SING		2	/* argument singularity  */
#define OVERFLOW	3	/* overflow range error  */
#define UNDERFLOW	4	/* underflow range error */
#define TLOSS		5	/* total loss of significance */
#define PLOSS		6	/* partial loss of significance */

int	matherr( struct exception * );
double	_matherr( struct exception * );
#endif	/* NO_EXT_KEYS */


#ifndef __NO_MATH_OPS
/*
    Defining the __NO_MATH_OPS macro will stop the compiler from recogizing
    the following functions as intrinsic operators.
*/

double	__LOG( double __x );
double	__COS( double __x );
double	__SIN( double __x );
double	__TAN( double __x );
double	__SQRT( double __x );
double	__FABS( double __x );
double	__POW( double __x, double __y );
double	__ATAN2( double __y, double __x );
double	__FMOD( double __x, double __y );
double	__ACOS( double __x );
double	__ASIN( double __x );
double	__ATAN( double __x );
double	__COSH( double __x );
double	__EXP( double __x );
double	__LOG10( double __x );
double	__SINH( double __x );
double	__TANH( double __x );

#define log( __x )	    __LOG( __x )
#define cos( __x )	    __COS( __x )
#define sin( __x )	    __SIN( __x )
#define tan( __x )	    __TAN( __x )
#define sqrt( __x )	    __SQRT( __x )
#define fabs( __x )	    __FABS( __x )
#define pow( __x, __y )     __POW( __x, __y )
#define atan2( __y, __x )   __ATAN2( __y, __x )
#define fmod( __x, __y )    __FMOD( __x, __y )
#define acos( __x )	    __ACOS( __x )
#define asin( __x )	    __ASIN( __x )
#define atan( __x )	    __ATAN( __x )
#define cosh( __x )	    __COSH( __x )
#define exp( __x )	    __EXP( __x )
#define log10( __x )	    __LOG10( __x )
#define sinh( __x )	    __SINH( __x )
#define tanh( __x )	    __TANH( __x )

#endif
#pragma pack();
#define _MATH_H_INCLUDED
#endif
