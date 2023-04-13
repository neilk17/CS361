//Mark Boady
//Drexel University 2021

//Helper functions and structures
//to work with text better

#include "stringTools.h"

//Convert a Word to Lower Case
std::string toLower(std::string myWord){
	std::string newWord="";
	for(int i=0; i < myWord.size(); i++){
		char c = myWord[i];
		newWord +=std::tolower(c);
	}
	return newWord;
}

//Clean Word
//Remove all non-letter characters
//Also, makes all lower case
std::string cleanString(std::string myWord){
	myWord = toLower(myWord);
	//Make a new string
	std::string newWord="";
	//Loop over characters
	for(int i=0; i < myWord.size(); i++){
		char c = myWord[i];
		//Only Keep letters
		if(c >= 'a' && c <= 'z'){
			newWord+=c;
		}
	}
	return newWord;
	
}
