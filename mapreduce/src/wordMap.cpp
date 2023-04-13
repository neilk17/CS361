//Mark Boady
//Drexel University 2021

//Count words using a sorted map

#include "wordMap.h"

//Constructor
wordMap::wordMap(){
	db = std::map<std::string,int>();
}
//Destructor
wordMap::~wordMap(){
}

//Increase count of word
//by amount
void wordMap::increment(std::string word,
	int amount){
	if(db.count(word)){
		db[word] =
			db[word]+amount;
	}else{
		db.insert(
			std::make_pair(word,
				amount)
		);
	}
}//increment

//Export all the words into
//target queue
void wordMap::exportQueue(
	safeQueue<wordCount>** target){
	//Get an iterator
	std::map<std::string, int>::iterator it
		= db.begin();
	while(it != db.end()){
		std::string myWord = it->first;
		int count = it->second;
		//Location of word
		char fLetter = myWord[0];
		char loc = static_cast<int>(fLetter)-97;
		//Make a wordCount DS
		wordCount wc;
		wc.word = myWord;
		wc.count = count;
		//Add to Queue
		target[loc]->push(wc);
		//Increment iterator
		it++;
	}
}
