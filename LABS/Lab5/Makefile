# Melanie Prettyman
# CS 6015 HW1
# Targets:
# clean deletes program, and all .o and .out files
# program compiles the source files of the program into output object files and then links them into an executable
# run runs the program
# test runs the program with the --test option

CXX=c++
CFLAGS=-std=c++11
CCSOURCE=main.cpp cmdline.cpp Expr.cpp tests.cpp parse.cpp
HEADERS=cmdline.h Expr.h catch.h tests.h parse.hpp
OBJECTS=$(CCSOURCE:.cpp=.o)
EXECUTABLE=msdScript
LIBRARY = ../Library_MSDScript/libmsdscript.a

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) *.out

run: $(EXECUTABLE)
	./$(EXECUTABLE)

test: $(EXECUTABLE)
	./$(EXECUTABLE) --test

msdscript_from_Library: $(LIBRARY)
	$(CXX) $(CFLAGS) -o $@ main.cpp -L ../Library_MSDScript -lmsdscript

$(LIBRARY): $(OBJECTS)
	ar -ruv $@ $(OBJECTS)