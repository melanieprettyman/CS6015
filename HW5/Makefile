#Melanie Prettyman
#CS 6015 HW1
#Targets:
#clean deletes program, and all .o and .out files
#program compiles the source files of the program into an output executable
#run runs the program 

CXX=c++
CFLAGS= -std=c++11
CCSOURCE= main.cpp cmdline.cpp Expr.cpp tests.cpp
HEADERS= cmdline.h Expr.h catch.h tests.h

msdScript: $(CCSOURCE) $(HEADERS)
	$(CXX) $(CFLAGS) -o msdScript $(CCSOURCE)


clean: 
	rm -f *.o *.out program

run: msdScript
	./msdScript

test: msdScript
	./msdScript --test


