//Mark Boady
//Drexel University 2021

//Count words using a sorted map

#ifndef _WORD_MAP_H_
#define _WORD_MAP_H_

#include <string>
#include <map>
#include "stringTools.h"
#include "safeQueue.h"

class wordMap{
	private:
		std::map<std::string,int> db;
	public:
		//Create a new empty map
		wordMap();
		//Destructor
		~wordMap();
		//Increment Word
		void increment(std::string word,
			int amount);
		//Export Word List to queue
		void exportQueue(
			safeQueue<wordCount>** target);
};

#endif
