CC=g++
FLAGS=--std=c++17 -pthread

bin/wordcount: src/main.cpp obj/stringTools.o src/safeQueue.h obj/wordMap.o src/taskQueue.h
	${CC} ${FLAGS} -o bin/wordcount obj/wordMap.o obj/stringTools.o src/main.cpp 

obj/stringTools.o: src/stringTools.h src/stringTools.cpp
	${CC} ${FLAGS} -c -o obj/stringTools.o src/stringTools.cpp

obj/wordMap.o: src/wordMap.h src/wordMap.cpp
	${CC} ${FLAGS} -c -o obj/wordMap.o src/wordMap.cpp

run: bin/wordcount
	bin/wordcount data

clean:
	rm -f obj/*.o
	rm -f bin/wordcount