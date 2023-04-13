
CC=g++
CFLAGS=--std=c++17 -pthread

all: bin/phil

bin/phil: obj/semaphore.o obj/philosopher.o src/main.cpp
	${CC} ${CFLAGS} -o bin/phil src/main.cpp obj/semaphore.o obj/philosopher.o

obj/semaphore.o: src/semaphore.h src/semaphore.cpp
	${CC} ${CFLAGS} -c -o obj/semaphore.o src/semaphore.cpp

obj/philosopher.o: src/philosopher.h src/philosopher.cpp
	${CC} ${CFLAGS} -c -o obj/philosopher.o src/philosopher.cpp

run:
	./bin/phil

clean:
	rm -f obj/*.o
	rm -f bin/phil