CC=g++
CFLAGS=--std=c++17 -pthread

all: bin/rend

bin/rend: obj/semaphore.o src/main.cpp
	${CC} ${CFLAGS} -o bin/rend src/main.cpp obj/semaphore.o

obj/semaphore.o: src/semaphore.h src/semaphore.cpp
	${CC} ${CFLAGS} -c -o obj/semaphore.o src/semaphore.cpp

run:
	./bin/rend

clean:
	rm -f obj/*.o
	rm -f bin/rend
