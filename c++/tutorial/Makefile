STD=--std=c++17 
GCC=g++
OBJ=obj
BIN=bin

hello: hello.cpp
	${GCC} ${STD} -o hello hello.cpp

run: ./hello
	g/hello || true

clean: 
	rm hello

