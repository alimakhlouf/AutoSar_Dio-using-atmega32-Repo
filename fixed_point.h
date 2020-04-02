/*
 * fixed_point.h
 *
 * Created: 6/4/2019 10:35:19 ص
 *  Author: hppp
 */ 
/* ----------------------------------------------------------------------------
[FILE NAME]:    fixed_point.h

[AUTHOR]:       Ali MAkhlouf

[DATE CREATED]: 6/4/2019 10:35:19 AM

[DESCRIPTION]:  a library header file containing MACROs for performing fixed
				point calculations
				 
-----------------------------------------------------------------------------*/


#ifndef FIXED_POINT_H_
#define FIXED_POINT_H_

/* ----------------------------------------------------------------------------
[MACRO Name] : MULTIPLY_FIXED_POINT
[Description] : This function is responsible multiplying 2 fixed point numbers
[NOTE] :
	the fixed point multiplication goes like this x=(y*z)>>PRECISION_BITS (we 
	shift right by the number of precision bits because multiplying 2 fixed 
	numbers THE RESULT HAS DOUBLE THE NUMBER OF PRECISION BITS SO WE HALF IT
	BY SHIFTING THE NUMBER OF PRECISION BITS)
[Args] :
[in] -A
	this ARG is the first operand in the multiplication
[IN] -B
	this ARG is the second operand in the multiplication
[IN] -PRECISION_BITS
	this ARG is the number of the precision bits
-----------------------------------------------------------------------------*/
#define FIXP_MUL(A, B, precision_bits) (((A) * (B)) >> (precision_bits))

/* -----------------------------------------------------------------------
[MACRO Name] : DIVIDE_FIXED_POINT
[Description] : This function is responsible dividing 2 fixed point numbers
[NOTE] :
	the fixed point multiplication goes like this x=((y<<1)*z)
	(we shift y left by the number of precision bits because
	dividing 2 fixed numbers , the numbers will remove each others
	precision bits (just like 20/30) so the result won't contain
	any precision bits and will be integer number we avoid this
	step by shifting the first operand left by the number of
	precision bits
[Args] :
[in] -A
	this ARG is the first operand(a fixed point number) in the division
[in] -B
	this ARG is the second operand(a fixed point number) in the division
[in] -orecision_bits
	this ARG is the number of the precision bits
-----------------------------------------------------------------------------*/
#define FIXP_DIV(A, B, precision_bits) (((A) << (precision_bits)) / (B))

/* -----------------------------------------------------------------------
[MACRO Name] : FIXP_CONVERT
[Description] : This function is responsible converting a number to a its
	fixed point representation
[Args] :
[in] -number
	this ARG is the number to be converted
[in] -precision_bits
	this ARG is the number of the precision bits
-----------------------------------------------------------------------------*/
#define FIXP_CONVERT(number, precision) ((number) << (precision))

/* -----------------------------------------------------------------------
[MACRO Name] : FIXP_REVERT
[Description] : This function is responsible reverting a fixed point number to 
	its typical numerical representation
[Args] :
[in] -number
	this ARG is the number to be reverted
[in] -precision_bits
	this ARG is the number of the precision bits
-----------------------------------------------------------------------------*/
#define FIXP_REVERT(number, precision) ((number) >> (precision))
#endif /* FIXED_POINT_H_ */