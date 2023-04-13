//Mark Boady
//Drexel University 2021

//Helper functions and structures
//to work with text better

#ifndef _STRING_TOOLS_H_
#define _STRING_TOOLS_H_

#include <string>

//A data structure
//stores <word, count>
//Key, value pairs
struct wordCount{
	//Word to Index On
	std::string word;
	//Count for word
	int count;
	//Default Constructor
	wordCount(){
		word="";
		count=0;
	}
};//wordCount

//Convert a Word to Lower Case
std::string toLower(std::string myWord);

//Clean Word
//Remove all non-letter characters
//Also, makes all lower case
std::string cleanString(std::string myWord);

#endif
