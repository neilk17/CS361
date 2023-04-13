CC=g++
FLAGS=--std=c++17 -pthread

bin/race: src/main.cpp src/safeQueue.h obj/race.o
	${CC} ${FLAGS} -o bin/race src/main.cpp obj/race.o

obj/race.o: src/race.cpp src/race.h src/safeQueue.h
	${CC} ${FLAGS} -c -o obj/race.o src/race.cpp

run: bin/race
	bin/race 3

clean:
	rm -f obj/race.o
	rm -f bin/race