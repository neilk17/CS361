
CC=g++
CFLAGS=--std=c++17 -pthread
OBJ=obj
BIN=bin

all: bin/race

bin/race: obj/semaphore.o obj/dicequeue.o obj/leaderboard.o src/main.cpp
	[ -d $(BIN) ] || mkdir -p $(BIN)
	${CC} ${CFLAGS} -o bin/race src/main.cpp obj/semaphore.o obj/dicequeue.o obj/leaderboard.o

obj/semaphore.o: src/semaphore.h src/semaphore.cpp
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${CC} ${CFLAGS} -c -o obj/semaphore.o src/semaphore.cpp
obj/dicequeue.o: src/semaphore.h src/dicequeue.h src/dicequeue.cpp
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${CC} ${CFLAGS} -c -o obj/dicequeue.o src/dicequeue.cpp
obj/leaderboard.o: src/semaphore.h src/leaderboard.h src/leaderboard.cpp
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${CC} ${CFLAGS} -c -o obj/leaderboard.o src/leaderboard.cpp

run: bin/race
	./bin/race 3 || true

.PHONY: doc
doc:
	doxygen config
	cd latex && make

clean:
	rm -f obj/*.o
	rm -f bin/race
	rm -r -f bin
	rm -r -f obj
	rm -r -f html
	rm -r -f latex