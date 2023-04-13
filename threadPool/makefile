STD=--std=c++17 -pthread
GCC=g++
OBJ=obj
BIN=bin

bin/main: obj/safeQueue
	[ -d $(BIN) ] || mkdir -p $(BIN)
	${GCC} ${STD} -o bin/main src/main.cpp

obj/safeQueue:
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${GCC} ${STD} -c -o obj/safeQueue src/safeQueue.h


.PHONY: run clean

run: bin/main
	./bin/main

clean:
	rm -r obj/*.o
	rm -rf bin
	rm -rf obj

