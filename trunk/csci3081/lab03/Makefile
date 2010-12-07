# $Id: Exp $
# makefile for 3081 lab 3 Fall 2008

CPP = g++
CXX_DIR = ../cxxtest
CXX = $(CXX_DIR)/cxxtestgen.pl

.SUFFIXES : .o .cpp .c
.cpp.o :
	$(CPP) -c -g $<

TESTS = QueueTest.h

OBJS = Node.o Queue.o


all: run_tests

Queue.o: Queue.h Queue.cpp
Node.o: Node.h Node.cpp


# Run the unit tests
run_tests: runner
	./runner

# Build the test runner
runner: runner.cpp $(OBJS)
	$(CPP) -I$(CXX_DIR) -o runner runner.cpp Node.o Queue.o

# Generate the test runner
runner.cpp: $(TESTS)
	$(CXX) --error-printer -o runner.cpp QueueTest.h

# Generate documentation
doc: Doxyfile $(OBJS)
	doxygen

# Clean up
clean: 
	rm runner* *.o


