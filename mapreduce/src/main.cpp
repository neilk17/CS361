
//Mark Boady
//Drexel University 2021

//Conceptual Example of Map Reduce
//To show threads and locking

#include <string>
#include <iostream>
#include <filesystem>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <map>
//Custom Libraries
#include "safeQueue.h"
#include "stringTools.h"
#include "wordMap.h"
#include "taskQueue.h"

void loadFiles(
	taskQueue<std::filesystem::path>* files,
	std::string folder);

void mapper(
	taskQueue<std::filesystem::path>* files,
	safeQueue<wordCount>** alphabet);
	
void reducer(
	int id,
	int tNum,
	safeQueue<wordCount>** alphabet);

int main(int argc, char** argv){
	//Task 0: Setup
	//Make sure a folder is given
	if(argc!=2){
		std::cout << "Input Folder Required."
			<< std::endl;
		return 1;
	}
	//Get the folder
	std::string folder = std::string(argv[1]);
	//Print out into
	std::cout << "Counting all words in "
		<< folder
		<< "." << std::endl;
	//Task 1: Make A queue to store the tasks
	taskQueue<std::filesystem::path>* files
		= new taskQueue<std::filesystem::path>();
	//Task 2: Array of 26 queues for results
	safeQueue<wordCount>** alphabet
		= new safeQueue<wordCount>*[26];
	for(int i=0; i < 26; i++){
		alphabet[i] = new safeQueue<wordCount>();
	}
	//Task 3: Initiate Map Threads
	//These map and shuffle
	int tNum=8;
	std::thread* workers = new std::thread[tNum];
	for(int i=0; i < tNum; i++){
		workers[i]=std::thread(mapper,files,alphabet);
	}
	//Task 4: Generate tasks
	loadFiles(files,folder);
	//Task 5: Wait on all mappers to finish
	for(int i=0; i < tNum; i++){
		workers[i].join();
	}
	//Task 6: Reduce all the values into one collection
	//Each thread takes different letters
	for(int i=0; i < tNum; i++){
		workers[i]=std::thread(reducer,i,tNum,alphabet);
	}
	for(int i=0; i < tNum; i++){
		workers[i].join();
	}
	//Task 7: Print Out the final results
	for(int i=0; i < 26; i++){
		safeQueue<wordCount>* Q = alphabet[i];
		while(!Q->empty()){
			wordCount wc = Q->waitAndPop();
			std::cout << wc.word << " : "
				<< wc.count
				<< std::endl;
		}
	}
	return 0;
}
		
		
void loadFiles(
	taskQueue<std::filesystem::path>* files,
	std::string folder){
	//Load all files in directory
	for(const auto & entry:
		std::filesystem::
		recursive_directory_iterator(folder)){
		std::filesystem::path myPath = entry.path();
		files->addTask(myPath);
	}
    files->close();
	return;
}

void mapper(
	taskQueue<std::filesystem::path>* files,
	safeQueue<wordCount>** alphabet){
    std::filesystem::path file;
	while(files->getTask(file)){
		//Open File and search
		std::ifstream myfile;
		myfile.open(file.c_str());
		//Failed to open
		if(!myfile.is_open()){
			continue;
		}
		//Make a map for totals
		wordMap db;
		//Loop over words
		std::string word;
		while(myfile >> word){
			//Convert to lower case
			word=cleanString(word);
			//Skip nonsense words
			if(word.size() < 1){
				continue;
			}
			//Word worth counting
			db.increment(word,1);
		}
		//Insert into output Queues
		db.exportQueue(alphabet);
	}
}

void reducer(
	int id,
	int tNum,
	safeQueue<wordCount>** alphabet){
	//There are 26 letters
	for(int i=id; i < 26; i+=tNum){
		safeQueue<wordCount>* myLetter =
			alphabet[i];
		//Loop Over that queue
		wordMap db;
		wordCount wc;
		while(!myLetter->empty()){
			wc = myLetter->waitAndPop();
			db.increment(wc.word,
				wc.count);
		}
		db.exportQueue(alphabet);
	}
}
