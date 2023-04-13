/**
	@file
	@author Mark Boady <mwb33@drexel.edu>
	@date September 22, 2022
	@section Description
 
	A simple loop to draw a triangle. Shows how the body and prototypes can be seperated into different files.
 */


//I/O Stream For Printing
#include <iostream>
//Include my Prototypes
#include "triangle.h"

//Draw a right triangle with x rows
//If x=3 we would draw
//
// *
// **
// ***

//Two nested looks the x loop is for rows.
//The j loop is for columns.
void triangle(int x){
    for(int i=0; i < x; i++){
        for(int j=0; j < i+1; j++){
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}
