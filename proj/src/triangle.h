/**
	@file
	@author Mark Boady <mwb33@drexel.edu>
	@date September 22, 2022
	@section Description
 
	A simple function that draws a triangle using * characters. Shows how prototypes and implementations can be seperated.
 */

//These compiler directives ensure the code is only
//included once no matter how many times
// #include appears across all the files.
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

/**
	Draw a right triangle using stars.
	@param x is the number of lines to draw.
 */
void triangle(int x);

#endif
