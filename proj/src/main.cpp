/**
 @mainpage CS361 - Triangle Example
 @section Description
 
 This is a CPP program that just draws a triangle. It is designed to show many of the feature of CPP program.
 
 To build the code you can use make. You have the following targets available:
 
 Build the program
	
	 make
 
 Build the documentation. Documenation will appear in html and latex (pdf version) folders.
 
	 make documentation
 
 Clean up all the compiled code to start from scratch
 
	 make clean
 
 Run a test version of the program with twelve lines
 
	 make run
 
 To run the program
 
	 ./bin/triangle [number of lines in triangle]
 
 @section Notes
 This is not designed for production use, it is an educational example.
 */

/**
	@file
	@author Mark Boady <mwb33@drexel.edu>
	@date September 22, 2022
	@section Description
 
	The main program for the triangle program. This file is designed to show you how to work with command line arguments.
 */

//I/O Stream for Error
#include <iostream>
//For working with strings
#include <string>
//Include Triangle Lib
#include "triangle.h"

/**
	This program reads 1 command line argument and prints a triangle with that many lines.
	@param argc is the number of command line arguments
	@param argv contains the arguments themselves. The value of argv[1] is the number of lines to draw.
	@return 0 is returned on success and 1 on bad command line input.
 */
int main(int argc, char** argv){
    if(argc!=2){
        std::cout << "Usage: "
            << argv[0]
            << " [number rows]"
            << std::endl;
        return 1;
    }
    //Store Input as a String
    std::string input(argv[1]);
    //Convert String to Number
    int value;
    try{
        value = stoi(input);
    }catch(std::invalid_argument e){
        std::cout << input
            << " is not a number."
            << std::endl;
        return 2;
    }
    //Draw the Triangle
    triangle(value);
}
