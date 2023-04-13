# Makefile by Mark Boady 2022
# Simple Demo For Students doing C++ Projects

# This are global variables. That way we can avoid retyping flags.
CC=g++
STD=--std=c++17
# These define target folders. That way we can change them once up here.
OBJ=obj
BIN=bin


# Each section has a pattern
# [targetname]: [dependencies]
# The target name is the thing we want to make. 
# The dependencies are the files we need to compile successfully.
# When you type make with no target, it uses the first target in the file.
# In this case we want bin/triangle to be compiled.
# We can make a fake target that is dependent on the read first target.
# Assuming the user doesn't know what the file names are both
# make
# and 
# make build
# Will do the right thing.
build: bin/triangle

#make all cleans and rebuilds everything from scratch
all: clean build documentation

# We need src/main.cpp and object/triangle.o to build the program.
# We can use $@ to say "name of target". That way we don't have to retype /bin/triangle
# We can use $^ for the all dependencies. That way we don't need to retype them all.
# Before the compile command you will notice a mkdir command. 
# The command [ -d $(BIN) ] checks if the directory in variable BIN exists.
# If it does, nothing else happens. If it does not, mkdir names it.
# The || is an OR. If the first part is false, then the second part runs.
# If the first part is true, the second part doesn't need to execute.
bin/triangle: src/main.cpp obj/triangle.o
	[ -d $(BIN) ] || mkdir -p $(BIN)
	${CC} ${STD} -o $@ $^

# We have a function in its own h/cpp section.
# It can be pre-compiled before building main. 
# This will give us compile advantages. If you change main.cpp but not triangle.h or triangle.cpp
# they don't need to be recompiled.
# This one has a trick. The code has two dependencies triangle.cpp and triangle.h.
# When we use G++, we only give it the cpp file and not the h file.
# We filter the dependency list to only keep files ending in CPP!
obj/triangle.o: src/triangle.cpp src/triangle.h
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${CC} ${STD} -c -o $@ $(filter %.cpp,$^)

# Most makefiles contain a run command.
# It gives the user a way to test the program and see how it works.
# It is dependent on having the compiled code.
run: bin/triangle
	./bin/triangle 12

# The source files are commented with Doxygen.
# This allows the makefile to produce documentation IF you have Doxygen installed.
# We want the user to control making documentation. 
# Not all users will have doxygen.
# .PHONY means this is a fake target. It can never actually exist.
# If a user types make documentation the commands will always run
.PHONY: documentation
documentation:
	doxygen docConfig
	cd latex && make

# Make Clean erases all the build code.
# This puts the folder back into a simple state with only the written code.
# The -f flag forces removal. It will not ask you to confirm deletes.
clean:
	rm -f obj/*.o
	rm -f -r obj
	rm -f bin/triangle
	rm -f -r bin
	rm -r -f html
	rm -r -f latex
